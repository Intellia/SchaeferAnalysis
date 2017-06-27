## STEP 1: BWA aln
bwa aln -Y -q20 -t 16 \
	mm10.fa \
	$(echo $samp.name).1.fastq.gz > $(echo $samp.name).1.sai

bwa aln -Y -q20 -t 16 \
	mm10.fa \
	$(echo $samp.name).2.fastq.gz > $(echo $samp.name).2.sai

bwa sampe \
	mm10.fa \
	$(echo $samp.name).1.sai \
	$(echo $samp.name).2.sai \
	$(echo $samp.name).1.fastq.gz \
	$(echo $samp.name).2.fastq.gz | \
	samtools view -bS - $(echo $samp.name).bam

samtools index $(echo $samp.name).bam


## STEP 2: adding RG info
java -jar ~/Downloads/picard-tools-1.83/AddOrReplaceReadGroups.jar \
	MAX_RECORDS_IN_RAM=2000000 \
	CREATE_INDEX=true \
	SORT_ORDER=coordinate \
	VALIDATION_STRINGENCY=SILENT \
	I=$(echo $samp.name).bam \
	O=$(echo $samp.name).rg.bam \
	RGID=$(echo $samp.name) \
	RGLB=$(echo $samp.name) \
	RGSM=$(echo $samp.name) \
	RGPU=$(echo $samp.name) \
	RGCN=$(echo $samp.name) \
	RGDS=$(echo $samp.name) \
	RGPL=$(echo $samp.name)



## STEP 3: Mark Duplicates
java -jar ~/Downloads/picard-tools-1.83/MarkDuplicates.jar \
	CREATE_INDEX=true \
	MAX_RECORDS_IN_RAM=2000000 \
	VALIDATION_STRINGENCY=SILENT \
	M=$(echo $samp.name).dedup.metrics \
	I=$(echo $samp.name).rg.bam  \
	O=$(echo $samp.name).dedup.bam 



## STEP 4: Realignment Target Creator
java -jar ~/Downloads/GenomeAnalysisTK.jar \
	-T RealignerTargetCreator \
	--interval_padding 200 \
	-rf BadCigar \
	-nt 24 \
	-R mm10.fa \
	-I F03.dedup.bam \
	-I F05.dedup.bam \
	-I Control.dedup.bam \
	-o realigner.joint.intervals



## STEP 5: Indel Realignment
java -jar ~/Downloads/GenomeAnalysisTK.jar \
 	-T IndelRealigner \
 	-rf BadCigar \
 	--consensusDeterminationModel USE_READS \
 	-dcov 1000 \
	-R mm10.fa \
	-I F03.dedup.bam \
	-I F05.dedup.bam \
	-I Control.dedup.bam \
 	-targetIntervals realigner.joint.intervals \
 	-nWayOut realigner.joint.map



## STEP 6: Generatinng BQSR Covariates
java -jar ~/Downloads/GenomeAnalysisTK.jar \
	-T BaseRecalibrator \
	--interval_padding 200 \
	--downsample_to_fraction 0.1 \
	-rf BadCigar \
	-nct 4 \
	-R mm10.fa \
	-I $(echo $samp.name).dedup.joint.realigned.bam \
	-o $(echo $samp.name).recal.grp \
	-knownSites dbSNP_v138.vcf.gz \
	-knownSites mgp.v3.indels.clean.vcf.gz



## STEP 7: Applying BQSR Adjustments
java -jar ~/Downloads/GenomeAnalysisTK.jar \
 	-T PrintReads \
 	-nct 4 \
 	-rf BadCigar \
 	--disable_indel_quals \
 	--emit_original_quals \
 	-R mm10.fa \
 	-I $(echo $samp.name).dedup.joint.realigned.bam \
 	-o $(echo $samp.name).recalibrated.bam \
 	-BQSR $(echo $samp.name).recal.grp


## Step 8: Running Callers
## Callers were run for all possible combinations of Control, F03, and F05 as t and n

## Running Lofreq
lofreq2_somatic.py \
	-n $(echo $samp.name).recalibrated.bam \
	-t $(echo $samp.name).recalibrated.bam \
	-f mm10.fa \
	-o $(echo $pair.name).strelka

## Running Strelka
./configureStrelkaWorkflow.pl \
	--tumor $(echo $samp.name).recalibrated.bam \
	--normal $(echo $samp.name).recalibrated.bam \
	--ref mm10.fa \
	--config strelka_config_bwa_default.ini \
	--output-dir $(echo $pair.name).strelka
cd $(echo $$pair.name).strelka
make 

## Running Mutect
java -jar  muTect-1.1.7.jar \
	--analysis_type MuTect \
	--num_threads 1 \
	--reference_sequence mm10.fa \
	--input_file:normal $(echo $samp.name).recalibrated.bam \
	--input_file:tumor $(echo $samp.name).recalibrated.bam \
	--baqGapOpenPenalty 30 \
	--out $(echo $pair.name).mutext



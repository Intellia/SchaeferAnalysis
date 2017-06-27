## STEP 1: Aligning Reads
bwa mem \
	-t 30 \
	mm10.fa \
	$(echo $samp.name).1.fastq.gz \
	$(echo $samp.name).2.fastq.gz |
	samtools view -bS >> $(echo $samp.name).bam

samtools index $(echo $samp.name).bam

## STEP 2: Adding Read Groups
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
	M=$(echo $samp.name).metrics \
	I=$(echo $samp.name).rg.bam  \
	O=$(echo $samp.name).dedup.bam 

## STEP 4: Generatinng BQSR Covariates
java -jar ~/Downloads/GenomeAnalysisTK.jar \
	-T BaseRecalibrator \
	--interval_padding 200 \
	--downsample_to_fraction 0.1 \
	-rf BadCigar \
	-R mm10.fa \
	-I $(echo $samp.name).dedup.bam \
	-o $(echo $samp.name).recal.grp \
	-knownSites dbSNP_v138.vcf.gz \
	-knownSites mgp.v3.indels.clean.vcf.gz

## STEP 5: Applying BQSR Adjustments
java -jar ~/Downloads/GenomeAnalysisTK.jar \
 	-T PrintReads \
 	-nct 4 \
 	-rf BadCigar \
 	--disable_indel_quals \
 	--emit_original_quals \
 	-R mm10.fa \
 	-I $(echo $samp.name).dedup.bam \
 	-o $(echo $samp.name).recal.bam \
 	-BQSR $(echo $samp.name).recal.grp

 ## STEP 6: Running Haplotype Caller
java –jar GenomeAnalysisTK.jar \
	-T HaplotypeCaller \
	--disable_auto_index_creation_and_locking_when_reading_rods \
	-R mm10.fa \
	-o $(echo $samp.name).vcf.gz \
	-I $(echo $samp.name).recal.bam \
	--minPruning 3 \
	--maxNumHaplotypesInPopulation 200 \
	-ERC GVCF \
	--max_alternate_alleles 3 \
	-variant_index_parameter 128000 \
	-variant_index_type LINEAR \
	-contamination 0.0





## STEP 1: adding RG info
<PATH>/java -Djava.io.tmpdir=<PATH> -Xmx24576m -XX:ParallelGCThreads=4 \
	-jar <PATH>/picard-tools/picard-tools-1.83/AddOrReplaceReadGroups.jar \
	MAX_RECORDS_IN_RAM=2000000 \
	CREATE_INDEX=true \
	SORT_ORDER=coordinate \
	VALIDATION_STRINGENCY=SILENT \
	I=$bam_dir/FXX_ATTCAGAA-AGGCGAAG_BC6RMGANXX_L001_001.aln.sampe.bam \
	O=$bam_dir/FXX_ATTCAGAA-AGGCGAAG_BC6RMGANXX_L001_001.aln.bam \
	RGID=FXX_ATTCAGAA-AGGCGAAG_BC6RMGANXX_L001_001 \
	RGLB=FXX \
	RGSM=FXX \
	RGPU="C6RMGANXX.1.ATTCAGAA-AGGCGAAG" \
	RGCN="NYGenome" \
	RGDS="RefVersion:GRCm38.70-Sequencer:HiSeq-2500(HiSeq-v4)" \
	RGPL="illumina"



## STEP 2: Mark Duplicates
## *merged.bam is after merging across lanes, already done when downloading from SRA
## Do this on one sample at a time
<PATH>/java -Djava.io.tmpdir=<PATH> -Xmx24576m -XX:ParallelGCThreads=5 \
	-jar <PATH>/picard-tools/picard-tools-1.83/MarkDuplicates.jar \
	CREATE_INDEX=true \
	MAX_RECORDS_IN_RAM=2000000 \
	VALIDATION_STRINGENCY=SILENT \
	M=$Sample_dir/qc/FXX.dedup.metrics \
	I=$Sample_dir/analysis/FXX.merged.bam \
	O=$Sample_dir/analysis/FXX.dedup.bam



## STEP 3: Realignment Target Creator
## Doing this on all samples at once
<PATH>/java -Djava.io.tmpdir=<PATH> -Xmx73728m \
	-jar <PATH>/GenomeAnalysisTK/GenomeAnalysisTK-3.4-0/GenomeAnalysisTK.jar \
	-T RealignerTargetCreator \
	--interval_padding 200 \
	-rf BadCigar \
	-nt 24 \
	-R <PATH>/Mus_musculus/GRCm38.70/Mus_musculus.GRCm38.70.dna.fasta \
	-I $Sample_dir/analysis/FXX.dedup.bam \
	-I $Sample_dir/analysis/FXX.dedup.bam \
	-I $Sample_dir/analysis/FXX.dedup.bam \
	-o $Sample_dir/analysis/FXX.for_realigner.joint.intervals



## STEP 4: Indel Realignment
## Doing this on all samples at once
## will need to generate this file -nWayOut $Sample_dir/analysis/for_realigner.joint.map
<PATH>/java -Djava.io.tmpdir=<PATH> -Xmx73728m \
 	-jar <PATH>/GenomeAnalysisTK/GenomeAnalysisTK-3.4-0/GenomeAnalysisTK.jar \
 	-T IndelRealigner \
 	-rf BadCigar \
 	--consensusDeterminationModel USE_READS \
 	-dcov 1000 \
 	-R <PATH>/Mus_musculus/GRCm38.70/Mus_musculus.GRCm38.70.dna.fasta \
 	-I $Sample_dir/analysis/FXX.dedup.bam \
 	-I $Sample_dir/analysis/FXX.dedup.bam \
 	-I $Sample_dir/analysis/FXX.dedup.bam \
 	-targetIntervals $Sample_dir/analysis/FXX.for_realigner.joint.intervals \
 	-nWayOut $Sample_dir/analysis/for_realigner.joint.map



## STEP 5: Generatinng BQSR Covariates
## use known site vcfs
<PATH>/java -Djava.io.tmpdir=<PATH> -Xmx24576m \
	-jar <PATH>/GenomeAnalysisTK/GenomeAnalysisTK-3.4-0/GenomeAnalysisTK.jar \
	-T BaseRecalibrator \
	--interval_padding 200 \
	--downsample_to_fraction 0.1 \
	-rf BadCigar \
	-nct 4 \
	-R <PATH>/Mus_musculus/GRCm38.70/Mus_musculus.GRCm38.70.dna.fasta \
	-I $Sample_dir/analysis/FXX.dedup.joint.realigned.bam \
	-o $Sample_dir/qc/FXX.recal.grp \
	-knownSites <PATH>/Mus_musculus/GRCm38.70/dbSNP_v138.vcf.gz \
	-knownSites <PATH>/Mus_musculus/GRCm38.70/mgp.v3.indels.clean.vcf.gz



## STEP 6: Applying BQSR Adjustments
$java_bin_dir/bin/java -Djava.io.tmpdir=<PATH> -Xmx24576m \
 	-jar <PATH>/GenomeAnalysisTK/GenomeAnalysisTK-3.4-0/GenomeAnalysisTK.jar \
 	-T PrintReads \
 	-nct 4 \
 	-rf BadCigar \
 	--disable_indel_quals \
 	--emit_original_quals \
 	-R <PATH>/Resources/Mus_musculus/GRCm38.70/Mus_musculus.GRCm38.70.dna.fasta \
 	-I $Sample_dir/analysis/FXX.dedup.joint.realigned.bam \
 	-o $Sample_dir/analysis/FXX.recalibrated.bam \
 	-BQSR $Sample_dir/qc/FXX.recal.grp


## ????? 
## Something happens where they go from *recalibrated.bam to *final.bam
## *final.bam is never created by this code

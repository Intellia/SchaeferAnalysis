

## STEP 1: adding RG info
java -Xmx24576m -XX:ParallelGCThreads=4 \
	-jar ~/Downloads/picard-tools-1.83/AddOrReplaceReadGroups.jar \
	MAX_RECORDS_IN_RAM=2000000 \
	CREATE_INDEX=true \
	SORT_ORDER=coordinate \
	VALIDATION_STRINGENCY=SILENT \
	I=~/Documents/OT/Align/FXX_ATTCAGAA-AGGCGAAG_BC6RMGANXX_L001_001.aln.sampe.bam \
	O=~/Documents/OT/Align/FXX_ATTCAGAA-AGGCGAAG_BC6RMGANXX_L001_001.aln.bam \
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
java -Xmx24576m -XX:ParallelGCThreads=5 \
	-jar ~/Downloads/picard-tools-1.83/AddOrReplaceReadGroups.jar \
	CREATE_INDEX=true \
	MAX_RECORDS_IN_RAM=2000000 \
	VALIDATION_STRINGENCY=SILENT \
	M=~/Documents/OT/Align/FXX.dedup.metrics \
	I=~/Documents/OT/Align/FXX.merged.bam \
	O=~/Documents/OT/Align/FXX.dedup.bam



## STEP 3: Realignment Target Creator
## Doing this on all samples at once
java -Xmx73728m \
	-jar ~/Downloads/GenomeAnalysisTK.jar \
	-T RealignerTargetCreator \
	--interval_padding 200 \
	-rf BadCigar \
	-nt 24 \
	-R <PATH>/Mus_musculus/GRCm38.70/Mus_musculus.GRCm38.70.dna.fasta \
	-I ~/Documents/OT/Align/FXX.dedup.bam \
	-I ~/Documents/OT/Align/FXX.dedup.bam \
	-I ~/Documents/OT/Align/FXX.dedup.bam \
	-o ~/Documents/OT/Align/FXX.for_realigner.joint.intervals



## STEP 4: Indel Realignment
## Doing this on all samples at once
## will need to generate this file -nWayOut $Sample_dir/analysis/for_realigner.joint.map
java -Xmx73728m \
 	-jar <PATH>/GenomeAnalysisTK/GenomeAnalysisTK-3.4-0/GenomeAnalysisTK.jar \
 	-T IndelRealigner \
 	-rf BadCigar \
 	--consensusDeterminationModel USE_READS \
 	-dcov 1000 \
 	-R <PATH>/Mus_musculus/GRCm38.70/Mus_musculus.GRCm38.70.dna.fasta \
 	-I ~/Documents/OT/Align/FXX.dedup.bam \
 	-I ~/Documents/OT/Align/FXX.dedup.bam \
 	-I ~/Documents/OT/Align/FXX.dedup.bam \
 	-targetIntervals ~/Documents/OT/Align/FXX.for_realigner.joint.intervals \
 	-nWayOut ~/Documents/OT/Align/for_realigner.joint.map



## STEP 5: Generatinng BQSR Covariates
## use known site vcfs
java -Xmx24576m \
	-jar <PATH>/GenomeAnalysisTK/GenomeAnalysisTK-3.4-0/GenomeAnalysisTK.jar \
	-T BaseRecalibrator \
	--interval_padding 200 \
	--downsample_to_fraction 0.1 \
	-rf BadCigar \
	-nct 4 \
	-R <PATH>/Mus_musculus/GRCm38.70/Mus_musculus.GRCm38.70.dna.fasta \
	-I ~/Documents/OT/Align/FXX.dedup.joint.realigned.bam \
	-o ~/Documents/OT/Align/FXX.recal.grp \
	-knownSites <PATH>/Mus_musculus/GRCm38.70/dbSNP_v138.vcf.gz \
	-knownSites <PATH>/Mus_musculus/GRCm38.70/mgp.v3.indels.clean.vcf.gz



## STEP 6: Applying BQSR Adjustments
java -Xmx24576m \
 	-jar <PATH>/GenomeAnalysisTK/GenomeAnalysisTK-3.4-0/GenomeAnalysisTK.jar \
 	-T PrintReads \
 	-nct 4 \
 	-rf BadCigar \
 	--disable_indel_quals \
 	--emit_original_quals \
 	-R <PATH>/Resources/Mus_musculus/GRCm38.70/Mus_musculus.GRCm38.70.dna.fasta \
 	-I ~/Documents/OT/Align/FXX.dedup.joint.realigned.bam \
 	-o ~/Documents/OT/Align/FXX.recalibrated.bam \
 	-BQSR ~/Documents/OT/Align/FXX.recal.grp


## ????? 
## Something happens where they go from *recalibrated.bam to *final.bam
## *final.bam is never created by this code

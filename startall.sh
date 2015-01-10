#!/bin/bash

#
# apply MIPVentricleSegmentation to all test images
#

PATIDLIST="11 14 20 25 29 47 57"

for PATID in ${PATIDLIST}
do
    CALL="bin/MIPVentricleSegmentation images/pat${PATID}_flair.mhd pat${PATID}_seg.pgm"
    echo "Aufruf:"
    echo $CALL 
    $CALL 
done

#
# apply MIPSegmentationEvaluation to compare with available expert segmentations (expert 1 only)
#
PATIDLIST="20 25 29"

for PATID in ${PATIDLIST}
do
    if [ ! -e "pat${PATID}_seg.pgm" ]; then
       echo "Segmentation missing: pat${PATID}_seg.pgm" 
       continue
    fi

    CALL="bin/MIPSegmentationEvaluation pat${PATID}_seg.pgm images/pat${PATID}_seg_expert1.pgm"
    echo "Aufruf:"
    echo $CALL 
    $CALL 
done



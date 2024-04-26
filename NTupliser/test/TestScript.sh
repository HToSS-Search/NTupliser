#!/bin/bash
thedataset=$1
# thedataset=`echo $thedataset | sed -e 's/[-]/HYPHEN/g'`
# thedataset=`echo $thedataset | sed -e 's/\//SLASH/g'`
# thedataset=`echo $thedataset | sed -e 's/\_/UNDERSCORE/g'`
# ISGGH=$2
# hadronType=$3
# skim=$4
# RUNERA=$5
# DOCUTS=$6
maxEvts=$2
#echo "thedataset is $thedataset"
#echo "ISGGH is $ISGGH"
#echo "hadronType is $hadronType"
#echo "skim is $skim"
#echo "RUNERA is $RUNERA"
#echo "DOCUTS is $DOCUTS"
#echo "maxEvts is $maxEvts"

cms_xrd='root://cms-xrd-global.cern.ch//'
full_path="$cms_xrd$thedataset"

#cp nTupliser_miniAOD_cfg.py testconfig.py
#sed -ie "s/THESKIM/$skim/g" testconfig.py
#sed -ie "s/DOCUTS/$DOCUTS/g" testconfig.py
#sed -ie "s/ISGGH/$ISGGH/g" testconfig.py
#sed -ie "s/THERUNERA/$RUNERA/g" testconfig.py
#sed -ie "s/THEHADRON/$hadronType/g" testconfig.py

cmsRun testconfig.py inputFiles=$full_path maxEvents=$maxEvts
#rm testconfig.py

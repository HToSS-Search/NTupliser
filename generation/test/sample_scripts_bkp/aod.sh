#!/bin/bash

wd=$PWD
charge=Q2Over3
rel="CMSSW_10_2_3_M100_$charge/src"
reldir=$wd/$rel
cd $reldir

source $VO_CMS_SW_DIR/cmsset_default.sh
eval `scram runtime -sh`
echo "CMSSW intialized to "$CMSSW_BASE

echo $PWD
export HOME=$PWD

cp $wd/cfgfiles_M100/ZTo2FCP_M100_pythia8_aod.py ZTo2FCP_M100_pythia8_aod_$1.py
sed -i "s/Q1/${charge}/g" ZTo2FCP_M100_pythia8_aod_$1.py
sed -i "s/ZTo2FCP_M100_${charge}_pythia8_digi/ZTo2FCP_M100_${charge}_pythia8_digi_$1/g" ZTo2FCP_M100_pythia8_aod_$1.py
sed -i "s/ZTo2FCP_M100_${charge}_pythia8_aod/ZTo2FCP_M100_${charge}_pythia8_aod_$1/g" ZTo2FCP_M100_pythia8_aod_$1.py
cmsRun ZTo2FCP_M100_pythia8_aod_$1.py
rm ZTo2FCP_M100_pythia8_aod_$1.py

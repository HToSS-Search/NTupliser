#!/bin/bash

wd=$PWD
charge=Q2Over3
rel="CMSSW_10_2_3_M100_$charge/src"
reldir=$wd/$rel
cd $reldir

source $VO_CMS_SW_DIR/cmsset_default.sh
eval `scram runtime -sh`
echo "CMSSW intialized to "$CMSSW_BASE

cp $wd/cfgfiles_M100/ZTo2FCP_M100_${charge}_pythia8_gen-sim.py ZTo2FCP_M100_${charge}_pythia8_gen-sim_$1.py
sed -i "s/initialSeed = SSS/initialSeed = $1/g" ZTo2FCP_M100_${charge}_pythia8_gen-sim_$1.py 
sed -i "s/ZTo2FCP_M100_${charge}_pythia8_gen-sim/ZTo2FCP_M100_${charge}_pythia8_gen-sim_$1/g" ZTo2FCP_M100_${charge}_pythia8_gen-sim_$1.py
cmsRun ZTo2FCP_M100_${charge}_pythia8_gen-sim_$1.py
rm ZTo2FCP_M100_${charge}_pythia8_gen-sim_$1.py

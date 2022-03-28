#!/bin/bash
source /cvmfs/cms.cern.ch/cmsset_default.sh
#export SCRAM_ARCH=slc7_amd64_gcc900
#if [ -r CMSSW_12_0_2_patch1/src ] ; then
# echo release CMSSW_12_0_2_patch1 already exists
#else
#scram p CMSSW CMSSW_12_0_2_patch1
#fi
#cd CMSSW_12_0_2_patch1/src
nevts=-1
ctauS=100
in_dir="/pnfs/iihe/cms/store/user/sdansana/HToSS/MC/DIGI2RAW/DIGI2RAW_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS${ctauS}_2021_220322"
out_dir="/pnfs/iihe/cms/store/user/sdansana/HToSS/MC/AODSIM/AODSIM_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS${ctauS}_2021_220323"
wd="/user/sdansana/HToSS-Search"
rel="CMSSW_12_0_2_patch1/src/NTupliser/generation/test/sample_scripts"
reldir=$wd/$rel
cd $reldir

export X509_USER_PROXY=/user/$USER/x509up_u$(id -u $USER)
eval `scram runtime -sh`
echo "CMSSW intialized to "$CMSSW_BASE

cp NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS${ctauS}_TuneCP_13TeV-powheg-pythia8_AOD_cfg.py NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS${ctauS}_TuneCP_13TeV-powheg-pythia8_AOD_cfg_$1.py
sed -i "s/step2/step2_$1/g" NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS${ctauS}_TuneCP_13TeV-powheg-pythia8_AOD_cfg_$1.py
sed -i "s/step3/step3_$1/g" NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS${ctauS}_TuneCP_13TeV-powheg-pythia8_AOD_cfg_$1.py

## cmsRun to run the job
cmsRun NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS${ctauS}_TuneCP_13TeV-powheg-pythia8_AOD_cfg_$1.py
rm NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS${ctauS}_TuneCP_13TeV-powheg-pythia8_AOD_cfg_$1.py

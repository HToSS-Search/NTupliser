#!/bin/bash
source /cvmfs/cms.cern.ch/cmsset_default.sh
nevts=-1
ctauS=0
in_dir="/pnfs/iihe/cms/store/user/sdansana/HToSS/MC/GEN-SIM/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2021_220318/CRAB3_GEN-SIM_NLO_HZJ_MH125_MS2_ctauS100_2021_220318/220318_170527/0000"
out_dir="/pnfs/iihe/cms/store/user/sdansana/HToSS/MC/DIGI2RAW/DIGI2RAW_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS${ctauS}_2021_220322"
wd="/user/sdansana/HToSS-Search"
rel="MC_production/CMSSW_12_0_2_patch1/src/generation_scripts/sample_scripts"
reldir=$wd/$rel
cd $reldir

export X509_USER_PROXY=/user/$USER/x509up_u$(id -u $USER)
eval `scram runtime -sh`
echo "CMSSW intialized to "$CMSSW_BASE

cp cfg_files/HToSSTo2Mu2Hadrons_MH125_MS2_ctauS${ctauS}_TuneCP_13TeV-powheg-pythia8_GS_cfg.py HToSSTo2Mu2Hadrons_MH125_MS2_ctauS${ctauS}_TuneCP_13TeV-powheg-pythia8_GS_cfg_$1.py
sed -i "s/initialSeed = SSS/initialSeed = $1/g" HToSSTo2Mu2Hadrons_MH125_MS2_ctauS${ctauS}_TuneCP_13TeV-powheg-pythia8_GS_cfg_$1.py
sed -i "s/step0/step0_$1/g" HToSSTo2Mu2Hadrons_MH125_MS2_ctauS${ctauS}_TuneCP_13TeV-powheg-pythia8_GS_cfg_$1.py
## confirm that number of events is -1 or 5000 and not 10 or something
## manually changing the output directory
## cmsRun to run the job
cmsRun HToSSTo2Mu2Hadrons_MH125_MS2_ctauS${ctauS}_TuneCP_13TeV-powheg-pythia8_GS_cfg_$1.py
rm HToSSTo2Mu2Hadrons_MH125_MS2_ctauS${ctauS}_TuneCP_13TeV-powheg-pythia8_GS_cfg_$1.py

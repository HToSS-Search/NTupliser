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
in_dir="/pnfs/iihe/cms/store/user/sdansana/HToSS/MC/GEN-SIM/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2021_220318/CRAB3_GEN-SIM_NLO_HZJ_MH125_MS2_ctauS100_2021_220318/220318_170527/0000"
out_dir="/pnfs/iihe/cms/store/user/sdansana/HToSS/MC/DIGI2RAW/DIGI2RAW_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS${ctauS}_2021_220322"
wd="/user/sdansana/HToSS-Search"
rel="CMSSW_12_0_2_patch1/src/NTupliser/generation/test/sample_scripts"
reldir=$wd/$rel
cd $reldir

#export X509_USER_PROXY=/user/$USER/x509up_u$(id -u $USER)
eval `scram runtime -sh`
#echo "CMSSW intialized to "$CMSSW_BASE

## download gen configuration file for GEN-SIM request MUO-RunIISummer18GS-00002 
## NEED TO REFER TO RAW GITHUBUSER TO COPY FILE 
#curl -s --insecure https://raw.githubusercontent.com/HToSS-Search/NTupliser/CMSSW_12_0_2_patch1/generation/genfragments/NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS100_TuneCP_13TeV-powheg-pythia8.py --retry 2 --create-dirs -o Configuration/GenProduction/python/HToSSTo2Mu2Hadrons/NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS100_TuneCP_13TeV-powheg-pythia8.py
#[ -s Configuration/GenProduction/python/HToSSTo2Mu2Hadrons/NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS100_TuneCP_13TeV-powheg-pythia8.py ] || exit $?;

#scram b
#cd ../../

## cmsDriver to properly configure the job
#cmsDriver.py  --python_filename NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS${ctauS}_TuneCP_13TeV-powheg-pythia8_DR_cfg_$1.py --eventcontent FEVTDEBUGHLT --customise Configuration/DataProcessing/Utils.addMonitoring --datatier GEN-SIM-DIGI-RAW --fileout file:$out_dir/step2_$1.root --pileup_input "dbs:/Neutrino_E-10_gun/Run3Summer21PrePremix-120X_mcRun3_2021_realistic_v6-v2/PREMIX" --conditions 120X_mcRun3_2021_realistic_v6 --step DIGI,DATAMIX,L1,DIGI2RAW,HLT:@relval2021 --procModifiers premix_stage2 --geometry DB:Extended --filein file:$in_dir/step0_$1.root --datamix PreMix --era Run3 --no_exec --mc -n $nevts
cp NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS${ctauS}_TuneCP_13TeV-powheg-pythia8_DR_cfg.py NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS${ctauS}_TuneCP_13TeV-powheg-pythia8_DR_cfg_$1.py
#sed -i "s/Q1/${charge}/g" NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS${ctauS}_TuneCP_13TeV-powheg-pythia8_DR_cfg_$1.py
sed -i "s/step0/step0_$1/g" NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS${ctauS}_TuneCP_13TeV-powheg-pythia8_DR_cfg_$1.py
sed -i "s/step1/step1_$1/g" NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS${ctauS}_TuneCP_13TeV-powheg-pythia8_DR_cfg_$1.py
## cmsRun to run the job
#cmsRun NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS${ctauS}_TuneCP_13TeV-powheg-pythia8_DR_cfg_$1.py
#rm NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS${ctauS}_TuneCP_13TeV-powheg-pythia8_DR_cfg_$1.py

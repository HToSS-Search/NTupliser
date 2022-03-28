#!/bin/bash
source /cvmfs/cms.cern.ch/cmsset_default.sh
#export SCRAM_ARCH=slc7_amd64_gcc900
#if [ -r CMSSW_12_0_2_patch1/src ] ; then
# echo release CMSSW_12_0_2_patch1 already exists
#else
#scram p CMSSW CMSSW_12_0_2_patch1
#fi
#cd CMSSW_12_0_2_patch1/src
nevts=10
ctauS=100
out_dir="/pnfs/iihe/cms/store/user/sdansana/HToSS/MC/GEN-SIM/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2021_220322"
wd="/user/sdansana/HToSS-Search"
rel="CMSSW_12_0_2_patch1/src/NTupliser/generation/test/sample_scripts"
reldir=$wd/$rel
cd $reldir

eval `scram runtime -sh`
echo "CMSSW intialized to "$CMSSW_BASE
#export X509_USER_PROXY=/user/$USER/x509up_u$(id -u $USER)

## download gen configuration file for GEN-SIM request MUO-RunIISummer18GS-00002 
## NEED TO REFER TO RAW GITHUBUSER TO COPY FILE 
#curl -s --insecure https://raw.githubusercontent.com/HToSS-Search/NTupliser/CMSSW_12_0_2_patch1/generation/genfragments/NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS100_TuneCP_13TeV-powheg-pythia8.py --retry 2 --create-dirs -o Configuration/GenProduction/python/HToSSTo2Mu2Hadrons/NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS100_TuneCP_13TeV-powheg-pythia8.py
#[ -s Configuration/GenProduction/python/HToSSTo2Mu2Hadrons/NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS100_TuneCP_13TeV-powheg-pythia8.py ] || exit $?;

#scram b
#cd ../../

## cmsDriver to properly configure the job
cmsDriver.py Configuration/GenProduction/python/HToSSTo2Mu2Hadrons/NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS${ctauS}_TuneCP_13TeV-powheg-pythia8.py --python_filename NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS${ctauS}_TuneCP_13TeV-powheg-pythia8_GS_cfg_$1.py --eventcontent RAWSIM --customise Configuration/DataProcessing/Utils.addMonitoring --datatier GEN-SIM --fileout file:$out_dir/step0_$1.root --conditions 120X_mcRun3_2021_realistic_v5 --beamspot Run3RoundOptics25ns13TeVLowSigmaZ --customise_commands "process.g4SimHits.Physics.G4GeneralProcess = cms.bool(False)"\\nprocess.source.numberEventsInLuminosityBlock="cms.untracked.uint32(100)" --step LHE,GEN,SIM --geometry DB:Extended --era Run3 --no_exec --mc -n $nevts
## cmsRun to run the job
cmsRun NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS${ctauS}_TuneCP_13TeV-powheg-pythia8_GS_cfg_$1.py
rm NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS${ctauS}_TuneCP_13TeV-powheg-pythia8_GS_cfg_$1.py

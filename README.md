VUB-EOS-Searches-nTuples
==============
***

The CMSSW_12_0_2_patch1 branch contains code from CMSSW_10_6_27 branch which is modified to work for Run-3 MC. 

Remember to add all prerequisite modules/packages from CMSSW and build before compiling this branch. 

Prerequisites: 
Get CMSSW_12_0_2_patch1 
```bash
cmsrel CMSSW_12_0_2_patch1
cd CMSSW_12_0_2_patch1/src/
cmsenv
```
Get the EGM scaling/smearing correction (enabled by default)
```bash
git cms-init
git cms-addpkg RecoEgamma/EgammaTools  ### essentially just checkout the package from CMSSW
scram b -j4
```
Get all egamma post-processing (i.e. to convert miniAODv1 to v2) [Not required for generation yet and causes errors]
```bash
git cms-init
git clone https://github.com/cms-egamma/EgammaPostRecoTools.git
mv EgammaPostRecoTools/python/EgammaPostRecoTools.py RecoEgamma/EgammaTools/python/.
scram b -j4
```

Steps: 
```bash
git clone Branch-Name ### checkout relevant branch
mkdir -p Configuration/GenProduction/python/HToSSTo2Mu2Hadrons/ ### needed for CMSSW to find genfragments
cp -r NTupliser/generation/genfragments/* Configuration/GenProduction/python/HToSSTo2Mu2Hadrons/. ###copy all genfragments to created dir
scram b -j4
```

#EXO - event generation
To get the generation package (including generation of cards):
```bash
git clone git@github.com:cms-sw/genproductions.git genproductions
```

The Higgs (gluon fusion produced) decay via scalars are found in bin/Powheg/production/2017/13TeV/Higgs/gg_H_quark-mass-effects_NNPDF31_13TeV and in
https://github.com/cms-sw/genproductions/tree/master/bin/Powheg/production/pre2017/13TeV/gg_H_quark-mass-effects_JHUGenV628_HWWLNuQQ_NNPDF30_13TeV

gridpack to be changed to 14TeV one found in /bin/Powheg/production/pre2017/14TeV/gg_H_quark-mass-effects_NNPDF30_14TeV and in https://github.com/cms-sw/genproductions/tree/master/bin/Powheg/production/pre2017/14TeV/gg_H_quark-mass-effects_NNPDF30_14TeV . In cvmfs, /cvmfs/cms.cern.ch/phys_generator/gridpacks//slc6_amd64_gcc700/14TeV/powheg/V2/gg_H_quark-mass-effects_HZZ4L_NNPDF30_14TeV_M125_JHUGenV724/v1/gg_H_quark-mass-effects_HZZ4L_NNPDF30_14TeV_M125_JHUGenV724.tgz
---

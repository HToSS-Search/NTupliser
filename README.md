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
git clone Branch-Name
mkdir -p Configuration/Configuration/GenProduction/python/HToSSTo2Mu2Hadrons/ ### needed for CMSSW to find genfragments
cp -r NTupliser/generation/genfragments/* Configuration/GenProduction/python/HToSSTo2Mu2Hadrons/. ###copy all genfragments to created dir
scram b -j4
```

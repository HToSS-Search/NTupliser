VUB-EOS-Searches-nTuples
==============
***

The CMSSW_10_6_27 branch contains code from CMSSW_9_4_10 branch which is modified to work for Run 2 UL data and MC. 

To get all egamma post-processing (i.e. to convert miniAODv1 to v2)
```bash
git cms-init
git clone git@github.com:cms-egamma/EgammaPostRecoTools.git  EgammaUser/EgammaPostRecoTools
cd  EgammaUser/EgammaPostRecoTools
git checkout master
cd -
echo $CMSSW_BASE
cd $CMSSW_BASE/src
```

***
To run ecalBadCalibReducedMINIAODFilter for 2017-2018 miniAOD (STILL WIP FOR UL - DO NOT USE)
```bash
git cms-addpkg RecoMET/METFilters
```
***

To be fixed:

- Check DeepCSV and DeepCMVA b-taggers actually work and include them in the skimmer's AnalysisEvent.h

***

#EXO - event generation
To get the generation package (including generation of cards):
```bash
git clone git@github.com:cms-sw/genproductions.git genproductions
```

The Higgs (gluon fusion produced) decay via scalars are found in bin/Powheg/production/2017/13TeV/Higgs/gg_H_quark-mass-effects_NNPDF31_13TeV and in
https://github.com/cms-sw/genproductions/tree/master/bin/Powheg/production/pre2017/13TeV/gg_H_quark-mass-effects_JHUGenV628_HWWLNuQQ_NNPDF30_13TeV

---


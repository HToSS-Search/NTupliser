# -*- coding: utf-8 -*-
from collections import namedtuple
from datetime import datetime

from CRABClient.UserUtilities import config

Dataset = namedtuple("Dataset", "process dataset")

## UL Datasets

## 2016 APV Datasets
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2016_APV",     "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2016_APV_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2016_APV_210519-33e4c8a3b4f5317ecda8cb830deafda2/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1_2016_APV",     "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS10_2016_APV_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS10_2016_APV_210519-33e4c8a3b4f5317ecda8cb830deafda2/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2016_APV",    "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1_2016_APV_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1_2016_APV_210519-33e4c8a3b4f5317ecda8cb830deafda2/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2016_APV",   "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2016_APV_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2016_APV_210519-33e4c8a3b4f5317ecda8cb830deafda2/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1000_2016_APV",  "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1000_2016_APV_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1000_2016_APV_210519-33e4c8a3b4f5317ecda8cb830deafda2/USER")

#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS0_2016_APV",     "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS0_2016_APV_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS0_2016_APV_210519-33e4c8a3b4f5317ecda8cb830deafda2/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2016_APV",     "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2016_APV_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2016_APV_210519-33e4c8a3b4f5317ecda8cb830deafda2/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2016_APV",    "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2016_APV_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2016_APV_210519-33e4c8a3b4f5317ecda8cb830deafda2/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2016_APV",   "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2016_APV_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2016_APV_210519-33e4c8a3b4f5317ecda8cb830deafda2/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1000_2016_APV",  "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1000_2016_APV_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1000_2016_APV_210519-33e4c8a3b4f5317ecda8cb830deafda2/USER")

## 2016 Datasets
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2016",         "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2016_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2016_210519-1da7033ad45096c8e0d0c59d4e469959/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1_2016",         "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1_2016_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1_2016_210519-1da7033ad45096c8e0d0c59d4e469959/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS10_2016",        "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS10_2016_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS10_2016_210519-1da7033ad45096c8e0d0c59d4e469959/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2016",       "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2016_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2016_210519-1da7033ad45096c8e0d0c59d4e469959/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1000_2016",      "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1000_2016_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1000_2016_210519-1da7033ad45096c8e0d0c59d4e469959/USER")

#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS0_2016",         "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS0_2016_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS0_2016_210519-1da7033ad45096c8e0d0c59d4e469959/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2016",         "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2016_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2016_210519-1da7033ad45096c8e0d0c59d4e469959/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2016",        "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2016_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2016_210519-1da7033ad45096c8e0d0c59d4e469959/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2016"        "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2016_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2016_210519-1da7033ad45096c8e0d0c59d4e469959/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1000_2016",      "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1000_2016_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1000_2016_210519-1da7033ad45096c8e0d0c59d4e469959/USER")

## 2017 Datasets
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2017",         "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2017_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2017_210519-882d39ca920c8d24d19c6799ea93610c/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1_2017",         "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1_2017_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1_2017_210519-882d39ca920c8d24d19c6799ea93610c/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS10_2017",        "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS10_2017_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS10_2017_210519-882d39ca920c8d24d19c6799ea93610c/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2017",       "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2017_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2017_210519-882d39ca920c8d24d19c6799ea93610c/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1000_2017",      "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1000_2017_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1000_2017_210519-882d39ca920c8d24d19c6799ea93610c/USER")

#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS0_2017",         "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS0_2017_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS0_2017_210519-882d39ca920c8d24d19c6799ea93610c/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2017",         "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2017_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2017_210519-882d39ca920c8d24d19c6799ea93610c/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2017",        "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2017_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2017_210519-882d39ca920c8d24d19c6799ea93610c/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2017",       "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2017_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2017_210519-882d39ca920c8d24d19c6799ea93610c/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1000_2017",      "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1000_2017_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1000_2017_210519-882d39ca920c8d24d19c6799ea93610c/USER")

## 2018 Datasets
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2018",         "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2018_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2018_210519-1fc3ecee7c51c31cd349cc9364673796/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1_2018",         "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1_2018_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1_2018_210519-1fc3ecee7c51c31cd349cc9364673796/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS10_2018",        "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS10_2018_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS10_2018_210519-1fc3ecee7c51c31cd349cc9364673796/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2018",       "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2018_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2018_210519-1fc3ecee7c51c31cd349cc9364673796/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1000_2018",      "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1000_2018_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1000_2018_210519-1fc3ecee7c51c31cd349cc9364673796/USER")

#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS0_2018",         "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS0_2018_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS0_2018_210519-1fc3ecee7c51c31cd349cc9364673796/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2018",         "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2018_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2018_210519-1fc3ecee7c51c31cd349cc9364673796/USER
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2018",        "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2018_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2018_210519-1fc3ecee7c51c31cd349cc9364673796/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2018",       "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2018_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2018_210519-1fc3ecee7c51c31cd349cc9364673796/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1000_2018",      "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1000_2018_210519/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1000_2018_210519-1fc3ecee7c51c31cd349cc9364673796/USER")

###############

## tZq
#dataset = Dataset("tZq_2016_APV", "")
#dataset = Dataset("tZq_2016",     "")
#dataset = Dataset("tZq_2017",     "/tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM") ###
#dataset = Dataset("tZq_2018",     "/tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer19UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM") ###

## tHq
#dataset = Dataset("tHq_2016_APV", "")
#dataset = Dataset("tHq_2016", "")
#dataset = Dataset("tHq_2017", "")
#dataset = Dataset("tHq_2018", "")

## tWZ/tWll
#dataset = Dataset("tWz_tWll_2016_APV", "")
#dataset = Dataset("tWz_tWll_2016", "")
#dataset = Dataset("tWz_tWll_2017", "")
#dataset = Dataset("tWz_tWll_2018", "")

## ttZ
#dataset = Dataset("ttZ_ll_2016_APV", "")
#dataset = Dataset("ttZ_ll_2016", "")
#dataset = Dataset("ttZ_ll_2017", "/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("ttZ_ll_2018", "/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer19UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM") ###
#dataset = Dataset("ttZ_qq_2016_APV", "")
#dataset = Dataset("ttZ_qq_2016", "")
#dataset = Dataset("ttZ_qq_2017", "/TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("ttZ_qq_2018", "/TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")

## ttW
#dataset = Dataset("ttW_lnu_2016_APV", "")
#dataset = Dataset("ttW_lnu_2016", "")
#dataset = Dataset("ttW_lnu_2017", "/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("ttW_lnu_2018", "/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")

#dataset = Dataset("ttW_qq_2016_APV", "
#dataset = Dataset("ttW_qq_2016", "
#dataset = Dataset("ttW_qq_2017", "
#dataset = Dataset("ttW_qq_2018", "/TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")

## ttH (bb)
#dataset = Dataset("ttH_bb_2016_APV", "")
#dataset = Dataset("ttH_bb_2016", "")
#dataset = Dataset("ttH_bb_2017", "")
#dataset = Dataset("ttH_bb_2018", "")

## ttH (non bb)
#dataset = Dataset("ttH_nonbb_2016_APV", "")
#dataset = Dataset("ttH_nonbb_2016", "")
#dataset = Dataset("ttH_nonbb_2017", "")
#dataset = Dataset("ttH_nonbb_2018", "")

# ttγ
#dataset = Dataset("ttgamma_2016_APV", "")
#dataset = Dataset("ttgamma_2016", "")
#dataset = Dataset("ttgamma_2017", "")
#dataset = Dataset("ttgamma_2018", "")

# W+jets
#dataset = Dataset("Wjets_2016_APV", "")
#dataset = Dataset("Wjets_2016", "")
#dataset = Dataset("Wjets_2017", "/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("Wjets_2018", "/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")

## WW (2l2nu)
#dataset = Dataset("WW_2l2nu_2016_APV", "")
#dataset = Dataset("WW_2l2nu_2016", "")
#dataset = Dataset("WW_2l2nu_2017", "")
#dataset = Dataset("WW_2l2nu_2018", "")

## WW (lnu2q)
#dataset = Dataset("WW_lnu2q_2016_APV", "")
#dataset = Dataset("WW_lnu2q_2016", "")
#dataset = Dataset("WW_lnu2q_2017", "")
#dataset = Dataset("WW_lnu2q_2018", "")

## WZ (3lnu + up to 1 jet)
#dataset = Dataset("WZ_3lnu_2016_APV", "")
#dataset = Dataset("WZ_3lnu_2016", "")
#dataset = Dataset("WZ_3lnu_2017", "")
#dataset = Dataset("WZ_3lnu_2018", "")

## WZ (2l2q)
#dataset = Dataset("WZ_2l2q_2016_APV", "")
#dataset = Dataset("WZ_2l2q_2016", "")
#dataset = Dataset("WZ_2l2q_2017", "")
#dataset = Dataset("WZ_2l2q_2018", "")

## WZ (lnu2q)
#dataset = Dataset("WZ_lnu2q_2016_APV", "")
#dataset = Dataset("WZ_lnu2q_2016", "")
#dataset = Dataset("WZ_lnu2q_2017", "")
#dataset = Dataset("WZ_lnu2q_2018", "")

#dataset = Dataset("WZ_l3nu_2016_APV",  "")
#dataset = Dataset("WZ_l3nu_2016",  "")
#dataset = Dataset("WZ_l3nu_2017",  "")
#dataset = Dataset("WZ_l3nu_2018",  "")

## ZZ (4l)
#dataset = Dataset("ZZ_4l_2016_APV", "")
#dataset = Dataset("ZZ_4l_2016", "")
#dataset = Dataset("ZZ_4l_2017", "")
#dataset = Dataset("ZZ_4l_2018", "")

## ZZ (2l2nu)
#dataset = Dataset("ZZ_2l2nu_2016_APV", "")
#dataset = Dataset("ZZ_2l2nu_2016", "")
#dataset = Dataset("ZZ_2l2nu_2017", "/ZZTo2L2Nu_TuneCP5_13TeV_powheg_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("ZZ_2l2nu_2018", "/ZZTo2L2Nu_TuneCP5_13TeV_powheg_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")

## ZZ (2l2q)
#dataset = Dataset("ZZ_2l2q_2016_APV", "")
#dataset = Dataset("ZZ_2l2q_2016", "")
#dataset = Dataset("ZZ_2l2q_2017", "")
#dataset = Dataset("ZZ_2l2q_2018", "")

### WWW
#dataset = Dataset("WWW_2016_APV", "")
#dataset = Dataset("WWW_2016", "")
#dataset = Dataset("WWW_2017", "/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("WWW_2018", "/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")

## WWZ
#dataset = Dataset("WWZ_2016_APV", "")
#dataset = Dataset("WWZ_2016", "")
#dataset = Dataset("WWZ_2017", "/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("WWZ_2018", "/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")

## WZZ
#dataset = Dataset("WZZ_2016_APV", "")
#dataset = Dataset("WZZ_2016", "")
#dataset = Dataset("WZZ_2017", "")
#dataset = Dataset("WZZ_2018", "")

## ZZZ
#dataset = Dataset("ZZZ_2016_APV", "")
#dataset = Dataset("ZZZ_2016", "")
#dataset = Dataset("ZZZ_2017", "/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("ZZZ_2018", "/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")

## ttbar
#dataset = Dataset("ttbar_hadronic_2016_APV", "" )
#dataset = Dataset("ttbar_hadronic_2016", "")
#dataset = Dataset("ttbar_hadronic_2017", "/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM") ###
#dataset = Dataset("ttbar_hadronic_2018", "/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")

#dataset = Dataset("ttbar_semileptonic_2016_APV", "")
#dataset = Dataset("ttbar_semileptonic_2016", "")
#dataset = Dataset("ttbar_semileptonic_2017", "/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM") ###
#dataset = Dataset("ttbar_semileptonic_2018", "/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")

#dataset = Dataset("ttbar_2l2v_2016_APV", "")
#dataset = Dataset("ttbar_2l2v_2016", "")
#dataset = Dataset("ttbar_2l2v_2017", "/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("ttbar_2l2v_2018", "/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")

## tW
#dataset = Dataset("tW_2016_APV", "")
#dataset = Dataset("tW_2016", "")
#dataset = Dataset("tW_2017", "")
#dataset = Dataset("tW_2018", "")

## tbarW
#dataset = Dataset("tbarW_2016_APV", "")
#dataset = Dataset("tbarW_2016", "")
#dataset = Dataset("tbarW_2017", "")
#dataset = Dataset("tbarW_2018", "")

## t s-channel
#dataset = Dataset("t_s_channel_2016_APV", "")
#dataset = Dataset("t_s_channel_2016", "")
#dataset = Dataset("t_s_channel_2017", "/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM") ###
#dataset = Dataset("t_s_channel_2018", "/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer19UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM") ###

# t t-channel
#dataset = Dataset("t_t_channel_2016_APV", "")
#dataset = Dataset("t_t_channel_2016", "")
#dataset = Dataset("t_t_channel_2017", "/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM") ###
#dataset = Dataset("t_t_channel_2018", "/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer19UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM") ###

## tbar t-channel
#dataset = Dataset("tbar_t_channel_2016_APV", "")
#dataset = Dataset("tbar_t_channel_2016", "")
#dataset = Dataset("tbar_t_channel_2017", "/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM") ###
#dataset = Dataset("tbar_t_channel_2018", "/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer19UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM") ###

# Zjets pt binned
#dataset = Dataset("DYJetsToLL_Pt-0To50",    "")
#dataset = Dataset("DYJetsToLL_Pt-50To100",  "")
#dataset = Dataset("DYJetsToLL_Pt-100To250", "")
#dataset = Dataset("DYJetsToLL_Pt-250To400", "")
#dataset = Dataset("DYJetsToLL_Pt-400To650", "")
#dataset = Dataset("DYJetsToLL_Pt-650ToInf", "")

#dataset = Dataset("DYJetsToLL_Pt-0To50_2016",    "")
#dataset = Dataset("DYJetsToLL_Pt-50To100_2016",  "")
#dataset = Dataset("DYJetsToLL_Pt-100To250_2016", "")
#dataset = Dataset("DYJetsToLL_Pt-250To400_2016", "")
#dataset = Dataset("DYJetsToLL_Pt-400To650_2016", "")
#dataset = Dataset("DYJetsToLL_Pt-650ToInf_2016", "")

#dataset = Dataset("DYJetsToLL_Pt-0To50_2017",    "")
#dataset = Dataset("DYJetsToLL_Pt-50To100_2017",  "")
#dataset = Dataset("DYJetsToLL_Pt-100To250_2017", "")
#dataset = Dataset("DYJetsToLL_Pt-250To400_2017", "")
#dataset = Dataset("DYJetsToLL_Pt-400To650_2017", "")
#dataset = Dataset("DYJetsToLL_Pt-650ToInf_2017", "")

#dataset = Dataset("DYJetsToLL_Pt-0To50_2018",    "")
#dataset = Dataset("DYJetsToLL_Pt-50To100_2018",  "")
#dataset = Dataset("DYJetsToLL_Pt-100To250_2018", "")
#dataset = Dataset("DYJetsToLL_Pt-250To400_2018", "")
#dataset = Dataset("DYJetsToLL_Pt-400To650_2018", "")
#dataset = Dataset("DYJetsToLL_Pt-650ToInf_2018", "")

# WG?
#dataset = Dataset("WG_lnug_2016_APV", "")
#dataset = Dataset("WG_lnug_2016", "")
#dataset = Dataset("WG_lnug_2017", "/WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("WG_lnug_2018", "/WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")

# ZG?
#dataset = Dataset("ZG_llg_2016_APV", "")
#dataset = Dataset("ZG_llg_2016", "")
#dataset = Dataset("ZG_llg_2017", "/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("ZG_llg_2018", "/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")

# QCD MuEnrichedPt15
#dataset = Dataset("QCD_Pt-20toInf_MuEnrichedPt15_2016_APV", "")
#dataset = Dataset("QCD_Pt-20toInf_MuEnrichedPt15_2016", "")
#dataset = Dataset("QCD_Pt-20toInf_MuEnrichedPt15_2017", "")
#dataset = Dataset("QCD_Pt-20toInf_MuEnrichedPt15_2018", "")

# QCD MuEnrichedPt5
#dataset = Dataset("QCD_Pt-15to20_MuEnrichedPt5_2016_APV", "")
#dataset = Dataset("QCD_Pt-20to30_MuEnrichedPt5_2016_APV", "")
#dataset = Dataset("QCD_Pt-30to50_MuEnrichedPt5_2016_APV", "")
#dataset = Dataset("QCD_Pt-50to80_MuEnrichedPt5_2016_APV", "")
#dataset = Dataset("QCD_Pt-80to120_MuEnrichedPt5_2016_APV", "")
#dataset = Dataset("QCD_Pt-120to170_MuEnrichedPt5_2016_APV", "")
#dataset = Dataset("QCD_Pt-170to300_MuEnrichedPt5_2016_APV", "")
#dataset = Dataset("QCD_Pt-300to470_MuEnrichedPt5_2016_APV", "")
#dataset = Dataset("QCD_Pt-470to600_MuEnrichedPt5_2016_APV", "")
#dataset = Dataset("QCD_Pt-600to800_MuEnrichedPt5_2016_APV", "")
#dataset = Dataset("QCD_Pt-800to1000_MuEnrichedPt5_2016_APV", "")
#dataset = Dataset("QCD_Pt-1000toInf_MuEnrichedPt5_2016_APV", "")

#dataset = Dataset("QCD_Pt-15to20_MuEnrichedPt5_2016", "")
#dataset = Dataset("QCD_Pt-20to30_MuEnrichedPt5_2016", "")
#dataset = Dataset("QCD_Pt-30to50_MuEnrichedPt5_2016", "")
#dataset = Dataset("QCD_Pt-50to80_MuEnrichedPt5_2016", "")
#dataset = Dataset("QCD_Pt-80to120_MuEnrichedPt5_2016", "")
#dataset = Dataset("QCD_Pt-120to170_MuEnrichedPt5_2016", "")
#dataset = Dataset("QCD_Pt-170to300_MuEnrichedPt5_2016" "")
#dataset = Dataset("QCD_Pt-300to470_MuEnrichedPt5_2016", "")
#dataset = Dataset("QCD_Pt-470to600_MuEnrichedPt5_2016", "")
#dataset = Dataset("QCD_Pt-600to800_MuEnrichedPt5_2016", "")
#dataset = Dataset("QCD_Pt-800to1000_MuEnrichedPt5_2016", "")
#dataset = Dataset("QCD_Pt-1000toInf_MuEnrichedPt5_2016", "")

#dataset = Dataset("QCD_Pt-15to20_MuEnrichedPt5_2017", "/QCD_Pt-15to20_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM") ###
#dataset = Dataset("QCD_Pt-20to30_MuEnrichedPt5_2017", "/QCD_Pt-20to30_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM") ###
#dataset = Dataset("QCD_Pt-30to50_MuEnrichedPt5_2017", "/QCD_Pt-30to50_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM") ###
#dataset = Dataset("QCD_Pt-50to80_MuEnrichedPt5_2017", "/QCD_Pt-50to80_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM") ###
#dataset = Dataset("QCD_Pt-80to120_MuEnrichedPt5_2017", "/QCD_Pt-80to120_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM") ###
#dataset = Dataset("QCD_Pt-120to170_MuEnrichedPt5_2017", "/QCD_Pt-120to170_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM") ###
#dataset = Dataset("QCD_Pt-170to300_MuEnrichedPt5_2017", "/QCD_Pt-170to300_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM") ###
#dataset = Dataset("QCD_Pt-300to470_MuEnrichedPt5_2017", "/QCD_Pt-300to470_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM") ###
#dataset = Dataset("QCD_Pt-470to600_MuEnrichedPt5_2017", "/QCD_Pt-470to600_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM") ###
#dataset = Dataset("QCD_Pt-600to800_MuEnrichedPt5_2017", "/QCD_Pt-600to800_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM") ###
#dataset = Dataset("QCD_Pt-800to1000_MuEnrichedPt5_2017", "/QCD_Pt-800to1000_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM") ###
#dataset = Dataset("QCD_Pt-1000toInf_MuEnrichedPt5_2017", "/QCD_Pt-1000toInf_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM") ###

#dataset = Dataset("QCD_Pt-15to20_MuEnrichedPt5_2018", "/QCD_Pt-15to20_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM") ###
#dataset = Dataset("QCD_Pt-20to30_MuEnrichedPt5_2018", "/QCD_Pt-20to30_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM") ###
#dataset = Dataset("QCD_Pt-30to50_MuEnrichedPt5_2018", "/QCD_Pt-30to50_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM") ###
#dataset = Dataset("QCD_Pt-50to80_MuEnrichedPt5_2018", "/QCD_Pt-50to80_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM") ###
#dataset = Dataset("QCD_Pt-80to120_MuEnrichedPt5_2018", "/QCD_Pt-80to120_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM") ###
#dataset = Dataset("QCD_Pt-120to170_MuEnrichedPt5_2018", "/QCD_Pt-120to170_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM") ###
#dataset = Dataset("QCD_Pt-170to300_MuEnrichedPt5_2018", "/QCD_Pt-170to300_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM") ###
#dataset = Dataset("QCD_Pt-300to470_MuEnrichedPt5_2018", "/QCD_Pt-300to470_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM") ###
#dataset = Dataset("QCD_Pt-470to600_MuEnrichedPt5_2018", "/QCD_Pt-470to600_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM") ###
#dataset = Dataset("QCD_Pt-600to800_MuEnrichedPt5_2018", "/QCD_Pt-600to800_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM") ###
#dataset = Dataset("QCD_Pt-800to1000_MuEnrichedPt5_2018", "/QCD_Pt-800to1000_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM") ###
#dataset = Dataset("QCD_Pt-1000toInf_MuEnrichedPt5_2018", "/QCD_Pt-1000toInf_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM") ###

print dataset.process

time = datetime.now().strftime("%Y%m%d%H%M%S")

config = config()

config.General.requestName = '{}_{}'.format(dataset.process, time)
config.General.workArea = 'crab_projects'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'nTupliserMC_miniAOD_cfg.py'
config.JobType.allowUndistributedCMSSW = True

config.Data.inputDataset = dataset.dataset
config.Data.inputDBS = 'phys03' ## private production MC
#config.Data.inputDBS = 'global' ## normal centrally generated MC

config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1

config.Data.outLFNDirBase = '/store/user/almorton/MC/nTuples/'

config.Data.publication = False
config.Data.outputDatasetTag = "CRAB3_MC_nTupilisation_{}_{}".format(dataset.process, time)

config.Data.allowNonValidInputDataset = True

config.Site.storageSite = 'T2_BE_IIHE' #T2_UK_London_IC, T2_UK_London_Brunel, T2_BE_IIHE
#config.Site.blacklist = ['T2_UK_London_Brunel']
config.Site.ignoreGlobalBlacklist = True

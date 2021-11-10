# -*- coding: utf-8 -*-
from collections import namedtuple
from datetime import datetime

from CRABClient.UserUtilities import config

Dataset = namedtuple("Dataset", "process dataset")

## UL Datasets

## 2016 APV Datasets
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2016_APV",     "")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1_2016_APV",     "")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2016_APV",    "")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2016_APV",   "")

#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS0_2016_APV",     "")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2016_APV",     "")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2016_APV",    "")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2016_APV",   "")

## 2016 Datasets
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2016",         "")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1_2016",         "")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS10_2016",        "")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2016",       "")

#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS0_2016",         "")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2016",         "")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2016",        "")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2016"        "")

## 2017 Datasets

#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS0_2017",      "/HToSSTo2Mu2Hadrons_MH125_MS0p4_ctauS0_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")
##dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS1_2017",      "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS1_2017_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS1_2017_210620-b37fc5ba2cc952d2522846eae35aac1f/USER")
##dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS10_2017",     "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS10_2017_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS10_2017_210620-b37fc5ba2cc952d2522846eae35aac1f/USER")
##dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS100_2017",    "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS100_2017_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS100_2017_210620-b37fc5ba2cc952d2522846eae35aac1f/USER")
##dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS1000_2017",   "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS1000_2017_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS1000_2017_210620-b37fc5ba2cc952d2522846eae35aac1f/USER")

#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS0p6_ctauS0_2017",      "/HToSSTo2Mu2Hadrons_MH125_MS0p6_ctauS0_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS0p6_ctauS1_2017",      "/HToSSTo2Mu2Hadrons_MH125_MS0p6_ctauS1_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")

#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS0_2017",      "/HToSSTo2Mu2Hadrons_MH125_MS0p8_ctauS0_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS1_2017",      "/HToSSTo2Mu2Hadrons_MH125_MS0p8_ctauS1_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS10_2017",     "/HToSSTo2Mu2Hadrons_MH125_MS0p8_ctauS10_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")
##dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS100_2017",    "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS100_2017_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS100_2017_210620-b37fc5ba2cc952d2522846eae35aac1f/USER")
##dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS1000_2017",   "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS1000_2017_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS1000_2017_210620-b37fc5ba2cc952d2522846eae35aac1f/USER")

#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS0p9_ctauS0_2017",      "/HToSSTo2Mu2Hadrons_MH125_MS0p9_ctauS0_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS0p9_ctauS1_2017",      "/HToSSTo2Mu2Hadrons_MH125_MS0p9_ctauS1_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")

#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2017",        "/HToSSTo2Mu2Hadrons_MH125_MS1_ctauS0_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1_2017",        "/HToSSTo2Mu2Hadrons_MH125_MS1_ctauS1_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")
##dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS10_2017",       "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS10_2017_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS10_2017_210620-b37fc5ba2cc952d2522846eae35aac1f/USER")
##dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2017",      "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2017_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2017_210620-b37fc5ba2cc952d2522846eae35aac1f/USER")
##dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1000_2017",     "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1000_2017_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1000_2017_210620-b37fc5ba2cc952d2522846eae35aac1f/USER")

#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1p1_ctauS1_2017",      "/HToSSTo2Mu2Hadrons_MH125_MS1p1_ctauS1_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1p1_ctauS100_2017",    "/HToSSTo2Mu2Hadrons_MH125_MS1p1_ctauS100_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")

#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1p2_ctauS0_2017",      "/HToSSTo2Mu2Hadrons_MH125_MS1p2_ctauS0_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1p2_ctauS1_2017",      "/HToSSTo2Mu2Hadrons_MH125_MS1p2_ctauS1_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1p2_ctauS10_2017",     "/HToSSTo2Mu2Hadrons_MH125_MS1p2_ctauS10_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1p2_ctauS100_2017",    "/HToSSTo2Mu2Hadrons_MH125_MS1p2_ctauS100_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")

#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1p4_ctauS0_2017",      "/HToSSTo2Mu2Hadrons_MH125_MS1p4_ctauS0_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1p4_ctauS10_2017",     "/HToSSTo2Mu2Hadrons_MH125_MS1p4_ctauS10_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")

#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1p6_ctauS0_2017",      "/HToSSTo2Mu2Hadrons_MH125_MS1p6_ctauS0_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1p6_ctauS10_2017",     "/HToSSTo2Mu2Hadrons_MH125_MS1p6_ctauS10_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")

#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1p8_ctauS0_2017",      "/HToSSTo2Mu2Hadrons_MH125_MS1p8_ctauS0_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1p8_ctauS10_2017",     "/HToSSTo2Mu2Hadrons_MH125_MS1p8_ctauS10_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1p8_ctauS100_2017",    "/HToSSTo2Mu2Hadrons_MH125_MS1p8_ctauS100_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")

#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS0_2017",        "/HToSSTo2Mu2Hadrons_MH125_MS2_ctauS0_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")
##dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2017",        "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2017_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2017_210620-b37fc5ba2cc952d2522846eae35aac1f/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2017",       "/HToSSTo2Mu2Hadrons_MH125_MS2_ctauS10_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")
##dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2017",      "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2017_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2017_210620-b37fc5ba2cc952d2522846eae35aac1f/USER")
##dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1000_2017",     "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1000_2017_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1000_2017_210620-b37fc5ba2cc952d2522846eae35aac1f/USER")

## 2018 Datasets

#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS0_2018",      "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS0_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS0_2018_210620-b7b002d074f841ca987cd18235688279/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS1_2018",      "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS1_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS1_2018_210620-b7b002d074f841ca987cd18235688279/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS10_2018",     "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS10_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS10_2018_210620-b7b002d074f841ca987cd18235688279/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS100_2018",    "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS100_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS100_2018_210620-b7b002d074f841ca987cd18235688279/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS1000_2018",   "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS1000_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS1000_2018_210620-b7b002d074f841ca987cd18235688279/USER")

#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS0_2018",      "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS0_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS0_2018_210620-b7b002d074f841ca987cd18235688279/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS1_2018",      "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS1_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS1_2018_210620-b7b002d074f841ca987cd18235688279/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS10_2018",     "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS10_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS10_2018_210620-b7b002d074f841ca987cd18235688279/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS100_2018",    "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS100_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS100_2018_210620-b7b002d074f841ca987cd18235688279/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS1000_2018",   "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS1000_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS1000_2018_210620-b7b002d074f841ca987cd18235688279/USER")

#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2018",         "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2018_210620-b7b002d074f841ca987cd18235688279/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1_2018",         "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1_2018_210620-b7b002d074f841ca987cd18235688279/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS10_2018",        "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS10_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS10_2018_210620-b7b002d074f841ca987cd18235688279/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2018",       "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2018_210620-b7b002d074f841ca987cd18235688279/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1000_2018",      "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1000_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1000_2018_210620-b7b002d074f841ca987cd18235688279/USER")

#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS0_2018",         "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS0_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS0_2018_210620-b7b002d074f841ca987cd18235688279/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2018",         "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2018_210620-b7b002d074f841ca987cd18235688279/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2018",        "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2018_210620-b7b002d074f841ca987cd18235688279/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2018",       "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2018_210620-b7b002d074f841ca987cd18235688279/USER")
#dataset = Dataset("HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1000_2018",      "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1000_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1000_2018_210620-b7b002d074f841ca987cd18235688279/USER")

###############

## tZq
#dataset = Dataset("tZq_2016_APV", "/tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM")
#dataset = Dataset("tZq_2016",     "/tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("tZq_2017",     "/tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("tZq_2018",     "

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
#dataset = Dataset("ttZ_ll_2016_APV", "/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM")
#dataset = Dataset("ttZ_ll_2016", "/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("ttZ_ll_2017", "/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("ttZ_ll_2018", "/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM")

#dataset = Dataset("ttZ_qq_2016_APV", "/TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM")
#dataset = Dataset("ttZ_qq_2016", "/TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("ttZ_qq_2017", "/TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("ttZ_qq_2018", "/TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")

## ttW
#dataset = Dataset("ttW_lnu_2016_APV", "/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM")
#dataset = Dataset("ttW_lnu_2016", "/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("ttW_lnu_2017", "/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("ttW_lnu_2018", "/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")

#dataset = Dataset("ttW_qq_2016_APV", "
#dataset = Dataset("ttW_qq_2016", "/TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("ttW_qq_2017", "/TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("ttW_qq_2018", "/TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")

## ttH (bb)
#dataset = Dataset("ttH_bb_2016_APV", "/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODAPV-106X_mcRun2_asymptotic_preVFP_v8-v1/MINIAODSIM")
#dataset = Dataset("ttH_bb_2016", "/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAOD-106X_mcRun2_asymptotic_v13-v1/MINIAODSIM")
#dataset = Dataset("ttH_bb_2017", "/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM")
#dataset = Dataset("ttH_bb_2018", "/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM")

## ttH (non bb)
#dataset = Dataset("ttH_nonbb_2016_APV", "/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM")
#dataset = Dataset("ttH_nonbb_2016", "/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAOD-106X_mcRun2_asymptotic_v13-v1/MINIAODSIM")
#dataset = Dataset("ttH_nonbb_2017", "/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM")
#dataset = Dataset("ttH_nonbb_2018", "/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM")

# ttγ
#dataset = Dataset("ttgamma_2016_APV", "/TTGamma_Dilept_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM")
#dataset = Dataset("ttgamma_2016", "/TTGamma_Dilept_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("ttgamma_2017", "/TTGamma_Dilept_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("ttgamma_2018", "/TTGamma_Dilept_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")

# W+jets
#dataset = Dataset("Wjets_2016_APV", "/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM")
#dataset = Dataset("Wjets_2016", "/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("Wjets_2017", "/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("Wjets_2018", "/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")

## WW (2l2nu)
#dataset = Dataset("WW_2l2nu_2016_APV", "/WWTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM")
#dataset = Dataset("WW_2l2nu_2016", "/WWTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("WW_2l2nu_2017", "/WWTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM")
#dataset = Dataset("WW_2l2nu_2018", "/WWTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM")

## WW (lnu2q)
#dataset = Dataset("WW_lnu2q_2016_APV", "")
#dataset = Dataset("WW_lnu2q_2016", "")
#dataset = Dataset("WW_lnu2q_2017", "")
#dataset = Dataset("WW_lnu2q_2018", "/WWTo1L1Nu2Q_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")

## WZ (3lnu + up to 1 jet)
#dataset = Dataset("WZ_3lnu_2016_APV", "")
#dataset = Dataset("WZ_3lnu_2016", "/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("WZ_3lnu_2017", "/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM")
#dataset = Dataset("WZ_3lnu_2018", "/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM")

## WZ (2l2q)
#dataset = Dataset("WZ_2l2q_2016_APV", "")
#dataset = Dataset("WZ_2l2q_2016", "")
#dataset = Dataset("WZ_2l2q_2017", "")
#dataset = Dataset("WZ_2l2q_2018", "/WZTo2Q2Nu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM")

## WZ (lnu2q)
#dataset = Dataset("WZ_lnu2q_2016_APV", "")
#dataset = Dataset("WZ_lnu2q_2016", "")
#dataset = Dataset("WZ_lnu2q_2017", "")
#dataset = Dataset("WZ_lnu2q_2018", "/WZTo1L1Nu2Q_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM")
	
#dataset = Dataset("WZ_l3nu_2016_APV",  "")
#dataset = Dataset("WZ_l3nu_2016",  "")
#dataset = Dataset("WZ_l3nu_2017",  "")
#dataset = Dataset("WZ_l3nu_2018",  "")

## ZZ (4l)
#dataset = Dataset("ZZ_4l_2016_APV", "")
#dataset = Dataset("ZZ_4l_2016", "")
#dataset = Dataset("ZZ_4l_2017", "/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM")
#dataset = Dataset("ZZ_4l_2018", "/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM")

## ZZ (2l2nu)
#dataset = Dataset("ZZ_2l2nu_2016_APV", "/ZZTo2L2Nu_TuneCP5_13TeV_powheg_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM")
#dataset = Dataset("ZZ_2l2nu_2016", "/ZZTo2L2Nu_TuneCP5_13TeV_powheg_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("ZZ_2l2nu_2017", "/ZZTo2L2Nu_TuneCP5_13TeV_powheg_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("ZZ_2l2nu_2018", "/ZZTo2L2Nu_TuneCP5_13TeV_powheg_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")

## ZZ (2l2q)
#dataset = Dataset("ZZ_2l2q_2016_APV", "")
#dataset = Dataset("ZZ_2l2q_2016", "")
#dataset = Dataset("ZZ_2l2q_2017", "")
#dataset = Dataset("ZZ_2l2q_2018", "")

### WWW
#dataset = Dataset("WWW_2016_APV", "/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM")
#dataset = Dataset("WWW_2016_APV_ext", "/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11_ext1-v1/MINIAODSIM")
#dataset = Dataset("WWW_2016", "/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("WWW_2016_ext", "/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17_ext1-v1/MINIAODSIM")
#dataset = Dataset("WWW_2017", "/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("WWW_2018", "/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")

## WWZ
#dataset = Dataset("WWZ_2016_APV", "/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM")
#dataset = Dataset("WWZ_2016_APV_ext", "/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11_ext1-v1/MINIAODSIM")
#dataset = Dataset("WWZ_2016", "/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("WWZ_2016_ext", "/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17_ext1-v1/MINIAODSIM")
#dataset = Dataset("WWZ_2017", "/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("WWZ_2018", "/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")

## WZZ
#dataset = Dataset("WZZ_2016_APV", "/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM")
#dataset = Dataset("WZZ_2016_APV_ext", "/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11_ext1-v1/MINIAODSIM")
#dataset = Dataset("WZZ_2016", "/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("WZZ_2016_ext", "/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17_ext1-v1/MINIAODSIM")
#dataset = Dataset("WZZ_2017", "/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("WZZ_2017_ext", "/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9_ext1-v2/MINIAODSIM")
#dataset = Dataset("WZZ_2018", "/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v3/MINIAODSIM")
#dataset = Dataset("WZZ_2018_ext", "/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1_ext1-v2/MINIAODSIM")

## ZZZ
#dataset = Dataset("ZZZ_2016_APV", "/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM")
#dataset = Dataset("ZZZ_2016_APV_ext", "/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11_ext1-v1/MINIAODSIM")
#dataset = Dataset("ZZZ_2016", "/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("ZZZ_2016_ext", "/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17_ext1-v1/MINIAODSIM")
#dataset = Dataset("ZZZ_2017", "/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("ZZZ_2018", "/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")

## ttbar
#dataset = Dataset("ttbar_hadronic_2016_APV", "/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM")
#dataset = Dataset("ttbar_hadronic_2016", "/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("ttbar_hadronic_2017", "/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM") ###
#dataset = Dataset("ttbar_hadronic_2018", "/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")

#dataset = Dataset("ttbar_semileptonic_2016_APV", "/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM")
#dataset = Dataset("ttbar_semileptonic_2016", "/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("ttbar_semileptonic_2017", "/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("ttbar_semileptonic_2018", "/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")

#dataset = Dataset("ttbar_2l2v_2016_APV", "/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM")
#dataset = Dataset("ttbar_2l2v_2016", "/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("ttbar_2l2v_2017", "/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("ttbar_2l2v_2018", "/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")

## tW
#dataset = Dataset("tW_2016_APV", "/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM")
#dataset = Dataset("tW_2016", "/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM")
#dataset = Dataset("tW_2017", "/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM")
#dataset = Dataset("tW_2018", "/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM")

## tbarW
#dataset = Dataset("tbarW_2016_APV", "/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM")
#dataset = Dataset("tbarW_2016", "/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM")
#dataset = Dataset("tbarW_2017", "/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM")
#dataset = Dataset("tbarW_2018", "/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM")

## t s-channel
#dataset = Dataset("t_s_channel_2016_APV", "/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM")
#dataset = Dataset("t_s_channel_2016", "/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAOD-106X_mcRun2_asymptotic_v13-v2/MINIAODSIM")
#dataset = Dataset("t_s_channel_2017", "/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM") ###
#dataset = Dataset("t_s_channel_2018", "/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer19UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM") ###

# t t-channel
#dataset = Dataset("t_t_channel_2016_APV", "/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v3/MINIAODSIM")
#dataset = Dataset("t_t_channel_2016", "/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v3/MINIAODSIM")
#dataset = Dataset("t_t_channel_2017", "/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM") ###
#dataset = Dataset("t_t_channel_2018", "/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer19UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM") ###

## tbar t-channel
#dataset = Dataset("tbar_t_channel_2016_APV", "/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v3/MINIAODSIM")
#dataset = Dataset("tbar_t_channel_2016", "/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v3/MINIAODSIM")
#dataset = Dataset("tbar_t_channel_2017", "/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM") ###
#dataset = Dataset("tbar_t_channel_2018", "/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer19UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM") ###

# Zjets pt binned
#dataset = Dataset("DYJetsToLL_Pt-0To50_2016_APV",    "")
#dataset = Dataset("DYJetsToLL_Pt-50To100_2016_APV",  "/DYJetsToLL_Pt-50To100_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODAPV-106X_mcRun2_asymptotic_preVFP_v8-v1/MINIAODSIM")
#dataset = Dataset("DYJetsToLL_Pt-100To250_2016_APV", "/DYJetsToLL_Pt-100To250_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM")
#dataset = Dataset("DYJetsToLL_Pt-250To400_2016_APV", "/DYJetsToLL_Pt-250To400_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM")
#dataset = Dataset("DYJetsToLL_Pt-400To650_2016_APV", "/DYJetsToLL_Pt-400To650_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM")
#dataset = Dataset("DYJetsToLL_Pt-650ToInf_2016_APV", "/DYJetsToLL_Pt-650ToInf_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM")

#dataset = Dataset("DYJetsToLL_Pt-0To50_2016",    "")
#dataset = Dataset("DYJetsToLL_Pt-50To100_2016",  "/DYJetsToLL_Pt-50To100_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("DYJetsToLL_Pt-100To250_2016", "/DYJetsToLL_Pt-100To250_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("DYJetsToLL_Pt-250To400_2016", "/DYJetsToLL_Pt-250To400_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("DYJetsToLL_Pt-400To650_2016", "/DYJetsToLL_Pt-400To650_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("DYJetsToLL_Pt-650ToInf_2016", "/DYJetsToLL_Pt-650ToInf_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")

#dataset = Dataset("DYJetsToLL_Pt-0To50_2017",    "")
#dataset = Dataset("DYJetsToLL_Pt-50To100_2017",  "/DYJetsToLL_Pt-50To100_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("DYJetsToLL_Pt-100To250_2017", "/DYJetsToLL_Pt-100To250_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM")
#dataset = Dataset("DYJetsToLL_Pt-250To400_2017", "/DYJetsToLL_Pt-250To400_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("DYJetsToLL_Pt-400To650_2017", "/DYJetsToLL_Pt-400To650_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("DYJetsToLL_Pt-650ToInf_2017", "/DYJetsToLL_Pt-650ToInf_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")

#dataset = Dataset("DYJetsToLL_Pt-0To50_2018",    "")
#dataset = Dataset("DYJetsToLL_Pt-50To100_2018",  "/DYJetsToLL_Pt-50To100_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")
#dataset = Dataset("DYJetsToLL_Pt-100To250_2018", "/DYJetsToLL_Pt-100To250_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")
#dataset = Dataset("DYJetsToLL_Pt-250To400_2018", "/DYJetsToLL_Pt-250To400_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")
#dataset = Dataset("DYJetsToLL_Pt-400To650_2018", "DYJetsToLL_Pt-400To650_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")
#dataset = Dataset("DYJetsToLL_Pt-650ToInf_2018", "/DYJetsToLL_Pt-650ToInf_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAOD-106X_upgrade2018_realistic_v11_L1v1-v1/MINIAODSIM")

# WG?
#dataset = Dataset("WG_lnug_2016_APV", "/WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM")
#dataset = Dataset("WG_lnug_2016", "/WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL16MiniAOD-106X_mcRun2_asymptotic_v13-v2/MINIAODSIM")
#dataset = Dataset("WG_lnug_2017", "/WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM")
#dataset = Dataset("WG_lnug_2018", "/WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM")

# ZG?
#dataset = Dataset("ZG_llg_2016_APV", "/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODAPV-106X_mcRun2_asymptotic_preVFP_v8-v1/MINIAODSIM")
#dataset = Dataset("ZG_llg_2016", "/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("ZG_llg_2017", "/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM") #Skip ISR/FSR flag!
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

#dataset = Dataset("QCD_Pt-15to20_MuEnrichedPt5_2016", "/QCD_Pt-15To20_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM")
#dataset = Dataset("QCD_Pt-20to30_MuEnrichedPt5_2016", "/QCD_Pt-20To30_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("QCD_Pt-30to50_MuEnrichedPt5_2016", "/QCD_Pt-30To50_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("QCD_Pt-50to80_MuEnrichedPt5_2016", "/QCD_Pt-50To80_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("QCD_Pt-80to120_MuEnrichedPt5_2016", "/QCD_Pt-80To120_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("QCD_Pt-120to170_MuEnrichedPt5_2016", "/QCD_Pt-120To170_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("QCD_Pt-170to300_MuEnrichedPt5_2016", "/QCD_Pt-170To300_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("QCD_Pt-300to470_MuEnrichedPt5_2016", "/QCD_Pt-300To470_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("QCD_Pt-470to600_MuEnrichedPt5_2016", "/QCD_Pt-470To600_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("QCD_Pt-600to800_MuEnrichedPt5_2016", "/QCD_Pt-600To800_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("QCD_Pt-800to1000_MuEnrichedPt5_2016", "/QCD_Pt-800To1000_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")
#dataset = Dataset("QCD_Pt-1000toInf_MuEnrichedPt5_2016", "/QCD_Pt-1000_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM")

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
#dataset = Dataset("QCD_Pt-800to1000_MuEnrichedPt5_2017", "/QCD_Pt-800to1000_MuEnrichedPt5_TuneCP5_13TeV_pythia8/RunIISummer19UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM") ### Skip ISR/FSR flag!
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
#config.Data.inputDBS = 'phys03' ## private production MC
config.Data.inputDBS = 'global' ## normal centrally generated MC

config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1

config.Data.outLFNDirBase = '/store/user/almorton/MC/nTuples/'

config.Data.publication = False
#config.Data.outputDatasetTag = "CRAB3_MC_nTupilisation_{}_{}".format(dataset.process, time)
config.Data.outputDatasetTag = "CRAB3_MC_miniNtupilisation_{}_{}".format(dataset.process, time)

config.Data.allowNonValidInputDataset = True

config.Site.storageSite = 'T2_BE_IIHE' #T2_UK_London_IC, T2_UK_London_Brunel, T2_BE_IIHE
#config.Site.blacklist = ['T2_UK_London_Brunel']
config.Site.ignoreGlobalBlacklist = True

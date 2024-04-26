# -*- coding: utf-8 -*-
from collections import namedtuple
from datetime import datetime
import yaml

from CRABClient.UserUtilities import config

## UL Datasets
# sample_dict = {
#   'HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS0_2017': {'location': "/HToSSTo2Mu2Hadrons_MH125_MS0p4_ctauS0_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},

# ## 2016 APV Datasets
#   "HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2016_APV": {"location":     ""},
#   "HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1_2016_APV": {"location":     ""},
#   "HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2016_APV": {"location":    ""},
#   "HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2016_APV": {"location":   ""},

#   "HToSS_SmuonHadronFiltered_MH125_MS2_ctauS0_2016_APV": {"location":     ""},
#   "HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2016_APV": {"location":     ""},
#   "HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2016_APV": {"location":    ""},
#   "HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2016_APV": {"location":   ""},

# ## 2016 Datasets
#   "HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2016": {"location":         ""},
#   "HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1_2016": {"location":         ""},
#   "HToSS_SmuonHadronFiltered_MH125_MS1_ctauS10_2016": {"location":        ""},
#   "HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2016": {"location":       ""},

#   "HToSS_SmuonHadronFiltered_MH125_MS2_ctauS0_2016": {"location":         ""},
#   "HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2016": {"location":         ""},
#   "HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2016": {"location":        ""},
#   "HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2016": {"location":        ""},

# ## 2017 Datasets

#   "HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS0_2017": {"location":      "/HToSSTo2Mu2Hadrons_MH125_MS0p4_ctauS0_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS1_2017": {"location":      "/HToSSTo2Mu2Hadrons_MH125_MS0p4_ctauS1_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS10_2017": {"location":     "/HToSSTo2Mu2Hadrons_MH125_MS0p4_ctauS10_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS0p4_ctauS100_2017": {"location":    "/HToSSTo2Mu2Hadrons_MH125_MS0p4_ctauS100_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},

#   "HToSS_SmuonHadronFiltered_MH125_MS0p6_ctauS0_2017": {"location":      "/HToSSTo2Mu2Hadrons_MH125_MS0p6_ctauS0_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS0p6_ctauS1_2017": {"location":      "/HToSSTo2Mu2Hadrons_MH125_MS0p6_ctauS1_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS0p6_ctauS10_2017": {"location":     "/HToSSTo2Mu2Hadrons_MH125_MS0p6_ctauS10_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS0p6_ctauS100_2017": {"location":    "/HToSSTo2Mu2Hadrons_MH125_MS0p6_ctauS100_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},

#   "HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS0_2017": {"location":      "/HToSSTo2Mu2Hadrons_MH125_MS0p8_ctauS0_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS1_2017": {"location":      "/HToSSTo2Mu2Hadrons_MH125_MS0p8_ctauS1_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS10_2017": {"location":     "/HToSSTo2Mu2Hadrons_MH125_MS0p8_ctauS10_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS100_2017": {"location":    "/HToSSTo2Mu2Hadrons_MH125_MS0p8_ctauS100_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},

#   "HToSS_SmuonHadronFiltered_MH125_MS0p9_ctauS0_2017": {"location":      "/HToSSTo2Mu2Hadrons_MH125_MS0p9_ctauS0_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS0p9_ctauS1_2017": {"location":      "/HToSSTo2Mu2Hadrons_MH125_MS0p9_ctauS1_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS0p9_ctauS10_2017": {"location":     "/HToSSTo2Mu2Hadrons_MH125_MS0p9_ctauS10_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS0p9_ctauS100_2017": {"location":    "/HToSSTo2Mu2Hadrons_MH125_MS0p9_ctauS100_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},

#   "HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2017": {"location":        "/HToSSTo2Mu2Hadrons_MH125_MS1_ctauS0_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1_2017": {"location":        "/HToSSTo2Mu2Hadrons_MH125_MS1_ctauS1_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS1_ctauS10_2017": {"location":       "/HToSSTo2Mu2Hadrons_MH125_MS1_ctauS10_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2017": {"location":      "/HToSSTo2Mu2Hadrons_MH125_MS1_ctauS100_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},

#   "HToSS_SmuonHadronFiltered_MH125_MS1p1_ctauS0_2017": {"location":      "/HToSSTo2Mu2Hadrons_MH125_MS1p1_ctauS0_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS1p1_ctauS1_2017": {"location":      "/HToSSTo2Mu2Hadrons_MH125_MS1p1_ctauS1_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS1p1_ctauS10_2017": {"location":     "/HToSSTo2Mu2Hadrons_MH125_MS1p1_ctauS10_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS1p1_ctauS100_2017": {"location":    "/HToSSTo2Mu2Hadrons_MH125_MS1p1_ctauS100_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},

#   "HToSS_SmuonHadronFiltered_MH125_MS1p2_ctauS0_2017": {"location":      "/HToSSTo2Mu2Hadrons_MH125_MS1p2_ctauS0_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS1p2_ctauS1_2017": {"location":      "/HToSSTo2Mu2Hadrons_MH125_MS1p2_ctauS1_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS1p2_ctauS10_2017": {"location":     "/HToSSTo2Mu2Hadrons_MH125_MS1p2_ctauS10_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS1p2_ctauS100_2017": {"location":    "/HToSSTo2Mu2Hadrons_MH125_MS1p2_ctauS100_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},

#   "HToSS_SmuonHadronFiltered_MH125_MS1p4_ctauS0_2017": {"location":      "/HToSSTo2Mu2Hadrons_MH125_MS1p4_ctauS0_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS1p4_ctauS1_2017": {"location":      "/HToSSTo2Mu2Hadrons_MH125_MS1p4_ctauS1_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS1p4_ctauS10_2017": {"location":     "/HToSSTo2Mu2Hadrons_MH125_MS1p4_ctauS10_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS1p4_ctauS100_2017": {"location":    "/HToSSTo2Mu2Hadrons_MH125_MS1p4_ctauS100_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},

#   "HToSS_SmuonHadronFiltered_MH125_MS1p6_ctauS0_2017": {"location":      "/HToSSTo2Mu2Hadrons_MH125_MS1p6_ctauS0_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS1p6_ctauS1_2017": {"location":      "/HToSSTo2Mu2Hadrons_MH125_MS1p6_ctauS1_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS1p6_ctauS10_2017": {"location":     "/HToSSTo2Mu2Hadrons_MH125_MS1p6_ctauS10_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS1p6_ctauS100_2017": {"location":    "/HToSSTo2Mu2Hadrons_MH125_MS1p6_ctauS100_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},

#   "HToSS_SmuonHadronFiltered_MH125_MS1p8_ctauS0_2017": {"location":      "/HToSSTo2Mu2Hadrons_MH125_MS1p8_ctauS0_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS1p8_ctauS1_2017": {"location":      "/HToSSTo2Mu2Hadrons_MH125_MS1p8_ctauS1_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS1p8_ctauS10_2017": {"location":     "/HToSSTo2Mu2Hadrons_MH125_MS1p8_ctauS10_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS1p8_ctauS100_2017": {"location":    "/HToSSTo2Mu2Hadrons_MH125_MS1p8_ctauS100_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},

#   "HToSS_SmuonHadronFiltered_MH125_MS2_ctauS0_2017": {"location":        "/HToSSTo2Mu2Hadrons_MH125_MS2_ctauS0_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2017": {"location":        "/HToSSTo2Mu2Hadrons_MH125_MS2_ctauS1_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2017": {"location":       "/HToSSTo2Mu2Hadrons_MH125_MS2_ctauS10_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2017": {"location":      "/HToSSTo2Mu2Hadrons_MH125_MS2_ctauS100_TuneCP2_13TeV-powheg-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},

# ## 2018 Datasets

#   "HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS0_2018": {"location":      "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS0_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS0_2018_210620-b7b002d074f841ca987cd18235688279/USER"},
#   "HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS1_2018": {"location":      "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS1_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS1_2018_210620-b7b002d074f841ca987cd18235688279/USER"},
#   "HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS10_2018": {"location":     "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS10_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS10_2018_210620-b7b002d074f841ca987cd18235688279/USER"},
#   "HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS100_2018": {"location":    "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS100_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS0p8_ctauS100_2018_210620-b7b002d074f841ca987cd18235688279/USER"},

#   "HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2018": {"location":         "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2018_210620-b7b002d074f841ca987cd18235688279/USER"},
#   "HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1_2018": {"location":         "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS1_2018_210620-b7b002d074f841ca987cd18235688279/USER"},
#   "HToSS_SmuonHadronFiltered_MH125_MS1_ctauS10_2018": {"location":        "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS10_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS10_2018_210620-b7b002d074f841ca987cd18235688279/USER"},
#   "HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2018": {"location":       "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS100_2018_210620-b7b002d074f841ca987cd18235688279/USER"},

#   "HToSS_SmuonHadronFiltered_MH125_MS2_ctauS0_2018": {"location":         "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS0_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS0_2018_210620-b7b002d074f841ca987cd18235688279/USER"},
#   "HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2018": {"location":         "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1_2018_210620-b7b002d074f841ca987cd18235688279/USER"},
#   "HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2018": {"location":        "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS10_2018_210620-b7b002d074f841ca987cd18235688279/USER"},
#   "HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2018": {"location":       "/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2018_210620/almorton-CRAB3_PAT_miniAOD_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2018_210620-b7b002d074f841ca987cd18235688279/USER"},

# ###############

# ## tZq
#   "tZq_2016_APV": {"location": "/tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM"},
#   "tZq_2016": {"location":     "/tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "tZq_2017": {"location":     "/tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM"},
#   "tZq_2018": {"location":     "/tZq_ll_4f_ckm_NLO_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},

# ## tHq
#   "tHq_2016_APV": {"location": "/THQ_ctcvcp_4f_Hincl_TuneCP5_13TeV_madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM"},
#   "tHq_2016": {"location": "/THQ_ctcvcp_4f_Hincl_TuneCP5_13TeV_madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM"},
#   "tHq_2017": {"location": "/THQ_ctcvcp_4f_Hincl_TuneCP5_13TeV_madgraph_pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v3/MINIAODSIM"},
#   "tHq_2018": {"location": "/THQ_ctcvcp_4f_Hincl_TuneCP5_13TeV_madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},

# ## tWZ/tWll
#   "tWz_tWll_2016_APV": {"location": ""},
#   "tWz_tWll_2016": {"location": ""},
#   "tWz_tWll_2017": {"location": ""},
#   "tWz_tWll_2018": {"location": ""},

# ## ttZ
#   "ttZ_ll_2016_APV": {"location": "/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM"},
#   "ttZ_ll_2016": {"location": "/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "ttZ_ll_2017": {"location": "/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM"},
#   "ttZ_ll_2018": {"location": "/TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},

#   "ttZ_qq_2016_APV": {"location": "/TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM"},
#   "ttZ_qq_2016": {"location": "/TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "ttZ_qq_2017": {"location": "/TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM"},
#   "ttZ_qq_2018": {"location": "/TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM"},

# ## ttW
#   "ttW_lnu_2016_APV": {"location": "/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM"},
#   "ttW_lnu_2016": {"location": "/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "ttW_lnu_2017": {"location": "/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM"},
#   "ttW_lnu_2018": {"location": "/TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM"},

#   "ttW_qq_2016_APV": {"location": "/TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM"},
#   "ttW_qq_2016": {"location": "/TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "ttW_qq_2017": {"location": "/TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM"},
#   "ttW_qq_2018": {"location": "/TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM"},

# ## ttH (bb},
#   "ttH_bb_2016_APV": {"location": "/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM"},
#   "ttH_bb_2016": {"location": "/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM"},
#   "ttH_bb_2017": {"location": "/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM"},
#   "ttH_bb_2018": {"location": "/ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},

# ## ttH (non bb},
#   "ttH_nonbb_2016_APV": {"location": "/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM"},
#   "ttH_nonbb_2016": {"location": "/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM"},
#   "ttH_nonbb_2017": {"location": "/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM"},
#   "ttH_nonbb_2018": {"location": "/ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},

# # ttγ
#   "ttgamma_2016_APV": {"location": "/TTGamma_Dilept_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM"},
#   "ttgamma_2016": {"location": "/TTGamma_Dilept_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "ttgamma_2017": {"location": "/TTGamma_Dilept_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM"},
#   "ttgamma_2018": {"location": "/TTGamma_Dilept_TuneCP5_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM"},

# # W+jets
#   "Wjets_2016_APV": {"location": "/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM"},
#   "Wjets_2016": {"location": "/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "Wjets_2017": {"location": "/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM"},
#   "Wjets_2018": {"location": "/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM"},

# ## WW (2l2nu},
#   "WW_2l2nu_2016_APV": {"location": "/WWTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM"},
#   "WW_2l2nu_2016": {"location": "/WWTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "WW_2l2nu_2017": {"location": "/WWTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM"},
#   "WW_2l2nu_2018": {"location": "/WWTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},

# ## WW (lnu2q},
#   "WW_lnu2q_2016_APV": {"location": "/WWTo1L1Nu2Q_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODAPV-106X_mcRun2_asymptotic_preVFP_v8-v2/MINIAODSIM"},
#   "WW_lnu2q_2016": {"location": "/WWTo1L1Nu2Q_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAOD-106X_mcRun2_asymptotic_v13-v2/MINIAODSIM"},
#   "WW_lnu2q_2017": {"location": ""},
#   "WW_lnu2q_2018": {"location": "/WWTo1L1Nu2Q_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM"},

# ## WZ (3lnu + up to 1 jet},
#   "WZ_3lnu_2016_APV": {"location": "/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODAPV-106X_mcRun2_asymptotic_preVFP_v8-v3/MINIAODSIM"},
#   "WZ_3lnu_2016": {"location": "/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "WZ_3lnu_2017": {"location": "/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM"},
#   "WZ_3lnu_2018": {"location": "/WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},

# ## WZ (2l2q},
#   "WZ_2l2q_2016_APV": {"location": "/WZTo2Q2Nu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODAPV-106X_mcRun2_asymptotic_preVFP_v8-v2/MINIAODSIM"},
#   "WZ_2l2q_2016": {"location": "/WZTo2Q2Nu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAOD-106X_mcRun2_asymptotic_v13-v2/MINIAODSIM"},
#   "WZ_2l2q_2017": {"location": "/WZTo2Q2Nu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v2/MINIAODSIM"},
#   "WZ_2l2q_2018": {"location": "/WZTo2Q2Nu_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},

# ## WZ (lnu2q},
#   "WZ_lnu2q_2016_APV": {"location": "/WZTo1L1Nu2Q_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODAPV-106X_mcRun2_asymptotic_preVFP_v8-v2/MINIAODSIM"},
#   "WZ_lnu2q_2016": {"location": "/WZTo1L1Nu2Q_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAOD-106X_mcRun2_asymptotic_v13-v2/MINIAODSIM"},
#   "WZ_lnu2q_2017": {"location": "/WZTo1L1Nu2Q_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v2/MINIAODSIM"},
#   "WZ_lnu2q_2018": {"location": "/WZTo1L1Nu2Q_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},
	
#   "WZ_l3nu_2016_APV": {"location":  ""},
#   "WZ_l3nu_2016": {"location":  ""},
#   "WZ_l3nu_2017": {"location":  ""},
#   "WZ_l3nu_2018": {"location":  ""},

# ## ZZ (4l},
#   "ZZ_4l_2016_APV": {"location": ""},
#   "ZZ_4l_2016": {"location": ""},
#   "ZZ_4l_2017": {"location": "/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM"},
#   "ZZ_4l_2018": {"location": "/ZZTo4L_TuneCP5_13TeV_powheg_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},

# ## ZZ (2l2nu},
#   "ZZ_2l2nu_2016_APV": {"location": "/ZZTo2L2Nu_TuneCP5_13TeV_powheg_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM"},
#   "ZZ_2l2nu_2016": {"location": "/ZZTo2L2Nu_TuneCP5_13TeV_powheg_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "ZZ_2l2nu_2017": {"location": "/ZZTo2L2Nu_TuneCP5_13TeV_powheg_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM"},
#   "ZZ_2l2nu_2018": {"location": "/ZZTo2L2Nu_TuneCP5_13TeV_powheg_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM"},

# ## ZZ (2l2q},
#   "ZZ_2l2q_2016_APV": {"location": ""},
#   "ZZ_2l2q_2016": {"location": ""},
#   "ZZ_2l2q_2017": {"location": ""},
#   "ZZ_2l2q_2018": {"location": ""},

# ### WWW
#   "WWW_2016_APV": {"location": "/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM"},
#   "WWW_2016_APV_ext": {"location": "/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11_ext1-v1/MINIAODSIM"},
#   "WWW_2016": {"location": "/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "WWW_2016_ext": {"location": "/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17_ext1-v1/MINIAODSIM"},
#   "WWW_2017": {"location": "/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM"},
#   "WWW_2018": {"location": "/WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM"},

# ## WWZ
#   "WWZ_2016_APV": {"location": "/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM"},
#   "WWZ_2016_APV_ext": {"location": "/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11_ext1-v1/MINIAODSIM"},
#   "WWZ_2016": {"location": "/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "WWZ_2016_ext": {"location": "/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17_ext1-v1/MINIAODSIM"},
#   "WWZ_2017": {"location": "/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM"},
#   "WWZ_2018": {"location": "/WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM"},

# ## WZZ
#   "WZZ_2016_APV": {"location": "/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM"},
#   "WZZ_2016_APV_ext": {"location": "/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11_ext1-v1/MINIAODSIM"},
#   "WZZ_2016": {"location": "/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "WZZ_2016_ext": {"location": "/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17_ext1-v1/MINIAODSIM"},
#   "WZZ_2017": {"location": "/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM"},
#   "WZZ_2017_ext": {"location": "/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9_ext1-v2/MINIAODSIM"},
#   "WZZ_2018": {"location": "/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v3/MINIAODSIM"},
#   "WZZ_2018_ext": {"location": "/WZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1_ext1-v2/MINIAODSIM"},

# ## ZZZ
#   "ZZZ_2016_APV": {"location": "/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM"},
#   "ZZZ_2016_APV_ext": {"location": "/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11_ext1-v1/MINIAODSIM"},
#   "ZZZ_2016": {"location": "/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "ZZZ_2016_ext": {"location": "/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17_ext1-v1/MINIAODSIM"},
#   "ZZZ_2017": {"location": "/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM"},
#   "ZZZ_2018": {"location": "/ZZZ_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM"},

# ## ttbar
#   "ttbar_hadronic_2016_APV": {"location": "/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM"},
#   "ttbar_hadronic_2016": {"location": "/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "ttbar_hadronic_2017": {"location": "/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM"},
#   "ttbar_hadronic_2018": {"location": "/TTToHadronic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM"},

#   "ttbar_semileptonic_2016_APV": {"location": "/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM"},
#   "ttbar_semileptonic_2016": {"location": "/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "ttbar_semileptonic_2017": {"location": "/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM"},
#   "ttbar_semileptonic_2018": {"location": "/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM"},

#   "ttbar_2l2nu_2016_APV": {"location": "/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM"},
#   "ttbar_2l2nu_2016": {"location": "/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "ttbar_2l2nu_2017": {"location": "/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM"},
#   "ttbar_2l2nu_2018": {"location": "/TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM"},

# ## tW
#   "tW_2016_APV": {"location": "/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM"},
#   "tW_2016": {"location": "/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM"},
#   "tW_2017": {"location": "/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM"},
#   "tW_2018": {"location": "/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},

# ## tbarW
#   "tbarW_2016_APV": {"location": "/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM"},
#   "tbarW_2016": {"location": "/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM"},
#   "tbarW_2017": {"location": "/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM"},
#   "tbarW_2018": {"location": "/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},

# ## t s-channel
#   "t_s_channel_2016_APV": {"location": "/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM"},
#   "t_s_channel_2016": {"location": "/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL16MiniAOD-106X_mcRun2_asymptotic_v13-v2/MINIAODSIM"},
#   "t_s_channel_2017": {"location": "/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM"},
#   "t_s_channel_2018": {"location": "/ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM"},

# # t t-channel
#   "t_t_channel_2016_APV": {"location": "/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v3/MINIAODSIM"},
#   "t_t_channel_2016": {"location": "/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v3/MINIAODSIM"},
#   "t_t_channel_2017": {"location": "/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM"},
#   "t_t_channel_2018": {"location": "/ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM"},

# ## tbar t-channel
#   "tbar_t_channel_2016_APV": {"location": "/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v3/MINIAODSIM"},
#   "tbar_t_channel_2016": {"location": "/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v3/MINIAODSIM"},
#   "tbar_t_channel_2017": {"location": "/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM"},
#   "tbar_t_channel_2018": {"location": "/ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM"},

# # Zjets pt binned
#   "DYJetsToLL_Pt-0To50_2016_APV": {"location":    ""},
#   "DYJetsToLL_Pt-50To100_2016_APV": {"location":  "/DYJetsToLL_Pt-50To100_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODAPV-106X_mcRun2_asymptotic_preVFP_v8-v1/MINIAODSIM"},
#   "DYJetsToLL_Pt-100To250_2016_APV": {"location": "/DYJetsToLL_Pt-100To250_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM"},
#   "DYJetsToLL_Pt-250To400_2016_APV": {"location": "/DYJetsToLL_Pt-250To400_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM"},
#   "DYJetsToLL_Pt-400To650_2016_APV": {"location": "/DYJetsToLL_Pt-400To650_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM"},
#   "DYJetsToLL_Pt-650ToInf_2016_APV": {"location": "/DYJetsToLL_Pt-650ToInf_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM"},

#   "DYJetsToLL_Pt-0To50_2016": {"location":    ""},
#   "DYJetsToLL_Pt-50To100_2016": {"location":  "/DYJetsToLL_Pt-50To100_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "DYJetsToLL_Pt-100To250_2016": {"location": "/DYJetsToLL_Pt-100To250_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "DYJetsToLL_Pt-250To400_2016": {"location": "/DYJetsToLL_Pt-250To400_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "DYJetsToLL_Pt-400To650_2016": {"location": "/DYJetsToLL_Pt-400To650_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "DYJetsToLL_Pt-650ToInf_2016": {"location": "/DYJetsToLL_Pt-650ToInf_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},

#   "DYJetsToLL_Pt-0To50_2017": {"location":    ""},
#   "DYJetsToLL_Pt-50To100_2017": {"location":  "/DYJetsToLL_Pt-50To100_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM"},
#   "DYJetsToLL_Pt-100To250_2017": {"location": "/DYJetsToLL_Pt-100To250_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM"},
#   "DYJetsToLL_Pt-250To400_2017": {"location": "/DYJetsToLL_Pt-250To400_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM"},
#   "DYJetsToLL_Pt-400To650_2017": {"location": "/DYJetsToLL_Pt-400To650_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM"},
#   "DYJetsToLL_Pt-650ToInf_2017": {"location": "/DYJetsToLL_Pt-650ToInf_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM"},

#   "DYJetsToLL_Pt-0To50_2018": {"location":    ""},
#   "DYJetsToLL_Pt-50To100_2018": {"location":  "/DYJetsToLL_Pt-50To100_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM"},
#   "DYJetsToLL_Pt-100To250_2018": {"location": "/DYJetsToLL_Pt-100To250_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM"},
#   "DYJetsToLL_Pt-250To400_2018": {"location": "/DYJetsToLL_Pt-250To400_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM"},
#   "DYJetsToLL_Pt-400To650_2018": {"location": "/DYJetsToLL_Pt-400To650_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM"},
#   "DYJetsToLL_Pt-650ToInf_2018": {"location": "/DYJetsToLL_Pt-650ToInf_MatchEWPDG20_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},

# # Zjets M binned -> Taken from JERC work: {"location": just LO samples for now 

#   "DYJetsToLL_M-50_2016_APV": {"location":    ""},
#   "DYJetsToLL_M-50_2016_APV": {"location":  "/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM"},

#   "DYJetsToLL_M-50_2016": {"location":    ""},
#   "DYJetsToLL_M-50_2016": {"location":  "/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},


#   "DYJetsToLL_M-50_2017": {"location":    ""},
#   "DYJetsToLL_M-50_2017": {"location":  "/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM"},
#   "DYJetsToLL_M-50_ext_2017": {"location":  "/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9_ext1-v1/MINIAODSIM"},

#   "DYJetsToLL_M-50_2018": {"location":    ""},
#   "DYJetsToLL_M-50_2018": {"location":  "/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},
#   "DYJetsToLL_M-50_ext_2018": {"location":  "/DYJetsToLL_M-50_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1_ext1-v1/MINIAODSIM"},


# # WG?
#   "WG_lnug_2016_APV": {"location": "/WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM"},
#   "WG_lnug_2016": {"location": "/WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL16MiniAOD-106X_mcRun2_asymptotic_v13-v2/MINIAODSIM"},
#   "WG_lnug_2017": {"location": "/WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM"},
#   "WG_lnug_2018": {"location": "/WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM"},

# # ZG?
#   "ZG_llg_2016_APV": {"location": "/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "ZG_llg_2016": {"location": "/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "ZG_llg_2017": {"location": "/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM"}, #Skip ISR/FSR flag!
#   "ZG_llg_2018": {"location": "/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM"},

# # QCD MuEnrichedPt15
#   "QCD_Pt-20toInf_MuEnrichedPt15_2016_APV": {"location": "/QCD_Pt-20_MuEnrichedPt15_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODAPV-106X_mcRun2_asymptotic_preVFP_v8-v1/MINIAODSIM"},
#   "QCD_Pt-20toInf_MuEnrichedPt15_2016": {"location": "/QCD_Pt-20_MuEnrichedPt15_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM"},
#   "QCD_Pt-20toInf_MuEnrichedPt15_2017": {"location": "/QCD_Pt-20_MuEnrichedPt15_TuneCP5_13TeV-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM"},
#   "QCD_Pt-20toInf_MuEnrichedPt15_2018": {"location": "/QCD_Pt-20_MuEnrichedPt15_TuneCP5_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},

# # QCD MuEnrichedPt5
#   "QCD_Pt-15to20_MuEnrichedPt5_2016_APV": {"location": ""},
#   "QCD_Pt-20to30_MuEnrichedPt5_2016_APV": {"location": "/QCD_Pt-20To30_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODAPV-106X_mcRun2_asymptotic_preVFP_v8-v1/MINIAODSIM"},
#   "QCD_Pt-30to50_MuEnrichedPt5_2016_APV": {"location": "/QCD_Pt-30To50_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODAPV-106X_mcRun2_asymptotic_preVFP_v8-v1/MINIAODSIM"},
#   "QCD_Pt-50to80_MuEnrichedPt5_2016_APV": {"location": "/QCD_Pt-50To80_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM"},
#   "QCD_Pt-80to120_MuEnrichedPt5_2016_APV": {"location": "/QCD_Pt-80To120_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODAPV-106X_mcRun2_asymptotic_preVFP_v8-v1/MINIAODSIM"},
#   "QCD_Pt-120to170_MuEnrichedPt5_2016_APV": {"location": "/QCD_Pt-120To170_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODAPV-106X_mcRun2_asymptotic_preVFP_v8-v2/MINIAODSIM"},
#   "QCD_Pt-170to300_MuEnrichedPt5_2016_APV": {"location": "/QCD_Pt-170To300_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM"},
#   "QCD_Pt-300to470_MuEnrichedPt5_2016_APV": {"location": "/QCD_Pt-300To470_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM"},
#   "QCD_Pt-470to600_MuEnrichedPt5_2016_APV": {"location": "/QCD_Pt-470To600_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM"},
#   "QCD_Pt-600to800_MuEnrichedPt5_2016_APV": {"location": "/QCD_Pt-600To800_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODAPV-106X_mcRun2_asymptotic_preVFP_v8-v2/MINIAODSIM"},
#   "QCD_Pt-800to1000_MuEnrichedPt5_2016_APV": {"location": "/QCD_Pt-800To1000_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODAPV-106X_mcRun2_asymptotic_preVFP_v8-v2/MINIAODSIM"},
#   "QCD_Pt-1000toInf_MuEnrichedPt5_2016_APV": {"location": "/QCD_Pt-1000_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODAPV-106X_mcRun2_asymptotic_preVFP_v8-v2/MINIAODSIM"},

#   "QCD_Pt-15to20_MuEnrichedPt5_2016": {"location": "/QCD_Pt-15To20_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM"},
#   "QCD_Pt-20to30_MuEnrichedPt5_2016": {"location": "/QCD_Pt-20To30_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "QCD_Pt-30to50_MuEnrichedPt5_2016": {"location": "/QCD_Pt-30To50_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "QCD_Pt-50to80_MuEnrichedPt5_2016": {"location": "/QCD_Pt-50To80_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "QCD_Pt-80to120_MuEnrichedPt5_2016": {"location": "/QCD_Pt-80To120_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "QCD_Pt-120to170_MuEnrichedPt5_2016": {"location": "/QCD_Pt-120To170_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "QCD_Pt-170to300_MuEnrichedPt5_2016": {"location": "/QCD_Pt-170To300_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "QCD_Pt-300to470_MuEnrichedPt5_2016": {"location": "/QCD_Pt-300To470_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "QCD_Pt-470to600_MuEnrichedPt5_2016": {"location": "/QCD_Pt-470To600_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "QCD_Pt-600to800_MuEnrichedPt5_2016": {"location": "/QCD_Pt-600To800_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "QCD_Pt-800to1000_MuEnrichedPt5_2016": {"location": "/QCD_Pt-800To1000_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},
#   "QCD_Pt-1000toInf_MuEnrichedPt5_2016": {"location": "/QCD_Pt-1000_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM"},

#   "QCD_Pt-15to20_MuEnrichedPt5_2017": {"location": "/QCD_Pt-15To20_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM"},
#   "QCD_Pt-20to30_MuEnrichedPt5_2017": {"location": "/QCD_Pt-20To30_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "QCD_Pt-30to50_MuEnrichedPt5_2017": {"location": "/QCD_Pt-30To50_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v1/MINIAODSIM"},
#   "QCD_Pt-50to80_MuEnrichedPt5_2017": {"location": "/QCD_Pt-50To80_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM"},
#   "QCD_Pt-80to120_MuEnrichedPt5_2017": {"location": "/QCD_Pt-80To120_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM"},
#   "QCD_Pt-120to170_MuEnrichedPt5_2017": {"location": "/QCD_Pt-120To170_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM"},
#   "QCD_Pt-170to300_MuEnrichedPt5_2017": {"location": "/QCD_Pt-170To300_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM"},
#   "QCD_Pt-300to470_MuEnrichedPt5_2017": {"location": "/QCD_Pt-300To470_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM"},
#   "QCD_Pt-470to600_MuEnrichedPt5_2017": {"location": "/QCD_Pt-470To600_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM"},
#   "QCD_Pt-600to800_MuEnrichedPt5_2017": {"location": "/QCD_Pt-600To800_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM"},
#   "QCD_Pt-800to1000_MuEnrichedPt5_2017": {"location": "/QCD_Pt-800To1000_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL17MiniAOD-106X_mc2017_realistic_v6-v2/MINIAODSIM"}, ### Skip ISR/FSR flag!
#   "QCD_Pt-1000toInf_MuEnrichedPt5_2017": {"location": "/QCD_Pt-1000_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM"},

#   "QCD_Pt-15to20_MuEnrichedPt5_2018": {"location": "/QCD_Pt-15To20_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},
#   "QCD_Pt-20to30_MuEnrichedPt5_2018": {"location": "/QCD_Pt-20To30_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},
#   "QCD_Pt-30to50_MuEnrichedPt5_2018": {"location": "/QCD_Pt-30To50_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},
#   "QCD_Pt-50to80_MuEnrichedPt5_2018": {"location": "/QCD_Pt-50To80_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},
#   "QCD_Pt-80to120_MuEnrichedPt5_2018": {"location": "/QCD_Pt-80To120_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},
#   "QCD_Pt-120to170_MuEnrichedPt5_2018": {"location": "/QCD_Pt-120To170_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},
#   "QCD_Pt-170to300_MuEnrichedPt5_2018": {"location": "/QCD_Pt-170To300_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},
#   "QCD_Pt-300to470_MuEnrichedPt5_2018": {"location": "/QCD_Pt-300To470_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},
#   "QCD_Pt-470to600_MuEnrichedPt5_2018": {"location": "/QCD_Pt-470To600_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},
#   "QCD_Pt-600to800_MuEnrichedPt5_2018": {"location": "/QCD_Pt-600To800_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},
#   "QCD_Pt-800to1000_MuEnrichedPt5_2018": {"location": "/QCD_Pt-800To1000_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},
#   "QCD_Pt-1000toInf_MuEnrichedPt5_2018": {"location": "/QCD_Pt-1000_MuEnrichedPt5_TuneCP5_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM"},

#   "SingleMuon_Run2016B": {"location": "/SingleMuon/Run2016B-ver2_HIPM_UL2016_MiniAODv2-v2/MINIAOD"},
#   "SingleMuon_Run2016C": {"location": "/SingleMuon/Run2016C-HIPM_UL2016_MiniAODv2-v2/MINIAOD"},
#   "SingleMuon_Run2016D": {"location": "/SingleMuon/Run2016D-HIPM_UL2016_MiniAODv2-v2/MINIAOD"},
#   "SingleMuon_Run2016E": {"location": "/SingleMuon/Run2016E-HIPM_UL2016_MiniAODv2-v2/MINIAOD"},
#   "SingleMuon_Run2016F": {"location": "/SingleMuon/Run2016F-HIPM_UL2016_MiniAODv2-v2/MINIAOD"},

#   "SingleMuon_Run2016Flate": {"location": "/SingleMuon/Run2016F-UL2016_MiniAODv2-v2/MINIAOD"},
#   "SingleMuon_Run2016G": {"location": "/SingleMuon/Run2016G-UL2016_MiniAODv2-v2/MINIAOD"},
#   "SingleMuon_Run2016H": {"location": "/SingleMuon/Run2016H-UL2016_MiniAODv2-v2/MINIAOD"},

#   "SingleMuon_Run2017B": {"location": "/SingleMuon/Run2017B-UL2017_MiniAODv2-v1/MINIAOD"},
#   "SingleMuon_Run2017C": {"location": "/SingleMuon/Run2017C-UL2017_MiniAODv2-v1/MINIAOD"},
#   "SingleMuon_Run2017D": {"location": "/SingleMuon/Run2017D-UL2017_MiniAODv2-v1/MINIAOD"},
#   "SingleMuon_Run2017E": {"location": "/SingleMuon/Run2017E-UL2017_MiniAODv2-v1/MINIAOD"},
#   "SingleMuon_Run2017F": {"location": "/SingleMuon/Run2017F-UL2017_MiniAODv2-v1/MINIAOD"},
  
#   "SingleMuon_Run2018A": {"location": "/SingleMuon/Run2018A-UL2018_MiniAODv2-v2/MINIAOD"},
#   "SingleMuon_Run2018B": {"location": "/SingleMuon/Run2018B-UL2018_MiniAODv2-v2/MINIAOD"},
#   "SingleMuon_Run2018C": {"location": "/SingleMuon/Run2018C-UL2018_MiniAODv2-v2/MINIAOD"},
#   "SingleMuon_Run2018D": {"location": "/SingleMuon/Run2018D-UL2018_MiniAODv2-v3/MINIAOD"}
# }
fdatasets = open('dataset_info.yaml','r')
sample_dict = yaml.safe_load(fdatasets)
Dataset = namedtuple("Dataset", "process dataset")
dataset = Dataset("THEDATASET", sample_dict["THEDATASET"]["location"])

print(dataset.process,dataset.dataset)

time = datetime.now().strftime("%Y%m%d%H%M%S")

config = config()

config.General.requestName = '{}_{}'.format(dataset.process, time)
config.General.workArea = 'crab_projects'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'theconfig.py'
config.JobType.allowUndistributedCMSSW = True

config.Data.inputDataset = dataset.dataset
#config.Data.inputDBS = 'phys03' ## private production MC
config.Data.inputDBS = 'global' ## normal centrally generated MC

#below to be updated for different years
if "Run2017" in dataset.dataset:
  config.Data.lumiMask = 'Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt'
elif "Run2018" in dataset.dataset:
  config.Data.lumiMask = 'Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt'
elif "Run2016Flate" in dataset.dataset or "Run2016G" in dataset.dataset or "Run2016H" in dataset.dataset:
  config.Data.lumiMask = 'Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt'
elif "Run2016B" in dataset.dataset or "Run2016C" in dataset.dataset or "Run2016D" in dataset.dataset or "Run2016E" in dataset.dataset or "Run2016F" in dataset.dataset:
  config.Data.lumiMask = 'Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt'
else:
  print("no lumi mask selected")

#config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Legacy_2016/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt'
##config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/Legacy_2017/Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt'
##config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/Legacy_2018/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt'
#config.Data.lumiMask = 'Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt'

#config.Data.runRange = "271036-284044" ### 2016
# config.Data.runRange = "294927-306462" ### 2017
#config.Data.runRange = "314472-325175" ###  2018

if "Run" in dataset.process:
  config.Data.splitting = 'LumiBased'
  config.Data.unitsPerJob = NJOBS
else:
  config.Data.splitting = 'FileBased'
  config.Data.unitsPerJob = NJOBS


config.Data.outLFNDirBase = '/store/user/sdansana/HToSS/MC/nTuples/'

config.Data.publication = False
campaigntag = dataset.dataset.split('/')[-2]
prefix = campaigntag

if "HToSS" in dataset.process:
    config.Data.outputDatasetTag = campaigntag+"_"+"RUNERA"+"_"+"THESKIM"+"_"+"THEHADRON"
else:
    config.Data.outputDatasetTag = campaigntag+"_"+"RUNERA"+"_"+"THESKIM"
#config.Data.outputDatasetTag = "CRAB3_MC_miniNtupilisation_{}_{}".format(dataset.process, time)

config.Data.allowNonValidInputDataset = True

config.Site.storageSite = 'T2_BE_IIHE' #T2_UK_London_IC, T2_UK_London_Brunel, T2_BE_IIHE
#config.Site.blacklist = ['T2_UK_London_Brunel']
config.Site.ignoreGlobalBlacklist = True

# -*- coding: utf-8 -*-
from collections import namedtuple
from datetime import datetime

from CRABClient.UserUtilities import config

Dataset = namedtuple("Dataset", "process dataset")

## 2017 Datasets
dataset = Dataset("SingleMuon_Run2017B", "/SingleMuon/Run2017B-31Mar2018-v1/MINIAOD")
#dataset = Dataset("SingleMuon_Run2017C", "/SingleMuon/Run2017C-31Mar2018-v1/MINIAOD")
#dataset = Dataset("SingleMuon_Run2017D", "/SingleMuon/Run2017D-31Mar2018-v1/MINIAOD")
#dataset = Dataset("SingleMuon_Run2017E", "/SingleMuon/Run2017E-31Mar2018-v1/MINIAOD")
#dataset = Dataset("SingleMuon_Run2017F", "/SingleMuon/Run2017F-31Mar2018-v1/MINIAOD")

config = config()

config.General.requestName = '{}'.format(dataset.process)
config.General.workArea = 'crab_projects'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'nTupliserData_miniAOD_cfg.py'

config.Data.inputDataset = dataset.dataset
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 100
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/Final/Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON.txt'

config.Data.runRange = "294927-306462"
config.Data.outLFNDirBase = '/store/user/almorton/MC/nTuples/'
config.Data.publication = False
config.Data.outputDatasetTag = "CRAB3_Data_nTuplisation_{}".format(dataset.process)

config.Site.storageSite = 'T2_BE_IIHE' #T2_UK_London_IC, T2_UK_London_Brunel, T2_BE_IIHE
#config.Site.blacklist = ['T2_UK_London_Brunel']


# -*- coding: utf-8 -*-
from collections import namedtuple
from datetime import datetime

from CRABClient.UserUtilities import config

Dataset = namedtuple("Dataset", "process dataset")

## UL 2016 APV Datasets
#dataset = Dataset("SingleMuon_Run2016B", "/SingleMuon/Run2016B-ver2_HIPM_UL2016_MiniAODv2-v2/MINIAOD")
#dataset = Dataset("SingleMuon_Run2016C", "/SingleMuon/Run2016C-HIPM_UL2016_MiniAODv2-v2/MINIAOD")
#dataset = Dataset("SingleMuon_Run2016D", "/SingleMuon/Run2016D-HIPM_UL2016_MiniAODv2-v2/MINIAOD")
#dataset = Dataset("SingleMuon_Run2016E", "/SingleMuon/Run2016E-HIPM_UL2016_MiniAODv2-v2/MINIAOD")
#dataset = Dataset("SingleMuon_Run2016F", "/SingleMuon/Run2016F-HIPM_UL2016_MiniAODv2-v2/MINIAOD")
## UL 2016 Datasets
#dataset = Dataset("SingleMuon_Run2016F", "/SingleMuon/Run2016F-UL2016_MiniAODv2-v2/MINIAOD")
#dataset = Dataset("SingleMuon_Run2016G", "/SingleMuon/Run2016G-UL2016_MiniAODv2-v2/MINIAOD")
#dataset = Dataset("SingleMuon_Run2016H", "/SingleMuon/Run2016H-UL2016_MiniAODv2-v2/MINIAOD")

## UL 2017 Datasets
#dataset = Dataset("SingleMuon_Run2017B", "/SingleMuon/Run2017B-UL2017_MiniAODv2-v1/MINIAOD")
#dataset = Dataset("SingleMuon_Run2017C", "/SingleMuon/Run2017C-UL2017_MiniAODv2-v1/MINIAOD")
dataset = Dataset("SingleMuon_Run2017D", "/SingleMuon/Run2017D-UL2017_MiniAODv2-v1/MINIAOD")
#dataset = Dataset("SingleMuon_Run2017E", "/SingleMuon/Run2017E-UL2017_MiniAODv2-v1/MINIAOD")
#dataset = Dataset("SingleMuon_Run2017F", "/SingleMuon/Run2017F-UL2017_MiniAODv2-v1/MINIAOD")

## UL 2018 Datasets

#dataset = Dataset("SingleMuon_Run2018A", "/SingleMuon/Run2018A-UL2018_MiniAODv2-v2/MINIAOD")
#dataset = Dataset("SingleMuon_Run2018B", "/SingleMuon/Run2018B-UL2018_MiniAODv2-v2/MINIAOD")
#dataset = Dataset("SingleMuon_Run2018C", "/SingleMuon/Run2018C-UL2018_MiniAODv2-v2/MINIAOD")
#dataset = Dataset("SingleMuon_Run2018D", "/SingleMuon/Run2018D-UL2018_MiniAODv2-v3/MINIAOD")

config = config()

config.General.requestName = '{}'.format(dataset.process)
config.General.workArea = 'crab_projects'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'nMiniMuonTupliserData_miniAOD_cfg.py'
config.JobType.allowUndistributedCMSSW = True

config.Data.inputDataset = dataset.dataset
config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 100

#config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/Legacy_2016/Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt'
##config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/Legacy_2017/Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt'
config.Data.lumiMask = 'Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt'
##config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/Legacy_2018/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt'
#config.Data.lumiMask = 'Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt'

#config.Data.runRange = "271036-284044" ### 2016
config.Data.runRange = "294927-306462" ### 2017
#config.Data.runRange = "314472-325175" ###  2018

config.Data.outLFNDirBase = '/store/user/almorton/MC/nTuplesMini/'
config.Data.publication = False
config.Data.outputDatasetTag = "CRAB3_Data_nTuplisation_{}".format(dataset.process)

config.Site.storageSite = 'T2_BE_IIHE' #T2_UK_London_IC, T2_UK_London_Brunel, T2_BE_IIHE
#config.Site.blacklist = ['T2_UK_London_Brunel']


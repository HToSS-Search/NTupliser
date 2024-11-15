# -*- coding: utf-8 -*-
from collections import namedtuple
from datetime import datetime
import yaml

from CRABClient.UserUtilities import config

fdatasets = open('dataset_info.yaml','r')
sample_dict = yaml.safe_load(fdatasets)
Dataset = namedtuple("Dataset", "process dataset")
dataset = Dataset("THEDATASET", sample_dict["THEDATASET"]["location"])

print(dataset.process,dataset.dataset)

time = datetime.now().strftime("%Y%m%d%H%M%S")

config = config()

config.General.requestName = '{}_{}'.format(dataset.process, time)
config.General.workArea = 'crab_projects_August'

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
    #config.Data.outputDatasetTag = campaigntag+"_"+"RUNERA"+"_"+"THESKIM"+"_"+"THEHADRON"
    config.Data.outputDatasetTag = campaigntag+"_"+"RUNERA"+"_"+"THESKIM"+"_"+"THEHADRON"+"_"+"LT"#special for lt reweighting - use above during normal ntuples
else:
    config.Data.outputDatasetTag = campaigntag+"_"+"RUNERA"+"_"+"THESKIM"
#config.Data.outputDatasetTag = "CRAB3_MC_miniNtupilisation_{}_{}".format(dataset.process, time)

config.Data.allowNonValidInputDataset = True

config.Site.storageSite = 'T2_BE_IIHE' #T2_UK_London_IC, T2_UK_London_Brunel, T2_BE_IIHE
#config.Site.blacklist = ['T2_UK_London_Brunel']
config.Site.ignoreGlobalBlacklist = True

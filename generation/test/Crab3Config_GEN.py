from CRABClient.UserUtilities import config

config = config()

config.General.requestName = 'GEN_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2017_210724'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.allowUndistributedCMSSW = True
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '2017_scripts/testProductionGeneration/NLO_HToSS_MH125_MS1_ctauS0_SmuonHadronFiltered_UL_13TeV_py_GEN.py'
config.JobType.maxMemoryMB = 9500
config.JobType.numCores = 8
config.JobType.maxJobRuntimeMin = 1500

config.Data.inputDataset = '/LHE_NLO_ggH_HToSS_2017_UL_210721/almorton-CRAB3_LHE_NLO_ggH_HToSS_2017_UL_210721-932a55fe6896b98f325dc16c3f0777e5/USER'
config.Data.inputDBS = 'phys03'

config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/almorton/MC/GEN/'

config.Data.publication = True
config.Data.outputDatasetTag = "CRAB3_GEN_NLO_ggH_MH125_MS1_ctauS0_2017_210724"

config.Site.storageSite = 'T2_BE_IIHE' #T2_UK_London_IC, T2_UK_London_Brunel, T2_BE_IIHE
#config.Site.blacklist = ['T2_UK_London_Brunel']


from CRABClient.UserUtilities import config

config = config()

config.General.requestName = 'SIM_DIGI2RAW_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2017_210724'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.allowUndistributedCMSSW = True
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '2017_scripts/step1_SIM_DIGI_DATAMIX_L1_DIGI2RAW.py'
config.JobType.maxMemoryMB = 9500
config.JobType.numCores = 8
config.JobType.maxJobRuntimeMin = 1500

config.Data.inputDataset = '/LHE_NLO_ggH_HToSS_2017_UL_210721/almorton-CRAB3_GEN_NLO_ggH_MH125_MS1_ctauS0_2017_210724-4e322ae177fada8582ea437cfc153ea8/USER'
config.Data.inputDBS = 'phys03'

config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/almorton/MC/SIM_DIGI2RAW/'

config.Data.publication = True
config.Data.outputDatasetTag = 'CRAB3_SIM_DIGI2RAW_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS1_ctauS0_2017_210724'

config.Site.storageSite = 'T2_BE_IIHE' #T2_UK_London_IC, T2_UK_London_Brunel, T2_BE_IIHE
#config.Site.blacklist = ['T2_UK_London_Brunel']

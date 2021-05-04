from CRABClient.UserUtilities import config

config = config()

config.General.requestName = 'DIGI2RAW_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1000_2017_200911'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.allowUndistributedCMSSW = True
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '2018_scripts/step1_DIGIPREMIX_S2_DATAMIX_L1_DIGI2RAW_2018.py'
config.JobType.maxMemoryMB = 9500
config.JobType.numCores = 8
config.JobType.maxJobRuntimeMin = 1500

config.Data.inputDataset = '/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1000_2017_200908/almorton-CRAB3_RAW2DIGI_RECO_EI_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1000_2017_200915-f37a88d3be5eb60946d5ea45196f13d8/USER'
config.Data.inputDBS = 'phys03'

config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/almorton/MC/DIGI2RAW/'

config.Data.publication = True
config.Data.outputDatasetTag = 'CRAB3_DIGI2RAW_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS1000_2017_200911'

config.Site.storageSite = 'T2_BE_IIHE' #T2_UK_London_IC, T2_UK_London_Brunel, T2_BE_IIHE
#config.Site.blacklist = ['T2_UK_London_Brunel']

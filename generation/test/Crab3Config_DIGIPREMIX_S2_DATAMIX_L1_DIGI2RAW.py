from CRABClient.UserUtilities import config

config = config()

config.General.requestName = 'DIGI2RAW_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2021_220322'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = False

config.JobType.allowUndistributedCMSSW = True
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '2021_scripts/step1_DIGIPREMIX_S2_DATAMIX_L1_DIGI2RAW_2021.py'
#config.JobType.maxMemoryMB = 9500
#config.JobType.numCores = 8
#config.JobType.maxJobRuntimeMin = 1500

config.Data.allowNonValidInputDataset = True
config.Data.outputPrimaryDataset = "DIGI2RAW_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2021"
config.Data.userInputFiles = open('GEN-SIM_inputFiles.txt').readlines()

#config.Data.inputDataset = '/NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2021_220318/sdansana-CRAB3_GEN-SIM_NLO_HZJ_MH125_MS2_ctauS100_2021_220318-ccfe7dbeae2ad6263e3b1ff5b97b9b3b/USER'
#config.Data.inputDBS = 'phys03'

config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.outLFNDirBase = '/store/user/sdansana/HToSS/MC/DIGI2RAW/'

config.Data.publication = True
config.Data.outputDatasetTag = 'CRAB3_DIGI2RAW_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2021_220322'

config.Site.storageSite = 'T2_BE_IIHE' #T2_UK_London_IC, T2_UK_London_Brunel, T2_BE_IIHE
#config.Site.blacklist = ['T2_UK_London_Brunel']

# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: --python_filename NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS100_TuneCP_13TeV-powheg-pythia8_AOD_cfg.py --eventcontent AODSIM --customise Configuration/DataProcessing/Utils.addMonitoring --datatier AODSIM --fileout file:/pnfs/iihe/cms/store/user/sdansana/HToSS/MC/AODSIM/AODSIM_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2021_220323/step3.root --conditions 120X_mcRun3_2021_realistic_v6 --customise_commands process.AODSIMoutput.outputCommands.extend(['keep  *_particleFlowCluster*_*_*', 'keep *_mix_MergedTrackTruth_*', 'keep *_ecalDigis*_*_*', 'keep *_genParticles*_*_*']); process.AODSIMoutput.outputCommands.append('keep *_particleFlowClusterECAL_*_*'); process.AODSIMoutput.outputCommands.append('keep *_mix_MergedTrackTruth_*'); process.AODSIMoutput.outputCommands.append('keep EBDigiCollection_ecalDigis*_*_*'); process.AODSIMoutput.outputCommands.append('keep EEDigiCollection_ecalDigis*_*_*'); process.AODSIMoutput.outputCommands.append('keep *SrFlagsSorted*_ecalDigis*_*_*'); process.AODSIMoutput.outputCommands.append('keep recoGenParticle*_genParticles_*_*') --step RAW2DIGI,L1Reco,RECO,RECOSIM --geometry DB:Extended --filein file:/pnfs/iihe/cms/store/user/sdansana/HToSS/MC/DIGI2RAW/DIGI2RAW_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2021_220322/step2.root --era Run3 --no_exec --mc -n -1
import FWCore.ParameterSet.Config as cms

from Configuration.Eras.Era_Run3_cff import Run3

process = cms.Process('RECO',Run3)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.RecoSim_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1),
    output = cms.optional.untracked.allowed(cms.int32,cms.PSet)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:/pnfs/iihe/cms/store/user/sdansana/HToSS/MC/DIGI2RAW/DIGI2RAW_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2021_220322/step2.root'),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(
    FailPath = cms.untracked.vstring(),
    IgnoreCompletely = cms.untracked.vstring(),
    Rethrow = cms.untracked.vstring(),
    SkipEvent = cms.untracked.vstring(),
    allowUnscheduled = cms.obsolete.untracked.bool,
    canDeleteEarly = cms.untracked.vstring(),
    deleteNonConsumedUnscheduledModules = cms.untracked.bool(True),
    dumpOptions = cms.untracked.bool(False),
    emptyRunLumiMode = cms.obsolete.untracked.string,
    eventSetup = cms.untracked.PSet(
        forceNumberOfConcurrentIOVs = cms.untracked.PSet(
            allowAnyLabel_=cms.required.untracked.uint32
        ),
        numberOfConcurrentIOVs = cms.untracked.uint32(0)
    ),
    fileMode = cms.untracked.string('FULLMERGE'),
    forceEventSetupCacheClearOnNewRun = cms.untracked.bool(False),
    makeTriggerResults = cms.obsolete.untracked.bool,
    numberOfConcurrentLuminosityBlocks = cms.untracked.uint32(0),
    numberOfConcurrentRuns = cms.untracked.uint32(1),
    numberOfStreams = cms.untracked.uint32(0),
    numberOfThreads = cms.untracked.uint32(1),
    printDependencies = cms.untracked.bool(False),
    sizeOfStackForThreadsInKB = cms.optional.untracked.uint32,
    throwIfIllegalParameter = cms.untracked.bool(True),
    wantSummary = cms.untracked.bool(False)
)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('--python_filename nevts:-1'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.AODSIMoutput = cms.OutputModule("PoolOutputModule",
    compressionAlgorithm = cms.untracked.string('LZMA'),
    compressionLevel = cms.untracked.int32(4),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('AODSIM'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(31457280),
    fileName = cms.untracked.string('file:/pnfs/iihe/cms/store/user/sdansana/HToSS/MC/AODSIM/AODSIM_NLO_ggH_HToSS_SmuonHadronFiltered_MH125_MS2_ctauS100_2021_220323/step3.root'),
    outputCommands = process.AODSIMEventContent.outputCommands
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '120X_mcRun3_2021_realistic_v6', '')

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstruction)
process.recosim_step = cms.Path(process.recosim)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.AODSIMoutput_step = cms.EndPath(process.AODSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.recosim_step,process.endjob_step,process.AODSIMoutput_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

# customisation of the process.

# Automatic addition of the customisation function from Configuration.DataProcessing.Utils
from Configuration.DataProcessing.Utils import addMonitoring 

#call to customisation function addMonitoring imported from Configuration.DataProcessing.Utils
process = addMonitoring(process)

# End of customisation functions


# Customisation from command line

process.AODSIMoutput.outputCommands.extend(['keep  *_particleFlowCluster*_*_*', 'keep *_mix_MergedTrackTruth_*', 'keep *_ecalDigis*_*_*', 'keep *_genParticles*_*_*']); process.AODSIMoutput.outputCommands.append('keep *_particleFlowClusterECAL_*_*'); process.AODSIMoutput.outputCommands.append('keep *_mix_MergedTrackTruth_*'); process.AODSIMoutput.outputCommands.append('keep EBDigiCollection_ecalDigis*_*_*'); process.AODSIMoutput.outputCommands.append('keep EEDigiCollection_ecalDigis*_*_*'); process.AODSIMoutput.outputCommands.append('keep *SrFlagsSorted*_ecalDigis*_*_*'); process.AODSIMoutput.outputCommands.append('keep recoGenParticle*_genParticles_*_*')
#Have logErrorHarvester wait for the same EDProducers to finish as those providing data for the OutputModule
from FWCore.Modules.logErrorHarvester_cff import customiseLogErrorHarvesterUsingOutputCommands
process = customiseLogErrorHarvesterUsingOutputCommands(process)

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion

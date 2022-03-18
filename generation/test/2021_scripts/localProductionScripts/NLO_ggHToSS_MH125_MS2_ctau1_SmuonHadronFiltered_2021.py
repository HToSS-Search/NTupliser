# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: Configuration/GenProduction/python/HToSSTo2Mu2Hadrons/NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS1_TuneCP_13TeV-powheg-pythia8.py --python_filename NLO_ggHToSS_MH125_MS2_ctau1_SmuonHadronFiltered_2021.py --eventcontent RAWSIM --customise Configuration/DataProcessing/Utils.addMonitoring --datatier GEN-SIM --fileout file:step0.root --conditions 120X_mcRun3_2021_realistic_v5 --beamspot Run3RoundOptics25ns13TeVLowSigmaZ --customise_commands process.g4SimHits.Physics.G4GeneralProcess = cms.bool(False)\nprocess.source.numberEventsInLuminosityBlock=cms.untracked.uint32(100) --step LHE,GEN,SIM --geometry DB:Extended --era Run3 --no_exec --mc -n 10
import FWCore.ParameterSet.Config as cms

from Configuration.Eras.Era_Run3_cff import Run3

process = cms.Process('SIM',Run3)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.GeometrySimDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRun3RoundOptics25ns13TeVLowSigmaZ_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10),
    output = cms.optional.untracked.allowed(cms.int32,cms.PSet)
)

# Input source
process.source = cms.Source("EmptySource")

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
    annotation = cms.untracked.string('Configuration/GenProduction/python/HToSSTo2Mu2Hadrons/NLO_HToSSTo2Mu2Hadrons_MH125_MS2_ctauS1_TuneCP_13TeV-powheg-pythia8.py nevts:10'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.RAWSIMoutput = cms.OutputModule("PoolOutputModule",
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    ),
    compressionAlgorithm = cms.untracked.string('LZMA'),
    compressionLevel = cms.untracked.int32(1),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM'),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(20971520),
    fileName = cms.untracked.string('file:step0.root'),
    outputCommands = process.RAWSIMEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
if hasattr(process, "XMLFromDBSource"): process.XMLFromDBSource.label="Extended"
if hasattr(process, "DDDetectorESProducerFromDB"): process.DDDetectorESProducerFromDB.label="Extended"
process.genstepfilter.triggerConditions=cms.vstring("generation_step")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '120X_mcRun3_2021_realistic_v5', '')

process.MuMuFilter = cms.EDFilter("PythiaFilterMotherSister",
    MaxEta = cms.untracked.double(10.0),
    MaxSisterDisplacement = cms.untracked.double(600.0),
    MinEta = cms.untracked.double(-10.0),
    MinNephewPts = cms.untracked.vdouble(5.0),
    MinPt = cms.untracked.double(0.0),
    MotherIDs = cms.untracked.vint32(25),
    NephewIDs = cms.untracked.vint32(13),
    ParticleID = cms.untracked.int32(9000006),
    SisterID = cms.untracked.int32(9000006)
)


process.generator = cms.EDFilter("Pythia8ConcurrentHadronizerFilter",
    PythiaParameters = cms.PSet(
        parameterSets = cms.vstring(
            'pythia8CommonSettings',
            'pythia8CP2Settings',
            'pythia8PowhegEmissionVetoSettings',
            'processParameters'
        ),
        processParameters = cms.vstring(
            'POWHEG:nFinal = 1',
            '9000006:all = sk   skbar    0        0          0       2.0  1.9732e-15  1.0  75.0 1',
            '9000006:oneChannel = 2  0.239 101  13 -13',
            '9000006:addChannel = 3  0.041 101  211 -211',
            '9000006:addChannel = 3  0.35  101  321 -321',
            '9000006:addChannel = 3  0.35  101  311 -311',
            '9000006:mayDecay = on',
            '9000006:isResonance = on',
            '25:m0 = 125.0',
            '25:onMode = off',
            '25:addChannel = 1 0.000000001 101 9000006 -9000006',
            '25:onIfMatch = 9000006 -9000006',
            '9000006:onMode = off',
            '9000006:onNegIfAny = 211',
            '9000006:onNegIfAny = 321',
            '9000006:onNegIfAny = 311',
            '9000006:onPosIfAny = 13'
        ),
        pythia8CP2Settings = cms.vstring(
            'Tune:pp 14',
            'Tune:ee 7',
            'MultipartonInteractions:ecmPow=0.1391',
            'PDF:pSet=17',
            'MultipartonInteractions:bProfile=2',
            'MultipartonInteractions:pT0Ref=2.306',
            'MultipartonInteractions:coreRadius=0.3755',
            'MultipartonInteractions:coreFraction=0.3269',
            'ColourReconnection:range=2.323',
            'SigmaTotal:zeroAXB=off',
            'SpaceShower:rapidityOrder=off',
            'SpaceShower:alphaSvalue=0.13',
            'TimeShower:alphaSvalue=0.13'
        ),
        pythia8CommonSettings = cms.vstring(
            'Tune:preferLHAPDF = 2',
            'Main:timesAllowErrors = 10000',
            'Check:epTolErr = 0.01',
            'Beams:setProductionScalesFromLHEF = off',
            'SLHA:minMassSM = 1000.',
            'ParticleDecays:limitTau0 = on',
            'ParticleDecays:tau0Max = 10',
            'ParticleDecays:allowPhotonRadiation = on'
        ),
        pythia8PowhegEmissionVetoSettings = cms.vstring(
            'POWHEG:veto = 1',
            'POWHEG:pTdef = 1',
            'POWHEG:emitted = 0',
            'POWHEG:pTemt = 0',
            'POWHEG:pThard = 0',
            'POWHEG:vetoCount = 100',
            'SpaceShower:pTmaxMatch = 2',
            'TimeShower:pTmaxMatch = 2'
        )
    ),
    comEnergy = cms.double(14000.0),
    maxEventsToPrint = cms.untracked.int32(1),
    pythiaHepMCVerbosity = cms.untracked.bool(False),
    pythiaPylistVerbosity = cms.untracked.int32(1)
)


process.externalLHEProducer = cms.EDProducer("ExternalLHEProducer",
    args = cms.vstring('/cvmfs/cms.cern.ch/phys_generator/gridpacks/slc6_amd64_gcc481/14TeV/powheg/V2/gg_H_quark-mass-effects_NNPDF30_14TeV_M125/v2/gg_H_quark-mass-effects_NNPDF30_14TeV_M125_tarball.tgz'),
    nEvents = cms.untracked.uint32(10),
    numberOfParameters = cms.uint32(1),
    outputFile = cms.string('cmsgrid_final.lhe'),
    scriptName = cms.FileInPath('GeneratorInterface/LHEInterface/data/run_generic_tarball_cvmfs.sh')
)


process.ProductionFilterSequence = cms.Sequence(process.generator+process.MuMuFilter)

# Path and EndPath definitions
process.lhe_step = cms.Path(process.externalLHEProducer)
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RAWSIMoutput_step = cms.EndPath(process.RAWSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.lhe_step,process.generation_step,process.genfiltersummary_step,process.simulation_step,process.endjob_step,process.RAWSIMoutput_step)
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)
# filter all path with the production filter sequence
for path in process.paths:
	if path in ['lhe_step']: continue
	getattr(process,path).insert(0, process.ProductionFilterSequence)

# customisation of the process.

# Automatic addition of the customisation function from Configuration.DataProcessing.Utils
from Configuration.DataProcessing.Utils import addMonitoring 

#call to customisation function addMonitoring imported from Configuration.DataProcessing.Utils
process = addMonitoring(process)

# End of customisation functions


# Customisation from command line

process.g4SimHits.Physics.G4GeneralProcess = cms.bool(False)
process.source.numberEventsInLuminosityBlock=cms.untracked.uint32(100)
# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion

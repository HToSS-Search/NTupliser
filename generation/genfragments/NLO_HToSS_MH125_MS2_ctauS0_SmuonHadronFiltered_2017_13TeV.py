import FWCore.ParameterSet.Config as cms
from Configuration.Generator.Pythia8CommonSettings_cfi import *
from Configuration.Generator.Pythia8CUEP8M1Settings_cfi import *
from Configuration.Generator.Pythia8PowhegEmissionVetoSettings_cfi import *

externalLHEProducer = cms.EDProducer("ExternalLHEProducer",
    args = cms.vstring('/cvmfs/cms.cern.ch/phys_generator/gridpacks/2017/13TeV/powheg/V2/gg_H_quark-mass-effects_NNPDF31_13TeV_M125/v1/gg_H_quark-mass-effects_NNPDF31_13TeV_M125_slc6_amd64_gcc630_CMSSW_9_3_0.tgz'),
    nEvents = cms.untracked.uint32(1000000),
    numberOfParameters = cms.uint32(1),
    outputFile = cms.string('cmsgrid_final.lhe'),
    scriptName = cms.FileInPath('GeneratorInterface/LHEInterface/data/run_generic_tarball_cvmfs.sh')
)


generator = cms.EDFilter("Pythia8HadronizerFilter",
    maxEventsToPrint = cms.untracked.int32(1),
    pythiaPylistVerbosity = cms.untracked.int32(1),
    filterEfficiency = cms.untracked.double(1.0),
    pythiaHepMCVerbosity = cms.untracked.bool(False),
    comEnergy = cms.double(13000.0),
    PythiaParameters = cms.PSet(
        parameterSets = cms.vstring('pythia8CommonSettings', 
            'pythia8CP2Settings', 
            'pythia8PowhegEmissionVetoSettings', 
            'processParameters'),
        processParameters = cms.vstring('POWHEG:nFinal = 1', 
            '9000006:all = sk   skbar    0        0          0       2.0  1.9732e-13  1.0  75.0 0',
            '9000006:oneChannel = 2  1.0 101  13 -13',
            '9000006:addChannel = 3  1.0 101  1 -1',
            '9000006:addChannel = 3  1.0 101  2 -2',
            '9000006:addChannel = 3  1.0 101  3 -3',
            '9000006:mayDecay = on',
            '9000006:isResonance = on',
            '25:m0 = 125.0',
            '25:onMode = off',
            '25:addChannel = 1 0.000000001 101 9000006 -9000006',
            '25:onIfMatch = 9000006 -9000006',
            '9000006:onMode = off',
            '9000006:onNegIfAny = 1',
            '9000006:onNegIfAny = 2',
            '9000006:onNegIfAny = 3',
            '9000006:onPosIfAny = 13'),
        pythia8CP2Settings = cms.vstring('Tune:pp 14', 
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
            'TimeShower:alphaSvalue=0.13'),
        pythia8CommonSettings = cms.vstring('Tune:preferLHAPDF = 2', 
            'Main:timesAllowErrors = 10000', 
            'Check:epTolErr = 0.01', 
            'Beams:setProductionScalesFromLHEF = off', 
            'SLHA:keepSM = on', 
            'SLHA:minMassSM = 1000.', 
            'ParticleDecays:limitTau0 = on', 
            'ParticleDecays:tau0Max = 10', 
            'ParticleDecays:allowPhotonRadiation = on'),
        pythia8PowhegEmissionVetoSettings = cms.vstring('POWHEG:veto = 1', 
            'POWHEG:pTdef = 1', 
            'POWHEG:emitted = 0', 
            'POWHEG:pTemt = 0', 
            'POWHEG:pThard = 0', 
            'POWHEG:vetoCount = 100', 
            'SpaceShower:pTmaxMatch = 2', 
            'TimeShower:pTmaxMatch = 2')
    ),
)

motherFilter = cms.EDFilter("PythiaFilter",
    MaxEta = cms.untracked.double(9999.0),
    MinEta = cms.untracked.double(-9999.0),
    ParticleID = cms.untracked.int32(9000006) # event must contain scalar, parameter is sign blind
)

muonDecayFilter= cms.EDFilter("PythiaDauVFilter",
    ParticleID = cms.untracked.int32(9000006), #sign dependent
    NumberDaughters = cms.untracked.int32(2), 
    DaughterIDs = cms.untracked.vint32(13, -13), #sign dependent
    MaxEta = cms.untracked.vdouble(9999.0, 9999.0), 
    MinEta = cms.untracked.vdouble(-9999.0, -9999.0),
    MinPt = cms.untracked.vdouble(-1.0, -1.0),
    verbose = cms.untracked.int32(0)
)

pionUpFilter = cms.EDFilter("PythiaDauVFilter",
    MotherID = cms.untracked.int32(9000006),
    ParticleID = cms.untracked.int32(1), #sign dependent
    NumberDaughters = cms.untracked.int32(2),
    DaughterIDs = cms.untracked.vint32(211, -211), #sign dependent
    MinPt           = cms.untracked.vdouble(0.5, 0.5),
    MinEta          = cms.untracked.vdouble(-2.5, 2.5),
    MaxEta          = cms.untracked.vdouble( 2.5, 2.5),
    verbose = cms.untracked.int32(0)
)

pionUpbarFilter = cms.EDFilter("PythiaDauVFilter",
    MotherID = cms.untracked.int32(9000006),
    ParticleID = cms.untracked.int32(-1), #sign dependent
    NumberDaughters = cms.untracked.int32(2),
    DaughterIDs = cms.untracked.vint32(211, -211), #sign dependent
    MinPt           = cms.untracked.vdouble(0.5, 0.5),
    MinEta          = cms.untracked.vdouble(-2.5, 2.5),
    MaxEta          = cms.untracked.vdouble( 2.5, 2.5),
    verbose = cms.untracked.int32(0)
)

pionDownFilter = cms.EDFilter("PythiaDauVFilter",
    MotherID = cms.untracked.int32(9000006),
    ParticleID = cms.untracked.int32(2), #sign dependent
    NumberDaughters = cms.untracked.int32(2),
    DaughterIDs = cms.untracked.vint32(211, -211), #sign dependent
    MinPt           = cms.untracked.vdouble(0.5, 0.5),
    MinEta          = cms.untracked.vdouble(-2.5, 2.5),
    MaxEta          = cms.untracked.vdouble( 2.5, 2.5),
    verbose = cms.untracked.int32(0)
)

pionDownbarFilter = cms.EDFilter("PythiaDauVFilter",
    MotherID = cms.untracked.int32(9000006),
    ParticleID = cms.untracked.int32(-2), #sign dependent
    NumberDaughters = cms.untracked.int32(2),
    DaughterIDs = cms.untracked.vint32(211, -211), #sign dependent
    MinPt           = cms.untracked.vdouble(0.5, 0.5),
    MinEta          = cms.untracked.vdouble(-2.5, 2.5),
    MaxEta          = cms.untracked.vdouble( 2.5, 2.5),
    verbose = cms.untracked.int32(0)
)

pionStrangeFilter = cms.EDFilter("PythiaDauVFilter",
    MotherID = cms.untracked.int32(9000006),
    ParticleID = cms.untracked.int32(3), #sign dependent
    NumberDaughters = cms.untracked.int32(2),
    DaughterIDs = cms.untracked.vint32(211, -211), #sign dependent
    MinPt           = cms.untracked.vdouble(0.5, 0.5),
    MinEta          = cms.untracked.vdouble(-2.5, 2.5),
    MaxEta          = cms.untracked.vdouble( 2.5, 2.5),
    verbose = cms.untracked.int32(0)
)

pionStrangebarFilter = cms.EDFilter("PythiaDauVFilter",
    MotherID = cms.untracked.int32(9000006),
    ParticleID = cms.untracked.int32(-3), #sign dependent
    NumberDaughters = cms.untracked.int32(2),
    DaughterIDs = cms.untracked.vint32(211, -211), #sign dependent
    MinPt           = cms.untracked.vdouble(0.5, 0.5),
    MinEta          = cms.untracked.vdouble(-2.5, 2.5),
    MaxEta          = cms.untracked.vdouble( 2.5, 2.5),
    verbose = cms.untracked.int32(0)
)

chargedKaonUpFilter = cms.EDFilter("PythiaDauVFilter",
    MotherID = cms.untracked.int32(9000006),
    ParticleID = cms.untracked.int32(1), #sign dependent
    NumberDaughters = cms.untracked.int32(2),
    DaughterIDs = cms.untracked.vint32(321, -321), #sign dependent
    MinPt           = cms.untracked.vdouble(0.5, 0.5),
    MinEta          = cms.untracked.vdouble(-2.5, 2.5),
    MaxEta          = cms.untracked.vdouble( 2.5, 2.5),
    verbose = cms.untracked.int32(0)
)

chargedKaonUpbarFilter = cms.EDFilter("PythiaDauVFilter",
    MotherID = cms.untracked.int32(9000006),
    ParticleID = cms.untracked.int32(-1), #sign dependent
    NumberDaughters = cms.untracked.int32(2),
    DaughterIDs = cms.untracked.vint32(321, -321), #sign dependent
    MinPt           = cms.untracked.vdouble(0.5, 0.5),
    MinEta          = cms.untracked.vdouble(-2.5, 2.5),
    MaxEta          = cms.untracked.vdouble( 2.5, 2.5),
    verbose = cms.untracked.int32(0)
)

chargedKaonDownFilter = cms.EDFilter("PythiaDauVFilter",
    MotherID = cms.untracked.int32(9000006),
    ParticleID = cms.untracked.int32(2), #sign dependent
    NumberDaughters = cms.untracked.int32(2),
    DaughterIDs = cms.untracked.vint32(321, -321), #sign dependent
    MinPt           = cms.untracked.vdouble(0.5, 0.5),
    MinEta          = cms.untracked.vdouble(-2.5, 2.5),
    MaxEta          = cms.untracked.vdouble( 2.5, 2.5),
    verbose = cms.untracked.int32(0)
)

chargedKaonDownbarFilter = cms.EDFilter("PythiaDauVFilter",
    MotherID = cms.untracked.int32(9000006),
    ParticleID = cms.untracked.int32(-2), #sign dependent
    NumberDaughters = cms.untracked.int32(2),
    DaughterIDs = cms.untracked.vint32(321, -321), #sign dependent
    MinPt           = cms.untracked.vdouble(0.5, 0.5),
    MinEta          = cms.untracked.vdouble(-2.5, 2.5),
    MaxEta          = cms.untracked.vdouble( 2.5, 2.5),
    verbose = cms.untracked.int32(0)
)

chargedKaonStrangeFilter = cms.EDFilter("PythiaDauVFilter",
    MotherID = cms.untracked.int32(9000006),
    ParticleID = cms.untracked.int32(3), #sign dependent
    NumberDaughters = cms.untracked.int32(2),
    DaughterIDs = cms.untracked.vint32(321, -321), #sign dependent
    MinPt           = cms.untracked.vdouble(0.5, 0.5),
    MinEta          = cms.untracked.vdouble(-2.5, 2.5),
    MaxEta          = cms.untracked.vdouble( 2.5, 2.5),
    verbose = cms.untracked.int32(0)
)

chargedKaonStrangebarFilter = cms.EDFilter("PythiaDauVFilter",
    MotherID = cms.untracked.int32(9000006),
    ParticleID = cms.untracked.int32(-3), #sign dependent
    NumberDaughters = cms.untracked.int32(2),
    DaughterIDs = cms.untracked.vint32(321, -321), #sign dependent
    MinPt           = cms.untracked.vdouble(0.5, 0.5),
    MinEta          = cms.untracked.vdouble(-2.5, 2.5),
    MaxEta          = cms.untracked.vdouble( 2.5, 2.5),
    verbose = cms.untracked.int32(0)
)

kshortUpFilter = cms.EDFilter("PythiaDauVFilter",
    MotherID = cms.untracked.int32(9000006),
    ParticleID = cms.untracked.int32(1), #sign dependent
    NumberDaughters = cms.untracked.int32(2),
    DaughterIDs = cms.untracked.vint32(310, -310), #sign dependent
    MinPt           = cms.untracked.vdouble(0.5, 0.5),
    MinEta          = cms.untracked.vdouble(-2.5, 2.5),
    MaxEta          = cms.untracked.vdouble( 2.5, 2.5),
    verbose = cms.untracked.int32(0)
)

kshortUpbarFilter = cms.EDFilter("PythiaDauVFilter",
    MotherID = cms.untracked.int32(9000006),
    ParticleID = cms.untracked.int32(-1), #sign dependent
    NumberDaughters = cms.untracked.int32(2),
    DaughterIDs = cms.untracked.vint32(310, -310), #sign dependent
    MinPt           = cms.untracked.vdouble(0.5, 0.5),
    MinEta          = cms.untracked.vdouble(-2.5, 2.5),
    MaxEta          = cms.untracked.vdouble( 2.5, 2.5),
    verbose = cms.untracked.int32(0)
)

kshortDownFilter = cms.EDFilter("PythiaDauVFilter",
    MotherID = cms.untracked.int32(9000006),
    ParticleID = cms.untracked.int32(2), #sign dependent
    NumberDaughters = cms.untracked.int32(2),
    DaughterIDs = cms.untracked.vint32(310, -310), #sign dependent
    MinPt           = cms.untracked.vdouble(0.5, 0.5),
    MinEta          = cms.untracked.vdouble(-2.5, 2.5),
    MaxEta          = cms.untracked.vdouble( 2.5, 2.5),
    verbose = cms.untracked.int32(0)
)

kshortDownbarFilter = cms.EDFilter("PythiaDauVFilter",
    MotherID = cms.untracked.int32(9000006),
    ParticleID = cms.untracked.int32(-2), #sign dependent
    NumberDaughters = cms.untracked.int32(2),
    DaughterIDs = cms.untracked.vint32(310, -310), #sign dependent
    MinPt           = cms.untracked.vdouble(0.5, 0.5),
    MinEta          = cms.untracked.vdouble(-2.5, 2.5),
    MaxEta          = cms.untracked.vdouble( 2.5, 2.5),
    verbose = cms.untracked.int32(0)
)

kshortStrangeFilter = cms.EDFilter("PythiaDauVFilter",
    MotherID = cms.untracked.int32(9000006),
    ParticleID = cms.untracked.int32(3), #sign dependent
    NumberDaughters = cms.untracked.int32(2),
    DaughterIDs = cms.untracked.vint32(310, -310), #sign dependent
    MinPt           = cms.untracked.vdouble(0.5, 0.5),
    MinEta          = cms.untracked.vdouble(-2.5, 2.5),
    MaxEta          = cms.untracked.vdouble( 2.5, 2.5),
    verbose = cms.untracked.int32(0)
)

kshortStrangebarFilter = cms.EDFilter("PythiaDauVFilter",
    MotherID = cms.untracked.int32(9000006),
    ParticleID = cms.untracked.int32(-3), #sign dependent
    NumberDaughters = cms.untracked.int32(2),
    DaughterIDs = cms.untracked.vint32(310, -310), #sign dependent
    MinPt           = cms.untracked.vdouble(0.5, 0.5),
    MinEta          = cms.untracked.vdouble(-2.5, 2.5),
    MaxEta          = cms.untracked.vdouble( 2.5, 2.5),
    verbose = cms.untracked.int32(0)
)

ProductionFilterSequence = cms.Sequence(generator * motherFilter * 
                                        pionUpFilter * pionUpbarFilter * pionDownFilter * pionDownbarFilter * pionStrangeFilter * pionStrangebarFilter * 
                                        chargedKaonUpFilter * chargedKaonUpbarFilter * chargedKaonDownFilter * chargedKaonDownbarFilter * chargedKaonStrangeFilter * chargedKaonStrangebarFilter * 
                                        kshortUpFilter * kshortUpbarFilter * kshortDownFilter * kshortDownbarFilter * kshortStrangeFilter * kshortStrangebarFilter)


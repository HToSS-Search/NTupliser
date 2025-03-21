import FWCore.ParameterSet.Config as cms
from Configuration.Generator.Pythia8CommonSettings_cfi import *
from Configuration.Generator.Pythia8CUEP8M1Settings_cfi import *
from Configuration.Generator.Pythia8PowhegEmissionVetoSettings_cfi import *

generator = cms.EDFilter("Pythia8ConcurrentHadronizerFilter",
    maxEventsToPrint = cms.untracked.int32(1),
    pythiaPylistVerbosity = cms.untracked.int32(1),
    pythiaHepMCVerbosity = cms.untracked.bool(False),
    comEnergy = cms.double(13000.0),
    PythiaParameters = cms.PSet(
        parameterSets = cms.vstring('pythia8CommonSettings', 
            'pythia8CP2Settings', 
            'pythia8PowhegEmissionVetoSettings', 
            'processParameters'),
        processParameters = cms.vstring('POWHEG:nFinal = 1', 
            '9000006:all = sk   skbar    0        0          0       1.0  1.9732e-14  1.0  75.0 10',
            '9000006:oneChannel = 2  0.01  101  13 -13',
            '9000006:addChannel = 3  0.654 101  211 -211',
            '9000006:addChannel = 3  0.005 101  321 -321',
            '9000006:addChannel = 3  0.005 101  311 -311',
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

MuMuFilter = cms.EDFilter("PythiaFilterMotherSister",
    MaxEta = cms.untracked.double(10.),
    MinEta = cms.untracked.double(-10.),
    MinPt = cms.untracked.double(0.0),
    ParticleID = cms.untracked.int32(9000006),
    MotherIDs = cms.untracked.vint32(25),
    SisterID = cms.untracked.int32(9000006),
    MaxSisterDisplacement = cms.untracked.double(600.0), # max Lxy displacement to generate in mm, -1 for no max
    NephewIDs = cms.untracked.vint32(13), # ids of the nephews you want to check the pt of
    MinNephewPts = cms.untracked.vdouble(5.0),
)

ProductionFilterSequence = cms.Sequence(generator+MuMuFilter)


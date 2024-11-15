TheSkim = "HToSS"
runEra="MCUL2016"
hadronType="ChargedPion"
doCuts_=bool(True)
isggH_=bool(True)
ctauS=100
mass=2

#Set up the pat environment
import FWCore.ParameterSet.Config as cms
process = cms.Process("customPAT")

from PhysicsTools.PatAlgos.tools.coreTools import *

##The line below always has to be included to make VarParsing work
import FWCore.ParameterSet.VarParsing as VarParsing

#Setting up various environmental stuff that makes all of this jazz actually work.

###############################
####### Global Setup ##########
###############################

process.load('Configuration.Geometry.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('PhysicsTools.PatAlgos.slimming.unpackedTracksAndVertices_cfi')

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")

process.load('RecoBTag.Configuration.RecoBTag_cff')
process.load('RecoJets.Configuration.RecoJetAssociations_cff')
process.load('RecoJets.Configuration.RecoJetAssociations_cff')
process.load('TrackingTools.TransientTrack.TransientTrackBuilder_cfi')

process.load("FWCore.Framework.test.cmsExceptionsFatal_cff")
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("PhysicsTools.HepMCCandAlgos.genParticles_cfi")
process.load('Configuration.StandardSequences.Services_cff')

process.load("FWCore.MessageLogger.MessageLogger_cfi")

options = VarParsing.VarParsing ('analysis')
options.parseArguments()

process.MessageLogger.destinations = ['cerr']
process.MessageLogger.statistics = []
process.MessageLogger.fwkJobReports = []
process.MessageLogger.categories=cms.untracked.vstring('FwkJob'
                                                       ,'FwkReport'
                                                       ,'FwkSummary'
                                                       )

process.MessageLogger.cerr.INFO = cms.untracked.PSet(limit = cms.untracked.int32(0))
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(10000)
process.options = cms.untracked.PSet(
                     wantSummary = cms.untracked.bool(True)
                     )

from Configuration.AlCa.GlobalTag import GlobalTag

## 2016 - 106X_mcRun2_asymptotic_preVFP_v11 OR 106X_mcRun2_asymptotic_v17
## 2017 - 106X_mc2017_realistic_v9
## 2018 - 106X_upgrade2018_realistic_v16_L1v1

if "MCUL2016APV" in runEra:
    process.GlobalTag.globaltag = cms.string('106X_mcRun2_asymptotic_preVFP_v11') #Good for all UL data
    EgammaEra="2016preVFP-UL"
elif "MCUL2016nonAPV" in runEra:
    process.GlobalTag.globaltag = cms.string('106X_mcRun2_asymptotic_v17') #Good for all UL data
    EgammaEra="2016postVFP-UL"
elif "MCUL2017" in runEra:
    process.GlobalTag.globaltag = cms.string('106X_mc2017_realistic_v10') #Good for all UL data
    EgammaEra="2017-UL"
elif "MCUL2018" in runEra:
    process.GlobalTag.globaltag = cms.string('106X_upgrade2018_realistic_v16_L1v1') #Good for all UL data
    EgammaEra="2018-UL"

elif "DataUL2016Flate" in runEra or "DataUL2016G" in runEra or "DataUL2016H" in runEra:
    process.GlobalTag.globaltag = cms.string('106X_dataRun2_v35') #Good for all UL data
    EgammaEra="2016postVFP-UL"
elif "DataUL2016B" in runEra or "DataUL2016C" in runEra or "DataUL2016D" in runEra or "DataUL2016E" in runEra or "DataUL2016F" in runEra:
    process.GlobalTag.globaltag = cms.string('106X_dataRun2_v35') #Good for all UL data
    EgammaEra="2016preVFP-UL"
elif "DataUL2017" in runEra:
    process.GlobalTag.globaltag = cms.string('106X_dataRun2_v35') #Good for all UL data
    EgammaEra="2017-UL"
elif "DataUL2018" in runEra:
    process.GlobalTag.globaltag = cms.string('106X_dataRun2_v35') #Good for all UL data
    EgammaEra="2018-UL"


process.load("NTupliser.NTupliser.MakeTopologyNtuple_miniAOD_LT_cfi")
if doCuts_:
    process.makeTopologyNtupleMiniAOD_LT.doCuts=cms.bool(True) # if set to false will skip ALL cuts. Z veto still applies electron cuts.
    process.makeTopologyNtupleMiniAOD_LT.Skim=cms.string(TheSkim) # if set to false will skip ALL cuts. Z veto still applies electron cuts.
else:
    process.makeTopologyNtupleMiniAOD_LT.doCuts=cms.bool(False) # if set to false will skip ALL cuts. Z veto still applies electron cuts.
    process.makeTopologyNtupleMiniAOD_LT.Skim=cms.string("RANDOM") # if set to false will skip ALL cuts. Z veto still applies electron cuts.

if "MC" in runEra:
    process.makeTopologyNtupleMiniAOD_LT.runMCInfo=cms.bool(True) # prevent checking gen info
    process.makeTopologyNtupleMiniAOD_LT.runPUReWeight=cms.bool(True) #Need to check this
    process.makeTopologyNtupleMiniAOD_LT.isMC=cms.bool(True) 
    if isggH_:
        process.makeTopologyNtupleMiniAOD_LT.isggH=cms.bool(True) # this is set to true for signal samples
        process.makeTopologyNtupleMiniAOD_LT.hadronType=cms.string(hadronType) # if set to false will skip ALL cuts. Z veto still applies electron cuts.
        process.makeTopologyNtupleMiniAOD_LT.lifetime=cms.double(ctauS)
        process.makeTopologyNtupleMiniAOD_LT.mass=cms.double(mass)
        if ctauS==0.1:
            process.makeTopologyNtupleMiniAOD_LT.lifetimeDown=cms.vstring("0.01" , "0.013", "0.017", "0.022", "0.028", "0.036", "0.046", "0.06" , "0.077", "0.1")
            process.makeTopologyNtupleMiniAOD_LT.lifetimeUp=cms.vstring("0.1"  , "0.129", "0.167", "0.215", "0.278", "0.359", "0.464", "0.599", "0.774","1")
        if ctauS==1:
            process.makeTopologyNtupleMiniAOD_LT.lifetimeDown=cms.vstring("0.1"  , "0.129", "0.167", "0.215", "0.278", "0.359", "0.464", "0.599", "0.774","1")
            process.makeTopologyNtupleMiniAOD_LT.lifetimeUp=cms.vstring( "1",  "1.292", "1.668",  "2.154",  "2.783",  "3.594",  "4.642",  "5.995","7.743", "10")
        if ctauS==10:
            process.makeTopologyNtupleMiniAOD_LT.lifetimeDown=cms.vstring( "1",  "1.292", "1.668",  "2.154",  "2.783",  "3.594",  "4.642",  "5.995","7.743", "10")
            process.makeTopologyNtupleMiniAOD_LT.lifetimeUp=cms.vstring("10","12.915", "16.681", "21.544",  "27.826", "35.938", "46.416","59.948", "77.426", "100")
        if ctauS==100:
            process.makeTopologyNtupleMiniAOD_LT.lifetimeDown=cms.vstring("10","12.915", "16.681", "21.544",  "27.826", "35.938", "46.416","59.948", "77.426", "100")
            process.makeTopologyNtupleMiniAOD_LT.lifetimeUp=cms.vstring( "100", "129.155", "166.81" , "215.443",  "278.256",  "359.381","464.159", "599.484", "774.264","1000.")
    else:
        process.makeTopologyNtupleMiniAOD_LT.isggH=cms.bool(False) # this is set to true for signal samples
        process.makeTopologyNtupleMiniAOD_LT.hadronType=cms.string(hadronType) # if set to false will skip ALL cuts. Z veto still applies electron cuts.


## Source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(options.inputFiles)
)

## Maximal Number of Events
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

#process.source.fileNames = [
#        'file:/vols/cms/adm10/MC/ggHZ/NLO_ggHZ_HToSSTobbbb_Vleptonic_M125_MS40_ctauS1000_13TeV/PAT_miniAOD/miniAOD_2017_500.root'
#        'file:/vols/cms/adm10/MC/HZJ/NLO_HZJ_HToSSTodddd_Vleptonic_M125_MS1_ctauS1000_13TeV/PAT_miniAOD/miniAOD_2017_500.root'
#       ]

from PhysicsTools.PatAlgos.patEventContent_cff import *
from PhysicsTools.PatAlgos.patEventContent_cff import patEventContentNoCleaning

process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('patTuple.root'),
                               ## save only events passing the full path
                               #SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                               ## save PAT output; you need a '*' to unpack the list of commands
                               outputCommands = cms.untracked.vstring('drop *', *patEventContentNoCleaning )
                               )

process.out.outputCommands += patEventContent
process.out.outputCommands += patTriggerEventContent
process.out.outputCommands += patExtraAodEventContent
# process.out.outputCommands += cms.untracked.vstring('keep *_flavorHistoryFilter_*_*','keep *_TriggerResults_*_*','keep *_selectedPat*_*_*', 'keep *_*goodOfflinePrimaryVertices*_*_*','keep double_*_rho_*', 'keep patMuons_*_*_*', 'keep *MET*_*_*_*', 'keep *_*MET*_*_*')

#PAT output and various other outpath stuff which is a bit dumb coz I'm probably not even gonna use the outpath. Nevermind.
process.out.fileName = cms.untracked.string('Data_out.root')

#NTuple output
process.TFileService = cms.Service("TFileService", fileName = cms.string (options.outputFile) )
process.options.wantSummary = False
process.out.SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('p'))

#Removing pat output (coz we really don't need it now)
#del process.out

process.p = cms.Path(
    process.makeTopologyNtupleMiniAOD_LT
    )
    # process.ecalBadCalibReducedMINIAODFilter *
    # process.jetCorrection *
    # process.egammaPostRecoSeq *


process.schedule = cms.Schedule( process.p )

process.outpath = cms.EndPath( process.out )

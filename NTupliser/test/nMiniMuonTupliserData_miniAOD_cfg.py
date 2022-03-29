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

process.load("FWCore.Framework.test.cmsExceptionsFatal_cff")
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("PhysicsTools.HepMCCandAlgos.genParticles_cfi")
process.load('Configuration.StandardSequences.Services_cff')

options = VarParsing.VarParsing ('analysis')
options.parseArguments()

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.destinations = ['cerr']
process.MessageLogger.statistics = []
process.MessageLogger.fwkJobReports = []
process.MessageLogger.categories=cms.untracked.vstring('FwkJob'
                                                       ,'FwkReport'
                                                       ,'FwkSummary'
                                                       )

process.MessageLogger.cerr.INFO = cms.untracked.PSet(limit = cms.untracked.int32(0))
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(10000)
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )

from Configuration.AlCa.GlobalTag import GlobalTag

process.GlobalTag.globaltag = cms.string('106X_dataRun2_v35') #Good for all UL data

#There's a bit in here about some btau tags that the code looks for. I don't know if this is significant, however. I'm going to ignore it for now.

from PhysicsTools.SelectorUtils.pvSelector_cfi import pvSelector

#from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD

# If you only want to re-correct for JEC and get the proper uncertainties for the default MET
#runMetCorAndUncFromMiniAOD(process,
#                           isData=True
#                           )


###############################
######### MET Filter ##########
###############################

process.load('RecoMET.METFilters.ecalBadCalibFilter_cfi')
baddetEcallist = cms.vuint32(
    [872439604,872422825,872420274,872423218,872423215,872416066,872435036,872439336,
    872420273,872436907,872420147,872439731,872436657,872420397,872439732,872439339,
    872439603,872422436,872439861,872437051,872437052,872420649,872421950,872437185,
    872422564,872421566,872421695,872421955,872421567,872437184,872421951,872421694,
    872437056,872437057,872437313,872438182,872438951,872439990,872439864,872439609,
    872437181,872437182,872437053,872436794,872436667,872436536,872421541,872421413,
    872421414,872421031,872423083,872421439])

process.ecalBadCalibReducedMINIAODFilter = cms.EDFilter(
    "EcalBadCalibFilter",
    EcalRecHitSource = cms.InputTag("reducedEgamma:reducedEERecHits"),
    ecalMinEt        = cms.double(50.),
    baddetEcal    = baddetEcallist,
    taggingMode = cms.bool(True),
    debug = cms.bool(False)
    )


####
# The N-tupliser/cutFlow
####

process.load("NTupliser.NTupliser.MakeMiniMuonNtuple_miniAOD_cfi")
process.makeMiniMuonNtupleMiniAOD.flavorHistoryTag=cms.bool(False) # change to false at your convenience
process.makeMiniMuonNtupleMiniAOD.runMCInfo=cms.bool(False) # prevent checking gen info
process.makeMiniMuonNtupleMiniAOD.runPUReWeight=cms.bool(False) #Run the reweighting for MC. I think I'm doing this right, but I might check anyway.
#process.makeMiniMuonNtupleMiniAOD.triggerToken = cms.InputTag("TriggerResults","","RECO") # or HLT, depends on file   

#Make the inputs for the n-tupliser right.
process.makeMiniMuonNtupleMiniAOD.muonPFToken = cms.InputTag("slimmedMuons")

## Source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(options.inputFiles)
)

## Maximal Number of Events
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

process.source.fileNames = [
	'file:/user/almorton/CMSSW/CMSSW_10_6_27/src/NTupliser/NTupliser/test/13EBC187-0F39-1346-9BE9-A3E859975436.root',
	]

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
process.out.outputCommands += cms.untracked.vstring('keep *_flavorHistoryFilter_*_*','keep *_TriggerResults_*_*','keep *_selectedPat*_*_*', 'keep *_*goodOfflinePrimaryVertices*_*_*','keep double_*_rho_*', 'keep patMuons_*_*_*', 'keep *MET*_*_*_*', 'keep *_*MET*_*_*')


#PAT output and various other outpath stuff which is a bit dumb coz I'm probably not even gonna use the outpath. Nevermind.
process.out.fileName = cms.untracked.string('Data_out.root')

#NTuple output
process.TFileService = cms.Service("TFileService", fileName = cms.string (options.outputFile) )
process.options.wantSummary = False
process.out.SelectEvents = cms.untracked.PSet(SelectEvents = cms.vstring('p'))

#Removing pat output (coz we really don't need it now)
#del process.out

process.p = cms.Path(
    process.ecalBadCalibReducedMINIAODFilter *
    process.makeMiniMuonNtupleMiniAOD
    )

process.schedule = cms.Schedule( process.p )

process.outpath = cms.EndPath( process.out )

TheSkim = "HToSS"
runEra="DataUL2016Flate"
hadronType="ChargedKaon"
doCuts_=bool(True)
isggH_=bool(False)
    
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


# if "Data" in runEra:
#     process.GlobalTag.globaltag = cms.string('106X_dataRun2_v35') #Good for all UL data
#     if "2017" in runEra:
#         EgammaEra="2017-UL"
#     elif "2018" in runEra:
#         EgammaEra="2018-UL"
#     elif "nonAPV" in runEra:
#         EgammaEra="2016postVFP-UL"
#     elif "APV" in runEra:
#         EgammaEra="2016preVFP-UL"
#     else:
#         EgammaEra="2018-UL"


# process.GlobalTag.globaltag = cms.string('106X_mc2017_realistic_v9')

#There's a bit in here about some btau tags that the code looks for. I don't know if this is significant, however. I'm going to ignore it for now.

#Import jet reco things. Apparently this makes cmsRun crash.
process.load('RecoJets.Configuration.RecoPFJets_cff')

process.ak4JetTracksAssociatorAtVertexPF.jets = cms.InputTag("ak4PFJetsCHS")
process.ak4JetTracksAssociatorAtVertexPF.tracks = cms.InputTag("unpackedTracksAndVertices")
process.impactParameterTagInfos.primaryVertex = cms.InputTag("unpackedTracksAndVertices")
process.inclusiveSecondaryVertexFinderTagInfos.extSVCollection = cms.InputTag("unpackedTracksAndVertices","secondary","")


#Now do cool fast jet correction things!

process.ak4PFJets.doRhoFastjet = True

from PhysicsTools.SelectorUtils.pvSelector_cfi import pvSelector

###############################
########Jet corrections########
###############################

from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection

updateJetCollection(
   process,
   jetSource = cms.InputTag('slimmedJets'),
   labelName = 'UpdatedJEC',
   jetCorrections = ('AK4PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute']), 'None'),
)

process.jetCorrection = cms.Sequence( process.patJetCorrFactorsUpdatedJEC * process.updatedPatJetsUpdatedJEC )

###############################
###EGM Smearing + Regression###
###############################

## All embedded in 2017 miniAODv2

###############################
######## Egamma ID ############
###############################

## All embedded in 2017 miniAODv2, but to rerun on v1 ...
#from EgammaUser.EgammaPostRecoTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
#setupEgammaPostRecoSeq(process,era=EgammaEra)  ### 2016preVFP-UL OR 2016postVFP-UL OR 2017-UL OR 2018-UL
from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
setupEgammaPostRecoSeq(process,runEnergyCorrections=True,runVID=False,era=EgammaEra)  ### 2016preVFP-UL OR 2016postVFP-UL OR 2017-UL OR 2018-UL

#a sequence egammaPostRecoSeq has now been created and should be added to your path, eg process.p=cms.Path(process.egammaPostRecoSeq)

###############################
##### MET Uncertainities ######
###############################

#from PhysicsTools.PatUtils.tools.runMETCorrectionsAndUncertainties import runMetCorAndUncFromMiniAOD

## If you only want to re-correct and get the proper uncertainties
#runMetCorAndUncFromMiniAOD(process,
#                           isData=False,
#                           )

# If you would like to re-cluster and get the proper uncertainties
#runMetCorAndUncFromMiniAOD(process,
#                           isData=False,
#                           pfCandColl=cms.InputTag("packedPFCandidates"),
#                           recoMetFromPFCs=True,
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

process.load("NTupliser.NTupliser.MakeTopologyNtuple_miniAOD_cfi")
########### MODIFY TRIGGER LIST ACCORDING TO RUNERA!!!!! ###########
if "2017" in runEra:
    process.makeTopologyNtupleMiniAOD.triggerList = cms.vstring(*[
        'HLT_IsoMu27_v' #2017 also
    ])
elif "2018" in runEra:
    process.makeTopologyNtupleMiniAOD.triggerList = cms.vstring(*[
        #Updated Muon Triggers for 2016
        'HLT_IsoMu24_v', #2018 also
        #Updated Muon Triggers for 2018
        'HLT_DoubleL2Mu23NoVtx_2Cha_v',
        'HLT_DoubleL2Mu23NoVtx_2Cha_CosmicSeed_v'
        #Updated Muon Triggers for 2017
    ])
else:
    process.makeTopologyNtupleMiniAOD.triggerList = cms.vstring(*[
        #Updated Muon Triggers for 2016
        'HLT_IsoMu24_v' #2018 also
        #Updated Muon Triggers for 2018
        # 'HLT_DoubleL2Mu23NoVtx_2Cha_v',
        # 'HLT_DoubleL2Mu23NoVtx_2Cha_CosmicSeed_v'
	#Updated Muon Triggers for 2017
    ])

if doCuts_:
    process.makeTopologyNtupleMiniAOD.doCuts=cms.bool(True) # if set to false will skip ALL cuts. Z veto still applies electron cuts.
    process.makeTopologyNtupleMiniAOD.Skim=cms.string(TheSkim) # if set to false will skip ALL cuts. Z veto still applies electron cuts.
else:
    process.makeTopologyNtupleMiniAOD.doCuts=cms.bool(False) # if set to false will skip ALL cuts. Z veto still applies electron cuts.
    process.makeTopologyNtupleMiniAOD.Skim=cms.string("RANDOM") # if set to false will skip ALL cuts. Z veto still applies electron cuts.

if "MC" in runEra:
    process.makeTopologyNtupleMiniAOD.runMCInfo=cms.bool(True) # prevent checking gen info
    process.makeTopologyNtupleMiniAOD.runPUReWeight=cms.bool(True) #Need to check this
    process.makeTopologyNtupleMiniAOD.isMC=cms.bool(True) 
    if isggH_:
        process.makeTopologyNtupleMiniAOD.isggH=cms.bool(True) # this is set to true for signal samples
        process.makeTopologyNtupleMiniAOD.hadronType=cms.string(hadronType) # if set to false will skip ALL cuts. Z veto still applies electron cuts.
    else:
        process.makeTopologyNtupleMiniAOD.isggH=cms.bool(False) # this is set to true for signal samples
        process.makeTopologyNtupleMiniAOD.hadronType=cms.string(hadronType) # if set to false will skip ALL cuts. Z veto still applies electron cuts.
if "Data" in runEra:
    process.makeTopologyNtupleMiniAOD.isLHEflag=cms.bool(False)
    process.makeTopologyNtupleMiniAOD.runMCInfo=cms.bool(False) # prevent checking gen info
    process.makeTopologyNtupleMiniAOD.runPUReWeight=cms.bool(False) #Run the reweighting for MC. I think I'm doing this right, but I might check anyway.
    process.makeTopologyNtupleMiniAOD.isMC=cms.bool(False) 
    process.makeTopologyNtupleMiniAOD.isggH=cms.bool(False) # this is set to true for signal samples
    process.makeTopologyNtupleMiniAOD.hadronType=cms.string("ChargedKaon") # Irrelevant for data



process.makeTopologyNtupleMiniAOD.flavorHistoryTag=cms.bool(False) # change to false at your convenience
#process.makeTopologyNtupleMiniAOD.triggerToken = cms.InputTag("TriggerResults","","HLT") # or HLT, depends on file   

#settings to apply tight selection:doCuts
# process.makeTopologyNtupleMiniAOD.doCuts=cms.bool(True)
process.makeTopologyNtupleMiniAOD.minJetPt=cms.double(0.0)
process.makeTopologyNtupleMiniAOD.maxJetEta=cms.double(5.5)
process.makeTopologyNtupleMiniAOD.bDiscCut=cms.double(-1.0)
process.makeTopologyNtupleMiniAOD.minElePt=cms.double(9.0)
process.makeTopologyNtupleMiniAOD.maxEleEta=cms.double(2.7)
process.makeTopologyNtupleMiniAOD.eleRelIso=cms.double(0.50)
process.makeTopologyNtupleMiniAOD.maxInvMuMuMass=cms.double(5.0) #typically using 5 GeV
process.makeTopologyNtupleMiniAOD.minInvMuMuhhMass=cms.double(50)
process.makeTopologyNtupleMiniAOD.maxMuonEta=cms.double(2.50)
process.makeTopologyNtupleMiniAOD.minMuonPt1=cms.double(20.0) #2018 - 20, 2016/2017 - 20 according to finalized trigger
process.makeTopologyNtupleMiniAOD.minMuonPt2=cms.double(5.0)
process.makeTopologyNtupleMiniAOD.maxMuonDeltaR = cms.double(0.5)
process.makeTopologyNtupleMiniAOD.minHadronPt = cms.double(5.0)
process.makeTopologyNtupleMiniAOD.maxHadronEta = cms.double(2.50)
process.makeTopologyNtupleMiniAOD.maxDistForPhotonRej=cms.double(0.04)
process.makeTopologyNtupleMiniAOD.maxDcotForPhotonRej=cms.double(0.03)
# process.makeTopologyNtupleMiniAOD.fillAll=cms.bool(True)
#process.makeTopologyNtupleMiniAOD.btagParameterizationList = cms.vstring()
#process.makeTopologyNtupleMiniAOD.btagParameterizationMode = cms.vstring()
#Don't actually do cuts

#Make the inputs for the n-tupliser right.
process.makeTopologyNtupleMiniAOD.electronPFToken = cms.InputTag("slimmedElectrons", "", "customPAT")
process.makeTopologyNtupleMiniAOD.photonPFToken = cms.InputTag("slimmedPhotons")
process.makeTopologyNtupleMiniAOD.tauPFTag = cms.InputTag("slimmedTaus")
process.makeTopologyNtupleMiniAOD.muonPFToken = cms.InputTag("slimmedMuons")
process.makeTopologyNtupleMiniAOD.jetPFToken = cms.InputTag("updatedPatJetsUpdatedJEC") # Originally slimmedJets, patJetsReapplyJEC is the jet collection with reapplied JECs
process.makeTopologyNtupleMiniAOD.metPFToken = cms.InputTag("slimmedMETs")
process.makeTopologyNtupleMiniAOD.rhoToken = cms.InputTag("fixedGridRhoFastjetAll")                                            
process.makeTopologyNtupleMiniAOD.conversionsToken = cms.InputTag("reducedEgamma", "reducedConversions")

#private signal MC has extra gen info in a new collection
#process.makeTopologyNtupleMiniAOD.genParticles = cms.InputTag("prunedGenParticlesPlus")
#process.makeTopologyNtupleMiniAOD.genSimParticles = cms.InputTag("prunedGenParticlesPlus")

#does miniAOD have general tracks saved from AOD stored? ### ONLY EVER USED FOR DEBUGGING
process.makeTopologyNtupleMiniAOD.hasGeneralTracks = cms.bool(False)
process.makeTopologyNtupleMiniAOD.generalTracksToken = cms.InputTag("generalTracks")

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
    process.egammaPostRecoSeq *
    process.jetCorrection *
    process.ecalBadCalibReducedMINIAODFilter *
    process.makeTopologyNtupleMiniAOD
    )

process.schedule = cms.Schedule( process.p )

process.outpath = cms.EndPath( process.out )

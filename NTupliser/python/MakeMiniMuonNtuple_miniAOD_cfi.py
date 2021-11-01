import FWCore.ParameterSet.Config as cms

makeMiniMuonNtupleMiniAOD = cms.EDAnalyzer('MakeMiniMuonNtupleMiniAOD',
                                           debugMode              = cms.bool(False),
					   is2016 = cms.bool(False),
                                           # "Calo"
                                           packedGenParticleToken = cms.InputTag("packedGenParticles"),
                                           muonTag                = cms.InputTag("slimmedMuons"),
                                           # PF
					   beamSpotToken          = cms.InputTag("offlineBeamSpot"),
                                           muonPFToken            = cms.InputTag("slimmedMuons"),

                                           primaryVertexToken     = cms.InputTag("offlineSlimmedPrimaryVertices"),

					   pileupToken	          = cms.InputTag("slimmedAddPileupInfo"),
                                           triggerToken           = cms.InputTag("TriggerResults","","HLT"),
                                           metFilterToken         = cms.InputTag("TriggerResults", "", "PAT"),
                                           ecalBadCalibReducedMINIAODFilter = cms.InputTag("EcalBadCalibFilter"),
                                           fakeTriggerList        = cms.vstring(), # empty. You can add fake triggers that are run on the fly to this list. No check on the process name is made so when duplicates are available only the latest one is added.
					   isLHEflag              = cms.bool(True),
					   externalLHEToken       = cms.InputTag("externalLHEProducer"), # "externalLHEProducer", "source" for THQ 

					   pdfIdStart             = cms.int32(2001),
					   pdfIdEnd               = cms.int32(2102),
					   hasAlphaWeightFlag     = cms.bool(True),
					   alphaIdStart           = cms.int32(2101),
					   alphaIdEnd             = cms.int32(2102),
                                           skipIsrFsrWeights      = cms.bool(False),

					   pdfInfoFixingToken     = cms.InputTag("pdfInfoFixing"),
					   generatorToken         = cms.InputTag("generator"),
                                          triggerList = cms.vstring(*[
        #Updated Muon Triggers for 2016
        'HLT_IsoMu24_v1',
        'HLT_IsoMu24_v2',
        'HLT_IsoMu24_v4',
        'HLT_IsoTkMu24_v1',
        'HLT_IsoTkMu24_v2',
        'HLT_IsoTkMu24_v3',
        'HLT_IsoTkMu24_v4',
        'HLT_IsoMu27_v3',
        'HLT_IsoMu27_v4',
        'HLT_IsoMu27_v5',
        'HLT_IsoMu27_v7',
        'HLT_IsoTkMu27_v3',
        'HLT_IsoTkMu27_v4',
        'HLT_IsoTkMu27_v5',
        'HLT_IsoTkMu27_v6',
        'HLT_IsoTkMu27_v7',

        'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v2',
        'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v3',
        'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v4',
        'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v7',
       	'HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v2',
       	'HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v3',
       	'HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v6',

	#Updated Muon Triggers for 2017
	'HLT_IsoMu27_v8',
	'HLT_IsoMu27_v9',
	'HLT_IsoMu27_v10',
	'HLT_IsoMu27_v11',
	'HLT_IsoMu27_v12',
	'HLT_IsoMu27_v13',
	'HLT_IsoMu27_v14', ## also 2018

	'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v8',
	'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v9',
	'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v10',
	'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v11',
	'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v12',
	'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v13',
	'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v14',
	'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v1',
	'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v2',

	'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v3',
	'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v4', ## also 2018
	'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v7',
	'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v8',
	'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v1',
	'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v2',
	'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v3',
	'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v4', ## also 2018

        #Updated Muon Triggers for 2018
        'HLT_IsoMu24_v11',
        'HLT_IsoMu24_v12',
        'HLT_IsoMu24_v13',
        'HLT_IsoMu27_v15',
        'HLT_IsoMu27_v16',

        'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v5',
        'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v5',

        ]),
                                           metFilterList = cms.vstring(		
	#MET Filters		
	'Flag_goodVertices',
	'Flag_globalTightHalo2016Filter',
	'Flag_HBHENoiseFilter',
	'Flag_HBHENoiseIsoFilter',
	'Flag_EcalDeadCellTriggerPrimitiveFilter',
        'Flag_BadPFMuonFilter',
	'Flag_BadChargedCandidateFilter',
	'Flag_eeBadScFilter',
        'Flag_ecalBadCalibFilter',
	),	
                                           l1TriggerTag = cms.InputTag("gtDigis"),                                    
                                           checkTriggers = cms.bool(True),
                                           genParticles = cms.InputTag("prunedGenParticles"),
					   genSimParticles = cms.InputTag("prunedGenParticles"),
                                           runMCInfo = cms.bool(True), # if set to true will skip MCInfo section
                                           runPUReWeight = cms.bool(False), #Run pile-up reweighting. Don't do if this is data I guess.
                                           doCuts = cms.bool(False), # if set to false will skip ALL cuts. Z veto still applies electron cuts.
                                           # default preselection settings! see https://twiki.cern.ch/twiki/bin/view/CMS/VplusJets for inspiration

                                           runSwissCross = cms.bool(True),
                                           runPDFUncertainties = cms.bool(False),
                                           useResidualJEC = cms.bool(False),
                                           # muon identification
                                           minMuonPt = cms.double(6.0),
                                           maxMuonEta = cms.double(2.80),
                                           muoRelIso = cms.double(0.50), # muon combined track isolation with delta beta corrections
                                           metCut = cms.double(0.0),
                                           isMCatNLO=cms.bool(False),
                                           isttBar = cms.bool(True),# This affects reweighting things. If set to false, then has a weight of 1.
                                           ttGenEvent = cms.InputTag("null")
                                           )# end of makeMiniMuonNtupleMiniAOD

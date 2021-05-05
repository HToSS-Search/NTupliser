import FWCore.ParameterSet.Config as cms

makeTopologyNtupleMiniAOD = cms.EDAnalyzer('MakeTopologyNtupleMiniAOD',
                                           debugMode              = cms.bool(False),
					   is2016 = cms.bool(False),
                                           # "Calo"
                                           packedCandToken        = cms.InputTag("packedPFCandidates"),
                                           packedGenParticleToken = cms.InputTag("packedGenParticles"),
                                           electronTag            = cms.InputTag("slimmedElectrons"),
                                           tauTag                 = cms.InputTag("slimmedTaus"),
                                           muonTag                = cms.InputTag("slimmedMuons"),
                                           jetLabel               = cms.InputTag("slimmedJets"),
                                           genJetToken            = cms.InputTag("slimmedGenJets"),
                                           photonTag              = cms.InputTag("slimmedPhotons"),
                                           ootPhotonTag           = cms.InputTag("slimmedOOTPhotons"),
                                           metTag                 = cms.InputTag("patMETs"),
                                           # PF
					   beamSpotToken          = cms.InputTag("offlineBeamSpot"),
                                           isolatedTrackToken     = cms.InputTag("isolatedTracks"),
                                           conversionsToken       = cms.InputTag("reducedEgamma", "reducedConversions"),
                                           electronPFToken        = cms.InputTag("slimmedElectrons"),
                                           tauPFTag               = cms.InputTag("slimmedTaus"),
                                           muonPFToken            = cms.InputTag("slimmedMuons"),
                                           jetPFToken             = cms.InputTag("slimmedJets"),
                                           jetPFRecoTag           = cms.InputTag("slimmedJets"),
                                           photonPFToken          = cms.InputTag("slimmedPhotons"),
                                           ootPhotonPFToken       = cms.InputTag("slimmedOOTPhotons"),
                                           metPFToken             = cms.InputTag("slimmedMETs"),
                                           # JPT
                                           #jetJPTTag             = cms.InputTag("selectedPatJetsAK4JPT"),
                                           #metJPTTag             = cms.InputTag("patMETsTC"),

                                           primaryVertexToken     = cms.InputTag("offlineSlimmedPrimaryVertices"),
                                           secondaryVertexToken   = cms.InputTag("slimmedSecondaryVertices"),
                                           kshortToken            = cms.InputTag("slimmedKshortVertices"),
                                           lambdaToken            = cms.InputTag("slimmedLambdaVertices"),

                                           rhoToken               = cms.InputTag("fixedGridRhoFastjetAll"),
					   effAreasConfigFile     = cms.FileInPath("RecoEgamma/ElectronIdentification/data/Fall17/effAreaElectrons_cone03_pfNeuHadronsAndPhotons_94X.txt"),
					   pileupToken	          = cms.InputTag("slimmedAddPileupInfo"),
                                           triggerToken           = cms.InputTag("TriggerResults","","HLT"),
                                           metFilterToken         = cms.InputTag("TriggerResults", "", "PAT"),
                                           ecalBadCalibReducedMINIAODFilter = cms.InputTag("EcalBadCalibFilter"),
                                           fakeTriggerList        = cms.vstring(), # empty. You can add fake triggers that are run on the fly to this list. No check on the process name is made so when duplicates are available only the latest one is added.
					   isLHEflag              = cms.bool(True),
					   externalLHEToken       = cms.InputTag("externalLHEProducer"), # "externalLHEProducer", "source" for THQ 

					   pdfIdStart             = cms.int32(2001),
					   pdfIdEnd               = cms.int32(2100),
					   hasAlphaWeightFlag     = cms.bool(False),
					   alphaIdStart           = cms.int32(2101),
					   alphaIdEnd             = cms.int32(2102),

                                           scalarPid              = cms.int32(9000006),
					   pdfInfoFixingToken     = cms.InputTag("pdfInfoFixing"),
					   generatorToken         = cms.InputTag("generator"),
                                           minLeptons             = cms.int32(0), ## currently deprecated

                                           hasGeneralTracks       = cms.bool(False),
                                           generalTracksToken     = cms.InputTag("generalTracks"),
                                           
                                           bTagList = cms.vstring(
        'pfCombinedInclusiveSecondaryVertexV2BJetTags',        #CombinedSecondaryVertex v2
        'pfDeepCSVJetTags:probudsg',                           #Deep Flavour CSV
        'pfDeepCSVJetTags:probb',                              #Deep Flavour CSV
        'pfDeepCSVJetTags:probc',                              #Deep Flavour CSV
        'pfDeepCSVJetTags:probbb',                             #Deep Flavour CSV
        'pfDeepCSVJetTags:probcc',                             #Deep Flavour CSV
        'pfDeepCMVAJetTags:probudsg',                          #Deep Flavour CMVA
        'pfDeepCMVAJetTags:probb',                             #Deep Flavour CMVA
        'pfDeepCMVAJetTags:probc',                             #Deep Flavour CMVA
        'pfDeepCMVAJetTags:probbb',                            #Deep Flavour CMVA
        'pfDeepCMVAJetTags:probcc',                            #Deep Flavour CMVA
        'pfCombinedCvsLJetTags',                               #Charm vs Light jets
        'pfCombinedCvsBJetTags',                               #Charm vs B jets
        ),
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
	'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v4',
	'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v7',
	'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v8',
	'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v1',
	'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v2',
	'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v3',
	'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v4',

        #Updated Muon Triggers for 2018
        'HLT_IsoMu24_v11',
        'HLT_IsoMu24_v12',
        'HLT_IsoMu24_v13',
        'HLT_IsoMu27_v15',
        'HLT_IsoMu27_v16',

        'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v4'
        'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v5'
        'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v4',
        'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v5',

        ## Displaced Muon triggers

### displaced muons andLevel-2/muon chambers only triggers
        'HLT DoubleMu33NoFiltersNoVtx_v2', #2016 only
        'HLT DoubleMu33NoFiltersNoVtx_v3', #2016 only
        'HLT DoubleMu33NoFiltersNoVtx_v5', #2016 only
        'HLT DoubleMu23NoFiltersNoVtxDisplaced_v2', #2016 only
        'HLT DoubleMu23NoFiltersNoVtxDisplaced_v3', #2016 only
        'HLT DoubleMu23NoFiltersNoVtxDisplaced_v5', #2016 only
        'HLT_L2DoubleMu23_NoVertex_v2', #2016 only
        'HLT_L2DoubleMu23_NoVertex_v3', #2016 only
        'HLT_L2DoubleMu23_NoVertex_v4', #2016 only
        'HLT_L2DoubleMu23_NoVertex_v6', #2016 only

        'HLT_DoubleMu43NoFiltersNoVtx_v2', #2017
        'HLT_DoubleMu43NoFiltersNoVtx_v3', #2017

        'HLT_DoubleL2Mu50_v1',#2017
        'HLT_DoubleL2Mu50_v2',#2017+2018

        'HLT_DoubleL2Mu23NoVtx_2Cha_v1', #2018 only
        'HLT_DoubleL2Mu23NoVtx_2Cha_v2', #2018 only
        'HLT_DoubleL2Mu25NoVtx_2Cha_Eta2p4_v1', #2018 only
        'HLT_DoubleL2Mu25NoVtx_2Cha_Eta2p4_v2', #2018 only
        'HLT_DoubleL2Mu25NoVtx_2Cha_v1', #2018 only
        'HLT_DoubleL2Mu25NoVtx_2Cha_v2', #2018 only
        'HLT_DoubleL2Mu30NoVtx_2Cha_Eta2p4_v1', #2018 only
        'HLT_DoubleL2Mu30NoVtx_2Cha_Eta2p4_v2', #2018 only
        'HLT_DoubleMu33NoFiltersNoVtxDisplaced_v1', #2018 only
        'HLT_DoubleMu40NoFiltersNoVtxDisplaced_v1', #2018 only
        'HLT_DoubleMu43NoFiltersNoVtx_v3', #2018 only 
        'HLT_DoubleMu43NoFiltersNoVtx_v4', #2018 only 
        'HLT_DoubleMu48NoFiltersNoVtx_v3', #2018 only
        'HLT_DoubleMu48NoFiltersNoVtx_v4', #2018 only

        ## BPH muon triggers - 2018 only
        'HLT_Mu12_IP6_part0_v2', #MC
        'HLT_Mu12_IP6_part1_v2', #MC 
        'HLT_Mu12_IP6_part2_v2', #MC
        'HLT_Mu12_IP6_part3_v2', #MC
        'HLT_Mu12_IP6_part4_v2', #MC
        'HLT_Mu9_IP5_part0_v2', #MC
        'HLT_Mu9_IP5_part1_v2', #MC
        'HLT_Mu9_IP5_part2_v2', #MC
        'HLT_Mu9_IP5_part3_v2', #MC
        'HLT_Mu9_IP5_part4_v2', #MC
        'HLT_Mu7_IP4_part0_v2', #MC
        'HLT_Mu7_IP4_part1_v2', #MC
        'HLT_Mu7_IP4_part2_v2', #MC
        'HLT_Mu7_IP4_part3_v2', #MC
        'HLT_Mu7_IP4_part4_v2', #MC
        'HLT_Mu9_IP4_part0_v2', #MC
        'HLT_Mu9_IP4_part1_v2', #MC
        'HLT_Mu9_IP4_part2_v2', #MC
        'HLT_Mu9_IP4_part3_v2', #MC
        'HLT_Mu9_IP4_part4_v2', #MC
        'HLT_Mu8_IP5_part0_v2', #MC
        'HLT_Mu8_IP5_part1_v2', #MC
        'HLT_Mu8_IP5_part2_v2', #MC
        'HLT_Mu8_IP5_part3_v2', #MC
        'HLT_Mu8_IP5_part4_v2', #MC
        'HLT_Mu8_IP6_part0_v2', #MC
        'HLT_Mu8_IP6_part1_v2', #MC
        'HLT_Mu8_IP6_part2_v2', #MC
        'HLT_Mu8_IP6_part3_v2', #MC
        'HLT_Mu8_IP6_part4_v2', #MC
        'HLT_Mu9_IP6_part0_v3', #MC
        'HLT_Mu9_IP6_part1_v3', #MC
        'HLT_Mu9_IP6_part2_v3', #MC
        'HLT_Mu9_IP6_part3_v3', #MC
        'HLT_Mu9_IP6_part4_v3', #MC
        'HLT_Mu8_IP3_part0_v3', #MC
        'HLT_Mu8_IP3_part1_v3', #MC
        'HLT_Mu8_IP3_part2_v3', #MC
        'HLT_Mu8_IP3_part3_v3', #MC
        'HLT_Mu8_IP3_part4_v3', #MC

        ## 2017 DatasetScouting Triggers with prescale = 1
#        'DST_HT250_CaloScouting_v6',
#        'DST_HT250_CaloScouting_v7',
#        'DST_HT250_CaloScouting_v8', ## MC
#        'DST_HT250_CaloScouting_v9',
#        'DST_HT250_CaloBTagScouting_v5',
#        'DST_HT250_CaloBTagScouting_v6',
#        'DST_HT250_CaloBTagScouting_v7', ## MC
#        'DST_HT250_CaloBTagScouting_v8',
#        'DST_HT410_PFScouting_v9',
#        'DST_HT410_PFScouting_v10',
#        'DST_HT410_PFScouting_v11',
#        'DST_HT410_PFScouting_v12', ## MC
#        'DST_HT410_PFScouting_v13',
#        'DST_HT410_PFScouting_v14',
#        'DST_HT410_BTagScouting_v10',
#        'DST_HT410_BTagScouting_v11',
#        'DST_HT410_BTagScouting_v12', ## MC
#        'DST_HT410_BTagScouting_v13',
#        'DST_HT410_BTagScouting_v14',
#        'DST_DoubleMu3_noVtx_CaloScouting_v2',
#        'DST_DoubleMu3_noVtx_CaloScouting_v3',
#        'DST_DoubleMu3_noVtx_CaloScouting_v4', ## MC
#        'DST_DoubleMu3_noVtx_CaloScouting_v5',

        ]),
                                           metFilterList = cms.vstring(		
	#MET Filters		
	'Flag_goodVertices'
	'Flag_globalTightHalo2016Filter',
	'Flag_HBHENoiseFilter',
	'Flag_HBHENoiseIsoFilter',
	'Flag_EcalDeadCellTriggerPrimitiveFilter',
        'Flag_BadPFMuonFilter',
	'Flag_BadChargedCandidateFilter',
	'Flag_eeBadScFilter'
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

                                           #Some jet cuts.
                                           minJetPt = cms.double(0.), #min jet pT in GeV/c
                                           maxJetEta = cms.double(5.5), # jet |eta|

                                           runSwissCross = cms.bool(True),
                                           runPDFUncertainties = cms.bool(False),
                                           useResidualJEC = cms.bool(False),
                                           minElePt = cms.double(9.0), #  electron pT in GeV
                                           maxEleEta = cms.double(2.70), #  electron |eta|
					   eleRelIso = cms.double(0.50), # electron combined rel track iso with rho corrections
                                           # muon identification
                                           minMuonPt = cms.double(6.0),
                                           maxMuonEta = cms.double(2.80),
                                           muoRelIso = cms.double(0.50), # muon combined track isolation with delta beta corrections
                                           metCut = cms.double(0.0),
                                           # photon rejection:
                                           dREleGeneralTrackMatchForPhotonRej=cms.double(0.3),
                                           magneticFieldForPhotonRej=cms.double(3.8),
                                           correctFactorForPhotonRej=cms.double(-0.003),
                                           maxDistForPhotonRej=cms.double(0),
                                           maxDcotForPhotonRej=cms.double(0),
                                           isMCatNLO=cms.bool(False),
                                           isttBar = cms.bool(True),# This affects reweighting things. If set to false, then has a weight of 1.
                                           ttGenEvent = cms.InputTag("null")
                                           )# end of MakeTopologyNtupleMiniAOD

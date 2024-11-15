import FWCore.ParameterSet.Config as cms

makeTopologyNtupleMiniAOD_LT = cms.EDAnalyzer('MakeTopologyNtupleMiniAOD_LT',
                                           debugMode              = cms.bool(False),
					   is2016 = cms.bool(False),
					   pileupToken	          = cms.InputTag("slimmedAddPileupInfo"),
					   generatorToken         = cms.InputTag("generator"),
                                           genParticles = cms.InputTag("prunedGenParticles"),
					   genSimParticles = cms.InputTag("prunedGenParticles"),
                                           runMCInfo = cms.bool(True), # if set to true will skip MCInfo section
                                           runPUReWeight = cms.bool(False), #Run pile-up reweighting. Don't do if this is data I guess.
                                           doCuts = cms.bool(False), # if set to false will skip ALL cuts. Z veto still applies electron cuts.
                                           Skim = cms.string("Default"),
                                           isMC=cms.bool(False),
                                           isggH = cms.bool(False),
                                           hadronType = cms.string(""),
                                           lifetime = cms.double(-1), # jet |eta|
                                           mass = cms.double(-1), # jet |eta|
                                           lifetimeUp=cms.vstring('-1' , '-1', '-1', '-1', '-1', '-1', '-1', '-1', '-1', '-1'),
                                           lifetimeDown=cms.vstring('-1' , '-1', '-1', '-1', '-1', '-1', '-1', '-1', '-1', '-1')
                                           )# end of MakeTopologyNtupleMiniAOD

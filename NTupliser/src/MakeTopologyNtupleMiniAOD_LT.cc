// -*- C++ -*-
//
// Package:    MakeTopologyNtuple
// Class:      MakeTopologyNtuple
// %
/**\class MakeTopologyNtuple MakeTopologyNtuple.cc
   FreyaAnalysis/MakeTopologyNtuple/src/MakeTopologyNtuplecc Description: <one
   line class summary> Implementation: <Notes on implementation>
*/
//
// Original Author:  Freya Blekman
// Modified by: Duncan Leggat, Alexander Morton
//         Created:  Mon Feb 16 12:53:13 CET 2009
// $Id: MakeTopologyNtuple.cc,v 1.115 2010/12/09 14:23:24 chadwick Exp $
// Modified: Thur April 30 2009
// Vesna --> Add the MC truth information.
//
//

// system include files
#include <boost/numeric/conversion/cast.hpp>
#include <cstdio>
#include <memory>
// user include files
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/IsolatedTrack.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/Candidate/interface/VertexCompositePtrCandidate.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/PdfInfo.h"
// JEC
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/PhysicsToolsObjects/interface/BinningPointByMap.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "RecoBTag/PerformanceDB/interface/BtagPerformance.h"
#include "RecoBTag/Records/interface/BTagPerformanceRecord.h"
#include "RecoEgamma/EgammaTools/interface/ConversionFinder.h"
#include "RecoEgamma/EgammaTools/interface/ConversionInfo.h"

// includes to make hadron/photonISO varaibles
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Lepton.h"

// Includes for conversion
#include "DataFormats/EgammaCandidates/interface/Conversion.h"
#include "DataFormats/EgammaCandidates/interface/ConversionFwd.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"
#include "RecoEgamma/EgammaTools/interface/EffectiveAreas.h"

// Including this for top pt reweighting
#include "AnalysisDataFormats/TopObjects/interface/TtGenEvent.h"

// Including this for hit patterns - needed for getting the lost number of
// tracker hits
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/GeometryCommonDetAlgo/interface/Measurement1D.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/METReco/interface/SigInputObj.h"
#include "DataFormats/TrackReco/interface/HitPattern.h"
#include "Math/GenVector/PxPyPzM4D.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "NTupliser/NTupliser/interface/MakeTopologyNtupleMiniAOD_LT.h"
#include "RecoLocalCalo/EcalRecAlgos/interface/EcalSeverityLevelAlgo.h"
#include "RecoMET/METAlgorithms/interface/significanceAlgo.h"
#include "TClonesArray.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include "TrackingTools/PatternTools/interface/ClosestApproachInRPhi.h"
#include "TrackingTools/IPTools/interface/IPTools.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/TrajectoryState/interface/TrajectoryStateTransform.h"
#include "RecoVertex/VertexPrimitives/interface/TransientVertex.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#include "RecoVertex/AdaptiveVertexFit/interface/AdaptiveVertexFitter.h"

#include <boost/container/vector.hpp>
#include <boost/numeric/conversion/cast.hpp>
#include <cmath>
#include <fstream>
#include <iostream>
#include <exception>
#include <map>
#include <string>
#include <vector>
#include <limits>

// relIso stuff
#include "DataFormats/PatCandidates/interface/Isolation.h"
#include "DataFormats/RecoCandidate/interface/IsoDeposit.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositDirection.h"
#include "DataFormats/RecoCandidate/interface/IsoDepositVetos.h"
#include "EgammaAnalysis/ElectronTools/interface/ElectronEffectiveArea.h"

#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"

// using namespace reweight;
using boost::numeric_cast;
typedef math::XYZTLorentzVectorF LorentzVector;
typedef math::PtEtaPhiELorentzVectorD FourVectorPtEtaPhiEVector;
typedef math::PtEtaPhiMLorentzVectorD FourVectorPtEtaPhiMVector;


MakeTopologyNtupleMiniAOD_LT::MakeTopologyNtupleMiniAOD_LT(
    const edm::ParameterSet& iConfig)
    : genParticlesToken_{consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("genParticles"))}
    , genSimParticlesToken_{consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("genSimParticles"))}
    , pileupToken_{consumes<std::vector<PileupSummaryInfo>>(iConfig.getParameter<edm::InputTag>("pileupToken"))}
    , isggH_{iConfig.getParameter<bool>("isggH")}
    , hadronType_{iConfig.getParameter<std::string>("hadronType")}
    , generatorToken_{consumes<GenEventInfoProduct>(iConfig.getParameter<edm::InputTag>("generatorToken"))}
    , runMCInfo_{iConfig.getParameter<bool>("runMCInfo")}
    , runPUReWeight_{iConfig.getParameter<bool>("runPUReWeight")}
    , doCuts_{iConfig.getParameter<bool>("doCuts")}
    , Skim_{iConfig.getParameter<std::string>("Skim")}
    , isMC_{iConfig.getParameter<bool>("isMC")}
    , orig_lt{iConfig.getParameter<double>("lifetime")}
    , mass{iConfig.getParameter<double>("mass")}
    , lifetimeUp_{iConfig.getParameter<std::vector<std::string>>("lifetimeUp")}
    , lifetimeDown_{iConfig.getParameter<std::vector<std::string>>("lifetimeDown")}
{
    // , scalarPid_{iConfig.getParameter<int>("scalarPid")}

    // filledBIDInfo_ = false;
    int npts = lifetimeDown_.size()+lifetimeUp_.size()-1;
    // int npts=20-1;
    histocontainer1D_["eventcount"] = fs->make<TH1D>("eventcount", "events processed", 1, -0.5, +0.5);
    histocontainer1D_["sumWeights_lt"] = fs->make<TH1D>("weightHisto", "weightHisto", npts, 0.5, npts+0.5);

    eventCount = 0;
    bookBranches(); // and fill tree

    // Some debugging variables
}

MakeTopologyNtupleMiniAOD_LT::~MakeTopologyNtupleMiniAOD_LT() {
    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)

    mytree_->FlushBaskets();
}

//
// member functions
//
void MakeTopologyNtupleMiniAOD_LT::fillSummaryVariables() {
    ran_postloop_ = true;
    return;
}

void MakeTopologyNtupleMiniAOD_LT::fillEventInfo(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
    if (ran_PV_) return;
    ran_PV_ = true;

    evtRun = iEvent.id().run();
    evtnum = iEvent.id().event();
    evtlumiblock = iEvent.luminosityBlock(); // or even: iEvent.luminosityBlock() might work, depending on the release
    // std::cout<<"evtRun,evtnum,evtlumiblock:"<<evtRun<<","<<evtnum<<","<<evtlumiblock<<std::endl;
    // std::cout<<"evtRun,evtnum,evtlumiblock:"<<iEvent.id().run()<<","<<iEvent.id().event()<<","<<iEvent.luminosityBlock()<<std::endl;

}
void MakeTopologyNtupleMiniAOD_LT::fillMCInfo(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

    edm::Handle<reco::GenParticleCollection> genParticles;
    iEvent.getByToken(genSimParticlesToken_, genParticles);

    if (!genParticles.isValid())
    {
        iEvent.getByToken(genParticlesToken_, genParticles);
    }

    nGenPar = 0;

    for (reco::GenParticleCollection::const_iterator it = genParticles->begin(); it != genParticles->end(); ++it) {

        // std::cout << "Status: " << it->status() << std::endl;
         // std::cout << "pdgId: " << it->pdgId() << std::endl;
        // std::cout << "pT: " << it->pt() << std::endl;
        // std::cout << "#Mothers: " << it->numberOfMothers() << std::endl;
        // std::cout << "#Daughters: " << it->numberOfDaughters() <<
        // std::endl;

        // if(it->isMostlyLikePythia6Status3()) // Pythia 6 criteria - MC generators now
        // use Pythia 8 - will store status instead of cutting on it.
        // if (std::abs(it->pdgId()) <= 18 || std::abs(it->pdgId()) == 24 || std::abs(it->pdgId()) == 23) {
        // only do this for particles with reasonable pT:
        if (nGenPar < NGENPARMAX) {
					  /*if ((evtRun==1) && (evtnum == 12579) && (evtlumiblock==12) && (std::abs(it->pdgId())==9000006)) {
							std::cout<<"Gen particle Pt,Eta,Phi,E,M,P:"<<it->pt()<<","<<it->eta()<<","<<it->phi()<<","<<it->energy()<<","<<it->mass()<<","<<it->p()<<std::endl;
						}*/
            // if(it->pt()>5. && nGenPar<NGENPARMAX)
            // these are sufficient to fill a lorentz vector, to save space
            // no duplicated information...
            genParEta[nGenPar] = it->eta();
            genParPhi[nGenPar] = it->phi();
            genParE[nGenPar] = it->energy();
            genParPt[nGenPar] = it->pt();
            genParId[nGenPar] = it->pdgId();
            genParVx[nGenPar] = it->vx();
            genParVy[nGenPar] = it->vy();
            genParVz[nGenPar] = it->vz();

            // if ( it->bestTrack() != nullptr) std::cout << "test: " << it->bestTrack()->vx() << std::endl;

            genParNumMothers[nGenPar] = it->numberOfMothers(); 
            if (it->numberOfMothers() > 0 ) genParMotherId[nGenPar] =  it->mother()->pdgId(); 
            else genParMotherId[nGenPar] = 0; // guards against seg fault if particle has no mother
            int idx {1};
            if (it->numberOfMothers() > 0 ) {
                for (reco::GenParticleCollection::const_iterator mit = genParticles->begin(); mit != genParticles->end(); ++mit) {
                    if(it->mother() == &(*mit)) {
                        idx = std::distance(genParticles->begin(), mit);
                        break;
                    }
                }
            }
            genParMotherIndex[nGenPar] = idx;
            genParNumDaughters[nGenPar] = it->numberOfDaughters(); 

            genParDaughterId1[nGenPar] = 0;
            genParDaughterId2[nGenPar] = 0;
            if (it->numberOfDaughters() > 0) genParDaughterId1[nGenPar] = it->daughter(0)->pdgId();
            if (it->numberOfDaughters() > 1) genParDaughterId2[nGenPar] = it->daughter(1)->pdgId();
            int idx_d1 {-1}, idx_d2 {-1};
            if (it->numberOfDaughters() > 0) {
                for (reco::GenParticleCollection::const_iterator mit = genParticles->begin(); mit != genParticles->end(); ++mit) {
                    if(it->daughter(0) == &(*mit)) {
                        idx_d1 = std::distance(genParticles->begin(), mit);
                        break;
                    }
                }
            }
            if (it->numberOfDaughters() > 1) {
                for (reco::GenParticleCollection::const_iterator mit = genParticles->begin(); mit != genParticles->end(); ++mit) {
                    if(it->daughter(0) == &(*mit)) {
                        idx_d2 = std::distance(genParticles->begin(), mit);
                        break;
                    }
                }
            }
            genParDaughter1Index[nGenPar] = idx_d1;
            genParDaughter2Index[nGenPar] = idx_d2;

            genParStatus[nGenPar] = it->status(); 
            genParCharge[nGenPar] = it->charge();
            nGenPar++;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////
void MakeTopologyNtupleMiniAOD_LT::clearMCarrays(){
    nGenPar=0;
    for (size_t i{0}; i < NGENPARMAX; i++) {
        genParEta[i]=-1;
        genParPhi[i]=-1;
        genParE[i]=-1;
        genParPt[i]=-1;
        genParId[i]=-1;
        genParVx[i]=-1;
        genParVy[i]=-1;
        genParVz[i]=-1;
        genParNumMothers[i]=-1;
        genParMotherId[i]=-1;
        genParMotherIndex[i]=-1;
        genParNumDaughters[i]=-1;
        genParDaughterId1[i]=-1;
        genParDaughterId2[i]=-1;
        genParDaughter1Index[i]=-1;
        genParDaughter2Index[i]=-1;
        genParStatus[i]=-1;
        genParCharge[i]=-1;
    }
}


/////////////////////////////////////
void MakeTopologyNtupleMiniAOD_LT::cleararrays() {
    // reset the bookkeeping bools;
    // std::cout << "cleararrays CHECK" << std::endl;
    // std::cout << "before FALSE: " << ran_postloop_ << std::endl;
    ran_jetloop_ = ran_eleloop_ = ran_muonloop_ = ran_PV_ = ran_BS_ = ran_tracks_ = ran_isotracks_ = ran_packedCands_ = ran_mcloop_ = ran_postloop_ = ran_photonTau_ = false;
//     // std::cout << "psot FALSE: " << ran_postloop_ << std::endl;

    // clearPVarrays();
    // clearSVarrays();
    // std::cout << "Cleared PV, SV arrays" << std::endl;
    // NOTE: TriggerRes element is a branch HENCE it has already been initialized at the start of Run
    // for (size_t iTrig{0}; iTrig < triggerList_.size(); iTrig++) { 
    //     triggerRes[iTrig]=-99;
    // }
    // // std::cout << "Cleared trig res arrays" << std::endl;
    // for (size_t iMetFilter{0}; iMetFilter < metFilterList_.size(); iMetFilter++) {
    //     metFilterRes[iMetFilter]=-99;
    // }
    // std::cout << "Cleared met filter res arrays" << std::endl;

//    Flag_ecalBadCalibReducedMINIAODFilter = -99; // Manually set rerun filter that's in its own object

    // for (int& HLT_fakeTriggerValue : HLT_fakeTriggerValues) {
    //     HLT_fakeTriggerValue = -99;
    // }
    // for (size_t ii{0}; ii < 200; ii++)  {
    //     TriggerBits.push_back(-99);
    // }
    // std::cout << "Cleared trigger arrays" << std::endl;


    // clearjetarrays("Calo");
    // clearelectronarrays("Calo");
    // clearmuonarrays("Calo");
    // clearMetArrays("Calo");
//    clearTauArrays("Calo");
//    clearPhotonArrays("Calo");

    // clearjetarrays("PF");
    // clearelectronarrays("PF");
    // clearmuonarrays("PF");
    // clearMetArrays("PF");
    // std::cout << "Cleared muon, MET arrays" << std::endl;

    // clearTauArrays("PF");
//    clearPhotonArrays("PF");

    // clearjetarrays("AK5PF");

    // clearjetarrays("JPT");
    // clearMetArrays("JPT");

    clearMCarrays();
    // std::cout << "Cleared MC arrays" << std::endl;

//    clearGeneralTracksArrays();
//    clearIsolatedTracksArrays();
//    clearLostTracksArrays();
    // clearPackedCandsArrays();
    // std::cout << "Cleared PackedCand arrays" << std::endl;


    // mhtSignif = -1;
    // mhtPx = -9999.;
    // mhtPy = -9999.;
    // mhtPhi = -9999.;
    // mhtSumEt = -1;
    // mhtPt = -1;

    // std::cout << "Cleared mht stuff" << std::endl;


    // metSignificance = -9999.; // metHandle->front().metSignificance();
    // metScalarEt = -9999.; // metHandle->front().sumEt();
    // metEtUncorrected = -9999.; // metHandle->front().uncorrectedPt();
    // metPhiUncorrected = -9999.; // metHandle->front().uncorrectedPhi();

    // topo_sphericity = -1;
    // topo_aplanarity = -1;
    // topo_ht = -1;
    // topo_sqrts = -1;
    // // and same but including the electron.
    // topo_sphericitye = -1;
    // topo_aplanaritye = -1;
    // topo_hte = -1;
    // topo_sqrtse = -1;
    // flavorHistory = 999;

    // clear zcandidates;

    // beamSpotX = beamSpotY = beamSpotZ = 0;
    // math::XYZPoint point(beamSpotX, beamSpotY, beamSpotZ);
    // beamSpotPoint_ = point;
    // vertexPoint_ = point;
    // vertexPrimary_ = 0;

    evtRun = 0;
    evtnum = 0;
    evtlumiblock = 0.;
}

void MakeTopologyNtupleMiniAOD_LT::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
    using namespace edm;
    if (debugMode_) {
        std::cout << iEvent.id().run() << " " << iEvent.luminosityBlock() << " "
                << iEvent.id().event()
                << std::endl; // Run pile-up reweighting here
    }
    numVert = 0;
    if (runPUReWeight_) {
        edm::Handle<std::vector<PileupSummaryInfo>> pileupSummaryInfo_;
        iEvent.getByToken(
            pileupToken_,
            pileupSummaryInfo_); // miniAODv1 uses "addPileupInfo", miniAODv2
                                 // uses "slimmedAddPileupInfo"

        std::vector<PileupSummaryInfo>::const_iterator PVI;

        float Tnpv{-1};
        for (PVI = pileupSummaryInfo_->begin(); PVI != pileupSummaryInfo_->end(); PVI++) {
            int BX{PVI->getBunchCrossing()};

            if (BX == 0) {
                Tnpv = pileupSummaryInfo_->begin()->getTrueNumInteractions();
                continue;
            }
        }
        numVert = Tnpv;
    }
    if (debugMode_) std::cout << "passes PUReweight" << std::endl;

    cleararrays();

    fillEventInfo(iEvent,iSetup);


    if (debugMode_) std::cout << "now in loop" << std::endl;
    if (debugMode_) std::cout << "cleared arrays." << std::endl;
    

    if (isMC_) {
        fillMCInfo(iEvent, iSetup);
        if (debugMode_) std::cout << "Filled MCInfo" << std::endl;
    }
    bool passGenCuts{false};
    if ((isggH_)) {
        // passGenCuts = false;
        if (debugMode_) std::cout << "Enters GenCuts" << std::endl;
        std::vector<int> genMuonIndex;
        std::vector<int> genPionIndex;
        std::vector<int> genChargedKaonIndex;
        std::vector <int> genKaonIndex;
        std::vector<int> genKshortIndex;
        std::vector<int> genKlongIndex;
        std::vector<int> genChsIndex;

        // gen particle loop -> only check final state particles!
        // int nGenPar_Clone = nGenPar;
        for ( unsigned int k = 0; k < nGenPar; k++ ) {
            const int pid { std::abs(genParId[k]) };
            const int motherId { std::abs(genParMotherId[k]) };
            // const int status {genParStatus[k]};
            const int motherIndex {std::abs(genParMotherIndex[k]) };

            bool hasScalarAncestry{false}; //checks if at any point, it comes from scalar
            int ancestorId = 9000006;
            int motherIdtemp = motherId;
            int motherIndextemp = motherIndex;
            int pdgIdtemp = pid;
            int debugCounter=0;
            int nmax = NGENPARMAX;
            while((motherIdtemp!=0) && (motherIndextemp!=-1) && (motherIndextemp < nmax)) {// if no parent, then mother Id is null and there's no index, quit search // index exceeds stored genParticle range, return false for safety
                debugCounter++;
                if (debugMode_) std::cout << "debugCounter: " << debugCounter << std::endl;
                if (debugMode_) std::cout << "Enters right condition ... pdgId = " << pdgIdtemp << " : motherIndex = " << motherIndextemp << " : motherId = " << motherIdtemp << std::endl;
                if (motherIdtemp == std::abs(ancestorId)) {
                    hasScalarAncestry=true; // if parent is ancestor, return true
                    break;
                }
                if ((pdgIdtemp != 130) && (pdgIdtemp != 310) && (pdgIdtemp != 311) && (motherIdtemp != pdgIdtemp)) break; // if parent is not an excited state of same particle, return false except in the case of neutral kaons
                motherIndextemp = genParMotherIndex[motherIndextemp];
                motherIdtemp = genParMotherId[motherIndextemp];
                pdgIdtemp = std::abs(genParId[motherIndextemp]);
            }
            if ( pid == 13 && hasScalarAncestry) {
                genMuonIndex.emplace_back(k);
            }
            else if ( pid == 211 && hasScalarAncestry) {
                genPionIndex.emplace_back(k); //low stats for pions comparitively
                genChsIndex.emplace_back(k);
            }
            else if ( pid == 321 && hasScalarAncestry) {
                genChargedKaonIndex.emplace_back(k);
                genChsIndex.emplace_back(k);
            }
            else if ( pid == 130 && hasScalarAncestry) {
                genKlongIndex.emplace_back(k);
            }
            else if ( pid == 310 && hasScalarAncestry) {
                genKshortIndex.emplace_back(k);
            }
            else if ( pid == 311 && hasScalarAncestry) {
                genKaonIndex.emplace_back(k);
            }
        }
        if (debugMode_) std::cout<<"GenLevelCheck (muons, hadrons) - "<<genMuonIndex.size()<<", "<<genChsIndex.size()<<std::endl;
        if (hadronType_ == "ChargedKaon") {
            if (( genChargedKaonIndex.size() >= 2 )&&(genMuonIndex.size() >= 2)) passGenCuts = true;
        }
        else if (hadronType_ == "ChargedPion") {
            if (( genPionIndex.size() >= 2 )&&(genMuonIndex.size() >= 2)) passGenCuts = true;
        }
        else {
            if (( genChsIndex.size() >= 2 )&&(genMuonIndex.size() >= 2)) passGenCuts = true;
        }
        if (passGenCuts) {
            histocontainer1D_["eventcount"]->Fill(0);
        }
        if (debugMode_) std::cout << "passes eventcount" << std::endl;

            edm::Handle<LHEEventProduct> EventHandle;
            edm::Handle<GenEventInfoProduct> genEventInfo;
            iEvent.getByToken(generatorToken_, genEventInfo);

            if(genEventInfo.isValid()) weight_=genEventInfo->weight();
            else weight_ = 0; //NOTE: Weights from scale variations, PDFs etc. are stored in the relative product. Notice that to be used they need to be renormalized to the central event weight at LHE level which may be different from genEvtInfo->weight()
            if (debugMode_) std::cout << "passes nominal weight" << std::endl;
        // if (passMuonCuts && passGenCuts) mytree_->Fill();
        if (debugMode_) std::cout << "filled tree" << std::endl;
    }
    else passGenCuts = true;
    

    if (!doCuts_) {
        mytree_->Fill(); // If not doing cuts, fill up EVERYTHING
    }
    else  { // If doing cuts, ensure that we have at least x leptons which meet minimum sensible criteria
        if (debugMode_) std::cout << "Entered doCuts" << std::endl;
        if (debugMode_) std::cout<<"Enters HToSS skim"<<std::endl;
        if (debugMode_) std::cout<<"PassGenCuts:"<<passGenCuts<<std::endl;
        // if (passGenCuts) {
        //     histocontainer1D_["eventFilterOR"]->Fill(1);
        //     histocontainer1D_["eventFilterAND"]->Fill(1);
        //     if (isMC_) histocontainer1D_["eventFilterAND_wtd"]->Fill(1,weight_);
        // }
        if (debugMode_) std::cout<<"Passes GenCuts"<<std::endl;
        bool passAllCuts{true};
        if (passGenCuts) {
            // Lifetime reweighting
            int npts=histocontainer1D_["sumWeights_lt"]->GetNbinsX();//should be 2*10-1
            double old_lt = orig_lt;
            if (old_lt<0) {
                std::cout<<"Code's gonna explode so quit now"<<std::endl;
                return;   
            }
            std::vector<float> new_lt_up={};
            std::vector<float> new_lt_down={};
            // int arr[10]={1,2,3,4,5,6,7,8,9,10};
            for (unsigned int i=0;i<lifetimeUp_.size();i++){
                new_lt_up.push_back(std::stof(lifetimeUp_[i]));
                histocontainer1D_["sumWeights_lt"]->GetXaxis()->SetBinLabel(i+(npts-1)/2+1, lifetimeUp_[i].c_str());
                if (i==9) continue; //remove nominal from lt_down part
                new_lt_down.push_back(std::stof(lifetimeDown_[i]));
                // histocontainer1D_["sumWeights_lt"] = fs->make<TH1D>("weightHisto", "weightHisto", npts, -npts/2, npts/2);
                histocontainer1D_["sumWeights_lt"]->GetXaxis()->SetBinLabel(i+1, lifetimeDown_[i].c_str());
            }
            
            for (unsigned int i=0;i<lifetimeUp_.size();i++){
                int S1_ind=-1;
                int S2_ind=-1;
                for (unsigned int k=0;k<=nGenPar;k++) { 
                    if (genParId[k]==9000006) {
                        S1_ind=k;
                    }
                    if (genParId[k]==-9000006) {
                        S2_ind=k;
                    }
                }
                if ((S1_ind<0) || (S2_ind<0)) std::cout<<"problem"<<std::endl;
                float S1_Vx=genParVx[S1_ind];float S1_Vy=genParVy[S1_ind];float S1_Vz=genParVz[S1_ind];
                float S2_Vx=genParVx[S2_ind];float S2_Vy=genParVy[S2_ind];float S2_Vz=genParVz[S2_ind];

                float S1_dau1_Vx=genParVx[genParDaughter1Index[S1_ind]];float S1_dau1_Vy=genParVy[genParDaughter1Index[S1_ind]];float S1_dau1_Vz=genParVz[genParDaughter1Index[S1_ind]];
                float S2_dau1_Vx=genParVx[genParDaughter1Index[S2_ind]];float S2_dau1_Vy=genParVy[genParDaughter1Index[S2_ind]];float S2_dau1_Vz=genParVz[genParDaughter1Index[S2_ind]];

                float S1_dau2_Vx=genParVx[genParDaughter2Index[S1_ind]];float S1_dau2_Vy=genParVy[genParDaughter2Index[S1_ind]];float S1_dau2_Vz=genParVz[genParDaughter2Index[S1_ind]];
                float S2_dau2_Vx=genParVx[genParDaughter2Index[S2_ind]];float S2_dau2_Vy=genParVy[genParDaughter2Index[S2_ind]];float S2_dau2_Vz=genParVz[genParDaughter2Index[S2_ind]];

                float S1_dVx=S1_Vx-S1_dau1_Vx;float S1_dVy=S1_Vy-S1_dau1_Vy;float S1_dVz=S1_Vz-S1_dau1_Vz;
                float S2_dVx=S2_Vx-S2_dau1_Vx;float S2_dVy=S2_Vy-S2_dau1_Vy;float S2_dVz=S2_Vz-S2_dau1_Vz;
                
                float S1_dist = sqrt(S1_dVx*S1_dVx + S1_dVy*S1_dVy + S1_dVz*S1_dVz);
                float S2_dist = sqrt(S2_dVx*S2_dVx + S2_dVy*S2_dVy + S2_dVz*S2_dVz);

                //FourVectorPtEtaPhiEVector* S1_vec = new FourVectorPtEtaPhiEVector(genParPt[S1_ind],genParEta[S1_ind],genParPhi[S1_ind],genParE[S1_ind]);
                //FourVectorPtEtaPhiEVector* S2_vec = new FourVectorPtEtaPhiEVector(genParPt[S2_ind],genParEta[S2_ind],genParPhi[S2_ind],genParE[S2_ind]);
                FourVectorPtEtaPhiMVector* S1_vec = new FourVectorPtEtaPhiMVector(genParPt[S1_ind],genParEta[S1_ind],genParPhi[S1_ind],mass);
                FourVectorPtEtaPhiMVector* S2_vec = new FourVectorPtEtaPhiMVector(genParPt[S2_ind],genParEta[S2_ind],genParPhi[S2_ind],mass);
                
                float lt_wt_up=getLifetimeReweight(old_lt,new_lt_up[i], S1_dist, S2_dist, *S1_vec, *S2_vec);
                histocontainer1D_["sumWeights_lt"]->Fill(i+(npts-1)/2+1,weight_*lt_wt_up);
                if (i==9) continue;//remove nominal from lt_down part
                float lt_wt_down=getLifetimeReweight(old_lt,new_lt_down[i], S1_dist, S2_dist, *S1_vec, *S2_vec);
                histocontainer1D_["sumWeights_lt"]->Fill(i+1,weight_*lt_wt_down);
                //if (lt_wt_down*weight_ > 1e8 ) {
                    std::cout<<"eventRun,eventNum,evtlumiblock:"<<evtRun<<","<<evtnum<<","<<evtlumiblock<<std::endl;
                    //std::cout<<"new_lt_up,old_lt:"<<new_lt_up[i]<<","<<old_lt<<std::endl;
                    //std::cout<<"nominal,lt_wt,reweighted:"<<weight_<<","<<lt_wt_up<<","<<(lt_wt_up*weight_)<<std::endl;
                    std::cout<<"new_lt_down,old_lt:"<<new_lt_down[i]<<","<<old_lt<<std::endl;
                    std::cout<<"nominal,lt_wt,reweighted:"<<weight_<<","<<lt_wt_down<<","<<(lt_wt_down*weight_)<<std::endl;
										std::cout<<"S1 Pt, Eta, Phi, E:"<<genParPt[S1_ind]<<","<<genParEta[S1_ind]<<","<<genParPhi[S1_ind]<<","<<genParE[S1_ind]<<std::endl;
										std::cout<<"S2 Pt, Eta, Phi, E:"<<genParPt[S2_ind]<<","<<genParEta[S2_ind]<<","<<genParPhi[S2_ind]<<","<<genParE[S2_ind]<<std::endl;
                //}

            }

        }
        if (isggH_) {
            if ((passAllCuts)&&(passGenCuts)) mytree_->Fill();
        }
    }
}

Float_t MakeTopologyNtupleMiniAOD_LT::getLifetimeReweight(float old_lt, float new_lt, float L_scalar1, float L_scalar2, FourVectorPtEtaPhiMVector& vec_scalar1, FourVectorPtEtaPhiMVector& vec_scalar2){
    /* MULTIPLIED BY 10 BECAUSE TYPICALLY UNITS OF VTX ARE IN CM */
    //Double_t beta1 = vec_scalar1.Beta();
    //float gamma1 = 1/(sqrt(1-beta1*beta1));
    //Double_t gamma1 = vec_scalar1.Gamma();
		Double_t betagamma_1 = vec_scalar1.P()/mass;
    Double_t t1 = 10*L_scalar1/betagamma_1; 
    //Double_t beta2 = vec_scalar2.Beta();
    //float gamma2 = 1/(sqrt(1-beta2*beta2));
    //Double_t gamma2 = vec_scalar2.Gamma();
		Double_t betagamma_2 = vec_scalar2.P()/mass;
    Double_t t2 = 10*L_scalar2/betagamma_2;
    Double_t weight = pow((old_lt/new_lt),2)*exp((t1+t2)*((1/old_lt) - (1/new_lt)));
    // Float_t weight = old_lt/new_lt*exp((t2)*((1/old_lt) - (1/new_lt)));
    if (weight>1e6) {
        std::cout<<"L_scalar1,P,M,betagamma,t1:"<<L_scalar1<<","<<vec_scalar1.P()<<","<<vec_scalar1.M()<<","<<betagamma_1<<","<<t1<<std::endl;
        std::cout<<"L_scalar2,P,M,betagamma,t2:"<<L_scalar2<<","<<vec_scalar2.P()<<","<<vec_scalar2.M()<<","<<betagamma_2<<","<<t2<<std::endl;
    }
    return weight;
}
void MakeTopologyNtupleMiniAOD_LT::bookBranches() {
    if (debugMode_) std::cout << "bookBranches CHECK" << std::endl;
    TTree::SetMaxTreeSize(std::numeric_limits<Long64_t>::max());
    mytree_ = new TTree("tree", "tree");
    mytree_->SetAutoSave(-std::numeric_limits<Long64_t>::max());

    // bookMuonBranches("PF", "PF2PAT");
    // bookMETBranches("PF", "PF2PAT");
    // bookPackedCandsBranches();
    if (runMCInfo_) {
        bookMCBranches();
    }

    // mytree_->Branch("processId", &processId_, "processId/I");
    // mytree_->Branch("processPtHat", &processPtHat_, "processPtHat/F");
    mytree_->Branch("processMCWeight", &weight_, "processMCWeight/D");
    // mytree_->Branch("processMCWeight_lt", &weight_lt_, "processMCWeight_lt/D");

    mytree_->Branch("eventRun", &evtRun, "eventRun/I");
    mytree_->Branch("eventNum", &evtnum, "eventNum/I");
    mytree_->Branch("eventLumiblock", &evtlumiblock, "eventLumiblock/F");
}

// book MC branches:
void MakeTopologyNtupleMiniAOD_LT::bookMCBranches()
{
    mytree_->Branch("nGenPar", &nGenPar, "nGenPar/I");
    mytree_->Branch("genParEta", genParEta, "genParEta[nGenPar]/F");
    mytree_->Branch("genParPhi", genParPhi, "genParPhi[nGenPar]/F");
    mytree_->Branch("genParE", genParE, "genParE[nGenPar]/F");
    mytree_->Branch("genParPt", genParPt, "genParPt[nGenPar]/F");
    mytree_->Branch("genParId", genParId, "genParId[nGenPar]/I");
    mytree_->Branch("genParVx", genParVx, "genParVx[nGenPar]/F");
    mytree_->Branch("genParVy", genParVy, "genParVy[nGenPar]/F");
    mytree_->Branch("genParVz", genParVz, "genParVz[nGenPar]/F");
    mytree_->Branch("genParNumMothers", genParNumMothers, "genParNumMothers[nGenPar]/I");
    mytree_->Branch("genParMotherId", genParMotherId, "genParMotherId[nGenPar]/I");
    mytree_->Branch("genParMotherIndex", genParMotherIndex, "genParMotherIndex[nGenPar]/I");
    mytree_->Branch("genParNumDaughters", genParNumDaughters, "genParNumDaughters[nGenPar]/I");
    mytree_->Branch("genParDaughterId1", genParDaughterId1, "genParDaughterId1[nGenPar]/I");
    mytree_->Branch("genParDaughterId2", genParDaughterId2, "genParDaughterId2[nGenPar]/I");
    mytree_->Branch("genParDaughter1Index", genParDaughter1Index, "genParDaughter1Index[nGenPar]/I");
    mytree_->Branch("genParDaughter2Index", genParDaughter2Index, "genParDaughter2Index[nGenPar]/I");
    mytree_->Branch("genParStatus",genParStatus, "genParStatus[nGenPar]/I");
    mytree_->Branch("genParCharge", genParCharge, "genParCharge[nGenPar]/I");
}
// ------------ method called once each job just before starting event loop
// ------------
void MakeTopologyNtupleMiniAOD_LT::beginJob()
{
    // if (runPDFUncertainties_)
    // {
    //     // Setup the PDFs
    //     // CTEQ 6.6
    //     initPDFSet(0, "cteq66", LHAPDF::LHGRID, 0);
    //     initPDFSet(1, "MRST2006nnlo", LHAPDF::LHGRID, 0);
    // }
}

// ------------ method called once each job just after ending the event loop
// ------------
void MakeTopologyNtupleMiniAOD_LT::endJob()
{
    std::cout << "+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+="
              << std::endl;
    std::cout << "\n\nJOB Summary:" << std::endl;
    std::cout << "number of events processed: " << histocontainer1D_["eventcount"]->GetEntries() << std::endl;
    std::cout << "number of events added to tree: " << mytree_->GetEntries() << std::endl;
    std::cout << "\n+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+="
              << std::endl;
}

DEFINE_FWK_MODULE(MakeTopologyNtupleMiniAOD_LT);

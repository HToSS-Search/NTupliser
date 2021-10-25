// -*- C++ -*-
//
// Package:    MakeMiniMuonNtuple
// Class:      MakeMiniMuonNtuple
// %
/**\class MakeMiniMuonNtuple MakeMiniMuonNtuple.cc
   FreyaAnalysis/MakeMiniMuonNtuple/src/MakeMiniMuonNtuplecc Description: <one
   line class summary> Implementation: <Notes on implementation>
*/
//
// Original Author:  Freya Blekman
// Modified by: Duncan Leggat, Alexander Morton
//         Created:  Mon Feb 16 12:53:13 CET 2009
// $Id: MakeMiniMuonNtuple.cc,v 1.115 2010/12/09 14:23:24 chadwick Exp $
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
#include "NTupliser/NTupliser/interface/MakeMiniMuonNtupleMiniAOD.h"
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

#include "Math/LorentzVector.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"

// using namespace reweight;
using boost::numeric_cast;
typedef math::XYZTLorentzVectorF LorentzVector;

MakeMiniMuonNtupleMiniAOD::MakeMiniMuonNtupleMiniAOD(
    const edm::ParameterSet& iConfig)
    : beamSpotToken_{consumes<reco::BeamSpot>(iConfig.getParameter<edm::InputTag>("beamSpotToken"))}
    , muoLabel_{iConfig.getParameter<edm::InputTag>("muonTag")}
    , patMuonsToken_{consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muonPFToken"))}
    , trigToken_{consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerToken"))}
    , metFilterToken_{consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("metFilterToken"))}
//    , ecalBadCalibFilterUpdate_token_{mayConsume<bool>(iConfig.getParameter<edm::InputTag>("ecalBadCalibReducedMINIAODFilter"))}
    , fakeTrigLabelList_{iConfig.getParameter<std::vector<std::string>>("fakeTriggerList")}
    , triggerList_{iConfig.getParameter<std::vector<std::string>>("triggerList")}
    , metFilterList_{iConfig.getParameter<std::vector<std::string>>("metFilterList")}
    , l1TrigLabel_{iConfig.getParameter<edm::InputTag>("l1TriggerTag")}
    , genParticlesToken_{consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("genParticles"))}
    , genSimParticlesToken_{consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("genSimParticles"))}
    , pileupToken_{consumes<std::vector<PileupSummaryInfo>>(iConfig.getParameter<edm::InputTag>("pileupToken"))}
    , debugMode_{iConfig.getParameter<bool>("debugMode")}
    , is2016_{iConfig.getParameter<bool>("is2016")}
    , isttbar_{iConfig.getParameter<bool>("isttBar")}
    , ttGenEvent_{iConfig.getParameter<edm::InputTag>("ttGenEvent")}
    , externalLHEToken_{mayConsume<LHEEventProduct>(iConfig.getParameter<edm::InputTag>("externalLHEToken"))}
    , pdfIdStart_{iConfig.getParameter<int>("pdfIdStart")}
    , pdfIdEnd_{iConfig.getParameter<int>("pdfIdEnd")}
    , alphaIdStart_{iConfig.getParameter<int>("alphaIdStart")}
    , alphaIdEnd_{iConfig.getParameter<int>("alphaIdEnd")}
    , pdfInfoToken_{consumes<GenEventInfoProduct>(iConfig.getParameter<edm::InputTag>("pdfInfoFixingToken"))}
    , generatorToken_{consumes<GenEventInfoProduct>(iConfig.getParameter<edm::InputTag>("generatorToken"))}
    , runMCInfo_{iConfig.getParameter<bool>("runMCInfo")}
    , runPUReWeight_{iConfig.getParameter<bool>("runPUReWeight")}
    , doCuts_{iConfig.getParameter<bool>("doCuts")}
    , runPDFUncertainties_{iConfig.getParameter<bool>("runPDFUncertainties")}
    , useResidualJEC_{iConfig.getParameter<bool>("useResidualJEC")}
    , check_triggers_{iConfig.getParameter<bool>("checkTriggers")}
    , isMCatNLO_{iConfig.getParameter<bool>("isMCatNLO")}
    , isLHEflag_{iConfig.getParameter<bool>("isLHEflag")}
    , hasAlphaWeightFlag_{iConfig.getParameter<bool>("hasAlphaWeightFlag")}
    , skipIsrFsrWeights_{iConfig.getParameter<bool>("skipIsrFsrWeights")}
    , isrRedHi{1.0}
    , fsrRedHi{1.0}
    , isrRedLo{1.0}
    , fsrRedLo{1.0}
    , isrDefHi{1.0}
    , fsrDefHi{1.0}
    , isrDefLo{1.0}
    , fsrDefLo{1.0}
    , isrConHi{1.0}
    , fsrConHi{1.0}
    , isrConLo{1.0}
    , fsrConLo{1.0}
{
    // now do what ever initialization is needed

    //{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}
    // define some histograms using the framework tfileservice. Define the
    // output file name in your .cfg.
    //{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}

    //{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}
    // histocontainer_ is of type std::map<std::string, TH1D*>. This means you
    // can use it with this syntax:
    // histocontainer_["histname"]->Fill(x);
    // histocontainer_["histname"]->Draw();
    // etc, etc. Essentially you use the histname string to look up a pointer to
    // a TH1D* which you can do everything to you would normally do in ROOT.
    //{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}

    //{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}
    // here we book new histograms:
    //{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}{}

    filledBIDInfo_ = false;
    histocontainer1D_["eventcount"] = fs->make<TH1D>("eventcount", "events processed", 1, -0.5, +0.5);
    histocontainer1I_["sumWeights"] = fs->make<TH1I>("weightHisto", "weightHisto", 14, -0.5, 13.5);

    // Putting in a few histograms to debug the loose lepton selection
    // hopefully.

    eventCount = 0;
    bookBranches(); // and fill tree
    bTags = 0;
    softTags = 0;

    // Some debugging variables
}

MakeMiniMuonNtupleMiniAOD::~MakeMiniMuonNtupleMiniAOD() {
    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)

    mytree_->FlushBaskets();
}

//
// member functions
//
void MakeMiniMuonNtupleMiniAOD::fillSummaryVariables() {
    ran_postloop_ = true;
    return;
}

void MakeMiniMuonNtupleMiniAOD::fillEventInfo(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
    if (ran_PV_) return;
    ran_PV_ = true;

    evtRun = iEvent.id().run();
    evtnum = iEvent.id().event();
    evtlumiblock = iEvent.luminosityBlock(); // or even: iEvent.luminosityBlock() might work, depending on the release)

    // also add pv:
    edm::Handle<reco::VertexCollection> pvHandle;
    iEvent.getByToken(pvLabel_, pvHandle);

    if (pvHandle.isValid()) {
        std::vector<reco::Vertex> pv{*pvHandle};

        if (pv.size() > 0) {
            for (auto it {pv.begin()}; it != pv.end() && numPVs < numeric_cast<int>(NPVSMAX); it++) {
                if (it->isValid() && it->chi2() != 0 && it->ndof() != 0 ) {
                    math::XYZPoint point(it->x(), it->y(), it->z());
                    vertexPoint_ = point;
                    vertexPrimary_ = &*it;
                    break;
                }
            }
   	}
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////
void MakeMiniMuonNtupleMiniAOD::fillBeamSpot(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
    if (ran_BS_) return;
    ran_BS_ = true;

    reco::BeamSpot beamSpot;

    edm::Handle<reco::BeamSpot> beamSpotHandle;
    iEvent.getByToken(beamSpotToken_, beamSpotHandle);

    if (beamSpotHandle.isValid()) beamSpot = *beamSpotHandle;
    else edm::LogInfo("MyAnalyzer") << "No beam spot available from EventSetup \n";

    beamSpotX = beamSpot.x0();
    beamSpotY = beamSpot.y0();
    beamSpotZ = beamSpot.z0();

    math::XYZPoint point(beamSpotX, beamSpotY, beamSpotZ);
    beamSpotPoint_ = point;
}


//////////////////////////////////////////////////////////////////////////////////////////////
void MakeMiniMuonNtupleMiniAOD::fillMuons(const edm::Event& iEvent, const edm::EventSetup& iSetup, edm::EDGetTokenT<pat::MuonCollection> muIn_, const std::string& ID) {

    if (debugMode_) std::cout << "fillMuons" << std::endl;

    // ran_muonloop_ = true;
    edm::Handle<pat::MuonCollection> muonHandle;
    iEvent.getByToken(muIn_, muonHandle);
    const pat::MuonCollection& muons {*muonHandle};

    // Primary vertex
    edm::Handle<reco::VertexCollection> pvHandle;
    iEvent.getByToken(pvLabel_, pvHandle);


    //   !!!
    // IMPORTANT: DO NOT CUT ON THE OBJECTS BEFORE THEY ARE SORTED, cuts should
    // be applied in the second loop!!!
    //   !!!

    // muons
    muonEts.clear();
    for (const auto& muon : muons) {
        double et{muon.et()}; // should already be corrected
        muonEts.emplace_back(et);
    }

    if (muonEts.size() == 0) { // prevents a crash, the IndexSorter does not know what to do with zero-size vectors
        return;
    }
    std::vector<size_t> etMuonSorted{IndexSorter<std::vector<float>>(muonEts, true)()};

    numMuo[ID] = 0;

    // muons:
    for (size_t imuo{0}; imuo < etMuonSorted.size() && numMuo[ID] < numeric_cast<int>(NMUONSMAX); ++imuo) {
        size_t jmu{etMuonSorted[imuo]};
        const pat::Muon& muo{muons[jmu]};

        if (debugMode_) std::cout << "numMuo[" << ID << "]: " << numMuo[ID] << std::endl;

        numMuo[ID]++;

        muonSortedE[ID][numMuo[ID] - 1] = muo.energy();
        muonSortedEt[ID][numMuo[ID] - 1] = muo.et();
        muonSortedPt[ID][numMuo[ID] - 1] = muo.pt();
        muonSortedEta[ID][numMuo[ID] - 1] = muo.eta();
        muonSortedTheta[ID][numMuo[ID] - 1] = muo.theta();
        muonSortedPhi[ID][numMuo[ID] - 1] = muo.phi();
        muonSortedPx[ID][numMuo[ID] - 1] = muo.px();
        muonSortedPy[ID][numMuo[ID] - 1] = muo.py();
        muonSortedPz[ID][numMuo[ID] - 1] = muo.pz();
        muonSortedCharge[ID][numMuo[ID] - 1] = muo.charge();

        muonSortedLooseCutId[ID][numMuo[ID] - 1] = muo.passed(reco::Muon::CutBasedIdLoose);
        muonSortedMediumCutId[ID][numMuo[ID] - 1] = muo.passed(reco::Muon::CutBasedIdMedium);
        muonSortedTightCutId[ID][numMuo[ID] - 1] = muo.passed(reco::Muon::CutBasedIdTight);

        muonSortedGlobalID[ID][numMuo[ID] - 1] = muo.isGlobalMuon();
        muonSortedTrackID[ID][numMuo[ID] - 1] = muo.isTrackerMuon();

        if (muo.isTrackerMuon() || muo.isGlobalMuon()) { // required to be a global or tracker muon - i.e. has inner tracker info
            muonValidFraction[ID][numMuo[ID] - 1] = muo.innerTrack()->validFraction();
            muonChi2LocalPosition[ID][numMuo[ID] - 1] = muo.combinedQuality().chi2LocalPosition;
            muonTrkKick[ID][numMuo[ID] - 1] = muo.combinedQuality().trkKink;
            muonSegmentCompatibility[ID][numMuo[ID] - 1] = muon::segmentCompatibility(muo);

            muonSortedDBBeamSpotCorrectedTrackD0[ID][numMuo[ID] - 1] = muo.dB();
            muonSortedTrackNHits[ID][numMuo[ID] - 1] = muo.track()->numberOfValidHits(); // number of valid hits in Tracker - same as muo.bestTrack()->hitPattern().numberOfValidHits()
            muonSortedDBInnerTrackD0[ID][numMuo[ID] - 1] = -1. * (muo.innerTrack()->dxy(beamSpotPoint_));
            muonSortedVldPixHits[ID][numMuo[ID] - 1] = muo.innerTrack()->hitPattern().numberOfValidPixelHits(); // muo.bestTrack()->hitPattern().numberOfValidPixelHits()

            // Save vertex information.
            muonSortedVertX[ID][numMuo[ID] - 1] = muo.vertex().X();
            muonSortedVertY[ID][numMuo[ID] - 1] = muo.vertex().Y();
            muonSortedVertZ[ID][numMuo[ID] - 1] = muo.vertex().Z();

            // Save track infomation
            muonSortedInnerTkPt[ID][numMuo[ID] - 1] = muo.bestTrack()->pt();
            muonSortedInnerTkPx[ID][numMuo[ID] - 1] = muo.bestTrack()->px();
            muonSortedInnerTkPy[ID][numMuo[ID] - 1] = muo.bestTrack()->py();
            muonSortedInnerTkPz[ID][numMuo[ID] - 1] = muo.bestTrack()->pz();
            muonSortedInnerTkEta[ID][numMuo[ID] - 1] = muo.bestTrack()->eta();
            muonSortedInnerTkPhi[ID][numMuo[ID] - 1] = muo.bestTrack()->phi();

            muonSortedTkLysWithMeasurements[ID][numMuo[ID] - 1] = muo.track()->hitPattern().trackerLayersWithMeasurement();
            muonSortedInnerTkNormChi2[ID][numMuo[ID] - 1] = muo.bestTrack()->normalizedChi2();
            muonSortedDBPV[ID][numMuo[ID] - 1] = muo.muonBestTrack()->dxy(vertexPoint_);
            muonSortedDBPVError[ID][numMuo[ID] - 1] = muo.muonBestTrack()->dxyError();
            muonSortedDZPV[ID][numMuo[ID] - 1] = muo.muonBestTrack()->dz(vertexPoint_);
            muonSortedDZPVError[ID][numMuo[ID] - 1] = muo.muonBestTrack()->dzError();
            muonSortedMatchedStations[ID][numMuo[ID] - 1] = muo.numberOfMatchedStations();
        }

        //----------------------------------------------------------------------------
        if (muo.isTrackerMuon() && muo.isGlobalMuon()) {
            muonSortedChi2[ID][numMuo[ID] - 1] = muo.combinedMuon()->chi2(); // chi2 of the combined muon
            //----------------------------------------------------------------------------
            muonSortedD0[ID][numMuo[ID] - 1] = muo.combinedMuon()->d0(); // impact parameter
            muonSortedBeamSpotCorrectedD0[ID][numMuo[ID] - 1] = -1. * (muo.combinedMuon()->dxy(beamSpotPoint_));
            muonSortedNDOF[ID][numMuo[ID] - 1] = muo.combinedMuon()->ndof(); // n_d.o.f
            muonSortedValidHitsGlobal[ID][numMuo[ID] - 1] = muo.globalTrack()->hitPattern().numberOfValidMuonHits();

            // Just some extra stuff.
            muonSortedGlbTkNormChi2[ID][numMuo[ID] - 1] = muo.globalTrack()->normalizedChi2();
        }

        // Impact param significance
        if ( pvHandle.isValid() && (muo.isTrackerMuon() || muo.isGlobalMuon()) ) {
            std::vector<reco::Vertex> pv{*pvHandle};

            edm::ESHandle<TransientTrackBuilder> trackBuilder;
            iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder", trackBuilder);
            reco::TransientTrack muTransient{trackBuilder->build( muo.bestTrack() )};

            std::pair<bool, Measurement1D> muImpactTrans{IPTools::absoluteTransverseImpactParameter(muTransient, pv[0])};
            std::pair<bool, Measurement1D> muImpact3D{IPTools::absoluteImpactParameter3D(muTransient, pv[0])};

            if (muImpactTrans.first) {
                muonSortedImpactTransDist[ID][numMuo[ID] - 1] = muImpactTrans.second.value();
                muonSortedImpactTransError[ID][numMuo[ID] - 1] = muImpactTrans.second.error();
                muonSortedImpactTransSignificance[ID][numMuo[ID] - 1] = muImpactTrans.second.significance();
            }
            if (muImpact3D.first) {
                muonSortedImpact3DDist[ID][numMuo[ID] - 1] = muImpact3D.second.value();
                muonSortedImpact3DError[ID][numMuo[ID] - 1] = muImpact3D.second.error();
                muonSortedImpact3DSignificance[ID][numMuo[ID] - 1] = muImpact3D.second.significance();
            }
        }


        //----------------------------------------------------------------------------
        // std::cout << "Gets to the filling bit which says track in it";
        // muonSortedTrackNHits[ID][numMuo[ID] - 1] =
        //     muo.track()->numberOfValidHits(); // number of valid hits in
        // Tracker std::cout << " and fills that bit" << std::endl;
        // muonSortedTrackNHits[ID][numMuo[ID] - 1] =
        //     muo.innerTrack()->numberOfValidHits();
        //----------------------------------------------------------------------------

        muonSortedChargedHadronIso[ID][numMuo[ID] - 1] = muo.chargedHadronIso();
        muonSortedNeutralHadronIso[ID][numMuo[ID] - 1] = muo.neutralHadronIso();
        muonSortedPhotonIso[ID][numMuo[ID] - 1] = muo.photonIso();

        muonSortedTrackIso[ID][numMuo[ID] - 1] = muo.isolationR03().sumPt; // muo.trackIso();
        muonSortedECalIso[ID][numMuo[ID] - 1] = muo.isolationR03().emEt; // muo.ecalIso();
        muonSortedHCalIso[ID][numMuo[ID] - 1] = muo.isolationR03().hadEt; // muo.hcalIso();

        // manually calculating comreliso - ie. muonSortedComRelIsodBeta is with
        // DeltaBeta correction:
        muonSortedComRelIso[ID][numMuo[ID] - 1] =  muonSortedTrackIso[ID][numMuo[ID] - 1];
        muonSortedComRelIso[ID][numMuo[ID] - 1] += muonSortedECalIso[ID][numMuo[ID] - 1];
        muonSortedComRelIso[ID][numMuo[ID] - 1] += muonSortedHCalIso[ID][numMuo[ID] - 1];
        // Old method of rel iso with beta correction
        // muonSortedComRelIsodBeta[ID][numMuo[ID] - 1] = (muo.chargedHadronIso() + std::max(0.0, muo.neutralHadronIso() + muo.photonIso() - 0.5 * muo.puChargedHadronIso())) / muo.pt();
        // New Method
        muonSortedComRelIsodBeta[ID][numMuo[ID] - 1] = (muo.pfIsolationR04().sumChargedHadronPt + std::max(0.0, muo.pfIsolationR04().sumNeutralHadronEt + muo.pfIsolationR04().sumPhotonEt - 0.5 * muo.pfIsolationR04().sumPUPt)) / muo.pt();
        muonSortedChHadIso[ID][numMuo[ID] - 1] = muo.pfIsolationR04().sumChargedHadronPt;
        muonSortedNtHadIso[ID][numMuo[ID] - 1] = muo.pfIsolationR04().sumNeutralHadronEt;
        muonSortedGammaIso[ID][numMuo[ID] - 1] = muo.pfIsolationR04().sumPhotonEt;
        muonSortedPuIso[ID][numMuo[ID] - 1] = muo.pfIsolationR04().sumPUPt;

        muonSortedComRelIso[ID][numMuo[ID] - 1] /= muonSortedPt[ID][numMuo[ID] - 1];
        muonSortedNumChambers[ID][numMuo[ID] - 1] = muo.numberOfChambers();
        muonSortedNumMatches[ID][numMuo[ID] - 1] = muo.numberOfMatches();
        muonSortedIsPFMuon[ID][numMuo[ID] - 1] = muo.isPFMuon();

        // Gen muon stuff

        // if (muo.genParticleRef().ref().isValid())
        if (!muo.genParticleRef().isNull()) {
            genMuonSortedPt[ID][numMuo[ID] - 1] = muo.genLepton()->pt();
            genMuonSortedEt[ID][numMuo[ID] - 1] = muo.genLepton()->et();
            genMuonSortedEta[ID][numMuo[ID] - 1] = muo.genLepton()->eta();
            genMuonSortedTheta[ID][numMuo[ID] - 1] = muo.genLepton()->theta();
            genMuonSortedPhi[ID][numMuo[ID] - 1] = muo.genLepton()->phi();
            genMuonSortedPx[ID][numMuo[ID] - 1] = muo.genLepton()->px();
            genMuonSortedPy[ID][numMuo[ID] - 1] = muo.genLepton()->py();
            genMuonSortedPz[ID][numMuo[ID] - 1] = muo.genLepton()->pz();
            genMuonSortedCharge[ID][numMuo[ID] - 1] = muo.genLepton()->charge();
            genMuonSortedPdgId[ID][numMuo[ID] - 1] = muo.genLepton()->pdgId();
            genMuonSortedMotherId[ID][numMuo[ID] - 1] = muo.genLepton()->mother()->pdgId();
            genMuonSortedPromptDecayed[ID][numMuo[ID] - 1] = muo.genLepton()->isPromptDecayed();
            genMuonSortedPromptFinalState[ID][numMuo[ID] - 1] = muo.genLepton()->isPromptFinalState();
            genMuonSortedHardProcess[ID][numMuo[ID] - 1] = muo.genLepton()->isHardProcess();
            genMuonSortedPythiaSixStatusThree[ID][numMuo[ID] - 1] = muo.genLepton()->fromHardProcessBeforeFSR(); 

        } // End gen muon loop

    }

}

//////////////////////////////////////////////////////////////////////////////////////////////

void MakeMiniMuonNtupleMiniAOD::fillMCInfo(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

    if (!runMCInfo_) return;
    if (ran_mcloop_) return;

    ran_mcloop_ = true;
    bool found_b{false};
    int W_hadronic{0};
    int W_leptonic{0};

    // Get the top gen events for top pt reweighting - so I guess this is
    // irrelevant.

    edm::Handle<LHEEventProduct> EventHandle;
    edm::Handle<GenEventInfoProduct> genEventInfo;

    if (isMCatNLO_) iEvent.getByToken(pdfInfoToken_, genEventInfo);
    else iEvent.getByToken(generatorToken_, genEventInfo);

    if (isLHEflag_) {
        iEvent.getByToken(externalLHEToken_, EventHandle);

        origWeightForNorm_ = EventHandle->originalXWGTUP();

        // Weights must be rescaled
        // https://twiki.cern.ch/twiki/bin/viewauth/CMS/LHEReaderCMSSW
        auto rescale_weight = [&](const double w) {
            return w * genEventInfo->weight() / origWeightForNorm_;
        };

        weight_muF0p5_ = rescale_weight(EventHandle->weights()[6].wgt); // muF = 0.5 | muR = 1
        weight_muF2_ = rescale_weight(EventHandle->weights()[3].wgt); // muF = 2 | muR = 1
        weight_muR0p5_ = rescale_weight(EventHandle->weights()[2].wgt); // muF = 1 | muR = 0.5
        weight_muR2_ = rescale_weight(EventHandle->weights()[1].wgt); // muF = 1 | muR = 2
        weight_muF0p5muR0p5_ = rescale_weight(EventHandle->weights()[8].wgt); // muF = 0.5 | muR = 0.5
        weight_muF2muR2_ = rescale_weight(EventHandle->weights()[4].wgt); // muF = 2 | muR = 2

        int initialIndex{pdfIdStart_};
        int finalIndex{pdfIdEnd_ + 1};
        int N{finalIndex - initialIndex};
        double pdfSum{0.0};
        double pdfSum2{0.0};

        for (int i{initialIndex}; i != finalIndex; i++) {
            for (unsigned int w{0}; w != EventHandle->weights().size(); ++w) {
                if (EventHandle->weights()[w].id == std::to_string(i)) {
                    pdfSum += rescale_weight(EventHandle->weights()[w].wgt);
                }
            }
        }

        double meanObs{(pdfSum) / (double(N))};
        for (int i{initialIndex}; i != finalIndex; i++) {
            for (unsigned int w{0}; w != EventHandle->weights().size(); ++w) {
                if (EventHandle->weights()[w].id == std::to_string(i)) {
                    pdfSum2 += (rescale_weight(EventHandle->weights()[w].wgt) - meanObs)
                               * (rescale_weight(EventHandle->weights()[w].wgt) - meanObs);
                }
            }
        }

        double sd{std::sqrt(pdfSum2 / (finalIndex - initialIndex - 1))};
        weight_pdfMax_ = (EventHandle->originalXWGTUP() + sd)
                         / EventHandle->originalXWGTUP();
        weight_pdfMin_ = (EventHandle->originalXWGTUP() - sd)
                         / EventHandle->originalXWGTUP();

        // Debug couts
        // std::cout << "N: " << N << std::endl;
        // std::cout << "pdfSum: " << pdfSum << std::endl;
        // std::cout << "meanObs: " << meanObs << std::endl;
        // std::cout << "evt weight: " << EventHandle->originalXWGTUP()
        //           << std::endl;
        // std::cout << "pdfSum2: " << pdfSum2 << std::endl;
        // std::cout << std::setprecision(10) << std::fixed;
        // std::cout << "sd: " << sd << std::endl;
        //
        // std::cout << (EventHandle->originalXWGTUP() + sd)
        //                  / EventHandle->originalXWGTUP()
        //           << std::endl;
        // std::cout << (EventHandle->originalXWGTUP() - sd)
        //                  / EventHandle->originalXWGTUP()
        //           << std::endl;

        if (hasAlphaWeightFlag_)
        {
            double alphaMax{1.0};
            double alphaMin{1.0};
            for (unsigned int w{0}; w != EventHandle->weights().size(); ++w)
            {
                if (EventHandle->weights()[w].id == alphaIdStart_)
                {
                    alphaMax = rescale_weight(EventHandle->weights()[w].wgt)
                               / EventHandle->originalXWGTUP();
                }
                if (EventHandle->weights()[w].id == alphaIdEnd_)
                {
                    alphaMin = rescale_weight(EventHandle->weights()[w].wgt)
                               / EventHandle->originalXWGTUP();
                }
            }
            weight_alphaMax_ = alphaMax;
            weight_alphaMin_ = alphaMin;
            weight_alphaMax_ = alphaMin;
            weight_alphaMin_ = alphaMax;
        }
        else
        {
            weight_alphaMax_ = 1.0;
            weight_alphaMin_ = 1.0;
        }
    }

    else {
        weight_muF0p5_ = -999.0;
        weight_muF2_ = -999.0;
        weight_muR0p5_ = -999.0;
        weight_muR2_ = -999.0;
        weight_muF0p5muR0p5_ = -999.0;
        weight_muF2muR2_ = -999.0;
        origWeightForNorm_ = 0.0;
        weight_pdfMax_ = 1.0;
        weight_pdfMin_ = 1.0;
        weight_alphaMax_ = 1.0;
        weight_alphaMin_ = 1.0;
    }

    if (!is2016_)  {
        // Perform the recommended rescaling
        // The TWiki says:
        // https://twiki.cern.ch/twiki/bin/viewauth/CMS/LHEReaderCMSSW#Retrieving_the_weights
        // final_weight = nominal_weight * systematic_weight / original_weight
        // but we want to turn these into an easy to use SF
        // sf = final_weight / original_weight
        //    = nominal_weight * systematic_weight / (original_weight ^ 2)
        auto weight_sf = [&](const double w) { 
            return w * genEventInfo->weight() / std::pow(EventHandle->originalXWGTUP(), 2);
        };

        if ( !skipIsrFsrWeights_ ) {
            for (size_t i{2}; i < genEventInfo->weights().size(); ++i) {
                switch (i) {
                    case 2:
                        isrRedHi = weight_sf(genEventInfo->weights()[i]);
                        break;
                    case 3:
                        fsrRedHi = weight_sf(genEventInfo->weights()[i]);
                        break;
                    case 4:
                        isrRedLo = weight_sf(genEventInfo->weights()[i]);
                        break;
                    case 5:
                        fsrRedLo = weight_sf(genEventInfo->weights()[i]);
                        break;
                    case 6:
                        isrDefHi = weight_sf(genEventInfo->weights()[i]);
                        break;
                    case 7:
                        fsrDefHi = weight_sf(genEventInfo->weights()[i]);
                        break;
                    case 8:
                        isrDefLo = weight_sf(genEventInfo->weights()[i]);
                        break;
                    case 9:
                        fsrDefLo = weight_sf(genEventInfo->weights()[i]);
                        break;
                    case 10:
                        isrConHi = weight_sf(genEventInfo->weights()[i]);
                        break;
                    case 11:
                        fsrConHi = weight_sf(genEventInfo->weights()[i]);
                        break;
                    case 12:
                        isrConLo = weight_sf(genEventInfo->weights()[i]);
                        break;
                    case 13:
                        fsrConLo = weight_sf(genEventInfo->weights()[i]);
                        break;
                    default: break;
                }
            }
        }
    }

    processPtHat_ = genEventInfo->qScale();
    weight_ = genEventInfo->weight();
    processId_ = genEventInfo->signalProcessID();
    edm::Handle<reco::GenParticleCollection> genParticles;
    iEvent.getByToken(genSimParticlesToken_, genParticles);

    if (!genParticles.isValid())
    {
        iEvent.getByToken(genParticlesToken_, genParticles);
    }

    if (isttbar_){
        double topPt{0.};
        double tBarPt{0.};
        for (size_t k{0}; k < genParticles->size(); k++) {
            const reco::Candidate& TCand{(*genParticles)[k]};
            if (TCand.pdgId() == 6)  topPt = TCand.pt();
            if (TCand.pdgId() == -6) tBarPt = TCand.pt();
        }
        // std::cout << topPt << " " << tBarPt << " "
        //           << sqrt(exp(0.0615 - 0.0005 * topPt)
        //                   * exp(0.0615 - 0.0005 * tBarPt))
        //           << std::endl;
        topPtReweight = sqrt(exp(0.0615 - 0.0005 * topPt) * exp(0.0615 - 0.0005 * tBarPt));
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
//        if (std::abs(it->pdgId()) <= 18 || std::abs(it->pdgId()) == 24 || std::abs(it->pdgId()) == 23) {
            // only do this for particles with reasonable pT:
            if (nGenPar < NGENPARMAX) {
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

		if ( it->bestTrack() != nullptr) std::cout << "test: " << it->bestTrack()->vx() << std::endl;

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
        //}
        //    }
        //if (std::abs(it->pdgId()) == 5 || std::abs(it->pdgId()) == 4)  {
            // for (int ijet = 0; ijet < numJet; ijet++)
            // {
            //     float deltaR = reco::deltaR(jetSortedEta[ijet],
            //                                 jetSortedPhi[ijet],
            //                                 it->eta(),
            //                                 it->phi());
            //     if (std::abs(it->pdgId()) == 5
            //         && (deltaR < genJetSortedClosestB[ijet]
            //             || genJetSortedClosestB[ijet] < 0))
            //     {
            //         genJetSortedClosestB[ijet] = deltaR;
            //     }
            //     else if (std::abs(it->pdgId()) == 4
            //              && (deltaR < genJetSortedClosestC[ijet]
            //                  || genJetSortedClosestC[ijet] < 0))
            //     {
            //         genJetSortedClosestC[ijet] = deltaR;
            //     }
            // }
        //}
        if (it->status() == 3 && std::abs(it->pdgId()) == 6) { // find t or tbar among the genParticles
            if (nT >= NTOPMCINFOSMAX)  continue;

            if (it->numberOfDaughters() >= 2) { // check t or tbar has at least 2 daughters
                // std::cout << "The t or tbar candidate has: "
                //           << it->numberOfDaughters() << " daughters"
                //           << std::endl;

                for (size_t i_Tdaughter{0}; i_Tdaughter < it->numberOfDaughters(); i_Tdaughter++) { // loop over t or tbar daughters
                    const reco::Candidate& TDaughter{*it->daughter(i_Tdaughter)};

                    if (TDaughter.status() == 3 && std::abs(TDaughter.pdgId()) == 5) { // find b
                        // std::cout << "we found b" << std::endl;
                        found_b = true;

                        if (nb >= NTOPMCINFOSMAX)continue;

                        // bMCTruthE[nb] = TDaughter.energy();
                        bMCTruthEt[nb] = TDaughter.et();
                        bMCTruthPx[nb] = TDaughter.px();
                        bMCTruthPy[nb] = TDaughter.py();
                        bMCTruthPz[nb] = TDaughter.pz();

                        nb++;
                    }
                    W_leptonic = W_hadronic = 0;
                    if (TDaughter.status() == 3 && std::abs(TDaughter.pdgId()) == 24) { // find W
                        if (TDaughter.numberOfDaughters() >= 2) { // check W has at least 2 daughters
                            for (size_t i_Wdaughter{0}; i_Wdaughter < TDaughter.numberOfDaughters(); i_Wdaughter++) {
                                const reco::Candidate& WDaughter{*TDaughter.daughter(i_Wdaughter)};
                                if (WDaughter.status() == 3 && std::abs(WDaughter.pdgId()) <= 6 && std::abs(WDaughter.pdgId()) > 0) { // W decays in hadronic mode
                                    if (std::abs(WDaughter.pdgId()) > std::abs(W_hadronic)) W_hadronic = WDaughter.pdgId();
                                }
                                if (WDaughter.status() == 3 && std::abs(WDaughter.pdgId()) > 10 && std::abs(WDaughter.pdgId()) < 17 && std::abs(WDaughter.pdgId()) % 2 == 1) {
                                                 // W decays in leptonic mode,
                                                 // ele=11, mu=13, tau=15,
                                                 // nuele=12, numu=14, nutau=16
                                    W_leptonic = WDaughter.pdgId();
                                }
                            }
                        }
                    }

                    if (W_hadronic != 0) {
                        if (nWhadronic >= NTOPMCINFOSMAX) continue;
                        W_hadronicMCTruthE[nWhadronic] = TDaughter.energy();
                        // std::cout << "The W hadronic decay energy is: "
                        //           << TDaughter.energy() << std::endl;
                        W_hadronicMCTruthEt[nWhadronic] = TDaughter.et();
                        W_hadronicMCTruthPx[nWhadronic] = TDaughter.px();
                        W_hadronicMCTruthPy[nWhadronic] = TDaughter.py();
                        W_hadronicMCTruthPz[nWhadronic] = TDaughter.pz();
                        W_hadronicMCTruthPID[nWhadronic] = W_hadronic;
                        W_hadronicMCTruthMother[nWhadronic] = nT;
                        nWhadronic++;
                    }

                    else if (W_leptonic != 0) {
                        if (nWleptonic >= NTOPMCINFOSMAX) continue;

                        W_leptonicMCTruthE[nWleptonic] = TDaughter.energy();
                        // std::cout << "The W leptonic decay energy is: "
                        //           << TDaughter.energy() << std::endl;
                        W_leptonicMCTruthEt[nWleptonic] = TDaughter.et();
                        W_leptonicMCTruthPx[nWleptonic] = TDaughter.px();
                        W_leptonicMCTruthPy[nWleptonic] = TDaughter.py();
                        W_leptonicMCTruthPz[nWleptonic] = TDaughter.pz();
                        W_leptonicMCTruthPID[nWleptonic] = W_leptonic;
                        W_leptonicMCTruthMother[nWleptonic] = nT;
                        nWleptonic++;
                    }

                    if (found_b && W_hadronic != 0) { // now we can keep the top in hadronic decay 4-vector
                        if (nThadronic >= NTOPMCINFOSMAX) continue;

                        T_hadronicMCTruthE[nThadronic] = it->energy();
                        // std::cout
                        //     << "The initial top (hadronic decay) energy is"
                        //        "then: "
                        //     << it->energy() << std::endl;
                        T_hadronicMCTruthEt[nThadronic] = it->et();
                        T_hadronicMCTruthPx[nThadronic] = it->px();
                        T_hadronicMCTruthPy[nThadronic] = it->py();
                        T_hadronicMCTruthPz[nThadronic] = it->pz();
                        T_hadronicMotherIndex[nThadronic] = nT;
                        nThadronic++;
                        // std::cout << "test1: " << nThadronic << std::endl;
                    }

                    if (found_b && W_leptonic != 0) { // now we can keep the top in leptonic decay 4-vector
                        if (nTleptonic >= NTOPMCINFOSMAX) continue;

                        T_leptonicMCTruthE[nTleptonic] = it->energy();
                        // std::cout << "The initial top (leptonic decay) energy
                        // "
                        //              "is then: "
                        //           << it->energy() << std::endl;
                        T_leptonicMCTruthEt[nTleptonic] = it->et();
                        T_leptonicMCTruthPx[nTleptonic] = it->px();
                        T_leptonicMCTruthPy[nTleptonic] = it->py();
                        T_leptonicMCTruthPz[nTleptonic] = it->pz();
                        T_leptonicMotherIndex[nTleptonic] = nT;
                        nTleptonic++;
                        // std::cout << "test2: " << nTleptonic << std::endl;
                    }
                }
            }
            nT++;
        }
    }
    // now check if electron+jets:
    isElePlusJets = 0;
    if (nWleptonic == 1 && std::abs(W_leptonicMCTruthPID[0]) == 11) isElePlusJets = 1;

    // PDF info for reweighting!
    // See AN2009/048 for full recipe and description!
    const gen::PdfInfo* pdfInfo{genEventInfo->pdf()};

    if (pdfInfo != nullptr) {
        genPDFScale = pdfInfo->scalePDF;
        genPDFx1 = pdfInfo->x.first;
        genPDFx2 = pdfInfo->x.second;
        genPDFf1 = pdfInfo->id.first;
        genPDFf2 = pdfInfo->id.second;
    }

    if (runPDFUncertainties_) {
        // CTEQ 6.6 General
        float best_fit{1.0};
        // loop over all (error) pdfs
        // subpdf is the index in the pdf set, 0 = best fit, 1-40 = error pdfs
        // up and down.
        // for (int subpdf = 0; subpdf < LHADPDF::numberPDF(0); subpdf++)
        for (int subpdf{0}; subpdf < 44; subpdf++) {
            LHAPDF::usePDFMember(0, subpdf);
            if (subpdf == 0) {
                best_fit = LHAPDF::xfx(pdfInfo->x.first, pdfInfo->scalePDF, pdfInfo->id.first)
                           * LHAPDF::xfx(pdfInfo->x.second, pdfInfo->scalePDF, pdfInfo->id.second);
                genCTEQ66_Weight[subpdf] = best_fit;
            }
            else {
                genCTEQ66_Weight[subpdf] = (LHAPDF::xfx(pdfInfo->x.first, pdfInfo->scalePDF, pdfInfo->id.first)
                     * LHAPDF::xfx(pdfInfo->x.second, pdfInfo->scalePDF, pdfInfo->id.second)
                     / best_fit);
            }
        }
        // MRST 2006 NLO
        best_fit = 1.0;
        // loop over all (error) pdfs
        // subpdf is the index in the pdf set, 0 = best fit, 1-40 = error pdfs
        // up and down.
        // for (int subpdf = 0; subpdf < LHADPDF::numberPDF(0); subpdf++)
        for (int subpdf{0}; subpdf < 31; subpdf++) {
            LHAPDF::usePDFMember(1, subpdf);
            if (subpdf == 0) {
                best_fit = LHAPDF::xfx(pdfInfo->x.first, pdfInfo->scalePDF, pdfInfo->id.first)
                           * LHAPDF::xfx(pdfInfo->x.second, pdfInfo->scalePDF, pdfInfo->id.second);
                genMRST2006nnlo_Weight[subpdf] = best_fit;
            }
            else {
                genMRST2006nnlo_Weight[subpdf] = (LHAPDF::xfx(pdfInfo->x.first, pdfInfo->scalePDF, pdfInfo->id.first)
                     * LHAPDF::xfx(pdfInfo->x.second, pdfInfo->scalePDF, pdfInfo->id.second)
                     / best_fit);
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////

void MakeMiniMuonNtupleMiniAOD::clearmuonarrays(const std::string& ID){
    // std::cout << "clearmuonarrays CHECK" << std::endl;
    numMuo[ID] = 0;
    muonEts.clear(); // just used for sorting

    muonSortedE[ID].clear();
    muonSortedEt[ID].clear();
    muonSortedPt[ID].clear();
    muonSortedEta[ID].clear();
    muonSortedTheta[ID].clear();
    muonSortedPhi[ID].clear();
    muonSortedPx[ID].clear();
    muonSortedPy[ID].clear();
    muonSortedPz[ID].clear();
    muonSortedCharge[ID].clear();

    muonSortedLooseCutId[ID].clear();
    muonSortedMediumCutId[ID].clear();
    muonSortedTightCutId[ID].clear();

    muonSortedGlobalID[ID].clear();
    muonSortedTrackID[ID].clear();

    muonValidFraction[ID].clear();
    muonChi2LocalPosition[ID].clear();
    muonTrkKick[ID].clear();
    muonSegmentCompatibility[ID].clear();

    muonSortedChi2[ID].clear();
    muonSortedD0[ID].clear();
    muonSortedDBBeamSpotCorrectedTrackD0[ID].clear();

    muonSortedDBInnerTrackD0[ID].clear();

    muonSortedBeamSpotCorrectedD0[ID].clear();
    muonSortedTrackNHits[ID].clear();
    muonSortedValidHitsGlobal[ID].clear();
    muonSortedNDOF[ID].clear(); // n_d.o.f

    muonSortedVertX[ID].clear();
    muonSortedVertY[ID].clear();
    muonSortedVertZ[ID].clear();

    muonSortedInnerTkPt[ID].clear();
    muonSortedInnerTkPx[ID].clear();
    muonSortedInnerTkPy[ID].clear();
    muonSortedInnerTkPz[ID].clear();
    muonSortedInnerTkEta[ID].clear();
    muonSortedInnerTkPhi[ID].clear();

    muonSortedTkLysWithMeasurements[ID].clear();
    muonSortedGlbTkNormChi2[ID].clear();
    muonSortedInnerTkNormChi2[ID].clear();
    muonSortedDBPV[ID].clear();
    muonSortedDBPVError[ID].clear();
    muonSortedDZPV[ID].clear();
    muonSortedDZPVError[ID].clear();
    muonSortedVldPixHits[ID].clear();
    muonSortedMatchedStations[ID].clear();

    muonSortedImpactTransDist[ID].clear();
    muonSortedImpactTransError[ID].clear();
    muonSortedImpactTransSignificance[ID].clear();
    muonSortedImpact3DDist[ID].clear();
    muonSortedImpact3DError[ID].clear();
    muonSortedImpact3DSignificance[ID].clear();

    muonSortedChargedHadronIso[ID].clear();
    muonSortedNeutralHadronIso[ID].clear();
    muonSortedPhotonIso[ID].clear();

    muonSortedTrackIso[ID].clear();
    muonSortedECalIso[ID].clear();
    muonSortedHCalIso[ID].clear();
    muonSortedComRelIso[ID].clear();
    muonSortedComRelIsodBeta[ID].clear();
    muonSortedChHadIso[ID].clear();
    muonSortedNtHadIso[ID].clear();
    muonSortedGammaIso[ID].clear();
    muonSortedPuIso[ID].clear();
    muonSortedIsPFMuon[ID].clear();

    muonSortedNumChambers[ID].clear();
    muonSortedNumMatches[ID].clear();

    genMuonSortedPt[ID].clear();
    genMuonSortedEt[ID].clear();
    genMuonSortedEta[ID].clear();
    genMuonSortedTheta[ID].clear();
    genMuonSortedPhi[ID].clear();
    genMuonSortedPx[ID].clear();
    genMuonSortedPy[ID].clear();
    genMuonSortedPz[ID].clear();
    genMuonSortedCharge[ID].clear();
    genMuonSortedPdgId[ID].clear();
    genMuonSortedMotherId[ID].clear();
    genMuonSortedPromptDecayed[ID].clear();
    genMuonSortedPromptFinalState[ID].clear();
    genMuonSortedHardProcess[ID].clear();
    genMuonSortedPythiaSixStatusThree[ID].clear();
}

/////////////////////////////////////
void MakeMiniMuonNtupleMiniAOD::clearMCarrays(){
    // electronTruthEts.clear(); // just used for sorting
    // std::cout << "clearMCarrays CHECK" << std::endl;
    nT = 0;
    nThadronic = 0;
    nTleptonic = 0;
    nb = 0;
    nWhadronic = 0;
    nWleptonic = 0;
    VQQBosonAbsId = -999;

    for (size_t i{0}; i < NTOPMCINFOSMAX; i++)
    {
        T_hadronicMCTruthE[i] = 0;
        T_hadronicMCTruthEt[i] = 0;
        T_hadronicMCTruthPx[i] = 0;
        T_hadronicMCTruthPy[i] = 0;
        T_hadronicMCTruthPz[i] = 0;
        T_hadronicMotherIndex[i] = -1;

        T_leptonicMCTruthE[i] = 0;
        T_leptonicMCTruthEt[i] = 0;
        T_leptonicMCTruthPx[i] = 0;
        T_leptonicMCTruthPy[i] = 0;
        T_leptonicMCTruthPz[i] = 0;
        T_leptonicMotherIndex[i] = -1;

        bMCTruthE[i] = 0;
        bMCTruthEt[i] = 0;
        bMCTruthPx[i] = 0;
        bMCTruthPy[i] = 0;
        bMCTruthPz[i] = 0;
        bMCTruthMother[i] = -1;

        W_hadronicMCTruthE[i] = 0;
        W_hadronicMCTruthEt[i] = 0;
        W_hadronicMCTruthPx[i] = 0;
        W_hadronicMCTruthPy[i] = 0;
        W_hadronicMCTruthPz[i] = 0;
        W_hadronicMCTruthPID[i] = 0;
        W_hadronicMCTruthMother[i] = -1;

        W_leptonicMCTruthE[i] = 0;
        W_leptonicMCTruthEt[i] = 0;
        W_leptonicMCTruthPx[i] = 0;
        W_leptonicMCTruthPy[i] = 0;
        W_leptonicMCTruthPz[i] = 0;
        W_leptonicMCTruthPID[i] = 0;
        W_leptonicMCTruthMother[i] = -1;

        // remainingEnergy[i] = 0;
    }
    // PDF Reweighting
    genPDFScale = -1;
    genPDFx1 = -1;
    genPDFx2 = -1;
    genPDFf1 = 9999;
    genPDFf2 = 9999;
    if (runPDFUncertainties_)
    {
        for (float& i : genCTEQ66_Weight)
        {
            i = -1;
        }
        for (float& i : genMRST2006nnlo_Weight)
        {
            i = -1;
        }
    }

    topPtReweight = 1.;
}

/////////////////////////////////////
void MakeMiniMuonNtupleMiniAOD::cleararrays() {
    // reset the bookkeeping bools;
    // std::cout << "cleararrays CHECK" << std::endl;
    // std::cout << "before FALSE: " << ran_postloop_ << std::endl;
    ran_muonloop_ = ran_mcloop_ = ran_PV_ = ran_postloop_ = false;
    // std::cout << "psot FALSE: " << ran_postloop_ << std::endl;

    for (size_t iTrig{0}; iTrig < triggerList_.size(); iTrig++) { 
        triggerRes[iTrig] = -99;
    }
    for (size_t iMetFilter{0}; iMetFilter < metFilterList_.size(); iMetFilter++) {
        metFilterRes[iMetFilter] = -99;
    }
//    Flag_ecalBadCalibReducedMINIAODFilter = -99; // Manually set rerun filter that's in its own object

    for (int& HLT_fakeTriggerValue : HLT_fakeTriggerValues) {
        HLT_fakeTriggerValue = -99;
    }
    for (size_t ii{0}; ii < 200; ii++)  {
        TriggerBits[ii] = -99;
    }

    clearmuonarrays("PF");
    clearMCarrays();

    mhtSignif = -1;
    mhtPx = -9999.;
    mhtPy = -9999.;
    mhtPhi = -9999.;
    mhtSumEt = -1;
    mhtPt = -1;

    topo_sphericity = -1;
    topo_aplanarity = -1;
    topo_ht = -1;
    topo_sqrts = -1;
    // and same but including the electron.
    topo_sphericitye = -1;
    topo_aplanaritye = -1;
    topo_hte = -1;
    topo_sqrtse = -1;
    flavorHistory = 999;

    // clear zcandidates;

    beamSpotX = beamSpotY = beamSpotZ = 0;
    math::XYZPoint point(beamSpotX, beamSpotY, beamSpotZ);
    beamSpotPoint_ = point;
    vertexPoint_ = point;
    vertexPrimary_ = 0;

    evtRun = 0;
    evtnum = 0;
    evtlumiblock = 0.;
}

// ------------ method called to for each event  ------------
void MakeMiniMuonNtupleMiniAOD::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
    using namespace edm;
    // std::cout << iEvent.id().run() << " " << iEvent.luminosityBlock() << " "
    //           << iEvent.id().event()
    //           << std::endl; // Run pile-up reweighting here
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

    histocontainer1D_["eventcount"]->Fill(0.0);

    // std::cout << "now in loop" << std::endl;
    // std::cout << "cleared arrays." << std::endl;

    cleararrays();

    fillEventInfo(iEvent, iSetup);
    fillTriggerData(iEvent);
    fillBeamSpot(iEvent, iSetup);
    fillMuons           (iEvent, iSetup, patMuonsToken_, "PF");
    fillMCInfo(iEvent, iSetup);
    fillSummaryVariables();

    mytree_->Fill(); // If not doing cuts, fill up EVERYTHING

    // fill debugging histograms.
    if ( isLHEflag_ ) {
        origWeightForNorm_    >= 0.0 ? histocontainer1I_["sumWeights"]->AddBinContent(1)   : histocontainer1I_["sumWeights"]->AddBinContent(2);
        weight_muF0p5_        >= 0.0 ? histocontainer1I_["sumWeights"]->AddBinContent(3)   : histocontainer1I_["sumWeights"]->AddBinContent(4);
        weight_muR0p5_        >= 0.0 ? histocontainer1I_["sumWeights"]->AddBinContent(5)   : histocontainer1I_["sumWeights"]->AddBinContent(6);
        weight_muF0p5muR0p5_  >= 0.0 ? histocontainer1I_["sumWeights"]->AddBinContent(7)   : histocontainer1I_["sumWeights"]->AddBinContent(8);
        weight_muF2_          >= 0.0 ? histocontainer1I_["sumWeights"]->AddBinContent(9)   : histocontainer1I_["sumWeights"]->AddBinContent(10);
        weight_muR2_          >= 0.0 ? histocontainer1I_["sumWeights"]->AddBinContent(11)  : histocontainer1I_["sumWeights"]->AddBinContent(12);
        weight_muF2muR2_      >= 0.0 ? histocontainer1I_["sumWeights"]->AddBinContent(13)  : histocontainer1I_["sumWeights"]->AddBinContent(14);
    }
    else {
        histocontainer1I_["sumWeights"]->AddBinContent(1);
        histocontainer1I_["sumWeights"]->AddBinContent(3);
        histocontainer1I_["sumWeights"]->AddBinContent(5);
        histocontainer1I_["sumWeights"]->AddBinContent(7);
        histocontainer1I_["sumWeights"]->AddBinContent(9);
        histocontainer1I_["sumWeights"]->AddBinContent(11);
        histocontainer1I_["sumWeights"]->AddBinContent(13);
    }
}

void MakeMiniMuonNtupleMiniAOD::bookBranches() {
    // std::cout << "bookBranches CHECK" << std::endl;
    TTree::SetMaxTreeSize(std::numeric_limits<Long64_t>::max());
    mytree_ = new TTree("tree", "tree");
    mytree_->SetAutoSave(-std::numeric_limits<Long64_t>::max());

    bookMuonBranches("PF", "PF2PAT");
    if (runMCInfo_) {
        bookMCBranches();
    }

    mytree_->Branch("processId", &processId_, "processId/I");
    mytree_->Branch("processPtHat", &processPtHat_, "processPtHat/F");
    mytree_->Branch("processMCWeight", &weight_, "processMCWeight/D");

    mytree_->Branch("beamSpotX", &beamSpotX, "beamSpotX/F");
    mytree_->Branch("beamSpotY", &beamSpotY, "beamSpotY/F");
    mytree_->Branch("beamSpotZ", &beamSpotZ, "beamSpotZ/F");

    mytree_->Branch("mhtPt", &mhtPt, "mhtPt/F");
    mytree_->Branch("mhtPy", &mhtPy, "mhtPy/F");
    mytree_->Branch("mhtPx", &mhtPx, "mhtPx/F");
    mytree_->Branch("mhtPhi", &mhtPhi, "mhtPhi/F");
    mytree_->Branch("mhtSumEt", &mhtSumEt, "mhtSumEt/F");
    mytree_->Branch("mhtSignif", &mhtSignif, "mhtSignif/F");

    mytree_->Branch("nTriggerBits", &nTriggerBits, "nTriggerBits/I");
    mytree_->Branch("TriggerBits", TriggerBits, "TriggerBits[nTriggerBits]/I");

    mytree_->Branch("numVert", &numVert, "numVert/I");

    mytree_->Branch("weight_muF0p5", &weight_muF0p5_, "weight_muF0p5/D");
    mytree_->Branch("weight_muF2", &weight_muF2_, "weight_muF2/D");
    mytree_->Branch("weight_muR0p5", &weight_muR0p5_, "weight_muR0p5/D");
    mytree_->Branch("weight_muR2", &weight_muR2_, "weight_muR2/D");
    mytree_->Branch("weight_muF0p5muR0p5", &weight_muF0p5muR0p5_, "weight_muF0p5muR0p5/D");
    mytree_->Branch("weight_muF2muR2", &weight_muF2muR2_, "weight_muF2muR2/D");
    mytree_->Branch("origWeightForNorm", &origWeightForNorm_, "origWeightForNorm/D");
    mytree_->Branch("weight_pdfMax", &weight_pdfMax_, "weight_pdfMax/D");
    mytree_->Branch("weight_pdfMin", &weight_pdfMin_, "weight_pdfMin/D");
    mytree_->Branch("weight_alphaMax", &weight_alphaMax_, "weight_alphaMax/D");
    mytree_->Branch("weight_alphaMin", &weight_alphaMin_, "weight_alphaMin/D");

    mytree_->Branch("isrRedHi", &isrRedHi, "isrRedHi/D");
    mytree_->Branch("fsrRedHi", &fsrRedHi, "fsrRedHi/D");
    mytree_->Branch("isrRedLo", &isrRedLo, "isrRedLo/D");
    mytree_->Branch("fsrRedLo", &fsrRedLo, "fsrRedLo/D");
    mytree_->Branch("isrDefHi", &isrDefHi, "isrDefHi/D");
    mytree_->Branch("fsrDefHi", &fsrDefHi, "fsrDefHi/D");
    mytree_->Branch("isrDefLo", &isrDefLo, "isrDefLo/D");
    mytree_->Branch("fsrDefLo", &fsrDefLo, "fsrDefLo/D");
    mytree_->Branch("isrConHi", &isrConHi, "isrConHi/D");
    mytree_->Branch("fsrConHi", &fsrConHi, "fsrConHi/D");
    mytree_->Branch("isrConLo", &isrConLo, "isrConLo/D");
    mytree_->Branch("fsrConLo", &fsrConLo, "fsrConLo/D");

    while (HLT_fakeTriggerValues.size() < fakeTrigLabelList_.size()) {
        HLT_fakeTriggerValues.emplace_back(-99);
    }
    for (size_t ii{0}; ii < fakeTrigLabelList_.size(); ii++) {
        TString name{"HLTFake_"};
        name += fakeTrigLabelList_[ii];
        name.ReplaceAll(" ", "");
        TString name2{name};
        name2 += "/I";
        std::cout << "making fake trigger branch " << name << std::endl;
        mytree_->Branch(name, &HLT_fakeTriggerValues[ii], name2);
    }

    // Dynamic trigger list
    // for (auto iTrig = triggerList_.begin(); iTrig != triggerList_.end();
    //      iTrig++)
    while (triggerRes.size() < triggerList_.size()) {
        triggerRes.emplace_back(-99);
    }
    while (metFilterRes.size() < metFilterList_.size()) { 
        metFilterRes.emplace_back(-99);
    }
    for (size_t iTrig{0}; iTrig < triggerList_.size(); iTrig++) {
//        std::cout << "Booking trigger branch: " << triggerList_[iTrig] << std::endl;
        mytree_->Branch(triggerList_[iTrig].c_str(), &triggerRes[iTrig], (triggerList_[iTrig] + "/I").c_str());
    }
    for (size_t iMetFilter{0}; iMetFilter < metFilterList_.size(); iMetFilter++) {
//        std::cout << "Booking MET filter branch: " << metFilterList_[iMetFilter] << std::endl;
        mytree_->Branch(metFilterList_[iMetFilter].c_str(), &metFilterRes[iMetFilter], (metFilterList_[iMetFilter] + "/I").c_str());
    }
//    mytree_->Branch("Flag_ecalBadCalibReducedMINIAODFilter", &Flag_ecalBadCalibReducedMINIAODFilter, "Flag_ecalBadCalibReducedMINIAODFilter/I");

    // generator level information
    //  mytree_->Branch("myProcess", &genMyProcId, "myProcess/I");
    if (runMCInfo_) {
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

    mytree_->Branch("eventRun", &evtRun, "eventRun/I");
    mytree_->Branch("eventNum", &evtnum, "eventNum/I");
    mytree_->Branch("eventLumiblock", &evtlumiblock, "eventLumiblock/F");
}

// book muon branches:
void MakeMiniMuonNtupleMiniAOD::bookMuonBranches(const std::string& ID, const std::string& name) {

    // Initialise maps to prevent root panicing.
    std::vector<float> tempVecF(NMUONSMAX);
    std::vector<int> tempVecI(NMUONSMAX);

    muonSortedE[ID] = tempVecF;
    muonSortedEt[ID] = tempVecF;
    muonSortedPt[ID] = tempVecF;
    muonSortedEta[ID] = tempVecF;
    muonSortedTheta[ID] = tempVecF;
    muonSortedPhi[ID] = tempVecF;
    muonSortedPx[ID] = tempVecF;
    muonSortedPy[ID] = tempVecF;
    muonSortedPz[ID] = tempVecF;
    muonSortedCharge[ID] = tempVecI;
    muonSortedLooseCutId[ID] = tempVecI;
    muonSortedMediumCutId[ID] = tempVecI;
    muonSortedTightCutId[ID] = tempVecI;
    muonSortedPfIsoVeryLoose[ID] = tempVecI;
    muonSortedPfIsoLoose[ID] = tempVecI;
    muonSortedPfIsoMedium[ID] = tempVecI;
    muonSortedPfIsoTight[ID] = tempVecI;
    muonSortedPfIsoVeryTight[ID] = tempVecI;
    muonSortedTkIsoLoose[ID] = tempVecI;
    muonSortedTkIsoTight[ID] = tempVecI;
    muonSortedMvaLoose[ID] = tempVecI;
    muonSortedMvaMedium[ID] = tempVecI;
    muonSortedMvaTight[ID] = tempVecI;

    muonSortedGlobalID[ID] = tempVecF;
    muonSortedTrackID[ID] = tempVecF;

    muonValidFraction[ID] = tempVecF;
    muonChi2LocalPosition[ID] = tempVecF;
    muonTrkKick[ID] = tempVecF;
    muonSegmentCompatibility[ID] = tempVecF;

    muonSortedChi2[ID] = tempVecF;
    muonSortedD0[ID] = tempVecF;
    muonSortedDBBeamSpotCorrectedTrackD0[ID] = tempVecF;

    muonSortedDBInnerTrackD0[ID] = tempVecF;

    muonSortedBeamSpotCorrectedD0[ID] = tempVecF;
    muonSortedTrackNHits[ID] = tempVecI;
    muonSortedValidHitsGlobal[ID] = tempVecI;
    muonSortedNDOF[ID] = tempVecF; // n_d.o.f

    muonSortedVertX[ID] = tempVecF;
    muonSortedVertY[ID] = tempVecF;
    muonSortedVertZ[ID] = tempVecF;

    muonSortedInnerTkPt[ID] = tempVecF;
    muonSortedInnerTkPx[ID] = tempVecF;
    muonSortedInnerTkPy[ID] = tempVecF;
    muonSortedInnerTkPz[ID] = tempVecF;
    muonSortedInnerTkEta[ID] = tempVecF;
    muonSortedInnerTkPhi[ID] = tempVecF;

    muonSortedTkLysWithMeasurements[ID] = tempVecI;
    muonSortedGlbTkNormChi2[ID] = tempVecF;
    muonSortedInnerTkNormChi2[ID] = tempVecF;
    muonSortedDBPV[ID] = tempVecF;
    muonSortedDBPVError[ID] = tempVecF;
    muonSortedDZPV[ID] = tempVecF;
    muonSortedDZPVError[ID] = tempVecF;
    muonSortedVldPixHits[ID] = tempVecI;
    muonSortedMatchedStations[ID] = tempVecI;

    muonSortedImpactTransDist[ID] = tempVecF;
    muonSortedImpactTransError[ID] = tempVecF;
    muonSortedImpactTransSignificance[ID] = tempVecF;
    muonSortedImpact3DDist[ID] = tempVecF;
    muonSortedImpact3DError[ID] = tempVecF;
    muonSortedImpact3DSignificance[ID] = tempVecF;

    muonSortedChargedHadronIso[ID] = tempVecF;
    muonSortedNeutralHadronIso[ID] = tempVecF;
    muonSortedPhotonIso[ID] = tempVecF;

    muonSortedTrackIso[ID] = tempVecF;
    muonSortedECalIso[ID] = tempVecF;
    muonSortedHCalIso[ID] = tempVecF;
    muonSortedComRelIso[ID] = tempVecF;
    muonSortedComRelIsodBeta[ID] = tempVecF;
    muonSortedChHadIso[ID] = tempVecF;
    muonSortedNtHadIso[ID] = tempVecF;
    muonSortedGammaIso[ID] = tempVecF;
    muonSortedPuIso[ID] = tempVecF;
    muonSortedIsPFMuon[ID] = tempVecI;

    muonSortedNumChambers[ID] = tempVecI;
    muonSortedNumMatches[ID] = tempVecI;

    genMuonSortedPt[ID] = tempVecF;
    genMuonSortedEt[ID] = tempVecF;
    genMuonSortedEta[ID] = tempVecF;
    genMuonSortedTheta[ID] = tempVecF;
    genMuonSortedPhi[ID] = tempVecF;
    genMuonSortedPx[ID] = tempVecF;
    genMuonSortedPy[ID] = tempVecF;
    genMuonSortedPz[ID] = tempVecF;
    genMuonSortedCharge[ID] = tempVecI;
    genMuonSortedPdgId[ID] = tempVecI;
    genMuonSortedMotherId[ID] = tempVecI;
    genMuonSortedPromptDecayed[ID] = tempVecI;
    genMuonSortedPromptFinalState[ID] = tempVecI;
    genMuonSortedHardProcess[ID] = tempVecI;
    genMuonSortedPythiaSixStatusThree[ID] = tempVecI;

    mytree_->Branch(("numMuon" + name).c_str(), &numMuo[ID], ("numMuon" + name + "/I").c_str());
    std::string prefix{"muon" + name};
    mytree_->Branch((prefix + "E").c_str(), &muonSortedE[ID][0], (prefix + "E[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "ET").c_str(), &muonSortedEt[ID][0], (prefix + "ET[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Pt").c_str(), &muonSortedPt[ID][0], (prefix + "Pt[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "PX").c_str(), &muonSortedPx[ID][0], (prefix + "PX[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "PY").c_str(), &muonSortedPy[ID][0], (prefix + "PY[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "PZ").c_str(), &muonSortedPz[ID][0], (prefix + "PZ[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Phi").c_str(), &muonSortedPhi[ID][0], (prefix + "Phi[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Theta").c_str(), &muonSortedTheta[ID][0], (prefix + "Theta[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Eta").c_str(), &muonSortedEta[ID][0], (prefix + "Eta[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Charge").c_str(), &muonSortedCharge[ID][0], (prefix + "Charge[numMuon" + name + "]/I").c_str());

    mytree_->Branch((prefix + "LooseCutId").c_str(), &muonSortedLooseCutId[ID][0], (prefix + "LooseCutId[numMuon" + name + "]/I").c_str());
    mytree_->Branch((prefix + "MediumCutId").c_str(), &muonSortedMediumCutId[ID][0], (prefix + "MediumCutId[numMuon" + name + "]/I").c_str());
    mytree_->Branch((prefix + "TightCutId").c_str(), &muonSortedTightCutId[ID][0], (prefix + "TightCutId[numMuon" + name + "]/I").c_str());
    mytree_->Branch((prefix + "PfIsoVeryLoose").c_str(), &muonSortedPfIsoVeryLoose[ID][0], (prefix + "PfIsoVeryLoose[numMuon" + name + "]/I").c_str());
    mytree_->Branch((prefix + "PfIsoLoose").c_str(), &muonSortedPfIsoLoose[ID][0], (prefix + "PfIsoLoose[numMuon" + name + "]/I").c_str());
    mytree_->Branch((prefix + "PfIsoMedium").c_str(), &muonSortedPfIsoMedium[ID][0], (prefix + "PfIsoMedium[numMuon" + name + "]/I").c_str());
    mytree_->Branch((prefix + "PfIsoTight").c_str(), &muonSortedPfIsoTight[ID][0], (prefix + "PfIsoTight[numMuon" + name + "]/I").c_str());
    mytree_->Branch((prefix + "PfIsoVeryTight").c_str(), &muonSortedPfIsoVeryTight[ID][0], (prefix + "PfIsoVeryTight[numMuon" + name + "]/I").c_str());
    mytree_->Branch((prefix + "TkIsoLoose").c_str(), &muonSortedTkIsoLoose[ID][0], (prefix + "TkIsoLoose[numMuon" + name + "]/I").c_str());
    mytree_->Branch((prefix + "TkIsoTight").c_str(), &muonSortedTkIsoTight[ID][0], (prefix + "TkIsoTight[numMuon" + name + "]/I").c_str());
    mytree_->Branch((prefix + "MvaLoose").c_str(), &muonSortedMvaLoose[ID][0], (prefix + "MvaLoose[numMuon" + name + "]/I").c_str());
    mytree_->Branch((prefix + "MvaMedium").c_str(), &muonSortedMvaMedium[ID][0], (prefix + "MvaMedium[numMuon" + name + "]/I").c_str());
    mytree_->Branch((prefix + "MvaTight").c_str(), &muonSortedMvaTight[ID][0], (prefix + "MvaTight[numMuon" + name + "]/I").c_str());

    mytree_->Branch((prefix + "GlobalID").c_str(), &muonSortedGlobalID[ID][0], (prefix + "GlobalID[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "TrackID").c_str(), &muonSortedTrackID[ID][0], (prefix + "TrackID[numMuon" + name + "]/F").c_str());

    mytree_->Branch((prefix + "Chi2").c_str(), &muonSortedChi2[ID][0], (prefix + "Chi2[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "D0").c_str(), &muonSortedD0[ID][0], (prefix + "D0[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "TrackDBD0").c_str(), &muonSortedDBBeamSpotCorrectedTrackD0[ID][0], (prefix + "TrackDBD0[numMuon" + name + "]/F").c_str());

    mytree_->Branch((prefix + "DBInnerTrackD0").c_str(), &muonSortedDBInnerTrackD0[ID][0], (prefix + "DBInnerTrackD0[numMuon" + name + "]/F").c_str());

    mytree_->Branch((prefix + "BeamSpotCorrectedD0").c_str(), &muonSortedBeamSpotCorrectedD0[ID][0], (prefix + "BeamSpotCorrectedD0[numMuon" + name + "]/F").c_str());

    mytree_->Branch((prefix + "TrackNHits").c_str(), &muonSortedTrackNHits[ID][0], (prefix + "TrackNHits[numMuon" + name + "]/I").c_str());
    mytree_->Branch((prefix + "MuonNHits").c_str(), &muonSortedValidHitsGlobal[ID][0], (prefix + "MuonNHits[numMuon" + name + "]/I").c_str());
    mytree_->Branch((prefix + "NDOF").c_str(), &muonSortedNDOF[ID][0], (prefix + "NDOF[numMuon" + name + "]/F").c_str());

    mytree_->Branch((prefix + "VertX").c_str(), &muonSortedVertX[ID][0], (prefix + "VertX[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "VertY").c_str(), &muonSortedVertY[ID][0], (prefix + "VertY[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "VertZ").c_str(), &muonSortedVertZ[ID][0], (prefix + "VertZ[numMuon" + name + "]/F").c_str());

    mytree_->Branch((prefix + "InnerTkPt").c_str(), &muonSortedInnerTkPt[ID][0], (prefix + "InnerTkPt[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "InnerTkPx").c_str(), &muonSortedInnerTkPx[ID][0], (prefix + "InnerTkPx[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "InnerTkPy").c_str(), &muonSortedInnerTkPy[ID][0], (prefix + "InnerTkPy[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "InnerTkPz").c_str(), &muonSortedInnerTkPz[ID][0], (prefix + "InnerTkPz[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "InnerTkEta").c_str(), &muonSortedInnerTkEta[ID][0], (prefix + "InnerTkEta[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "InnerTkPhi").c_str(), &muonSortedInnerTkPhi[ID][0], (prefix + "InnerTkPhi[numMuon" + name + "]/F").c_str());

    mytree_->Branch((prefix + "TkLysWithMeasurements").c_str(), &muonSortedTkLysWithMeasurements[ID][0], (prefix + "TkLysWithMeasurements[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "GlbTkNormChi2").c_str(), &muonSortedGlbTkNormChi2[ID][0], (prefix + "GlbTkNormChi2[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "InnerTkNormChi2").c_str(), &muonSortedInnerTkNormChi2[ID][0], (prefix + "InnerTkNormChi2[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "DBPV").c_str(), &muonSortedDBPV[ID][0], (prefix + "DBPV[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "DBPVError").c_str(), &muonSortedDBPVError[ID][0], (prefix + "DBPVError[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "DZPV").c_str(), &muonSortedDZPV[ID][0], (prefix + "DZPV[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "DZPVError").c_str(), &muonSortedDZPVError[ID][0], (prefix + "DZPVError[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "VldPixHits").c_str(), &muonSortedVldPixHits[ID][0], (prefix + "VldPixHits[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "MatchedStations").c_str(), &muonSortedMatchedStations[ID][0], (prefix + "MatchedStations[numMuon" + name + "]/F").c_str());

    mytree_->Branch((prefix + "ImpactTransDist").c_str(), &muonSortedImpactTransDist[ID][0], (prefix + "ImpactTransDist[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "ImpactTransError").c_str(), &muonSortedImpactTransError[ID][0], (prefix + "ImpactTransError[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "ImpactTransSignificance").c_str(), &muonSortedImpactTransSignificance[ID][0], (prefix + "ImpactTransSignificance[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Impact3DDist").c_str(), &muonSortedImpact3DDist[ID][0], (prefix + "Impact3DDist[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Impact3DError").c_str(), &muonSortedImpact3DError[ID][0], (prefix + "Impact3DError[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Impact3DSignificance").c_str(), &muonSortedImpact3DSignificance[ID][0], (prefix + "Impact3DSignificance[numMuon" + name + "]/F").c_str());

    mytree_->Branch((prefix + "ChargedHadronIso").c_str(), &muonSortedChargedHadronIso[ID][0], (prefix + "ChargedHadronIso[numMuon" + name + "]/F").c_str());
    mytree_->Branch( (prefix + "NeutralHadronIso").c_str(), &muonSortedNeutralHadronIso[ID][0], (prefix + "NeutralHadronIso[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "PhotonIso").c_str(), &muonSortedPhotonIso[ID][0], (prefix + "PhotonIso[numMuon" + name + "]/F").c_str());

    mytree_->Branch((prefix + "TrackIso").c_str(), &muonSortedTrackIso[ID][0], (prefix + "TrackIso[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "EcalIso").c_str(), &muonSortedECalIso[ID][0], (prefix + "EcalIso[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "HcalIso").c_str(), &muonSortedHCalIso[ID][0], (prefix + "HcalIso[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "ComRelIso").c_str(), &muonSortedComRelIso[ID][0], (prefix + "ComRelIso[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "ComRelIsodBeta").c_str(), &muonSortedComRelIsodBeta[ID][0], (prefix + "ComRelIsodBeta[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "ChHadIso").c_str(), &muonSortedChHadIso[ID][0], (prefix + "ChHadIso[numMuon" + name + "]/F").c_str());;
    mytree_->Branch((prefix + "NtHadIso").c_str(), &muonSortedNtHadIso[ID][0], (prefix + "NtHadIso[numMuon" + name + "]/F").c_str());;
    mytree_->Branch((prefix + "GammaIso").c_str(), &muonSortedGammaIso[ID][0], (prefix + "GammaIso[numMuon" + name + "]/F").c_str());;
    mytree_->Branch((prefix + "PuIso").c_str(), &muonSortedPuIso[ID][0], (prefix + "PuIso[numMuon" + name + "]/F").c_str());;
    mytree_->Branch((prefix + "IsPFMuon").c_str(), &muonSortedIsPFMuon[ID][0], (prefix + "IsPFMuon[numMuon" + name + "]/I").c_str());

    mytree_->Branch((prefix + "NChambers").c_str(), &muonSortedNumChambers[ID][0], (prefix + "NChambers[numMuon" + name + "]/I").c_str());
    mytree_->Branch((prefix + "NMatches").c_str(), &muonSortedNumMatches[ID][0], (prefix + "NMatches[numMuon" + name + "]/I").c_str());

    mytree_->Branch((prefix + "ValidFraction").c_str(), &muonValidFraction[ID][0], (prefix + "ValidFraction[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Chi2LocalPosition").c_str(), &muonChi2LocalPosition[ID][0], (prefix + "Chi2LocalPosition[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "TrkKick").c_str(), &muonTrkKick[ID][0], (prefix + "TrkKick[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SegmentCompatibility").c_str(), &muonSegmentCompatibility[ID][0], (prefix + "SegmentCompatibility[numMuon" + name + "]/F").c_str());

    if (runMCInfo_) {
        prefix = "genMuon" + name;
        mytree_->Branch((prefix + "PT").c_str(), &genMuonSortedPt[ID][0], (prefix + "PT[numMuon" + name + "]/F").c_str());
        mytree_->Branch((prefix + "ET").c_str(), &genMuonSortedEt[ID][0], (prefix + "ET[numMuon" + name + "]/F").c_str());
        mytree_->Branch((prefix + "PX").c_str(), &genMuonSortedPx[ID][0], (prefix + "PX[numMuon" + name + "]/F").c_str());
        mytree_->Branch((prefix + "PY").c_str(), &genMuonSortedPy[ID][0], (prefix + "PY[numMuon" + name + "]/F").c_str());
        mytree_->Branch((prefix + "PZ").c_str(), &genMuonSortedPz[ID][0], (prefix + "PZ[numMuon" + name + "]/F").c_str());
        mytree_->Branch((prefix + "Phi").c_str(), &genMuonSortedPhi[ID][0], (prefix + "Phi[numMuon" + name + "]/F").c_str());
        mytree_->Branch((prefix + "Theta").c_str(), &genMuonSortedTheta[ID][0], (prefix + "Theta[numMuon" + name + "]/F").c_str());
        mytree_->Branch((prefix + "Eta").c_str(), &genMuonSortedEta[ID][0], (prefix + "Eta[numMuon" + name + "]/F").c_str());
        mytree_->Branch((prefix + "Charge").c_str(), &genMuonSortedCharge[ID][0], (prefix + "Charge[numMuon" + name + "]/I").c_str());
        mytree_->Branch((prefix + "PdgId").c_str(), &genMuonSortedPdgId[ID][0], (prefix + "PdgId[numMuon" + name + "]/I").c_str());
        mytree_->Branch((prefix + "MotherId").c_str(), &genMuonSortedMotherId[ID][0], (prefix + "MotherId[numMuon" + name + "]/I").c_str());
        mytree_->Branch((prefix + "PromptDecayed").c_str(), &genMuonSortedPromptDecayed[ID][0], (prefix + "PromptDecayed[numMuon" + name + "]/I").c_str());
        mytree_->Branch( (prefix + "PromptFinalState").c_str(), &genMuonSortedPromptFinalState[ID][0], (prefix + "PromptFinalState[numMuon" + name + "]/I").c_str());
        mytree_->Branch((prefix + "HardProcess").c_str(), &genMuonSortedHardProcess[ID][0], (prefix + "HardProcess[numMuon" + name + "]/I").c_str());
        mytree_->Branch((prefix + "PythiaSixStatusThree").c_str(), &genMuonSortedPythiaSixStatusThree[ID][0], (prefix + "PythiaSixStatusThree[numMuon" + name + "]/I").c_str());
    }
}

// book MC branches:
void MakeMiniMuonNtupleMiniAOD::bookMCBranches()
{
    // std::cout << "bookMCBranches CHECK" << std::endl;
    // mytree_->Branch("nT", &nT, "nT/I");
    //
    // mytree_->Branch("nThadronic", &nThadronic, "nThadronic/I");
    // mytree_->Branch("T_hadronicMCTruthE",
    //                 T_hadronicMCTruthE,
    //                 "T_hadronicMCTruthE[nThadronic]/F");
    // mytree_->Branch("T_hadronicMCTruthEt",
    //                 T_hadronicMCTruthEt,
    //                 "T_hadronicMCTruthEt[nThadronic]/F");
    // mytree_->Branch("T_hadronicMCTruthPx",
    //                 T_hadronicMCTruthPx,
    //                 "T_hadronicMCTruthPx[nThadronic]/F");
    // mytree_->Branch("T_hadronicMCTruthPy",
    //                 T_hadronicMCTruthPy,
    //                 "T_hadronicMCTruthPy[nThadronic]/F");
    // mytree_->Branch("T_hadronicMCTruthPz",
    //                 T_hadronicMCTruthPz,
    //                 "T_hadronicMCTruthPz[nThadronic]/F");
    // mytree_->Branch("T_hadronicMCMotherIndex",
    //                 T_hadronicMotherIndex,
    //                 "T_hadronicMCMotherIndex[nThadronic]/I");
    //
    // mytree_->Branch("nTleptonic", &nTleptonic, "nTleptonic/I");
    // mytree_->Branch("T_leptonicMCTruthE",
    //                 T_leptonicMCTruthE,
    //                 "T_leptonicMCTruthE[nTleptonic]/F");
    // mytree_->Branch("T_leptonicMCTruthEt",
    //                 T_leptonicMCTruthEt,
    //                 "T_leptonicMCTruthEt[nTleptonic]/F");
    // mytree_->Branch("T_leptonicMCTruthPx",
    //                 T_leptonicMCTruthPx,
    //                 "T_leptonicMCTruthPx[nTleptonic]/F");
    // mytree_->Branch("T_leptonicMCTruthPy",
    //                 T_leptonicMCTruthPy,
    //                 "T_leptonicMCTruthPy[nTleptonic]/F");
    // mytree_->Branch("T_leptonicMCTruthPz",
    //                 T_leptonicMCTruthPz,
    //                 "T_leptonicMCTruthPz[nTleptonic]/F");
    // mytree_->Branch("T_leptonicMCMotherIndex",
    //                 T_leptonicMotherIndex,
    //                 "T_leptonicMCMotherIndex[nTleptonic]/I");
    //
    // mytree_->Branch("nb", &nb, "nb/I");
    // mytree_->Branch("bMCTruthE", bMCTruthE, "bMCTruthE[nb]/F");
    // mytree_->Branch("bMCTruthEt", bMCTruthEt, "bMCTruthEt[nb]/F");
    // mytree_->Branch("bMCTruthPx", bMCTruthPx, "bMCTruthPx[nb]/F");
    // mytree_->Branch("bMCTruthPy", bMCTruthPy, "bMCTruthPy[nb]/F");
    // mytree_->Branch("bMCTruthPz", bMCTruthPz, "bMCTruthPz[nb]/F");
    // mytree_->Branch("bMCTruthMother", bMCTruthMother,
    // "bMCTruthMother[nb]/I");
    //
    // mytree_->Branch("nWhadronic", &nWhadronic, "nWhadronic/I");
    // mytree_->Branch("W_hadronicMCTruthE",
    //                 W_hadronicMCTruthE,
    //                 "W_hadronicMCTruthE[nWhadronic]/F");
    // mytree_->Branch("W_hadronicMCTruthEt",
    //                 W_hadronicMCTruthEt,
    //                 "W_hadronicMCTruthEt[nWhadronic]/F");
    // mytree_->Branch("W_hadronicMCTruthPx",
    //                 W_hadronicMCTruthPx,
    //                 "W_hadronicMCTruthPx[nWhadronic]/F");
    // mytree_->Branch("W_hadronicMCTruthPy",
    //                 W_hadronicMCTruthPy,
    //                 "W_hadronicMCTruthPy[nWhadronic]/F");
    // mytree_->Branch("W_hadronicMCTruthPz",
    //                 W_hadronicMCTruthPz,
    //                 "W_hadronicMCTruthPz[nWhadronic]/F");
    // mytree_->Branch("W_hadronicMCTruthPID",
    //                 W_hadronicMCTruthPID,
    //                 "W_hadronicMCTruthPID[nWhadronic]/I");
    // mytree_->Branch("W_hadronicMCTruthMother",
    //                 W_hadronicMCTruthMother,
    //                 "W_hadronicMCTruthMother[nWhadronic]/I");
    //
    // mytree_->Branch("nWleptonic", &nWleptonic, "nWleptonic/I");
    // mytree_->Branch("W_leptonicMCTruthE",
    //                 W_leptonicMCTruthE,
    //                 "W_leptonicMCTruthE[nWleptonic]/F");
    // mytree_->Branch("W_leptonicMCTruthEt",
    //                 W_leptonicMCTruthEt,
    //                 "W_leptonicMCTruthEt[nWleptonic]/F");
    // mytree_->Branch("W_leptonicMCTruthPx",
    //                 W_leptonicMCTruthPx,
    //                 "W_leptonicMCTruthPx[nWleptonic]/F");
    // mytree_->Branch("W_leptonicMCTruthPy",
    //                 W_leptonicMCTruthPy,
    //                 "W_leptonicMCTruthPy[nWleptonic]/F");
    // mytree_->Branch("W_leptonicMCTruthPz",
    //                 W_leptonicMCTruthPz,
    //                 "W_leptonicMCTruthPz[nWleptonic]/F");
    // mytree_->Branch("W_leptonicMCTruthPID",
    //                 W_leptonicMCTruthPID,
    //                 "W_leptonicMCTruthPID[nWleptonic]/I");
    // mytree_->Branch("W_leptonicMCTruthMother",
    //                 W_leptonicMCTruthMother,
    //                 "W_leptonicMCTruthMother[nWleptonic]/I");

    mytree_->Branch("isElePlusJets", &isElePlusJets, "isElePlusJets/I");
    // mytree_->Branch("VQQBosonAbsId", &VQQBosonAbsId, "VQQBosonAbsId/I");

    mytree_->Branch("genPDFScale", &genPDFScale, "genPDFScale/F");
    mytree_->Branch("genPDFx1", &genPDFx1, "genPDFx1/F");
    mytree_->Branch("genPDFx2", &genPDFx2, "genPDFx2/F");
    mytree_->Branch("genPDFf1", &genPDFf1, "genPDFf1/I");
    mytree_->Branch("genPDFf2", &genPDFf2, "genPDFf2/I");

    if (runPDFUncertainties_)
    {
        mytree_->Branch(
            "genCTEQ66_Weight", genCTEQ66_Weight, "genCTEQ66_Weight[44]/F");
        mytree_->Branch("genMRST2006nnlo_Weight",
                        genMRST2006nnlo_Weight,
                        "genMRST2006nnlo_Weight[31]/F");
    }

    // Book in the ttbar top pt reweighting information.
    mytree_->Branch("topPtReweight", &topPtReweight, "topPtReweight/D");
}

// ------------ method called once each job just before starting event loop
// ------------
void
    // MakeMiniMuonNtupleMiniAOD::beginJob(const edm::EventSetup&
    // #<{(|unused|)}>#)
    MakeMiniMuonNtupleMiniAOD::beginJob()
{
    if (runPDFUncertainties_)
    {
        // Setup the PDFs
        // CTEQ 6.6
        initPDFSet(0, "cteq66", LHAPDF::LHGRID, 0);
        initPDFSet(1, "MRST2006nnlo", LHAPDF::LHGRID, 0);
    }
}

// ------------ method called once each job just after ending the event loop
// ------------
void MakeMiniMuonNtupleMiniAOD::endJob()
{
    std::cout << "+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+="
              << std::endl;
    std::cout << "\n\nJOB Summary:" << std::endl;
    std::cout << "number of events processed: " << histocontainer1D_["eventcount"]->GetEntries() << std::endl;
    std::cout << "number of events added to tree: " << mytree_->GetEntries() << std::endl;
    std::cout << "\n+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+="
              << std::endl;
}
void MakeMiniMuonNtupleMiniAOD::fillTriggerData(const edm::Event& iEvent)
{
    // std::cout << "fillTriggerData CHECK" << std::endl;
    for (int& TriggerBit : TriggerBits)
    { // size hard-coded in MakeMiniMuonNtuple.h!!!
        TriggerBit = -999;
    }

    if (!check_triggers_)
    {
        std::cout << "not checking triggers! " << std::endl;
        return;
    }
    edm::Handle<edm::TriggerResults> hltResults;
    iEvent.getByToken(trigToken_, hltResults);

    if (hltResults.product()->wasrun())
    {
        const edm::TriggerNames& triggerNames{iEvent.triggerNames(*hltResults)};

        // HLTBits_Size = hltResults.product()->size();
        nTriggerBits = 0;

        hltnames_ = triggerNames.triggerNames();

        for (int itrig{0}; itrig < (int)hltnames_.size(); ++itrig)  {
            const bool accept{hltResults->accept(itrig)};
            // if (histocontainer1D_["eventcount"]->GetBinContent(0.0) < 2)
            // {
            //     std::cout << "TRIGGER BIT:" << itrig << ", NAME:" << hltnames_[itrig] << " FIRED:" << accept << std::endl;
            // }
            int trigbit{0};
            if (accept) {
                trigbit = 1;
            }
            if (!hltResults->wasrun(itrig))
                trigbit = -1;
            if (hltResults->error(itrig))
                trigbit = -2;

            for (size_t iTrigList{0}; iTrigList < triggerList_.size(); iTrigList++) {
                if (triggerList_[iTrigList] == hltnames_[itrig]) {
                    // if (mytree_->GetEntries() < 1)
                    // {
                    //     std::cout << "found 'standard' trigger bit "
                    //               << triggerList_[iTrigList] << std::endl;
                    // }
                    triggerRes[iTrigList] = trigbit;
                }
            }
        }
    } // hltResults.wasRun()

    edm::Handle<edm::TriggerResults> metFilterResults;
    iEvent.getByToken(metFilterToken_, metFilterResults);

    // ecalBadCalibReducedMINIAODFilter
/*    if (!is2016_) {
        edm::Handle< bool > passecalBadCalibFilterUpdate;
        iEvent.getByToken(ecalBadCalibFilterUpdate_token_, passecalBadCalibFilterUpdate);
        bool _passecalBadCalibFilterUpdate = (*passecalBadCalibFilterUpdate);
        Flag_ecalBadCalibReducedMINIAODFilter = _passecalBadCalibFilterUpdate;
    }
*/
    if (metFilterResults.product()->wasrun()) {
        const edm::TriggerNames& metFilterNames{iEvent.triggerNames(*metFilterResults)};
        // HLTBits_Size = metFilterResults.product()->size();

        metFilterNames_ = metFilterNames.triggerNames();
        for (int iFilter{0}; iFilter < (int)metFilterNames_.size(); ++iFilter) {
            const bool accept(metFilterResults->accept(iFilter));
            // if (histocontainer1D_["eventcount"]->GetBinContent(0.0) < 2)
            // {
            //     if (metFilterNames_[iFilter] == "Flag_noBadMuons")
            //     {
            //         std::cout << "FILTER BIT:" << iFilter << ", NAME:" << metFilterNames_[iFilter] << " FIRED:" << accept << std::endl;
            //     }
            // }
            int filterbit{0};
            if (accept) {
                filterbit = 1;
            }
            if (!metFilterResults->wasrun(iFilter))
                filterbit = -1;
            if (metFilterResults->error(iFilter))
                filterbit = -2;
            for (size_t iMetFilterList{0}; iMetFilterList < metFilterList_.size(); iMetFilterList++) {
                if (metFilterList_[iMetFilterList] == metFilterNames_[iFilter]) {
                    metFilterRes[iMetFilterList] = filterbit;
                }
            }
        }
    } // metFilterResults.wasRun()

    // collect the fake trigger information:
    if (fakeTrigLabelList_.size() > 0)
    {
        edm::Handle<edm::TriggerResults> fakeResults;
        // gettnig the default TriggerResults, which is (by definition) the
        // latest one produced.
        iEvent.getByLabel(edm::InputTag("TriggerResults"), fakeResults);

        const edm::TriggerNames& triggerNamesFake{
            iEvent.triggerNames(*fakeResults)};
        for (size_t ii{0}; ii < fakeTrigLabelList_.size(); ++ii)
        {
            // std::cout << "looking for path " << fakeTrigLabelList_[ii]
            //           << std::endl;
            size_t pathIndex{
                triggerNamesFake.triggerIndex(fakeTrigLabelList_[ii])};
            HLT_fakeTriggerValues[ii] = -99;
            // if (pathIndex >= 0 && pathIndex < triggerNamesFake.size())
            if (pathIndex < triggerNamesFake.size())
            {
                // std::cout << "found it! " << std::endl;
                int trigbit{0};
                if (fakeResults->accept(pathIndex))
                    trigbit = 1;
                if (!fakeResults->wasrun(pathIndex))
                    trigbit = -1;
                if (fakeResults->error(pathIndex))
                    trigbit = -2;
                HLT_fakeTriggerValues[ii] = trigbit;
                if (mytree_->GetEntries() <= 2)
                    std::cout << "fake trigger bit: " << fakeTrigLabelList_[ii]
                              << " TRIGGERED: " << HLT_fakeTriggerValues[ii]
                              << std::endl;
            }
        }
    }
}

/////////////
// identification functions!
/////////////

// define this as a plug-in
DEFINE_FWK_MODULE(MakeMiniMuonNtupleMiniAOD);

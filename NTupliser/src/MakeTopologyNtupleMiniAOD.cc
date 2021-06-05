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
#include "NTupliser/NTupliser/interface/MakeTopologyNtupleMiniAOD.h"
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

#include "Math/LorentzVector.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"

// using namespace reweight;
using boost::numeric_cast;
typedef math::XYZTLorentzVectorF LorentzVector;

MakeTopologyNtupleMiniAOD::MakeTopologyNtupleMiniAOD(
    const edm::ParameterSet& iConfig)
    : beamSpotToken_{consumes<reco::BeamSpot>(iConfig.getParameter<edm::InputTag>("beamSpotToken"))}
    , packedCandToken_{consumes<std::vector<pat::PackedCandidate>>(iConfig.getParameter<edm::InputTag>("packedCandToken"))}
    , packedGenParticleToken_{consumes<std::vector<pat::PackedGenParticle>>(iConfig.getParameter<edm::InputTag>("packedGenParticleToken"))}
    , isolatedTrackToken_{consumes<std::vector<pat::IsolatedTrack>>(iConfig.getParameter<edm::InputTag>("isolatedTrackToken"))}
    , conversionsToken_{consumes<std::vector<reco::Conversion>>(iConfig.getParameter<edm::InputTag>("conversionsToken"))}
    , eleLabel_{consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("electronTag"))}
    , phoLabel_{consumes<pat::PhotonCollection>(iConfig.getParameter<edm::InputTag>("photonTag"))}
    , ootPhoLabel_{consumes<pat::PhotonCollection>(iConfig.getParameter<edm::InputTag>("ootPhotonTag"))}
    , muoLabel_{iConfig.getParameter<edm::InputTag>("muonTag")}
    , jetLabel_{iConfig.getParameter<edm::InputTag>("jetLabel")}
    , genJetsToken_{consumes<reco::GenJetCollection>(iConfig.getParameter<edm::InputTag>("genJetToken"))}
    , tauLabel_{iConfig.getParameter<edm::InputTag>("tauTag")}
    , metLabel_{iConfig.getParameter<edm::InputTag>("metTag")}
    , patPhotonsToken_{consumes<pat::PhotonCollection>(iConfig.getParameter<edm::InputTag>("photonPFToken"))}
    , patOOTphotonsToken_{consumes<pat::PhotonCollection>(iConfig.getParameter<edm::InputTag>("ootPhotonPFToken"))}
    , patElectronsToken_{consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("electronPFToken"))}
    , tauPFTag_{iConfig.getParameter<edm::InputTag>("tauPFTag")}
    , patMuonsToken_{consumes<pat::MuonCollection>(iConfig.getParameter<edm::InputTag>("muonPFToken"))}
    , patJetsToken_{consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("jetPFToken"))}
    , jetPFRecoTag_{iConfig.getParameter<edm::InputTag>("jetPFRecoTag")}
    , patMetToken_{consumes<pat::METCollection>(iConfig.getParameter<edm::InputTag>("metPFToken"))}
    // , jetJPTTag_(iConfig.getParameter<edm::InputTag>("jetJPTTag"))
    // , metJPTTag_(iConfig.getParameter<edm::InputTag>("metJPTTag"))
    , trigToken_{consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerToken"))}
    , metFilterToken_{consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("metFilterToken"))}
    , fakeTrigLabelList_{iConfig.getParameter<std::vector<std::string>>("fakeTriggerList")}
    , bTagList_{iConfig.getParameter<std::vector<std::string>>("bTagList")}
    , triggerList_{iConfig.getParameter<std::vector<std::string>>("triggerList")}
    , metFilterList_{iConfig.getParameter<std::vector<std::string>>("metFilterList")}
    , l1TrigLabel_{iConfig.getParameter<edm::InputTag>("l1TriggerTag")}
    , genParticlesToken_{consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("genParticles"))}
    , genSimParticlesToken_{consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("genSimParticles"))}
    , pvLabel_{consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("primaryVertexToken"))}
    , svLabel_{consumes<reco::VertexCompositePtrCandidateCollection>(iConfig.getParameter<edm::InputTag>("secondaryVertexToken"))}
    , kshortToken_{consumes<reco::VertexCompositePtrCandidateCollection>(iConfig.getParameter<edm::InputTag>("kshortToken"))}
    , lambdaToken_{consumes<reco::VertexCompositePtrCandidateCollection>(iConfig.getParameter<edm::InputTag>("lambdaToken"))}
    , rhoToken_{consumes<double>(iConfig.getParameter<edm::InputTag>("rhoToken"))}
    , effectiveAreaInfo_{(iConfig.getParameter<edm::FileInPath>("effAreasConfigFile")).fullPath()}
    , pileupToken_{consumes<std::vector<PileupSummaryInfo>>(iConfig.getParameter<edm::InputTag>("pileupToken"))}
    , hasGeneralTracks_{iConfig.getParameter<bool>("hasGeneralTracks")}
    , generalTracksToken_{mayConsume<reco::TrackCollection>(iConfig.getParameter<edm::InputTag>("generalTracksToken"))}
    , debugMode_{iConfig.getParameter<bool>("debugMode")}
    , is2016rereco_{iConfig.getParameter<bool>("is2016rereco")}
    , isttbar_{iConfig.getParameter<bool>("isttBar")}
    , ttGenEvent_{iConfig.getParameter<edm::InputTag>("ttGenEvent")}
    , scalarPid_{iConfig.getParameter<int>("scalarPid")}
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
    , jetPtCut_{iConfig.getParameter<double>("minJetPt")}
    , jetEtaCut_{iConfig.getParameter<double>("maxJetEta")}
    , runPDFUncertainties_{iConfig.getParameter<bool>("runPDFUncertainties")}
    , useResidualJEC_{iConfig.getParameter<bool>("useResidualJEC")}
    , minLeptons_{iConfig.getParameter<int>("minLeptons")}
    , elePtCut_{iConfig.getParameter<double>("minElePt")}
    , eleEtaCut_{iConfig.getParameter<double>("maxEleEta")}
    , eleIsoCut_{iConfig.getParameter<double>("eleRelIso")}
    , muoPt1Cut_{iConfig.getParameter<double>("minMuonPt1")}
    , muoPt2Cut_{iConfig.getParameter<double>("minMuonPt2")}
    , muoEtaCut_{iConfig.getParameter<double>("maxMuonEta")}
    , invMuMuMassCut_{iConfig.getParameter<double>("maxInvMuMuMass")}
    , muoIsoCut_{iConfig.getParameter<double>("muoRelIso")}
    , metCut_{iConfig.getParameter<double>("metCut")} // met cut
    , check_triggers_{iConfig.getParameter<bool>("checkTriggers")}
    , dREleGeneralTrackMatch_{iConfig.getParameter<double>("dREleGeneralTrackMatchForPhotonRej")}
    , magneticField_{iConfig.getParameter<double>("magneticFieldForPhotonRej")}
    , correctFactor_{iConfig.getParameter<double>("correctFactorForPhotonRej")}
    , maxDist_{iConfig.getParameter<double>("maxDistForPhotonRej")}
    , maxDcot_{iConfig.getParameter<double>("maxDcotForPhotonRej")}
    , isMCatNLO_{iConfig.getParameter<bool>("isMCatNLO")}
    , isLHEflag_{iConfig.getParameter<bool>("isLHEflag")}
    , hasAlphaWeightFlag_{iConfig.getParameter<bool>("hasAlphaWeightFlag")}
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

MakeTopologyNtupleMiniAOD::~MakeTopologyNtupleMiniAOD() {
    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)

    mytree_->FlushBaskets();
}

//
// member functions
//
void MakeTopologyNtupleMiniAOD::fillSummaryVariables() {
    ran_postloop_ = true;
    return;
}

void MakeTopologyNtupleMiniAOD::fillEventInfo(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
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

void MakeTopologyNtupleMiniAOD::fillPV(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

    edm::Handle<reco::VertexCollection> pvHandle;
    iEvent.getByToken(pvLabel_, pvHandle);

    if (pvHandle.isValid()) {
        std::vector<reco::Vertex> pv{*pvHandle};

        numPVs = 0;

        for (auto it{pv.begin()}; it != pv.end() && numPVs < numeric_cast<int>(NPVSMAX); it++) {
            pvX[numPVs] = it->x();
            pvY[numPVs] = it->y();
            pvZ[numPVs] = it->z();
            pvCov00[numPVs] = it->covariance(0,0);
            pvCov01[numPVs] = it->covariance(0,1);
            pvCov02[numPVs] = it->covariance(0,2);
            pvCov10[numPVs] = it->covariance(1,0);
            pvCov11[numPVs] = it->covariance(1,1);
            pvCov12[numPVs] = it->covariance(1,2);
            pvCov20[numPVs] = it->covariance(2,0);
            pvCov21[numPVs] = it->covariance(2,1);
            pvCov22[numPVs] = it->covariance(2,2);
            pvRho[numPVs] = it->position().Rho();
            pvNdof[numPVs] = it->ndof();
            pvIsFake[numPVs] = numeric_cast<int>(it->isFake());
            pvChi2[numPVs] = it->chi2();
            pvNtracks[numPVs] = int(it->tracksSize());
            pvNtracksW05[numPVs] = it->nTracks(0.5);
            pvTime[numPVs] = it->t();
            pvTimeError[numPVs] = it->tError();
            numPVs++;
        }
    }
}

void MakeTopologyNtupleMiniAOD::fillSV(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

    edm::Handle<reco::VertexCompositePtrCandidateCollection> svHandle;
    iEvent.getByToken(svLabel_, svHandle);

    edm::Handle<reco::VertexCompositePtrCandidateCollection> kshortHandle;
    iEvent.getByToken(kshortToken_, kshortHandle);    

    edm::Handle<reco::VertexCompositePtrCandidateCollection> lambdaHandle;
    iEvent.getByToken(lambdaToken_, lambdaHandle);    

    if (!ran_PV_) fillEventInfo(iEvent, iSetup); // Make sure we have PV info otherwise this cannot be done!

    if (svHandle.isValid()) {
        std::vector<reco::VertexCompositePtrCandidate> sv{*svHandle};

        std::vector<reco::VertexCompositePtrCandidate> kshort{*kshortHandle};
        std::vector<reco::VertexCompositePtrCandidate> lambda{*lambdaHandle};

        numSVs = 0;
        for (auto it{sv.begin()}; it != sv.end() && numSVs < numeric_cast<int>(NSVSMAX); it++) {

            svPt[numSVs] = it->pt();
            svPx[numSVs] = it->px();
            svPy[numSVs] = it->py();
            svPz[numSVs] = it->pz();
            svMass[numSVs] = it->mass();
            svE[numSVs] = it->energy();
            svEta[numSVs] = it->eta();
            svTheta[numSVs] = it->theta();
            svPhi[numSVs] = it->phi();
            svX[numSVs] = it->vx();
            svY[numSVs] = it->vy();
            svZ[numSVs] = it->vz();
            svCov00[numSVs] = it->vertexCovariance(0,0);
            svCov01[numSVs] = it->vertexCovariance(0,1);
            svCov02[numSVs] = it->vertexCovariance(0,2);
            svCov10[numSVs] = it->vertexCovariance(1,0);
            svCov11[numSVs] = it->vertexCovariance(1,1);
            svCov12[numSVs] = it->vertexCovariance(1,2);
            svCov20[numSVs] = it->vertexCovariance(2,0);
            svCov21[numSVs] = it->vertexCovariance(2,1);
            svCov22[numSVs] = it->vertexCovariance(2,2);
            svVertexChi2[numSVs] = it->vertexChi2();
            svVertexNdof[numSVs] = it->vertexNdof();
            svNtracks[numSVs] = int(it->numberOfDaughters());

            reco::Vertex * sec_vertex = new reco::Vertex(it->vertex(),it->vertexCovariance(),it->vertexChi2(),it->vertexNdof(), 0);
            VertexDistance3D vdist3D, vdistXY;
            Measurement1D dist3D = vdist3D.distance(*sec_vertex,*vertexPrimary_);
            Measurement1D distXY = vdistXY.distance(*sec_vertex,*vertexPrimary_);

            svDist3D[numSVs] = dist3D.value();
            svDist3DSig[numSVs] = dist3D.significance();
            svDist3DError[numSVs] = dist3D.error();
            svDistXY[numSVs] = distXY.value();
            svDistXYSig[numSVs] = distXY.significance();
            svDistXYError[numSVs] = distXY.error();

            reco::Candidate::Vector p = it->momentum();
            reco::Candidate::Vector d(it->vx() - vertexPrimary_->x(), it->vy() - vertexPrimary_->y(), it->vz() - vertexPrimary_->z());
            svAnglePV[numSVs] = p.Unit().Dot(d.Unit());

            svIsLambda[numSVs] = 0;
            svIsKshort[numSVs] = 0;

            if (kshortHandle.isValid()) {
                for (auto kIt{kshort.begin()}; kIt != kshort.end(); kIt++) {
                    for (unsigned int i1 = 0; i1 != kIt->numberOfSourceCandidatePtrs(); i1++) {
                        auto c1s = kIt->sourceCandidatePtr(i1);
                        for (unsigned int i2 = 0; i2 != it->numberOfSourceCandidatePtrs(); i2++) {
                            if ( it->sourceCandidatePtr(i2) == c1s) {
                                svIsKshort[numSVs] = 1;
                                break;
                            }
                        }
                    }
                }
            }

            if (lambdaHandle.isValid()) {
                for (auto lIt{lambda.begin()}; lIt != lambda.end(); lIt++) {
                    for (unsigned int  i1 = 0; i1 !=  lIt->numberOfSourceCandidatePtrs(); i1++) {
                        auto c1s = lIt->sourceCandidatePtr(i1);
                        for (unsigned int i2 = 0; i2 != it->numberOfSourceCandidatePtrs(); i2++) {
                            if ( it->sourceCandidatePtr(i2) == c1s) {
                                svIsLambda[numSVs] = 1;
                                break;
                            }
                        }
                    }
                }
            }

            numSVs++;
        }
    }
}

void MakeTopologyNtupleMiniAOD::fillMissingET(const edm::Event& iEvent, const edm::EventSetup& iSetup, edm::EDGetTokenT<pat::METCollection> metIn_, const std::string& ID) {

    edm::Handle<pat::METCollection> metHandle;
    iEvent.getByToken(metIn_, metHandle);

    metE[ID] = metHandle->front().energy();
    metEt[ID] = metHandle->front().et();
    metEtRaw[ID] = metHandle->front().et();
    metPhi[ID] = metHandle->front().phi();
    metPt[ID] = metHandle->front().pt();
    metPx[ID] = metHandle->front().px();
    metPy[ID] = metHandle->front().py();
    metPz[ID] = metHandle->front().pz();
    metScalarEt[ID] = metHandle->front().sumEt();
    metEtUncorrected[ID] = metHandle->front().uncorPt();
    metPhiUncorrected[ID] = metHandle->front().uncorPhi();
    metUnclusteredEnUp[ID] = metHandle->front().shiftedPt(pat::MET::UnclusteredEnUp);
    metUnclusteredEnDown[ID] = metHandle->front().shiftedPt(pat::MET::UnclusteredEnDown);

    if (metHandle->front().isCaloMET()) {
        metMaxEtEM[ID] = metHandle->front().maxEtInEmTowers();
        metMaxEtHad[ID] = metHandle->front().maxEtInHadTowers();
        metEtFracHad[ID] = metHandle->front().etFractionHadronic();
        metEtFracEM[ID] = metHandle->front().emEtFraction();
        metHadEtHB[ID] = metHandle->front().hadEtInHB();
        metHadEtHO[ID] = metHandle->front().hadEtInHO();
        metHadEtHF[ID] = metHandle->front().hadEtInHF();
        metHadEtHE[ID] = metHandle->front().hadEtInHE();
        metEmEtHF[ID] = metHandle->front().emEtInHF();
        metEmEtEE[ID] = metHandle->front().emEtInEE();
        metEmEtEB[ID] = metHandle->front().emEtInEB();

        metSignificance[ID] = metHandle->front().metSignificance();
        // std::cout << metSignificance << std::endl;
    }
    if (metHandle->front().genMET()) {
        genMetE[ID] = metHandle->front().genMET()->energy();
        genMetEt[ID] = metHandle->front().genMET()->et();
        genMetPhi[ID] = metHandle->front().genMET()->phi();
        genMetPt[ID] = metHandle->front().genMET()->pt();
        genMetPx[ID] = metHandle->front().genMET()->px();
        genMetPy[ID] = metHandle->front().genMET()->py();
        genMetPz[ID] = metHandle->front().genMET()->pz();
    }
    else {
        genMetE[ID] = -999.;
        genMetEt[ID] = -999.;
        genMetPhi[ID] = -999.;
        genMetPt[ID] = -999.;
        genMetPx[ID] = -999.;
        genMetPy[ID] = -999.;
        genMetPz[ID] = -999.;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////
void MakeTopologyNtupleMiniAOD::fillBeamSpot(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
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
void MakeTopologyNtupleMiniAOD::fillPhotons( const edm::Event& iEvent, const edm::EventSetup& iSetup, edm::EDGetTokenT<pat::PhotonCollection> phoIn_, const std::string& ID, edm::EDGetTokenT<pat::PhotonCollection> phoInOrg_) {
  // info for 'default conversion finder

  edm::ESHandle<MagneticField> magneticField;
  iSetup.get<IdealMagneticFieldRecord>().get(magneticField);
  
//  fillBeamSpot(iEvent, iSetup);
//  fillIsolatedTracks(iEvent, iSetup);
//  fillLostTracksCands(iEvent, iSetup);
//  fillPackedCands(iEvent, iSetup);

  edm::Handle<pat::PhotonCollection> photonHandle;
  iEvent.getByToken(phoIn_, photonHandle);
  const pat::PhotonCollection& photons{*photonHandle};
  
  // Original collection used for id-decisions
  edm::Handle<pat::PhotonCollection> photonOrgHandle;
  iEvent.getByToken(phoInOrg_, photonOrgHandle);
  // const pat::PhotonCollection& PhotonsOrg = *PhotonOrgHandle;
  
  edm::Handle<pat::PackedCandidateCollection> packedCandHandle;
  iEvent.getByToken(packedCandToken_, packedCandHandle);
  const pat::PackedCandidateCollection& packedCands{*packedCandHandle};

  // Electron conversions
  edm::Handle<reco::ConversionCollection> Conversions;
  iEvent.getByToken(conversionsToken_, Conversions);
  
  // Get the rho isolation co-efficient here
  edm::Handle<double> rhoHand_;
  iEvent.getByToken(rhoToken_, rhoHand_);
  rhoIso = *(rhoHand_.product());
  
  photonEts.clear();
  for (const auto& photon : photons) {
    double et{photon.et()};
    photonEts.emplace_back(et);
  }
  
  std::vector<size_t> etSortedIndex{IndexSorter<std::vector<float>>(photonEts, true)()};

  packedCandEts.clear();
  for ( const auto& cand : packedCands ) {
      double et{cand.et()};
      packedCandEts.emplace_back(et);
  }
  std::vector<size_t> etSortedPackedCands{IndexSorter<std::vector<float>>(packedCandEts, true)()};

  // Primary vertex
  edm::Handle<reco::VertexCollection> pvHandle;
  iEvent.getByToken(pvLabel_, pvHandle);
  
  numPho[ID] = 0;
  
  for (size_t ipho{0}; ipho < etSortedIndex.size() && numPho[ID] < numeric_cast<int>(NPHOTONSMAX); ++ipho) {
    size_t jpho{etSortedIndex[ipho]};
    const pat::Photon& pho{(*photonHandle)[jpho]};
    
    pat::PhotonRef refpho{photonOrgHandle,
	numeric_cast<unsigned int>(jpho)};

//    int photonConversionTag{-1};
    
    numPho[ID]++;
    
    photonSortedE[ID][numPho[ID] - 1] = pho.energy();
    photonSortedSigmaE[ID][numPho[ID] - 1] = pho.userFloat("ecalEnergyErrPostCorr");
    photonSortedET[ID][numPho[ID] - 1] = pho.et();
    photonSortedPhi[ID][numPho[ID] - 1] = pho.phi();
    photonSortedEta[ID][numPho[ID] - 1] = pho.eta();
    photonSortedTheta[ID][numPho[ID] - 1] = pho.theta();
    photonSortedPt[ID][numPho[ID] - 1] = pho.pt();
    photonSortedPx[ID][numPho[ID] - 1] = pho.px();
    photonSortedPy[ID][numPho[ID] - 1] = pho.py();
    photonSortedPz[ID][numPho[ID] - 1] = pho.pz();
    photonSortedCalibE[ID][numPho[ID] - 1] = pho.userFloat("ecalEnergyPostCorr");
    photonSortedCalibEt[ID][numPho[ID] - 1] = pho.et()*pho.userFloat("ecalEnergyPostCorr")/pho.energy();
    photonSortedSCE[ID][numPho[ID] - 1] = pho.superCluster()->energy();
    photonSortedSCRawE[ID][numPho[ID] - 1] = pho.superCluster()->rawEnergy();
    photonSortedESEnP1[ID][numPho[ID] - 1] = pho.superCluster()->preshowerEnergyPlane1();
    photonSortedESEnP2[ID][numPho[ID] - 1] = pho.superCluster()->preshowerEnergyPlane2();
    photonSortedSCEta[ID][numPho[ID] - 1] = pho.superCluster()->eta();
    photonSortedSCEtaWidth[ID][numPho[ID] - 1] = pho.superCluster()->etaWidth();
    photonSortedSCPhi[ID][numPho[ID] - 1] = pho.superCluster()->phi();
    photonSortedSCPhiWidth[ID][numPho[ID] - 1] = pho.superCluster()->phiWidth();
    photonSortedSCBrem[ID][numPho[ID] - 1] = (pho.superCluster()->phiWidth()/pho.superCluster()->etaWidth());
    photonSortedHasPixelSeed[ID][numPho[ID] - 1] = pho.hasPixelSeed();
    photonSortedEleVeto[ID][numPho[ID] - 1] = pho.passElectronVeto();
    photonSortedR9[ID][numPho[ID] - 1] = pho.r9();
    photonSortedHoverE[ID][numPho[ID] - 1] = pho.hadTowOverEm();
    photonSortedSigmaIEtaIEtaFull5x5[ID][numPho[ID] - 1] = pho.full5x5_sigmaIetaIeta();
    photonSortedSigmaIEtaIPhiFull5x5[ID][numPho[ID] - 1] = 0;
    photonSortedSigmaIPhiIPhiFull5x5[ID][numPho[ID] - 1] = 0;
    photonSortedE2x2Full5x5[ID][numPho[ID] - 1] = 0;
    photonSortedE5x5Full5x5[ID][numPho[ID] - 1] = pho.full5x5_e5x5();
    photonSortedR9Full5x5[ID][numPho[ID] - 1] = pho.full5x5_r9();
    photonSortedPFChIso[ID][numPho[ID] - 1] = pho.userFloat("phoChargedIsolation"); 
    photonSortedPFPhoIso[ID][numPho[ID] - 1] = pho.userFloat("phoPhotonIsolation");
    photonSortedPFNeuIso[ID][numPho[ID] - 1] = pho.userFloat("phoNeutralHadronIsolation");
    photonSortedPFChWorstIso[ID][numPho[ID] - 1] = pho.userFloat("phoWorstChargedIsolation");
    photonSortedMIPTotEnergy[ID][numPho[ID] - 1] = pho.mipTotEnergy();
    if (is2016rereco_) {
      photonSortedCutIdLoose[ID][numPho[ID] - 1] =
	pho.photonID("cutBasedPhotonID-Spring16-V2p2-loose");
      photonSortedCutIdMedium[ID][numPho[ID] - 1] =
	pho.photonID("cutBasedPhotonID-Spring16-V2p2-medium");
      photonSortedCutIdTight[ID][numPho[ID] - 1] =
	pho.photonID("cutBasedPhotonID-Spring16-V2p2-tight");
      photonSortedMvaIdWp80[ID][numPho[ID] - 1] =
	pho.photonID("mvaPhoID-Spring16-nonTrig-V1-wp80");
      photonSortedMvaIdWp90[ID][numPho[ID] - 1] =
	pho.photonID("mvaPhoID-Spring16-nonTrig-V1-wp90");
    }
    else {
      photonSortedCutIdLoose[ID][numPho[ID] - 1] =
	pho.photonID("cutBasedPhotonID-Fall17-94X-V1-loose");
      photonSortedCutIdMedium[ID][numPho[ID] - 1] =
	pho.photonID("cutBasedPhotonID-Fall17-94X-V1-medium");
      photonSortedCutIdTight[ID][numPho[ID] - 1] =
	pho.photonID("cutBasedPhotonID-Fall17-94X-V1-tight");
      photonSortedMvaIdWp80[ID][numPho[ID] - 1] =
	pho.photonID("mvaPhoID-RunIIFall17-v1-wp80");
      photonSortedMvaIdWp90[ID][numPho[ID] - 1] =
	pho.photonID("mvaPhoID-RunIIFall17-v1-wp90");
    }

    // Get index ref to packed cand collection
    unsigned int nSourcePackedCands = pho.numberOfSourceCandidatePtrs();
    int numPackedCands{0};
    int pfCandPtrIndex {-1};

    if ( nSourcePackedCands > 0 ) {
        for ( unsigned int j = 0; j < nSourcePackedCands; j++ ) {
            reco::CandidatePtr photonPtr = pho.sourceCandidatePtr(j);
            for (size_t iCand{0}; iCand < etSortedPackedCands.size() && numPackedCands < numeric_cast<int>(NPACKEDCANDSMAX); ++iCand) {
                size_t jCand{etSortedPackedCands[iCand]};
                const pat::PackedCandidate& packedCand{packedCands[jCand]};
                if (packedCand.pt() < 0.5) continue;

                reco::CandidatePtr pfCandPtr(packedCandHandle, jCand);
                if (pfCandPtr.isNonnull() && photonPtr == pfCandPtr) {
                    pfCandPtrIndex = numPackedCands;
                    break;
                } // end ptr comparison if ptrs match
                numPackedCands++;
            } // loop over entire packed pf cand collection
        } // loop over each assoc packed pf cand
    } // if there's at least one packed pf cand assoc with this PAT photon

    photonSortedNumSourceCandidates[ID][numMuo[ID] - 1] = nSourcePackedCands;
    photonSortedPackedCandIndex[ID][numMuo[ID] - 1] = pfCandPtrIndex;

    if (!pho.genParticleRef().isNull()) {
      genPhotonSortedPt[ID][numPho[ID] - 1] = pho.genPhoton()->pt();
      genPhotonSortedET[ID][numPho[ID] - 1] = pho.genPhoton()->et();
      genPhotonSortedEta[ID][numPho[ID] - 1] = pho.genPhoton()->eta();
      genPhotonSortedTheta[ID][numPho[ID] - 1] = pho.genPhoton()->theta();
      genPhotonSortedPhi[ID][numPho[ID] - 1] = pho.genPhoton()->phi();
      genPhotonSortedPx[ID][numPho[ID] - 1] = pho.genPhoton()->px();
      genPhotonSortedPy[ID][numPho[ID] - 1] = pho.genPhoton()->py();
      genPhotonSortedPz[ID][numPho[ID] - 1] = pho.genPhoton()->pz();
      genPhotonSortedCharge[ID][numPho[ID] - 1] = pho.genPhoton()->charge();
      genPhotonSortedPdgId[ID][numPho[ID] - 1] = pho.genPhoton()->pdgId();
      genPhotonSortedMotherId[ID][numPho[ID] - 1] = pho.genPhoton()->mother()->pdgId();
      genPhotonSortedIsPhoton[ID][numPho[ID] - 1] = pho.genPhoton()->isPhoton();
      genPhotonSortedIsConvertedPhoton[ID][numPho[ID] - 1] = pho.genPhoton()->isConvertedPhoton();
      genPhotonSortedIsJet[ID][numPho[ID] - 1] = pho.genPhoton()->isJet();
//      genPhotonSortedPromptDecayed[ID][numPho[ID] - 1] = pho.genPhoton()->isPromptDecayed();
//      genPhotonSortedPromptFinalState[ID][numPho[ID] - 1] = pho.genPhoton()->isPromptFinalState();
//      genPhotonSortedHardProcess[ID][numPho[ID] - 1] = pho.genPhoton()->isHardProcess();
//      genPhotonSortedPythiaSixStatusThree[ID][numPho[ID] - 1] = pho.genPhoton()->fromHardProcessBeforeFSR();
      genPhotonSortedScalarAncestor[ID][numPho[ID] - 1] = leptonScalarAncestor( pho.genPhoton() );
      genPhotonSortedDirectScalarAncestor[ID][numPho[ID] - 1] = leptonScalarAncestor( pho.genPhoton(), true, 22 );
    }
  }  
}

//////////////////////////////////////////////////////////////////////////////////////////////
void MakeTopologyNtupleMiniAOD::fillElectrons(const edm::Event& iEvent, const edm::EventSetup& iSetup, edm::EDGetTokenT<pat::ElectronCollection> eleIn_, const std::string& ID, edm::EDGetTokenT<pat::ElectronCollection> eleInOrg_) {

    // if (ran_eleloop_)
    // {
    //     return;
    // }
    // ran_eleloop_ = true;

    // info for 'default conversion finder
    edm::ESHandle<MagneticField> magneticField;
    iSetup.get<IdealMagneticFieldRecord>().get(magneticField);
    // over-ride the magnetic field supplied from the configfile:
    //    double realMagfield=magneticField_;
    //    if(magneticField->inTesla(GlobalPoint(0.,0.,0.)).z()>0) //Accept 0?
    //    realMagfield=magneticField->inTesla(GlobalPoint(0.,0.,0.)).z();
    //  needs beam spot
    //fillBeamSpot(iEvent, iSetup);
    // and tracks for photon conversion checks:
    //fillIsolatedTracks(iEvent, iSetup);
    //fillLostTracksCands(iEvent, iSetup);
    //fillPackedCands(iEvent, iSetup);

    // note that the fillJets() method needs electrons, due to the fact that we
    // do our own 'cross' cleaning
    edm::Handle<pat::ElectronCollection> electronHandle; // changed handle from pat::Electron to reco::GsfElectron
    iEvent.getByToken(eleIn_, electronHandle);
    const pat::ElectronCollection& electrons{*electronHandle};

    // Original collection used for id-decisions
    edm::Handle<pat::ElectronCollection> electronOrgHandle;
    iEvent.getByToken(eleInOrg_, electronOrgHandle);
    // const pat::ElectronCollection& electronsOrg = *electronOrgHandle;

    // Electron conversions
    edm::Handle<reco::ConversionCollection> Conversions;
    iEvent.getByToken(conversionsToken_, Conversions);

    // Get the rho isolation co-efficient here
    edm::Handle<double> rhoHand_;
    iEvent.getByToken(rhoToken_, rhoHand_);
    rhoIso = *(rhoHand_.product());

    edm::Handle<pat::PackedCandidateCollection> packedCandHandle;
    iEvent.getByToken(packedCandToken_, packedCandHandle);
    const pat::PackedCandidateCollection& packedCands{*packedCandHandle};

    electronEts.clear();
    for (const auto& electron : electrons) {
        double et{electron.et()};
        electronEts.emplace_back(et);
    }
    // if (ID == "PF")
    // {
    //     std::cout << "N PF ele: " << electronEts.size() << std::endl;
    // }
    std::vector<size_t> etSortedIndex{IndexSorter<std::vector<float>>(electronEts, true)()};

    packedCandEts.clear();
    for ( const auto& cand : packedCands ) {
        double et{cand.et()};
        packedCandEts.emplace_back(et);
    }
    std::vector<size_t> etSortedPackedCands{IndexSorter<std::vector<float>>(packedCandEts, true)()};

    // Primary vertex
    edm::Handle<reco::VertexCollection> pvHandle;
    iEvent.getByToken(pvLabel_, pvHandle);

    // std::cout << "now starting loop" << std::std::endl;
    // now loop again, in the correct order
    numEle[ID] = 0;

    for (size_t iele{0}; iele < etSortedIndex.size() && numEle[ID] < numeric_cast<int>(NELECTRONSMAX); ++iele) {
        size_t jele{etSortedIndex[iele]};
        // const pat::Electron& ele = electrons[jele];
        const pat::Electron& ele{(*electronHandle)[jele]};

        pat::ElectronRef refel{electronOrgHandle, numeric_cast<unsigned int>(jele)};

//        int photonConversionTag{-1};
        numEle[ID]++;

        // Impact param significance
        if (pvHandle.isValid()) {
            std::vector<reco::Vertex> pv{*pvHandle};

            edm::ESHandle<TransientTrackBuilder> trackBuilder;
            iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder", trackBuilder);
            reco::TransientTrack eleTransient{trackBuilder->build(ele.gsfTrack())};

            std::pair<bool, Measurement1D> eleImpactTrans{IPTools::absoluteTransverseImpactParameter(eleTransient, pv[0])};
            std::pair<bool, Measurement1D> eleImpact3D{IPTools::absoluteImpactParameter3D(eleTransient, pv[0])};

            if (eleImpactTrans.first) {
                electronSortedImpactTransDist[ID][numEle[ID] - 1] = eleImpactTrans.second.value();
                electronSortedImpactTransError[ID][numEle[ID] - 1] = eleImpactTrans.second.error();
                electronSortedImpactTransSignificance[ID][numEle[ID] - 1] = eleImpactTrans.second.significance();
            }
            if (eleImpact3D.first) {
                electronSortedImpact3DDist[ID][numEle[ID] - 1] = eleImpact3D.second.value();
                electronSortedImpact3DError[ID][numEle[ID] - 1] = eleImpact3D.second.error();
                electronSortedImpact3DSignificance[ID][numEle[ID] - 1] = eleImpact3D.second.significance();
            }
        }

        const double eleCorrScale{ele.userFloat("ecalTrkEnergyPostCorr") / ele.p4().energy()};
        const TLorentzVector eleCorr{ele.px() * eleCorrScale, ele.py() * eleCorrScale, ele.pz() * eleCorrScale, ele.energy() * eleCorrScale};

        electronSortedE[ID][numEle[ID] - 1] = eleCorr.E();
        electronSortedEt[ID][numEle[ID] - 1] = eleCorr.Et();
        electronSortedEta[ID][numEle[ID] - 1] = eleCorr.Eta();
        electronSortedPt[ID][numEle[ID] - 1] = eleCorr.Pt();
        electronSortedTheta[ID][numEle[ID] - 1] = eleCorr.Theta();
        electronSortedPhi[ID][numEle[ID] - 1] = eleCorr.Phi();
        electronSortedPx[ID][numEle[ID] - 1] = eleCorr.Px();
        electronSortedPy[ID][numEle[ID] - 1] = eleCorr.Py();
        electronSortedPz[ID][numEle[ID] - 1] = eleCorr.Pz();
        electronSortedCharge[ID][numEle[ID] - 1] = ele.charge();

        if (is2016rereco_) {
            electronSortedCutIdVeto[ID][numEle[ID] - 1] =
                ele.electronID("cutBasedElectronID-Summer16-80X-V1-veto");
            electronSortedCutIdLoose[ID][numEle[ID] - 1] =
                ele.electronID("cutBasedElectronID-Summer16-80X-V1-loose");
            electronSortedCutIdMedium[ID][numEle[ID] - 1] =
                ele.electronID("cutBasedElectronID-Summer16-80X-V1-medium");
            electronSortedCutIdTight[ID][numEle[ID] - 1] =
                ele.electronID("cutBasedElectronID-Summer16-80X-V1-tight");
            electronSortedMvaIdWp80[ID][numEle[ID] - 1] =
                ele.electronID("mvaEleID-Spring16-GeneralPurpose-V1-wp80");
            electronSortedMvaIdWp90[ID][numEle[ID] - 1] =
                ele.electronID("mvaEleID-Spring16-GeneralPurpose-V1-wp90");
            electronSortedMvaIdWpLoose[ID][numEle[ID] - 1] =
                ele.electronID("mvaEleID-Spring16-GeneralPurpose-V1-wp90");
        }
        else
        {
            electronSortedCutIdVeto[ID][numEle[ID] - 1] =
                ele.electronID("cutBasedElectronID-Fall17-94X-V1-veto");
            electronSortedCutIdLoose[ID][numEle[ID] - 1] =
                ele.electronID("cutBasedElectronID-Fall17-94X-V1-loose");
            electronSortedCutIdMedium[ID][numEle[ID] - 1] =
                ele.electronID("cutBasedElectronID-Fall17-94X-V1-medium");
            electronSortedCutIdTight[ID][numEle[ID] - 1] =
                ele.electronID("cutBasedElectronID-Fall17-94X-V1-tight");
            electronSortedMvaIdWp80[ID][numEle[ID] - 1] =
                ele.electronID("mvaEleID-Fall17-iso-V1-wp80");
            electronSortedMvaIdWp90[ID][numEle[ID] - 1] =
                ele.electronID("mvaEleID-Fall17-iso-V1-wp90");
            electronSortedMvaIdWpLoose[ID][numEle[ID] - 1] =
                ele.electronID("mvaEleID-Fall17-iso-V1-wpLoose");
        }
        electronSortedChargedHadronIso[ID][numEle[ID] - 1] =
            ele.chargedHadronIso();
        electronSortedNeutralHadronIso[ID][numEle[ID] - 1] =
            ele.neutralHadronIso();
        electronSortedPhotonIso[ID][numEle[ID] - 1] = ele.photonIso();

        electronSortedTrackPt[ID][numEle[ID] - 1] = ele.gsfTrack()->pt();
        electronSortedTrackEta[ID][numEle[ID] - 1] = ele.gsfTrack()->eta();
        electronSortedTrackPhi[ID][numEle[ID] - 1] = ele.gsfTrack()->phi();
        electronSortedTrackChi2[ID][numEle[ID] - 1] = ele.gsfTrack()->chi2();
        electronSortedTrackNDOF[ID][numEle[ID] - 1] = ele.gsfTrack()->ndof();
        electronSortedTrackD0[ID][numEle[ID] - 1] = ele.gsfTrack()->d0();
        electronSortedDBBeamSpotCorrectedTrackD0[ID][numEle[ID] - 1] = ele.dB();
        // electronSortedDBInnerTrackD0[ID][numEle[ID] - 1] = -1. * (ele.innerTrack()->dxy(beamSpotPoint_));
        electronSortedBeamSpotCorrectedTrackD0[ID][numEle[ID] - 1] = -1. * (ele.gsfTrack()->dxy(beamSpotPoint_));
        electronSortedTrackDz[ID][numEle[ID] - 1] = ele.gsfTrack()->dz();
        electronSortedTrackD0PV[ID][numEle[ID] - 1] = ele.gsfTrack()->dxy(vertexPoint_);
        electronSortedTrackDZPV[ID][numEle[ID] - 1] = ele.gsfTrack()->dz(vertexPoint_);
        electronSortedVtxZ[ID][numEle[ID] - 1] = ele.vertex().z();

        electronSortedIsGsf[ID][numEle[ID] - 1] = ele.gsfTrack().isNonnull();
        electronSortedGsfPx[ID][numEle[ID] - 1] = ele.ecalDrivenMomentum().px();
        electronSortedGsfPy[ID][numEle[ID] - 1] = ele.ecalDrivenMomentum().py();
        electronSortedGsfPz[ID][numEle[ID] - 1] = ele.ecalDrivenMomentum().pz();
        electronSortedGsfE[ID][numEle[ID] - 1] =  ele.ecalDrivenMomentum().energy();
        electronSortedEcalEnergy[ID][numEle[ID] - 1] = ele.ecalEnergy();

        electronSortedSuperClusterEta[ID][numEle[ID] - 1] =
            ele.superCluster()->eta();
        electronSortedSuperClusterE[ID][numEle[ID] - 1] =
            ele.superCluster()->energy();
        electronSortedSuperClusterPhi[ID][numEle[ID] - 1] =
            ele.superCluster()->phi();
        electronSortedSuperClusterEoverP[ID][numEle[ID] - 1] =
            ele.eSuperClusterOverP();
        electronSortedSuperClusterSigmaEtaEta[ID][numEle[ID] - 1] =
            ele.scSigmaEtaEta();
        electronSortedSuperClusterE1x5[ID][numEle[ID] - 1] = ele.scE1x5();
        electronSortedSuperClusterE2x5max[ID][numEle[ID] - 1] = ele.scE2x5Max();
        electronSortedSuperClusterE5x5[ID][numEle[ID] - 1] = ele.scE5x5();
        electronSortedSuperClusterSigmaIEtaIEta[ID][numEle[ID] - 1] =
            ele.scSigmaIEtaIEta();
        electronSortedSuperClusterSigmaIEtaIEta5x5[ID][numEle[ID] - 1] =
            ele.full5x5_sigmaIetaIeta();

        electronSortedTrackIso04[ID][numEle[ID] - 1] =
            ele.dr04TkSumPt(); // trackIso();
        electronSortedECalIso04[ID][numEle[ID] - 1] =
            ele.dr04EcalRecHitSumEt(); // ecalIso();
        electronSortedTrackIso03[ID][numEle[ID] - 1] =
            ele.dr03TkSumPt(); // trackIso();
        electronSortedECalIso03[ID][numEle[ID] - 1] =
            ele.dr03EcalRecHitSumEt(); // ecalIso();
        electronSortedHCalIso03[ID][numEle[ID] - 1] =
            ele.dr03HcalTowerSumEt(); // ele.hcalIso();
        // electronSortedECalIsoDeposit[ID][numEle[ID] - 1] =
        //     ele.ecalIsoDeposit()->candEnergy();
        // electronSortedHCalIsoDeposit[ID][numEle[ID] - 1] =
        //     ele.hcalIsoDeposit()->candEnergy();
        electronSortedCaloIso[ID][numEle[ID] - 1] = ele.caloIso();

        const reco::GsfElectron::PflowIsolationVariables& pfIso{
            ele.pfIsolationVariables()};

        // calculate comRelIso:
        electronSortedComRelIso[ID][numEle[ID] - 1] =
            electronSortedTrackIso03[ID][numEle[ID] - 1];
        electronSortedComRelIso[ID][numEle[ID] - 1] +=
            electronSortedECalIso03[ID][numEle[ID] - 1];
        electronSortedComRelIso[ID][numEle[ID] - 1] +=
            electronSortedHCalIso03[ID][numEle[ID] - 1];
        electronSortedComRelIso[ID][numEle[ID] - 1] /=
            electronSortedEt[ID][numEle[ID] - 1];
        electronSortedChHadIso[ID][numEle[ID] - 1] = pfIso.sumChargedHadronPt;
        electronSortedNtHadIso[ID][numEle[ID] - 1] = pfIso.sumNeutralHadronEt;
        electronSortedGammaIso[ID][numEle[ID] - 1] = pfIso.sumPhotonEt;
        electronSortedComRelIsodBeta[ID][numEle[ID] - 1] = (pfIso.sumChargedHadronPt + std::max(0.0, pfIso.sumPhotonEt - 0.5 * pfIso.sumPUPt)) / ele.pt();

        const float AEff03{effectiveAreaInfo_.getEffectiveArea(std::abs(ele.superCluster()->eta()))};
        electronSortedAEff03[ID][numEle[ID] - 1] = AEff03;
        electronSortedRhoIso[ID][numEle[ID] - 1] = rhoIso;

        const double combrelisorho{(pfIso.sumChargedHadronPt + std::max(0.0, pfIso.sumNeutralHadronEt + pfIso.sumPhotonEt - rhoIso * AEff03)) / ele.pt()};
        electronSortedComRelIsoRho[ID][numEle[ID] - 1] = combrelisorho;
        // (ele.trackIso() + ele.ecalIso() + ele.hcalIso()) / ele.et();

        // pass electron to photonConversionVeto and see if it comes from photon
        // conversion

        electronSortedMissingInnerLayers[ID][numEle[ID] - 1] =
            ele.gsfTrack()->hitPattern().numberOfLostTrackerHits(
                reco::HitPattern::MISSING_INNER_HITS);

        electronSortedHoverE[ID][numEle[ID] - 1] = ele.hadronicOverEm();
        electronSortedDeltaPhiSC[ID][numEle[ID] - 1] =
            ele.deltaPhiSuperClusterTrackAtVtx();
        electronSortedDeltaEtaSC[ID][numEle[ID] - 1] =
            ele.deltaEtaSuperClusterTrackAtVtx();
        electronSortedDeltaEtaSeedSC[ID][numEle[ID] - 1] =
            (ele.superCluster().isNonnull() && ele.superCluster()->seed().isNonnull()
                 ? ele.deltaEtaSuperClusterTrackAtVtx() - ele.superCluster()->eta()  + ele.superCluster()->seed()->eta()
                 : std::numeric_limits<float>::max());
        electronSortedIsBarrel[ID][numEle[ID] - 1] = ele.isEB();

        // calculate dcot and dist using the egamma code...
        // use fixed magnetic field for now:

        // ELECTRON CONVERSIONS

        electronSortedPhotonConversionTag[ID][numEle[ID] - 1] =
            ConversionTools::hasMatchedConversion(
                ele, Conversions, beamSpotPoint_);
        electronSortedPhotonConversionDist[ID][numEle[ID] - 1] = ele.convDist();
        electronSortedPhotonConversionDcot[ID][numEle[ID] - 1] = ele.convDcot();
        electronSortedPhotonConversionVeto[ID][numEle[ID] - 1] = ele.passConversionVeto();

        if (check_triggers_) {
            std::vector<pat::TriggerObjectStandAlone> matchedtriggers{ele.triggerObjectMatches()};

            if (false) { // Debug verboose info if set to 1.
                for (auto& matchedtrigger : matchedtriggers) {
                    for (auto it{matchedtrigger.filterLabels().begin()},
                         it_end = matchedtrigger.filterLabels().end();
                         it != it_end;
                         it++) {
                        // std::cout << *it << std::endl;
                    }
                }
            }
            electronSortedTriggerMatch[ID][numEle[ID] - 1] = matchedtriggers.size(); // very coarse, probably want to select on a filter.
        }

        // Get index ref to packed cand collection
        unsigned int nSourcePackedCands = ele.numberOfSourceCandidatePtrs();
        int numPackedCands{0}; 
        int pfCandPtrIndex {-1};

        if ( nSourcePackedCands > 0 ) {
            for ( unsigned int j = 0; j < nSourcePackedCands; j++ ) {
                reco::CandidatePtr electronPtr = ele.sourceCandidatePtr(j);
                for (size_t iCand{0}; iCand < etSortedPackedCands.size() && numPackedCands < numeric_cast<int>(NPACKEDCANDSMAX); ++iCand) {
                    size_t jCand{etSortedPackedCands[iCand]};
                    const pat::PackedCandidate& packedCand{packedCands[jCand]};
                    if (packedCand.pt() < 0.5) continue;

                    reco::CandidatePtr pfCandPtr(packedCandHandle, jCand);
                    if (pfCandPtr.isNonnull() && electronPtr == pfCandPtr) {
                        pfCandPtrIndex = numPackedCands;
                        break;
                    } // end ptr comparison if ptrs match
                    numPackedCands++;
                } // loop over entire packed pf cand collection
            } // loop over each assoc packed pf cand
        } // if there's at least one packed pf cand assoc with this PAT electron

        electronSortedNumSourceCandidates[ID][numEle[ID] - 1] = nSourcePackedCands;
        electronSortedPackedCandIndex[ID][numEle[ID] - 1] = pfCandPtrIndex;

        // if(ele.genParticleRef().ref().isValid()){
        if (!ele.genParticleRef().isNull())  {
            genElectronSortedPt[ID][numEle[ID] - 1] = ele.genLepton()->pt();
            genElectronSortedEt[ID][numEle[ID] - 1] = ele.genLepton()->et();
            genElectronSortedEta[ID][numEle[ID] - 1] = ele.genLepton()->eta();
            genElectronSortedTheta[ID][numEle[ID] - 1] = ele.genLepton()->theta();
            genElectronSortedPhi[ID][numEle[ID] - 1] = ele.genLepton()->phi();
            genElectronSortedPx[ID][numEle[ID] - 1] = ele.genLepton()->px();
            genElectronSortedPy[ID][numEle[ID] - 1] = ele.genLepton()->py();
            genElectronSortedPz[ID][numEle[ID] - 1] = ele.genLepton()->pz();
            genElectronSortedCharge[ID][numEle[ID] - 1] = ele.genLepton()->charge();
            genElectronSortedPdgId[ID][numEle[ID] - 1] = ele.genLepton()->pdgId();
            genElectronSortedMotherId[ID][numEle[ID] - 1] = ele.genLepton()->mother()->pdgId();
            genElectronSortedPromptDecayed[ID][numEle[ID] - 1] = ele.genLepton()->isPromptDecayed();
            genElectronSortedPromptFinalState[ID][numEle[ID] - 1] = ele.genLepton()->isPromptFinalState();
            genElectronSortedHardProcess[ID][numEle[ID] - 1] = ele.genLepton()->isHardProcess();
            genElectronSortedPythiaSixStatusThree[ID][numEle[ID] - 1] = ele.genLepton()->fromHardProcessBeforeFSR();
            genElectronSortedScalarAncestor[ID][numEle[ID] - 1] = leptonScalarAncestor( ele.genLepton() );
            genElectronSortedDirectScalarAncestor[ID][numEle[ID] - 1] = leptonScalarAncestor( ele.genLepton(), true, 11 );

        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
void MakeTopologyNtupleMiniAOD::fillMuons(const edm::Event& iEvent, const edm::EventSetup& iSetup, edm::EDGetTokenT<pat::MuonCollection> muIn_, const std::string& ID) {

    if (debugMode_) std::cout << "fillMuons" << std::endl;

    // ran_muonloop_ = true;
    edm::Handle<pat::MuonCollection> muonHandle;
    iEvent.getByToken(muIn_, muonHandle);
    const pat::MuonCollection& muons {*muonHandle};

    edm::Handle<pat::PackedCandidateCollection> packedCandHandle;
    iEvent.getByToken(packedCandToken_, packedCandHandle);
    const pat::PackedCandidateCollection& packedCands{*packedCandHandle};

    edm::ESHandle<MagneticField> magneticFieldHandle;
    iSetup.get<IdealMagneticFieldRecord>().get(magneticFieldHandle);
    const MagneticField* theMagneticField = magneticFieldHandle.product();

    // Primary vertex
    edm::Handle<reco::VertexCollection> pvHandle;
    iEvent.getByToken(pvLabel_, pvHandle);

    //fillBeamSpot(iEvent, iSetup);
    //fillIsolatedTracks(iEvent, iSetup);
    //fillLostTracksCands(iEvent, iSetup);
    //fillPackedCands(iEvent, iSetup);

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

    packedCandEts.clear();
    for ( const auto& cand : packedCands ) {
        double et{cand.et()};
        packedCandEts.emplace_back(et);
    }
    std::vector<size_t> etSortedPackedCands{IndexSorter<std::vector<float>>(packedCandEts, true)()};

    // muon tracks
    // vectors to store muon track refs and indices for later
    muonTkIndices.clear();
    muonTrackRefs.clear();
    muonTransTracks.clear();

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
        muonSortedPfIsoVeryLoose[ID][numMuo[ID] - 1] = muo.passed(reco::Muon::PFIsoVeryLoose);
        muonSortedPfIsoLoose[ID][numMuo[ID] - 1] = muo.passed(reco::Muon::PFIsoLoose);
        muonSortedPfIsoMedium[ID][numMuo[ID] - 1] = muo.passed(reco::Muon::PFIsoMedium);
        muonSortedPfIsoTight[ID][numMuo[ID] - 1] = muo.passed(reco::Muon::PFIsoTight);
        muonSortedPfIsoVeryTight[ID][numMuo[ID] - 1] = muo.passed(reco::Muon::PFIsoVeryTight);
        muonSortedTkIsoLoose[ID][numMuo[ID] - 1] = muo.passed(reco::Muon::TkIsoLoose);
        muonSortedTkIsoTight[ID][numMuo[ID] - 1] = muo.passed(reco::Muon::TkIsoTight);
        muonSortedMvaLoose[ID][numMuo[ID] - 1] = muo.passed(reco::Muon::MvaLoose);
        muonSortedMvaMedium[ID][numMuo[ID] - 1] = muo.passed(reco::Muon::MvaMedium);
        muonSortedMvaTight[ID][numMuo[ID] - 1] = muo.passed(reco::Muon::MvaTight);

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

            // Store muon track refs for post muon loop tracking analysis
            muonTkIndices.push_back( numMuo[ID] - 1 );
            muonTrackRefs.push_back( muo.innerTrack() );
            reco::TransientTrack tmpTransient( *(muo.innerTrack()), theMagneticField);
            muonTransTracks.push_back( std::move( tmpTransient ) );
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
        muonSortedComRelIso[ID][numMuo[ID] - 1] /= muonSortedPt[ID][numMuo[ID] - 1];
        muonSortedNumChambers[ID][numMuo[ID] - 1] = muo.numberOfChambers();
        muonSortedNumMatches[ID][numMuo[ID] - 1] = muo.numberOfMatches();
        muonSortedIsPFMuon[ID][numMuo[ID] - 1] = muo.isPFMuon();

	// Get index ref to packed cand collection
        unsigned int nSourcePackedCands = muo.numberOfSourceCandidatePtrs();
        int numPackedCands{0};
        int pfCandPtrIndex {-1};

        if ( nSourcePackedCands > 0 ) {
            for ( unsigned int j = 0; j < nSourcePackedCands; j++ ) {
                reco::CandidatePtr muonPtr = muo.sourceCandidatePtr(j);
                for (size_t iCand{0}; iCand < etSortedPackedCands.size() && numPackedCands < numeric_cast<int>(NPACKEDCANDSMAX); ++iCand) {
                    size_t jCand{etSortedPackedCands[iCand]};
                    const pat::PackedCandidate& packedCand{packedCands[jCand]};
                    if (packedCand.pt() < 0.5) continue;

                    reco::CandidatePtr pfCandPtr(packedCandHandle, jCand);
                    if (pfCandPtr.isNonnull() && muonPtr == pfCandPtr) {
                        pfCandPtrIndex = numPackedCands;
                        break;
                    } // end ptr comparison if ptrs match
                    numPackedCands++;
                } // loop over entire packed pf cand collection
            } // loop over each assoc packed pf cand
        } // if there's at least one packed pf cand assoc with this PAT electron

        muonSortedNumSourceCandidates[ID][numMuo[ID] - 1] = nSourcePackedCands;
        muonSortedPackedCandIndex[ID][numMuo[ID] - 1] = pfCandPtrIndex;
	
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

            genMuonSortedScalarAncestor[ID][numMuo[ID] - 1] = leptonScalarAncestor( muo.genLepton() );
            genMuonSortedDirectScalarAncestor[ID][numMuo[ID] - 1] = leptonScalarAncestor( muo.genLepton(), true, 13);

        } // End gen muon loop

    }

    numMuonTrackPairs[ID] = 0;

    // loop over muon tracks
    for (unsigned int trdx1 = 0; trdx1 < muonTrackRefs.size() && numMuonTrackPairs[ID] < numeric_cast<int>(NMUONTKPAIRMAX); ++trdx1) {
        for (unsigned int trdx2 = trdx1 + 1; trdx2 < muonTrackRefs.size() && numMuonTrackPairs[ID] < numeric_cast<int>(NMUONTKPAIRMAX); ++trdx2) {

            reco::TrackRef trackRef1;
            reco::TrackRef trackRef2;
            reco::TransientTrack* transTkPtr1 = nullptr;
            reco::TransientTrack* transTkPtr2 = nullptr;

            trackRef1 = muonTrackRefs[trdx1];
            trackRef2 = muonTrackRefs[trdx2];
            transTkPtr1 = &muonTransTracks[trdx1];
            transTkPtr2 = &muonTransTracks[trdx2];

            // check tracks are opposite charges
            if ( trackRef1->charge() * trackRef2->charge() >= 0 ) continue;

            // measure distance between tracks at their closest approach

            //these two variables are needed to 'pin' the temporary value returned to the stack in order to keep both States from pointing to destructed objects
            auto const& impact1 = transTkPtr1->impactPointTSCP();
            auto const& impact2 = transTkPtr2->impactPointTSCP();
            if (!impact1.isValid() || !impact2.isValid()) continue;
            FreeTrajectoryState const& state1 = impact1.theState();
            FreeTrajectoryState const& state2 = impact2.theState();

            ClosestApproachInRPhi cApp;
            cApp.calculate(state1, state2);
            if (!cApp.status()) continue;

            float dca = std::abs(cApp.distance());

            // the POCA should at least be in the sensitive volume
            GlobalPoint cxPt = cApp.crossingPoint();
            if ((cxPt.x() * cxPt.x() + cxPt.y() * cxPt.y()) > 120. * 120. || std::abs(cxPt.z()) > 300.) continue;

            TrajectoryStateClosestToPoint const& TSCP1 = transTkPtr1->trajectoryStateClosestToPoint(cxPt);
            TrajectoryStateClosestToPoint const& TSCP2 = transTkPtr2->trajectoryStateClosestToPoint(cxPt);
            if (!TSCP1.isValid() || !TSCP2.isValid()) continue;

            // Are tracks in the same quadrant?
            if ( TSCP1.momentum().dot(TSCP2.momentum()) < 0 ) continue;

            // Fill the vector of TransientTracks to send to KVF
            std::vector<reco::TransientTrack> tmpTransTracks;
            tmpTransTracks.reserve(2);
            tmpTransTracks.push_back(*transTkPtr1);
            tmpTransTracks.push_back(*transTkPtr2);

            // create the vertex fitter object and vertex the tracks
            KalmanVertexFitter theKalmanFitter(true); // KalmanVertexFitter(bool useSmoothing = false);
            TransientVertex theRecoVertex  = theKalmanFitter.vertex(tmpTransTracks);
            if (!theRecoVertex.isValid()) continue;

            // do stuff with new vertices

            reco::Vertex theVtx = theRecoVertex;
            GlobalPoint vtxPos(theVtx.x(), theVtx.y(), theVtx.z());

            // 2D decay significance
            ROOT::Math::SMatrix<double, 3, 3, ROOT::Math::MatRepSym<double, 3>> totalCov = vertexPrimary_->covariance() + theVtx.covariance();
            ROOT::Math::SVector<double, 3>  distVecXY(vtxPos.x() - vertexPrimary_->position().x(), vtxPos.y() - vertexPrimary_->position().y(), 0.);
            double distMagXY = ROOT::Math::Mag(distVecXY);
            double sigmaDistMagXY = sqrt(ROOT::Math::Similarity(totalCov, distVecXY)) / distMagXY;

            // 3D decay significance
            ROOT::Math::SVector<double, 3>  distVecXYZ(vtxPos.x() - vertexPrimary_->position().x(), vtxPos.y() - vertexPrimary_->position().y(), vtxPos.z() - vertexPrimary_->position().z());
            double distMagXYZ = ROOT::Math::Mag(distVecXYZ);
            double sigmaDistMagXYZ = sqrt(ROOT::Math::Similarity(totalCov, distVecXYZ)) / distMagXYZ;

            // do stuff with refit tracks

            std::unique_ptr<TrajectoryStateClosestToPoint> traj1;
            std::unique_ptr<TrajectoryStateClosestToPoint> traj2;
            std::vector<reco::TransientTrack> theRefTracks = theRecoVertex.refittedTracks();

            if ( theRefTracks.size() > 1 ) {
                reco::TransientTrack* transTk1 = nullptr;
                reco::TransientTrack* transTk2 = nullptr;

                transTk1 = &theRefTracks[0];
                transTk2 = &theRefTracks[1];

                if (transTk1 == nullptr || transTk2 == nullptr) continue;
                traj1 = std::make_unique<TrajectoryStateClosestToPoint>(transTk1->trajectoryStateClosestToPoint(vtxPos));
                traj2 = std::make_unique<TrajectoryStateClosestToPoint>(transTk2->trajectoryStateClosestToPoint(vtxPos));
            }
            else {
                traj1 = std::make_unique<TrajectoryStateClosestToPoint>(transTkPtr1->trajectoryStateClosestToPoint(vtxPos));
                traj2 = std::make_unique<TrajectoryStateClosestToPoint>(transTkPtr2->trajectoryStateClosestToPoint(vtxPos));
            }

            if (traj1.get() == nullptr || traj2.get() == nullptr || !traj1->isValid() || !traj2->isValid()) continue;

            GlobalVector P1(traj1->momentum());
            GlobalVector P2(traj2->momentum());
            GlobalVector totalP(P1 + P2);

            // 2D pointing angle
            double dx = theVtx.x() - vertexPrimary_->position().x();
            double dy = theVtx.y() - vertexPrimary_->position().y();
            double px = totalP.x();
            double py = totalP.y();
            double angleXY = (dx * px + dy * py) / (sqrt(dx * dx + dy * dy) * sqrt(px * px + py * py));

            // 3D pointing angle
            double dz = theVtx.z() - vertexPrimary_->position().z();
            double pz = totalP.z();
            double angleXYZ = (dx * px + dy * py + dz * pz) / (sqrt(dx * dx + dy * dy + dz * dz) * sqrt(px * px + py * py + pz * pz));

            reco::Particle::Point vtx(theVtx.x(), theVtx.y(), theVtx.z());
           const reco::Vertex::CovarianceMatrix vtxCov(theVtx.covariance());

            numMuonTrackPairs[ID]++;

            muonTkPairSortedIndex1[ID][numMuonTrackPairs[ID] - 1] = muonTkIndices[trdx1];
            muonTkPairSortedIndex2[ID][numMuonTrackPairs[ID] - 1] = muonTkIndices[trdx2];

            muonTkPairSortedTkVtxPx[ID][numMuonTrackPairs[ID] - 1] = px;
            muonTkPairSortedTkVtxPy[ID][numMuonTrackPairs[ID] - 1] = py;
            muonTkPairSortedTkVtxPz[ID][numMuonTrackPairs[ID] - 1] = pz;
            muonTkPairSortedTkVtxP2[ID][numMuonTrackPairs[ID] - 1] = totalP.mag2();
            muonTkPairSortedTkVx[ID][numMuonTrackPairs[ID] - 1] = theVtx.x();
            muonTkPairSortedTkVy[ID][numMuonTrackPairs[ID] - 1] = theVtx.y();
            muonTkPairSortedTkVz[ID][numMuonTrackPairs[ID] - 1] = theVtx.z();
            muonTkPairSortedTkVtxCov00[ID][numMuonTrackPairs[ID] - 1] = vtxCov(0,0);
            muonTkPairSortedTkVtxCov01[ID][numMuonTrackPairs[ID] - 1] = vtxCov(0,1);
            muonTkPairSortedTkVtxCov02[ID][numMuonTrackPairs[ID] - 1] = vtxCov(0,2);
            muonTkPairSortedTkVtxCov10[ID][numMuonTrackPairs[ID] - 1] = vtxCov(1,0);
            muonTkPairSortedTkVtxCov11[ID][numMuonTrackPairs[ID] - 1] = vtxCov(1,1);
            muonTkPairSortedTkVtxCov12[ID][numMuonTrackPairs[ID] - 1] = vtxCov(1,2);
            muonTkPairSortedTkVtxCov20[ID][numMuonTrackPairs[ID] - 1] = vtxCov(2,0);
            muonTkPairSortedTkVtxCov21[ID][numMuonTrackPairs[ID] - 1] = vtxCov(2,1);
            muonTkPairSortedTkVtxCov22[ID][numMuonTrackPairs[ID] - 1] = vtxCov(2,2);
            muonTkPairSortedTkVtxChi2[ID][numMuonTrackPairs[ID] - 1] = theVtx.chi2();
            muonTkPairSortedTkVtxNdof[ID][numMuonTrackPairs[ID] - 1] = theVtx.ndof();
            muonTkPairSortedTkVtxTime[ID][numMuonTrackPairs[ID] - 1] = theVtx.t();
            muonTkPairSortedTkVtxTimeError[ID][numMuonTrackPairs[ID] - 1] = theVtx.tError();
            muonTkPairSortedTkVtxAngleXY[ID][numMuonTrackPairs[ID] - 1] = angleXY;
            muonTkPairSortedTkVtxDistMagXY[ID][numMuonTrackPairs[ID] - 1] = distMagXY;
            muonTkPairSortedTkVtxDistMagXYSigma[ID][numMuonTrackPairs[ID] - 1] = sigmaDistMagXY;
            muonTkPairSortedTkVtxAngleXYZ[ID][numMuonTrackPairs[ID] - 1] = angleXYZ; 
            muonTkPairSortedTkVtxDistMagXYZ[ID][numMuonTrackPairs[ID] - 1] = distMagXYZ;
            muonTkPairSortedTkVtxDistMagXYZSigma[ID][numMuonTrackPairs[ID] - 1] = sigmaDistMagXYZ;

            muonTkPairSortedTk1Pt[ID][numMuonTrackPairs[ID] - 1] = traj1->pt();
            muonTkPairSortedTk1Px[ID][numMuonTrackPairs[ID] - 1] = P1.x();
            muonTkPairSortedTk1Py[ID][numMuonTrackPairs[ID] - 1] = P1.y();
            muonTkPairSortedTk1Pz[ID][numMuonTrackPairs[ID] - 1] = P1.z();
            muonTkPairSortedTk1P2[ID][numMuonTrackPairs[ID] - 1] = P1.mag2();
            muonTkPairSortedTk1Eta[ID][numMuonTrackPairs[ID] - 1] = P1.eta();
            muonTkPairSortedTk1Phi[ID][numMuonTrackPairs[ID] - 1] = P1.phi();
            muonTkPairSortedTk1Charge[ID][numMuonTrackPairs[ID] - 1] = traj1->charge();
            float tk1Chi2{0.}, tk1Ndof{0.};
            if ( theRefTracks.size() > 1 ) {
                tk1Chi2 = theRefTracks[0].chi2();
                tk1Ndof = theRefTracks[0].ndof();
            }
            muonTkPairSortedTk1Chi2[ID][numMuonTrackPairs[ID] - 1] = tk1Chi2;
            muonTkPairSortedTk1Ndof[ID][numMuonTrackPairs[ID] - 1] = tk1Ndof;

            muonTkPairSortedTk2Pt[ID][numMuonTrackPairs[ID] - 1] = traj2->pt();
            muonTkPairSortedTk2Px[ID][numMuonTrackPairs[ID] - 1] = P2.x();
            muonTkPairSortedTk2Py[ID][numMuonTrackPairs[ID] - 1] = P2.y();
            muonTkPairSortedTk2Pz[ID][numMuonTrackPairs[ID] - 1] = P2.z();
            muonTkPairSortedTk2P2[ID][numMuonTrackPairs[ID] - 1] = P2.mag2();
            muonTkPairSortedTk2Eta[ID][numMuonTrackPairs[ID] - 1] = P2.eta();
            muonTkPairSortedTk2Phi[ID][numMuonTrackPairs[ID] - 1] = P2.phi();
            muonTkPairSortedTk2Charge[ID][numMuonTrackPairs[ID] - 1] = traj2->charge();
            float tk2Chi2{0.}, tk2Ndof{0.};
            if ( theRefTracks.size() > 1 ) {
                tk2Chi2 = theRefTracks[1].chi2();
                tk2Ndof = theRefTracks[1].ndof();
            }
            muonTkPairSortedTk2Chi2[ID][numMuonTrackPairs[ID] - 1] = tk2Chi2;
            muonTkPairSortedTk2Ndof[ID][numMuonTrackPairs[ID] - 1] = tk2Ndof;

            muonTkPairSortedTkVtxDcaPreFit[ID][numMuonTrackPairs[ID] - 1] = dca;
        }
    }

}

//////////////////////////////////////////////////////////////////////////////////////////////
void MakeTopologyNtupleMiniAOD::fillOtherJetInfo(const pat::Jet& jet,
                                                 const size_t jetindex,
                                                 const std::string& ID,
                                                 const edm::Event& iEvent)
{
    jetSortedCorrFactor[ID][jetindex] = jetSortedCorrErrLow[ID][jetindex] =
        jetSortedCorrErrHi[ID][jetindex] = -1;

    if (jet.jecSetsAvailable())
    {
        jetSortedCorrFactor[ID][jetindex] =
            jet.jecFactor("Uncorrected"); // jet.corrStep());

        // jetSortedCorrErrLow[ID][jetindex] = jet.relCorrUncert("DOWN"); //
        // jetSortedCorrErrHi[ID][jetindex] = jet.relCorrUncert("UP");
        jetSortedCorrErrLow[ID][jetindex] = -1.0;
        jetSortedCorrErrHi[ID][jetindex] = -1.0;
    }

    if (false)
    { // very verbose
        std::vector<std::string> corrlabels{jet.availableJECSets()};
        // std::cout << jet.currentJECLevel() << " " << jet.currentJECFlavor()
        //           << " ";
        // for (size_t icorr = 0; icorr < corrlabels.size(); icorr++)
        //     std::cout << corrlabels[icorr] << " ";
        // std::cout << std::endl;
    }
    // Residuals as needed
    float resCor{1.0};
    constexpr float L2L3ResErr{-1.0}; // Temp as uncertainty is missing.

    if (!runMCInfo_)
    {
        resCor = jet.jecFactor("L3Absolute");
    }
    jetSortedCorrResidual[ID][jetindex] = resCor;
    jetSortedL2L3ResErr[ID][jetindex] = L2L3ResErr;

    jetSortedE[ID][jetindex] = jet.energy();
    jetSortedEt[ID][jetindex] = jet.et();
    jetSortedPt[ID][jetindex] = jet.pt();
    jetSortedPtRaw[ID][jetindex] = jet.pt();
    jetSortedUnCorEt[ID][jetindex] = jet.correctedP4("Uncorrected").Et();
    jetSortedUnCorPt[ID][jetindex] = jet.correctedP4("Uncorrected").Pt();
    jetSortedEta[ID][jetindex] = jet.eta();
    jetSortedTheta[ID][jetindex] = jet.theta();
    jetSortedPhi[ID][jetindex] = jet.phi();
    jetSortedPx[ID][jetindex] = jet.px();
    jetSortedPy[ID][jetindex] = jet.py();
    jetSortedPz[ID][jetindex] = jet.pz();
    jetSortedMass[ID][jetindex] = jet.mass();
    // jetSortedID[ID][jetindex] = jet.jetID();
    jetSortedNtracksInJet[ID][jetindex] =
        jet.associatedTracks().size(); // Need to fix - not a high priority as
                                       // currently not used in the analysis
    jetSortedN90Hits[ID][jetindex] = jet.jetID().n90Hits;
    jetSortedfHPD[ID][jetindex] = jet.jetID().fHPD;
    jetSortedJetCharge[ID][jetindex] = jet.jetCharge();
    jetSortedNConstituents[ID][jetindex] = jet.numberOfDaughters();

    // Tracks associated with jet
//    const reco::TrackRefVector assocTrks = jet.associatedTracks();
    
//    std::cout << "isCaloJet() : " << jet.isCaloJet() << std::endl;
//    std::cout << "isPFJet() : " << jet.isPFJet() << std::endl;
    if ( jet.isJPTJet()) std::cout << "isJPTJet() : " << jet.isJPTJet() << std::endl;

    // Calo & JPT
    if (jet.isCaloJet())
    {
        jetSortedEMEnergyInEB[ID][jetindex] = jet.emEnergyInEB();
        jetSortedEMEnergyInEE[ID][jetindex] = jet.emEnergyInEE();
        jetSortedEMEnergyInHF[ID][jetindex] = jet.emEnergyInHF();
        jetSortedEMEnergyFraction[ID][jetindex] = jet.emEnergyFraction();
        jetSortedHadEnergyInHB[ID][jetindex] = jet.hadEnergyInHB();
        jetSortedHadEnergyInHE[ID][jetindex] = jet.hadEnergyInHE();
        jetSortedHadEnergyInHF[ID][jetindex] = jet.hadEnergyInHF();
        jetSortedHadEnergyInHO[ID][jetindex] = jet.hadEnergyInHO();
        jetSortedN60[ID][jetindex] = jet.n60();
        jetSortedN90[ID][jetindex] = jet.n90();
    }
    else if (jet.isPFJet())
    {
        jetSortedMuEnergy[ID][jetindex] = jet.chargedMuEnergy();
        jetSortedMuEnergyFraction[ID][jetindex] =
            jet.correctedJet("Uncorrected").chargedMuEnergyFraction();
        jetSortedChargedMultiplicity[ID][jetindex] = jet.chargedMultiplicity();
        jetSortedNeutralEmEnergy[ID][jetindex] = jet.neutralEmEnergy();
        jetSortedNeutralHadEnergy[ID][jetindex] = jet.neutralHadronEnergy();
        jetSortedNeutralMultiplicity[ID][jetindex] = jet.neutralMultiplicity();
        jetSortedChargedHadronEnergyFraction[ID][jetindex] =
            jet.correctedJet("Uncorrected").chargedHadronEnergyFraction();
        jetSortedNeutralHadronEnergyFraction[ID][jetindex] =
            jet.correctedJet("Uncorrected").neutralHadronEnergyFraction();
        jetSortedChargedEmEnergyFraction[ID][jetindex] =
            jet.correctedJet("Uncorrected").chargedEmEnergyFraction();
        jetSortedNeutralEmEnergyFraction[ID][jetindex] =
            jet.correctedJet("Uncorrected").neutralEmEnergyFraction();
        jetSortedMuonFraction[ID][jetindex] =
            jet.correctedJet("Uncorrected").muonEnergyFraction();
        jetSortedChargedHadronEnergyFractionCorr[ID][jetindex] =
            jet.chargedHadronEnergyFraction();
        jetSortedNeutralHadronEnergyFractionCorr[ID][jetindex] =
            jet.neutralHadronEnergyFraction();
        jetSortedChargedEmEnergyFractionCorr[ID][jetindex] =
            jet.chargedEmEnergyFraction();
        jetSortedNeutralEmEnergyFractionCorr[ID][jetindex] =
            jet.neutralEmEnergyFraction();
        jetSortedMuonFractionCorr[ID][jetindex] = jet.muonEnergyFraction();
    }
    // else if(jet.isJPTJet()) //This function does not exist in 361, when we
    //  move to 382 reinstate
    else
    {
        //"PF" like branches not compatable with 36X. May not be
        // functional/useful anyway.
        // jetSortedChargedHadronEnergyFraction[ID][jetindex] =
        //     jet.chargedHadronEnergyFraction();
        // jetSortedNeutralHadronEnergyFraction[ID][jetindex] =
        //     jet.neutralHadronEnergyFraction();
        // jetSortedChargedEmEnergyFraction[ID][jetindex] =
        //     jet.chargedEmEnergyFraction();
        // jetSortedNeutralEmEnergyFraction[ID][jetindex] =
        //     jet.neutralEmEnergyFraction();
        jetSortedChargedHadronEnergyFraction[ID][jetindex] = -1.0;
        jetSortedNeutralHadronEnergyFraction[ID][jetindex] = -1.0;
        jetSortedChargedEmEnergyFraction[ID][jetindex] = -1.0;
        jetSortedNeutralEmEnergyFraction[ID][jetindex] = -1.0;

        // Calo collection seems to be empty so get the EMF from oldJetID
        // struct.
        jetSortedEMEnergyFraction[ID][jetindex] = jet.jetID().restrictedEMF;
    }
    // check for triggers:
    if (check_triggers_)
    {
        std::vector<pat::TriggerObjectStandAlone> matchedtriggers{
            jet.triggerObjectMatches()};

        if (false)
        { // very verbose.
            for (auto& matchedtrigger : matchedtriggers)
            {
                for (auto it{matchedtrigger.filterLabels().begin()},
                     it_end = matchedtrigger.filterLabels().end();
                     it != it_end;
                     it++)
                {
                    // std::cout << *it << std::endl;
                }
            }
            jetSortedTriggered[ID][jetindex] =
                matchedtriggers.size(); // very coarse, probably want to select
                                        // on a filter.
        }
    }
    // MC information

    genJetSortedClosestB[ID][jetindex] = -1;
    genJetSortedClosestC[ID][jetindex] = -1;

    if (runMCInfo_)
    {
        edm::Handle<reco::GenParticleCollection> genParticles;
        iEvent.getByToken(genSimParticlesToken_, genParticles);
        if (!genParticles.isValid())
        {
            iEvent.getByToken(genParticlesToken_, genParticles);
        }
        for (size_t k{0}; k < genParticles->size(); k++)
        {
            const reco::Candidate& TCand{(*genParticles)[k]};
            if (std::abs(TCand.pdgId()) == 5 || std::abs(TCand.pdgId()) == 4)
            {
                double deltaR{reco::deltaR(jetSortedEta[ID][jetindex],
                                           jetSortedPhi[ID][jetindex],
                                           TCand.eta(),
                                           TCand.phi())};
                if (std::abs(TCand.pdgId()) == 5
                    && (deltaR < genJetSortedClosestB[ID][jetindex]
                        || genJetSortedClosestB[ID][jetindex] < 0))
                {
                    genJetSortedClosestB[ID][jetindex] = deltaR;
                }
                else if (std::abs(TCand.pdgId()) == 4
                         && (deltaR < genJetSortedClosestC[ID][jetindex]
                             || genJetSortedClosestC[ID][jetindex] < 0))
                {
                    genJetSortedClosestC[ID][jetindex] = deltaR;
                }
            }
        }
    }
    jetSortedPID[ID][jetindex] = jet.partonFlavour();
    // next: only fill if genJet was matched.
}

void MakeTopologyNtupleMiniAOD::fillMCJetInfo(const reco::GenJet& jet, const size_t jetindex,  const std::string& ID, bool runMC)
{
    if (runMC)
    {
        //    Not every status-1 GEN particle is saved in miniAOD and thus some
        //    of the constituents may be missing. Skip GenConstituent pdgId of
        //    such events.
        edm::Ptr<reco::Candidate> const& constituent{jet.sourceCandidatePtr(0)}; // Get pointer to the first genConstituent.

/*
        std::cout << "\ngenJetConstituents: " << jet.numberOfSourceCandidatePtrs() << std::endl;
        const TLorentzVector genJetVec {jet.px(), jet.py(), jet.pz(), jet.energy()};
        std::cout << "genJet inv mass and energy = " << jet.energy() << " / " << genJetVec.M() << std::endl;
        for ( uint ijet = 0; ijet != jet.numberOfSourceCandidatePtrs(); ijet ++ ){
            edm::Ptr<reco::Candidate> const& constit{jet.sourceCandidatePtr(ijet)};
            if ( !constit.isNull() or not constit.isAvailable()) {
                const TLorentzVector constitVec {constit->px(), constit->py(), constit->pz(), constit->energy()};
                std::cout << "ijet(" << ijet << ") PID = " << constit->pdgId() << " inv mass = " << constitVec.M()<< " ; pT = " << constit->pt() << " ; E = " << constit->energy() << std::endl;
            }
        }
*/

        if (!constituent.isNull() or not constituent.isAvailable())
        {
            genJetSortedPID[ID][jetindex] = constituent->pdgId();
            genJetSortedMotherPID[ID][jetindex] = constituent->mother()->pdgId();
            genJetSortedScalarAncestor[ID][jetindex] = jetScalarAncestor(constituent->mother());
        }
        else
        {
            genJetSortedPID[ID][jetindex] = 0;
            genJetSortedMotherPID[ID][jetindex] = 0;
            genJetSortedScalarAncestor[ID][jetindex] = 0;
        }
/*
        if ( genJetSortedScalarAncestor[ID][jetindex] == 1 ) {
            std::cout << "\ngenJetConstituents: " << jet.numberOfSourceCandidatePtrs() << std::endl;
            const TLorentzVector genJetVec {jet.px(), jet.py(), jet.pz(), jet.energy()};
            std::cout << "genJet energy and inv mass (Tlorentz) = " << jet.energy() << " / " << genJetVec.M() << std::endl;
            for ( uint ijet = 0; ijet != jet.numberOfSourceCandidatePtrs(); ijet ++ ){
                edm::Ptr<reco::Candidate> const& constit{jet.sourceCandidatePtr(ijet)};
                if ( !constit.isNull() or not constit.isAvailable()) {
                    const TLorentzVector constitVec {constit->px(), constit->py(), constit->pz(), constit->energy()};
                    std::cout << "ijet(" << ijet << ") PID = " << constit->pdgId() << " inv mass = " << constitVec.M()<< " ; pT = " << constit->pt() << " ; E = " << constit->energy() << std::endl;
                }
            }
        }
*/

        genJetSortedE[ID][jetindex] = jet.energy();
        genJetSortedEt[ID][jetindex] = jet.et();
        genJetSortedPt[ID][jetindex] = jet.pt();
        genJetSortedEta[ID][jetindex] = jet.eta();
        genJetSortedTheta[ID][jetindex] = jet.theta();
        genJetSortedPhi[ID][jetindex] = jet.phi();
        genJetSortedPx[ID][jetindex] = jet.px();
        genJetSortedPy[ID][jetindex] = jet.py();
        genJetSortedPz[ID][jetindex] = jet.pz();
        genJetSortedMass[ID][jetindex] = jet.mass();
        // genJetSortedID[ID][jetindex] = jet.jetID();
    }
    else
    {
        genJetSortedE[ID][jetindex] = -999.;
        genJetSortedEt[ID][jetindex] = -999.;
        genJetSortedPt[ID][jetindex] = -999.;
        genJetSortedEta[ID][jetindex] = -999.;
        genJetSortedTheta[ID][jetindex] = -999.;
        genJetSortedPhi[ID][jetindex] = -999.;
        genJetSortedPx[ID][jetindex] = -999.;
        genJetSortedPy[ID][jetindex] = -999.;
        genJetSortedPz[ID][jetindex] = -999.;
        genJetSortedMass[ID][jetindex] = -999.;
        // genJetSortedID[ID][jetindex] = 0;
        genJetSortedPID[ID][jetindex] = 0;
        genJetSortedMotherPID[ID][jetindex] = 0;
        genJetSortedScalarAncestor[ID][jetindex] = 0;
        genJetSortedClosestB[ID][jetindex] = -1;
        genJetSortedClosestC[ID][jetindex] = -1;
    }
}

void MakeTopologyNtupleMiniAOD::fillMCJetInfo(int /*empty*/,
                                              const size_t jetindex,
                                              const std::string& ID,
                                              bool /*runMC*/)
{
    genJetSortedE[ID][jetindex] = -999.;
    genJetSortedEt[ID][jetindex] = -999.;
    genJetSortedPt[ID][jetindex] = -999.;
    genJetSortedEta[ID][jetindex] = -999.;
    genJetSortedTheta[ID][jetindex] = -999.;
    genJetSortedPhi[ID][jetindex] = -999.;
    genJetSortedPx[ID][jetindex] = -999.;
    genJetSortedPy[ID][jetindex] = -999.;
    genJetSortedPz[ID][jetindex] = -999.;
    genJetSortedMass[ID][jetindex] = -999.;
    // genJetSortedID[ID][jetindex] = 0;
    genJetSortedPID[ID][jetindex] = 0;
    genJetSortedMotherPID[ID][jetindex] = 0;
    genJetSortedScalarAncestor[ID][jetindex] = 0;
    genJetSortedClosestB[ID][jetindex] = -1;
    genJetSortedClosestC[ID][jetindex] = -1;
}

void MakeTopologyNtupleMiniAOD::fillBTagInfo(const pat::Jet& jet,
                                             const size_t jetindex,
                                             const std::string& ID)
{
    for (const auto& iBtag : bTagList_)
    {
        bTagRes[iBtag][ID][jetindex] = jet.bDiscriminator(iBtag);
    }

    const reco::SecondaryVertexTagInfo* svTagInfo{jet.tagInfoSecondaryVertex()};
    if (svTagInfo)
    {
        bTags++;
        jetSortedSVX[ID][jetindex] = svTagInfo->secondaryVertex(0).x();
        jetSortedSVY[ID][jetindex] = svTagInfo->secondaryVertex(0).y();
        jetSortedSVZ[ID][jetindex] = svTagInfo->secondaryVertex(0).z();
        jetSortedSVDX[ID][jetindex] = svTagInfo->secondaryVertex(0).xError();
        jetSortedSVDY[ID][jetindex] = svTagInfo->secondaryVertex(0).yError();
        jetSortedSVDZ[ID][jetindex] = svTagInfo->secondaryVertex(0).zError();
    }
}

void MakeTopologyNtupleMiniAOD::fillMCInfo(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

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

    else
    {
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

    if (!is2016rereco_)
    {
        // Perform the recommended rescaling
        // The TWiki says:
        // https://twiki.cern.ch/twiki/bin/viewauth/CMS/LHEReaderCMSSW#Retrieving_the_weights
        // final_weight = nominal_weight * systematic_weight / original_weight
        // but we want to turn these into an easy to use SF
        // sf = final_weight / original_weight
        //    = nominal_weight * systematic_weight / (original_weight ^ 2)
        auto weight_sf = [&](const double w) {
            return w * genEventInfo->weight()
                   / std::pow(EventHandle->originalXWGTUP(), 2);
        };

        for (size_t i{2}; i < genEventInfo->weights().size(); ++i)
        {
            switch (i)
            {
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

    processPtHat_ = genEventInfo->qScale();
    weight_ = genEventInfo->weight();
    processId_ = genEventInfo->signalProcessID();
    edm::Handle<reco::GenParticleCollection> genParticles;
    iEvent.getByToken(genSimParticlesToken_, genParticles);

    if (!genParticles.isValid())
    {
        iEvent.getByToken(genParticlesToken_, genParticles);
    }

    // fillJets(iEvent, iSetup); // needed to do additional MC truth matching.

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

void MakeTopologyNtupleMiniAOD::fillJets( const edm::Event& iEvent, const edm::EventSetup& iSetup, edm::EDGetTokenT<pat::JetCollection> jetIn_, const std::string& ID ) {
    // if (ran_jetloop_)
    // {
    //     return;
    // }
    // ran_jetloop_ = true;

    // Make sure tracks are filled before jet stuff occurs
    //fillIsolatedTracks(iEvent, iSetup);
    //fillLostTracksCands(iEvent, iSetup);
    //fillPackedCands(iEvent, iSetup);

    edm::Handle<pat::JetCollection> jetHandle;
    iEvent.getByToken(jetIn_, jetHandle);
    const pat::JetCollection& jets{*jetHandle};

    edm::Handle<reco::GenJetCollection> genJetHandle;
    if (runMCInfo_)
    {
        iEvent.getByToken(genJetsToken_, genJetHandle);
    }

    // check that the electrons are filled, if not do so:
    // if (!ran_eleloop_)
    // {
    //     fillElectrons(iEvent, iSetup);
    // }
    //   !!!
    // IMPORTANT: DO NOT CUT ON THE OBJECTS BEFORE THEY ARE SORTED, cuts should
    // be applied in the second loop!!!
    //   !!!
    correctedJetEts.clear();

    // std::cout << __LINE__ << " : " << __FILE__ << " : nJets = " <<
    // jets.size()
    //           << std::endl;

    for (const auto& jet : jets) {
        if (useResidualJEC_) { // Correct the Et with residuals first
            if (jet.isCaloJet()) {
                jecCalo->setJetEta(jet.eta());
                jecCalo->setJetPt(jet.pt());
                correctedJetEts.emplace_back(jet.et() * jecCalo->getCorrection());
            }
            else if (jet.isPFJet()) {
                jecPF->setJetEta(jet.eta());
                jecPF->setJetPt(jet.pt());
                correctedJetEts.emplace_back(jet.et() * jecPF->getCorrection());
            }
            // else if (jet_iter->isJPTJet())
            else {
                jecJPT->setJetEta(jet.eta());
                jecJPT->setJetPt(jet.pt());
                correctedJetEts.emplace_back(jet.et() * jecJPT->getCorrection());
            }
        }
        else {
            correctedJetEts.emplace_back(jet.et());
        }
    }

    std::vector<size_t> etJetSorted{ IndexSorter<std::vector<float>>(correctedJetEts, true)() };
    // std::cout << "second jet loop: " << std::endl;

    // jets:
    numJet[ID] = 0;

    boost::container::vector<bool> genJetUsed(
        100,
        false); // index of jets in the gen jet collection - if it's true it
                // means it's already matched and so shouldn't be used again
    for (size_t ijet{0}; ijet < etJetSorted.size() && numJet[ID] < numeric_cast<int>(NJETSMAX); ++ijet) {
        size_t jjet{etJetSorted[ijet]};

        const pat::Jet& jet{jets[jjet]};

        // Check our type to match with our electron collection. This will NOT
        // throw errors if it has not been ran yet!
        // Commented out as it is not used currently
/* 
       std::string eleCol;
        if (jet.isCaloJet())
        {
            eleCol = "Calo";
        }
        // else if (jet.isJPTJet())
        // {
        //     eleCol = "Calo";
        // } // JPT only jets
        else if (ID == "AK5PF")
        {
            eleCol = "Calo";
        } // Pass for reco PF jets
        else if (jet.isPFJet())
        {
            eleCol = "PF";
        }
        else
        {
            eleCol = "Calo";
        } // For backup.
*/
        fillOtherJetInfo(jet, numJet[ID], ID, iEvent);
        // Do jet smearing here.
        if (runMCInfo_)
        {
            float delR{9999.};
            reco::GenJet assocJet;
            const reco::GenJetCollection& genJets{*genJetHandle};
            int genJetIndex{0};
            int tempIndex{0};
            for (const auto& genJet : genJets)
            {
                double dphi{jet.phi() - genJet.phi()};
                if (dphi > TMath::Pi())
                {
                    dphi = 2 * TMath::Pi() - dphi;
                }
                if (dphi < -TMath::Pi())
                {
                    dphi = -2 * TMath::Pi() - dphi;
                }
                double dEta{jet.eta() - genJet.eta()};
                double dR{sqrt(dphi * dphi + pow(dEta, 2))};
                if (dR < 0.4 && dR < delR && !genJetUsed[genJetIndex])
                {
                    delR = dR;

                    assocJet = genJet;
                    tempIndex = genJetIndex;
                }
                genJetIndex++;
            }
            if (delR < 999.)
            {
                genJetUsed[tempIndex] = true;
                // Make a fill MC info section here that will fill with the
                // associated jet.
                fillMCJetInfo(assocJet, numJet[ID], ID, true);
            }
            else
            { // if no associated gen jet fill with -999.
                fillMCJetInfo(assocJet, numJet[ID], ID, false);
            }
        }
        else
        {
            fillMCJetInfo(0, numJet[ID], ID, false);
        }

        /////////////////////////////
        // no cuts that remove jets after this!

        numJet[ID]++;

        fillBTagInfo(jet, numJet[ID] - 1, ID);
    }
    metE[ID] = sqrt(pow(metPx[ID], 2) + pow(metPy[ID], 2) + pow(metPz[ID], 2));
    metEt[ID] = sqrt(pow(metPx[ID], 2) + pow(metPy[ID], 2));
    if (numJet[ID] == 0)
    {
        clearjetarrays(ID);
    }

    edm::Handle<double> rhoHand_;
    iEvent.getByToken(rhoToken_, rhoHand_);
    fixedGridRhoFastjetAll[ID] = *(rhoHand_.product());
}

/////////////////////////////////////

void MakeTopologyNtupleMiniAOD::fillGeneralTracks(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

    if (!hasGeneralTracks_) return;
    if (ran_tracks_) return;
    ran_tracks_ = true;

    edm::Handle<reco::TrackCollection> generalTracks;
    iEvent.getByToken(generalTracksToken_, generalTracks);

    numGeneralTracks=0;
    for (reco::TrackCollection::const_iterator it=generalTracks->begin(); it!=generalTracks->end() && numGeneralTracks < (int)NTRACKSMAX; it++){
      generalTracksPt[numGeneralTracks]=it->pt();
      generalTracksPx[numGeneralTracks]=it->px();
      generalTracksPy[numGeneralTracks]=it->py();
      generalTracksPz[numGeneralTracks]=it->pz();
      generalTracksEta[numGeneralTracks]=it->eta();
      generalTracksTheta[numGeneralTracks]=it->theta();
      generalTracksPhi[numGeneralTracks]=it->phi();
      generalTracksCharge[numGeneralTracks]=it->charge();    
      generalTracksVx[numGeneralTracks]=it->vx();
      generalTracksVy[numGeneralTracks]=it->vy();
      generalTracksVz[numGeneralTracks]=it->vz();
      generalTracksBeamSpotCorrectedD0[numGeneralTracks]=-1.*(it->dxy(beamSpotPoint_));
      numGeneralTracks++;
    }

}

/////////////////////////////////////

void MakeTopologyNtupleMiniAOD::fillIsolatedTracks(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
    if (ran_isotracks_) return;
    ran_isotracks_ = true;

    edm::Handle<std::vector<pat::IsolatedTrack>> isoTracks;
    iEvent.getByToken(isolatedTrackToken_, isoTracks);

    numIsolatedTracks = 0;

    for (auto it{isoTracks->begin()}; it != isoTracks->end() && numIsolatedTracks < numeric_cast<int>(NISOTRACKSMAX); it++) {
        isoTracksPt[numIsolatedTracks] = it->pt();
        isoTracksPx[numIsolatedTracks] = it->p4().px();
        isoTracksPy[numIsolatedTracks] = it->p4().py();
        isoTracksPz[numIsolatedTracks] = it->p4().pz();
        isoTracksE[numIsolatedTracks] = it->p4().E();
        isoTracksEta[numIsolatedTracks] = it->eta();
        isoTracksTheta[numIsolatedTracks] = it->theta();
        isoTracksPhi[numIsolatedTracks] = it->phi();
        isoTracksCharge[numIsolatedTracks] = it->charge();
        isoTracksPdgId[numIsolatedTracks] = it->pdgId();
        isoTracksMatchedCaloJetEmEnergy[numIsolatedTracks] = it->matchedCaloJetEmEnergy();
        isoTracksMatchedCaloJetHadEnergy[numIsolatedTracks] = it->matchedCaloJetHadEnergy();
        isoTracksDz[numIsolatedTracks] = it->dz();
        isoTracksDxy[numIsolatedTracks] = it->dxy();
        isoTracksDzError[numIsolatedTracks] = it->dzError();
        isoTracksDxyError[numIsolatedTracks] = it->dxyError();
        isoTracksFromPV[numIsolatedTracks] = it->fromPV();
        isoTracksVx[numIsolatedTracks] = it->vx();
        isoTracksVy[numIsolatedTracks] = it->vy();
        isoTracksVz[numIsolatedTracks] = it->vz();
        isoTracksHighPurity[numIsolatedTracks] = it->isHighPurityTrack();
        isoTracksTight[numIsolatedTracks] = it->isTightTrack();
        isoTracksLoose[numIsolatedTracks] = it->isLooseTrack();
        isoTracksDeltaEta[numIsolatedTracks] = it->deltaEta();
        isoTracksDeltaPhi[numIsolatedTracks] = it->deltaPhi();

        numIsolatedTracks++;
    }
}

/////////////////////////////////////

void MakeTopologyNtupleMiniAOD::fillPackedCands(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
    if (ran_packedCands_) return;
    ran_packedCands_ = true;

    edm::Handle<pat::PackedCandidateCollection> packedCandHandle;
    iEvent.getByToken(packedCandToken_, packedCandHandle);
    const pat::PackedCandidateCollection& packedCands{*packedCandHandle};

    // Primary vertex
    edm::Handle<reco::VertexCollection> pvHandle;
    iEvent.getByToken(pvLabel_, pvHandle);

    // Sort packed cands by eT
    packedCandEts.clear();
    for ( const auto& cand : packedCands ) {
        double et{cand.et()};
        packedCandEts.emplace_back(et);
    }

    std::vector<size_t> etSortedPackedCands{IndexSorter<std::vector<float>>(packedCandEts, true)()};

    // Get reco'ed electron, muon, tau, photon and jet collections for index matching

    //// Get electrons
    edm::Handle<pat::ElectronCollection> electronHandle; // changed handle from pat::Electron to reco::GsfElectron
    iEvent.getByToken(patElectronsToken_, electronHandle);
    // Sort electrons by eT like in fillElectrons()
    const pat::ElectronCollection& electrons{*electronHandle};
    electronEts.clear();
    for (const auto& electron : electrons) {
        double et{electron.et()};
        electronEts.emplace_back(et);
    }
    std::vector<size_t> etSortedElectron {};
    if ( electronEts.size() != 0 ) etSortedElectron = IndexSorter<std::vector<float>>(electronEts, true)();

    // Get muons
    edm::Handle<pat::MuonCollection> muonHandle;
    iEvent.getByToken(patMuonsToken_, muonHandle);
    // Sort muons by eT like in fillMuons()
    const pat::MuonCollection& muons{*muonHandle};
    muonEts.clear();
    for (const auto& muon : muons) {
        double et{muon.et()}; // should already be corrected
        muonEts.emplace_back(et);
    }
    std::vector<size_t> etMuonSorted {};
    if ( muonEts.size() != 0 ) etMuonSorted = IndexSorter<std::vector<float>>(muonEts, true)();

    // Get Photons
    edm::Handle<pat::PhotonCollection> photonHandle;
    iEvent.getByToken(patPhotonsToken_, photonHandle);
    const pat::PhotonCollection& photons{*photonHandle};
    photonEts.clear();
    for (const auto& photon : photons) {
      double et{photon.et()};
      photonEts.emplace_back(et);
    }
    std::vector<size_t> etPhotonSorted{IndexSorter<std::vector<float>>(photonEts, true)()};

    // Get Jets
    edm::Handle<pat::JetCollection> jetHandle;
    iEvent.getByToken(patJetsToken_, jetHandle);
    // Sort jets by eT like in fillJets()
    const pat::JetCollection& jets{*jetHandle};
    correctedJetEts.clear();
    for (const auto& jet : jets) {
        if (useResidualJEC_) { // Correct the Et with residuals first
            if (jet.isCaloJet()) {
                jecCalo->setJetEta(jet.eta());
                jecCalo->setJetPt(jet.pt());
                correctedJetEts.emplace_back(jet.et()* jecCalo->getCorrection());
            }
            else if (jet.isPFJet()) {
                jecPF->setJetEta(jet.eta());
                jecPF->setJetPt(jet.pt());
                correctedJetEts.emplace_back(jet.et() * jecPF->getCorrection());
            }
            else {
                jecJPT->setJetEta(jet.eta());
                jecJPT->setJetPt(jet.pt());
                correctedJetEts.emplace_back(jet.et() * jecJPT->getCorrection());
            }
        }
        else
            correctedJetEts.emplace_back(jet.et());
    }

    std::vector<size_t> etJetSorted {IndexSorter<std::vector<float>>(correctedJetEts, true)()};

    edm::ESHandle<MagneticField> magneticFieldHandle;
    iSetup.get<IdealMagneticFieldRecord>().get(magneticFieldHandle);
    const MagneticField* theMagneticField = magneticFieldHandle.product();

    chsTkIndices.clear();
    chsTrackRefs.clear();
    chsTransTracks.clear();

    numPackedCands = 0;

    for (size_t iCand{0}; iCand < etSortedPackedCands.size() && numPackedCands < numeric_cast<int>(NPACKEDCANDSMAX); ++iCand) {
        size_t jCand{etSortedPackedCands[iCand]};
        const pat::PackedCandidate& packedCand{packedCands[jCand]};

       if ( packedCand.pt() < 0.5 ) continue; // want low or high precision track info

//        packedCandsPt[numPackedCands] = packedCand.pt();
        packedCandsPx[numPackedCands] = packedCand.px();
        packedCandsPy[numPackedCands] = packedCand.py();
        packedCandsPz[numPackedCands] = packedCand.pz();
        packedCandsE[numPackedCands] = packedCand.energy();
//        packedCandsEta[numPackedCands] = packedCand.eta();
//        packedCandsTheta[numPackedCands] = packedCand.theta();
//        packedCandsPhi[numPackedCands] = packedCand.phi();
        packedCandsCharge[numPackedCands] = packedCand.charge();
        packedCandsPdgId[numPackedCands] = packedCand.pdgId();
        packedCandsTime[numPackedCands] = packedCand.time();

        packedCandsFromPV[numPackedCands] = packedCand.fromPV();
        packedCandsPVquality[numPackedCands] = packedCand.pvAssociationQuality();
        packedCandsVx[numPackedCands] = packedCand.vx();
        packedCandsVy[numPackedCands] = packedCand.vy();
        packedCandsVz[numPackedCands] = packedCand.vz();
//        packedCandsVEta[numPackedCands] = packedCand.etaAtVtx();
//        packedCandsVPhi[numPackedCands] = packedCand.phiAtVtx();
//        packedCandsBeamSpotCorrectedD0[numPackedCands] = -1. * (packedCand.dxy(beamSpotPoint_));
        packedCandsDz[numPackedCands] = packedCand.dz();
        packedCandsDxy[numPackedCands] = packedCand.dxy();
//        packedCandsDzAssocPV[numPackedCands] = packedCand.dzAssociatedPV();
//        packedCandsVtxChi2Norm[numPackedCands] = packedCand.vertexNormalizedChi2();

    int electronIndex {-1};
    int muonIndex {-1};
//    int tauIndex {-1};
    int photonIndex {-1};
    int jetIndex {-1};

    reco::CandidatePtr pfCandPtr(packedCandHandle, jCand); // reco::CandidatePtr pfCandPtr(std::vector<pat::PackedCandidate>, index);

    // loop over electrons
    int numEle = 0;
    for (size_t iele{0}; iele < etSortedElectron.size() && numEle < numeric_cast<int>(NELECTRONSMAX); ++iele) { // Loop over electrons
        size_t jele{etSortedElectron[iele]};
        const pat::Electron& ele{(*electronHandle)[jele]};
        if (ele.numberOfSourceCandidatePtrs() > 0 ) { // If there's at least one packed pf cands associated with this electron
            for (unsigned int k = 0; k < ele.numberOfSourceCandidatePtrs(); k++) { // Loop over all packed pf cands associated with this electron
                reco::CandidatePtr electronPtr = ele.sourceCandidatePtr(k);
                if ( electronPtr.isNonnull() && pfCandPtr == electronPtr ) { // If electron ptr == packed pf ptr
                    electronIndex = numEle;
                    break;
                } // End if ptrs matches
            } // End loop over packed pf cands associated with this electron
        } // End if there's at least one packed cand assoc with this electron
    numEle++;
    } // End loop over electrons

    // loop over muons
    int numMuo = 0;
    for (size_t imuo{0}; imuo < etMuonSorted.size() && numMuo < numeric_cast<int>(NMUONSMAX); ++imuo) { // Loop	over muons
        size_t jmu{etMuonSorted[imuo]};
        const pat::Muon& muo{muons[jmu]};
        if (muo.numberOfSourceCandidatePtrs() > 0 ) { // If there's at least one packed pf cands associated with this muon
            for (unsigned int k = 0; k < muo.numberOfSourceCandidatePtrs(); k++) { // Loop over all packed pf cands associated with this muon
                reco::CandidatePtr muonPtr = muo.sourceCandidatePtr(k);
                if ( muonPtr.isNonnull() && pfCandPtr == muonPtr ) { //	If muon ptr == packed pf ptr
                    muonIndex = numMuo;
                    break;
                } // End if ptrs matches
            } // End loop over packed pf cands associated with this muon
        } // End if there's at least one packed	cand assoc with	this muon
    numMuo++;
    } // End loop over muons

    // loop over photons
    int numPho = 0;
    for (size_t ipho{0}; ipho < etPhotonSorted.size() && numPho < numeric_cast<int>(NPHOTONSMAX); ++ipho) { // Loop over photons
        size_t jpho{etPhotonSorted[ipho]};
        const pat::Photon& pho{(*photonHandle)[jpho]};
       	if (pho.numberOfSourceCandidatePtrs() > 0 ) { // If there's at least one packed pf cands associated with this photon
            for (unsigned int k = 0; k < pho.numberOfSourceCandidatePtrs(); k++) { // Loop over all packed pf cands associated with this photon
                reco::CandidatePtr photonPtr = pho.sourceCandidatePtr(k);
                if ( photonPtr.isNonnull() && pfCandPtr == photonPtr ) { // If photon ptr == packed pf ptr
                    photonIndex = numPho;
                    break;
                } // End if ptrs matches
            } // End loop over packed pf cands associated with this photon
        } // End if there's at least one packed cand assoc with this photon
        numPho++;
    } // End loop over photons

    // loop over jets
    int numJet = 0;
    for (size_t ijet{0}; ijet < etJetSorted.size() && numJet < numeric_cast<int>(NJETSMAX); ++ijet) { // Loop over jets
        size_t jjet{etJetSorted[ijet]};
        const pat::Jet& jet{jets[jjet]};
        if (jet.numberOfSourceCandidatePtrs() > 0 ) { // If there's at least one packed pf cands associated with this jet
            for (unsigned int k = 0; k < jet.numberOfSourceCandidatePtrs(); k++) { // Loop over all packed pf cands associated with this jet
                reco::CandidatePtr jetPtr = jet.sourceCandidatePtr(k);
                if ( jetPtr.isNonnull() && pfCandPtr == jetPtr ) {  // If jet ptr == packed pf ptr
                    jetIndex = numJet;
                    break;
                } // End if ptrs matches
            } // End loop over packed pf cands associated with this jet
        } // End if there's at least one packed cand assoc with this jet
        numJet++;
    } // End loop over jets

    packedCandsElectronIndex[numPackedCands] = electronIndex;
    packedCandsMuonIndex[numPackedCands] = muonIndex; 
//    packedCandsTauIndex[numPackedCands] = tauIndex;
    packedCandsPhotonIndex[numPackedCands] = photonIndex;
    packedCandsJetIndex[numPackedCands] = jetIndex;

        packedCandsHasTrackDetails[numPackedCands] = packedCand.hasTrackDetails();
        if ( packedCand.hasTrackDetails() ) {

            packedCandsDzError[numPackedCands] = packedCand.dzError();
            packedCandsDxyError[numPackedCands] = packedCand.dxyError();
            packedCandsTimeError[numPackedCands] = packedCand.timeError();

            packedCandsPseudoTrkPt[numPackedCands] = packedCand.pseudoTrack().pt();
            packedCandsPseudoTrkPx[numPackedCands] = packedCand.pseudoTrack().px();
            packedCandsPseudoTrkPy[numPackedCands] = packedCand.pseudoTrack().py();
            packedCandsPseudoTrkPz[numPackedCands] = packedCand.pseudoTrack().pz();
            packedCandsPseudoTrkEta[numPackedCands] = packedCand.pseudoTrack().eta();
            packedCandsPseudoTrkPhi[numPackedCands] = packedCand.pseudoTrack().phi();
            packedCandsPseudoTrkCharge[numPackedCands] = packedCand.pseudoTrack().charge();
            packedCandsPseudoTrkVx[numPackedCands] = packedCand.pseudoTrack().vx();
            packedCandsPseudoTrkVy[numPackedCands] = packedCand.pseudoTrack().vy();
            packedCandsPseudoTrkVz[numPackedCands] = packedCand.pseudoTrack().vz();
            packedCandsPseudoTrkChi2Norm[numPackedCands] = packedCand.pseudoTrack().normalizedChi2();
            packedCandsPseudoTrkNumberOfHits[numPackedCands] = packedCand.pseudoTrack().hitPattern().numberOfValidTrackerHits();
            packedCandsPseudoTrkNumberOfPixelHits[numPackedCands] = packedCand.pseudoTrack().hitPattern().numberOfValidPixelHits();
//            packedCandsPseudoTrkPixelLayersWithMeasurement[numPackedCands] = packedCand.pseudoTrack().hitPattern().pixelLayersWithMeasurement();
//            packedCandsPseudoTrkStripLayersWithMeasurement[numPackedCands] = packedCand.pseudoTrack().hitPattern().stripLayersWithMeasurement();
//            packedCandsPseudoTrkTrackerLayersWithMeasurement[numPackedCands] = packedCand.pseudoTrack().hitPattern().trackerLayersWithMeasurement();
            packedCandsHighPurityTrack[numPackedCands] = packedCand.trackHighPurity();

            // Store impact parameter info
            if ( pvHandle.isValid() ) {
                std::vector<reco::Vertex> pv{*pvHandle};

                edm::ESHandle<TransientTrackBuilder> trackBuilder;
                iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder", trackBuilder);
                reco::TransientTrack trackTransient{trackBuilder->build( packedCand.pseudoTrack() )};

                std::pair<bool, Measurement1D> trackImpactTrans{IPTools::absoluteTransverseImpactParameter(trackTransient, pv[0])};
                std::pair<bool, Measurement1D> trackImpact3D{IPTools::absoluteImpactParameter3D(trackTransient, pv[0])};

                if (trackImpactTrans.first) {
                    packedCandsTrkImpactTransDist[numPackedCands] = trackImpactTrans.second.value();
                    packedCandsTrkImpactTransError[numPackedCands] = trackImpactTrans.second.error();
                    packedCandsTrkImpactTransSignificance[numPackedCands] = trackImpactTrans.second.significance();
                }
                if (trackImpact3D.first) {
                    packedCandsTrk3DDist[numPackedCands] = trackImpact3D.second.value();
                    packedCandsTrk3DError[numPackedCands] = trackImpact3D.second.error();
                    packedCandsTrk3DSignificance[numPackedCands] = trackImpact3D.second.significance();
                }
            }

            // Store packed cands track refs for post muon loop tracking analysis
            if ( std::abs(packedCand.pdgId()) == 211 && packedCand.charge() != 0 && packedCand.pseudoTrack().pt() > 2.9 ) { // only store charged hadrons
                chsTkIndices.push_back( numPackedCands );
                chsTrackRefs.push_back( packedCand.pseudoTrack() );
                reco::TransientTrack tmpTransient( (packedCand.pseudoTrack()), theMagneticField);
                chsTransTracks.push_back( std::move( tmpTransient ) );
            }

        } // End track info loop
        numPackedCands++;
    } // end packed cands loop

    numChsTrackPairs = 0;

    // loop over chs tracks
    for (unsigned int trdx1 = 0; trdx1 < chsTrackRefs.size() && numChsTrackPairs< numeric_cast<int>(NCHSTKPAIRMAX); ++trdx1) {
        for (unsigned int trdx2 = trdx1 + 1; trdx2 < chsTrackRefs.size() && numChsTrackPairs < numeric_cast<int>(NCHSTKPAIRMAX); ++trdx2) {

            reco::Track trackRef1;
            reco::Track trackRef2;
            reco::TransientTrack* transTkPtr1 = nullptr;
            reco::TransientTrack* transTkPtr2 = nullptr;

            trackRef1 = chsTrackRefs[trdx1];
            trackRef2 = chsTrackRefs[trdx2];
            transTkPtr1 = &chsTransTracks[trdx1];
            transTkPtr2 = &chsTransTracks[trdx2];

       	    // check tracks are	opposite charges
	    if ( trackRef1.charge() * trackRef2.charge() >= 0 ) continue;

            // measure distance between tracks at their closest approach

            //these two variables are needed to 'pin' the temporary value returned to the stack in order to keep both States from pointing to destructed objects
            auto const& impact1 = transTkPtr1->impactPointTSCP();
            auto const& impact2 = transTkPtr2->impactPointTSCP();
            if (!impact1.isValid() || !impact2.isValid()) continue;
            FreeTrajectoryState const& state1 = impact1.theState();
            FreeTrajectoryState const& state2 = impact2.theState();

            ClosestApproachInRPhi cApp;
            cApp.calculate(state1, state2);
            if (!cApp.status()) continue;

            float dca = std::abs(cApp.distance());

            // the POCA should at least be in the sensitive volume
            GlobalPoint cxPt = cApp.crossingPoint();
            if ((cxPt.x() * cxPt.x() + cxPt.y() * cxPt.y()) > 120. * 120. || std::abs(cxPt.z()) > 300.) continue;

            TrajectoryStateClosestToPoint const& TSCP1 = transTkPtr1->trajectoryStateClosestToPoint(cxPt);
            TrajectoryStateClosestToPoint const& TSCP2 = transTkPtr2->trajectoryStateClosestToPoint(cxPt);
            if (!TSCP1.isValid() || !TSCP2.isValid()) continue;

            // Are tracks in the same quadrant?
            if ( TSCP1.momentum().dot(TSCP2.momentum()) < 0 ) continue;

            // Fill the vector of TransientTracks to send to KVF
            std::vector<reco::TransientTrack> tmpTransTracks;
            tmpTransTracks.reserve(2);
            tmpTransTracks.push_back(*transTkPtr1);
            tmpTransTracks.push_back(*transTkPtr2);

            // create the vertex fitter object and vertex the tracks
            KalmanVertexFitter theKalmanFitter(true); // KalmanVertexFitter(bool useSmoothing = false);
            TransientVertex theRecoVertex  = theKalmanFitter.vertex(tmpTransTracks);
            if (!theRecoVertex.isValid()) continue;

            // do stuff with new vertices

            reco::Vertex theVtx = theRecoVertex;
            GlobalPoint vtxPos(theVtx.x(), theVtx.y(), theVtx.z());

            // 2D decay significance
            ROOT::Math::SMatrix<double, 3, 3, ROOT::Math::MatRepSym<double, 3>> totalCov = vertexPrimary_->covariance() + theVtx.covariance();
            ROOT::Math::SVector<double, 3>  distVecXY(vtxPos.x() - vertexPrimary_->position().x(), vtxPos.y() - vertexPrimary_->position().y(), 0.);
            double distMagXY = ROOT::Math::Mag(distVecXY);
            double sigmaDistMagXY = sqrt(ROOT::Math::Similarity(totalCov, distVecXY)) / distMagXY;

            // 3D decay significance
            ROOT::Math::SVector<double, 3>  distVecXYZ(vtxPos.x() - vertexPrimary_->position().x(), vtxPos.y() - vertexPrimary_->position().y(), vtxPos.z() - vertexPrimary_->position().z());
            double distMagXYZ = ROOT::Math::Mag(distVecXYZ);
            double sigmaDistMagXYZ = sqrt(ROOT::Math::Similarity(totalCov, distVecXYZ)) / distMagXYZ;

            // do stuff with refit tracks

            std::unique_ptr<TrajectoryStateClosestToPoint> traj1;
            std::unique_ptr<TrajectoryStateClosestToPoint> traj2;
            std::vector<reco::TransientTrack> theRefTracks = theRecoVertex.refittedTracks();
 
            if ( theRefTracks.size() > 1 ) {
                reco::TransientTrack* transTk1 = nullptr;
                reco::TransientTrack* transTk2 = nullptr;
 
                transTk1 = &theRefTracks[0];
                transTk2 = &theRefTracks[1];

                if (transTk1 == nullptr || transTk2 == nullptr) continue;
                traj1 = std::make_unique<TrajectoryStateClosestToPoint>(transTk1->trajectoryStateClosestToPoint(vtxPos));
                traj2 = std::make_unique<TrajectoryStateClosestToPoint>(transTk2->trajectoryStateClosestToPoint(vtxPos));
            }
            else {
                traj1 = std::make_unique<TrajectoryStateClosestToPoint>(transTkPtr1->trajectoryStateClosestToPoint(vtxPos));
                traj2 = std::make_unique<TrajectoryStateClosestToPoint>(transTkPtr2->trajectoryStateClosestToPoint(vtxPos));
            }

            if (traj1.get() == nullptr || traj2.get() == nullptr || !traj1->isValid() || !traj2->isValid()) continue;

            GlobalVector P1(traj1->momentum());
            GlobalVector P2(traj2->momentum());
            GlobalVector totalP(P1 + P2);

            if ( reco::deltaR(P1.eta(), P1.phi(), P2.eta(), P2.phi())> 0.5 ) continue;

            // 2D pointing angle
            double dx = theVtx.x() - vertexPrimary_->position().x();
            double dy = theVtx.y() - vertexPrimary_->position().y();
            double px = totalP.x();
            double py = totalP.y();
            double angleXY = (dx * px + dy * py) / (sqrt(dx * dx + dy * dy) * sqrt(px * px + py * py));

            // 3D pointing angle
            double dz = theVtx.z() - vertexPrimary_->position().z();
            double pz = totalP.z();
            double angleXYZ = (dx * px + dy * py + dz * pz) / (sqrt(dx * dx + dy * dy + dz * dz) * sqrt(px * px + py * py + pz * pz));

            reco::Particle::Point vtx(theVtx.x(), theVtx.y(), theVtx.z());
            const reco::Vertex::CovarianceMatrix vtxCov(theVtx.covariance());
 
            chsTkPairIndex1[numChsTrackPairs] = chsTkIndices[trdx1];
            chsTkPairIndex2[numChsTrackPairs] = chsTkIndices[trdx2];

            chsTkPairTkVtxPx[numChsTrackPairs] = px;
            chsTkPairTkVtxPy[numChsTrackPairs] = py;
            chsTkPairTkVtxPz[numChsTrackPairs] = pz;
            chsTkPairTkVtxP2[numChsTrackPairs] = totalP.mag2();
            chsTkPairTkVx[numChsTrackPairs] = theVtx.x();
            chsTkPairTkVy[numChsTrackPairs] = theVtx.y();
            chsTkPairTkVz[numChsTrackPairs] = theVtx.z();
            chsTkPairTkVtxCov00[numChsTrackPairs] = vtxCov(0,0);
            chsTkPairTkVtxCov01[numChsTrackPairs] = vtxCov(0,1);
            chsTkPairTkVtxCov02[numChsTrackPairs] = vtxCov(0,2);
            chsTkPairTkVtxCov10[numChsTrackPairs] = vtxCov(1,0);
            chsTkPairTkVtxCov11[numChsTrackPairs] = vtxCov(1,1);
            chsTkPairTkVtxCov12[numChsTrackPairs] = vtxCov(1,2);
            chsTkPairTkVtxCov20[numChsTrackPairs] = vtxCov(2,0);
            chsTkPairTkVtxCov21[numChsTrackPairs] = vtxCov(2,1);
            chsTkPairTkVtxCov22[numChsTrackPairs] = vtxCov(2,2);
            chsTkPairTkVtxChi2[numChsTrackPairs] = theVtx.chi2();
            chsTkPairTkVtxNdof[numChsTrackPairs] = theVtx.ndof();
            chsTkPairTkVtxTime[numChsTrackPairs] = theVtx.t();
            chsTkPairTkVtxTimeError[numChsTrackPairs] = theVtx.tError();
            chsTkPairTkVtxAngleXY[numChsTrackPairs] = angleXY;
            chsTkPairTkVtxDistMagXY[numChsTrackPairs] = distMagXY;
            chsTkPairTkVtxDistMagXYSigma[numChsTrackPairs] = sigmaDistMagXY;
            chsTkPairTkVtxAngleXYZ[numChsTrackPairs] = angleXYZ; 
            chsTkPairTkVtxDistMagXYZ[numChsTrackPairs] = distMagXYZ;
            chsTkPairTkVtxDistMagXYZSigma[numChsTrackPairs] = sigmaDistMagXYZ;

            chsTkPairTk1Pt[numChsTrackPairs] = traj1->pt();
            chsTkPairTk1Px[numChsTrackPairs] = P1.x();
            chsTkPairTk1Py[numChsTrackPairs] = P1.y();
            chsTkPairTk1Pz[numChsTrackPairs] = P1.z();
            chsTkPairTk1P2[numChsTrackPairs] = P1.mag2();
            chsTkPairTk1Eta[numChsTrackPairs] = P1.eta();
            chsTkPairTk1Phi[numChsTrackPairs] = P1.phi();
            chsTkPairTk1Charge[numChsTrackPairs] = traj1->charge();
            float tk1Chi2{0.}, tk1Ndof{0.};
            if ( theRefTracks.size() > 1 ) {
                tk1Chi2 = theRefTracks[0].chi2();
                tk1Ndof = theRefTracks[0].ndof();
            }
            chsTkPairTk1Chi2[numChsTrackPairs] = tk1Chi2;
            chsTkPairTk1Ndof[numChsTrackPairs] = tk1Ndof;

            chsTkPairTk2Pt[numChsTrackPairs] = traj2->pt();
            chsTkPairTk2Px[numChsTrackPairs] = P2.x();
            chsTkPairTk2Py[numChsTrackPairs] = P2.y();
            chsTkPairTk2Pz[numChsTrackPairs] = P2.z();
            chsTkPairTk2P2[numChsTrackPairs] = P2.mag2();
            chsTkPairTk2Eta[numChsTrackPairs] = P2.eta();
            chsTkPairTk2Phi[numChsTrackPairs] = P2.phi();
            chsTkPairTk2Charge[numChsTrackPairs] = traj2->charge();
            float tk2Chi2{0.}, tk2Ndof{0.};
            if ( theRefTracks.size() > 1 ) {
                tk2Chi2 = theRefTracks[1].chi2();
                tk2Ndof = theRefTracks[1].ndof();
            }
            chsTkPairTk2Chi2[numChsTrackPairs] = tk2Chi2;
            chsTkPairTk2Ndof[numChsTrackPairs] = tk2Ndof;

            chsTkPairTkVtxDcaPreFit[numChsTrackPairs] = dca;

            numChsTrackPairs++;
        }
    }
}

/////////////////////////////////////
void MakeTopologyNtupleMiniAOD::clearTauArrays(const std::string& ID){
    numTaus[ID] = 0;
    tau_e[ID].clear();
    tau_phi[ID].clear();
    tau_eta[ID].clear();
    tau_pt[ID].clear();
}
void MakeTopologyNtupleMiniAOD::clearPhotonArrays(const std::string& ID){
    numPho[ID] = 0;

    photonEts.clear(); // just used for sorting

    photonSortedE[ID].clear();
    photonSortedSigmaE[ID].clear();
    photonSortedET[ID].clear();
    photonSortedPhi[ID].clear();
    photonSortedEta[ID].clear();
    photonSortedTheta[ID].clear();
    photonSortedPt[ID].clear();
    photonSortedPx[ID].clear();
    photonSortedPy[ID].clear();
    photonSortedPz[ID].clear();
    photonSortedCalibE[ID].clear();
    photonSortedCalibEt[ID].clear();
    photonSortedSCE[ID].clear();
    photonSortedSCRawE[ID].clear();
    photonSortedESEnP1[ID].clear();
    photonSortedESEnP2[ID].clear();
    photonSortedSCEta[ID].clear();
    photonSortedSCEtaWidth[ID].clear();
    photonSortedSCPhi[ID].clear();
    photonSortedSCPhiWidth[ID].clear();
    photonSortedSCBrem[ID].clear();
    photonSortedHasPixelSeed[ID].clear();
    photonSortedEleVeto[ID].clear();
    photonSortedR9[ID].clear();
    photonSortedHoverE[ID].clear();
    photonSortedESEffSigmaRR[ID].clear();
    photonSortedSigmaIEtaIEtaFull5x5[ID].clear();
    photonSortedSigmaIEtaIPhiFull5x5[ID].clear();
    photonSortedSigmaIPhiIPhiFull5x5[ID].clear();
    photonSortedE2x2Full5x5[ID].clear();
    photonSortedE5x5Full5x5[ID].clear();
    photonSortedR9Full5x5[ID].clear();
    photonSortedPFChIso[ID].clear();
    photonSortedPFPhoIso[ID].clear();
    photonSortedPFNeuIso[ID].clear();
    photonSortedPFChWorstIso[ID].clear();
    photonSortedMIPTotEnergy[ID].clear();    
    photonSortedCutIdLoose[ID].clear();
    photonSortedCutIdMedium[ID].clear();
    photonSortedCutIdTight[ID].clear();
    photonSortedMvaIdWp80[ID].clear();
    photonSortedMvaIdWp90[ID].clear();

    photonSortedNumSourceCandidates[ID].clear();
    photonSortedPackedCandIndex[ID].clear();

    genPhotonSortedPt[ID].clear();
    genPhotonSortedET[ID].clear();
    genPhotonSortedEta[ID].clear();
    genPhotonSortedTheta[ID].clear();
    genPhotonSortedPhi[ID].clear();
    genPhotonSortedPx[ID].clear();
    genPhotonSortedPy[ID].clear();
    genPhotonSortedPz[ID].clear();
    genPhotonSortedCharge[ID].clear();
    genPhotonSortedPdgId[ID].clear();
    genPhotonSortedMotherId[ID].clear();
    genPhotonSortedIsPhoton[ID].clear();
    genPhotonSortedIsConvertedPhoton[ID].clear();
    genPhotonSortedIsJet[ID].clear();
//    genPhotonSortedPromptDecayed[ID].clear();
//    genPhotonSortedPromptFinalState[ID].clear();
//    genPhotonSortedHardProcess[ID].clear();
//    genPhotonSortedPythiaSixStatusThree[ID].clear();
    genPhotonSortedScalarAncestor[ID].clear();
    genPhotonSortedDirectScalarAncestor[ID].clear();
}
void MakeTopologyNtupleMiniAOD::clearelectronarrays(const std::string& ID){
    numEle[ID] = 0;

    nzcandidates[ID] = 0;
    zcandidatesvector[ID].clear();

    electronEts.clear(); // just used for sorting
    std::vector<float> tempVector;

    electronSortedE[ID].clear();
    electronSortedEt[ID].clear();
    electronSortedEta[ID].clear();
    electronSortedPt[ID].clear();
    electronSortedTheta[ID].clear();
    electronSortedPhi[ID].clear();
    electronSortedPx[ID].clear();
    electronSortedPy[ID].clear();
    electronSortedPz[ID].clear();
    electronSortedCharge[ID].clear();

    electronSortedCutIdVeto[ID].clear();
    electronSortedCutIdLoose[ID].clear();
    electronSortedCutIdMedium[ID].clear();
    electronSortedCutIdTight[ID].clear();
    electronSortedMvaIdWp80[ID].clear();
    electronSortedMvaIdWp90[ID].clear();
    electronSortedMvaIdWpLoose[ID].clear();

    electronSortedChargedHadronIso[ID].clear();
    electronSortedNeutralHadronIso[ID].clear();
    electronSortedPhotonIso[ID].clear();
    electronSortedTrackPt[ID].clear();
    electronSortedTrackEta[ID].clear();
    electronSortedTrackPhi[ID].clear();
    electronSortedTrackChi2[ID].clear();
    electronSortedTrackNDOF[ID].clear();
    electronSortedTrackD0[ID].clear();
    electronSortedDBBeamSpotCorrectedTrackD0[ID].clear();

    // electronSortedDBInnerTrackD0[ID].clear();

    electronSortedBeamSpotCorrectedTrackD0[ID].clear();
    electronSortedTrackDz[ID].clear();
    electronSortedTrackD0PV[ID].clear();
    electronSortedTrackDZPV[ID].clear();
    electronSortedVtxZ[ID].clear();
    electronSortedBeamSpotCorrectedTrackDz[ID].clear();
    electronSortedIsGsf[ID].clear();
    electronSortedGsfPx[ID].clear();
    electronSortedGsfPy[ID].clear();
    electronSortedGsfPz[ID].clear();
    electronSortedGsfE[ID].clear();
    electronSortedEcalEnergy[ID].clear();

    electronSortedSuperClusterEta[ID].clear();
    electronSortedSuperClusterE[ID].clear();
    electronSortedSuperClusterPhi[ID].clear();
    electronSortedSuperClusterEoverP[ID].clear();
    electronSortedSuperClusterSigmaEtaEta[ID].clear();
    electronSortedSuperClusterE1x5[ID].clear();
    electronSortedSuperClusterE2x5max[ID].clear();
    electronSortedSuperClusterE5x5[ID].clear();
    electronSortedSuperClusterSigmaIEtaIEta[ID].clear();
    electronSortedSuperClusterSigmaIEtaIEta5x5[ID].clear();
    electronSortedTrackIso04[ID].clear();
    electronSortedECalIso04[ID].clear();
    electronSortedHCalIso04[ID].clear();
    electronSortedTrackIso03[ID].clear();
    electronSortedECalIso03[ID].clear();
    electronSortedHCalIso03[ID].clear();
    electronSorteddr04EcalRecHitSumEt[ID].clear();
    electronSorteddr03EcalRecHitSumEt[ID].clear();
    electronSortedECalIsoDeposit[ID].clear();
    electronSortedHCalIsoDeposit[ID].clear();
    electronSortedCaloIso[ID].clear();
    electronSortedTriggerMatch[ID].clear();
    electronSortedJetOverlap[ID].clear();
    electronSortedComRelIso[ID].clear();
    electronSortedComRelIsodBeta[ID].clear();
    electronSortedComRelIsoRho[ID].clear();
    electronSortedChHadIso[ID].clear();
    electronSortedNtHadIso[ID].clear();
    electronSortedGammaIso[ID].clear();
    electronSortedRhoIso[ID].clear();
    electronSortedAEff03[ID].clear();
    electronSortedMissingInnerLayers[ID].clear();
    electronSortedHoverE[ID].clear();
    electronSortedDeltaPhiSC[ID].clear();
    electronSortedDeltaEtaSC[ID].clear();
    electronSortedDeltaEtaSeedSC[ID].clear();
    electronSortedIsBarrel[ID].clear();
    electronSortedPhotonConversionTag[ID].clear();
//    electronSortedPhotonConversionTagCustom[ID].clear();
    electronSortedPhotonConversionDcot[ID].clear();
    electronSortedPhotonConversionDist[ID].clear();
    electronSortedPhotonConversionVeto[ID].clear();
    electronSortedPhotonConversionDcotCustom[ID].clear();
    electronSortedPhotonConversionDistCustom[ID].clear();

    electronSortedImpactTransDist[ID].clear();
    electronSortedImpactTransError[ID].clear();
    electronSortedImpactTransSignificance[ID].clear();
    electronSortedImpact3DDist[ID].clear();
    electronSortedImpact3DError[ID].clear();
    electronSortedImpact3DSignificance[ID].clear();

    // electronSortedIDResults_[ID].clear();

    electronSortedNumSourceCandidates[ID].clear();
    electronSortedPackedCandIndex[ID].clear();

    genElectronSortedPt[ID].clear();
    genElectronSortedEt[ID].clear();
    genElectronSortedEta[ID].clear();
    genElectronSortedTheta[ID].clear();
    genElectronSortedPhi[ID].clear();
    genElectronSortedPx[ID].clear();
    genElectronSortedPy[ID].clear();
    genElectronSortedCharge[ID].clear();
    genElectronSortedPdgId[ID].clear();
    genElectronSortedMotherId[ID].clear();
    genElectronSortedPromptDecayed[ID].clear();
    genElectronSortedPromptFinalState[ID].clear();
    genElectronSortedHardProcess[ID].clear();
    genElectronSortedPythiaSixStatusThree[ID].clear();
    genElectronSortedScalarAncestor[ID].clear();
    genElectronSortedDirectScalarAncestor[ID].clear();
}

void MakeTopologyNtupleMiniAOD::clearmuonarrays(const std::string& ID){
    // std::cout << "clearmuonarrays CHECK" << std::endl;
    numMuo[ID] = 0;
    muonEts.clear(); // just used for sorting
    // vectors to store muon track refs and indices for later
    muonTkIndices.clear();
    muonTrackRefs.clear();
    muonTransTracks.clear();

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
    muonSortedPfIsoVeryLoose[ID].clear();
    muonSortedPfIsoLoose[ID].clear();
    muonSortedPfIsoMedium[ID].clear();
    muonSortedPfIsoTight[ID].clear();
    muonSortedPfIsoVeryTight[ID].clear();
    muonSortedTkIsoLoose[ID].clear();
    muonSortedTkIsoTight[ID].clear();
    muonSortedMvaLoose[ID].clear();
    muonSortedMvaMedium[ID].clear();
    muonSortedMvaTight[ID].clear();

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
    muonSortedIsPFMuon[ID].clear();

    muonSortedNumChambers[ID].clear();
    muonSortedNumMatches[ID].clear();

    muonSortedNumSourceCandidates[ID].clear();
    muonSortedPackedCandIndex[ID].clear();

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
    genMuonSortedScalarAncestor[ID].clear();
    genMuonSortedDirectScalarAncestor[ID].clear();

    numMuonTrackPairs[ID] = 0;
    muonTkPairSortedIndex1[ID].clear(); 
    muonTkPairSortedIndex2[ID].clear();
    muonTkPairSortedTkVtxPx[ID].clear();
    muonTkPairSortedTkVtxPy[ID].clear();
    muonTkPairSortedTkVtxPz[ID].clear();
    muonTkPairSortedTkVtxP2[ID].clear();
    muonTkPairSortedTkVx[ID].clear();
    muonTkPairSortedTkVy[ID].clear();                   
    muonTkPairSortedTkVz[ID].clear();
    muonTkPairSortedTkVtxCov00[ID].clear();
    muonTkPairSortedTkVtxCov01[ID].clear();
    muonTkPairSortedTkVtxCov02[ID].clear();
    muonTkPairSortedTkVtxCov10[ID].clear();
    muonTkPairSortedTkVtxCov11[ID].clear();
    muonTkPairSortedTkVtxCov12[ID].clear();
    muonTkPairSortedTkVtxCov20[ID].clear();
    muonTkPairSortedTkVtxCov21[ID].clear();
    muonTkPairSortedTkVtxCov22[ID].clear();
    muonTkPairSortedTkVtxChi2[ID].clear();
    muonTkPairSortedTkVtxNdof[ID].clear();
    muonTkPairSortedTkVtxTime[ID].clear();
    muonTkPairSortedTkVtxTimeError[ID].clear();
    muonTkPairSortedTkVtxAngleXY[ID].clear();
    muonTkPairSortedTkVtxDistMagXY[ID].clear();
    muonTkPairSortedTkVtxDistMagXYSigma[ID].clear();
    muonTkPairSortedTkVtxAngleXYZ[ID].clear();
    muonTkPairSortedTkVtxDistMagXYZ[ID].clear();
    muonTkPairSortedTkVtxDistMagXYZSigma[ID].clear();
    muonTkPairSortedTk1Pt[ID].clear();
    muonTkPairSortedTk1Px[ID].clear();
    muonTkPairSortedTk1Py[ID].clear();
    muonTkPairSortedTk1Pz[ID].clear();
    muonTkPairSortedTk1P2[ID].clear();
    muonTkPairSortedTk1Eta[ID].clear();
    muonTkPairSortedTk1Phi[ID].clear();
    muonTkPairSortedTk1Charge[ID].clear();
    muonTkPairSortedTk1Chi2[ID].clear();
    muonTkPairSortedTk1Ndof[ID].clear();
    muonTkPairSortedTk2Pt[ID].clear();
    muonTkPairSortedTk2Px[ID].clear();
    muonTkPairSortedTk2Py[ID].clear();
    muonTkPairSortedTk2Pz[ID].clear();
    muonTkPairSortedTk2P2[ID].clear();
    muonTkPairSortedTk2Eta[ID].clear();
    muonTkPairSortedTk2Phi[ID].clear();
    muonTkPairSortedTk2Charge[ID].clear();
    muonTkPairSortedTk2Chi2[ID].clear();
    muonTkPairSortedTk2Ndof[ID].clear();
    muonTkPairSortedTkVtxDcaPreFit[ID].clear();
}

void MakeTopologyNtupleMiniAOD::clearMetArrays(const std::string& ID){
    // std::cout << "clearMetArrays CHECK" << std::endl;
    metE[ID] = -99999.0;
    metEt[ID] = -99999.0;
    metEtRaw[ID] = -99999.0;
    metPhi[ID] = -99999.0;
    metPt[ID] = -99999.0;
    metPx[ID] = -99999.0;
    metPy[ID] = -99999.0;
    metPz[ID] = -99999.0;
    metSignificance[ID] = -99999.0;
    metScalarEt[ID] = -99999.0;
    metEtUncorrected[ID] = -99999.0;
    metPhiUncorrected[ID] = -99999.0;
    metUnclusteredEnUp[ID] = -99999.0;
    metUnclusteredEnDown[ID] = -99999.0;
    metMaxEtEM[ID] = -99999.0;
    metMaxEtHad[ID] = -99999.0;
    metEtFracHad[ID] = -99999.0;
    metEtFracEM[ID] = -99999.0;
    metHadEtHB[ID] = -99999.0;
    metHadEtHO[ID] = -99999.0;
    metHadEtHE[ID] = -99999.0;
    metEmEtEE[ID] = -99999.0;
    metEmEtEB[ID] = -99999.0;
    metEmEtHF[ID] = -99999.0;
    metHadEtHF[ID] = -99999.0;
    genMetE[ID] = -99999.0;
    genMetEt[ID] = -99999.0;
    genMetPhi[ID] = -99999.0;
    genMetPt[ID] = -99999.0;
    genMetPx[ID] = -99999.0;
    genMetPy[ID] = -99999.0;
    genMetPz[ID] = -99999.0;
}
/////////////////////////////////////
void MakeTopologyNtupleMiniAOD::clearMCarrays(){
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
void MakeTopologyNtupleMiniAOD::clearjetarrays(const std::string& ID){
    // std::cout << "clearjetarrays CHECK" << std::endl;
    numJet[ID] = 0;
    correctedJetEts.clear();

    jetSortedE[ID].clear();
    jetSortedEt[ID].clear();
    jetSortedPt[ID].clear();
    jetSortedPtRaw[ID].clear();
    jetSortedUnCorEt[ID].clear();
    jetSortedUnCorPt[ID].clear();
    jetSortedEta[ID].clear();
    jetSortedTheta[ID].clear();
    jetSortedPhi[ID].clear();
    jetSortedPx[ID].clear();
    jetSortedPy[ID].clear();
    jetSortedPz[ID].clear();
    jetSortedMass[ID].clear();
    // jetSortedID[ID].clear();
    jetSortedClosestLepton[ID].clear();
    jetSortedNtracksInJet[ID].clear();
    jetSortedJetCharge[ID].clear();
    jetSortedfHPD[ID].clear();
    jetSortedCorrFactor[ID].clear();
    jetSortedCorrResidual[ID].clear();
    jetSortedL2L3ResErr[ID].clear();
    jetSortedCorrErrLow[ID].clear();
    jetSortedCorrErrHi[ID].clear();
    jetSortedN90Hits[ID].clear();
    jetSortedBtagSoftMuonPtRel[ID].clear();
    jetSortedBtagSoftMuonQuality[ID].clear();
    jetSortedTriggered[ID].clear();
    jetSortedSVX[ID].clear();
    jetSortedSVY[ID].clear();
    jetSortedSVZ[ID].clear();
    jetSortedSVDX[ID].clear();
    jetSortedSVDY[ID].clear();
    jetSortedSVDZ[ID].clear();
    jetSortedBIDParams_[ID].clear();
    jetSortedNConstituents[ID].clear();
    bidParamsDiscCut_[ID] = -1.0;

    for (const auto& iBtag : bTagList_) {
        bTagRes[iBtag][ID].clear();
    }

    // Calo specific
    jetSortedEMEnergyInEB[ID].clear();
    jetSortedEMEnergyInEE[ID].clear();
    jetSortedEMEnergyFraction[ID].clear();
    jetSortedEMEnergyInHF[ID].clear();
    jetSortedHadEnergyInHB[ID].clear();
    jetSortedHadEnergyInHE[ID].clear();
    jetSortedHadEnergyInHF[ID].clear();
    jetSortedHadEnergyInHO[ID].clear();
    jetSortedN60[ID].clear();
    jetSortedN90[ID].clear();
    // PF specific
    jetSortedNeutralMultiplicity[ID].clear();
    jetSortedChargedMultiplicity[ID].clear();
    jetSortedMuEnergy[ID].clear();
    jetSortedMuEnergyFraction[ID].clear();
    jetSortedNeutralHadEnergy[ID].clear();
    jetSortedNeutralEmEnergy[ID].clear();
    jetSortedChargedHadronEnergyFraction[ID].clear();
    jetSortedNeutralHadronEnergyFraction[ID].clear();
    jetSortedChargedEmEnergyFraction[ID].clear();
    jetSortedNeutralEmEnergyFraction[ID].clear();
    jetSortedMuonFraction[ID].clear();
    jetSortedChargedHadronEnergyFractionCorr[ID].clear();
    jetSortedNeutralHadronEnergyFractionCorr[ID].clear();
    jetSortedChargedEmEnergyFractionCorr[ID].clear();
    jetSortedNeutralEmEnergyFractionCorr[ID].clear();
    jetSortedMuonFractionCorr[ID].clear();

    genJetSortedE[ID].clear();
    genJetSortedEt[ID].clear();
    genJetSortedPt[ID].clear();
    genJetSortedEta[ID].clear();
    genJetSortedTheta[ID].clear();
    genJetSortedPhi[ID].clear();
    genJetSortedPx[ID].clear();
    genJetSortedPy[ID].clear();
    genJetSortedPz[ID].clear();
    genJetSortedMass[ID].clear();
    // genJetSortedID[ID].clear();
    jetSortedPID[ID].clear();
    genJetSortedPID[ID].clear();
    genJetSortedMotherPID[ID].clear();
    genJetSortedScalarAncestor[ID].clear();
    genJetSortedClosestB[ID].clear();
    genJetSortedClosestC[ID].clear();

    fixedGridRhoFastjetAll[ID] = -999.0f;
}

/////////////////////////////////////
void MakeTopologyNtupleMiniAOD::clearPVarrays() {
    // std::cout << "clearPVarrays CHECK" << std::endl;
    numPVs = 0;

    for (size_t i{0}; i < NPVSMAX; i++) {
        pvX[numPVs] = -999999;
        pvY[numPVs] = -999999;
        pvZ[numPVs] = -999999;
        pvCov00[numPVs] = 0;
        pvCov01[numPVs] = 0;
        pvCov02[numPVs] = 0;
        pvCov10[numPVs] = 0;
        pvCov11[numPVs] = 0;
        pvCov12[numPVs] = 0;
        pvCov20[numPVs] = 0;
        pvCov21[numPVs] = 0;
        pvCov20[numPVs] = 0;
        pvRho[numPVs] = -999999;
        pvNdof[numPVs] = 1;
        pvIsFake[numPVs] = -1;
        pvChi2[numPVs] = -1;
        pvNtracks[numPVs] = 0;
        pvNtracksW05[numPVs] = 0;
        pvTime[numPVs] = 0.;
        pvTimeError[numPVs] = -999999.;
    }   
}

/////////////////////////////////////

void MakeTopologyNtupleMiniAOD::clearSVarrays() {
    // std::cout << "clearSVarrays CHECK" << std::endl;
    numSVs = 0;

    for (size_t i{0}; i < NSVSMAX; i++) {
        svPt[numSVs] = -1.;
        svPx[numSVs] = -999999;
        svPy[numSVs] = -999999;
        svPz[numSVs] = -999999;
        svMass[numSVs] = 0;
        svE[numSVs] = -999999;
        svEta[numSVs] = 9999;
        svTheta[numSVs] = 9999;
        svPhi[numSVs] = 9999;
        svX[numSVs] = -999999;
        svY[numSVs] = -999999;
        svZ[numSVs] = -999999;
        svCov00[numSVs] = 0;
        svCov01[numSVs] = 0;
        svCov02[numSVs] = 0;
        svCov10[numSVs] = 0;
        svCov11[numSVs] = 0;
        svCov12[numSVs] = 0;
        svCov20[numSVs] = 0;
        svCov21[numSVs] = 0;
        svCov22[numSVs] = 0;
        svVertexChi2[numSVs] = -1.;
        svVertexNdof[numSVs] = 1.;
        svNtracks[numSVs] = 0;
        svDist3D[numSVs] = -999999;
        svDist3DSig[numSVs] = -999999;
        svDist3DError[numSVs] = 0;
        svDistXY[numSVs] = -999999;
        svDistXYSig[numSVs] = -999999;
        svDistXYError[numSVs] = 0;
        svAnglePV[numSVs] = -999999;
        svIsLambda[numSVs] = -1;
        svIsKshort[numSVs] = -1;
    }
}

/////////////////////////////////////
void MakeTopologyNtupleMiniAOD::clearGeneralTracksArrays() {
    // std::cout << "clearGeneralTracksarrays CHECK" << std::endl;
    numGeneralTracks = 0;

    for (size_t i{0}; i < NTRACKSMAX; i++) {
      generalTracksPt[i] = -1.;
      generalTracksPx[i] = -1.;
      generalTracksPy[i] = -1.;
      generalTracksPz[i] = -1.;
      generalTracksEta[i] = 9999.;
      generalTracksTheta[i] = 9999.;
      generalTracksPhi[i] = 9999.;
      generalTracksCharge[i] = 0.;
      generalTracksVx[i] = -1.;
      generalTracksVy[i] = -1.;
      generalTracksVz[i] = -1.;
      generalTracksBeamSpotCorrectedD0[i] = -9999.;
    }
}

/////////////////////////////////////
void MakeTopologyNtupleMiniAOD::clearIsolatedTracksArrays() {
    // std::cout << "clearIsolatedTracksarrays CHECK" << std::endl;
    numIsolatedTracks = 0;

    for (size_t i{0}; i < NISOTRACKSMAX; i++) {
        isoTracksPt[i] = -1.;
        isoTracksPx[i] = -1.;
        isoTracksPy[i] = -1.;
        isoTracksPz[i] = -1.;
        isoTracksE[i] = -1.;
        isoTracksEta[i] = 9999.;
        isoTracksTheta[i] = 9999.;
        isoTracksPhi[i] = 9999.;
        isoTracksCharge[i] = 0.;
        isoTracksPdgId[i] = 0.;
        isoTracksMatchedCaloJetEmEnergy[i] = -1.;
        isoTracksMatchedCaloJetHadEnergy[i] = -1.;
        isoTracksDz[i] = 9999.;
        isoTracksDxy[i] = 9999.;
        isoTracksDzError[i] = 9999.;
        isoTracksDxyError[i] = 9999.;
        isoTracksFromPV[i] = -1;
        isoTracksVx[i] = 0.;
        isoTracksVy[i] = 0.;
        isoTracksVz[i] = 0.;
        isoTracksHighPurity[i] = -1;
        isoTracksTight[i] = -1;
        isoTracksLoose[i] = -1;
        isoTracksDeltaEta[i] = 9999.;
        isoTracksDeltaPhi[i] = 9999.;
    }
}

/////////////////////////////////////

void MakeTopologyNtupleMiniAOD::clearPackedCandsArrays() {
    // std::cout << "clearPackedCandsArrays CHECK" << std::endl;
    numPackedCands = 0;

    chsTkIndices.clear();
    chsTrackRefs.clear();
    chsTransTracks.clear();

    for (size_t i{0}; i < NPACKEDCANDSMAX; i++) {
//        packedCandsPt[i] = 0.;
        packedCandsPx[i] = 0.;
        packedCandsPy[i] = 0.;
        packedCandsPz[i] = 0.;
        packedCandsE[i] = -1.;
//        packedCandsEta[i] = 9999;
//        packedCandsTheta[i] = 9999;
//        packedCandsPhi[i] = 9999;
        packedCandsCharge[i] = 0;
        packedCandsPdgId[i] = 0;
        packedCandsTime[i] = 0.;
        packedCandsFromPV[i] = -1.;
        packedCandsPVquality[i] = -1.;
        packedCandsVx[i] = 0.;
        packedCandsVy[i] = 0.;
        packedCandsVz[i] = 0.;
//        packedCandsVEta[numPackedCands] = 9999;
//        packedCandsVPhi[numPackedCands] = 9999;
//        packedCandsBeamSpotCorrectedD0[i] = -9999;
        packedCandsDz[i] = 9999;
        packedCandsDxy[i] = 9999;
//        packedCandsDzAssocPV[i] = 9999;
//        packedCandsVtxChi2Norm[i] = -9999;

        packedCandsElectronIndex[i] = -1;
        packedCandsMuonIndex[i] = -1;
//        packedCandsTauIndex[i] = -1;
        packedCandsPhotonIndex[i] = -1;
        packedCandsJetIndex[i] = -1;

        packedCandsHasTrackDetails[i] = -1;
        packedCandsDzError[i] = 9999;
        packedCandsDxyError[i] = 9999;
        packedCandsTimeError[i] = 9999;
        packedCandsPseudoTrkPt[i] = 0.;
        packedCandsPseudoTrkPx[i] = 0.;
        packedCandsPseudoTrkPy[i] = 0.;
        packedCandsPseudoTrkPz[i] = 0.;
        packedCandsPseudoTrkEta[i] = 9999;
        packedCandsPseudoTrkPhi[i] = 9999;
        packedCandsPseudoTrkCharge[i] = 0;
        packedCandsPseudoTrkVx[i] = 0.;
        packedCandsPseudoTrkVy[i] = 0.;
        packedCandsPseudoTrkVz[i] = 0.;
        packedCandsPseudoTrkChi2Norm[i] = -9999;
        packedCandsPseudoTrkNumberOfHits[i] = -1;
        packedCandsPseudoTrkNumberOfPixelHits[i] = -1;
//        packedCandsPseudoTrkPixelLayersWithMeasurement[i] = -1;
//        packedCandsPseudoTrkStripLayersWithMeasurement[i] = -1;
//        packedCandsPseudoTrkTrackerLayersWithMeasurement[i] = -1;
        packedCandsHighPurityTrack[i] = -1;
        packedCandsTrkImpactTransDist[numPackedCands] = -9999;
        packedCandsTrkImpactTransError[numPackedCands] = -9999;
        packedCandsTrkImpactTransSignificance[numPackedCands] = -9999;
        packedCandsTrk3DDist[numPackedCands] = -9999;
        packedCandsTrk3DError[numPackedCands] = -9999;
        packedCandsTrk3DSignificance[numPackedCands] = -9999;
    }

    numChsTrackPairs = 0;
    for (size_t i{0}; i < NCHSTKPAIRMAX; i++) {
        chsTkPairIndex1[i] = -1; 
        chsTkPairIndex2[i] = -1;
        chsTkPairTkVtxPx[i] = 0.;
        chsTkPairTkVtxPy[i] = 0.;
        chsTkPairTkVtxPz[i] = 0.;
        chsTkPairTkVtxP2[i] = 0.;
        chsTkPairTkVx[i] = 0.;
        chsTkPairTkVy[i] = 0.;                                   
        chsTkPairTkVz[i] = 0.;
        chsTkPairTkVtxCov00[i] = 0.;
        chsTkPairTkVtxCov01[i] = 0.;
        chsTkPairTkVtxCov02[i] = 0.;
        chsTkPairTkVtxCov10[i] = 0.;
        chsTkPairTkVtxCov11[i] = 0.;
        chsTkPairTkVtxCov12[i] = 0.;
        chsTkPairTkVtxCov20[i] = 0.;
        chsTkPairTkVtxCov21[i] = 0.;
        chsTkPairTkVtxCov22[i] = 0.;
        chsTkPairTkVtxChi2[i] = -9999.;
        chsTkPairTkVtxNdof[i] = 0.;
        chsTkPairTkVtxTime[i] = 0.;
        chsTkPairTkVtxTimeError[i] = 0.;
        chsTkPairTkVtxAngleXY[i] = 0.;
        chsTkPairTkVtxDistMagXY[i] = 0.;
        chsTkPairTkVtxDistMagXYSigma[i] = 0.;
        chsTkPairTkVtxAngleXYZ[i] = 0.;
        chsTkPairTkVtxDistMagXYZ[i] = 0.;
        chsTkPairTkVtxDistMagXYZSigma[i] = 0.;
        chsTkPairTk1Pt[i] = 0.;
        chsTkPairTk1Px[i] = 0.;
        chsTkPairTk1Py[i] = 0.;
        chsTkPairTk1Pz[i] = 0.;
        chsTkPairTk1P2[i] = -1.;
        chsTkPairTk1Eta[i] = 9999.;
        chsTkPairTk1Phi[i] = 9999.;
        chsTkPairTk1Charge[i] = 0;
        chsTkPairTk1Chi2[i] = -9999.;
        chsTkPairTk1Ndof[i] = 0.;
        chsTkPairTk2Pt[i] = 0.;
        chsTkPairTk2Px[i] = 0.;
        chsTkPairTk2Py[i] = 0.;
        chsTkPairTk2Pz[i] = 0.;
        chsTkPairTk2P2[i] = -1.;
        chsTkPairTk2Eta[i] = 9999.;
        chsTkPairTk2Phi[i] = 9999.;
        chsTkPairTk2Charge[i] = 0;
        chsTkPairTk2Chi2[i] = -9999.;
        chsTkPairTk2Ndof[i] = 0.;
        chsTkPairTkVtxDcaPreFit[i] = -9999.;
    }
}

/////////////////////////////////////
void MakeTopologyNtupleMiniAOD::cleararrays() {
    // reset the bookkeeping bools;
    // std::cout << "cleararrays CHECK" << std::endl;
    // std::cout << "before FALSE: " << ran_postloop_ << std::endl;
    ran_jetloop_ = ran_eleloop_ = ran_muonloop_ = ran_PV_ = ran_BS_ = ran_tracks_ = ran_isotracks_ = ran_packedCands_ = ran_mcloop_ = ran_postloop_ = ran_photonTau_ = false;
    // std::cout << "psot FALSE: " << ran_postloop_ << std::endl;

    clearPVarrays();
    clearSVarrays();

    for (size_t iTrig{0}; iTrig < triggerList_.size(); iTrig++) { 
        triggerRes[iTrig] = -99;
    }
    for (size_t iMetFilter{0}; iMetFilter < metFilterList_.size(); iMetFilter++) {
        metFilterRes[iMetFilter] = -99;
    }

    for (int& HLT_fakeTriggerValue : HLT_fakeTriggerValues) {
        HLT_fakeTriggerValue = -99;
    }
    for (size_t ii{0}; ii < 200; ii++)  {
        TriggerBits[ii] = -99;
    }

    clearjetarrays("Calo");
    clearelectronarrays("Calo");
    clearmuonarrays("Calo");
    clearMetArrays("Calo");
//    clearTauArrays("Calo");
//    clearPhotonArrays("Calo");

    clearjetarrays("PF");
    clearelectronarrays("PF");
    clearmuonarrays("PF");
    clearMetArrays("PF");
    clearTauArrays("PF");
    clearPhotonArrays("PF");

    clearjetarrays("AK5PF");

    clearjetarrays("JPT");
    clearMetArrays("JPT");

    clearMCarrays();
//    clearGeneralTracksArrays();
//    clearIsolatedTracksArrays();
//    clearLostTracksArrays();
    clearPackedCandsArrays();

    mhtSignif = -1;
    mhtPx = -9999.;
    mhtPy = -9999.;
    mhtPhi = -9999.;
    mhtSumEt = -1;
    mhtPt = -1;

    // metSignificance = -9999.; // metHandle->front().metSignificance();
    // metScalarEt = -9999.; // metHandle->front().sumEt();
    // metEtUncorrected = -9999.; // metHandle->front().uncorrectedPt();
    // metPhiUncorrected = -9999.; // metHandle->front().uncorrectedPhi();

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
void MakeTopologyNtupleMiniAOD::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
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

    fillPV(iEvent,iSetup);
    fillSV(iEvent,iSetup);

    fillTriggerData(iEvent);
    fillBeamSpot(iEvent, iSetup);

//    fillGeneralTracks(iEvent, iSetup);
//    fillIsolatedTracks(iEvent, iSetup);
//    fillLostTracksCands(iEvent, iSetup);
    fillPackedCands(iEvent, iSetup);

    // std::cout << "done with trigger and beam spot" << std::endl;

    // Here I am taking out the Calo and JPT stuff. I don't think this should
    // matter, as I'm only using PF things. If it turns out to be a problem I
    // can add them back in later.

    // fillMuons(iEvent, iSetup, muoLabel_, "Calo");
    fillMuons           (iEvent, iSetup, patMuonsToken_, "PF");

    fillElectrons(iEvent, iSetup, patElectronsToken_, "PF", eleLabel_);
//    fillPhotons(iEvent, iSetup, patPhotonsToken_, "PF", phoLabel_);
//    fillPhotons(iEvent, iSetup, patOOTphotonsToken_, "OOT", ootPhoLabel_);

    // fillJets(iEvent, iSetup, jetLabel_, "Calo");
    // Putting MET info before jets so it can be used for jet smearing.
    fillMissingET(iEvent, iSetup, patMetToken_, "PF");

    fillJets(iEvent, iSetup, patJetsToken_, "PF");

    // fillJets(iEvent, iSetup, jetPFRecoTag_, "AK5PF");
    // fillJets(iEvent, iSetup, jetJPTTag_, "JPT");
    //
    // std::cout << "done with jets" << std::endl;

    // fillElectrons(iEvent, iSetup, eleLabel_, "Calo");
    fillMCInfo(iEvent, iSetup);
    // fillMissingET(iEvent, iSetup, metLabel_, "Calo");
    //
    // fillMissingET(iEvent, iSetup, metJPTTag_, "JPT");
    // fillPackedCands(iEvent, iSetup);

    fillSummaryVariables();

    // std::cout << "done with topology, now filling tree..." << std::endl;
    // std::cout << numEle["PF"] << std::endl;
    // Run the cut flow code. This involves event selections and seeing how many
    // events containing things we get. Eventually this will require me putting
    // in different selections for the different channels, but for now just
    // double electron.

    if (!doCuts_) {
        mytree_->Fill(); // If not doing cuts, fill up EVERYTHING
    }
    else  { // If doing cuts, ensure that we have at least x leptons which meet minimum sensible criteria

        bool passMuonCuts {false};

        for (int j{0}; j < numMuo["PF"]; j++) {
            if ( std::abs(muonSortedEta["PF"][j]) > muoEtaCut_ ) continue;
            for (int k{j+1}; k < numMuo["PF"]; k++) {
                if ( std::abs(muonSortedEta["PF"][k]) > muoEtaCut_ ) continue;
                TLorentzVector muon1{ muonSortedPx["PF"][j], muonSortedPy["PF"][j], muonSortedPz["PF"][j], muonSortedE["PF"][j] };
                TLorentzVector muon2{ muonSortedPx["PF"][k], muonSortedPy["PF"][k], muonSortedPz["PF"][k], muonSortedE["PF"][k] };
                if ( muon1.Pt() > muon2.Pt() ) {
                    if ( muon1.Pt() < muoPt1Cut_ || muon2.Pt() < muoPt2Cut_ ) continue;
                }
                else {
                    if ( muon1.Pt() < muoPt2Cut_ || muon1.Pt() < muoPt2Cut_ ) continue;
                }
                double invMass { (muon1+muon2).M() };
                if (invMass <= invMuMuMassCut_) {
                    passMuonCuts = true;
                    break;
                }
            }
            if ( passMuonCuts ) break;
        }

        if (passMuonCuts) mytree_->Fill();
    }

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

void MakeTopologyNtupleMiniAOD::bookBranches() {
    // std::cout << "bookBranches CHECK" << std::endl;
    TTree::SetMaxTreeSize(std::numeric_limits<Long64_t>::max());
    mytree_ = new TTree("tree", "tree");
    mytree_->SetAutoSave(-std::numeric_limits<Long64_t>::max());

    // bookElectronBranches("Calo", "Calo");
    // bookMuonBranches("Calo", "Calo");
    // bookJetBranches("Calo", "Calo");
    // bookMETBranches("Calo", "Calo");
    // bookTauBranches("Calo", "Calo");
    // bookPhotonBranches("Calo", "Calo");

    bookElectronBranches("PF", "PF2PAT");
    bookMuonBranches("PF", "PF2PAT");
    bookJetBranches("PF", "PF2PAT");
    bookPFJetBranches("PF", "PF2PAT");
    bookMETBranches("PF", "PF2PAT");
//    bookTauBranches("PF", "PF2PAT");
    bookPhotonBranches("PF", "PF2PAT");
//    bookPhotonBranches("OOT", "OOT_PF2PAT");

    // bookJetBranches("AK5PF", "AK5PF");
    // bookPFJetBranches("AK5PF", "AK5PF");
    // bookJetBranches("JPT", "JPT");
    // bookMETBranches("JPT", "TC");

//    bookGeneralTracksBranches();
//    bookIsolatedTracksBranches();
//    bookLostTracksBranches();
    bookPackedCandsBranches();
    if (runMCInfo_) {
        bookMCBranches();
    }

    mytree_->Branch("processId", &processId_, "processId/I");
    mytree_->Branch("processPtHat", &processPtHat_, "processPtHat/F");
    mytree_->Branch("processMCWeight", &weight_, "processMCWeight/D");

    mytree_->Branch("beamSpotX", &beamSpotX, "beamSpotX/F");
    mytree_->Branch("beamSpotY", &beamSpotY, "beamSpotY/F");
    mytree_->Branch("beamSpotZ", &beamSpotZ, "beamSpotZ/F");

    bookPVbranches();
    bookSVbranches();

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

void MakeTopologyNtupleMiniAOD::bookTauBranches(const std::string& ID, const std::string& name){
    numTaus[ID] = 0;

    std::vector<float> tempVecF(NTAUSMAX);
    tau_e[ID] = tempVecF;
    tau_phi[ID] = tempVecF;
    tau_eta[ID] = tempVecF;
    tau_pt[ID] = tempVecF;

    mytree_->Branch(("numTau" + name).c_str(), &numTaus[ID], ("numTau" + name + "/I").c_str());

    std::string prefix{"tau" + name};
    mytree_->Branch((prefix + "E").c_str(), &tau_e[ID][0], (prefix + "E[numTau" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Pt").c_str(), &tau_pt[ID][0], (prefix + "Pt[numTau" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Phi").c_str(), &tau_phi[ID][0], (prefix + "Phi[numTau" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Eta").c_str(), &tau_eta[ID][0], (prefix + "Eta[numTau" + name + "]/F").c_str());
}

// book photon branches:
void MakeTopologyNtupleMiniAOD::bookPhotonBranches(const std::string& ID, const std::string& name) {
    // Initialise maps so ROOT wont panic
    std::vector<float> tempVecF(NPHOTONSMAX);
    std::vector<int> tempVecI(NPHOTONSMAX);
    boost::container::vector<bool> tempVecB(NPHOTONSMAX);

    numPho[ID] = -1;

    photonSortedE[ID] = tempVecF;
    photonSortedSigmaE[ID] = tempVecF;
    photonSortedET[ID] = tempVecF;
    photonSortedPhi[ID] = tempVecF;
    photonSortedEta[ID] = tempVecF;
    photonSortedTheta[ID] = tempVecF;
    photonSortedPt[ID] = tempVecF;
    photonSortedPx[ID] = tempVecF;
    photonSortedPy[ID] = tempVecF;
    photonSortedPz[ID] = tempVecF;
    photonSortedCalibE[ID] = tempVecF;
    photonSortedCalibEt[ID] = tempVecF;
    photonSortedSCE[ID] = tempVecF;
    photonSortedSCRawE[ID] = tempVecF;
    photonSortedESEnP1[ID] = tempVecF;
    photonSortedESEnP2[ID] = tempVecF;
    photonSortedSCEta[ID] = tempVecF;
    photonSortedSCEtaWidth[ID] = tempVecF;
    photonSortedSCPhi[ID] = tempVecF;
    photonSortedSCPhiWidth[ID] = tempVecF;
    photonSortedSCBrem[ID] = tempVecF;
    photonSortedHasPixelSeed[ID] = tempVecI;
    photonSortedEleVeto[ID] = tempVecI;
    photonSortedR9[ID] = tempVecF;
    photonSortedHoverE[ID] = tempVecF;
    photonSortedESEffSigmaRR[ID] = tempVecF;
    photonSortedSigmaIEtaIEtaFull5x5[ID] = tempVecF;
    photonSortedSigmaIEtaIPhiFull5x5[ID] = tempVecF;
    photonSortedSigmaIPhiIPhiFull5x5[ID] = tempVecF;
    photonSortedE2x2Full5x5[ID] = tempVecF;
    photonSortedE5x5Full5x5[ID] = tempVecF;
    photonSortedR9Full5x5[ID] = tempVecF;
    photonSortedPFChIso[ID] = tempVecF;
    photonSortedPFPhoIso[ID] = tempVecF;
    photonSortedPFNeuIso[ID] = tempVecF;
    photonSortedPFChWorstIso[ID] = tempVecF;
    photonSortedMIPTotEnergy[ID] = tempVecF;    
    photonSortedCutIdLoose[ID] = tempVecI;
    photonSortedCutIdMedium[ID] = tempVecI;
    photonSortedCutIdTight[ID] = tempVecI;     
    photonSortedMvaIdWp80[ID] = tempVecI;
    photonSortedMvaIdWp90[ID] = tempVecI;

    photonSortedNumSourceCandidates[ID] = tempVecI;
    photonSortedPackedCandIndex[ID] = tempVecI;

    genPhotonSortedPt[ID] = tempVecF;
    genPhotonSortedET[ID] = tempVecF;
    genPhotonSortedEta[ID] = tempVecF;
    genPhotonSortedTheta[ID] = tempVecF;
    genPhotonSortedPhi[ID] = tempVecF;
    genPhotonSortedPx[ID] = tempVecF;
    genPhotonSortedPy[ID] = tempVecF;
    genPhotonSortedPz[ID] = tempVecF;
    genPhotonSortedCharge[ID] = tempVecI;
    genPhotonSortedPdgId[ID] = tempVecI;
    genPhotonSortedMotherId[ID] = tempVecI;
    genPhotonSortedIsPhoton[ID] = tempVecI;
    genPhotonSortedIsConvertedPhoton[ID] = tempVecI;
    genPhotonSortedIsJet[ID] = tempVecI;
//    genPhotonSortedPromptDecayed[ID] = tempVecI;
//    genPhotonSortedPromptFinalState[ID] = tempVecI;
//    genPhotonSortedHardProcess[ID] = tempVecI;
//    genPhotonSortedPythiaSixStatusThree[ID] = tempVecI;
    genPhotonSortedScalarAncestor[ID] = tempVecI;
    genPhotonSortedDirectScalarAncestor[ID] = tempVecI;

    std::string prefix{"pho" + name};
    mytree_->Branch(("numPho" + name).c_str(),
                    &numPho[ID],
                    ("numPho" + name + "/I").c_str());

    // Dynamic ID's
    mytree_->Branch((prefix + "E").c_str(),
                    &photonSortedE[ID][0],
                    (prefix + "E[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SigmaE").c_str(),
                    &photonSortedSigmaE[ID][0],
                    (prefix + "SigmaE[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "ET").c_str(),
                    &photonSortedET[ID][0],
                    (prefix + "ET[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Phi").c_str(),
                    &photonSortedPhi[ID][0],
                    (prefix + "Phi[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Eta").c_str(),
                    &photonSortedEta[ID][0],
                    (prefix + "Eta[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Theta").c_str(),
                    &photonSortedTheta[ID][0],
                    (prefix + "Theta[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Pt").c_str(),
                    &photonSortedPt[ID][0],
                    (prefix + "Pt[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Px").c_str(),
                    &photonSortedPx[ID][0],
                    (prefix + "Px[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Py").c_str(),
                    &photonSortedPy[ID][0],
                    (prefix + "Py[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Pz").c_str(),
                    &photonSortedPz[ID][0],
                    (prefix + "Pz[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "CalibE").c_str(),
                    &photonSortedCalibE[ID][0],
                    (prefix + "CalibE[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "CalibEt").c_str(),
                    &photonSortedCalibEt[ID][0],
                    (prefix + "CalibEt[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SCE").c_str(),
                    &photonSortedSCE[ID][0],
                    (prefix + "SCE[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SCRawE").c_str(),
                    &photonSortedSCRawE[ID][0],
                    (prefix + "SCRawE[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "ESEnP1").c_str(),
                    &photonSortedESEnP1[ID][0],
                    (prefix + "ESEnP1[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "ESEnP2").c_str(),
                    &photonSortedESEnP2[ID][0],
                    (prefix + "ESEnP2[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SCEta").c_str(),
                    &photonSortedSCEta[ID][0],
                    (prefix + "SCEta[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SCEtaWidth").c_str(),
                    &photonSortedSCEtaWidth[ID][0],
                    (prefix + "SCEtaWidth[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SCPhi").c_str(),
                    &photonSortedSCPhi[ID][0],
                    (prefix + "SCPhi[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SCPhiWidth").c_str(),
                    &photonSortedSCPhiWidth[ID][0],
                    (prefix + "SCPhiWidth[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SCBrem").c_str(),
                    &photonSortedSCBrem[ID][0],
                    (prefix + "SCBrem[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "HasPixelSeed").c_str(),
                    &photonSortedHasPixelSeed[ID][0],
                    (prefix + "HasPixelSeed[numPho" + name + "]/I").c_str());
    mytree_->Branch((prefix + "EleVeto").c_str(),
                    &photonSortedEleVeto[ID][0],
                    (prefix + "EleVeto[numPho" + name + "]/I").c_str());
    mytree_->Branch((prefix + "R9").c_str(),
                    &photonSortedR9[ID][0],
                    (prefix + "R9[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "HoverE").c_str(),
                    &photonSortedHoverE[ID][0],
                    (prefix + "HoverE[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "ESEffSigmaRR").c_str(),
                    &photonSortedESEffSigmaRR[ID][0],
                    (prefix + "ESEffSigmaRR[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SigmaIEtaIEtaFull5x5").c_str(),
                    &photonSortedSigmaIEtaIEtaFull5x5[ID][0],
                    (prefix + "SigmaIEtaIEtaFull5x5[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SigmaIEtaIPhiFull5x5").c_str(),
                    &photonSortedSigmaIEtaIPhiFull5x5[ID][0],
                    (prefix + "SigmaIEtaIPhiFull5x5[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SigmaIPhiIPhiFull5x5").c_str(),
                    &photonSortedSigmaIPhiIPhiFull5x5[ID][0],
                    (prefix + "SigmaIPhiIPhiFull5x5[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "E2x2Full5x5").c_str(),
                    &photonSortedE2x2Full5x5[ID][0],
                    (prefix + "E2x2Full5x5[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "E5x5Full5x5").c_str(),
                    &photonSortedE5x5Full5x5[ID][0],
                    (prefix + "E5x5Full5x5[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "R9Full5x5").c_str(),
                    &photonSortedR9Full5x5[ID][0],
                    (prefix + "R9Full5x5[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "PFChIso").c_str(),
                    &photonSortedPFChIso[ID][0],
                    (prefix + "PFChIso[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "PFPhoIso").c_str(),
                    &photonSortedPFPhoIso[ID][0],
                    (prefix + "PFPhoIso[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "PFNeuIso").c_str(),
                    &photonSortedPFNeuIso[ID][0],
                    (prefix + "PFNeuIso[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "PFChWorstIso").c_str(),
                    &photonSortedPFChWorstIso[ID][0],
                    (prefix + "PFChWorstIso[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "MIPTotEnergy").c_str(),
                    &photonSortedMIPTotEnergy[ID][0],
                    (prefix + "MIPTotEnergy[numPho" + name + "]/F").c_str());
    mytree_->Branch((prefix + "CutIdLoose").c_str(),
                    &photonSortedCutIdLoose[ID][0],
                    (prefix + "CutIdLoose[numPho" + name + "]/I").c_str());
    mytree_->Branch((prefix + "CutIdMedium").c_str(),
                    &photonSortedCutIdMedium[ID][0],
                    (prefix + "CutIdMedium[numPho" + name + "]/I").c_str());
    mytree_->Branch((prefix + "CutIdTight").c_str(),
                    &photonSortedCutIdTight[ID][0],
                    (prefix + "CutIdTight[numPho" + name + "]/I").c_str());
    mytree_->Branch((prefix + "MvaIdWp80").c_str(),
                    &photonSortedMvaIdWp80[ID][0],
                    (prefix + "MvaIdWp80[numPho" + name + "]/I").c_str());
    mytree_->Branch((prefix + "MvaIdWp90").c_str(),
                    &photonSortedMvaIdWp90[ID][0],
                    (prefix + "MvaIdWp90[numPho" + name + "]/I").c_str());

    mytree_->Branch((prefix + "NumSourceCandidates").c_str(), &photonSortedNumSourceCandidates[ID][0], (prefix + "NumSourceCandidates[numPho" + name + "]/I").c_str());
    mytree_->Branch((prefix + "PackedCandIndex").c_str(), &photonSortedPackedCandIndex[ID][0], (prefix + "PackedCandIndex[numPho" + name + "]/I").c_str());

    // gen branches
    if (runMCInfo_) {
      mytree_->Branch(("genPho" + name + "Pt").c_str(),
		      &genPhotonSortedPt[ID][0],
		      ("genPho" + name + "PhoPT[numPho" + name + "]/F").c_str());
      mytree_->Branch(("genPho" + name + "ET").c_str(),
                      &genPhotonSortedET[ID][0],
                      ("genPho" + name + "PhoET[numPho" + name + "]/F").c_str());
      mytree_->Branch(("genPho" + name + "Eta").c_str(),
                      &genPhotonSortedEta[ID][0],
                      ("genPho" + name + "PhoEta[numPho" + name + "]/F").c_str());
      mytree_->Branch(("genPho" + name + "Theta").c_str(),
                      &genPhotonSortedTheta[ID][0],
                      ("genPho" + name + "PhoTheta[numPho" + name + "]/F").c_str());
      mytree_->Branch(("genPho" + name + "Phi").c_str(),
                      &genPhotonSortedPhi[ID][0],
                      ("genPho" + name + "PhoPhi[numPho" + name + "]/F").c_str());
      mytree_->Branch(("genPho" + name + "Px").c_str(),
                      &genPhotonSortedPx[ID][0],
                      ("genPho" + name + "PhoPx[numPho" + name + "]/F").c_str());
      mytree_->Branch(("genPho" + name + "Py").c_str(),
                      &genPhotonSortedPy[ID][0],
                      ("genPho" + name + "PhoPy[numPho" + name + "]/F").c_str());
      mytree_->Branch(("genPho" + name + "Pz").c_str(),
                      &genPhotonSortedPz[ID][0],
                      ("genPho" + name + "PhoPz[numPho" + name + "]/F").c_str());
      mytree_->Branch(("genPho" + name + "Charge").c_str(),
                      &genPhotonSortedCharge[ID][0],
                      ("genPho" + name + "PhoCharge[numPho" + name + "]/I").c_str());
      mytree_->Branch(("genPho" + name + "PdgId").c_str(),
                      &genPhotonSortedPdgId[ID][0],
                      ("genPho" + name + "PhoPdgId[numPho" + name + "]/I").c_str());
      mytree_->Branch(("genPho" + name + "MotherId").c_str(),
                      &genPhotonSortedMotherId[ID][0],
                      ("genPho" + name + "PhoMotherId[numPho" + name + "]/I").c_str());
      mytree_->Branch(("genPho" + name + "IsPhoton").c_str(),
                      &genPhotonSortedIsPhoton[ID][0],
                      ("genPho" + name + "PhoIsPhoton[numPho" + name + "]/I").c_str());
      mytree_->Branch(("genPho" + name + "IsConvertedPhoton").c_str(),
                      &genPhotonSortedIsConvertedPhoton[ID][0],
                      ("genPho" + name + "PhoIsConvertedPhoton[numPho" + name + "]/I").c_str());
      mytree_->Branch(("genPho" + name + "IsJet").c_str(),
                      &genPhotonSortedIsJet[ID][0],
                      ("genPho" + name + "PhoIsJet[numPho" + name + "]/I").c_str());
//      mytree_->Branch(("genPho" + name + "PromptDecayed").c_str(),
//                      &genPhotonSortedPromptDecayed[ID][0],
//                      ("genPho" + name + "PromptDecayed[numPho" + name + "]/I").c_str());
//      mytree_->Branch(("genPho" + name + "PromptFinalState").c_str(),
//                      &genPhotonSortedPromptFinalState[ID][0],
//                      ("genPho" + name + "PromptFinalState[numPho" + name + "]/I").c_str());
//      mytree_->Branch(("genPho" + name + "HardProcess").c_str(),
//                      &genPhotonSortedHardProcess[ID][0],
//                      ("genPho" + name + "HardProcess[numPho" + name + "]/I").c_str());
//      mytree_->Branch(("genPho" + name + "PythiaSixStatusThree").c_str(),
//                      &genPhotonSortedPythiaSixStatusThree[ID][0],
//                      ("genPho" + name + "PythiaSixStatusThree[numPho" + name + "]/I").c_str());
      mytree_->Branch(("genPho" + name + "ScalarAncestor").c_str(),
                      &genPhotonSortedScalarAncestor[ID][0],
                      ("genPho" + name + "ScalarAncestor[numPho" + name + "]/I").c_str());
      mytree_->Branch(("genPho" + name + "DirectScalarAncestor").c_str(),
                      &genPhotonSortedDirectScalarAncestor[ID][0],
                      ("genPho" + name + "DirectScalarAncestor[numPho" + name + "]/I").c_str());
    }
}

// book electron branches:
void MakeTopologyNtupleMiniAOD::bookElectronBranches(const std::string& ID, const std::string& name) {
    // Initialise maps so ROOT wont panic
    std::vector<float> tempVecF(NELECTRONSMAX);
    std::vector<int> tempVecI(NELECTRONSMAX);
    boost::container::vector<bool> tempVecB(NELECTRONSMAX);

    numEle[ID] = -1;

    electronSortedCharge[ID] = tempVecI;

    electronSortedIsBarrel[ID] = tempVecI;
    electronSortedPhotonConversionTag[ID] = tempVecI;
//    electronSortedPhotonConversionTagCustom[ID] = tempVecI;
    electronSortedMissingInnerLayers[ID] = tempVecI;

    electronSortedE[ID] = tempVecF;
    electronSortedEt[ID] = tempVecF;
    electronSortedEta[ID] = tempVecF;
    electronSortedPt[ID] = tempVecF;
    electronSortedTheta[ID] = tempVecF;
    electronSortedPhi[ID] = tempVecF;
    electronSortedPx[ID] = tempVecF;
    electronSortedPy[ID] = tempVecF;
    electronSortedPz[ID] = tempVecF;

    electronSortedCutIdVeto[ID] = tempVecI;
    electronSortedCutIdLoose[ID] = tempVecI;
    electronSortedCutIdMedium[ID] = tempVecI;
    electronSortedCutIdTight[ID] = tempVecI;
    electronSortedMvaIdWp80[ID] = tempVecI;
    electronSortedMvaIdWp90[ID] = tempVecI;
    electronSortedMvaIdWpLoose[ID] = tempVecI;

    electronSortedChargedHadronIso[ID] = tempVecF;
    electronSortedNeutralHadronIso[ID] = tempVecF;
    electronSortedPhotonIso[ID] = tempVecF;

    electronSortedTrackPt[ID] = tempVecF;
    electronSortedTrackEta[ID] = tempVecF;
    electronSortedTrackPhi[ID] = tempVecF;
    electronSortedTrackChi2[ID] = tempVecF;
    electronSortedTrackNDOF[ID] = tempVecF;
    electronSortedTrackD0[ID] = tempVecF;
    electronSortedDBBeamSpotCorrectedTrackD0[ID] = tempVecF;

    // electronSortedDBInnerTrackD0[ID] = tempVecF;

    electronSortedBeamSpotCorrectedTrackD0[ID] = tempVecF;
    electronSortedTrackDz[ID] = tempVecF;
    electronSortedTrackD0PV[ID] = tempVecF;
    electronSortedTrackDZPV[ID] = tempVecF;
    electronSortedVtxZ[ID] = tempVecF;
    electronSortedBeamSpotCorrectedTrackDz[ID] = tempVecF;
    electronSortedIsGsf[ID] = tempVecI;
    electronSortedGsfPx[ID] = tempVecF;
    electronSortedGsfPy[ID] = tempVecF;
    electronSortedGsfPz[ID] = tempVecF;
    electronSortedGsfE[ID] = tempVecF;
    electronSortedEcalEnergy[ID] = tempVecF;

    electronSortedSuperClusterEta[ID] = tempVecF;
    electronSortedSuperClusterE[ID] = tempVecF;
    electronSortedSuperClusterPhi[ID] = tempVecF;
    electronSortedSuperClusterEoverP[ID] = tempVecF;
    electronSortedSuperClusterSigmaEtaEta[ID] = tempVecF;
    electronSortedSuperClusterE1x5[ID] = tempVecF;
    electronSortedSuperClusterE2x5max[ID] = tempVecF;
    electronSortedSuperClusterE5x5[ID] = tempVecF;
    electronSortedSuperClusterSigmaIEtaIEta[ID] = tempVecF;
    electronSortedSuperClusterSigmaIEtaIEta5x5[ID] = tempVecF;
    electronSortedTrackIso04[ID] = tempVecF;
    electronSortedECalIso04[ID] = tempVecF;
    electronSortedHCalIso04[ID] = tempVecF;
    electronSortedTrackIso03[ID] = tempVecF;
    electronSortedECalIso03[ID] = tempVecF;
    electronSortedHCalIso03[ID] = tempVecF;
    electronSorteddr04EcalRecHitSumEt[ID] = tempVecF;
    electronSorteddr03EcalRecHitSumEt[ID] = tempVecF;
    electronSortedECalIsoDeposit[ID] = tempVecF;
    electronSortedHCalIsoDeposit[ID] = tempVecF;
    electronSortedCaloIso[ID] = tempVecF;
    electronSortedTriggerMatch[ID] = tempVecF;
    electronSortedJetOverlap[ID] = tempVecF;
    electronSortedComRelIso[ID] = tempVecF;
    electronSortedComRelIsodBeta[ID] = tempVecF;
    electronSortedComRelIsoRho[ID] = tempVecF;
    electronSortedChHadIso[ID] = tempVecF;
    electronSortedNtHadIso[ID] = tempVecF;
    electronSortedGammaIso[ID] = tempVecF;
    electronSortedRhoIso[ID] = tempVecF;
    electronSortedAEff03[ID] = tempVecF;
    electronSortedHoverE[ID] = tempVecF;
    electronSortedDeltaPhiSC[ID] = tempVecF;
    electronSortedDeltaEtaSC[ID] = tempVecF;
    electronSortedDeltaEtaSeedSC[ID] = tempVecF;
    electronSortedPhotonConversionDcot[ID] = tempVecF;
    electronSortedPhotonConversionDist[ID] = tempVecF;
    electronSortedPhotonConversionVeto[ID] = tempVecI;
    electronSortedPhotonConversionDcotCustom[ID] = tempVecF;
    electronSortedPhotonConversionDistCustom[ID] = tempVecF;
    electronSortedImpactTransDist[ID] = tempVecF;
    electronSortedImpactTransError[ID] = tempVecF;
    electronSortedImpactTransSignificance[ID] = tempVecF;
    electronSortedImpact3DDist[ID] = tempVecF;
    electronSortedImpact3DError[ID] = tempVecF;
    electronSortedImpact3DSignificance[ID] = tempVecF;

    electronSortedNumSourceCandidates[ID] = tempVecI;
    electronSortedPackedCandIndex[ID] = tempVecI;

    genElectronSortedPt[ID] = tempVecF;
    genElectronSortedEt[ID] = tempVecF;
    genElectronSortedEta[ID] = tempVecF;
    genElectronSortedTheta[ID] = tempVecF;
    genElectronSortedPhi[ID] = tempVecF;
    genElectronSortedPx[ID] = tempVecF;
    genElectronSortedPy[ID] = tempVecF;
    genElectronSortedPz[ID] = tempVecF;
    genElectronSortedCharge[ID] = tempVecI;
    genElectronSortedPdgId[ID] = tempVecI;
    genElectronSortedMotherId[ID] = tempVecI;
    genElectronSortedPromptDecayed[ID] = tempVecI;
    genElectronSortedPromptFinalState[ID] = tempVecI;
    genElectronSortedHardProcess[ID] = tempVecI;
    genElectronSortedPythiaSixStatusThree[ID] = tempVecI;
    genElectronSortedScalarAncestor[ID] = tempVecI;
    genElectronSortedDirectScalarAncestor[ID] = tempVecI;

    std::string prefix{"ele" + name};
    mytree_->Branch(("numEle" + name).c_str(),
                    &numEle[ID],
                    ("numEle" + name + "/I").c_str());

    // Dynamic ID's

    mytree_->Branch((prefix + "E").c_str(),
                    &electronSortedE[ID][0],
                    (prefix + "E[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "ET").c_str(),
                    &electronSortedEt[ID][0],
                    (prefix + "ET[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "PX").c_str(),
                    &electronSortedPx[ID][0],
                    (prefix + "PX[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "PY").c_str(),
                    &electronSortedPy[ID][0],
                    (prefix + "PY[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "PZ").c_str(),
                    &electronSortedPz[ID][0],
                    (prefix + "PZ[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Phi").c_str(),
                    &electronSortedPhi[ID][0],
                    (prefix + "Phi[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Theta").c_str(),
                    &electronSortedTheta[ID][0],
                    (prefix + "Theta[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Eta").c_str(),
                    &electronSortedEta[ID][0],
                    (prefix + "Eta[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "PT").c_str(),
                    &electronSortedPt[ID][0],
                    (prefix + "PT[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Charge").c_str(),
                    &electronSortedCharge[ID][0],
                    (prefix + "Charge[numEle" + name + "]/I").c_str());

    mytree_->Branch((prefix + "CutIdVeto").c_str(),
                    &electronSortedCutIdVeto[ID][0],
                    (prefix + "CutIdVeto[numEle" + name + "]/I").c_str());
    mytree_->Branch((prefix + "CutIdLoose").c_str(),
                    &electronSortedCutIdLoose[ID][0],
                    (prefix + "CutIdLoose[numEle" + name + "]/I").c_str());
    mytree_->Branch((prefix + "CutIdMedium").c_str(),
                    &electronSortedCutIdMedium[ID][0],
                    (prefix + "CutIdMedium[numEle" + name + "]/I").c_str());
    mytree_->Branch((prefix + "CutIdTight").c_str(),
                    &electronSortedCutIdTight[ID][0],
                    (prefix + "CutIdTight[numEle" + name + "]/I").c_str());
    mytree_->Branch((prefix + "MvaIdWp80").c_str(),
                    &electronSortedMvaIdWp80[ID][0],
                    (prefix + "MvaIdWp80[numEle" + name + "]/I").c_str());
    mytree_->Branch((prefix + "MvaIdWp90").c_str(),
       	       	    &electronSortedMvaIdWp90[ID][0],
                    (prefix + "MvaIdWp90[numEle" + name + "]/I").c_str());
    mytree_->Branch((prefix + "MvaIdWpLoose").c_str(),
                    &electronSortedMvaIdWpLoose[ID][0],
                    (prefix + "MvaIdWpLoose[numEle" + name + "]/I").c_str());

    mytree_->Branch((prefix + "ImpactTransDist").c_str(),
                    &electronSortedImpactTransDist[ID][0],
                    (prefix + "ImpactTransDist[numEle" + name + "]/F").c_str());
    mytree_->Branch(
        (prefix + "ImpactTransError").c_str(),
        &electronSortedImpactTransError[ID][0],
        (prefix + "ImpactTransError[numEle" + name + "]/F").c_str());
    mytree_->Branch(
        (prefix + "ImpactTransSignificance").c_str(),
        &electronSortedImpactTransSignificance[ID][0],
        (prefix + "ImpactTransSignificance[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Impact3DDist").c_str(),
                    &electronSortedImpact3DDist[ID][0],
                    (prefix + "Impact3DDist[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Impact3DError").c_str(),
                    &electronSortedImpact3DError[ID][0],
                    (prefix + "Impact3DError[numEle" + name + "]/F").c_str());
    mytree_->Branch(
        (prefix + "Impact3DSignificance").c_str(),
        &electronSortedImpact3DSignificance[ID][0],
        (prefix + "Impact3DSignificance[numEle" + name + "]/F").c_str());

    mytree_->Branch(
        (prefix + "ChargedHadronIso").c_str(),
        &electronSortedChargedHadronIso[ID][0],
        (prefix + "ChargedHadronIso[numEle" + name + "]/F").c_str());
    mytree_->Branch(
        (prefix + "NeutralHadronIso").c_str(),
        &electronSortedNeutralHadronIso[ID][0],
        (prefix + "NeutralHadronIso[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "PhotonIso").c_str(),
                    &electronSortedPhotonIso[ID][0],
                    (prefix + "PhotonIso[numEle" + name + "]/F").c_str());

    mytree_->Branch((prefix + "TrackPt").c_str(),
                    &electronSortedTrackPt[ID][0],
                    (prefix + "TrackPt[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "TrackPhi").c_str(),
                    &electronSortedTrackPhi[ID][0],
                    (prefix + "TrackPhi[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "TrackEta").c_str(),
                    &electronSortedTrackEta[ID][0],
                    (prefix + "TrackEta[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "TrackChi2").c_str(),
                    &electronSortedTrackChi2[ID][0],
                    (prefix + "TrackChi2[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "TrackNDOF").c_str(),
                    &electronSortedTrackNDOF[ID][0],
                    (prefix + "TrackNDOF[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "TrackD0").c_str(),
                    &electronSortedTrackD0[ID][0],
                    (prefix + "TrackD0[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "TrackDBD0").c_str(),
                    &electronSortedDBBeamSpotCorrectedTrackD0[ID][0],
                    (prefix + "TrackDBD0[numEle" + name + "]/F").c_str());

    // mytree_->Branch((prefix + "DBInnerTrackD0").c_str(),
    //                 &electronSortedDBInnerTrackD0[ID][0],
    //                 (prefix + "DBInnerTrackD0[numEle" + name +
    //                 "]/F").c_str());

    mytree_->Branch(
        (prefix + "BeamSpotCorrectedTrackD0").c_str(),
        &electronSortedBeamSpotCorrectedTrackD0[ID][0],
        (prefix + "BeamSpotCorrectedTrackD0[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "TrackDz").c_str(),
                    &electronSortedTrackDz[ID][0],
                    (prefix + "TrackDz[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "D0PV").c_str(),
                    &electronSortedTrackD0PV[ID][0],
                    (prefix + "D0PV[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "DZPV").c_str(),
                    &electronSortedTrackDZPV[ID][0],
                    (prefix + "DZPV[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "VtxZ").c_str(),
                    &electronSortedVtxZ[ID][0],
                    (prefix + "VtxZ[numEle" + name + "]/F").c_str());

    mytree_->Branch((prefix + "IsGsf").c_str(),
                    &electronSortedIsGsf[ID][0],
                    (prefix + "IsGsf[numEle" + name + "]/I").c_str());

    mytree_->Branch((prefix + "GsfPx").c_str(),
                    &electronSortedGsfPx[ID][0],
                    (prefix + "GsfPx[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "GsfPy").c_str(),
                    &electronSortedGsfPy[ID][0],
                    (prefix + "GsfPy[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "GsfPz").c_str(),
                    &electronSortedGsfPz[ID][0],
                    (prefix + "GsfPz[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "GsfE").c_str(),
                    &electronSortedGsfE[ID][0],
                    (prefix + "GsfE[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "EcalEnergy").c_str(),
                    &electronSortedEcalEnergy[ID][0],
                    (prefix + "EcalEnergy[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SCEta").c_str(),
                    &electronSortedSuperClusterEta[ID][0],
                    (prefix + "SCEta[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SCE").c_str(),
                    &electronSortedSuperClusterE[ID][0],
                    (prefix + "SCE[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SCPhi").c_str(),
                    &electronSortedSuperClusterPhi[ID][0],
                    (prefix + "SCPhi[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SCEoverP").c_str(),
                    &electronSortedSuperClusterEoverP[ID][0],
                    (prefix + "SCEoverP[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SCSigmaEtaEta").c_str(),
                    &electronSortedSuperClusterSigmaEtaEta[ID][0],
                    (prefix + "SCSigmaEtaEta[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SCSigmaIEtaIEta").c_str(),
                    &electronSortedSuperClusterSigmaIEtaIEta[ID][0],
                    (prefix + "SCSigmaIEtaIEta[numEle" + name + "]/F").c_str());
    mytree_->Branch(
        (prefix + "SCSigmaIEtaIEta5x5").c_str(),
        &electronSortedSuperClusterSigmaIEtaIEta5x5[ID][0],
        (prefix + "SCSigmaIEtaIEta5x5[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SCE1x5").c_str(),
                    &electronSortedSuperClusterE1x5[ID][0],
                    (prefix + "SCE1x5[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SCE5x5").c_str(),
                    &electronSortedSuperClusterE5x5[ID][0],
                    (prefix + "SCE5x5[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SCE2x5max").c_str(),
                    &electronSortedSuperClusterE2x5max[ID][0],
                    (prefix + "SCE2x5max[numEle" + name + "]/F").c_str());

    mytree_->Branch((prefix + "TrackIso04").c_str(),
                    &electronSortedTrackIso04[ID][0],
                    (prefix + "TrackIso04[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "EcalIso04").c_str(),
                    &electronSortedECalIso04[ID][0],
                    (prefix + "EcalIso04[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "HcalIso04").c_str(),
                    &electronSortedHCalIso04[ID][0],
                    (prefix + "HcalIso04[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "TrackIso03").c_str(),
                    &electronSortedTrackIso03[ID][0],
                    (prefix + "TrackIso03[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "EcalIso03").c_str(),
                    &electronSortedECalIso03[ID][0],
                    (prefix + "EcalIso03[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "HcalIso03").c_str(),
                    &electronSortedHCalIso03[ID][0],
                    (prefix + "HcalIso03[numEle" + name + "]/F").c_str());
    mytree_->Branch(
        (prefix + "dr04EcalRecHitSumEt").c_str(),
        &electronSorteddr04EcalRecHitSumEt[ID][0],
        (prefix + "dr04EcalRecHitSumEt[numEle" + name + "]/F").c_str());
    mytree_->Branch(
        (prefix + "dr03EcalRecHitSumEt").c_str(),
        &electronSorteddr03EcalRecHitSumEt[ID][0],
        (prefix + "dr03EcalRecHitSumEt[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "EcalIsoDeposit").c_str(),
                    &electronSortedECalIsoDeposit[ID][0],
                    (prefix + "EcalIsoDeposit[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "HcalIsoDeposit").c_str(),
                    &electronSortedHCalIsoDeposit[ID][0],
                    (prefix + "HcalIsoDeposit[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "ComRelIso").c_str(),
                    &electronSortedComRelIso[ID][0],
                    (prefix + "ctronComRelIso[numEle" + name + "]/F").c_str());
    mytree_->Branch(
        (prefix + "ComRelIsodBeta").c_str(),
        &electronSortedComRelIsodBeta[ID][0],
        (prefix + "ctronComRelIsodBeta[numEle" + name + "]/F").c_str());
    mytree_->Branch(
        (prefix + "ComRelIsoRho").c_str(),
        &electronSortedComRelIsoRho[ID][0],
        (prefix + "ctronComRelIsoRho[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "ChHadIso").c_str(),
                    &electronSortedChHadIso[ID][0],
                    (prefix + "ChHadIso[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "NtHadIso").c_str(),
                    &electronSortedNtHadIso[ID][0],
                    (prefix + "NtHadIso[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "GammaIso").c_str(),
                    &electronSortedGammaIso[ID][0],
                    (prefix + "GammaIso[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "RhoIso").c_str(),
                    &electronSortedRhoIso[ID][0],
                    (prefix + "RhoIso[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "AEff03").c_str(),
                    &electronSortedAEff03[ID][0],
                    (prefix + "AEff03[numEle" + name + "]/F").c_str());
    mytree_->Branch(
        (prefix + "MissingInnerLayers").c_str(),
        &electronSortedMissingInnerLayers[ID][0],
        (prefix + "MissingInnerLayers[numEle" + name + "]/I").c_str());
    mytree_->Branch((prefix + "HoverE").c_str(),
                    &electronSortedHoverE[ID][0],
                    (prefix + "HoverE[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "DeltaPhiSC").c_str(),
                    &electronSortedDeltaPhiSC[ID][0],
                    (prefix + "DeltaPhiSC[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "DeltaEtaSC").c_str(),
                    &electronSortedDeltaEtaSC[ID][0],
                    (prefix + "DeltaEtaSC[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "DeltaEtaSeedSC").c_str(),
                    &electronSortedDeltaEtaSeedSC[ID][0],
                    (prefix + "DeltaEtaSeedSC[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "IsBarrel").c_str(),
                    &electronSortedIsBarrel[ID][0],
                    (prefix + "IsBarrel[numEle" + name + "]/I").c_str());
    mytree_->Branch(
        (prefix + "PhotonConversionTag").c_str(),
        &electronSortedPhotonConversionTag[ID][0],
        (prefix + "PhotonConversionTag[numEle" + name + "]/I").c_str());
    mytree_->Branch(
        (prefix + "PhotonConversionDist").c_str(),
        &electronSortedPhotonConversionDist[ID][0],
        (prefix + "PhotonConversionDist[numEle" + name + "]/F").c_str());
    mytree_->Branch(
        (prefix + "PhotonConversionDcot").c_str(),
        &electronSortedPhotonConversionDcot[ID][0],
        (prefix + "PhotonConversionDcot[numEle" + name + "]/F").c_str());
    mytree_->Branch(
        (prefix + "PhotonConversionVeto").c_str(),
        &electronSortedPhotonConversionVeto[ID][0],
        (prefix + "PhotonConversionVeto[numEle" + name + "]/I").c_str());
//    mytree_->Branch((prefix + "PhotonConversionTagCustom").c_str(), &electronSortedPhotonConversionTagCustom[ID][0], (prefix + "PhotonConversionTagCustom[numEle" + name + "]/I").c_str());
    mytree_->Branch(
        (prefix + "PhotonConversionDistCustom").c_str(),
        &electronSortedPhotonConversionDistCustom[ID][0],
        (prefix + "PhotonConversionDistCustom[numEle" + name + "]/F").c_str());
    mytree_->Branch(
        (prefix + "PhotonConversionDcotCustom").c_str(),
        &electronSortedPhotonConversionDcotCustom[ID][0],
        (prefix + "PhotonConversionDcotCustom[numEle" + name + "]/F").c_str());

    mytree_->Branch((prefix + "TriggerMatch").c_str(),
                    &electronSortedTriggerMatch[ID][0],
                    (prefix + "TriggerMatch[numEle" + name + "]/F").c_str());
    mytree_->Branch((prefix + "JetOverlap").c_str(),
                    &electronSortedJetOverlap[ID][0],
                    (prefix + "JetOverlap[numEle" + name + "]/F").c_str());

    mytree_->Branch((prefix + "NumSourceCandidates").c_str(), &electronSortedNumSourceCandidates[ID][0], (prefix + "NumSourceCandidates[numEle" + name + "]/I").c_str());
    mytree_->Branch((prefix + "PackedCandIndex").c_str(), &electronSortedPackedCandIndex[ID][0], (prefix + "PackedCandIndex[numEle" + name + "]/I").c_str());


    if (runMCInfo_)
    {
        mytree_->Branch(
            ("genEle" + name + "PT").c_str(),
            &genElectronSortedPt[ID][0],
            ("genEle" + name + "ElePT[numEle" + name + "]/F").c_str());
        mytree_->Branch(
            ("genEle" + name + "ET").c_str(),
            &genElectronSortedEt[ID][0],
            ("genEle" + name + "EleET[numEle" + name + "]/F").c_str());
        mytree_->Branch(
            ("genEle" + name + "PX").c_str(),
            &genElectronSortedPx[ID][0],
            ("genEle" + name + "ElePx[numEle" + name + "]/F").c_str());
        mytree_->Branch(
            ("genEle" + name + "PY").c_str(),
            &genElectronSortedPy[ID][0],
            ("genEle" + name + "ElePy[numEle" + name + "]/F").c_str());
        mytree_->Branch(
            ("genEle" + name + "PZ").c_str(),
            &genElectronSortedPz[ID][0],
            ("genEle" + name + "ElePz[numEle" + name + "]/F").c_str());
        mytree_->Branch(
            ("genEle" + name + "Phi").c_str(),
            &genElectronSortedPhi[ID][0],
            ("genEle" + name + "ElePhi[numEle" + name + "]/F").c_str());
        mytree_->Branch(
            ("genEle" + name + "Theta").c_str(),
            &genElectronSortedTheta[ID][0],
            ("genEle" + name + "EleTheta[numEle" + name + "]/F").c_str());
        mytree_->Branch(
            ("genEle" + name + "Eta").c_str(),
            &genElectronSortedEta[ID][0],
            ("genEle" + name + "EleEta[numEle" + name + "]/F").c_str());
        mytree_->Branch(
            ("genEle" + name + "Charge").c_str(),
            &genElectronSortedCharge[ID][0],
            ("genEle" + name + "EleCharge[numEle" + name + "]/I").c_str());
        mytree_->Branch(
            ("genEle" + name + "PdgId").c_str(),
            &genElectronSortedPdgId[ID][0],
            ("genEle" + name + "ElePdgId[numEle" + name + "]/I").c_str());
        mytree_->Branch(
            ("genEle" + name + "MotherId").c_str(),
            &genElectronSortedMotherId[ID][0],
            ("genEle" + name + "EleMotherId[numEle" + name + "]/I").c_str());
        mytree_->Branch(
            ("genEle" + name + "PromptDecayed").c_str(),
            &genElectronSortedPromptDecayed[ID][0],
            ("genEle" + name + "ElePromptDecayed[numEle" + name + "]/I")
                .c_str());
        mytree_->Branch(
            ("genEle" + name + "PromptFinalState").c_str(),
            &genElectronSortedPromptFinalState[ID][0],
            ("genEle" + name + "ElePromptFinalState[numEle" + name + "]/I")
                .c_str());
        mytree_->Branch(("genEle" + name + "HardProcess").c_str(), &genElectronSortedHardProcess[ID][0], ("genEle" + name + "ElePromptHardProcess[numEle" + name + "]/I").c_str());
        mytree_->Branch(("genEle" + name + "PythiaSixStatusThree").c_str(), &genElectronSortedPythiaSixStatusThree[ID][0], ("genEle" + name + "ElePythiaSixStatusThree[numEle" + name + "]/I").c_str());
        mytree_->Branch(("genEle" + name + "ScalarAncestor").c_str(), &genElectronSortedScalarAncestor[ID][0], ("genEle" + name + "EleScalarAncestor[numEle" + name + "]/I").c_str());
        mytree_->Branch(("genEle" + name + "DirectScalarAncestor").c_str(), &genElectronSortedDirectScalarAncestor[ID][0], ("genEle" + name + "EleDirectScalarAncestor[numEle" + name + "]/I").c_str());
    }

    // Also handle z candidates
    nzcandidates[ID] = 0;
    zcandidatesvector[ID] = tempVecF;
}
// book muon branches:
void MakeTopologyNtupleMiniAOD::bookMuonBranches(const std::string& ID, const std::string& name) {

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
    muonSortedIsPFMuon[ID] = tempVecI;

    muonSortedNumChambers[ID] = tempVecI;
    muonSortedNumMatches[ID] = tempVecI;

    muonSortedNumSourceCandidates[ID] = tempVecI;
    muonSortedPackedCandIndex[ID] = tempVecI;

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
    genMuonSortedScalarAncestor[ID] = tempVecI;
    genMuonSortedDirectScalarAncestor[ID] = tempVecI;

    // Initialise maps to prevent root panicing.
    std::vector<float> tempVecF2(NMUONTKPAIRMAX);
    std::vector<int> tempVecI2(NMUONTKPAIRMAX);

    muonTkPairSortedIndex1[ID] = tempVecI2;
    muonTkPairSortedIndex2[ID] = tempVecI2;
    muonTkPairSortedTkVtxPx[ID] = tempVecF2;
    muonTkPairSortedTkVtxPy[ID] = tempVecF2;
    muonTkPairSortedTkVtxPz[ID] = tempVecF2;
    muonTkPairSortedTkVtxP2[ID] = tempVecF2;
    muonTkPairSortedTkVx[ID] = tempVecF2;
    muonTkPairSortedTkVy[ID] = tempVecF2;
    muonTkPairSortedTkVz[ID] = tempVecF2;
    muonTkPairSortedTkVtxCov00[ID] = tempVecF2;
    muonTkPairSortedTkVtxCov01[ID] = tempVecF2;
    muonTkPairSortedTkVtxCov02[ID] = tempVecF2;
    muonTkPairSortedTkVtxCov10[ID] = tempVecF2;
    muonTkPairSortedTkVtxCov11[ID] = tempVecF2;
    muonTkPairSortedTkVtxCov12[ID] = tempVecF2;
    muonTkPairSortedTkVtxCov20[ID] = tempVecF2;
    muonTkPairSortedTkVtxCov21[ID] = tempVecF2;
    muonTkPairSortedTkVtxCov22[ID] = tempVecF2;
    muonTkPairSortedTkVtxChi2[ID] = tempVecF2;
    muonTkPairSortedTkVtxNdof[ID] = tempVecF2;
    muonTkPairSortedTkVtxTime[ID] = tempVecF2;
    muonTkPairSortedTkVtxTimeError[ID] = tempVecF2;
    muonTkPairSortedTkVtxAngleXY[ID] = tempVecF2;
    muonTkPairSortedTkVtxDistMagXY[ID] = tempVecF2;
    muonTkPairSortedTkVtxDistMagXYSigma[ID] = tempVecF2;
    muonTkPairSortedTkVtxAngleXYZ[ID] = tempVecF2;
    muonTkPairSortedTkVtxDistMagXYZ[ID] = tempVecF2;
    muonTkPairSortedTkVtxDistMagXYZSigma[ID] = tempVecF2;
    muonTkPairSortedTk1Pt[ID] = tempVecF2;
    muonTkPairSortedTk1Px[ID] = tempVecF2;
    muonTkPairSortedTk1Py[ID] = tempVecF2;
    muonTkPairSortedTk1Pz[ID] = tempVecF2;
    muonTkPairSortedTk1P2[ID] = tempVecF2;
    muonTkPairSortedTk1Eta[ID] = tempVecF2;
    muonTkPairSortedTk1Phi[ID] = tempVecF2;
    muonTkPairSortedTk1Charge[ID] = tempVecI2;
    muonTkPairSortedTk1Chi2[ID] = tempVecF2;
    muonTkPairSortedTk1Ndof[ID] = tempVecF2;
    muonTkPairSortedTk2Pt[ID] = tempVecF2;
    muonTkPairSortedTk2Px[ID] = tempVecF2;
    muonTkPairSortedTk2Py[ID] = tempVecF2;
    muonTkPairSortedTk2Pz[ID] = tempVecF2;
    muonTkPairSortedTk2P2[ID] = tempVecF2;
    muonTkPairSortedTk2Eta[ID] = tempVecF2;
    muonTkPairSortedTk2Phi[ID] = tempVecF2;
    muonTkPairSortedTk2Charge[ID] = tempVecI2;
    muonTkPairSortedTk2Chi2[ID] = tempVecF2;
    muonTkPairSortedTk2Ndof[ID] = tempVecF2;
    muonTkPairSortedTkVtxDcaPreFit[ID] = tempVecF2;

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
    mytree_->Branch((prefix + "IsPFMuon").c_str(), &muonSortedIsPFMuon[ID][0], (prefix + "IsPFMuon[numMuon" + name + "]/I").c_str());

    mytree_->Branch((prefix + "NChambers").c_str(), &muonSortedNumChambers[ID][0], (prefix + "NChambers[numMuon" + name + "]/I").c_str());
    mytree_->Branch((prefix + "NMatches").c_str(), &muonSortedNumMatches[ID][0], (prefix + "NMatches[numMuon" + name + "]/I").c_str());

    mytree_->Branch((prefix + "ValidFraction").c_str(), &muonValidFraction[ID][0], (prefix + "ValidFraction[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Chi2LocalPosition").c_str(), &muonChi2LocalPosition[ID][0], (prefix + "Chi2LocalPosition[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "TrkKick").c_str(), &muonTrkKick[ID][0], (prefix + "TrkKick[numMuon" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SegmentCompatibility").c_str(), &muonSegmentCompatibility[ID][0], (prefix + "SegmentCompatibility[numMuon" + name + "]/F").c_str());

    mytree_->Branch((prefix + "NumSourceCandidates").c_str(), &muonSortedNumSourceCandidates[ID][0], (prefix + "NumSourceCandidates[numMuon" + name + "]/I").c_str());
    mytree_->Branch((prefix + "PackedCandIndex").c_str(), &muonSortedPackedCandIndex[ID][0], (prefix + "PackedCandIndex[numMuon" + name + "]/I").c_str());

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
        mytree_->Branch((prefix + "ScalarAncestor").c_str(), &genMuonSortedScalarAncestor[ID][0], (prefix + "ScalarAncestor[numMuon" + name + "]/I").c_str());
        mytree_->Branch((prefix + "DirectScalarAncestor").c_str(), &genMuonSortedDirectScalarAncestor[ID][0], (prefix + "DirectScalarAncestor[numMuon" + name + "]/I").c_str());
    }

    mytree_->Branch(("numMuonTrackPairs" + name).c_str(), &numMuonTrackPairs[ID], ("numMuonTrackPairs" + name + "/I").c_str());
    std::string prefix2{"muonTkPair" + name};
    mytree_->Branch((prefix2 + "Index1").c_str(), &muonTkPairSortedIndex1[ID][0], (prefix2 + "Index1[numMuonTrackPairs" + name + "]/I").c_str());
    mytree_->Branch((prefix2 + "Index2").c_str(), &muonTkPairSortedIndex2[ID][0], (prefix2 + "Index2[numMuonTrackPairs" + name + "]/I").c_str());
    mytree_->Branch((prefix2 + "TkVtxPx").c_str(), &muonTkPairSortedTkVtxPx[ID][0], (prefix2 + "TkVtxPx[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVtxPy").c_str(), &muonTkPairSortedTkVtxPy[ID][0], (prefix2 + "TkVtxPy[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVtxPz").c_str(), &muonTkPairSortedTkVtxPz[ID][0], (prefix2 + "TkVtxPz[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVtxP2").c_str(), &muonTkPairSortedTkVtxP2[ID][0], (prefix2 + "TkVtxP2[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVx").c_str(), &muonTkPairSortedTkVx[ID][0], (prefix2 + "TkVx[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVy").c_str(), &muonTkPairSortedTkVy[ID][0], (prefix2 + "TkVy[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVz").c_str(), &muonTkPairSortedTkVz[ID][0], (prefix2 + "TkVz[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVtxCov00").c_str(), &muonTkPairSortedTkVtxCov00[ID][0], (prefix2 + "TkVtxCov00[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVtxCov01").c_str(), &muonTkPairSortedTkVtxCov02[ID][0], (prefix2 + "TkVtxCov01[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVtxCov02").c_str(), &muonTkPairSortedTkVtxCov02[ID][0], (prefix2 + "TkVtxCov02[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVtxCov10").c_str(), &muonTkPairSortedTkVtxCov10[ID][0], (prefix2 + "TkVtxCov10[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVtxCov11").c_str(), &muonTkPairSortedTkVtxCov11[ID][0], (prefix2 + "TkVtxCov11[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVtxCov12").c_str(), &muonTkPairSortedTkVtxCov12[ID][0], (prefix2 + "TkVtxCov12[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVtxCov20").c_str(), &muonTkPairSortedTkVtxCov20[ID][0], (prefix2 + "TkVtxCov20[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVtxCov21").c_str(), &muonTkPairSortedTkVtxCov21[ID][0], (prefix2 + "TkVtxCov21[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVtxCov22").c_str(), &muonTkPairSortedTkVtxCov22[ID][0], (prefix2 + "TkVtxCov22[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVtxChi2").c_str(), &muonTkPairSortedTkVtxChi2[ID][0], (prefix2 + "TkVtxChi2[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVtxNdof").c_str(), &muonTkPairSortedTkVtxNdof[ID][0], (prefix2 + "TkVtxNdof[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVtxTime").c_str(), &muonTkPairSortedTkVtxTime[ID][0], (prefix2 + "TkVtxTimeError[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVtxTimeError").c_str(), &muonTkPairSortedTkVtxTimeError[ID][0], (prefix2 + "TkVtxTimeError[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVtxAngleXY").c_str(), &muonTkPairSortedTkVtxAngleXY[ID][0], (prefix2 + "TkVtxAngleXY[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVtxDistMagXY").c_str(), &muonTkPairSortedTkVtxDistMagXY[ID][0], (prefix2 + "TkVtxDistMagXY[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVtxDistMagXYSigma").c_str(), &muonTkPairSortedTkVtxDistMagXYSigma[ID][0], (prefix2 + "TkVtxDistMagXYSigma[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVtxAngleXYZ").c_str(), &muonTkPairSortedTkVtxAngleXYZ[ID][0], (prefix2 + "TkVtxAngleXYZ[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVtxDistMagXYZ").c_str(), &muonTkPairSortedTkVtxDistMagXYZ[ID][0], (prefix2 + "TkVtxDistMagXYZ[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVtxDistMagXYZSigma").c_str(), &muonTkPairSortedTkVtxDistMagXYZSigma[ID][0], (prefix2 + "TkVtxDistMagXYZSigma[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "Tk1Pt").c_str(), &muonTkPairSortedTk1Pt[ID][0], (prefix2 + "Tk1Pt[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "Tk1Px").c_str(), &muonTkPairSortedTk1Px[ID][0], (prefix2 + "Tk1Px[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "Tk1Py").c_str(), &muonTkPairSortedTk1Py[ID][0], (prefix2 + "Tk1Py[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "Tk1Pz").c_str(), &muonTkPairSortedTk1Pz[ID][0], (prefix2 + "Tk1Pz[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "Tk1P2").c_str(), &muonTkPairSortedTk1P2[ID][0], (prefix2 + "Tk1P2[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "Tk1Eta").c_str(), &muonTkPairSortedTk1Eta[ID][0], (prefix2 + "Tk1Eta[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "Tk1Phi").c_str(), &muonTkPairSortedTk1Phi[ID][0], (prefix2 + "Tk1Phi[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "Tk1Charge").c_str(), &muonTkPairSortedTk1Charge[ID][0], (prefix2 + "Tk1Charge[numMuonTrackPairs" + name + "]/I").c_str());
    mytree_->Branch((prefix2 + "Tk1Chi2").c_str(), &muonTkPairSortedTk1Chi2[ID][0], (prefix2 + "Tk1Chi2[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "Tk1Ndof").c_str(), &muonTkPairSortedTk1Ndof[ID][0], (prefix2 + "Tk1Ndof[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "Tk2Pt").c_str(), &muonTkPairSortedTk2Pt[ID][0], (prefix2 + "Tk2Pt[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "Tk2Px").c_str(), &muonTkPairSortedTk2Px[ID][0], (prefix2 + "Tk2Px[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "Tk2Py").c_str(), &muonTkPairSortedTk2Py[ID][0], (prefix2 + "Tk2Py[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "Tk2Pz").c_str(), &muonTkPairSortedTk2Pz[ID][0], (prefix2 + "Tk2Pz[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "Tk2P2").c_str(), &muonTkPairSortedTk2P2[ID][0], (prefix2 + "Tk2P2[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "Tk2Eta").c_str(), &muonTkPairSortedTk2Eta[ID][0], (prefix2 + "Tk2Eta[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "Tk2Phi").c_str(), &muonTkPairSortedTk2Phi[ID][0], (prefix2 + "Tk2Phi[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "Tk2Charge").c_str(), &muonTkPairSortedTk2Charge[ID][0], (prefix2 + "Tk2Charge[numMuonTrackPairs" + name + "]/I").c_str());
    mytree_->Branch((prefix2 + "Tk2Chi2").c_str(), &muonTkPairSortedTk2Chi2[ID][0], (prefix2 + "Tk2Chi2[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "Tk2Ndof").c_str(), &muonTkPairSortedTk2Ndof[ID][0], (prefix2 + "Tk2Ndof[numMuonTrackPairs" + name + "]/F").c_str());
    mytree_->Branch((prefix2 + "TkVtxDcaPreFit").c_str(), &muonTkPairSortedTkVtxDcaPreFit[ID][0], (prefix2 + "TkVtxDcaPreFit[numMuonTrackPairs" + name + "]/F").c_str());
}

void MakeTopologyNtupleMiniAOD::bookMETBranches(const std::string& ID, const std::string& name) {
    // std::cout << "bookMETBranches CHECK" << std::endl;

    metE[ID] = -1.0;
    metEt[ID] = -1.0;
    metEtRaw[ID] = -1.0;
    metPhi[ID] = -99999;
    metPt[ID] = -99999;
    metPx[ID] = -99999;
    metPy[ID] = -99999;
    metPz[ID] = -99999;
    metScalarEt[ID] = -1.0;
    metEtUncorrected[ID] = -1.0;
    metPhiUncorrected[ID] = -99999;
    metUnclusteredEnUp[ID] = -99999;
    metUnclusteredEnDown[ID] = -99999;
    genMetE[ID] = -1.0;
    genMetEt[ID] = -1.0;
    genMetPhi[ID] = -99999;
    genMetPt[ID] = -99999;
    genMetPx[ID] = -99999;
    genMetPy[ID] = -99999;
    genMetPz[ID] = -99999;

    std::string prefix{"met" + name};
    mytree_->Branch(
        (prefix + "E").c_str(), &metE[ID], (prefix + "E/D").c_str());
    mytree_->Branch(
        (prefix + "Et").c_str(), &metEt[ID], (prefix + "Et/D").c_str());
    mytree_->Branch((prefix + "EtRaw").c_str(),
                    &metEtRaw[ID],
                    (prefix + "EtRaw/D").c_str());
    mytree_->Branch(
        (prefix + "Phi").c_str(), &metPhi[ID], (prefix + "Phi/D").c_str());
    mytree_->Branch(
        (prefix + "Pt").c_str(), &metPt[ID], (prefix + "Pt/D").c_str());
    mytree_->Branch(
        (prefix + "Px").c_str(), &metPx[ID], (prefix + "Px/D").c_str());
    mytree_->Branch(
        (prefix + "Py").c_str(), &metPy[ID], (prefix + "Py/D").c_str());
    mytree_->Branch(
        (prefix + "Pz").c_str(), &metPz[ID], (prefix + "Pz/D").c_str());
    mytree_->Branch((prefix + "ScalarEt").c_str(),
                    &metScalarEt[ID],
                    (prefix + "ScalarEt/F").c_str());
    mytree_->Branch((prefix + "EtUncorrected").c_str(),
                    &metEtUncorrected[ID],
                    (prefix + "EtUncorrected/F").c_str());
    mytree_->Branch((prefix + "PhiUncorrected").c_str(),
                    &metPhiUncorrected[ID],
                    (prefix + "PhiUncorrected/F").c_str());
    mytree_->Branch((prefix + "UnclusteredEnUp").c_str(),
                    &metUnclusteredEnUp[ID],
                    (prefix + "UnclusteredEnUp/F").c_str());
    mytree_->Branch((prefix + "UnclusteredEnDown").c_str(),
                    &metUnclusteredEnDown[ID],
                    (prefix + "UnclusteredEnDown/F").c_str());

    prefix = "genMet" + name;
    if (runMCInfo_)
    {
        mytree_->Branch(
            (prefix + "E").c_str(), &genMetE, (prefix + "E/F").c_str());
        mytree_->Branch(
            (prefix + "Et").c_str(), &genMetEt, (prefix + "Et/F").c_str());
        mytree_->Branch(
            (prefix + "Phi").c_str(), &genMetPhi, (prefix + "Phi/F").c_str());
        mytree_->Branch(
            (prefix + "Pt").c_str(), &genMetPt, (prefix + "Pt/F").c_str());
        mytree_->Branch(
            (prefix + "Px").c_str(), &genMetPx, (prefix + "Px/F").c_str());
        mytree_->Branch(
            (prefix + "Py").c_str(), &genMetPy, (prefix + "Py/F").c_str());
        mytree_->Branch(
            (prefix + "Pz").c_str(), &genMetPz, (prefix + "Pz/F").c_str());
    }
}
// book MC branches:
void MakeTopologyNtupleMiniAOD::bookMCBranches()
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

// book jet branches:
void MakeTopologyNtupleMiniAOD::bookPFJetBranches(const std::string& ID,
                                                  const std::string& name)
{
    // std::cout << "bookPFJetBranches CHECK" << std::endl;
    // Initialise the maps so ROOT wont panic
    std::vector<float> tempVecF(NJETSMAX);
    std::vector<int> tempVecI(NJETSMAX);

    jetSortedNeutralMultiplicity[ID] = tempVecI;
    jetSortedChargedMultiplicity[ID] = tempVecI;

    jetSortedMuEnergy[ID] = tempVecF;
    jetSortedMuEnergyFraction[ID] = tempVecF;
    jetSortedNeutralHadEnergy[ID] = tempVecF;
    jetSortedNeutralEmEnergy[ID] = tempVecF;
    jetSortedChargedHadronEnergyFraction[ID] = tempVecF;
    jetSortedNeutralHadronEnergyFraction[ID] = tempVecF;
    jetSortedChargedEmEnergyFraction[ID] = tempVecF;
    jetSortedNeutralEmEnergyFraction[ID] = tempVecF;
    jetSortedMuonFraction[ID] = tempVecF;
    jetSortedChargedHadronEnergyFractionCorr[ID] = tempVecF;
    jetSortedNeutralHadronEnergyFractionCorr[ID] = tempVecF;
    jetSortedChargedEmEnergyFractionCorr[ID] = tempVecF;
    jetSortedNeutralEmEnergyFractionCorr[ID] = tempVecF;
    jetSortedMuonFractionCorr[ID] = tempVecF;

    std::string prefix{"jet" + name};
    mytree_->Branch((prefix + "MuEnergy").c_str(),
                    &jetSortedMuEnergy[ID][0],
                    (prefix + "MuEnergy[numJet" + name + "]/F").c_str());
    mytree_->Branch(
        (prefix + "MuEnergyFraction").c_str(),
        &jetSortedMuEnergyFraction[ID][0],
        (prefix + "MuEnergyFraction[numJet" + name + "]/F").c_str());
    mytree_->Branch(
        (prefix + "NeutralHadEnergy").c_str(),
        &jetSortedNeutralHadEnergy[ID][0],
        (prefix + "NeutralHadEnergy[numJet" + name + "]/F").c_str());
    mytree_->Branch((prefix + "NeutralEmEnergy").c_str(),
                    &jetSortedNeutralEmEnergy[ID][0],
                    (prefix + "NeutralEmEnergy[numJet" + name + "]/F").c_str());

    mytree_->Branch(
        (prefix + "ChargedHadronEnergyFraction").c_str(),
        &jetSortedChargedHadronEnergyFraction[ID][0],
        (prefix + "ChargedHadronEnergyFraction[numJet" + name + "]/F").c_str());
    mytree_->Branch(
        (prefix + "NeutralHadronEnergyFraction").c_str(),
        &jetSortedNeutralHadronEnergyFraction[ID][0],
        (prefix + "NeutralHadronEnergyFraction[numJet" + name + "]/F").c_str());
    mytree_->Branch(
        (prefix + "ChargedEmEnergyFraction").c_str(),
        &jetSortedChargedEmEnergyFraction[ID][0],
        (prefix + "ChargedEmEnergyFraction[numJet" + name + "]/F").c_str());
    mytree_->Branch(
        (prefix + "NeutralEmEnergyFraction").c_str(),
        &jetSortedNeutralEmEnergyFraction[ID][0],
        (prefix + "NeutralEmEnergyFraction[numJet" + name + "]/F").c_str());
    mytree_->Branch((prefix + "MuonFraction").c_str(),
                    &jetSortedMuonFraction[ID][0],
                    (prefix + "MuonFraction[numJet" + name + "]/F").c_str());
    mytree_->Branch(
        (prefix + "ChargedHadronEnergyFractionCorr").c_str(),
        &jetSortedChargedHadronEnergyFractionCorr[ID][0],
        (prefix + "ChargedHadronEnergyFractionCorr[numJet" + name + "]/F")
            .c_str());
    mytree_->Branch(
        (prefix + "NeutralHadronEnergyFractionCorr").c_str(),
        &jetSortedNeutralHadronEnergyFractionCorr[ID][0],
        (prefix + "NeutralHadronEnergyFractionCorr[numJet" + name + "]/F")
            .c_str());
    mytree_->Branch(
        (prefix + "ChargedEmEnergyFractionCorr").c_str(),
        &jetSortedChargedEmEnergyFractionCorr[ID][0],
        (prefix + "ChargedEmEnergyFractionCorr[numJet" + name + "]/F").c_str());
    mytree_->Branch(
        (prefix + "NeutralEmEnergyFractionCorr").c_str(),
        &jetSortedNeutralEmEnergyFractionCorr[ID][0],
        (prefix + "NeutralEmEnergyFractionCorr[numJet" + name + "]/F").c_str());
    mytree_->Branch(
        (prefix + "MuonFractionCorr").c_str(),
        &jetSortedMuonFractionCorr[ID][0],
        (prefix + "MuonFractionCorr[numJet" + name + "]/F").c_str());

    mytree_->Branch(
        (prefix + "NeutralMultiplicity").c_str(),
        &jetSortedNeutralMultiplicity[ID][0],
        (prefix + "NeutralMultiplicity[numJet" + name + "]/I").c_str());
    mytree_->Branch(
        (prefix + "ChargedMultiplicity").c_str(),
        &jetSortedChargedMultiplicity[ID][0],
        (prefix + "ChargedMultiplicity[numJet" + name + "]/I").c_str());
}

void MakeTopologyNtupleMiniAOD::bookJetBranches(const std::string& ID,
                                                const std::string& name)
{
    // std::cout << "bookJetBranches CHECK" << std::endl;
    // Initialise the maps so ROOT wont panic
    std::vector<float> tempVecF(NJETSMAX);
    std::vector<int> tempVecI(NJETSMAX);
    std::vector<double> tempVecD(NJETSMAX);

    numJet[ID] = -1;

    jetSortedNtracksInJet[ID] = tempVecI;
    jetSortedPID[ID] = tempVecI;
    jetSortedNConstituents[ID] = tempVecI;
    genJetSortedPID[ID] = tempVecI;
    genJetSortedMotherPID[ID] = tempVecI;
    genJetSortedScalarAncestor[ID] = tempVecI;

    jetSortedE[ID] = tempVecD;
    jetSortedEt[ID] = tempVecD;
    jetSortedPt[ID] = tempVecD;
    jetSortedPtRaw[ID] = tempVecD;
    jetSortedUnCorEt[ID] = tempVecD;
    jetSortedUnCorPt[ID] = tempVecD;
    jetSortedEta[ID] = tempVecD;
    jetSortedTheta[ID] = tempVecD;
    jetSortedPhi[ID] = tempVecD;
    jetSortedPx[ID] = tempVecD;
    jetSortedPy[ID] = tempVecD;
    jetSortedPz[ID] = tempVecD;
    jetSortedMass[ID] = tempVecD;
    // jetSortedID[ID] = tempVecI;
    jetSortedClosestLepton[ID] = tempVecD;
    jetSortedJetCharge[ID] = tempVecF;
    jetSortedfHPD[ID] = tempVecF;
    jetSortedCorrFactor[ID] = tempVecF;
    jetSortedCorrResidual[ID] = tempVecF;
    jetSortedL2L3ResErr[ID] = tempVecF;
    jetSortedCorrErrLow[ID] = tempVecF;
    jetSortedCorrErrHi[ID] = tempVecF;
    jetSortedN90Hits[ID] = tempVecF;
    jetSortedBtagSoftMuonPtRel[ID] = tempVecF;
    jetSortedBtagSoftMuonQuality[ID] = tempVecF;
    jetSortedTriggered[ID] = tempVecF;
    jetSortedSVX[ID] = tempVecF;
    jetSortedSVY[ID] = tempVecF;
    jetSortedSVZ[ID] = tempVecF;
    jetSortedSVDX[ID] = tempVecF;
    jetSortedSVDY[ID] = tempVecF;
    jetSortedSVDZ[ID] = tempVecF;

    for (size_t iBtag{0}; iBtag < bTagList_.size(); iBtag++)
    {
        bTagRes[bTagList_[iBtag]][ID] = tempVecF;
    }

    genJetSortedE[ID] = tempVecF;
    genJetSortedEt[ID] = tempVecF;
    genJetSortedPt[ID] = tempVecF;
    genJetSortedEta[ID] = tempVecF;
    genJetSortedTheta[ID] = tempVecF;
    genJetSortedPhi[ID] = tempVecF;
    genJetSortedPx[ID] = tempVecF;
    genJetSortedPy[ID] = tempVecF;
    genJetSortedPz[ID] = tempVecF;
    genJetSortedMass[ID] = tempVecF;
    // genJetSortedID[ID] = tempVecI;
    genJetSortedClosestB[ID] = tempVecF;
    genJetSortedClosestC[ID] = tempVecF;

    std::string prefix{"jet" + name};
    mytree_->Branch(("numJet" + name).c_str(),
                    &numJet[ID],
                    ("numJet" + name + "/I").c_str());

    mytree_->Branch((prefix + "E").c_str(),
                    &jetSortedE[ID][0],
                    (prefix + "E[numJet" + name + "]/D").c_str());
    mytree_->Branch((prefix + "Et").c_str(),
                    &jetSortedEt[ID][0],
                    (prefix + "Et[numJet" + name + "]/D").c_str());
    mytree_->Branch((prefix + "Pt").c_str(),
                    &jetSortedPt[ID][0],
                    (prefix + "Pt[numJet" + name + "]/D").c_str());
    mytree_->Branch((prefix + "PtRaw").c_str(),
                    &jetSortedPtRaw[ID][0],
                    (prefix + "PtRaw[numJet" + name + "]/D").c_str());
    mytree_->Branch((prefix + "UnCorEt").c_str(),
                    &jetSortedUnCorEt[ID][0],
                    (prefix + "UnCorEt[numJet" + name + "]/D").c_str());
    mytree_->Branch((prefix + "UnCorPt").c_str(),
                    &jetSortedUnCorPt[ID][0],
                    (prefix + "UnCorPt[numJet" + name + "]/D").c_str());
    mytree_->Branch((prefix + "Eta").c_str(),
                    &jetSortedEta[ID][0],
                    (prefix + "Eta[numJet" + name + "]/D").c_str());
    mytree_->Branch((prefix + "Theta").c_str(),
                    &jetSortedTheta[ID][0],
                    (prefix + "Theta[numJet" + name + "]/D").c_str());
    mytree_->Branch((prefix + "Phi").c_str(),
                    &jetSortedPhi[ID][0],
                    (prefix + "Phi[numJet" + name + "]/D").c_str());
    mytree_->Branch((prefix + "Px").c_str(),
                    &jetSortedPx[ID][0],
                    (prefix + "Px[numJet" + name + "]/D").c_str());
    mytree_->Branch((prefix + "Py").c_str(),
                    &jetSortedPy[ID][0],
                    (prefix + "Py[numJet" + name + "]/D").c_str());
    mytree_->Branch((prefix + "Pz").c_str(), &jetSortedPz[ID][0], (prefix + "Pz[numJet" + name + "]/D").c_str());
    mytree_->Branch((prefix + "Mass").c_str(), &jetSortedMass[ID][0], (prefix + "Mass[numJet" + name + "]/D").c_str());
    // mytree_->Branch((prefix + "ID").c_str(),
    //                 &jetSortedID[ID][0],
    //                 (prefix + "ID[numJet" + name + "]/I").c_str());
    mytree_->Branch((prefix + "dRClosestLepton").c_str(),
                    &jetSortedClosestLepton[ID][0],
                    (prefix + "ClosestLepton[numJet" + name + "]/D").c_str());
    mytree_->Branch((prefix + "NtracksInJet").c_str(),
                    &jetSortedNtracksInJet[ID][0],
                    (prefix + "NtracksInJet[numJet" + name + "]/I").c_str());
    mytree_->Branch((prefix + "JetCharge").c_str(),
                    &jetSortedJetCharge[ID][0],
                    (prefix + "JetCharge[numJet" + name + "]/F").c_str());
    mytree_->Branch((prefix + "fHPD").c_str(),
                    &jetSortedfHPD[ID][0],
                    (prefix + "fHPD[numJet" + name + "]/F").c_str());
    mytree_->Branch(
        (prefix + "BtagSoftMuonPtRel").c_str(),
        &jetSortedBtagSoftMuonPtRel[ID][0],
        (prefix + "BtagSoftMuonPtRel[numJet" + name + "]/F").c_str());
    mytree_->Branch(
        (prefix + "BtagSoftMuonQuality").c_str(),
        &jetSortedBtagSoftMuonQuality[ID][0],
        (prefix + "BtagSoftMuonQuality[numJet" + name + "]/F").c_str());
    mytree_->Branch((prefix + "CorrFactor").c_str(),
                    &jetSortedCorrFactor[ID][0],
                    (prefix + "CorrFactor[numJet" + name + "]/F").c_str());
    mytree_->Branch((prefix + "CorrResidual").c_str(),
                    &jetSortedCorrResidual[ID][0],
                    (prefix + "CorrResidual[numJet" + name + "]/F").c_str());
    mytree_->Branch((prefix + "L2L3ResErr").c_str(),
                    &jetSortedL2L3ResErr[ID][0],
                    (prefix + "L2L3ResErr[numJet" + name + "]/F").c_str());
    mytree_->Branch((prefix + "CorrErrLow").c_str(),
                    &jetSortedCorrErrLow[ID][0],
                    (prefix + "CorrErrLow[numJet" + name + "]/F").c_str());
    mytree_->Branch((prefix + "CorrErrHi").c_str(),
                    &jetSortedCorrErrHi[ID][0],
                    (prefix + "CorrErrHi[numJet" + name + "]/F").c_str());
    mytree_->Branch((prefix + "N90Hits").c_str(),
                    &jetSortedN90Hits[ID][0],
                    (prefix + "N90Hits[numJet" + name + "]/F").c_str());
    mytree_->Branch((prefix + "Triggered").c_str(),
                    &jetSortedTriggered[ID][0],
                    (prefix + "Triggered[numJet" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SVX").c_str(),
                    &jetSortedSVX[ID][0],
                    (prefix + "SVX[numJet" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SVY").c_str(),
                    &jetSortedSVY[ID][0],
                    (prefix + "SVY[numJet" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SVZ").c_str(),
                    &jetSortedSVZ[ID][0],
                    (prefix + "SVZ[numJet" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SVDX").c_str(),
                    &jetSortedSVDX[ID][0],
                    (prefix + "SVDX[numJet" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SVDY").c_str(),
                    &jetSortedSVDY[ID][0],
                    (prefix + "SVDY[numJet" + name + "]/F").c_str());
    mytree_->Branch((prefix + "SVDZ").c_str(),
                    &jetSortedSVDZ[ID][0],
                    (prefix + "SVDZ[numJet" + name + "]/F").c_str());
    mytree_->Branch((prefix + "NConstituents").c_str(),
                    &jetSortedNConstituents[ID][0],
                    (prefix + "NConstituents[numJet" + name + "]/I").c_str());

    for (size_t iBtag{0}; iBtag < bTagList_.size(); iBtag++)
    {
//        std::cout << "Booking bTag disc branch: " << bTagList_[iBtag] << std::endl;
        mytree_->Branch(
            (prefix + bTagList_[iBtag]).c_str(),
            &bTagRes[bTagList_[iBtag]][ID][0],
            (prefix + bTagList_[iBtag] + "[numJet" + name + "]/F").c_str());
    }

    // generator information
    mytree_->Branch((prefix + "PID").c_str(), &jetSortedPID[ID][0], (prefix + "PID[numJet" + name + "]/I").c_str());
    mytree_->Branch((prefix + "ClosestBPartonDeltaR").c_str(), &genJetSortedClosestB[ID][0], (prefix + "ClosestBPartonDeltaR[numJet" + name + "]/F").c_str());
    mytree_->Branch((prefix + "ClosestCPartonDeltaR").c_str(), &genJetSortedClosestC[ID][0], (prefix + "ClosestCPartonDeltaR[numJet" + name + "]/F").c_str());

    prefix = "genJet" + name;
    if (runMCInfo_)
    {
        mytree_->Branch((prefix + "E").c_str(),  &genJetSortedE[ID][0],  (prefix + "E[numJet" + name + "]/F").c_str());
        mytree_->Branch((prefix + "ET").c_str(), &genJetSortedEt[ID][0], (prefix + "ET[numJet" + name + "]/F").c_str());
        mytree_->Branch((prefix + "PT").c_str(), &genJetSortedPt[ID][0], (prefix + "PT[numJet" + name + "]/F").c_str());
        mytree_->Branch((prefix + "PX").c_str(), &genJetSortedPx[ID][0], (prefix + "PX[numJet" + name + "]/F").c_str());
        mytree_->Branch((prefix + "PY").c_str(), &genJetSortedPy[ID][0], (prefix + "PY[numJet" + name + "]/F").c_str());
        mytree_->Branch((prefix + "PZ").c_str(), &genJetSortedPz[ID][0], (prefix + "PZ[numJet" + name + "]/F").c_str());
        mytree_->Branch((prefix + "Mass").c_str(), &genJetSortedMass[ID][0], (prefix + "Mass[numJet" + name + "]/F").c_str());
        // mytree_->Branch((prefix + "ID").c_str(), &genJetSortedID[ID][0], (prefix + "ID[numJet" + name + "]/I").c_str());
        mytree_->Branch((prefix + "Phi").c_str(), &genJetSortedPhi[ID][0], (prefix + "Phi[numJet" + name + "]/F").c_str());
        mytree_->Branch((prefix + "Theta").c_str(), &genJetSortedTheta[ID][0], (prefix + "Theta[numJet" + name + "]/F").c_str());
        mytree_->Branch((prefix + "Eta").c_str(), &genJetSortedEta[ID][0], (prefix + "Eta[numJet" + name + "]/F").c_str());
        mytree_->Branch((prefix + "PID").c_str(), &genJetSortedPID[ID][0], (prefix + "PID[numJet" + name + "]/I").c_str());
        mytree_->Branch((prefix + "MotherPID").c_str(), &genJetSortedMotherPID[ID][0], (prefix + "MotherPID[numJet" + name + "]/I").c_str());
        mytree_->Branch((prefix + "ScalarAncestor").c_str(), &genJetSortedScalarAncestor[ID][0], (prefix + "genJetSortedScalarAncestor[numJet" + name + "]/I").c_str());
    }

    mytree_->Branch("fixedGridRhoFastjetAll", &fixedGridRhoFastjetAll[ID], "fixedGridRhoFastjetAll]/F");

}
void MakeTopologyNtupleMiniAOD::bookGeneralTracksBranches() {
    // std::cout << "bookGeneralTracksBranches CHECK" << std::endl;
    mytree_->Branch("numGeneralTracks", &numGeneralTracks, "numGeneralTracks/I");
    mytree_->Branch("generalTracksPt", &generalTracksPt, "generalTracksPt[numGeneralTracks]/F");
    mytree_->Branch("generalTracksPx", &generalTracksPx, "generalTracksPx[numGeneralTracks]/F");
    mytree_->Branch("generalTracksPy", &generalTracksPy, "generalTracksPy[numGeneralTracks]/F");
    mytree_->Branch("generalTracksPz", &generalTracksPz, "generalTracksPz[numGeneralTracks]/F");
    mytree_->Branch("generalTracksEta", &generalTracksEta, "generalTracksEta[numGeneralTracks]/F");
    mytree_->Branch("generalTracksTheta", &generalTracksTheta, "generalTracksTheta[numGeneralTracks]/F");
    mytree_->Branch("generalTracksPhi", &generalTracksPhi, "generalTracksPhi[numGeneralTracks]/F");
    mytree_->Branch("generalTracksCharge", &generalTracksCharge, "generalTracksCharge[numGeneralTracks]/F");
    mytree_->Branch("generalTracksVx", &generalTracksVx, "generalTracksVx[numGeneralTracks]/F");
    mytree_->Branch("generalTracksVy", &generalTracksVy, "generalTracksVy[numGeneralTracks]/F");
    mytree_->Branch("generalTracksVz", &generalTracksVz, "generalTracksVz[numGeneralTracks]/F");
    mytree_->Branch("generalTracksBeamSpotCorrectedD0", &generalTracksBeamSpotCorrectedD0, "generalTracksBeamSpotCorrectedD0[numGeneralTracks]/F");
}

void MakeTopologyNtupleMiniAOD::bookIsolatedTracksBranches() {
    // std::cout << "bookIsolatedTrackBranches CHECK" << std::endl;
    mytree_->Branch("numIsolatedTracks", &numIsolatedTracks, "numIsolatedTracks/I");
    mytree_->Branch("isoTracksPt", &isoTracksPt, "isoTracksPt[numIsolatedTracks]/F");
    mytree_->Branch("isoTracksPx", &isoTracksPx, "isoTracksPx[numIsolatedTracks]/F");
    mytree_->Branch("isoTracksPy", &isoTracksPy, "isoTracksPy[numIsolatedTracks]/F");
    mytree_->Branch("isoTracksPz", &isoTracksPz, "isoTracksPz[numIsolatedTracks]/F");
    mytree_->Branch("isoTracksE", &isoTracksE, "isoTracksE[numIsolatedTracks]/F");
    mytree_->Branch("isoTracksEta", &isoTracksEta, "isoTracksEta[numIsolatedTracks]/F");
    mytree_->Branch("isoTracksTheta", &isoTracksTheta, "isoTracksTheta[numIsolatedTracks]/F");
    mytree_->Branch("isoTracksPhi", &isoTracksPhi, "isoTracksPhi[numIsolatedTracks]/F");
    mytree_->Branch("isoTracksCharge", &isoTracksCharge, "isoTracksCharge[numIsolatedTracks]/I");
    mytree_->Branch("isoTracksPdgId", &isoTracksPdgId, "isoTracksPdgId[numIsolatedTracks]/I");
    mytree_->Branch("isoTracksMatchedCaloJetEmEnergy", &isoTracksMatchedCaloJetEmEnergy, "isoTracksMatchedCaloJetEmEnergy[numIsolatedTracks]/F");
    mytree_->Branch("isoTracksMatchedCaloJetHadEnergy", &isoTracksMatchedCaloJetHadEnergy, "isoTracksMatchedCaloJetHadEnergy[numIsolatedTracks]/F");
    mytree_->Branch("isoTracksDz", &isoTracksDz, "isoTracksDz[numIsolatedTracks]/F");
    mytree_->Branch("isoTracksDxy", &isoTracksDxy, "isoTracksDxy[numIsolatedTracks]/F");
    mytree_->Branch("isoTracksDzError", &isoTracksDzError, "isoTracksDzError[numIsolatedTracks]/F");
    mytree_->Branch("isoTracksDxyError", &isoTracksDxyError, "isoTracksDxyError[numIsolatedTracks]/F");
    mytree_->Branch("isoTracksFromPV", &isoTracksFromPV, "isoTracksFromPV[numIsolatedTracks]/I");
    mytree_->Branch("isoTracksVx", &isoTracksVx, "isoTracksVx[numIsolatedTracks]/F");
    mytree_->Branch("isoTracksVy", &isoTracksVy, "isoTracksVy[numIsolatedTracks]/F");
    mytree_->Branch("isoTracksVz", &isoTracksVz, "isoTracksVz[numIsolatedTracks]/F");
    mytree_->Branch("isoTracksHighPurity", &isoTracksHighPurity, "isoTracksHighPurity[numIsolatedTracks]/I");
    mytree_->Branch("isoTracksTight", &isoTracksTight, "isoTracksTIght[numIsolatedTracks]/I");
    mytree_->Branch("isoTracksLoose", &isoTracksLoose, "isoTracksLoose[numIsolatedTracks]/I");
    mytree_->Branch("isoTracksDeltaEta", &isoTracksDeltaEta, "isoTracksDeltaEta[numIsolatedTracks]/F");
    mytree_->Branch("isoTracksDeltaPhi", &isoTracksDeltaPhi, "isoTracksDeltaPhi[numIsolatedTracks]/F");
}

void MakeTopologyNtupleMiniAOD::bookPackedCandsBranches() {
    // std::cout << "bookPackedCandsBranches CHECK" << std::endl;
    mytree_->Branch("numPackedCands", &numPackedCands, "numPackedCands/I");
//    mytree_->Branch("packedCandsPt", &packedCandsPt, "packedCandsPt[numPackedCands]/F");
    mytree_->Branch("packedCandsPx", &packedCandsPx, "packedCandsPx[numPackedCands]/F");
    mytree_->Branch("packedCandsPy", &packedCandsPy, "packedCandsPy[numPackedCands]/F");
    mytree_->Branch("packedCandsPz", &packedCandsPz, "packedCandsPz[numPackedCands]/F");
    mytree_->Branch("packedCandsE", &packedCandsE, "packedCandsE[numPackedCands]/F");
//    mytree_->Branch("packedCandsEta", &packedCandsEta, "packedCandsEta[numPackedCands]/F");
//    mytree_->Branch("packedCandsTheta", &packedCandsTheta, "packedCandsTheta[numPackedCands]/F");
//    mytree_->Branch("packedCandsPhi", &packedCandsPhi, "packedCandsPhi[numPackedCands]/F");
    mytree_->Branch("packedCandsCharge", &packedCandsCharge, "packedCandsCharge[numPackedCands]/I");
    mytree_->Branch("packedCandsPdgId", &packedCandsPdgId, "packedCandsPdgId[numPackedCands]/I");
    mytree_->Branch("packedCandsTime", &packedCandsTime, "packedCandsTime[numPackedCands]/F");
    mytree_->Branch("packedCandsFromPV", &packedCandsFromPV, "packedCandsFromPV[numPackedCands]/I");
    mytree_->Branch("packedCandsPVquality", &packedCandsPVquality, "packedCandsPVquality[numPackedCands]/I");
    mytree_->Branch("packedCandsVx", &packedCandsVx, "packedCandsVx[numPackedCands]/F");
    mytree_->Branch("packedCandsVy", &packedCandsVy, "packedCandsVy[numPackedCands]/F");
    mytree_->Branch("packedCandsVz", &packedCandsVz, "packedCandsVz[numPackedCands]/F");
//    mytree_->Branch("packedCandsVEta", &packedCandsVEta, "packedCandsVEta[numPackedCands]/F");
//    mytree_->Branch("packedCandsVPhi", &packedCandsVPhi, "packedCandsVPhi[numPackedCands]/F"); 
//    mytree_->Branch("packedCandsBeamSpotCorrectedD0", &packedCandsBeamSpotCorrectedD0, "packedCandsBeamSpotCorrectedD0[numPackedCands]/F");
    mytree_->Branch("packedCandsDz", &packedCandsDz, "packedCandsDz[numPackedCands]/F");
    mytree_->Branch("packedCandsDxy", &packedCandsDxy, "packedCandsDxy[numPackedCands]/F");
//    mytree_->Branch("packedCandsDzAssocPV", &packedCandsDzAssocPV, "packedCandsDzAssocPV[numPackedCands]/F");
//    mytree_->Branch("packedCandsVtxChi2Norm", &packedCandsVtxChi2Norm, "packedCandsVtxChi2Norm[numPackedCands]/F");

    mytree_->Branch("packedCandsElectronIndex", &packedCandsElectronIndex, "packedCandsElectronIndex[numPackedCands]/I");
    mytree_->Branch("packedCandsMuonIndex", &packedCandsMuonIndex, "packedCandsMuonIndex[numPackedCands]/I");
//    mytree_->Branch("packedCandsTauIndex", &packedCandsTauIndex, "packedCandsTauIndex[numPackedCands]/I");
    mytree_->Branch("packedCandsPhotonIndex", &packedCandsPhotonIndex, "packedCandsPhotonIndex[numPackedCands]/I");
    mytree_->Branch("packedCandsJetIndex", &packedCandsJetIndex, "packedCandsJetIndex[numPackedCands]/I");

    mytree_->Branch("packedCandsHasTrackDetails", &packedCandsHasTrackDetails, "packedCandsHasTrackDetails[numPackedCands]/I");
    mytree_->Branch("packedCandsDzError", &packedCandsDzError, "packedCandsDzError[numPackedCands]/F");
    mytree_->Branch("packedCandsDxyError", &packedCandsDxyError, "packedCandsDxyError[numPackedCands]/F");
    mytree_->Branch("packedCandsTimeError", &packedCandsTimeError, "packedCandsTimeError[numPackedCands]/F");
    mytree_->Branch("packedCandsPseudoTrkPt", &packedCandsPseudoTrkPt, "packedCandsPseudoTrkPt[numPackedCands]/F");
    mytree_->Branch("packedCandsPseudoTrkPx", &packedCandsPseudoTrkPx, "packedCandsPseudoTrkPx[numPackedCands]/F");
    mytree_->Branch("packedCandsPseudoTrkPy", &packedCandsPseudoTrkPy, "packedCandsPseudoTrkPy[numPackedCands]/F");
    mytree_->Branch("packedCandsPseudoTrkPz", &packedCandsPseudoTrkPz, "packedCandsPseudoTrkPz[numPackedCands]/F");
    mytree_->Branch("packedCandsPseudoTrkEta", &packedCandsPseudoTrkEta, "packedCandsPseudoTrkEta[numPackedCands]/F");
    mytree_->Branch("packedCandsPseudoTrkPhi", &packedCandsPseudoTrkPhi, "packedCandsPseudoTrkPhi[numPackedCands]/F");
    mytree_->Branch("packedCandsPseudoTrkCharge", &packedCandsPseudoTrkCharge, "packedCandsPseudoTrkCharge[numPackedCands]/I");
    mytree_->Branch("packedCandsPseudoTrkVx", &packedCandsPseudoTrkVx, "packedCandsPseudoTrkVx[numPackedCands]/F");
    mytree_->Branch("packedCandsPseudoTrkVy", &packedCandsPseudoTrkVy, "packedCandsPseudoTrkVy[numPackedCands]/F");
    mytree_->Branch("packedCandsPseudoTrkVz", &packedCandsPseudoTrkVz, "packedCandsPseudoTrkVz[numPackedCands]/F");
    mytree_->Branch("packedCandsPseudoTrkChi2Norm", &packedCandsPseudoTrkChi2Norm, "packedCandsPseudoTrkChi2Norm[numPackedCands]/F");
    mytree_->Branch("packedCandsPseudoTrkNumberOfHits", &packedCandsPseudoTrkNumberOfHits, "packedCandsPseudoTrkNumberOfHits[numPackedCands]/I");
    mytree_->Branch("packedCandsPseudoTrkNumberOfPixelHits", &packedCandsPseudoTrkNumberOfPixelHits, "packedCandsPseudoTrkNumberOfHits[numPackedCands]/I");
//    mytree_->Branch("packedCandsPseudoTrkPixelLayersWithMeasurement", &packedCandsPseudoTrkPixelLayersWithMeasurement, "packedCandsPseudoTrkPixelLayersWithMeasurement[numPackedCands]/I");
//    mytree_->Branch("packedCandsPseudoTrkStripLayersWithMeasurement", &packedCandsPseudoTrkStripLayersWithMeasurement, "packedCandsPseudoTrkStripLayersWithMeasurement[numPackedCands]/I");
//    mytree_->Branch("packedCandsPseudoTrkTrackerLayersWithMeasurement", &packedCandsPseudoTrkTrackerLayersWithMeasurement, "packedCandsPseudoTrkTrackerLayersWithMeasurement[numPackedCands]/I");
    mytree_->Branch("packedCandsHighPurityTrack", &packedCandsHighPurityTrack, "packedCandsHighPurityTrack[numPackedCands]/I");
    mytree_->Branch("packedCandsTrkImpactTransDist", &packedCandsTrkImpactTransDist, "packedCandsTrkImpactTransDist[numPackedCands]/F");
    mytree_->Branch("packedCandsTrkImpactTransError", &packedCandsTrkImpactTransError, "packedCandsTrkImpactTransError[numPackedCands]/F");
    mytree_->Branch("packedCandsTrkImpactTransSignificance", &packedCandsTrkImpactTransSignificance, "packedCandsTrkImpactTransSignificance[numPackedCands]/F");
    mytree_->Branch("packedCandsTrk3DDist", &packedCandsTrk3DDist, "packedCandsTrk3DDist[numPackedCands]/F");
    mytree_->Branch("packedCandsTrk3DError", &packedCandsTrk3DError, "packedCandsTrk3DError[numPackedCands]/F");
    mytree_->Branch("packedCandsTrk3DSignificance", &packedCandsTrk3DSignificance, "packedCandsTrk3DSignificance[numPackedCands]/F");

    mytree_->Branch("numChsTrackPairs", &numChsTrackPairs, "numChsTrackPairs/I");
    mytree_->Branch("chsTkPairIndex1", &chsTkPairIndex1, "chsTkPairIndex1[numChsTrackPairs]/I");
    mytree_->Branch("chsTkPairIndex2", &chsTkPairIndex2, "chsTkPairIndex2[numChsTrackPairs]/I");
    mytree_->Branch("chsTkPairTkVtxPx", &chsTkPairTkVtxPx, "chsTkPairTkVtxPx[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVtxPy", &chsTkPairTkVtxPy, "chsTkPairTkVtxPy[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVtxPz", &chsTkPairTkVtxPz, "chsTkPairTkVtxPz[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVtxP2", &chsTkPairTkVtxP2, "chsTkPairTkVtxP2[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVx", &chsTkPairTkVx, "chsTkPairTkVx[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVy", &chsTkPairTkVy, "chsTkPairTkVy[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVz", &chsTkPairTkVz, "chsTkPairTkVz[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVtxCov00", &chsTkPairTkVtxCov00, "chsTkPairTkVtxCov00[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVtxCov01", &chsTkPairTkVtxCov01, "chsTkPairTkVtxCov01[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVtxCov02", &chsTkPairTkVtxCov02, "chsTkPairTkVtxCov02[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVtxCov10", &chsTkPairTkVtxCov10, "chsTkPairTkVtxCov10[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVtxCov11", &chsTkPairTkVtxCov11, "chsTkPairTkVtxCov11[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVtxCov12", &chsTkPairTkVtxCov12, "chsTkPairTkVtxCov12[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVtxCov20", &chsTkPairTkVtxCov20, "chsTkPairTkVtxCov20[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVtxCov21", &chsTkPairTkVtxCov21, "chsTkPairTkVtxCov21[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVtxCov22", &chsTkPairTkVtxCov22, "chsTkPairTkVtxCov22[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVtxChi2", &chsTkPairTkVtxChi2, "chsTkPairTkVtxChi2[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVtxNdof", &chsTkPairTkVtxNdof, "chsTkPairTkVtxNdof[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVtxTime", &chsTkPairTkVtxTime, "chsTkPairTkVtxTime[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVtxTimeError", &chsTkPairTkVtxTimeError, "chsTkPairTkVtxTimeError[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVtxAngleXY", &chsTkPairTkVtxAngleXY, "chsTkPairTkVtxAngleXY[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVtxDistMagXY", &chsTkPairTkVtxDistMagXY, "chsTkPairTkVtxDistMagXY[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVtxDistMagXYSigma", &chsTkPairTkVtxDistMagXYSigma, "chsTkPairTkVtxDistMagXYSigma[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVtxAngleXYZ", &chsTkPairTkVtxAngleXYZ, "chsTkPairTkVtxAngleXYZ[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVtxDistMagXYZ", &chsTkPairTkVtxDistMagXYZ, "chsTkPairTkVtxDistMagXYZ[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVtxDistMagXYZSigma", &chsTkPairTkVtxDistMagXYZSigma, "chsTkPairTkVtxDistMagXYZSigma[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTk1Pt", &chsTkPairTk1Pt, "chsTkPairTk1Pt[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTk1Px", &chsTkPairTk1Px, "chsTkPairTk1Px[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTk1Py", &chsTkPairTk1Py, "chsTkPairTk1Py[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTk1Pz", &chsTkPairTk1Pz, "chsTkPairTk1Pz[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTk1P2", &chsTkPairTk1P2, "chsTkPairTk1P2[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTk1Eta", &chsTkPairTk1Eta, "chsTkPairTk1Eta[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTk1Phi", &chsTkPairTk1Phi, "chsTkPairTk1Phi[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTk1Charge", &chsTkPairTk1Charge, "chsTkPairTk1Charge[numChsTrackPairs]/I");
    mytree_->Branch("chsTkPairTk1Chi2", &chsTkPairTk1Chi2, "chsTkPairTk1Chi2[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTk1Ndof", &chsTkPairTk1Ndof, "chsTkPairTk1Ndof[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTk2Pt", &chsTkPairTk2Pt, "chsTkPairTk2Pt[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTk2Px", &chsTkPairTk2Px, "chsTkPairTk2Px[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTk2Py", &chsTkPairTk2Py, "chsTkPairTk2Py[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTk2Pz", &chsTkPairTk2Pz, "chsTkPairTk2Pz[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTk2P2", &chsTkPairTk2P2, "chsTkPairTk2P2[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTk2Eta", &chsTkPairTk2Eta, "chsTkPairTk2Eta[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTk2Phi", &chsTkPairTk2Phi, "chsTkPairTk2Phi[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTk2Charge", &chsTkPairTk2Charge, "chsTkPairTk2Charge[numChsTrackPairs]/I");
    mytree_->Branch("chsTkPairTk2Chi2", &chsTkPairTk2Chi2, "chsTkPairTk2Chi2[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTk2Ndof", &chsTkPairTk2Ndof, "chsTkPairTk2Ndof[numChsTrackPairs]/F");
    mytree_->Branch("chsTkPairTkVtxDcaPreFit", &chsTkPairTkVtxDcaPreFit, "chsTkPairTkVtxDcaPreFit[numChsTrackPairs]/F");
}

void MakeTopologyNtupleMiniAOD::bookPVbranches() {
    mytree_->Branch("numPVs", &numPVs, "numPVs/I");
    mytree_->Branch("pvX", &pvX, "pvX[numPVs]/F");
    mytree_->Branch("pvY", &pvY, "pvY[numPVs]/F");
    mytree_->Branch("pvZ", &pvZ, "pvZ[numPVs]/F");
    mytree_->Branch("pvCov00", &pvCov00, "pvCov00[numPVs]/F");
    mytree_->Branch("pvCov01", &pvCov01, "pvCov01[numPVs]/F");
    mytree_->Branch("pvCov02", &pvCov02, "pvCov02[numPVs]/F");
    mytree_->Branch("pvCov10", &pvCov10, "pvCov10[numPVs]/F");
    mytree_->Branch("pvCov11", &pvCov11, "pvCov11[numPVs]/F");
    mytree_->Branch("pvCov12", &pvCov12, "pvCov12[numPVs]/F");
    mytree_->Branch("pvCov20", &pvCov20, "pvCov20[numPVs]/F");
    mytree_->Branch("pvCov21", &pvCov21, "pvCov21[numPVs]/F");
    mytree_->Branch("pvCov22", &pvCov22, "pvCov22[numPVs]/F");
    mytree_->Branch("pvRho", &pvRho, "pvRho[numPVs]/F");
    mytree_->Branch("pvIsFake", &pvIsFake, "pvIsFake[numPVs]/I");
    mytree_->Branch("pvNdof", &pvNdof, "pvNdof[numPVs]/F");
    mytree_->Branch("pvChi2", &pvChi2, "pvChi2[numPVs]/F");
    mytree_->Branch("pvNtracks", &pvNtracks, "pvNtracks[numPVs]/I");
    mytree_->Branch("pvNtracksW05", &pvNtracksW05, "pvNtracksW05[numPVs]/I");
    mytree_->Branch("pvTime", &pvTime, "pvTime[numPVs]/F");
    mytree_->Branch("pvTimeError", &pvTime, "pvTimeError[numPVs]/F");
}
void MakeTopologyNtupleMiniAOD::bookSVbranches() {
    mytree_->Branch("numSVs", &numSVs, "numSVs/I");
    mytree_->Branch("svPt", &svPt, "svPt[numSVs]/F");
    mytree_->Branch("svPx", &svPx, "svPx[numSVs]/F");
    mytree_->Branch("svPy", &svPy, "svPy[numSVs]/F");
    mytree_->Branch("svPz", &svPz, "svPz[numSVs]/F");
    mytree_->Branch("svMass", &svMass, "svMass[numSVs]/F");
    mytree_->Branch("svE", &svE, "svE[numSVs]/F");
    mytree_->Branch("svEta", &svEta, "svEta[numSVs]/F");
    mytree_->Branch("svTheta", &svTheta, "svTheta[numSVs]/F");
    mytree_->Branch("svPhi", &svPhi, "svPhi[numSVs]/F");
    mytree_->Branch("svX", &svX, "svX[numSVs]/F");
    mytree_->Branch("svY", &svY, "svY[numSVs]/F");
    mytree_->Branch("svZ", &svZ, "svZ[numSVs]/F");
    mytree_->Branch("svCov00", &svCov00, "svCov00[numSVs]/F");
    mytree_->Branch("svCov01", &svCov01, "svCov01[numSVs]/F");
    mytree_->Branch("svCov02", &svCov02, "svCov02[numSVs]/F");
    mytree_->Branch("svCov10", &svCov10, "svCov10[numSVs]/F");
    mytree_->Branch("svCov11", &svCov11, "svCov11[numSVs]/F");
    mytree_->Branch("svCov12", &svCov12, "svCov12[numSVs]/F");
    mytree_->Branch("svCov20", &svCov20, "svCov20[numSVs]/F");
    mytree_->Branch("svCov21", &svCov21, "svCov21[numSVs]/F");
    mytree_->Branch("svCov22", &svCov22, "svCov22[numSVs]/F");
    mytree_->Branch("svVertexChi2", &svVertexChi2, "svVertexChi2[numSVs]/F");
    mytree_->Branch("svVertexNdof", &svVertexNdof, "svVertexNdof[numSVs]/F");
    mytree_->Branch("svNtracks", &svNtracks, "svNtracks[numSVs]/I");
    mytree_->Branch("svDist3D", &svDist3D, "svDist3D[numSVs]/F");
    mytree_->Branch("svDist3DSig", &svDist3DSig, "svDist3DSig[numSVs]/F");
    mytree_->Branch("svDist3DError", &svDist3DError, "svDist3DError[numSVs]/F");
    mytree_->Branch("svDistXY", &svDistXY, "svDistXY[numSVs]/F");
    mytree_->Branch("svDistXYSig", &svDistXYSig, "svDistXYSig[numSVs]/F");
    mytree_->Branch("svDistXYError", &svDistXYError, "svDistXYError[numSVs]/F");
    mytree_->Branch("svAnglePV", &svAnglePV, "svAnglePV[numSVs]/F");
    mytree_->Branch("svIsLambda", &svIsLambda, "svIsLambda[numSVs]/I");
    mytree_->Branch("svIsKshort", &svIsKshort, "svIsKshort[numSVs]/I");
}

bool MakeTopologyNtupleMiniAOD::leptonScalarAncestor(const reco::Candidate* genPar, const bool& directDecay, const int& lepId) {
    if ( genPar->numberOfMothers() == 0 ) return false; // if there aren't any more mothers to check , return false
    if ( debugMode_ && !directDecay ) std::cout << "leptonScalarAncestor - mother Id: " << std::abs(genPar->mother()->pdgId()) << std::endl;

    const int motherId {std::abs(genPar->mother()->pdgId())};

    if ( motherId == scalarPid_ ) return true; // if mother is scalar, return true
    else if ( directDecay && motherId == lepId ) return leptonScalarAncestor(genPar->mother(), directDecay, lepId); // If looking for chained muon decays from scalar, check mother == 13, and search that muon's mother
    else if ( directDecay && motherId != lepId ) return false; // if looking for chained muon decays from scalar, and mother != 13 (or scalarId implicitly above), return false;
    else return leptonScalarAncestor(genPar->mother()); // if not looking for chained muon decays from scalar, check this particle's mother Id
}

bool MakeTopologyNtupleMiniAOD::jetScalarAncestor(const reco::Candidate* genJetMother) {
    if ( debugMode_ ) std::cout << "jetScalarAncestor - mother Id: " << std::abs(genJetMother->pdgId()) << std::endl;
    if ( std::abs(genJetMother->pdgId()) == scalarPid_ ) return true;
    else if ( genJetMother->numberOfMothers() == 0 ) return false;
    else return jetScalarAncestor(genJetMother->mother());
}

// ------------ method called once each job just before starting event loop
// ------------
void
    // MakeTopologyNtupleMiniAOD::beginJob(const edm::EventSetup&
    // #<{(|unused|)}>#)
    MakeTopologyNtupleMiniAOD::beginJob()
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
void MakeTopologyNtupleMiniAOD::endJob()
{
    std::cout << "+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+="
              << std::endl;
    std::cout << "\n\nJOB Summary:" << std::endl;
    std::cout << "number of events processed: " << histocontainer1D_["eventcount"]->GetEntries() << std::endl;
    std::cout << "number of events added to tree: " << mytree_->GetEntries() << std::endl;
    std::cout << "\n+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+="
              << std::endl;
}
void MakeTopologyNtupleMiniAOD::fillTriggerData(const edm::Event& iEvent)
{
    // std::cout << "fillTriggerData CHECK" << std::endl;
    for (int& TriggerBit : TriggerBits)
    { // size hard-coded in MakeTopologyNtuple.h!!!
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

        for (int itrig{0}; itrig < (int)hltnames_.size(); ++itrig)
        {
            const bool accept{hltResults->accept(itrig)};
            // if (histocontainer1D_["eventcount"]->GetBinContent(0.0) < 2)
            // {
            //     std::cout << "TRIGGER BIT:" << itrig
            //               << ", NAME:" << hltnames_[itrig]
            //               << " FIRED:" << accept << std::endl;
            // }
            int trigbit{0};
            if (accept)
            {
                trigbit = 1;
            }
            if (!hltResults->wasrun(itrig))
                trigbit = -1;
            if (hltResults->error(itrig))
                trigbit = -2;

            for (size_t iTrigList{0}; iTrigList < triggerList_.size();
                 iTrigList++)
            {
                if (triggerList_[iTrigList] == hltnames_[itrig])
                {
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

    if (metFilterResults.product()->wasrun())
    {
        const edm::TriggerNames& metFilterNames{
            iEvent.triggerNames(*metFilterResults)};
        // HLTBits_Size = metFilterResults.product()->size();

        metFilterNames_ = metFilterNames.triggerNames();
        for (int iFilter{0}; iFilter < (int)metFilterNames_.size(); ++iFilter)
        {
            const bool accept(metFilterResults->accept(iFilter));
            // if (histocontainer1D_["eventcount"]->GetBinContent(0.0) < 2)
            // {
            //     if (metFilterNames_[iFilter] == "Flag_noBadMuons")
            //     {
            //         std::cout << "TRIGGER BIT:" << iFilter
            //                   << ", NAME:" << metFilterNames_[iFilter]
            //                   << " FIRED:" << accept << std::endl;
            //     }
            // }
            int filterbit{0};
            if (accept)
            {
                filterbit = 1;
            }
            if (!metFilterResults->wasrun(iFilter))
                filterbit = -1;
            if (metFilterResults->error(iFilter))
                filterbit = -2;
            for (size_t iMetFilterList{0};
                 iMetFilterList < metFilterList_.size();
                 iMetFilterList++)
            {
                if (metFilterList_[iMetFilterList] == metFilterNames_[iFilter])
                {
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
DEFINE_FWK_MODULE(MakeTopologyNtupleMiniAOD);

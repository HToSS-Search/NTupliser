/// -*- C++ -*-
//
// Package:    MakeTopologyNtuple
// Class:      MakeTopologyNtuple
//
// Original Author:  Freya Blekman
// Modified by: Duncan Leggat, Alexander Morton
//         Created:  Wed April 22 19:23:10 CET 2009
// $Id: MakeTopologyNtuple.h,v 1.68 2010/11/05 15:32:16 chadwick Exp $
//
//

#ifndef __MAKE_TOPOLOGY_NTUPLE_MINIAOD_LT_H__
#define __MAKE_TOPOLOGY_NTUPLE_MINIAOD_LT_H__

#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "DataFormats/Math/interface/LorentzVector.h"


typedef math::PtEtaPhiELorentzVectorD FourVectorPtEtaPhiEVector;
typedef math::PtEtaPhiMLorentzVectorD FourVectorPtEtaPhiMVector;

class EffectiveAreas;
class TTree;

class MakeTopologyNtupleMiniAOD_LT : public edm::EDAnalyzer
{
    public:
    explicit MakeTopologyNtupleMiniAOD_LT(const edm::ParameterSet&);
    ~MakeTopologyNtupleMiniAOD_LT();

    private:
    //  virtual void beginJob(const edm::EventSetup&) ;
    virtual void beginJob();
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    virtual void endJob();

    // ----------member data ---------------------------

    edm::Service<TFileService> fs;
    // std::map<std::string, TH1I*> histocontainer1I_; // simple map to contain all 1I histograms. Histograms are booked in the beginJob() method
    std::map<std::string, TH1D*> histocontainer1D_; // simple map to contain all 1D histograms. Histograms are booked in the beginJob() method
    // std::map<std::string, TH2D*> histocontainer2D_; // simple map to contain all 2D histograms. Histograms are booked in the beginJob() method

    edm::EDGetTokenT<std::vector<pat::PackedGenParticle>> packedGenParticleToken_;
    edm::EDGetTokenT<reco::GenParticleCollection> genParticlesToken_;
    edm::EDGetTokenT<reco::GenParticleCollection> genSimParticlesToken_;
    edm::EDGetTokenT<std::vector<PileupSummaryInfo>> pileupToken_;

    // Debug flag
    const bool debugMode_{};


    // Sets whether the sample is ttbar or not. Default is false. This affects
    // top pt reweighting of the sample.
    const bool isggH_{};
    std::string hadronType_;


    // Generator level info
    edm::EDGetTokenT<GenEventInfoProduct> generatorToken_;

    bool runMCInfo_{};
    bool runPUReWeight_{};
    bool doCuts_{};
    std::string Skim_{};
    const bool isMC_{};
    double orig_lt{};
    double mass{};
    std::vector<std::string> lifetimeUp_;
    std::vector<std::string> lifetimeDown_;



    bool ran_jetloop_{};
    bool ran_eleloop_{};
    bool ran_muonloop_{};
    bool ran_mcloop_{};
    bool ran_postloop_{};
    bool ran_PV_{};
    bool ran_BS_{};
    bool ran_tracks_{};
    bool ran_isotracks_{};
    bool ran_packedCands_{};
    bool ran_photonTau_{};
    const bool isLHEflag_{};

    // and an ntuple (filling in the methods)
    void fillEventInfo(const edm::Event&, const edm::EventSetup&);
    void fillMCInfo(const edm::Event&, const edm::EventSetup&);
    void fillSummaryVariables(void); // should only be called after all other functions.

    // Helper functions
    void bookBranches(void); // does all the branching.
    void bookMCBranches(void); // called by bookBranches, makes MC branches.
    float getLifetimeReweight(float old_lt, float new_lt, float L_scalar1, float L_scalar2, FourVectorPtEtaPhiMVector& vec_scalar1, FourVectorPtEtaPhiMVector& vec_scalar2);

    TTree* mytree_{};

    double origWeightForNorm_{};

    int processId_{};
    int genMyProcId{};
    float processPtHat_{};

    double weight_{};

    void cleararrays(void); // used to set everything in the following arrays
                            // to zero or unphysical numbers
    void clearMCarrays(void); // clearing MC info

    int numVert{};

    // float mhtPx{};
    // float mhtPy{};
    // float mhtPt{};
    // float mhtPhi{};
    // float mhtSumEt{};
    // float mhtSignif{};

    // gen particle vars
    static constexpr size_t NGENPARMAX{1000};
    size_t nGenPar{};
    int genParStatus[NGENPARMAX]{}; 
    float genParEta[NGENPARMAX]{};
    float genParPhi[NGENPARMAX]{};
    float genParE[NGENPARMAX]{};
    float genParPt[NGENPARMAX]{};
    int genParId[NGENPARMAX]{};
    float genParVx[NGENPARMAX]{};
    float genParVy[NGENPARMAX]{};
    float genParVz[NGENPARMAX]{};
    int genParNumMothers[NGENPARMAX]{}; 
    int genParMotherId[NGENPARMAX]{}; 
    int genParMotherIndex[NGENPARMAX]{}; 
    int genParNumDaughters[NGENPARMAX]{};
    int genParDaughterId1[NGENPARMAX]{};
    int genParDaughterId2[NGENPARMAX]{};
    int genParDaughter1Index[NGENPARMAX]{};
    int genParDaughter2Index[NGENPARMAX]{};
    int genParCharge[NGENPARMAX]{};

    int evtRun{};
    int evtnum{};
    float evtlumiblock{};
    int eventCount{};

};

#endif

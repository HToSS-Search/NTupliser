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

#ifndef __MAKE_MINI_MUON_NTUPLE_MINIAOD_H__
#define __MAKE_MINI_MUON_NTUPLE_MINIAOD_H__

#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"

class EffectiveAreas;
class TTree;

class MakeMiniMuonNtupleMiniAOD : public edm::EDAnalyzer
{
    public:
    explicit MakeMiniMuonNtupleMiniAOD(const edm::ParameterSet&);
    ~MakeMiniMuonNtupleMiniAOD();

    private:
    //  virtual void beginJob(const edm::EventSetup&) ;
    virtual void beginJob();
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    virtual void endJob();

    // ----------member data ---------------------------

    edm::Service<TFileService> fs;
    std::map<std::string, TH1I*> histocontainer1I_; // simple map to contain all 1I histograms. Histograms are booked in the beginJob() method
    std::map<std::string, TH1D*> histocontainer1D_; // simple map to contain all 1D histograms. Histograms are booked in the beginJob() method
    std::map<std::string, TH2D*> histocontainer2D_; // simple map to contain all 2D histograms. Histograms are booked in the beginJob() method

    edm::EDGetTokenT<reco::BeamSpot> beamSpotToken_;
    edm::EDGetTokenT<reco::ConversionCollection> conversionsToken_;

    edm::InputTag muoLabel_;

    edm::EDGetTokenT<pat::MuonCollection> patMuonsToken_;

    edm::EDGetTokenT<edm::TriggerResults> trigToken_;
    edm::EDGetTokenT<edm::TriggerResults> metFilterToken_;
    std::vector<std::string> fakeTrigLabelList_;
    std::vector<std::string> triggerList_;
    std::vector<std::string> metFilterList_;

    edm::InputTag l1TrigLabel_;
    edm::EDGetTokenT<reco::GenParticleCollection> genParticlesToken_;
    edm::EDGetTokenT<reco::GenParticleCollection> genSimParticlesToken_;
    edm::EDGetTokenT<reco::VertexCollection> pvLabel_;
    edm::EDGetTokenT<reco::VertexCompositePtrCandidateCollection> svLabel_;
    edm::EDGetTokenT<reco::VertexCompositePtrCandidateCollection> kshortToken_;
    edm::EDGetTokenT<reco::VertexCompositePtrCandidateCollection> lambdaToken_;
    edm::EDGetTokenT<double> rhoToken_;
    edm::EDGetTokenT<std::vector<PileupSummaryInfo>> pileupToken_;

    // Debug flag
    const bool debugMode_{};

    // Sets stuff for different eras
    const bool is2016_{};

    // Sets whether the sample is ttbar or not. Default is false. This affects
    // top pt reweighting of the sample.
    const bool isttbar_{};
    edm::InputTag ttGenEvent_;

    // Generator level info
    edm::EDGetTokenT<LHEEventProduct> externalLHEToken_;
    const int pdfIdStart_{};
    const int pdfIdEnd_{};
    const int alphaIdStart_{};
    const int alphaIdEnd_{};
    edm::EDGetTokenT<GenEventInfoProduct> pdfInfoToken_;
    edm::EDGetTokenT<GenEventInfoProduct> generatorToken_;

    std::map<std::string, int> hltpasses_;
    std::vector<std::string> hltnames_;
    std::vector<std::string> metFilterNames_;

    bool filledBIDInfo_{};
    bool runMCInfo_{};
    bool runPUReWeight_{};
    bool doCuts_{};
    bool doSynch_{};

    bool runPDFUncertainties_{};
    bool useResidualJEC_{};

    bool ran_muonloop_{};
    bool ran_mcloop_{};
    bool ran_postloop_{};
    bool ran_PV_{};
    bool ran_BS_{};
    bool check_triggers_;
    std::string muoIDquality_;
    bool flavorHistoryTag_{};
    double dREleGeneralTrackMatch_{};
    double magneticField_{};
    double correctFactor_{};
    double maxDist_{};
    double maxDcot_{};
    edm::InputTag ebRecHits_;
    edm::InputTag eeRecHits_;
    const bool isMCatNLO_{};
    const bool isLHEflag_{};
    const bool hasAlphaWeightFlag_{};
    const bool skipIsrFsrWeights_{};

    // and an ntuple (filling in the methods)
    void fillBeamSpot(const edm::Event&, const edm::EventSetup&);
    void fillMuons          (const edm::Event&, const edm::EventSetup&, edm::EDGetTokenT<pat::MuonCollection>, const std::string&);
    void fillEventInfo(const edm::Event&, const edm::EventSetup&);
    void fillMCInfo(const edm::Event&, const edm::EventSetup&);
    void fillTriggerData(const edm::Event&);
    void fillSummaryVariables(void); // should only be called after all other functions.

    // Helper functions
    void bookBranches(void); // does all the branching.
    void bookMuonBranches(const std::string& ID, const std::string& name); // called by bookBranches, makes muon branches.
    void bookMCBranches(void); // called by bookBranches, makes MC branches.

    TTree* mytree_{};

    double weight_muF0p5_{};
    double weight_muF2_{};
    double weight_muR0p5_{};
    double weight_muR2_{};
    double weight_muF0p5muR0p5_{};
    double weight_muF2muR2_{};

    double isrRedHi{};
    double fsrRedHi{};
    double isrRedLo{};
    double fsrRedLo{};
    double isrDefHi{};
    double fsrDefHi{};
    double isrDefLo{};
    double fsrDefLo{};
    double isrConHi{};
    double fsrConHi{};
    double isrConLo{};
    double fsrConLo{};

    double origWeightForNorm_{};

    double weight_pdfMax_{};
    double weight_pdfMin_{};
    double weight_alphaMax_{};
    double weight_alphaMin_{};

    int processId_{};
    int genMyProcId{};
    float processPtHat_{};

    double weight_{};
    double topPtReweight{};

    std::map<std::string, int> numMuo;

    math::XYZPoint beamSpotPoint_;
    math::XYZPoint vertexPoint_;
    reco::Vertex* vertexPrimary_;

    unsigned int flavorHistory{};

    template<class C>
    struct IndexSorter
    {
        IndexSorter(const C& values, bool decreasing = true)
            : values_(values), decrease_(decreasing)
        {
        }
        std::vector<size_t> operator()() const
        {
            std::vector<size_t> result;
            result.reserve(values_.size());
            for (size_t i = 0; i < values_.size(); ++i)
                result.emplace_back(i);
            sort(result.begin(), result.end(), *this);
            return result;
        }
        bool operator()(int a, int b)
        {
            if (decrease_)
                return values_[a] > values_[b];
            else
                return values_[a] < values_[b];
        }
        const C& values_;
        bool decrease_;
    };

    void cleararrays(void); // used to set everything in the following arrays
                            // to zero or unphysical numbers
    void clearPVarrays(void); // clearing PV info, used by cleararrays
    void clearSVarrays(void); // clearing SV info, used by cleararrays
    void clearmuonarrays(const std::string&); // clearing muon info, used by cleararrays
    void clearMCarrays(void); // clearing MC info

    std::vector<float> muonEts; // just used for sorting

    float beamSpotX{};
    float beamSpotY{};
    float beamSpotZ{};

    static constexpr size_t NPVSMAX{80};
    int numPVs{};
    float pvX[NPVSMAX]{};
    float pvY[NPVSMAX]{};
    float pvZ[NPVSMAX]{};
    float pvCov00[NPVSMAX]{};
    float pvCov01[NPVSMAX]{};
    float pvCov02[NPVSMAX]{};
    float pvCov10[NPVSMAX]{};
    float pvCov11[NPVSMAX]{};
    float pvCov12[NPVSMAX]{};
    float pvCov20[NPVSMAX]{};
    float pvCov21[NPVSMAX]{};
    float pvCov22[NPVSMAX]{};
    float pvRho[NPVSMAX]{};
    int pvIsFake[NPVSMAX]{};
    float pvChi2[NPVSMAX]{};	
    float pvNdof[NPVSMAX]{};
    int pvNtracks[NPVSMAX]{};
    int pvNtracksW05[NPVSMAX]{};
    float pvTime[NPVSMAX]{};
    float pvTimeError[NPVSMAX]{};

    // gen branches


    // MC Truth
    size_t nT{};
    size_t nThadronic{};
    size_t nb{};
    size_t nWhadronic{};
    size_t nTleptonic{};
    size_t nWleptonic{};
    int VQQBosonAbsId{};

    static constexpr size_t NTOPMCINFOSMAX{20};
    float T_hadronicMCTruthE[NTOPMCINFOSMAX]{};
    float T_hadronicMCTruthEt[NTOPMCINFOSMAX]{};
    float T_hadronicMCTruthPx[NTOPMCINFOSMAX]{};
    float T_hadronicMCTruthPy[NTOPMCINFOSMAX]{};
    float T_hadronicMCTruthPz[NTOPMCINFOSMAX]{};
    int T_hadronicMotherIndex[NTOPMCINFOSMAX]{};

    float T_leptonicMCTruthE[NTOPMCINFOSMAX]{};
    float T_leptonicMCTruthEt[NTOPMCINFOSMAX]{};
    float T_leptonicMCTruthPx[NTOPMCINFOSMAX]{};
    float T_leptonicMCTruthPy[NTOPMCINFOSMAX]{};
    float T_leptonicMCTruthPz[NTOPMCINFOSMAX]{};
    int T_leptonicMotherIndex[NTOPMCINFOSMAX]{};

    float bMCTruthE[NTOPMCINFOSMAX]{};
    float bMCTruthEt[NTOPMCINFOSMAX]{};
    float bMCTruthPx[NTOPMCINFOSMAX]{};
    float bMCTruthPy[NTOPMCINFOSMAX]{};
    float bMCTruthPz[NTOPMCINFOSMAX]{};
    int bMCTruthMother[NTOPMCINFOSMAX]{};

    float W_hadronicMCTruthE[NTOPMCINFOSMAX]{};
    float W_hadronicMCTruthEt[NTOPMCINFOSMAX]{};
    float W_hadronicMCTruthPx[NTOPMCINFOSMAX]{};
    float W_hadronicMCTruthPy[NTOPMCINFOSMAX]{};
    float W_hadronicMCTruthPz[NTOPMCINFOSMAX]{};
    int W_hadronicMCTruthPID[NTOPMCINFOSMAX]{};
    int W_hadronicMCTruthMother[NTOPMCINFOSMAX]{};

    float W_leptonicMCTruthE[NTOPMCINFOSMAX]{};
    float W_leptonicMCTruthEt[NTOPMCINFOSMAX]{};
    float W_leptonicMCTruthPx[NTOPMCINFOSMAX]{};
    float W_leptonicMCTruthPy[NTOPMCINFOSMAX]{};
    float W_leptonicMCTruthPz[NTOPMCINFOSMAX]{};
    int W_leptonicMCTruthPID[NTOPMCINFOSMAX]{};
    int W_leptonicMCTruthMother[NTOPMCINFOSMAX]{};

    int isElePlusJets{};

    //  float remainingEnergy[20];

    int numVert{};

    float mhtPx{};
    float mhtPy{};
    float mhtPt{};
    float mhtPhi{};
    float mhtSumEt{};
    float mhtSignif{};

    static constexpr size_t NMUONSMAX{20};
    std::map<std::string, std::vector<float>> muonSortedE;
    std::map<std::string, std::vector<float>> muonSortedEt;
    std::map<std::string, std::vector<float>> muonSortedPt;
    std::map<std::string, std::vector<float>> muonSortedEta;
    std::map<std::string, std::vector<float>> muonSortedTheta;
    std::map<std::string, std::vector<float>> muonSortedPhi;
    std::map<std::string, std::vector<float>> muonSortedPx;
    std::map<std::string, std::vector<float>> muonSortedPy;
    std::map<std::string, std::vector<float>> muonSortedPz;
    std::map<std::string, std::vector<int>> muonSortedCharge;
    std::map<std::string, std::vector<int>> muonSortedLooseCutId;
    std::map<std::string, std::vector<int>> muonSortedMediumCutId;
    std::map<std::string, std::vector<int>> muonSortedTightCutId;
    std::map<std::string, std::vector<int>> muonSortedPfIsoVeryLoose;
    std::map<std::string, std::vector<int>> muonSortedPfIsoLoose;
    std::map<std::string, std::vector<int>> muonSortedPfIsoMedium;
    std::map<std::string, std::vector<int>> muonSortedPfIsoTight;
    std::map<std::string, std::vector<int>> muonSortedPfIsoVeryTight;
    std::map<std::string, std::vector<int>> muonSortedTkIsoLoose;
    std::map<std::string, std::vector<int>> muonSortedTkIsoTight;
    std::map<std::string, std::vector<int>> muonSortedMvaLoose;
    std::map<std::string, std::vector<int>> muonSortedMvaMedium;
    std::map<std::string, std::vector<int>> muonSortedMvaTight;

    std::map<std::string, std::vector<float>> muonSortedGlobalID;
    std::map<std::string, std::vector<float>> muonSortedTrackID;
    std::map<std::string, std::vector<float>> muonSortedChi2;
    std::map<std::string, std::vector<float>> muonSortedD0;
    std::map<std::string, std::vector<float>> muonSortedDBBeamSpotCorrectedTrackD0;
    std::map<std::string, std::vector<float>> muonSortedDBInnerTrackD0;
    std::map<std::string, std::vector<float>> muonSortedBeamSpotCorrectedD0;
    std::map<std::string, std::vector<int>> muonSortedTrackNHits;
    std::map<std::string, std::vector<int>> muonSortedValidHitsGlobal;
    std::map<std::string, std::vector<float>> muonSortedNDOF; // n_d.o.f

    // Extra muon variables used for ID and stuff
    std::map<std::string, std::vector<int>> muonSortedTkLysWithMeasurements;
    std::map<std::string, std::vector<float>> muonSortedGlbTkNormChi2;
    std::map<std::string, std::vector<float>> muonSortedInnerTkNormChi2;
    std::map<std::string, std::vector<float>> muonSortedDBPV;
    std::map<std::string, std::vector<float>> muonSortedDBPVError;
    std::map<std::string, std::vector<float>> muonSortedDZPV;
    std::map<std::string, std::vector<float>> muonSortedDZPVError;
    std::map<std::string, std::vector<int>> muonSortedVldPixHits;
    std::map<std::string, std::vector<int>> muonSortedMatchedStations;

    // Vertex location information. For dZ cuts.
    std::map<std::string, std::vector<float>> muonSortedVertX;
    std::map<std::string, std::vector<float>> muonSortedVertY;
    std::map<std::string, std::vector<float>> muonSortedVertZ;

    // Best muon track information
    std::map<std::string, std::vector<float>> muonSortedInnerTkPt;
    std::map<std::string, std::vector<float>> muonSortedInnerTkPx;
    std::map<std::string, std::vector<float>> muonSortedInnerTkPy;
    std::map<std::string, std::vector<float>> muonSortedInnerTkPz;
    std::map<std::string, std::vector<float>> muonSortedInnerTkEta;
    std::map<std::string, std::vector<float>> muonSortedInnerTkPhi;

    std::map<std::string, std::vector<float>> muonSortedChargedHadronIso;
    std::map<std::string, std::vector<float>> muonSortedNeutralHadronIso;
    std::map<std::string, std::vector<float>> muonSortedPhotonIso;

    std::map<std::string, std::vector<float>> muonSortedTrackIso;
    std::map<std::string, std::vector<float>> muonSortedECalIso;
    std::map<std::string, std::vector<float>> muonSortedHCalIso;
    std::map<std::string, std::vector<float>> muonSortedComRelIso;
    std::map<std::string, std::vector<float>> muonSortedComRelIsodBeta;
    std::map<std::string, std::vector<float>> muonSortedChHadIso;
    std::map<std::string, std::vector<float>> muonSortedNtHadIso;
    std::map<std::string, std::vector<float>> muonSortedGammaIso;
    std::map<std::string, std::vector<float>> muonSortedPuIso;
    std::map<std::string, std::vector<int>> muonSortedIsPFMuon;

    std::map<std::string, std::vector<int>> muonSortedNumChambers;
    std::map<std::string, std::vector<int>> muonSortedNumMatches;

    // Extra variables used for ICHEP ID during HIP issue stuff
    std::map<std::string, std::vector<float>> muonValidFraction;
    std::map<std::string, std::vector<float>> muonChi2LocalPosition;
    std::map<std::string, std::vector<float>> muonTrkKick;
    std::map<std::string, std::vector<float>> muonSegmentCompatibility;

    std::map<std::string, std::vector<float>> genMuonSortedPt;
    std::map<std::string, std::vector<float>> genMuonSortedEt;
    std::map<std::string, std::vector<float>> genMuonSortedEta;
    std::map<std::string, std::vector<float>> genMuonSortedTheta;
    std::map<std::string, std::vector<float>> genMuonSortedPhi;
    std::map<std::string, std::vector<float>> genMuonSortedPx;
    std::map<std::string, std::vector<float>> genMuonSortedPy;
    std::map<std::string, std::vector<float>> genMuonSortedPz;
    std::map<std::string, std::vector<int>> genMuonSortedCharge;
    std::map<std::string, std::vector<int>> genMuonSortedPdgId;
    std::map<std::string, std::vector<int>> genMuonSortedMotherId;
    std::map<std::string, std::vector<int>> genMuonSortedPromptDecayed;
    std::map<std::string, std::vector<int>> genMuonSortedPromptFinalState;
    std::map<std::string, std::vector<int>> genMuonSortedHardProcess;
    std::map<std::string, std::vector<int>> genMuonSortedPythiaSixStatusThree;

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
    // PDF info
    float genPDFScale{};
    float genPDFx1{};
    float genPDFx2{};
    int genPDFf1{};
    int genPDFf2{};
    // CTEQ_6.6 general purpose
    float genCTEQ66_Weight[44]{};
    // MRST98 NLO
    float genMRST2006nnlo_Weight[31]{};

    // basic 4-vectors for photons,taus as we're not interested in them.
    static constexpr size_t NTAUSMAX{20};
    std::map<std::string, int> numTaus;
    std::map<std::string, std::vector<float>> tau_e;
    std::map<std::string, std::vector<float>> tau_phi;
    std::map<std::string, std::vector<float>> tau_eta;
    std::map<std::string, std::vector<float>> tau_pt;

    std::map<std::string, std::map<std::string, std::vector<float>>> bTagRes;
    std::vector<int> triggerRes;
    std::vector<int> metFilterRes;
//    int Flag_ecalBadCalibReducedMINIAODFilter;
    std::vector<int> HLT_fakeTriggerValues;

    static constexpr size_t NTRIGGERBITSMAX{700};
    int nTriggerBits{};
    int TriggerBits[NTRIGGERBITSMAX]{};

    float topo_sphericity{};
    float topo_aplanarity{};
    float topo_sphericitye{};
    float topo_aplanaritye{};
    float topo_oblateness{};
    float topo_sqrts{};
    float topo_sqrtse{};
    float topo_ht3{};
    float topo_hte{};
    float topo_ht{};

    int evtRun{};
    int evtnum{};
    float evtlumiblock{};
    int eventCount{};

    int bTags{};
    int softTags{};
};

namespace LHAPDF
{
    enum SetType
    {
        EVOLVE = 0,
        LHPDF = 0,
        INTERPOLATE = 1,
        LHGRID = 1
    };
    enum Verbosity
    {
        SILENT = 0,
        LOWKEY = 1,
        DEFAULT = 2
    };
    void setVerbosity(Verbosity noiselevel);
    void initPDFSet(int nset, const std::string& filename, int member = 0);
    void initPDFSet(const std::string& name,
                    LHAPDF::SetType type,
                    int member = 0);
    void initPDFSet(int nset,
                    const std::string& name,
                    LHAPDF::SetType type,
                    int member = 0);
    int numberPDF(int nset);
    void usePDFMember(int nset, int member);
    void usePDFMember(int member);
    double xfx(int nset, double x, double Q, int fl);
    double xfx(double x, double Q, int fl);
    double getXmin(int nset, int member);
    double getXmax(int nset, int member);
    double getQ2min(int nset, int member);
    double getQ2max(int nset, int member);
    void extrapolate(bool extrapolate = true);
} // namespace LHAPDF

#endif

//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Feb  6 15:48:26 2020 by ROOT version 6.14/09
// from TTree HTauTauTree/small tree for HH analysis
// found on file: /eos/home-c/camendol/SKIMS_Legacy2018/SKIMS_30Jan2020/SKIM_ZZ/output_1.root
//////////////////////////////////////////////////////////

#ifndef analysisCode_h
#define analysisCode_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "map"
#include <fstream>
#include <unistd.h>
#include <string>
#include <sys/stat.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <map>

// ROOT
#include <Math/VectorUtil.h>
#include <Math/LorentzVector.h>
#include <Math/PxPyPzM4D.h>
#include <Math/PtEtaPhiE4D.h>
#include <TLorentzVector.h>

using LorentzVector = ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiE4D<float>>;


using namespace std;

class analysisCode {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         MC_weight;
   Float_t         totalWeight;
   Float_t         prescaleWeight;
   Float_t         L1pref_weight;
   Float_t         PUReweight;
   Float_t         bTagweightL;
   Float_t         bTagweightM;
   Float_t         bTagweightT;
   Float_t         TTtopPtreweight;
   Float_t         TTtopPtreweight_up;
   Float_t         TTtopPtreweight_down;
   Float_t         trigSF;
   Float_t         trigSF_single;
   Float_t         trigSF_cross;
   Float_t         VBFtrigSF;
   Float_t         FakeRateSF;
   Float_t         jetFakeSF;
   Float_t         IdAndIsoSF_MVA;
   Float_t         IdAndIsoSF_deep;
   Float_t         IdAndIsoAndFakeSF_MVA;
   Float_t         IdAndIsoAndFakeSF_deep;
   Float_t         DYscale_LL;
   Float_t         DYscale_MM;
   Float_t         DYscale_LL_NLO;
   Float_t         DYscale_MM_NLO;
   Float_t         DYLOtoNLOreweight;
   Float_t         DYptZweight;
   Float_t         DY_NPVweight;
   Int_t           nBhadrons;
   Int_t           lheNOutPartons;
   Int_t           lheNOutB;
   ULong64_t       EventNumber;
   Int_t           RunNumber;
   Int_t           isBoosted;
   Int_t           isVBF;
   Int_t           isVBFtrigger;
   Int_t           genDecMode1;
   Int_t           genDecMode2;
   Float_t         genMHH;
   Float_t         genCosth;
   Int_t           npv;
   Float_t         npu;
   Int_t           lumi;
   Long64_t        triggerbit;
   Int_t           pass_triggerbit;
   Bool_t          cross_monitoring_trig;
   Float_t         rho;
   Int_t           pairType;
   Int_t           isMC;
   Int_t           isOS;
   Float_t         met_phi;
   Float_t         met_et;
   Float_t         met_phi_jetup;
   Float_t         met_et_jetup;
   Float_t         met_phi_jetdown;
   Float_t         met_et_jetdown;
   Float_t         met_phi_tauup;
   Float_t         met_et_tauup;
   Float_t         met_phi_taudown;
   Float_t         met_et_taudown;
   Float_t         met_phi_eleup;
   Float_t         met_et_eleup;
   Float_t         met_phi_eledown;
   Float_t         met_et_eledown;
   Float_t         met_et_corr;
   Float_t         met_cov00;
   Float_t         met_cov01;
   Float_t         met_cov10;
   Float_t         met_cov11;
   Float_t         met_er_phi;
   Float_t         met_er_et;
   Float_t         mT1;
   Float_t         mT2;
   Float_t         dau1_iso;
   Int_t           dau1_MVAiso;
   Int_t           dau1_MVAisoNew;
   Int_t           dau1_MVAisoNewdR0p3;
   Int_t           dau1_CUTiso;
   Int_t           dau1_antiele;
   Int_t           dau1_antimu;
   Int_t           dau1_deepTauVsJet;
   Int_t           dau1_deepTauVsEle;
   Int_t           dau1_deepTauVsMu;
   Float_t         dau1_photonPtSumOutsideSignalCone;
   Bool_t          dau1_byLooseCombinedIsolationDeltaBetaCorr3Hits;
   Bool_t          dau1_byMediumCombinedIsolationDeltaBetaCorr3Hits;
   Bool_t          dau1_byTightCombinedIsolationDeltaBetaCorr3Hits;
   Float_t         dau1_pt;
   Float_t         dau1_pt_tauup;
   Float_t         dau1_pt_taudown;
   Float_t         dau1_pt_eleup;
   Float_t         dau1_pt_eledown;
   Float_t         dau1_eta;
   Float_t         dau1_phi;
   Float_t         dau1_e;
   Float_t         dau1_flav;
   Float_t         dau1_dxy;
   Float_t         dau1_dz;
   Int_t           dau1_decayMode;
   Float_t         genmatched1_pt;
   Float_t         genmatched1_eta;
   Float_t         genmatched1_phi;
   Float_t         genmatched1_e;
   Float_t         genmatched2_pt;
   Float_t         genmatched2_eta;
   Float_t         genmatched2_phi;
   Float_t         genmatched2_e;
   Bool_t          hasgenmatch1;
   Bool_t          hasgenmatch2;
   Float_t         dau2_iso;
   Int_t           dau2_MVAiso;
   Int_t           dau2_MVAisoNew;
   Int_t           dau2_MVAisoNewdR0p3;
   Int_t           dau2_CUTiso;
   Int_t           dau2_antiele;
   Int_t           dau2_antimu;
   Int_t           dau2_deepTauVsJet;
   Int_t           dau2_deepTauVsEle;
   Int_t           dau2_deepTauVsMu;
   Float_t         dau2_photonPtSumOutsideSignalCone;
   Bool_t          dau2_byLooseCombinedIsolationDeltaBetaCorr3Hits;
   Bool_t          dau2_byMediumCombinedIsolationDeltaBetaCorr3Hits;
   Bool_t          dau2_byTightCombinedIsolationDeltaBetaCorr3Hits;
   Float_t         dau2_pt;
   Float_t         dau2_pt_tauup;
   Float_t         dau2_pt_taudown;
   Float_t         dau2_pt_eleup;
   Float_t         dau2_pt_eledown;
   Float_t         dau2_eta;
   Float_t         dau2_phi;
   Float_t         dau2_e;
   Float_t         dau2_flav;
   Float_t         dau2_dxy;
   Float_t         dau2_dz;
   Int_t           dau2_decayMode;
   Float_t         bjet1_pt;
   Float_t         bjet1_eta;
   Float_t         bjet1_phi;
   Float_t         bjet1_e;
   Float_t         bjet1_bID;
   Float_t         bjet1_bID_deepCSV;
   Float_t         bjet1_bID_deepFlavor;
   Float_t         bjet1_bMVAID;
   Int_t           bjet1_flav;
   Float_t         bjet1_pt_raw;
   Float_t         bjet1_pt_raw_jetup;
   Float_t         bjet1_pt_raw_jetdown;
   Bool_t          bjet1_hasgenjet;
   Float_t         bjet1_JER;
   Bool_t          bjet1_gen_matched;
   Float_t         bjet2_pt;
   Float_t         bjet2_eta;
   Float_t         bjet2_phi;
   Float_t         bjet2_e;
   Float_t         bjet2_bID;
   Float_t         bjet2_bID_deepCSV;
   Float_t         bjet2_bID_deepFlavor;
   Float_t         bjet2_bMVAID;
   Int_t           bjet2_flav;
   Float_t         bjet2_pt_raw;
   Float_t         bjet2_pt_raw_jetup;
   Float_t         bjet2_pt_raw_jetdown;
   Bool_t          bjet2_hasgenjet;
   Float_t         bjet2_JER;
   Bool_t          bjet2_gen_matched;
   Float_t         bjets_bID;
   Float_t         bjets_bID_deepCSV;
   Float_t         bjets_bID_deepFlavor;
   Bool_t          bjets_gen_matched;
   Int_t           nfatjets;
   Float_t         fatjet_pt;
   Float_t         fatjet_eta;
   Float_t         fatjet_phi;
   Float_t         fatjet_e;
   Float_t         fatjet_bID;
   Float_t         fatjet_bID_deepCSV;
   Float_t         fatjet_bID_deepFlavor;
   Float_t         fatjet_filteredMass;
   Float_t         fatjet_prunedMass;
   Float_t         fatjet_trimmedMass;
   Float_t         fatjet_softdropMass;
   Float_t         fatjet_tau1;
   Float_t         fatjet_tau2;
   Float_t         fatjet_tau3;
   Int_t           fatjet_nsubjets;
   Float_t         dR_subj1_subj2;
   Float_t         subjetjet1_pt;
   Float_t         subjetjet1_eta;
   Float_t         subjetjet1_phi;
   Float_t         subjetjet1_e;
   Float_t         subjetjet1_bID;
   Float_t         subjetjet1_bID_deepCSV;
   Float_t         subjetjet1_bID_deepFlavor;
   Float_t         subjetjet2_pt;
   Float_t         subjetjet2_eta;
   Float_t         subjetjet2_phi;
   Float_t         subjetjet2_e;
   Float_t         subjetjet2_bID;
   Float_t         subjetjet2_bID_deepCSV;
   Float_t         subjetjet2_bID_deepFlavor;
   Float_t         genjet1_pt;
   Float_t         genjet1_eta;
   Float_t         genjet1_phi;
   Float_t         genjet1_e;
   Float_t         genjet2_pt;
   Float_t         genjet2_eta;
   Float_t         genjet2_phi;
   Float_t         genjet2_e;
   Float_t         tauH_pt;
   Float_t         tauH_eta;
   Float_t         tauH_phi;
   Float_t         tauH_e;
   Float_t         tauH_mass;
   Float_t         tauH_SVFIT_mass;
   Float_t         tauH_SVFIT_pt;
   Float_t         tauH_SVFIT_eta;
   Float_t         tauH_SVFIT_phi;
   Float_t         tauH_SVFIT_METphi;
   Float_t         tauH_SVFIT_METrho;
   Float_t         tauH_SVFIT_mass_up;
   Float_t         tauH_SVFIT_mass_down;
   Float_t         tauH_SVFIT_mass_METup;
   Float_t         tauH_SVFIT_mass_METdown;
   Float_t         bH_pt;
   Float_t         bH_eta;
   Float_t         bH_phi;
   Float_t         bH_e;
   Float_t         bH_mass;
   Float_t         HHsvfit_pt;
   Float_t         HHsvfit_eta;
   Float_t         HHsvfit_phi;
   Float_t         HHsvfit_e;
   Float_t         HHsvfit_mass;
   Float_t         HH_pt;
   Float_t         HH_eta;
   Float_t         HH_phi;
   Float_t         HH_e;
   Float_t         HH_mass;
   Float_t         HH_mass_raw;
   Float_t         HH_mass_raw_tauup;
   Float_t         HH_mass_raw_taudown;
   Float_t         HH_mass_raw_eleup;
   Float_t         HH_mass_raw_eledown;
   Float_t         HHKin_mass;
   Float_t         HHKin_chi2;
   Float_t         HH_deltaPhi;
   Float_t         HH_deltaR;
   Float_t         HH_deltaEta;
   Float_t         HHsvfit_deltaPhi;
   Float_t         tauHMet_deltaPhi;
   Float_t         tauHsvfitMet_deltaPhi;
   Float_t         bHMet_deltaPhi;
   Float_t         ditau_deltaPhi;
   Float_t         ditau_deltaEta;
   Float_t         dib_deltaPhi;
   Float_t         dib_deltaEta;
   Float_t         ditau_deltaR;
   Float_t         dib_deltaR;
   Float_t         ditau_deltaR_per_tauHsvfitpt;
   Float_t         dib_deltaR_per_bHpt;
   Float_t         btau_deltaRmin;
   Float_t         btau_deltaRmax;
   Float_t         dau1MET_deltaphi;
   Float_t         dau2MET_deltaphi;
   Float_t         HT20;
   Float_t         HT50;
   Float_t         HT20Full;
   Float_t         jet20centrality;
   vector<float>   *jets_pt;
   vector<float>   *jets_eta;
   vector<float>   *jets_phi;
   vector<float>   *jets_e;
   vector<float>   *jets_btag;
   vector<float>   *jets_btag_deepCSV;
   vector<float>   *jets_btag_deepFlavor;
   vector<int>     *jets_flav;
   vector<int>     *jets_isH;
   vector<bool>    *jets_hasgenjet;
   Int_t           njets;
   Int_t           addjets;
   Int_t           njets20;
   Int_t           njets50;
   Int_t           nbjets20;
   Int_t           nbjets50;
   Int_t           nbjetscand;
   Int_t           njetsBHadFlav;
   Int_t           njetsCHadFlav;
   vector<float>   *jets_jecUnc;
   Float_t         dau1_jecUnc;
   Float_t         dau2_jecUnc;
   Float_t         bjet1_jecUnc;
   Float_t         bjet2_jecUnc;
   vector<float>   *leps_pt;
   vector<float>   *leps_eta;
   vector<float>   *leps_phi;
   vector<float>   *leps_e;
   vector<int>     *leps_flav;
   Int_t           nleps;
   Float_t         HHkinsvfit_bHmass;
   Float_t         HHkinsvfit_pt;
   Float_t         HHkinsvfit_eta;
   Float_t         HHkinsvfit_phi;
   Float_t         HHkinsvfit_e;
   Float_t         HHkinsvfit_m;
   Float_t         MT2;
   Float_t         MT2_tauup;
   Float_t         MT2_taudown;
   Float_t         MT2_jetup;
   Float_t         MT2_jetdown;
   Float_t         MT2_eleup;
   Float_t         MT2_eledown;
   Float_t         bH_mass_raw;
   Float_t         bH_mass_raw_jetup;
   Float_t         bH_mass_raw_jetdown;
   Float_t         HHKin_mass_raw;
   Float_t         HHKin_mass_raw_tauup;
   Float_t         HHKin_mass_raw_taudown;
   Float_t         HHKin_mass_raw_jetup;
   Float_t         HHKin_mass_raw_jetdown;
   Float_t         HHKin_mass_raw_eleup;
   Float_t         HHKin_mass_raw_eledown;
   Float_t         HHKin_mass_raw_chi2;
   Int_t           HHKin_mass_raw_convergence;
   Float_t         HHKin_mass_raw_prob;
   Float_t         HHKin_mass_raw_copy;
   Float_t         lheht;
   Float_t         topReweight;
   Float_t         VBFjet1_pt;
   Float_t         VBFjet1_eta;
   Float_t         VBFjet1_phi;
   Float_t         VBFjet1_e;
   Float_t         VBFjet1_btag;
   Float_t         VBFjet1_btag_deepCSV;
   Float_t         VBFjet1_btag_deepFlavor;
   Int_t           VBFjet1_flav;
   Bool_t          VBFjet1_hasgenjet;
   Float_t         VBFgenjet1_pt;
   Float_t         VBFgenjet1_eta;
   Float_t         VBFgenjet1_phi;
   Float_t         VBFgenjet1_e;
   Float_t         VBFjet2_pt;
   Float_t         VBFjet2_eta;
   Float_t         VBFjet2_phi;
   Float_t         VBFjet2_e;
   Float_t         VBFjet2_btag;
   Float_t         VBFjet2_btag_deepCSV;
   Float_t         VBFjet2_btag_deepFlavor;
   Int_t           VBFjet2_flav;
   Bool_t          VBFjet2_hasgenjet;
   Float_t         VBFgenjet2_pt;
   Float_t         VBFgenjet2_eta;
   Float_t         VBFgenjet2_phi;
   Float_t         VBFgenjet2_e;
   Float_t         VBFjj_mass_log;
   Float_t         jj_mass_log;
   Float_t         VBFjj_mass;
   Float_t         VBFjj_deltaEta;
   Float_t         VBFjj_HT;
   Float_t         jet3_pt;
   Float_t         jet3_eta;
   Float_t         jet3_phi;
   Float_t         jet3_e;
   Float_t         jet3_btag;
   Float_t         jet3_btag_deepCSV;
   Float_t         jet3_btag_deepFlavor;
   Int_t           jet3_flav;
   Bool_t          jet3_hasgenjet;
   Float_t         genjet3_pt;
   Float_t         genjet3_eta;
   Float_t         genjet3_phi;
   Float_t         genjet3_e;
   Float_t         jet4_pt;
   Float_t         jet4_eta;
   Float_t         jet4_phi;
   Float_t         jet4_e;
   Float_t         jet4_btag;
   Float_t         jet4_btag_deepCSV;
   Float_t         jet4_btag_deepFlavor;
   Int_t           jet4_flav;
   Bool_t          jet4_hasgenjet;
   Float_t         genjet4_pt;
   Float_t         genjet4_eta;
   Float_t         genjet4_phi;
   Float_t         genjet4_e;
   Float_t         jj_mass;
   Float_t         jj_deltaEta;
   Float_t         jj_HT;
   Float_t         dau1_z;
   Float_t         dau2_z;
   Float_t         bjet1_z;
   Float_t         bjet2_z;
   Float_t         tauH_z;
   Float_t         bH_z;
   Float_t         HH_z;
   Float_t         HH_zV;
   Float_t         HH_A;
   Float_t         jet5_pt;
   Float_t         jet5_eta;
   Float_t         jet5_phi;
   Float_t         jet5_e;
   Float_t         jet5_btag;
   Float_t         jet5_btag_deepCSV;
   Float_t         jet5_btag_deepFlavor;
   Int_t           jet5_flav;
   Bool_t          jet5_hasgenjet;
   Float_t         jet5_z;
   Float_t         jet5_VBF_pt;
   Float_t         jet5_VBF_eta;
   Float_t         jet5_VBF_phi;
   Float_t         jet5_VBF_e;
   Float_t         jet5_VBF_btag;
   Float_t         jet5_VBF_btag_deepCSV;
   Float_t         jet5_VBF_btag_deepFlavor;
   Float_t         jet5_VBF_flav;
   Bool_t          jet5_VBF_hasgenjet;
   Float_t         jet5_VBF_z;
   Float_t         genjet5_VBF_pt;
   Float_t         genjet5_VBF_eta;
   Float_t         genjet5_VBF_phi;
   Float_t         genjet5_VBF_e;
   Float_t         top_Wc_bclose_mass;
   Float_t         top_Wc_bcentral_mass;
   Float_t         top_Wc_bforward_mass;
   Float_t         top_Wf_bclose_mass;
   Float_t         top_Wf_bcentral_mass;
   Float_t         top_Wf_bforward_mass;
   Float_t         top_Wmass_bclose_mass;
   Float_t         top_Wjj_b_mass;
   Float_t         top_Wjj_bclose_mass;
   Float_t         BDT_channel;
   Float_t         tauH_MET_pt;
   Float_t         dau2_MET_deltaEta;
   Float_t         bH_MET_deltaEta;
   Float_t         bH_MET_deltaR;
   Float_t         bH_tauH_MET_deltaR;
   Float_t         ditau_deltaR_per_tauH_MET_pt;
   Float_t         p_zeta;
   Float_t         p_zeta_visible;
   Float_t         mT_tauH_MET;
   Float_t         mT_tauH_SVFIT_MET;
   Float_t         mT_total;
   Float_t         BDT_ditau_deltaPhi;
   Float_t         BDT_dib_abs_deltaPhi;
   Float_t         BDT_dib_deltaPhi;
   Float_t         BDT_dau1MET_deltaPhi;
   Float_t         BDT_tauHsvfitMet_abs_deltaPhi;
   Float_t         BDT_tauHsvfitMet_deltaPhi;
   Float_t         BDT_bHMet_deltaPhi;
   Float_t         BDT_HHsvfit_abs_deltaPhi;
   Float_t         BDT_HT20;
   Float_t         BDT_topPairMasses;
   Float_t         BDT_MX;
   Float_t         BDT_bH_tauH_MET_InvMass;
   Float_t         BDT_bH_tauH_SVFIT_InvMass;
   Float_t         BDT_bH_tauH_InvMass;
   Float_t         BDT_total_CalcPhi;
   Float_t         BDT_ditau_CalcPhi;
   Float_t         BDT_dib_CalcPhi;
   Float_t         BDT_MET_tauH_SVFIT_cosTheta;
   Float_t         BDT_MET_bH_cosTheta;
   Float_t         BDT_b1_bH_cosTheta;
   Float_t         BDT_tauH_SVFIT_reson_cosTheta;
   Float_t         VBFjj_dEtaSign;
   Float_t         VBFjet2_PUjetID;
   Float_t         bH_VBF1_deltaEta;
   Float_t         dib_dEtaSign;
   Int_t           isTau1real;
   Int_t           isTau2real;
   Int_t           nRealTaus;
   Float_t         BDToutSM_kl_1;
   Float_t         DNN_VBFvsGGF_MuTau;   
   Float_t         DNN_VBFvsGGF_ETau;   
   Float_t         DNN_VBFvsGGF_TauTauTight;   
   Float_t         DNN_VBFvsGGF_TauTauLoose;   

   // List of branches
   TBranch        *b_MC_weight;   //!
   TBranch        *b_totalWeight;   //!
   TBranch        *b_prescaleWeight;   //!
   TBranch        *b_L1pref_weight;   //!
   TBranch        *b_PUReweight;   //!
   TBranch        *b_bTagweightL;   //!
   TBranch        *b_bTagweightM;   //!
   TBranch        *b_bTagweightT;   //!
   TBranch        *b_TTtopPtreweight;   //!
   TBranch        *b_TTtopPtreweight_up;   //!
   TBranch        *b_TTtopPtreweight_down;   //!
   TBranch        *b_trigSF;   //!
   TBranch        *b_trigSF_single;   //!
   TBranch        *b_trigSF_cross;   //!
   TBranch        *b_VBFtrigSF;   //!
   TBranch        *b_FakeRateSF;   //!
   TBranch        *b_jetFakeSF;   //!
   TBranch        *b_IdAndIsoSF_MVA;   //!
   TBranch        *b_IdAndIsoSF_deep;   //!
   TBranch        *b_IdAndIsoAndFakeSF_MVA;   //!
   TBranch        *b_IdAndIsoAndFakeSF_deep;   //!
   TBranch        *b_DYscale_LL;   //!
   TBranch        *b_DYscale_MM;   //!
   TBranch        *b_DYscale_LL_NLO;   //!
   TBranch        *b_DYscale_MM_NLO;   //!
   TBranch        *b_DYLOtoNLOreweight;   //!
   TBranch        *b_DYptZweight;   //!
   TBranch        *b_DY_NPVweight;   //!
   TBranch        *b_nBhadrons;   //!
   TBranch        *b_lheNOutPartons;   //!
   TBranch        *b_lheNOutB;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_isBoosted;   //!
   TBranch        *b_isVBF;   //!
   TBranch        *b_isVBFtrigger;   //!
   TBranch        *b_genDecMode1;   //!
   TBranch        *b_genDecMode2;   //!
   TBranch        *b_m_genMHH;   //!
   TBranch        *b_m_genCosth;   //!
   TBranch        *b_npv;   //!
   TBranch        *b_npu;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_triggerbit;   //!
   TBranch        *b_pass_triggerbit;   //!
   TBranch        *b_cross_monitoring_trig;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_pairType;   //!
   TBranch        *b_isMC;   //!
   TBranch        *b_isOS;   //!
   TBranch        *b_met_phi;   //!
   TBranch        *b_met_et;   //!
   TBranch        *b_met_phi_jetup;   //!
   TBranch        *b_met_et_jetup;   //!
   TBranch        *b_met_phi_jetdown;   //!
   TBranch        *b_met_et_jetdown;   //!
   TBranch        *b_met_phi_tauup;   //!
   TBranch        *b_met_et_tauup;   //!
   TBranch        *b_met_phi_taudown;   //!
   TBranch        *b_met_et_taudown;   //!
   TBranch        *b_met_phi_eleup;   //!
   TBranch        *b_met_et_eleup;   //!
   TBranch        *b_met_phi_eledown;   //!
   TBranch        *b_met_et_eledown;   //!
   TBranch        *b_met_et_corr;   //!
   TBranch        *b_met_cov00;   //!
   TBranch        *b_met_cov01;   //!
   TBranch        *b_met_cov10;   //!
   TBranch        *b_met_cov11;   //!
   TBranch        *b_met_er_phi;   //!
   TBranch        *b_met_er_et;   //!
   TBranch        *b_mT1;   //!
   TBranch        *b_mT2;   //!
   TBranch        *b_dau1_iso;   //!
   TBranch        *b_dau1_MVAiso;   //!
   TBranch        *b_dau1_MVAisoNew;   //!
   TBranch        *b_dau1_MVAisoNewdR0p3;   //!
   TBranch        *b_dau1_CUTiso;   //!
   TBranch        *b_dau1_antiele;   //!
   TBranch        *b_dau1_antimu;   //!
   TBranch        *b_dau1_deepTauVsJet;   //!
   TBranch        *b_dau1_deepTauVsEle;   //!
   TBranch        *b_dau1_deepTauVsMu;   //!
   TBranch        *b_dau1_photonPtSumOutsideSignalCone;   //!
   TBranch        *b_dau1_byLooseCombinedIsolationDeltaBetaCorr3Hits;   //!
   TBranch        *b_dau1_byMediumCombinedIsolationDeltaBetaCorr3Hits;   //!
   TBranch        *b_dau1_byTightCombinedIsolationDeltaBetaCorr3Hits;   //!
   TBranch        *b_dau1_pt;   //!
   TBranch        *b_dau1_pt_tauup;   //!
   TBranch        *b_dau1_pt_taudown;   //!
   TBranch        *b_dau1_pt_eleup;   //!
   TBranch        *b_dau1_pt_eledown;   //!
   TBranch        *b_dau1_eta;   //!
   TBranch        *b_dau1_phi;   //!
   TBranch        *b_dau1_e;   //!
   TBranch        *b_dau1_flav;   //!
   TBranch        *b_dau1_dxy;   //!
   TBranch        *b_dau1_dz;   //!
   TBranch        *b_dau1_decayMode;   //!
   TBranch        *b_genmatched1_pt;   //!
   TBranch        *b_genmatched1_eta;   //!
   TBranch        *b_genmatched1_phi;   //!
   TBranch        *b_genmatched1_e;   //!
   TBranch        *b_genmatched2_pt;   //!
   TBranch        *b_genmatched2_eta;   //!
   TBranch        *b_genmatched2_phi;   //!
   TBranch        *b_genmatched2_e;   //!
   TBranch        *b_hasgenmatch1;   //!
   TBranch        *b_hasgenmatch2;   //!
   TBranch        *b_dau2_iso;   //!
   TBranch        *b_dau2_MVAiso;   //!
   TBranch        *b_dau2_MVAisoNew;   //!
   TBranch        *b_dau2_MVAisoNewdR0p3;   //!
   TBranch        *b_dau2_CUTiso;   //!
   TBranch        *b_dau2_antiele;   //!
   TBranch        *b_dau2_antimu;   //!
   TBranch        *b_dau2_deepTauVsJet;   //!
   TBranch        *b_dau2_deepTauVsEle;   //!
   TBranch        *b_dau2_deepTauVsMu;   //!
   TBranch        *b_dau2_photonPtSumOutsideSignalCone;   //!
   TBranch        *b_dau2_byLooseCombinedIsolationDeltaBetaCorr3Hits;   //!
   TBranch        *b_dau2_byMediumCombinedIsolationDeltaBetaCorr3Hits;   //!
   TBranch        *b_dau2_byTightCombinedIsolationDeltaBetaCorr3Hits;   //!
   TBranch        *b_dau2_pt;   //!
   TBranch        *b_dau2_pt_tauup;   //!
   TBranch        *b_dau2_pt_taudown;   //!
   TBranch        *b_dau2_pt_eleup;   //!
   TBranch        *b_dau2_pt_eledown;   //!
   TBranch        *b_dau2_eta;   //!
   TBranch        *b_dau2_phi;   //!
   TBranch        *b_dau2_e;   //!
   TBranch        *b_dau2_flav;   //!
   TBranch        *b_dau2_dxy;   //!
   TBranch        *b_dau2_dz;   //!
   TBranch        *b_dau2_decayMode;   //!
   TBranch        *b_bjet1_pt;   //!
   TBranch        *b_bjet1_eta;   //!
   TBranch        *b_bjet1_phi;   //!
   TBranch        *b_bjet1_e;   //!
   TBranch        *b_bjet1_bID;   //!
   TBranch        *b_bjet1_bID_deepCSV;   //!
   TBranch        *b_bjet1_bID_deepFlavor;   //!
   TBranch        *b_bjet1_bMVAID;   //!
   TBranch        *b_bjet1_flav;   //!
   TBranch        *b_bjet1_pt_raw;   //!
   TBranch        *b_bjet1_pt_raw_jetup;   //!
   TBranch        *b_bjet1_pt_raw_jetdown;   //!
   TBranch        *b_bjet1_hasgenjet;   //!
   TBranch        *b_bjet1_JER;   //!
   TBranch        *b_bjet1_gen_matched;   //!
   TBranch        *b_bjet2_pt;   //!
   TBranch        *b_bjet2_eta;   //!
   TBranch        *b_bjet2_phi;   //!
   TBranch        *b_bjet2_e;   //!
   TBranch        *b_bjet2m_bID;   //!
   TBranch        *b_bjet2_bID_deepCSV;   //!
   TBranch        *b_bjet2_bID_deepFlavor;   //!
   TBranch        *b_bjet2m_bMVAID;   //!
   TBranch        *b_bjet2_flav;   //!
   TBranch        *b_bjet2_pt_raw;   //!
   TBranch        *b_bjet2_pt_raw_jetup;   //!
   TBranch        *b_bjet2_pt_raw_jetdown;   //!
   TBranch        *b_bjet2_hasgenjet;   //!
   TBranch        *b_bjet2_JER;   //!
   TBranch        *b_bjet2_gen_matched;   //!
   TBranch        *b_bjets_bID;   //!
   TBranch        *b_bjets_bID_deepCSV;   //!
   TBranch        *b_bjets_bID_deepFlavor;   //!
   TBranch        *b_bjets_gen_matched;   //!
   TBranch        *b_nfatjets;   //!
   TBranch        *b_fatjet_pt;   //!
   TBranch        *b_fatjet_eta;   //!
   TBranch        *b_fatjet_phi;   //!
   TBranch        *b_fatjet_e;   //!
   TBranch        *b_fatjet_bID;   //!
   TBranch        *b_fatjet_bID_deepCSV;   //!
   TBranch        *b_fatjet_bID_deepFlavor;   //!
   TBranch        *b_fatjet_filteredMass;   //!
   TBranch        *b_fatjet_prunedMass;   //!
   TBranch        *b_fatjet_trimmedMass;   //!
   TBranch        *b_fatjet_softdropMass;   //!
   TBranch        *b_fatjet_tau1;   //!
   TBranch        *b_fatjet_tau2;   //!
   TBranch        *b_fatjet_tau3;   //!
   TBranch        *b_fatjet_nsubjets;   //!
   TBranch        *b_dR_subj1_subj2;   //!
   TBranch        *b_subjetjet1_pt;   //!
   TBranch        *b_subjetjet1_eta;   //!
   TBranch        *b_subjetjet1_phi;   //!
   TBranch        *b_subjetjet1_e;   //!
   TBranch        *b_subjetjet1_bID;   //!
   TBranch        *b_subjetjet1_bID_deepCSV;   //!
   TBranch        *b_subjetjet1_bID_deepFlavor;   //!
   TBranch        *b_subjetjet2_pt;   //!
   TBranch        *b_subjetjet2_eta;   //!
   TBranch        *b_subjetjet2_phi;   //!
   TBranch        *b_subjetjet2_e;   //!
   TBranch        *b_subjetjet2_bID;   //!
   TBranch        *b_subjetjet2_bID_deepCSV;   //!
   TBranch        *b_subjetjet2_bID_deepFlavor;   //!
   TBranch        *b_genjet1_pt;   //!
   TBranch        *b_genjet1_eta;   //!
   TBranch        *b_genjet1_phi;   //!
   TBranch        *b_genjet1_e;   //!
   TBranch        *b_genjet2_pt;   //!
   TBranch        *b_genjet2_eta;   //!
   TBranch        *b_genjet2_phi;   //!
   TBranch        *b_genjet2_e;   //!
   TBranch        *b_tauH_pt;   //!
   TBranch        *b_tauH_eta;   //!
   TBranch        *b_tauH_phi;   //!
   TBranch        *b_tauH_e;   //!
   TBranch        *b_tauH_mass;   //!
   TBranch        *b_tauH_SVFIT_mass;   //!
   TBranch        *b_tauH_SVFIT_pt;   //!
   TBranch        *b_tauH_SVFIT_eta;   //!
   TBranch        *b_tauH_SVFIT_phi;   //!
   TBranch        *b_tauH_SVFIT_METphi;   //!
   TBranch        *b_tauH_SVFIT_METrho;   //!
   TBranch        *b_tauH_SVFIT_mass_up;   //!
   TBranch        *b_tauH_SVFIT_mass_down;   //!
   TBranch        *b_tauH_SVFIT_mass_METup;   //!
   TBranch        *b_tauH_SVFIT_mass_METdown;   //!
   TBranch        *b_bH_pt;   //!
   TBranch        *b_bH_eta;   //!
   TBranch        *b_bH_phi;   //!
   TBranch        *b_bH_e;   //!
   TBranch        *b_bH_mass;   //!
   TBranch        *b_HHsvfit_pt;   //!
   TBranch        *b_HHsvfit_eta;   //!
   TBranch        *b_HHsvfit_phi;   //!
   TBranch        *b_HHsvfit_e;   //!
   TBranch        *b_HHsvfit_mass;   //!
   TBranch        *b_HH_pt;   //!
   TBranch        *b_HH_eta;   //!
   TBranch        *b_HH_phi;   //!
   TBranch        *b_HH_e;   //!
   TBranch        *b_HH_mass;   //!
   TBranch        *b_HH_mass_raw;   //!
   TBranch        *b_HH_mass_raw_tauup;   //!
   TBranch        *b_HH_mass_raw_taudown;   //!
   TBranch        *b_HH_mass_raw_eleup;   //!
   TBranch        *b_HH_mass_raw_eledown;   //!
   TBranch        *b_HHKin_mass;   //!
   TBranch        *b_HHKin_chi2;   //!
   TBranch        *b_HH_deltaPhi;   //!
   TBranch        *b_HH_deltaR;   //!
   TBranch        *b_HH_deltaEta;   //!
   TBranch        *b_HHsvfit_deltaPhi;   //!
   TBranch        *b_tauHMet_deltaPhi;   //!
   TBranch        *b_tauHsvfitMet_deltaPhi;   //!
   TBranch        *b_bHMet_deltaPhi;   //!
   TBranch        *b_ditau_deltaPhi;   //!
   TBranch        *b_ditau_deltaEta;   //!
   TBranch        *b_dib_deltaPhi;   //!
   TBranch        *b_dib_deltaEta;   //!
   TBranch        *b_ditau_deltaR;   //!
   TBranch        *b_dib_deltaR;   //!
   TBranch        *b_ditau_deltaR_per_tauHsvfitpt;   //!
   TBranch        *b_dib_deltaR_per_bHpt;   //!
   TBranch        *b_btau_deltaRmin;   //!
   TBranch        *b_btau_deltaRmax;   //!
   TBranch        *b_dau1MET_deltaphi;   //!
   TBranch        *b_dau2MET_deltaphi;   //!
   TBranch        *b_HT20;   //!
   TBranch        *b_HT50;   //!
   TBranch        *b_HT20Full;   //!
   TBranch        *b_jet20centrality;   //!
   TBranch        *b_jets_pt;   //!
   TBranch        *b_jets_eta;   //!
   TBranch        *b_jets_phi;   //!
   TBranch        *b_jets_e;   //!
   TBranch        *b_jets_btag;   //!
   TBranch        *b_jets_btag_deepCSV;   //!
   TBranch        *b_jets_btag_deepFlavor;   //!
   TBranch        *b_jets_flav;   //!
   TBranch        *b_jets_isH;   //!
   TBranch        *b_jets_hasgenjet;   //!
   TBranch        *b_njets;   //!
   TBranch        *b_addjets;   //!
   TBranch        *b_njets20;   //!
   TBranch        *b_njets50;   //!
   TBranch        *b_nbjets20;   //!
   TBranch        *b_nbjets50;   //!
   TBranch        *b_nbjetscand;   //!
   TBranch        *b_njetsBHadFlav;   //!
   TBranch        *b_njetsCHadFlav;   //!
   TBranch        *b_jets_jecUnc;   //!
   TBranch        *b_dau1_jecUnc;   //!
   TBranch        *b_dau2_jecUnc;   //!
   TBranch        *b_bjet1_jecUnc;   //!
   TBranch        *b_bjet2_jecUnc;   //!
   TBranch        *b_leps_pt;   //!
   TBranch        *b_leps_eta;   //!
   TBranch        *b_leps_phi;   //!
   TBranch        *b_leps_e;   //!
   TBranch        *b_leps_flav;   //!
   TBranch        *b_nleps;   //!
   TBranch        *b_HHkinsvfit_bHmass;   //!
   TBranch        *b_HHkinsvfit_pt;   //!
   TBranch        *b_HHkinsvfit_eta;   //!
   TBranch        *b_HHkinsvfit_phi;   //!
   TBranch        *b_HHkinsvfit_e;   //!
   TBranch        *b_HHkinsvfit_m;   //!
   TBranch        *b_MT2;   //!
   TBranch        *b_MT2_tauup;   //!
   TBranch        *b_MT2_taudown;   //!
   TBranch        *b_MT2_jetup;   //!
   TBranch        *b_MT2_jetdown;   //!
   TBranch        *b_MT2_eleup;   //!
   TBranch        *b_MT2_eledown;   //!
   TBranch        *b_bH_mass_raw;   //!
   TBranch        *b_bH_mass_raw_jetup;   //!
   TBranch        *b_bH_mass_raw_jetdown;   //!
   TBranch        *b_HHKin_mass_raw;   //!
   TBranch        *b_HHKin_mass_raw_tauup;   //!
   TBranch        *b_HHKin_mass_raw_taudown;   //!
   TBranch        *b_HHKin_mass_raw_jetup;   //!
   TBranch        *b_HHKin_mass_raw_jetdown;   //!
   TBranch        *b_HHKin_mass_raw_eleup;   //!
   TBranch        *b_HHKin_mass_raw_eledown;   //!
   TBranch        *b_HHKin_mass_raw_chi2;   //!
   TBranch        *b_HHKin_mass_raw_convergence;   //!
   TBranch        *b_HHKin_mass_raw_prob;   //!
   TBranch        *b_HHKin_mass_raw_copy;   //!
   TBranch        *b_lheht;   //!
   TBranch        *b_topReweight;   //!
   TBranch        *b_VBFjet1_pt;   //!
   TBranch        *b_VBFjet1_eta;   //!
   TBranch        *b_VBFjet1_phi;   //!
   TBranch        *b_VBFjet1_e;   //!
   TBranch        *b_VBFjet1_btag;   //!
   TBranch        *b_VBFjet1_btag_deepCSV;   //!
   TBranch        *b_VBFjet1_btag_deepFlavor;   //!
   TBranch        *b_VBFjet1_flav;   //!
   TBranch        *b_VBFjet1_hasgenjet;   //!
   TBranch        *b_VBFgenjet1_pt;   //!
   TBranch        *b_VBFgenjet1_eta;   //!
   TBranch        *b_VBFgenjet1_phi;   //!
   TBranch        *b_VBFgenjet1_e;   //!
   TBranch        *b_VBFjet2_pt;   //!
   TBranch        *b_VBFjet2_eta;   //!
   TBranch        *b_VBFjet2_phi;   //!
   TBranch        *b_VBFjet2_e;   //!
   TBranch        *b_VBFjet2_btag;   //!
   TBranch        *b_VBFjet2_btag_deepCSV;   //!
   TBranch        *b_VBFjet2_btag_deepFlavor;   //!
   TBranch        *b_VBFjet2_flav;   //!
   TBranch        *b_VBFjet2_hasgenjet;   //!
   TBranch        *b_VBFgenjet2_pt;   //!
   TBranch        *b_VBFgenjet2_eta;   //!
   TBranch        *b_VBFgenjet2_phi;   //!
   TBranch        *b_VBFgenjet2_e;   //!
   TBranch        *b_VBFjj_mass_log;   //!
   TBranch        *b_jj_mass_log;   //!
   TBranch        *b_VBFjj_mass;   //!
   TBranch        *b_VBFjj_deltaEta;   //!
   TBranch        *b_VBFjj_HT;   //!
   TBranch        *b_jet3_pt;   //!
   TBranch        *b_jet3_eta;   //!
   TBranch        *b_jet3_phi;   //!
   TBranch        *b_jet3_e;   //!
   TBranch        *b_jet3_btag;   //!
   TBranch        *b_jet3_btag_deepCSV;   //!
   TBranch        *b_jet3_btag_deepFlavor;   //!
   TBranch        *b_jet3_flav;   //!
   TBranch        *b_jet3_hasgenjet;   //!
   TBranch        *b_genjet3_pt;   //!
   TBranch        *b_genjet3_eta;   //!
   TBranch        *b_genjet3_phi;   //!
   TBranch        *b_genjet3_e;   //!
   TBranch        *b_jet4_pt;   //!
   TBranch        *b_jet4_eta;   //!
   TBranch        *b_jet4_phi;   //!
   TBranch        *b_jet4_e;   //!
   TBranch        *b_jet4_btag;   //!
   TBranch        *b_jet4_btag_deepCSV;   //!
   TBranch        *b_jet4_btag_deepFlavor;   //!
   TBranch        *b_jet4_flav;   //!
   TBranch        *b_jet4_hasgenjet;   //!
   TBranch        *b_genjet4_pt;   //!
   TBranch        *b_genjet4_eta;   //!
   TBranch        *b_genjet4_phi;   //!
   TBranch        *b_genjet4_e;   //!
   TBranch        *b_jj_mass;   //!
   TBranch        *b_jj_deltaEta;   //!
   TBranch        *b_jj_HT;   //!
   TBranch        *b_dau1_z;   //!
   TBranch        *b_dau2_z;   //!
   TBranch        *b_bjet1_z;   //!
   TBranch        *b_bjet2_z;   //!
   TBranch        *b_tauH_z;   //!
   TBranch        *b_bH_z;   //!
   TBranch        *b_HH_z;   //!
   TBranch        *b_HH_zV;   //!
   TBranch        *b_HH_A;   //!
   TBranch        *b_jet5_pt;   //!
   TBranch        *b_jet5_eta;   //!
   TBranch        *b_jet5_phi;   //!
   TBranch        *b_jet5_e;   //!
   TBranch        *b_jet5_btag;   //!
   TBranch        *b_jet5_btag_deepCSV;   //!
   TBranch        *b_jet5_btag_deepFlavor;   //!
   TBranch        *b_jet5_flav;   //!
   TBranch        *b_jet5_hasgenjet;   //!
   TBranch        *b_jet5_z;   //!
   TBranch        *b_jet5_VBF_pt;   //!
   TBranch        *b_jet5_VBF_eta;   //!
   TBranch        *b_jet5_VBF_phi;   //!
   TBranch        *b_jet5_VBF_e;   //!
   TBranch        *b_jet5_VBF_btag;   //!
   TBranch        *b_jet5_VBF_btag_deepCSV;   //!
   TBranch        *b_jet5_VBF_btag_deepFlavor;   //!
   TBranch        *b_jet5_VBF_flav;   //!
   TBranch        *b_jet5_VBF_hasgenjet;   //!
   TBranch        *b_jet5_VBF_z;   //!
   TBranch        *b_genjet5_VBF_pt;   //!
   TBranch        *b_genjet5_VBF_eta;   //!
   TBranch        *b_genjet5_VBF_phi;   //!
   TBranch        *b_genjet5_VBF_e;   //!
   TBranch        *b_top_Wc_bclose_mass;   //!
   TBranch        *b_top_Wc_bcentral_mass;   //!
   TBranch        *b_top_Wc_bforward_mass;   //!
   TBranch        *b_top_Wf_bclose_mass;   //!
   TBranch        *b_top_Wf_bcentral_mass;   //!
   TBranch        *b_top_Wf_bforward_mass;   //!
   TBranch        *b_top_Wmass_bclose_mass;   //!
   TBranch        *b_top_Wjj_b_mass;   //!
   TBranch        *b_top_Wjj_bclose_mass;   //!
   TBranch        *b_BDT_channel;   //!
   TBranch        *b_tauH_MET_pt;   //!
   TBranch        *b_dau2_MET_deltaEta;   //!
   TBranch        *b_bH_MET_deltaEta;   //!
   TBranch        *b_bH_MET_deltaR;   //!
   TBranch        *b_bH_tauH_MET_deltaR;   //!
   TBranch        *b_ditau_deltaR_per_tauH_MET_pt;   //!
   TBranch        *b_p_zeta;   //!
   TBranch        *b_p_zeta_visible;   //!
   TBranch        *b_mT_tauH_MET;   //!
   TBranch        *b_mT_tauH_SVFIT_MET;   //!
   TBranch        *b_mT_total;   //!
   TBranch        *b_m_BDT_ditau_deltaPhi;   //!
   TBranch        *b_BDT_dib_abs_deltaPhi;   //!
   TBranch        *b_BDT_dib_deltaPhi;   //!
   TBranch        *b_BDT_dau1MET_deltaPhi;   //!
   TBranch        *b_BDT_tauHsvfitMet_abs_deltaPhi;   //!
   TBranch        *b_BDT_tauHsvfitMet_deltaPhi;   //!
   TBranch        *b_BDT_bHMet_deltaPhi;   //!
   TBranch        *b_BDT_HHsvfit_abs_deltaPhi;   //!
   TBranch        *b_BDT_HT20;   //!
   TBranch        *b_BDT_topPairMasses;   //!
   TBranch        *b_BDT_MX;   //!
   TBranch        *b_BDT_bH_tauH_MET_InvMass;   //!
   TBranch        *b_BDT_bH_tauH_SVFIT_InvMass;   //!
   TBranch        *b_BDT_bH_tauH_InvMass;   //!
   TBranch        *b_BDT_total_CalcPhi;   //!
   TBranch        *b_BDT_ditau_CalcPhi;   //!
   TBranch        *b_BDT_dib_CalcPhi;   //!
   TBranch        *b_BDT_MET_tauH_SVFIT_cosTheta;   //!
   TBranch        *b_BDT_MET_bH_cosTheta;   //!
   TBranch        *b_BDT_b1_bH_cosTheta;   //!
   TBranch        *b_BDT_tauH_SVFIT_reson_cosTheta;   //!
   TBranch        *b_VBFjj_dEtaSign;   //!
   TBranch        *b_VBFjet2_PUjetID;   //!
   TBranch        *b_bH_VBF1_deltaEta;   //!
   TBranch        *b_dib_dEtaSign;   //!
   TBranch        *b_isTau1real;   //!
   TBranch        *b_isTau2real;   //!
   TBranch        *b_nRealTaus;   //!
   TBranch        *b_BDToutSM_kl_1;   //!
   TBranch        *b_DNN_VBFvsGGF_MuTau;   //!
   TBranch        *b_DNN_VBFvsGGF_ETau;   //!
   TBranch        *b_DNN_VBFvsGGF_TauTauTight;   //!
   TBranch        *b_DNN_VBFvsGGF_TauTauLoose;   //!

   //analysisCode(int a=0, const TString & outName = "");
   analysisCode(const TString & inSample = "", const TString & outName = "", const int & MC = -1);
   //analysisCode(TTree *tree=0);
   virtual ~analysisCode();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(bool info);
   virtual void     Fill();
   virtual void     Book();
   virtual void     EndJob();
   virtual Float_t  getDeltaR(Float_t eta1, Float_t phi1, Float_t eta2, Float_t phi2);
   virtual Float_t  getDeltaPhi(Float_t phi1, Float_t phi2);
   virtual Float_t  getDeltaEta(Float_t eta1, Float_t eta2);
   virtual Float_t  getCosDelta(const LorentzVector& v, const LorentzVector& r); 
   virtual Float_t  getDeltaRboosted(const LorentzVector& v_0, const LorentzVector& v_1, const LorentzVector& ref);
   virtual Float_t  getCentrality(Float_t eta);
   virtual Float_t  getHHCentrality();
   virtual Float_t  getDeltaEtaPlus();
   virtual Float_t  getDeltaEtaMinus();
   virtual Float_t  getAHH();
   virtual Bool_t   Notify();
   virtual std::vector <std::string> addCategories();
   virtual void     Show(Long64_t entry = -1);

   TFile m_outFile; 
   std::map <std::string, TH1F*> m_plots;
   int evt_den_;
   int isMCSample;  
};

#endif

#ifdef analysisCode_cxx
/*analysisCode::analysisCode(int a, const TString & outName) : fChain(0), m_outFile(outName, "RECREATE") 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   TTree *tree;
   if (a == 0) {
   //if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/home-c/camendol/SKIMS_Legacy2018/SKIMS_30Jan2020/SKIM_ZZ/output_1.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/eos/home-c/camendol/SKIMS_Legacy2018/SKIMS_30Jan2020/SKIM_ZZ/output_1.root");
      }
      f->GetObject("HTauTauTree",tree);

   }
   Init(tree);
}
*/

analysisCode::analysisCode(const TString & inSample, const TString & outName, const int & MC) : fChain(0), m_outFile(outName, "RECREATE")
{
   TChain *tree = new TChain("HTauTauTree");
   TString goodFile;

   isMCSample = MC;
   evt_den_ = 0; 

   ifstream file(inSample + "/goodfiles.txt");
   if (file.good()) {
     if (file.is_open()){
       while (file >> goodFile) {
         TFile *f = new TFile(goodFile);
         TH1F * h = (TH1F*) f->Get("h_eff");
         evt_den_ += h->GetBinContent(1);
         tree->Add(goodFile);
         f->Close();
       }
     }
   } else {
     cout << "Algo baila" << endl; 
     return;
   }
   Init(tree);
}

analysisCode::~analysisCode()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t analysisCode::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t analysisCode::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void analysisCode::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   jets_pt = 0;
   jets_eta = 0;
   jets_phi = 0;
   jets_e = 0;
   jets_btag = 0;
   jets_btag_deepCSV = 0;
   jets_btag_deepFlavor = 0;
   jets_flav = 0;
   jets_isH = 0;
   jets_hasgenjet = 0;
   jets_jecUnc = 0;
   leps_pt = 0;
   leps_eta = 0;
   leps_phi = 0;
   leps_e = 0;
   leps_flav = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   if (fChain->GetListOfBranches()->FindObject("MC_weight"))
     fChain->SetBranchAddress("MC_weight", &MC_weight, &b_MC_weight);
   if (fChain->GetListOfBranches()->FindObject("totalWeight"))
     fChain->SetBranchAddress("totalWeight", &totalWeight, &b_totalWeight);
   if (fChain->GetListOfBranches()->FindObject("prescaleWeight"))
     fChain->SetBranchAddress("prescaleWeight", &prescaleWeight, &b_prescaleWeight);
   if (fChain->GetListOfBranches()->FindObject("L1pref_weight"))
     fChain->SetBranchAddress("L1pref_weight", &L1pref_weight, &b_L1pref_weight);
   if (fChain->GetListOfBranches()->FindObject("PURweight"))
     fChain->SetBranchAddress("PUReweight", &PUReweight, &b_PUReweight);
   if (fChain->GetListOfBranches()->FindObject("bTagweightL"))
     fChain->SetBranchAddress("bTagweightL", &bTagweightL, &b_bTagweightL);
   if (fChain->GetListOfBranches()->FindObject("bTagweightM"))
     fChain->SetBranchAddress("bTagweightM", &bTagweightM, &b_bTagweightM);
   if (fChain->GetListOfBranches()->FindObject("bTagweightT"))
     fChain->SetBranchAddress("bTagweightT", &bTagweightT, &b_bTagweightT);
   if (fChain->GetListOfBranches()->FindObject("TTtopPtreweight"))
     fChain->SetBranchAddress("TTtopPtreweight", &TTtopPtreweight, &b_TTtopPtreweight);
   if (fChain->GetListOfBranches()->FindObject("TTtopPtreweight_up"))
     fChain->SetBranchAddress("TTtopPtreweight_up", &TTtopPtreweight_up, &b_TTtopPtreweight_up);
   if (fChain->GetListOfBranches()->FindObject("TTtopPtreweight_down"))
     fChain->SetBranchAddress("TTtopPtreweight_down", &TTtopPtreweight_down, &b_TTtopPtreweight_down);
   if (fChain->GetListOfBranches()->FindObject("trigSF"))
     fChain->SetBranchAddress("trigSF", &trigSF, &b_trigSF);
   if (fChain->GetListOfBranches()->FindObject("trigSF_single"))
     fChain->SetBranchAddress("trigSF_single", &trigSF_single, &b_trigSF_single);
   if (fChain->GetListOfBranches()->FindObject("trigSF_cross"))
     fChain->SetBranchAddress("trigSF_cross", &trigSF_cross, &b_trigSF_cross);
   if (fChain->GetListOfBranches()->FindObject("VBFtrigSF"))
     fChain->SetBranchAddress("VBFtrigSF", &VBFtrigSF, &b_VBFtrigSF);
   if (fChain->GetListOfBranches()->FindObject("FakeRateSF"))
     fChain->SetBranchAddress("FakeRateSF", &FakeRateSF, &b_FakeRateSF);
   if (fChain->GetListOfBranches()->FindObject("jetFakeSF"))
     fChain->SetBranchAddress("jetFakeSF", &jetFakeSF, &b_jetFakeSF);
   if (fChain->GetListOfBranches()->FindObject("IdAndIsoSF_MVA"))
     fChain->SetBranchAddress("IdAndIsoSF_MVA", &IdAndIsoSF_MVA, &b_IdAndIsoSF_MVA);
   if (fChain->GetListOfBranches()->FindObject("IdAndIsoSF_deep"))
     fChain->SetBranchAddress("IdAndIsoSF_deep", &IdAndIsoSF_deep, &b_IdAndIsoSF_deep);
   if (fChain->GetListOfBranches()->FindObject("IdAndIsoAndFakeSF_MVA"))
     fChain->SetBranchAddress("IdAndIsoAndFakeSF_MVA", &IdAndIsoAndFakeSF_MVA, &b_IdAndIsoAndFakeSF_MVA);
   if (fChain->GetListOfBranches()->FindObject("IdAndIsoAndFakeSF_deep"))
     fChain->SetBranchAddress("IdAndIsoAndFakeSF_deep", &IdAndIsoAndFakeSF_deep, &b_IdAndIsoAndFakeSF_deep);
   if (fChain->GetListOfBranches()->FindObject("DYscale_LL"))
     fChain->SetBranchAddress("DYscale_LL", &DYscale_LL, &b_DYscale_LL);
   if (fChain->GetListOfBranches()->FindObject("DYscale_MM"))
     fChain->SetBranchAddress("DYscale_MM", &DYscale_MM, &b_DYscale_MM);
   if (fChain->GetListOfBranches()->FindObject("DYscale_LL_NLO"))
     fChain->SetBranchAddress("DYscale_LL_NLO", &DYscale_LL_NLO, &b_DYscale_LL_NLO);
   if (fChain->GetListOfBranches()->FindObject("DYscale_MM_NLO"))
     fChain->SetBranchAddress("DYscale_MM_NLO", &DYscale_MM_NLO, &b_DYscale_MM_NLO);
   if (fChain->GetListOfBranches()->FindObject("DYLOtoNLOreweight"))
     fChain->SetBranchAddress("DYLOtoNLOreweight", &DYLOtoNLOreweight, &b_DYLOtoNLOreweight);
   if (fChain->GetListOfBranches()->FindObject("DYptZweight"))
     fChain->SetBranchAddress("DYptZweight", &DYptZweight, &b_DYptZweight);
   if (fChain->GetListOfBranches()->FindObject("DYs_NPVweight"))
     fChain->SetBranchAddress("DY_NPVweight", &DY_NPVweight, &b_DY_NPVweight);
   fChain->SetBranchAddress("nBhadrons", &nBhadrons, &b_nBhadrons);
   fChain->SetBranchAddress("lheNOutPartons", &lheNOutPartons, &b_lheNOutPartons);
   fChain->SetBranchAddress("lheNOutB", &lheNOutB, &b_lheNOutB);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("isBoosted", &isBoosted, &b_isBoosted);
   fChain->SetBranchAddress("isVBF", &isVBF, &b_isVBF);
   fChain->SetBranchAddress("isVBFtrigger", &isVBFtrigger, &b_isVBFtrigger);
   fChain->SetBranchAddress("genDecMode1", &genDecMode1, &b_genDecMode1);
   fChain->SetBranchAddress("genDecMode2", &genDecMode2, &b_genDecMode2);
   fChain->SetBranchAddress("genMHH", &genMHH, &b_m_genMHH);
   fChain->SetBranchAddress("genCosth", &genCosth, &b_m_genCosth);
   fChain->SetBranchAddress("npv", &npv, &b_npv);
   fChain->SetBranchAddress("npu", &npu, &b_npu);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("triggerbit", &triggerbit, &b_triggerbit);
   fChain->SetBranchAddress("pass_triggerbit", &pass_triggerbit, &b_pass_triggerbit);
   fChain->SetBranchAddress("cross_monitoring_trig", &cross_monitoring_trig, &b_cross_monitoring_trig);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("pairType", &pairType, &b_pairType);
   fChain->SetBranchAddress("isMC", &isMC, &b_isMC);
   fChain->SetBranchAddress("isOS", &isOS, &b_isOS);
   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain->SetBranchAddress("met_et", &met_et, &b_met_et);
   fChain->SetBranchAddress("met_phi_jetup", &met_phi_jetup, &b_met_phi_jetup);
   fChain->SetBranchAddress("met_et_jetup", &met_et_jetup, &b_met_et_jetup);
   fChain->SetBranchAddress("met_phi_jetdown", &met_phi_jetdown, &b_met_phi_jetdown);
   fChain->SetBranchAddress("met_et_jetdown", &met_et_jetdown, &b_met_et_jetdown);
   fChain->SetBranchAddress("met_phi_tauup", &met_phi_tauup, &b_met_phi_tauup);
   fChain->SetBranchAddress("met_et_tauup", &met_et_tauup, &b_met_et_tauup);
   fChain->SetBranchAddress("met_phi_taudown", &met_phi_taudown, &b_met_phi_taudown);
   fChain->SetBranchAddress("met_et_taudown", &met_et_taudown, &b_met_et_taudown);
   if (fChain->GetListOfBranches()->FindObject("met_phi_eleup"))
     fChain->SetBranchAddress("met_phi_eleup", &met_phi_eleup, &b_met_phi_eleup);
   if (fChain->GetListOfBranches()->FindObject("met_et_eleup"))
     fChain->SetBranchAddress("met_et_eleup", &met_et_eleup, &b_met_et_eleup);
   if (fChain->GetListOfBranches()->FindObject("met_phi_eledown"))
     fChain->SetBranchAddress("met_phi_eledown", &met_phi_eledown, &b_met_phi_eledown);
   if (fChain->GetListOfBranches()->FindObject("met_et_eledown"))
     fChain->SetBranchAddress("met_et_eledown", &met_et_eledown, &b_met_et_eledown);
   fChain->SetBranchAddress("met_et_corr", &met_et_corr, &b_met_et_corr);
   fChain->SetBranchAddress("met_cov00", &met_cov00, &b_met_cov00);
   fChain->SetBranchAddress("met_cov01", &met_cov01, &b_met_cov01);
   fChain->SetBranchAddress("met_cov10", &met_cov10, &b_met_cov10);
   fChain->SetBranchAddress("met_cov11", &met_cov11, &b_met_cov11);
   fChain->SetBranchAddress("met_er_phi", &met_er_phi, &b_met_er_phi);
   fChain->SetBranchAddress("met_er_et", &met_er_et, &b_met_er_et);
   fChain->SetBranchAddress("mT1", &mT1, &b_mT1);
   fChain->SetBranchAddress("mT2", &mT2, &b_mT2);
   fChain->SetBranchAddress("dau1_iso", &dau1_iso, &b_dau1_iso);
   fChain->SetBranchAddress("dau1_MVAiso", &dau1_MVAiso, &b_dau1_MVAiso);
   fChain->SetBranchAddress("dau1_MVAisoNew", &dau1_MVAisoNew, &b_dau1_MVAisoNew);
   fChain->SetBranchAddress("dau1_MVAisoNewdR0p3", &dau1_MVAisoNewdR0p3, &b_dau1_MVAisoNewdR0p3);
   fChain->SetBranchAddress("dau1_CUTiso", &dau1_CUTiso, &b_dau1_CUTiso);
   fChain->SetBranchAddress("dau1_antiele", &dau1_antiele, &b_dau1_antiele);
   fChain->SetBranchAddress("dau1_antimu", &dau1_antimu, &b_dau1_antimu);
   if (fChain->GetListOfBranches()->FindObject("dau1_deepTauVsJet"))
     fChain->SetBranchAddress("dau1_deepTauVsJet", &dau1_deepTauVsJet, &b_dau1_deepTauVsJet);
   if (fChain->GetListOfBranches()->FindObject("dau1_deepTauVsEle"))
     fChain->SetBranchAddress("dau1_deepTauVsEle", &dau1_deepTauVsEle, &b_dau1_deepTauVsEle);
   if (fChain->GetListOfBranches()->FindObject("dau1_deepTauVsMu"))
     fChain->SetBranchAddress("dau1_deepTauVsMu", &dau1_deepTauVsMu, &b_dau1_deepTauVsMu);
   fChain->SetBranchAddress("dau1_photonPtSumOutsideSignalCone", &dau1_photonPtSumOutsideSignalCone, &b_dau1_photonPtSumOutsideSignalCone);
   fChain->SetBranchAddress("dau1_byLooseCombinedIsolationDeltaBetaCorr3Hits", &dau1_byLooseCombinedIsolationDeltaBetaCorr3Hits, &b_dau1_byLooseCombinedIsolationDeltaBetaCorr3Hits);
   fChain->SetBranchAddress("dau1_byMediumCombinedIsolationDeltaBetaCorr3Hits", &dau1_byMediumCombinedIsolationDeltaBetaCorr3Hits, &b_dau1_byMediumCombinedIsolationDeltaBetaCorr3Hits);
   fChain->SetBranchAddress("dau1_byTightCombinedIsolationDeltaBetaCorr3Hits", &dau1_byTightCombinedIsolationDeltaBetaCorr3Hits, &b_dau1_byTightCombinedIsolationDeltaBetaCorr3Hits);
   fChain->SetBranchAddress("dau1_pt", &dau1_pt, &b_dau1_pt);
   fChain->SetBranchAddress("dau1_pt_tauup", &dau1_pt_tauup, &b_dau1_pt_tauup);
   fChain->SetBranchAddress("dau1_pt_taudown", &dau1_pt_taudown, &b_dau1_pt_taudown);
   if (fChain->GetListOfBranches()->FindObject("dau1_pt_eleup"))
     fChain->SetBranchAddress("dau1_pt_eleup", &dau1_pt_eleup, &b_dau1_pt_eleup);
   if (fChain->GetListOfBranches()->FindObject("dau1_pt_eledown"))
     fChain->SetBranchAddress("dau1_pt_eledown", &dau1_pt_eledown, &b_dau1_pt_eledown);
   fChain->SetBranchAddress("dau1_eta", &dau1_eta, &b_dau1_eta);
   fChain->SetBranchAddress("dau1_phi", &dau1_phi, &b_dau1_phi);
   fChain->SetBranchAddress("dau1_e", &dau1_e, &b_dau1_e);
   fChain->SetBranchAddress("dau1_flav", &dau1_flav, &b_dau1_flav);
   fChain->SetBranchAddress("dau1_dxy", &dau1_dxy, &b_dau1_dxy);
   fChain->SetBranchAddress("dau1_dz", &dau1_dz, &b_dau1_dz);
   fChain->SetBranchAddress("dau1_decayMode", &dau1_decayMode, &b_dau1_decayMode);
   fChain->SetBranchAddress("genmatched1_pt", &genmatched1_pt, &b_genmatched1_pt);
   fChain->SetBranchAddress("genmatched1_eta", &genmatched1_eta, &b_genmatched1_eta);
   fChain->SetBranchAddress("genmatched1_phi", &genmatched1_phi, &b_genmatched1_phi);
   fChain->SetBranchAddress("genmatched1_e", &genmatched1_e, &b_genmatched1_e);
   fChain->SetBranchAddress("genmatched2_pt", &genmatched2_pt, &b_genmatched2_pt);
   fChain->SetBranchAddress("genmatched2_eta", &genmatched2_eta, &b_genmatched2_eta);
   fChain->SetBranchAddress("genmatched2_phi", &genmatched2_phi, &b_genmatched2_phi);
   fChain->SetBranchAddress("genmatched2_e", &genmatched2_e, &b_genmatched2_e);
   fChain->SetBranchAddress("hasgenmatch1", &hasgenmatch1, &b_hasgenmatch1);
   fChain->SetBranchAddress("hasgenmatch2", &hasgenmatch2, &b_hasgenmatch2);
   fChain->SetBranchAddress("dau2_iso", &dau2_iso, &b_dau2_iso);
   fChain->SetBranchAddress("dau2_MVAiso", &dau2_MVAiso, &b_dau2_MVAiso);
   fChain->SetBranchAddress("dau2_MVAisoNew", &dau2_MVAisoNew, &b_dau2_MVAisoNew);
   fChain->SetBranchAddress("dau2_MVAisoNewdR0p3", &dau2_MVAisoNewdR0p3, &b_dau2_MVAisoNewdR0p3);
   fChain->SetBranchAddress("dau2_CUTiso", &dau2_CUTiso, &b_dau2_CUTiso);
   fChain->SetBranchAddress("dau2_antiele", &dau2_antiele, &b_dau2_antiele);
   fChain->SetBranchAddress("dau2_antimu", &dau2_antimu, &b_dau2_antimu);
   if (fChain->GetListOfBranches()->FindObject("dau2_deepTauVsJet"))
     fChain->SetBranchAddress("dau2_deepTauVsJet", &dau2_deepTauVsJet, &b_dau2_deepTauVsJet);
   if (fChain->GetListOfBranches()->FindObject("dau2_deepTauVsEle"))
     fChain->SetBranchAddress("dau2_deepTauVsEle", &dau2_deepTauVsEle, &b_dau2_deepTauVsEle);
   if (fChain->GetListOfBranches()->FindObject("dau2_deepTauVsMu"))
     fChain->SetBranchAddress("dau2_deepTauVsMu", &dau2_deepTauVsMu, &b_dau2_deepTauVsMu);
   fChain->SetBranchAddress("dau2_photonPtSumOutsideSignalCone", &dau2_photonPtSumOutsideSignalCone, &b_dau2_photonPtSumOutsideSignalCone);
   fChain->SetBranchAddress("dau2_byLooseCombinedIsolationDeltaBetaCorr3Hits", &dau2_byLooseCombinedIsolationDeltaBetaCorr3Hits, &b_dau2_byLooseCombinedIsolationDeltaBetaCorr3Hits);
   fChain->SetBranchAddress("dau2_byMediumCombinedIsolationDeltaBetaCorr3Hits", &dau2_byMediumCombinedIsolationDeltaBetaCorr3Hits, &b_dau2_byMediumCombinedIsolationDeltaBetaCorr3Hits);
   fChain->SetBranchAddress("dau2_byTightCombinedIsolationDeltaBetaCorr3Hits", &dau2_byTightCombinedIsolationDeltaBetaCorr3Hits, &b_dau2_byTightCombinedIsolationDeltaBetaCorr3Hits);
   fChain->SetBranchAddress("dau2_pt", &dau2_pt, &b_dau2_pt);
   fChain->SetBranchAddress("dau2_pt_tauup", &dau2_pt_tauup, &b_dau2_pt_tauup);
   fChain->SetBranchAddress("dau2_pt_taudown", &dau2_pt_taudown, &b_dau2_pt_taudown);
   if (fChain->GetListOfBranches()->FindObject("dau2_pt_eleup"))
     fChain->SetBranchAddress("dau2_pt_eleup", &dau2_pt_eleup, &b_dau2_pt_eleup);
   if (fChain->GetListOfBranches()->FindObject("dau2_pt_eledown"))
     fChain->SetBranchAddress("dau2_pt_eledown", &dau2_pt_eledown, &b_dau2_pt_eledown);
   fChain->SetBranchAddress("dau2_eta", &dau2_eta, &b_dau2_eta);
   fChain->SetBranchAddress("dau2_phi", &dau2_phi, &b_dau2_phi);
   fChain->SetBranchAddress("dau2_e", &dau2_e, &b_dau2_e);
   fChain->SetBranchAddress("dau2_flav", &dau2_flav, &b_dau2_flav);
   fChain->SetBranchAddress("dau2_dxy", &dau2_dxy, &b_dau2_dxy);
   fChain->SetBranchAddress("dau2_dz", &dau2_dz, &b_dau2_dz);
   fChain->SetBranchAddress("dau2_decayMode", &dau2_decayMode, &b_dau2_decayMode);
   fChain->SetBranchAddress("bjet1_pt", &bjet1_pt, &b_bjet1_pt);
   fChain->SetBranchAddress("bjet1_eta", &bjet1_eta, &b_bjet1_eta);
   fChain->SetBranchAddress("bjet1_phi", &bjet1_phi, &b_bjet1_phi);
   fChain->SetBranchAddress("bjet1_e", &bjet1_e, &b_bjet1_e);
   fChain->SetBranchAddress("bjet1_bID", &bjet1_bID, &b_bjet1_bID);
   fChain->SetBranchAddress("bjet1_bID_deepCSV", &bjet1_bID_deepCSV, &b_bjet1_bID_deepCSV);
   if (fChain->GetListOfBranches()->FindObject("bjet1_bID_deepFlavor"))
     fChain->SetBranchAddress("bjet1_bID_deepFlavor", &bjet1_bID_deepFlavor, &b_bjet1_bID_deepFlavor);
   fChain->SetBranchAddress("bjet1_bMVAID", &bjet1_bMVAID, &b_bjet1_bMVAID);
   fChain->SetBranchAddress("bjet1_flav", &bjet1_flav, &b_bjet1_flav);
   fChain->SetBranchAddress("bjet1_pt_raw", &bjet1_pt_raw, &b_bjet1_pt_raw);
   fChain->SetBranchAddress("bjet1_pt_raw_jetup", &bjet1_pt_raw_jetup, &b_bjet1_pt_raw_jetup);
   fChain->SetBranchAddress("bjet1_pt_raw_jetdown", &bjet1_pt_raw_jetdown, &b_bjet1_pt_raw_jetdown);
   fChain->SetBranchAddress("bjet1_hasgenjet", &bjet1_hasgenjet, &b_bjet1_hasgenjet);
   fChain->SetBranchAddress("bjet1_JER", &bjet1_JER, &b_bjet1_JER);
   if (fChain->GetListOfBranches()->FindObject("bjet1_gen_matched"))
     fChain->SetBranchAddress("bjet1_gen_matched", &bjet1_gen_matched, &b_bjet1_gen_matched);
   fChain->SetBranchAddress("bjet2_pt", &bjet2_pt, &b_bjet2_pt);
   fChain->SetBranchAddress("bjet2_eta", &bjet2_eta, &b_bjet2_eta);
   fChain->SetBranchAddress("bjet2_phi", &bjet2_phi, &b_bjet2_phi);
   fChain->SetBranchAddress("bjet2_e", &bjet2_e, &b_bjet2_e);
   fChain->SetBranchAddress("bjet2_bID", &bjet2_bID, &b_bjet2m_bID);
   fChain->SetBranchAddress("bjet2_bID_deepCSV", &bjet2_bID_deepCSV, &b_bjet2_bID_deepCSV);
   if (fChain->GetListOfBranches()->FindObject("bjet2_bID_deepFlavor"))
     fChain->SetBranchAddress("bjet2_bID_deepFlavor", &bjet2_bID_deepFlavor, &b_bjet2_bID_deepFlavor);
   fChain->SetBranchAddress("bjet2_bMVAID", &bjet2_bMVAID, &b_bjet2m_bMVAID);
   fChain->SetBranchAddress("bjet2_flav", &bjet2_flav, &b_bjet2_flav);
   fChain->SetBranchAddress("bjet2_pt_raw", &bjet2_pt_raw, &b_bjet2_pt_raw);
   fChain->SetBranchAddress("bjet2_pt_raw_jetup", &bjet2_pt_raw_jetup, &b_bjet2_pt_raw_jetup);
   fChain->SetBranchAddress("bjet2_pt_raw_jetdown", &bjet2_pt_raw_jetdown, &b_bjet2_pt_raw_jetdown);
   fChain->SetBranchAddress("bjet2_hasgenjet", &bjet2_hasgenjet, &b_bjet2_hasgenjet);
   fChain->SetBranchAddress("bjet2_JER", &bjet2_JER, &b_bjet2_JER);
   if (fChain->GetListOfBranches()->FindObject("bjet2_gen_matched"))
     fChain->SetBranchAddress("bjet2_gen_matched", &bjet2_gen_matched, &b_bjet2_gen_matched);
   fChain->SetBranchAddress("bjets_bID", &bjets_bID, &b_bjets_bID);
   fChain->SetBranchAddress("bjets_bID_deepCSV", &bjets_bID_deepCSV, &b_bjets_bID_deepCSV);
   if (fChain->GetListOfBranches()->FindObject("bjets_bID_deepFlavor"))
     fChain->SetBranchAddress("bjets_bID_deepFlavor", &bjets_bID_deepFlavor, &b_bjets_bID_deepFlavor);
   if (fChain->GetListOfBranches()->FindObject("bjets_gen_matched"))
   fChain->SetBranchAddress("bjets_gen_matched", &bjets_gen_matched, &b_bjets_gen_matched);
   fChain->SetBranchAddress("nfatjets", &nfatjets, &b_nfatjets);
   fChain->SetBranchAddress("fatjet_pt", &fatjet_pt, &b_fatjet_pt);
   fChain->SetBranchAddress("fatjet_eta", &fatjet_eta, &b_fatjet_eta);
   fChain->SetBranchAddress("fatjet_phi", &fatjet_phi, &b_fatjet_phi);
   fChain->SetBranchAddress("fatjet_e", &fatjet_e, &b_fatjet_e);
   fChain->SetBranchAddress("fatjet_bID", &fatjet_bID, &b_fatjet_bID);
   fChain->SetBranchAddress("fatjet_bID_deepCSV", &fatjet_bID_deepCSV, &b_fatjet_bID_deepCSV);
   if (fChain->GetListOfBranches()->FindObject("fatjet_bID_deepFlavor"))
     fChain->SetBranchAddress("fatjet_bID_deepFlavor", &fatjet_bID_deepFlavor, &b_fatjet_bID_deepFlavor);
   fChain->SetBranchAddress("fatjet_filteredMass", &fatjet_filteredMass, &b_fatjet_filteredMass);
   fChain->SetBranchAddress("fatjet_prunedMass", &fatjet_prunedMass, &b_fatjet_prunedMass);
   fChain->SetBranchAddress("fatjet_trimmedMass", &fatjet_trimmedMass, &b_fatjet_trimmedMass);
   fChain->SetBranchAddress("fatjet_softdropMass", &fatjet_softdropMass, &b_fatjet_softdropMass);
   fChain->SetBranchAddress("fatjet_tau1", &fatjet_tau1, &b_fatjet_tau1);
   fChain->SetBranchAddress("fatjet_tau2", &fatjet_tau2, &b_fatjet_tau2);
   fChain->SetBranchAddress("fatjet_tau3", &fatjet_tau3, &b_fatjet_tau3);
   fChain->SetBranchAddress("fatjet_nsubjets", &fatjet_nsubjets, &b_fatjet_nsubjets);
   fChain->SetBranchAddress("dR_subj1_subj2", &dR_subj1_subj2, &b_dR_subj1_subj2);
   fChain->SetBranchAddress("subjetjet1_pt", &subjetjet1_pt, &b_subjetjet1_pt);
   fChain->SetBranchAddress("subjetjet1_eta", &subjetjet1_eta, &b_subjetjet1_eta);
   fChain->SetBranchAddress("subjetjet1_phi", &subjetjet1_phi, &b_subjetjet1_phi);
   fChain->SetBranchAddress("subjetjet1_e", &subjetjet1_e, &b_subjetjet1_e);
   fChain->SetBranchAddress("subjetjet1_bID", &subjetjet1_bID, &b_subjetjet1_bID);
   fChain->SetBranchAddress("subjetjet1_bID_deepCSV", &subjetjet1_bID_deepCSV, &b_subjetjet1_bID_deepCSV);
   if (fChain->GetListOfBranches()->FindObject("subjetjet1_bID_deepFlavor"))
   fChain->SetBranchAddress("subjetjet1_bID_deepFlavor", &subjetjet1_bID_deepFlavor, &b_subjetjet1_bID_deepFlavor);
   fChain->SetBranchAddress("subjetjet2_pt", &subjetjet2_pt, &b_subjetjet2_pt);
   fChain->SetBranchAddress("subjetjet2_eta", &subjetjet2_eta, &b_subjetjet2_eta);
   fChain->SetBranchAddress("subjetjet2_phi", &subjetjet2_phi, &b_subjetjet2_phi);
   fChain->SetBranchAddress("subjetjet2_e", &subjetjet2_e, &b_subjetjet2_e);
   fChain->SetBranchAddress("subjetjet2_bID", &subjetjet2_bID, &b_subjetjet2_bID);
   fChain->SetBranchAddress("subjetjet2_bID_deepCSV", &subjetjet2_bID_deepCSV, &b_subjetjet2_bID_deepCSV);
   if (fChain->GetListOfBranches()->FindObject("subjetjet2_bID_deepFlavor"))
   fChain->SetBranchAddress("subjetjet2_bID_deepFlavor", &subjetjet2_bID_deepFlavor, &b_subjetjet2_bID_deepFlavor);
   fChain->SetBranchAddress("genjet1_pt", &genjet1_pt, &b_genjet1_pt);
   fChain->SetBranchAddress("genjet1_eta", &genjet1_eta, &b_genjet1_eta);
   fChain->SetBranchAddress("genjet1_phi", &genjet1_phi, &b_genjet1_phi);
   fChain->SetBranchAddress("genjet1_e", &genjet1_e, &b_genjet1_e);
   fChain->SetBranchAddress("genjet2_pt", &genjet2_pt, &b_genjet2_pt);
   fChain->SetBranchAddress("genjet2_eta", &genjet2_eta, &b_genjet2_eta);
   fChain->SetBranchAddress("genjet2_phi", &genjet2_phi, &b_genjet2_phi);
   fChain->SetBranchAddress("genjet2_e", &genjet2_e, &b_genjet2_e);
   fChain->SetBranchAddress("tauH_pt", &tauH_pt, &b_tauH_pt);
   fChain->SetBranchAddress("tauH_eta", &tauH_eta, &b_tauH_eta);
   fChain->SetBranchAddress("tauH_phi", &tauH_phi, &b_tauH_phi);
   fChain->SetBranchAddress("tauH_e", &tauH_e, &b_tauH_e);
   fChain->SetBranchAddress("tauH_mass", &tauH_mass, &b_tauH_mass);
   fChain->SetBranchAddress("tauH_SVFIT_mass", &tauH_SVFIT_mass, &b_tauH_SVFIT_mass);
   fChain->SetBranchAddress("tauH_SVFIT_pt", &tauH_SVFIT_pt, &b_tauH_SVFIT_pt);
   fChain->SetBranchAddress("tauH_SVFIT_eta", &tauH_SVFIT_eta, &b_tauH_SVFIT_eta);
   fChain->SetBranchAddress("tauH_SVFIT_phi", &tauH_SVFIT_phi, &b_tauH_SVFIT_phi);
   fChain->SetBranchAddress("tauH_SVFIT_METphi", &tauH_SVFIT_METphi, &b_tauH_SVFIT_METphi);
   fChain->SetBranchAddress("tauH_SVFIT_METrho", &tauH_SVFIT_METrho, &b_tauH_SVFIT_METrho);
   fChain->SetBranchAddress("tauH_SVFIT_mass_up", &tauH_SVFIT_mass_up, &b_tauH_SVFIT_mass_up);
   fChain->SetBranchAddress("tauH_SVFIT_mass_down", &tauH_SVFIT_mass_down, &b_tauH_SVFIT_mass_down);
   fChain->SetBranchAddress("tauH_SVFIT_mass_METup", &tauH_SVFIT_mass_METup, &b_tauH_SVFIT_mass_METup);
   fChain->SetBranchAddress("tauH_SVFIT_mass_METdown", &tauH_SVFIT_mass_METdown, &b_tauH_SVFIT_mass_METdown);
   fChain->SetBranchAddress("bH_pt", &bH_pt, &b_bH_pt);
   fChain->SetBranchAddress("bH_eta", &bH_eta, &b_bH_eta);
   fChain->SetBranchAddress("bH_phi", &bH_phi, &b_bH_phi);
   fChain->SetBranchAddress("bH_e", &bH_e, &b_bH_e);
   fChain->SetBranchAddress("bH_mass", &bH_mass, &b_bH_mass);
   fChain->SetBranchAddress("HHsvfit_pt", &HHsvfit_pt, &b_HHsvfit_pt);
   fChain->SetBranchAddress("HHsvfit_eta", &HHsvfit_eta, &b_HHsvfit_eta);
   fChain->SetBranchAddress("HHsvfit_phi", &HHsvfit_phi, &b_HHsvfit_phi);
   fChain->SetBranchAddress("HHsvfit_e", &HHsvfit_e, &b_HHsvfit_e);
   fChain->SetBranchAddress("HHsvfit_mass", &HHsvfit_mass, &b_HHsvfit_mass);
   fChain->SetBranchAddress("HH_pt", &HH_pt, &b_HH_pt);
   fChain->SetBranchAddress("HH_eta", &HH_eta, &b_HH_eta);
   fChain->SetBranchAddress("HH_phi", &HH_phi, &b_HH_phi);
   fChain->SetBranchAddress("HH_e", &HH_e, &b_HH_e);
   fChain->SetBranchAddress("HH_mass", &HH_mass, &b_HH_mass);
   fChain->SetBranchAddress("HH_mass_raw", &HH_mass_raw, &b_HH_mass_raw);
   fChain->SetBranchAddress("HH_mass_raw_tauup", &HH_mass_raw_tauup, &b_HH_mass_raw_tauup);
   fChain->SetBranchAddress("HH_mass_raw_taudown", &HH_mass_raw_taudown, &b_HH_mass_raw_taudown);
   if (fChain->GetListOfBranches()->FindObject("HH_mass_raw_eleup"))
     fChain->SetBranchAddress("HH_mass_raw_eleup", &HH_mass_raw_eleup, &b_HH_mass_raw_eleup);
   if (fChain->GetListOfBranches()->FindObject("HH_mass_raw_eledown"))
     fChain->SetBranchAddress("HH_mass_raw_eledown", &HH_mass_raw_eledown, &b_HH_mass_raw_eledown);
   fChain->SetBranchAddress("HHKin_mass", &HHKin_mass, &b_HHKin_mass);
   fChain->SetBranchAddress("HHKin_chi2", &HHKin_chi2, &b_HHKin_chi2);
   fChain->SetBranchAddress("HH_deltaPhi", &HH_deltaPhi, &b_HH_deltaPhi);
   fChain->SetBranchAddress("HH_deltaR", &HH_deltaR, &b_HH_deltaR);
   fChain->SetBranchAddress("HH_deltaEta", &HH_deltaEta, &b_HH_deltaEta);
   fChain->SetBranchAddress("HHsvfit_deltaPhi", &HHsvfit_deltaPhi, &b_HHsvfit_deltaPhi);
   fChain->SetBranchAddress("tauHMet_deltaPhi", &tauHMet_deltaPhi, &b_tauHMet_deltaPhi);
   fChain->SetBranchAddress("tauHsvfitMet_deltaPhi", &tauHsvfitMet_deltaPhi, &b_tauHsvfitMet_deltaPhi);
   fChain->SetBranchAddress("bHMet_deltaPhi", &bHMet_deltaPhi, &b_bHMet_deltaPhi);
   fChain->SetBranchAddress("ditau_deltaPhi", &ditau_deltaPhi, &b_ditau_deltaPhi);
   fChain->SetBranchAddress("ditau_deltaEta", &ditau_deltaEta, &b_ditau_deltaEta);
   fChain->SetBranchAddress("dib_deltaPhi", &dib_deltaPhi, &b_dib_deltaPhi);
   fChain->SetBranchAddress("dib_deltaEta", &dib_deltaEta, &b_dib_deltaEta);
   fChain->SetBranchAddress("ditau_deltaR", &ditau_deltaR, &b_ditau_deltaR);
   fChain->SetBranchAddress("dib_deltaR", &dib_deltaR, &b_dib_deltaR);
   fChain->SetBranchAddress("ditau_deltaR_per_tauHsvfitpt", &ditau_deltaR_per_tauHsvfitpt, &b_ditau_deltaR_per_tauHsvfitpt);
   fChain->SetBranchAddress("dib_deltaR_per_bHpt", &dib_deltaR_per_bHpt, &b_dib_deltaR_per_bHpt);
   fChain->SetBranchAddress("btau_deltaRmin", &btau_deltaRmin, &b_btau_deltaRmin);
   fChain->SetBranchAddress("btau_deltaRmax", &btau_deltaRmax, &b_btau_deltaRmax);
   fChain->SetBranchAddress("dau1MET_deltaphi", &dau1MET_deltaphi, &b_dau1MET_deltaphi);
   fChain->SetBranchAddress("dau2MET_deltaphi", &dau2MET_deltaphi, &b_dau2MET_deltaphi);
   fChain->SetBranchAddress("HT20", &HT20, &b_HT20);
   fChain->SetBranchAddress("HT50", &HT50, &b_HT50);
   fChain->SetBranchAddress("HT20Full", &HT20Full, &b_HT20Full);
   fChain->SetBranchAddress("jet20centrality", &jet20centrality, &b_jet20centrality);
   fChain->SetBranchAddress("jets_pt", &jets_pt, &b_jets_pt);
   fChain->SetBranchAddress("jets_eta", &jets_eta, &b_jets_eta);
   fChain->SetBranchAddress("jets_phi", &jets_phi, &b_jets_phi);
   fChain->SetBranchAddress("jets_e", &jets_e, &b_jets_e);
   fChain->SetBranchAddress("jets_btag", &jets_btag, &b_jets_btag);
   fChain->SetBranchAddress("jets_btag_deepCSV", &jets_btag_deepCSV, &b_jets_btag_deepCSV);
   if (fChain->GetListOfBranches()->FindObject("jets_btag_deepFlavor"))
     fChain->SetBranchAddress("jets_btag_deepFlavor", &jets_btag_deepFlavor, &b_jets_btag_deepFlavor);
   fChain->SetBranchAddress("jets_flav", &jets_flav, &b_jets_flav);
   fChain->SetBranchAddress("jets_isH", &jets_isH, &b_jets_isH);
   fChain->SetBranchAddress("jets_hasgenjet", &jets_hasgenjet, &b_jets_hasgenjet);
   fChain->SetBranchAddress("njets", &njets, &b_njets);
   fChain->SetBranchAddress("addjets", &addjets, &b_addjets);
   fChain->SetBranchAddress("njets20", &njets20, &b_njets20);
   fChain->SetBranchAddress("njets50", &njets50, &b_njets50);
   fChain->SetBranchAddress("nbjets20", &nbjets20, &b_nbjets20);
   fChain->SetBranchAddress("nbjets50", &nbjets50, &b_nbjets50);
   fChain->SetBranchAddress("nbjetscand", &nbjetscand, &b_nbjetscand);
   fChain->SetBranchAddress("njetsBHadFlav", &njetsBHadFlav, &b_njetsBHadFlav);
   fChain->SetBranchAddress("njetsCHadFlav", &njetsCHadFlav, &b_njetsCHadFlav);
   fChain->SetBranchAddress("jets_jecUnc", &jets_jecUnc, &b_jets_jecUnc);
   fChain->SetBranchAddress("dau1_jecUnc", &dau1_jecUnc, &b_dau1_jecUnc);
   fChain->SetBranchAddress("dau2_jecUnc", &dau2_jecUnc, &b_dau2_jecUnc);
   fChain->SetBranchAddress("bjet1_jecUnc", &bjet1_jecUnc, &b_bjet1_jecUnc);
   fChain->SetBranchAddress("bjet2_jecUnc", &bjet2_jecUnc, &b_bjet2_jecUnc);
   fChain->SetBranchAddress("leps_pt", &leps_pt, &b_leps_pt);
   fChain->SetBranchAddress("leps_eta", &leps_eta, &b_leps_eta);
   fChain->SetBranchAddress("leps_phi", &leps_phi, &b_leps_phi);
   fChain->SetBranchAddress("leps_e", &leps_e, &b_leps_e);
   fChain->SetBranchAddress("leps_flav", &leps_flav, &b_leps_flav);
   fChain->SetBranchAddress("nleps", &nleps, &b_nleps);
   fChain->SetBranchAddress("HHkinsvfit_bHmass", &HHkinsvfit_bHmass, &b_HHkinsvfit_bHmass);
   fChain->SetBranchAddress("HHkinsvfit_pt", &HHkinsvfit_pt, &b_HHkinsvfit_pt);
   fChain->SetBranchAddress("HHkinsvfit_eta", &HHkinsvfit_eta, &b_HHkinsvfit_eta);
   fChain->SetBranchAddress("HHkinsvfit_phi", &HHkinsvfit_phi, &b_HHkinsvfit_phi);
   fChain->SetBranchAddress("HHkinsvfit_e", &HHkinsvfit_e, &b_HHkinsvfit_e);
   fChain->SetBranchAddress("HHkinsvfit_m", &HHkinsvfit_m, &b_HHkinsvfit_m);
   fChain->SetBranchAddress("MT2", &MT2, &b_MT2);
   fChain->SetBranchAddress("MT2_tauup", &MT2_tauup, &b_MT2_tauup);
   fChain->SetBranchAddress("MT2_taudown", &MT2_taudown, &b_MT2_taudown);
   fChain->SetBranchAddress("MT2_jetup", &MT2_jetup, &b_MT2_jetup);
   fChain->SetBranchAddress("MT2_jetdown", &MT2_jetdown, &b_MT2_jetdown);
   if (fChain->GetListOfBranches()->FindObject("MT2_eleup"))
     fChain->SetBranchAddress("MT2_eleup", &MT2_eleup, &b_MT2_eleup);
   if (fChain->GetListOfBranches()->FindObject("MT2_eledown"))
     fChain->SetBranchAddress("MT2_eledown", &MT2_eledown, &b_MT2_eledown);
   fChain->SetBranchAddress("bH_mass_raw", &bH_mass_raw, &b_bH_mass_raw);
   fChain->SetBranchAddress("bH_mass_raw_jetup", &bH_mass_raw_jetup, &b_bH_mass_raw_jetup);
   fChain->SetBranchAddress("bH_mass_raw_jetdown", &bH_mass_raw_jetdown, &b_bH_mass_raw_jetdown);
   fChain->SetBranchAddress("HHKin_mass_raw", &HHKin_mass_raw, &b_HHKin_mass_raw);
   fChain->SetBranchAddress("HHKin_mass_raw_tauup", &HHKin_mass_raw_tauup, &b_HHKin_mass_raw_tauup);
   fChain->SetBranchAddress("HHKin_mass_raw_taudown", &HHKin_mass_raw_taudown, &b_HHKin_mass_raw_taudown);
   fChain->SetBranchAddress("HHKin_mass_raw_jetup", &HHKin_mass_raw_jetup, &b_HHKin_mass_raw_jetup);
   fChain->SetBranchAddress("HHKin_mass_raw_jetdown", &HHKin_mass_raw_jetdown, &b_HHKin_mass_raw_jetdown);
   if (fChain->GetListOfBranches()->FindObject("HHKin_mass_raw_eleup"))
     fChain->SetBranchAddress("HHKin_mass_raw_eleup", &HHKin_mass_raw_eleup, &b_HHKin_mass_raw_eleup);
   if (fChain->GetListOfBranches()->FindObject("HHKin_mass_raw_eledown"))
     fChain->SetBranchAddress("HHKin_mass_raw_eledown", &HHKin_mass_raw_eledown, &b_HHKin_mass_raw_eledown);
   fChain->SetBranchAddress("HHKin_mass_raw_chi2", &HHKin_mass_raw_chi2, &b_HHKin_mass_raw_chi2);
   fChain->SetBranchAddress("HHKin_mass_raw_convergence", &HHKin_mass_raw_convergence, &b_HHKin_mass_raw_convergence);
   fChain->SetBranchAddress("HHKin_mass_raw_prob", &HHKin_mass_raw_prob, &b_HHKin_mass_raw_prob);
   fChain->SetBranchAddress("HHKin_mass_raw_copy", &HHKin_mass_raw_copy, &b_HHKin_mass_raw_copy);
   fChain->SetBranchAddress("lheht", &lheht, &b_lheht);
   fChain->SetBranchAddress("topReweight", &topReweight, &b_topReweight);
   fChain->SetBranchAddress("VBFjet1_pt", &VBFjet1_pt, &b_VBFjet1_pt);
   fChain->SetBranchAddress("VBFjet1_eta", &VBFjet1_eta, &b_VBFjet1_eta);
   fChain->SetBranchAddress("VBFjet1_phi", &VBFjet1_phi, &b_VBFjet1_phi);
   fChain->SetBranchAddress("VBFjet1_e", &VBFjet1_e, &b_VBFjet1_e);
   fChain->SetBranchAddress("VBFjet1_btag", &VBFjet1_btag, &b_VBFjet1_btag);
   fChain->SetBranchAddress("VBFjet1_btag_deepCSV", &VBFjet1_btag_deepCSV, &b_VBFjet1_btag_deepCSV);
   if (fChain->GetListOfBranches()->FindObject("VBFjet1_btag_deepFlavor"))
     fChain->SetBranchAddress("VBFjet1_btag_deepFlavor", &VBFjet1_btag_deepFlavor, &b_VBFjet1_btag_deepFlavor);
   fChain->SetBranchAddress("VBFjet1_flav", &VBFjet1_flav, &b_VBFjet1_flav);
   fChain->SetBranchAddress("VBFjet1_hasgenjet", &VBFjet1_hasgenjet, &b_VBFjet1_hasgenjet);
   fChain->SetBranchAddress("VBFgenjet1_pt", &VBFgenjet1_pt, &b_VBFgenjet1_pt);
   fChain->SetBranchAddress("VBFgenjet1_eta", &VBFgenjet1_eta, &b_VBFgenjet1_eta);
   fChain->SetBranchAddress("VBFgenjet1_phi", &VBFgenjet1_phi, &b_VBFgenjet1_phi);
   fChain->SetBranchAddress("VBFgenjet1_e", &VBFgenjet1_e, &b_VBFgenjet1_e);
   fChain->SetBranchAddress("VBFjet2_pt", &VBFjet2_pt, &b_VBFjet2_pt);
   fChain->SetBranchAddress("VBFjet2_eta", &VBFjet2_eta, &b_VBFjet2_eta);
   fChain->SetBranchAddress("VBFjet2_phi", &VBFjet2_phi, &b_VBFjet2_phi);
   fChain->SetBranchAddress("VBFjet2_e", &VBFjet2_e, &b_VBFjet2_e);
   fChain->SetBranchAddress("VBFjet2_btag", &VBFjet2_btag, &b_VBFjet2_btag);
   fChain->SetBranchAddress("VBFjet2_btag_deepCSV", &VBFjet2_btag_deepCSV, &b_VBFjet2_btag_deepCSV);
   if (fChain->GetListOfBranches()->FindObject("VBFjet2_btag_deepFlavor"))
     fChain->SetBranchAddress("VBFjet2_btag_deepFlavor", &VBFjet2_btag_deepFlavor, &b_VBFjet2_btag_deepFlavor);
   fChain->SetBranchAddress("VBFjet2_flav", &VBFjet2_flav, &b_VBFjet2_flav);
   fChain->SetBranchAddress("VBFjet2_hasgenjet", &VBFjet2_hasgenjet, &b_VBFjet2_hasgenjet);
   fChain->SetBranchAddress("VBFgenjet2_pt", &VBFgenjet2_pt, &b_VBFgenjet2_pt);
   fChain->SetBranchAddress("VBFgenjet2_eta", &VBFgenjet2_eta, &b_VBFgenjet2_eta);
   fChain->SetBranchAddress("VBFgenjet2_phi", &VBFgenjet2_phi, &b_VBFgenjet2_phi);
   fChain->SetBranchAddress("VBFgenjet2_e", &VBFgenjet2_e, &b_VBFgenjet2_e);
   fChain->SetBranchAddress("VBFjj_mass_log", &VBFjj_mass_log, &b_VBFjj_mass_log);
   fChain->SetBranchAddress("jj_mass_log", &jj_mass_log, &b_jj_mass_log);
   fChain->SetBranchAddress("VBFjj_mass", &VBFjj_mass, &b_VBFjj_mass);
   fChain->SetBranchAddress("VBFjj_deltaEta", &VBFjj_deltaEta, &b_VBFjj_deltaEta);
   fChain->SetBranchAddress("VBFjj_HT", &VBFjj_HT, &b_VBFjj_HT);
   fChain->SetBranchAddress("jet3_pt", &jet3_pt, &b_jet3_pt);
   fChain->SetBranchAddress("jet3_eta", &jet3_eta, &b_jet3_eta);
   fChain->SetBranchAddress("jet3_phi", &jet3_phi, &b_jet3_phi);
   fChain->SetBranchAddress("jet3_e", &jet3_e, &b_jet3_e);
   fChain->SetBranchAddress("jet3_btag", &jet3_btag, &b_jet3_btag);
   fChain->SetBranchAddress("jet3_btag_deepCSV", &jet3_btag_deepCSV, &b_jet3_btag_deepCSV);
   if (fChain->GetListOfBranches()->FindObject("jet3_btag_deepFlavor"))
   fChain->SetBranchAddress("jet3_btag_deepFlavor", &jet3_btag_deepFlavor, &b_jet3_btag_deepFlavor);
   fChain->SetBranchAddress("jet3_flav", &jet3_flav, &b_jet3_flav);
   fChain->SetBranchAddress("jet3_hasgenjet", &jet3_hasgenjet, &b_jet3_hasgenjet);
   fChain->SetBranchAddress("genjet3_pt", &genjet3_pt, &b_genjet3_pt);
   fChain->SetBranchAddress("genjet3_eta", &genjet3_eta, &b_genjet3_eta);
   fChain->SetBranchAddress("genjet3_phi", &genjet3_phi, &b_genjet3_phi);
   fChain->SetBranchAddress("genjet3_e", &genjet3_e, &b_genjet3_e);
   fChain->SetBranchAddress("jet4_pt", &jet4_pt, &b_jet4_pt);
   fChain->SetBranchAddress("jet4_eta", &jet4_eta, &b_jet4_eta);
   fChain->SetBranchAddress("jet4_phi", &jet4_phi, &b_jet4_phi);
   fChain->SetBranchAddress("jet4_e", &jet4_e, &b_jet4_e);
   fChain->SetBranchAddress("jet4_btag", &jet4_btag, &b_jet4_btag);
   fChain->SetBranchAddress("jet4_btag_deepCSV", &jet4_btag_deepCSV, &b_jet4_btag_deepCSV);
   if (fChain->GetListOfBranches()->FindObject("jet4_btag_deepFlavor"))
   fChain->SetBranchAddress("jet4_btag_deepFlavor", &jet4_btag_deepFlavor, &b_jet4_btag_deepFlavor);
   fChain->SetBranchAddress("jet4_flav", &jet4_flav, &b_jet4_flav);
   fChain->SetBranchAddress("jet4_hasgenjet", &jet4_hasgenjet, &b_jet4_hasgenjet);
   fChain->SetBranchAddress("genjet4_pt", &genjet4_pt, &b_genjet4_pt);
   fChain->SetBranchAddress("genjet4_eta", &genjet4_eta, &b_genjet4_eta);
   fChain->SetBranchAddress("genjet4_phi", &genjet4_phi, &b_genjet4_phi);
   fChain->SetBranchAddress("genjet4_e", &genjet4_e, &b_genjet4_e);
   fChain->SetBranchAddress("jj_mass", &jj_mass, &b_jj_mass);
   fChain->SetBranchAddress("jj_deltaEta", &jj_deltaEta, &b_jj_deltaEta);
   fChain->SetBranchAddress("jj_HT", &jj_HT, &b_jj_HT);
   fChain->SetBranchAddress("dau1_z", &dau1_z, &b_dau1_z);
   fChain->SetBranchAddress("dau2_z", &dau2_z, &b_dau2_z);
   fChain->SetBranchAddress("bjet1_z", &bjet1_z, &b_bjet1_z);
   fChain->SetBranchAddress("bjet2_z", &bjet2_z, &b_bjet2_z);
   fChain->SetBranchAddress("tauH_z", &tauH_z, &b_tauH_z);
   fChain->SetBranchAddress("bH_z", &bH_z, &b_bH_z);
   fChain->SetBranchAddress("HH_z", &HH_z, &b_HH_z);
   fChain->SetBranchAddress("HH_zV", &HH_zV, &b_HH_zV);
   fChain->SetBranchAddress("HH_A", &HH_A, &b_HH_A);
   fChain->SetBranchAddress("jet5_pt", &jet5_pt, &b_jet5_pt);
   fChain->SetBranchAddress("jet5_eta", &jet5_eta, &b_jet5_eta);
   fChain->SetBranchAddress("jet5_phi", &jet5_phi, &b_jet5_phi);
   fChain->SetBranchAddress("jet5_e", &jet5_e, &b_jet5_e);
   fChain->SetBranchAddress("jet5_btag", &jet5_btag, &b_jet5_btag);
   fChain->SetBranchAddress("jet5_btag_deepCSV", &jet5_btag_deepCSV, &b_jet5_btag_deepCSV);
   if (fChain->GetListOfBranches()->FindObject("jet5_btag_deepFlavor"))
   fChain->SetBranchAddress("jet5_btag_deepFlavor", &jet5_btag_deepFlavor, &b_jet5_btag_deepFlavor);
   fChain->SetBranchAddress("jet5_flav", &jet5_flav, &b_jet5_flav);
   fChain->SetBranchAddress("jet5_hasgenjet", &jet5_hasgenjet, &b_jet5_hasgenjet);
   fChain->SetBranchAddress("jet5_z", &jet5_z, &b_jet5_z);
   fChain->SetBranchAddress("jet5_VBF_pt", &jet5_VBF_pt, &b_jet5_VBF_pt);
   fChain->SetBranchAddress("jet5_VBF_eta", &jet5_VBF_eta, &b_jet5_VBF_eta);
   fChain->SetBranchAddress("jet5_VBF_phi", &jet5_VBF_phi, &b_jet5_VBF_phi);
   fChain->SetBranchAddress("jet5_VBF_e", &jet5_VBF_e, &b_jet5_VBF_e);
   fChain->SetBranchAddress("jet5_VBF_btag", &jet5_VBF_btag, &b_jet5_VBF_btag);
   fChain->SetBranchAddress("jet5_VBF_btag_deepCSV", &jet5_VBF_btag_deepCSV, &b_jet5_VBF_btag_deepCSV);
   if (fChain->GetListOfBranches()->FindObject("jet5_VBF_btag_deepFlavor"))
   fChain->SetBranchAddress("jet5_VBF_btag_deepFlavor", &jet5_VBF_btag_deepFlavor, &b_jet5_VBF_btag_deepFlavor);
   fChain->SetBranchAddress("jet5_VBF_flav", &jet5_VBF_flav, &b_jet5_VBF_flav);
   fChain->SetBranchAddress("jet5_VBF_hasgenjet", &jet5_VBF_hasgenjet, &b_jet5_VBF_hasgenjet);
   fChain->SetBranchAddress("jet5_VBF_z", &jet5_VBF_z, &b_jet5_VBF_z);
   fChain->SetBranchAddress("genjet5_VBF_pt", &genjet5_VBF_pt, &b_genjet5_VBF_pt);
   fChain->SetBranchAddress("genjet5_VBF_eta", &genjet5_VBF_eta, &b_genjet5_VBF_eta);
   fChain->SetBranchAddress("genjet5_VBF_phi", &genjet5_VBF_phi, &b_genjet5_VBF_phi);
   fChain->SetBranchAddress("genjet5_VBF_e", &genjet5_VBF_e, &b_genjet5_VBF_e);
   fChain->SetBranchAddress("top_Wc_bclose_mass", &top_Wc_bclose_mass, &b_top_Wc_bclose_mass);
   fChain->SetBranchAddress("top_Wc_bcentral_mass", &top_Wc_bcentral_mass, &b_top_Wc_bcentral_mass);
   fChain->SetBranchAddress("top_Wc_bforward_mass", &top_Wc_bforward_mass, &b_top_Wc_bforward_mass);
   fChain->SetBranchAddress("top_Wf_bclose_mass", &top_Wf_bclose_mass, &b_top_Wf_bclose_mass);
   fChain->SetBranchAddress("top_Wf_bcentral_mass", &top_Wf_bcentral_mass, &b_top_Wf_bcentral_mass);
   fChain->SetBranchAddress("top_Wf_bforward_mass", &top_Wf_bforward_mass, &b_top_Wf_bforward_mass);
   fChain->SetBranchAddress("top_Wmass_bclose_mass", &top_Wmass_bclose_mass, &b_top_Wmass_bclose_mass);
   fChain->SetBranchAddress("top_Wjj_b_mass", &top_Wjj_b_mass, &b_top_Wjj_b_mass);
   fChain->SetBranchAddress("top_Wjj_bclose_mass", &top_Wjj_bclose_mass, &b_top_Wjj_bclose_mass);
   fChain->SetBranchAddress("BDT_channel", &BDT_channel, &b_BDT_channel);
   fChain->SetBranchAddress("tauH_MET_pt", &tauH_MET_pt, &b_tauH_MET_pt);
   fChain->SetBranchAddress("dau2_MET_deltaEta", &dau2_MET_deltaEta, &b_dau2_MET_deltaEta);
   fChain->SetBranchAddress("bH_MET_deltaEta", &bH_MET_deltaEta, &b_bH_MET_deltaEta);
   fChain->SetBranchAddress("bH_MET_deltaR", &bH_MET_deltaR, &b_bH_MET_deltaR);
   fChain->SetBranchAddress("bH_tauH_MET_deltaR", &bH_tauH_MET_deltaR, &b_bH_tauH_MET_deltaR);
   fChain->SetBranchAddress("ditau_deltaR_per_tauH_MET_pt", &ditau_deltaR_per_tauH_MET_pt, &b_ditau_deltaR_per_tauH_MET_pt);
   fChain->SetBranchAddress("p_zeta", &p_zeta, &b_p_zeta);
   fChain->SetBranchAddress("p_zeta_visible", &p_zeta_visible, &b_p_zeta_visible);
   fChain->SetBranchAddress("mT_tauH_MET", &mT_tauH_MET, &b_mT_tauH_MET);
   fChain->SetBranchAddress("mT_tauH_SVFIT_MET", &mT_tauH_SVFIT_MET, &b_mT_tauH_SVFIT_MET);
   fChain->SetBranchAddress("mT_total", &mT_total, &b_mT_total);
   fChain->SetBranchAddress("BDT_ditau_deltaPhi", &BDT_ditau_deltaPhi, &b_m_BDT_ditau_deltaPhi);
   fChain->SetBranchAddress("BDT_dib_abs_deltaPhi", &BDT_dib_abs_deltaPhi, &b_BDT_dib_abs_deltaPhi);
   fChain->SetBranchAddress("BDT_dib_deltaPhi", &BDT_dib_deltaPhi, &b_BDT_dib_deltaPhi);
   fChain->SetBranchAddress("BDT_dau1MET_deltaPhi", &BDT_dau1MET_deltaPhi, &b_BDT_dau1MET_deltaPhi);
   fChain->SetBranchAddress("BDT_tauHsvfitMet_abs_deltaPhi", &BDT_tauHsvfitMet_abs_deltaPhi, &b_BDT_tauHsvfitMet_abs_deltaPhi);
   fChain->SetBranchAddress("BDT_tauHsvfitMet_deltaPhi", &BDT_tauHsvfitMet_deltaPhi, &b_BDT_tauHsvfitMet_deltaPhi);
   fChain->SetBranchAddress("BDT_bHMet_deltaPhi", &BDT_bHMet_deltaPhi, &b_BDT_bHMet_deltaPhi);
   fChain->SetBranchAddress("BDT_HHsvfit_abs_deltaPhi", &BDT_HHsvfit_abs_deltaPhi, &b_BDT_HHsvfit_abs_deltaPhi);
   fChain->SetBranchAddress("BDT_HT20", &BDT_HT20, &b_BDT_HT20);
   fChain->SetBranchAddress("BDT_topPairMasses", &BDT_topPairMasses, &b_BDT_topPairMasses);
   fChain->SetBranchAddress("BDT_MX", &BDT_MX, &b_BDT_MX);
   fChain->SetBranchAddress("BDT_bH_tauH_MET_InvMass", &BDT_bH_tauH_MET_InvMass, &b_BDT_bH_tauH_MET_InvMass);
   fChain->SetBranchAddress("BDT_bH_tauH_SVFIT_InvMass", &BDT_bH_tauH_SVFIT_InvMass, &b_BDT_bH_tauH_SVFIT_InvMass);
   fChain->SetBranchAddress("BDT_bH_tauH_InvMass", &BDT_bH_tauH_InvMass, &b_BDT_bH_tauH_InvMass);
   fChain->SetBranchAddress("BDT_total_CalcPhi", &BDT_total_CalcPhi, &b_BDT_total_CalcPhi);
   fChain->SetBranchAddress("BDT_ditau_CalcPhi", &BDT_ditau_CalcPhi, &b_BDT_ditau_CalcPhi);
   fChain->SetBranchAddress("BDT_dib_CalcPhi", &BDT_dib_CalcPhi, &b_BDT_dib_CalcPhi);
   fChain->SetBranchAddress("BDT_MET_tauH_SVFIT_cosTheta", &BDT_MET_tauH_SVFIT_cosTheta, &b_BDT_MET_tauH_SVFIT_cosTheta);
   fChain->SetBranchAddress("BDT_MET_bH_cosTheta", &BDT_MET_bH_cosTheta, &b_BDT_MET_bH_cosTheta);
   fChain->SetBranchAddress("BDT_b1_bH_cosTheta", &BDT_b1_bH_cosTheta, &b_BDT_b1_bH_cosTheta);
   fChain->SetBranchAddress("BDT_tauH_SVFIT_reson_cosTheta", &BDT_tauH_SVFIT_reson_cosTheta, &b_BDT_tauH_SVFIT_reson_cosTheta);
   fChain->SetBranchAddress("VBFjj_dEtaSign", &VBFjj_dEtaSign, &b_VBFjj_dEtaSign);
   fChain->SetBranchAddress("VBFjet2_PUjetID", &VBFjet2_PUjetID, &b_VBFjet2_PUjetID);
   fChain->SetBranchAddress("bH_VBF1_deltaEta", &bH_VBF1_deltaEta, &b_bH_VBF1_deltaEta);
   fChain->SetBranchAddress("dib_dEtaSign", &dib_dEtaSign, &b_dib_dEtaSign);
   fChain->SetBranchAddress("isTau1real", &isTau1real, &b_isTau1real);
   fChain->SetBranchAddress("isTau2real", &isTau2real, &b_isTau2real);
   fChain->SetBranchAddress("nRealTaus", &nRealTaus, &b_nRealTaus);
   fChain->SetBranchAddress("BDToutSM_kl_1", &BDToutSM_kl_1, &b_BDToutSM_kl_1);
   if (fChain->GetListOfBranches()->FindObject("DNN_VBFvsGGF_MuTau"))    
     fChain->SetBranchAddress("DNN_VBFvsGGF_MuTau", &DNN_VBFvsGGF_MuTau, &b_DNN_VBFvsGGF_MuTau);
   if (fChain->GetListOfBranches()->FindObject("DNN_VBFvsGGF_ETau"))    
     fChain->SetBranchAddress("DNN_VBFvsGGF_ETau", &DNN_VBFvsGGF_ETau, &b_DNN_VBFvsGGF_ETau);
   if (fChain->GetListOfBranches()->FindObject("DNN_VBFvsGGF_TauTau"))    
     fChain->SetBranchAddress("DNN_VBFvsGGF_TauTauTight", &DNN_VBFvsGGF_TauTauTight, &b_DNN_VBFvsGGF_TauTauTight);
   if (fChain->GetListOfBranches()->FindObject("DNN_VBFvsGGF_MuTau"))    
     fChain->SetBranchAddress("DNN_VBFvsGGF_TauTauLoose", &DNN_VBFvsGGF_TauTauLoose, &b_DNN_VBFvsGGF_TauTauLoose);
   Notify();
}

Bool_t analysisCode::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void analysisCode::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t analysisCode::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef analysisCode_cxx

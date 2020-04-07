#define analysisCode_cxx
#include "analysisCode.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "vector"
#include "map"
#include <fstream>
#include <unistd.h>
#include <string>
#include <sys/stat.h>




void analysisCode::Loop()
{
   if (fChain == 0) return;
   Book();
   Long64_t nentries = fChain->GetEntries();
   std::cout << "Total entries = " << nentries << endl;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      if (jentry == 1000000) break;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      if(jentry % 100 == 0)
        std::cout << "[analysisCode::Loop] processed : "
        << jentry << " entries\r" << std::flush;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      Fill();
   }
   std::cout << std::endl;
   EndJob();
}


void analysisCode::Book()
{

  //std::vector <std::string> categories = {""};
  std::vector <std::string> categories = {"noSelection","baseline","s1b1jresolvedMcut", "s2b0jresolvedMcut", "VBFtight_DNN", "VBFloose_DNN", "sboostedLLMcut", "VBFloose", "VBFtight"};

  m_outFile.cd();

  for (auto & cat : categories) {
    for (int i = 1; i<=2; i++) {
      m_plots["tau" + std::to_string(i) + "pt" + cat]    = new TH1F(("tau" + std::to_string(i) + "_pt_"+ cat).c_str(), ("tau" + std::to_string(i) + "_pt; tau" + std::to_string(i) + " pt(GeV); Entries").c_str(), 200, 0, 200); 
      m_plots["tau" + std::to_string(i) + "eta" + cat]    = new TH1F(("tau" + std::to_string(i) + "_eta_"+ cat).c_str(), ("tau" + std::to_string(i) + "_eta; tau" + std::to_string(i) + " eta; Entries").c_str(), 100, -2.5, 2.5); 
      m_plots["tau" + std::to_string(i) + "iso" + cat]    = new TH1F(("tau" + std::to_string(i) + "_iso_"+ cat).c_str(), ("tau" + std::to_string(i) + "_iso; tau" + std::to_string(i) + " iso; Entries").c_str(), 100, -0.1, 1.1); 
      m_plots["tau" + std::to_string(i) + "z" + cat]    = new TH1F(("tau" + std::to_string(i) + "_z_"+ cat).c_str(), ("tau" + std::to_string(i) + "_z; tau" + std::to_string(i) + " z; Entries").c_str(), 100, -5, 5);

      m_plots["bjet" + std::to_string(i) + "pt" + cat]    = new TH1F(("bjet" + std::to_string(i) + "_pt_"+ cat).c_str(), ("bjet" + std::to_string(i) + "_pt; bjet" + std::to_string(i) + " pt(GeV); Entries").c_str(), 200, 0, 200); 
      m_plots["bjet" + std::to_string(i) + "eta" + cat]    = new TH1F(("bjet" + std::to_string(i) + "_eta_"+ cat).c_str(), ("bjet" + std::to_string(i) + "_eta; bjet" + std::to_string(i) + " eta; Entries").c_str(), 100, -2.5, 2.5); 
      m_plots["bjet" + std::to_string(i) + "z" + cat]    = new TH1F(("bjet" + std::to_string(i) + "_z_"+ cat).c_str(), ("bjet" + std::to_string(i) + "_z; bjet" + std::to_string(i) + " z; Entries").c_str(), 100, -5, 5);

      m_plots["additionalJet" + std::to_string(i) + "pt" + cat]    = new TH1F(("additionalJet" + std::to_string(i) + "_pt_"+ cat).c_str(), ("additionalJet" + std::to_string(i) + "_pt; additionalJet" + std::to_string(i) + " pt(GeV); Entries").c_str(), 200, 0, 200); 
      m_plots["additionalJet" + std::to_string(i) + "eta" + cat]    = new TH1F(("additionalJet" + std::to_string(i) + "_eta_"+ cat).c_str(), ("additionalJet" + std::to_string(i) + "_eta; additionalJet" + std::to_string(i) + " eta; Entries").c_str(), 100, -2.5, 2.5); 
      m_plots["additionalJet" + std::to_string(i) + "z" + cat]    = new TH1F(("additionalJet" + std::to_string(i) + "_z_"+ cat).c_str(), ("additionalJet" + std::to_string(i) + "_z; additionalJet" + std::to_string(i) + " z; Entries").c_str(), 100, -5, 5);
     
      m_plots["VBFjet" + std::to_string(i) + "pt" + cat]    = new TH1F(("VBFjet" + std::to_string(i) + "_pt_"+ cat).c_str(), ("VBFjet" + std::to_string(i) + "_pt; VBFjet" + std::to_string(i) + " pt(GeV); Entries").c_str(), 200, 0, 200); 
      m_plots["VBFjet" + std::to_string(i) + "eta" + cat]    = new TH1F(("VBFjet" + std::to_string(i) + "_eta_"+ cat).c_str(), ("VBFjet" + std::to_string(i) + "_eta; VBFjet" + std::to_string(i) + " eta; Entries").c_str(), 100, -2.5, 2.5); 
      m_plots["VBFjet" + std::to_string(i) + "phi" + cat]    = new TH1F(("VBFjet" + std::to_string(i) + "_phi_"+ cat).c_str(), ("VBFjet" + std::to_string(i) + "_phi; VBFjet" + std::to_string(i) + " phi; Entries").c_str(), 100, -3.5, 3.5); 
      m_plots["VBFjet" + std::to_string(i) + "z" + cat]    = new TH1F(("VBFjet" + std::to_string(i) + "_z_"+ cat).c_str(), ("VBFjet" + std::to_string(i) + "_z; VBFjet" + std::to_string(i) + " z; Entries").c_str(), 100, -5, 5);

    }

    m_plots["bjets_deltaEta"+ cat]    = new TH1F(("bjets_deltaEta_"+ cat).c_str(), "bjets_deltaEta; bjets_deltaEta ; Entries", 100, -0, 10); 
    m_plots["bjets_eta1eta2"+ cat]    = new TH1F(("bjets_eta1eta2_"+ cat).c_str(), "bjets_eta1eta2; bjets eta1#times eta2 ; Entries", 100, -10, 10); 

    m_plots["VBFjj_deltaEta"+ cat]    = new TH1F(("VBFjj_deltaEta_"+ cat).c_str(), "VBFjj_deltaEta; VBFjj_deltaEta ; Entries", 100, -0, 10); 
    m_plots["VBFjj_eta1eta2"+ cat]    = new TH1F(("VBFjj_eta1eta2_"+ cat).c_str(), "VBFjj_eta1eta2; VBFjj eta1#times eta2 ; Entries", 100, -10, 10); 

    m_plots["additionalJets_deltaEta"+ cat]    = new TH1F(("additionalJets_deltaEta_"+ cat).c_str(), "additionalJets_deltaEta; additionalJets_deltaEta ; Entries", 100, -0, 10); 
    m_plots["additionalJets_eta1eta2"+ cat]    = new TH1F(("additionalJets_eta1eta2_"+ cat).c_str(), "additionalJets_eta1eta2; additionalJets eta1#times eta2 ; Entries", 100, -10, 10); 
    m_plots["additionalJets_mass"+ cat]    = new TH1F(("additionalJets_mass_"+ cat).c_str(), "additionalJets_mass; additionalJets_mass ; Entries", 100, 0, 1000); 
    
    m_plots["additionalVBFjet" + std::to_string(1) + "pt" + cat]  = new TH1F(("additionalVBFjet" + std::to_string(1) + "_pt_"+ cat).c_str(), ("additionalVBFjet" + std::to_string(1) + "_pt; VBFjet" + std::to_string(1) + " pt(GeV); Entries").c_str(), 200, 0, 200); 
    m_plots["additionalVBFjet" + std::to_string(1) + "eta" + cat] = new TH1F(("additionalVBFjet" + std::to_string(1) + "_eta_"+ cat).c_str(), ("additionalVBFjet" + std::to_string(1) + "_eta; VBFjet" + std::to_string(1) + " eta; Entries").c_str(), 100, -2.5, 2.5);    
    m_plots["additionalVBFjet" + std::to_string(1) + "z" + cat]   = new TH1F(("additionalVBFjet" + std::to_string(1) + "_z_"+ cat).c_str(), ("additionalVBFjet" + std::to_string(1) + "_z; VBFjet" + std::to_string(1) + " z; Entries").c_str(), 100, -5, 5);

    m_plots["HH_mass"+ cat]   = new TH1F(("HH_mass_"+ cat).c_str(), "HH mass; HH Mass (GeV); Entries", 100, 0, 2000); 
    m_plots["HH_eta"+ cat]    = new TH1F(("HH_eta_"+ cat).c_str(), "HH eta; HH eta; Entries", 100, -2.5, 2.5); 
    m_plots["HH_phi"+ cat]    = new TH1F(("HH_phi_"+ cat).c_str(), "HH phi; HH phi; Entries", 100, -3.5, 3.5); 
    m_plots["HH_pt"+ cat]   = new TH1F(("HH_pt_"+ cat).c_str(), "HH pt; HH pt (GeV); Entries", 100, 0, 500); 
    m_plots["HH_z"+ cat]   = new TH1F(("HH_z_"+ cat).c_str(), "HH z; HH z; Entries", 100, -5, 5); 
    m_plots["HH_AHH"+ cat]   = new TH1F(("HH_AHH_"+ cat).c_str(), "HH AHH; HH AHH; Entries", 100, -0.1, 1.1); 
  
    m_plots["HH_deltaPhi"+ cat] = new TH1F(("HH_deltaPhi_"+ cat).c_str(), "HH_deltaPhi; HH_deltaPhi ; Entries", 100, -0.5, 3.5);
    m_plots["HH_deltaEta"+ cat]    = new TH1F(("HH_deltaEta_"+ cat).c_str(), "HH_deltaEta; HH_deltaEta ; Entries", 100, -0.5, 10); 
    m_plots["HH_deltaR"+ cat]    = new TH1F(("HH_deltaR_"+ cat).c_str(), "HH_deltaR; HH_deltaR ; Entries", 100, 0, 10); 

    m_plots["HHsvfit_mass"+ cat]   = new TH1F(("HHsvfit_mass_"+ cat).c_str(), "HH mass; HH Mass (GeV); Entries", 100, 0, 2000); 
    m_plots["HHsvfit_eta"+ cat]    = new TH1F(("HHsvfit_eta_"+ cat).c_str(), "HH eta; HH eta; Entries", 100, -2.5, 2.5); 
    m_plots["HHsvfit_phi"+ cat]    = new TH1F(("HHsvfit_phi_"+ cat).c_str(), "HH phi; HH phi; Entries", 100, -3.5, 3.5); 
    m_plots["HHsvfit_pt"+ cat]   = new TH1F(("HHsvfit_pt_"+ cat).c_str(), "HH pt; HH pt (GeV); Entries", 100, 0, 500); 
    m_plots["HHsvfit_deltaPhi"+ cat] = new TH1F(("HHsvfit_deltaPhi_"+ cat).c_str(), "HH_deltaPhi; HH_deltaPhi ; Entries", 100, -0.5, 3.5);
  
    m_plots["HHKin_mass_raw"+ cat]   = new TH1F(("HHKin_mass_raw_"+ cat).c_str(), "HHKin mass; HHKin Mass (GeV); Entries", 100, 0, 2000); 
    m_plots["HHkinsvfit_mass"+ cat]   = new TH1F(("HHkinsvfit_mass_"+ cat).c_str(), "HH mass; HH Mass (GeV); Entries", 100, 0, 500); 
    m_plots["HHkinsvfit_eta"+ cat]    = new TH1F(("HHkinsvfit_eta_"+ cat).c_str(), "HH eta; HH eta; Entries", 100, -2.5, 2.5); 
    m_plots["HHkinsvfit_phi"+ cat]    = new TH1F(("HHkinsvfit_phi_"+ cat).c_str(), "HH phi; HH phi; Entries", 100, -6.5, 6.5); 
    m_plots["HHkinsvfit_pt"+ cat]   = new TH1F(("HHkinsvfit_pt_"+ cat).c_str(), "HH pt; HH pt (GeV); Entries", 100, 0, 500); 
    m_plots["HHkinsvfit_bHmass"+ cat]   = new TH1F(("HHkinsvfit_bHmass_"+ cat).c_str(), "bH mass; bH Mass (GeV); Entries", 100, 0, 250); 
    m_plots["HHKin_chi2"+ cat] = new TH1F(("HHKin_chi2_"+ cat).c_str(), "HHKin chi2; HHKin_chi2; Entries", 100, -0.5, 10); 
  
    m_plots["tauH_mass"+ cat] = new TH1F(("tauH_mass_"+ cat).c_str(), "tauH mass; tauH Mass (GeV); Entries", 100, 0, 250); 
    m_plots["tauH_pt"+ cat]   = new TH1F(("tauH_pt_"+ cat).c_str(), "tauH pt; tauH pt (GeV); Entries", 100, 0, 500); 
    m_plots["tauH_eta"+ cat]  = new TH1F(("tauH_eta_"+ cat).c_str(), "tauH eta; tauH eta ; Entries", 100, -2.5, 2.5); 
    m_plots["tauH_phi"+ cat]  = new TH1F(("tauH_phi_"+ cat).c_str(), "tauH phi; tauH phi ; Entries", 100, -3.5, 3.5); 
    m_plots["tauH_z"+ cat]  = new TH1F(("tauH_z_"+ cat).c_str(), "tauH z; tauH z ; Entries", 100, -0.1, 1.1); 
  
    m_plots["tauH_SVFIT_mass"+ cat] = new TH1F(("tauH_SVFIT_mass_"+ cat).c_str(), "tauH SVFIT mass; tauH Mass (GeV); Entries", 100, 0, 250); 
    m_plots["tauH_SVFIT_pt"+cat]   = new TH1F(("tauH_SVFIT_pt_"+ cat).c_str(), "tauH SVFIT pt; tauH pt (GeV); Entries", 100, 0, 500); 
    m_plots["tauH_SVFIT_eta"+cat]  = new TH1F(("tauH_SVFIT_eta_"+ cat).c_str(), "tauH SVFIT eta; tauH eta ; Entries", 100, -2.5, 2.5); 
    m_plots["tauH_SVFIT_phi"+cat]  = new TH1F(("tauH_SVFIT_phi_"+ cat).c_str(), "tauH SVFIT phi; tauH phi ; Entries", 100, -3.5, 3.5); 
  
  
    m_plots["bH_mass"+ cat]   = new TH1F(("bH_mass_"+ cat).c_str(), "bH mass; bH Mass (GeV); Entries", 100, 0, 250); 
    m_plots["bH_pt"+ cat]     = new TH1F(("bH_pt_"+ cat).c_str(), "bH pt (GeV); bH pt (GeV); Entries", 100, 0, 500); 
    m_plots["bH_eta"+ cat]    = new TH1F(("bH_eta_"+ cat).c_str(), "bH eta; bH eta ; Entries", 100, -2.5, 2.5); 
    m_plots["bH_phi"+ cat]    = new TH1F(("bH_phi_"+ cat).c_str(), "bH phi; bH phi ; Entries", 100, -3.5, 3.5); 
    m_plots["bH_z"+ cat]      = new TH1F(("bH_z_"+ cat).c_str(), "bH z; bH z ; Entries", 100, -0.1, 1.1); 
    
    m_plots["VBFjj_mass"+ cat] = new TH1F(("VBFjj_mass_"+ cat).c_str(), "VBFjj mass; VBFjj Mass (GeV); Entries", 100, 0, 2000); 
    m_plots["VBFjj_HT"+ cat] = new TH1F(("VBFjj_HT_"+ cat).c_str(), "VBFjj HT; VBFjj HT (GeV); Entries", 100, 0, 500); 
    m_plots["VBFjj_deltaPhi"+ cat]    = new TH1F(("VBFjj_deltaPhi_"+ cat).c_str(), "VBFjj_deltaPhi; VBFjj_deltaPhi ; Entries", 70, -3.5, 3.5); 
    m_plots["VBFjj_deltaR"+ cat]    = new TH1F(("VBFjj_deltaR_"+ cat).c_str(), "VBFjj_deltaR; VBFjj_deltaR ; Entries", 100, 0, 10); 
    m_plots["VBFgenjj_deltaPhi"+ cat]    = new TH1F(("VBFgenjj_deltaPhi_"+ cat).c_str(), "VBFgenjj_deltaPhi; VBFgenjj_deltaPhi ; Entries", 70, -3.5, 3.5); 
  
    m_plots["VBFjTau_deltaR"+ cat]    = new TH1F(("VBFjTau_deltaR_"+ cat).c_str(), "VBFjTau_deltaR; VBFjTau_deltaR ; Entries", 100, 0, 10); 
    m_plots["VBFjb_deltaR"+ cat]    = new TH1F(("VBFjb_deltaR_"+ cat).c_str(), "VBFjb_deltaR; VBFjb_deltaR ; Entries", 100, 0, 10); 

    
    // SOME OF GILES' VARIABLES
    m_plots["dR_hbb_sv"+ cat]    = new TH1F(("dR_hbb_sv_"+ cat).c_str(), "dR_hbb_tauH_SVFIT; dR_hbb_tauH_SVFIT ; Entries", 100, 0, 10);
    m_plots["dR_l1_l2_x_sv_pT"+ cat]    = new TH1F(("dR_l1_l2_x_sv_pT_"+ cat).c_str(), "dR_l1_l2 * tauH_SVFIT_pT; dR_l1_l2 * tauH_SVFIT_pT ; Entries", 100, 0, 1000);
    m_plots["dphi_sv_met"+ cat]    = new TH1F(("dphi_sv_met_"+ cat).c_str(), "dphi_sv_met; dphi_sv_met ; Entries", 100, -3.5, 3.5);
    m_plots["dR_l1_l2_boosted_htt_met"+ cat]    = new TH1F(("dR_l1_l2_boosted_htt_met_"+ cat).c_str(), "dR_l1_l2_boosted_htt_met; dR_l1_l2_boosted_htt_met; Entries", 100, 0, 10);
    m_plots["dphi_hbb_sv"+ cat]    = new TH1F(("dphi_hbb_sv_"+ cat).c_str(), "dphi_hbb_sv; dphi_hbb_sv; Entries", 100, -3.5, 3.5);
    m_plots["deta_b1_b2"+ cat]    = new TH1F(("deta_b1_b2_"+ cat).c_str(), "deta_b1_b2; deta_b1_b2 ; Entries", 100, -0.5, 10);
    m_plots["costheta_l2_htt"+ cat]    = new TH1F(("costheta_l2_htt_"+ cat).c_str(), "costheta_l2_htt; costheta_l2_htt; Entries", 100, -1.1, 1.1);
    m_plots["dphi_l1_met"+ cat]    = new TH1F(("dphi_l1_met_"+ cat).c_str(), "dphi_l1_met; dphi_l1_met; Entries", 100, -3.5, 3.5);
    m_plots["costheta_htt_hh_met"+ cat]    = new TH1F(("costheta_htt_hh_met_"+ cat).c_str(), "costheta_htt_hh_met; costheta_htt_hh_met; Entries", 100, -1.1, 1.1);
    m_plots["dR_hbb_httmet"+ cat]    = new TH1F(("dR_hbb_httmet_"+ cat).c_str(), "dR_hbb_httmet; dR_hbb_httmet ; Entries", 100, 0, 10);
    m_plots["costheta_b1_hbb"+ cat]    = new TH1F(("costheta_b1_hbb_"+ cat).c_str(), "costheta_b1_hbb; costheta_b1_hbb; Entries", 100, -1.1, 1.1);
    m_plots["deta_hbb_httmet"+ cat]    = new TH1F(("deta_hbb_httmet_"+ cat).c_str(), "deta_hbb_httmet; deta_hbb_httmet; Entries", 100, -0.5, 10);
    m_plots["costheta_met_htt"+ cat]    = new TH1F(("costheta_met_htt_"+ cat).c_str(), "costheta_met_htt; costheta_met_htt; Entries", 100, -1.1, 1.1);
    m_plots["boosted"+ cat]    = new TH1F(("boosted_"+ cat).c_str(), "boosted; boosted; Entries", 3, -1.5, 1.5);
    m_plots["channel"+ cat]    = new TH1F(("channel_"+ cat).c_str(), "channel / pairType; channel; Entries", 5, -0.5, 4.5);


     








  }
}

void analysisCode::Fill()
{

  std::vector <std::string> categories = addCategories();
  categories.push_back("noSelection");

  for (auto & cat : categories ) {

    //Fill tau plots
    m_plots["tau1pt"+cat]->Fill(dau1_pt);
    m_plots["tau2pt"+cat]->Fill(dau2_pt);
    m_plots["tau1eta"+cat]->Fill(dau1_eta);
    m_plots["tau2eta"+cat]->Fill(dau2_eta);
    m_plots["tau1iso"+cat]->Fill(dau1_iso);
    m_plots["tau2iso"+cat]->Fill(dau2_iso);
    m_plots["tau1z"+cat]->Fill(getCentrality(dau1_eta));
    m_plots["tau2z"+cat]->Fill(getCentrality(dau2_eta));
    
    // Fill b plots
    if (bjet1_pt != -1) m_plots["bjet1pt"+cat]->Fill(bjet1_pt);
    if (bjet2_pt != -1) m_plots["bjet2pt"+cat]->Fill(bjet2_pt);
    if (bjet1_pt != -1) m_plots["bjet1eta"+cat]->Fill(bjet1_eta);
    if (bjet2_pt != -1) m_plots["bjet2eta"+cat]->Fill(bjet2_eta);
    if (bjet1_pt != -1) m_plots["bjet1z"+cat]->Fill(getCentrality(bjet1_eta));
    if (bjet2_pt != -1) m_plots["bjet2z"+cat]->Fill(getCentrality(bjet2_eta));
    if (bjet1_pt != -1 && bjet2_pt != -1) m_plots["bjets_deltaEta"+cat]->Fill(std::fabs(bjet1_eta - bjet2_eta));
    if (bjet1_pt != -1 && bjet2_pt != -1) m_plots["bjets_eta1eta2"+cat]->Fill(bjet1_eta * bjet2_eta);
    
    // Fill VBFjet plots
    if (VBFjet1_pt!=-999.) m_plots["VBFjet1pt"+cat]->Fill(VBFjet1_pt);
    if (VBFjet2_pt!=-999.) m_plots["VBFjet2pt"+cat]->Fill(VBFjet2_pt);
    if (VBFjet1_pt!=-999.) m_plots["VBFjet1eta"+cat]->Fill(VBFjet1_eta);
    if (VBFjet2_pt!=-999.) m_plots["VBFjet2eta"+cat]->Fill(VBFjet2_eta);
    if (VBFjet1_pt!=-999.) m_plots["VBFjet1z"+cat]->Fill(getCentrality(VBFjet1_eta));
    if (VBFjet2_pt!=-999.) m_plots["VBFjet2z"+cat]->Fill(getCentrality(VBFjet2_eta));
    if (VBFjet1_pt!=-999. && VBFjet2_pt!=-999.) m_plots["VBFjj_deltaEta"+cat]->Fill(VBFjj_deltaEta);
    if (VBFjet1_pt!=-999. && VBFjet2_pt!=-999.) m_plots["VBFjj_eta1eta2"+cat]->Fill(VBFjet1_eta*VBFjet2_eta);
    if (VBFjj_mass!=-999.) m_plots["VBFjj_mass"+cat]->Fill(VBFjj_mass);

    // Fill additional b plots
    if (jet3_pt!=-999.) m_plots["additionalJet1pt"+cat]->Fill(jet3_pt);
    if (jet4_pt!=-999.) m_plots["additionalJet2pt"+cat]->Fill(jet4_pt);
    if (jet3_pt!=-999.) m_plots["additionalJet1eta"+cat]->Fill(jet3_eta);
    if (jet4_pt!=-999.) m_plots["additionalJet2eta"+cat]->Fill(jet4_eta);
    if (jet3_pt!=-999.) m_plots["additionalJet1z"+cat]->Fill(getCentrality(jet3_eta));
    if (jet4_pt!=-999.) m_plots["additionalJet2z"+cat]->Fill(getCentrality(jet4_eta));
    if (jet3_pt!=-999. && jet4_pt!=-999.) m_plots["additionalJets_deltaEta"+cat]->Fill(jj_deltaEta);
    if (jet3_pt!=-999. && jet4_pt!=-999.) m_plots["additionalJets_eta1eta2"+cat]->Fill(jet3_eta*jet4_eta);
    if (jj_mass!=-999.) m_plots["additionalJets_mass"+cat]->Fill(jj_mass);

    // Fill additional VBFjet
    if (jet5_VBF_pt!=-999.) m_plots["additionalVBFjet1pt"+cat]->Fill(jet5_VBF_pt);
    if (jet5_VBF_pt!=-999.) m_plots["additionalVBFjet1eta"+cat]->Fill(jet5_VBF_eta);
    if (jet5_VBF_pt!=-999.) m_plots["additionalVBFjet1z"+cat]->Fill(getCentrality(jet5_VBF_eta));


    if (HH_eta != -1. && HH_phi != -1. && HH_pt != -1.) { 
      m_plots["HH_mass"+cat]->Fill( HH_mass );
      m_plots["HH_eta"+cat]->Fill( HH_eta );
      m_plots["HH_phi"+cat]->Fill( HH_phi );
      m_plots["HH_pt"+cat]->Fill( HH_pt );
      m_plots["HH_z"+cat]->Fill( getHHCentrality());
      m_plots["HH_AHH"+cat]->Fill( getAHH());
    } else {
      //m_plots["HH_mass"]->Fill( -999. );
      //m_plots["HH_eta"]->Fill( -999. );
      //m_plots["HH_phi"]->Fill( -999. );
      //m_plots["HH_pt"]->Fill( -999. );
    }
    if (HHKin_mass_raw != 0.) m_plots["HHKin_mass_raw"+cat]->Fill( HHKin_mass_raw );
    //else m_plots["HHKin_mass_raw"]->Fill( -999. );
  
    m_plots["HHKin_chi2"+cat]->Fill(HHKin_chi2);
   
    if (HHsvfit_eta != -1. && HHsvfit_phi != -1. && HHsvfit_pt != -1.) { 
      m_plots["HHsvfit_mass"+cat]->Fill( HHsvfit_mass );
      m_plots["HHsvfit_eta"+cat]->Fill( HHsvfit_eta );
      m_plots["HHsvfit_phi"+cat]->Fill( HHsvfit_phi );
      m_plots["HHsvfit_pt"+cat]->Fill( HHsvfit_pt );
      m_plots["HHsvfit_deltaPhi"+cat]->Fill( HHsvfit_deltaPhi );
    } else {
      //m_plots["HHsvfit_mass"]->Fill( -999. );
      //m_plots["HHsvfit_eta"]->Fill( -999. );
      //m_plots["HHsvfit_phi"]->Fill( -999. );
      //m_plots["HHsvfit_pt"]->Fill( -999. );
      //m_plots["HHsvfit_deltaPhi"]->Fill( -999. );
    }
  
    if (HHkinsvfit_eta != -1. && HHkinsvfit_phi != -1. && HHkinsvfit_pt != -1.) { 
      m_plots["HHkinsvfit_eta"+cat]->Fill( HHkinsvfit_eta );
      m_plots["HHkinsvfit_phi"+cat]->Fill( HHkinsvfit_phi );
      m_plots["HHkinsvfit_pt"+cat]->Fill( HHkinsvfit_pt );
      m_plots["HHkinsvfit_bHmass"+cat]->Fill( HHkinsvfit_bHmass );
    } else {
      //m_plots["HHkinsvfit_eta"]->Fill( -999. );
      //m_plots["HHkinsvfit_phi"]->Fill( -999. );
      //m_plots["HHkinsvfit_pt"]->Fill( -999. );
      //m_plots["HHkinsvfit_bHmass"]->Fill( -999. );
    }
  
    if (HH_deltaPhi != -1. && HH_deltaEta != -1. && HH_deltaR != -1.) { 
      m_plots["HH_deltaPhi"+cat]->Fill( HH_deltaPhi );
      m_plots["HH_deltaEta"+cat]->Fill( HH_deltaEta );
      m_plots["HH_deltaR"+cat]->Fill( HH_deltaR );
    } else {
    //m_plots["HH_deltaPhi"]->Fill( -999. );
    //m_plots["HH_deltaEta"]->Fill( -999. );
    //m_plots["HH_deltaR"]->Fill( -999. );
    }
  
  
    if (tauH_mass != -1. && tauH_pt != -1 && tauH_eta!=-1 ) {
      m_plots["tauH_mass"+cat]->Fill( tauH_mass );
      m_plots["tauH_pt"+cat]->Fill( tauH_pt );
      m_plots["tauH_eta"+cat]->Fill( tauH_eta );
      m_plots["tauH_phi"+cat]->Fill( tauH_phi );
      m_plots["tauH_z"+cat]->Fill( getCentrality(tauH_eta) );
    } else {
      //m_plots["tauH_mass"]->Fill( -999. );
      //m_plots["tauH_pt"]->Fill( -999. );
      //m_plots["tauH_eta"]->Fill( -999. );
      //m_plots["tauH_phi"]->Fill( -999. );
    }
 
    if (tauH_SVFIT_mass != -1. && tauH_SVFIT_pt != -1 && tauH_SVFIT_eta!=-1 ) {
      m_plots["tauH_SVFIT_mass"+cat]->Fill( tauH_SVFIT_mass );
      m_plots["tauH_SVFIT_pt"+cat]->Fill( tauH_SVFIT_pt );
      m_plots["tauH_SVFIT_eta"+cat]->Fill( tauH_SVFIT_eta );
      m_plots["tauH_SVFIT_phi"+cat]->Fill( tauH_SVFIT_phi );
    } else {
      //m_plots["tauH_SVFIT_mass"]->Fill( -999. );
      //m_plots["tauH_SVFIT_pt"]->Fill( -999. );
      //m_plots["tauH_SVFIT_eta"]->Fill( -999. );
      //m_plots["tauH_SVFIT_phi"]->Fill( -999. );
    }

    if (bH_mass != -1. && bH_pt != -1. && bH_eta!=-1. ) {
      m_plots["bH_mass"+cat]->Fill( bH_mass );
      m_plots["bH_pt"+cat]->Fill( bH_pt );
      m_plots["bH_eta"+cat]->Fill( bH_eta );
      m_plots["bH_phi"+cat]->Fill( bH_phi );
      m_plots["bH_z"+cat]->Fill( getCentrality(bH_eta) );
    } else {
      //m_plots["bH_mass"]->Fill( -999. );
      //m_plots["bH_pt"]->Fill( -999. );
      //m_plots["bH_eta"]->Fill( -999. );
      //m_plots["bH_phi"]->Fill( -999. );
    }
    m_plots["VBFjj_HT"+cat]->Fill(VBFjj_HT); 
  

    if (VBFjet1_phi != -999 && VBFjet2_phi != -999) { 
      m_plots["VBFjj_deltaPhi"+cat]->Fill(getDeltaPhi(VBFjet1_phi,VBFjet2_phi)); 
      m_plots["VBFjj_deltaR"+cat]->Fill( getDeltaR(VBFjet1_eta, VBFjet1_phi, VBFjet2_eta, VBFjet2_phi) ); 
    } else {
      // m_plots["VBFjj_deltaPhi"]->Fill(-999);
      // m_plots["VBFjj_deltaR"]->Fill(-999);
    }
    if (VBFgenjet1_phi != -999 && VBFgenjet2_phi != -999) m_plots["VBFgenjj_deltaPhi"+cat]->Fill(getDeltaPhi(VBFgenjet1_phi, VBFgenjet2_phi)); 
    //  else m_plots["VBFgenjj_deltaPhi"]->Fill(-999);

    // Fill VBF(j/tau) plots
    Float_t minDeltaRVBFjTau = 9999; 
    if (getDeltaR(VBFjet1_eta, VBFjet1_phi, dau1_eta, dau1_phi)!=-1) minDeltaRVBFjTau = getDeltaR(VBFjet1_eta, VBFjet1_phi, dau1_eta, dau1_phi);
    if (getDeltaR(VBFjet1_eta, VBFjet1_phi, dau2_eta, dau2_phi)!=-1 && getDeltaR(VBFjet1_eta, VBFjet1_phi, dau2_eta, dau2_phi) < minDeltaRVBFjTau) minDeltaRVBFjTau = getDeltaR(VBFjet1_eta, VBFjet1_phi, dau2_eta, dau2_phi);
    if (getDeltaR(VBFjet2_eta, VBFjet2_phi, dau1_eta, dau1_phi)!=-1 && getDeltaR(VBFjet2_eta, VBFjet2_phi, dau1_eta, dau1_phi) < minDeltaRVBFjTau) minDeltaRVBFjTau = getDeltaR(VBFjet2_eta, VBFjet2_phi, dau1_eta, dau1_phi);
    if (getDeltaR(VBFjet2_eta, VBFjet2_phi, dau2_eta, dau2_phi)!=-1 && getDeltaR(VBFjet2_eta, VBFjet2_phi, dau2_eta, dau2_phi) < minDeltaRVBFjTau) minDeltaRVBFjTau = getDeltaR(VBFjet2_eta, VBFjet2_phi, dau2_eta, dau2_phi);

    if (minDeltaRVBFjTau!=9999) m_plots["VBFjTau_deltaR"+cat]->Fill(minDeltaRVBFjTau);

    Float_t minDeltaRVBFjb = 9999; 
    if (getDeltaR(VBFjet1_eta, VBFjet1_phi, bjet1_eta, bjet1_phi)!=-1) minDeltaRVBFjb = getDeltaR(VBFjet1_eta, VBFjet1_phi, bjet1_eta, bjet1_phi);
    if (getDeltaR(VBFjet1_eta, VBFjet1_phi, bjet2_eta, bjet2_phi)!=-1 && getDeltaR(VBFjet1_eta, VBFjet1_phi, bjet2_eta, bjet2_phi) < minDeltaRVBFjTau) minDeltaRVBFjb = getDeltaR(VBFjet1_eta, VBFjet1_phi, bjet2_eta, bjet2_phi);
    if (getDeltaR(VBFjet2_eta, VBFjet2_phi, bjet1_eta, bjet1_phi)!=-1 && getDeltaR(VBFjet2_eta, VBFjet2_phi, bjet1_eta, bjet1_phi) < minDeltaRVBFjTau) minDeltaRVBFjb = getDeltaR(VBFjet2_eta, VBFjet2_phi, bjet1_eta, bjet1_phi);
    if (getDeltaR(VBFjet2_eta, VBFjet2_phi, bjet2_eta, bjet2_phi)!=-1 && getDeltaR(VBFjet2_eta, VBFjet2_phi, bjet2_eta, bjet2_phi) < minDeltaRVBFjTau) minDeltaRVBFjb = getDeltaR(VBFjet2_eta, VBFjet2_phi, bjet2_eta, bjet2_phi);

    if (minDeltaRVBFjb!=9999) m_plots["VBFjb_deltaR"+cat]->Fill(minDeltaRVBFjb);


    if (getDeltaR( bH_eta, bH_phi, tauH_SVFIT_eta, tauH_SVFIT_phi ) != -1 ) m_plots["dR_hbb_sv"+ cat] -> Fill(getDeltaR( bH_eta, bH_phi, tauH_SVFIT_eta, tauH_SVFIT_phi )); 
    if (getDeltaR( dau1_eta, dau1_phi, dau2_eta, dau2_phi ) != -1 ) m_plots["dR_l1_l2_x_sv_pT"+ cat] -> Fill( getDeltaR( dau1_eta, dau1_phi, dau2_eta, dau2_phi) * tauH_SVFIT_pt );
    m_plots["dphi_sv_met"+ cat] -> Fill ( tauHsvfitMet_deltaPhi );
 

    TLorentzVector metT, tauH_SVFIT; 
    metT.SetPtEtaPhiM(met_et, 0., met_phi, 0); 
    tauH_SVFIT.SetPtEtaPhiM(tauH_SVFIT_pt, tauH_SVFIT_eta, tauH_SVFIT_phi, tauH_SVFIT_mass); 

    LorentzVector l_1, l_2, b_1, h_bb, h_tt_vis, met, h_tt_SVFIT ; 
    l_1.SetEta(dau1_eta);  l_1.SetPhi(dau1_phi);  l_1.SetPt(dau1_pt);  l_1.SetE(dau1_e);
    l_2.SetEta(dau2_eta);  l_2.SetPhi(dau2_phi);  l_2.SetPt(dau2_pt);  l_2.SetE(dau2_e);
    b_1.SetEta(bjet1_eta);  b_1.SetPhi(bjet1_phi);  b_1.SetPt(bjet1_pt);  b_1.SetE(bjet1_e);
    h_bb.SetEta(bH_eta);  h_bb.SetPhi(bH_phi);  h_bb.SetPt(bH_pt);  h_bb.SetE(bH_e);
    h_tt_vis.SetEta(tauH_eta);  h_tt_vis.SetPhi(tauH_phi);  h_tt_vis.SetPt(tauH_pt);  h_tt_vis.SetE(tauH_e);
    h_tt_SVFIT.SetEta(tauH_SVFIT.Eta());  h_tt_SVFIT.SetPhi(tauH_SVFIT.Phi());  h_tt_SVFIT.SetPt(tauH_SVFIT.Pt());  h_tt_SVFIT.SetE(tauH_SVFIT.E());
    met.SetEta(0.);  met.SetPhi(met_phi);  met.SetPt(met_et);  met.SetE(metT.E());
    
    m_plots["dR_l1_l2_boosted_htt_met"+ cat] -> Fill ( getDeltaRboosted( l_1, l_2, h_tt_vis+met ));
    if (getDeltaPhi (tauH_SVFIT_phi, bH_phi) != -999.) m_plots["dphi_hbb_sv"+ cat] -> Fill( getDeltaPhi (tauH_SVFIT_phi, bH_phi) );
    if (getDeltaEta (bjet1_eta, bjet2_eta) != -999.) m_plots["deta_b1_b2"+ cat] -> Fill( getDeltaEta (bjet1_eta, bjet2_eta) );
    m_plots["costheta_l2_htt"+ cat] -> Fill ( getCosDelta(l_2, h_tt_SVFIT) ) ;
    m_plots["dphi_l1_met"+ cat] -> Fill(getDeltaPhi ( dau1_phi, met_phi ) );
    m_plots["costheta_htt_hh_met"+ cat] -> Fill(getCosDelta( h_tt_SVFIT,  h_tt_vis+met+h_bb ) );
    m_plots["dR_hbb_httmet"+ cat] -> Fill(getDeltaR(h_bb.Eta(), h_bb.Phi(), (h_tt_vis+met).Eta(), (h_tt_vis+met).Phi()));
    m_plots["costheta_b1_hbb"+ cat] -> Fill( getCosDelta ( b_1 , h_bb ) ); 
    m_plots["deta_hbb_httmet"+ cat] -> Fill( getDeltaEta ( h_bb.Eta(), (h_tt_vis+met).Eta() ) );
    m_plots["costheta_met_htt"+ cat] -> Fill( getCosDelta( met, h_tt_SVFIT ) );
    m_plots["boosted"+ cat] -> Fill (isBoosted);
    m_plots["channel"+ cat] -> Fill (pairType);






  }

}

void analysisCode::EndJob()
{
  m_outFile.cd();
  m_outFile.Write();
  m_outFile.Close();
}

Float_t analysisCode::getDeltaEta(Float_t eta1, Float_t eta2)
{
  if (eta1 == -999 || eta2 == -999) return -999;
  auto dEta = eta1 - eta2;
  return dEta;
}



Float_t analysisCode::getDeltaR(Float_t eta1, Float_t phi1, Float_t eta2, Float_t phi2) 
{
  if ((eta1 == -999 && phi1 == -999) || (eta2 == -999 && phi2 == -999)) return -1; 
  auto dp = std::abs(phi1 - phi2);
  if (dp > 3.14159) dp = dp - 2*3.14159; 
  return std::sqrt ( (eta1-eta2)*(eta1-eta2) + dp*dp ) ;
}

Float_t analysisCode::getDeltaPhi(Float_t phi1, Float_t phi2) 
{
  if (phi1 == -999 || phi2 == -999) return -999.; 
  auto dp = phi1 - phi2;
  if (dp >= 3.14159) dp = dp - 2*3.14159; 
  if (dp < -3.14159) dp = dp + 2*3.14159; 
  return dp;
}

Float_t analysisCode::getCosDelta(const LorentzVector& v, const LorentzVector& r) {
      
  using namespace ROOT::Math::VectorUtil;
  return  CosTheta(ROOT::Math::VectorUtil::boost(v, r.BoostToCM()), r);
}




Float_t analysisCode::getCentrality(Float_t eta)
{
  if (VBFjet1_eta == -999. || VBFjet2_eta == -999.) return -999.;
  return (eta - 0.5*(VBFjet1_eta + VBFjet2_eta ))/(std::fabs(VBFjet1_eta - VBFjet2_eta)); 

}

Float_t analysisCode::getHHCentrality() 
{
  if ( getDeltaEtaMinus() < getDeltaEtaPlus() ) return getDeltaEtaMinus();
  else if ( getDeltaEtaMinus() == getDeltaEtaPlus() &&  getDeltaEtaPlus() == -999. ) return -999.;
  else return getDeltaEtaPlus();

}


Float_t analysisCode::getDeltaEtaMinus() 
{
  if (VBFjet1_eta == -999. || VBFjet2_eta == -999.  || bH_eta == -999. || tauH_eta == -999.) return -999.;
  
  float minH; 
  if ( bH_eta < tauH_eta ) minH = bH_eta; 
  else minH = tauH_eta; 

  float minVBF; 
  if ( VBFjet1_eta < VBFjet2_eta ) minVBF = VBFjet1_eta; 
  else minVBF = VBFjet2_eta; 

  return minH - minVBF; 

}


Float_t analysisCode::getDeltaEtaPlus() 
{
  if (VBFjet1_eta == -999. || VBFjet2_eta == -999.  || bH_eta == -999. || tauH_eta == -999.) return -999.;
  
  float maxH; 
  if ( bH_eta > tauH_eta ) maxH = bH_eta; 
  else maxH = tauH_eta; 

  float maxVBF; 
  if ( VBFjet1_eta > VBFjet2_eta ) maxVBF = VBFjet1_eta; 
  else maxVBF = VBFjet2_eta; 

  return maxVBF - maxH; 

}

Float_t analysisCode::getAHH()
{
  TLorentzVector vHtau, vHb; 
  vHtau.SetPtEtaPhiE ( tauH_pt, tauH_eta, tauH_phi, tauH_e);
  vHb.SetPtEtaPhiE ( bH_pt, bH_eta, bH_phi, bH_e);

  return ( (vHb + vHtau).Pt() ) / (vHb.Pt() + vHtau.Pt() ); 


}

Float_t  analysisCode::getDeltaRboosted(const LorentzVector& v_0, const LorentzVector& v_1, const LorentzVector& ref){
  using namespace ROOT::Math::VectorUtil; 
  return DeltaR(ROOT::Math::VectorUtil::boost(v_0, ref.BoostToCM()), ROOT::Math::VectorUtil::boost(v_1, ref.BoostToCM()));
}








std::vector <std::string> analysisCode::addCategories () {
   std::vector <std::string> categories = {};

   bool baseline = pairType == 2 && dau1_pt > 40 && abs (dau1_eta) < 2.1 && dau2_pt > 40 && abs (dau2_eta) < 2.1 && nleps == 0 && nbjetscand > 1;   
   // bool baseline = pairType == 2 && dau1_pt > 40 && abs (dau1_eta) < 2.1 && dau2_pt > 40 && abs (dau2_eta) < 2.1 && nleps == 0 && nbjetscand > 1 && isVBFtrigger == 0 && BDToutSM_kl_1 > 0;       // old baseline from Chiara's VBF
   bool baseline55     = baseline && tauH_SVFIT_mass > 50;
   bool baselineVBFtight = pairType == 2 && dau1_pt > 25 && abs (dau1_eta) < 2.1 && dau2_pt > 25 && tauH_SVFIT_mass > 50 && abs (dau2_eta) < 2.1 && nleps == 0 && nbjetscand > 1 && isVBFtrigger == 1 && VBFjj_mass > 800 && VBFjet1_pt > 140 && VBFjet2_pt > 60;
   bool baselineVBFloose = baseline55 && isVBF == 1 && VBFjj_mass > 500 && VBFjj_deltaEta > 3;

   bool btagLL = bjet1_bID_deepCSV > 0.1522 && bjet2_bID_deepCSV > 0.1522;
   bool btagM  = bjet1_bID_deepCSV > 0.4941 && bjet2_bID_deepCSV < 0.4941;
   bool btagMM = bjet1_bID_deepCSV > 0.4941 && bjet2_bID_deepCSV > 0.4941; 
   bool btagMfirst = bjet1_bID_deepCSV > 0.4941;
   bool ellypsMassCut  = ((tauH_SVFIT_mass-116.)*(tauH_SVFIT_mass-116.))/(35.*35.) + ((bH_mass_raw-111.)*(bH_mass_raw-111.))/(45.*45.) <  1.0;
   bool boostMassCut = tauH_SVFIT_mass > 79.5 && tauH_SVFIT_mass < 152.5 && fatjet_softdropMass > 90 && fatjet_softdropMass < 160;

   bool s1b1jresolvedMcut = baseline && btagM &&  isBoosted != 1 && ellypsMassCut && !(isVBF == 1 && VBFjj_mass > 500 && VBFjj_deltaEta > 3 && bjet1_bID_deepCSV > 0.4941);
   bool s2b0jresolvedMcut = baseline && btagMM && isBoosted != 1 && ellypsMassCut && !(isVBF == 1 && VBFjj_mass > 500 && VBFjj_deltaEta > 3 && bjet1_bID_deepCSV > 0.4941);
   bool VBFtight_DNN = baselineVBFtight && btagMfirst && BDToutSM_kl_1 > 0 && DNN_VBFvsGGF_TauTauTight > 0.3;
   bool VBFloose_DNN = baselineVBFloose && btagMfirst && BDToutSM_kl_1 > 0 && DNN_VBFvsGGF_TauTauLoose > 0.4;
   bool sboostedLLMcut = baseline && btagLL && isBoosted == 1 && boostMassCut && !(isVBF == 1 && VBFjj_mass > 500 && VBFjj_deltaEta > 3 && bjet1_bID_deepCSV > 0.4941);
   bool VBFloose = baselineVBFloose && btagMfirst && BDToutSM_kl_1 > 0;
   bool VBFtight = baselineVBFtight && btagMfirst && BDToutSM_kl_1 > 0;

   if (s1b1jresolvedMcut) categories.push_back("s1b1jresolvedMcut");
   if (s2b0jresolvedMcut) categories.push_back("s2b0jresolvedMcut");
   if (VBFtight_DNN) categories.push_back("VBFtight_DNN");
   if (VBFloose_DNN) categories.push_back("VBFloose_DNN");
   if (sboostedLLMcut) categories.push_back("sboostedLLMcut");
   if (VBFtight) categories.push_back("VBFtight");
   if (VBFloose) categories.push_back("VBFloose");
   if (baseline) categories.push_back("baseline");

   return categories; 
}

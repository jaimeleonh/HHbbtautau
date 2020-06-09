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
#include <boost/variant.hpp>
#include "TTreeFormula.h"


void analysisCode::Loop(bool info)
{
   if (fChain == 0) return;
   Book();
   Long64_t nentries = fChain->GetEntries();
   std::cout << "Total entries = " << nentries << endl;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
  //    cout << "After LoadTree" << endl; 
      if (ientry < 0) break;
      //if(jentry % 100 == 0)
      if(jentry % 100 == 0 && info==true)
        std::cout << "[analysisCode::Loop] processed : "
        << jentry << " entries\r" << std::flush;
   //   cout << "Entry " << jentry << " before fChain->GetEntry(jentry)" << endl; 
      nb = fChain->GetEntry(jentry);   nbytes += nb;
   //   cout << "Entry " << jentry << " before Fill()" << endl; 
      Fill();
   }
   std::cout << std::endl;
   EndJob();
}


void analysisCode::Book()
{

  //std::vector <std::string> categories = {""};
  //std::vector <std::string> categories = {"noSelection","baseline","s1b1jresolvedMcut", "s2b0jresolvedMcut", "VBFtight_DNN", "VBFloose_DNN", "sboostedLLMcut", "VBFloose", "VBFtight"};
  std::vector <std::string> selections = {"noSelection","baseline_etauh","baseline_mutauh","baseline_tauhtauh", "VBF_baseline", "VBFloose", "VBF_loose_baseline"};
  std::vector <std::string> regions = {"","SR", "SStight", "OSrlx", "SSrlx", "OSinviso", "SSinviso"}; 
  std::vector <std::string> categories = {};

  for (auto & cat : selections ) {
    for (auto & reg : regions ) {
      stats[cat + "_" + reg] = 0; 
      categories.push_back(cat + "_" +reg);
    }
  }
  m_outFile.cd();

  cout << "Creating all plots" << endl; 
  m_plots["NGenJets"]    = new TH1F("NGenJets", "NGenJets; ;NGenJets Entries", 4, -1.5, 2.5);

  for (auto & cat : categories) {
    for (int i = 1; i<=2; i++) {
      m_plots["tau" + std::to_string(i) + "pt" + cat]    = new TH1F(("tau" + std::to_string(i) + "_pt_"+ cat).c_str(), ("tau" + std::to_string(i) + "_pt; #tau_{" + std::to_string(i) + "} pt(GeV); Entries").c_str(), 35, 40, 140); 
      m_plots["tau" + std::to_string(i) + "pt/m" + cat]    = new TH1F(("tau" + std::to_string(i) + "_pt_m_"+ cat).c_str(), ("tau" + std::to_string(i) + "_pt / tauH_mass; #tau_{" + std::to_string(i) + "} pt / H(#tau#tau) mass; Entries").c_str(), 50, 0, 2); 
      m_plots["tauTrig" + std::to_string(i) + "pt" + cat]    = new TH1F(("tau" + std::to_string(i) + "_pt_VBFtrigger_"+ cat).c_str(), ("tau" + std::to_string(i) + "_pt; #tau_{" + std::to_string(i) + "} pt(GeV); Entries").c_str(), 35, 40, 140); 
      m_plots["tauw" + std::to_string(i) + "pt" + cat]    = new TH1F(("tau" + std::to_string(i) + "_pt_noweight_"+ cat).c_str(), ("tau" + std::to_string(i) + "_pt; #tau_{" + std::to_string(i) + "} pt(GeV); Entries").c_str(), 35, 40, 140); 
      m_plots["tau" + std::to_string(i) + "eta" + cat]    = new TH1F(("tau" + std::to_string(i) + "_eta_"+ cat).c_str(), ("tau" + std::to_string(i) + "_eta; #tau_{" + std::to_string(i) + "} eta; Entries").c_str(), 50, -2.5, 2.5); 
      m_plots["tau" + std::to_string(i) + "e" + cat]    = new TH1F(("tau" + std::to_string(i) + "_e_"+ cat).c_str(), ("tau" + std::to_string(i) + "_e; #tau_{" + std::to_string(i) + "} e; Entries").c_str(), 50, 0, 1000); 
      m_plots["tau" + std::to_string(i) + "iso" + cat]    = new TH1F(("tau" + std::to_string(i) + "_iso_"+ cat).c_str(), ("tau" + std::to_string(i) + "_iso; #tau_{" + std::to_string(i) + "} iso; Entries").c_str(), 50, 0, 1); 
      m_plots["tau" + std::to_string(i) + "z" + cat]    = new TH1F(("tau" + std::to_string(i) + "_z_"+ cat).c_str(), ("tau" + std::to_string(i) + "_z; #tau_{" + std::to_string(i) + "} z; Entries").c_str(), 50, -5, 5);
      std::vector <std::string> DM = {"0", "1", "10", "11"};
      for (auto & dm : DM) {
        m_plots["tau" + std::to_string(i) + "DM" + dm + cat]    = new TH1F(("tau" + std::to_string(i) + "_dm"+ dm + "_" + cat).c_str(), ("#tau_{" + std::to_string(i) + "}_dm" + dm + "; tau" + std::to_string(i) + " dm" + dm + "; Entries").c_str(), 2, -0.5, 1.5);
      }

      m_plots["bjet" + std::to_string(i) + "pt" + cat]    = new TH1F(("bjet" + std::to_string(i) + "_pt_"+ cat).c_str(), ("bjet" + std::to_string(i) + "_pt; b_{" + std::to_string(i) + "} pt(GeV); Entries").c_str(), 50, 20, 200); 
      m_plots["bjet" + std::to_string(i) + "pt/m" + cat]    = new TH1F(("bjet" + std::to_string(i) + "_pt_m_"+ cat).c_str(), ("bjet" + std::to_string(i) + "_pt / bH_mass; b_{" + std::to_string(i) + "} pt / H(bb) Mass; Entries").c_str(), 50, 0, 2); 
      m_plots["bjet" + std::to_string(i) + "eta" + cat]    = new TH1F(("bjet" + std::to_string(i) + "_eta_"+ cat).c_str(), ("bjet" + std::to_string(i) + "_eta; b_{" + std::to_string(i) + "} eta; Entries").c_str(), 50, -2.5, 2.5); 
      m_plots["bjet" + std::to_string(i) + "e" + cat]    = new TH1F(("bjet" + std::to_string(i) + "_e_"+ cat).c_str(), ("bjet" + std::to_string(i) + "_e; b_{" + std::to_string(i) + "} e; Entries").c_str(), 50, 0, 1000); 
      m_plots["bjet" + std::to_string(i) + "z" + cat]    = new TH1F(("bjet" + std::to_string(i) + "_z_"+ cat).c_str(), ("bjet" + std::to_string(i) + "_z; b_{" + std::to_string(i) + "} z; Entries").c_str(), 50, -5, 5);

      m_plots["additionalJet" + std::to_string(i) + "pt" + cat]    = new TH1F(("additionalJet" + std::to_string(i) + "_pt_"+ cat).c_str(), ("additionalJet" + std::to_string(i) + "_pt; additionalJet" + std::to_string(i) + " pt(GeV); Entries").c_str(), 50, 0, 200); 
      m_plots["additionalJet" + std::to_string(i) + "eta" + cat]    = new TH1F(("additionalJet" + std::to_string(i) + "_eta_"+ cat).c_str(), ("additionalJet" + std::to_string(i) + "_eta; additionalJet" + std::to_string(i) + " eta; Entries").c_str(), 50, -2.5, 2.5); 
      m_plots["additionalJet" + std::to_string(i) + "e" + cat]    = new TH1F(("additionalJet" + std::to_string(i) + "_e_"+ cat).c_str(), ("additionalJet" + std::to_string(i) + "_e; additionalJet" + std::to_string(i) + " e; Entries").c_str(), 50, 0, 1000); 
      m_plots["additionalJet" + std::to_string(i) + "z" + cat]    = new TH1F(("additionalJet" + std::to_string(i) + "_z_"+ cat).c_str(), ("additionalJet" + std::to_string(i) + "_z; additionalJet" + std::to_string(i) + " z; Entries").c_str(), 50, -5, 5);
     
      m_plots["VBFjet" + std::to_string(i) + "pt" + cat]    = new TH1F(("VBFjet" + std::to_string(i) + "_pt_"+ cat).c_str(), ("VBFjet" + std::to_string(i) + "_pt; VBFjet_{" + std::to_string(i) + "} pt(GeV); Entries").c_str(), 50, 0, 400); 
      m_plots["VBFjet" + std::to_string(i) + "pt/m" + cat]    = new TH1F(("VBFjet" + std::to_string(i) + "_pt_m_"+ cat).c_str(), ("VBFjet" + std::to_string(i) + "_pt / VBFjj_mass; VBFjet_{" + std::to_string(i) + "} pt / VBF dijet Mass; Entries").c_str(), 50, 0, 2); 
      m_plots["VBFjet" + std::to_string(i) + "eta" + cat]    = new TH1F(("VBFjet" + std::to_string(i) + "_eta_"+ cat).c_str(), ("VBFjet" + std::to_string(i) + "_eta; VBFjet_{" + std::to_string(i) + "} #eta; Entries").c_str(), 50, -6, 6); 
      m_plots["VBFjet" + std::to_string(i) + "e" + cat]    = new TH1F(("VBFjet" + std::to_string(i) + "_e_"+ cat).c_str(), ("VBFjet" + std::to_string(i) + "_e; VBFjet_{" + std::to_string(i) + "} e; Entries").c_str(), 50, 0, 1000); 
      m_plots["VBFjet" + std::to_string(i) + "phi" + cat]    = new TH1F(("VBFjet" + std::to_string(i) + "_phi_"+ cat).c_str(), ("VBFjet" + std::to_string(i) + "_phi; VBFjet_{" + std::to_string(i) + "} phi; Entries").c_str(), 50, -3.5, 3.5); 
      m_plots["VBFjet" + std::to_string(i) + "z" + cat]    = new TH1F(("VBFjet" + std::to_string(i) + "_z_"+ cat).c_str(), ("VBFjet" + std::to_string(i) + "_z; VBFjet_{" + std::to_string(i) + "} z; Entries").c_str(), 50, -5, 5);

      m_plots["prodgenjet" + std::to_string(i) + "pt" + cat]    = new TH1F(("prodgenjet" + std::to_string(i) + "_pt_"+ cat).c_str(), ("prodgenjet" + std::to_string(i) + "_pt; prodgenjet_{" + std::to_string(i) + "} pt(GeV); Entries").c_str(), 50, 0, 200); 
    }

    m_plots["met_pt"+ cat]   = new TH1F(("met_pt_"+ cat).c_str(), "met pt; met pt (GeV); Entries", 50, 0, 500); 

    m_plots["NGenJets"+ cat]    = new TH1F(("NGenJets_"+cat).c_str(), "NGenJets; NGenJets; Entries", 4, -1.5, 2.5);
    m_plots["genMHH"+ cat]   = new TH1F(("genMHH_"+ cat).c_str(), "genHH mass; genHH Mass (GeV); Entries", 50, 0, 2000); 

    m_plots["bjets_deltaEta"+ cat]    = new TH1F(("bjets_deltaEta_"+ cat).c_str(), "bjets_deltaEta; #Delta #eta (b_1, b_2) ; Entries", 50, -0, 10); 
    m_plots["bjets_eta1eta2"+ cat]    = new TH1F(("bjets_eta1eta2_"+ cat).c_str(), "bjets_eta1eta2;  #eta(b_1) #times #eta(b_2) ; Entries", 50, -10, 10); 

    m_plots["VBFjj_deltaEta"+ cat]    = new TH1F(("VBFjj_deltaEta_"+ cat).c_str(), "VBFjj_deltaEta; #Delta #eta (VBFjet_1, VBFjet_2) ; Entries", 50, -0, 10); 
    m_plots["VBFjj_eta1eta2"+ cat]    = new TH1F(("VBFjj_eta1eta2_"+ cat).c_str(), "VBFjj_eta1eta2; #eta(VBFjet_1) #times #eta(VBFjet_2) ; Entries", 50, -10, 10); 

    m_plots["additionalJets_deltaEta"+ cat]    = new TH1F(("additionalJets_deltaEta_"+ cat).c_str(), "additionalJets_deltaEta; additionalJets_deltaEta ; Entries", 50, -0, 10); 
    m_plots["additionalJets_eta1eta2"+ cat]    = new TH1F(("additionalJets_eta1eta2_"+ cat).c_str(), "additionalJets_eta1eta2; additionalJets eta1#times eta2 ; Entries", 50, -10, 10); 
    m_plots["additionalJets_mass"+ cat]    = new TH1F(("additionalJets_mass_"+ cat).c_str(), "additionalJets_mass; additionalJets_mass ; Entries", 50, 0, 1000); 
    
    m_plots["additionalVBFjet" + std::to_string(1) + "pt" + cat]  = new TH1F(("additionalVBFjet" + std::to_string(1) + "_pt_"+ cat).c_str(), ("additionalVBFjet" + std::to_string(1) + "_pt; VBFjet" + std::to_string(1) + " pt(GeV); Entries").c_str(), 50, 0, 200); 
    m_plots["additionalVBFjet" + std::to_string(1) + "eta" + cat] = new TH1F(("additionalVBFjet" + std::to_string(1) + "_eta_"+ cat).c_str(), ("additionalVBFjet" + std::to_string(1) + "_eta; VBFjet" + std::to_string(1) + " eta; Entries").c_str(), 50, -2.5, 2.5);    
    m_plots["additionalVBFjet" + std::to_string(1) + "e" + cat] = new TH1F(("additionalVBFjet" + std::to_string(1) + "_e_"+ cat).c_str(), ("additionalVBFjet" + std::to_string(1) + "_e; VBFjet" + std::to_string(1) + " e; Entries").c_str(), 50, 0, 1000);    
    m_plots["additionalVBFjet" + std::to_string(1) + "z" + cat]   = new TH1F(("additionalVBFjet" + std::to_string(1) + "_z_"+ cat).c_str(), ("additionalVBFjet" + std::to_string(1) + "_z; VBFjet" + std::to_string(1) + " z; Entries").c_str(), 50, -5, 5);

    m_plots["HH_mass"+ cat]   = new TH1F(("HH_mass_"+ cat).c_str(), "HH mass; HH Mass (GeV); Entries", 50, 0, 2000); 
    m_plots["HH_eta"+ cat]    = new TH1F(("HH_eta_"+ cat).c_str(), "HH eta; HH eta; Entries", 50, -2.5, 2.5); 
    m_plots["HH_phi"+ cat]    = new TH1F(("HH_phi_"+ cat).c_str(), "HH phi; HH phi; Entries", 50, -3.5, 3.5); 
    m_plots["HH_pt"+ cat]   = new TH1F(("HH_pt_"+ cat).c_str(), "HH pt; HH pt (GeV); Entries", 50, 0, 500); 
    m_plots["HH_z"+ cat]   = new TH1F(("HH_z_"+ cat).c_str(), "HH z; HH z; Entries", 50, -5, 5); 
    m_plots["HH_z_nt"+ cat]   = new TH1F(("HH_z_nt_"+ cat).c_str(), "HH z; HH z; Entries", 50, -5, 5); 
    m_plots["HH_AHH"+ cat]   = new TH1F(("HH_AHH_"+ cat).c_str(), "HH AHH; HH AHH; Entries", 50, -0.1, 1.1); 
    m_plots["HH_costhetaCS"+ cat]   = new TH1F(("HH_costhetaCS_"+ cat).c_str(), "HH abs(costhetaCS); HH abs(cos#theta_{CS}); Entries", 50, -0.1, 1.1); 
    m_plots["HH_costhetaCS_rev"+ cat]   = new TH1F(("HH_costhetaCS_rev_"+ cat).c_str(), "HH abs(costhetaCS); HH abs(cos#theta_{CS}); Entries", 50, -0.1, 1.1); 
    m_plots["HH_costhetaCS_svfit"+ cat]   = new TH1F(("HH_costhetaCS_svfit_"+ cat).c_str(), "HH abs(costhetaCS); HH abs(cos#theta_{CS}); Entries", 50, -0.1, 1.1); 
    
  
    m_plots["HH_deltaPhi"+ cat] = new TH1F(("HH_deltaPhi_"+ cat).c_str(), "HH_deltaPhi; HH_deltaPhi ; Entries", 15, -3.14159, 3.14159);
    m_plots["HH_deltaEta"+ cat]    = new TH1F(("HH_deltaEta_"+ cat).c_str(), "HH_deltaEta; HH_deltaEta ; Entries", 50, -0.5, 10); 
    m_plots["HH_deltaR"+ cat]    = new TH1F(("HH_deltaR_"+ cat).c_str(), "HH_deltaR; HH_deltaR ; Entries", 50, 0, 10); 

    m_plots["HHsvfit_mass"+ cat]   = new TH1F(("HHsvfit_mass_"+ cat).c_str(), "HH mass; HH Mass (GeV); Entries", 50, 0, 2000); 
    m_plots["HHsvfit_eta"+ cat]    = new TH1F(("HHsvfit_eta_"+ cat).c_str(), "HH eta; HH eta; Entries", 50, -2.5, 2.5); 
    m_plots["HHsvfit_phi"+ cat]    = new TH1F(("HHsvfit_phi_"+ cat).c_str(), "HH phi; HH phi; Entries", 50, -3.5, 3.5); 
    m_plots["HHsvfit_pt"+ cat]   = new TH1F(("HHsvfit_pt_"+ cat).c_str(), "HH pt; HH pt (GeV); Entries", 50, 0, 500); 
    m_plots["HHsvfit_deltaPhi"+ cat] = new TH1F(("HHsvfit_deltaPhi_"+ cat).c_str(), "HH_deltaPhi; HH_deltaPhi ; Entries", 15, -3.14159, 3.14159);
  
    m_plots["HHKin_mass_raw"+ cat]   = new TH1F(("HHKin_mass_raw_"+ cat).c_str(), "HHKin mass; HHKin Mass (GeV); Entries", 50, 0, 2000); 
    m_plots["HHkinsvfit_mass"+ cat]   = new TH1F(("HHkinsvfit_mass_"+ cat).c_str(), "HH mass; HH Kin SVFit Mass (GeV); Entries", 50, 0, 2000); 
    m_plots["HHkinsvfit_eta"+ cat]    = new TH1F(("HHkinsvfit_eta_"+ cat).c_str(), "HH eta; HH Kin SVFit eta; Entries", 50, -2.5, 2.5); 
    m_plots["HHkinsvfit_phi"+ cat]    = new TH1F(("HHkinsvfit_phi_"+ cat).c_str(), "HH phi; HH Kin SVFit phi; Entries", 50, -6.5, 6.5); 
    m_plots["HHkinsvfit_pt"+ cat]   = new TH1F(("HHkinsvfit_pt_"+ cat).c_str(), "HH pt; HH Kin SVFit pt (GeV); Entries", 50, 0, 500); 
    m_plots["HHkinsvfit_bHmass"+ cat]   = new TH1F(("HHkinsvfit_bHmass_"+ cat).c_str(), "H(bb) mass; H(bb) Kin SVFit Mass (GeV); Entries", 50, 0, 250); 
    m_plots["HHKin_chi2"+ cat] = new TH1F(("HHKin_chi2_"+ cat).c_str(), "HHKin chi2; HHKin_chi2; Entries", 50, -0.5, 10); 
  
    m_plots["tauH_mass"+ cat] = new TH1F(("tauH_mass_"+ cat).c_str(), "tauH mass; H(#tau#tau) Mass (GeV); Entries", 50, 0, 250); 
    m_plots["tauH_pt"+ cat]   = new TH1F(("tauH_pt_"+ cat).c_str(), "tauH pt; H(#tau#tau) pt (GeV); Entries", 50, 0, 500); 
    m_plots["tauH_pt/m"+ cat]   = new TH1F(("tauH_pt_m_"+ cat).c_str(), "tauH pt / HH_mass; H(#tau#tau) pt / HH Mass; Entries", 30, 0, 1); 
    m_plots["tauH_eta"+ cat]  = new TH1F(("tauH_eta_"+ cat).c_str(), "tauH eta; H(#tau#tau) eta ; Entries", 50, -6, 6); 
    m_plots["tauH_phi"+ cat]  = new TH1F(("tauH_phi_"+ cat).c_str(), "tauH phi; H(#tau#tau) phi ; Entries", 50, -3.5, 3.5); 
    m_plots["tauH_z"+ cat]  = new TH1F(("tauH_z_"+ cat).c_str(), "tauH z; H(#tau#tau) z ; Entries", 50, -0.1, 1.1); 
    m_plots["ditau_dr"+ cat]  = new TH1F(("ditau_dr_"+ cat).c_str(), "ditau #Delta R; #Delta R (#tau_{1}, #tau_{2}) ; Entries", 50, 0, 10); 
    m_plots["ditau_deltaPhi"+ cat]  = new TH1F(("ditau_deltaPhi_"+ cat).c_str(), "ditau #Delta #phi; #Delta #phi (#tau_{1}, #tau_{2}); Entries", 15, -3.14159, 3.14159); 

    m_plots["tauH_SVFIT_mass"+ cat] = new TH1F(("tauH_SVFIT_mass_"+ cat).c_str(), "tauH SVFIT mass; H(#tau#tau) SVFit Mass (GeV); Entries", 50, 0, 250); 
    m_plots["tauH_SVFIT_pt"+cat]   = new TH1F(("tauH_SVFIT_pt_"+ cat).c_str(), "tauH SVFIT pt; H(#tau#tau) SVFit pt (GeV); Entries", 50, 0, 500); 
    m_plots["tauH_SVFIT_eta"+cat]  = new TH1F(("tauH_SVFIT_eta_"+ cat).c_str(), "tauH SVFIT eta; H(#tau#tau) eta ; Entries", 50, -2.5, 2.5); 
    m_plots["tauH_SVFIT_phi"+cat]  = new TH1F(("tauH_SVFIT_phi_"+ cat).c_str(), "tauH SVFIT phi; H(#tau#tau) phi ; Entries", 50, -3.5, 3.5); 
    m_plots["costheta_tau1_tau2"+ cat] = new TH1F(("costheta_tau1_tau2_"+ cat).c_str(), "#tau_{1}-#tau_{2} abs(cos#theta); #tau_{1}-#tau_{2} abs(cos#theta) ; Entries", 50, -0.1, 1.1); 
  
    m_plots["bH_mass"+ cat]   = new TH1F(("bH_mass_"+ cat).c_str(), "H(bb) mass; H(bb) Mass (GeV); Entries", 50, 0, 250); 
    m_plots["bH_pt"+ cat]     = new TH1F(("bH_pt_"+ cat).c_str(), "H(bb) pt (GeV); H(bb) pt (GeV); Entries", 50, 0, 500); 
    m_plots["bH_pt/m"+ cat]     = new TH1F(("bH_pt_m_"+ cat).c_str(), "bH pt / HH_mass; H(bb) pt / HH_mass; Entries", 50, 0, 2); 
    m_plots["bH_eta"+ cat]    = new TH1F(("bH_eta_"+ cat).c_str(), "bH eta; H(bb) eta ; Entries", 50, -6, 6); 
    m_plots["bH_phi"+ cat]    = new TH1F(("bH_phi_"+ cat).c_str(), "bH phi; H(bb) phi ; Entries", 50, -3.5, 3.5); 
    m_plots["bH_z"+ cat]      = new TH1F(("bH_z_"+ cat).c_str(), "bH z; H(bb) z ; Entries", 50, -0.1, 1.1); 
    m_plots["dib_dr"+ cat]  = new TH1F(("dib_dr_"+ cat).c_str(), "dib #Delta R; #Delta R (b_{1}, b_{2}); Entries", 50, 0, 10); 
    m_plots["dib_deltaPhi"+ cat]  = new TH1F(("dib_deltaPhi_"+ cat).c_str(), "dib #Delta #phi; #Delta #phi (b_{1}, b_{2}); Entries", 15, -3.14159, 3.14159); 
    m_plots["costheta_b1_b2"+ cat] = new TH1F(("costheta_b1_b2_"+ cat).c_str(), "b1-b2 abs(cos#theta); b_{1}-b_{2} abs(cos#theta) ; Entries", 50, -0.1, 1.1); 
    
    m_plots["btau_dr_min"+ cat]  = new TH1F(("btau_dr_min_"+ cat).c_str(), "b#tau min #Delta R; b#tau min #Delta R ; Entries", 50, 0, 5); 
    m_plots["btau_dr_max"+ cat]  = new TH1F(("btau_dr_max_"+ cat).c_str(), "b#tau max #Delta R; b#tau max #Delta R ; Entries", 50, 0, 6); 
    
    m_plots["VBFjj_mass"+ cat] = new TH1F(("VBFjj_mass_"+ cat).c_str(), "VBFjj mass; VBFjj Mass (GeV); Entries", 50, 0, 2000); 
    m_plots["VBFjj_mass_5000"+ cat] = new TH1F(("VBFjj_mass_5000_"+ cat).c_str(), "VBFjj mass; VBFjj Mass (GeV); Entries", 100, 0, 5000); 
    m_plots["VBFjj_HT"+ cat] = new TH1F(("VBFjj_HT_"+ cat).c_str(), "VBFjj HT; VBFjj HT (GeV); Entries", 50, 0, 500); 
    m_plots["VBFjj_deltaPhi"+ cat]    = new TH1F(("VBFjj_deltaPhi_"+ cat).c_str(), "VBFjj_deltaPhi; VBFjj_deltaPhi ; Entries", 15, -3.14159, 3.14159); 
    m_plots["VBFjj_deltaR"+ cat]    = new TH1F(("VBFjj_deltaR_"+ cat).c_str(), "VBFjj_deltaR; #DeltaR VBF dijet ; Entries", 50, 0, 10); 
    m_plots["VBFgenjj_deltaPhi"+ cat]    = new TH1F(("VBFgenjj_deltaPhi_"+ cat).c_str(), "VBFgenjj_deltaPhi; VBFgenjj_deltaPhi ; Entries", 15, -3.14159, 3.14159); 
  
    m_plots["VBFjTau_deltaR"+ cat]    = new TH1F(("VBFjTau_deltaR_"+ cat).c_str(), "VBFjTau_deltaR; Min #Delta R (VBFj,#tau) ; Entries", 50, 0, 6); 
    m_plots["VBFjb_deltaR"+ cat]    = new TH1F(("VBFjb_deltaR_"+ cat).c_str(), "VBFjb_deltaR; Min #Delta R (VBFj,b) ; Entries", 50, 0, 6); 

    
    // SOME OF GILES' VARIABLES
    m_plots["dR_hbb_sv"+ cat]    = new TH1F(("dR_hbb_sv_"+ cat).c_str(), "dR_hbb_tauH_SVFIT; dR_hbb_tauH_SVFIT ; Entries", 50, 0, 10);
    m_plots["dR_l1_l2_x_sv_pT"+ cat]    = new TH1F(("dR_l1_l2_x_sv_pT_"+ cat).c_str(), "dR_l1_l2 * tauH_SVFIT_pT; dR_l1_l2 * tauH_SVFIT_pT ; Entries", 50, 0, 1000);
    m_plots["dphi_sv_met"+ cat]    = new TH1F(("dphi_sv_met_"+ cat).c_str(), "dphi_sv_met; dphi_sv_met ; Entries", 50, -3.5, 3.5);
    m_plots["dR_l1_l2_boosted_htt_met"+ cat]    = new TH1F(("dR_l1_l2_boosted_htt_met_"+ cat).c_str(), "dR_l1_l2_boosted_htt_met; dR_l1_l2_boosted_htt_met; Entries", 50, 0, 10);
    m_plots["dphi_hbb_sv"+ cat]    = new TH1F(("dphi_hbb_sv_"+ cat).c_str(), "dphi_hbb_sv; dphi_hbb_sv; Entries", 50, -3.5, 3.5);
    m_plots["deta_b1_b2"+ cat]    = new TH1F(("deta_b1_b2_"+ cat).c_str(), "deta_b1_b2; deta_b1_b2 ; Entries", 50, -0.5, 10);
    m_plots["costheta_l2_htt"+ cat]    = new TH1F(("costheta_l2_htt_"+ cat).c_str(), "abs(costheta_l2_htt); abs(costheta_l2_htt); Entries", 50, -0.1, 1.1);
    m_plots["dphi_l1_met"+ cat]    = new TH1F(("dphi_l1_met_"+ cat).c_str(), "dphi_l1_met; dphi_l1_met; Entries", 50, -3.5, 3.5);
    m_plots["costheta_htt_hh_met"+ cat]    = new TH1F(("costheta_htt_hh_met_"+ cat).c_str(), "abs(costheta_htt_hh_met); abs(costheta_htt_hh_met); Entries", 50, -0.1, 1.1);
    m_plots["dR_hbb_httmet"+ cat]    = new TH1F(("dR_hbb_httmet_"+ cat).c_str(), "dR_hbb_httmet; dR_hbb_httmet ; Entries", 50, 0, 10);
    m_plots["costheta_b1_hbb"+ cat]    = new TH1F(("costheta_b1_hbb_"+ cat).c_str(), "abs(costheta_b1_hbb); abs(costheta_b1_hbb); Entries", 50, -0.1, 1.1);
    m_plots["deta_hbb_httmet"+ cat]    = new TH1F(("deta_hbb_httmet_"+ cat).c_str(), "deta_hbb_httmet; deta_hbb_httmet; Entries", 50, -0.5, 10);
    m_plots["deta_hbb_svfit"+ cat]    = new TH1F(("deta_hbb_svfit_"+ cat).c_str(), "deta_hbb_svfit; #Delta#eta(H(bb),H(#tau#tau SVFit)); Entries", 50, -0.5, 10);
    m_plots["costheta_met_htt"+ cat]    = new TH1F(("costheta_met_htt_"+ cat).c_str(), "abs(costheta_met_htt); abs(costheta_met_htt); Entries", 50, -0.1, 1.1);
    m_plots["boosted"+ cat]    = new TH1F(("boosted_"+ cat).c_str(), "boosted; boosted; Entries", 3, -1.5, 1.5);
    m_plots["channel"+ cat]    = new TH1F(("channel_"+ cat).c_str(), "channel / pairType; channel; Entries", 5, -0.5, 4.5);
    m_plots["BDT_topPairMasses"+ cat]    = new TH1F(("BDT_topPairMasses_"+ cat).c_str(), "BDT_topPairMasses; BDT_topPairMasses; Entries", 50, 50, 250);
    m_plots["BDT_topPairMasses2"+ cat]    = new TH1F(("BDT_topPairMasses2_"+ cat).c_str(), "BDT_topPairMasses2; BDT_topPairMasses2; Entries", 50, 50, 250);
    

    // CHIARA's DNNs
    m_plots["DNN_VBFvsGGF_TauTauTight"+ cat]    = new TH1F(("DNN_VBFvsGGF_TauTauTight_"+ cat).c_str(), "DNN_VBFvsGGF_TauTauTight; DNN_VBFvsGGF_TauTauTight ; Entries", 10, 0, 1);
    m_plots["DNN_VBFvsGGF_TauTauLoose"+ cat]    = new TH1F(("DNN_VBFvsGGF_TauTauLoose_"+ cat).c_str(), "DNN_VBFvsGGF_TauTauLoose; DNN_VBFvsGGF_TauTauLoose ; Entries", 10, 0, 1);
    m_plots["DNN_VBFvsGGF_MuTau"+ cat]    = new TH1F(("DNN_VBFvsGGF_MuTau_"+ cat).c_str(), "DNN_VBFvsGGF_MuTau; DNN_VBFvsGGF_MuTau; Entries", 10, 0, 1);
    m_plots["DNN_VBFvsGGF_ETau"+ cat]    = new TH1F(("DNN_VBFvsGGF_ETau_"+ cat).c_str(), "DNN_VBFvsGGF_ETau; DNN_VBFvsGGF_ETau; Entries", 10, 0, 1);
    m_plots["DNNoutSM_kl_1"+ cat]    = new TH1F(("DNNoutSM_kl_1_"+ cat).c_str(), "DNNoutSM_kl_1; DNNoutSM_kl_1; Entries", 10,  0, 1);
    m_plots["BDToutSM_kl_1"+ cat]    = new TH1F(("BDToutSM_kl_1_"+ cat).c_str(), "BDToutSM_kl_1; BDToutSM_kl_1; Entries", 10, -1, 1);
    m_plots["BDToutSM_kl_1_noweight"+ cat]    = new TH1F(("BDToutSM_kl_1_noweight_"+ cat).c_str(), "BDToutSM_kl_1; BDToutSM_kl_1; Entries", 10, -1, 1);

    // bbgg centralities
    m_plots["centrality_bb"+cat] = new TH1F(("centrality_bb_"+ cat).c_str(), "bb centrality; b_{1},b_{2} centrality; Entries", 50, 0, 1);
    m_plots["centrality_tautau"+cat] = new TH1F(("centrality_tautau_"+ cat).c_str(), "tautau centrality; #tau_{1},#tau_{2} centrality; Entries", 50, 0, 1);


  }
  cout << "Finished adding plots" << endl;
}

void analysisCode::Fill()
{
  if (numberOfGenJets_ > -1){
    if (NGenJets != numberOfGenJets_) return;
  }
  m_plots["NGenJets"]->Fill(NGenJets);


  //cout << "Adding categories" << endl; 
  std::vector <std::string> selections = addCategories();

  //cout << "Adding regions" << endl; 
  std::vector <std::pair<std::string, std::string>> categories = addRegions(selections); 

  for (auto & cat : selections) {
    categories.push_back(make_pair(cat,cat+"_"));
  }
  categories.push_back(make_pair("noSelection","noSelection_"));
  
  //cout << "After regions" << endl;

  for (auto & mycat : categories ) {
    std::string cat = mycat.second; 
    stats[cat]++; 
    double myweight = 1;
    if (isMCSample == 1){
    //  cout << "Before weights" << endl;
      myweight = getWeights(mycat.first);
    //  cout << "After weights" << endl;
      if (TMath::IsNaN(myweight)) myweight = 0; 
    }
    
    m_plots["NGenJets"+ cat]->Fill(NGenJets);
    
    
    //Fill tau plots
    m_plots["tau1pt"+cat]->Fill(dau1_pt, myweight);
    m_plots["tau1pt/m"+cat]->Fill(dau1_pt / tauH_mass, myweight);
    if (isVBFtrigger == 0) m_plots["tauTrig1pt"+cat]->Fill(dau1_pt, myweight);
    m_plots["tauw1pt"+cat]->Fill(dau1_pt);
    m_plots["tau2pt"+cat]->Fill(dau2_pt, myweight);
    m_plots["tau2pt/m"+cat]->Fill(dau2_pt / tauH_mass, myweight);
    m_plots["tau1eta"+cat]->Fill(dau1_eta, myweight);
    m_plots["tau2eta"+cat]->Fill(dau2_eta, myweight);
    m_plots["tau1e"+cat]->Fill(dau1_e, myweight);
    m_plots["tau2e"+cat]->Fill(dau2_e, myweight);
    m_plots["tau1iso"+cat]->Fill(dau1_iso, myweight);
    m_plots["tau2iso"+cat]->Fill(dau2_iso, myweight);
    m_plots["tau1z"+cat]->Fill(getCentrality(dau1_eta), myweight);
    m_plots["tau2z"+cat]->Fill(getCentrality(dau2_eta), myweight);
    for (auto & i : {0,1,10,11}){
      m_plots["tau1DM" + std::to_string(i) + cat]->Fill(dau1_decayMode == i, myweight);
      m_plots["tau2DM" + std::to_string(i) + cat]->Fill(dau2_decayMode == i, myweight);
    }
    if (dau1_pt != -1 && dau2_pt != -1){
        m_plots["ditau_dr"+ cat]->Fill(getDeltaR(dau1_eta, dau1_phi, dau2_eta, dau2_phi), myweight);
        m_plots["ditau_deltaPhi"+ cat]->Fill(getDeltaPhi(dau1_phi, dau2_phi)); 
    }

    m_plots["prodgenjet1pt" + cat]->Fill(prodgenjet1_pt); 
    m_plots["prodgenjet2pt" + cat]->Fill(prodgenjet2_pt); 
    
      // Fill b plots
    if (bjet1_pt != -1) m_plots["bjet1pt"+cat]->Fill(bjet1_pt, myweight);
    if (bjet2_pt != -1) m_plots["bjet2pt"+cat]->Fill(bjet2_pt, myweight);
    if (bjet1_pt != -1) m_plots["bjet1pt/m"+cat]->Fill(bjet1_pt / bH_mass, myweight);
    if (bjet2_pt != -1) m_plots["bjet2pt/m"+cat]->Fill(bjet2_pt / bH_mass, myweight);
    if (bjet1_pt != -1) m_plots["bjet1eta"+cat]->Fill(bjet1_eta, myweight);
    if (bjet2_pt != -1) m_plots["bjet2eta"+cat]->Fill(bjet2_eta, myweight);
    if (bjet1_pt != -1) m_plots["bjet1e"+cat]->Fill(bjet1_e, myweight);
    if (bjet2_pt != -1) m_plots["bjet2e"+cat]->Fill(bjet2_e, myweight);
    if (bjet1_pt != -1) m_plots["bjet1z"+cat]->Fill(getCentrality(bjet1_eta), myweight);
    if (bjet2_pt != -1) m_plots["bjet2z"+cat]->Fill(getCentrality(bjet2_eta), myweight);
    if (bjet1_pt != -1 && bjet2_pt != -1) m_plots["bjets_deltaEta"+cat]->Fill(std::fabs(bjet1_eta - bjet2_eta), myweight);
    if (bjet1_pt != -1 && bjet2_pt != -1) m_plots["bjets_eta1eta2"+cat]->Fill(bjet1_eta * bjet2_eta, myweight);
    if (bjet1_pt != -1 && bjet2_pt != -1) {
        m_plots["dib_dr"+ cat]->Fill(getDeltaR(bjet1_eta, bjet1_phi, bjet2_eta, bjet2_phi), myweight);
        m_plots["dib_deltaPhi"+ cat]->Fill(getDeltaPhi(bjet1_phi, bjet2_phi)); 
    }
   
    // met plots
    m_plots["met_pt"+ cat]->Fill(met_et, myweight); 

    // Fill VBFjet plots
    if (VBFjet1_pt!=-999.) m_plots["VBFjet1pt"+cat]->Fill(VBFjet1_pt, myweight);
    if (VBFjet2_pt!=-999.) m_plots["VBFjet2pt"+cat]->Fill(VBFjet2_pt, myweight);
    if (VBFjet1_pt!=-999.) m_plots["VBFjet1pt/m"+cat]->Fill(VBFjet1_pt / VBFjj_mass, myweight);
    if (VBFjet2_pt!=-999.) m_plots["VBFjet2pt/m"+cat]->Fill(VBFjet2_pt / VBFjj_mass, myweight);
    if (VBFjet1_pt!=-999.) m_plots["VBFjet1eta"+cat]->Fill(VBFjet1_eta, myweight);
    if (VBFjet2_pt!=-999.) m_plots["VBFjet2eta"+cat]->Fill(VBFjet2_eta, myweight);
    if (VBFjet1_pt!=-999.) m_plots["VBFjet1phi"+cat]->Fill(VBFjet1_phi, myweight);
    if (VBFjet2_pt!=-999.) m_plots["VBFjet2phi"+cat]->Fill(VBFjet2_phi, myweight);
    if (VBFjet1_pt!=-999.) m_plots["VBFjet1e"+cat]->Fill(VBFjet1_e, myweight);
    if (VBFjet2_pt!=-999.) m_plots["VBFjet2e"+cat]->Fill(VBFjet2_e, myweight);
    if (VBFjet1_pt!=-999.) m_plots["VBFjet1z"+cat]->Fill(getCentrality(VBFjet1_eta), myweight);
    if (VBFjet2_pt!=-999.) m_plots["VBFjet2z"+cat]->Fill(getCentrality(VBFjet2_eta), myweight);
    if (VBFjet1_pt!=-999. && VBFjet2_pt!=-999.) m_plots["VBFjj_deltaEta"+cat]->Fill(VBFjj_deltaEta, myweight);
    if (VBFjet1_pt!=-999. && VBFjet2_pt!=-999.) m_plots["VBFjj_eta1eta2"+cat]->Fill(VBFjet1_eta*VBFjet2_eta, myweight);
    if (VBFjj_mass!=-999.) m_plots["VBFjj_mass"+cat]->Fill(VBFjj_mass, myweight);
    if (VBFjj_mass!=-999.) m_plots["VBFjj_mass_5000"+cat]->Fill(VBFjj_mass, myweight);

    // Fill additional b plots
    if (jet3_pt!=-999.) m_plots["additionalJet1pt"+cat]->Fill(jet3_pt, myweight);
    if (jet4_pt!=-999.) m_plots["additionalJet2pt"+cat]->Fill(jet4_pt, myweight);
    if (jet3_pt!=-999.) m_plots["additionalJet1eta"+cat]->Fill(jet3_eta, myweight);
    if (jet4_pt!=-999.) m_plots["additionalJet2eta"+cat]->Fill(jet4_eta, myweight);
    if (jet3_pt!=-999.) m_plots["additionalJet1e"+cat]->Fill(jet3_e, myweight);
    if (jet4_pt!=-999.) m_plots["additionalJet2e"+cat]->Fill(jet4_e, myweight);
    if (jet3_pt!=-999.) m_plots["additionalJet1z"+cat]->Fill(getCentrality(jet3_eta), myweight);
    if (jet4_pt!=-999.) m_plots["additionalJet2z"+cat]->Fill(getCentrality(jet4_eta), myweight);
    if (jet3_pt!=-999. && jet4_pt!=-999.) m_plots["additionalJets_deltaEta"+cat]->Fill(jj_deltaEta, myweight);
    if (jet3_pt!=-999. && jet4_pt!=-999.) m_plots["additionalJets_eta1eta2"+cat]->Fill(jet3_eta*jet4_eta, myweight);
    if (jj_mass!=-999.) m_plots["additionalJets_mass"+cat]->Fill(jj_mass, myweight);

    // Fill additional VBFjet
    if (jet5_VBF_pt!=-999.) m_plots["additionalVBFjet1pt"+cat]->Fill(jet5_VBF_pt, myweight);
    if (jet5_VBF_pt!=-999.) m_plots["additionalVBFjet1eta"+cat]->Fill(jet5_VBF_eta, myweight);
    if (jet5_VBF_pt!=-999.) m_plots["additionalVBFjet1e"+cat]->Fill(jet5_VBF_e, myweight);
    if (jet5_VBF_pt!=-999.) m_plots["additionalVBFjet1z"+cat]->Fill(getCentrality(jet5_VBF_eta), myweight);

    m_plots["genMHH"+cat]->Fill( genMHH, myweight );

    if (HH_eta != -1. && HH_phi != -1. && HH_pt != -1.) { 
      m_plots["HH_mass"+cat]->Fill( HH_mass, myweight );
      m_plots["HH_eta"+cat]->Fill( HH_eta, myweight );
      m_plots["HH_phi"+cat]->Fill( HH_phi, myweight );
      m_plots["HH_pt"+cat]->Fill( HH_pt, myweight );
      m_plots["HH_z"+cat]->Fill( getHHCentrality(), myweight);
      m_plots["HH_z_nt"+cat]->Fill( HH_z, myweight);
      m_plots["HH_AHH"+cat]->Fill( getAHH(), myweight);
    } else {
      //m_plots["HH_mass"]->Fill( -999. );
      //m_plots["HH_eta"]->Fill( -999. );
      //m_plots["HH_phi"]->Fill( -999. );
      //m_plots["HH_pt"]->Fill( -999. );
    }
    if (HHKin_mass_raw != 0.) m_plots["HHKin_mass_raw"+cat]->Fill( HHKin_mass_raw, myweight );
    //else m_plots["HHKin_mass_raw"]->Fill( -999. );
  
    m_plots["HHKin_chi2"+cat]->Fill(HHKin_chi2, myweight);
   
    if (HHsvfit_eta != -1. && HHsvfit_phi != -1. && HHsvfit_pt != -1.) { 
      m_plots["HHsvfit_mass"+cat]->Fill( HHsvfit_mass, myweight );
      m_plots["HHsvfit_eta"+cat]->Fill( HHsvfit_eta, myweight );
      m_plots["HHsvfit_phi"+cat]->Fill( HHsvfit_phi, myweight );
      m_plots["HHsvfit_pt"+cat]->Fill( HHsvfit_pt, myweight );
      m_plots["HHsvfit_deltaPhi"+cat]->Fill( HHsvfit_deltaPhi, myweight );
    } else {
      //m_plots["HHsvfit_mass"]->Fill( -999. );
      //m_plots["HHsvfit_eta"]->Fill( -999. );
      //m_plots["HHsvfit_phi"]->Fill( -999. );
      //m_plots["HHsvfit_pt"]->Fill( -999. );
      //m_plots["HHsvfit_deltaPhi"]->Fill( -999. );
    }
  
    if (HHkinsvfit_pt != -1.) { 
      m_plots["HHkinsvfit_mass"+ cat]->Fill(HHkinsvfit_m, myweight); 
      m_plots["HHkinsvfit_eta"+cat]->Fill( HHkinsvfit_eta, myweight );
      m_plots["HHkinsvfit_phi"+cat]->Fill( HHkinsvfit_phi, myweight );
      m_plots["HHkinsvfit_pt"+cat]->Fill( HHkinsvfit_pt, myweight );
      m_plots["HHkinsvfit_bHmass"+cat]->Fill( HHkinsvfit_bHmass, myweight );
    } else {
      //m_plots["HHkinsvfit_eta"]->Fill( -999. );
      //m_plots["HHkinsvfit_phi"]->Fill( -999. );
      //m_plots["HHkinsvfit_pt"]->Fill( -999. );
      //m_plots["HHkinsvfit_bHmass"]->Fill( -999. );
    }
  
    if (HH_deltaPhi != -1. && HH_deltaEta != -1. && HH_deltaR != -1.) { 
      m_plots["HH_deltaPhi"+cat]->Fill( HH_deltaPhi, myweight );
      m_plots["HH_deltaEta"+cat]->Fill( HH_deltaEta, myweight );
      m_plots["HH_deltaR"+cat]->Fill( HH_deltaR, myweight );
    } else {
    //m_plots["HH_deltaPhi"]->Fill( -999. );
    //m_plots["HH_deltaEta"]->Fill( -999. );
    //m_plots["HH_deltaR"]->Fill( -999. );
    }
  
  
    if (tauH_mass != -1. && tauH_pt != -1 && tauH_eta!=-1 ) {
      m_plots["tauH_mass"+cat]->Fill( tauH_mass, myweight );
      m_plots["tauH_pt"+cat]->Fill( tauH_pt, myweight );
      m_plots["tauH_pt/m"+cat]->Fill( tauH_pt / HH_mass, myweight );
      m_plots["tauH_eta"+cat]->Fill( tauH_eta, myweight );
      m_plots["tauH_phi"+cat]->Fill( tauH_phi, myweight );
      m_plots["tauH_z"+cat]->Fill( getCentrality(tauH_eta), myweight );
    } else {
      //m_plots["tauH_mass"]->Fill( -999. );
      //m_plots["tauH_pt"]->Fill( -999. );
      //m_plots["tauH_eta"]->Fill( -999. );
      //m_plots["tauH_phi"]->Fill( -999. );
    }
 
    if (tauH_SVFIT_mass != -1. && tauH_SVFIT_pt != -1 && tauH_SVFIT_eta!=-1 ) {
      m_plots["tauH_SVFIT_mass"+cat]->Fill( tauH_SVFIT_mass, myweight );
      m_plots["tauH_SVFIT_pt"+cat]->Fill( tauH_SVFIT_pt, myweight );
      m_plots["tauH_SVFIT_eta"+cat]->Fill( tauH_SVFIT_eta, myweight );
      m_plots["tauH_SVFIT_phi"+cat]->Fill( tauH_SVFIT_phi, myweight );
    } else {
      
      //m_plots["tauH_SVFIT_pt"]->Fill( -999. );
      //m_plots["tauH_SVFIT_eta"]->Fill( -999. );
      //m_plots["tauH_SVFIT_phi"]->Fill( -999. );
    }

    if (bH_mass != -1. && bH_pt != -1.) {
      m_plots["bH_mass"+cat]->Fill(bH_mass, myweight);
      m_plots["bH_pt"+cat]->Fill(bH_pt, myweight);
      m_plots["bH_pt/m"+cat]->Fill(bH_pt / HH_mass, myweight);
      m_plots["bH_eta"+cat]->Fill(bH_eta, myweight);
      m_plots["bH_phi"+cat]->Fill(bH_phi, myweight);
      m_plots["bH_z"+cat]->Fill(getCentrality(bH_eta), myweight);
    } else {
      //m_plots["bH_mass"]->Fill( -999. );
      //m_plots["bH_pt"]->Fill( -999. );
      //m_plots["bH_eta"]->Fill( -999. );
      //m_plots["bH_phi"]->Fill( -999. );
    }
    m_plots["VBFjj_HT"+cat]->Fill(VBFjj_HT, myweight); 
    m_plots["btau_dr_min"+ cat]->Fill(btau_deltaRmin, myweight); 
    m_plots["btau_dr_max"+ cat]->Fill(btau_deltaRmax, myweight); 
  

    if (VBFjet1_phi != -999 && VBFjet2_phi != -999) { 
      m_plots["VBFjj_deltaPhi"+cat]->Fill(getDeltaPhi(VBFjet1_phi,VBFjet2_phi), myweight); 
      m_plots["VBFjj_deltaR"+cat]->Fill( getDeltaR(VBFjet1_eta, VBFjet1_phi, VBFjet2_eta, VBFjet2_phi), myweight ); 
    } else {
      // m_plots["VBFjj_deltaPhi"]->Fill(-999);
      // m_plots["VBFjj_deltaR"]->Fill(-999);
    }
    if (VBFgenjet1_phi != -999 && VBFgenjet2_phi != -999) m_plots["VBFgenjj_deltaPhi"+cat]->Fill(getDeltaPhi(VBFgenjet1_phi, VBFgenjet2_phi), myweight); 
    //  else m_plots["VBFgenjj_deltaPhi"]->Fill(-999);

    // Fill VBF(j/tau) plots
    Float_t minDeltaRVBFjTau = 9999; 
    if (getDeltaR(VBFjet1_eta, VBFjet1_phi, dau1_eta, dau1_phi)!=-1) minDeltaRVBFjTau = getDeltaR(VBFjet1_eta, VBFjet1_phi, dau1_eta, dau1_phi);
    if (getDeltaR(VBFjet1_eta, VBFjet1_phi, dau2_eta, dau2_phi)!=-1 && getDeltaR(VBFjet1_eta, VBFjet1_phi, dau2_eta, dau2_phi) < minDeltaRVBFjTau) minDeltaRVBFjTau = getDeltaR(VBFjet1_eta, VBFjet1_phi, dau2_eta, dau2_phi);
    if (getDeltaR(VBFjet2_eta, VBFjet2_phi, dau1_eta, dau1_phi)!=-1 && getDeltaR(VBFjet2_eta, VBFjet2_phi, dau1_eta, dau1_phi) < minDeltaRVBFjTau) minDeltaRVBFjTau = getDeltaR(VBFjet2_eta, VBFjet2_phi, dau1_eta, dau1_phi);
    if (getDeltaR(VBFjet2_eta, VBFjet2_phi, dau2_eta, dau2_phi)!=-1 && getDeltaR(VBFjet2_eta, VBFjet2_phi, dau2_eta, dau2_phi) < minDeltaRVBFjTau) minDeltaRVBFjTau = getDeltaR(VBFjet2_eta, VBFjet2_phi, dau2_eta, dau2_phi);

    if (minDeltaRVBFjTau!=9999) m_plots["VBFjTau_deltaR"+cat]->Fill(minDeltaRVBFjTau, myweight);

    Float_t minDeltaRVBFjb = 9999; 
    if (getDeltaR(VBFjet1_eta, VBFjet1_phi, bjet1_eta, bjet1_phi)!=-1) minDeltaRVBFjb = getDeltaR(VBFjet1_eta, VBFjet1_phi, bjet1_eta, bjet1_phi);
    if (getDeltaR(VBFjet1_eta, VBFjet1_phi, bjet2_eta, bjet2_phi)!=-1 && getDeltaR(VBFjet1_eta, VBFjet1_phi, bjet2_eta, bjet2_phi) < minDeltaRVBFjTau) minDeltaRVBFjb = getDeltaR(VBFjet1_eta, VBFjet1_phi, bjet2_eta, bjet2_phi);
    if (getDeltaR(VBFjet2_eta, VBFjet2_phi, bjet1_eta, bjet1_phi)!=-1 && getDeltaR(VBFjet2_eta, VBFjet2_phi, bjet1_eta, bjet1_phi) < minDeltaRVBFjTau) minDeltaRVBFjb = getDeltaR(VBFjet2_eta, VBFjet2_phi, bjet1_eta, bjet1_phi);
    if (getDeltaR(VBFjet2_eta, VBFjet2_phi, bjet2_eta, bjet2_phi)!=-1 && getDeltaR(VBFjet2_eta, VBFjet2_phi, bjet2_eta, bjet2_phi) < minDeltaRVBFjTau) minDeltaRVBFjb = getDeltaR(VBFjet2_eta, VBFjet2_phi, bjet2_eta, bjet2_phi);

    if (minDeltaRVBFjb!=9999) m_plots["VBFjb_deltaR"+cat]->Fill(minDeltaRVBFjb, myweight);


    if (getDeltaR( bH_eta, bH_phi, tauH_SVFIT_eta, tauH_SVFIT_phi ) != -1 ) m_plots["dR_hbb_sv"+ cat] -> Fill(getDeltaR( bH_eta, bH_phi, tauH_SVFIT_eta, tauH_SVFIT_phi ), myweight); 
    if (getDeltaR( dau1_eta, dau1_phi, dau2_eta, dau2_phi ) != -1 && tauH_SVFIT_pt != -1 ) m_plots["dR_l1_l2_x_sv_pT"+ cat] -> Fill( getDeltaR( dau1_eta, dau1_phi, dau2_eta, dau2_phi) * tauH_SVFIT_pt, myweight);
    if (tauH_SVFIT_pt != -1) m_plots["dphi_sv_met"+ cat] -> Fill (fabs(tauHsvfitMet_deltaPhi), myweight);
 

    TLorentzVector metT, tauH_SVFIT; 
    metT.SetPtEtaPhiM(met_et, 0., met_phi, 0); 
    tauH_SVFIT.SetPtEtaPhiM(tauH_SVFIT_pt, tauH_SVFIT_eta, tauH_SVFIT_phi, tauH_SVFIT_mass); 

    LorentzVector l_1, l_2, b_1, b_2, h_bb, h_tt_vis, met, h_tt_SVFIT, hh; 
    l_1.SetEta(dau1_eta);  l_1.SetPhi(dau1_phi);  l_1.SetPt(dau1_pt);  l_1.SetE(dau1_e);
    l_2.SetEta(dau2_eta);  l_2.SetPhi(dau2_phi);  l_2.SetPt(dau2_pt);  l_2.SetE(dau2_e);
    b_1.SetEta(bjet1_eta);  b_1.SetPhi(bjet1_phi);  b_1.SetPt(bjet1_pt);  b_1.SetE(bjet1_e);
    b_2.SetEta(bjet2_eta);  b_2.SetPhi(bjet2_phi);  b_2.SetPt(bjet2_pt);  b_2.SetE(bjet2_e);
    h_bb.SetEta(bH_eta);  h_bb.SetPhi(bH_phi);  h_bb.SetPt(bH_pt);  h_bb.SetE(bH_e);
    h_tt_vis.SetEta(tauH_eta);  h_tt_vis.SetPhi(tauH_phi);  h_tt_vis.SetPt(tauH_pt);  h_tt_vis.SetE(tauH_e);
    h_tt_SVFIT.SetEta(tauH_SVFIT.Eta());  h_tt_SVFIT.SetPhi(tauH_SVFIT.Phi());  h_tt_SVFIT.SetPt(tauH_SVFIT.Pt());  h_tt_SVFIT.SetE(tauH_SVFIT.E());
    met.SetEta(0.);  met.SetPhi(met_phi);  met.SetPt(met_et);  met.SetE(metT.E());
    hh.SetEta(HH_eta);  hh.SetPhi(HH_phi);  hh.SetPt(HH_pt);  hh.SetE(HH_e);
    
    
    m_plots["dR_l1_l2_boosted_htt_met"+ cat] -> Fill ( getDeltaRboosted( l_1, l_2, h_tt_vis+met ), myweight);
    if (getDeltaPhi (tauH_SVFIT_phi, bH_phi) != -999.) m_plots["dphi_hbb_sv"+ cat] -> Fill( getDeltaPhi (tauH_SVFIT_phi, bH_phi), myweight );
    if (getDeltaEta (bjet1_eta, bjet2_eta) != -999.) m_plots["deta_b1_b2"+ cat] -> Fill( getDeltaEta (bjet1_eta, bjet2_eta), myweight );
    if (tauH_SVFIT_pt != -1.) m_plots["costheta_l2_htt"+ cat] -> Fill ( fabs(getCosDelta(l_2, h_tt_SVFIT)) , myweight) ;
    m_plots["dphi_l1_met"+ cat] -> Fill(getDeltaPhi ( dau1_phi, met_phi ), myweight );
    if (tauH_SVFIT_pt != -1.) m_plots["costheta_htt_hh_met"+ cat] -> Fill(getCosDelta( h_tt_SVFIT,  h_tt_vis+met+h_bb ), myweight );
    m_plots["dR_hbb_httmet"+ cat] -> Fill(getDeltaR(h_bb.Eta(), h_bb.Phi(), (h_tt_vis+met).Eta(), (h_tt_vis+met).Phi()), myweight);
    m_plots["costheta_b1_hbb"+ cat] -> Fill( fabs(getCosDelta ( b_1 , h_bb )), myweight); 
    m_plots["deta_hbb_httmet"+ cat] -> Fill( getDeltaEta ( h_bb.Eta(), (h_tt_vis+met).Eta() ), myweight );
    m_plots["deta_hbb_svfit"+ cat] -> Fill( getDeltaEta ( h_bb.Eta(), (h_tt_SVFIT).Eta() ), myweight );
    if (tauH_SVFIT_pt != -1) m_plots["costheta_met_htt"+ cat] -> Fill( fabs(getCosDelta( met, h_tt_SVFIT )), myweight );
    m_plots["boosted"+ cat] -> Fill (isBoosted, myweight);
    m_plots["channel"+ cat] -> Fill (pairType, myweight);
    if (BDT_topPairMasses!=-999.) m_plots["BDT_topPairMasses"+cat]->Fill(BDT_topPairMasses, myweight);

    m_plots["costheta_b1_b2"+ cat] -> Fill(fabs(getCosDelta (b_1, b_2)), myweight); 
    m_plots["costheta_tau1_tau2"+ cat] -> Fill(fabs(getCosDelta(l_1, l_2)), myweight); 
    m_plots["HH_costhetaCS"+ cat] -> Fill(fabs(getCosThetaStar_CS(h_bb, h_tt_vis, 6500)), myweight);
    m_plots["HH_costhetaCS_svfit"+ cat] -> Fill(fabs(getCosThetaStar_CS(h_bb, h_tt_SVFIT, 6500)), myweight);
    m_plots["HH_costhetaCS_rev"+ cat] -> Fill(fabs(getCosThetaStar_CS(h_tt_vis, h_bb, 6500)), myweight);
    
    // Chiara's DNNs

    if ( VBFjj_mass > 800 && VBFjet1_pt > 140 && VBFjet2_pt > 60 && fabs(VBFjj_deltaEta)>3 ) 
        m_plots["DNN_VBFvsGGF_TauTauTight"+ cat]  -> Fill(DNN_VBFvsGGF_TauTauTight, myweight);
    //if ( ( isVBFtrigger == 1 && VBFjj_mass > 800 && VBFjet1_pt > 140 && VBFjet2_pt > 60 && fabs(VBFjj_deltaEta)>3 ) ) m_plots["DNN_VBFvsGGF_TauTauTight"+ cat]  -> Fill(DNN_VBFvsGGF_TauTauTight, myweight);
    else if (isVBF == 1 && VBFjj_mass > 500 && fabs(VBFjj_deltaEta)>3) m_plots["DNN_VBFvsGGF_TauTauLoose"+ cat]  -> Fill(DNN_VBFvsGGF_TauTauLoose, myweight);
    if (VBFjj_mass > 500 && fabs(VBFjj_deltaEta)>3) m_plots["DNN_VBFvsGGF_MuTau"+ cat] -> Fill(DNN_VBFvsGGF_MuTau, myweight);
    if (VBFjj_mass > 500 && fabs(VBFjj_deltaEta)>3) m_plots["DNN_VBFvsGGF_ETau"+ cat] -> Fill(DNN_VBFvsGGF_ETau, myweight);
    m_plots["DNNoutSM_kl_1"+ cat] -> Fill(DNNoutSM_kl_1, myweight);
    m_plots["BDToutSM_kl_1"+ cat] -> Fill(BDToutSM_kl_1, myweight);
    m_plots["BDToutSM_kl_1_noweight"+ cat] -> Fill(BDToutSM_kl_1);

    m_plots["centrality_bb" + cat] -> Fill(getSystemCentrality(bjet1_eta, bjet2_eta, bH_eta));
    m_plots["centrality_tautau" + cat] -> Fill(getSystemCentrality(dau1_eta, dau2_eta, tauH_eta));
    

  }

}

void analysisCode::EndJob()
{
  if (isMCSample == 1){
    for (auto &plot : m_plots) {
      cout << plot.first << "-> evt_den: " << evt_den_ << ", integral: " << plot.second->Integral() << endl;  
      if (plot.second->Integral() == 0 || evt_den_ == 0) plot.second->Scale(0.);
      else plot.second -> Scale ((double)lumi_ / (double)evt_den_ );
    }
  }

  cout << "Event statistics for sample " << mySampleName << endl;  
  for (auto & sel: stats ){
    cout << sel.first << " " << sel.second << endl; 
  }

  m_outFile.cd();
  m_outFile.Write();
  m_outFile.Close();
  std::cout << ">>>>>> Finished processing this sample >>>>>>" << endl; 

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

Float_t analysisCode::getSystemCentrality(Float_t eta1, Float_t eta2, Float_t eta){
  Float_t val = (eta - (eta1+eta2)/2)*(eta - (eta1+eta2)/2);
  val = (-4) * val / ((eta1-eta2)*(eta1-eta2));
  return exp(val);
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


Float_t analysisCode::getCosThetaStar_CS(const LorentzVector& h1, const LorentzVector& h2, float ebeam){
  // Copied almost everything from here: https://github.com/ResonantHbbHgg/Selection/blob/master/selection.h#L3367-L3385
  
  TLorentzVector p1, p2;
  p1.SetPxPyPzE(0, 0,  ebeam, ebeam);
  p2.SetPxPyPzE(0, 0, -ebeam, ebeam);

  TLorentzVector hh, h1_t, h2_t; 
  h1_t.SetPxPyPzE(h1.Px(), h1.Py(), h1.Pz(), h1.E());
  h2_t.SetPxPyPzE(h2.Px(), h2.Py(), h2.Pz(), h2.E());
  hh = h1_t + h2_t;

  TVector3 boost = - hh.BoostVector();
  p1.Boost(boost);
  p2.Boost(boost);
  h1_t.Boost(boost);

  TVector3 CSaxis = p1.Vect().Unit() - p2.Vect().Unit();
  CSaxis.Unit();

  return cos(CSaxis.Angle(h1_t.Vect().Unit()));

} 


Float_t  analysisCode::getDeltaRboosted(const LorentzVector& v_0, const LorentzVector& v_1, const LorentzVector& ref){
  using namespace ROOT::Math::VectorUtil; 
  return DeltaR(ROOT::Math::VectorUtil::boost(v_0, ref.BoostToCM()), ROOT::Math::VectorUtil::boost(v_1, ref.BoostToCM()));
}

Float_t analysisCode::getWeights( std::string category ){
  //return 1;
  typedef boost::variant<bool, int, float, double> varType;
  unordered_map<string, varType> valuesMap; 

  //cout << "Adding weights to category " << category << endl; 

  std::vector <std::string> sampleWeights;
  if (cutCfg_->hasOpt(Form("sampleWeights::%s", mySampleName.c_str()))) { 
    sampleWeights = cutCfg_->readStringListOpt(Form("sampleWeights::%s", mySampleName.c_str())); 
  }

  std::vector <std::string> selectionWeights;
  if (cutCfg_->hasOpt(Form("selectionWeights::%s", category.c_str()))) { 
    selectionWeights = cutCfg_->readStringListOpt(Form("selectionWeights::%s", category.c_str())); 
  }
  
  vector<pair<string, float> > weights_ext;
  if (cutCfg_->hasOpt(Form("selectionWeights_ext::%s", category.c_str()))){
    weights_ext = cutCfg_->readStringFloatListOpt(Form("selectionWeights_ext::%s", category.c_str()));
  }

  for (auto &sampleWeight : sampleWeights) {
    valuesMap[sampleWeight] = float(0);
  }
  for (auto &selectionWeight : selectionWeights) {
    valuesMap[selectionWeight] = float(0);
  }

  // Filling external weights

  unordered_map<string, double> extValuesMap; 
  //unordered_map<string, varType> extValuesMap; 
  for (auto &selectionWeight : weights_ext) {
    extValuesMap[selectionWeight.first] = selectionWeight.second;
  }
  
 // Finding weight values for sample and selection weights
  
  
  Float_t myWeight = 1; 
  for (auto & value : valuesMap) {
    //cout << "Trying to apply weight " << value.first << endl;  
    TBranch * myBranch = fChain->GetBranch(value.first.c_str());
    TLeaf * myLeaf = myBranch->GetLeaf(value.first.c_str());
    value.second = myLeaf->GetValue();
  }

  // Applying sample and selection weights
  for (auto & value : valuesMap) {
    myWeight *= boost::apply_visitor(get_variant_as_double(), value.second);
  }

  // Applying external selection weights
  int weightNum = 0; 
  for (auto & value : extValuesMap) {
    //double thisExtWeight = boost::apply_visitor(get_variant_as_double(), value.second);
    double thisExtWeight = value.second;
    //cout << "Tengo el numerito" << endl; 
    TTreeFormula* TTF_extWeight = new TTreeFormula (Form("TTF_extWeight_%i", weightNum), value.first.c_str(), fChain); 
    //cout << "Hago TTF_extWeight" << endl; 
    if (TTF_extWeight->EvalInstance())  {
      //cout << "Calculo EvalInstance y da bien" << endl; 
      myWeight *= thisExtWeight;
    }
    weightNum ++;
  }
  


  return myWeight; 
}

std::vector <std::pair<std::string, std::string>> analysisCode::addRegions (std::vector<std::string> categories) {
  std::vector <std::pair<std::string, std::string>> regions = {};
  for (auto & selection : categories) {
    //cout << selection << endl; 
    bool SR          = (isOS != 0 && dau1_deepTauVsJet >= 5 && dau2_deepTauVsJet >= 5 && strcmp(selection.c_str(), "baseline_tauhtauh" )==0 ) 
                    || (isOS != 0 && dau2_deepTauVsJet >= 4 && strcmp(selection.c_str(), "VBF_baseline" )==0 ) 
                    || (isOS != 0 && dau2_deepTauVsJet >= 4 && strcmp(selection.c_str(), "VBFloose" )==0 ) 
                    || (isOS != 0 && dau2_deepTauVsJet >= 4 && strcmp(selection.c_str(), "VBF_loose_baseline" )==0 ) 
                    || (isOS != 0 && dau1_iso < 0.1 && dau2_deepTauVsJet >= 5 && strcmp(selection.c_str(), "baseline_etauh" )==0 )   
                    || (isOS != 0 && dau1_iso < 0.15 && dau2_deepTauVsJet >= 5 && strcmp(selection.c_str(), "baseline_mutauh" )==0 );// signal region: opposite sign, isolated taus
    bool SStight     = (isOS == 0 && dau1_deepTauVsJet >= 5 && dau2_deepTauVsJet >= 5 && strcmp(selection.c_str(), "baseline_tauhtauh" )==0 )
                    || (isOS == 0 && dau1_iso < 0.1 && dau2_deepTauVsJet >= 5 && strcmp(selection.c_str(), "baseline_etauh" )==0)
                    || (isOS == 0 && dau1_iso < 0.15 && dau2_deepTauVsJet >= 5  && strcmp(selection.c_str(), "baseline_mutauh" )==0); // B region
    bool OSrlx       = (isOS != 0 && dau1_deepTauVsJet >= 5 && dau2_deepTauVsJet >= 2 && strcmp(selection.c_str(), "baseline_tauhtauh" )==0 )
                    || (isOS != 0 && dau1_iso < 0.1 && dau2_deepTauVsJet >= 2 && strcmp(selection.c_str(), "baseline_etauh" )==0)
                    || (isOS != 0 && dau1_iso < 0.15 && dau2_deepTauVsJet >= 2 && strcmp(selection.c_str(), "baseline_mutauh" )==0); 
    bool SSrlx       = (isOS == 0 && dau1_deepTauVsJet >= 5 && dau2_deepTauVsJet >= 2 && strcmp(selection.c_str(), "baseline_tauhtauh" )==0 )
                    || (isOS == 0 && dau1_iso < 0.1 && dau2_deepTauVsJet >= 2 && strcmp(selection.c_str(), "baseline_etauh" )==0 )
                    || (isOS == 0 && dau1_iso < 0.15 && dau2_deepTauVsJet >= 2  && strcmp(selection.c_str(), "baseline_mutauh" )==0 ) ; // B' region
    bool OSinviso    = (isOS != 0 && dau1_deepTauVsJet >= 5 && dau2_deepTauVsJet >= 2 && dau2_deepTauVsJet < 5 && strcmp(selection.c_str(), "baseline_tauhtauh" )==0 )
                    || (isOS != 0 && dau1_iso < 0.1 && dau2_deepTauVsJet >= 2 && dau2_deepTauVsJet < 5 && strcmp(selection.c_str(), "baseline_etauh" )==0 )
                    || (isOS != 0 && dau1_iso < 0.15 && dau2_deepTauVsJet >= 2 && dau2_deepTauVsJet < 5 && strcmp(selection.c_str(), "baseline_mutauh" )==0 ); // C region
    bool SSinviso    = (isOS == 0 && dau1_deepTauVsJet >= 5 && dau2_deepTauVsJet >= 2 && dau2_deepTauVsJet < 5 && strcmp(selection.c_str(), "baseline_tauhtauh" )==0 )
                    || (isOS == 0 && dau1_iso < 0.1 && dau2_deepTauVsJet >= 2 && dau2_deepTauVsJet < 5 && strcmp(selection.c_str(), "baseline_etauh" )==0 )
                    || (isOS == 0 && dau1_iso < 0.15 && dau2_deepTauVsJet >= 2 && dau2_deepTauVsJet < 5 && strcmp(selection.c_str(), "baseline_mutauh" )==0 ); // D region
    
/*    
    bool SR          = (isOS != 0 && dau1_MVAisoNew >= 3 && dau2_MVAisoNew >= 3 && strcmp(selection.c_str(), "baseline_tauhtauh" )==0 )
                     || (isOS != 0 && dau1_iso < 0.15 && dau2_MVAisoNew >= 3 && strcmp(selection.c_str(), "baseline_mutauh" )==0 )
                     || (isOS != 0 && dau1_iso < 0.10 && dau2_MVAisoNew >= 3 && strcmp(selection.c_str(), "baseline_etauh" )==0);
    bool SStight     = (isOS == 0 && dau1_MVAisoNew >= 3 && dau2_MVAisoNew >= 3 && strcmp(selection.c_str(), "baseline_tauhtauh" )==0 )
                     || (isOS == 0 && dau1_iso < 0.15 && dau2_MVAisoNew >= 3 && strcmp(selection.c_str(), "baseline_mutauh" )==0 )
                     || (isOS == 0 && dau1_iso < 0.10 && dau2_MVAisoNew >= 3 && strcmp(selection.c_str(), "baseline_etauh" )==0 );
    bool OSrlx       = (isOS != 0 && dau1_MVAisoNew >= 3 && dau2_MVAisoNew >= 1 && strcmp(selection.c_str(), "baseline_tauhtauh" )==0 )
                     || (isOS != 0 && dau1_iso < 0.15 && dau2_MVAisoNew >= 1 && strcmp(selection.c_str(), "baseline_mutauh" )==0 )
                     || (isOS != 0 && dau1_iso < 0.10 && dau2_MVAisoNew >= 1 && strcmp(selection.c_str(), "baseline_etauh" )==0 );
    bool SSrlx       = (isOS == 0 && dau1_MVAisoNew >= 3 && dau2_MVAisoNew >= 1 && strcmp(selection.c_str(), "baseline_tauhtauh" )==0 )
                     || (isOS == 0 && dau1_iso < 0.15 && dau2_MVAisoNew >= 1 && strcmp(selection.c_str(), "baseline_mutauh" )==0 )
                     || (isOS == 0 && dau1_iso < 0.10 && dau2_MVAisoNew >= 1 && strcmp(selection.c_str(), "baseline_etauh" )==0 );
    bool OSinviso    = (isOS != 0 && dau1_MVAisoNew >= 3 && dau2_MVAisoNew >= 1 && dau2_MVAisoNew < 3 && strcmp(selection.c_str(), "baseline_tauhtauh" )==0 )
                     || (isOS != 0 && dau1_iso < 0.15 && dau2_MVAisoNew >= 1 && dau2_MVAisoNew < 3 && strcmp(selection.c_str(), "baseline_mutauh" )==0 )
                     || (isOS != 0 && dau1_iso < 0.10 && dau2_MVAisoNew >= 1 && dau2_MVAisoNew < 3 && strcmp(selection.c_str(), "baseline_etauh" )==0 );
    bool SSinviso    = (isOS == 0 && dau1_MVAisoNew >= 3 && dau2_MVAisoNew >= 1 && dau2_MVAisoNew < 3 && strcmp(selection.c_str(), "baseline_tauhtauh" )==0 )
                     || (isOS == 0 && dau1_iso < 0.15 && dau2_MVAisoNew >= 1 && dau2_MVAisoNew < 3 && strcmp(selection.c_str(), "baseline_mutauh" )==0 )
                     || (isOS == 0 && dau1_iso < 0.10 && dau2_MVAisoNew >= 1 && dau2_MVAisoNew < 3 && strcmp(selection.c_str(), "baseline_etauh" )==0 );
*/
    
    /*
    bool SR          = (isOS != 0 && dau1_MVAisoNew >= 3 && dau2_MVAisoNew >= 3);
    bool SStight     = (isOS == 0 && dau1_MVAisoNew >= 3 && dau2_MVAisoNew >= 3);
    bool OSrlx       = (isOS != 0 && dau1_MVAisoNew >= 3 && dau2_MVAisoNew >= 1);
    bool SSrlx       = (isOS == 0 && dau1_MVAisoNew >= 3 && dau2_MVAisoNew >= 1);
    bool OSinviso    = (isOS != 0 && dau1_MVAisoNew >= 3 && dau2_MVAisoNew >= 1);
    bool SSinviso    = (isOS == 0 && dau1_MVAisoNew >= 3 && dau2_MVAisoNew >= 1);
*/  

    if (SR) regions.push_back(make_pair(selection, selection+"_SR"));
    if (SStight) regions.push_back(make_pair(selection,selection+"_SStight"));
    if (OSrlx) regions.push_back(make_pair(selection,selection+"_OSrlx")); 
    if (SSrlx) regions.push_back(make_pair(selection,selection+"_SSrlx")); 
    if (OSinviso) regions.push_back(make_pair(selection,selection+"_OSinviso"));
    if (SSinviso) regions.push_back(make_pair(selection,selection+"_SSinviso"));
  }
  return regions; 
}   
   
std::vector <std::string> analysisCode::addCategories () {
   std::vector <std::string> categories = {};

   bool baselinetauhtauh = pairType == 2 && dau1_pt > 40 && abs (dau1_eta) < 2.1 && dau2_pt > 40 && abs (dau2_eta) < 2.1 && nleps == 0 && nbjetscand > 1; // SAME DEF THAN MARCEL
   //bool baselinetauhtauh = pairType == 2 && dau1_pt > 20 && abs (dau1_eta) < 2.1 && dau2_pt > 20 && abs (dau2_eta) < 2.1 && nleps == 0 && nbjetscand > 1;   // DEFAULT
   //bool baselinetauhtauh = pairType == 2 && dau1_pt > 40 && abs (dau1_eta) < 2.1 && dau2_pt > 40 && abs (dau2_eta) < 2.1 && nleps == 0 && nbjetscand > 1;   
   bool baselineetauh    = pairType == 1 && dau1_pt > 20 && abs (dau1_eta) < 2.1 && dau2_pt > 20 && abs (dau2_eta) < 2.3 && nleps == 0 && nbjetscand > 1;
   bool baselinemutauh   = pairType == 0 && dau1_pt > 22 && abs (dau1_eta) < 2.1 && dau2_pt > 20 && abs (dau2_eta) < 2.3 && nleps == 0 && nbjetscand > 1;


   bool baseline55     = (baselinetauhtauh || baselineetauh) && tauH_SVFIT_mass > 50;
   //bool baseline55     = (baselinetauhtauh || baselineetauh || baselinemutauh ) && tauH_SVFIT_mass > 50;
   //bool baselineVBFtight = pairType == 2 && dau1_pt > 25 && abs (dau1_eta) < 2.1 && dau2_pt > 25 && tauH_SVFIT_mass > 50 && abs (dau2_eta) < 2.1 && nleps == 0 && nbjetscand > 1 && isVBFtrigger == 1 && VBFjj_mass > 800 && VBFjet1_pt > 140 && VBFjet2_pt > 60;
   bool baselineVBFloose = baseline55 && isVBF == 1 && VBFjj_mass > 500 && VBFjj_deltaEta > 3;

   //bool btagLL = bjet1_bID_deepCSV > 0.1522 && bjet2_bID_deepCSV > 0.1522;
   //bool btagM  = bjet1_bID_deepCSV > 0.4941 && bjet2_bID_deepCSV < 0.4941;
   //bool btagMM = bjet1_bID_deepCSV > 0.4941 && bjet2_bID_deepCSV > 0.4941; 
   bool btagMfirst = bjet1_bID_deepFlavor > 0.3033;
   //bool ellypsMassCut  = ((tauH_SVFIT_mass-116.)*(tauH_SVFIT_mass-116.))/(35.*35.) + ((bH_mass_raw-111.)*(bH_mass_raw-111.))/(45.*45.) <  1.0;
   //bool boostMassCut = tauH_SVFIT_mass > 79.5 && tauH_SVFIT_mass < 152.5 && fatjet_softdropMass > 90 && fatjet_softdropMass < 160;

   //bool s1b1jresolvedMcut = baselinetauhtauh && btagM &&  isBoosted != 1 && ellypsMassCut && !(isVBF == 1 && VBFjj_mass > 500 && VBFjj_deltaEta > 3 && bjet1_bID_deepCSV > 0.4941);
   //bool s2b0jresolvedMcut = baselinetauhtauh && btagMM && isBoosted != 1 && ellypsMassCut && !(isVBF == 1 && VBFjj_mass > 500 && VBFjj_deltaEta > 3 && bjet1_bID_deepCSV > 0.4941);
   //bool VBFtight_DNN = baselineVBFtight && btagMfirst && BDToutSM_kl_1 > 0 && DNN_VBFvsGGF_TauTauTight > 0.3;
   //bool VBFloose_DNN = baselineVBFloose && btagMfirst && BDToutSM_kl_1 > 0 && DNN_VBFvsGGF_TauTauLoose > 0.4;
   //bool sboostedLLMcut = baselinetauhtauh && btagLL && isBoosted == 1 && boostMassCut && !(isVBF == 1 && VBFjj_mass > 500 && VBFjj_deltaEta > 3 && bjet1_bID_deepCSV > 0.4941);
   bool VBFloose = baselineVBFloose && btagMfirst && BDToutSM_kl_1 > 0;
   //bool VBFtight = baselineVBFtight && btagMfirst && BDToutSM_kl_1 > 0;

   //if (s1b1jresolvedMcut) categories.push_back("s1b1jresolvedMcut");
   //if (s2b0jresolvedMcut) categories.push_back("s2b0jresolvedMcut");
   //f (VBFtight_DNN) categories.push_back("VBFtight_DNN");
   //if (VBFloose_DNN) categories.push_back("VBFloose_DNN");
   //if (sboostedLLMcut) categories.push_back("sboostedLLMcut");
   //if (VBFtight) categories.push_back("VBFtight");
   if (VBFloose) categories.push_back("VBFloose");
   if (baselineVBFloose) categories.push_back("VBF_loose_baseline");
   if (baselinetauhtauh) categories.push_back("baseline_tauhtauh");
   if ((baselinetauhtauh || baselineetauh) && isVBF == 1) categories.push_back("VBF_baseline");
    //if ((baselinetauhtauh || baselineetauh || baselinemutauh) && isVBF == 1) categories.push_back("VBF_baseline");
   if (baselinemutauh) categories.push_back("baseline_mutauh");
   if (baselineetauh) categories.push_back("baseline_etauh");

   return categories; 
}

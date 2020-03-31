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
  std::vector <std::string> categories = {"noSelection","s1b1jresolvedMcut", "s2b0jresolvedMcut", "VBFtight_DNN", "VBFloose_DNN", "sboostedLLMcut", "VBFloose", "VBFtight"};

  m_outFile.cd();

  for (auto & cat : categories) {
    m_plots["lepsPt" + cat]    = new TH1F(("lepsPt_"+ cat).c_str(), "pt from the leptons; lepton pt(GeV); Entries", 200, 0, 200); 

    m_plots["HH_mass"+ cat]   = new TH1F(("HH_mass_"+ cat).c_str(), "HH mass; HH Mass (GeV); Entries", 100, 0, 1000); 
    m_plots["HH_eta"+ cat]    = new TH1F(("HH_eta_"+ cat).c_str(), "HH eta; HH eta; Entries", 100, -2.5, 2.5); 
    m_plots["HH_phi"+ cat]    = new TH1F(("HH_phi_"+ cat).c_str(), "HH phi; HH phi; Entries", 100, -3.5, 3.5); 
    m_plots["HH_pt"+ cat]   = new TH1F(("HH_pt_"+ cat).c_str(), "HH pt; HH pt (GeV); Entries", 100, 0, 500); 
  
    m_plots["HH_deltaPhi"+ cat] = new TH1F(("HH_deltaPhi_"+ cat).c_str(), "HH_deltaPhi; HH_deltaPhi ; Entries", 100, -0.5, 3.5);
    m_plots["HH_deltaEta"+ cat]    = new TH1F(("HH_deltaEta_"+ cat).c_str(), "HH_deltaEta; HH_deltaEta ; Entries", 100, -0.5, 10); 
    m_plots["HH_deltaR"+ cat]    = new TH1F(("HH_deltaR_"+ cat).c_str(), "HH_deltaR; HH_deltaR ; Entries", 100, 0, 10); 

    m_plots["HHsvfit_mass"+ cat]   = new TH1F(("HHsvfit_mass_"+ cat).c_str(), "HH mass; HH Mass (GeV); Entries", 100, 0, 2000); 
    m_plots["HHsvfit_eta"+ cat]    = new TH1F(("HHsvfit_eta_"+ cat).c_str(), "HH eta; HH eta; Entries", 100, -2.5, 2.5); 
    m_plots["HHsvfit_phi"+ cat]    = new TH1F(("HHsvfit_phi_"+ cat).c_str(), "HH phi; HH phi; Entries", 100, -3.5, 3.5); 
    m_plots["HHsvfit_pt"+ cat]   = new TH1F(("HHsvfit_pt_"+ cat).c_str(), "HH pt; HH pt (GeV); Entries", 100, 0, 500); 
    m_plots["HHsvfit_deltaPhi"+ cat] = new TH1F(("HHsvfit_deltaPhi_"+ cat).c_str(), "HH_deltaPhi; HH_deltaPhi ; Entries", 100, -0.5, 3.5);
  
    m_plots["HHKin_mass_raw"+ cat]   = new TH1F(("HHKin_mass_raw_"+ cat).c_str(), "HHKin mass; HHKin Mass (GeV); Entries", 100, 230, 2000); 
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
  
    m_plots["tauH_SVFIT_mass"+ cat] = new TH1F(("tauH_SVFIT_mass_"+ cat).c_str(), "tauH SVFIT mass; tauH Mass (GeV); Entries", 100, 0, 250); 
    m_plots["tauH_SVFIT_pt"+cat]   = new TH1F(("tauH_SVFIT_pt_"+ cat).c_str(), "tauH SVFIT pt; tauH pt (GeV); Entries", 100, 0, 500); 
    m_plots["tauH_SVFIT_eta"+cat]  = new TH1F(("tauH_SVFIT_eta_"+ cat).c_str(), "tauH SVFIT eta; tauH eta ; Entries", 100, -2.5, 2.5); 
    m_plots["tauH_SVFIT_phi"+cat]  = new TH1F(("tauH_SVFIT_phi_"+ cat).c_str(), "tauH SVFIT phi; tauH phi ; Entries", 100, -3.5, 3.5); 
  
  
    m_plots["bH_mass"+ cat]   = new TH1F(("bH_mass_"+ cat).c_str(), "bH mass; bH Mass (GeV); Entries", 100, 0, 250); 
    m_plots["bH_pt"+ cat]     = new TH1F(("bH_pt_"+ cat).c_str(), "bH pt (GeV); bH pt (GeV); Entries", 100, 0, 500); 
    m_plots["bH_eta"+ cat]    = new TH1F(("bH_eta_"+ cat).c_str(), "bH eta; bH eta ; Entries", 100, -2.5, 2.5); 
    m_plots["bH_phi"+ cat]    = new TH1F(("bH_phi_"+ cat).c_str(), "bH phi; bH phi ; Entries", 100, -3.5, 3.5); 

    m_plots["VBFjet1_pt"+ cat]     = new TH1F(("VBFjet1_pt_"+ cat).c_str(), "VBFjet1 pt (GeV); VBFjet1 pt (GeV); Entries", 100, 0, 500); 
    m_plots["VBFjet1_eta"+ cat]    = new TH1F(("VBFjet1_eta_"+ cat).c_str(), "VBFjet1 eta; VBFjet1 eta ; Entries", 100, -2.5, 2.5); 
    m_plots["VBFjet1_phi"+ cat]    = new TH1F(("VBFjet1_phi_"+ cat).c_str(), "VBFjet1 phi; VBFjet1 phi ; Entries", 100, -3.5, 3.5); 
    m_plots["VBFjet2_pt"+ cat]     = new TH1F(("VBFjet2_pt_"+ cat).c_str(), "VBFjet2 pt (GeV); VBFjet2 pt (GeV); Entries", 100, 0, 500); 
    m_plots["VBFjet2_eta"+ cat]    = new TH1F(("VBFjet2_eta_"+ cat).c_str(), "VBFjet2 eta; VBFjet2 eta ; Entries", 100, -2.5, 2.5); 
    m_plots["VBFjet2_phi"+ cat]    = new TH1F(("VBFjet2_phi_"+ cat).c_str(), "VBFjet2 phi; VBFjet2 phi ; Entries", 100, -3.5, 3.5); 

    m_plots["VBFjj_mass"+ cat] = new TH1F(("VBFjj_mass_"+ cat).c_str(), "VBF mass; VBF Mass (GeV); Entries", 100, 0, 2000); 
    m_plots["VBFjj_HT"+ cat] = new TH1F(("VBFjj_HT_"+ cat).c_str(), "VBF HT; VBF HT (GeV); Entries", 100, 0, 500); 
    m_plots["VBFjj_deltaEta"+ cat]    = new TH1F(("VBFjj_deltaEta_"+ cat).c_str(), "VBFjj_deltaEta; VBFjj_deltaEta ; Entries", 100, -0, 10); 
    m_plots["VBFjj_deltaPhi"+ cat]    = new TH1F(("VBFjj_deltaPhi_"+ cat).c_str(), "VBFjj_deltaPhi; VBFjj_deltaPhi ; Entries", 70, -3.5, 3.5); 
    m_plots["VBFjj_deltaR"+ cat]    = new TH1F(("VBFjj_deltaR_"+ cat).c_str(), "VBFjj_deltaR; VBFjj_deltaR ; Entries", 100, 0, 10); 
    m_plots["VBFgenjj_deltaPhi"+ cat]    = new TH1F(("VBFgenjj_deltaPhi_"+ cat).c_str(), "VBFgenjj_deltaPhi; VBFgenjj_deltaPhi ; Entries", 70, -3.5, 3.5); 
  
    m_plots["VBFjTau_deltaR"+ cat]    = new TH1F(("VBFjTau_deltaR_"+ cat).c_str(), "VBFjTau_deltaR; VBFjTau_deltaR ; Entries", 100, 0, 10); 
    m_plots["VBFjb_deltaR"+ cat]    = new TH1F(("VBFjb_deltaR_"+ cat).c_str(), "VBFjb_deltaR; VBFjb_deltaR ; Entries", 100, 0, 10); 

  }
}

void analysisCode::Fill()
{

  std::vector <std::string> categories = addCategories();
  categories.push_back("noSelection");

  for (auto & cat : categories ) {

    for (size_t i = 0; i < leps_pt->size(); i++) {
      m_plots["lepsPt"+cat]->Fill(leps_pt->at(i));
    }
    if (HH_eta != -1. && HH_phi != -1. && HH_pt != -1.) { 
      m_plots["HH_mass"+cat]->Fill( HH_mass );
      m_plots["HH_eta"+cat]->Fill( HH_eta );
      m_plots["HH_phi"+cat]->Fill( HH_phi );
      m_plots["HH_pt"+cat]->Fill( HH_pt );
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
    } else {
      //m_plots["bH_mass"]->Fill( -999. );
      //m_plots["bH_pt"]->Fill( -999. );
      //m_plots["bH_eta"]->Fill( -999. );
      //m_plots["bH_phi"]->Fill( -999. );
    }
    m_plots["VBFjj_mass"+cat]->Fill(VBFjj_mass);
    m_plots["VBFjj_HT"+cat]->Fill(VBFjj_HT); 
    m_plots["VBFjj_deltaEta"+cat]->Fill(VBFjj_deltaEta); 
  

    if (VBFjet1_pt != -999. && VBFjet1_eta != -999. && VBFjet1_phi!=-999. ) {
      m_plots["VBFjet1_pt"+cat]->Fill(VBFjet1_pt);
      m_plots["VBFjet1_eta"+cat]->Fill(VBFjet1_eta);
      m_plots["VBFjet1_phi"+cat]->Fill(VBFjet1_phi);
    }
    if (VBFjet2_pt != -999. && VBFjet2_eta != -999. && VBFjet2_phi!=-999. ) {
      m_plots["VBFjet2_pt"+cat]->Fill(VBFjet2_pt);
      m_plots["VBFjet2_eta"+cat]->Fill(VBFjet2_eta);
      m_plots["VBFjet2_phi"+cat]->Fill(VBFjet2_phi);
    } 
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
 
  }

}

void analysisCode::EndJob()
{
  m_outFile.cd();
  m_outFile.Write();
  m_outFile.Close();
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
  if (phi1 == -999 || phi2 == -999) return -1; 
  auto dp = phi1 - phi2;
  if (dp >= 3.14159) dp = dp - 2*3.14159; 
  if (dp < -3.14159) dp = dp + 2*3.14159; 
  return dp;
}

std::vector <std::string> analysisCode::addCategories () {
   std::vector <std::string> categories = {};

   bool baseline = pairType == 2 && dau1_pt > 40 && abs (dau1_eta) < 2.1 && dau2_pt > 40 && abs (dau2_eta) < 2.1 && nleps == 0 && nbjetscand > 1 && isVBFtrigger == 0 && BDToutSM_kl_1 > 0;   
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

   return categories; 
}

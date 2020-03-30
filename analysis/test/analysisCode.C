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
  m_outFile.cd();
    
  m_plots["lepsPt"]    = new TH1F("lepsPt", "pt from the leptons; lepton pt(GeV); Entries", 200, 0, 200); 

  m_plots["HH_mass"]   = new TH1F("HH_mass", "HH mass; HH Mass (GeV); Entries", 200, 0, 500); 
  m_plots["HH_eta"]    = new TH1F("HH_eta", "HH eta; HH eta; Entries", 200, -2.5, 2.5); 
  m_plots["HH_phi"]    = new TH1F("HH_phi", "HH phi; HH phi; Entries", 200, -3.5, 3.5); 
  m_plots["HH_pt"]   = new TH1F("HH_pt", "HH pt; HH pt (GeV); Entries", 200, 0, 500); 
 
  m_plots["HH_deltaPhi"] = new TH1F("HH_deltaPhi", "HH_deltaPhi; HH_deltaPhi ; Entries", 300, -0.5, 3.5);
  m_plots["HH_deltaEta"]    = new TH1F("HH_deltaEta", "HH_deltaEta; HH_deltaEta ; Entries", 200, -0.5, 10); 
  m_plots["HH_deltaR"]    = new TH1F("HH_deltaR", "HH_deltaR; HH_deltaR ; Entries", 200, 0, 10); 

  m_plots["HHsvfit_mass"]   = new TH1F("HHsvfit_mass", "HH mass; HH Mass (GeV); Entries", 200, 0, 500); 
  m_plots["HHsvfit_eta"]    = new TH1F("HHsvfit_eta", "HH eta; HH eta; Entries", 100, -2.5, 2.5); 
  m_plots["HHsvfit_phi"]    = new TH1F("HHsvfit_phi", "HH phi; HH phi; Entries", 100, -3.5, 3.5); 
  m_plots["HHsvfit_pt"]   = new TH1F("HHsvfit_pt", "HH pt; HH pt (GeV); Entries", 100, 0, 500); 
  m_plots["HHsvfit_deltaPhi"] = new TH1F("HHsvfit_deltaPhi", "HH_deltaPhi; HH_deltaPhi ; Entries", 300, -0.5, 3.5);
  
  m_plots["HHKin_mass_raw"]   = new TH1F("HHKin_mass_raw", "HHKin mass; HHKin Mass (GeV); Entries", 100, 200, 500); 
  m_plots["HHkinsvfit_mass"]   = new TH1F("HHkinsvfit_mass", "HH mass; HH Mass (GeV); Entries", 200, 0, 500); 
  m_plots["HHkinsvfit_eta"]    = new TH1F("HHkinsvfit_eta", "HH eta; HH eta; Entries", 100, -2.5, 2.5); 
  m_plots["HHkinsvfit_phi"]    = new TH1F("HHkinsvfit_phi", "HH phi; HH phi; Entries", 100, -6.5, 6.5); 
  m_plots["HHkinsvfit_pt"]   = new TH1F("HHkinsvfit_pt", "HH pt; HH pt (GeV); Entries", 100, 0, 500); 
  m_plots["HHkinsvfit_bHmass"]   = new TH1F("HHkinsvfit_bHmass", "bH mass; bH Mass (GeV); Entries", 250, 0, 250); 
  m_plots["HHKin_chi2"] = new TH1F("HHKin_chi2", "HHKin chi2; HHKin_chi2; Entries", 250, -0.5, 10); 
  
  m_plots["tauH_mass"] = new TH1F("tauH_mass", "tauH mass; tauH Mass (GeV); Entries", 500, 0, 250); 
  m_plots["tauH_pt"]   = new TH1F("tauH_pt", "tauH pt; tauH pt (GeV); Entries", 200, 0, 500); 
  m_plots["tauH_eta"]  = new TH1F("tauH_eta", "tauH eta; tauH eta ; Entries", 200, -2.5, 2.5); 
  m_plots["tauH_phi"]  = new TH1F("tauH_phi", "tauH phi; tauH phi ; Entries", 200, -3.5, 3.5); 
  
  m_plots["tauH_SVFIT_mass"] = new TH1F("tauH_SVFIT_mass", "tauH SVFIT mass; tauH Mass (GeV); Entries", 500, 0, 250); 
  m_plots["tauH_SVFIT_pt"]   = new TH1F("tauH_SVFIT_pt", "tauH SVFIT pt; tauH pt (GeV); Entries", 100, 0, 500); 
  m_plots["tauH_SVFIT_eta"]  = new TH1F("tauH_SVFIT_eta", "tauH SVFIT eta; tauH eta ; Entries", 200, -2.5, 2.5); 
  m_plots["tauH_SVFIT_phi"]  = new TH1F("tauH_SVFIT_phi", "tauH SVFIT phi; tauH phi ; Entries", 200, -3.5, 3.5); 
  
  
  m_plots["bH_mass"]   = new TH1F("bH_mass", "bH mass; bH Mass (GeV); Entries", 500, 0, 250); 
  m_plots["bH_pt"]     = new TH1F("bH_pt", "bH pt (GeV); bH pt (GeV); Entries", 200, 0, 500); 
  m_plots["bH_eta"]    = new TH1F("bH_eta", "bH eta; bH eta ; Entries", 200, -2.5, 2.5); 
  m_plots["bH_phi"]    = new TH1F("bH_phi", "bH phi; bH phi ; Entries", 200, -4, 4); 


  m_plots["VBFjet1_pt"]     = new TH1F("VBFjet1_pt", "VBFjet1 pt (GeV); VBFjet1 pt (GeV); Entries", 200, 0, 500); 
  m_plots["VBFjet1_eta"]    = new TH1F("VBFjet1_eta", "VBFjet1 eta; VBFjet1 eta ; Entries", 200, -2.5, 2.5); 
  m_plots["VBFjet1_phi"]    = new TH1F("VBFjet1_phi", "VBFjet1 phi; VBFjet1 phi ; Entries", 200, -4, 4); 
  m_plots["VBFjet2_pt"]     = new TH1F("VBFjet2_pt", "VBFjet2 pt (GeV); VBFjet2 pt (GeV); Entries", 200, 0, 500); 
  m_plots["VBFjet2_eta"]    = new TH1F("VBFjet2_eta", "VBFjet2 eta; VBFjet2 eta ; Entries", 200, -2.5, 2.5); 
  m_plots["VBFjet2_phi"]    = new TH1F("VBFjet2_phi", "VBFjet2 phi; VBFjet2 phi ; Entries", 200, -4, 4); 


  m_plots["VBFjj_mass"] = new TH1F("VBFjj_mass", "VBF mass; VBF Mass (GeV); Entries", 250, 0, 1000); 
  m_plots["VBFjj_HT"] = new TH1F("VBFjj_HT", "VBF HT; VBF HT (GeV); Entries", 500, 0, 500); 
  m_plots["VBFjj_deltaEta"]    = new TH1F("VBFjj_deltaEta", "VBFjj_deltaEta; VBFjj_deltaEta ; Entries", 200, -0, 10); 
  m_plots["VBFjj_deltaPhi"]    = new TH1F("VBFjj_deltaPhi", "VBFjj_deltaPhi; VBFjj_deltaPhi ; Entries", 140, -3.5, 3.5); 
  m_plots["VBFjj_deltaR"]    = new TH1F("VBFjj_deltaR", "VBFjj_deltaR; VBFjj_deltaR ; Entries", 200, 0, 10); 
  m_plots["VBFgenjj_deltaPhi"]    = new TH1F("VBFgenjj_deltaPhi", "VBFgenjj_deltaPhi; VBFgenjj_deltaPhi ; Entries", 140, -3.5, 3.5); 
  

  m_plots["VBFjTau_deltaR"]    = new TH1F("VBFjTau_deltaR", "VBFjTau_deltaR; VBFjTau_deltaR ; Entries", 200, 0, 10); 
  m_plots["VBFjb_deltaR"]    = new TH1F("VBFjb_deltaR", "VBFjb_deltaR; VBFjb_deltaR ; Entries", 200, 0, 10); 


}

void analysisCode::Fill()
{
  for (size_t i = 0; i < leps_pt->size(); i++) {
    m_plots["lepsPt"]->Fill(leps_pt->at(i));
  }
  if (HH_eta != -1. && HH_phi != -1. && HH_pt != -1.) { 
    m_plots["HH_mass"]->Fill( HH_mass );
    m_plots["HH_eta"]->Fill( HH_eta );
    m_plots["HH_phi"]->Fill( HH_phi );
    m_plots["HH_pt"]->Fill( HH_pt );
  } else {
    //m_plots["HH_mass"]->Fill( -999. );
    //m_plots["HH_eta"]->Fill( -999. );
    //m_plots["HH_phi"]->Fill( -999. );
    //m_plots["HH_pt"]->Fill( -999. );
  }
  if (HHKin_mass_raw != 0.) m_plots["HHKin_mass_raw"]->Fill( HHKin_mass_raw );
  //else m_plots["HHKin_mass_raw"]->Fill( -999. );
  
  m_plots["HHKin_chi2"]->Fill(HHKin_chi2);
  
  if (HHsvfit_eta != -1. && HHsvfit_phi != -1. && HHsvfit_pt != -1.) { 
    m_plots["HHsvfit_mass"]->Fill( HHsvfit_mass );
    m_plots["HHsvfit_eta"]->Fill( HHsvfit_eta );
    m_plots["HHsvfit_phi"]->Fill( HHsvfit_phi );
    m_plots["HHsvfit_pt"]->Fill( HHsvfit_pt );
    m_plots["HHsvfit_deltaPhi"]->Fill( HHsvfit_deltaPhi );
  } else {
    //m_plots["HHsvfit_mass"]->Fill( -999. );
    //m_plots["HHsvfit_eta"]->Fill( -999. );
    //m_plots["HHsvfit_phi"]->Fill( -999. );
    //m_plots["HHsvfit_pt"]->Fill( -999. );
    //m_plots["HHsvfit_deltaPhi"]->Fill( -999. );
  }
  
  if (HHkinsvfit_eta != -1. && HHkinsvfit_phi != -1. && HHkinsvfit_pt != -1.) { 
    m_plots["HHkinsvfit_eta"]->Fill( HHkinsvfit_eta );
    m_plots["HHkinsvfit_phi"]->Fill( HHkinsvfit_phi );
    m_plots["HHkinsvfit_pt"]->Fill( HHkinsvfit_pt );
    m_plots["HHkinsvfit_bHmass"]->Fill( HHkinsvfit_bHmass );
  } else {
    //m_plots["HHkinsvfit_eta"]->Fill( -999. );
    //m_plots["HHkinsvfit_phi"]->Fill( -999. );
    //m_plots["HHkinsvfit_pt"]->Fill( -999. );
    //m_plots["HHkinsvfit_bHmass"]->Fill( -999. );
  }
  
  if (HH_deltaPhi != -1. && HH_deltaEta != -1. && HH_deltaR != -1.) { 
    m_plots["HH_deltaPhi"]->Fill( HH_deltaPhi );
    m_plots["HH_deltaEta"]->Fill( HH_deltaEta );
    m_plots["HH_deltaR"]->Fill( HH_deltaR );
  } else {
    //m_plots["HH_deltaPhi"]->Fill( -999. );
    //m_plots["HH_deltaEta"]->Fill( -999. );
    //m_plots["HH_deltaR"]->Fill( -999. );
  }
  
  
  if (tauH_mass != -1. && tauH_pt != -1 && tauH_eta!=-1 ) {
    m_plots["tauH_mass"]->Fill( tauH_mass );
    m_plots["tauH_pt"]->Fill( tauH_pt );
    m_plots["tauH_eta"]->Fill( tauH_eta );
    m_plots["tauH_phi"]->Fill( tauH_phi );
  } else {
    //m_plots["tauH_mass"]->Fill( -999. );
    //m_plots["tauH_pt"]->Fill( -999. );
    //m_plots["tauH_eta"]->Fill( -999. );
    //m_plots["tauH_phi"]->Fill( -999. );
  }

  if (tauH_SVFIT_mass != -1. && tauH_SVFIT_pt != -1 && tauH_SVFIT_eta!=-1 ) {
    m_plots["tauH_SVFIT_mass"]->Fill( tauH_SVFIT_mass );
    m_plots["tauH_SVFIT_pt"]->Fill( tauH_SVFIT_pt );
    m_plots["tauH_SVFIT_eta"]->Fill( tauH_SVFIT_eta );
    m_plots["tauH_SVFIT_phi"]->Fill( tauH_SVFIT_phi );
  } else {
    //m_plots["tauH_SVFIT_mass"]->Fill( -999. );
    //m_plots["tauH_SVFIT_pt"]->Fill( -999. );
    //m_plots["tauH_SVFIT_eta"]->Fill( -999. );
    //m_plots["tauH_SVFIT_phi"]->Fill( -999. );
  }

  if (bH_mass != -1. && bH_pt != -1. && bH_eta!=-1. ) {
    m_plots["bH_mass"]->Fill( bH_mass );
    m_plots["bH_pt"]->Fill( bH_pt );
    m_plots["bH_eta"]->Fill( bH_eta );
    m_plots["bH_phi"]->Fill( bH_phi );
  } else {
    //m_plots["bH_mass"]->Fill( -999. );
    //m_plots["bH_pt"]->Fill( -999. );
    //m_plots["bH_eta"]->Fill( -999. );
    //m_plots["bH_phi"]->Fill( -999. );
  }
  m_plots["VBFjj_mass"]->Fill(VBFjj_mass);
  m_plots["VBFjj_HT"]->Fill(VBFjj_HT); 
  m_plots["VBFjj_deltaEta"]->Fill(VBFjj_deltaEta); 
  

  if (VBFjet1_pt != -999. && VBFjet1_eta != -999. && VBFjet1_phi!=-999. ) {
    m_plots["VBFjet1_pt"]->Fill(VBFjet1_pt);
    m_plots["VBFjet1_eta"]->Fill(VBFjet1_eta);
    m_plots["VBFjet1_phi"]->Fill(VBFjet1_phi);
  }
  if (VBFjet2_pt != -999. && VBFjet2_eta != -999. && VBFjet2_phi!=-999. ) {
    m_plots["VBFjet2_pt"]->Fill(VBFjet2_pt);
    m_plots["VBFjet2_eta"]->Fill(VBFjet2_eta);
    m_plots["VBFjet2_phi"]->Fill(VBFjet2_phi);
  }
  if (VBFjet1_phi != -999 && VBFjet2_phi != -999) { 
    m_plots["VBFjj_deltaPhi"]->Fill(getDeltaPhi(VBFjet1_phi,VBFjet2_phi)); 
    m_plots["VBFjj_deltaR"]->Fill( getDeltaR(VBFjet1_eta, VBFjet1_phi, VBFjet2_eta, VBFjet2_phi) ); 
  } else {
//    m_plots["VBFjj_deltaPhi"]->Fill(-999);
//    m_plots["VBFjj_deltaR"]->Fill(-999);
  }
  if (VBFgenjet1_phi != -999 && VBFgenjet2_phi != -999) m_plots["VBFgenjj_deltaPhi"]->Fill(getDeltaPhi(VBFgenjet1_phi, VBFgenjet2_phi)); 
//  else m_plots["VBFgenjj_deltaPhi"]->Fill(-999);

  // Fill VBF(j/tau) plots
  Float_t minDeltaRVBFjTau = 9999; 
  if (getDeltaR(VBFjet1_eta, VBFjet1_phi, dau1_eta, dau1_phi)!=-1) minDeltaRVBFjTau = getDeltaR(VBFjet1_eta, VBFjet1_phi, dau1_eta, dau1_phi);
  if (getDeltaR(VBFjet1_eta, VBFjet1_phi, dau2_eta, dau2_phi)!=-1 && getDeltaR(VBFjet1_eta, VBFjet1_phi, dau2_eta, dau2_phi) < minDeltaRVBFjTau) minDeltaRVBFjTau = getDeltaR(VBFjet1_eta, VBFjet1_phi, dau2_eta, dau2_phi);
  if (getDeltaR(VBFjet2_eta, VBFjet2_phi, dau1_eta, dau1_phi)!=-1 && getDeltaR(VBFjet2_eta, VBFjet2_phi, dau1_eta, dau1_phi) < minDeltaRVBFjTau) minDeltaRVBFjTau = getDeltaR(VBFjet2_eta, VBFjet2_phi, dau1_eta, dau1_phi);
  if (getDeltaR(VBFjet2_eta, VBFjet2_phi, dau2_eta, dau2_phi)!=-1 && getDeltaR(VBFjet2_eta, VBFjet2_phi, dau2_eta, dau2_phi) < minDeltaRVBFjTau) minDeltaRVBFjTau = getDeltaR(VBFjet2_eta, VBFjet2_phi, dau2_eta, dau2_phi);

  if (minDeltaRVBFjTau!=9999) m_plots["VBFjTau_deltaR"]->Fill(minDeltaRVBFjTau);

  Float_t minDeltaRVBFjb = 9999; 
  if (getDeltaR(VBFjet1_eta, VBFjet1_phi, bjet1_eta, bjet1_phi)!=-1) minDeltaRVBFjb = getDeltaR(VBFjet1_eta, VBFjet1_phi, bjet1_eta, bjet1_phi);
  if (getDeltaR(VBFjet1_eta, VBFjet1_phi, bjet2_eta, bjet2_phi)!=-1 && getDeltaR(VBFjet1_eta, VBFjet1_phi, bjet2_eta, bjet2_phi) < minDeltaRVBFjTau) minDeltaRVBFjb = getDeltaR(VBFjet1_eta, VBFjet1_phi, bjet2_eta, bjet2_phi);
  if (getDeltaR(VBFjet2_eta, VBFjet2_phi, bjet1_eta, bjet1_phi)!=-1 && getDeltaR(VBFjet2_eta, VBFjet2_phi, bjet1_eta, bjet1_phi) < minDeltaRVBFjTau) minDeltaRVBFjb = getDeltaR(VBFjet2_eta, VBFjet2_phi, bjet1_eta, bjet1_phi);
  if (getDeltaR(VBFjet2_eta, VBFjet2_phi, bjet2_eta, bjet2_phi)!=-1 && getDeltaR(VBFjet2_eta, VBFjet2_phi, bjet2_eta, bjet2_phi) < minDeltaRVBFjTau) minDeltaRVBFjb = getDeltaR(VBFjet2_eta, VBFjet2_phi, bjet2_eta, bjet2_phi);

  if (minDeltaRVBFjb!=9999) m_plots["VBFjb_deltaR"]->Fill(minDeltaRVBFjb);
  
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

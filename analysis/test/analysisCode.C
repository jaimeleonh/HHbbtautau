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

  m_plots["HH_mass"]   = new TH1F("HH_mass", "HH mass; HH Mass (GeV); Entries", 500, 0, 500); 
  m_plots["HH_eta"]    = new TH1F("HH_eta", "HH eta; HH eta; Entries", 200, -2.5, 2.5); 
  m_plots["HH_phi"]    = new TH1F("HH_phi", "HH phi; HH phi; Entries", 200, -4, 4); 
  m_plots["HH_pt"]   = new TH1F("HH_pt", "HH pt; HH pt (GeV); Entries", 200, 0, 500); 
 
  m_plots["HH_deltaPhi"] = new TH1F("HH_deltaPhi", "HH_deltaPhi; HH_deltaPhi ; Entries", 300, -0, 4);
  m_plots["HH_deltaEta"]    = new TH1F("HH_deltaEta", "HH_deltaEta; HH_deltaEta ; Entries", 200, -0, 10); 
  m_plots["HH_deltaR"]    = new TH1F("HH_deltaR", "HH_deltaR; HH_deltaR ; Entries", 200, 0, 10); 

  m_plots["HHsvfit_mass"]   = new TH1F("HHsvfit_mass", "HH mass; HH Mass (GeV); Entries", 200, 0, 500); 
  m_plots["HHsvfit_eta"]    = new TH1F("HHsvfit_eta", "HH eta; HH eta; Entries", 100, -2.5, 2.5); 
  m_plots["HHsvfit_phi"]    = new TH1F("HHsvfit_phi", "HH phi; HH phi; Entries", 100, -4, 4); 
  m_plots["HHsvfit_pt"]   = new TH1F("HHsvfit_pt", "HH pt; HH pt (GeV); Entries", 100, 0, 500); 
  m_plots["HHsvfit_deltaPhi"] = new TH1F("HHsvfit_deltaPhi", "HH_deltaPhi; HH_deltaPhi ; Entries", 300, -10, 10);
  
  m_plots["HHKin_mass_raw"]   = new TH1F("HHKin_mass_raw", "HHKin mass; HHKin Mass (GeV); Entries", 200, 0, 500); 
  m_plots["HHkinsvfit_mass"]   = new TH1F("HHkinsvfit_mass", "HH mass; HH Mass (GeV); Entries", 200, 0, 500); 
  m_plots["HHkinsvfit_eta"]    = new TH1F("HHkinsvfit_eta", "HH eta; HH eta; Entries", 100, -2.5, 2.5); 
  m_plots["HHkinsvfit_phi"]    = new TH1F("HHkinsvfit_phi", "HH phi; HH phi; Entries", 100, -6.5, 6.5); 
  m_plots["HHkinsvfit_pt"]   = new TH1F("HHkinsvfit_pt", "HH pt; HH pt (GeV); Entries", 100, 0, 500); 
  m_plots["HHkinsvfit_bHmass"]   = new TH1F("HHkinsvfit_bHmass", "bH mass; bH Mass (GeV); Entries", 2500, 0, 250); 
  
  
  m_plots["tauH_mass"] = new TH1F("tauH_mass", "tauH mass; tauH Mass (GeV); Entries", 500, 0, 250); 
  m_plots["tauH_pt"]   = new TH1F("tauH_pt", "tauH pt; tauH pt (GeV); Entries", 200, 0, 500); 
  m_plots["tauH_eta"]  = new TH1F("tauH_eta", "tauH eta; tauH eta ; Entries", 200, -2.5, 2.5); 
  m_plots["tauH_phi"]  = new TH1F("tauH_phi", "tauH phi; tauH phi ; Entries", 200, -6.5, 6.5); 
  
  m_plots["tauH_SVFIT_mass"] = new TH1F("tauH_SVFIT_mass", "tauH SVFIT mass; tauH Mass (GeV); Entries", 500, 0, 250); 
  m_plots["tauH_SVFIT_pt"]   = new TH1F("tauH_SVFIT_pt", "tauH SVFIT pt; tauH pt (GeV); Entries", 200, 0, 500); 
  m_plots["tauH_SVFIT_eta"]  = new TH1F("tauH_SVFIT_eta", "tauH SVFIT eta; tauH eta ; Entries", 200, -2.5, 2.5); 
  m_plots["tauH_SVFIT_phi"]  = new TH1F("tauH_SVFIT_phi", "tauH SVFIT phi; tauH phi ; Entries", 200, -4, 4); 
  
  
  m_plots["bH_mass"]   = new TH1F("bH_mass", "bH mass; bH Mass (GeV); Entries", 500, 0, 250); 
  m_plots["bH_pt"]     = new TH1F("bH_pt", "bH pt (GeV); bH pt (GeV); Entries", 200, 0, 500); 
  m_plots["bH_eta"]    = new TH1F("bH_eta", "bH eta; bH eta ; Entries", 200, -2.5, 2.5); 
  m_plots["bH_phi"]    = new TH1F("bH_phi", "bH phi; bH phi ; Entries", 200, -4, 4); 

  m_plots["VBFjj_mass"] = new TH1F("VBFjj_mass", "VBF mass; VBF Mass (GeV); Entries", 250, 0, 1000); 
  m_plots["VBFjj_HT"] = new TH1F("VBFjj_HT", "VBF HT; VBF HT (GeV); Entries", 500, 0, 500); 
  m_plots["VBFjj_deltaEta"]    = new TH1F("VBFjj_deltaEta", "VBFjj_deltaEta; VBFjj_deltaEta ; Entries", 200, -0, 10); 
  m_plots["VBFjj_deltaPhi"]    = new TH1F("VBFjj_deltaPhi", "VBFjj_deltaPhi; VBFjj_deltaPhi ; Entries", 300, -10, 10); 
  m_plots["VBFgenjj_deltaPhi"]    = new TH1F("VBFgenjj_deltaPhi", "VBFgenjj_deltaPhi; VBFgenjj_deltaPhi ; Entries", 300, -10, 10); 
  



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
    m_plots["HH_mass"]->Fill( -999. );
    m_plots["HH_eta"]->Fill( -999. );
    m_plots["HH_phi"]->Fill( -999. );
    m_plots["HH_pt"]->Fill( -999. );
  }
  if (HHKin_mass_raw != 0.) m_plots["HHKin_mass_raw"]->Fill( HHKin_mass_raw );
  else m_plots["HHKin_mass_raw"]->Fill( -999. );

  if (HHsvfit_eta != -1. && HHsvfit_phi != -1. && HHsvfit_pt != -1.) { 
    m_plots["HHsvfit_mass"]->Fill( HHsvfit_mass );
    m_plots["HHsvfit_eta"]->Fill( HHsvfit_eta );
    m_plots["HHsvfit_phi"]->Fill( HHsvfit_phi );
    m_plots["HHsvfit_pt"]->Fill( HHsvfit_pt );
    m_plots["HHsvfit_deltaPhi"]->Fill( HHsvfit_deltaPhi );
  } else {
    m_plots["HHsvfit_mass"]->Fill( -999. );
    m_plots["HHsvfit_eta"]->Fill( -999. );
    m_plots["HHsvfit_phi"]->Fill( -999. );
    m_plots["HHsvfit_pt"]->Fill( -999. );
    m_plots["HHsvfit_deltaPhi"]->Fill( -999. );
  }
  
  if (HHkinsvfit_eta != -1. && HHkinsvfit_phi != -1. && HHkinsvfit_pt != -1.) { 
    m_plots["HHkinsvfit_eta"]->Fill( HHkinsvfit_eta );
    m_plots["HHkinsvfit_phi"]->Fill( HHkinsvfit_phi );
    m_plots["HHkinsvfit_pt"]->Fill( HHkinsvfit_pt );
    m_plots["HHkinsvfit_bHmass"]->Fill( HHkinsvfit_bHmass );
  } else {
    m_plots["HHkinsvfit_eta"]->Fill( -999. );
    m_plots["HHkinsvfit_phi"]->Fill( -999. );
    m_plots["HHkinsvfit_pt"]->Fill( -999. );
    m_plots["HHkinsvfit_bHmass"]->Fill( -999. );
  }
  
  if (HH_deltaPhi != -1. && HH_deltaEta != -1. && HH_deltaR != -1.) { 
    m_plots["HH_deltaPhi"]->Fill( HH_deltaPhi );
    m_plots["HH_deltaEta"]->Fill( HH_deltaEta );
    m_plots["HH_deltaR"]->Fill( HH_deltaR );
  } else {
    m_plots["HH_deltaPhi"]->Fill( -999. );
    m_plots["HH_deltaEta"]->Fill( -999. );
    m_plots["HH_deltaR"]->Fill( -999. );
  }
  
  
  if (tauH_mass != -1. && tauH_pt != -1 && tauH_eta!=-1 ) {
    m_plots["tauH_mass"]->Fill( tauH_mass );
    m_plots["tauH_pt"]->Fill( tauH_pt );
    m_plots["tauH_eta"]->Fill( tauH_eta );
    m_plots["tauH_phi"]->Fill( tauH_phi );
  } else {
    m_plots["tauH_mass"]->Fill( -999. );
    m_plots["tauH_pt"]->Fill( -999. );
    m_plots["tauH_eta"]->Fill( -999. );
    m_plots["tauH_phi"]->Fill( -999. );
  }

  if (tauH_SVFIT_mass != -1. && tauH_SVFIT_pt != -1 && tauH_SVFIT_eta!=-1 ) {
    m_plots["tauH_SVFIT_mass"]->Fill( tauH_SVFIT_mass );
    m_plots["tauH_SVFIT_pt"]->Fill( tauH_SVFIT_pt );
    m_plots["tauH_SVFIT_eta"]->Fill( tauH_SVFIT_eta );
    m_plots["tauH_SVFIT_phi"]->Fill( tauH_SVFIT_phi );
  } else {
    m_plots["tauH_SVFIT_mass"]->Fill( -999. );
    m_plots["tauH_SVFIT_pt"]->Fill( -999. );
    m_plots["tauH_SVFIT_eta"]->Fill( -999. );
    m_plots["tauH_SVFIT_phi"]->Fill( -999. );
  }

  if (bH_mass != -1. && bH_pt != -1. && bH_eta!=-1. ) {
    m_plots["bH_mass"]->Fill( bH_mass );
    m_plots["bH_pt"]->Fill( bH_pt );
    m_plots["bH_eta"]->Fill( bH_eta );
    m_plots["bH_phi"]->Fill( bH_phi );
  } else {
    m_plots["bH_mass"]->Fill( -999. );
    m_plots["bH_pt"]->Fill( -999. );
    m_plots["bH_eta"]->Fill( -999. );
    m_plots["bH_phi"]->Fill( -999. );
  }
  m_plots["VBFjj_mass"]->Fill(VBFjj_mass);
  m_plots["VBFjj_HT"]->Fill(VBFjj_HT); 
  
  
  
  
  
  m_plots["VBFjj_deltaEta"]->Fill(VBFjj_deltaEta); 
  if (VBFjet1_phi != -999 && VBFjet2_phi != -999) m_plots["VBFjj_deltaPhi"]->Fill(VBFjet1_phi - VBFjet2_phi); 
  else m_plots["VBFjj_deltaPhi"]->Fill(-999);
  if (VBFgenjet1_phi != -999 && VBFgenjet2_phi != -999) m_plots["VBFgenjj_deltaPhi"]->Fill(VBFgenjet1_phi - VBFgenjet2_phi); 
  else m_plots["VBFgenjj_deltaPhi"]->Fill(-999);
}

void analysisCode::EndJob()
{
  m_outFile.cd();
  m_outFile.Write();
  m_outFile.Close();
}

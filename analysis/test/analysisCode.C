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
   Long64_t nentries = fChain->GetEntriesFast();
   std::cout << "Total entries = " << nentries << endl;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      if (jentry == 100000) break;
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
  m_plots["tauH_mass"] = new TH1F("tauH_mass", "tauH mass; tauH Mass (GeV); Entries", 500, 0, 250); 
  m_plots["tauH_pt"]   = new TH1F("tauH_pt", "tauH pt; tauH pt (GeV); Entries", 200, 0, 200); 
  m_plots["tauH_eta"]  = new TH1F("tauH_eta", "tauH eta; tauH eta ; Entries", 200, -2.5, 2.5); 
  m_plots["bH_mass"]   = new TH1F("bH_mass", "bH mass; bH Mass (GeV); Entries", 500, 0, 250); 
  m_plots["bH_pt"]     = new TH1F("bH_pt", "bH pt (GeV); Entries", 200, 0, 200); 
  m_plots["bH_eta"]    = new TH1F("bH_eta", "bH eta; bH eta ; Entries", 200, -2.5, 2.5); 

}

void analysisCode::Fill()
{
  for (size_t i = 0; i < leps_pt->size(); i++) {
    m_plots["lepsPt"]->Fill(leps_pt->at(i));
  } 
  m_plots["HH_mass"]->Fill( HH_mass );
  m_plots["tauH_mass"]->Fill( tauH_mass );
  m_plots["tauH_pt"]->Fill( tauH_pt );
  m_plots["tauH_eta"]->Fill( tauH_eta );
  m_plots["bH_mass"]->Fill( bH_mass );
  m_plots["bH_pt"]->Fill( bH_pt );
  m_plots["bH_eta"]->Fill( bH_eta );
}

void analysisCode::EndJob()
{
  m_outFile.cd();
  m_outFile.Write();
  m_outFile.Close();
}

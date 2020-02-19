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
//   In a ROOT session, you can do:
//      root> .L analysisCode.C
//      root> analysisCode t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
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
    
  m_plots["lepsPt"] = new TH1F("lepsPt", "pt from the leptons; lepton pt(GeV); Entries", 200, 0, 200); 
  m_plots["HH_mass"] = new TH1F("HH_mass", "HH mass; HH Mass (GeV); Entries", 500, 0, 500); 
  m_plots["tauH_mass"] = new TH1F("tauH_mass", "tauH mass; tauH Mass (GeV); Entries", 500, 0, 250); 
  m_plots["bH_mass"] = new TH1F("bH_mass", "bH mass; bH Mass (GeV); Entries", 500, 0, 250); 

}

void analysisCode::Fill()
{
  for (size_t i = 0; i < leps_pt->size(); i++) {
    m_plots["lepsPt"]->Fill(leps_pt->at(i));
  } 
  m_plots["HH_mass"]->Fill( HH_mass );
  m_plots["tauH_mass"]->Fill( tauH_mass );
  m_plots["bH_mass"]->Fill( bH_mass );
}

void analysisCode::EndJob()
{
  m_outFile.cd();
  m_outFile.Write();
  m_outFile.Close();
}

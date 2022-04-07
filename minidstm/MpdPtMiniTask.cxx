// skelet

#ifndef ROOT_MpdPtMiniTask
#include "MpdPtMiniTask.h"
#endif

#include <TLorentzVector.h>
#include "FairRootManager.h"
#include "MpdMCTrack.h"
#include "MpdTrack.h"
#include "MpdMiniDstReader.h"
#include "MpdMiniTrack.h"
#include "MpdMiniMcTrack.h"

#include <iostream>
using std::cout;
using std::endl;

// -----   Default constructor ---------------------------------------
MpdPtMiniTask::MpdPtMiniTask():
  FairTask(),
  fEventCounter(0)
{
}

// -----   constructor with names ------------------------------------
MpdPtMiniTask::MpdPtMiniTask(const char *name, const char *title):
  FairTask(name),
  fEventCounter(0)
{
}

// -----   Destructor -----------------------------------------------
MpdPtMiniTask::~MpdPtMiniTask()
{}

// -------------------------------------------------------------------
InitStatus MpdPtMiniTask::Init()
{
  cout<<"\n-I- [MpdPtMiniTask::Init] " <<endl;  
  
  FairRootManager *manager = FairRootManager::Instance();
  fMCTracks = (TClonesArray *) manager->GetObject("McTrack");
  if(fMCTracks == nullptr) return kFATAL;
  fDstEvent = (TClonesArray *) manager->GetObject("Track");
  if(fDstEvent == nullptr) return kFATAL;
   
 
  Register();
  
  fhistPt = new TH1F("fhistPt","p_{T} distribution; p_{T}(GeV/c); 1/N_{ev} dN/dp_{T}",400,0,10);
  fhistPtMC = new TH1F("fhistPtMC","MC p_{T} distribution; p_{T}(GeV/c); 1/N_{ev} dN/dp_{T}",400,0,10);
  fhistPtMC->SetLineColor(kRed);


  fPDG = TDatabasePDG::Instance();

  return kSUCCESS;
}

// -------------------------------------------------------------------
void MpdPtMiniTask::Exec(Option_t * option)
{
  fEventCounter++;
  cout<<"-I- [MpdPtMiniTask::Exec] " << "{" << fEventCounter << "}" <<endl;
    
  Int_t nTracks = fDstEvent->GetEntriesFast();  
  
  cout << "N of Reconstructed tracks = " << nTracks << endl;
    
  /* 
   * Get pT distribution
   */
 
  const Double_t cut_pt = 0.15; // default: 0.15 GeV/c
  const Double_t cut_eta = 0.5; // default: 0.5
  const Int_t cut_nhits = 16;   // default: 16
  const Double_t dca_cut = 0.5; // default: 0.5 cm
 
  /* Events loop */
  for (Int_t i = 0; i < nTracks; i++)
  {
	MpdMiniTrack *track = (MpdMiniTrack *) fDstEvent->UncheckedAt(i);

        TVector3 gptotal = track->gMom();
        TVector3 gdcaor = track->origin();
       
        Double_t pt = track->gPt();
        Double_t eta = 0.5*TMath::Log((gptotal.Mag()+gptotal.Z())/(gptotal.Mag()-gptotal.Z()+1.e-13));
        Int_t nhits = track->nHits();
	
      if (TMath::Abs(pt) < cut_pt) continue;
      if (TMath::Abs(eta) > cut_eta) continue;
      if (nhits < cut_nhits) continue;

      // Primary track selection

      Bool_t isprimarytrack     = track->isPrimary(); 
      if (isprimarytrack != 1) continue;
    
      fhistPt->Fill(TMath::Abs(pt));
  }
  /* End of events loop */
  
  /* Events loop. The same but for MC */
  Int_t nMCTracks = fMCTracks->GetEntriesFast();  
  
  cout << "N of MC tracks = " << nMCTracks << endl;
  
  for (Int_t i = 0; i < nMCTracks; i++)
  {
    MpdMiniMcTrack *MCtrack = (MpdMiniMcTrack*) fMCTracks->UncheckedAt(i);

    Double_t ptmc=TMath::Sqrt(MCtrack->px()*MCtrack->px() + MCtrack->py()*MCtrack->py());
    TVector3 P(MCtrack->px(),MCtrack->py(),MCtrack->pz());
    Double_t etamc=0.5*TMath::Log((P.Mag() + MCtrack->pz())/(P.Mag() - MCtrack->pz()+1.e-13));
    
    Int_t abspdg = TMath::Abs(MCtrack->pdgId());
 
    if (MCtrack->isFromGenerator()==kFALSE)continue; //only primaries 

     if (ptmc < cut_pt) continue;
     if(TMath::Abs(etamc) > cut_eta) continue;
 
     if(abspdg == 211 || abspdg == 321 || abspdg == 2212)fhistPtMC->Fill(ptmc);
    }
  /* End of MC events loop */

}

// -------------------------------------------------------------------
void MpdPtMiniTask::Reset()
{}

// -------------------------------------------------------------------
void MpdPtMiniTask::Finish()
{
  //cout<<"\n-I- [MpdPtMiniTask::Finish] "<< endl;
  
  Double_t scale = 1./ (Double_t) fEventCounter;
  
  fhistPt->Scale(scale); // scale to total number of events
  fhistPtMC->Scale(scale); // scale to total number of events

  fhistPt->Write("");
  fhistPtMC->Write("");
}

// -------------------------------------------------------------------
void MpdPtMiniTask::Register()
{
  //FairRootManager::Instance()->Register("MCTrack", "MC", fMCTracks, kTRUE);
}


// -------------------------------------------------------------------
ClassImp(MpdPtMiniTask);

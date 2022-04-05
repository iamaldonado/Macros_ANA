// skelet

#ifndef ROOT_MpdPtTask
#include "MpdPtTask.h"
#endif

#include <TLorentzVector.h>
#include "FairRootManager.h"
#include "MpdMCTrack.h"
#include "MpdTrack.h"

#include <iostream>
using std::cout;
using std::endl;

// -----   Default constructor ---------------------------------------
MpdPtTask::MpdPtTask():
  FairTask(),
  fEventCounter(0)
{}

// -----   constructor with names ------------------------------------
MpdPtTask::MpdPtTask(const char *name, const char *title):
  FairTask(name),
  fEventCounter(0)
{}

// -----   Destructor -----------------------------------------------
MpdPtTask::~MpdPtTask()
{}

// -------------------------------------------------------------------
InitStatus MpdPtTask::Init()
{
  cout<<"\n-I- [MpdPtTask::Init] " <<endl;  
  
  FairRootManager *manager = FairRootManager::Instance();

  fMCTracks = (TClonesArray *) manager->GetObject("MCTrack");
  fDstEvent = (MpdEvent *) manager->GetObject("MPDEvent.");
  Register();
  
  fhistPt = new TH1F("fhistPt","p_{T} distribution; p_{T}(GeV/c); 1/N_{ev} dN/dp_{T}",400,0,10);
//  fhistPt->GetXaxis()->SetTitle("p_{T}(GeV/c)");
  fhistPtMC = new TH1F("fhistPtMC","MC p_{T} distribution; p_{T}(GeV/c); 1/N_{ev} dN/dp_{T}",400,0,10);
//  fhistPtMC->GetXaxis()->SetTitle("p_{T}(GeV/c)");
  fhistPtMC->SetLineColor(kRed);


  fPDG = TDatabasePDG::Instance();

  return kSUCCESS;
}

// -------------------------------------------------------------------
void MpdPtTask::Exec(Option_t * option)
{
  fEventCounter++;
  cout<<"-I- [MpdPtTask::Exec] " << "{" << fEventCounter << "}" <<endl;
    
  //MpdEvent *mpdEvent = fDstEvent; // one event by one event
  //event->Dump(); 
  TClonesArray *mpdTracks = fDstEvent->GetGlobalTracks();
  Int_t nTracks = mpdTracks->GetEntriesFast();
  
  cout << "N of Reconstructed tracks = " << nTracks << endl;
    
  //mpdTracks->Dump();
  
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
	MpdTrack *track = (MpdTrack *) mpdTracks->UncheckedAt(i);
	//if ( !track->GetTofFlag() ) continue;  // no tof identification
       
        Double_t pt = track->GetPt();
        Double_t eta = track->GetEta();
        Int_t nhits = track->GetNofHits();
	
      if (TMath::Abs(pt) < cut_pt) continue;
      if (TMath::Abs(eta) > cut_eta) continue;
      if (nhits < cut_nhits) continue;

      // Primary track selection
      if (TMath::Sqrt(TMath::Power(track->GetDCAX(),2) + TMath::Power(track->GetDCAY(),2) + TMath::Power(track->GetDCAZ(),2)) > dca_cut) continue;
    
      fhistPt->Fill(TMath::Abs(pt));
  }
  /* End of events loop */
  
  /* Events loop. The same but for MC */
  Int_t nMCTracks = fMCTracks->GetEntriesFast();  
  
  cout << "N of MC tracks = " << nMCTracks << endl;
  
  for (Int_t i = 0; i < nMCTracks; i++)
  {
    MpdMCTrack *MCtrack = (MpdMCTrack*) fMCTracks->UncheckedAt(i);

    Double_t ptmc=MCtrack->GetPt();
    TVector3 P(MCtrack->GetPx(),MCtrack->GetPy(),MCtrack->GetPz());
    Double_t etamc=0.5*TMath::Log((P.Mag() + MCtrack->GetPz())/(P.Mag() - MCtrack->GetPz()+1.e-13));
    
    Int_t abspdg = TMath::Abs(MCtrack->GetPdgCode());
 
    if (MCtrack->GetMotherId()!=-1)continue; //only primaries 

     if (ptmc < cut_pt) continue;
     if(TMath::Abs(etamc) > cut_eta) continue;
 
     if(abspdg == 211 || abspdg == 321 || abspdg == 2212)fhistPtMC->Fill(ptmc);
    }
  /* End of MC events loop */

}

// -------------------------------------------------------------------
void MpdPtTask::Reset()
{}

// -------------------------------------------------------------------
void MpdPtTask::Finish()
{
  //cout<<"\n-I- [MpdPtTask::Finish] "<< endl;
  
  Double_t scale = 1./ (Double_t) fEventCounter;
  
  fhistPt->Scale(scale); // scale to total number of events
  fhistPtMC->Scale(scale); // scale to total number of events

  fhistPt->Write("");
  fhistPtMC->Write("");
}

// -------------------------------------------------------------------
void MpdPtTask::Register()
{
  //FairRootManager::Instance()->Register("MCTrack", "MC", fMCTracks, kTRUE);
}


// -------------------------------------------------------------------
ClassImp(MpdPtTask);

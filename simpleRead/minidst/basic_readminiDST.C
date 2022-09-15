//Some basic headers
#include <vector>
#include "Rtypes.h"
#include "TChain.h"
#include "TFile.h"

//MPD useful packages
R__ADD_INCLUDE_PATH($VMCWORKDIR)
#include "mpdloadlibs.C"

 
 TH1F *hCHtrack 	   = new TH1F("hCHtrack","Charged tracks Distribution (Reco)",150,0,1500); // Charged particles distribution histogram
 TH1F *hRecTrack_hits      = new TH1F("hRecTrack_hits","hRecTrack_hits",100,0,50);
 TH1F *hRecTrack_rapidity = new TH1F("hRecTrack_rapidity"," Charged tracks Rapidity Distribution (Reco)",1000,-10,10); 
 TH1F *hRecTrack_pT 	   = new TH1F("hRecTrack_pT","Charged tracks p_{T} Distribution (Reco)",3200,-16,16); 
 TH1F *hRecTrack_eta 	   = new TH1F("hRecTrack_eta"," Charged tracks eta Distribution (Reco)",3200,-16,16);
 TH1F *hRecTrack_phi 	   = new TH1F("hRecTrack_phi"," Charged tracks phi Distribution (Reco)",3200,-16,16); 

 TH1F *hRecTrack_DCAX = new TH1F("hRecTrack_DCAX"," tracks DCAX (Reco) ",100,-20,20); // DCA distribution
 TH1F *hRecTrack_DCAY = new TH1F("hRecTrack_DCAY"," tracks DCAY (Reco)",100,-20,20); 
 TH1F *hRecTrack_DCAZ = new TH1F("hRecTrack_DCAZ"," tracks DCAZ (Reco)",100,-60,60); 
 
 TH2D *hetapt = new TH2D("hetapt","hetapt",500,-2.5,2.5,60,0,2);
 TH2D *hetaptc = new TH2D("hetaptc","hetaptc",340,-1.7,1.7,60,0,2);

char name[50];
const Char_t * Particle[6]={"ch","pi","k","p","Kp","Km"};

//_______________________________________________________________________________________
void basic_readminiDST(const Char_t* inFileName, int myevents, TString outFileName ) {
  
  // Begin new class to read inFileName
  MpdMiniDstReader* miniDstReader = new MpdMiniDstReader(inFileName);

  TH1F *hRefMult = new TH1F("hRefMultSTAR","hRefMultSTAR",2500,0,2500);
  TH2F *hBvsRefMult = new TH2F("hBvsRefMult","hBvsRefMult",2500,0,2500,200,0.,20.);

  TH1F *hRefMultMC = new TH1F("hRefMultSTARMC","hRefMultSTARMC",2500,0,2500);
  TH2F *hBvsRefMultMC = new TH2F("hBvsRefMultMC","hBvsRefMultMC",2500,0,2500,200,0.,20.);


  TH1F *hRapidity = new TH1F("hRapidity","hRapidity",200,-10,10);
  TH1F *hRapidityMC = new TH1F("hRapidityMC","hRapidityMC",200,-10,10);

TH1F *hpt[6]={0,0,0,0,0,0};
TH1F *hptMC[6]={0,0,0,0,0,0};
for(Int_t ipart=0;ipart<6;++ipart){
hpt[ipart]=new TH1F(Form("hpt_%s",Particle[ipart]),Form("%s p_{T} Distribution",Particle[ipart]),100,0,10);
hptMC[ipart]=new TH1F(Form("hptmc_%s",Particle[ipart]),Form("%s p_{T} MC Distribution",Particle[ipart]),100,0,10);
}






  TFile *fo = new TFile(outFileName.Data(),"RECREATE");  
  //Initialize reader
  miniDstReader->Init();
  //================= The branches of miniDST than I need
  
  // Turn off all branches
  miniDstReader->SetStatus("*", 0);  
  // Turn on specific branch:             
  miniDstReader->SetStatus("Event*", 1);          
  miniDstReader->SetStatus("Track*", 1);
  miniDstReader->SetStatus("BTofHit*", 1);
  miniDstReader->SetStatus("BTofPidTraits*", 1);
  miniDstReader->SetStatus("BECalCluster*", 1);
  miniDstReader->SetStatus("FHCalHit*", 1);
  // Turn off specific branch:
  miniDstReader->SetStatus("TrackCovMatrix*", 0);
   
  miniDstReader->SetStatus("McEvent*", 1);
  miniDstReader->SetStatus("McTrack*", 1);
  
  // For mpd reconstruced tracks
  
  Float_t nRecoTracks, mpdTrack_px, mpdTrack_py, mpdTrack_pz, mpdTrack_P, mpdTrack_Eta, mpdTrack_AbsEta, mpdTrack_pT,mpdTrack_phi;
  Int_t mpdTrack_charge, mpdtrack_pdg;
  Float_t NumSimTracks =0;
  // For mc simulated tracks
  
  Float_t mc_px, mc_py, mc_pz, mc_P, mc_Eta, mc_AbsEta, mc_pT;
  Int_t mc_charge;

  //==================================================//
  //            Begin loop of events                    //
  //==================================================//

  //Get number of events of file
  Long64_t events2read = miniDstReader->chain()->GetEntries();

  for (Long64_t i = 0; i < myevents; i++) {

    Bool_t  isOk = miniDstReader->readMiniEvent( i );

    // Retrieve current miniDst (from the given .MiniDst.root file)
    MpdMiniDst *dst = miniDstReader->miniDst();

    
    // Get MiniEvent information
    MpdMiniEvent *event = dst->event();
    Int_t evID = event->eventId();
    
    MpdMiniMcEvent *mcEvent = dst->mcEvent(); // For the McEvents
    
    // Get primary vertex z-position
    Float_t vertexX = event->primaryVertex().X();
    Float_t vertexY = event->primaryVertex().Y();
    Float_t vertexZ = event->primaryVertex().Z();

    Float_t b       = mcEvent->b(); // From MC

    Float_t NumRecoTracks =0;
    Long_t n_tracks_mpd=0;
    //print number of events
    cout << "N. event: " << i << endl;
    //cout << "Event RECO ID " << evID <<  endl; 
  
    
  //==================================================//
  //		Begin loop of RECO TRACKS		//
  //==================================================//

    // Get number of reconstructed tracks
    Int_t nRecoTracks = dst->numberOfTracks();
    Float_t primaryTrackCounter = 0;

    
    //print number of reconstructed tracks in this event
    //cout << "Total number of reco tracks: " << nRecoTracks << endl;
    
    for (Int_t j = 0; j < nRecoTracks; j++) {
    

      
      // Get jth reconstructed track
      MpdMiniTrack *miniTrack = dst->track(j);
      
      // Bool_t hasmc 		= miniTrack->hasMcTrack();
      //Float_t mcIndex  	= miniTrack->mcTrackIndex();
      Bool_t isprimarytrack 	= miniTrack->isPrimary();
      
      //if (mcIndex < 1) continue;
      //if (hasmc == false) continue;
      
      TVector3 mpdTrack_ptot 	= miniTrack->pMom(); // Primary tracks momentum
      mpdTrack_px	= mpdTrack_ptot.X();
      mpdTrack_py	= mpdTrack_ptot.Y();
      mpdTrack_pz	= mpdTrack_ptot.Z();
      Int_t nHits       = miniTrack->nHits();
      mpdTrack_P 	= miniTrack->pMom().Mag();  //Get P magnitude
      mpdTrack_Eta 	= 0.5*TMath::Log((mpdTrack_P+mpdTrack_pz)/(mpdTrack_P-mpdTrack_pz));
      mpdTrack_AbsEta 	= TMath::Abs(mpdTrack_Eta);
      mpdTrack_pT	= miniTrack->pPt(); //          (p for primaries, g for global tracks) 
      mpdTrack_phi 	= TMath::ATan2(mpdTrack_py,mpdTrack_px);

      mpdTrack_charge	= miniTrack->charge();
        	
      Float_t dcaX = miniTrack->gDCAx(vertexX);
      Float_t dcaY = miniTrack->gDCAy(vertexY);
      Float_t dcaZ = miniTrack->gDCAz(vertexZ);
      Float_t DCA  = TMath::Sqrt(dcaX*dcaX+dcaY*dcaY+dcaZ*dcaZ);   
	
      // Filling histograms for charged particles
      if (nHits<16) continue;
      if (isprimarytrack != 1) continue;
      if (mpdTrack_charge == 0) continue;
      hetapt->Fill(mpdTrack_Eta,mpdTrack_pT);
      if(TMath::Abs(mpdTrack_Eta)>0.5) continue;
      if(mpdTrack_pT<0.15) continue;
//      if(TMath::Abs(DCA)>0.5) continue;
      hetaptc->Fill(mpdTrack_Eta,mpdTrack_pT);
      hRecTrack_pT->Fill(mpdTrack_pT);
      hRecTrack_eta->Fill(mpdTrack_Eta);
      hRecTrack_phi->Fill(mpdTrack_phi);
      hRecTrack_hits->Fill(nHits);  
      NumRecoTracks++;
      n_tracks_mpd++;
    } //end of reco tracks loop
  hCHtrack->Fill(n_tracks_mpd);
  hRefMult->Fill(n_tracks_mpd);
  hBvsRefMult->Fill(n_tracks_mpd, b);
  } // end jentry loops

  fo->cd();
  hRecTrack_pT->Write();
  hRecTrack_eta->Write();
  hRecTrack_phi->Write();
  hRecTrack_hits->Write();
  hetapt->Write();
  hetaptc->Write();
  hRefMult->Write();
  hBvsRefMult->Write();
  fo->Close();          
 //+++++++++++++++++++++++++++++++++++++++++++++
 

  // Finalize miniDst reader
}

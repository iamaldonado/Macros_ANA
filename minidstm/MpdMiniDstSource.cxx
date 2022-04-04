/*
 * MpdMiniDstSource.cxx
 *
 *  Created on: 17 kwi 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */

#include "MpdMiniDstSource.h"

#include <FairLogger.h>
#include <FairRootManager.h>
#include <TChain.h>
#include <TClonesArray.h>
#include <TTree.h>
#include <fstream>

MpdMiniDstSource::MpdMiniDstSource() : MpdMiniDstSource("data.root") {}

MpdMiniDstSource::MpdMiniDstSource(TString inFile) :
  fChain(nullptr),
  fEvent(nullptr),
  fTracks(nullptr),
  fTofInfo(nullptr),
  fEmcInfo(nullptr),
  fMcEvent(nullptr),
  fMcTracks(nullptr),
  fMaxEventsNo(0) {
  fFileName.push_back(inFile);
}

Bool_t MpdMiniDstSource::Init() {
  FairRootManager* mngr = FairRootManager::Instance();
  fChain                = new TChain("MiniDst");
  if (fFileName[0].EndsWith(".root")) {
    LOG(DEBUG3) << "MpdMiniDstSource: opening root file(s)" << fFileName[0];
    for (unsigned int j = 0; j < fFileName.size(); j++) {
      fChain->Add(fFileName[j], 0);
    }
  } else {  // this is long list
    for (unsigned int j = 0; j < fFileName.size(); j++) {
      std::ifstream list;
      list.open(fFileName[j]);
      int no = 1;
      do {
        TString temp;
        list >> temp;
        if (temp.Length() > 1) {
          fChain->Add(temp);
        } else {
          break;
        }
        LOG(DEBUG3) << "Adding file no.\t" << no++ << "\t" << temp << " to chain";
      } while (!list.eof());
      list.close();
    }
  }

  fChain->SetBranchStatus("Event", 1);
  fChain->SetBranchStatus("Track", 1);
  fChain->SetBranchStatus("BTofPidTraits", 1);
  //    fChain->SetBranchStatus("")
  fChain->SetBranchStatus("McEvent", 1);
  fChain->SetBranchStatus("McTrack", 1);
  fEvent    = new TClonesArray("MpdMiniEvent");
  fMcEvent  = new TClonesArray("MpdMiniMcEvent");
  fTracks   = new TClonesArray("MpdMiniTrack");
  fTofInfo  = new TClonesArray("MpdMiniBTofPidTraits");
  fEmcInfo  = new TClonesArray("MpdMiniBECalCluster");
  fMcTracks = new TClonesArray("MpdMiniMcTrack");

  fChain->SetBranchAddress("Event", &fEvent);
  fChain->SetBranchAddress("Track", &fTracks);
  fChain->SetBranchAddress("BTofPidTraits", &fTofInfo);
  fChain->SetBranchAddress("McEvent", &fMcEvent);
  fChain->SetBranchAddress("McTrack", &fMcTracks);
  fMaxEventsNo = fChain->GetEntries();

  mngr->SetInChain(fChain, -1);
  mngr->Register("Event", "DST", fEvent, kFALSE);
  mngr->Register("Track", "DST", fTracks, kFALSE);
  mngr->Register("BTofPidTraits", "TOF", fTofInfo, kFALSE);
  mngr->Register("McEvent", "MC", fMcEvent, kFALSE);
  mngr->Register("McTrack", "MC", fMcTracks, kFALSE);
  return kTRUE;
}

Int_t MpdMiniDstSource::ReadEvent(UInt_t unsignedInt) {
  fChain->GetEntry(unsignedInt);
  return 0;
}

void MpdMiniDstSource::Close() {}

Int_t MpdMiniDstSource::CheckMaxEventNo(Int_t int1) { return fMaxEventsNo; }

MpdMiniDstSource::MpdMiniDstSource(const MpdMiniDstSource& other) {
  fFileName    = other.fFileName;
  fMaxEventsNo = other.fMaxEventsNo;
  if (!other.fChain) { Init(); }
}

MpdMiniDstSource::~MpdMiniDstSource() {}

void MpdMiniDstSource::AddFile(TString file) { fFileName.push_back(file); }

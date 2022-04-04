/*
 * MpdMiniDstSource.h
 *
 *  Created on: 17 kwi 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef NICAMINIDSTSOURCE_H_
#define NICAMINIDSTSOURCE_H_

#include <FairSource.h>
#include <TString.h>

#include <vector>


class TChain;
class TClonesArray;
/**
 * class for reading minidst files with FairRunAna
 */

class MpdMiniDstSource : public FairSource {
  std::vector<TString> fFileName;
  TChain* fChain;
  TClonesArray* fEvent;
  TClonesArray* fTracks;
  TClonesArray* fTofInfo;
  TClonesArray* fEmcInfo;
  TClonesArray* fMcEvent;
  TClonesArray* fMcTracks;
  Int_t fMaxEventsNo;

public:
  MpdMiniDstSource();
  MpdMiniDstSource(const MpdMiniDstSource& other);
  MpdMiniDstSource(TString inFile);
  virtual void AddFile(TString file);
  virtual Bool_t Init();
  virtual Int_t ReadEvent(UInt_t = 0);
  virtual void Close();
  virtual void Reset() {};
  virtual Bool_t ActivateObject(TObject**, const char*) { return kFALSE; }
  virtual Source_Type GetSourceType() { return kFILE; };
  virtual void SetParUnpackers() {};
  virtual Bool_t InitUnpackers() { return kTRUE; };
  virtual Bool_t ReInitUnpackers() { return kTRUE; };
  virtual Int_t CheckMaxEventNo(Int_t = 0);
  virtual void ReadBranchEvent(const char* BrName) {};
  virtual void ReadBranchEvent(const char* BrName, Int_t Event) {};
  virtual void FillEventHeader(FairEventHeader* feh) {};
  void SetRunId(Int_t runId) { fRunId = runId; }
  Int_t GetRunId() const { return fRunId; }
  virtual Bool_t SpecifyRunId() { return kFALSE; };
  virtual ~MpdMiniDstSource();
  ClassDef(MpdMiniDstSource, 1)
};

#endif /* MPDROOT_NICA_MPD_FORMAT_MPDMC_NICAMINIDSTSOURCE_H_ */

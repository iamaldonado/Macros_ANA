// skelet

#ifndef ROOT_MpdPtMiniTask
#define ROOT_MpdPtMiniTask
#ifndef ROOT_FairTask
#include "FairTask.h"
#endif

#include <TDatabasePDG.h>
#include <TH1F.h>

#include "MpdEvent.h"

class MpdPtMiniTask : public FairTask {
private:
    UInt_t fEventCounter; //! event counter
    TDatabasePDG*  fPDG;  //!  PDG database

    TClonesArray *fDstEvent; // dst event
    TClonesArray *fMCTracks; // array of MC tracks
    
    TH1F *fhistPt; // Pt rec
    TH1F *fhistPtMC; // Pt MC

public:

  MpdPtMiniTask();
  MpdPtMiniTask(const char *name, const char *title="MPD Analysis");
  virtual ~MpdPtMiniTask();	// Destructor

    virtual void Exec(Option_t * option);
    virtual InitStatus Init(); // Init before Exec
    virtual void Finish(); // Finish after Exec

    void  Reset(); //
    void  Register(); // Register what do you want to write to file
    void  SetOption(Option_t *option=" ") {fOption = option;  fOption.ToLower();}

  ClassDef(MpdPtMiniTask,0)
};

#endif

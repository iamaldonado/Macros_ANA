// skelet

#ifndef ROOT_MpdPtTask
#define ROOT_MpdPtTask
#ifndef ROOT_FairTask
#include "FairTask.h"
#endif

#include <TDatabasePDG.h>
#include <TH1F.h>

#include "MpdEvent.h"

class MpdPtTask : public FairTask {

private:
    UInt_t fEventCounter; //! event counter
    TDatabasePDG*  fPDG;  //!  PDG database

    MpdEvent *fDstEvent; // dst event
    TClonesArray *fMCTracks; // array of MC tracks
    
    TH1F *fhistPt;
    TH1F *fhistPtMC;

public:

  MpdPtTask();
  MpdPtTask(const char *name, const char *title="MPD Analysis");
  virtual ~MpdPtTask();	// Destructor

    virtual void Exec(Option_t * option);
    virtual InitStatus Init(); // Init before Exec
    virtual void Finish(); // Finish after Exec

    void  Reset(); //
    void  Register(); // Register what do you want to write to file
    void  SetOption(Option_t *option=" ") {fOption = option;  fOption.ToLower();}

  ClassDef(MpdPtTask,0)
};

#endif

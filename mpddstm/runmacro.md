# Macro for run analysis with mpddst files

This macro call the FairRunAna class and its structure is similar to runReco.C macro:

```ruby
#if !defined(__CINT__) && !defined(__CLING__)
// ROOT includes
#include "TString.h"
#include "TStopwatch.h"
#include "TSystem.h"
#include "TChain.h"
// Fair includes
#include "FairRunAna.h"
#include "FairFileSource.h"
#include "FairRuntimeDb.h"
#include "FairParRootFileIo.h"
#include "FairTask.h"
#include "FairField.h"
//
#include "MpdPtTask.h"

#include <iostream>
using namespace std;
#endif

#include "commonFunctions.C"

void runanalysis(TString inFile = "/eos/nica/mpd/sim/data/exp/dst-BiBi-09.2GeV-mp06-21-500ev/BiBi/09.2GeV-mb/UrQMD/BiBi-09.2GeV-mp06-21-500ev/urqmd-BiBi-09.2GeV-mb-eos0-500-347.reco.root", TString outFile = "outputana0.root", Int_t nStartEvent =0, Int_t nEvents =500){

// -----   Timer   --------------------------------------------------------
     TStopwatch timer;
        timer.Start();

FairRunAna* fRun;
if (!CheckFileExist(inFile)) return;
        fRun = new FairRunAna();

    FairSource* fFileSource = new FairFileSource(inFile);
    fRun->SetSource(fFileSource);
    fRun->SetOutputFile(outFile); // [WARN] FairRun::SetOutputFile() deprecated. Use FairRootFileSink.
    fRun->SetGenerateRunInfo(false);
    fRun->SetUseFairLinks(true);

TString parFile = inFile;

    FairTask* physics = new MpdPtTask("MpdPhysicstask","task");
    fRun->AddTask(physics);

  fRun->Init();
  fRun->Run(nStartEvent, nStartEvent + nEvents);
 
    // -----   Finish   -------------------------------------------------------
         timer.Stop();
         Double_t rtime = timer.RealTime();
         Double_t ctime = timer.CpuTime();
         cout << endl << endl;
         cout << "Macro finished successfully." << endl;      // marker of successful execution for CDASH
         cout << "Output file is " << outFile << endl;
         cout << "Parameter file is " << parFile << endl;
         cout << "Real time " << rtime << " s, CPU time " << ctime << " s" << endl;
         cout << endl;

}
```

The FairTask allows you to include your analysis task

| [:arrow_left: previous](dictionary.md)| [main:arrow_up:](../README.md) | [next :arrow_right:](../minidstm/runmacro.md) |

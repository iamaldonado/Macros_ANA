#if !defined(__CINT__) && !defined(__CLING__)
// ROOT includes
#include "TString.h"
#include "TStopwatch.h"
#include "TSystem.h"
#include "TChain.h"
//
// Fair includes
#include "FairRunAna.h"
#include "FairFileSource.h"
#include "FairRuntimeDb.h"
#include "FairParRootFileIo.h"
#include "FairTask.h"
#include "FairField.h"
//
#include "MpdPtMiniTask.h"
#include "MpdRoInvMassTask.h"

#include <iostream>
using namespace std;
#endif

#include "../mpd/macros/common/commonFunctions.C"

void runmini(TString inFile = "MiniDst.root", TString outFile = "outmini.root", Int_t nStartEvent =0, Int_t nEvents =500){

// -----   Timer   --------------------------------------------------------
     TStopwatch timer;
        timer.Start();


FairRunAna* fRun;
if (!CheckFileExist(inFile)) return;
        fRun = new FairRunAna();

    MpdMiniDstSource* fFileSource = new MpdMiniDstSource(inFile);
    fRun->SetSource(fFileSource);
    fRun->SetOutputFile(outFile); // [WARN] FairRun::SetOutputFile() deprecated. Use FairRootFileSink.
    fRun->SetGenerateRunInfo(false);
    fRun->SetUseFairLinks(true);

TString parFile = inFile;

    FairTask* physics = new MpdPtMiniTask("MpdPhysicstask","task");
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

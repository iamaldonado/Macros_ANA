# Analysis Task for mpddst files

The code used in mpdroot is written in form of C++ *classes*. Each class is stored in its own header (*.h*) and implementation file (*.cxx*). To read mpddst files we can write our own class which is derived from **FairTask**.

The example class **MpdPtTask** shown here, read mpddst.root files and gives the transverse momentum distribution of reconstructed tracks and generated tracks. Because is derived from FairTask, it shares the common base methods, defined in the header file

## Functions in the Header file .h


- **Constructors and Destructors**: Are  standard C++ features, called each time an Instance of the class is created or deleted.

```
MpdPtTask::MpdPtTask() // default constructor
MpdPtTask::MpdPtTask(const char *name, const char *title) // constructor with names
MpdPtTask::∼MpdPtTask() // destructor
```
- **Initialization of objects**: In this function we can define the output objects of the analysis, like histograms and trees. In this case the histograms of transverse momentum distribution.

```
InitStatus MpdPtTask::Init() // objects to fill (trees, histograms, profiles, etc.)
```
- **Execution and process of analysis**: This function is called for each event. This function is the event loop. 

```
void MpdPtTask::Exec(Option_t *option) // event loop function
```
- **Finish()**: Called at the end of analysis. In this example to store the histograms

```
void MpdPtTask::Finish(); // To store the files
```

## Functions in the implementation files .cxx

-  **Init Status MpdPtTask::Init()**:
   - This function call the branches in the tree stored in the mpddst file, implementing the FairRootManager. In this example we call the generated tracks (*MCTrack*) and the reconstructed events (*MPDEvent.*). 

```ruby
FairRootManager *manager = FairRootManager::Instance();
fMCTracks = (TClonesArray *) manager->GetObject(”MCTrack”);
fDstEvent = (MpdEvent *) manager->GetObject(”MPDEvent.”);
Register();

```
   - The output objects like histograms, also are defined here, in this case a TH1F histograms for the transverse Momentum distribution in generated and reconstructed tracks.

```
fhistPt = new TH1F(”fhistPt”,”p_T distribution; p_T(GeV/c); 1/N_evdN/dp_T”,400,0,10);
fhistPtMC = new TH1F(”fhistPtMC”,”MC p_T distribution; p_T(GeV/c);1/N_evdN/dp_T”,400,0,10);
```

- **MpdPtTask::Exec(Option_t option)**:
  - This FUnction describes the event loop, fill the array mpdTracks with the global tracks stored in the event (fDstEvent) called in the Init function. Get the number of tracks that is going to be used for the loop; in which assign each element like an MpdTrack, to obtain the different variables, in this case transverse momentum. In the case of generated tracks is similar. 

```
TClonesArray *mpdTracks = fDstEvent->GetGlobalTracks(); 
Int_t nTracks = mpdTracks->GetEntriesFast();
for (Int_t i = 0; i < nTracks; i++){
MpdTrack *track = (MpdTrack *) mpdTracks->UncheckedAt(i);
fhistpt->Fill(track->GetPt());
}
```

- **MpdPtTask::Finish()**
  - In this part we store the output objects in the output file.

```
fhistPt->Write(””);
fhistPtMC->Write(””);
```  


| [:arrow_left: previous](../simpleRead/minidst/README.md)| [main:arrow_up:](../README.md) | [next :arrow_right:](../minidstm/README.md) |


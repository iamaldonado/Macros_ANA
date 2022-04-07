# Analysis Task for minidst files

The content of the class [**MpdPtMiniTask**](MpdPtMiniTask.h) also is derived from FairTask, and its structure is similar to the class to read mpddst files. The differences appear on the [implementation file](MpdPtMiniTask.cxx), in the functions:

- **InitStatus MpdPtMiniTask::Init()**: In the name of the branches for generated and reconstructed tracks

```ruby
  fMCTracks = (TClonesArray *) manager->GetObject("McTrack");
  if(fMCTracks == nullptr) return kFATAL;
  fDstEvent = (TClonesArray *) manager->GetObject("Track");
  if(fDstEvent == nullptr) return kFATAL;
``` 
-**MpdPtMiniTask::Exec(Option_t * option)**: The function assign the MpdMiniTrack to the reconstructed tracks and the MpdMiniTrack to the generated tracks.  
```ruby
MpdMiniTrack *track = (MpdMiniTrack *) fDstEvent->UncheckedAt(i); // reconstructed tracks

MpdMiniMcTrack *MCtrack = (MpdMiniMcTrack*) fMCTracks->UncheckedAt(i); //generated tracks
```
Also the methods need to be changed in agreement with the definition in the assigned classes, for example for reconstructed tracks in mpddst files

> Double_t pt = track->GetPt();

change to

> Double_t pt = track->gPt();

for the minidst files. In a similar way for the generated tracks

> Double_t ptmc=MCtrack->GetPt();

 change to 

> Double_t ptmc=TMath::Sqrt(MCtrack->px()*MCtrack->px() + MCtrack->py()*MCtrack->py());

# Additional Class to read minidst files

To read the tree in the minidst file, we need in our mpdroot version, the class [MpdMiniDstSource](MpdMiniDstSource.h). In case that it does not appear, we can copy the class in the same folder in which we have the class to read the minidst files.

| [:arrow_left: previous](../mpddstm/README.md)| [main:arrow_up:](../README.md) | [next :arrow_right:](../mpddstm/dictionary.md) |


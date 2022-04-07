#Analysis Task for minidst files

The content of the class [**MpdPtMiniTask**](MpdPtMiniTask.h) also is derived from FairTask, and its structure is similar to the class to read mpddst files. The differences appear on the implementation file, in the functions:

- **InitStatus MpdPtMiniTask::Init()**: In the name of the branches for generated and reconstructed tracks

```ruby
  fMCTracks = (TClonesArray *) manager->GetObject("McTrack");
  if(fMCTracks == nullptr) return kFATAL;
  fDstEvent = (TClonesArray *) manager->GetObject("Track");
  if(fDstEvent == nullptr) return kFATAL;
``` 
-**MpdPtMiniTask::Exec(Option_t * option)**: The function assign the MpdMiniTrack to the reconstructed tracks and the MpdMiniMcTrack to the generated tracks



| [:arrow_left: previous](../mpddstm/README.md)| [main:arrow_up:](../README.md) | [next :arrow_right:](../README.md) |


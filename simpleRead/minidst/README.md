# Simple Macro basic_readminiDST.C

This simple macro[basic_readminiDST.C](https://github.com/iamaldonado/Macros_ANA/tree/main/simpleRead/minidst/basic_readminiDST.C),
can be run for only one or for several files.


 1. Run for only one file.
 Write the following instruction: 

```ruby
root basic_readminiDST.C'("inputFile",Nev,"outputfile")'
```

in which inputFile is the path to the mpddst.MiniDst.root file, Nev is the number of events to be analyzed and outputfile is the name of the root (test.root) file in which is going to be stored the histograms of the analysis
 
 2. For several files.

First you need a file name.list with a list of the mpddst.MiniDst.root files, for example:

*filename.list*
> /eos/nica/mpd/sim/data/MiniDst/dst-BiBi-09.2GeV-mp02-21-500ev/BiBi/09.2GeV-mb/UrQMD/BiBi-09.2GeV-mp02-21-500ev/urqmd-BiBi-09.2GeV-mb-eos0-500-29970.reco.MiniDst.root
> /eos/nica/mpd/sim/data/MiniDst/dst-BiBi-09.2GeV-mp02-21-500ev/BiBi/09.2GeV-mb/UrQMD/BiBi-09.2GeV-mp02-21-500ev/urqmd-BiBi-09.2GeV-mb-eos0-500-29971.reco.MiniDst.root
> /eos/nica/mpd/sim/data/MiniDst/dst-BiBi-09.2GeV-mp02-21-500ev/BiBi/09.2GeV-mb/UrQMD/BiBi-09.2GeV-mp02-21-500ev/urqmd-BiBi-09.2GeV-mb-eos0-500-29972.reco.MiniDst.root
> /eos/nica/mpd/sim/data/MiniDst/dst-BiBi-09.2GeV-mp02-21-500ev/BiBi/09.2GeV-mb/UrQMD/BiBi-09.2GeV-mp02-21-500ev/urqmd-BiBi-09.2GeV-mb-eos0-500-29973.reco.MiniDst.root

then is possible to run the analysis with:

```ruby
root basic_readminiDST.C'("filename.list",2000,"test.root")'

```
Notice that you can restrict the analysis a few number of events, choosing a smaller number of Nev.


## Basic structure of macro 

The class used is __MpdMiniDstReader__ which allows to initialize the reader to call the branches to be used in the analysis with:

```ruby 
MpdMiniDstReader* miniDstReader = new MpdMiniDstReader(inFileName);
miniDstReader->Init();
```
with the following line, all the branches (\*) are turn off (option 0):

```ruby
miniDstReader->SetStatus("*", 0); 
```

and we can only turn on an specific branch with the name of the branch and option 1

```ruby
  miniDstReader->SetStatus("McEvent*", 1);
```

In the macro appears the following options

```ruby
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
```

The recovery of information from miniDst files is done with the __MpdMiniDst__ class through the instruction:

```ruby
MpdMiniDst *dst = miniDstReader->miniDst();
```

The information for each branch is managed for a different class and a function to retrieve the information as appears in the following table

|Branch|Class |Function|
|------|------|------|
|Event|MpdMiniEvent|event()|
|Track|MpdMiniTrack|track(Int\_t i)|
|BTofHit|MpdMiniBTofHit|btofHit(Int\_t i)|
|BTofPidTraits|MpdMiniBTofPidTraits|btofPidTraits(Int\_t i)|
|BeCalCluster|MpdMiniBECalCluster|becalCluster(Int\_t i)|
|TrackCovMatrix|MpdMiniTrackCovMatrix|trackCovMatrix(Int\_t i)|
|FHCalHit|MpdMiniFHCalHit|fhcalHit(Int\_t i)|
|McEvent|MpdMiniMcEvent|mcEvent()|
|MCTrack|MpdMiniMcTrack|mcTrack(Int\_t i)|

for example the information for the MiniEvent or MiniMcEvent  is obtained with
```ruby
MpdMiniEvent *event = dst->event();
MpdMiniMcEvent *mcEvent = dst->mcEvent(); 
```
In the case of tracks or hits, is required a loop over the number of tracks or hits in that branch 

```ruby 
MpdMiniTrack *miniTrack = dst->track(j);
``` 



| [:arrow_left: previous](../mpddst/README.md)| [main:arrow_up:](../../README.md) | [next :arrow_right:](../../mpddstm/README.md) |


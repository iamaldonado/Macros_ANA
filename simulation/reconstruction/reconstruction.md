### Reconstruction with macro runReco.C

The reconstruction procedure gives the final output with simulated data. This macro reads the output File **evetest.root** of runMC.C macro, if your macro is in the same folder, to run it you just need to run it writing in the terminal:

> root -b -q runReco.C

The output files could be only **mpddst.root** or also **minidst.root** files. To change the name of the input and output files and also the number of reconstructed events you can modify the following line in the macro

```ruby
void runReco(TString inFile = "evetest.root", TString outFile = "mpddst.root", Int_t nStartEvent = 0, Int_t nEvents = 10, TString run_type = "local")
```

The principal classes in the macro are the FairRunAna class that manage the reconstruction process and the clases that configure it, like: 

- FairSource, that manage the input files
- MpdKalmanFilter,
- MpdTpcHitProducer,
- MpdVertexZfinder,
- MpdFfdHitProducer,
- etc..

## mpddst.root file

The output file contains the tree **mpdsim** with different branches that stores information of the generated tracks MCTracks, reconstructed tracks, MpdEvent, vertex information, etc.

To open the file and visualize the content you can do it from the terminal with root

> root mpddst.root
> TBrowser n

and then browse in the content on the file
<img src=mpddstcmp.png>


| [:arrow_left: previous](../transport/transport.md)| [main:arrow_up:](../../README.md) | [next :arrow_right:](../../simpleRead/mpddst/README.md) |

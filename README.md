
<img src="mpd-logo_v2_small.png">

# Welcome to the Analysis Tutorial

In this repository you will find some macros to perform analysis within [mpdroot](http://mpdroot.jinr.ru) framework for the MPD (Multi-Purpose Detector) experiment at the NICA (Nuclotron-based Ion Collider fAcility) project. 

## Introduction

After run macros runMC.C and runReco.C from [mpdroot](https://git.jinr.ru/nica/mpdroot/-/tree/dev/macros/common) framework we can get two types of files: mpddst.root and mpddst.MiniDst.root which contains the required information of reconstructed particles to do analysis. In the following sections we will describe the basics of this, the macros available and explanations of how to use them.

The available outputs are: 

 * **mpddst files**. The mpdsim Tree contains the different branches: EventHeader, TpcKalmanTrack, Vertex, FfdHit, TOFHit, TOFMatching, ZdcDigi, MCEventHeader, MCTrack, MPDEvent.


 * **minidst files**. The MiniDst Tree contains the different branches: Event, Track, BTofHit, BTofPidTraits, BECalCluster, TrackCovMatrix, FHCalHit, McEvent, McTrack. 

### Start with a Simple macro to Read Files

This kind of macros can be used with both, the user and developer installationof mpdroot.

 * [Read mpdst files](simpleRead/mpddst)
 * [Read minidst files](simpleRead/minidst)

### Create a simple Task

To implement this tasks, we need the mpdroot developer version, to add the clases and compile it.

 * [For mpddst files](mpddstm)
 * [For minidst files](minidstm)

### Compile mpdroot with your analysis class

We need to create a folder in mpdroot with our class and the [CMakeList.txt and LinkDef.h](mpddstm/dictionary.md) files to tell which classes should be added to the dictionary.

### Macro to run the analysis with your class

This will allows you to implement your task and add several analysis task at the same time. The structure differs for [mpddst files](mpddstm/runmacro.md) with respect to [minidst files](minidstm/runmacro.md)


## Links
|Description|Repository|
|------|------|
|The Principal page of software|[mpdroot](http://mpdroot.jinr.ru/)
|Macros for simulation and transport|[common](https://git.jinr.ru/nica/mpdroot/-/tree/dev/macros/common)|
|Macros for physical analysis|[mpd](https://git.jinr.ru/nica/mpdroot/-/tree/dev/macro/physical_analysis)|
|------|------|


|[top :arrow_up:](https://github.com/iamaldonado/Macros_ANA) |[next :arrow_right:](simpleRead/mpddst/README.md)|


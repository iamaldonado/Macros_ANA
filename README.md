
<img src="mpd-logo_v2_small.png">

# Welcome to the Analysis Tutorial

In this repository you will find some macros to perform analysis within [mpdroot](http://mpdroot.jinr.ru) framework for the MPD (Multi-Purpose Detector) experiment at the NICA (Nuclotron-based Ion Collider fAcility) project. 

## Introduction

After run macros runMC.C and runReco.C from [mpdroot](https://git.jinr.ru/nica/mpdroot/-/tree/dev/macros/common) framework we can get two types of files: mpddst.root and mpddst.MiniDst.root which contains the required information of reconstructed particles to do analysis. In the following sections we will describe the basics of this, the macros available and explanations of how to use them.

### Structure of mpddst files

The mpdsim Tree contains the different branches: EventHeader, TpcKalmanTrack, Vertex, FfdHit, TOFHit, TOFMatching, ZdcDigi, MCEventHeader, MCTrack, MPDEvent.


### Structure of minidst files 

The MiniDst Tree contains the different branches: Event, Track, BTofHit, BTofPidTraits, BECalCluster, TrackCovMatrix, FHCalHit, McEvent, McTrack. 


### Create a simple Task

 * [For mpddst files](https://github.com/iamaldonado/Macros_ANA/tree/main/mpddstm)
 * [For minidst files](https://github.com/iamaldonado/Macros_ANA/tree/main/minidstm)


## Available Analysis Macros
|Macro|Repository|
|------|------|
|The Principal page of software|[mpdroot](http://mpdroot.jinr.ru/)

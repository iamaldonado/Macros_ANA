# Simple Macro ReadDST.C

There are several macros in mpdroot to read this kind of files. The most basic macro is [readDST.C](https://git.jinr.ru/nica/mpdroot/-/blob/dev/macros/common/readDST.C) which reads the number of events in DST file and the reconstructed tracks in each event.

Because the function is defined to read a string:

> void readDST(TString in = "") {

It is possible to run it in different ways:

1. In the same command line:
```
root readDST.C'("mpddst.root")'
```
2. or from the command line interface:
```
root -l
root [0] .L readDST.C
root [1] readDST("mpddst.root")
```

## Add pt histogram

Define the histogram after timer initialization with the following line:
```
TH1F *h1 = new TH1F("h1","p_{T} distribition;p_{T}(GeV/c);Entries",100,0,10);
```
Get the *p_{T}* in the loop over tracks looking for the proper method in [MpdTrack.h](https://git.jinr.ru/nica/mpdroot/-/blob/dev/core/mpdBase/MpdTrack.h)
```
h1->Fill(track->GetPt());
```
To draw the histogram add the following line after loop over tracks, before to print the time
```
h1->Draw();
```

## Save the histogram in a file

Before the definition of the histogram, you can add the following line 

```
TFile out("salida.root","recreate");
```
and at the end of the function *readDST* write the file and close it
```
out.Write();
out.Close();
```

| [:arrow_left: previous](../../README.md)| [main:arrow_up:](../../README.md) | [next :arrow_right:](../minidst/README.md) |




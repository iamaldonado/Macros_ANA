# Simple Macro ReadDST.C

There are several macros in mpdroot to read this kind of files. The most basic macro is [readDST.C](https://git.jinr.ru/nica/mpdroot/-/blob/dev/macros/common/readDST.C) which reads the number of events in DST file and the reconstructed tracks in each event.

Because the function is defined to read a string:

> void readDST(TString in = "") {

It is possible to run it in different ways:

1. In the same command line:
```
root readDST.C'("mpddst.root")'
```
2. or:
```
root -l
root [0] .L readDST.C
root [1] readDST("mpddst.root")
```

## Add pt histogram


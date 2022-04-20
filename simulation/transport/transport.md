### Macro for transport

To start the simulation process we require the macros **runMC.C**, **commonFunctions.C** and **geometry_stage1.C** located in the folder [macros/common](https://git.jinr.ru/nica/mpdroot/-/blob/dev/macros/common/). If they are in the same folder we just need to run it writing in the terminal:

> root -b -q runMC.C

This is going to get us the file **evetest.root**, with 2 events generated with BOX and transported with Geant3. To modify this default parameters, we need to know the structure of this macro and modify where is required.

 * 1. Options in the macro runMC.C: In the definition of the function,

```ruby
void runMC(EGenerators generator = EGenerators::BOX, EVMCType vmc = EVMCType::GEANT3, Int_t nStartSeed = 0,
           TString inFile = "auau.04gev.0_3fm.10k.f14.gz", TString outFile = "evetest.root", Int_t nStartEvent = 0,
           Int_t nEvents = 2, Bool_t flag_store_FairRadLenPoint = kFALSE, Int_t FieldSwitcher = 0)
```
you can change the options
 - the generator to be used replacing **BOX** for any of the availables
```ruby
enum EGenerators
{
   BOX = 1,
   FLUID,
   HSD,
   ION,
   LAQGSM,
   MCDST,
   PART,
   SMASH,
   UNIGEN,
   URQMD,
   VHLLE
};
```
 - The transport package Geant3 or Geant 4
 - The input File **inFile** according with your generated data, for default appears a file from UrQMD generator **auau.04gev.0_3fm.10k.f14.gz**, even is not used for BOX generator.
 - The output file **outFile** with MC data, by default: evetest.root 
 - **nStartEvent**, first event in the file to be analyzed
 - **nEvents**, the number of events to be transported, for example the number of events in inFile
 - **flag_store_FairRadLenPoint** to  enables radiation length manager to estimate radiation length data by default: kFALSE;
 - **FieldSwitcher** To choose the magnetic Field, default option is 0 that corresponds to Constant field (0, 0, 5) kG; option 1, corresponds to the FieldMap stored in a file

| [:arrow_left: previous](../generation.md)| [main:arrow_up:](../../README.md) | [next :arrow_right:](../reconstruction.md) |

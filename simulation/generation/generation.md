### Generation of particles

The first step is to generate high-energy particle physics events, with some Monte Carlo event generator, which are used to compare experimental results with theoretical predictions. The MpdRoot framework works with several event generators like:

 * BOX: which is used by default by mpdroot
 * UrQMD - Ultrarelativistic Quantum Molecular Dynamics (UrQMD)
 * 3FD - 3 Fluid Dynamics
 * PHSD - Parton Hadron String Dynamics
 * LAQGSM - Los Alamos Quark Gluon String Model
 * SMASH - Simulating Many Accelerated Strongly-interacting Hadrons

The classes associated to the supported generators and the skeletons to add a new one are in the folder [simulation/generators](https://git.jinr.ru/nica/mpdroot/-/tree/dev/simulation/generators/mpdGen)


| [:arrow_left: previous](../../README.md)| [main:arrow_up:](../../README.md) | [next :arrow_right:](../transport/transport.md) |
 

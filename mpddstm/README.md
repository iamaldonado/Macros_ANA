# Analysis Task for mpddst files

The code used in mpdroot is written in form of C++ *classes*. Each class is stored in its own header (*.h*) and implementation file (*.cxx*). To read mpddst files we can write our own class which is derived from **FairTask**.

The example class **MpdPtTask** shown here, read mpddst.root files and gives the transverse momemtum distribution of reconstructed tracks and generated tracks. Because is derived from FairTask, it shares the common base methods

- **Constructors and Destructors**: Are  standard C++ features, called each time an Instance of the class is created or deleted.

```
MpdPtTask::MpdPtTask() // default constructor
MpdPtTask::MpdPtTask(const char *name, const char *title) // constructor with names
MpdPtTask::∼MpdPtTask() // destructor
```
- **Initialization of objects**: In this function we can define the output objects of the analysis, like histograms and trees. In this case the histograms of transverse momentum distribution.

```
InitStatus MpdPtTask::Init() // objects to fill (trees, histograms, profiles, etc.)
```
- **Execution and process of analysis**: This function is called for each event. This function is the event loop. 

```
void MpdPtTask::Exec(Option_t *option) // event loop function
```
- **Finish()**: Called at the end of analysis. In this example to store the histograms

```
void MpdPtTask::Finish(); // To store the files
```


| [:arrow_left: previous](../simpleRead/minidst/README.md)| [main:arrow_up:](../README.md) | [next :arrow_right:](../minidstm/README.md) |


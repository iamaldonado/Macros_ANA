# Compile mpdroot with your class

You have to create a folder in mpdroot, for example in *mpdroot/physics*, and add it to the CMakeList.txt file in physics folder.

In this example we create the folder anaclass, that folder should contain the files to tell which classes should be added to the dictionary and your class's files:

- CMakeList.txt
- AnaClassLinkDef.h
- MpdPtTask.h
- MpdPtTask.cxx
 
## CMakeList.txt

The [CMakeList.txt](CMakeList.txt) file should include all the folders that contain the inherited classes and methods for your class.


For example: In our class we call the MpdTrack class that is defined in *mpdbase* folder, that's the reason appears in the third line

```ruby
set(INCLUDE_DIRECTORIES
 ${BASE_INCLUDE_DIRECTORIES}
 ${CMAKE_SOURCE_DIR}/mpdbase
 ${CMAKE_SOURCE_DIR}/kalman
 ${CMAKE_SOURCE_DIR}/generators
 ${CMAKE_SOURCE_DIR}/mcstack
 ${CMAKE_SOURCE_DIR}/mpddst
 ${CMAKE_SOURCE_DIR}/zdc
 ${CMAKE_SOURCE_DIR}/mpddst/MpdMiniEvent
 ${CMAKE_SOURCE_DIR}/physics
 ${CMAKE_SOURCE_DIR}/physics/anaclass
)

Set(SYSTEM_INCLUDE_DIRECTORIES
 ${ROOT_INCLUDE_DIR}
)

include_directories(${INCLUDE_DIRECTORIES})
Include_Directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
 ${ROOT_LIBRARY_DIR}
 ${FAIRROOT_LIBRARY_DIR}
)

link_directories(${LINK_DIRECTORIES})
```

In the next part you have to add the name of your implementation class or classes

```ruby
set(SRCS
  MpdPtTask.cxx
)
```

And finally write the name of your *LinkDef.h* file and the name of your library

```ruby
Set(HEADERS)
Set(LINKDEF AnaClassLinkDef.h)
Set(LIBRARY_NAME MpdAnaClass)
Set(DEPENDENCIES)

GENERATE_LIBRARY()
```

:red_circle: :warning: :red_circle: **NOTE**: mpdroot is a work in progress, the location of some classes are changing from one version to another, for example *mpdbase* was moved to *core/mpdbase*. Check it in your own version.



## LinkDef.h 

This file tells which classes should be added to the dictionary

```ruby
#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class MpdPtTask+;

#endif
```

| [:arrow_left: previous](../minidstm/README.md)| [main:arrow_up:](../README.md) | [next :arrow_right:](runmacro.md) |


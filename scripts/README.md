## Getting Started

Installation scripts for both Linux and Windows are available to configure the whole project.

### Prerequisites

- Git v2.x
- Windows or Linux (Ubuntu, Debian/Kali, Mageia or CentOS), x64 is preferable
- Visual Studio 2017 or newer with C++ Dev Tools (Windows Only)
- The program will open OpenCV Windows so a Graphical Interface support is needed

### Installing

#### Linux :

```
OpenFaceTracker/scripts/$ chmod u+x configure.sh install.sh
OpenFaceTracker/scripts/$ ./configure.sh
OpenFaceTracker/scripts/$ ./install.sh
```
These scripts will install the necessary packages using the default package manager.


#### Windows :

Launch Powershell with admin privileges.

The default path for downloading and installating the packages is "C:\dev\", you can change the path at line 130.

```
PS C:\OpenFaceTracker\scripts> ./installation.ps1
```

This Powershell script will install [vcpkg](https://github.com/microsoft/vcpkg) if not already and will use it to install and build dependencies.

### Build

Building OpenFaceTracker is done using CMake, installed by the scripts. For both Linux and Windows targets, CMake will produce a Makefile. This generator can be changed in `./PreLoad.cmake`.

#### Linux :

```
OpenFaceTracker/$ mkdir build
OpenFaceTracker/$ cb build
OpenFaceTracker/build/$ cmake ..
OpenFaceTracker/build/$ make
```

#### Windows :

In order for the Makefile to build with Visual Studio C++ Dev Tools, you need to build using `x64 Native Tools Command Prompt for VS 2019` command prompt. Refer to the [microsoft documentation](https://docs.microsoft.com/en-gb/cpp/build/how-to-enable-a-64-bit-visual-cpp-toolset-on-the-command-line?view=vs-2019) if needed.

```
**********************************************************************
** Visual Studio 2019 Developer Command Prompt v16.7.0
** Copyright (c) 2020 Microsoft Corporation
**********************************************************************
[vcvarsall.bat] Environment initialized for: 'x64'

C:\OpenFaceTracker\>mkdir build
C:\OpenFaceTracker\>cd build
C:\OpenFaceTracker\build>cmake ..
C:\OpenFaceTracker\build>nmake
```

# OpenFaceTracker

OpenFaceTracker (OFT) is an OpenSource C++ library for facial detection and recognition. This project can be used as a C++ library or as a command-line based program.

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
_______________________________________________________________________________

Once built, OpenFaceTracker library binaries will be in `./lib` and the OpenFaceTracker Application will be ready to use in `./bin`. A Doxygen documentation for the library is also generated in `./doc`.

We will discuss the application usage now. To use the library, please refer to the generated documentation.

### Usage

There is no difference in usage between Linux or Windows.

A configuration file for oftapp is located in `./data/config.json`. It defines path to data files relative to working directory being `./bin` (home of `oftapp`).

#### Options :

>Displays help
```
	/OpenFaceTracker/bin>oftapp --help
```

>Displays version
```
	/OpenFaceTracker/bin>oftapp --help
```

>Opens the first connected webcam and do facial analysis in real time
```
	/OpenFaceTracker/bin>oftapp -d CAM0
```

>Reads a local image file and do facial analysis
```
	/OpenFaceTracker/bin>oftapp -i "path/to/image.png"
```

>Reads a local video file and do facial analysis
```
	/OpenFaceTracker/bin>oftapp -p "path/to/video.mp4"
```

>Downloads the youtube video in './tmp' and do facial analysis on cached file
```
	/OpenFaceTracker/bin>oftapp -p https://www.youtube.com/watch?v=dQw4w9WgXcQ
```

>Downloads a remote file in './tmp' and do facial analysis
```
	/OpenFaceTracker/bin>oftapp -u https://url.to/a/remote/file.jpg
```

>Opens the webcam and only detect faces. A sample is taken each frame the user left clicks. While exiting, "John" will be inserted in database with its associated data.
```
	/OpenFaceTracker/bin>oftapp -d CAM0 -a John
```

>The same as above but each detected face at every frame is taken as sample for inserting or updating "John". Use with caution!
```
	/OpenFaceTracker/bin>oftapp -d CAM0 -a John -y
```

>Works with every source given
```
	/OpenFaceTracker/bin>oftapp -i "../path/to/source.jpeg" -a Smith -y
```

## Explications

In this section will be discussed the technologies and algorithms currently used for each modules. Please note the project is still in developpement and these algorithms will be improved in the future, their usage and operation are subject to changes.

### Detection

To detect faces in a frame, we use a [Haar Cascade Classifier](https://fr.wikipedia.org/wiki/M%C3%A9thode_de_Viola_et_Jones). This algorithm, proposed by [Paul Viola and Michael Jones in 2001](https://www.cs.cmu.edu/~efros/courses/LBMV07/Papers/viola-cvpr-01.pdf), is still widely used due to its easy implementation, low computational costs and performance. OpenCV proposes an implementation of this facial detection algorithm.

However, this method is not reliable. Even with different trained cascades, faces with glasses are not detected well, as well as inclined faces or in non-optimal conditions.

Despite all these disavantages, we still use this method over [newer methods](https://www.learnopencv.com/face-detection-opencv-dlib-and-deep-learning-c-python/) because of its simplicity and also because we need well centered and alligned faces for our facial recognition algorithm.


### Recognition

The recognition module is the heart of this project. The general idea of recognition is to represent face images (which are high-dimensional vectors) in a lower-dimension space that can be seen as a universe in which exists only the known faces ; where they are represented as a point. When many faces populates a vector space accurately, their distances between each other tend to act as a "similarity score". The closest two faces are represented, the more similar they are.

>#### Eigenface

The first idea is to use the [Eigenface](https://en.wikipedia.org/wiki/Eigenface) algorithm. This method consists in computing a [Principal Component Analysis](https://en.wikipedia.org/wiki/Principal_component_analysis) (or PCA) using the faces of all the subjects we know the identity. The PCA generates a n-dimensions vector space. Then, when we want to identify an unknown face, we project the image (a high-dimensional vector) onto the PCA space (a low-dimensional space), we can compute the distance with each known face. The nearest face is considered the most similar.

This method is popular, due to an easy implementation thanks to OpenCV, and to its low computational costs. However, this performs better when the PCA is computed with many faces, from different persons and in different variations (lightning, face alignement...). OpenFaceTracker's goal is to be used with a small number of samples if wanted. If we compute Eigenface using three faces of three different people, the vector space will not have enough dimensions to accurately classify a face.

>#### Generic Eigenface

Eigenface in itself, and in its OpenCV implementation, is not suitable for OpenFaceTracker. But if we populate the vector space with thousands of realistic faces, with variations (lightning, head inclinaison...), the PCA will accurately found the best componants to separate all these faces, and there will be enough faces to represent what a human face looks like generally.

To get such a dataset of realistic faces with variations, we parsed the website [thispersondoesnotexist.com](https://thispersondoesnotexist.com/), a [StyleGAN2](https://arxiv.org/abs/1912.04958) that generates a high quality image of a face that does not exist. The PCA of OpenFaceTracker is based of 50,000 faces from this website. This PCA has been computed once and is reused indefinetly. 

Once the vector space defined, we only have to project our faces there and compute distances. But a face is changing and if we project several faces of one subject, they will represent a point cloud. This is why we average all the samples to approximate the center of the cloud. This very point is then saved as a blob in the database, with the total number of samples that we keep track of. And thanks to incremental averageing, this whole calculation is optimized and allows a subject's data to be updated.

Another advantage of using these faces is that they are always centered and the eyes are always on the same position. This is important since, even when projected to a vector space, the comparison between two faces is near-pixel perfect. Using OpenCV's facial landmarks detector, we transform the image to match the eyes position.

## TODO

- [ ] Add configuration file linkage via oftapp option
- [ ] Build Doxygen documentation and publish in Github Pages
- [ ] Test RTSP Stream Support
- [ ] Improve face alignement (Delaunay triangulation and warp)
- [ ] Improve data averageing and check variance
- [ ] Implement full cmd line option for app

## Acknowledgments

- [OpenCV](https://opencv.org/)
- [Learn OpenCV](https://www.learnopencv.com/)
- [youtube-dl](https://youtube-dl.org/)
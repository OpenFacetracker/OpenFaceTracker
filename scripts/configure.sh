#!/bin/bash

#   This script is part of OpenFaceTracker project
#   
#   Software Engineer :     Hethsron Jedaël BOUEYA
#   Project Manager :       Richard REY
#   Date :                  3rd June 2019
#   Version :               6.0.0
#   Copyright (C) :         Laboratoire CNS/(C+V)°
#                           ESIEA - Laval 2020
#
#   This text plain is developed in the hope that it will be useful
#   but WITHOUT ANY WARRANTY ; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#

#   Default flags
ERROR="[\033[31m!\033[0m]"
DEBUG="[\033[33m#\033[0m]"
OK="[\033[32mo\033[0m]"

#   By default PREROGATIVE is set to sudo for normal users
if [[ $USER = root ]]; then
    export PREROGATIVE=
else
    export PREROGATIVE=sudo
fi

#   Default commands
ECHO="echo -e"

#   Check GNU/Linux distribtion function
function checkDistrib() {
    DISTRIB=$(cat /etc/os-release | grep "NAME" | head -n 1 | cut -d'"' -f2 | cut -d' ' -f1)

    if [[ "$DISTRIB" = "CentOS" ]]; then
        # Define appropriate download manager for CentOS Distribution
        DOWN_MANAG="yum"
        PKG_MANAG="rpm"
    elif [[ "$DISTRIB" = "Debian" ]] || [[ "$DISTRIB" = "Kali" ]]; then
        # Define appropriate download manager for Debian Like Distribution
        DOWN_MANAG="apt-get"
        PKG_MANAG="dpkg-query"
    elif [[ "$DISTRIB" = "Mageia" ]]; then
        # Define appropriate download manager for Mageia Distribution
        DOWN_MANAG="urpmi"
        PKG_MANAG="rpm"
    else
        return 1
    fi
}

#   Install missing package functions
function installMissingPKG() {
    if [ -z "$1" ]; then
        ${ECHO} "${ERROR} \$PKG is empty"
    else
        COMMAND=$(${PKG_MANAG} -W -f='${Status}\n' $1 | cut -d' ' -f1)
        if [[ "$COMMAND" = "install" ]]; then
            ${ECHO} "${OK} $1 is installed"
            sleep 1
        else
            ${ECHO} "${ERROR} $1 is not installed"
            sleep 2
            ${ECHO} "${DEBUG} Installation of $1 ..."
            ${PREROGATIVE} ${DOWN_MANAG} install -y $1 > /dev/null
            sleep 2
            ${ECHO} "${OK} $1 has been installed"
        fi
    fi
}

function installMissingRPM() {
    if [ -z "$1" ]; then
        echo "\$PKG is empty"
    else
        export NUX=nux-dextop-release
        FIREWALL=$(${PKG_MANAG} -qa ${NUX})

        if [ -z "$FIREWALL" ]; then
            ${ECHO} "${ERROR} ${NUX} is not installed"
            sleep 2
            ${ECHO} "${DEBUG} Installation of ${NUX} ..."

            #   Load missing repositories
            ${PREROGATIVE} ${PKG_MANAG} --import http://li.nux.ro/download/nux/RPM-GPG-KEY-nux.ro
            ${PREROGATIVE} ${PKG_MANAG} -Uvh http://li.nux.ro/download/nux/dextop/el7/x86_64/nux-dextop-release-0-1.el7.nux.noarch.rpm > /dev/null

            #   Uploading repositories
            ${PREROGATIVE} ${DOWN_MANAG} update -y > /dev/null
        fi

        COMMAND=$(${PKG_MANAG} -qa $1)
        if [ -z "$COMMAND" ]; then
            ${ECHO} "${ERROR} $1 is not installed"
            sleep 2
            ${ECHO} "${DEBUG} Installation of $1 ..."
            ${PREROGATIVE} ${DOWN_MANAG} install -y $1 > /dev/null
            sleep 2
            ${ECHO} "${OK} $1 has been installed"
        else
            ${ECHO} "${OK} $1 is installed"
            sleep 1
        fi
    fi
}

#   String arrays of packages
declare -a PKGS_CENTOS=(
                "ant"
                "apiviz"
                "boost-devel"
                "bzip2-devel"
                "ceres-solver"
                "ceres-solver-devel"
                "cmake3"
                "Coin2-devel"
                "doxygen"
                "eigen3-devel"
                "ffmpeg"
                "ffmpeg-devel"
                "gcc"
                "gcc-c++"
                "gdal-devel"
                "genders-java-devel"
                "gflags"
                "gflags-devel"
                "ghc-OpenGL-devel"
                "glog"
                "glog-devel"
                "gstreamer-plugins-base-devel"
                "git"
                "gtkglext-devel"
                "gtk+"
                "gtk+-devel"
                "gtk2-devel"
                "gtk3-devel"
                "gsl-devel"
                "hdf"
                "hdf5"
                "hdf-devel"
                "hdf5-devel"
                "jasper"
                "json-c"
                "json-c12"
                "json-c-devel"
                "json-c12-devel"
                "kernel-devel"
                "lapack"
                "lapack64"
                "lapack-devel"
                "lapack64-devel"
                "leptonica"
                "leptonica-devel"
                "libavc1394-devel"
                "libcurl"
                "libcurl-devel"
                "libdb-java-devel"
                "libdc1394-devel"
                "libgcrypt-devel"
                "libgomp"
                "libgphoto2"
                "libgphoto2-devel"
                "libicu-devel"
                "libjasper-devel"
                "libjpeg-devel"
                "libmcrypt-devel"
                "libpng-devel"
                "libtiff-devel"
                "libtheora-devel"
                "libunicap-devel"
                "libunicapgtk-devel"
                "libvorbis-devel"
                "libv4l-devel"
                "libwebp-devel"
                "libXinerama-devel"
                "libXinerama"
                "openexr-devel"
                "openni"
                "openni-devel"
                "openni-java"
                "openssl"
                "mcrypt"
                "mesa-libGL"
                "mesa-libGL-devel"
                "pkgconfig"
                "nv-codec-headers"
                "pcre"
                "pcre-devel"
                "python34"
                "python34-devel"
                "python34-numpy"
                "python34-pip"
                "python34-sphinx"
                "tbb"
                "tbb-devel"
                "tesseract"
                "tesseract-devel"
                "tesseract-langpack-fra"
                "vtk"
                "vtk-devel"
                "v4l-utils"
                "v4l-utils-devel-tools"
                "yasm"
				"youtube-dl"
)

declare -a PKGS_DEBIAN=(
                "autotools-dev"
                "build-essential"
                "cmake"
                "doxygen"
                "ffmpeg"
                "gcc"
                "g++"
                "gnome-themes-standard"
                "gphoto2"
                "libatlas-base-dev"
                "libavc1394-dev"
                "libavfilter-dev"
                "libavresample-dev"
                "libboost-all-dev"
                "libboost-dev"
                "libbz2-dev"
                "libceres-dev"
                "libcppdb-dev"
                "libcrypto++-dev"
                "libcurl4-gnutls-dev"
                "libdc1394-22-dev"
                "libeigen3-dev"
                "libgegl-dev"
                "libglew-dev"
                "libgoogle-glog-dev"
                "libgphoto2-dev"
                "libgstreamer1.0-dev"
                "libgstreamer-plugins-base1.0-dev"
                "libgtk2.0-dev"
                "libhdf5-dev"
                "libicu-dev"
                "libjpeg-dev"
                "libjson-c-dev"
                "libkf5coreaddons5"
                "liblapack-dev"
                "liblapacke-dev"
                "libleptonica-dev"
                "libmcrypt-dev"
                "libmp3lame-dev"
                "libomp-dev"
                "libopenblas-dev"
                "libopencore-amrnb-dev"
                "libopencore-amrwb-dev"
                "libpcre3-dev"
                "libprotobuf-dev"
                "libprotobuf-c-dev"
                "libprotoc-dev"
                "libpng-dev"
                "libtesseract-dev"
                "libtheora-dev"
                "libtbb2"
                "libtbb-dev"
                "libtiff5-dev"
                "libv4l-dev"
                "libvorbis-dev"
                "libx264-dev"
                "libxine2-dev"
                "libxvidcore-dev"
                "mcrypt"
                "mesa-utils"
                "openssl"
                "pkg-config"
                "python3-dev"
                "python3-pip"
                "uvcdynctrl"
                "v4l-utils"
                "x264"
                "yasm"
				"youtube-dl"
                "zlib1g-dev"
)

declare -a PKGS_KALI=(
                "autotools-dev"
                "build-essential"
                "cmake"
                "doxygen"
                "ffmpeg"
                "gcc"
                "g++"
                "gphoto2"
                "libatlas-base-dev"
                "libavc1394-dev"
                "libavfilter-dev"
                "libavresample-dev"
                "libboost-all-dev"
                "libboost-dev"
                "libbz2-dev"
                "libceres-dev"
                "libcppdb-dev"
                "libcrypto++-dev"
                "libcurl4-gnutls-dev"
                "libdc1394-22-dev"
                "libeigen3-dev"
                "libfaac-dev"
                "libgegl-dev"
                "libglew-dev"
                "libgoogle-glog-dev"
                "libgphoto2-dev"
                "libgstreamer1.0-dev"
                "libgstreamer-plugins-base1.0-dev"
                "libgtk2.0-dev"
                "libhdf5-dev"
                "libicu-dev"
                "libjpeg-dev"
                "libjson-c-dev"
                "libkf5coreaddons5"
                "liblapack-dev"
                "liblapacke-dev"
                "libleptonica-dev"
                "libmcrypt-dev"
                "libmp3lame-dev"
                "libomp-dev"
                "libopenblas-dev"
                "libopencore-amrnb-dev"
                "libopencore-amrwb-dev"
                "libpcre3-dev"
                "libprotobuf-dev"
                "libprotobuf-c-dev"
                "libprotoc-dev"
                "libpng-dev"
                "libtesseract-dev"
                "libtheora-dev"
                "libtbb2"
                "libtbb-dev"
                "libtiff5-dev"
                "libv4l-dev"
                "libvorbis-dev"
                "libx264-dev"
                "libxine2-dev"
                "libxvidcore-dev"
                "mcrypt"
                "mesa-utils"
                "openssl"
                "pkg-config"
                "python3-dev"
                "python3-pip"
                "uvcdynctrl"
                "v4l-utils"
                "x264"
                "yasm"
				"youtube-dl"
                "zlib1g-dev"
)

declare -a PKGS_MAGEIA=(
                ""
)

#   Display Welcome message
${ECHO} "OpenFaceTracker For Developers"
${ECHO} "GNU GPL Version 6.0.0"
${ECHO} "© Copyright - ESIEA Campus Laval 2020"
${ECHO} "CNS (Confiance Numérique et Sécurité)\n"
${ECHO} "Starting the configuration of your GNU/Linux Operating System"
${ECHO} ""

#   Execute Check GNU/Linux distribtion function
checkDistrib

if [[ "$DISTRIB" = "CentOS" ]]; then
    #   Loop list of packages
    for PKG in "${PKGS_CENTOS[@]}"; do
        # Execute Install missing package function
        installMissingRPM ${PKG}
    done
elif [[ "$DISTRIB" = "Debian" ]]; then
    #   Loop list of pakages
    for PKG in "${PKGS_DEBIAN[@]}"; do
        #   Execute Install missing package function
        installMissingPKG ${PKG}
    done
elif [[ "$DISTRIB" = "Kali" ]]; then
    #   Loop list of pakages
    for PKG in "${PKGS_KALI[@]}"; do
        #   Execute Install missing package function
        installMissingPKG ${PKG}
    done
fi

${ECHO} ""
${ECHO} "Configuration done"
#!/bin/bash

#   This script is part of OpenFaceTracker project
#   
#   Software Engineer :     Hethsron Jedaël BOUEYA
#   Project Manager :       Richard REY
#   Date :                  27th August 2020
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
CD="cd"
ECHO="echo -e"
EXEC="exec bash"
EXPORT="export"
LDCONFIG="ldconfig"
MAKE="make"
MKDIR="mkdir"
MV="mv"
PKGCONFIG="pkg-config"
RM="rm -rf"
SH="sh -c"
SOURCE="source"
TEE="tee -a"
UNZIP="unzip"
WGET="wget -nv"

#   Check GNU/Linux distribtion function
function checkDistrib() {
    DISTRIB=$(cat /etc/os-release | grep "NAME" | head -n 1 | cut -d'"' -f2 | cut -d' ' -f1)

    if [[ "$DISTRIB" = "CentOS" ]]; then
        # Define appropriate download manager for CentOS Distribution
        DOWN_MANAG="yum"
        PKG_MANAG="rpm"
        CMAKE="cmake3"
    elif [[ "$DISTRIB" = "Debian" ]] || [[ "$DISTRIB" = "Kali" ]]; then
        # Define appropriate download manager for Debian Like Distribution
        DOWN_MANAG="apt-get"
        PKG_MANAG="dpkg-query"
        CMAKE="cmake"
    elif [[ "$DISTRIB" = "Mageia" ]]; then
        # Define appropriate download manager for Mageia Distribution
        DOWN_MANAG="urpmi"
        PKG_MANAG="rpm"
        CMAKE="cmake"
    else
        return 1
    fi
}

#   Building OpenCV function
function buildingOpenCV() {
    CORE=$(cat /proc/cpuinfo | grep "cpu cores" | head -n 1 | cut -d':' -f2)
    ${CMAKE} -D CMAKE_BUILD_TYPE=RELEASE \
                -D CMAKE_INSTALL_PREFIX=/usr/local \
                -D INSTALL_C_EXAMPLES=ON \
                -D INSTALL_PYTHON_EXAMPLES=ON \
                -D OPENCV_GENERATE_PKGCONFIG=ON \
                -D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules \
                -D BUILD_EXAMPLES=ON ..
    
    ${MAKE} -j${CORE}

    ${PREROGATIVE} ${MAKE} install > /dev/null
    ${PREROGATIVE} ${LDCONFIG}
    ${PREROGATIVE} ${SH} 'echo "/usr/local/lib" >> /etc/ld.so.conf.d/opencv.conf'
}

#   Install missing package functions
function installMissingPKG() {
    if [[ "$DISTRIB" = "CentOS" ]]; then
        #   Check if PKG-CONFIG is already installed
        FIREWALL=$(${PKG_MANAG} -qa pkgconfig)
        if [ -z "$FIREWALL" ]; then
            ${ECHO} "${ERROR} pkgconfig is not installed"
            sleep 2

            ${ECHO} "${DEBUG} Installation of pkgconfig ..."
            sleep 2

            ${PREROGATIVE} ${DOWN_MANAG} install -y pkgconfig > /dev/null

            ${ECHO} "${OK} pkgconfig has been installed"
        fi

        #   Check if OpenCV 3.4.2 is already installed
        COMMAND=$(${PKGCONFIG} --modversion opencv)
        if [[ "$COMMAND" = "3.4.2" ]]; then
            ${ECHO} "${OK} OpenCV 3.4.2 is installed"
            sleep 1
        else
            ${ECHO} "${ERROR} OpenCV 3.4.2 is not installed"
            sleep 2

            #   Installing OpenCV 3.4.2
            ${ECHO} "${DEBUG} Installing OpenCV 3.4.2 ..."

            #   Getting OpenCV 3.4.2 Sources
            sleep 2
            ${ECHO} "${DEBUG} Getting OpenCV 3.4.2 sources ..."
            ${WGET} -O opencv.zip https://github.com/opencv/opencv/archive/3.4.2.zip
            ${UNZIP} opencv.zip > /dev/null
            ${MV} opencv-3.4.2 opencv
            ${RM} opencv.zip
            
            #   Getting OpenCV 3.4.2 Contributions
            sleep 2
            ${ECHO} "${DEBUG} Getting OpenCV 3.4.2 contributions ..."
            ${WGET} -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/3.4.2.zip
            ${UNZIP} opencv_contrib.zip > /dev/null
            ${MV} opencv_contrib-3.4.2 opencv_contrib
            ${RM} opencv_contrib.zip

            #   Check if CMAKE is already installed
            FIREWALL2=$(${PKG_MANAG} -qa ${CMAKE})
            if [ -z "$FIREWALL2" ];  then
                ${ECHO} "${ERROR} ${CMAKE} is not installed"
                sleep 2

                ${ECHO} "${DEBUG} Installation of ${CMAKE} ..."
                sleep 2

                ${PREROGATIVE} ${DOWN_MANAG} install -y ${CMAKE} > /dev/null

                ${ECHO} "${OK} ${CMAKE} has been installed"
            fi

            #   Building OpenCV 3.4.2
            sleep 2
            ${ECHO} "${DEBUG} Building OpenCV 3.4.2 ..."
            ${CD} opencv
            ${MKDIR} build
            ${CD} build

            #   Execute building OpenCV function
            buildingOpenCV

            ${CD} ../../
            ${RM} opencv opencv_contrib

            sleep 2
            ${ECHO} "${OK} OpenCV 3.4.2 has been installed"
        fi
    elif [[ "$DISTRIB" = "Debian" ]] || [[ "$DISTRIB" = "Kali" ]]; then
        #   Check if PKG-CONFIG is already installed
        FIREWALL=$(${PKG_MANAG} -W -f='${Status}\n' pkg-config | cut -d' ' -f1)
        if [[ "$FIREWALL" = "install" ]]; then
            sleep 1
        else
            ${ECHO} "${ERROR} pkg-config is not installed"
            sleep 2

            #   Installing pkg-config
            ${ECHO} "${DEBUG} Installation of pkg-config ..."
            sleep 2

            ${PREROGATIVE} ${DOWN_MANAG} install -y pkg-config > /dev/null

            sleep 2
            ${ECHO} "${OK} pkg-config has been installed"
        fi

         #   Check if OpenCV 3.4.2 is already installed
        COMMAND=$(${PKGCONFIG} --modversion opencv)
        if [[ "$COMMAND" = "3.4.2" ]]; then
            ${ECHO} "${OK} OpenCV 3.4.2 is installed"
            sleep 1
        else
            ${ECHO} "${ERROR} OpenCV 3.4.2 is not installed"
            sleep 2

            #   Installing OpenCV 3.4.2
            ${ECHO} "${DEBUG} Installing OpenCV 3.4.2 ..."

            #   Getting OpenCV 3.4.2 Sources
            sleep 2
            ${ECHO} "${DEBUG} Getting OpenCV 3.4.2 sources ..."
            ${WGET} -O opencv.zip https://github.com/opencv/opencv/archive/3.4.2.zip
            ${UNZIP} opencv.zip > /dev/null
            ${MV} opencv-3.4.2 opencv
            ${RM} opencv.zip
            
            #   Getting OpenCV 3.4.2 Contributions
            sleep 2
            ${ECHO} "${DEBUG} Getting OpenCV 3.4.2 contributions ..."
            ${WGET} -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/3.4.2.zip
            ${UNZIP} opencv_contrib.zip > /dev/null
            ${MV} opencv_contrib-3.4.2 opencv_contrib
            ${RM} opencv_contrib.zip

            #   Check if CMAKE is already installed
            FIREWALL2=$(${PKG_MANAG} -W -f='${Status}\n' ${CMAKE} | cut -d' ' -f1)
            if [[ "$FIREWALL2" = "install" ]]; then
                sleep 1
            else
                ${ECHO} "${ERROR} ${CMAKE} is not installed"
                sleep 2

                ${ECHO} "${DEBUG} Installation of ${CMAKE} ..."
                sleep 2

                ${PREROGATIVE} ${DOWN_MANAG} install -y ${CMAKE} > /dev/null

                ${ECHO} "${OK} ${CMAKE} has been installed"
            fi

            #   Building OpenCV 3.4.2
            sleep 2
            ${ECHO} "${DEBUG} Building OpenCV 3.4.2 ..."
            ${CD} opencv
            ${MKDIR} build
            ${CD} build

            #   Execute building OpenCV function
            buildingOpenCV

            ${CD} ../../
            ${RM} opencv opencv_contrib

            sleep 2
            ${ECHO} "${OK} OpenCV 3.4.2 has been installed"
        fi
    fi
}

#   Display Welcome message
${ECHO} "OpenFaceTracker For Developers"
${ECHO} "GNU GPL Version 6.0.0"
${ECHO} "© Copyright - ESIEA Campus Laval 2020"
${ECHO} "CNS (Confiance Numérique et Sécurité)\n"
${ECHO} "Starting the configuration of your GNU/Linux Operating System"
${ECHO} ""

#   Execute Check GNU/Linux distribtion function
checkDistrib

#   Execute Install Missing Package function
installMissingPKG

${ECHO} ""
${ECHO} "Configuration done"

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// AUTHOR: Hethsron Jedaël BOUEYA
//
//                             LICENSE AGREEMENT
// Copyright (c) 2019, ESIEA Campus of Laval, France
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. All advertising materials mentioning features or use of this software
//    must display the following acknowledgement:
//    This product includes software developed by the ESIEA Campus of Laval (France).
// 4. Neither the name of the ESIEA Campus of Laval (France) nor the
//    names of its contributors may be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY ESIEA CAMPUS OF LAVAL (FRANCE) ''AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL ESIEA CAMPUS LAVAL OF LAVAL (FRANCE) OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _EXPLORER_HPP_
#define _EXPLORER_HPP_
/**
 *	\file			explorer.hpp
 *	\brief			Header of Explorer class
 *
 *					This header contains an useful class to manage directories and files
 *
 *  \details        System :                OpenFaceTracker
 *                  Component Name :        oft
 *                  Status :                Version 5.0.0 Release 1
 *                  Language :              C++
 * 
 *                  Platform Dependencies:  GNU/Linux, Windows
 * 
 *  \copyright      GPLv3+ : GNU GPL version 3 or later
 *                  Licencied Material - Property of CNS (Confiance Numérique et Sécurité)
 *                  © Copyright - ESIEA Campus Laval 2019
 * 
 *	\author			Hethsron Jedaël BOUEYA (boueya@et.esiea.fr)
 * 
 * 	\bug			No known bug to date
 *  \date 			3rd June 2019
 */
#ifdef __linux__
    #include <cstdio>
    #include <cstdlib>
    #include <ctime>
    #include <curl/curl.h>
    #include <dirent.h>
    #include <errno.h>
    #include <fstream>
    #include <iostream>
    #include <limits.h>
    #include <oft/directory.hpp>
    #include <oft/sha256.hpp>
    #include <random>
    #include <string.h>
    #include <sstream>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <tuple>
    #include <unistd.h>
    #include <X11/Xlib.h>
	#include <oft/defs.hpp>
    #undef Status
#elif defined _WIN32
    #include <cstdio>
    #include <cstdlib>
    #include <ctime>
    #include <curl/curl.h>
    #include <fstream>
    #include <iostream>
    #include <oft/directory.hpp>
    #include <oft/sha256.hpp>
    #include <oft/toolsbox.hpp>
    #include <random>
    #include <string.h>
    #include <sstream>
    #include <tuple>
    #include <Windows.h>
    #include <direct.h>
	#include <oft/defs.hpp>
#endif // ! __linux__ or _WIN32

namespace oft {

    /**
     *  \fn         itos
     *  \brief      Template of string conversion
     *  \tparam[in]         T       The type of data stored in the table
     *  \return             The string converted
     */
    template <typename T>
    std::string itos(T value) {
        std::ostringstream os;
        os << value;
        return os.str();
    }

    /**
     *  \class      Explorer
     *  \brief      Class of default file explorer
     */
    class Explorer
    {
    public:
        /**
         *  \fn     Explorer
         *  \brief  Class default constructor
         */
        OFT_EXPORT Explorer();

        /**
         *  \fn     checkrtsp
         *  \brief  RTSP (Real Timer Streaming Protocol) checker offers a solution to users who want to verify accessibility of a streaming server
         * 
         *  \param[in]      url     Uniform resource locator of a streaming server
         *  \return         true    If the streaming server is reachable
         *  \return         false   If the streaming server is unreachable
         */
        OFT_EXPORT bool checkrtsp(const std::string& url);

        /**
         *  \fn     delfs
         *  \brief  The delfs (delete files) tool allows to delete a specific and existing file
         *  
         *  \param[in]      obj     The specified file to be deleted
         *  \return         true    If the file has been deleted
         *  \return         false   If the file does not exist or cannot be deleted
         */
        OFT_EXPORT bool delfs(File obj);

        /**
         *  \fn     delfs
         *  \brief  The delfs (delete files) tool allows to delete all files in a specific and existing directory
         * 
         *  \param[in]      obj     The specified directory that contains files to be deleted
         *  \return         true    If the files have been deleted
         *  \return         false   If the directory does not exist or the files cannot be deleted
         */
        OFT_EXPORT bool delfs(Directory obj);

        /**
         *  \fn     empty
         *  \brief  The empty tool allows users to know if a file is empty or not
         * 
         *  \param[in]      distn   The distinguished name of the file
         *  \return         true    If the file is empty
         *  \return         false   If the file is not empty
         */
        OFT_EXPORT bool empty(const std::string& distn);

        /**
         *  \fn     exist
         *  \brief  File existence checker offers a solution to users who want to verify the existence of files or folders on their computer
         * 
         *  \param[in]      distn   The distinguished name of the file or folder to analyze
         *  \return         true    If the file or folder exists
         *  \return         false   If the or folder does not exist
         */
        OFT_EXPORT bool exist(const std::string& distn);

        /**
         *  \fn     forensic
         *  \brief  Digital image and video forensic analyzer. Use to analyze JPEG or JPG file and AVI, MPEG-4 or MATROSKA file
         * 
         *  \param[in]      distn   The distinguished name of the file to analyze
         *  \return         true    If the file is a JPEG, JPG, AVI, MPEG-4, MATROSKA file
         *  \return         false   If the file is not a JPEG, JPG, AVI, MPEG-4, MATROSKA file
         */
        OFT_EXPORT bool forensic(const std::string& distn);

        /**
         *  \fn     gwd
         *  \brief  The gwd (get working directory) tool returns the name of the present/current working directory
         * 
         *  \return                 The current working directory
         */
        OFT_EXPORT std::string gwd();

        /**
         *  \fn     makdir
         *  \brief  The makdir (make directory) tool allows to create a new directory
         * 
         *  \param[in]      obj     The specified directory to be created
         *  \return         true    If the new directory has been created
         *  \return         false   If the new directory already exists or cannot be created
         */
        OFT_EXPORT bool makdir(Directory obj);

        /**
         *  \fn     remdir
         *  \brief  The remdir (remove directory) tool allows to remove a specific and existing directory
         * 
         *  \param[in]      obj     The specified directory to be removed
         *  \return         true    If the directory has been removed
         *  \return         false   If the directory does not exist or cannot be removed
         */
        OFT_EXPORT bool remdir(Directory obj);

        /**
         *  \fn     rngd
         *  \brief  The Random Number Generator daemon is designed to generate a random number.
         *          This daemon feeds data from a random number generator to the kernel's random number entropy pool, after first checking
         *          the data to ensure that it is properly random.
         * 
         *  \return         Random number
         */
        OFT_EXPORT std::string rngd();

        /**
         *  \fn     screenres
         *  \brief  The Screen Resolution tool allows users to get the resolution of the computer the software is running on
         * 
         *  \return         The Screen Resolution (height, width)
         */
        OFT_EXPORT std::tuple<int, int> screenres();

        /**
         *  \fn     sha256Sum
         *  \brief  The Secure Hash Algorithm 256 Sum is designed to verify data integrity using the SHA-256
         * 
         *  \param[in]      message The message to hash
         *  \return         Hash
         */
        OFT_EXPORT std::string sha256Sum(const std::string& message);

        /**
         *  \fn     vi
         *  \brief  The vi classic text editor offers a solution to users inserting text into a file founded by its distinguished name
         * 
         *  \param[in]      distn   The distinguished name
         *  \param[in]      content The text to insert
         *  \return         void
         */
        OFT_EXPORT void vi(const std::string& distn, const std::string& content);

        /**
         *  \fn     ~Explorer
         *  \brief  Class destructor
         */
        OFT_EXPORT ~Explorer();
    };
    
}	// END namespace oft

#endif // ! _EXPLORER_HPP_
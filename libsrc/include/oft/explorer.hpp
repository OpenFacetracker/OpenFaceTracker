/////////////////////////////////////////////////////////////////////////////
// AUTHOR: Maxime BEASSE
//
// Copyright (C) 2020  ESIEA Campus of Laval, France
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
/////////////////////////////////////////////////////////////////////////////
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
 *                  Status :                Version 6.0.0 Release 1
 *                  Language :              C++
 * 
 *                  Platform Dependencies:  GNU/Linux, Windows
 * 
 *  \copyright      GPLv3+ : GNU GPL version 3 or later
 *                  Licencied Material - Property of CNS (Confiance Numérique et Sécurité)
 *                  © Copyright - ESIEA Campus Laval 2020
 * 
 *	\author			Maxime BEASSE (beasse@et.esiea.fr)
 * 
 * 	\bug			No known bug to date
 *  \date 			19th June 2020
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
    #include <oft/sha256.hpp>
    #include <random>
    #include <string.h>
    #include <sstream>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <tuple>
    #include <unistd.h>
	#include <boost/filesystem.hpp>
    #include <X11/Xlib.h>
	#include <regex>
	#include <oft/defs.hpp>
    #undef Status
#elif defined _WIN32
    #include <cstdio>
    #include <cstdlib>
    #include <ctime>
    #include <curl/curl.h>
    #include <fstream>
    #include <iostream>
	#include <boost/filesystem.hpp>
    #include <oft/sha256.hpp>
    #include <random>
    #include <string>
    #include <sstream>
    #include <tuple>
	#include <regex>
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

    size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream);

    /**
     *  \class      Explorer
     *  \brief      Class of default file explorer
     */
    class OFT_EXPORT Explorer
    {
	private:
		/**
         *  \fn     Explorer
         *  \brief  Class default constructor. It is not intended to be instantiated.
         */
        Explorer();

    public:

		/**
         *  \fn     fullPath
         *  \brief  Rectifies a path using pathRectifier() and then adds gwd() at the begining if old_path is relative
         * 
         *  \param[in]		old_path     Input path
		 * 
		 * 	\return			Absolute path rectified to match current OS standards
         */
		static std::string fullPath(const std::string& old_path);

        /**
         *  \fn     checkrtsp
         *  \brief  RTSP (Real Timer Streaming Protocol) checker offers a solution to users who want to verify accessibility of a streaming server
         * 
         *  \param[in]      url     Uniform resource locator of a streaming server
		 * 
         *  \return         true    If the streaming server is reachable
         *  \return         false   If the streaming server is unreachable
         */
        static bool checkrtsp(const std::string& url);

		/**
         *  \fn     checkurl
         *  \brief  Checks whether or not a file exist given its URL
         * 
         *  \param[in]      url     	Uniform resource locator of a file
		 *  \param[in]      path    	Path to the cache directory
		 *  \param[in]      verbose    	The function will print progress in std::cout if true (does not affect std::cerr)
		 * 
         *  \return         true    	If download is successful
         *  \return         false   	If download is not successful
         */
		static std::string download(const std::string& url, const std::string& path = "", bool verbose = false);

        /**
         *  \fn     delfs
         *  \brief  The delfs (delete files) tool allows to delete a specific and existing file
         *  
         *  \param[in]      obj     The specified file to be deleted
		 * 
         *  \return         true    If the file has been deleted
         *  \return         false   If the file does not exist or cannot be deleted
         */
        static bool delfs(const std::string& path);

        /**
         *  \fn     empty
         *  \brief  The empty tool allows users to know if a file is empty or not
         * 
         *  \param[in]      distn   The distinguished name of the file
		 * 
         *  \return         true    If the file is empty
         *  \return         false   If the file is not empty
         */
        static bool empty(const std::string& distn);

        /**
         *  \fn     exist
         *  \brief  File existence checker offers a solution to users who want to verify the existence of files or folders on their computer
         * 
         *  \param[in]      distn   The distinguished name of the file or folder to analyze
		 * 
         *  \return         true    If the file or folder exists
         *  \return         false   If the or folder does not exist
         */
        static bool exist(const std::string& distn);

        /**
         *  \fn     forensic
         *  \brief  Digital image and video forensic analyzer. Use to analyze JPEG or JPG file and AVI, MPEG-4 or MATROSKA file
         * 
         *  \param[in]      distn   The distinguished name of the file to analyze
		 * 
         *  \return         true    If the file is a JPEG, JPG, AVI, MPEG-4, MATROSKA file
         *  \return         false   If the file is not a JPEG, JPG, AVI, MPEG-4, MATROSKA file
         */
        static bool forensic(const std::string& distn);

        /**
         *  \fn     gwd
         *  \brief  The gwd (get working directory) tool returns the name of the present/current working directory
         * 
         *  \return        The current working directory
         */
        static std::string gwd();

		/**
         *  \fn     create_directories
         *  \brief  boost::filesystem::create_directories wrapper. Creates all the non-existent directories given a path (boost accepts dir paths)
         * 
         *  \param[in]      path    Path containig potentially non-existent directories to create
		 * 
         *  \return         true    If the new directories has been created
         *  \return         false   If the new directories already exists or cannot be created
         */
		static bool create_directories(const std::string& path);

        /**
         *  \fn     makdir
         *  \brief  The makdir (make directory) tool allows to create new directories
         * 
         *  \param[in]      dirpath     The specified directory tree to be created
		 * 
         *  \return         true    	If the new directory tree has been created
         *  \return         false   	If the new directory tree already exists or cannot be created
         */
        static bool makdir(const std::string& dirpath);

        /**
         *  \fn     remdir
         *  \brief  The remdir (remove directory) tool allows to remove a specific and existing directory
         * 
         *  \param[in]      dirpath     The specified directory to be removed
		 * 
         *  \return         true    	If the directory has been removed
         *  \return         false   	If the directory does not exist or cannot be removed
         */
        static bool remdir(const std::string& dirpath);

        /**
         *  \fn     rename
         *  \brief  Renames a file with a new name
         *
         *  \param[in]      oldf        The specified filepath to rename
         *  \param[in]      newf        The new filepath applied to file
         *
         *  \return         true        If the file has been renamed
         *  \return         false       If the file could not be renamed
         */
        static bool rename(const std::string& oldf, const std::string& newf);

        /**
         *  \fn     rngd
         *  \brief  The Random Number Generator daemon is designed to generate a random number.
         *          This daemon feeds data from a random number generator to the kernel's random number entropy pool, after first checking
         *          the data to ensure that it is properly random.
         * 
         *  \return         Random number
         */
        static std::string rngd();

        /**
         *  \fn     screenres
         *  \brief  The Screen Resolution tool allows users to get the resolution of the computer the software is running on
         * 
         *  \return         The Screen Resolution (height, width)
         */
        static std::tuple<int, int> screenres();

        /**
         *  \fn     sha256Sum
         *  \brief  The Secure Hash Algorithm 256 Sum is designed to verify data integrity using the SHA-256
         * 
         *  \param[in]      message The message to hash
		 * 
         *  \return         Hash
         */
        static std::string sha256Sum(const std::string& message);

        /**
         *  \fn     vi
         *  \brief  The vi classic text editor offers a solution to users inserting text into a file founded by its distinguished name
         * 
         *  \param[in]      distn   The distinguished name
         *  \param[in]      content The text to insert
		 * 
         *  \return         void
         */
        static void vi(const std::string& distn, const std::string& content);
    };
    
}	// END namespace oft

#endif // ! _EXPLORER_HPP_

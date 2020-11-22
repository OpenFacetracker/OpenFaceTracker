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
#ifndef _HANDLERLOG_HPP_
#define _HANDLERLOG_HPP_
/**
 *	\file			handlerlog.hpp
 *	\brief			Header of HandlerLog class
 *
 *					This header contains an useful class to manage logs
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
 *  \date 			11th August 2020
 */
#ifdef __linux__
    #include <ctime>
    #include <fstream>
    #include <iostream>
    #include <oft/explorer.hpp>
    #include <syslog.h>
	#include <oft/defs.hpp>
#elif defined _WIN32
    #include <ctime>
    #include <fstream>
    #include <iostream>
    #include <oft/explorer.hpp>
	#include <oft/defs.hpp>
#endif // ! __linux__ or _WIN32

namespace oft {
    /**
     *  \class      HandlerLog
     *  \brief      Class that help to manage the log files
     */
    class OFT_EXPORT HandlerLog
    {
    private:
        static std::string log_path;		/*!< Path to log file. (default: "./oft.log") */
		
		/**
         *  \fn     HandlerLog
         *  \brief  Class default constructor. It is not intended to be instantiated.
         */
        HandlerLog();

    public:

        /**
         *  \fn     log
         *  \brief  Function that allows users to write a Log
         * 
         *  \param[in]      event       Event log
         *  \return         void
         */
        static void log(const std::string& event);

		/**
         *  \fn     setLogPath
         *  \brief  Sets log file path as a static member
         * 
         *  \param[in]      event       Event log
         *  \return         void
         */
		static void setLogPath(const std::string& path);
    };
    
}   // ! END namespace oft

#endif // ! _HANDLERLOG_HPP_

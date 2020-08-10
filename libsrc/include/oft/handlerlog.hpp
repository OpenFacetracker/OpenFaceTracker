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
    #include <ctime>
    #include <fstream>
    #include <iostream>
    #include <oft/explorer.hpp>
    #include <oft/toolsbox.hpp>
    #include <syslog.h>
	#include <oft/defs.hpp>
#elif defined _WIN32
    #include <ctime>
    #include <fstream>
    #include <iostream>
    #include <oft/explorer.hpp>
    #include <oft/toolsbox.hpp>
	#include <oft/defs.hpp>
#endif // ! __linux__ or _WIN32

namespace oft {
    /**
     *  \class      HandlerLog
     *  \brief      Class that help to manage the log files
     */
    class HandlerLog : public ToolsBox
    {
    private:
        
    public:
        /**
         *  \fn     HandlerLog
         *  \brief  Class parameterized constructor
         * 
         *  \param[in]      _flag       Power switch (must be true)
         */
        OFT_EXPORT HandlerLog(bool _flag);

        /**
         *  \fn     HandlerLog
         *  \brief  Class copy constructor
         *  
         *  \param[in]      obj         HandlerLog object
         */
        OFT_EXPORT HandlerLog(HandlerLog const& obj);

        /**
         *  \fn     create
         *  \brief  Function that allows users to write a Log
         * 
         *  \param[in]      event       Event log
         *  \return         void
         */
        OFT_EXPORT void create(const std::string& event);

        /**
         *  \fn     stop
         *  \brief  Function that alows users to stop using the tool
         * 
         *  \return         void
         */
        OFT_EXPORT void stop();

        /**
         *  \fn     ~HandlerLog
         *  \brief  Class destructor
         */
        OFT_EXPORT ~HandlerLog();
    };
    
}   // ! END namespace oft

#endif // ! _HANDLERLOG_HPP_
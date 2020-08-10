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
#ifndef _HANDLERJSON_HPP_
#define _HANDLERJSON_HPP_
/**
 *	\file			handlerjson.hpp
 *	\brief			Header of HandlerJson class
 *
 *					This header contains an useful class to manage JSON file
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
    #include <iostream>
    #include <json-c/json.h>
    #include <oft/toolsbox.hpp>
	#include <oft/defs.hpp>
#elif defined _WIN32
    #include <iostream>
    #include <json-c/json.h>
    #include <oft/toolsbox.hpp>
	#include <oft/defs.hpp>
#endif // ! __linux__ or _WIN32

namespace oft {
    /**
     *  \class      HandlerJson
     *  \brief
     */
    class HandlerJson : public ToolsBox
    {
    private:
        
    public:
        /**
         *  \fn     HandlerJson
         *  \brief  Class parameterized constructor
         * 
         *  \param[in]      _flag       Power switch (must be true)
         */
        OFT_EXPORT HandlerJson(bool _flag);

        /**
         *  \fn     HandlerJson
         *  \brief  Class copy constructor
         * 
         *  \param[in]      obj         HandlerJson object
         */
        OFT_EXPORT HandlerJson(HandlerJson const& obj);

        /**
         *  \fn     stop
         *  \brief  Function that alows users to stop using the tool
         * 
         *  \return         void
         */
        OFT_EXPORT void stop();

        /**
         *  \fn     ~HandlerJson
         *  \brief  Class destructor
         */
        OFT_EXPORT ~HandlerJson();
    };
    
}	// END namespace oft

#endif // ! _HANDLERJSON_HPP_
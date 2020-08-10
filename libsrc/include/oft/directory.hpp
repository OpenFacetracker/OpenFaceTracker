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
#ifndef _DIRECTORY_HPP_
#define _DIRECTORY_HPP_
/**
 *	\file			directory.hpp
 *	\brief			Header of Directory class
 *
 *					This header contains an useful class that describes directories
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
    #include <oft/file.hpp>
    #include <oft/toolsbox.hpp>
	#include <oft/defs.h>
    #include <vector>
#elif defined _WIN32
    #include <iostream>
    #include <oft/file.hpp>
    #include <oft/toolsbox.hpp>
	#include <oft/defs.hpp>
    #include <vector>
#endif // ! __linux__ or _WIN32

namespace oft {
    /**
     *  \class      Directory
     *  \brief      Class that contains a description of a directory. Sub class inheriting from File Class
     */
    class Directory : public File
    {
    public:
        /**
         *  \fn     Directory
         *  \brief  Class parameterized constructor
         * 
         *  \param[in]      _name       Directory name
         *  \param[in]      _location   Directory location
         */
        OFT_EXPORT Directory(const std::string& _name, const std::string& _location);

        /**
         *  \fn     Directory
         *  \brief  Class copy constructor
         *  
         *  \param[in]      obj         Directory object
         */
        OFT_EXPORT Directory(Directory const& obj);

        /**
         *  \fn     ~Directory
         *  \brief  Class destructor
         */
        OFT_EXPORT ~Directory();
    };
    
}	// END namespace oft

#endif // ! _DIRECTORY_HPP_
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
#ifndef _FILE_HPP_
#define _FILE_HPP_
/**
 *	\file			file.hpp
 *	\brief			Header of File class
 *
 *					This header contains an useful class that describes a file
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
    #include <oft/toolsbox.hpp>
	#include <oft/defs.hpp>
#elif defined _WIN32
    #include <iostream>
    #include <oft/toolsbox.hpp>
	#include <oft/defs.hpp>
#endif // ! __linux__ or _WIN32

namespace oft {
    /**
     *  \class      File
     *  \brief      Class that contains a description of a file. Base class.
     */
    class File
    {
    protected:
        std::string name;               /*!< File name */
        std::size_t size;               /*!< File size */
        std::string extension;          /*!< File extension */
        std::string location;           /*!< File location */
        bool isFile;                    /*!< Flag that differentiates a file from a directory */

    private:
        /**
         *  \fn     File
         *  \brief  Class default constructor. It is not intended to be instantiated.
         */
        File();
        
    public:
        /**
         *  \fn     File
         *  \brief  Class parameterized constructor
         *  
         *  \param[in]      _name       File name
         *  \param[in]      _extension  File extension
         *  \param[in]      _location   File location
         *  \param[in]      flag        Flag to differentiate a file from a directory
         */
        OFT_EXPORT File(const std::string& _name, const std::string& _extension, const std::string& _location, bool flag);

        /**
         *  \fn     File
         *  \brief  Class copy constructor
         * 
         *  \param[in]      obj         File object
         */
        OFT_EXPORT File(File const& obj);

        /**
         *  \fn     distn
         *  \brief  The distn (Distinguished Name) tool allows users to get a string that is formed by concatening the relative distinguished name
         *          of the object and each of its ancestors all the way to root (location).
         * 
         *  \return         The distinguished name of the object
         */
        OFT_EXPORT std::string distn() const;

        /**
         *  \fn     File
         *  \brief  Class destructor
         */
        OFT_EXPORT ~File();
    };
    
}	// END namespace oft

#endif // ! _FILE_HPP_
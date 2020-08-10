///////////////////////////////////////////////////////////////////////////////////////////////////////////
// AUTHOR: Hethsron Jedaël BOUEYA
//
//                             LICENSE AGREEMENT
// Copyright (c) 2020, ESIEA Campus of Laval, France
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
#ifndef _TOOLSBOX_HPP_
#define _TOOLSBOX_HPP_
/**
 *	\file			toolsbox.hpp
 *	\brief			Header of ToolsBox class
 *
 *					This header contains an useful class to manage different tools
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
 *	\author			Hethsron Jedaël BOUEYA (boueya@et.esiea.fr)
 * 
 * 	\bug			No known bug to date
 *  \date 			3rd June 2019
 */
#ifdef __linux__
    #include <iostream>
	#include <oft/defs.h>
#elif defined _WIN32
    #include <iostream>
	#include <oft/defs.hpp>
#endif // ! __linux__ or _WIN32

namespace oft {

    /**
     *  \class      ToolsBox
     *  \brief      Class of differents tools
     */
    class ToolsBox
    {
    protected:
        bool flag;                          /*!< Power switch */

    private:
        /**
         *  \fn     ToolsBox
         *  \brief  Class default constructor. It is not intended to be instantiated
         */
        ToolsBox();
        
    public:
        /**
         *  \fn     ToolsBox()
         *  \brief  Class parameterized constructor
         * 
         *  \param[in]      _flag           Power switch (must be tree)
         */
        OFT_EXPORT ToolsBox(bool _flag);

        /**
         *  \fn     ToolsBox
         *  \brief  Class copy constructor
         * 
         *  \param[in]      obj             ToolsBox object
         */
        OFT_EXPORT ToolsBox(ToolsBox const& obj);

        /**
         *  \fn     stop
         *  \brief  Pure virtual function. However, the derived class still has to implement the pure virtual function.
         * 
         *  \return         void
         */
        OFT_EXPORT virtual void stop() = 0;

        /**
         *  \fn     ~ToolsBox
         *  \brief  Class destructor
         */
        OFT_EXPORT virtual ~ToolsBox();
    };
    
}	// END namespace oft

#endif // ! _TOOLSBOX_HPP_
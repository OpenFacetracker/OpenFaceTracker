/////////////////////////////////////////////////////////////////////////////
// AUTHOR: Hethsron Jedaël BOUEYA
//
// Copyright (C) 2019  ESIEA Campus of Laval, France
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
#ifndef _CONSOLE_HPP_
#define _CONSOLE_HPP_
/**
 *	\file			console.hpp
 *	\brief			Header of Console class
 *
 *					This header contains an useful class to manage fundamental commands
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
    #include <algorithm>
    #include <iostream>
    #include <oft/explorer.hpp>
    #include <oft/backend.hpp>
    #include <oft/labcollector.hpp>
    #include <vector>
#elif defined _WIN32
    #include <algorithm>
    #include <iostream>
    #include <oft/explorer.hpp>
    #include <oft/backend.hpp>
    #include <oft/labcollector.hpp>
    #include <vector>
#endif // ! __linux__ or _WIN32

namespace oft {
	
    /**
     *  \class      Console
     *  \brief      Class of default command-line options analyzer
     */
    class Console
    {
    private:
        int argco;                  /*!< Argument count */
        char** argve;               /*!< Argument vector */

        /**
         *  \fn     Console
         *  \brief  Class default constructor. It is not intended to be instantiated.
         */
        Console();
    public:
        /**
         *  \fn     Console
         *  \brief  Class parameterized constructor
         * 
         *  \param[in]      _argco      Argument count
         *  \param[in]      _argve      Argument vector
         */
        Console(int _argco, char* _argve[]);

        /**
         *  \fn     Console
         *  \brief  Class copy constructor
         * 
         *  \param[in]      obj         Console object
         */
        Console(Console const& obj);

        /**
         *  \fn     listener
         *  \brief  Class listener method
         * 
         *  \return         void
         */
        void listener();

        /**
         *  \fn     ~Console
         *  \brief  Class destructor
         */
        ~Console();
    };
    
}	// END namespace oft

#endif // ! _CONSOLE_HPP_

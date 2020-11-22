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
 *  \date 			17th August 2020
 */
#ifdef __linux__
    #include <iostream>
	#include <fstream>
    #include <nlohmann/json.hpp>
	#include <oft/handlerlog.hpp>
	#include <oft/explorer.hpp>
	#include <oft/defs.hpp>
#elif defined _WIN32
    #include <iostream>
	#include <fstream>
    #include <nlohmann/json.hpp>
	#include <oft/handlerlog.hpp>
	#include <oft/explorer.hpp>
	#include <oft/defs.hpp>
#endif // ! __linux__ or _WIN32

namespace oft {
    /**
     *  \class      HandlerJson
     *  \brief
     */
    class HandlerJson : public nlohmann::json
    {
    private:
		/**
         *  \fn     HandlerJson
         *  \brief  Class default constructor. It is not intended to be instantiated.
         */
        HandlerJson();
		
    public:

		/**
         *  \fn     FacialDetection
         *  \brief  Class parameterized constructor
         *
         *  \param[in]      facedetect		Path to a CascadeClassifer file to detect faces
         */
		OFT_EXPORT HandlerJson(const std::string& file);

		/**
         *  \fn     ~HandlerJson
         *  \brief  Class destructor
         */
        OFT_EXPORT ~HandlerJson();
    };

}	// END namespace oft

#endif // ! _HANDLERJSON_HPP_

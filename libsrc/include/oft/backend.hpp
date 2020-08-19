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
#ifndef _BACKEND_HPP_
#define _BACKEND_HPP_
/**
 *	\file			backend.hpp
 *	\brief			Header of Backend class
 *
 *					This header contains an useful class to manage database
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
    #include <cppdb/frontend.h>
    #include <ctime>
    #include <oft/explorer.hpp>
    #include <oft/handlerlog.hpp>
	#include <oft/defs.hpp>
    #include <iostream>
#elif defined _WIN32
    #include <cppdb/frontend.h>
    #include <ctime>
    #include <oft/explorer.hpp>
    #include <oft/handlerlog.hpp>
	#include <oft/defs.hpp>
    #include <iostream>
#endif // ! __linux__ or _WIN32

namespace oft {
    /**
     *  \class      Backend
     *  \brief      Class of database management system
     */
    class OFT_EXPORT Backend
    {
    private:
        static std::string database;                        /*!< The database filepath */
        static std::string connection;              		/*!< Connection string */

        static cppdb::result getAllRes;                     /*!< GetAll Result. Initialized when getAll() is called and updated in getNext() */

		/**
         *  \fn     Backend
         *  \brief  Class default constructor. It is not intended to be instantiated.
         */
        Backend();

    public:
        /**
         *  \fn     setDBPath
         *  \brief  Setter for database path
         * 
         *  \param[in]      db_path			Path to database
         */
        static void setDBPath(const std::string& db_path);

        /**
         *  \fn     insert
         *  \brief  Function that allows users to insert image file in the database
         * 
         *  \param[in]      label		Label associated to person
         *  \param[in]      is			Float vector stored as BLOB
         *  \param[in]      nb_Samples  Total number of samples used to average data
		 * 
         *  \return         Row ID    	If entry is correctly inserted
         *  \return         -1   		If not
         */
        static long long insert(const std::string& label, std::istream& is, int nb_Samples = 1);

        /**
         *  \fn     update
         *  \brief  Function that allows users to update a Person data in the database
         *
         *  \param[in]      label		Label associated to person
         *  \param[in]      is			Float vector stored as BLOB
         *  \param[in]      nb_Samples  Total number of samples used to average data
		 * 
         *  \return         true    	If entry is correctly updated
         *  \return         false   	If not
         */
        static bool update(const std::string& label, std::istream& is, int nb_Samples);

        /**
         *  \fn     remove
         *  \brief  Function that allows users to delete a Person row in the database
         *
         *  \param[in]      label       Label associated to the Person to delete
		 * 
         *  \return         true    	If entry is correctly removed
         *  \return         false   	If not
         */
        static bool remove(const std::string& label);

        /**
         *  \fn     size
         *  \brief  Function that allows users to get the database size or the total number of entries in the databse
         * 
         *  \return         size_t		Number of entry in table 'Person'
         */
        static std::size_t size();

        /**
         *  \fn     getAll
         *  \brief  Function that initializes the getAll() statement
         *
         *  \return         true    	If statement is correctly initialized
         *  \return         false   	If not
         */
        static bool getAll();

        /**
         *  \fn     getNext
         *  \brief  Function that iterates over each row of getAll() result
		 * 
         *  \param[in]      result      Row data as Tuple. <ID, label, nbSamples, data>
         *
         *  \return         true    	If a row has been retrieved
         *  \return         false   	If there is no more entry in result
         */
        static bool getNext(std::tuple<long long, std::string, int, std::stringstream>& result);

        /**
         *  \fn     start
         *  \brief  Function that clears and initializes database
		 * 
		 * 	Will generate a .db if it does not exist
         */
        static void start();
    };

}   // END namespace oft

#endif // ! _BACKEND_HPP_
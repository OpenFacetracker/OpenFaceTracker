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
    #include <oft/toolsbox.hpp>
	#include <oft/defs.hpp>
    #include <iostream>
#elif defined _WIN32
    #include <cppdb/frontend.h>
    #include <ctime>
    #include <oft/explorer.hpp>
    #include <oft/handlerlog.hpp>
    #include <oft/toolsbox.hpp>
	#include <oft/defs.hpp>
    #include <iostream>
#endif // ! __linux__ or _WIN32

namespace oft {
    /**
     *  \class      Backend
     *  \brief      Class of database management system
     */
    class Backend : public ToolsBox
    {
    private:
        std::string connection;                         /*!< Connection string */
        std::string database;                           /*!< The database file */
        cppdb::session session;                         /*!< The database session */

        cppdb::result getAllRes;                        /*!< GetAll Result. Initialized when getAll() is called and updated in getNext() */

    public:
        /**
         *  \fn     Backend
         *  \brief  Class parameterized constructor
         * 
         *  \param[in]      _flag       Power switch (must be true)
         */
        OFT_EXPORT Backend(bool _flag);

        /**
         *  \fn     Backend
         *  \brief  Class copy constructor
         * 
         *  \param[in]      obj         Backend object
         */
        OFT_EXPORT Backend(Backend const& obj);

        /**
         *  \fn     insert
         *  \brief  Function that allows users to insert image file in the database
         * 
         *  \param[in]      distn       The distinguished name of image file that identifies a physical person
         *  \return         long long   Row ID
         */
        OFT_EXPORT long long insert(const std::string& label, std::istream& is, int nb_Samples = 1);

        /**
         *  \fn     update
         *  \brief  Function that allows users to update a Person data in the database
         *
         *  \param[in]      distn       The distinguished name of image file that identifies a physical person
         *  \return         bool        Success
         */
        OFT_EXPORT bool update(const std::string& label, std::istream& is, int nb_Samples);

        /**
         *  \fn     remove
         *  \brief  Function that allows users to delete a Person row in the database
         *
         *  \param[in]      label       Label associated to the Person to delete
         *  \return         bool        Success
         */
        OFT_EXPORT bool remove(const std::string& label);

        /**
         *  \fn     size
         *  \brief  Function that allows users to get the database size or the total number of entries in the databse
         * 
         *  \return         The database size
         */
        OFT_EXPORT std::size_t size();

        /**
         *  \fn     getAll
         *  \brief  Function that initializes the getAll() statement
         *
         *  \return         Success
         */
        OFT_EXPORT bool getAll();

        /**
         *  \fn     getNext
         *  \brief  Function that iterates over each row of getAll() result
         *
         *  \return         Success
         */
        OFT_EXPORT bool getNext(std::tuple<long long, std::string, int, std::stringstream>& result);

        /**
         *  \fn     start
         *  \brief  Function that allows users to start using the database management system with its default database file
         */
        OFT_EXPORT void start();

        /**
         *  \fn     stop
         *  \brief  Function that allows users to stop using the database management system
         */
        OFT_EXPORT void stop();
        
        /**
         *  \fn     ~Backend
         *  \brief  Class destructor
         */
        OFT_EXPORT ~Backend();
    };

}   // END namespace oft

#endif // ! _BACKEND_HPP_
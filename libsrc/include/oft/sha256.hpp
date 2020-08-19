///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Updated to C++, zedwood.com 2012
// Based on Olivier Gay's version
// See Modified BSD License below: 
//
// FIPS 180-2 SHA-224/256/384/512 implementation
// Issue date:  04/30/2005
// http://www.ouah.org/ogay/sha2/
//
// Copyright (C) 2005, 2007 Olivier Gay <olivier.gay@a3.epfl.ch>
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. Neither the name of the project nor the names of its contributors
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
// OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
// SUCH DAMAGE.
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SHA256_HPP_
#define _SHA256_HPP_
/**
 *	\file			sha256.hpp
 *	\brief			Header of Sha256 class
 *
 *					This header contains an useful class to manage Secure Hash Algorith
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
    #include <string.h>
#elif defined _WIN32
    #include <iostream>
    #include <string.h>
#endif // ! __linux__ or _WIN32

#define SHA2_SHFR(x, n)    (x >> n)
#define SHA2_ROTR(x, n)   ((x >> n) | (x << ((sizeof(x) << 3) - n)))
#define SHA2_ROTL(x, n)   ((x << n) | (x >> ((sizeof(x) << 3) - n)))
#define SHA2_CH(x, y, z)  ((x & y) ^ (~x & z))
#define SHA2_MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define SHA256_F1(x) (SHA2_ROTR(x,  2) ^ SHA2_ROTR(x, 13) ^ SHA2_ROTR(x, 22))
#define SHA256_F2(x) (SHA2_ROTR(x,  6) ^ SHA2_ROTR(x, 11) ^ SHA2_ROTR(x, 25))
#define SHA256_F3(x) (SHA2_ROTR(x,  7) ^ SHA2_ROTR(x, 18) ^ SHA2_SHFR(x,  3))
#define SHA256_F4(x) (SHA2_ROTR(x, 17) ^ SHA2_ROTR(x, 19) ^ SHA2_SHFR(x, 10))
#define SHA2_UNPACK32(x, str)                 \
{                                             \
    *((str) + 3) = (uint8) ((x)      );       \
    *((str) + 2) = (uint8) ((x) >>  8);       \
    *((str) + 1) = (uint8) ((x) >> 16);       \
    *((str) + 0) = (uint8) ((x) >> 24);       \
}
#define SHA2_PACK32(str, x)                   \
{                                             \
    *(x) =   ((uint32) *((str) + 3)      )    \
           | ((uint32) *((str) + 2) <<  8)    \
           | ((uint32) *((str) + 1) << 16)    \
           | ((uint32) *((str) + 0) << 24);   \
}

namespace oft {
    /**
     *  \class      Sha256
     *  \brief      Class that help to manage Secure Hash Algorithm 256
     */
    class Sha256
    {
    protected:
        typedef unsigned char uint8;                                                /*!< Alias for unsigned char */
        typedef unsigned int uint32;                                                /*!< Alias for unsigned int */
        typedef unsigned long long uint64;                                          /*!< Alias for unsigned long long */
        const static uint32 sha256_k[];                                             /*!< Digest block for sha256 */
        static const unsigned int SHA224_256_BLOCK_SIZE = (512/8);                  /*!< Digest block size */

    private:
        unsigned int m_tot_len;                                                     /*!< Total length */
        unsigned int m_len;                                                         /*!< Length */
        unsigned char m_block[2*SHA224_256_BLOCK_SIZE];                             /*!< Digest block for sha224 and sha256 */
        uint32 m_h[8];                                                              /*!< Block */

        /**
         *  \fn     transform
         *  \brief  Function that allows users to transform message in block
         * 
         *  \param[in]      message         Message to transform
         *  \param[in]      block_nb        Block
         */
        void transform(const unsigned char *message, unsigned int block_nb);

    public:
		static const unsigned int DIGEST_SIZE = ( 256 / 8 );						/*!< Digest size */

        /**
         *  \fn     Sha256
         *  \brief  Class default constructor
         * 
         */
        Sha256();

        /**
         *  \fn     Sha256
         *  \brief  Class copy constructor
         * 
         *  \param[in]      obj             Sha256 object
         */
        Sha256(Sha256 const& obj);

        /**
         *  \fn     final
         *  \brief  Function that allows users to finalize the calculation of Secure Hash Algorithm
         * 
         *  \param[in]      digest          Digest
         *  \return         void
         */
        void final(unsigned char *digest);

        /**
         *  \fn     stop
         *  \brief  Function that allows users to stop Secure Hash Algorithm
         * 
         *  \return         void
         */
        void stop();

        /**
         *  \fn     update
         *  \brief  Function that allows users to update Secure Hash Algorithm
         * 
         *  \param[in]      message         Message to transform
         *  \param[in]      len             Length
         *  \return         void
         */
        void update(const unsigned char *message, unsigned int len);

        /**
         *  \fn     ~Sha256
         *  \brief  Class destructor
         */
        ~Sha256();
    };

}   // ! END namespace oft

#endif // ! _SHA256_HPP_

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// AUTHOR: Maxime BEASSE
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
#ifndef _FACIALDETECTION_HPP_
#define _FACIALDETECTION_HPP_
/**
 *	\file			facialdetection.hpp
 *	\brief			Header of FacialDetection class
 *
 *					This header contains an useful class to perform facial detection
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
 *  \date 			16th March 2020
 */
#ifdef __linux__
    #include <iostream>
    #include <oft/backend.hpp>
    #include <oft/explorer.hpp>
    #include <oft/handlerdraw.hpp>
    #include <oft/handlerlog.hpp>
    #include <opencv2/face.hpp>
    #include <opencv2/opencv.hpp>
	#include <oft/defs.hpp>
    #include <tuple>
#elif defined _WIN32
    #include <iostream>
    #include <oft/backend.hpp>
    #include <oft/explorer.hpp>
    #include <oft/handlerdraw.hpp>
    #include <oft/handlerlog.hpp>
    #include <opencv2/face.hpp>
    #include <opencv2/opencv.hpp>
	#include <oft/defs.hpp>
    #include <tuple>
#endif // ! __linux__ or _WIN32

namespace oft {
    /**
     *  \class      FacialDetection
     *  \brief      Class of facial detection
     */
    class FacialDetection
    {
    private:
        cv::CascadeClassifier haarcascade;                      /*!< Haarcascade classifier */

		/**
         *  \fn     FacialDetection
         *  \brief  Class default constructor. It is not intended to be instantiated.
         */
        FacialDetection();

    public:

        static const cv::Size face_size;

        /**
         *  \fn     FacialDetection
         *  \brief  Class parameterized constructor
         *
         *  \param[in]      facedetect		Path to a CascadeClassifer file to detect faces
         */
        OFT_EXPORT FacialDetection(const std::string& facedetect);

        /**
         *  \fn     FacialDetection
         *  \brief  Class copy constructor
         *
         *  \param[in]      obj             FacialDetection object
         */
        //OFT_EXPORT FacialDetection(FacialDetection const& obj);

        /**
         *  \fn     perform
         *  \brief  Detects and returns rectangles on faces in the image
         *
         *  \param[in]      frame			Matrix of the image
         *  \param[out]     positions		List of positions of detected faces on _frame
         */
        OFT_EXPORT void perform(cv::Mat frame, std::vector<cv::Rect>& positions, bool isEqHist = false);

        /**
         *  \fn     ~FacialDetection
         *  \brief  Class destructor
         */
        OFT_EXPORT ~FacialDetection();
    };
} // END namespace oft

#endif // ! _FACIALDETECTION_HPP_

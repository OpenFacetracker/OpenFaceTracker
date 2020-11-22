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

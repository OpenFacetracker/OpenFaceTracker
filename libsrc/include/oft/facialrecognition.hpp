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
#ifndef _FACIALRECOGNITION_HPP_
#define _FACIALRECOGNITION_HPP_
/**
 *	\file			facialrecognition.hpp
 *	\brief			Header of FacialRecognition class
 *
 *					This header contains an useful class to perform facial recognition
 *
 *  \details        System :                OpenFaceTracker
 *                  Component Name :        oft
 *                  Status :                Version 6.0.0 Release 1
 *                  Language :              C++
 *
 *                  Platform Dependencies:  GNU/Linux, Windows
 *
 *  \copyright      GPLv3+ : GNU GPL version 3 or later
 *                  Licencied Material - Property of CNS (Confiance Num�rique et S�curit�)
 *                  � Copyright - ESIEA Campus Laval 2020
 *
 *	\author			Maxime BEASSE (beasse@et.esiea.fr)
 *
 * 	\bug			No known bug to date
 *  \date 			16th April 2020
 */
#ifdef __linux__
	#include <iostream>
	#include <fstream>
	#include <sstream>
	#include <string>
	#include <oft/backend.hpp>
	#include <oft/explorer.hpp>
	#include <oft/globalanalysis.hpp>
	#include <oft/handlerdraw.hpp>
	#include <oft/handlerlog.hpp>
	#include <opencv2/face.hpp>
	#include <opencv2/opencv.hpp>
    #include <oft/toolsbox.hpp>
	#include <oft/defs.hpp>
	#include <tuple>
#elif defined _WIN32
	#include <iostream>
	#include <fstream>
	#include <sstream>
	#include <string>
	#include <oft/backend.hpp>
	#include <oft/explorer.hpp>
	#include <oft/globalanalysis.hpp>
	#include <oft/facialdetection.hpp>
	#include <oft/handlerdraw.hpp>
	#include <oft/handlerlog.hpp>
	#include <opencv2/face.hpp>
	#include <opencv2/opencv.hpp>
    #include <oft/toolsbox.hpp>
	#include <oft/defs.hpp>
	#include <tuple>
#endif // ! __linux__ or _WIN32

namespace oft {
    /**
     *  \class      FacialRecognition
     *  \brief      Class of facial recognition
     */
    class FacialRecognition : public GlobalAnalysis
    {
    private:

        static constexpr double RETAINED_VARIANCE_GENERIC_PCA = 0.95;       /*!< Joliffe criterion. We keep RETAINED_VARIANCE_GENERIC_PCA of the variance of generic PCA to limit the number of components */
        
        cv::PCA generic_pca;                                                /*!< PCA based on a large sample of faces to generalize */

        std::tuple<std::vector<long long>, std::vector<std::string>, std::vector<cv::Mat>, std::vector<int>> gallery_data;    /*!< Tuples vector of the projection of every image of the database and its corresponding label, id and nb_samples */

        double threshold = 5000.0;

    public:
        /**
         *  \fn     FacialRecognition
         *  \brief  Class parameterized constructor
         *
         *  \param[in]      _fuse           Fuse (must be true)
         */
        OFT_EXPORT FacialRecognition(bool _fuse);

        /**
         *  \fn     FacialRecognition
         *  \brief  Class copy constructor
         *
         *  \param[in]      obj             FacialRecognition object
         */
        OFT_EXPORT FacialRecognition(FacialRecognition const& obj);

        /**
         *  \fn     perform
         *  \brief  Recognize a face from a Matrix using a database
         *
         *  \param[in]      _face           Matrix of a face to identify
         *
         *  \return         std::tuple      Label associated to most similar face and confidence
         */
        OFT_EXPORT std::tuple<std::string, double> perform(cv::Mat _face);

        /**
         *  \fn     project
         *  \brief  Recognize a face from a Matrix using a database
         *
         *  \param[in]      _face           Matrix of a face to identify
         *
         *  \return         cv::Mat         Projection of _face onto generic_pca subspace 
         */
        OFT_EXPORT void add_Person(cv::Mat& face, std::string label, int nb_Samples = 1);

        /**
         *  \fn     project
         *  \brief  Project given face onto generic_pca subspace
         *
         *  \param[in]      face           Matrix of a face to project
         *
         *  \return         cv::Mat         Projection of _face onto generic_pca subspace
         */
        OFT_EXPORT cv::Mat project(cv::Mat& face, cv::Mat squared = cv::Mat(), cv::Mat dst = cv::Mat());

        /**
         *  \fn     stop
         *  \brief  Function that allows users to stop facial detection
         *
         *  \return         void
         */
        OFT_EXPORT void stop();

        /**
         *  \fn     ~FacialRecognition
         *  \brief  Class destructor
         */
        OFT_EXPORT ~FacialRecognition();

        /**
         *  \fn     getSquareImage
         *  \brief  Compute and returns a square resized image of img. Apsect ratio is preserved and extra pixels are set to black
         *  (https://stackoverflow.com/questions/28562401/resize-an-image-to-a-square-but-keep-aspect-ratio-c-opencv)
         * 
         *  \param[in]      img                 cv::Mat of an image to resize as square
         *  \param[in]      target_width        Width and Height of dst
         *
         *  \return         cv::Mat             A square image of size [target_width x target_width] containing img with its aspect ratio respected and zero padding
         */
        OFT_EXPORT static cv::Mat getSquareImage(const cv::Mat& img, int target_width = 60);

    private:

        /**
         *  \fn     updateGallery
         *  \brief  Get all database and keep in gallery_data
         *
         */
        void updateGallery();
    };
} // END namespace oft

#endif // ! _FACIALRECOGNITION_HPP_
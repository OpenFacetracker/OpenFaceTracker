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
	#include <oft/facialdetection.hpp>
	#include <oft/handlerdraw.hpp>
	#include <oft/handlerlog.hpp>
	#include <opencv2/face.hpp>
	#include <opencv2/opencv.hpp>
	#include <oft/defs.hpp>
	#include <tuple>
#elif defined _WIN32
	#include <iostream>
	#include <fstream>
	#include <sstream>
	#include <string>
	#include <oft/backend.hpp>
	#include <oft/explorer.hpp>
	#include <oft/facialdetection.hpp>
	#include <oft/handlerdraw.hpp>
	#include <oft/handlerlog.hpp>
	#include <opencv2/face.hpp>
	#include <opencv2/opencv.hpp>
	#include <oft/defs.hpp>
	#include <tuple>
#endif // ! __linux__ or _WIN32

namespace oft {
    /**
     *  \class      FacialRecognition
     *  \brief      Class of facial recognition
     */
    class FacialRecognition {

    private:

        static constexpr double RETAINED_VARIANCE_GENERIC_PCA = 0.95;       /*!< Joliffe criterion. We keep RETAINED_VARIANCE_GENERIC_PCA of the variance of generic PCA to limit the number of components */
        cv::PCA generic_pca;                                                /*!< PCA based on a large sample of faces to generalize */
        double threshold = 4000.0;

		cv::Ptr<cv::face::Facemark> facemarker;								/*!< Face landmarks detector */
		std::vector<cv::Point2f> mean_landmarks;							/*!< PCA mean landmarks */
		
        std::tuple<std::vector<long long>, std::vector<std::string>, std::vector<cv::Mat>, std::vector<int>> gallery_data;    /*!< Tuples vector of the projection of every image of the database and its corresponding label, id and nb_samples */

		//* UNUSED
		// static const cv::Point2f boundaries[8];								/*!< Boundaries Points. Added to Landmarks to form all Delaunay Triangles */
		// static const int delaunayTriangulation[142][3];						/*!< Delaunay Triangulation of target facial landmarks */
	
		/**
         *  \fn     FacialRecognition
         *  \brief  Class default constructor. It is not intended to be instantiated.
         */
        FacialRecognition();

    public:
        /**
         *  \fn     FacialRecognition
         *  \brief  Class parameterized constructor
         *
         *  \param[in]      pca_file       	Path to PCA file
         *  \param[in]      facemark		Path to a facemark model file
         */
        OFT_EXPORT FacialRecognition(const std::string& pca_file, const std::string& facemark);

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
         *  \param[in]     	face           	Matrix of a face to identify
         *
         *  \return        	Predicted label associated to most similar face and confidence
		 * 	\return			<"UNKOWN", -1.0> 	if the nearest person was at a distance > this->threshold
         */
        OFT_EXPORT std::vector<std::tuple<std::string, double>> perform(cv::Mat frame, const std::vector<cv::Rect>& facePositions, bool isEqHist = false, cv::Mat projections = cv::Mat());

		/**
         *  \fn     alignFace
         *  \brief  Align a given face to generic_pca.mean
         *
         *  \param[in]     	face           	Frame containing the face
         *  \param[out]     dst       		Aligned face (dSize=FacialDetection::face_size)
         *  \param[in]     	landmarks       Landmarks of the face to align
         */
		OFT_EXPORT void alignFace(cv::Mat frame, cv::Mat dst, std::vector<cv::Point2f> landmarks);

		/**
         *  \fn     alignFace
         *  \brief  Align a given face to generic_pca.mean
         *
         *  \param[in]     	face           	Frame containing the face
         *  \param[out]     dst       		Aligned face (dSize=FacialDetection::face_size)
         *  \param[in]     	face_position   Position of the face in the frame
         */
		OFT_EXPORT void alignFace(cv::Mat frame, cv::Mat dst, cv::Rect face_position);

        /**
         *  \fn     add_Person
         *  \brief  Recognize a face from a Matrix using a database
         *
         *  \param[in]      projection      Projection of the face onto generic_pca subspace
         *  \param[in]      label         	Label associated to the person
         *  \param[in]      nb_Samples    	Number of samples used to average face
         */
        OFT_EXPORT void add_Person(cv::Mat projection, std::string label, int nb_Samples = 1);

        /**
         *  \fn     project
         *  \brief  Project given face onto generic_pca subspace
         *
         *  \param[in]      frame           Frame containing a face
         *  \param[in]      position        Rectangle tracking the face
         *  \param[in]      squared         Optionnal buffer (dsize=FacialDetection::face_size)
         *  \param[out]     dst           	Optionnal dst buffer (dsize=generic_pca.mean.size)
         *
         *  \return         Projection of face onto generic_pca subspace
         */
        OFT_EXPORT cv::Mat project(cv::Mat frame, cv::Rect position, cv::Mat squared = cv::Mat(), cv::Mat dst = cv::Mat(), bool isEqHist = false);

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
         *  \return         A square image of size [target_width x target_width] containing img with its aspect ratio respected and zero padding
         */
        static cv::Mat getSquareImage(const cv::Mat& img, int target_width = FacialDetection::face_size.width);

    private:

        /**
         *  \fn     updateGallery
         *  \brief  Get all database and keep in gallery_data
         */
        void updateGallery();
    };
} // END namespace oft

#endif // ! _FACIALRECOGNITION_HPP_

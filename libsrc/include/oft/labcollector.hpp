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
#ifndef _LABCOLLECTOR_HPP_
#define _LABCOLLECTOR_HPP_
/**
 *	\file			labcollector.hpp
 *	\brief			Header of LabCollector class
 *
 *					This header contains an useful class to manage different types of analysis to practice
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
 *  \date 			8th August 2020
 */
#ifdef __linux__
    #include <iostream>
    #include <oft/explorer.hpp>
    #include <oft/facialdetection.hpp>
    #include <oft/facialrecognition.hpp>
    #include <oft/handlerdraw.hpp>
    #include <oft/handlerjson.hpp>
    #include <opencv2/opencv.hpp>
	#include <oft/defs.hpp>
    #include <tuple>
#elif defined _WIN32
    #include <iostream>
    #include <oft/explorer.hpp>
    #include <oft/facialdetection.hpp>
    #include <oft/facialrecognition.hpp>
    #include <oft/handlerdraw.hpp>
    #include <oft/handlerjson.hpp>
    #include <opencv2/opencv.hpp>
	#include <opencv2/videoio/registry.hpp>
	#include <oft/defs.hpp>
    #include <tuple>
#endif // ! __linux__ or _WIN32

namespace oft {

	static void onMouse( int event, int x, int y, int, void* data);

    /**
     *  \class      LabCollector
     *  \brief      Class of default methods of analysis
     */
    class OFT_EXPORT LabCollector
    {
    private:

		/**
         *  \fn     LabCollector
         *  \brief  Class default constructor. It is not intended to be instantiated.
         */
        LabCollector();

		static std::string configFilePath;		/*<! Set configFilePath to a JSON config file to set Backend, FacialDetection, FacialRecognition and HandlerLog files */

    public:

		static void setConfigPath(const std::string& filepath);

        /**
         *  \fn     VideoAnalysis
         *  \brief  Function that allows users to perform analysis from a real time streaming that could be a video file, an image sequence or a camera
         *	
		 *
         *  \param[in]      streaming           Streaming media. Can be a camera device, an AVI/MPEG-4/MATROSKA file or a rechable streaming URL with RTSP or HTTP scheme
         *  \param[in]      label           	Optionnal parameter. When !label.empty(), every detected face will be projected and averaged to be added to the database under 'label'
         *  \param[in]      confirmation        Optionnal parameter. If true, every detected face will appear in a window waiting for user confirmation ('y' key press) before adding to database. Use carefully when false
         */
        static void VideoAnalysis(char streaming[], std::string label = "", bool confirmation = false);

        /**
         *  \fn     ImageAnalysis
         *  \brief  Function that allows users to perform analysis from an image file
         *
         *  \param[in]      file           		Image media. Can be a JPEG or JPG file or a rechable URL with RTSP or HTTP scheme
         *  \param[in]      label           	Optionnal parameter. When !label.empty(), every detected face will be projected and averaged to be added to the database under 'label'
         *  \param[in]      confirmation        Optionnal parameter. If true, every detected face will appear in a window waiting for user confirmation ('y' key press) before adding to database. Use carefully when false
         */
        static void ImageAnalysis(char file[], std::string label = "", bool confirmation = false);

        /**
         *  \fn     askConfirmation
         *  \brief  Function that awaits for a key press to continue
         *
         *  \return         true if user has pressed 'y' key
		 * 	\return         false if user has pressed any other key
         */
        static bool askConfirmation();
    };

}   // END namespace oft

#endif // ! _LABCOLLECTOR_HPP_

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

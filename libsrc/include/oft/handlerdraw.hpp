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
#ifndef _HANDLERDRAW_HPP_
#define _HANDLERDRAW_HPP_
/**
 *	\file			handlerdraw.hpp
 *	\brief			Header of HandlerDraw class
 *
 *					This header contains an useful class to manage particular geometric shapes
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
    #include <opencv2/opencv.hpp>
	#include <oft/defs.hpp>
#elif defined _WIN32
    #include <iostream>
    #include <opencv2/opencv.hpp>
	#include <oft/defs.hpp>
#endif // ! __linux__ or _WIN32

namespace oft {
    /**
     *  \class      HandlerDraw
     *  \brief
     */
    class OFT_EXPORT HandlerDraw
    {
	private:
		/**
         *  \fn     HandlerDraw
         *  \brief  Class default constructor. It is not intended to be instantiated.
         */
        HandlerDraw();

    public:

        /**
         *  \fn     line
         *  \brief  Function that allows users to draw dotted line
         * 
         *  \param[in]      img             Image
         *  \param[in]      pt1             Vertex of the line (Top left)
         *  \param[in]      pt2             Vertex of the line opposite to pt1 (bottom right)
         *  \param[in]      color           Line color or brightness
         *  \param[in]      thickness       Thickness of line
         *  \param[in]      gap             Point gap
         *  \return         void
         */
        static void line(cv::Mat& img, cv::Point pt1, cv::Point pt2, const cv::Scalar& color, const int thickness, const int gap);

        /**
         *  \fn     rectangle
         *  \brief  Function that allows users to draw rectangle outline with rounded corner whose two opposite corners are pt1 and pt2.
         * 
         *  \param[in]      img             Image
         *  \param[in]      pt1             Vertex of the rectangle (Top left)
         *  \param[in]      pt2             Vertex of the rectangle opposite to pt1 (bottom right)
         *  \param[in]      color           Rectangle color or brightness
         *  \param[in]      thickness       Thickness of lines that make up the rectangle
         *  \param[in]      lineType        Type of the line
         *  \param[in]      cornerRadius    Corner radius of the rectangle
         *  \return         void
         */
        static void rectangle(cv::Mat& img, cv::Point pt1, cv::Point pt2, const cv::Scalar& color, const int thickness, const int lineType, const int cornerRadius);

        /**
         *  \fn     rectangle
         *  \brief  Function that allows users to draw rounded corners (arcs) or lines of rectangle whose two opposite corners are pt1 and pt2.
         * 
         *  \param[in]      img             Image
         *  \param[in]      pt1             Vertex of the rectangle (Top left)
         *  \param[in]      pt2             Vertex of the rectangle opposite to pt1 (bottom right)
         *  \param[in]      color           Rectangle color or brightness
         *  \param[in]      thickness       Thickness of lines that make up the rectangle
         *  \param[in]      lineType        Type of the line
         *  \param[in]      cornerRadius    Corner radius of the rectangle
         *  \param[in]      status          If true enable rounded corner, if false enable lines
         *  \return         void
         */
        static void rectangle(cv::Mat& img, cv::Point pt1, cv::Point pt2, const cv::Scalar& color, const int thickness, const int lineType, const int cornerRadius, bool status);

        /**
         *  \fn     rectangle
         *  \brief  Function that allows users to draw dotted rectangle outline with rounded corner whose two opposite corners are pt1 and pt2.
         * 
         *  \param[in]      img             Image
         *  \param[in]      pt1             Vertex of the rectangle (Top left)
         *  \param[in]      pt2             Vertex of the rectangle opposite to pt1 (bottom right)
         *  \param[in]      color           Rectangle color or brightness
         *  \param[in]      thickness       Thickness of lines that make up the rectangle
         *  \param[in]      lineType        Type of the line
         *  \param[in]      cornerRadius    Corner radius of the rectangle
         *  \param[in]      gap             Point gap
         *  \return         void
         */
        static void rectangle(cv::Mat& img, cv::Point pt1, cv::Point pt2, const cv::Scalar& color, const int thickness, const int lineType, const int cornerRadius, const int gap);
        
        /**
         *  \fn     triangle
         *  \brief  Function that allows users to draw triangle from two points
         * 
         *  \param[in]      img             Image
         *  \param[in]      pt1             Vertex of the triangle (Top left)
         *  \param[in]      pt2             Vertex of the triangle opposite to pt1 (bottom right)
         *  \param[in]      color           Triangle color or brightness
         *  \param[in]      thickness       Thickness of lines that make up the triangle
         *  \param[in]      lineType        Type of the line
         */
        static void triangle(cv::Mat& img, cv::Point pt1, cv::Point pt2, const cv::Scalar& color, const int thickness, const int lineType);

        /**
         *  \fn     drawUI
         *  \brief  Function that draws a rectangle on face position and puts text on top.
		 *  Draws only a blue rectangle when label.empty(),
		 *  draws a red rectangle with the label "UNKNOWN" if confidence < 0,
		 * 	draws a blue rectangle with the label "<label> (<confidence>)" otherwise.
         *
         *  \param[in]      img             Image
         *  \param[in]      face_pos        Position of the face on img
         *  \param[in]      label           Predicted label to write
         *  \param[in]      confidence      Confidence score of the prediction
         */
        static void drawUI(cv::Mat& img, cv::Rect& face_pos, std::string label = "", double confidence = -1);
    };
    
}	// END namespace oft

#endif // ! _HANDLERDRAW_HPP_
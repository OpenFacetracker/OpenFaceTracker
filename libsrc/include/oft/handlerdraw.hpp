/////////////////////////////////////////////////////////////////////////////
// AUTHOR: Hethsron Jedaël BOUEYA
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

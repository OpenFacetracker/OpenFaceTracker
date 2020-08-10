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
    #include <oft/toolsbox.hpp>
    #include <opencv2/opencv.hpp>
#elif defined _WIN32
    #include <iostream>
    #include <oft/toolsbox.hpp>
    #include <opencv2/opencv.hpp>
	#include <oft/defs.hpp>
#endif // ! __linux__ or _WIN32

namespace oft {
    /**
     *  \class      HandlerDraw
     *  \brief
     */
    class HandlerDraw : public ToolsBox
    {
    private:
        
    public:
        /**
         *  \fn     HandlerDraw
         *  \brief  Class parameterized constructor
         * 
         *  \param[in]      _flag           Power switch (must be true)
         */
        OFT_EXPORT HandlerDraw(bool _flag);

        /**
         *  \fn     HandlerDraw
         *  \brief  Class copy constructor
         * 
         *  \param[in]      obj             HandlerDraw object
         */
        OFT_EXPORT HandlerDraw(HandlerDraw const& obj);

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
        OFT_EXPORT void line(cv::Mat& img, cv::Point pt1, cv::Point pt2, const cv::Scalar& color, const int thickness, const int gap);

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
        OFT_EXPORT void rectangle(cv::Mat& img, cv::Point pt1, cv::Point pt2, const cv::Scalar& color, const int thickness, const int lineType, const int cornerRadius);

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
        OFT_EXPORT void rectangle(cv::Mat& img, cv::Point pt1, cv::Point pt2, const cv::Scalar& color, const int thickness, const int lineType, const int cornerRadius, bool status);

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
        OFT_EXPORT void rectangle(cv::Mat& img, cv::Point pt1, cv::Point pt2, const cv::Scalar& color, const int thickness, const int lineType, const int cornerRadius, const int gap);

        /**
         *  \fn     stop
         *  \brief  Function that alows users to stop using the tool
         * 
         *  \return         void
         */
        OFT_EXPORT void stop();
        
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
        OFT_EXPORT void triangle(cv::Mat& img, cv::Point pt1, cv::Point pt2, const cv::Scalar& color, const int thickness, const int lineType);

        /**
         *  \fn     drawUI
         *  \brief  Function that draws a rectangle on face position and puts text on top
         *
         *  \param[in]      img             Image
         *  \param[in]      face_pos        Position of the face on img
         *  \param[in]      label           Predicted label to write
         *  \param[in]      confidence      Confidence score of the prediction
         */
        OFT_EXPORT void drawUI(cv::Mat& img, cv::Rect& face_pos, std::string label = "", double confidence = -1);

        /**
         *  \fn     ~HandlerDraw
         *  \brief  Class destructor
         */
        OFT_EXPORT ~HandlerDraw();
    };
    
}	// END namespace oft

#endif // ! _HANDLERDRAW_HPP_
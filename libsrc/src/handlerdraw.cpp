#include <oft/handlerdraw.hpp>

namespace oft {

	HandlerDraw::HandlerDraw() {}

    void HandlerDraw::line(cv::Mat& img, cv::Point pt1, cv::Point pt2, const cv::Scalar& color, const int thickness, const int gap) {
        
		// Get line coordinate
		double dx = pt1.x - pt2.x;
		double dy = pt1.y - pt2.y;

		// Get line distance
		double distance = sqrt(dx * dx + dy * dy);

		// Define point vectors
		std::vector<cv::Point> pts;

		for (int i = 0; i < distance; i += gap) {
			// Define new point coordinate
			double r = (double) i / distance;
			int x = int((pt1.x * (1.0 - r) + pt2.x * r) + 0.5);
			int y = int((pt1.y * (1.0 - r) + pt2.y * r) + 0.5);

			// Set new point
			cv::Point pt3 = cv::Point(x, y);

			// Load new point
			pts.push_back(pt3);
		}

		// Draw each point
		for (std::size_t i = 0; i < pts.size(); i++) {
			cv::circle(img, pts[i], thickness, color, -1);
		}
    }

    void HandlerDraw::rectangle(cv::Mat& img, cv::Point pt1, cv::Point pt2, const cv::Scalar& color, const int thickness, const int lineType, const int cornerRadius) {
        
		// Definition of corners
		cv::Point c1 = pt1;
		cv::Point c2 = cv::Point(pt2.x, pt1.y);
		cv::Point c3 = pt2;
		cv::Point c4 = cv::Point(pt1.x, pt2.y);

		// Draw straight lines
		cv::line(img, cv::Point(c1.x + cornerRadius, c1.y), cv::Point(c2.x - cornerRadius, c2.y), color, thickness, lineType);
		cv::line(img, cv::Point(c2.x, cornerRadius + c2.y), cv::Point(c3.x, c3.y - cornerRadius), color, thickness, lineType);
		cv::line(img, cv::Point(c4.x + cornerRadius, c4.y), cv::Point(c3.x - cornerRadius, c3.y), color, thickness, lineType);
		cv::line(img, cv::Point(c1.x, cornerRadius + c1.y), cv::Point(c4.x, c4.y - cornerRadius), color, thickness, lineType);

		// Draw arcs
		cv::ellipse(img, c1 + cv::Point(cornerRadius, cornerRadius), cv::Size(cornerRadius, cornerRadius), 180.0, 0, 90, color, thickness, lineType);
		cv::ellipse(img, c2 + cv::Point(-cornerRadius, cornerRadius), cv::Size(cornerRadius, cornerRadius), 270.0, 0, 90, color, thickness, lineType);
		cv::ellipse(img, c3 + cv::Point(-cornerRadius, -cornerRadius), cv::Size(cornerRadius, cornerRadius), 0.0, 0, 90, color, thickness, lineType);
		cv::ellipse(img, c4 + cv::Point(cornerRadius, -cornerRadius), cv::Size(cornerRadius, cornerRadius), 90.0, 0, 90, color, thickness, lineType);
        
    }

    void HandlerDraw::rectangle(cv::Mat& img, cv::Point pt1, cv::Point pt2, const cv::Scalar& color, const int thickness, const int lineType, const int cornerRadius, bool status) {
        
		if (status) {
			// Defintion of corners
			cv::Point c1 = cv::Point(pt1.x + 17, pt1.y + 17);
			cv::Point c2 = cv::Point(pt2.x - 17, pt1.y + 17);
			cv::Point c3 = cv::Point(pt2.x - 17, pt2.y - 17);
			cv::Point c4 = cv::Point(pt1.x + 17, pt2.y - 17);

			// Draw arcs
			cv::ellipse(img, c1 + cv::Point(cornerRadius, cornerRadius), cv::Size(cornerRadius, cornerRadius), 180.0, 0, 90, color, thickness, lineType);
			cv::ellipse(img, c2 + cv::Point(-cornerRadius, cornerRadius), cv::Size(cornerRadius, cornerRadius), 270.0, 0, 90, color, thickness, lineType);
			cv::ellipse(img, c3 + cv::Point(-cornerRadius, -cornerRadius), cv::Size(cornerRadius, cornerRadius), 0.0, 0, 90, color, thickness, lineType);
			cv::ellipse(img, c4 + cv::Point(cornerRadius, -cornerRadius), cv::Size(cornerRadius, cornerRadius), 90.0, 0, 90, color, thickness, lineType);
		}
		else {
			// Defintion of corners
			cv::Point c1 = cv::Point(pt1.x + 7, pt1.y + 7);
			cv::Point c2 = cv::Point(pt2.x - 7, pt1.y + 7);
			cv::Point c3 = cv::Point(pt2.x - 7, pt2.y - 7);
			cv::Point c4 = cv::Point(pt1.x + 7, pt2.y - 7);

			// Draw straight lines
			cv::line(img, cv::Point(c1.x + cornerRadius, c1.y), cv::Point(c2.x - cornerRadius, c2.y), color, thickness, lineType);
			cv::line(img, cv::Point(c2.x, cornerRadius + c2.y), cv::Point(c3.x, c3.y - cornerRadius), color, thickness, lineType);
			cv::line(img, cv::Point(c4.x + cornerRadius, c4.y), cv::Point(c3.x - cornerRadius, c3.y), color, thickness, lineType);
			cv::line(img, cv::Point(c1.x, cornerRadius + c1.y), cv::Point(c4.x, c4.y - cornerRadius), color, thickness, lineType);
		}
    }

    void HandlerDraw::rectangle(cv::Mat& img, cv::Point pt1, cv::Point pt2, const cv::Scalar& color, const int thickness, const int lineType, const int cornerRadius, const int gap) {
        
		// Definition of corners
		cv::Point c1 = pt1;
		cv::Point c2 = cv::Point(pt2.x, pt1.y);
		cv::Point c3 = pt2;
		cv::Point c4 = cv::Point(pt1.x, pt2.y);

		// Draw straight lines
		HandlerDraw::line(img, cv::Point(c1.x + cornerRadius, c1.y), cv::Point(c2.x - cornerRadius, c2.y), color, thickness, gap);
		HandlerDraw::line(img, cv::Point(c2.x, cornerRadius + c2.y), cv::Point(c3.x, c3.y - cornerRadius), color, thickness, gap);
		HandlerDraw::line(img, cv::Point(c4.x + cornerRadius, c4.y), cv::Point(c3.x - cornerRadius, c3.y), color, thickness, gap);
		HandlerDraw::line(img, cv::Point(c1.x, cornerRadius + c1.y), cv::Point(c4.x, c4.y - cornerRadius), color, thickness, gap);

		// Draw arcs
		cv::ellipse(img, c1 + cv::Point(cornerRadius, cornerRadius), cv::Size(cornerRadius, cornerRadius), 180.0, 0, 90, color, thickness, lineType);
		cv::ellipse(img, c2 + cv::Point(-cornerRadius, cornerRadius), cv::Size(cornerRadius, cornerRadius), 270.0, 0, 90, color, thickness, lineType);
		cv::ellipse(img, c3 + cv::Point(-cornerRadius, -cornerRadius), cv::Size(cornerRadius, cornerRadius), 0.0, 0, 90, color, thickness, lineType);
		cv::ellipse(img, c4 + cv::Point(cornerRadius, -cornerRadius), cv::Size(cornerRadius, cornerRadius), 90.0, 0, 90, color, thickness, lineType);
        
    }

    void HandlerDraw::triangle(cv::Mat& img, cv::Point pt1, cv::Point pt2, const cv::Scalar& color, const int thickness, const int lineType) {
        
		// Defintion of corners
		cv::Point c1 = cv::Point(pt1.x + 14, pt1.y + 14);
		cv::Point c2 = cv::Point(pt2.x - 14, pt1.y + 14);
		cv::Point c3 = cv::Point(pt2.x - 14, pt2.y - 14);
		cv::Point c4 = cv::Point(pt1.x + 14, pt2.y - 14);

		// Draw straight lines
		cv::line(img, cv::Point(c1.x, c1.y), cv::Point(c2.x, c2.y), color, thickness, lineType);
		cv::line(img, cv::Point(c2.x, c2.y), cv::Point((c4.x + c3.x) / 2, c3.y), color, thickness, lineType);
		cv::line(img, cv::Point(c1.x, c1.y), cv::Point((c4.x + c3.x) / 2, c4.y), color, thickness, lineType);
    }

    void HandlerDraw::drawUI(cv::Mat& img, cv::Rect& face_pos, std::string label, double confidence) {

        // Define all needed variables to draw
        int font_face = cv::FONT_HERSHEY_DUPLEX;
        double font_scale = 0.5;
        int thickness = 1;
        int baseline;

        // rectangle color (BGR)
        cv::Scalar color(255, 0, 0);

        // set Green by default, and change to Red if unknown
        if (confidence < 0.0)
            color = cv::Scalar(0, 0, 255);

        cv::rectangle(img, face_pos, color);

        if (label.empty())
            return;

        std::stringstream text;
        text << label;

        if (confidence > 0.0)
            text << " (" << std::fixed << std::setprecision(2) << confidence << ")";

        // Render UI
        cv::Size textSize = cv::getTextSize(text.str(), font_face, font_scale, thickness, &baseline);

        cv::rectangle(img, cv::Rect(face_pos.x, face_pos.y - 5 - textSize.height, face_pos.width, textSize.height + baseline), color, -1);
        cv::putText(img, text.str(), cv::Point(face_pos.x, face_pos.y - 5), font_face, font_scale, cv::Scalar(255, 255, 255));
    }
}
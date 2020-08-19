#include <oft/facialdetection.hpp>

namespace oft {

	FacialDetection::FacialDetection() {}

    const cv::Size FacialDetection::face_size = cv::Size(60, 60);

    FacialDetection::FacialDetection(const std::string& facedetect) {

        const std::string& classifier = Explorer::fullPath(facedetect);

        // Check cascade classifier
        if (!Explorer::exist(classifier)) {

            // Send a log event
            HandlerLog::log("Missing classifier files at " + classifier);

            // Terminates the process normally, performing the regular cleanup for terminating programs.
            std::exit(EXIT_FAILURE);
        }

        // Load classifier from a file
        this->haarcascade = cv::CascadeClassifier(classifier);
	}

    /*FacialDetection::FacialDetection(FacialDetection const& obj) {
		this->haarcascade = cv::CascadeClassifier(obj.haarcascade);
    }*/

    void FacialDetection::perform(cv::Mat frame, std::vector<cv::Rect>& positions, bool isEqHist) {
        cv::Mat frame_gray;
        if (frame.type() != CV_8UC1)
            cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
        else
            frame_gray = frame;

		cv::Mat hist = frame_gray;

		if(!isEqHist)	
        	cv::equalizeHist(frame_gray, hist);

        if(hist.empty())
            return;

		positions.clear();

        haarcascade.detectMultiScale(hist, positions, 1.1, 5, 0, cv::Size(80, 80));
    }

    FacialDetection::~FacialDetection() {}
}

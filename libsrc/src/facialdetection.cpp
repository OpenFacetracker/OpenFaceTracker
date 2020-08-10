#include <oft/facialdetection.hpp>

namespace oft {

    const cv::Size FacialDetection::face_size = cv::Size(60, 60);

    FacialDetection::FacialDetection(bool _fuse) : GlobalAnalysis(_fuse) {

        // Define an Explorer object
        Explorer e = Explorer();

        #ifdef __linux__
            #ifdef API
                const char file[] = "/../../../data/classifier/face/haarcascade_frontalface_alt2.xml";
            #else
                const char file[] = "/../data/classifier/face/haarcascade_frontalface_alt2.xml";
            #endif // ! API
        #elif defined _WIN32
            #ifdef API
                const char file[] = "\\..\\..\\..\\data\\classifier\\face\\haarcascade_frontalface_alt2.xml";
            #else
                const char file[] = "\\..\\data\\classifier\\face\\haarcascade_frontalface_alt2.xml";
            #endif // ! API
        #endif // ! __linux__ or _WIN32

        std::string classifier = e.gwd() + std::string(file);

        // Check file
        if (!e.exist(classifier)) {

            // Define a HandlerLog object
            HandlerLog hl = HandlerLog(true);

            // Send a log event
            hl.create("Missing classifier files at " + classifier);

            // Erase the string or making it empty
            classifier.clear();

            // Terminates the process normally, performing the regular cleanup for terminating programs.
            std::exit(EXIT_FAILURE);
        }

        this->haarcascade = cv::CascadeClassifier();

        // Load a classifier from a file
        this->haarcascade.load(classifier);
    }

    FacialDetection::FacialDetection(FacialDetection const& obj) : GlobalAnalysis(obj) {

    }

    std::vector<cv::Rect> FacialDetection::perform(cv::Mat _frame) {
        cv::Mat frame_gray;
        if (_frame.type() != CV_8UC1)
            cv::cvtColor(_frame, frame_gray, cv::COLOR_BGR2GRAY);
        else
            frame_gray = _frame;
        cv::equalizeHist(frame_gray, frame_gray);

        std::vector<cv::Rect> faces(0);

        if(frame_gray.empty()) {
            std::cout << "oopsie" << std::endl;
            return faces;
        }

        haarcascade.detectMultiScale(frame_gray, faces, 1.1, 3, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(80,80));

        return faces;
    }

    void FacialDetection::stop() {
        this->fuse = false;
    }

    FacialDetection::~FacialDetection() {}
}

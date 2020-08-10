#include <oft/labcollector.hpp>

namespace oft {

    LabCollector::LabCollector() {}

    LabCollector::~LabCollector() {}

    void LabCollector::VideoAnalysis(char streaming[], std::string label, bool confirmation) {

        // Define video capturing object
        cv::VideoCapture cap;

        // Check video file, image sequence or camera
        if (strstr(streaming, "CAM0")) {
            cap.open((int)(streaming[strlen(streaming) - 1] - '0'));
        }
        else if (strstr(streaming, "CAM1")) {
            cap.open((int)(streaming[strlen(streaming) - 1] - '0'));
        }
        else if (strstr(streaming, "CAM2")) {
            cap.open((int)(streaming[strlen(streaming) - 1] - '0'));
        }
        else {
            cap.open(streaming);
        }

        // Check if video capturing has been already initialized
        if (cap.isOpened()) {

            // Initialize Facial Detection
            FacialDetection fd(true);

            // Initialize Facial Detection
            FacialRecognition fr(true);

            // Define HandlerDraw
            HandlerDraw hd(true);

            // Initialize data vectors
            std::vector<cv::Mat> faces;

            // Define predicted label and confidence
            std::string prediction = "";
            double confidence = -1;

            // Define a frame
            cv::Mat frame;

            size_t i;

            // Define a cv::Mat to keep the mean projection and keep track of nbSamples taken
            cv::Mat averageProjection = cv::Mat();
            int nbSamples = 0;

            // Define buffers and allocate them
            cv::Mat squared = (label.empty()) ? cv::Mat() : cv::Mat(FacialDetection::face_size, CV_8UC1);
            cv::Mat buf_projection = cv::Mat();

            // Waiting from press key
            while(cv::waitKey(1) < 0) {

                // Grabs, decodes and returns the next video frame
                cap.read(frame);

                // Check if array has no elements
                if (frame.empty()) {
                    // Wait for a pressed key
                    cv::waitKey();

                    // Break the loop
                    break;
                }

                // Detect faces
                std::vector<cv::Rect> facesFrames(fd.perform(frame));   // TODO check to avoid vector clone

                faces.clear();

                for (i = 0; i < facesFrames.size(); i++) {

                    // Get corresponding matrix
                    faces.push_back(frame(facesFrames[i]));

                    if (label.empty()) {
                        // Get Prediction
                        std::tie(prediction, confidence) = fr.perform(faces.back());
                    }
                    else {
                        if (!confirmation || askConfirmation(faces.back())) {

                            // Incremental averageing
                            nbSamples++;

                            if(averageProjection.empty())
                                averageProjection = fr.project(faces.back(), squared, averageProjection);
                            else {
                                buf_projection = fr.project(faces.back(), squared, buf_projection);
                                averageProjection = averageProjection + (buf_projection - averageProjection) / float(nbSamples);
                            }
                        }
                    }

                    // Draw face position
                    hd.drawUI(frame, facesFrames[i], prediction, confidence);
                }

                // Display an image in a specific window
                cv::imshow("OpenFaceTracker", frame);
            }

            if (!label.empty())
                fr.add_Person(averageProjection, label, nbSamples);
        }
        else {
            std::cout << "Video feed could not be opened" << std::endl;
        }
    }

    void LabCollector::ImageAnalysis(char file[], std::string label, bool confirmation) {
        // Load the image
        cv::Mat frame = cv::imread(file, cv::IMREAD_COLOR);

        // Check if frame empty
        if (!frame.empty()) {

            // Initialize Facial Detection
            FacialDetection fd = FacialDetection(true);

            // Initialize Facial Detection
            FacialRecognition fr = FacialRecognition(true);

            // Define HandlerDraw
            HandlerDraw hd(true);

            cv::Mat frame_gray;
            cv::cvtColor(frame, frame_gray, cv::COLOR_RGB2GRAY);

            // Detect faces
            std::vector<cv::Rect> facesFrames(fd.perform(frame_gray));   // TODO avoid vector clone

            std::vector<cv::Mat> faces;

            for (size_t i = 0; i < facesFrames.size(); i++) {

                // Draw face position
                hd.drawUI(frame, facesFrames[i]);

                // get Corresponding matrix
                faces.push_back(frame_gray(facesFrames[i]));

                if (!label.empty() && (!confirmation || askConfirmation(faces.back()))) {
                    fr.add_Person(faces.back(), label);
                }
            }

            if (label.empty()){
                cv::imshow("frame,", frame);
                cv::waitKey();
            }
        }
    }

    bool LabCollector::askConfirmation(cv::Mat& face) {

        cv::imshow("Confirmation", face);

        int ans = cv::waitKey();
        return (ans == int('y') || ans == int('Y'));
    }

    std::vector<std::string> LabCollector::benoticed() {
        return this->notice;
    }
}

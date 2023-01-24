#include <oft/labcollector.hpp>


namespace oft {

#ifdef oft_EXPORTS
	std::string LabCollector::configFilePath = Explorer::fullPath("./config.json");
#endif

	void onMouse(int event, int x, int y, int, void* data) {
		x;y;	// Simply to remove warnings

		int* clicked = (int*)data;

		if(event == cv::EVENT_LBUTTONUP) {
			*clicked = 0;
			return;
		}

		if(event == cv::EVENT_LBUTTONDOWN/* && *clicked == 0*/) {
			*clicked = 1;
			return;
		}
	}

	LabCollector::LabCollector() {}

	void LabCollector::setConfigPath(const std::string& filepath) {
		if (!Explorer::exist(filepath)) {
			HandlerLog::log("LabCollector::setConfigPath : given config filepath does not exist (" + filepath + ")");

			std::exit(EXIT_FAILURE);
		}

		LabCollector::configFilePath = Explorer::fullPath(filepath);
	}

    void LabCollector::VideoAnalysis(char streaming[], std::string label, bool confirmation) {

        // Define video capturing object
        cv::VideoCapture cap;
		std::vector<std::string> vtr;
		int videoAPIWebcam = 0;
#ifdef __linux__
		videoAPIWebcam = cv::VideoCaptureAPIs::CAP_V4L;
#elif defined _WIN32
		videoAPIWebcam = cv::VideoCaptureAPIs::CAP_DSHOW;
#endif // ! __linux__ or _WIN32

        // Check video file, image sequence or camera
        if (strstr(streaming, "CAM0")) {
            cap.open((int)(streaming[strlen(streaming) - 1] - '0'), videoAPIWebcam );
        }
        else if (strstr(streaming, "CAM1")) {
            cap.open((int)(streaming[strlen(streaming) - 1] - '0'), videoAPIWebcam );
        }
        else if (strstr(streaming, "CAM2")) {
            cap.open((int)(streaming[strlen(streaming) - 1] - '0'), videoAPIWebcam );
        }
        else {
			cap.open(streaming, cv::VideoCaptureAPIs::CAP_FFMPEG );
        }

        // Check if video capturing has been already initialized
        if (cap.isOpened()) {
			
			// Open config file
			HandlerJson hjson(configFilePath);
			/* .get<std::string>() */

            // Initialize HandlerLog
			HandlerLog::setLogPath(hjson["logpath"]);

			// Initialize Backend
			Backend::setDBPath(hjson["dbpath"]);

            // Initialize Facial Detection
            FacialDetection fd(hjson["haarpath"]);

            // Initialize Facial Recognition
            FacialRecognition fr(hjson["pcapath"], hjson["facemarkpath"]);

            // Initialize data vectors
            cv::Mat face;

			// Initialize faces positions
			std::vector<cv::Rect> pos_faces;

            // Define predicted label and confidence
            std::string prediction = "";
            double confidence = -1;

            // Define a frame
            cv::Mat frame;
			cv::Mat frame_gray;

            size_t i;

            // Define a cv::Mat to keep the mean projection and keep track of nbSamples taken
            cv::Mat averageProjection = cv::Mat();
            int nbSamples = 0;

            // Define buffers and allocate them
            cv::Mat squared = (label.empty()) ? cv::Mat() : cv::Mat(FacialDetection::face_size, CV_8UC1);
            cv::Mat buf_projection = cv::Mat();

			std::string winName("VideoAnalysis");
			cv::namedWindow(winName);

			int clicked = 0;

			if (!label.empty())
				cv::setMouseCallback(winName, onMouse, &clicked);

            // Waiting from press key
            while(cv::waitKey(1) < 0) {

                // Grabs, decodes and returns the next video frame
                cap.read(frame);

                // Check if array has no elements
                if (frame.empty()) {
                    // Wait for a pressed key
                    //cv::waitKey();
                    // Break the loop
                    break;
                }

            	cv::cvtColor(frame, frame_gray, cv::COLOR_RGB2GRAY);

				// We equalize frame histogram to avoid later operations (cv::equalizeHist() call and allocation cost)
				cv::equalizeHist(frame_gray, frame_gray);

                // Detect faces
				fd.perform(frame_gray, pos_faces, true);

				std::vector<std::tuple<std::string, double>> predictions;

				if (label.empty()) {
					// Perform Facial Recognition
					predictions = fr.perform(frame_gray, pos_faces, true);
				}

                for (i = 0; i < pos_faces.size(); i++) {

                    if (label.empty()) {
						// Retrieve this face's result
						std::tie(prediction, confidence) = predictions[i];
						bool tmp = true;
						for(int j = 0; j< vtr.size() ; j++){
							if(prediction == vtr[j]){
								tmp = false;
								break;
							}
						}
						if(tmp)
							vtr.push_back(prediction);					
                    }
					else {
                        if (!confirmation || clicked == 1) {

							//clicked = -1;

                            // Incremental averageing
                            nbSamples++;

                            if(averageProjection.empty()) {
                                averageProjection = fr.project(frame_gray, pos_faces[i], squared, averageProjection);
							}
                            else {
                                buf_projection = fr.project(frame_gray, pos_faces[i], squared, buf_projection);
                                averageProjection = averageProjection + (buf_projection - averageProjection) / float(nbSamples);
                            }
                        }
                    }

					// Draw face position
					HandlerDraw::drawUI(frame, pos_faces[i], prediction, confidence);
                }
				
				if(!label.empty()) {
					// Display nbSamples in the bottom-left corner
					cv::putText(frame, std::to_string(nbSamples), cv::Point(0, frame.rows-1), cv::FONT_HERSHEY_DUPLEX, 1.0, cv::Scalar(255, 0, 0), 2, cv::LineTypes::FILLED);
				}

				// Display an image in a specific window
				cv::imshow(winName, frame);
            }

            if (nbSamples > 0)
                fr.add_Person(averageProjection, label, nbSamples);
				
        }
        else {
			HandlerLog::log("Video feed could not be opened " + std::string(streaming));
            std::cout << "Video feed could not be opened" << std::endl;
        }		

		// Release Video Capture
		cap.release();

		for(int i=0; i < vtr.size(); i++)
			std::cout << vtr[i] << "\n";
		// Close all OpenCV windows
		cv::destroyAllWindows();
    }

    void LabCollector::ImageAnalysis(char file[], std::string label, bool confirmation) {
        // Load the image
        cv::Mat frame = cv::imread(file, cv::IMREAD_COLOR);
        // Check if frame empty
        if (!frame.empty()) {

			// Open config file
			HandlerJson hjson(configFilePath);
			/* .get<std::string>() */

            // Initialize HandlerLog
			HandlerLog::setLogPath(hjson["logpath"]);

			// Initialize Backend
			Backend::setDBPath(hjson["dbpath"]);

            // Initialize Facial Detection
            FacialDetection fd(hjson["haarpath"]);

            // Initialize Facial Recognition
            FacialRecognition fr(hjson["pcapath"], hjson["facemarkpath"]);

            cv::Mat frame_gray;
            cv::cvtColor(frame, frame_gray, cv::COLOR_RGB2GRAY);

            // Detect faces
            std::vector<cv::Rect> pos_faces;
			fd.perform(frame_gray, pos_faces);

			std::vector<std::tuple<std::string, double>> predictions;

			if (label.empty()) {
				// Perform Facial Recognition
				predictions = fr.perform(frame_gray, pos_faces);
			}

            for (size_t i = 0; i < pos_faces.size(); i++) {

                if (!label.empty()) {

                    // Draw face position
					HandlerDraw::drawUI(frame, pos_faces[i]);

					cv::imshow("ImageAnalysis", frame);

					if(!confirmation || askConfirmation()) {

						try
						{
							// Add person to db
							fr.add_Person(fr.project(frame_gray, pos_faces[i]), label);
						}
						catch(const std::exception& e)
						{
							std::cerr << e.what() << '\n';
						}
					}
                }
				else {
					// Define predicted label and confidence
					std::string prediction = "";
					double confidence = -1;

					// Retrieve this face's result
					std::tie(prediction, confidence) = predictions[i];

					if(confidence < 0.0)
						std::cout << i << "/" << pos_faces.size() << " : UNKNOWN" << std::endl;
					else
						std::cout << i+1 << "/" << pos_faces.size() << " : " << prediction << " (" << std::fixed << std::setprecision(2) << confidence << ")" << std::endl;

					// Draw UI over this detected face
					HandlerDraw::drawUI(frame, pos_faces[i], prediction, confidence);
				}
            }

            if (label.empty()){
                cv::imshow("frame,", frame);
                //cv::waitKey();
            }
        }
		else{
			std::cout << "Frame empty" << std::endl;
		}
    }

    bool LabCollector::askConfirmation() {
        int ans = cv::waitKey();
        return (ans == int('y') || ans == int('Y'));
    }
}

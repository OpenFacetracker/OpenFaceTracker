#include <oft/facialrecognition.hpp>

namespace oft {

/*	Will be used in the next update

	const cv::Point2f FacialRecognition::boundaries[8] = {
		cv::Point2f(0.0f, 										0.0f),													//*< Top Left
		cv::Point2f(FacialDetection::face_size.width / 2.0f, 	0.0f),													//*< Top Mid											
		cv::Point2f(float(FacialDetection::face_size.width), 	0.0f),													//*< Top Right
		cv::Point2f(0.0f, 										FacialDetection::face_size.height / 2.0f),				//*< Mid Left
		cv::Point2f(float(FacialDetection::face_size.width), 	FacialDetection::face_size.height / 2.0f),				//*< Mid Right
		cv::Point2f(0.0f, 										float(FacialDetection::face_size.height)),				//*< Bottom Left
		cv::Point2f(FacialDetection::face_size.width / 2.0f, 	float(FacialDetection::face_size.height)),				//*< Bottom Mid
		cv::Point2f(float(FacialDetection::face_size.width), 	float(FacialDetection::face_size.height))				//*< Bottom Right
	};

	const int FacialRecognition::delaunayTriangulation[142][3] = {
		{ 68, 71, 0 },
		{ 68, 0, 17 },
		{ 68, 17, 18 },
		{ 68, 18, 19 },
		{ 68, 19, 69 },
		{ 69, 19, 20 },
		{ 69, 20, 21 },
		{ 69, 21, 22 },
		{ 69, 22, 23 },
		{ 69, 23, 24 },
		{ 69, 24, 70 },
		{ 70, 24, 25 },
		{ 70, 25, 26 },
		{ 70, 26, 16 },
		{ 70, 16, 72 },
		{ 72, 16, 15 },
		{ 72, 15, 14 },
		{ 72, 14, 13 },
		{ 72, 13, 75 },
		{ 75, 13, 12 },
		{ 75, 12, 11 },
		{ 75, 11, 10 },
		{ 75, 10, 74 },
		{ 74, 10, 9 },
		{ 74, 9, 8 },
		{ 74, 8, 7 },
		{ 74, 7, 73 },
		{ 73, 7, 6 },
		{ 73, 6, 5 },
		{ 73, 5, 4 },
		{ 73, 4, 71 },
		{ 71, 4, 3 },
		{ 71, 3, 2 },
		{ 71, 2, 1 },
		{ 71, 1, 0 },
		{ 0, 1, 36 },
		{ 0, 17, 36 },
		{ 17, 18, 36 },
		{ 18, 36, 37 },
		{ 18, 19, 37 },
		{ 19, 20, 37 },
		{ 20, 37, 38 },
		{ 20, 21, 38 },
		{ 21, 38, 39 },
		{ 21, 39, 27 },
		{ 21, 22, 27 },
		{ 22, 27, 42 },
		{ 22, 42, 43 },
		{ 22, 23, 43 },
		{ 23, 24, 43 },
		{ 24, 43, 44 },
		{ 24, 25, 44 },
		{ 44, 25, 45 },
		{ 25, 26, 45 },
		{ 26, 45, 15 },
		{ 26, 16, 15 },
		{ 45, 15, 14 },
		{ 45, 46, 14 },
		{ 45, 44, 46 },
		{ 44, 47, 46 },
		{ 43, 44, 47 },
		{ 42, 43, 47 },
		{ 27, 42, 28 },
		{ 27, 39, 28 },
		{ 39, 38, 40 },
		{ 38, 40, 37 },
		{ 37, 40, 41 },
		{ 37, 36, 41 },
		{ 1, 36, 41 },
		{ 1, 41, 31 },
		{ 40, 41, 31 },
		{ 40, 31, 29 },
		{ 40, 39, 29 },
		{ 39, 28, 29 },
		{ 42, 28, 29 },
		{ 42, 29, 35 },
		{ 42, 47, 35 },
		{ 46, 47, 35 },
		{ 46, 35, 14 },
		{ 35, 14, 54 },
		{ 14, 13, 54 },
		{ 13, 12, 54 },
		{ 11, 12, 54 },
		{ 54, 11, 55 },
		{ 10, 11, 55 },
		{ 55, 56, 10 },
		{ 56, 10, 9 },
		{ 56, 9, 8 },
		{ 8, 56, 57 },
		{ 57, 8, 7 },
		{ 57, 7, 58 },
		{ 7, 58, 6 },
		{ 58, 59, 6 },
		{ 5, 6, 59 },
		{ 59, 48, 5 },
		{ 4, 5, 48 },
		{ 3, 4, 48 },
		{ 2, 3, 48 },
		{ 2, 31, 48 },
		{ 1, 2, 31 },
		{ 31, 48, 49 },
		{ 31, 49, 32 },
		{ 31, 32, 30 },
		{ 31, 30, 29 },
		{ 29, 30, 35 },
		{ 30, 32, 33 },
		{ 30, 33, 34 },
		{ 30, 34, 35 },
		{ 35, 54, 53 },
		{ 35, 53, 52 },
		{ 35, 34, 52 },
		{ 34, 33, 52 },
		{ 33, 51, 52 },
		{ 33, 51, 50 },
		{ 33, 32, 50 },
		{ 32, 49, 50 },
		{ 48, 60, 49 },
		{ 48, 60, 59 },
		{ 60, 49, 59 },
		{ 49, 59, 61 },
		{ 49, 50, 61 },
		{ 50, 61, 51 },
		{ 61, 51, 62 },
		{ 51, 62, 63 },
		{ 51, 52, 63 },
		{ 52, 63, 53 },
		{ 53, 64, 54 },
		{ 64, 54, 55 },
		{ 53, 64, 55 },
		{ 53, 55, 63 },
		{ 55, 63, 65 },
		{ 63, 65, 62 },
		{ 62, 66, 65 },
		{ 62, 66, 67 },
		{ 61, 62, 67 },
		{ 61, 67, 59 },
		{ 59, 67, 58 },
		{ 67, 66, 58 },
		{ 58, 57, 66 },
		{ 66, 57, 56 },
		{ 66, 65, 56 },
		{ 65, 56, 55 }
	}; */

	FacialRecognition::FacialRecognition()
	 : generic_pca(), gallery_data(std::make_tuple(std::vector<long long>(), std::vector<std::string>(), std::vector<cv::Mat>(), std::vector<int>())) {}

	FacialRecognition::FacialRecognition(const std::string& pca_file, const std::string& facemark)
	 : generic_pca(), gallery_data(std::make_tuple(std::vector<long long>(), std::vector<std::string>(), std::vector<cv::Mat>(), std::vector<int>())) {

		// Generic PCA file path
		std::string pca_gen_path = Explorer::fullPath(pca_file);

		// Check PCA file
		if (!Explorer::exist(pca_gen_path)) {
			
			// Send a log event
            HandlerLog::log("Missing PCA files at " + pca_gen_path);

            // Erase the string or making it empty
            pca_gen_path.clear();

			std::exit(EXIT_FAILURE);
		}
		else {
			// Retrieve Generic PCA from file
			try {
				cv::FileStorage fs(pca_gen_path, cv::FileStorage::READ);
				generic_pca.read(fs.root());
				fs.release();
			}
			catch (cv::Exception& e) {
				const char* err_msg = e.what();

				// Send a log event
            	HandlerLog::log("Exception caught: " + std::string(err_msg));

				std::cerr << "exception caught: " << err_msg << std::endl;
			}
		}

		std::string facemark_path = Explorer::fullPath(facemark);

		// Check facemark model
        if (!Explorer::exist(facemark_path)) {

            // Send a log event
            HandlerLog::log("Missing facemark files at " + facemark_path);

            // Erase the string or making it empty
            facemark_path.clear();

            // Terminates the process normally, performing the regular cleanup for terminating programs.
            std::exit(EXIT_FAILURE);
        }

		// Load FaceMarkLBF Model
		cv::face::FacemarkLBF::Params params;
		params.verbose = false;
		this->facemarker = cv::face::FacemarkLBF::create(params);
		this->facemarker->loadModel(facemark_path);

		// Compute average landmark from generic_pca.mean
		cv::Mat mean = generic_pca.mean.reshape(1, FacialDetection::face_size.height);

		mean_landmarks.clear();
		std::vector<cv::Rect> face_position({cv::Rect(0, 0, FacialDetection::face_size.width, FacialDetection::face_size.height)});

		// Compute mean landmarks
		std::vector<std::vector<cv::Point2f>> all_landmarks;
		if(!facemarker->fit(mean, face_position, all_landmarks)) {
			// Send a log event
            HandlerLog::log("Failure in Facemarking PCA mean");

            // Terminates the process normally, performing the regular cleanup for terminating programs.
            std::exit(EXIT_FAILURE);
		}

		mean_landmarks = all_landmarks[0];
		all_landmarks.clear();

		// Append boundaries points
		//mean_landmarks.insert(std::end(mean_landmarks), std::begin(boundaries), std::end(boundaries));

		// Get database and prepare data
		this->updateGallery();
	}

	cv::Mat FacialRecognition::getSquareImage(const cv::Mat& img, int target_width) {
		int width = img.cols,
			height = img.rows;

		cv::Mat square = cv::Mat::zeros(target_width, target_width, img.type());

		int max_dim = (width >= height) ? width : height;
		float scale = float(target_width) / float(max_dim);
		cv::Rect roi;
		if (width >= height)
		{
			roi.width = target_width;
			roi.x = 0;
			roi.height = std::min(int(std::ceil(height * scale)), target_width);
			roi.y = (target_width - roi.height) / 2;
		}
		else
		{
			roi.y = 0;
			roi.height = target_width;
			roi.width = std::min(int(std::ceil(width * scale)), target_width);
			roi.x = (target_width - roi.width) / 2;
		}

		cv::resize(img, square(roi), roi.size());

		return square;
	}

	void FacialRecognition::updateGallery() {
		
		std::get<0>(gallery_data).clear();
		std::get<1>(gallery_data).clear();
		std::get<2>(gallery_data).clear();
		std::get<3>(gallery_data).clear();

		if (Backend::getAll()) {

			std::tuple<long long, std::string, int, std::stringstream> row = std::make_tuple<long long, std::string, int, std::stringstream>(-1, "", -1, std::stringstream());

			while (Backend::getNext(row)) {
				
				// Row ID
				std::get<0>(gallery_data).push_back(std::get<0>(row));

				// Label
				std::get<1>(gallery_data).push_back(std::get<1>(row));

				// Projection (convertion std::istream -> cv::Mat)
				std::vector<float> data;
				std::stringstream& ss = std::get<3>(row);

				float value;
				while (ss.peek() != EOF) {
					ss >> value;
					data.push_back(value);
				}
				std::get<2>(gallery_data).push_back(cv::Mat(data, true).reshape(0, 1));

				// NB_samples
				std::get<3>(gallery_data).push_back(std::get<2>(row));
			}
		}
	}

	std::vector<std::tuple<std::string, double>> FacialRecognition::perform(cv::Mat frame, const std::vector<cv::Rect>& facePositions, bool isEqHist, cv::Mat projections) {

		// We prepare the image to be a 60*60 grayscale vector

		cv::Mat gray_frame;
		if (!isEqHist && frame.type() != CV_8UC1)
            cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);
        else
            gray_frame = frame;

		size_t nb_faces = facePositions.size();
		
		bool keep_projections = false;
		
		// Check if projections has enough space to fit all projections
		if (projections.rows >= nb_faces && projections.cols >= generic_pca.mean.cols && projections.type() == generic_pca.mean.type())
			keep_projections = true;

		// Face alignment
		std::vector<std::vector<cv::Point2f>> face_landmarks;
		std::vector<std::tuple<std::string, double>> result;

		// Detect landmarks for each detected face
		if (facemarker->fit(gray_frame, facePositions, face_landmarks)) {

			// Eyes and chin landmarks (mean)
			const cv::Point2f pointsDst[3] = {
				mean_landmarks[36],
				mean_landmarks[45],
				mean_landmarks[8]
			};

			cv::Point2f pointsSrc[3] = {
				cv::Point2f(0.0f, 0.0f),
				cv::Point2f(0.0f, 0.0f),
				cv::Point2f(0.0f, 0.0f)
			};

			cv::Mat warped = cv::Mat(FacialDetection::face_size.height, FacialDetection::face_size.width, CV_8UC1);
			cv::Mat affine_tr;
			cv::Mat targetProjection = cv::Mat(generic_pca.mean.rows, generic_pca.mean.cols, CV_32F);

			cv::Mat hist;

			if (!isEqHist)
				cv::equalizeHist(gray_frame, hist);

			size_t i;

			for (i = 0; i < nb_faces; i++) {

				alignFace(gray_frame, warped, face_landmarks[i]);

				// Project onto generic_pca subspace
				generic_pca.project(warped.reshape(0, 1), targetProjection);

				if(keep_projections) {
					targetProjection.row(int(i)).copyTo(projections.row(int(i)));
				}

				size_t j;
				size_t size_gallery = std::get<0>(gallery_data).size();

				double distance = 0.0;
				double minDist = -1;
				size_t indexBestMatch = 0;

				// TODO : Check if parallelization possible here

				for (j = 0; j < size_gallery; j++) {

					// For each pair <target, gallery[j]>, we compute the confidence score (= distance between faces)

					// compute euclidian distance between projected vectors
					// distance is the similarity bewteen faces of target and galery[j]
					distance = cv::norm(targetProjection, std::get<2>(gallery_data)[j], cv::NORM_L2);

					if (minDist < 0 || distance < minDist) {
						minDist = distance;
						indexBestMatch = j;
					}
				}

				if (minDist > this->threshold || minDist < 0.0){
					result.push_back(std::make_tuple(std::string("UNKNOWN"), -1.0));
				}			
				else{
					result.push_back(std::make_tuple(std::get<1>(gallery_data)[indexBestMatch], minDist));
				}
			}
		}

		return result;
	}

	cv::Mat FacialRecognition::project(cv::Mat frame, cv::Rect position, cv::Mat squared, cv::Mat dst, bool isEqHist) {

		cv::Mat gray_frame;
		if (frame.type() != CV_8UC1)
            cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);
        else
            gray_frame = frame;

		try {

			if (squared.empty() || squared.total() < FacialDetection::face_size.area())
				squared = cv::Mat(FacialDetection::face_size, gray_frame.type());

			alignFace(gray_frame, squared, position);

			if (dst.empty() || dst.total() < generic_pca.mean.total())
				dst = cv::Mat(generic_pca.mean.rows, generic_pca.mean.cols, generic_pca.mean.type());
			
			if (!isEqHist)
				cv::equalizeHist(squared, squared);

			generic_pca.project(squared.reshape(0, 1), dst);
		}
		catch(const std::exception& e) {
			std::cerr << e.what() << '\n';
		}

		return dst;
	}

	void FacialRecognition::alignFace(cv::Mat frame, cv::Mat dst, std::vector<cv::Point2f> landmarks) {

		if (landmarks.empty() || landmarks.size() < 68)
			throw std::exception("Assertion failed : (!landmarks.empty() && landmarks.size() >= 68)");

		// Eyes and chin landmarks (mean)
		const cv::Point2f pointsDst[3] = {
			mean_landmarks[36],
			mean_landmarks[45],
			mean_landmarks[8]
		};

		const cv::Point2f pointsSrc[3] = {
			landmarks[36],
			landmarks[45],
			landmarks[8]
		};

		// Compute affine transformation from target to mean
		cv::Mat affine_tr = cv::getAffineTransform(pointsSrc, pointsDst);

		// Then apply transformation to center and align face
		cv::warpAffine(frame, dst, affine_tr, FacialDetection::face_size);
	}

	void FacialRecognition::alignFace(cv::Mat frame, cv::Mat dst, cv::Rect face_position) {

		int rect[4] = {face_position.x, face_position.y, face_position.width, face_position.height};
		cv::Mat pos = cv::Mat(cv::Size(1, 1), CV_32SC4, rect);

		std::vector<std::vector<cv::Point2f>> landmarks;

		if(!facemarker->fit(frame, pos, landmarks))
			throw std::exception("Error : Face marking failed");

		// Eyes and chin landmarks (mean)
		const cv::Point2f pointsDst[3] = {
			mean_landmarks[36],
			mean_landmarks[45],
			mean_landmarks[8]
		};

		// Eyes and chin landmarks (target)
		const cv::Point2f pointsSrc[3] = {
			landmarks[0][36],
			landmarks[0][45],
			landmarks[0][8]		
		};
		
		// Compute affine transformation from target to mean
		cv::Mat affine_tr = cv::getAffineTransform(pointsSrc, pointsDst);

		// Then apply transformation to center and align face
		cv::warpAffine(frame, dst, affine_tr, FacialDetection::face_size);
	}

	void FacialRecognition::add_Person(cv::Mat projection, std::string label, int nb_Samples) {
		
		// Check if label is already used
		std::vector<std::string>::iterator it;
		std::vector<std::string>& labels = std::get<1>(gallery_data);

		bool alreadyExist = false;

		if ((it = std::find(labels.begin(), labels.end(), label)) != labels.end()) {

			alreadyExist = true;

			size_t index = it - labels.begin();

			cv::Mat& old = std::get<2>(gallery_data)[index];

			int oldNbSamples = std::get<3>(gallery_data)[index];
			int N = oldNbSamples + nb_Samples;

			// compute average between old and new projections with respect to nb_samples of each (= weight)
			// combined mean = (nbSamples_A * mean_A + nbSamples_B * mean_B) / (nbSamples_A + nbSamples_B)
			
			std::get<2>(gallery_data)[index] = (float(oldNbSamples) * old + float(nb_Samples) * projection) / float(N);
			projection = std::get<2>(gallery_data)[index];

			nb_Samples = N;
		}
		

		// serialize cv::Mat to std::stringstream
		std::stringstream ss;

		int channels = projection.channels();

		int nRows = projection.rows;
		int nCols = projection.cols * channels;

		if (projection.isContinuous())
		{
			nCols *= nRows;
			nRows = 1;
		}

		int i, j;
		float* p;
		std::string separator = "";
		for (i = 0; i < nRows; ++i) {
			p = projection.ptr<float>(i);
			for (j = 0; j < nCols; ++j) {
				ss << separator << p[j];
				separator = " ";
			}
		}
		if (!alreadyExist) {
			if (Backend::insert(label, ss, nb_Samples) >= 0)
				std::cout << label << " successfully added to Database" << std::endl;
			else
				std::cout << "Error when adding sample to Database" << std::endl;
		}
		else {
			if (Backend::update(label, ss, nb_Samples))
				std::cout << label << " successfully updated" << std::endl;
			else
				std::cout << "Error when updating sample to Database" << std::endl;
		}
	}

	FacialRecognition::~FacialRecognition() {
		std::get<0>(gallery_data).clear();
		std::get<1>(gallery_data).clear();
		std::get<2>(gallery_data).clear();
		std::get<3>(gallery_data).clear();

		this->facemarker.reset();
	}
}
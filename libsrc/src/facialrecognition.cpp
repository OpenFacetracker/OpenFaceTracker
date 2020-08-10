#include <oft/facialrecognition.hpp>

namespace oft {

	/**
		 *  \fn     FacialRecognition
		 *  \brief  Class parameterized constructor
		 *
		 *  \param[in]      _fuse           Fuse (must be true)
		 */
	FacialRecognition::FacialRecognition(bool _fuse)
		: GlobalAnalysis(_fuse), generic_pca() {

		// Define an Explorer object
		Explorer e = Explorer();
		
		#ifdef __linux__
			#ifdef API
				const char pca_file[] = "/../../../data/classifier/face/pca_gen.xml";
			#else
				const char pca_file[] = "/../data/classifier/face/pca_gen.xml";
			#endif // ! API
		#elif defined _WIN32
			#ifdef API
				const char pca_file[] = "\\..\\..\\..\\data\\classifier\\face\\pca_gen.xml";
			#else
				const char pca_file[] = "\\..\\data\\classifier\\face\\pca_gen.xml";
			#endif // ! API
		#endif // ! __linux__ or _WIN32

		// Generic PCA file path
		std::string pca_gen_path = e.gwd() + std::string(pca_file);

		// Check PCA file
		if (!e.exist(pca_gen_path)) {
			
			// if it does not exist, then log and quit
			exit(EXIT_FAILURE);
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
				std::cerr << "exception caught: " << err_msg << std::endl;
			}
		}

		// Get database and prepare data
		this->updateGallery();
	}

	FacialRecognition::FacialRecognition(FacialRecognition const& obj) : GlobalAnalysis(obj) {

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

		Backend b(true);

		if (b.getAll()) {

			std::tuple<long long, std::string, int, std::stringstream> row;

			while (b.getNext(row)) {
				
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

	std::tuple<std::string, double> FacialRecognition::perform(cv::Mat _face) {

		// We prepare the image to be a 60*60 grayscale vector

		cv::Mat gray;
		cv::cvtColor(_face, gray, cv::COLOR_BGR2GRAY);
		cv::Mat gray_scaled = getSquareImage(gray).reshape(0, 1);

		// Project target onto the generic PCA subspace
		cv::Mat targetProjection = generic_pca.project(gray_scaled);

		size_t i;
		size_t size_gallery = std::get<0>(gallery_data).size();

		double distance = 0.0;
		double minDist = -1;
		size_t indexBestMatch = 0;

		for (i = 0; i < size_gallery; i++) {

			// For each pair <target, gallery[i]>, we compute the confidence score (= distance between faces)

			// compute euclidian distance between projected vectors
			// distance is the similarity bewteen faces of target and galery[i]
			distance = cv::norm(targetProjection, std::get<2>(gallery_data)[i], cv::NORM_L2);

			if (minDist < 0 || distance < minDist) {
				minDist = distance;
				indexBestMatch = i;
			}
		}

		if (minDist > this->threshold || minDist < 0.0)
			return std::make_tuple("UNKOWN", -1.0);
		return std::make_tuple(std::get<1>(gallery_data)[indexBestMatch], minDist);
	}

	cv::Mat FacialRecognition::project(cv::Mat& face, cv::Mat squared, cv::Mat dst) {
		cv::resize(face, squared, FacialDetection::face_size);

		if (dst.empty())
			dst = cv::Mat(generic_pca.mean.rows, generic_pca.mean.cols, generic_pca.mean.type());

		generic_pca.project(squared.reshape(0, 1), dst);
		return dst;
	}

	void FacialRecognition::add_Person(cv::Mat& face, std::string label, int nb_Samples) {

		cv::Mat projection = project(face);

		Backend b(true);
		
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
			if (b.insert(label, ss, nb_Samples) >= 0)
				std::cout << label << " successfully added to Database" << std::endl;
			else
				std::cout << "Error when adding sample to Database" << std::endl;
		}
		else {
			if (b.update(label, ss, nb_Samples))
				std::cout << label << " successfully updated" << std::endl;
			else
				std::cout << "Error when updating sample to Database" << std::endl;
		}
	}

	void FacialRecognition::stop() {
		this->fuse = false;
	}

	FacialRecognition::~FacialRecognition() {
		std::get<0>(gallery_data).clear();
		std::get<1>(gallery_data).clear();
		std::get<2>(gallery_data).clear();
		std::get<3>(gallery_data).clear();
	}
}
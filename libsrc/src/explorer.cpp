#include <oft/explorer.hpp>

namespace oft {



    size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) {
        size_t written = fwrite(ptr, size, nmemb, stream);
        return written;
    }

	Explorer::Explorer() {}

	std::string Explorer::fullPath(const std::string& old_path) {
		return boost::filesystem::absolute(boost::filesystem::path(old_path)).string();
	}

    std::string Explorer::gwd() {
        return boost::filesystem::current_path().string();
    }

	bool Explorer::create_directories(const std::string& path) {
		boost::filesystem::path filepath(path);

		if(!boost::filesystem::is_directory(filepath)) {
			filepath = filepath.parent_path();
		}

		return boost::filesystem::create_directories(filepath);
	}

    bool Explorer::makdir(const std::string& dirpath) {
		return boost::filesystem::create_directories(boost::filesystem::path(dirpath));
    }

    bool Explorer::remdir(const std::string& dirpath) {
        return boost::filesystem::remove_all(boost::filesystem::path(dirpath));
    }

    bool Explorer::delfs(const std::string& path) {
        return boost::filesystem::remove_all(boost::filesystem::path(path));
    }

    bool Explorer::empty(const std::string& distn) {
		return boost::filesystem::is_empty(boost::filesystem::path(distn));
    }

    bool Explorer::forensic(const std::string& distn) {
        bool status = false;
		// TODO RETURN ENUM
        // Verifying extension
        std::size_t pos = distn.rfind(".");
        if (pos == std::string::npos) {
            // If there is no extension

            // Getting magic number
            std::ifstream file(distn.c_str(), std::ios::binary);
            if (file) {
                // If file is opened
                file.seekg(0, std::ios::beg);
                unsigned char magic[8] = {0};
                file.read((char*)magic, sizeof(magic));

                if (magic[0] == 0xFF && magic[1] == 0xD8 && magic[2] == 0xFF) {
                    // It is a JPEG or JPG file
                    status = true;
                }
                else if ((magic[0] == 0x52 && magic[1] == 0x49 && magic[2] == 0x46 && magic[3] == 0x46) || (magic[0] == 0x41 && magic[1] == 0x56 && magic[2] == 0x49 && magic[3] == 0x20)) {
                    // It is a AVI file
                    status = true;
                }
                else if (magic[0] == 0x00 && magic[1] == 0x00 && magic[2] == 0x00 && magic[3] == 0x018 && magic[4] == 0x66 && magic[5] == 0x74 && magic[6] == 0x79 && magic[7] == 0x70) {
                    // It is a MPEG-4 file
                    status = true;
                }
                else if (magic[0] == 0x1A && magic[1] == 0x45 && magic[2] == 0xDF && magic[3] == 0xA3) {
                    // It is a MATROSKA file
                    status = true;
                }
                else {
                    // If it is an unauthorized file
                    status = false;
                }
                file.close();
            }
            else {
                // If file cannot be opened
                status = false;
            }
        }
        else {
            // If there is an extension

            // Getting extension
            std::string extension = distn.substr(pos + 1);

            // Verifying extension
            if (extension == "jpg" || extension == "jpeg" || extension == "avi" || extension == "mp4" || extension == "mkv" || extension == "MKV") {
                // If the extensions match

                // Getting magic number
                std::ifstream file(distn.c_str(), std::ios::binary);
                if (file) {
                    // If file is opened
                    file.seekg(0, std::ios::beg);
                    unsigned char magic[8] = {0};
                    file.read((char*)magic, sizeof(magic));

                    if (magic[0] == 0xFF && magic[1] == 0xD8 && magic[2] == 0xFF) {
                        // It is a JPEG or JPG file
                        status = true;
                    }
                    else if ((magic[0] == 0x52 && magic[1] == 0x49 && magic[2] == 0x46 && magic[3] == 0x46) || (magic[0] == 0x41 && magic[1] == 0x56 && magic[2] == 0x49 && magic[3] == 0x20)) {
                        // It is a AVI file
                        status = true;
                    }
                    else if (magic[0] == 0x00 && magic[1] == 0x00 && magic[2] == 0x00 && magic[3] == 0x018 && magic[4] == 0x66 && magic[5] == 0x74 && magic[6] == 0x79 && magic[7] == 0x70) {
                        // It is a MPEG-4 file
                        status = true;
                    }
                    else if (magic[0] == 0x1A && magic[1] == 0x45 && magic[2] == 0xDF && magic[3] == 0xA3) {
                        // It is a MATROSKA file
                        status = true;
                    }
                    else {
                        // If it is an unauthorized file
                        status = false;
                    }
                    file.close();
                }
                else {
                    // If file cannot be opened
                    status = false;
                }
            }
            else {
                // If the extensions don't match
                status = false;
            }
        }
        return status;
    }

    bool Explorer::exist(const std::string& distn) {
        return boost::filesystem::exists(boost::filesystem::path(distn));
    }

    bool Explorer::rename(const std::string& oldf, const std::string& newf) {

        boost::filesystem::path old_p(oldf);
        boost::filesystem::path new_p(newf);

        boost::system::error_code err;

        boost::filesystem::rename(old_p, new_p, err);

        return err.value() == boost::system::errc::success;
    }

	std::string Explorer::download(const std::string& url, const std::string& path, bool verbose) {

		// Check if url is indeed and URL

		// URL regex
		std::regex urlregex("^http[s]?:\\/\\/.*$");
        
        if(!std::regex_match(url, urlregex)) {
			// url is not an URL, we assume it is a filepath
			return url;
		}
		
		// Ensure path exists
		Explorer::create_directories(path);

		// Check if url is a youtube url (https://gist.github.com/rodrigoborgesdeoliveira/987683cfbfcc8d800192da1e73adc486)
		const std::regex ytregex("(\\/|%3D|v=)([0-9A-z-_]{11})([%#?&]|$)");
		std::smatch match;

		if(std::regex_search(url, match, ytregex)) {
			// a youtube token has been found in url, the url should be from youtube

			std::string filepath = path + "/" + match.str(2) + ".mp4";

			// if filepath already exists, then skip downloading step
			if(Explorer::exist(filepath)) {
				if (verbose) std::cout << "Video already downloaded in cache (" << filepath << ")" << std::endl;
				return filepath;
			}

			std::string cmd = "cd ../tmp && youtube-dl -q --hls-prefer-ffmpeg --id \"" + url + "\"";

			if (verbose) std::cout << "Downloading video" << std::endl;
			system(cmd.c_str());
			if (verbose) std::cout << "Downloading video - done" << std::endl;

			return filepath;
		}

        std::string oldpath = path + "/cache";
        std::string filepath;

		//  Start a libcurl easy session
        CURL *curl = curl_easy_init();

		if (curl) {

			// If libcurl easy session is initialized

			// Create new file (c-style)
			FILE* cache = NULL;
			errno_t status = fopen_s(&cache, oldpath.c_str(), "wb");

			if(!cache || status) {

                char err_msg[256];
                strerror_s(err_msg, 256, status);

				// Report error
				std::cerr << err_msg << std::endl;

				std::exit(EXIT_FAILURE);
			}

			// Define resource
			CURLcode res;

			// Tell libcurl how to behave
			curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, cache); 
			curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);

			//  Perform a file transfer synchronously
			res = curl_easy_perform(curl);

			if (res == CURLE_OK) {
				// File exists

                char* ct = NULL;
                res = curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct);

                if (!res && ct) {
                    // ct is of format "<type>/<extension>"
                    const char* ext = strrchr(ct, int('/')) + 1;
                    filepath = oldpath + "." + std::string(ext);

                    fclose(cache);

				    if (verbose) std::cout << "File successfully downloaded (" << filepath << ")" << std::endl;

                    if (!Explorer::rename(oldpath, filepath))
                        std::cerr << "Error when renaming '" << oldpath << "' to '" << filepath << "'" << std::endl;
                }
                else {
                    // CURL encountered an error
                    std::cerr << "CURL ERROR : " << curl_easy_strerror(res) << std::endl;

                    // return given url
                    filepath = url;

                    fclose(cache);
                }
			}
			else {
  				// CURL encountered an error
				std::cerr << "CURL ERROR : " << curl_easy_strerror(res) << std::endl;
				
				// return given url
				filepath = url;

                fclose(cache);
			}

			curl_easy_cleanup(curl);
		}

		return filepath;
	}

    bool Explorer::checkrtsp(const std::string& url) {
        bool status = false;

        //  Start a libcurl easy session
        CURL *curl = curl_easy_init();

        // Verifying character ':'
        std::size_t pos = url.rfind(":");
        std::string scheme = url.substr(0, pos);

        if (scheme == "http") {
            if (curl) {
                // If libcurl easy session is initialized

                // Define resource
                CURLcode res;

                // Tell libcurl how to behave
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_NOBODY, url.c_str());

                //  Perform a file transfer synchronously
                res = curl_easy_perform(curl);

                if (!res) {
                    // If everything was OK

                    // Define last received response code
                    long response = 0;

                    // Extract information from a curl handle
                    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response);
                    if (response == 200 && res != CURLE_ABORTED_BY_CALLBACK) {
                        // If the request succeeded

                        // Define content-type
                        char *ct = NULL;

                        // Extract information from a curl handle
                        curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, & ct);

                        if (!res && ct) {
                            // If the content-type was saved
                            const char ctd[] = "multipart/x-mixed-replace; boundary=myboundary";

                            if (ct == ctd) {
                                // If it is a good content-type
                                status = true;
                            }
                            else {
                                // If it is a bad content-type
                                status = false;
                            }
                        }
                        else {
                            // If the content-type was not saved
                            status = false;
                        }
                    }
                    else {
                        // If the request didn't succeed
                        status = false;
                    }
                }
                else {
                    // If everything was not OK
                    status = false;
                }

                // End a libcurl easy handle
                curl_easy_cleanup(curl);
            }
            else {
                // If libcurl session is not initialized
                status = false;
            }
        }
        else if (scheme == "rtsp") {
            // If scheme is 'rtsp'
            if (curl) {
                // If libcurl session is initialized

                // Define resource
                CURLcode res;

                // Tell libcurl how to behave
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

                //  Perform a file transfer synchronously
                res = curl_easy_perform(curl);

                if (res == CURLE_OK) {
                    // If everything was OK

                    // Define last received response code
                    long response = 0;

                    // Extract information from a curl handle
                    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response);
                    if (response == 200 && res != CURLE_ABORTED_BY_CALLBACK) {
                        // If the request succeeded

                        // Define RTSP server CSEQ
                        long cseq = 0;

                        // Extract information from a curl handle
                        curl_easy_getinfo(curl, CURLINFO_RTSP_SERVER_CSEQ, &cseq);

                        if (cseq == 1) {
                            // If CSEQ is 1
                            status = true;
                        }
                        else {
                            // If CSEQ isn't 1
                            status = false;
                        }
                    }
                    else {
                        // If the request didn't succeed
                        status = false;
                    }
                }
                else {
                    // If everything was not OK
                    status = false;
                }

                // End a libcurl easy handle
                curl_easy_cleanup(curl);
            }
            else {
                // If libcurl session is not initialized
                status = false;
            }
        }
        else {
            // If it is an unauthorized scheme
            status = false;
        }

        return status;
    }

    void Explorer::vi(const std::string& distn, const std::string& content) {
        // Define a ofstream object
        std::ofstream file(distn, std::ios::in | std::ios::app);

        if (file) {
            // If stream is open
            if (content.empty() || content.compare("") == 0) {
                file.close();
            }
            else {
                file << content << std::endl;
                file.close();
            }
        }
    }

    std::tuple<int, int> Explorer::screenres() {
        // Define screen resolution
        int height;
        int width;

        #ifdef __linux__
            // Get a Display structure that serves as the connection to the X server 
            Display *disp = XOpenDisplay(NULL);

            // Get default screen of the specified display
            Screen *scrn = DefaultScreenOfDisplay(disp);

            // Get height of screen
            height = scrn->height;

            // Get width of screen
            width = scrn->width;
        #elif defined _WIN32
            // Get height of screen
        	height = (int)GetSystemMetrics(SM_CYSCREEN);

            // Get width of screen
            width  = (int) GetSystemMetrics(SM_CXSCREEN);
        #endif // ! __linux__ or _WIN32

        // Return screen resolution
        return std::make_tuple(height, width);
    }

    std::string Explorer::sha256Sum(const std::string& message) {
        unsigned char digest[Sha256::DIGEST_SIZE];
        memset(digest, 0, Sha256::DIGEST_SIZE);

        Sha256 sh = Sha256();
        sh.update((unsigned char*)message.c_str(), (unsigned int)message.length());
        sh.final(digest);
    
        char buf[2*Sha256::DIGEST_SIZE+1];
        buf[2*Sha256::DIGEST_SIZE] = 0;

        for (char i = 0; i < char(Sha256::DIGEST_SIZE); i++) {
            sprintf_s(buf + (char(i) * char(2)), Sha256::DIGEST_SIZE, "%02x", digest[i]);
        }

        return std::string(buf);
    }

    std::string Explorer::rngd() {
        std::string result;

        // Seed with a real random value, if available
        std::random_device r;

        // Choose a random mean between 1 and 65535
        std::default_random_engine el(r());
        std::uniform_int_distribution<int> uniform_dist(1, 65535);
        int mean = uniform_dist(el);

        // Initialize system random number generator
        srand((unsigned int)time(nullptr));

        // Get entropy
        int entropy = rand() % 10 + 1;

        // Get random number
        result = itos(mean * entropy);

        return result;
    }
}
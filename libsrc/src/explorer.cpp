#include <oft/explorer.hpp>

namespace oft {

    Explorer::Explorer() {}
    
    Explorer::~Explorer() {}

    std::string Explorer::gwd() {
        std::string result;

        #ifdef __linux__
            char cwd[PATH_MAX];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                result = std::string(cwd); 
            }
        #elif defined _WIN32
            char buffer[MAX_PATH];

            if (_getcwd(buffer, sizeof(char) * MAX_PATH) != NULL) {
                result = std::string(buffer);
            }
            /*
            if (GetModuleFileName(NULL, (LPWSTR)std::wstring(bufstr.begin(), bufstr.end()).c_str(), MAX_PATH) != NULL) {
                std::string::size_type pos = bufstr.find_last_of("\\/");
                result = bufstr.substr(0, pos);
            }*/
        #endif // ! __linux__ or _WIN32

        return result;
    }

    bool Explorer::makdir(Directory obj) {
        bool status = false;

        #ifdef __linux__
            int flag;
            if ((flag = mkdir(obj.distn().c_str(), S_IRWXU | S_IRGRP |  S_IXGRP | S_IROTH | S_IXOTH)) != -1) {
                // Directory created
                status = true;
            }
            else {
                // Directory already exists
                status = false;
            }
        #elif defined _WIN32
            if (CreateDirectoryW(std::wstring(obj.distn().begin(), obj.distn().end()).c_str(), NULL)) {
                // Directory created
                status = true;
            }
            else if (ERROR_ALREADY_EXISTS == GetLastError()) {
                // Directory already exists
                status = false;
            }
            else {
                // Failed for some other reason
                status = false;
            }
        #endif // ! __linux or _WIN32

        return status;
    }

    bool Explorer::remdir(Directory obj) {
        bool status = false;

         #ifdef __linux__
            int flag;
            if ((flag = rmdir(obj.distn().c_str())) != -1) {
                // Directory removed
                status = true;
            }
            else {
                // Directory not removed
                status = false;
            }
        #elif defined _WIN32
            if (RemoveDirectoryW(std::wstring(obj.distn().begin(), obj.distn().end()).c_str())) {
                // Directory removed
                status = true;
            }
            else {
                // Directory not removed
                status = false;
            }
        #endif // ! __linux or _WIN32

        return status;
    }

    bool Explorer::delfs(File obj) {
        bool status = false;

        #ifdef __linux__
            if (remove(obj.distn().c_str()) != 0) {
                // File deleted
                status = true;
            }
            else {
                // File not deleted
                status = false;
            }
        #elif defined _WIN32
            if (DeleteFileW(std::wstring(obj.distn().begin(), obj.distn().end()).c_str()) != NULL) {
                // File deleted
                status = true;
            }
            else {
                // File not deleted
                status = false;
            }
        #endif // ! __linux__ or _WIN32

        return status;
    }

    bool Explorer::delfs(Directory obj) {
        bool status = false;

        #ifdef __linux__
            DIR *dir = opendir(obj.distn().c_str());
            if (dir) {
                // Directory exists
                struct dirent *file = NULL;
                char filePath[512];

                while ((file = readdir(dir)) != NULL) {
                    // Build the path for each file in the folder
                    sprintf(filePath, "%s/%s", obj.distn().c_str(), file->d_name);
                    remove(filePath);
                }
                closedir(dir);
                status = true;
            }
            else if (ENOENT == errno) {
                // Directory does not exist
                status = false;
            }
            else {
                // Failed for some reasons
                status = false;
            }
        #elif defined _WIN32
            
            WIN32_FIND_DATA file;
            HANDLE searches;
            std::string obj_distn = obj.distn();

            std::string filePath = obj_distn + "\\*.*";

            std::wstring filestr(filePath.begin(), filePath.end());
            searches = FindFirstFileW(filestr.c_str(), (LPWIN32_FIND_DATAW)&file);
            if (searches != NULL) {
                do {
                    // Build the path for each file in the folder
                    std::wstring wstrFileName = std::wstring((wchar_t*)file.cFileName);

                    filestr = std::wstring(obj_distn.begin(), obj_distn.end()) + L"\\" + wstrFileName;

                    DeleteFileW(filestr.c_str());

                } while (FindNextFileW(searches, (LPWIN32_FIND_DATAW)&file));
                FindClose(searches);
                status = true;
            }
            else if (ERROR_FILE_NOT_FOUND == GetLastError()) {
                // Files don't exist
                status = false;
            }
            else {
                // Files don't exist
                status = false;
            }
        #endif // ! __linux__ or _WIN32

        return status;
    }

    bool Explorer::empty(const std::string& distn) {
        bool status = false;

        // Load file
        std::ifstream file(distn, std::ios::in);

        // Check if file is opened
        if (file) {
            // File is opened
            std::string line;
            std::string content = "";

            // Getting content from file
            while (std::getline(file, line)) {
                content += line + "\n";
            }

            // Check if content is empty
            if (content.empty() || content.compare("") == 0) {
                // Content is empty
                status = true;
            }
            else {
                // Content is not empty
                status = false;
            }
            // Close file
            file.close();
        }
        else {
            // File cannot be opened
            status = false;
        }

        return status;
    }

    bool Explorer::forensic(const std::string& distn) {
        bool status = false;

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
        bool status = false;

        std::ifstream file(distn.c_str());
        if (file.good())  {
            // The file exists
            status = true;
        }
        else {
            // The file does not exist
            #ifdef __linux__
                DIR* dir = opendir(distn.c_str());
                if (dir) {
                    // The directory exists
                    closedir(dir);
                    status = true;
                }
                else if (ENOENT == errno) {
                    // The directory does not exist
                    status = false;
                }
                else {
                    // Failed for some reasons
                    status = false;
                }
            #elif defined _WIN32
                DWORD file_attr = GetFileAttributesW(std::wstring(distn.begin(), distn.end()).c_str());
                if (file_attr == INVALID_FILE_ATTRIBUTES) {
                    // Failed for some reasons
                    status = false;
                }
                else if (file_attr & FILE_ATTRIBUTE_DIRECTORY) {
                    // The directory exits
                    status = true;
                }
                else {
                    // The directory does not exist
                    status = false;
                }
            #endif // ! __linux__ or _WIN32
        }

        return status;
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

        Sha256 sh = Sha256(true);
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
#include <console.hpp>

namespace oft {

    Console::Console() {}

    Console::~Console() {}

    Console::Console(int _argco, char* _argve[])
        : argco(_argco), argve(_argve) {}

    Console::Console(Console const& obj)
        : argco(obj.argco), argve(obj.argve)  {}

    void displayHelp(const std::string& program) {
        #ifdef __linux__
            const std::string message =
                "                 \033[36m===============\033[0m                 \n"
                "              \033[36m=====================\033[0m              \n"
                "           \033[36m=========\033[0m         \033[36m=========\033[0m           \n"
                "        \033[36m======\033[0m                     \033[36m======\033[0m        \n"
                "       \033[36m====\033[0m                           \033[36m====\033[0m       \n"
                "      \033[36m===\033[0m                               \033[36m===\033[0m      \n"
                "     \033[36m====\033[0m                               \033[36m====\033[0m     \n"
                "    \033[33m====\033[0m    \033[32m*\033[0m                            \033[33m====\033[0m    \n"
                "   \033[33m====\033[0m     \033[32m*  *        *\033[0m                 \033[33m====\033[0m   \n"
                "  \033[33m===\033[0m       \033[32m*    *    *   *\033[0m                 \033[33m===\033[0m  \n"
                " \033[33m====\033[0m       \033[32m*       *       *\033[0m               \033[33m====\033[0m \n"
                "\033[33m====\033[0m        \033[32m*       * *   * *\033[0m                \033[33m====\033[0m\n"
                "\033[33m====\033[0m        \033[32m*       *   *   *\033[0m                \033[33m====\033[0m\n"
                "\033[33m====\033[0m        \033[32m*       *   *   *\033[0m                \033[33m====\033[0m\n"
                " \033[33m====\033[0m       \033[32m*    *    * * *\033[0m                 \033[33m====\033[0m \n"
                "  \033[33m===\033[0m       \033[32m*  *        *\033[0m                   \033[33m===\033[0m  \n"
                "   \033[33m====\033[0m     \033[32m*           *\033[0m                 \033[33m====\033[0m   \n"
                "    \033[33m====\033[0m      \033[32m*         *\033[0m                \033[33m====\033[0m    \n"
                "     \033[33m====\033[0m       \033[32m*       *\033[0m               \033[33m====\033[0m     \n"
                "      \033[33m===\033[0m         \033[32m*     *\033[0m               \033[33m===\033[0m      \n"
                "       \033[33m====\033[0m         \033[32m*   *\033[0m             \033[33m====\033[0m       \n"
                "        \033[33m======\033[0m        \033[32m* *\033[0m          \033[33m======\033[0m OpenFaceTracker\n"
                "           \033[31m=========\033[0m         \033[31m=========\033[0m    License GPLv3+ : GNU GPL version 3 or later\n"
                "             \033[31m=======================\033[0m      © Copyright - ESIEA Campus Laval 2020\n"
                "                \033[31m=================\033[0m         CNS (Confiance Numérique et Sécurité)\n"
                ;
        #elif defined _WIN32
            const std::string message =
                "                 ===============                 \n"
                "              =====================              \n"
                "           =========         =========           \n"
                "        ======                     ======        \n"
                "       ====                           ====       \n"
                "      ===                               ===      \n"
                "     ====                               ====     \n"
                "    ====    *                            ====    \n"
                "   ====     *  *        *                 ====   \n"
                "  ===       *    *    *   *                 ===  \n"
                " ====       *       *       *               ==== \n"
                "====        *       * *   * *                ====\n"
                "====        *       *   *   *                ====\n"
                "====        *       *   *   *                ====\n"
                " ====       *    *    * * *                 ==== \n"
                "  ===       *  *        *                   ===  \n"
                "   ====     *           *                 ====   \n"
                "    ====      *         *                ====    \n"
                "     ====       *       *               ====     \n"
                "      ===         *     *               ===      \n"
                "       ====         *   *             ====       \n"
                "        ======        * *          ====== OpenFaceTracker\n"
                "           =========         =========    License GPLv3+ : GNU GPL version 3 or later\n"
                "             =======================      © Copyright - ESIEA Campus Laval 2020\n"
                "                =================         CNS (Confiance Numérique et Sécurité)\n"
                ;
        #endif // __linux__ or _WIN32

        std::cout << message << std::endl;
        std::cout << "\n" << "Name : " << std::endl;
        std::cout << "\t" << program << " - OpenFaceTracker" << std::endl;
        std::cout << "\n" << "Usage : " << std::endl;
        std::cout << "\t" << program << " option <SOURCE> [-a|--add [<LABEL>] [-y|--yes]] " << std::endl;
        std::cout << "\t" << program << " -r|--remove <LABEL|ID> " << std::endl;
        std::cout << "\n" << "Description : " << std::endl;
        std::cout << "\t" << "OpenFaceTracker is a facial recognition system, a technology capable of identifying or verifying a person from a digital image or a video frame from a video source." << std::endl;
        std::cout << "\t" << "Mandatory arguments to long options are mandatory for short options too." << std::endl;
        std::cout << "\t" << "-h, --help" << "\t\t" << "display this help and exit" << std::endl;
        std::cout << "\t" << "-v, --version" << "\t\t" << "display the version of the application and exit" << std::endl;
        std::cout << "\t" << "-d, --device" << "\t\t" << "identify a person from a video frame (from <SOURCE> that could be CAM0, CAM1 or CAM2)" << std::endl;
        std::cout << "\t" << "-i, --image" << "\t\t" << "identify a person from a digital image (from <SOURCE> that could be a JPEG or JPG file)" << std::endl;
        std::cout << "\t" << "-p, --player" << "\t\t" << "identify a person from a video (from <SOURCE> that could be a AVI, MPEG-4 or MATROSKA file)" << std::endl;
        std::cout << "\t" << "-u, --url" << "\t\t" << "identify a person from a video frame (<SOURCE> must be a reachable streaming URL with RTSP or HTTP scheme)" << std::endl;
        std::cout << "\t" << "-a, --add" << "\t\t" << "add the identified person's sample to database as <LABEL>. Works only when used with -i|--image" << std::endl;
        std::cout << "\t" << "-y, --yes" << "\t\t" << "used with [-a|--add]. Ignores confirmation to add face (<SOURCE> has to contain only one person)" << std::endl;
        std::cout << "\t" << "-r, --remove" << "\t\t" << "remove person labelled <LABEL> or with <ID> from database" << std::endl;
        std::cout << "\n" << "Author : " << std::endl;
        std::cout << "\t" << "Written by Maxime BEASSE" << std::endl;
    }

    void displayVersion() {
        std::cout << "OpenFaceTracker" << std::endl;
        std::cout << "Version 6.0.0" << std::endl;
        std::cout << "License GPLv3+ : GNU GPL version 3 or later" << std::endl;
        std::wcout << (wchar_t)0xA9 << " Copyright - ESIEA Campus Laval 2020" << std::endl;
#ifdef __linux__
        std::cout << "CNS (Confiance Numérique et Sécurité)" << std::endl;
#elif defined _WIN32
        std::cout << "CNS (Confiance Num\202rique et S\202curit\202)" << std::endl;
#endif // __linux__ or _WIN32
    }

    void Console::listener() {
        std::vector<std::string> parameters;
        std::vector<std::string>::iterator it;
        std::string label("");
		bool confirmation = true;

        // Building argument vector with argument count
        for (int i = 0; i < this->argco; ++i) {
            parameters.push_back(this->argve[i]);
        }

        // If there is no parameter
        if (this->argco == 1) {
            std::cerr << "No parameter" << std::endl;
            std::cerr << "Use [" << parameters[0] << " --help] to have the complete list of options available on the command-line." << std::endl;
            return;
        }

        // Search for -h and --help command-line options
        if ((it = std::find(parameters.begin(), parameters.end(), "-h")) != parameters.end() ||
            (it = std::find(parameters.begin(), parameters.end(), "--help")) != parameters.end()) {
            displayHelp(parameters[0]);
            parameters.erase(it);
            return;
        }

        // Search for -v and --version command-line options
        if ((it = std::find(parameters.begin(), parameters.end(), "-v")) != parameters.end() ||
            (it = std::find(parameters.begin(), parameters.end(), "--version")) != parameters.end()) {
            displayVersion();
            parameters.erase(it);
            return;
        }

        // Search for -r and --remove command-line options
        if ((it = std::find(parameters.begin(), parameters.end(), "-r")) != parameters.end() ||
            (it = std::find(parameters.begin(), parameters.end(), "--remove")) != parameters.end()) {
            
            // Verify <LABEL> is specified
            if (it != parameters.end() - 1 && (label = *(it + 1)).front() != '-') {

                parameters.erase(it + 1);

                Backend b(true);
                // TODO Remove <LABEL|ID> from db
            }
            else {
                std::cerr << "Invalid label" << std::endl;
                std::cerr << "Use [" << parameters[0] << " --remove <LABEL>]" << std::endl;
            }

            parameters.erase(it);
            return;
        }

        // Search for -a and --add command-line options
        if ((it = std::find(parameters.begin(), parameters.end(), "-a")) != parameters.end() ||
            (it = std::find(parameters.begin(), parameters.end(), "--add")) != parameters.end()) {

            // Verify <LABEL> is specified
            if (it != parameters.end() - 1 && (label = *(it + 1)).front() != '-') {
                parameters.erase(it + 1);
            }
            else {
                std::cerr << "Invalid label" << std::endl;
                std::cerr << "Use [ ... --add <LABEL>]" << std::endl;
            }

            parameters.erase(it);
        }

		// Search for -y and --yes command-line options
        if ((it = std::find(parameters.begin(), parameters.end(), "-y")) != parameters.end() ||
            (it = std::find(parameters.begin(), parameters.end(), "--yes")) != parameters.end()) {

			confirmation = false;

            parameters.erase(it);
        }

        // If there are additional parameters
        if (parameters.size() > 1) {

            // Define an Explorer object
            Explorer e = Explorer();

            // Define LabCollector object
            LabCollector lc = LabCollector();

            // Search for -d and --device command-line options
            if ((it = std::find(parameters.begin(), parameters.end(), "-d")) != parameters.end() ||
                (it = std::find(parameters.begin(), parameters.end(), "--device")) != parameters.end()) {


                // Verify <SOURCE> is specified
                if (it != parameters.end() - 1) {

                    std::string device = *(it + 1);
                    parameters.erase(it + 1);

                    // Verifying the source
                    if (device == "CAM0" || device == "CAM1" || device == "CAM2") {
                        // Launch Video Analysis from the real time streaming
                        lc.VideoAnalysis((char*)device.c_str(), label, confirmation);
                    }
                    else {
                        std::cerr << "Invalid device" << std::endl;
                        std::cerr << "You should use the devices provided for this purpose" << std::endl;
                        std::cerr << "Authorized peripherals : CAM0, CAM1 or CAM2" << std::endl;
                    }
                }
                else {
                    std::cerr << "Invalid source" << std::endl;
                    std::cerr << "Use [" << parameters[0] << " --device <SOURCE>]" << std::endl;
                }

                parameters.erase(it);
                return;
            }

            // Search for -i and --image command-line options
            if ((it = std::find(parameters.begin(), parameters.end(), "-i")) != parameters.end() ||
                (it = std::find(parameters.begin(), parameters.end(), "--image")) != parameters.end()) {

                std::string image;

                // Verify <SOURCE> is specified
                if (it != parameters.end() - 1 && (image = *(it + 1)).front() != '-') {

                    parameters.erase(it + 1);

                    // Verifying the source
                    if (e.exist(image)) {
                        // If file exists
                        if (e.forensic(image)) {
                            // If it is an authorized image file

                            // Launch Image Analysis from the file
                            lc.ImageAnalysis((char*)image.c_str(), label, confirmation);
                        }
                        else {
                            // If it is an unauthorized image file
                            std::cerr << "Invalid format" << std::endl;
                            std::cerr << "You should use the formats provided for this purpose" << std::endl;
                            std::cerr << "Authorized formats : JPEG or JPG" << std::endl;
                        }
                    }
                    else {
                        // if file does not exit
                        std::cerr << "No image file found in 'file://" << image << "'" << std::endl;
                    }
                }
                else {
                    std::cerr << "Invalid arguments" << std::endl;
                    std::cerr << "Use [" << parameters[0] << " --image <SOURCE>]" << std::endl;
                }

                parameters.erase(it);
                return;
            }

            // Search for -p and --player command-line options
            if ((it = std::find(parameters.begin(), parameters.end(), "-p")) != parameters.end() ||
                (it = std::find(parameters.begin(), parameters.end(), "--player")) != parameters.end()) {

                std::string video;

                // Verify <SOURCE> is specified
                if (it != parameters.end() - 1 && (video = *(it + 1)).front() != '-') {

                    parameters.erase(it + 1);

                    // Verifying the source
                    if (e.exist(video)) {
                        // If file exists
                        if (e.forensic(video)) {
                            // If it is an authorized video file

                            // Launch Video Analysis from the real time streaming
                            lc.VideoAnalysis((char*)video.c_str(), label, confirmation);
                        }
                        else {
                            // If it is an unauthirized image file
                            std::cerr << "Invalid format" << std::endl;
                            std::cerr << "You should use the formats provided for this purpose" << std::endl;
                            std::cerr << "Authorized formats : AVI, MPEG-4 or MATROSKA" << std::endl;
                        }
                    }
                    else {
                        // if file does not exit
                        std::cerr << "No video file found in 'file://" << video << "' " << std::endl;
                    }
                }
                else {
                    std::cerr << "Invalid arguments" << std::endl;
                    std::cerr << "Use [" << parameters[0] << " --player <SOURCE>]" << std::endl;
                }

                parameters.erase(it);
                return;
            }

            // Search for -u and --url command-line options
            if ((it = std::find(parameters.begin(), parameters.end(), "-u")) != parameters.end() ||
                (it = std::find(parameters.begin(), parameters.end(), "--url")) != parameters.end()) {

                std::string url;

                // Verify <SOURCE> is specified
                if (it != parameters.end() - 1 && (url = *(it + 1)).front() != '-') {

                    parameters.erase(it + 1);

                    // Verifying the source
                    if (e.checkrtsp(url)) {
                        // If the streaming server is reachable

                        // Launch Video Analysis from the real time streaming
                        lc.VideoAnalysis((char*)url.c_str(), label, confirmation);
                    }
                    else {
                        // If the streaming server is unreachable
                        std::cerr << "Unreachable streaming server " << std::endl;
                        std::cerr << "You shoud provide reachable streaming url with RTSP or HTTP scheme" << std::endl;
                    }
                }
                else {
                    std::cerr << "Invalid arguments" << std::endl;
                    std::cerr << "Use [" << parameters[0] << " --url <SOURCE>]" << std::endl;
                }

                parameters.erase(it);
                return;
            }
        }

        // If there is an invalid parameter
        if (parameters.size() > 1) {
            std::cerr << "Invalid parameter ";
            for (auto p = parameters.begin() + 1; p != parameters.end(); ++p) {
                std::cerr << *p << std::endl;
            }
            std::cerr << "Launch [" << parameters[0] << " --help] to have the complete list of options available on the command-line." << std::endl;
        }

        // Clear parameters
        parameters.clear();
    }
}

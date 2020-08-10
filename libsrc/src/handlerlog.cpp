#include <oft/handlerlog.hpp>

namespace oft {
    
    HandlerLog::HandlerLog(bool _flag) 
        : ToolsBox(_flag) {}

    HandlerLog::HandlerLog(HandlerLog const& obj)
        : ToolsBox(obj) {}

    void HandlerLog::stop() {
        this->flag = false;
    }

    void HandlerLog::create(const std::string& event) {
        // Get current time
        std::time_t system_clock = time(0);

        // Define locale time zone structure
        struct tm locale_time_zone;

        // Define a buffer for locale time zone
        char buffer[80];

        // Get locale time zone
        errno_t err = localtime_s(&locale_time_zone , &system_clock);

        if (err)
            throw("Invalid argument to localtime_s.");

        // Format locale time zone in a buffer
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %X", &locale_time_zone);

        // Define explorer
        Explorer e;

        // Define log file
        #ifdef __linux__
            #ifdef API
                const char log_file[] = "/../../../var/log/oft.log";
            #else
                const char log_file[] = "/../var/log/oft.log";
            #endif // ! API
        #elif defined _WIN32
            #ifdef API
                const char log_file[] = "\\..\\..\\..\\var\\log\\oft.log";
            #else
                const char log_file[] = "\\..\\var\\log\\oft.log";
            #endif // ! API
        #endif // ! __linux__ or _WIN32

        std::string log = e.gwd() + std::string(log_file);

        // Define event log
        std::string event_log = std::string(buffer) + " OPENFACETRACKER : " + event;

        // Write a log
        e.vi(log, event_log);

        #ifdef __linux__
            // Set the logmask for calling process
            setlogmask(LOG_UPTO(LOG_NOTICE));

            // Open a connection to the system logger for the program
            openlog("oft", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

            // Generate a log message
            syslog(LOG_NOTICE, "OpenFaceTracker started by User %d", getuid());
            syslog(LOG_INFO, event.c_str());
        #endif // ! __linux__
    }
    
    HandlerLog::~HandlerLog() {}
}
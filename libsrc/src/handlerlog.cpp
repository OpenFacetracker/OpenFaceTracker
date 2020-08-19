#include <oft/handlerlog.hpp>

namespace oft {
    
#ifdef oft_EXPORTS
	std::string HandlerLog::log_path = Explorer::fullPath("./oft.log");
#endif

	HandlerLog::HandlerLog() {}

	void HandlerLog::log(const std::string& event) {
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

        // Define event log
        std::string event_log = std::string(buffer) + " OPENFACETRACKER : " + event;

        // Write a log
        Explorer::vi(HandlerLog::log_path, event_log);

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

	void HandlerLog::setLogPath(const std::string& path) {
		HandlerLog::log_path = Explorer::fullPath(path);
		Explorer::create_directories(HandlerLog::log_path);
	}
}
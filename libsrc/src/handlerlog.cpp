/////////////////////////////////////////////////////////////////////////////
// AUTHOR: Maxime BEASSE
//
// Copyright (C) 2020  ESIEA Campus of Laval, France
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
/////////////////////////////////////////////////////////////////////////////
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
        #ifdef WIN32
        errno_t err = localtime_s(&locale_time_zone, &system_clock);
        #else
        auto err = localtime_r(&system_clock, &locale_time_zone);
        #endif

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

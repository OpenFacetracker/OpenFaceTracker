#include <oft/backend.hpp>

namespace oft {

#ifdef oft_EXPORTS
	std::string Backend::database("");
	std::string Backend::connection("");
	cppdb::result Backend::getAllRes = cppdb::result();
#endif

	Backend::Backend() {}

    void Backend::setDBPath(const std::string& db_path) {
				
        // Set db path
		Backend::database = Explorer::fullPath(db_path);

		Explorer::create_directories(Backend::database);

        // Load connection string
        Backend::connection = "sqlite3:db=" + Backend::database;

        // initialize database tables if it does not exist
        if (!Explorer::exist(Backend::database)) {
            start();
        }
    }

    void Backend::start() {
		// Define new session
		cppdb::session sql(Backend::connection);

		try {
			// Check if database is exist and is empty
			if (Explorer::empty(Backend::database)) {

				// Drop tables if they exist
				//sql << "DROP TABLE IF EXISTS DB_Header" << cppdb::exec;

				sql << "DROP TABLE IF EXISTS Person" << cppdb::exec;

				// Create table DB_Header if not exists
				/*sql << "CREATE TABLE IF NOT EXISTS DB_Header ( "
					"   ID_Person               INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,   "
					"   Label                   TEXT NOT NULL UNIQUE,   "
					"   NB_Samples              INTEGER NOT NULL,   "
					"   Data                    BLOB NOT NULL   "
					")  " << cppdb::exec;*/

				// Create table Person if not exists
				sql << "CREATE TABLE IF NOT EXISTS Person ( "
					"   ID_Person               INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,   "
					"   Label                   TEXT NOT NULL,   "
					"   NB_Samples              INTEGER NOT NULL,   "
					"   Data                    BLOB NOT NULL   "
					")  " << cppdb::exec;

				// TODO last update time for Person
			}
		}
		catch (std::exception const& e) {
			std::cerr << e.what() << std::endl;
		}

		HandlerLog::log("Backend - Database Initialized");
    }

    long long Backend::insert(const std::string& label, std::istream& is, int nb_Samples) {
        long long result = -1;

		// Define new session
		cppdb::session sql(Backend::connection);

		try {
			// Get current time
			std::time_t system_clock = time(0);

			// Define locale time zone structure
			struct tm locale_time_zone;

			// Get locale time zone
			errno_t err = localtime_s(&locale_time_zone, &system_clock);

			if (err)
				throw("Invalid argument to localtime_s.");

			// Define statement
			cppdb::statement stat;

			// Insert new entry
			stat = sql << "INSERT INTO Person(Label, NB_Samples, Data)   "
							"VALUES(?, ?, ?)   "
							<< label << nb_Samples << is;
			stat.exec();

			result = stat.last_insert_id();
		}
		catch(std::exception const& e) {
			std::cerr << e.what() << std::endl;
		}

        return result;
    }

    bool Backend::update(const std::string& label, std::istream& is, int nb_Samples) {
        bool result = false;

		// Define new session
		cppdb::session sql(Backend::connection);

		try {
			// Get current time
			std::time_t system_clock = time(0);

			// Define locale time zone structure
			struct tm locale_time_zone;

			// Get locale time zone
			errno_t err = localtime_s(&locale_time_zone, &system_clock);

			if (err)
				throw("Invalid argument to localtime_s.");

			// Define statement
			cppdb::statement stat;

			// Update entry
			stat = sql << "UPDATE Person SET Label = ?, NB_Samples = ?, Data = ?"
				<< label << nb_Samples << is;
			stat.exec();

			result = true;
		}
		catch (std::exception const& e) {
			std::cerr << e.what() << std::endl;
		}

        return result;
    }

    bool Backend::remove(const std::string& label) {
        bool result = false;

		// Define new session
		cppdb::session sql(Backend::connection);

		try {
			// Define statement
			cppdb::statement stat;

			// Update entry
			stat = sql << "DELETE FROM Person WHERE Label = ?"
				<< label;
			stat.exec();

			result = true;
		}
		catch (std::exception const& e) {
			std::cerr << e.what() << std::endl;
		}

        return result;
    }

    bool Backend::getAll() {
        bool result = false;

		// Define new session
		cppdb::session sql(Backend::connection);

		try {
			Backend::getAllRes = sql << "SELECT * FROM Person";
			result = true;
		}
		catch (std::exception const& e) {
			std::cerr << e.what() << std::endl;
		}

        return result;
    }

    bool Backend::getNext(std::tuple<long long, std::string, int, std::stringstream>& result) {

        bool success = false;

		try {
			if (!getAllRes.next())
				return false;

			result = std::make_tuple(getAllRes.get<long long>(0), getAllRes.get<std::string>(1), getAllRes.get<int>(2), getAllRes.get<std::stringstream>(3));

			success = true;
		}
		catch (std::exception const& e) {
			std::cerr << e.what() << std::endl;
		}

        return success;
    }

    std::size_t Backend::size() {
        std::size_t result = 0;

		// Define new session
		cppdb::session sql(Backend::connection);

		try {
			// Define statement
			cppdb::statement stat;

			stat = sql << "SELECT count(*) FROM Person  ";

			// Get result
			cppdb::result res = stat.row();

			if (!res.empty()) {
				result = std::stoi(res.get<std::string>(0));
			}
		}
		catch(std::exception const& e) {
			std::cerr << e.what() << std::endl;
		}

        return result;
    }
}
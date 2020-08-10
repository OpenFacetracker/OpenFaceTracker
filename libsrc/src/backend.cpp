#include <oft/backend.hpp>

namespace oft {

    Backend::Backend(bool _flag)
        : ToolsBox(_flag) {
        // Define an Explorer object
        Explorer e = Explorer();

        // Define a database file
#ifdef __linux__
#ifdef API
        const char file[] = "/../../../data/database/openfacetracker.db";
#else
        const char file[] = "/../data/database/openfacetracker.db";
#endif // ! API
#elif defined _WIN32
#ifdef API
        const char file[] = "\\..\\..\\..\\data\\database\\openfacetracker.db";
#else
        const char file[] = "\\..\\data\\database\\openfacetracker.db";
#endif // ! API
#endif // ! __linux__ or _WIN32

        // Load database file
        this->database = e.gwd() + std::string(file);

        // Load connection string
        this->connection = "sqlite3:db=" + this->database;

        // initialize database tables if it does not exist
        if (!e.exist(this->database)) {
            start();
        }

        // Load database session
        this->session.open(this->connection);
    }

    Backend::Backend(Backend const& obj)
        : ToolsBox(obj) {

        // Load database file
        this->database = obj.database;

        // Load connection string
        this->connection = obj.connection;

        // Load database session
        this->session = cppdb::session(this->connection);
    }

    void Backend::start() {
        if (this->flag) {
            // Define new session
            cppdb::session sql(this->connection);

            try {
                // Define an Explorer object
                Explorer e = Explorer();

                // Check if database is empty
                if (e.empty(this->database)) {

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

                    // Create a statement
                    /*cppdb::statement stat;

                    stat = sql << "INSERT INTO PersonStatus(Status) "
                                    "VALUES(?)  "
                                    << "Administrator";
                    stat.exec();

                    stat = sql << "INSERT INTO PersonStatus(Status) "
                                    "VALUES(?)  "
                                    << "Guest";
                    stat.exec();

                    stat = sql << "INSERT INTO Person(PersonCode, PersonStatusId)   "
                                    "VALUES(?, ?)   "
                                    << "0" << 1;
                    stat.exec();

                    stat = sql << "INSERT INTO PasseportPicture(Hash, DistinguishedName, Release, PersonId) "
                                    "VALUES(?, ?, ?, ?) "
                                    << "0" << admin << now << 1;
                    stat.exec();*/
                }
            }
            catch (std::exception const& e) {
                std::cerr << e.what() << std::endl;
            }

            // Load session
            this->session = sql;
        }
    }

    long long Backend::insert(const std::string& label, std::istream& is, int nb_Samples) {
        long long result = -1;

        if (this->flag) {
            // Define new session
            cppdb::session sql(this->connection);

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
        }

        return result;
    }

    bool Backend::update(const std::string& label, std::istream& is, int nb_Samples) {
        bool result = false;

        if (this->flag) {
            // Define new session
            cppdb::session sql(this->connection);

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
        }

        return result;
    }

    bool Backend::remove(const std::string& label) {
        bool result = false;

        if (this->flag) {
            // Define new session
            cppdb::session sql(this->connection);

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
        }

        return result;
    }

    bool Backend::getAll() {
        bool result = false;

        if (this->flag) {
            // Define new session
            cppdb::session sql(this->connection);

            try {
                this->getAllRes = sql << "SELECT * FROM Person";
                result = true;
            }
            catch (std::exception const& e) {
                std::cerr << e.what() << std::endl;
            }
        }

        return result;
    }

    bool Backend::getNext(std::tuple<long long, std::string, int, std::stringstream>& result) {

        bool success = false;

        if (this->flag) {
            try {
                if (!getAllRes.next())
                    return false;

                result = std::make_tuple(getAllRes.get<long long>(0), getAllRes.get<std::string>(1), getAllRes.get<int>(2), getAllRes.get<std::stringstream>(3));

                success = true;
            }
            catch (std::exception const& e) {
                std::cerr << e.what() << std::endl;
            }
        }

        return success;
    }

    std::size_t Backend::size() {
        std::size_t result = 0;

        if (this->flag) {
            // Define new session
            cppdb::session sql(this->connection);

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
        }

        return result;
    }

    void Backend::stop() {
        this->flag = false;
    }

    Backend::~Backend() {}
}

#include <oft/handlerjson.hpp>

namespace oft {
    
	HandlerJson::HandlerJson() {}

	HandlerJson::HandlerJson(const std::string& filepath) {

		if (!Explorer::exist(filepath)) {
			HandlerLog::log("HandlerJson : given config filepath does not exist (" + filepath + ")");

			std::exit(EXIT_FAILURE);
		}

		std::ifstream fs(filepath);
		fs >> (*this);
		fs.close();
	}

    HandlerJson::~HandlerJson() {}

}
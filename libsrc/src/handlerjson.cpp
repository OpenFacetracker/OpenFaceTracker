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

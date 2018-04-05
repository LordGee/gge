#pragma once

#include <string>
#include <fstream>
#include <sstream>

namespace gge
{
	class FileRead {
	public:
		static std::string ReadFile(const char* filepath) {

			std::ifstream file(filepath);
			std::string line;
			std::stringstream stream;

			while (std::getline(file, line)) {
				stream << line << "\n";
			}

			return stream.str();

		}
	};
}

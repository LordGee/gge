#pragma once

#include <string>
#include <fstream>
#include <sstream>

namespace gge
{
	/* Reads in a text file and returns as a string, this is used for the shader load */
	static std::string ReadFile(const char* filepath) {
		std::ifstream file(filepath);
		std::string line;
		std::stringstream stream;
		while (std::getline(file, line)) {
			stream << line << "\n";
		}
		return stream.str();
	}
}

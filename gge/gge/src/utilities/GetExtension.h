#pragma once

#include <string>
#include <sstream>
#include <vector>

namespace gge {
	static std::vector<std::string> GetExtensionFromFilename(const std::string &s, char delimeter) {
		std::vector<std::string> elements;
		std::stringstream ss(s);
		std::string character;
		while (std::getline(ss, character, delimeter)) {
			elements.push_back(character);
		}
		return elements;
	}
}
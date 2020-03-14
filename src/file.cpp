#include <fstream>
#include <sstream>
#include <string>

#include "file.hpp"

std::string apparator::file::read(const char* filePath) {
	std::string fileData;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		printf("Cannot open file: %s.\n", filePath);
		return 0;
	}

	std::stringstream sstr;
	sstr << fileStream.rdbuf();
	fileData = sstr.str();
	fileStream.close();

	return fileData;
}

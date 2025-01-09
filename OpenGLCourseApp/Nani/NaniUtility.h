#pragma once

#define ReadFile(FilePath, FileData) \
	std::ifstream filestream = std::ifstream(FilePath.c_str(), std::ios::in); \
	if (!filestream.is_open()) { /* checks to see if the file is successfully open and read for i/o operations */ \
		std::cerr << "Unable to Read File!" << std::endl; \
	} \
	std::string Line = ""; \
	while (!filestream.eof()) { /* Getting each line until end of the line */ \
		std::getline(filestream, Line); \
		FileData += Line + "\n"; \
	} \
	filestream.close(); \
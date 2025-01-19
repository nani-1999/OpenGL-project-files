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

#define PrintMat4(Mat4Val) \
	for (int i = 0; i < 4; i++) { \
		for (int j = 0; j < 4; j++) { \
			std::cout << Mat4Val[i][j] << " "; \
		} \
		std::cout << std::endl; \
	} \
	std::cout << std::endl;
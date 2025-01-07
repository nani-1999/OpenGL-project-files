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

//std::string ReadFile(const std::string FilePath) {
//	std::string FileData = "";
//
//	std::ifstream filestream = std::ifstream(FilePath.c_str(), std::ios::in);
//	if (!filestream.is_open()) { /* checks to see if the file is successfully open and read for i/o operations */
//		std::cerr << "Unable to Read File!" << std::endl;
//		return FileData;
//	}
//
//	std::string Line = "";
//	while (!filestream.eof()) { /* Getting each line until end of the line */
//		std::getline(filestream, Line);
//		FileData += Line;
//	}
//
//	//std::cout << "FileData: \n" << FileData << std::endl;
//	filestream.close();
//	return FileData;
//}
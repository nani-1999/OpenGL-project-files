#pragma once

#define PrintMat4(Mat4Val) \
	for (int i = 0; i < 4; i++) { \
		for (int j = 0; j < 4; j++) { \
			std::cout << Mat4Val[i][j] << " "; \
		} \
		std::cout << std::endl; \
	} \
	std::cout << std::endl;
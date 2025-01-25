#pragma once

#define PrintMat4(Mat4Val) \
	std::cout << #Mat4Val << std::endl; \
	for (int i = 0; i < 4; i++) { \
		for (int j = 0; j < 4; j++) { \
			std::cout << Mat4Val[j][i] << " "; \
		} \
		std::cout << std::endl; \
	} \
	std::cout << std::endl;

#define PrintVec3(Vec3Val) std::cout << #Vec3Val << ": X = " << Vec3Val.x << ", Y = " << Vec3Val.y << ", Z = " << Vec3Val.z << std::endl << std::endl;
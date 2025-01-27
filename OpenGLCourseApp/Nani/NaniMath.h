#pragma once

#include <glm/glm.hpp>

#define N_PI 					(3.1415926535897932f)	/* Extra digits if needed: 3.1415926535897932384626433832795f */
#define N_SMALL_NUMBER			(1.e-8f)

namespace Nani {
	float NormalizeAngle(float Angle) {
		if (Angle > 180.f) Angle -= 360.f;
		if (Angle < -180.f) Angle += 360.f;
		return Angle;
	}
	float RAInterpTo(float CurrentRotationAxis, float TargetRotationAxis, float DeltaTime, float InterpSpeed) {
		if (InterpSpeed <= 0.f)
		{
			return TargetRotationAxis;
		}

		const float DifferenceAngle = NormalizeAngle(TargetRotationAxis - CurrentRotationAxis); /* also determines direction */

		if (glm::sqrt(DifferenceAngle) < N_SMALL_NUMBER)
		{
			return TargetRotationAxis;
		}

		const float DeltaRotationAxis = DifferenceAngle * glm::clamp<float>(DeltaTime * InterpSpeed, 0.f, 1.f);

		return NormalizeAngle(CurrentRotationAxis + DeltaRotationAxis); /* normalized here also */
	}
}
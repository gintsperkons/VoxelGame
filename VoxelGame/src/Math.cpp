#include "Math.h"

// gets the distance in a direction
glm::vec3 Math::GetDirectionDistance(glm::vec3 normalizedDirection, float distance)
{
		return normalizedDirection * distance;
}

// gets the distance to the next block in a direction
float Math::DistToBlock(glm::vec3 pos, Axis axis, glm::vec3 dir)
{
	if (dir[axis] == 0.0f)
		return INFINITY;
	else
		return DistToBlock(pos, axis, dir[axis] < 0.0f);
}

// gets the distance to the next block in a direction
float Math::DistToBlock(glm::vec3 pos, Axis axis, bool negative)
{
	return DistToBlock(pos[axis], axis, negative);
}

// gets the distance to the next block in a direction
float Math::DistToBlock(float pos, Axis axis, bool negative)
{
	float result;

	if (!negative)
		result = 1.0f - glm::fract(pos);
	else
		result = glm::fract(pos);
	if (result == 0.0f)
		result = 1.0f;

	return result;
}

// converts an axis and direction to a direction enum
Math::Direction Math::AxisToDir(Axis axis, bool negative)
{
	return Math::Direction(axis * 2 + (negative ? 1 : 0));
}

// converts an axis to a normal vector in that direction 
glm::vec3 Math::AxisToNormal(Axis axis, bool negative)
{	
	switch (axis)
	{
	case Math::AXIS_X:
		if (negative)
			return glm::vec3(-1.0f, 0.0f, 0.0f);
		return glm::vec3(1.0f, 0.0f, 0.0f);
	case Math::AXIS_Y:
		if (negative)
			return glm::vec3(0.0f, -1.0f, 0.0f);
		return glm::vec3(0.0f, 1.0f, 0.0f);
	case Math::AXIS_Z:
		if (negative)
			return glm::vec3(0.0f, 0.0f, -1.0f);
		return glm::vec3(0.0f, 0.0f, 1.0f);
	default:
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}


}
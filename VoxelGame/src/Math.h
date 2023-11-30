#pragma once
#include <glm/glm.hpp>
#include <iostream>
namespace Math
{
	// 3D axes
	enum Axis
	{
		AXIS_X,
		AXIS_Y,
		AXIS_Z,

		AXIS_COUNT
	};

	// 3D directions
	enum Direction
	{
		DIRECTION_LEFT,
		DIRECTION_RIGHT,
		DIRECTION_UP,
		DIRECTION_DOWN,
		DIRECTION_FORWARD,
		DIRECTION_BACKWARD,

		DIRECTION_COUNT
	};

	glm::vec3 GetDirectionDistance(glm::vec3 normalizedDirection, float distance);
	float DistToBlock(glm::vec3 pos, Axis axis, glm::vec3 dir);
	float DistToBlock(glm::vec3 pos, Axis axis, bool negative);
	float DistToBlock(float pos, Axis axis, bool negative);
	Direction AxisToDir(Axis axis, bool negative);
	glm::vec3 AxisToNormal(Axis axis, bool negative);
};


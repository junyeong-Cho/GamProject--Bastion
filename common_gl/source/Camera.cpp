#include "Camera.h"
#include <corecrt_math.h>

Camera::Camera(vec2 camera_position, vec2 camera_up) noexcept
{
	Position = camera_position;
	IsFirstPerson = false;
	up = camera_up;
	right = { -camera_up.y, camera_up.x };
	orientation = static_cast<float>(atan2(camera_up.y, camera_up.x));
}

void Camera::SetUp(vec2 camera_up) noexcept
{
	up = camera_up;
	right = { -camera_up.y, camera_up.x };
	orientation = static_cast<float>(atan2(camera_up.y, camera_up.x));
}

void Camera::SetOrientation(float angle_radians) noexcept
{
	orientation = angle_radians;
	up = { static_cast<float>(cos(orientation)), static_cast<float>(sin(orientation)) };
	right = { -up.y, up.x };
}

void Camera::MoveUp(float distance) noexcept
{
	Position = Position + up * distance;
}

void Camera::MoveRight(float distance) noexcept
{
	Position = Position + right * distance;
}

void Camera::Rotate(float angle_radians) noexcept
{
	SetOrientation(orientation + angle_radians);
}

mat3 Camera::BuildCameraToWorld() const noexcept
{
	if (IsFirstPerson)
	{
		return mat3(right.x, right.y, 0, up.x, up.y, 0, Position.x, Position.y, 1);
	}
	else
	{
		return mat3(1, 0, 0, 0, 1, 0, Position.x, Position.y, 1);
	}
}

mat3 Camera::BuildWorldToCamera() const noexcept
{
	if (IsFirstPerson)
	{
		return mat3(-right.x, up.x, 0,
					-right.y, up.y, 0,
			dot(right, Position), -dot(up, Position), 1);

	}
	else
	{
		return mat3(1, 0, 0,
					0, 1, 0,
			-Position.x, -Position.y, 1);

	}
}


#include "camera.h"

Camera::Camera(const Vector3f& mPos, const Vector3f& mTarget, const Vector3f& mUp) {
				up = mUp;
				target = mTarget;
				position = mPos;
}

Camera::~Camera() {}

void Camera::Initialize()
{
}

void Camera::Update()
{
}


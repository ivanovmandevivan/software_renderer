
#include "camera.h"

Camera::Camera(const Vector3f& mPos, const Vector3f& mTarget, const Vector3f& mUp, const Vector3f& mFront) {
				up = mUp;
				front = mFront;
				side = up.crossProduct(front);
				target = mTarget;
				position = mPos;
				
				cameraFrustum = Frustum(90.0f, Display::SCREEN_ASPECT_RATIO, 0.1f, 1000.0f);
				viewMatrix = Matrix4::lookAt(position, target, up);
				projectionMatrix = Matrix4::projectionMat(cameraFrustum.fov, cameraFrustum.AR, cameraFrustum.near, cameraFrustum.far);
				cameraFrustum.SetCameraInternals();
				cameraFrustum.UpdatePlanes(viewMatrix, position);
}

Camera::~Camera() {}

void Camera::Update(unsigned int deltaTime)
{
				// Set the lookAt point direction to in front of the camera.
				target = position + front;

				viewMatrix = Matrix4::lookAt(position, target, up);
				cameraFrustum.UpdatePlanes(viewMatrix, position);
				projectionMatrix = Matrix4::projectionMat(cameraFrustum.fov, cameraFrustum.AR, cameraFrustum.near, cameraFrustum.far);
}

bool Camera::checkFrustumCulling(const AABox& boundary)
{
				return cameraFrustum.boxInFrustum(boundary);
}


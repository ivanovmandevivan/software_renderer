
#ifndef __CAMERA_H__
#define __CAMERA_H__ 1

#include "matrix.h"
#include "frustum.h"
#include "display.h"

class Camera {

public:
				Camera(const Vector3f& mPos, const Vector3f& mTarget, const Vector3f& mUp, const Vector3f& mFront);
				Camera(const Camera&) = delete;
				~Camera();

				void Update(unsigned int deltaTime);

				bool checkFrustumCulling(const AABox &boundary);

				Vector3f position;
				Vector3f target;
				Vector3f up;
				Vector3f front;
				Vector3f side;

				Matrix4 viewMatrix;
				Matrix4 projectionMatrix;
				Frustum cameraFrustum;

				float cameraSpeed = 0.3f;
				float pitch = 0;
				float yaw = -90;
};


#endif

#ifndef __CAMERA_H__
#define __CAMERA_H__ 1

#include "matrix.h"

class Camera {

public:
				Camera(const Vector3f &mPos, const Vector3f& mTarget, const Vector3f& mUp);
				Camera(const Camera&) = delete;
				~Camera();

				void Initialize();
				void Update();

				Vector3f position;
				Vector3f target;
				Vector3f up;
				Vector3f side;

				Matrix4 viewMatrix;
				Matrix4 projectionMatrix;
};


#endif
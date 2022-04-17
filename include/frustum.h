
#ifndef __FRUSTUM_H__
#define __FRUSTUM_H__ 1

#include "vector3d.h"
#include "matrix.h"
#include "geometry.h"

struct Plane {
				Vector3f n;
				float D;

				float distance(const Vector3f &r);
				void setNormalAndPoint(const Vector3f &mN, const Vector3f &p0);
};

struct AABox {
				Vector3f minBoundary;
				Vector3f maxBoundary;

				void generateAABB(const Geometry &geo);
				void updateBoundaries(const Matrix4 &modelMat);
};

class Frustum {

public:
				Frustum(float mFov, float mAR, float mNear, float mFar);
				~Frustum();
				Frustum(const Frustum&) = delete;

				static enum {OUTSIDE, INTERSECT, INSIDE};
				float fov, AR, near, far, nearH, nearW;
				Plane pl[6];

				void SetCameraInternals();
				void UpdatePlanes(Matrix4 &viewMat, const Vector3f &cameraPos);
				//int pointInFrustum(const Vector3f& p);
				//int boxInFrustum(BoundaryBox &b)

private:

				enum {
								TOP = 0, BOTTOM, LEFT, RIGHT, NEARP, FARP
				};

};

#endif
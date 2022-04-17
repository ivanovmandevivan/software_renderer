
#include "frustum.h"
#include <limits>

#define PI 3.14159265359

float Plane::distance(const Vector3f& r)
{
				return n.dotProduct(r) + D;
}

void Plane::setNormalAndPoint(const Vector3f& mN, const Vector3f& p0)
{
				n = mN;
				D = -(n.dotProduct(p0));
}

Frustum::Frustum(float mFov, float mAR, float mNear, float mFar) {
				fov = mFov;
				AR = mAR;
				near = mNear;
				far = mFar;
				nearH = 0.0f;
				nearW = 0.0f;
}

Frustum::~Frustum() {}

void Frustum::SetCameraInternals()
{
				float tanHalfFOV = tanf((fov * 0.5f) * (PI / 180.0f));
				nearH = near * tanHalfFOV;
				nearW = nearH * AR;
}

void Frustum::UpdatePlanes(Matrix4& viewMat, const Vector3f& cameraPos)
{
				SetCameraInternals();
				Vector3f rightVector = Vector3f(viewMat(0, 0), viewMat(0, 1), viewMat(0, 2));
				Vector3f upVector = Vector3f(viewMat(1, 0), viewMat(1, 1), viewMat(1, 2));
				Vector3f forwardVector = Vector3f(viewMat(2, 0), viewMat(2, 1), viewMat(2, 2));

				Vector3f nearCenter = cameraPos - (forwardVector * near);
				Vector3f farCenter = cameraPos - (forwardVector * far);

				Vector3f normal;
				Vector3f point;

				point = nearCenter + (upVector * nearH);
				normal = (point - cameraPos).normalized();
				normal = normal.crossProduct(rightVector);
				pl[TOP].setNormalAndPoint(normal, point);

				point = nearCenter - (upVector * nearH);
				normal = (point - cameraPos).normalized();
				normal = normal.crossProduct(rightVector);
				pl[BOTTOM].setNormalAndPoint(normal, point);

				point = nearCenter - (rightVector * nearW);
				normal = (point - cameraPos).normalized();
				normal = normal.crossProduct(upVector);
				pl[LEFT].setNormalAndPoint(normal, point);


				point = nearCenter + (rightVector * nearW);
				normal = (point - cameraPos).normalized();
				normal = normal.crossProduct(upVector);
				pl[RIGHT].setNormalAndPoint(normal, point);

				pl[NEARP].setNormalAndPoint(-forwardVector, nearCenter);
				pl[FARP].setNormalAndPoint(forwardVector, farCenter);
}

void AABox::generateAABB(const Geometry& geo)
{
				Vector3f tmpMin(std::numeric_limits<float>::min());
				Vector3f tmpMax(std::numeric_limits<float>::max());

				for (int i = 0; i < geo.numVertices; ++i) {
								for (int axis = 0; axis < 3; ++axis) {
												tmpMax.data[axis] = std::max(geo.vertices[i].data[axis], tmpMax.data[axis]);
												tmpMin.data[axis] = std::min(geo.vertices[i].data[axis], tmpMin.data[axis]);
								}
				}
				minBoundary = tmpMin;
				maxBoundary = tmpMax;
}

void AABox::updateBoundaries(const Matrix4& modelMat)
{
				Vector3f boundaryVerts[8];
				boundaryVerts[0] = Vector3f(minBoundary.x, minBoundary.y, minBoundary.z);
				boundaryVerts[1] = Vector3f(maxBoundary.x, minBoundary.y, minBoundary.z);
				boundaryVerts[2] = Vector3f(minBoundary.x, maxBoundary.y, minBoundary.z);
				boundaryVerts[3] = Vector3f(maxBoundary.x, maxBoundary.y, minBoundary.z);
				boundaryVerts[4] = Vector3f(minBoundary.x, maxBoundary.y, maxBoundary.z);
				boundaryVerts[5] = Vector3f(minBoundary.x, minBoundary.y, maxBoundary.z);
				boundaryVerts[6] = Vector3f(maxBoundary.x, minBoundary.y, maxBoundary.z);
				boundaryVerts[7] = Vector3f(maxBoundary.x, maxBoundary.y, maxBoundary.z);

				Vector3f tmpMin(std::numeric_limits<float>::min());
				Vector3f tmpMax(std::numeric_limits<float>::max());

				// Iterate through bounding box:
				for (int i = 0; i < 8; ++i) {

								for (int axis = 0; axis < 3; ++axis) {
												tmpMin.data[axis] = std::min(boundaryVerts[i].data[axis], tmpMin.data[axis]);
												tmpMax.data[axis] = std::max(boundaryVerts[i].data[axis], tmpMax.data[axis]);
								}
				}

				minBoundary = tmpMin;
				maxBoundary = tmpMax;
}

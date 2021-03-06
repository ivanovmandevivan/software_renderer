
#ifndef __MODEL_H__
#define __MODEL_H__ 1

#include "geometry.h"
#include "frustum.h"
#include "matrix.h"

class Model {

public:
				Model(const std::string filePath, const Vector3f& translation = Vector3f(0.0f), const Vector3f& rotation = Vector3f(0.0f), const Vector3f& scale = Vector3f(1.0f));
				~Model();
				Model(const Model&) = delete;

				void update(float rot);

				Geometry *getGeometry();
				Matrix4 *getModelMatrix();
				AABox *getBoundaryBox();

private:

				Geometry baseGeo;
				Matrix4 modelMatrix;
				AABox boundaryBox;
};

#endif

#include "model.h"
#include "obj_loader.h"

Model::Model(const std::string filePath, const Vector3f& translation, const Vector3f& rotation, const Vector3f& scale) {
				
				if (!OBJLoader::loadOBJ(baseGeo, filePath)) {
								printf("Model with path: %s could not be loaded correctly!\n", filePath.c_str());
				}
				modelMatrix = Matrix4::transformMat(translation, rotation, scale);
}

Model::~Model() {}

Geometry* Model::getGeometry()
{
				return &baseGeo;
}

Matrix4* Model::getModelMatrix()
{
				return &modelMatrix;
}

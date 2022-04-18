
#include "model.h"
#include "obj_loader.h"

Model::Model(const std::string filePath, const Vector3f& translation, const Vector3f& rotation, const Vector3f& scale) {
				
				if (!OBJLoader::loadOBJ(baseGeo, filePath)) {
								printf("Model with path: %s could not be loaded correctly!\n", filePath.c_str());
				}
				boundaryBox.generateAABB(baseGeo);
				baseGeo.buildFaceNormals();
				modelMatrix = Matrix4::transformMat(translation, rotation, scale);
}

Model::~Model() {}

void Model::update(float rot)
{
				modelMatrix = Matrix4::transformMat(Vector3f(0.0f), Vector3f(0.0f, rot * (PI / 180.0f), 0.0f));
				boundaryBox.updateBoundaries(modelMatrix);
}

Geometry* Model::getGeometry()
{
				return &baseGeo;
}

Matrix4* Model::getModelMatrix()
{
				return &modelMatrix;
}

AABox* Model::getBoundaryBox()
{
				return &boundaryBox;
}

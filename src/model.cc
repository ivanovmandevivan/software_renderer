
#include "model.h"
#include "obj_loader.h"

Model::Model(const std::string filePath) {
				
				if (!OBJLoader::loadOBJ(baseGeo, filePath)) {
								printf("Model with path: %s could not be loaded correctly!\n", filePath);
				}
}

Model::~Model() {}

Geometry* Model::getGeometry()
{
				return &baseGeo;
}

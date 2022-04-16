
#ifndef __MODEL_H__
#define __MODEL_H__ 1

#include "geometry.h"

class Model {

public:
				Model(const std::string filePath);
				~Model();
				Model(const Model&) = delete;

				Geometry *getGeometry();

private:

				Geometry baseGeo;
};

#endif
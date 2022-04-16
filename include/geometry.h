
#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__ 1

#include <vector>
#include "platform_types.h"
#include "vector3d.h"

class Geometry {

public:
				Geometry();
				~Geometry();
				Geometry(const Geometry&) = delete;

				void debugVertices();

				inline s32 getNumVertices() const {
								return vertices.size();
				}

				inline s32 getNumUVs() const {
								return uvs.size();
				}

				inline s32 getNumNormals() const {
								return normals.size();
				}

				s32 numVertices = 0;
				std::vector<Vector3f> vertices;
				std::vector<Vector3f> uvs;
				std::vector<Vector3f> normals;

				s32 numFaces = 0;
				std::vector<Vector3i> vertexIndices;
				std::vector<Vector3i> uvIndices;
				std::vector<Vector3i> normalsIndices;
};


#endif
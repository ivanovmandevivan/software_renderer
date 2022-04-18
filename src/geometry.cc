
#include "geometry.h"

Geometry::Geometry() {}
Geometry::~Geometry() {}

void Geometry::debugVertices()
{
				printf("\n==== VERTICES ==== \n");
				for (int i = 0; i < vertices.size(); ++i) {
								printf("Vertex: x:%f,y:%f,z:%f\n", vertices[i].x, vertices[i].y, vertices[i].z);
				}
				printf("\n==== VERTICES INDICES ==== \n");
				for (int i = 0; i < vertexIndices.size(); ++i) {
								printf("Vi: x:%d,y:%d,z:%d\n", vertexIndices[i].x, vertexIndices[i].y, vertexIndices[i].z);
				}

}

void Geometry::buildFaceNormals()
{
				for (int i = 0; i < numFaces; ++i) {
								Vector3i indices = vertexIndices[i];
								Vector3f normalOne = vertices[indices.data[1]] - vertices[indices.data[0]];
								Vector3f normalTwo = vertices[indices.data[2]] - vertices[indices.data[0]];
								faceNormals.push_back((normalOne.crossProduct(normalTwo)).normalized());
				}
}


#include "geometry.h"

Geometry::Geometry() {}
Geometry::~Geometry() {}

void Geometry::debugVertices()
{
				for (int i = 0; i < vertices.size(); ++i) {
								printf("Vertex: x:%f,y:%f,z:%f\n", vertices[i].x, vertices[i].y, vertices[i].z);
				}
}

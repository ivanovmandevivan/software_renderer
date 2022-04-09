
#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__ 1

#include <platform_types.h>
#include "buffer.h"
#include "vector3D.h"

class Primitive {

public:
				Primitive();
				~Primitive();

				void DrawScanBuffer(int height, int xMin, int xMax);
				void FillShape(Buffer<u32>* buffer, int yMin, int yMax);
				void FillTriangle(Buffer<u32>* buffer, Vector3f &v1, Vector3f &v2, Vector3f &v3);

				void ScanConvertLine(const Vector3f &minYVert, const Vector3f &maxYVert, int side);
				void ScanConvertTriangle(const Vector3f &minYVert, const Vector3f &midYVert, const Vector3f &maxYVert, int side);

private:
				u32 *scanBuffer;

};


#endif

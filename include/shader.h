
#ifndef __SHADER_H__
#define __SHADER_H__ 1

#include "vector3d.h"
#include "matrix.h"

struct IShader {
				virtual ~IShader() {};
				virtual Vector3f vertex(const Vector3f &vert, const Vector3f &normal, const Vector3f &uvVals, int index) = 0;
				virtual Vector3f fragment(const Vector3f &uv) = 0;
};

struct BaseShader : public IShader {
				Matrix4 modelViewProjection, modelView, view;
				float intensity;

				Vector3f whiteColor = Vector3f(255.0f, 255.0f, 255.0f);

				Vector3f vertex(const Vector3f& vertex, const Vector3f& normal, const Vector3f& uvVals, int index) override
				{
								return modelViewProjection.matMultVec(vertex);
				}

				Vector3f fragment(const Vector3f& uv) override {
								return whiteColor * intensity;
				}
};


#endif
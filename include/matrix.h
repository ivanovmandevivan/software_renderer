
#ifndef __MATRIX_H__
#define __MATRIX_H__ 1

#include "vector3d.h"


class Matrix4 {

public:
				Matrix4() {
								for (int i = 0; i < 16; ++i) {
												m[i] = 0.0f;
								}
				};
				~Matrix4() {};

				// Column Major Index Retrieving: [Memory is stored as Row Major because it's a linear buffer]
				inline float& operator()(size_t y, size_t x) {
								return m[y * 4 + x];
				}
				inline Matrix4 operator*(Matrix4& other) {
								Matrix4 result;
								int n = 4;
								for (int row = 0; row < n; ++row) {
												for (int col = 0; col < n; ++col) {
																float total = 0.0f;

																for (int sub = 1; sub < n + 1; ++sub) {
																				int rowL = row; // Row Idx in LeftM;
																				int colL = sub - 1; // Col Idx in LeftM;
																				int rowR = sub - 1; // Row Idx in RightM;
																				int colR = col; // Col Idx in RightM;

																				total += (*this)(rowL, colL) * other(rowR, colR);
																}
																result(row, col) = total;
												}
								}
								return result;
				}

				inline Vector3f matMultVec(const Vector3f& vec) {
								Vector3f newVec = Vector3f(0.0f, 0.0f, 1.0f);
								float w2 = 0.0f;

								newVec.x = vec.x * (*this)(0, 0) + 
																			vec.y * (*this)(0, 1) + 
																			vec.z * (*this)(0, 2) + 
																			(*this)(0, 3); // W is always 1.0
								
								newVec.y = vec.x * (*this)(1, 0) + 
																			vec.y * (*this)(1, 1) + 
																			vec.z * (*this)(1, 2) + 
																			(*this)(1, 3); // W is always 1.0
								
								newVec.z = vec.x * (*this)(2, 0) + 
																			vec.y * (*this)(2, 1) + 
																			vec.z * (*this)(2, 2) + 
																			(*this)(2, 3); // W is always 1.0
								
								w2 = vec.x * (*this)(3, 0) + 
													vec.y * (*this)(3, 1) + 
													vec.z * (*this)(3, 2) + 
													(*this)(3, 3); // -Pz when multiplied with -1 from the projection.
								
								newVec.w = w2;

								//newVec.x = (*this)(0, 0) * vec.x + (*this)(0, 1) * vec.y + (*this)(0, 2) * vec.z + (*this)(0, 3) * vec.w;
								//newVec.y = (*this)(1, 0) * vec.x + (*this)(1, 1) * vec.y + (*this)(1, 2) * vec.z + (*this)(1, 3) * vec.w;
								//newVec.z = (*this)(2, 0) * vec.x + (*this)(2, 1) * vec.y + (*this)(2, 2) * vec.z + (*this)(2, 3) * vec.w;
								//w2 = (*this)(3, 0) * vec.x + (*this)(3, 1) * vec.y + (*this)(3, 2) * vec.z + (*this)(3, 3) * vec.w;

								//newVec.w = w2;

								return newVec;
				}

				inline Vector3f matMultDir(const Vector3f& vec) {
								Vector3f newVec = Vector3f(0.0f, 0.0f, 0.0f);

								newVec.x = vec.x * (*this)(0, 0) + vec.y * (*this)(0, 1) + vec.z * (*this)(0, 2);
								newVec.y = vec.y * (*this)(1, 0) + vec.y * (*this)(1, 1) + vec.z * (*this)(1, 2);
								newVec.z = vec.z * (*this)(2, 0) + vec.y * (*this)(2, 1) + vec.z * (*this)(2, 2);

								return newVec;
				}

				inline Matrix4 transpose() {
								Matrix4 transposedMat;

								// First Row
								transposedMat(0, 0) = (*this)(0, 0);
								transposedMat(0, 1) = (*this)(1, 0);
								transposedMat(0, 2) = (*this)(2, 0);
								transposedMat(0, 3) = (*this)(3, 0);

								// Second Row;
								transposedMat(1, 0) = (*this)(0, 1);
								transposedMat(1, 1) = (*this)(1, 1);
								transposedMat(1, 2) = (*this)(2, 1);
								transposedMat(1, 3) = (*this)(3, 1);

								// Third Row;
								transposedMat(2, 0) = (*this)(0, 2);
								transposedMat(2, 1) = (*this)(1, 2);
								transposedMat(2, 2) = (*this)(2, 2);
								transposedMat(2, 3) = (*this)(3, 2);

								// Fourth Row;
								transposedMat(3, 0) = (*this)(0, 3);
								transposedMat(3, 1) = (*this)(1, 3);
								transposedMat(3, 2) = (*this)(2, 3);
								transposedMat(3, 3) = (*this)(3, 3);

								return transposedMat;
				}

				// @ https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
				// @ Taken from Mesa GLU Inverse() Implementation
				inline Matrix4 inverse() {
								Matrix4 inverseMat;
								float det = 0.0f;

								inverseMat(0, 0) = m[5] * m[10] * m[15] -
																												m[5] * m[11] * m[14] -
																												m[9] * m[6] * m[15] +
																												m[9] * m[7] * m[14] +
																												m[13] * m[6] * m[11] -
																												m[13] * m[7] * m[10];

								inverseMat(1, 0) = -m[4] * m[10] * m[15] +
																												m[4] * m[11] * m[14] +
																												m[8] * m[6] * m[15] -
																												m[8] * m[7] * m[14] -
																												m[12] * m[6] * m[11] +
																												m[12] * m[7] * m[10];

								inverseMat(2, 0) = m[4] * m[9] * m[15] -
																												m[4] * m[11] * m[13] -
																												m[8] * m[5] * m[15] +
																												m[8] * m[7] * m[13] +
																												m[12] * m[5] * m[11] -
																												m[12] * m[7] * m[9];

								inverseMat(3, 0) = -m[4] * m[9] * m[14] +
																												m[4] * m[10] * m[13] +
																												m[8] * m[5] * m[14] -
																												m[8] * m[6] * m[13] -
																												m[12] * m[5] * m[10] +
																												m[12] * m[6] * m[9];

								inverseMat(0, 1) = -m[1] * m[10] * m[15] +
																												m[1] * m[11] * m[14] +
																												m[9] * m[2] * m[15] -
																												m[9] * m[3] * m[14] -
																												m[13] * m[2] * m[11] +
																												m[13] * m[3] * m[10];

								inverseMat(1, 1) = m[0] * m[10] * m[15] -
																												m[0] * m[11] * m[14] -
																												m[8] * m[2] * m[15] +
																												m[8] * m[3] * m[14] +
																												m[12] * m[2] * m[11] -
																												m[12] * m[3] * m[10];

								inverseMat(2, 1) = -m[0] * m[9] * m[15] +
																												m[0] * m[11] * m[13] +
																												m[8] * m[1] * m[15] -
																												m[8] * m[3] * m[13] -
																												m[12] * m[1] * m[11] +
																												m[12] * m[3] * m[9];

								inverseMat(3, 1) = m[0] * m[9] * m[14] -
																												m[0] * m[10] * m[13] -
																												m[8] * m[1] * m[14] +
																												m[8] * m[2] * m[13] +
																												m[12] * m[1] * m[10] -
																												m[12] * m[2] * m[9];

								inverseMat(0, 2) = m[1] * m[6] * m[15] -
																												m[1] * m[7] * m[14] -
																												m[5] * m[2] * m[15] +
																												m[5] * m[3] * m[14] +
																												m[13] * m[2] * m[7] -
																												m[13] * m[3] * m[6];

								inverseMat(1, 2) = -m[0] * m[6] * m[15] +
																												m[0] * m[7] * m[14] +
																												m[4] * m[2] * m[15] -
																												m[4] * m[3] * m[14] -
																												m[12] * m[2] * m[7] +
																												m[12] * m[3] * m[6];

								inverseMat(2, 2) = m[0] * m[5] * m[15] -
																												m[0] * m[7] * m[13] -
																												m[4] * m[1] * m[15] +
																												m[4] * m[3] * m[13] +
																												m[12] * m[1] * m[7] -
																												m[12] * m[3] * m[5];

								inverseMat(3, 2) = -m[0] * m[5] * m[14] +
																												m[0] * m[6] * m[13] +
																												m[4] * m[1] * m[14] -
																												m[4] * m[2] * m[13] -
																												m[12] * m[1] * m[6] +
																												m[12] * m[2] * m[5];

								inverseMat(0, 3) = -m[1] * m[6] * m[11] +
																												m[1] * m[7] * m[10] +
																												m[5] * m[2] * m[11] -
																												m[5] * m[3] * m[10] -
																												m[9] * m[2] * m[7] +
																												m[9] * m[3] * m[6];

								inverseMat(1, 3) = m[0] * m[6] * m[11] -
																												m[0] * m[7] * m[10] -
																												m[4] * m[2] * m[11] +
																												m[4] * m[3] * m[10] +
																												m[8] * m[2] * m[7] -
																												m[8] * m[3] * m[6];

								inverseMat(2, 3) = -m[0] * m[5] * m[11] +
																												m[0] * m[7] * m[9] +
																												m[4] * m[1] * m[11] -
																												m[4] * m[3] * m[9] -
																												m[8] * m[1] * m[7] +
																												m[8] * m[3] * m[5];

								inverseMat(3, 3) = m[0] * m[5] * m[10] -
																												m[0] * m[6] * m[9] -
																												m[4] * m[1] * m[10] +
																												m[4] * m[2] * m[9] +
																												m[8] * m[1] * m[6] -
																												m[8] * m[2] * m[5];

								det = m[0] * inverseMat(0, 0) + m[1] * inverseMat(1, 0) + m[2] * inverseMat(2, 0) + m[3] * inverseMat(3, 0);
								det = 1.0f / det;

								for (int i = 0; i < 4; ++i) {
												for (int j = 0; j < 4; ++j) {
																inverseMat(i, j) = inverseMat(i, j) * det;
												}
								}

								return inverseMat;
				}

				inline static Matrix4 identity() {
								Matrix4 identityMat;



								identityMat(0, 0) = 1.0f;
								identityMat(1, 1) = 1.0f;
								identityMat(2, 2) = 1.0f;
								identityMat(3, 3) = 1.0f;

								return identityMat;
				}

				inline static Matrix4 testMat() {
								Matrix4 testMat;
								int n = 4;
								int val = 1;
								for (int row = 0; row < n; ++row) {
												for (int col = 0; col < n; ++col) {
																testMat(row, col) = val;
																++val;
												}
								}
								return testMat;
				}

				// ZYX Rotation
				inline static Matrix4 rotMat(float rotX, float rotY, float rotZ) {
								Matrix4 rotationMatrix = Matrix4::identity();

								float cosX = cos(rotX);
								float sinX = sin(rotX);

								float cosY = cos(rotY);
								float sinY = sin(rotY);

								float cosZ = cos(rotZ);
								float sinZ = sin(rotZ);

								// First Row;
								rotationMatrix(0, 0) = cosY * cosZ;
								rotationMatrix(0, 1) = -cosX * sinZ + sinX * sinY * cosZ;
								rotationMatrix(0, 2) = sinX * sinZ + cosX * sinY * cosZ;

								// Second Row;
								rotationMatrix(1, 0) = cosX * sinZ;
								rotationMatrix(1, 1) = cosX * cosZ + sinX * sinY * sinZ;
								rotationMatrix(1, 2) = -sinX * cosZ + cosX * sinY * sinZ;

								// Third Row;
								rotationMatrix(2, 0) =		-sinY;
								rotationMatrix(2, 1) = sinX * cosY;
								rotationMatrix(2, 2) = cosX * cosY;

								// Fourth Row;
								rotationMatrix(3, 3) = 1;

								return rotationMatrix;
				}

				inline static Matrix4 scaleMat(float scaleX, float scaleY, float scaleZ) {
								Matrix4 scaleMatrix = Matrix4::identity();
								scaleMatrix(0, 0) = scaleX;
								scaleMatrix(1, 1) = scaleY;
								scaleMatrix(2, 2) = scaleZ;
								scaleMatrix(3, 3) = 1.0f;

								return scaleMatrix;
				}

				inline static Matrix4 translateMat(float dx, float dy, float dz) {
								Matrix4 translateMatrix = Matrix4::identity();

								// We internally set scale matrix to 1.0f default.
								translateMatrix(0, 0) = 1.0f;
								translateMatrix(1, 1) = 1.0f;
								translateMatrix(2, 2) = 1.0f;

								translateMatrix(3, 0) = dx;
								translateMatrix(3, 1) = dy;
								translateMatrix(3, 2) = dz;
								translateMatrix(3, 3) = 1.0f;

								return translateMatrix;
				}

				inline static Matrix4 transformMat(Vector3f& translate, Vector3f& rotation, Vector3f& scale = Vector3f(1.0f, 1.0f, 1.0f)) {
								Matrix4 rotMatrix = Matrix4::rotMat(rotation.x, rotation.y, rotation.z);
								Matrix4 scaleMatrix = Matrix4::scaleMat(scale.x, scale.y, scale.z);
								Matrix4 translateMatrix = Matrix4::translateMat(translate.x, translate.y, translate.z);
								
								Matrix4 tmp = (rotMatrix * scaleMatrix);
								return translateMatrix * tmp; // TRS
				}

				inline static Matrix4 lookAt(Vector3f& eye, Vector3f& at, Vector3f& tmp) {
								Matrix4 viewMat;

								Vector3f forward = (at - eye).normalized();
								Vector3f side = (tmp.crossProduct(forward)).normalized();
								Vector3f up = forward.crossProduct(side);

								// First Row
								viewMat(0, 0) = side.x;
								viewMat(0, 1) = side.y;
								viewMat(0, 2) = side.z;
								viewMat(0, 3) = -side.dotProduct(eye);

								// Second Row
								viewMat(1, 0) = up.x;
								viewMat(1, 1) = up.y;
								viewMat(1, 2) = up.z;
								viewMat(1, 3) = -up.dotProduct(eye);

								// Third Row
								viewMat(2, 0) = forward.x;
								viewMat(2, 1) = forward.y;
								viewMat(2, 2) = forward.z;
								viewMat(2, 3) = -forward.dotProduct(eye);

								// Fourth Row
								viewMat(3, 3) = 1.0f;

								return viewMat;
				}

				inline static Matrix4 projectionMat(float fov, float ar, float near, float far) {
								Matrix4 projMatrix = Matrix4::identity();
								
								/*projMatrix(0, 0) = 1 / (ar * tan(fov * 0.5));
								projMatrix(1, 1) = 1 / tan(fov * 0.5);
								projMatrix(2, 2) = (near + far) / (near - far);
								projMatrix(3, 2) = (2 * far * near) / (near - far);
								projMatrix(2, 3) = 1;
								projMatrix(3, 3) = 0;*/


								float tanHalfFOVInverse = 1.0f / tanf((fov * 0.5f) * (M_PI / 180.0f));
								projMatrix(0, 0) = tanHalfFOVInverse;
								projMatrix(1, 1) = ar * tanHalfFOVInverse;
								projMatrix(2, 2) = (near) / (far - near);
								projMatrix(2, 3) = (far * near) / (far - near);
								projMatrix(3, 2) = -1.0f;
								projMatrix(3, 3) = 0.0f;

								//float tanHalfFOV = tanf(fov * 0.5f);
								//float zRange = near - far;

								//projMatrix(0, 0) = 1.0f / (tanHalfFOV * ar);
								//projMatrix(1, 1) = 1.0f / tanHalfFOV;
								//projMatrix(2, 2) = (-near - far) / zRange;
								//projMatrix(2, 3) = 2 * far * near / zRange;
								//projMatrix(3, 2) = 1.0f;
								//projMatrix(3, 3) = 0.0f;

								return projMatrix;
				}

				inline static Matrix4 orthoMat(float right, float left, float top, float bottom, float near, float far) {
								Matrix4 orthoMat;

								orthoMat(0,0) = 2.0f / (right - left);
								orthoMat(3, 0) -((right + left) / (right - left));
								orthoMat(1, 1) = 2.0f / (top - bottom);
								orthoMat(3, 1) = -((top + bottom) / (top - bottom));
								orthoMat(2, 2) = 2.0f / (far - near);
								orthoMat(3, 2) = -((far + near)/(far - near));

								return orthoMat;
				}

				inline static Matrix4 screenSpaceTransformMat(float halfWidth, float halfHeight) {
								Matrix4 screenSpaceMat = Matrix4::identity();
								
								screenSpaceMat(0, 0) = halfWidth;
								screenSpaceMat(3, 0) = halfWidth;
								screenSpaceMat(1, 1) = halfHeight;
								screenSpaceMat(3, 1) = halfHeight;

								return screenSpaceMat;
				}

				// Normalize NDC range from -1, 1 to 0, 1 and map to screen spaace with width & height.
				inline static Vector3f NDCToScreenSpace(Vector3f& vert, int width, int height) {
								Vector3f res = Vector3f(0.0f, 0.0f, 0.0f);

								res.x = floor(0.5f * width * (vert.x + 1));
								res.y = floor(0.5f * height * (vert.y + 1));
								res.z = vert.z;
								res.w = vert.w;

								return res;
				}

				inline void print() {
								int n = 4;
								for (int row = 0; row < n; ++row) {
												for (int col = 0; col < n; ++col) {
																float val = (*this)(row, col);
																printf("%f\t", val);
												}
												printf("\n");
								}
								printf("\n");
				}
				
private:
				float m[16];

};

#endif
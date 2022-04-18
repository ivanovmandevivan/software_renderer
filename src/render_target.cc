
#include <stdio.h>
#include "render_target.h"
#include "rasterizer.h"
#include "shader.h"

RenderTarget::RenderTarget() {}

RenderTarget::~RenderTarget() {}

bool RenderTarget::Initialize(int width, int height)
{
				if (!createBuffers(width, height)) {
								return false;
				}

				startUpComplete = true;
				return startUpComplete;
}

void RenderTarget::Shutdown()
{
				if (startUpComplete) {
								delete pixelBuffer;
				}
}

void RenderTarget::drawTriangularMesh(Model* model)
{
				Geometry *geoCaptured = model->getGeometry();
				std::vector<Vector3i> *vertexIndices = &geoCaptured->vertexIndices;
				std::vector<Vector3i> *uvIndices = &geoCaptured->uvIndices;
				std::vector<Vector3i> *normalIndices = &geoCaptured->normalsIndices;
				std::vector<Vector3f> *faceNormals = &geoCaptured->faceNormals;

				std::vector<Vector3f> *vertices = &geoCaptured->vertices;
				std::vector<Vector3f> *uvs = &geoCaptured->uvs;
				std::vector<Vector3f> *normals = &geoCaptured->normals;
				int numFaces = geoCaptured->numFaces;


				BaseShader shader;
				shader.modelView = (camera->viewMatrix) * (*(model->getModelMatrix()));
				shader.modelViewProjection = (camera->projectionMatrix) * shader.modelView;
				shader.view = camera->viewMatrix;

				Matrix4 objectSpaceMatrix = (*model->getModelMatrix()).inverse();
				int count = 0;

				for (int j = 0; j < numFaces; ++j) {

								Vector3i f = (*vertexIndices)[j];
								Vector3i n = (*normalIndices)[j];
								Vector3i u = (*uvIndices)[j];

								Vector3f trianglePrimitive[3];
								packDataIntoTris(f, trianglePrimitive, *vertices);
								
								// Backface Culling
								if (backfaceCull((*faceNormals)[j], trianglePrimitive[0], objectSpaceMatrix)) {
												continue; // We exclude parallel faces too, so we only cull the ones that are < 0 as far as normal to eye camera pos angle.
								}

								// Vertex Shader:
								for (int i = 0; i < 3; ++i) {
												trianglePrimitive[i] = shader.vertex(trianglePrimitive[i], (*normals)[i], (*uvs)[i], i);
								}

								// Clipping Faces Against the View Volume
								for (int i = 0; i < 3; ++i) {
												Vector3f testingVertex = trianglePrimitive[i];
												bool isInside = (-testingVertex.w <= testingVertex.x <= testingVertex.w)
																&& (-testingVertex.w <=  testingVertex.y <= testingVertex.w)
																&& (0 <= testingVertex.z <= testingVertex.w);
												if (!isInside) ++count;
								}
								if (count == 3) continue;

								// Perspective Divide
								for (int i = 0; i < 3; ++i) {
												trianglePrimitive[i].perspectiveDivide();
								}


								//Rasterizer::drawWireframe(pixelBuffer, trianglePrimitive);
								Rasterizer::drawTriangle3D(pixelBuffer, shader, trianglePrimitive);
				}


}

bool RenderTarget::backfaceCull(const Vector3f& normalFace, const Vector3f& vert, Matrix4& objectMatrix)
{
				Vector3f viewDirection = objectMatrix.matMultVec(camera->position) - vert; // Get view direction towards object in object space (we transform camera position to object)
				viewDirection.normalized();
				return normalFace.dotProduct(viewDirection) >= 0.0f;
}

Buffer<u32>* RenderTarget::getRenderTarget()
{
				return pixelBuffer;
}

void RenderTarget::clearBuffers()
{
				pixelBuffer->Clear(0x00);
}

void RenderTarget::setRenderTargetCamera(Camera* camera)
{
				this->camera = camera;
}

bool RenderTarget::createBuffers(int w, int h)
{
				u32 pixelCount = w * h;
				bool isSuccessful = true;
				pixelBuffer = new Buffer<u32>(w, h, new u32[pixelCount]);
				if (pixelBuffer == nullptr) {
								printf("Could not build pixel buffer. [Renderer].\n");
								isSuccessful = false;
				}

				return isSuccessful;
}

void RenderTarget::packDataIntoTris(Vector3i& index, Vector3f* primitive, std::vector<Vector3f>& vals)
{
				for (int i = 0; i < 3; ++i) {
								primitive[i] = vals[index.data[i]];
				}
}

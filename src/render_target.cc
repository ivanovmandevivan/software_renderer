
#include <stdio.h>
#include "render_target.h"
#include "rasterizer.h"

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

				std::vector<Vector3f> *vertices = &geoCaptured->vertices;
				std::vector<Vector3f> *uvs = &geoCaptured->uvs;
				std::vector<Vector3f> *normals = &geoCaptured->normals;
				int numFaces = geoCaptured->numFaces;




				for (int j = 0; j < numFaces; ++j) {

								Vector3i f = (*vertexIndices)[j];
								Vector3i n = (*normalIndices)[j];
								Vector3i u = (*uvIndices)[j];

								Vector3f trianglePrimitive[3];
								packDataIntoTris(f, trianglePrimitive, *vertices);
								for (int i = 0; i < 3; ++i) {
												trianglePrimitive[i].perspectiveDivide();
								}

								// Backface Culling
								// Clipping Faces Against the View Volume
								

								Rasterizer::drawWireframe(pixelBuffer, trianglePrimitive);
				}


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

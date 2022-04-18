
#include "obj_loader.h"

bool OBJLoader::loadOBJ(Geometry& geo, std::string filePath)
{
				if (!fileExists(filePath)) return false;
				std::ifstream file(filePath.c_str());

				std::string line = "";
				std::string key;
				Vector3f tempVertexData = Vector3f(0.0f, 0.0f, 0.0f);
				std::string x, y, z;
				Vector3i indices[3];

				char indices_token  = '/';
				while (!file.eof()) {
								std::getline(file, line);
								std::istringstream ss(line);

								ss >> key; 
								if (key == "v") { // Vertex
												ss >> tempVertexData.x >> tempVertexData.y >> tempVertexData.z;
												geo.vertices.push_back(tempVertexData);
								}
								else if (key == "vt") { // UV 
												ss >> tempVertexData.x >> tempVertexData.y >> tempVertexData.z;
												geo.normals.push_back(tempVertexData);
								}
								else if (key == "vn") { // Normal
												ss >> tempVertexData.x >> tempVertexData.y;
												geo.uvs.push_back(tempVertexData);
								}
								else if (key == "f") { // Face {Indices}

												ss >> x >> y >> z;
												std::vector<std::string> splitVertexIndex = stringTokenizer(x, indices_token);
												std::vector<std::string> splitVertexUVs = stringTokenizer(y, indices_token);
												std::vector<std::string> splitVertexNormals = stringTokenizer(z, indices_token);
												for (int i = 0; i < 3; ++i) {
																indices[i] = Vector3i(std::stoi(splitVertexIndex[i]) - 1, std::stoi(splitVertexUVs[i]) - 1, std::stoi(splitVertexNormals[i]) - 1);
												}
												geo.vertexIndices.push_back(indices[0]);
												geo.uvIndices.push_back(indices[1]);
												geo.normalsIndices.push_back(indices[2]);
								}
				}
				geo.numVertices = geo.vertices.size();
				geo.numFaces = geo.vertexIndices.size();

				file.clear();
				file.seekg(0, file.beg); // Reset SEEK_PTR to beginning of file.

				return true;
}

bool OBJLoader::fileExists(std::string& path)
{
				std::ifstream file(path.c_str());
				return file.good();
}

std::vector<std::string> OBJLoader::stringTokenizer(std::string& str, char delim)
{
				std::stringstream ss(str);
				std::string token;
				std::vector<std::string> splittedResult;
				while (std::getline(ss, token, delim)) {
								if (token == "") splittedResult.push_back("0"); // Debug, in case token is empty, put a zero.
								else {
												splittedResult.push_back(token);
								}
				}
				return splittedResult;
}

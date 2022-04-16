
#ifndef __OBJ_LOADER_H__
#define __OBJ_LOADER_H__ 1

#include <string>
#include <fstream>
#include <sstream>

#include "geometry.h"

class OBJLoader {

public:
				static bool loadOBJ(Geometry &geo, std::string filePath);
				static bool fileExists(std::string &path);
				static std::vector<std::string> stringTokenizer(std::string &str, char delim);

};


#endif
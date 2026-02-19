#pragma once

#include <fstream>
#include <sstream>
#include<libs/glad/include/glad/glad.h>

GLuint createShaderProgram(const std::string& vertexPath,
                           const std::string& fragmentPath);
#ifndef MESH_HPP
#define MESH_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <array>

#include <glm/glm.hpp>
#include "../shaders/shaders.hpp"
#include "../../Util/Logger.hpp"

#include "../options.hpp"

namespace mesh
{

    extern std::vector<GLuint> vao;
    extern std::vector<int> vaoVerticies;
    extern std::vector<GLuint> buffers; // identyfikatory obiektow VBO
    extern std::vector<float[8]> vertices;
    extern std::vector<GLenum> drawMode;

    extern GLuint shaderProgram;
    extern GLuint vertexLoc;
    extern GLuint colorLoc;

    bool addVao(std::vector<float> vertices, GLuint shaderProgram, GLenum mode);

    void drawVAO(GLenum mode);
    void drawVAO();

    void cleanup();

} // namespace mesh

#endif // MESH_HPP

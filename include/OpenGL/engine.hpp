#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <array>

#include "shaders/shaders.hpp"

#include "../Util/Logger.hpp"

#include "options.hpp"

using namespace options;

namespace engine
{
//******************************************************************************************
extern GLuint shaderProgram; // identyfikator programu cieniowania

extern GLuint vertexLoc; // lokalizacja atrybutu wierzcholka - wspolrzedne
extern GLuint colorLoc;  // lokalizacja atrybutu wierzcholka - kolor

extern std::array<GLuint, 2> vao;	   // identyfikatory obiektow VAO
extern std::array<GLuint, 3> buffers; // identyfikatory obiektow VBO

extern GLFWwindow *window;

//******************************************************************************************

void initEngine();
void draw();
void errorCallback(int error, const char *description);
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void cleanup();
void initGL();
void setupShaders();
void setupBuffers();
void renderScene();
void initGLEW();
void initGLFW();

void setPositionsAndColors();

void drawVAO(void (*)(GLuint array), size_t arraySize);



} // namespace engine

#endif // ENGINE_HPP

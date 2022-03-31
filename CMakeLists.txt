cmake_minimum_required(VERSION 3.11.0)

#rename Shaders to Your prefered project name
project(GenerativeArt LANGUAGES CXX VERSION 0.1.0)

#uncomment for CTests
#include(CTest)
#enable_testing()

#change for different executable path(why would You do that) root is build/ so '..' might be needed
set(BINARY_DIR ../bin)

# change  ${PROJECT_NAME} to prefered executable name if different from project name
add_executable(${PROJECT_NAME} main.cpp)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

#change CXX version as needed
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

set(CMAKE_CXX_FLAGS_DEBUG "-g -D DEBUG")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


#linking cpp and hpp files in includes/ and includes/*/ directories 
file(GLOB SOURCES
#    includes/*/*.hpp
#    includes/*/*.cpp
#    includes/*.hpp
#    includes/*.cpp
    includes/*.*
    includes/**/*.*
)
#file(GLOB SOURCES_DIRS
#    includes/**/[!.]
#)



SET (EXECUTABLE_OUTPUT_PATH ${BINARY_DIR})
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR})

# Flags to enable native support for PNG image files, using the PNG library.
# ( http://www.libpng.org/ )
SET(CIMG_PNG_CCFLAGS  -Dcimg_use_png)


set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)  


include(CPack)
#find_package(OpenGL REQUIRED)
#find_package(glm REQUIRED)
#find_package(GLEW REQUIRED)
#find_package(SDL2 REQUIRED)
#find_package(DevIL REQUIRED)
#find_package(glfw3 3.3 REQUIRED)
find_package(PNG REQUIRED)
find_package(Cairo REQUIRED)


#  ${X11_INCLUDE_DIR}  ${X11_LIBRARIES}  might be needed but i don't know yet
#SET(INCLUDE_DIRS ${OpenGL_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${Assimp_INCLUDE_DIRS} ${IL_INCLUDE_DIR} ${GLFW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${PNG_INCLUDE_DIR} includes)
#SET(LIBS ${LIBS} ${OpenGL_LIBRARIES} ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${Assimp_LIBRARIES} ${IL_LIBRARIES} ${ILU_LIBRARIES} ${ILUT_LIBRARIES} ${PNG_LIBRARY} ${GLFW_LIBRARIES} ${GLM_LIBRARIES})

SET(INCLUDE_DIRS ${Cairo_INCLUDE_DIRS} ${PNG_INCLUDE_DIR} includes)
SET(LIBS ${LIBS} ${Cairo_LIBRARIES} ${GLM_LIBRARIES})

include_directories(${INCLUDE_DIRS}) 
#include_directories(${INCLUDE_DIRS} ${SOURCES_DIRS})

target_link_libraries(${PROJECT_NAME} ${SOURCES} ${LIBS} -lcairo -lX11)
#target_link_libraries(${PROJECT_NAME} ${LIBS} glfw -lGL)

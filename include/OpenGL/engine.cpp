#include "engine.hpp"
namespace engine
{
	//******************************************************************************************
	GLuint shaderProgram; // identyfikator programu cieniowania

	GLuint vertexLoc; // lokalizacja atrybutu wierzcholka - wspolrzedne
	GLuint colorLoc;  // lokalizacja atrybutu wierzcholka - kolor

	GLFWwindow *window;
	//******************************************************************************************

	void initEngine(int width, int height)
	{
		engine::initGLFW(width, height);
		engine::initGLEW();
		engine::initGL();
	}

	void draw()
	{

		// glowna petla programu
		while (!glfwWindowShouldClose(window))
		{
			renderScene();

			glfwSwapBuffers(window); // zamieniamy bufory
			glfwPollEvents();		 // przetwarzanie zdarzen
		}
	}

	void initGLFW(int width, int height)
	{
		glfwSetErrorCallback(engine::errorCallback); // rejestracja funkcji zwrotnej do obslugi bledow

		if (!glfwInit()) // inicjacja biblioteki GLFW
			exit(EXIT_FAILURE);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // inicjacja wersji kontekstu
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // incicjacja profilu rdzennego

		glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
		
		window = glfwCreateWindow(width, height, "test", NULL, NULL); // utworzenie okna i zwiazanego z nim kontekstu
		if (!window)
		{
			glfwTerminate(); // konczy dzialanie biblioteki GLFW
			exit(EXIT_FAILURE);
		}

		glfwSetKeyCallback(window, keyCallback); // rejestracja funkcji zwrotnej do oblsugi klawiatury

		glfwMakeContextCurrent(window);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable( GL_BLEND );
	}

	void drawVAO(GLenum mode, GLuint Vao, size_t arraySize) {
		glBindVertexArray(Vao);
		glDrawArrays(mode, 0, arraySize);
	}


	void initGLEW()
	{
		// inicjacja GLEW
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			std::cerr << "Blad: " << glewGetErrorString(err) << std::endl;
			exit(1);
		}

		if (!GLEW_VERSION_3_3)
		{
			std::cerr << "Brak obslugi OpenGL 3.3\n";
			exit(2);
		}

		glfwSwapInterval(1); // v-sync on
	}

	/*------------------------------------------------------------------------------------------
	** funkcja zwrotna do obslugi bledow biblioteki GLFW
	** error - kod bledu
	** description - opis bledu
	**------------------------------------------------------------------------------------------*/
	void errorCallback(int error, const char *description)
	{
		std::cerr << "Error: " << description << std::endl;
	}

	/*------------------------------------------------------------------------------------------
	** funkcja zwrotna do obslugi klawiatury
	** window - okno, kt�re otrzymalo zdarzenie
	** key - klawisz jaki zostal nacisniety lub zwolniony
	** scancode - scancode klawisza specyficzny dla systemu
	** action - zachowanie klawisza (GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT)
	** mods - pole bitowe zawierajace informacje o nacisnietych modyfikatorach (GLFW_MOD_SHIFT, GLFW_MOD_CONTROL, GLFW_MOD_ALT, GLFW_MOD_SUPER)
	**------------------------------------------------------------------------------------------*/
	void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	/*------------------------------------------------------------------------------------------
	** funkcja inicjujaca ustawienia OpenGL
	**------------------------------------------------------------------------------------------*/
	void initGL()
	{
		std::cout << "GLEW = " << glewGetString(GLEW_VERSION) << std::endl;
		std::cout << "GL_VENDOR = " << glGetString(GL_VENDOR) << std::endl;
		std::cout << "GL_RENDERER = " << glGetString(GL_RENDERER) << std::endl;
		std::cout << "GL_VERSION = " << glGetString(GL_VERSION) << std::endl;
		std::cout << "GLSL = " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // kolor (RGBA) uzywany do czyszczenia bufora koloru
		setupShaders();
	}
	void setupShaders()
	{
		if (!shaders::setupShaders("shaders/basic/vertex.vert", "shaders/basic/fragment.frag", shaderProgram))
			exit(3);

		vertexLoc = glGetAttribLocation(shaderProgram, "vPosition");
		colorLoc = glGetAttribLocation(shaderProgram, "vColor");
		glUseProgram(shaderProgram);
		//GLint glViewport = glGetUniformLocation(shaderProgram, "glViewport");
		//glUniform2f(glViewport, options::WIN_WIDTH, options::WIN_HEIGHT);

	}

	/*------------------------------------------------------------------------------------------
	** funkcja rysujaca scene
	**------------------------------------------------------------------------------------------*/
	void renderScene()
	{

		glClear(GL_COLOR_BUFFER_BIT); // czyszczenie bufora koloru

		glUseProgram(shaderProgram); // wlaczenie programu cieniowania

	}
	
}
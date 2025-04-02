#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <glm/glm.hpp>

#include "shader.h"

struct Camera
{
	struct Viewport
	{
		int windowWidth = 500;
		int windowHeight = 500;
	};
	Viewport viewport;
};

struct InitReturn
{
	int failed;
	SDL_Window* window;
	SDL_GLContext gl_context;
	InitReturn(int failed = 0, SDL_Window* window = nullptr)
	{
		this->failed = failed;
		this->window = window;
		this->gl_context = nullptr;
	}
};

static InitReturn WindowInitialization(Camera& camera)
{
	InitReturn r;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return { -1 };
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_Window* window = SDL_CreateWindow("fgame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, camera.viewport.windowWidth, camera.viewport.windowHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN /*| SDL_WINDOW_MAXIMIZED*/);
	if (!window)
	{
		SDL_Quit();
		return { -1 };
	}
	SDL_SetWindowMinimumSize(window, 160 * 4, 90 * 4);
	r.gl_context = SDL_GL_CreateContext(window);
	if (!r.gl_context)
	{
		SDL_DestroyWindow(window);
		SDL_Quit();
		return { -1 };
	}
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "GLEW Initialization Failed: " << glewGetErrorString(glewInit()) << std::endl;
		SDL_GL_DeleteContext(r.gl_context);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return { -1 };
	}
	r.window = window;
	return r;
}

bool running = true;

int CheckForGLError(std::string fnName)
{
	fnName += ' ';

	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		std::cout << "OpenGL error after " << fnName << err << std::endl;
		return -1;
	}
	return 0;
}

int CheckForSuccess(unsigned int shader)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		switch (shader)
		{
		case GL_VERTEX_SHADER:
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			break;
		case GL_FRAGMENT_SHADER:
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
			break;
		case GL_LINK_STATUS:
			std::cout << "ERROR::LINK::STATUS::COMPILATION_FAILED\n" << infoLog << std::endl;
			break;
		}
		return -1;
	}
	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		switch (shader)
		{
		case GL_VERTEX_SHADER:
			std::cout << "VERTEX" << std::endl;
			break;
		case GL_FRAGMENT_SHADER:
			std::cout << "FRAGMENT" << std::endl;
			break;
		case GL_LINK_STATUS:
			std::cout << "LINKING" << std::endl;
			break;
		default:
			std::cout << "other" << std::endl;
			break;
		}
		std::cout << "OpenGL error: " << err << std::endl;
	}
	return success;
}

int CheckForLinking(unsigned int program)
{
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return -1;
	}
	return success;
}
int main()
{
	Camera camera;

#pragma region setup
	InitReturn r = WindowInitialization(camera);
	if (r.failed == -1) return -1;
	SDL_Window* window = r.window;
	SDL_GLContext& gl_context = r.gl_context;

	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGuiIO& io = ImGui::GetIO();

#pragma endregion setup

	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec2 aPos;\n"
		"layout (location = 1) in vec3 aCol;\n"
		"out vec3 Color;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, 1.0, 1.0);\n"
		"	Color = aCol;\n"
		"}\0";
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 Color;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(Color, 1.0f);"
		"}\0";
	//TODO: ZET DE SHADER IN EEN FILE

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	CheckForSuccess(vertexShader);

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	CheckForSuccess(fragmentShader);

	Shader defaultShader("resources/vertex.shader", "resources/fragment.shader");

	defaultShader.ID = glCreateProgram();
	glAttachShader(defaultShader.ID, vertexShader);
	glAttachShader(defaultShader.ID, fragmentShader);
	glLinkProgram(defaultShader.ID);
	CheckForLinking(defaultShader.ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	/*********************************************************************/

	float vertices[] = 
	{
		0.5f,  0.5f,	1.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  	0.0f, 1.0f, 0.0f,
	   -0.5f, -0.5f,  	0.0f, 0.0f, 1.0f,
	   -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,
	};

	unsigned int indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};


	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT)	running = false;
		}
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		glClearColor(.0f, .0f, .0f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Update here 
		glUseProgram(defaultShader.ID);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		SDL_GL_SwapWindow(window);
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(defaultShader.ID);

	return 0;
}
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include "object.h"

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
	if (!(IMG_Init(IMG_INIT_PNG) | IMG_INIT_PNG))
	{
		printf("IMG_Init: %s\n", IMG_GetError());
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
	float x = 0;
	Object base;

	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT)	running = false;
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_a)
				{
					x -= 0.1f;
				}
				if (event.key.keysym.sym == SDLK_d)
				{
					x += 0.1f;
				}
			}
		}
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		glClearColor(.0f, .0f, .0f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Update here 
		base.transform.position = glm::vec2(x, 1.0f);
		base.transform.SetTransform();
		base.Render();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		SDL_GL_SwapWindow(window);
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	glDeleteVertexArrays(1, &base.mesh.VAO);
	glDeleteBuffers(1, &base.mesh.VBO);
	glDeleteProgram(base.shader.ID);

	return 0;
}
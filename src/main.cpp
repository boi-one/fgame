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

		float left{ 0 }, right{ 0 }, top{ 0 }, bottom{ 0 };
	};
	Viewport viewport;
	glm::vec2 position = glm::vec2(0, 0);

	void SetProjection()
	{
		viewport.left = -(viewport.windowWidth * 0.5f);
		viewport.right = viewport.windowWidth * 0.5f;
		viewport.top = viewport.windowHeight * 0.5f;
		viewport.bottom = -(viewport.windowHeight * 0.5f);

		float scale = 0.01f;

		projection = glm::mat4(1.0f);

		projection = glm::ortho(
			(viewport.left + position.x) * scale,
			(viewport.right + position.x) * scale,
			(viewport.bottom + position.y) * scale,
			(viewport.top + position.y) * scale,
			-1.0f, 1.0f);
	}

	glm::mat4 GetProjection()
	{
		return projection;
	}

private:
	glm::mat4 projection;
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
	Object base({-2.8f, 0});
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

		SDL_GL_GetDrawableSize(window, &camera.viewport.windowWidth, &camera.viewport.windowHeight);
		glViewport(0, 0, camera.viewport.windowWidth, camera.viewport.windowHeight);
		glClearColor(1.0f, .0f, .0f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Update here 

		camera.SetProjection();
		
		for (Object& object : Object::allObjects)
		{
			object.shader.Use();
			object.shader.SetMat4("Projection", camera.GetProjection());
			base.transform.SetTransform();
			base.Render();
		}

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
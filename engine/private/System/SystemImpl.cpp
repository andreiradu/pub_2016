#include <Engine/System/System.h>
#include "System/SystemImpl.h"

namespace Engine
{


void SystemImpl::Init(SCreationSettings&& cs)
{
	SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);
	m_window = SDL_CreateWindow(cs.windowTitle, 100, 100, cs.windowWidth, cs.windowHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	m_context = SDL_GL_CreateContext(m_window);
	//if (cs.hideWindow)
	//	SDL_HideWindow(m_window);
	SDL_GL_SetSwapInterval(0);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);

	glEnable(GL_TEXTURE_2D);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_NORMALIZE);
}

void SystemImpl::Start()
{
	bool done = false;
	while (!done) {

		SDL_Event evt;
		while (SDL_PollEvent(&evt)) {
			switch (evt.type)
			{
			case SDL_KEYDOWN:
			case SDL_KEYUP:
			{

				break;
			}
			case SDL_WINDOWEVENT:
				switch (evt.window.event) {
				case SDL_WINDOWEVENT_CLOSE:
				{
					SDL_Window *window = SDL_GetWindowFromID(evt.window.windowID);
					if (window)
					{
						SDL_DestroyWindow(window);
					}

				}
				break;
				}
				break;
			}
		}
		SDL_GL_MakeCurrent(m_window, m_context);
		SDL_GL_SwapWindow(m_window);


	}
};

}
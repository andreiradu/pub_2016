#include <SDL.h>
#include <SDL_opengl.h>
#include <Engine/Config.h>

namespace Engine
{
	class Renderer;
	struct SCreationSettings;

	class ENGINE_API SystemImpl
	{
	public:
		void Init(SCreationSettings&& cs);
		void Start();
	protected:
		SDL_Window* m_window;
		SDL_GLContext m_context;
		Renderer* m_renderer;
	};
}
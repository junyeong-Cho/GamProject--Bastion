/*
#pragma once

#include "../Engine/owner.h"

#include "../Engine/GameState.h"

#include <string>


struct		  SDL_Window;
typedef void* SDL_GLContext;
class		  GameState;


class Engine
{
public:
	static Engine& Instance()
	{
		static Engine instance;
		return instance;
	}

	Engine(const char* title = "OpenGL App", int desired_width = 800, int desired_height = 600);
	~Engine();

	Engine(const Engine&)				 = delete;
	Engine& operator=(const Engine&)	 = delete;
	Engine(Engine&&) noexcept			 = delete;
	Engine& operator=(Engine&&) noexcept = delete;

	void Start(std::string window_title);
	void Update();
	bool IsDone() const noexcept;


private:
	util::owner<GameState*>     ptr_gamestate = nullptr;
	util::owner<SDL_Window*>    ptr_window    = nullptr;
	util::owner<SDL_GLContext>  gl_context    = nullptr;
	bool                        is_done		  = false;

};
*/
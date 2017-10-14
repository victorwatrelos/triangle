#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window.hpp>
#include "Types.hpp"
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

class WindowManager
{
	public:
		WindowManager(void);
		virtual ~WindowManager(void);

		WindowManager(const WindowManager &obj) = delete;
		WindowManager &operator=(const WindowManager &p) = delete;

		void				Run();
		U16					AddObject(sf::Drawable *drawable, bool visible);
	private:
		typedef struct		s_drawable
		{
			sf::Drawable	*drawable;
			bool			visible;
		}					t_drawable;


		std::vector<t_drawable>		m_drawnObjects;
		std::mutex					mutex;
		std::atomic<bool>			m_drawableChange;
		sf::RenderWindow					*m_window;

		const std::mutex	&getMutex() const;
		void				drawObject();
};

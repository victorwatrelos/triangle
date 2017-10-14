#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "Types.hpp"
#include <iostream>

class WindowManager
{
	public:
		WindowManager(void);
		virtual ~WindowManager(void);

		WindowManager(const WindowManager &obj) = delete;
		WindowManager &operator=(const WindowManager &p) = delete;

		void				run();
		U16					addObject(sf::Drawable *drawable, bool visible);
		const std::mutex	&getMutex() const;
	private:
		typedef struct	s_drawable
		{
			sf::Drawable	*drawable;
			bool			isDraw;
		}				t_drawable;

		std::vector<t_drawable>		m_drawnObjects;
		std::mutex					mutex;
};

#pragma once

#include "ObjectManager.hpp"
#include "WindowManagerBase.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Types.hpp"
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

class WindowManager : public WindowManagerBase
{
	public:
		WindowManager(ObjectManagerBase *objectManager);
		virtual ~WindowManager(void);

		WindowManager(const WindowManager &obj) = delete;
		WindowManager &operator=(const WindowManager &p) = delete;

		void				Run();
		U16					AddObject(sf::Drawable *drawable, bool visible) override;
		std::mutex			&GetMutex();
	private:
		typedef struct		s_drawable
		{
			sf::Drawable	*drawable;
			bool			visible;
		}					t_drawable;


		std::vector<t_drawable>		m_drawnObjects;
		std::mutex					mutex;
		std::atomic<bool>			m_drawableChange;
		sf::RenderWindow			*m_window;
		ObjectManagerBase			*m_objectManager;

		void						drawObject();
};

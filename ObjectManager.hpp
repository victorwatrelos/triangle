#pragma once

#include "WindowManager.hpp"
#include <SFML/Graphics/CircleShape.hpp>

class ObjectManager
{
	public:
		ObjectManager(WindowManager *windowManager);
		virtual ~ObjectManager(void);
		ObjectManager(const ObjectManager &obj) = delete;
		ObjectManager &operator=(const ObjectManager &p) = delete;

		void	Run();
		void	Stop();
	private:
		WindowManager	*m_windowManager;
		std::atomic<bool>	m_running;
};

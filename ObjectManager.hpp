#pragma once

#include "Entity.hpp"
#include "ObjectManagerBase.hpp"
#include "WindowManagerBase.hpp"
#include "Types.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <cmath>
#include <mutex>

class WindowManager;

class ObjectManager : public ObjectManagerBase
{
	public:
		ObjectManager();
		virtual ~ObjectManager(void);
		ObjectManager(const ObjectManager &obj) = delete;
		ObjectManager &operator=(const ObjectManager &p) = delete;

		void	Loop() override;
		void	Init(WindowManagerBase *window) override;
		void	Stop();
	private:
		WindowManagerBase				*m_windowManager;
		std::atomic<bool>			m_running;
		Entity						m_player;
};

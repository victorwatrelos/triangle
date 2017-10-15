#include "ObjectManager.hpp"

ObjectManager::ObjectManager() :
	  m_running(false)
	  , m_player("textures/triangle-green-double.png")
{
	m_player.CenterOrigin();
	m_player.AddPosition({200.f, 200.f});
}

void	ObjectManager::Stop()
{
	m_running = false;
}

void	ObjectManager::Init(WindowManagerBase *windowManager)
{
	m_running = true;
	m_windowManager = windowManager;
	auto ret = m_windowManager->AddObject(&m_player, true);
	m_player.SetId(ret);
}

void	ObjectManager::Loop(const sf::Time &time)
{
	m_player.rotate(360.f * time.asSeconds());
}

ObjectManager::~ObjectManager(void) {
}

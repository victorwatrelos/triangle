#include "ObjectManager.hpp"

ObjectManager::ObjectManager() :
	  m_running(false)
	  , m_player("textures/triangle-green-double.png")
{
	m_player.CenterOrigin();
	m_player.AddPosition({200.f, 200.f});
	m_player.rotate(-30.f);
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
	m_player.setScale(0.3f, 0.3f);
}

void	ObjectManager::Loop(const sf::Time &time)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_player.SetVelocity({100.f, 0.f});
	else
		m_player.SetVelocity({0.f, 0.f});
	m_player.Move(time);
}

ObjectManager::~ObjectManager(void) {
}

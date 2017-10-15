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

void	ObjectManager::Loop()
{
	static float rotation = 0.f;
	m_player.rotate(rotation);
	rotation += 0.1f;
	rotation = std::fmod(rotation, 360.f);
	sf::sleep(sf::milliseconds(50));
}

ObjectManager::~ObjectManager(void) {
}

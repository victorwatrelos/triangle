#include "ObjectManager.hpp"

ObjectManager::ObjectManager(WindowManager *windowManager)
	: m_windowManager(windowManager)
	  , m_running(false)
{
}

void	ObjectManager::Stop()
{
	m_running = false;
}

void	ObjectManager::Run()
{
	sf::CircleShape *shape;

	m_running = true;
	shape = new sf::CircleShape(100);
	shape->setFillColor(sf::Color(150, 50, 250));
	shape->setOutlineThickness(10);
	shape->setOutlineColor(sf::Color(250, 150, 100));
	m_windowManager->AddObject(shape, true);
	while (m_running)
		sf::sleep(sf::milliseconds(100));
	delete shape;
}

ObjectManager::~ObjectManager(void) {
}

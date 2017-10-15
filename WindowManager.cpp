#include "WindowManager.hpp"

WindowManager::WindowManager(ObjectManagerBase *objectManager)
	: m_drawableChange(false)
	  , m_objectManager(objectManager)
{
	this->m_window = new sf::RenderWindow(sf::VideoMode(1600, 1200), "Triangle");
	this->m_window->setVerticalSyncEnabled(true);
	//this->m_window->setFramerateLimit(30);
	this->m_objectManager->Init(this);
}

WindowManager::~WindowManager(void) {
	delete this->m_window;
}

std::mutex	&WindowManager::GetMutex()
{
	return this->mutex;
}

U16		WindowManager::AddObject(sf::Drawable *drawable, bool visible)
{
	U16	ret;

	ret = this->m_drawnObjects.size();
	this->m_drawnObjects.push_back({drawable, visible});
	this->m_drawableChange = true;
	std::cout << "Add object" << std::endl;
	return ret;
}

void	WindowManager::drawObject()
{
	std::lock_guard<std::mutex> guard(this->mutex);
	for (const auto &drawable : this->m_drawnObjects)
	{
		if (drawable.visible)
			m_window->draw(*drawable.drawable);
	}
}

void	WindowManager::Run()
{
	U64		nbLoop = 0;
	sf::Clock	clock;
	sf::Time	time;
	U64			fps;

	while (m_window->isOpen())
	{
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					m_window->close();
					continue ;
			}

		}
		time = clock.restart();
		m_objectManager->Loop(time);
		this->m_window->clear();
		this->drawObject();
		this->m_window->display();
		++nbLoop;
	}
}

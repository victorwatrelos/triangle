#include "WindowManager.hpp"

WindowManager::WindowManager(void)
	: m_drawableChange(false)
{
	this->m_window = new sf::RenderWindow(sf::VideoMode(1600, 1200), "Triangle");
	this->m_window->setVerticalSyncEnabled(true);
}

WindowManager::~WindowManager(void) {
	delete this->m_window;
}

const std::mutex	&WindowManager::getMutex() const
{
	return this->mutex;
}

U16		WindowManager::AddObject(sf::Drawable *drawable, bool visible)
{
	U16	ret;

	std::lock_guard<std::mutex> guard(this->mutex);

	ret = this->m_drawnObjects.size();
	this->m_drawnObjects.push_back({drawable, visible});
	this->m_drawableChange = true;
	std::cout << "Add object" << std::endl;
	return ret;
}

void	WindowManager::drawObject()
{
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
		m_window->display();
		while (m_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window->close();
				continue ;
			}
			//sf::sleep(sf::milliseconds(20));
			this->m_window->clear(sf::Color::Black);
			this->drawObject();
			this->m_window->display();
		}
		++nbLoop;
	}
}

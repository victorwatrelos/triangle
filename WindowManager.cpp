#include "WindowManager.hpp"

WindowManager::WindowManager(void) {

}

WindowManager::~WindowManager(void) {

}

const std::mutex	&WindowManager::getMutex() const
{
	return this->mutex;
}

U16		WindowManager::addObject(sf::Drawable *drawable, bool visible)
{
	U16	ret;

	ret = this->m_drawnObjects.size();
	this->m_drawnObjects.push_back({drawable, visible});
	return ret;
}

void	WindowManager::run()
{
	sf::Window window(sf::VideoMode(800, 600), "My window");
	U64		nbLoop = 0;

	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		std::cout << "Frame " << nbLoop << std::endl; 
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		++nbLoop;
	}
}

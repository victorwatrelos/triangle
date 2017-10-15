#pragma once

class WindowManagerBase;

class ObjectManagerBase
{
	public:
		virtual void	Loop(const sf::Time &time) = 0;
		virtual void	Init(WindowManagerBase *window) = 0;
};

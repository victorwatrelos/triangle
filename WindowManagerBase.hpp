#pragma once

class WindowManagerBase
{
	public:
		virtual U16 AddObject(sf::Drawable *drawable, bool visible) = 0;
};

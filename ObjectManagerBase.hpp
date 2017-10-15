#pragma once

class WindowManagerBase;

class ObjectManagerBase
{
	public:
		virtual void	Loop() = 0;
		virtual void	Init(WindowManagerBase *window) = 0;
};

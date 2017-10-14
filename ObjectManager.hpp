#pragma once

#ifndef OBJECTMANAGER
# define OBJECTMANAGER

# include "WindowManager.hpp"

class ObjectManager
{
	public:
		ObjectManager(WindowManager *windowManager);
		virtual ~ObjectManager(void);
		ObjectManager(const ObjectManager &obj) = delete;
		ObjectManager &operator=(const ObjectManager &p) = delete;

	private:
		
};

#endif

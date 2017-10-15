#include "WindowManager.hpp"
#include "ObjectManager.hpp"

int main()
{
	ObjectManager	objectManager;
	WindowManager	windowManager(&objectManager);

//	std::thread tObjectUpdate(launchObjectManager, &objectManager);
	windowManager.Run();
//objectManager.Stop();
//	tObjectUpdate.join();
	return 0;
}

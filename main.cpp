#include "WindowManager.hpp"
#include "ObjectManager.hpp"

void	launchObjectManager(ObjectManager *objectManager)
{
	objectManager->Run();
}

int main()
{
	WindowManager	windowManager;
	ObjectManager	objectManager(&windowManager);

	std::thread tObjectUpdate(launchObjectManager, &objectManager);
	windowManager.Run();
	objectManager.Stop();
	tObjectUpdate.join();
	return 0;
}

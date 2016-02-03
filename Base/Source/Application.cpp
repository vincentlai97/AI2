#include "Application.h"

Application* Application::instance = nullptr;

Application::~Application()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

Application* Application::GetInstance()
{
	if (instance == nullptr)
		instance = new Application();

	return instance;
}

Application::Application()
{

}
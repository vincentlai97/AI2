#ifndef APPLICATION_H
#define APPLICATION_H

class Application
{
public:
	~Application();

	Application* GetInstance();

private:
	static Application *instance;

	Application();
};

#endif
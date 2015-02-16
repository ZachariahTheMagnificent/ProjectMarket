
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include <vector>

class Application
{
public:
	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
private:
	StopWatch m_timer;
};

#endif
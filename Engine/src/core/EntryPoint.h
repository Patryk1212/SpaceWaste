#pragma once
#include "Engine.h"

extern Engine::Application* Engine::createApplication();

int main(const int argc, const char* argv[])
{
	auto app = Engine::createApplication();
	app->init();
	app->run();
	delete app;
	return 0;
}
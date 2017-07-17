#include "GameAIApp.h"

int main() {
	
	// allocation
	auto app = new GameAIApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}
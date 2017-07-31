#include "BoidsApp.h"

int main() {
	
	auto app = new BoidsApp();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}
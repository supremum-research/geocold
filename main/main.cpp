// libc++ headers + STL headers => basically standard library content at the top
#include <iostream>
#include <array>

//headers from our own library

#include "geocold.hpp"
#include "rendererapplication.hpp"


int main() {
	renderer::RenderApplication app;

	try {
		app.run();
	} catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

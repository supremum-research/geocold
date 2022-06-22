// libc++ headers + STL headers => basically standard library content at the top
#include <iostream>
#include <array>

//headers from our own library
#include "extra.hpp"
#include "geocold.hpp"

using namespace geocold;

int main() {
	auto app {RenderingApplication()};
	app.run();
}

// libc++ headers + STL headers => basically standard library content at the top
#include <iostream>
#include <array>

//headers from our own library
#include "extra.hpp"
#include "rendererapplication.hpp"

using namespace renderer;

int main() {
	RenderApplication app;
	app.run();
}

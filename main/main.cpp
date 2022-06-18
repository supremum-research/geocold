#include <iostream>
#include <array>
#include "geocold/primitives/line"

using namespace geocold;

int main() {
  Line<2, float> a(Point<2,float>({1,2}), Point<2,float>({1,2}));
  std::cout << "Hello World\n";
}

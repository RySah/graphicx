// graphicx.cpp : Defines the entry point for the application.
//

#include "triangle_example.h"
#include "quad_example.h"

#define USE_TRIANGLE_EXAMPLE

int main() {
#if defined(USE_TRIANGLE_EXAMPLE)
	return TriangleExample::run();
#elif defined(USE_QUAD_EXAMPLE)
	return QuadExample::run();
#else
	return 69420;
#endif
}

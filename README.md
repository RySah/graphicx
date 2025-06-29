# GraphicX

Graphics libary for games and applications.

## GX
Main libary for which others rely, provides main API.

### Getting started
You can get the latest binaries from the release page, or [build it yourself](gx/BUILD.md).

#### Triangle example
```cpp
#include <iostream>
#include <gx/gx.h>

using namespace std;

// Keyboard event callback
void handleKeyPress(GXApplication* app, GXWindow* window, GXKey key, int scancode, GXKeyAction action, int mods) {
	// Close window when ESC key is pressed
	if (key == GX_KEY_ESCAPE && action == GX_KEY_ACTION_PRESS) {
		printf("ESC pressed - closing window\n");
		gxWindowClose(window);
	} 
}

// Stores all the relevant data for rendering, this memory is completely handled by the libary.
GXObject* triangleObject;

// Draw callback
void drawScene(GXWindow* window) {
	// This updates the viewport relative to the windows (framebuffer) size.
	// The windows (framebuffer) size is updated automatically before this callback is called each frame.
	// You can use gxViewport(x, y, w, h) as an more advanced alternative.
	gxUpdateViewport(window);

	// This sets the background of `window`
	// This is the same as running:
	// ```	
	// gxClearColor(r, g, b, a);
	// gxClear(GX_COLOR_BUFFER_BIT);
	// ```
	gxSetBackground(0.2f, 0.3f, 0.8f, 1.0f); // Blue background

	// This enables the rendering of a object via its respective shader.
	// If 2 or more objects use the same shader, this function only has to be used on one, to allow consecutive rendering.
	// e.g.
	// ```
	// gxUseShader(triangleObjectUsingSameShader); // 
	// gxUseShader(squareObjectUsingSameShader);   // <- This second call is useless
	// ```
	gxUseShader(triangleObject);

	// This draws all 3 vertices of the object, with a offset of 0
	gxDrawVertices(triangleObject, 0, 3);
}

// Entry point
int main() {
	// This initializes all of its dependencies
	// This must be used before anything related to GX is used
	if (const char* errorMessage = gxInit()) { 
		fprintf(stderr, "Initialization failed: %s\n", error);
		return 1;
	}

	// Creates an application for which manages all resources and objects
	gxCreateApplication(GX_APP_OPTION_NONE);

	GXWindow* window = gxCreateWindow(true, true, 800, 600, "GX Triangle example");
	if (!window) { // If window creation failed
		fprintf(stderr, "Window creation failed\n");
		gxTerminate(); // Shutdown and cleanup resources used by the libary
		return 1;
	}

	uint shader_program = 0;
	{
		GXProgramCompilationResult result = gxCompileGLSLProgram(
			R"glsl(
#version 460 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
			
layout(location = 0) out vec4 vColor;
			
void main() {
	gl_Position = vec4(aPos, 1.0);
	vColor = aColor;
}
			)glsl",
			R"glsl(
#version 460 core
layout(location = 0) in vec4 vColor;

out vec4 fragColor;

void main() {
	fragColor = vColor;
}
			)glsl"
		);
		if (!result.success) {
			fprintf(stderr, "SHADER LINKING ERROR: %s\n", result.program_log);
			fprintf(stderr, "VERTEX SHADER COMPILATION ERROR: %s\n", result.vertex_result.info_log);
			fprintf(stderr, "FRAGMENT SHADER COMPILATION ERROR: %s\n", result.fragment_result.info_log);
			gxTerminate();
			return 1;
		}
		else shader_program = result.program;
	}

	float triangle_vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
	};

	triangleObject = gxCreateRenderObject(shader_program, GX_BUFFER_USAGE_TYPE_STATIC, sizeof(float) * (3 * 7), triangle_vertices, nullptr);
	gxBindObject(triangleObject);

	gxEnableVertexAttribute(triangleObject, 0);
	gxSetVertexAttribute(triangleObject, 0, 3, GX_VERTEX_ATTRIB_TYPE_FLOAT, false, 7 * sizeof(float), (void*)0);
	gxEnableVertexAttribute(triangleObject, 1);
	gxSetVertexAttribute(triangleObject, 1, 4, GX_VERTEX_ATTRIB_TYPE_FLOAT, false, 7 * sizeof(float), (void*)(3 * sizeof(float)));

	gxAddKeyboardCallback(handleKeyPress);
	gxWindowSetDrawCallback(window, drawScene);

	gxExec();

	gxTerminate();
	return 0;
}
```

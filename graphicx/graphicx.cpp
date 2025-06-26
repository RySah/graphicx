// graphicx.cpp : Defines the entry point for the application.
//

// Triangle example using GraphicX library

#define GX_CMAKE_GL

#include "graphicx.h"

using namespace std;

void handleKeyPress(GXApplication* app, GXWindow* win, GXKey key, int scancode, GXKeyAction action, int mods) {
	// Close window when ESC key is pressed
	if (key == GX_KEY_ESCAPE && action == GX_KEY_ACTION_PRESS) {
		printf("ESC pressed - closing window\n");
		gxWindowClose(win);
	}
}

GXObject* triangleObject;

void drawScene(GXWindow* window) {
	gxUpdateViewport(window);
	gxSetBackground(0.2f, 0.3f, 0.8f, 1.0f); // Blue background
	
	gxUseShader(triangleObject);

	gxDrawVertices(triangleObject, 0, 3);
}

int main() {
	if (const char* error = gxInit()) {
		fprintf(stderr, "Initialization failed: %s\n", error);
		return 1;
	}

	gxCreateApplication(GX_APP_OPTION_NONE);

	GXWindow* window = gxCreateWindow(true, true, 800, 600, "GX Test");
	if (!window) {
		fprintf(stderr, "Window creation failed\n");
		gxTerminate();
		return 1;
	}

	uint32_t shader_program = 0;
	{
		auto result = gxCompileGLSLProgram(
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

#define RGBA_DISTRIBUTOR(r8, g8, b8, a8) \
	((float)(r8) / 255.0f), ((float)(g8) / 255.0f), ((float)(b8) / 255.0f), ((float)(a8) / 255.0f)

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, RGBA_DISTRIBUTOR(255, 0, 0, 255),
		 0.0f,  0.5f, 0.0f, RGBA_DISTRIBUTOR(0, 0, 255, 255),
		 0.5f, -0.5f, 0.0f, RGBA_DISTRIBUTOR(0, 255, 0, 255)
	};

	triangleObject = gxCreateRenderObject(shader_program, GX_BUFFER_USAGE_TYPE_STATIC, sizeof(float) * (3 * 7), vertices, nullptr);
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

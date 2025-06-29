
#define GX_CMAKE_GL

#include "graphicx.h"

using namespace std;

namespace QuadExample {

	void handleKeyPress(GXApplication* app, GXWindow* win, GXKey key, int scancode, GXKeyAction action, int mods) {
		// Close window when ESC key is pressed
		if (key == GX_KEY_ESCAPE && action == GX_KEY_ACTION_PRESS) {
			printf("ESC pressed - closing window\n");
			gxWindowClose(win);
		}
	}

	GXObject* squareObject;

	void drawScene(GXWindow* window) {
		gxUpdateViewport(window);
		gxSetBackground(0.2f, 0.3f, 0.8f, 1.0f); // Blue background

		gxUseShader(squareObject);
		gxDrawElements(squareObject, 6, GX_VERTEX_ATTRIB_TYPE_UNSIGNED_SHORT);
	}

	int run() {
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

		float square_vertices[] = {
			-0.5f, -0.5f, 0.0f, RGBA_DISTRIBUTOR(255, 0, 0, 255), // bottom-left
			0.5f,  -0.5f, 0.0f, RGBA_DISTRIBUTOR(127, 127, 0, 255),  // bottom-right
			0.5f,  0.5f, 0.0f, RGBA_DISTRIBUTOR(127, 127, 127, 255),  // top-right
			-0.5f,  0.5f, 0.0f, RGBA_DISTRIBUTOR(127, 127, 255, 255) // top-left
		};
		uint16_t square_indices[] = {
			0, 1, 2, // First triangle
			2, 3, 0  // Second triangle
		};

		squareObject = gxCreateRenderObjectWithElements(shader_program,
			GX_BUFFER_USAGE_TYPE_STATIC, sizeof(float) * (4 * 7), square_vertices,
			GX_BUFFER_USAGE_TYPE_STATIC, sizeof(uint16_t) * 6, square_indices,
			nullptr);
		gxBindObject(squareObject);

		gxEnableVertexAttribute(squareObject, 0);
		gxSetVertexAttribute(squareObject, 0, 3, GX_VERTEX_ATTRIB_TYPE_FLOAT, false, 7 * sizeof(float), (void*)0);
		gxEnableVertexAttribute(squareObject, 1);
		gxSetVertexAttribute(squareObject, 1, 4, GX_VERTEX_ATTRIB_TYPE_FLOAT, false, 7 * sizeof(float), (void*)(3 * sizeof(float)));

		gxAddKeyboardCallback(handleKeyPress);
		gxWindowSetDrawCallback(window, drawScene);

		gxExec();

		gxTerminate();
		return 0;
	}

}
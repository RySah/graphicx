#ifndef __GX_INCLUDE_GX_H__
#define __GX_INCLUDE_GX_H__

#include <cstdint>

#if defined(GX_CMAKE_GL) || defined(GX_GL)
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif // defined(GX_CMAKE_GL) || defined(GX_GL)

#if defined(_WIN32)
#if defined(GX_SHARED)
#ifdef GX_BUILD
#define GX_API __declspec(dllexport)
#else
#define GX_API __declspec(dllimport)
#endif
#else
#define GX_API
#endif
#else
#if defined(GX_SHARED)
#define GX_API __attribute__((visibility("default")))
#else
#define GX_API
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	/** \mainpage GX Library Manual
	 *  Welcome to the GX Library documentation.
	 *
	 *  \section sec_basics Basics
	 *  - \ref Basics Core Libary Initialization
	 *
	 *  \section sec_enums Enumerations
	 *  - \ref GXKey
	 *  - \ref GXApplicationOptions
	 *  - \ref GXResourceType
	 *  - \ref GXResourceStatus
	 */

	/** \page Basics Core Library Initialization
	 *  \brief Basic library initialization and termination functions.
	 *
	 *  Before using the libary both of these functions should be used respectively.
	 *  - \ref gxInit()
	 *  - \ref gxTerminate()
	 *
	 *  \code
	 *	int main(...) {
	 *		gxInit();
	 *		...
	 *		gxTerminate();
	 *  }
	 *  \endcode
	 *  Both serve to initiate and terminate its own dependencies, and clean up memory usage.
	 *
	 */


	/** \fn const char* gxInit()
	 *  \brief Initializes GX library and dependencies (GLFW).
	 *  \return nullptr on success, error message on failure.
	 *  \see gxTerminate()
	 */
	GX_API const char* gxInit();

	/** \fn void gxTerminate()
	 *  \brief Terminates GX library and cleans up resources.
	 *  \see gxInit()
	 */
	GX_API void gxTerminate();

	/*! \enum GXKey
	 *  \brief Keyboard key enumeration (mirrors GLFW key values).
	 *
	 */
	enum GXKey {
		GX_KEY_SPACE = 32,
		GX_KEY_APOSTROPHE = 39,
		GX_KEY_COMMA = 44,
		GX_KEY_MINUS = 45,
		GX_KEY_PERIOD = 46,
		GX_KEY_SLASH = 47,
		GX_KEY_0 = 48,
		GX_KEY_1 = 49,
		GX_KEY_2 = 50,
		GX_KEY_3 = 51,
		GX_KEY_4 = 52,
		GX_KEY_5 = 53,
		GX_KEY_6 = 54,
		GX_KEY_7 = 55,
		GX_KEY_8 = 56,
		GX_KEY_9 = 57,
		GX_KEY_SEMICOLON = 59,
		GX_KEY_EQUAL = 61,
		GX_KEY_A = 65,
		GX_KEY_B = 66,
		GX_KEY_C = 67,
		GX_KEY_D = 68,
		GX_KEY_E = 69,
		GX_KEY_F = 70,
		GX_KEY_G = 71,
		GX_KEY_H = 72,
		GX_KEY_I = 73,
		GX_KEY_J = 74,
		GX_KEY_K = 75,
		GX_KEY_L = 76,
		GX_KEY_M = 77,
		GX_KEY_N = 78,
		GX_KEY_O = 79,
		GX_KEY_P = 80,
		GX_KEY_Q = 81,
		GX_KEY_R = 82,
		GX_KEY_S = 83,
		GX_KEY_T = 84,
		GX_KEY_U = 85,
		GX_KEY_V = 86,
		GX_KEY_W = 87,
		GX_KEY_X = 88,
		GX_KEY_Y = 89,
		GX_KEY_Z = 90,
		GX_KEY_LEFT_BRACKET = 91,
		GX_KEY_BACKSLASH = 92,
		GX_KEY_RIGHT_BRACKET = 93,
		GX_KEY_GRAVE_ACCENT = 96,
		GX_KEY_WORLD_1 = 161,
		GX_KEY_WORLD_2 = 162,
		GX_KEY_ESCAPE = 256,
		GX_KEY_ENTER = 257,
		GX_KEY_TAB = 258,
		GX_KEY_BACKSPACE = 259,
		GX_KEY_INSERT = 260,
		GX_KEY_DELETE = 261,
		GX_KEY_RIGHT = 262,
		GX_KEY_LEFT = 263,
		GX_KEY_DOWN = 264,
		GX_KEY_UP = 265,
		GX_KEY_PAGE_UP = 266,
		GX_KEY_PAGE_DOWN = 267,
		GX_KEY_HOME = 268,
		GX_KEY_END = 269,
		GX_KEY_CAPS_LOCK = 280,
		GX_KEY_SCROLL_LOCK = 281,
		GX_KEY_NUM_LOCK = 282,
		GX_KEY_PRINT_SCREEN = 283,
		GX_KEY_PAUSE = 284,
		GX_KEY_F1 = 290,
		GX_KEY_F2 = 291,
		GX_KEY_F3 = 292,
		GX_KEY_F4 = 293,
		GX_KEY_F5 = 294,
		GX_KEY_F6 = 295,
		GX_KEY_F7 = 296,
		GX_KEY_F8 = 297,
		GX_KEY_F9 = 298,
		GX_KEY_F10 = 299,
		GX_KEY_F11 = 300,
		GX_KEY_F12 = 301,
		GX_KEY_F13 = 302,
		GX_KEY_F14 = 303,
		GX_KEY_F15 = 304,
		GX_KEY_F16 = 305,
		GX_KEY_F17 = 306,
		GX_KEY_F18 = 307,
		GX_KEY_F19 = 308,
		GX_KEY_F20 = 309,
		GX_KEY_F21 = 310,
		GX_KEY_F22 = 311,
		GX_KEY_F23 = 312,
		GX_KEY_F24 = 313,
		GX_KEY_F25 = 314,
		GX_KEY_KP_0 = 320,
		GX_KEY_KP_1 = 321,
		GX_KEY_KP_2 = 322,
		GX_KEY_KP_3 = 323,
		GX_KEY_KP_4 = 324,
		GX_KEY_KP_5 = 325,
		GX_KEY_KP_6 = 326,
		GX_KEY_KP_7 = 327,
		GX_KEY_KP_8 = 328,
		GX_KEY_KP_9 = 329,
		GX_KEY_KP_DECIMAL = 330,
		GX_KEY_KP_DIVIDE = 331,
		GX_KEY_KP_MULTIPLY = 332,
		GX_KEY_KP_SUBTRACT = 333,
		GX_KEY_KP_ADD = 334,
		GX_KEY_KP_ENTER = 335,
		GX_KEY_KP_EQUAL = 336,
		GX_KEY_LEFT_SHIFT = 340,
		GX_KEY_LEFT_CONTROL = 341,
		GX_KEY_LEFT_ALT = 342,
		GX_KEY_LEFT_SUPER = 343,
		GX_KEY_RIGHT_SHIFT = 344,
		GX_KEY_RIGHT_CONTROL = 345,
		GX_KEY_RIGHT_ALT = 346,
		GX_KEY_RIGHT_SUPER = 347,
		GX_KEY_MENU = 348
	};

	/*! \enum GXApplicationOptions
	 *  \brief Application configuration flags.
	 *
	 *  Values:
	 *  - `GX_APP_OPTION_NONE`: Default options
	 */
	enum GXApplicationOptions {
		GX_APP_OPTION_NONE = 0,
	};

	/*! \struct GXApplication
	 *  \brief Main application context.
	 *
	 *  Members:
	 *  - `options`: Application configuration flags
	 *  - `resource_collection`: Dynamic array of managed resources
	 *  - `keyboard_cb_collection`: Dynamic array of keyboard callbacks
	 */
	struct GXApplication {
		GXApplicationOptions options;
		void* resource_collection_vec_ptr;
		void* keyboard_cb_collection_vec_ptr;
	};

	struct GXWindow;
	struct GXResource;

	/*! \typedef void (*GXDrawCallback)(GXWindow*)
	 *  \brief Window rendering callback type.
	 *  \param win Pointer to window being rendered
	 */
	typedef void (*GXDrawCallback)(GXWindow*);

	/*! \struct GXWindow
	 *  \brief Window configuration and state.
	 *
	 *  Members:
	 *  - `resource`: Pointer to container resource
	 *  - `width`: Window width in pixels
	 *  - `height`: Window height in pixels
	 *  - `title`: Window title string
	 *  - `show`: Window visibility flag
	 *  - `internal`: Internal platform-specific handle
	 *  - `draw_callback`: Rendering callback function
	 */
	struct GXWindow {
		GXResource* resource;
		int width, height;
		const char* title;
		bool show;
		void* internal;
		GXDrawCallback draw_callback;
	};

	/*! \enum GXKeyAction
	 *  \brief Key action identifiers (mirrors GLFW key actions).
	 *
	 *  Values:
	 *  - `GX_KEY_ACTION_PRESS`: The key was pressed
	 *  - `GX_KEY_ACTION_RELEASE`: The key was released
	 *  - `GX_KEY_ACTION_REPEAT`: The key is being held down (repeated)
	 */
	typedef enum {
		GX_KEY_ACTION_PRESS = 1,
		GX_KEY_ACTION_RELEASE = 0,
		GX_KEY_ACTION_REPEAT = 2
	} GXKeyAction;

	/*! \typedef void (*GXKeyboardCallback)(GXApplication*, GXWindow*, GXKey, int, int, int)
	 *  \brief Keyboard event callback.
	 *  \param app Application context
	 *  \param win Target window
	 *  \param key Pressed key
	 *  \param scancode Platform-specific scancode
	 *  \param action Key action (press/release/repeat)
	 *  \param mods Modifier keys (Ctrl/Shift/Alt)
	 */
	typedef void (*GXKeyboardCallback)(GXApplication*, GXWindow*, GXKey, int, GXKeyAction, int);

	/*! \enum GXResourceType
	 *  \brief Resource type identifiers.
	 *
	 *  Values:
	 *  - `GX_RESOURCE_WINDOW`: Window resource
	 *  - `GX_RSOURCE_OBJECT`: Renderable object resource
	 */
	typedef enum {
		GX_RESOURCE_WINDOW,
		GX_RESOURCE_OBJECT
	} GXResourceType;

	/*! \enum GXResourceStatus
	 *  \brief Resource state flags.
	 *
	 *  Values:
	 *  - `GX_RESOURCE_STATUS_NONE`: Initial state
	 *  - `GX_RESOURCE_STATUS_SHOWING`: Window is visible
	 *  - `GX_RESOURCE_STATUS_INITIATED`: Resource initialized
	 *  - `GX_RESOURCE_STATUS_SHOULD_CLOSE`: Resource marked for closure
	 */
	typedef enum {
		GX_RESOURCE_STATUS_NONE = 0,
		GX_RESOURCE_STATUS_SHOWING = 1,
		GX_RESOURCE_STATUS_SHOWING_MASK = ~GX_RESOURCE_STATUS_SHOWING,
		GX_RESOURCE_STATUS_INITIATED = 2,
		GX_RESOURCE_STATUS_INITIATED_MASK = ~GX_RESOURCE_STATUS_INITIATED,
		GX_RESOURCE_STATUS_SHOULD_CLOSE = 4,
		GX_RESOURCE_STATUS_SHOULD_CLOSE_MASK = ~GX_RESOURCE_STATUS_SHOULD_CLOSE
	} GXResourceStatus;

	/*! \enum GXBufferUsageType
	 *  \brief Buffer usage type identifiers for buffer objects.
	 * 
	 * Values:
	 * - `GX_BUFFER_TYPE_STATIC`: Static buffer, data does not change after creation
	 * - `GX_BUFFER_TYPE_DYNAMIC`: Dynamic buffer, data may change frequently
	 * - `GX_BUFFER_TYPE_STREAM`: Stream buffer, data is updated every frame (do not use as a subsitute for dynamic buffers)
	 */
	typedef enum {
		GX_BUFFER_USAGE_TYPE_STATIC = 0x88E4,
		GX_BUFFER_USAGE_TYPE_DYNAMIC = 0x88E8,
		GX_BUFFER_USAGE_TYPE_STREAM = 0x88E0
	} GXBufferUsageType;

	/*! \enum GXBufferType
	 *  \brief Buffer type identifiers for buffer objects.
	 * 
	 *  Values:
	 *  - `GX_BUFFER_TYPE_ARRAY`: Vertex array buffer
	 *  - `GX_BUFFER_TYPE_ELEMENT_ARRAY`: Element array buffer
	 *  - `GX_BUFFER_TYPE_UNIFORM`: Uniform buffer
	 */
	typedef enum {
		GX_BUFFER_TYPE_ARRAY = 0x8892,
		GX_BUFFER_TYPE_ELEMENT_ARRAY = 0x8893,
		GX_BUFFER_TYPE_UNIFORM = 0x8A11
	} GXBufferType;

	/*! \enum GXBufferBit
	 *  \brief Buffer bit bindings for glads GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT, and GX_COLOR_BUFFER_BIT.
	 *
	 *  Values:
	 *  - `GX_DEPTH_BUFFER_BIT`: Indicates the depth buffer
	 *  - `GX_STENCIL_BUFFER_BIT`: Indicates the stencil buffer
	 *  - `GX_COLOR_BUFFER_BIT`: Inidcates the buffers currently enabled for color writing
	 */
	typedef enum : unsigned int {
		GX_DEPTH_BUFFER_BIT = UINT32_C(0x00000100),
		GX_STENCIL_BUFFER_BIT = UINT32_C(0x00000400),
		GX_COLOR_BUFFER_BIT = UINT32_C(0x00004000),
	} GXBufferBit;

	/*! \struct GXObject
	 *  \brief Renderable object.
	 *
	 *  Members:
	 *  - `shader_program`: Shader program id
	 *  - `vao`: Vertex array object id
	 *  - `vbo`: Vertex buffer object id
	 *  - `ebo`: Element buffer object id, this is optional
	 *  - `resource`: Pointer to resource container
	 *  - `user_data`: User-defined data pointer (can be null)
	 */
	struct GXObject {
		uint32_t shader_program, vao, vbo, ebo;
		GXResource* resource;
		void* user_data;
	};

	/*! \struct GXResource
	 *  \brief Managed resource container.
	 *
	 *  Members:
	 *  - `status`: Current resource state
	 *  - `index`: Position in resource array
	 *  - `type`: Resource type identifier
	 *  - `resource`: Resource data
	 *  - `buffer_data`: Buffer data
	 */
	struct GXResource {
		GXResourceStatus status;
		GXResourceType type;
		void* resource;
	};

	/*! \struct GXShaderCompilationResult
	 *  \brief Result of shader compilation.
	 * 
	 *  Members:
	 *  - `handle`: Shader handle (id)
	 *  - `success`: Compilation success flag (1 for success, 0 for failure)
	 *  - `info_log`: Compilation log message
	 */
	struct GXShaderCompilationResult {
		uint32_t handle;
		int success;
		char info_log[512];
	};

	/*! \struct GXProgramCompilationResult
	 *  \brief Result of shader program compilation.
	 *  
	 *  Members:
	 *  - `program`: Shader program id
	 *  - `success`: Compilation success flag (1 for success, 0 for failure)
	 *  - `program_log`: Compilation log message
	 *  - `vertex_result`: Vertex shader compilation result
	 *  - `fragment_result`: Fragment shader compilation result
	 */
	struct GXProgramCompilationResult {
		uint32_t program;
		int success;
		char program_log[1024];
		GXShaderCompilationResult vertex_result, fragment_result;
	};

	/*! \enum GXShaderType
	 *  \brief Shader type bindings for glads GL_FRAGMENT_SHADER, and GL_VERTEX_SHADER.
	 *
	 *  Values:
	 *  - `GX_GLSL_FRAGMENT_SHADER`: Fragment shader type
	 *  - `GX_GLSL_VERTEX_SHADER`: Vertex shader type
	 */
	typedef enum {
		GX_GLSL_FRAGMENT_SHADER = 0x8B30,
		GX_GLSL_VERTEX_SHADER = 0x8B31
	} GXShaderType;

	/*! \enum GXMappingBits
	 *  \brief Buffer mapping bits for glMapBufferRange/gxMapBufferRange.
	 *  
	 *  Values:
	 *  - `GX_MAP_READ_BIT`: Allows reading from the mapped buffer, needed if you plan to read GPU buffer data from CPU
	 *  - `GX_MAP_WRITE_BIT`: Allows writing to the mapped buffer, needed for writing to GPU buffer from CPU
	 *  - `GX_MAP_INVALIDATE_RANGE_BIT`: Tells the driver you don’t care about the previous contents of the mapped range, use this to avoid synchronization if you're replacing part of the buffer
	 *  - `GX_MAP_INVALIDATE_BUFFER_BIT`: Tells the driver you don’t care about the previous contents of the mapped entire buffer, ideal for full rewrites and may trigger buffer reallocation
	 *  - `GX_MAP_UNSYNCHRONIZED_BIT`: Tells the driver not to block even if the buffer is in use, Can avoid sync stalls, but you must be careful not to write to in-use regions
	 *  - `GX_MAP_SIMPLE_WRITE`: Used when you’re rewriting the whole buffer and want to avoid a sync
	 *  - `GX_MAP_FREQUENT_WRITE`: Used when you're writing data frequently
	 *  - `GX_MAP_UNSAFE_HIGH_PERFORMANCE_WRITE`: Bypasses driver sync, but you must manage synchronization manually
	 */
	typedef enum {
		GX_MAP_READ_BIT = 0x0001,
		GX_MAP_WRITE_BIT = 0x0002,
		GX_MAP_INVALIDATE_RANGE_BIT = 0x0004,
		GX_MAP_INVALIDATE_BUFFER_BIT = 0x0008,
		//GX_MAP_FLUSH_EXPLICIT_BIT = 0x0010,
		GX_MAP_UNSYNCHRONIZED_BIT = 0x0020,
		GX_MAP_SIMPLE_WRITE = GX_MAP_WRITE_BIT | GX_MAP_INVALIDATE_BUFFER_BIT,
		GX_MAP_FREQUENT_WRITE = GX_MAP_SIMPLE_WRITE,
		GX_MAP_UNSAFE_HIGH_PERFORMANCE_WRITE = GX_MAP_WRITE_BIT | GX_MAP_UNSYNCHRONIZED_BIT
	} GXMappingBits;

	/*! \enum GXVertexAttributeType
	 *  \brief Data type identifiers
	 *  
	 *  Values:
	 *  - `GX_VERTEX_ATTRIB_TYPE_BYTE`: 8-bit signed integer
	 *  - `GX_VERTEX_ATTRIB_TYPE_UNSIGNED_BYTE`: 8-bit unsigned integer
	 *  - `GX_VERTEX_ATTRIB_TYPE_SHORT`: 16-bit signed integer
	 *  - `GX_VERTEX_ATTRIB_TYPE_UNSIGNED_SHORT`: 16-bit unsigned integer
	 *  - `GX_VERTEX_ATTRIB_TYPE_INT`: 32-bit signed integer
	 *  - `GX_VERTEX_ATTRIB_TYPE_UNSIGNED_INT`: 32-bit unsigned integer
	 *  - `GX_VERTEX_ATTRIB_TYPE_FLOAT`: 32-bit floating point
	 */
	typedef enum {
		GX_VERTEX_ATTRIB_TYPE_BYTE = 0x1400,
		GX_VERTEX_ATTRIB_TYPE_UNSIGNED_BYTE = 0x1401,
		GX_VERTEX_ATTRIB_TYPE_SHORT = 0x1402,
		GX_VERTEX_ATTRIB_TYPE_UNSIGNED_SHORT = 0x1403,
		GX_VERTEX_ATTRIB_TYPE_INT = 0x1404,
		GX_VERTEX_ATTRIB_TYPE_UNSIGNED_INT = 0x1405,
		GX_VERTEX_ATTRIB_TYPE_FLOAT = 0x1406
	} GXVertexAttributeType;

	/** \fn bool gxAddKeyboardCallback(GXKeyboardCallback cb)
	 *  \brief Registers a keyboard event callback.
	 *  \param cb Callback function to register
	 */
	GX_API void gxAddKeyboardCallback(GXKeyboardCallback cb);

	/** \fn bool gxClearKeyboardCallback()
	 *  \brief Clears all keyboard callbacks.
	 */
	GX_API void gxClearKeyboardCallback();

	// ==============================================
	// Application API
	// ==============================================

	/** \fn void gxDestroyApplication(GXApplication* application)
	 *  \brief Releases application resources.
	 *  \param application Application context to destroy
	 */
	GX_API void gxDestroyApplication(GXApplication* application);

	/** \fn GXApplication* gxCreateApplication(GXApplicationOptions options)
	 *  \brief Creates main application context.
	 *  \param options Configuration flags
	 *  \return Pointer to application context
	 */
	GX_API GXApplication* gxCreateApplication(GXApplicationOptions options);

	/** \fn GXApplication* gxGetApplication()
	 *  \brief Retrieves current application context.
	 *  \return Pointer to application context (null if not initialized)
	 */
	GX_API GXApplication* gxGetApplication();

	/** \fn void gxExec()
	 *	\brief Executes the current application.
	 */
	GX_API void gxExec();

	/** \fn GXObject* gxAsObject(GXResource* res)
	 *  \brief Returns a memory pointer to GXObject from the specified GXResource.
	 *  \param res Resource memory pointer
	 *  \return Associated object
	 */
	GX_API GXObject* gxAsObject(GXResource* res);

	/** \fn GXObject* gxCreateStaticObject(uint32_t shader_program, uint32_t vao, uint32_t vbo, uint32_t ebo, void* user_data)
	 *  \brief Creates and initiatlizes an static GXObject in memory.
	 *  \param shader_program Shader program id
	 *  \param vao Vertex array object id
	 *  \param vbo Vertex buffer object id
	 *  \param ebo Element buffer object id (optional, can be 0)
	 *  \param user_data User-defined data pointer (can be null)
	 *  \return Pointer to object
	 *  \note All memory is managed by the libary and does not account for the manual freeing of memory outside of its codebase.
	 */
	GX_API GXObject* gxCreateObject(uint32_t shader_program, uint32_t vao, uint32_t vbo, uint32_t ebo, void* user_data);

	/** \fn GXObject* gxCreateRenderObject(uint32_t shader_program, GXBufferUsageType vert_buffer_usage, size_t vert_size, void* vert_data, GXBufferUsageType elem_buffer_usage, size_t elem_size, void* elem_data, void* user_data)
	 *  \brief Creates and initializes a renderable GXObject in memory.
	 *  \param shader_program Shader program id
	 *  \param vert_buffer_usage Buffer usage type for vertex buffer
	 *  \param vert_size Size of vertex data in bytes
	 *  \param vert_data Pointer to vertex data (can be null)
	 *  \param elem_buffer_usage Buffer usage type for element buffer
	 *  \param elem_size Size of element data in bytes
	 *  \param elem_data Pointer to element data (can be null)
	 *  \param user_data User-defined data pointer (can be null)
	 *  \return Pointer to object
	 * 
	 *  \note Requires gxBindObject(...) to be called to ensure it works.
	 */
	GX_API GXObject* gxCreateRenderObjectWithElements(uint32_t shader_program, GXBufferUsageType vert_buffer_usage, size_t vert_size, void* vert_data, GXBufferUsageType elem_buffer_usage, size_t elem_size, void* elem_data, void* user_data);

	/** \fn GXObject* gxCreateRenderObject(uint32_t shader_program, GXBufferUsageType vert_buffer_usage, size_t vert_size, void* vert_data)
	 *  \brief Creates and initializes a renderable GXObject in memory without an element buffer.
	 *  \param shader_program Shader program id
	 *  \param vert_buffer_usage Buffer usage type for vertex buffer
	 *  \param vert_size Size of vertex data in bytes
	 *  \param vert_data Pointer to vertex data (can be null)
	 *  \param user_data User-defined data pointer (can be null)
	 *  \return Pointer to object
	 * 
	 *  \note Requires gxBindObject(...) to be called to ensure it works.
	 */
	GX_API GXObject* gxCreateRenderObject(uint32_t shader_program, GXBufferUsageType vert_buffer_usage, size_t vert_size, void* vert_data, void* user_data);

	/** \fn void gxDrawVertices(GXObject* object, size_t offset, size_t count)
	 *  \brief Draws a set of vertices from GXObject.
	 *  \param object Object pointer
	 *  \param offset Vertex offset
	 *  \param count Vertex count
	 */
	GX_API void gxDrawVertices(GXObject* object, size_t offset, size_t count);

	/** \fn void gxDrawElements(GXObject* object, size_t offset, size_t count)
	 *  \brief Draws a set of elements from GXObject.
	 *  \param object Object pointer
	 *  \param count Element count
	 *  \param type Element type
	 */
	GX_API void gxDrawElements(GXObject* object, size_t count, GXVertexAttributeType type);

	/** \fn void gxBindObject(GXObject* object)
	 *  \brief Binds all data stored in object, effectively making it work
	 *  \param object Object pointer
	 */
	GX_API void gxBindObject(GXObject* object);

	/** \fn GXWindow* gxAsWindow(GXResource* res)
	 *  \brief Returns a memory pointer to GXWindow from the specified GXResource.
	 *  \param res Resource memory pointer
	 *  \return Associated window
	 */
	GX_API GXWindow* gxAsWindow(GXResource* res);

	/** \fn GXWindow* gxCreateWindow(bool vsync, bool show, int width, int height, const char* title)
	 *  \brief Creates and initiatlizes an GXWindow in memory.
	 *  \param vsync Sync frame rate wuth refresh rate of monitor to prevent "screen tearing"
	 *  \param show Should the window be shown or hidden after creation
	 *  \param width The desired width, in screen coordinates, of the window content area
	 *  \param height The desired height, in screen coordinates, of the window content area
	 *  \param title The title of the window
	 *  \return Pointer to window
	 *  \note All memory is managed by the libary and does not account for the manual freeing of memory outside of its codebase. Furthermore, events regarding the framebuffer does NOT interrupt drawing, this may be optional in the future.
	 */
	GX_API GXWindow* gxCreateWindow(bool vsync, bool show, int width, int height, const char* title);

	/** \fn void gxWindowSetDrawCallback(GXWindow* win, GXDrawCallback cb)
	 *  \brief Assigns the draw callback for the respective GXWindow.
	 *  \param win Pointer to window to assign callback to
	 *  \param cb Callback (GXDrawCallback)
	 */
	GX_API void gxWindowSetDrawCallback(GXWindow* win, GXDrawCallback cb);

	/** \fn void gxWindowClose(GXWindow* win)
	 *  \brief Inidicates to the libary, that the specified window should close.
	 *  \param win GXWindow to close
	 */
	GX_API void gxWindowClose(GXWindow* win);

	/** \fn bool gxWindowShouldClose(GXWindow* win)
	 *  \brief Returns whether the status of the specified window indicates it should close.
	 *  \param win The GXWindow to query
	 *  \return true if the window should close, false if otherwise.
	 */
	GX_API bool gxWindowShouldClose(GXWindow* win);

	/** \fn bool gxDestroyResource(GXResource* resource)
	 *  \brief Destroy and free the specified resource.
	 *  \param resource The GXResource to destroy
	 *  \return true if the resource was successfully destroyed, false if it was not (likely due to memory issues).
	 */
	GX_API bool gxDestroyResource(GXResource* resource);

	/** \fn void gxUpdateViewport(GXWindow* win)
	 *  \brief Updates the viewport for a specific window (equivalent to gxViewport(0, 0, win->width, win->height)).
	 *  \param win The GXWindow to update the viewport for.
	 * 
	 *  \note This should only be used in the drawing callback of a window.
	 *  
	 *  \see gxViewport()
	 */
	GX_API void gxUpdateViewport(GXWindow* win);

	/** \fn void gxSetBackground(float r, float g, float b, float a)
	 *  \brief Sets the background for the respective graphical context.
	 *  \param r R/RED channel value ranged between 0.0 to 1.0
	 *  \param g G/GREEN channel value ranged between 0.0 to 1.0
	 *  \param b B/BLUE channel value ranged between 0.0 to 1.0
	 *  \param a A/ALPHA channel value ranged between 0.0 to 1.0
	 *
	 * Is the same as doing:
	 * \code
	 * gxClearColor(r, g, b, a);
	 * gxClearColorBuffer();
	 * \endcode
	 *
	 * \see gxClearColor()
	 * \see gxClearColorBuffer()
	 */
	GX_API void gxSetBackground(float r, float g, float b, float a);

	/** \fn void gxViewport(int x, int y, int w, int h)
	 *  \brief Sets the viewport for the respective graphical context.
	 *  \param x Viewport x position
	 *  \param y Viewport y position
	 *  \param w Viewport width
	 *  \param h Viewport height
	 *
	 *  \note This is the same as glViewport, and simply a wrapper to allow easier binding implementation.
	 */
	GX_API void gxViewport(int x, int y, int w, int h);

	/** \fn void gxClearColor(float r, float g, float b, float a)
	 *  \brief Sets the clear color for the respective graphical context.
	 *  \param r R/RED channel value ranged between 0.0 to 1.0
	 *  \param g G/GREEN channel value ranged between 0.0 to 1.0
	 *  \param b B/BLUE channel value ranged between 0.0 to 1.0
	 *  \param a A/ALPHA channel value ranged between 0.0 to 1.0
	 *
	 *  \note This is the same as glClearColor(...), and simply a wrapper to allow easier binding implementation.
	 */
	GX_API void gxClearColor(float r, float g, float b, float a);

	/** \fn void gxClear(unsigned int bit)
	 *  \brief Sets the bitplane area for the respective graphical context.
	 *  \param bit GXBufferBit
	 *
	 *  \note This is the same as glClear(...), and simply a wrapper to allow easier binding implementation.
	 *
	 *  \see GXBufferBit
	 */
	GX_API void gxClear(unsigned int bit);

	/** \fn GXShaderCompilationResult gxCompileGLSLShader(const char* shader_src, GXShaderType shader_type)
	 *  \brief Compiles a GLSL shader from source code.
	 *  \param shader_src Source code of the shader
	 *  \param shader_type Type of the shader (vertex or fragment)
	 *  \return Compilation result.
	 * 
	 *  \see GXShaderType
	 *  \see GXShaderCompilationResult
	 */
	GX_API GXShaderCompilationResult gxCompileGLSLShader(const char* shader_src, GXShaderType shader_type);
	
	/** \fn GXProgramCompilationResult gxCompileGLSLProgram(const char* vertex_shader_src, const char* fragment_shader_src)
	 *  \brief Compiles a GLSL vertex and fragment shader from source code.
	 *  \param vertex_shader_src Source code of the vertex shader
	 *  \param fragment_shader_src Source code of the fragment shader
	 *  \return Compilation result.
	 * 
	 *  \see GXProgramCompilationResult
	 */
	GX_API GXProgramCompilationResult gxCompileGLSLProgram(const char* vertex_shader_src, const char* fragment_shader_src);

	/** \fn uint32_t gxGenVertexArrayObject()
	 *  \brief Generates a new Vertex Array Object (VAO).
	 *  \return Vertex Array Object (VAO) id.
	 */
	GX_API uint32_t gxGenVertexArrayObject();

	/** \fn void gxBindVertexArrayObject(uint32_t vao)
	 *  \brief Binds a Vertex Array Object (VAO) for use.
	 *  \param vao Vertex array object (VAO) id to bind
	 */
	GX_API void gxBindVertexArrayObject(uint32_t vao);

	/** \fn uint32_t gxGenBufferObject(GXBufferType buffer_type, GXBufferUsageType buffer_usage, size_t size, void* data)
	 *  \brief Generates a new (Array/Element Array) Buffer Object.
	 *  \param buffer_type Type of buffer
	 *  \param buffer_usage Buffer usage type
	 *  \param size Size of	`data`
	 *  \param data Data to place in buffer
	 *  \returns (Array/Element Array) Buffer Object id
	 * 
	 *  \see GXBufferType
	 *  \see GXBufferUsageType
	 */
	GX_API uint32_t gxGenBufferObject(GXBufferType buffer_type, GXBufferUsageType buffer_usage, size_t size, void* data);

	/** \fn void gxBindBufferObject(GXBufferType buffer_type, uint32_t buffer)
	 *  \brief Binds a (Array/Element Array) Buffer Object for use.
	 *  \param buffer_type Type of buffer
	 *  \param buffer (Array/Element Array) Buffer Object id
	 * 
	 *  \see GXBufferType
	 */
	GX_API void gxBindBufferObject(GXBufferType buffer_type, uint32_t buffer);

	/** \fn void* gxMapBufferRange(GXBufferType buffer_type, size_t offset, size_t length, GXMappingBits bits)
	 *  \brief Maps a range of a (Array/Element Array) Buffer Object to CPU memory, allowing access (based of `bits`).
	 *  \param buffer_type Type of buffer to map
	 *  \param offset Offset in bytes from the start of the buffer
	 *  \param length Length in bytes of the range to map
	 *  \param bits Mapping bits that control how the buffer is accessed
	 *  \return Pointer to the mapped buffer range, or `nullptr` (or its respective alternative) on failure.
	 * 
	 *  \note This is equivalent to glMapBufferRange, and simply a wrapper to allow easier binding implementation.
	 */
	GX_API void* gxMapBufferRange(GXBufferType buffer_type, size_t offset, size_t length, GXMappingBits bits);

	/** \fn void gxUnmapBuffer(GXBufferType buffer_type)
	 *  \brief Unmaps a previously mapped (Array/Element Array) Buffer Object.
	 *  \param buffer_type Type of buffer to unmap
	 *  \return true if the buffer was successfully unmapped, false if it was not (likely due to memory issues).
	 *
	 *  \note This is equivalent to glUnmapBuffer, and simply a wrapper to allow easier binding implementation.
	 */
	GX_API bool gxUnmapBuffer(GXBufferType buffer_type);

	/** \fn void gxBufferData(GXBufferType buffer_type, size_t size, void* data, GXBufferUsageType usage)
	 *  \brief Allocates and initializes a (Array/Element Array) Buffer Object with data.
	 *  \param buffer_type Type of buffer to allocate
	 *  \param size Size of the buffer in bytes
	 *  \param data Data to initialize the buffer with
	 *  \param usage Buffer usage type
	 *
	 *  \note This is equivalent to glBufferSubData, and simply a wrapper to allow easier binding implementation.
	 */
	GX_API void gxBufferSubData(GXBufferType buffer_type, size_t offset, size_t length, void* data);

	/** \fn bool gxUpdateBufferObject(GXBufferType type, uint32_t bo, size_t offset, size_t length, void* data)
	 *  \brief Updates data in a (Array/Element Array/Uniform) Buffer Object.
	 *  \param type Type of buffer to update
	 *  \param bo Buffer Object id to update
	 *  \param offset Offset in bytes from the start of the buffer
	 *  \param length Length in bytes of the data to update
	 *  \param data Pointer to the new data
	 *  \return true if the buffer was successfully updated, false if it was not (likely due to memory issues).
	 */
	GX_API bool gxUpdateBufferObject(GXBufferType type, uint32_t bo, size_t offset, size_t length, void* data);

	/** \fn void gxUpdateVertices(GXObject* object, size_t offset, size_t length, void* data)
	 *  \brief Updates the vertex data of a GXObject.
	 *  \param object Pointer to the GXObject to update
	 *  \param offset Offset in bytes from the start of the vertex buffer
	 *  \param length Length in bytes of the data to update
	 *  \param data Pointer to the new vertex data
	 *  \return true if the vertices were successfully updated, false if it was not (likely due to memory issues).
	 *
	 */
	GX_API bool gxUpdateVertices(GXObject* object, size_t offset, size_t length, void* data);

	/** \fn bool gxUpdateElements(GXObject* object, size_t offset, size_t length, void* data)
	 *  \brief Updates the index data of a GXObject.
	 *  \param object Pointer to the GXObject to update
	 *  \param offset Offset in bytes from the start of the element buffer
	 *  \param length Length in bytes of the data to update
	 *  \param data Pointer to the new index data
	 *  \return true if the elements were successfully updated, false if it was not (likely due to memory issues).
	 * 
	 */
	GX_API bool gxUpdateElements(GXObject* object, size_t offset, size_t length, void* data);

	/** \fn bool gxUpdateUniformBlock(uint32_t ubo, size_t offset, size_t length, void* data)
	 *  \brief Updates the index data of a GXObject.
	 *  \param ubo Uniform Buffer Object id to update
	 *  \param offset Offset in bytes from the start of the uniform buffer
	 *  \param length Length in bytes of the data to update
	 *  \param data Pointer to the new index data
	 *  \return true if the uniforms were successfully updated, false if it was not (likely due to memory issues).
	 *
	 */
	GX_API bool gxUpdateUniformBlock(uint32_t ubo, size_t offset, size_t length, void* data);

	/** \fn void gxSetVertexAttribute(GXObject* object, uint32_t index, int size, GXVertexAttributeType type, bool normalize, size_t stride, void* pointer)
	 *  \brief Sets a vertex attribute for a GXObject.
	 *  \param object Pointer to the GXObject to set the attribute for
	 *  \param index Index of the vertex attribute
	 *  \param size Number of components per vertex attribute (1, 2, 3, or 4)
	 *  \param type Data type of the vertex attribute (e.g., float, int)
	 *  \param normalize Whether to normalize the vertex attribute data
	 *  \param stride Byte offset between consecutive vertex attributes
	 *  \param pointer Pointer to the vertex attribute data in the buffer
	 *  
	 *  \see GXVertexAttributeType
	 */
	GX_API void gxSetVertexAttribute(GXObject* object, uint32_t index, int size, GXVertexAttributeType type, bool normalize, size_t stride, void* pointer);

	/** \fn void gxEnableVertexAttribute(GXObject* object, uint32_t index)
	 *  \brief Enables a vertex attribute for a GXObject.
	 *  \param object Pointer to the GXObject to enable the attribute for
	 *  \param index Index of the vertex attribute to enable
	 */
	GX_API void gxEnableVertexAttribute(GXObject* object, uint32_t index);

	/** \fn void gxDisableVertexAttribute(GXObject* object, uint32_t index)
	 *  \brief Disables a vertex attribute for a GXObject.
	 *  \param object Pointer to the GXObject to disable the attribute for
	 *  \param index Index of the vertex attribute to disable
	 */
	GX_API void gxDisableVertexAttribute(GXObject* object, uint32_t index);

	/** \fn void gxBindBufferBase(GXBufferType type, uint32_t binding_point, uint32_t bo)
	 *  \brief Binds a Buffer Object to a specific binding point.
	 *  \param type Type of buffer to bind (e.g., uniform, array)
	 *  \param binding_point Binding point index to bind the buffer to
	 *  \param bo Buffer Object id to bind
	 */
	GX_API void gxBindBufferBase(GXBufferType type, uint32_t binding_point, uint32_t bo);

	/** \fn void gxBindUniformBlock(uint32_t binding_point, uint32_t ubo)
	 *  \brief Binds a Uniform Block to a specific binding point for a shader.
	 *  \param binding_point Binding point index to bind the buffer to
	 *  \param ubo Uniform Buffer Object id to bind
	 */
	GX_API void gxBindUniformBlock(uint32_t binding_point, uint32_t ubo);

	/** \fn void gxUseShader(GXObject* object)
	 *  \brief Tells the program to use the shader associated with the object.
	 *  \param object Pointer to GXObject and therefore its shader
	 */
	GX_API void gxUseShader(GXObject* object);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __GX_INCLUDE_GX_H__
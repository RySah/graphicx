#define GX_CMAKE_GL

#include "gx/gx.h"

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <GLFW/glfw3.h>

template <typename Container, typename Iterator>
void _container_unordered_remove(Container& c, Iterator it) {
    if (it == c.end()) return;
    auto last = std::prev(c.end());
    if (it != last) {
        *it = std::move(*last);
    }
    c.pop_back();  // Only works with containers that support pop_back
}

typedef std::unordered_set<GXResource*> _app_resource_collection_t;
typedef std::unordered_set<GXKeyboardCallback> _app_keyboard_callback_collection_t;


static GXResourceStatus operator|(GXResourceStatus lhs, GXResourceStatus rhs) {
    return static_cast<GXResourceStatus>(static_cast<int>(lhs) | static_cast<int>(rhs));
}
static GXResourceStatus& operator|=(GXResourceStatus& lhs, GXResourceStatus rhs) {
    lhs = lhs | rhs; 
    return lhs;
}
static GXResourceStatus operator&(GXResourceStatus lhs, GXResourceStatus rhs) {
    return static_cast<GXResourceStatus>(static_cast<int>(lhs) & static_cast<int>(rhs));
}
static GXResourceStatus& operator&=(GXResourceStatus& lhs, GXResourceStatus rhs) {
    lhs = lhs & rhs;
    return lhs;
}

static GXApplication* m_app = nullptr;

const char* gxInit() {
    if (!glfwInit()) return "Failed to initialize GLFW";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    return nullptr;
}

void gxTerminate() {
    if (m_app) gxDestroyApplication(m_app);
    glfwTerminate();
}

void gxAddKeyboardCallback(GXKeyboardCallback cb) {
    if (!m_app) return;
    ((_app_keyboard_callback_collection_t*)m_app->keyboard_cb_collection_vec_ptr)->insert(cb);
}

void gxClearKeyboardCallback() {
    if (!m_app) return;
    ((_app_keyboard_callback_collection_t*)m_app->keyboard_cb_collection_vec_ptr)->clear();
}

void gxDestroyApplication(GXApplication* application) {
    _app_resource_collection_t resource_collection_clone = *((_app_resource_collection_t*)application->resource_collection_vec_ptr);
    for (GXResource* res : resource_collection_clone) {
        if (res) gxDestroyResource(res);
	}
    _app_keyboard_callback_collection_t* kcb = (_app_keyboard_callback_collection_t*)application->keyboard_cb_collection_vec_ptr;
    _app_resource_collection_t* rs = (_app_resource_collection_t*)application->resource_collection_vec_ptr;
	delete kcb;
    delete rs;
    delete application;
}

GXApplication* gxCreateApplication(GXApplicationOptions options) {
    if (m_app) gxDestroyApplication(m_app);
    m_app = new GXApplication{};
    m_app->options = options;
    m_app->keyboard_cb_collection_vec_ptr = new _app_keyboard_callback_collection_t();
    m_app->resource_collection_vec_ptr = new _app_resource_collection_t();
    return m_app;
}

GXApplication* gxGetApplication() {
    return m_app;
}

void gxExec() {
    if (!m_app) return;

    _app_resource_collection_t* resource_collection = (_app_resource_collection_t*)m_app->resource_collection_vec_ptr;
    _app_keyboard_callback_collection_t* keyboard_cb_collection = (_app_keyboard_callback_collection_t*)m_app->keyboard_cb_collection_vec_ptr;

    int width, height;
    GXResource* res = nullptr;
	GXWindow* win = nullptr; GXObject* obj = nullptr;
    GLFWwindow* glfwWin = nullptr;

    bool shouldRun = true;

    while (shouldRun) {
        glfwPollEvents();

        shouldRun = false;
        std::unordered_set<GXResource*> removal_cache;
        for (auto res : *resource_collection) {
            if (!res) {
                continue;
            }
            if (res->type == GX_RESOURCE_WINDOW) {
                win = gxAsWindow(res);
                glfwWin = static_cast<GLFWwindow*>(win->internal);

                if (glfwWindowShouldClose(glfwWin)) {
                    //gxDestroyResource(res);
                    removal_cache.insert(res);
                    continue; // Skip increment since element is removed
                }

                if (win->show && !(res->status & GX_RESOURCE_STATUS_SHOWING)) {
                    glfwShowWindow(glfwWin);
                    res->status |= GX_RESOURCE_STATUS_SHOWING;
                }
                else if (!win->show && (res->status & GX_RESOURCE_STATUS_SHOWING)) {
                    glfwHideWindow(glfwWin);
                    res->status &= GX_RESOURCE_STATUS_SHOWING_MASK;
                }

                if (win->show) shouldRun |= true;
            }
            
        }
        for (auto res : removal_cache) gxDestroyResource(res);


        if (!shouldRun) break;

        for (auto it = resource_collection->begin(); it != resource_collection->end(); it++) {
            res = *it;
            if (!res || res->type != GX_RESOURCE_WINDOW) continue;

            win = gxAsWindow(res);
            if (!win->show || !win->draw_callback) continue;

            glfwWin = static_cast<GLFWwindow*>(win->internal);
            glfwMakeContextCurrent(glfwWin);

            glfwGetFramebufferSize(glfwWin, &width, &height);
            win->width = width;
            win->height = height;

            win->draw_callback(win);

            glfwSwapBuffers(glfwWin);
        }
    }
}

GXObject* gxAsObject(GXResource* res) { return static_cast<GXObject*>(res->resource); }

GXObject* gxCreateObject(uint32_t shader_program, uint32_t vao, uint32_t vbo, uint32_t ebo, void* user_data) {
    if (!m_app) return nullptr;
    GXResource* resource = new GXResource{};
    resource->type = GX_RESOURCE_OBJECT;
    resource->status = GX_RESOURCE_STATUS_NONE;
    GXObject* obj = new GXObject{ shader_program, vao, vbo, ebo, resource, user_data };
    resource->resource = obj;

    _app_resource_collection_t* resource_collection = (_app_resource_collection_t*)m_app->resource_collection_vec_ptr;
    resource_collection->insert(resource);

    return obj;
}

GXObject* gxCreateRenderObjectWithElements(uint32_t shader_program, GXBufferUsageType vert_buffer_usage, size_t vert_size, void* vert_data, GXBufferUsageType elem_buffer_usage, size_t elem_size, void* elem_data, void* user_data) {
    return gxCreateObject(
        shader_program,
        gxGenVertexArrayObject(),
        vert_data ? gxGenBufferObject(GX_BUFFER_TYPE_ARRAY, vert_buffer_usage, vert_size, vert_data) : 0,
        elem_data ? gxGenBufferObject(GX_BUFFER_TYPE_ELEMENT_ARRAY, elem_buffer_usage, elem_size, elem_data) : 0,
        user_data
    );
}

GXObject* gxCreateRenderObject(uint32_t shader_program, GXBufferUsageType vert_buffer_usage, size_t vert_size, void* vert_data, void* user_data) {
	return gxCreateRenderObjectWithElements(shader_program, vert_buffer_usage, vert_size, vert_data, GX_BUFFER_USAGE_TYPE_STATIC, 0, nullptr, user_data);
}

void gxDrawVertices(GXObject* object, size_t offset, size_t count) {
    gxBindVertexArrayObject(object->vao);
    glDrawArrays(GL_TRIANGLES, offset, count);
}

void gxDrawElements(GXObject* object, size_t count, GXVertexAttributeType type) {
    gxBindVertexArrayObject(object->vao);
    glDrawElements(GL_TRIANGLES, count, type, nullptr);
}

void gxBindObject(GXObject* object) {
    if (!object->vao) return;
    gxBindVertexArrayObject(object->vao);
    if (object->vbo) gxBindBufferObject(GX_BUFFER_TYPE_ARRAY, object->vbo);
    if (object->ebo) gxBindBufferObject(GX_BUFFER_TYPE_ELEMENT_ARRAY, object->ebo);
}

GXWindow* gxAsWindow(GXResource* res) { return static_cast<GXWindow*>(res->resource); }

GXWindow* gxCreateWindow(bool vsync, bool show, int width, int height, const char* title) {
	if (!m_app) return nullptr;
    glfwWindowHint(GLFW_VISIBLE, show ? GLFW_TRUE : GLFW_FALSE);
#if _DEBUG
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
    GXResource* resource = new GXResource{};
    resource->type = GX_RESOURCE_WINDOW;
    resource->status = GX_RESOURCE_STATUS_NONE;
    GXWindow* window = new GXWindow;
    resource->resource = window;
    GLFWwindow* glfwWin = nullptr;

    *window = { resource, width, height, title, show, nullptr, nullptr };
    window->internal = glfwWin = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (!window->internal) {
        delete resource;
        return nullptr;
    }

    glfwMakeContextCurrent(glfwWin);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwDestroyWindow(glfwWin);
        delete resource;
        return nullptr;
    }
    if (vsync) glfwSwapInterval(1);

    glfwSetWindowUserPointer(glfwWin, resource);

    glfwSetWindowCloseCallback(glfwWin,
        [](GLFWwindow* gw) {
            if (GXResource* res = static_cast<GXResource*>(glfwGetWindowUserPointer(gw))) {
                res->status |= GX_RESOURCE_STATUS_SHOULD_CLOSE;
            }
        });

    glfwSetWindowRefreshCallback(glfwWin,
        [](GLFWwindow* gw) {
            if (GXResource* res = static_cast<GXResource*>(glfwGetWindowUserPointer(gw))) {
                GXWindow* win = gxAsWindow(res);
                win->draw_callback(win);
                glfwSwapBuffers(gw);
            }
        });

    glfwSetKeyCallback(glfwWin,
        [](GLFWwindow* gw, int key, int scancode, int action, int mods) {
            if (GXResource* res = static_cast<GXResource*>(glfwGetWindowUserPointer(gw))) {
                GXWindow* win = gxAsWindow(res);
                _app_keyboard_callback_collection_t* keyboard_cb_collection = (_app_keyboard_callback_collection_t*)m_app->keyboard_cb_collection_vec_ptr;
                for (auto cb : *keyboard_cb_collection) {
                    if (cb) {
                        cb(m_app, win, static_cast<GXKey>(key), scancode, static_cast<GXKeyAction>(action), mods);
                    }
                }
                
            }
        });

    _app_resource_collection_t* resource_collection = (_app_resource_collection_t*)m_app->resource_collection_vec_ptr;
    resource_collection->insert(resource);

    return window;
}

void gxWindowSetDrawCallback(GXWindow* win, GXDrawCallback cb) {
    if (win) win->draw_callback = cb;
}

void gxWindowClose(GXWindow* win) {
    if (win) {
        if (GLFWwindow* glfwWin = static_cast<GLFWwindow*>(win->internal)) {
            glfwSetWindowShouldClose(glfwWin, GLFW_TRUE);
        }
    }
}

bool gxWindowShouldClose(GXWindow* win) {
    return win && glfwWindowShouldClose(static_cast<GLFWwindow*>(win->internal));
}

bool gxDestroyResource(GXResource* resource) {
    if (!m_app) return false;
    if (!resource) return false;

    _app_resource_collection_t* resource_collection = (_app_resource_collection_t*)m_app->resource_collection_vec_ptr;
    
    resource_collection->erase(resource);

    switch (resource->type) {
    case GX_RESOURCE_WINDOW:
        if (auto win = gxAsWindow(resource)) {
            glfwDestroyWindow(static_cast<GLFWwindow*>(win->internal));
        }
        break;
    case GX_RESOURCE_OBJECT:
        if (auto obj = gxAsObject(resource)) {
            if (obj->vao) glDeleteVertexArrays(1, &obj->vao);
            if (obj->vbo) glDeleteBuffers(1, &obj->vbo);
            if (obj->ebo) glDeleteBuffers(1, &obj->ebo);
        }
    }
    delete resource;

    return true;
}

void gxUpdateViewport(GXWindow* win) {
    gxViewport(0, 0, win->width, win->height);
}

void gxSetBackground(float r, float g, float b, float a) {
    gxClearColor(r, g, b, a);
    gxClear(GX_COLOR_BUFFER_BIT);
}

void gxViewport(int x, int y, int w, int h) { glViewport(x, y, w, h); }
void gxClearColor(float r, float g, float b, float a) { glClearColor(r, g, b, a); }
void gxClear(unsigned int bit) { glClear(bit); }

GXShaderCompilationResult gxCompileGLSLShader(const char* shader_src, GXShaderType shader_type) {
    GXShaderCompilationResult result = {};
    result.handle = glCreateShader(shader_type);
    glShaderSource(result.handle, 1, &shader_src, NULL);
    glCompileShader(result.handle);
    glGetShaderiv(result.handle, GL_COMPILE_STATUS, &result.success);
    if (!result.success)
        glGetShaderInfoLog(result.handle, sizeof(result.info_log), NULL, result.info_log);
    return result;
}

GXProgramCompilationResult gxCompileGLSLProgram(const char* vertex_shader_src, const char* fragment_shader_src) {
    GXProgramCompilationResult result = {};
    result.vertex_result = gxCompileGLSLShader(vertex_shader_src, GX_GLSL_VERTEX_SHADER);
    result.fragment_result = gxCompileGLSLShader(fragment_shader_src, GX_GLSL_FRAGMENT_SHADER);
    if (!result.vertex_result.success || !result.fragment_result.success) return result;
    result.program = glCreateProgram();
    glAttachShader(result.program, result.vertex_result.handle);
    glAttachShader(result.program, result.fragment_result.handle);
    glLinkProgram(result.program);
    glGetProgramiv(result.program, GL_LINK_STATUS, &result.success);
    if (!result.success) glGetProgramInfoLog(result.program, sizeof(result.program_log), NULL, result.program_log);
    glDeleteShader(result.vertex_result.handle);
    glDeleteShader(result.fragment_result.handle);
    return result;
}

uint32_t gxGenVertexArrayObject() {
    uint32_t vaoId;
    glGenVertexArrays(1, &vaoId); 
	glBindVertexArray(0);
	return vaoId;
}

void gxBindVertexArrayObject(uint32_t vao) { glBindVertexArray(vao); }

uint32_t gxGenBufferObject(GXBufferType buffer_type, GXBufferUsageType buffer_usage, size_t size, void* data) {
    GLuint xboId;
    glGenBuffers(1, &xboId);
    gxBindBufferObject(buffer_type, xboId);
    glBufferData(buffer_type, size, data, buffer_usage);  // Fixed: using buffer_usage instead of buffer_type
    gxBindBufferObject(buffer_type, 0);
    return xboId;
}

void gxBindBufferObject(GXBufferType buffer_type, uint32_t buffer) { glBindBuffer(buffer_type, buffer); }

void* gxMapBufferRange(GXBufferType buffer_type, size_t offset, size_t length, GXMappingBits bits) { return glMapBufferRange(buffer_type, offset, length, bits); }

bool gxUnmapBuffer(GXBufferType buffer_type) { return glUnmapBuffer(buffer_type); }

void gxBufferSubData(GXBufferType buffer_type, size_t offset, size_t length, void* data) { glBufferSubData(buffer_type, offset, length, data); }

bool gxUpdateBufferObject(GXBufferType type, uint32_t bo, size_t offset, size_t length, void* data) {
    if (!bo || !data) return false;
    gxBindBufferObject(type, bo);
    auto dest = gxMapBufferRange(type, offset, length, GX_MAP_WRITE_BIT);
    if (!dest) return false;
    memcpy(dest, data, length);
    auto result = gxUnmapBuffer(type);
    gxBindBufferObject(type, 0);
    return result;
}

bool gxUpdateVertices(GXObject* object, size_t offset, size_t length, void* data) {
    if (!object) return false;
    return gxUpdateBufferObject(GX_BUFFER_TYPE_ARRAY, object->vbo, offset, length, data);
}

bool gxUpdateElements(GXObject* object, size_t offset, size_t length, void* data) {
    if (!object) return false;
    return gxUpdateBufferObject(GX_BUFFER_TYPE_ELEMENT_ARRAY, object->ebo, offset, length, data);
}

bool gxUpdateUniformBlock(uint32_t ubo, size_t offset, size_t length, void* data) {
    return gxUpdateBufferObject(GX_BUFFER_TYPE_UNIFORM, ubo, offset, length, data);
}

void gxSetVertexAttribute(GXObject* object, uint32_t index, int size, GXVertexAttributeType type, bool normalize, size_t stride, void* pointer) {
    if (!object) return;
    gxBindBufferObject(GX_BUFFER_TYPE_ARRAY, object->vbo);
    glVertexAttribPointer(index, size, type, normalize, stride, pointer);
}

void gxEnableVertexAttribute(GXObject* object, uint32_t index) { 
    if (!object) return;
    glEnableVertexArrayAttrib(object->vao, index); 
}

void gxDisableVertexAttribute(GXObject* object, uint32_t index) { 
    if (!object) return;
    glDisableVertexArrayAttrib(object->vao, index); 
}

void gxBindBufferBase(GXBufferType type, uint32_t binding_point, uint32_t bo) {
	glBindBufferBase(type, binding_point, bo);
}

void gxBindUniformBlock(uint32_t binding_point, uint32_t ubo) {
    gxBindBufferBase(GX_BUFFER_TYPE_UNIFORM, binding_point, ubo);
}

void gxUseShader(GXObject* object) {
    glUseProgram(object->shader_program);
}

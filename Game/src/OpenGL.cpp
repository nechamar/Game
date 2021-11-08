#include "OpenGL.h"
#include "Core.h"

handler opengl_handler;




static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}


static void checkGLError(const char* where, int line) {
    GLenum err = glGetError();
    if (err == GL_NONE)
        return;

    std::string errString = "<unknown>";
    switch (err) {
    case GL_INVALID_ENUM:
        errString = "GL_INVALID_ENUM";
        break;
    case GL_INVALID_VALUE:
        errString = "GL_INVALID_VALUE";
        break;
    case GL_INVALID_OPERATION:
        errString = "GL_INVALID_OPERATION";
        break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        errString = "GL_INVALID_FRAMEBUFFER_OPERATION";
        break;
    case GL_OUT_OF_MEMORY:
        errString = "GL_OUT_OF_MEMORY";
        break;
    default:;
    }
    if (where == 0 || *where == 0)
        std::cerr << "GL error occurred: " << errString << std::endl;
    else
        std::cerr << "GL error occurred in " << where << ":" << line << ": " << errString << std::endl;
}

#define CHECK_GL_ERROR() do { checkGLError(__FUNCTION__, __LINE__); } while(0)


void window_resize_callback(GLFWwindow* window, int width, int height)
{
    opengl_handler.window_width = width;
    opengl_handler.window_height = height;
    glViewport(0, 0, width, height);
}

static GLuint createShaderFromSource(GLenum eShaderType, const std::string& strShaderText) {
    GLuint shader = glCreateShader(eShaderType);
    const char* strFileData = strShaderText.c_str();
    glShaderSource(shader, 1, &strFileData, NULL);

    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar* strInfoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

        const char* strShaderType = NULL;
        switch (eShaderType) {
        case GL_VERTEX_SHADER: strShaderType = "vertex";   break;
        case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
        case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
        }

        std::cerr << "Compile failure in " << strShaderType << " shader:" << std::endl;
        std::cerr << strInfoLog;

        delete[] strInfoLog;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}


static GLuint createShaderFromFile(GLenum eShaderType, const std::string& filename) {
    FILE* f = fopen(filename.c_str(), "rb");
    if (!f) {
        std::cerr << "Unable to open file " << filename << " for reading" << std::endl;
        return 0;
    }
    else
        std::cout << "loading shader: " << filename << std::endl;

    fseek(f, 0, SEEK_END);
    int length = ftell(f);
    fseek(f, 0, SEEK_SET);

    char* buffer = new char[length + 1];
    int length2 = fread(buffer, 1, length, f);
    fclose(f);
    buffer[length] = '\0';

    GLuint sh = createShaderFromSource(eShaderType, buffer);
    delete[] buffer;
    return sh;
}

static bool linkProgram(GLuint program) {
    glLinkProgram(program);

    GLint status = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    CHECK_GL_ERROR();

    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

        GLchar* strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
        return false;
    }

    return true;
}

static GLuint createProgram(const GLuint* shaders) {
    GLuint program = glCreateProgram();

    while (shaders && *shaders)
        glAttachShader(program, *shaders++);
    CHECK_GL_ERROR();

    if (!linkProgram(program)) {
        return 0;
    }

    return program;
}



void compile_shaders() {
	GLuint shaders[] = {
		createShaderFromFile(GL_VERTEX_SHADER,  "src\\Shaders\\BasicShader.vert"),
		createShaderFromFile(GL_FRAGMENT_SHADER,"src\\Shaders\\BasicShader.frag"),
		0,
	};

	// Create Shader Program Object and get its reference
	opengl_handler.shader_program = createProgram(shaders);
}

int init_opengl()
{
	// Initialize GLFW
	glfwSetErrorCallback(error_callback);
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	opengl_handler.window = glfwCreateWindow(opengl_handler.window_width, opengl_handler.window_height, "ImGui + GLFW", NULL, NULL);
    // Error check if the window fails to create
	if (opengl_handler.window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(opengl_handler.window);

	//Load GLAD so it configures OpenGL
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
		glfwTerminate();
		return -1;
	}

	// Specify the viewport of OpenGL in the Window
    glViewport(0, 0, opengl_handler.window_width, opengl_handler.window_height);

	compile_shaders();
}

void finalize_opengl()
{
	glDeleteProgram(opengl_handler.shader_program);
	// Delete window before ending the program
	glfwDestroyWindow(opengl_handler.window);
	// Terminate GLFW before ending the program
	glfwTerminate();
}
#include <vector>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "rendering/Renderer.h"
#include "Errors.h"

#include "Satellite.h"

#include "maths/vec3.h"
#include "maths/vec2.h"


// Request NVIDIA high-performance GPU on hybrid systems
extern "C" {
	__declspec(dllexport) unsigned long NvOptimusEnablement = 1;
}

const int WIDTH = 1800;
const int HEIGHT = 1300;

class OrbitEngine
{
private:
    GLFWwindow* window;
    std::unique_ptr<Renderer> renderer;
   
    unsigned int windowWidth;
    unsigned int windowHeight;

    std::vector<Satellite> satellites = std::vector<Satellite>{
        Satellite(vec3(1.0f, 0.0f, 0.0f), 0.3f, 1.0f, vec3(0.7, 0.5, 0.6)),
        Satellite(vec3(0.0f, 1.0f, 0.0f), 0.4f, 1.0f, vec3(0.3, 0.6, 0.2)),
        Satellite(vec3(0.1f, 0.5f, 0.0f), 0.45f, 1.0f, vec3(0.2, 0.3, 0.6)),
        Satellite(vec3(0.0f, 0.0f, 0.0f), 0.5f, 1.0f, vec3(0.8, 0.3, 0.4))
    };

public:
    OrbitEngine(int width, int height)
        : windowWidth(width), windowHeight(height), renderer(nullptr), window(nullptr)
    {}


    bool createWindow()
    {
        // Initialize the library
        if (!glfwInit())
            return -1;

        // Specify the version required
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

        // Specify use core profile
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create a windowed mode window and its OpenGL context
        window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);

        // Check if window was created succesfully
        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        // Set the interval to swap front and back buffers
        glfwSwapInterval(1); // Only swap once per screen draw (this doesnt actually do anything when using vsync)

        // Make the window's context current
        glfwMakeContextCurrent(window);


        // Initialise GLEW
        if (glewInit() != GLEW_OK)
        {
            std::cout << "Failed to initialise glew" << std::endl;
        }

        // Display the GLEW version to the console
        std::cout << glGetString(GL_VERSION) << std::endl;

        // Create the renderer object
        renderer = std::make_unique<Renderer>(window, windowWidth, windowHeight);

        // Enable blending
        GLCALL(glEnable(GL_BLEND));
        GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    }

    void runSimulation()
    {
        // Main loop
        while (!glfwWindowShouldClose(window))
        {
            // Draw elements on the screen
            renderer->drawSatellites(satellites);

            // Poll for and process events
            glfwPollEvents();

            // Swap back and front buffers
            glfwSwapBuffers(window);
        }
    }
};

int main()
{
    // Create engine object
    OrbitEngine engine(WIDTH, HEIGHT);

    // Initialise OpenGL context and create window
    engine.createWindow();

    // Run the engine simulation loop
    engine.runSimulation();
}
#include <vector>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "rendering/Renderer.h"
#include "Errors.h"

#include "Satellite.h"

#include "maths/vec3.h"
#include "maths/vec2.h"


#define G 6.6743015e-11 // Gravitational constant
#define AU 1.495978707e+11 // Astronomical Unit in meters

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

    bool timeFrozen = false;
    float timeMultiplier = 6.5; // *10^n
    double currentTime;

    bool windowCreated = false;

    

    std::vector<Satellite> satellites = std::vector<Satellite>{
        //Satellite(vec3d(AU + 384400000, 0.0, 0.0), vec3d(0.0, 29780.0, 0.0), 2.0e+9, 7.346e+22, vec3(0.7, 0.7, 0.72)),
        Satellite(vec3d(AU, 0.0, 0.0), vec3d(0.0, 32784.73549, 0.0), 3.0e+9, 5.9722e+24
            , vec3(0.1f, 0.4f, 0.6f), false), // Earth
        Satellite(vec3d(0.0, 0.0, 0.0), vec3d(0.0, 0.0, 0.0), 6.37e+9, 1.988475e+30, vec3(0.95f, 0.8f, 0.3f), true) // Sun
    };

public:
    OrbitEngine(int width, int height)
        : windowWidth(width), windowHeight(height), renderer(nullptr), window(nullptr), currentTime(0.0) {}

    ~OrbitEngine()
    {
        // Destroy the renderer object
        renderer.reset();

        if (windowCreated)
        {
            // Cleanup imgui
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();

            // Destroy the window and terminate GLFW
            if (window)
            {
                glfwDestroyWindow(window);
                glfwTerminate();
            }
        }
	}


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
            return -1;
        }

        // Display the GLEW version to the console
        std::cout << glGetString(GL_VERSION) << std::endl;

        // Create the renderer object
        renderer = std::make_unique<Renderer>(window, windowWidth, windowHeight);

        // Enable blending
        GLCALL(glEnable(GL_BLEND));
        GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


        // Initialise ImGui
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 460 core");

        // Imgui styling
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 3.0f;
        style.FrameRounding = 3.0f;
        style.GrabRounding = 3.0f;

        currentTime = glfwGetTime();
        windowCreated = true;
        return 0;
    }

    void updateSatellites(float deltaTime)
    {
        for (Satellite& satellite : satellites)
        {
            vec3d acceleration;
            if (satellite.stationary == false)
            {
                // Calculate the resultant force on the satellite
                for (const Satellite& other : satellites)
                {
                    vec3d difference = other.getPosition() - satellite.getPosition();
                    if (difference.magnitude() != 0.0f)
                    {
                        double lengthCubed = pow(difference.magnitude(), 3);
                        double massGravityProduct = other.getMass() * G;

                        acceleration.x += massGravityProduct * difference.x / lengthCubed;
                        acceleration.y += massGravityProduct * difference.y / lengthCubed;
                        acceleration.z += massGravityProduct * difference.z / lengthCubed;
                    }
                }

                satellite.update(acceleration, deltaTime);
            }
        }
    }

    void drawImgui()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // FPS counter
        ImGui::SetNextWindowPos(ImVec2(windowWidth - 90, 5), ImGuiCond_Always);
        ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::End();

        // Basic Settings
        ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always);
        ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
        if (timeFrozen)
        {
            if (ImGui::Button("Play"))
            {
                timeFrozen = false;
            }
        }
        else
        {
            if (ImGui::Button("Pause"))
            {
                timeFrozen = true;
            }
        }

        // Time multiplier slider
        ImGui::SliderFloat("Time multiplier (x10^n)", &timeMultiplier, -3, 10, "%.4f");
        ImGui::End();


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void runSimulation()
    {
        double newTime;
        double deltaTime;

        unsigned int updatesPerFrame = 1000; // Number of calculations per frame
        // Main loop
        while (!glfwWindowShouldClose(window))
        {
            newTime = glfwGetTime();
            deltaTime = newTime - currentTime;
            currentTime = newTime;

            // Poll for and process events
            glfwPollEvents();

            // Update the position of each satellite
            if (not timeFrozen)
            { 
                for (unsigned int i = 0; i < updatesPerFrame; i++)
                {
                    updateSatellites(deltaTime * pow(10, timeMultiplier) / updatesPerFrame);
                }
            }

            // Draw elements on the screen
            renderer->drawSatellites(satellites);

            // Draw Gui elements
            drawImgui();

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
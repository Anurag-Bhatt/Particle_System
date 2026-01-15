#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdint>
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "BufferLayout.h"

#include "ParticleSystem.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);

float zoom = 45.0f;

const int window_height = 800;
const int window_width  = 600;

const float aspect_ratio = static_cast<float>(window_height) / window_width;
const float fov = 45.0f;

// Camera variables
glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);

Camera cam(camera_pos, camera_front, camera_up);

float delta_time = 0.0f;
float last_frame = 0.0f;
float current_frame = 0.0f;

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(window_height, window_width, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    ParticleSystem ps(100);

    fs::path vs_path = fs::current_path() / "Shaders" / "particle.vert";
    fs::path fs_path = fs::current_path() / "Shaders" / "particle.frag";

    Shader particle_shader(vs_path, fs_path);

    glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        // Calculate and update delta_time
        current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        /* Process Input */
        processInput(window);

        /* Render here */

        glClearColor(0.3f, 0.2f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ps.OnUpdate(delta_time);
        ps.OnRender(particle_shader, cam, zoom);

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            ParticleProps props;
            props.Position = { 0.0f, 0.0f, 0.0f }; // Start at center
            props.Velocity = { 0.0f, 2.0f, 0.0f }; // Move UP
            props.VelocityVariation = { 6.0f, 1.0f, 0.0f }; // Spread out in X

            props.ColorBegin = { 250 / 255.0f, 152 / 255.0f, 78 / 255.0f, 1.0f }; 
            props.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 0.0f };  

            props.SizeBegin = 0.5f;
            props.SizeEnd = 0.0f; // Shrink to nothing
            props.SizeVariation = 0.3f;

            props.LifeTime = 1.0f;

            // Emit 5 particles per frame for a thick trail
            for (int i = 0; i < 50; i++)
                ps.Emit(props);
        }

        // Wireframe mode
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    // Escape key for closing window
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    // WASD keys for movement
    float camera_speed = 5.0f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cam.update_position(delta_time * camera_front);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        //camera_pos -= (camera_speed * delta_time) * camera_front;
        cam.update_position(-(delta_time * camera_front));
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cam.update_position(-(delta_time * glm::normalize(glm::cross(camera_front, camera_up))));
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        //camera_pos += (camera_speed * delta_time) * glm::normalize(glm::cross(camera_front, camera_up));
        cam.update_position(delta_time * glm::normalize(glm::cross(camera_front, camera_up)));
    }
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
    zoom -= static_cast<float>(yOffset);
   
    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 90.0f)
        zoom = 90.0f;
}


#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

/**
 * @brief OpenGL renderer for the Kalem animation engine
 * 
 * Handles all rendering operations with minimal input handling.
 * Focuses on programmatic animation control like Manim.
 */
class Renderer {
public:
    Renderer(GLFWwindow* window);
    ~Renderer();

    // Rendering control
    void beginFrame();
    void endFrame();
    void clear();
    
    // Background
    void setBackground(float r, float g, float b);
    glm::vec3 getBackground() const;
    
    // Viewport and camera
    void setViewport(int width, int height);
    void setOrthographic(float left, float right, float bottom, float top, float near, float far);
    void setPerspective(float fov, float aspect, float near, float far);
    
    // Camera control (for programmatic camera movements)
    void setCameraPosition(float x, float y, float z);
    void setCameraTarget(float x, float y, float z);
    void setCameraUp(float x, float y, float z);
    
    // Simple input handling (minimal, for basic controls)
    bool isKeyPressed(int key) const;
    bool isMouseButtonPressed(int button) const;
    glm::vec2 getMousePosition() const;
    
    // Window info
    int getWindowWidth() const;
    int getWindowHeight() const;
    GLFWwindow* getWindow() const;

private:
    GLFWwindow* m_window;
    glm::vec3 m_background;
    glm::vec3 m_cameraPosition;
    glm::vec3 m_cameraTarget;
    glm::vec3 m_cameraUp;
    
    int m_windowWidth;
    int m_windowHeight;
    
    // Projection matrix
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    
    // Helper methods
    void updateViewMatrix();
    void setupOpenGL();
}; 
#include "Renderer.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Renderer::Renderer(GLFWwindow* window)
    : m_window(window)
    , m_background(0.1f, 0.1f, 0.1f)
    , m_cameraPosition(0.0f, 0.0f, 5.0f)
    , m_cameraTarget(0.0f, 0.0f, 0.0f)
    , m_cameraUp(0.0f, 1.0f, 0.0f)
    , m_windowWidth(1200)
    , m_windowHeight(800) {
    
    setupOpenGL();
    
    // Set up default orthographic projection for 2D animations
    setOrthographic(-600.0f, 600.0f, -400.0f, 400.0f, -1.0f, 1.0f);
    updateViewMatrix();
}

Renderer::~Renderer() {
}

void Renderer::beginFrame() {
    clear();
    
    // Set up matrices for this frame
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(&m_projectionMatrix[0][0]);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(&m_viewMatrix[0][0]);
}

void Renderer::endFrame() {
    // Swap buffers
    if (m_window) {
        glfwSwapBuffers(m_window);
    }
}

void Renderer::clear() {
    glClearColor(m_background.r, m_background.g, m_background.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setBackground(float r, float g, float b) {
    m_background = glm::vec3(r, g, b);
}

glm::vec3 Renderer::getBackground() const {
    return m_background;
}

void Renderer::setViewport(int width, int height) {
    m_windowWidth = width;
    m_windowHeight = height;
    glViewport(0, 0, width, height);
}

void Renderer::setOrthographic(float left, float right, float bottom, float top, float near, float far) {
    m_projectionMatrix = glm::ortho(left, right, bottom, top, near, far);
}

void Renderer::setPerspective(float fov, float aspect, float near, float far) {
    m_projectionMatrix = glm::perspective(glm::radians(fov), aspect, near, far);
}

void Renderer::setCameraPosition(float x, float y, float z) {
    m_cameraPosition = glm::vec3(x, y, z);
    updateViewMatrix();
}

void Renderer::setCameraTarget(float x, float y, float z) {
    m_cameraTarget = glm::vec3(x, y, z);
    updateViewMatrix();
}

void Renderer::setCameraUp(float x, float y, float z) {
    m_cameraUp = glm::vec3(x, y, z);
    updateViewMatrix();
}

bool Renderer::isKeyPressed(int key) const {
    if (!m_window) return false;
    return glfwGetKey(m_window, key) == GLFW_PRESS;
}

bool Renderer::isMouseButtonPressed(int button) const {
    if (!m_window) return false;
    return glfwGetMouseButton(m_window, button) == GLFW_PRESS;
}

glm::vec2 Renderer::getMousePosition() const {
    if (!m_window) return glm::vec2(0.0f);
    
    double xpos, ypos;
    glfwGetCursorPos(m_window, &xpos, &ypos);
    
    // Convert to world coordinates
    float worldX = (xpos - m_windowWidth * 0.5f) * 2.0f / m_windowWidth;
    float worldY = (m_windowHeight * 0.5f - ypos) * 2.0f / m_windowHeight;
    
    return glm::vec2(worldX, worldY);
}

int Renderer::getWindowWidth() const {
    return m_windowWidth;
}

int Renderer::getWindowHeight() const {
    return m_windowHeight;
}

GLFWwindow* Renderer::getWindow() const {
    return m_window;
}

void Renderer::updateViewMatrix() {
    m_viewMatrix = glm::lookAt(m_cameraPosition, m_cameraTarget, m_cameraUp);
}

void Renderer::setupOpenGL() {
    if (!m_window) return;
    
    glfwMakeContextCurrent(m_window);
    
    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return;
    }
    
    // Set up OpenGL state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Set up viewport
    glfwGetFramebufferSize(m_window, &m_windowWidth, &m_windowHeight);
    glViewport(0, 0, m_windowWidth, m_windowHeight);
    
    std::cout << "Renderer initialized successfully!" << std::endl;
} 
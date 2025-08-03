#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>

// Include our professional Kalem engine
#include "api/EasyAPI.h"

/**
 * @brief Main application entry point
 * 
 * This demonstrates the professional Kalem animation engine
 * with a simple but powerful example.
 */
int main() {
    std::cout << "=== Kalem Professional Animation Engine ===" << std::endl;
    std::cout << "Version: 1.0.0" << std::endl;
    std::cout << "Building professional educational animations..." << std::endl;
    
    // ============================================================================
    // INITIALIZE THE ENGINE
    // ============================================================================
    
    initEngine();
    
    // ============================================================================
    // CREATE A SIMPLE DEMO
    // ============================================================================
    
    std::cout << "Creating simple animation demo..." << std::endl;
    
    // Create title
    auto title = create_text(0, 300, "Kalem - Professional Animation Engine", WHITE);
    
    // Create coordinate system
    auto xAxis = create_line(-400, 0, 400, 0, GRAY);
    auto yAxis = create_line(0, -300, 0, 300, GRAY);
    
    // Create animated objects
    auto ball1 = create_circle(-200, 0, 25, RED);
    auto ball2 = create_circle(0, 0, 20, BLUE);
    auto ball3 = create_circle(200, 0, 30, GREEN);
    
    // Create labels
    auto label1 = create_text(-200, -50, "Physics Ball", WHITE);
    auto label2 = create_text(0, -50, "Animated Ball", WHITE);
    auto label3 = create_text(200, -50, "Interactive Ball", WHITE);
    
    // ============================================================================
    // SET UP ANIMATIONS
    // ============================================================================
    
    // Ball 1: Physics simulation
    apply_gravity(ball1);
    set_bounce(ball1, true);
    
    // Ball 2: Simple animation
    animate(ball2, move_to(0, 150), Time::seconds(2.0f));
    
    // Ball 3: Interactive (will be controlled by mouse)
    set_color(ball3, Color(1.0f, 0.5f, 0.0f)); // Orange
    
    // ============================================================================
    // ADD MINIMAL CONTROLS (Manim-like approach)
    // ============================================================================
    
    // Minimal controls for essential functions only
    // Most animation control is programmatic, not interactive
    
    // Space to pause/resume (essential for presentation)
    on_key_press(GLFW_KEY_SPACE, []() {
        if (is_playing()) {
            pause_animation();
            std::cout << "Animation paused (programmatic control)" << std::endl;
        } else {
            resume_animation();
            std::cout << "Animation resumed (programmatic control)" << std::endl;
        }
    });
    
    // R to reset (essential for demonstrations)
    on_key_press(GLFW_KEY_R, []() {
        reset_animation();
        std::cout << "Animation reset (programmatic control)" << std::endl;
    });
    
    // Minimal mouse interaction (Manim-like approach)
    // Most animation control is programmatic, not interactive
    on_mouse_click([](float x, float y) {
        auto ball3 = findObjectByName("ball3");
        if (ball3) {
            // Programmatic response to mouse click
            // In a real Manim-like scenario, this would trigger predefined animations
            animate(ball3, move_to(x, y), Time::seconds(1.0f));
            std::cout << "Programmatic animation triggered at (" << x << ", " << y << ")" << std::endl;
        }
    });
    
    // ============================================================================
    // DISPLAY CONTROLS
    // ============================================================================
    
    std::cout << "\n=== Minimal Controls (Manim-like) ===" << std::endl;
    std::cout << "SPACE - Pause/Resume animation (essential)" << std::endl;
    std::cout << "R - Reset animation (essential)" << std::endl;
    std::cout << "Mouse Click - Trigger programmatic animation" << std::endl;
    std::cout << "ESC - Exit" << std::endl;
    std::cout << "\nNote: Most animation control is programmatic, not interactive!" << std::endl;
    
    // ============================================================================
    // RUN THE ANIMATION
    // ============================================================================
    
    std::cout << "\nStarting professional animation demo..." << std::endl;
    std::cout << "Kalem Engine is now running!" << std::endl;
    
    try {
        run_animation();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    // ============================================================================
    // CLEANUP
    // ============================================================================
    
    shutdownEngine();
    std::cout << "Kalem Engine shutdown complete." << std::endl;
    
    return 0;
}

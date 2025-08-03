#include "api/EasyAPI.h"
#include <iostream>

/**
 * @brief Physics Demo - Bouncing Balls
 * 
 * This example demonstrates the physics capabilities of Kalem:
 * - Multiple bouncing balls with different properties
 * - Gravity simulation
 * - Collision detection
 * - Realistic physics behavior
 */
int main() {
    std::cout << "=== Kalem Physics Demo ===" << std::endl;
    std::cout << "Creating bouncing balls with physics..." << std::endl;
    
    // ============================================================================
    // CREATE PHYSICS OBJECTS
    // ============================================================================
    
    // Create multiple balls with different properties
    auto ball1 = create_circle(-200, 300, 25, RED);
    auto ball2 = create_circle(0, 250, 20, BLUE);
    auto ball3 = create_circle(200, 200, 30, GREEN);
    auto ball4 = create_circle(-100, 150, 15, YELLOW);
    
    // Create ground
    auto ground = create_line(-500, -300, 500, -300, GRAY);
    
    // Create walls
    auto leftWall = create_line(-500, -300, -500, 400, GRAY);
    auto rightWall = create_line(500, -300, 500, 400, GRAY);
    
    // Create title
    auto title = create_text(0, 350, "Physics Simulation - Bouncing Balls", WHITE);
    
    // ============================================================================
    // SET UP PHYSICS PROPERTIES
    // ============================================================================
    
    // Apply physics to all balls
    apply_gravity(ball1);
    apply_gravity(ball2);
    apply_gravity(ball3);
    apply_gravity(ball4);
    
    // Set different bounce properties
    set_bounce(ball1, true);
    set_bounce(ball2, true);
    set_bounce(ball3, true);
    set_bounce(ball4, true);
    
    // Set different masses
    ball1->setMass(1.0f);
    ball2->setMass(2.0f);
    ball3->setMass(0.5f);
    ball4->setMass(1.5f);
    
    // Add some initial velocity
    ball1->setVelocity(50, 0, 0);
    ball2->setVelocity(-30, 0, 0);
    ball3->setVelocity(0, -20, 0);
    ball4->setVelocity(40, 10, 0);
    
    // ============================================================================
    // ADD INTERACTIVE CONTROLS
    // ============================================================================
    
    // Space to pause/resume
    on_key_press(GLFW_KEY_SPACE, []() {
        if (is_playing()) {
            pause_animation();
            std::cout << "Animation paused" << std::endl;
        } else {
            resume_animation();
            std::cout << "Animation resumed" << std::endl;
        }
    });
    
    // R to reset
    on_key_press(GLFW_KEY_R, []() {
        reset_animation();
        std::cout << "Animation reset" << std::endl;
    });
    
    // Mouse click to add new ball
    on_mouse_click([](float x, float y) {
        auto newBall = create_circle(x, y, 15, CYAN);
        apply_gravity(newBall);
        set_bounce(newBall, true);
        newBall->setMass(1.0f);
        newBall->setVelocity(0, -50, 0);
        std::cout << "Added new ball at (" << x << ", " << y << ")" << std::endl;
    });
    
    // ============================================================================
    // RUN THE SIMULATION
    // ============================================================================
    
    std::cout << "Starting physics simulation..." << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  SPACE - Pause/Resume" << std::endl;
    std::cout << "  R - Reset" << std::endl;
    std::cout << "  Mouse Click - Add new ball" << std::endl;
    
    // Run the animation
    run_animation();
    
    return 0;
}

/**
 * @brief Wave Animation Demo
 * 
 * This example shows wave-like animations using mathematical functions.
 */
void wave_demo() {
    std::cout << "=== Wave Animation Demo ===" << std::endl;
    
    // Create wave particles
    std::vector<std::shared_ptr<AnimationObject>> particles;
    
    for (int i = 0; i < 50; ++i) {
        float x = (i - 25) * 10.0f;
        auto particle = create_circle(x, 0, 5, BLUE);
        particles.push_back(particle);
    }
    
    // Create wave animation
    auto wave_animation = [](AnimationObject* obj, float time) {
        if (obj) {
            glm::vec3 pos = obj->getPosition();
            float wave = sin(time * 2.0f + pos.x * 0.1f) * 50.0f;
            obj->setPosition(pos.x, wave, pos.z);
        }
    };
    
    // Animate all particles
    for (auto& particle : particles) {
        animate(particle, wave_animation, 10_seconds);
    }
    
    run_animation();
}

/**
 * @brief Complex Animation Demo
 * 
 * This example demonstrates complex animation sequences and parallel animations.
 */
void complex_animation_demo() {
    std::cout << "=== Complex Animation Demo ===" << std::endl;
    
    // Create objects
    auto circle = create_circle(-300, 0, 30, RED);
    auto square = create_rectangle(-100, 0, 60, 60, BLUE);
    auto triangle = create_circle(100, 0, 25, GREEN);
    auto star = create_circle(300, 0, 20, YELLOW);
    
    // Create complex animation sequence
    auto complex_sequence = sequence({
        move_to(0, 100, 2_seconds),
        rotate_to(360, 1_second),
        scale_to(2.0, 1_second),
        move_to(0, -100, 2_seconds),
        scale_to(1.0, 1_second)
    });
    
    // Apply to all objects with different timing
    animate(circle, complex_sequence, 7_seconds);
    animate(square, complex_sequence, 7_seconds);
    animate(triangle, complex_sequence, 7_seconds);
    animate(star, complex_sequence, 7_seconds);
    
    run_animation();
} 
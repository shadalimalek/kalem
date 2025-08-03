#include "kalem/api/EasyAPI.h"

/**
 * @brief Basic Motion Example
 * 
 * This example shows how to create a simple animation with a moving ball.
 * It demonstrates the basic workflow: create objects, animate them, run the animation.
 */
int main() {
    // ============================================================================
    // CREATE OBJECTS
    // ============================================================================
    
    // Create a red ball
    auto ball = create_circle(-300, 0, 20, RED);
    
    // Create a label
    auto label = create_text(0, 100, "Moving Ball Animation", WHITE);
    
    // Create a coordinate system
    auto xAxis = create_line(-500, 0, 500, 0, GRAY);
    auto yAxis = create_line(0, -300, 0, 300, GRAY);
    
    // ============================================================================
    // CREATE ANIMATIONS
    // ============================================================================
    
    // Animate the ball moving from left to right
    animate(ball, move_to(300, 0), 5_seconds);
    
    // ============================================================================
    // RUN THE ANIMATION
    // ============================================================================
    
    // Start the animation
    run_animation();
    
    return 0;
}

/**
 * @brief Physics Example
 * 
 * This example shows how to create a physics simulation with gravity and bouncing.
 */
void physics_example() {
    // Create a bouncing ball
    auto ball = create_circle(0, 200, 15, BLUE);
    
    // Apply gravity
    apply_gravity(ball);
    
    // Enable bouncing
    set_bounce(ball, true);
    
    // Run physics simulation for 10 seconds
    run_simulation(10_seconds);
}

/**
 * @brief Complex Animation Example
 * 
 * This example shows how to create complex animations with multiple objects
 * and sequences of animations.
 */
void complex_animation_example() {
    // Create multiple objects
    auto car = create_rectangle(-400, 0, 60, 30, BLUE);
    auto road = create_line(-500, -50, 500, -50, GRAY);
    auto title = create_text(0, 150, "Car Animation", WHITE);
    
    // Create a complex animation sequence
    sequence({
        animate(car, move_to(400, 0), 8_seconds),
        animate(car, rotate_to(180), 1_second),
        animate(car, move_to(-400, 0), 8_seconds)
    });
    
    // Run the animation
    run_animation();
}

/**
 * @brief Interactive Example
 * 
 * This example shows how to add interactive controls to animations.
 */
void interactive_example() {
    // Create a ball
    auto ball = create_circle(0, 0, 25, GREEN);
    
    // Add keyboard controls
    on_key_press(GLFW_KEY_SPACE, []() {
        pause_animation();
    });
    
    on_key_press(GLFW_KEY_R, []() {
        reset_animation();
    });
    
    // Add mouse click to move ball
    on_mouse_click([](float x, float y) {
        // Move ball to clicked position
        auto ball = get_object("ball");
        if (ball) {
            animate(ball, move_to(x, y), 1_second);
        }
    });
    
    // Animate ball in a circle
    auto circular_motion = [](AnimationObject* obj, float time) {
        float radius = 100;
        float x = cos(time) * radius;
        float y = sin(time) * radius;
        obj->set_position(x, y);
    };
    
    animate(ball, circular_motion, 10_seconds);
    
    run_animation();
} 
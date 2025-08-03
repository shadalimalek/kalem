#pragma once

#include <memory>
#include <string>
#include <functional>
#include <vector>

// Forward declarations
class AnimationObject;
class Color;
class Time;

// Color definitions
struct Color {
    float r, g, b;
    Color(float r, float g, float b) : r(r), g(g), b(b) {}
};

// Predefined colors
extern const Color RED;
extern const Color GREEN;
extern const Color BLUE;
extern const Color YELLOW;
extern const Color CYAN;
extern const Color MAGENTA;
extern const Color WHITE;
extern const Color BLACK;
extern const Color GRAY;

// Time duration literals
struct Time {
    float value;
    Time(float s) : value(s) {}
    
    static Time seconds(float s) { return Time(s); }
    static Time minutes(float m) { return Time(m * 60); }
    static Time milliseconds(float ms) { return Time(ms / 1000.0f); }
    
    operator float() const { return value; }
};

// Duration literals
inline Time operator""_seconds(long double s) { return Time(static_cast<float>(s)); }
inline Time operator""_minutes(long double m) { return Time(static_cast<float>(m) * 60); }

// ============================================================================
// OBJECT CREATION FUNCTIONS
// ============================================================================

/**
 * @brief Create a circle
 * @param x X position
 * @param y Y position
 * @param radius Circle radius
 * @param color Circle color
 * @return Pointer to the created circle object
 */
std::shared_ptr<AnimationObject> create_circle(float x, float y, float radius, const Color& color);

/**
 * @brief Create a rectangle
 * @param x X position
 * @param y Y position
 * @param width Rectangle width
 * @param height Rectangle height
 * @param color Rectangle color
 * @return Pointer to the created rectangle object
 */
std::shared_ptr<AnimationObject> create_rectangle(float x, float y, float width, float height, const Color& color);

/**
 * @brief Create a line
 * @param x1 Start X position
 * @param y1 Start Y position
 * @param x2 End X position
 * @param y2 End Y position
 * @param color Line color
 * @return Pointer to the created line object
 */
std::shared_ptr<AnimationObject> create_line(float x1, float y1, float x2, float y2, const Color& color);

/**
 * @brief Create text
 * @param x X position
 * @param y Y position
 * @param text Text content
 * @param color Text color
 * @return Pointer to the created text object
 */
std::shared_ptr<AnimationObject> create_text(float x, float y, const std::string& text, const Color& color);

/**
 * @brief Create a particle with physics
 * @param x X position
 * @param y Y position
 * @param mass Particle mass
 * @return Pointer to the created particle object
 */
std::shared_ptr<AnimationObject> create_particle(float x, float y, float mass = 1.0f);

// ============================================================================
// ANIMATION FUNCTIONS
// ============================================================================

/**
 * @brief Move object to position
 * @param x Target X position
 * @param y Target Y position
 * @return Animation function
 */
std::function<void(AnimationObject*, float)> move_to(float x, float y);

/**
 * @brief Move object by offset
 * @param dx X offset
 * @param dy Y offset
 * @return Animation function
 */
std::function<void(AnimationObject*, float)> move_by(float dx, float dy);

/**
 * @brief Rotate object to angle
 * @param angle Target angle in degrees
 * @return Animation function
 */
std::function<void(AnimationObject*, float)> rotate_to(float angle);

/**
 * @brief Scale object to factor
 * @param factor Target scale factor
 * @return Animation function
 */
std::function<void(AnimationObject*, float)> scale_to(float factor);

/**
 * @brief Animate an object
 * @param obj Object to animate
 * @param animation Animation function
 * @param duration Animation duration
 */
void animate(std::shared_ptr<AnimationObject> obj, 
             std::function<void(AnimationObject*, float)> animation, 
             const Time& duration);

// ============================================================================
// PHYSICS FUNCTIONS
// ============================================================================

/**
 * @brief Apply force to object
 * @param obj Target object
 * @param fx X component of force
 * @param fy Y component of force
 */
void apply_force(std::shared_ptr<AnimationObject> obj, float fx, float fy);

/**
 * @brief Apply gravity to object
 * @param obj Target object
 */
void apply_gravity(std::shared_ptr<AnimationObject> obj);

/**
 * @brief Set object to bounce off walls
 * @param obj Target object
 * @param bounce Whether to bounce
 */
void set_bounce(std::shared_ptr<AnimationObject> obj, bool bounce);

/**
 * @brief Run physics simulation
 * @param duration Simulation duration
 */
void run_simulation(const Time& duration);

// ============================================================================
// COMPLEX ANIMATIONS
// ============================================================================

/**
 * @brief Create sequence of animations
 * @param animations List of animation functions
 * @return Combined animation function
 */
std::function<void(AnimationObject*, float)> sequence(
    std::vector<std::function<void(AnimationObject*, float)>> animations);

/**
 * @brief Run animations in parallel
 * @param objects List of objects
 * @param animations List of animations
 * @param duration Animation duration
 */
void parallel(std::vector<std::shared_ptr<AnimationObject>> objects,
             std::vector<std::function<void(AnimationObject*, float)>> animations,
             const Time& duration);

// ============================================================================
// CONTROL FUNCTIONS
// ============================================================================

/**
 * @brief Run the animation
 */
void run_animation();

/**
 * @brief Pause animation
 */
void pause_animation();

/**
 * @brief Resume animation
 */
void resume_animation();

/**
 * @brief Reset animation to beginning
 */
void reset_animation();

/**
 * @brief Set animation speed
 * @param scale Time scale (1.0 = normal, 2.0 = double speed, 0.5 = half speed)
 */
void set_speed(float scale);

// ============================================================================
// STYLING FUNCTIONS
// ============================================================================

/**
 * @brief Set object color
 * @param obj Target object
 * @param color New color
 */
void set_color(std::shared_ptr<AnimationObject> obj, const Color& color);

/**
 * @brief Set object opacity
 * @param obj Target object
 * @param opacity Opacity (0.0 = transparent, 1.0 = opaque)
 */
void set_opacity(std::shared_ptr<AnimationObject> obj, float opacity);

/**
 * @brief Set object visibility
 * @param obj Target object
 * @param visible Whether object is visible
 */
void set_visible(std::shared_ptr<AnimationObject> obj, bool visible);

// ============================================================================
// EXPORT FUNCTIONS
// ============================================================================

/**
 * @brief Export animation to video
 * @param filename Output filename
 * @param fps Frames per second
 */
void export_video(const std::string& filename, int fps = 30);

/**
 * @brief Export animation to GIF
 * @param filename Output filename
 * @param fps Frames per second
 */
void export_gif(const std::string& filename, int fps = 15);

/**
 * @brief Export animation code
 * @param filename Output filename
 */
void export_code(const std::string& filename);

// ============================================================================
// INTERACTIVE FUNCTIONS
// ============================================================================

/**
 * @brief Add keyboard callback
 * @param key Key code
 * @param callback Function to call when key is pressed
 */
void on_key_press(int key, std::function<void()> callback);

/**
 * @brief Add mouse click callback
 * @param callback Function to call when mouse is clicked
 */
void on_mouse_click(std::function<void(float, float)> callback);

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

/**
 * @brief Get current animation time
 * @return Current time in seconds
 */
float get_current_time();

/**
 * @brief Check if animation is playing
 * @return True if animation is playing
 */
bool is_playing();

/**
 * @brief Find object by name
 * @param name Object name
 * @return Pointer to object or nullptr if not found
 */
std::shared_ptr<AnimationObject> findObjectByName(const std::string& name);

/**
 * @brief Wait for specified time
 * @param duration Time to wait
 */
void wait(const Time& duration); 

// Engine initialization and shutdown
void initEngine();
void shutdownEngine(); 
# Kalem - Educational Animation Engine

**Kalem** is a powerful, easy-to-use animation engine designed for creating educational content. Think of it as a **supercharged Manim** - simple enough for beginners, powerful enough for professionals.

## 🎯 What is Kalem?

Kalem is an animation engine that lets you create **professional educational videos** with just a few lines of code. Whether you're teaching physics, math, chemistry, or biology, Kalem makes it incredibly easy to create stunning visualizations.

### ✨ Key Features:
- **🚀 Simple API** - Create animations with just 3 lines of code
- **🎬 Professional Quality** - Export to video, GIF, or code
- **⚡ Real-time Physics** - Gravity, bouncing, collisions, forces
- **🎨 Beautiful Graphics** - Modern OpenGL rendering
- **📱 Interactive** - Mouse and keyboard controls
- **📚 Educational Focus** - Perfect for teaching and learning

## 🚀 Quick Start

### Step 1: Installation

#### Prerequisites:
- **Windows**: MinGW-w64 or Visual Studio
- **Linux**: GCC 7+ or Clang
- **macOS**: Xcode Command Line Tools
- **CMake**: Version 3.16 or higher
- **OpenGL**: Version 3.3 or higher

#### Installation Commands:
```bash
# 1. Clone the repository
git clone https://github.com/yourusername/kalem.git
cd kalem

# 2. Build the project
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build

# 3. Run the demo
./build/bin/Kalem.exe
```

### Step 2: Your First Animation

Create a file called `my_first_animation.cpp`:

```cpp
#include "kalem/api/EasyAPI.h"

int main() {
    // Create a red ball
    auto ball = create_circle(-300, 0, 20, RED);
    
    // Make it move to the right
    animate(ball, move_to(300, 0), 5_seconds);
    
    // Run the animation
    run_animation();
    
    return 0;
}
```

### Step 3: Build and Run
```bash
# Compile your animation
g++ my_first_animation.cpp -o my_animation -lkalem

# Run it
./my_animation
```

**That's it!** You've created your first animation! 🎉

## 📚 Complete Tutorial

### Chapter 1: Basic Objects

#### Creating Shapes

**Circles:**
```cpp
// Create a circle at position (100, 200) with radius 25, colored red
auto circle = create_circle(100, 200, 25, RED);

// Create a blue circle
auto blueCircle = create_circle(0, 0, 15, BLUE);
```

**Rectangles:**
```cpp
// Create a rectangle: x=50, y=100, width=80, height=60, color=green
auto rectangle = create_rectangle(50, 100, 80, 60, GREEN);
```

**Lines:**
```cpp
// Create a line from (0,0) to (200,100), colored white
auto line = create_line(0, 0, 200, 100, WHITE);
```

**Text:**
```cpp
// Create text at position (0, 300), saying "Hello World", colored white
auto text = create_text(0, 300, "Hello World", WHITE);
```

#### Available Colors:
```cpp
RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA, WHITE, BLACK, GRAY

// Or create custom colors:
Color myColor(1.0, 0.5, 0.0);  // Orange
Color purple(0.5, 0.0, 1.0);   // Purple
```

### Chapter 2: Basic Animations

#### Moving Objects

**Move to a specific position:**
```cpp
auto ball = create_circle(0, 0, 20, RED);

// Move ball to position (300, 200) over 3 seconds
animate(ball, move_to(300, 200), 3_seconds);
```

**Move by a certain amount:**
```cpp
// Move ball 100 pixels to the right and 50 pixels up over 2 seconds
animate(ball, move_by(100, 50), 2_seconds);
```

#### Rotating Objects
```cpp
// Rotate object 360 degrees (full circle) over 2 seconds
animate(ball, rotate_to(360), 2_seconds);

// Rotate 90 degrees
animate(ball, rotate_to(90), 1_second);
```

#### Scaling Objects
```cpp
// Make object twice as big over 1 second
animate(ball, scale_to(2.0), 1_second);

// Make object half size
animate(ball, scale_to(0.5), 1_second);
```

### Chapter 3: Physics Simulations

#### Gravity and Bouncing

**Simple bouncing ball:**
```cpp
// Create a ball
auto ball = create_circle(0, 200, 20, BLUE);

// Apply gravity (makes it fall down)
apply_gravity(ball);

// Enable bouncing (makes it bounce off the ground)
set_bounce(ball, true);

// Run the simulation for 10 seconds
run_simulation(10_seconds);
```

**Multiple balls with different properties:**
```cpp
// Create multiple balls
auto ball1 = create_circle(-200, 300, 25, RED);
auto ball2 = create_circle(0, 250, 20, BLUE);
auto ball3 = create_circle(200, 200, 30, GREEN);

// Apply physics to all balls
apply_gravity(ball1);
apply_gravity(ball2);
apply_gravity(ball3);

// Set different bounce properties
set_bounce(ball1, true);
set_bounce(ball2, true);
set_bounce(ball3, true);

// Set different masses (affects how they fall)
ball1->setMass(1.0f);   // Normal mass
ball2->setMass(2.0f);   // Heavy ball (falls faster)
ball3->setMass(0.5f);   // Light ball (falls slower)

// Add initial velocity
ball1->setVelocity(50, 0, 0);   // Moving right
ball2->setVelocity(-30, 0, 0);  // Moving left
ball3->setVelocity(0, -20, 0);  // Moving down

run_simulation(10_seconds);
```

#### Forces and Physics

**Apply forces:**
```cpp
auto ball = create_circle(0, 0, 15, RED);

// Apply a force pushing the ball up and right
apply_force(ball, 10.0f, 20.0f);

// Apply gravity
apply_gravity(ball);

run_simulation(5_seconds);
```

### Chapter 4: Complex Animations

#### Animation Sequences

**Do multiple animations in order:**
```cpp
auto ball = create_circle(0, 0, 20, RED);

// Create a sequence: move up, rotate, scale, move down
auto complex_animation = sequence({
    move_to(0, 100, 2_seconds),    // Move up
    rotate_to(360, 1_second),      // Rotate 360 degrees
    scale_to(2.0, 0.5_seconds),    // Get bigger
    move_to(0, 0, 2_seconds),      // Move back down
    scale_to(1.0, 0.5_seconds)     // Return to normal size
});

// Run the entire sequence
animate(ball, complex_animation, 6_seconds);
```

#### Parallel Animations

**Animate multiple objects at the same time:**
```cpp
// Create multiple objects
auto ball1 = create_circle(-200, 0, 20, RED);
auto ball2 = create_circle(0, 0, 20, BLUE);
auto ball3 = create_circle(200, 0, 20, GREEN);

// Create different animations for each
auto move_right = move_to(200, 0, 3_seconds);
auto move_left = move_to(-200, 0, 3_seconds);
auto move_up = move_to(0, 100, 3_seconds);

// Run all animations at the same time
parallel({ball1, ball2, ball3}, {move_right, move_left, move_up}, 3_seconds);
```

### Chapter 5: Interactive Controls

#### Keyboard Controls

**Add keyboard shortcuts:**
```cpp
// Space bar to pause/resume
on_key_press(GLFW_KEY_SPACE, []() {
    if (is_playing()) {
        pause_animation();
        std::cout << "Animation paused" << std::endl;
    } else {
        resume_animation();
        std::cout << "Animation resumed" << std::endl;
    }
});

// R key to reset
on_key_press(GLFW_KEY_R, []() {
    reset_animation();
    std::cout << "Animation reset" << std::endl;
});

// Number keys to change speed
on_key_press(GLFW_KEY_1, []() { set_speed(0.5); });  // Half speed
on_key_press(GLFW_KEY_2, []() { set_speed(1.0); });  // Normal speed
on_key_press(GLFW_KEY_3, []() { set_speed(2.0); });  // Double speed
```

#### Mouse Controls

**Click to create objects:**
```cpp
// Create a ball wherever you click
on_mouse_click([](float x, float y) {
    auto newBall = create_circle(x, y, 15, CYAN);
    apply_gravity(newBall);
    set_bounce(newBall, true);
    std::cout << "Created ball at (" << x << ", " << y << ")" << std::endl;
});
```

**Click to move objects:**
```cpp
auto ball = create_circle(0, 0, 20, RED);

// Move ball to where you click
on_mouse_click([](float x, float y) {
    animate(ball, move_to(x, y), 1_second);
});
```

### Chapter 6: Custom Animations

#### Mathematical Animations

**Sine wave animation:**
```cpp
auto ball = create_circle(0, 0, 15, BLUE);

// Create a sine wave motion
auto sine_animation = [](AnimationObject* obj, float time) {
    if (obj) {
        float x = time * 100;  // Move right over time
        float y = sin(time * 2.0f) * 50;  // Sine wave up and down
        obj->setPosition(x, y, 0);
    }
};

animate(ball, sine_animation, 10_seconds);
```

**Circular motion:**
```cpp
auto ball = create_circle(0, 0, 15, GREEN);

// Create circular motion
auto circle_animation = [](AnimationObject* obj, float time) {
    if (obj) {
        float radius = 100;
        float x = cos(time) * radius;
        float y = sin(time) * radius;
        obj->setPosition(x, y, 0);
    }
};

animate(ball, circle_animation, 10_seconds);
```

#### Physics-based Animations

**Spring animation:**
```cpp
auto ball = create_circle(0, 0, 15, RED);

// Create spring-like motion
auto spring_animation = [](AnimationObject* obj, float time) {
    if (obj) {
        float amplitude = 100;
        float frequency = 3.0f;
        float damping = exp(-time * 0.5f);  // Gradually slow down
        float y = sin(time * frequency) * amplitude * damping;
        obj->setPosition(0, y, 0);
    }
};

animate(ball, spring_animation, 10_seconds);
```

## 🎬 Complete Examples

### Example 1: Physics Lesson - Projectile Motion

```cpp
#include "kalem/api/EasyAPI.h"

int main() {
    std::cout << "=== Projectile Motion Demo ===" << std::endl;
    
    // Create the projectile
    auto projectile = create_circle(0, 0, 10, RED);
    
    // Create ground
    auto ground = create_line(-500, -200, 500, -200, GRAY);
    
    // Create title
    auto title = create_text(0, 250, "Projectile Motion", WHITE);
    
    // Set up physics
    apply_gravity(projectile);
    set_bounce(projectile, true);
    
    // Initial velocity (angle of 45 degrees)
    float angle = 45.0f * 3.14159f / 180.0f;  // Convert to radians
    float speed = 100.0f;
    float vx = speed * cos(angle);
    float vy = speed * sin(angle);
    
    projectile->setVelocity(vx, vy, 0);
    
    // Add controls
    on_key_press(GLFW_KEY_SPACE, []() {
        if (is_playing()) pause_animation();
        else resume_animation();
    });
    
    on_key_press(GLFW_KEY_R, []() {
        reset_animation();
    });
    
    std::cout << "Controls: SPACE=pause, R=reset" << std::endl;
    
    run_animation();
    return 0;
}
```

### Example 2: Math Lesson - Function Graphing

```cpp
#include "kalem/api/EasyAPI.h"
#include <cmath>

int main() {
    std::cout << "=== Function Graphing Demo ===" << std::endl;
    
    // Create coordinate system
    auto xAxis = create_line(-400, 0, 400, 0, GRAY);
    auto yAxis = create_line(0, -300, 0, 300, GRAY);
    
    // Create title
    auto title = create_text(0, 250, "f(x) = sin(x)", WHITE);
    
    // Create points for the function
    std::vector<std::shared_ptr<AnimationObject>> points;
    
    for (int i = -20; i <= 20; ++i) {
        float x = i * 20.0f;  // Scale x
        float y = sin(i * 0.5f) * 100.0f;  // Calculate y = sin(x)
        
        auto point = create_circle(x, y, 3, BLUE);
        points.push_back(point);
    }
    
    // Animate the points appearing one by one
    for (size_t i = 0; i < points.size(); ++i) {
        auto point = points[i];
        point->setScale(0, 0, 1);  // Start invisible
        
        // Animate to full size
        animate(point, scale_to(1.0), 0.1_seconds);
        
        // Delay each point
        wait(0.1_seconds);
    }
    
    run_animation();
    return 0;
}
```

### Example 3: Chemistry Lesson - Molecular Motion

```cpp
#include "kalem/api/EasyAPI.h"

int main() {
    std::cout << "=== Molecular Motion Demo ===" << std::endl;
    
    // Create molecules (particles)
    std::vector<std::shared_ptr<AnimationObject>> molecules;
    
    for (int i = 0; i < 20; ++i) {
        float x = (rand() % 800) - 400;  // Random position
        float y = (rand() % 600) - 300;
        
        auto molecule = create_circle(x, y, 8, CYAN);
        molecules.push_back(molecule);
        
        // Apply random velocity
        float vx = (rand() % 100) - 50;
        float vy = (rand() % 100) - 50;
        molecule->setVelocity(vx, vy, 0);
        
        // Apply physics
        apply_gravity(molecule);
        set_bounce(molecule, true);
    }
    
    // Create container walls
    auto leftWall = create_line(-400, -300, -400, 300, GRAY);
    auto rightWall = create_line(400, -300, 400, 300, GRAY);
    auto topWall = create_line(-400, 300, 400, 300, GRAY);
    auto bottomWall = create_line(-400, -300, 400, -300, GRAY);
    
    auto title = create_text(0, 350, "Molecular Motion Simulation", WHITE);
    
    // Add temperature control
    on_key_press(GLFW_KEY_UP, []() {
        set_speed(2.0);  // Increase temperature (speed)
        std::cout << "Temperature increased" << std::endl;
    });
    
    on_key_press(GLFW_KEY_DOWN, []() {
        set_speed(0.5);  // Decrease temperature (speed)
        std::cout << "Temperature decreased" << std::endl;
    });
    
    std::cout << "Controls: UP/DOWN arrows to change temperature" << std::endl;
    
    run_simulation(30_seconds);
    return 0;
}
```

## 🎨 Advanced Features

### Exporting Animations

**Export to video:**
```cpp
// Export animation as MP4 video
export_video("my_animation.mp4", 30);  // 30 FPS
```

**Export to GIF:**
```cpp
// Export animation as GIF
export_gif("my_animation.gif", 15);  // 15 FPS
```

**Export code:**
```cpp
// Export the animation as C++ code
export_code("my_animation.cpp");
```

### Styling Objects

**Change colors:**
```cpp
auto ball = create_circle(0, 0, 20, RED);

// Change color during animation
set_color(ball, BLUE);
set_color(ball, Color(1.0, 0.5, 0.0));  // Orange
```

**Change opacity:**
```cpp
// Make object semi-transparent
set_opacity(ball, 0.5);

// Make object invisible
set_opacity(ball, 0.0);
```

**Show/hide objects:**
```cpp
// Hide object
set_visible(ball, false);

// Show object
set_visible(ball, true);
```

### Time Control

**Duration literals:**
```cpp
1_second      // 1 second
2_seconds     // 2 seconds
0.5_seconds   // Half a second
1_minute      // 1 minute
30_minutes    // 30 minutes
```

**Time units:**
```cpp
Time::seconds(5)        // 5 seconds
Time::minutes(2)        // 2 minutes
Time::milliseconds(500) // 500 milliseconds
```

## 🔧 Troubleshooting

### Common Issues

**"Cannot find kalem/api/EasyAPI.h"**
- Make sure you've built the project first
- Check that the include path is correct
- Ensure you're linking against the Kalem library

**"Animation doesn't show"**
- Make sure you called `run_animation()` at the end
- Check that objects are within the visible area (-500 to 500)
- Verify that objects have colors set

**"Physics doesn't work"**
- Make sure you called `apply_gravity()` on objects
- Check that you're using `run_simulation()` instead of `run_animation()`
- Verify that objects have mass set

**"Build errors"**
- Ensure you have the correct compiler (MinGW-w64 for Windows)
- Check that OpenGL is properly installed
- Verify CMake version is 3.16 or higher

### Performance Tips

1. **Limit object count** - Too many objects can slow down rendering
2. **Use efficient animations** - Complex mathematical functions can be expensive
3. **Optimize physics** - Reduce physics update frequency for better performance
4. **Batch operations** - Create objects in loops rather than individually

## 📖 API Reference

### Object Creation Functions

| Function | Description | Example |
|----------|-------------|---------|
| `create_circle(x, y, radius, color)` | Create a circle | `create_circle(0, 0, 20, RED)` |
| `create_rectangle(x, y, width, height, color)` | Create a rectangle | `create_rectangle(0, 0, 50, 30, BLUE)` |
| `create_line(x1, y1, x2, y2, color)` | Create a line | `create_line(0, 0, 100, 100, WHITE)` |
| `create_text(x, y, text, color)` | Create text | `create_text(0, 0, "Hello", WHITE)` |
| `create_particle(x, y, mass)` | Create physics particle | `create_particle(0, 0, 1.0)` |

### Animation Functions

| Function | Description | Example |
|----------|-------------|---------|
| `move_to(x, y)` | Move to position | `animate(obj, move_to(100, 200), 2_seconds)` |
| `move_by(dx, dy)` | Move by offset | `animate(obj, move_by(50, -30), 1_second)` |
| `rotate_to(angle)` | Rotate to angle | `animate(obj, rotate_to(90), 1_second)` |
| `scale_to(factor)` | Scale to factor | `animate(obj, scale_to(2.0), 1_second)` |

### Physics Functions

| Function | Description | Example |
|----------|-------------|---------|
| `apply_gravity(obj)` | Apply gravity to object | `apply_gravity(ball)` |
| `set_bounce(obj, true)` | Enable bouncing | `set_bounce(ball, true)` |
| `apply_force(obj, fx, fy)` | Apply force | `apply_force(ball, 10, 20)` |
| `run_simulation(duration)` | Run physics simulation | `run_simulation(10_seconds)` |

### Control Functions

| Function | Description | Example |
|----------|-------------|---------|
| `run_animation()` | Start animation loop | `run_animation()` |
| `pause_animation()` | Pause animation | `pause_animation()` |
| `resume_animation()` | Resume animation | `resume_animation()` |
| `reset_animation()` | Reset to beginning | `reset_animation()` |
| `set_speed(scale)` | Change animation speed | `set_speed(2.0)` |

## 🏗️ Architecture

### Core Components

- **AnimationEngine**: Main animation system and coordination
- **Scene**: Container for objects and animations
- **Timeline**: Animation timing and playback control
- **PhysicsEngine**: Physics simulation and collision detection
- **Renderer**: Graphics rendering with OpenGL
- **EasyAPI**: Simple interface for users

### Object Types

- **Particle**: Physics-based objects with mass, velocity, acceleration
- **Shape**: Geometric shapes (circle, rectangle, line)
- **Text**: Text labels and equations
- **Vector**: Arrows and force vectors
- **Group**: Collections of objects

### File Structure

```
Kalem/
├── src/
│   ├── engine/          # Core engine classes
│   ├── objects/         # Animation objects
│   ├── rendering/       # Graphics and rendering
│   ├── api/            # Public API
│   └── utils/          # Utility functions
├── examples/           # Example programs
├── docs/              # Documentation
└── tests/             # Unit tests
```

## 🤝 Contributing

We welcome contributions! Please see our [Contributing Guide](CONTRIBUTING.md) for details.

### Development Setup
```bash
# Clone with submodules
git clone --recursive https://github.com/yourusername/kalem.git

# Build in debug mode
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- Inspired by Manim and other educational animation tools
- Built with OpenGL and GLFW
- Thanks to all contributors and users

## 🚨 Troubleshooting Guide

### Common Issues and Solutions

#### Build Problems

**"Cannot find kalem/api/EasyAPI.h"**
- **Solution**: Make sure you've built the project first with `cmake --build build`
- **Solution**: Check that your include path includes the `src` directory
- **Solution**: Ensure you're linking against the Kalem library

**"GLFW not found"**
- **Solution**: Make sure GLFW submodule is cloned: `git submodule update --init --recursive`
- **Solution**: Check that `libs/glfw` directory exists and contains source files

**"OpenGL functions not found"**
- **Solution**: Ensure OpenGL 3.3+ is installed on your system
- **Solution**: On Windows, install graphics drivers
- **Solution**: On Linux, install `mesa-utils` and `libgl1-mesa-dev`

#### Runtime Problems

**"Animation doesn't show anything"**
- **Solution**: Make sure you called `run_animation()` at the end of your program
- **Solution**: Check that objects are within the visible area (-500 to 500 pixels)
- **Solution**: Verify that objects have colors set (not transparent)
- **Solution**: Ensure objects have non-zero size

**"Physics doesn't work"**
- **Solution**: Make sure you called `apply_gravity()` on objects
- **Solution**: Check that you're using `run_simulation()` instead of `run_animation()`
- **Solution**: Verify that objects have mass set with `setMass()`
- **Solution**: Ensure objects are not static with `setStatic(false)`

**"Animation is too fast/slow"**
- **Solution**: Use `set_speed(0.5)` for slower, `set_speed(2.0)` for faster
- **Solution**: Adjust duration in your animations (e.g., `5_seconds` instead of `1_second`)
- **Solution**: Check your system's frame rate settings

#### Performance Issues

**"Animation is laggy"**
- **Solution**: Reduce the number of objects (aim for < 100 objects)
- **Solution**: Simplify complex mathematical animations
- **Solution**: Use `set_speed(0.5)` to reduce frame rate
- **Solution**: Close other applications to free up system resources

**"Memory usage is high"**
- **Solution**: Use `clearObjects()` to remove unused objects
- **Solution**: Avoid creating objects in loops without cleanup
- **Solution**: Use smart pointers (`std::shared_ptr`) for automatic cleanup

### Debug Tips

**Enable debug output:**
```cpp
// Add this at the start of your program
std::cout << "Debug: Creating objects..." << std::endl;
auto ball = create_circle(0, 0, 20, RED);
std::cout << "Debug: Object created at position " << ball->getPosition().x << ", " << ball->getPosition().y << std::endl;
```

**Check object properties:**
```cpp
// Verify object properties
std::cout << "Ball position: " << ball->getPosition().x << ", " << ball->getPosition().y << std::endl;
std::cout << "Ball color: " << ball->getColor().r << ", " << ball->getColor().g << ", " << ball->getColor().b << std::endl;
std::cout << "Ball visible: " << (ball->isVisible() ? "yes" : "no") << std::endl;
```

## 🎯 Best Practices

### Code Organization
1. **Start simple** - Begin with basic shapes and movements
2. **Test frequently** - Run your code often to catch issues early
3. **Use meaningful names** - Name your objects descriptively
4. **Comment your code** - Explain complex animations and physics

### Performance Tips
1. **Limit object count** - Too many objects can slow down rendering
2. **Use efficient animations** - Complex mathematical functions can be expensive
3. **Optimize physics** - Reduce physics update frequency for better performance
4. **Batch operations** - Create objects in loops rather than individually

### Educational Content Tips
1. **Start with the concept** - Plan your animation before coding
2. **Use clear labels** - Add text to explain what's happening
3. **Control the pace** - Use appropriate speeds for your audience
4. **Add interactivity** - Let users control the animation

## 📞 Support

- **Documentation**: This README and inline code comments
- **Examples**: Check the `examples/` folder for working code
- **Issues**: Report bugs on GitHub Issues
- **Discussions**: Ask questions on GitHub Discussions
- **Getting Help**: 
  1. Check the examples first
  2. Read the troubleshooting section
  3. Look at error messages carefully
  4. Try a simple example before building complex animations

---

**Kalem** - Making educational animations easy and powerful! 🎬✨

*Start creating amazing educational content today!*

**Remember**: The best way to learn is by doing! Start with the simple examples and gradually build up to more complex animations. Don't be afraid to experiment and have fun! 🚀 
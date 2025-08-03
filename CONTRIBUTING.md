# Contributing to Kalem

Thank you for your interest in contributing to Kalem! This document provides guidelines and information for contributors.

## 🚀 Quick Start

### Prerequisites
- CMake 3.16+
- MinGW-w64 (Windows) or GCC 7+ (Linux)
- OpenGL 3.3+
- Git

### Development Setup
```bash
# Clone the repository
git clone https://github.com/yourusername/kalem.git
cd kalem

# Clone submodules
git submodule update --init --recursive

# Build in debug mode
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build

# Run tests
./build/bin/tests
```

## 📋 Contribution Guidelines

### Code Style

#### C++ Style Guide
- **Indentation**: 4 spaces (no tabs)
- **Line Length**: Maximum 120 characters
- **Naming Conventions**:
  - Classes: `PascalCase` (e.g., `AnimationObject`)
  - Functions: `camelCase` (e.g., `createCircle`)
  - Variables: `camelCase` (e.g., `objectCount`)
  - Constants: `UPPER_SNAKE_CASE` (e.g., `MAX_OBJECTS`)
  - Private members: `m_camelCase` (e.g., `m_position`)

#### File Organization
```
src/
├── engine/          # Core engine classes
├── objects/         # Animation objects
├── rendering/       # Graphics and rendering
├── api/            # Public API
└── utils/          # Utility functions
```

#### Documentation
- All public APIs must be documented with Doxygen comments
- Include examples in documentation
- Update README.md for new features

### Commit Messages

Use conventional commit format:
```
type(scope): description

[optional body]

[optional footer]
```

Types:
- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation changes
- `style`: Code style changes
- `refactor`: Code refactoring
- `test`: Adding tests
- `chore`: Maintenance tasks

Examples:
```
feat(api): add create_circle function
fix(physics): resolve collision detection bug
docs(readme): update installation instructions
```

### Pull Request Process

1. **Fork the repository**
2. **Create a feature branch**:
   ```bash
   git checkout -b feature/your-feature-name
   ```
3. **Make your changes** following the code style guidelines
4. **Add tests** for new functionality
5. **Update documentation** if needed
6. **Commit your changes** with conventional commit messages
7. **Push to your fork**:
   ```bash
   git push origin feature/your-feature-name
   ```
8. **Create a Pull Request** with:
   - Clear description of changes
   - Link to related issues
   - Screenshots/videos for UI changes

### Review Process

- All PRs require at least one review
- Maintainers will review for:
  - Code quality and style
  - Performance implications
  - Security considerations
  - Documentation completeness
  - Test coverage

## 🧪 Testing

### Running Tests
```bash
# Build tests
cmake --build build --target tests

# Run all tests
./build/bin/tests

# Run specific test
./build/bin/tests --gtest_filter=AnimationObjectTest*
```

### Writing Tests
- Use Google Test framework
- Test both positive and negative cases
- Include performance tests for critical paths
- Mock external dependencies

Example test:
```cpp
TEST(AnimationObjectTest, SetPosition) {
    auto obj = std::make_shared<AnimationObject>("test");
    obj->setPosition(10.0f, 20.0f);
    
    auto pos = obj->getPosition();
    EXPECT_FLOAT_EQ(pos.x, 10.0f);
    EXPECT_FLOAT_EQ(pos.y, 20.0f);
}
```

## 🐛 Bug Reports

### Before Reporting
1. Check existing issues
2. Try the latest version
3. Reproduce on a clean build

### Bug Report Template
```markdown
**Description**
Brief description of the bug

**Steps to Reproduce**
1. Step 1
2. Step 2
3. Step 3

**Expected Behavior**
What should happen

**Actual Behavior**
What actually happens

**Environment**
- OS: [e.g., Windows 10]
- Compiler: [e.g., MinGW-w64 8.1.0]
- OpenGL Version: [e.g., 4.6]

**Additional Information**
Screenshots, logs, etc.
```

## 💡 Feature Requests

### Before Requesting
1. Check if the feature already exists
2. Consider if it fits the project's scope
3. Think about implementation complexity

### Feature Request Template
```markdown
**Feature Description**
Clear description of the feature

**Use Case**
Why this feature is needed

**Proposed Implementation**
How you think it should work

**Alternatives Considered**
Other approaches you've thought about

**Additional Context**
Any other relevant information
```

## 🏗️ Architecture Guidelines

### Adding New Object Types
1. Inherit from `AnimationObject`
2. Implement required virtual methods
3. Add to object factory
4. Update documentation
5. Add tests

### Adding New Animation Types
1. Create animation function
2. Add to EasyAPI
3. Update examples
4. Add tests

### Performance Considerations
- Use efficient data structures
- Minimize memory allocations
- Profile critical paths
- Consider GPU acceleration

## 📚 Documentation

### Code Documentation
- Use Doxygen comments for all public APIs
- Include parameter descriptions
- Provide usage examples
- Document exceptions and error conditions

### User Documentation
- Keep README.md up to date
- Add examples for new features
- Include troubleshooting section
- Maintain API reference

## 🔧 Development Tools

### Recommended Tools
- **IDE**: Visual Studio Code, CLion, or Visual Studio
- **Debugger**: GDB or LLDB
- **Profiler**: Valgrind, gprof, or built-in profilers
- **Static Analysis**: clang-tidy, cppcheck

### VS Code Extensions
- C/C++
- CMake Tools
- GitLens
- Doxygen Documentation Generator

## 🚨 Security

### Security Guidelines
- Validate all user inputs
- Use secure coding practices
- Avoid buffer overflows
- Sanitize file operations
- Report security issues privately

### Reporting Security Issues
Email security issues to: security@kalem-engine.org

## 📄 License

By contributing to Kalem, you agree that your contributions will be licensed under the MIT License.

## 🙏 Recognition

Contributors will be recognized in:
- README.md contributors section
- Release notes
- Project documentation

## 📞 Getting Help

- **Issues**: Use GitHub issues for bugs and feature requests
- **Discussions**: Use GitHub discussions for questions
- **Email**: contact@kalem-engine.org for private matters

Thank you for contributing to Kalem! 🎬✨ 
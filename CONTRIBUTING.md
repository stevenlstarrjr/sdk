# Contributing to Hultrix

Thank you for your interest in contributing to Hultrix! This document provides guidelines and instructions for contributing to the project.

## Table of Contents

- [Getting Started](#getting-started)
- [Development Setup](#development-setup)
- [Code Style](#code-style)
- [Making Changes](#making-changes)
- [Testing](#testing)
- [Submitting Changes](#submitting-changes)

## Getting Started

Before you begin:
- Make sure you have a GitHub account
- Familiarize yourself with the project by reading the README
- Check existing issues and pull requests to avoid duplicates

## Development Setup

### Prerequisites

- CMake 3.21 or higher
- C++17 compatible compiler (GCC, Clang, or MSVC)
- Git

#### Linux (Fedora/RHEL)
```bash
sudo dnf install gcc gcc-c++ make cmake git
```

#### Linux (Ubuntu/Debian)
```bash
sudo apt-get install build-essential cmake git
```

#### macOS
```bash
brew install cmake
```

### Building the Project

1. Clone the repository:
```bash
git clone https://github.com/yourusername/Hultrix.git
cd Hultrix
```

2. Configure and build:
```bash
cmake -B build -S .
cmake --build build
```

The project uses vcpkg for dependency management. Dependencies will be automatically downloaded and built on first configuration.

### Dependencies

The project uses the following libraries (managed via vcpkg):
- Skia (with fontconfig, freetype, harfbuzz, icu)
- bgfx
- Poco
- GLM
- OpenImageIO
- MiniAudio
- Google Test
- SDL3
- Boost

## Code Style

### General Guidelines

- Use C++17 features where appropriate
- Follow RAII principles
- Prefer smart pointers over raw pointers
- Use const correctness
- Write self-documenting code with clear variable and function names

### Formatting

- Indentation: Use spaces (typically 2 or 4 spaces)
- Braces: Opening brace on same line for functions and control structures
- Naming conventions:
  - Classes/Structs: PascalCase (e.g., `MyClass`)
  - Functions/Methods: camelCase (e.g., `myFunction`)
  - Variables: camelCase (e.g., `myVariable`)
  - Constants: UPPER_SNAKE_CASE (e.g., `MAX_SIZE`)
  - Private members: prefix with underscore (e.g., `_privateVar`) or use your preferred convention

### Comments

- Use `//` for single-line comments
- Use `/* */` for multi-line comments
- Document public APIs with descriptive comments
- Explain "why" not "what" in comments

## Making Changes

### Branching Strategy

1. Create a new branch for your work:
```bash
git checkout -b feature/your-feature-name
```

2. Use descriptive branch names:
   - `feature/` for new features
   - `bugfix/` for bug fixes
   - `refactor/` for code refactoring
   - `docs/` for documentation changes

### Commits

- Write clear, concise commit messages
- Use present tense ("Add feature" not "Added feature")
- Reference issue numbers when applicable (e.g., "Fix #123: Description")
- Keep commits focused and atomic

Example commit message:
```
Add rendering pipeline for UI elements

- Implement basic render loop
- Add support for hardware acceleration
- Integrate with bgfx backend

Fixes #42
```

## Testing

### Running Tests

```bash
cd build
ctest --output-on-failure
```

### Writing Tests

- Write unit tests for new functionality using Google Test
- Place tests in appropriate test directories
- Ensure all tests pass before submitting a pull request
- Aim for good test coverage

Example test:
```cpp
#include <gtest/gtest.h>
#include "your_module.h"

TEST(YourModuleTest, TestCase) {
  // Arrange
  YourClass obj;

  // Act
  auto result = obj.someMethod();

  // Assert
  EXPECT_EQ(result, expectedValue);
}
```

## Submitting Changes

### Pull Request Process

1. Ensure all tests pass
2. Update documentation if needed
3. Push your branch to your fork
4. Create a pull request with:
   - Clear title describing the change
   - Detailed description of what changed and why
   - Reference to related issues
   - Screenshots (if UI changes)

### Pull Request Template

```markdown
## Description
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Breaking change
- [ ] Documentation update

## Related Issues
Fixes #(issue number)

## Testing
Describe how you tested your changes

## Checklist
- [ ] Code follows project style guidelines
- [ ] Self-review completed
- [ ] Comments added for complex code
- [ ] Documentation updated
- [ ] No new warnings generated
- [ ] Tests added/updated
- [ ] All tests pass
```

### Code Review

- Be patient and respectful during code review
- Address all feedback or explain why you disagree
- Be open to suggestions and improvements
- All pull requests require approval before merging

## Questions?

If you have questions or need help:
- Open an issue for discussion
- Reach out to maintainers
- Check existing documentation

Thank you for contributing to Hultrix!

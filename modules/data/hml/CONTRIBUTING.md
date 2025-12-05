# Contributing to HML

We love your input! We want to make contributing to HML as easy and transparent as possible, whether it's:

- Reporting a bug
- Discussing the current state of the code
- Submitting a fix
- Proposing new features
- Becoming a maintainer

## Development Process

We use GitHub to host code, track issues and feature requests, and accept pull requests.

## Code of Conduct

This project and everyone participating in it is governed by our Code of Conduct. By participating, you are expected to uphold this code.

## How to Contribute

### Reporting Bugs

We use GitHub issues to track public bugs. Report a bug by [opening a new issue](https://github.com/yourusername/hml/issues).

**Great Bug Reports** tend to have:

- A quick summary and/or background
- Steps to reproduce
  - Be specific!
  - Give sample code if you can
- What you expected would happen
- What actually happens
- Notes (possibly including why you think this might be happening, or stuff you tried that didn't work)

### Suggesting Features

We use GitHub issues to track feature requests. Feature requests are welcome! But take a moment to find out whether your idea fits with the scope and aims of the project.

**Great Feature Requests** include:

- A clear and descriptive title
- A detailed description of the proposed feature
- Use cases and examples
- Possible implementation approach (optional)

### Pull Requests

1. Fork the repo and create your branch from `main`.
2. If you've added code that should be tested, add tests.
3. If you've changed APIs, update the documentation.
4. Ensure the test suite passes.
5. Make sure your code lints.
6. Issue that pull request!

## Development Setup

### Prerequisites

- C++17 compiler
- CMake 3.16+
- ANTLR4 C++ runtime

See [BUILDING.md](BUILDING.md) for detailed setup instructions.

### Building

```bash
git clone https://github.com/yourusername/hml.git
cd hml
mkdir build && cd build
cmake ..
make -j4
```

### Running Tests

```bash
# Run the demo to ensure everything works
./test_hml

# Test with examples
./test_hml examples/basic/hello-world.hml
./test_hml examples/basic/primitives-showcase.hml
```

## Coding Style

### C++ Guidelines

- Follow [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
- Use C++17 features appropriately
- Prefer RAII and smart pointers
- Use meaningful variable and function names

### Code Formatting

- Use 4 spaces for indentation (no tabs)
- Maximum line length: 100 characters
- Place opening braces on the same line
- Use `camelCase` for variables and functions
- Use `PascalCase` for classes and types

### Example:

```cpp
class HmlParser {
public:
    void parseFile(const std::string& filename) {
        if (filename.empty()) {
            throw std::invalid_argument("Filename cannot be empty");
        }
        
        // Implementation here
    }
    
private:
    std::map<std::string, std::string> variables;
};
```

### Grammar Style

For ANTLR4 grammar files (`.g4`):

- Use `camelCase` for rule names
- Use `UPPER_CASE` for token names
- Include comments for complex rules
- Group related rules together

### Example:

```antlr
// Variable declaration rule
variableDeclaration : VAR ID ':' typeAnnotation '=' propertyValue ;

// Type annotations
typeAnnotation : 'int' | 'string' | 'bool' | 'any' ;

// Keywords
VAR : 'var' ;
```

## File Organization

### Source Files

- `src/` - Core implementation
- `generated/` - ANTLR generated parser files
- `examples/` - Example HML files
- `docs/` - Documentation
- `build/` - Build artifacts

### Naming Conventions

- Source files: `snake_case.cpp`
- Header files: `snake_case.h`
- Class files: `ClassName.cpp` / `ClassName.h`
- Example files: `kebab-case.hml`

## Documentation

### Code Documentation

Use doxygen-style comments for public APIs:

```cpp
/**
 * @brief Parses an HML file and returns the AST
 * @param filename Path to the HML file
 * @return Parsed AST or nullptr on error
 * @throws std::runtime_error if file cannot be read
 */
std::unique_ptr<HmlAST> parseFile(const std::string& filename);
```

### README Updates

When adding features:

1. Update the main README.md
2. Add examples to appropriate sections
3. Update feature lists and roadmap

### API Documentation

When changing public APIs:

1. Update `docs/api/README.md`
2. Add examples to the documentation
3. Update any affected guides

## Testing

### Manual Testing

Always test your changes with:

```bash
# Build fresh
make -j4

# Test basic functionality
./test_hml

# Test your specific changes
./test_hml path/to/your/test.hml
```

### Grammar Testing

When modifying `Hml.g4`:

```bash
# Regenerate parser
mkdir -p generated
antlr4 -Dlanguage=Cpp -o generated Hml.g4 -visitor

# Rebuild
make -j4

# Test grammar changes
./test_hml examples/basic/primitives-showcase.hml
```

### Edge Cases

Test edge cases like:
- Empty files
- Malformed syntax
- Missing imports
- Circular dependencies
- Large files

## Git Commit Guidelines

### Commit Messages

Use the conventional commit format:

```
<type>(<scope>): <description>

[optional body]

[optional footer]
```

**Types:**
- `feat`: New feature
- `fix`: Bug fix
- `docs`: Documentation only
- `style`: Formatting changes
- `refactor`: Code restructuring
- `test`: Adding tests
- `chore`: Maintenance tasks

**Examples:**
```
feat(parser): add support for complex expressions

Adds mathematical operations in property values like:
width: ${baseWidth} * 2 + 10

Fixes #123
```

```
fix(grammar): resolve shift/reduce conflict in conditionals

The if/else grammar was ambiguous when nested.
Added precedence rules to resolve conflicts.
```

### Branch Naming

- `feature/feature-name` - New features
- `fix/bug-description` - Bug fixes
- `docs/update-description` - Documentation updates
- `refactor/component-name` - Refactoring

## Release Process

### Version Numbers

We use [Semantic Versioning](https://semver.org/):

- `MAJOR.MINOR.PATCH`
- Breaking changes → MAJOR
- New features → MINOR  
- Bug fixes → PATCH

### Creating Releases

1. Update version in `CMakeLists.txt`
2. Update `CHANGELOG.md`
3. Create release branch
4. Test thoroughly
5. Create tagged release
6. Update documentation

## Getting Help

### Communication

- **GitHub Issues** - Bug reports and feature requests
- **GitHub Discussions** - General questions and ideas
- **Email** - Contact maintainers directly for sensitive issues

### Resources

- [API Reference](docs/api/README.md)
- [Getting Started Guide](docs/guides/getting-started.md)
- [Building Instructions](BUILDING.md)
- [Example Gallery](examples/)

## Recognition

Contributors are recognized in:

- `CONTRIBUTORS.md` file
- Release notes
- GitHub contributor graphs
- Special mentions for significant contributions

## License

By contributing, you agree that your contributions will be licensed under the Apache License 2.0.

### Copyright Headers

All new files must include the Apache 2.0 license header:

```cpp
/*
 * Copyright 2024 HML Project Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
```

## Questions?

Don't hesitate to ask questions! We're here to help:

1. Check existing [GitHub Issues](https://github.com/yourusername/hml/issues)
2. Create a new issue with the `question` label
3. Start a [GitHub Discussion](https://github.com/yourusername/hml/discussions)

Thank you for contributing to HML! 🚀
# HML - HTML-like Markup Language

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)]()
[![C++ Standard](https://img.shields.io/badge/C%2B%2B-17-blue.svg)]()

HML is a modern, declarative UI description language that combines the simplicity of HTML-like syntax with the power of reactive programming. Built on just 6 primitive components, HML enables developers to create sophisticated user interfaces with clean, maintainable code.

## ✨ Features

### 🎯 **6 Powerful Primitives**
- **HMouseArea** - Input handling and interaction
- **HShape** - Visual styling and geometry
- **HText** - Text rendering and formatting
- **HImage** - Image display and loading
- **HLayout** - Positioning and layout management
- **HCanvas** - Custom drawing and graphics

### 🚀 **Modern Language Features**
- **Type System** - Strong typing with `int`, `string`, `bool`, `any`
- **Signals & Events** - Custom event system with typed parameters
- **Property Binding** - Reactive variable substitution
- **Conditionals** - Dynamic UI with `if/else` statements
- **Components** - Reusable component system with imports
- **Scripts** - Flexible JavaScript integration with timing control

### 🔧 **Developer Experience**
- **Clean Syntax** - Intuitive, HTML-like markup
- **Component System** - Import and compose reusable UI elements
- **Hot Reload** - Fast development cycle
- **Type Safety** - Catch errors at compile time
- **Comprehensive Tooling** - Built on ANTLR4 for robust parsing

## 🚀 Quick Start

### Prerequisites

- CMake 3.16+
- C++17 compiler (GCC 7+, Clang 6+, MSVC 2019+)
- ANTLR4 C++ runtime

### Installation

```bash
# Clone the repository
git clone https://github.com/yourusername/hml.git
cd hml

# Build the project
mkdir build && cd build
cmake ..
make -j4

# Run the demo
./test_hml
```

### Your First HML File

Create `hello.hml`:

```hml
// Variables with types
var title: string = "Hello, HML!"
var buttonWidth: int = 200

// Main window
Window {
    title: ${title}
    width: 800
    height: 600
    
    // Centered layout
    HLayout {
        direction: "column"
        spacing: 20
        
        // Welcome text
        HText {
            text: "Welcome to HML"
            fontSize: 24
            color: "#333"
        }
        
        // Interactive button
        HMouseArea {
            signal clicked()
            
            width: ${buttonWidth}
            height: 50
            
            HShape {
                background: "#007acc"
                borderRadius: 8
            }
            
            HText {
                text: "Click Me!"
                color: "white"
                align: "center"
            }
            
            onClicked: `console.log("Button clicked!");`
        }
    }
}
```

## 📚 Language Reference

### Variables

```hml
var name: string = "HML"
var width: int = 100
var visible: bool = true
var data: any = 42
```

### Signals and Events

```hml
HMouseArea {
    // Declare custom signals
    signal customClick(x: int, y: int)
    signal dragStarted()
    
    // Event handlers
    onCustomClick: `console.log("Clicked at", x, y);`
    onDragStarted: `this.startDragMode();`
}
```

### Conditionals

```hml
var showAdvanced: bool = true

if (showAdvanced == true) {
    HText { text: "Advanced Options" }
} else {
    HText { text: "Basic Options" }
}
```

### Scripts

```hml
// External script files
script "utils.js"                    // Load immediately
script defer "init.js"               // Load after UI
script async "analytics.js"          // Load in background

// Inline scripts
script `
    function initialize() {
        console.log("App started");
    }
`
```

### Components

**MyButton.hml:**
```hml
MyButton {
    width: 120
    height: 40
    background: "#007acc"
    
    HText {
        text: "Button"
        color: "white"
    }
}
```

**main.hml:**
```hml
import "MyButton.hml"

Window {
    MyButton {
        text: "Custom Text"    // Override default properties
        width: 150
    }
}
```

## 🏗️ Architecture

### The 6 Primitives

| Primitive | Purpose | Key Features |
|-----------|---------|--------------|
| **HMouseArea** | Input handling | Click, drag, hover events |
| **HShape** | Visual styling | Colors, borders, shadows |
| **HText** | Text display | Fonts, colors, formatting |
| **HImage** | Image rendering | Loading states, scaling |
| **HLayout** | Positioning | Flexbox-like layout |
| **HCanvas** | Custom graphics | 2D drawing, animations |

### Component Composition

Everything in HML is built by composing these 6 primitives:

```hml
// A button is just primitives composed together
Button {
    HMouseArea {          // Handle clicks
        HShape {          // Visual appearance  
            HText {       // Button label
                text: "Click Me"
            }
        }
    }
}
```

## 🎨 Examples

### Responsive Layout

```hml
var screenWidth: int = 1200
var isMobile: bool = false

HLayout {
    direction: ${isMobile} ? "column" : "row"
    spacing: ${isMobile} ? 10 : 20
    
    if (isMobile == false) {
        Sidebar { width: 250 }
    }
    
    MainContent { 
        width: ${screenWidth} - 250
    }
}
```

### Interactive Form

```hml
Form {
    signal submitted(data: string)
    
    var email: string = ""
    var password: string = ""
    
    HLayout {
        direction: "column"
        spacing: 15
        
        TextInput {
            placeholder: "Email"
            onTextChanged: `email = newText;`
        }
        
        TextInput {
            placeholder: "Password"
            inputType: "password"
            onTextChanged: `password = newText;`
        }
        
        Button {
            text: "Sign In"
            onClicked: `this.submit({email, password});`
        }
    }
}
```

### Data-Driven UI

```hml
var users: any = ["Alice", "Bob", "Charlie"]

UserList {
    HLayout {
        direction: "column"
        
        // Dynamic user cards (future feature)
        // Repeater {
        //     model: users
        //     delegate: UserCard { name: ${model} }
        // }
    }
}
```

## 🔧 Building and Development

### Dependencies

- **ANTLR4** - Parser generator
- **CMake** - Build system
- **C++17** - Modern C++ features

### Project Structure

```
hml/
├── src/
│   ├── Hml.g4              # Grammar definition
│   ├── test_hml.cpp        # Parser implementation
│   └── CMakeLists.txt      # Build configuration
├── examples/
│   ├── basic/
│   ├── components/
│   └── advanced/
├── docs/
│   ├── api/
│   ├── guides/
│   └── tutorials/
├── LICENSE                 # Apache 2.0 License
└── README.md              # This file
```

### Development Workflow

1. Modify `Hml.g4` grammar
2. Regenerate parser: `antlr4 -Dlanguage=Cpp Hml.g4 -visitor`
3. Build: `make -j4`
4. Test: `./test_hml`

## 🤝 Contributing

We welcome contributions! Please see our [Contributing Guide](CONTRIBUTING.md) for details.

### Development Setup

```bash
# Fork and clone the repo
git clone https://github.com/yourusername/hml.git
cd hml

# Create a feature branch
git checkout -b feature/amazing-feature

# Make your changes and test
make -j4 && ./test_hml

# Commit and push
git commit -m "Add amazing feature"
git push origin feature/amazing-feature
```

## 📖 Documentation

- [API Reference](docs/api/README.md)
- [Getting Started Guide](docs/guides/getting-started.md)
- [Component Library](docs/components/README.md)
- [Advanced Features](docs/advanced/README.md)

## 🚧 Roadmap

### Current (v1.0)
- ✅ 6 Primitive system
- ✅ Type system
- ✅ Signals & Events
- ✅ Property binding
- ✅ Component system

### Planned (v1.1)
- 🔄 Complex expressions (`width: ${height} * 2`)
- 🔄 Reactive updates (live property binding)
- 🔄 Animation system
- 🔄 Data models and repeaters

### Future (v2.0)
- 🔮 Visual editor
- 🔮 Hot reload
- 🔮 Theme system
- 🔮 Plugin architecture

## 📄 License

This project is licensed under the Apache License 2.0 - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- **ANTLR4** - Powerful parser generation
- **QML** - Inspiration for declarative UI
- **React** - Component architecture patterns
- **Flutter** - Modern UI framework concepts

---

**Built with ❤️ for the developer community**
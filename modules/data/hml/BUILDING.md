# Building HML

This guide covers how to build HML from source on different platforms.

## Prerequisites

### All Platforms

- **CMake 3.16+**
- **C++17 compiler**
- **ANTLR4 C++ runtime**

### Platform-Specific Requirements

#### Ubuntu/Debian

```bash
sudo apt update
sudo apt install -y \
    build-essential \
    cmake \
    antlr4 \
    libantlr4-runtime-dev \
    git
```

#### macOS

```bash
# Install Xcode command line tools
xcode-select --install

# Install dependencies via Homebrew
brew install cmake antlr antlr4-cpp-runtime
```

#### Windows

1. Install **Visual Studio 2019+** with C++ tools
2. Install **CMake** from https://cmake.org/download/
3. Install **ANTLR4** runtime:
   - Download from https://www.antlr.org/download.html
   - Follow Windows installation guide
   - Set `ANTLR4_ROOT` environment variable

#### Fedora/CentOS/RHEL

```bash
sudo dnf install -y \
    gcc-c++ \
    cmake \
    antlr4-cpp-runtime-devel \
    git
```

## Building from Source

### Clone Repository

```bash
git clone https://github.com/yourusername/hml.git
cd hml
```

### Configure Build

```bash
mkdir build
cd build
cmake ..
```

#### CMake Options

```bash
# Specify ANTLR4 location (if needed)
cmake -DANTLR4_ROOT=/path/to/antlr4 ..

# Debug build
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Release build
cmake -DCMAKE_BUILD_TYPE=Release ..

# Custom install prefix
cmake -DCMAKE_INSTALL_PREFIX=/usr/local ..
```

### Build

```bash
# Build with all available cores
make -j$(nproc)

# Or specify core count
make -j4
```

### Test Build

```bash
# Run the demo
./test_hml

# Should output parsed HML structure without errors
```

## Development Build

### Regenerate Parser (when modifying grammar)

```bash
# From project root
mkdir -p generated
antlr4 -Dlanguage=Cpp -o generated Hml.g4 -visitor

# Then rebuild
cd build
make -j4
```

### Clean Build

```bash
# Remove build directory
rm -rf build

# Start fresh
mkdir build && cd build
cmake ..
make -j4
```

## IDE Setup

### Visual Studio Code

Install recommended extensions:
- C/C++ Extension Pack
- CMake Tools
- ANTLR4 grammar syntax support

### CLion

CLion should automatically detect the CMake project.

### Visual Studio (Windows)

Open the folder in Visual Studio 2019+ with CMake support.

## Cross-Compilation

### Example: ARM64

```bash
# Install cross-compilation toolchain
sudo apt install gcc-aarch64-linux-gnu g++-aarch64-linux-gnu

# Configure for ARM64
mkdir build-arm64
cd build-arm64
cmake -DCMAKE_SYSTEM_NAME=Linux \
      -DCMAKE_SYSTEM_PROCESSOR=aarch64 \
      -DCMAKE_C_COMPILER=aarch64-linux-gnu-gcc \
      -DCMAKE_CXX_COMPILER=aarch64-linux-gnu-g++ \
      ..

make -j4
```

## Troubleshooting

### Common Issues

**CMake can't find ANTLR4:**
```bash
# Specify path explicitly
cmake -DANTLR4_ROOT=/usr/local ..

# Or install development package
sudo apt install libantlr4-runtime-dev
```

**C++17 not supported:**
```bash
# Check compiler version
g++ --version  # Should be 7.0+
clang++ --version  # Should be 6.0+

# Update if needed (Ubuntu)
sudo apt install gcc-9 g++-9
```

**ANTLR4 version mismatch:**
```bash
# Check versions match
antlr4 -version
pkg-config --modversion antlr4-runtime

# Rebuild grammar if needed
antlr4 -Dlanguage=Cpp Hml.g4 -visitor
```

**Permission denied errors:**
```bash
# Ensure execute permissions
chmod +x test_hml

# Check file ownership
ls -la test_hml
```

### Getting Help

1. Check the [FAQ](docs/FAQ.md)
2. Search existing [GitHub Issues](https://github.com/yourusername/hml/issues)
3. Create a new issue with:
   - OS and version
   - Compiler version
   - Complete error output
   - Steps to reproduce

## Performance Tips

### Faster Builds

```bash
# Use Ninja generator (faster than Make)
cmake -GNinja ..
ninja

# Use ccache for faster rebuilds
sudo apt install ccache
export CC="ccache gcc"
export CXX="ccache g++"
cmake ..
make -j4
```

### Optimized Release

```bash
cmake -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_CXX_FLAGS="-O3 -march=native" \
      ..
make -j4
```

## Packaging

### Create Distribution

```bash
# Configure for packaging
cmake -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/usr \
      ..

# Build and create package
make -j4
make package
```

### Install System-Wide

```bash
# Build with proper prefix
cmake -DCMAKE_INSTALL_PREFIX=/usr/local ..
make -j4

# Install (requires sudo)
sudo make install
```

This will install:
- `hml_parser` library to `/usr/local/lib`
- Headers to `/usr/local/include/hml`
- Documentation to `/usr/local/share/doc/hml`

## Next Steps

After successful build:

1. Run examples: `./test_hml examples/basic/hello-world.hml`
2. Read the [Getting Started Guide](docs/guides/getting-started.md)
3. Check out the [API Reference](docs/api/README.md)
4. Try building your own HML applications!
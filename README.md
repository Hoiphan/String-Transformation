# String Transformation: Minimum Operations

This website and API were built to solve the **String Transformation (Minimum Operations)** problem, calculating the exact number of edits required to transform one string into another.

This project is built on top of a C++ backend template that uses CMake as the build system, vcpkg as the dependency manager, Crow as the web framework, and features full Docker and Docker Compose support. It also provides already defined Microsoft-like formatting options with `clang-format`.

---

## 🌐 Live Website & CI/CD Architecture

If you just want to use the web application, I have already deployed it! Please visit:
👉 **[http://20.204.173.70](http://20.204.173.70)**

**Automated Deployment:**
I also built a GitHub Actions CI/CD pipeline for this project. Whenever code is pushed, the pipeline automatically builds the image, pushes this image to Docker Hub, and after that, deploys the image to a VPS (Azure).

---

## ⚙️ Dependencies

To clone and use this project on your local machine, you need:

- A C++ compiler (C++23 is used by default; edit the `CMakeLists.txt` config if you want to use a different standard)
- CMake (3.14.0 >=)
- vcpkg
- Docker and Docker Compose
- clang-format (optional, used to format code)

---

## 🚀 How to Run Locally

You can clone this repository and run it locally in different ways depending on your preference.

### Option 1: Run with Docker Compose

If you want to run this by Docker Compose without installing local C++ tools, simply run:

```bash
make up
```

### Option 2: Native Local Build

If you want to run it locally on your own machine's hardware:

```bash
make devenv
cmake --build build
./bin/cpp-backend-template
```

### 🧪 Testing the Algorithm

If you want to test the algorithm, just put your test cases in the tests/algorithm_test.cpp file and run:

```bash
make devenv
cmake --build build
./bin/backend_tests
```

This will show whether your test case is valid or not directly in the console output.

### 🙏 Acknowledgments

I coded this project based on this template from this project: https://github.com/landiluigi746/cpp-backend-template.

I highly appreciate it, because it helped me do this stuff faster and effectively!


## **Contributing**

This project is developed mainly on **Linux Mint** using **NeoVim**.

- Pull Requests are **welcome**!
- For major changes, please open a **discussion/issue** first.
- Constructive feedback is appreciated.

## **Compilation Guide:**
## **Windows**
You need:

 - CMake → the build system generator
   - 🔗 Download from https://cmake.org/download/
 - Compiler toolchain:
   - MinGW or LLVM/Clang → if you prefer GCC-style.
   - 🔗 Download from https://sourceforge.net/projects/mingw/

**cmake command**:
```bash 
cmake -S . -B out -G "MinGW Makefiles"
cmake --build out
```

Don't forget to clone and compile glfw:
```bash
git clone https://github.com/glfw/glfw.git
    cmake -S glfw -B glfw/build -G "MinGW Makefiles" -DBUILD_SHARED_LIBS=OFF
    cmake --build glfw/build --config Release
    mkdir -p libs/lib
    cp glfw/build/src/libglfw3.a libs/lib/
```

---
## **Linux**
You just need to install `build-essential` and `glfw` using your package manager.

### **Fedora**

```bash
dnf install glfw-devel cmake make freetype-devel automake gcc gcc-c++ kernel-devel mesa-libGL-devel mesa-libGLU-devel
```

### **Debian/Ubuntu**

```bash
apt install build-essential libglfw3-dev libfreetype6-dev
```

### **CMake command**:
```bash 
cmake -S . -B out
cmake --build out
```
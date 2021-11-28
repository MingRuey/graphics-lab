# DrawSvg
Playground for a  SVG drawer from Scratch

## Build Process

First we have to use the Microsoft cl.exe from terminal. [General guide](https://docs.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=msvc-170) is here. 
Specifically, we use [x64 Native Tools Command Prompt for VS 2019](https://docs.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=msvc-170#developer_command_prompt_shortcuts)

```cmd
mkdir build
cd build
cmake ..
msbuild ./DrawSVG.sln
```

After build, one can trigger the output executable by
```cmd
.\Debug\main.exe
```

## Depedency Explained

The libraries in `lib` and header files `include/GLFW`is directly from [official site (64bit Windows)](https://www.glfw.org/download.html).
After downloading, we get the `xxxx.lib` from `lib-vc2019` inside the download zip file.

For GLAD files, we generate the `glad.c`, `glad.h` & `khrplatform.h` from [GLAD web service](https://glad.dav1d.de/).
The paramaters for the web service is:
- Language: C/C++
- Specification: OpenGL
- Profile: Core
- API:
    - gl: Version 4.6
    - gles1 ~ glsc2: None
- Extensions: None (i.e. remain blank)
- [x] Generate a loader
- [ ] Omit KHR
- [ ] Local Files


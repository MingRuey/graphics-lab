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

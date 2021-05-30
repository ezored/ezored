# Targets

Targets are generally a platform (like macos or android).

The target have all files and scripts to build C++ code to some platform. You can see all targets inside folder **"files/targets"**.

Currently all targets use CMake to compile and generate project files ready to build. So each target has their own **CMakeLists.txt** file inside target folder called **"cmake"**, example `files/targets/linux/cmake/CmakeLists.txt`.

And the target have a **module** for it, that contains specific C++ code for that platform and is imported by **CMakeLists.txt** file, example `files/modules/target-linux/cmake/module.cmake`.

Generally all targets share the most used C++ in the project and because of this Ezored has a commom CMake file `files/common/cmake/common.cmake`.

Some targets add more source files and compile parameters. Some examples are the targets **"android"** that add their JNI files and **"ios"** that add their OBJC files.

A target has their **"verbs"** that can have any name like **build**, **package** etc. All verbs are stored inside **"verbs"** folder of a target and this will be used to appear on target verb list when you call the target on terminal. Example:

```python make.py target linux```

and

```python make.py target linux build```

It will execute bootstrap file of Ezored, that will do some validations and will search for a file with the path `files/targets/linux/verbs/build.py` and will send all parameter to a function called **run** inside it.

If you don't remember what verbs are available for a target you can type only this to list all verbs:

```python make.py target linux```

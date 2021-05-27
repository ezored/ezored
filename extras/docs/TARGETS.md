<p align="center"><a href="https://github.com/ezored/ezored" target="_blank" rel="noopener noreferrer"><img width="180" src="../images/doc-logo.png" alt="ezored logo"></a></p>

<h1 align="center"><strong>Targets</strong></h1>

A target in ezored contains all files and scripts to build C++ code to some platform. You can see on folder **"files/targets"**.

Currently all targets use CMake to compile and generate project files ready to build. So each target has their own **CMakeLists.txt** file inside target folder **"cmake"**.

Generally all targets shared the same C++ code and because of this ezored has a commom **CMakeLists.txt** file inside folder **"files/common/cmake"**.

Some targets add more source files and compile parameters. Some examples are the targets **"android"** that add their JNI files and **"ios"** that add their OBJC files.

A target has their **"verbs"** that can have any file name like **"build"**, **"package"** etc. All verbs are stored inside **"verbs"** folder of a target and this will be used to appear on target verb list when you call on terminal. Example:

```python make.py target android build```

It will execute bootstrap file of ezored, that will do some validations and will search for a file with the path **"files/targets/android/verbs/build.py"** and will send all parameter to a function called **"run"** inside it.

If you don't remember what verbs are available for a target you can type only this to list all verbs:

```python make.py target android```

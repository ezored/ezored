# ezored

## About

This project is a collection of tools, ready to use, to fastest compile C/C++ code for current supported platforms.

You can get the project code as a start project and evolve it to your needs.

The goal of ezored is keep the focus on C/C++ code. You can keep your business code fastest and secure as possible in native code and reuse it on all supported platforms.

But ezored don't replace platform code (dialogs, user interface, activity, view controllers, button etc), it let you only reuse your single C/C++ code between supported platforms and on each platform you need only implement visual things that will call native functions.

To show it working, inside folder "projects" we have a simple Desktop app, and a mobile app for Android and iOS. All 3 applications use the same C/C++ code, but the interface was built using their platorm code.

It come with a lot of modules that share C/C++ code between mobile and desktop platforms.

The main advantage is have a single code with business logic and other teams only focusing on their platform code.

You can use it for free, for any purpose, including commercial purposes.

Feel free to collaborate with ezored, creating or improving the project and modules.

## Supported platforms:

1. android
2. iOS
3. macOS
4. linux
5. windows

Obs: Generally any platform with C/C++ supported will work too, like smart tvs.

## Modules:

A module in ezored is C++ implementation of one specific feature. Ezored come with some modules already implemented:

1. **datetime**  
    Some functions to work with date and time.
2. **file helper**  
    Helper functions to work with files (write, read, create folder, delete files etc).
3. **http client**  
    A http client to make http and https requests.
4. **logger**  
    Logger functions to show messages with different levels.
5. **shared data**  
    Shared data storage (android = shared preferences, ios = NSUserDefaults)
6. **string helper**  
    Some string helper functions.
7. **support lib**  
    Mobile modules use djinni, and for mobile (Android and iOS) this module is used to make the bridge between codes works.
8. **sqlite3**  
    SQLite3 come with ezored and let you use the same database on all platforms. Internally you can check our migration implementation. A library called "sqlitecpp" is used too, and make the job more easy.
9. **rapidjson**  
    RapidJSON is used to parsing json from remote requests in ezored samples. It works on all tested platforms nice and fast.

Modules are stored in "files/djinni" and "files/src".

## Targets:

A target in ezored contains all files, config and scripts to build C++ code to the platform. You can see on folder "files/targets".

Currently all targets use cmake structure to compile all. So each target has their own **CMakeLists.txt** file inside target folder "cmake".

Generally all targets shared the same C/C++ code and because of this ezored has a commom **CMakeLists.txt** file inside folder "files/cmake/common". Some targets add more source files, "android_aar" add their JNI files and "ios_framework" add their OBJC files.

A target has their "verbs", that can be any file name "build", "package" etc. All verbs are store inside "verbs" folder of a target and the file name will be use to find it when you call on terminal. Example:

```python make.py target android_aar build```

It will execute bootstrap file of ezored, that will do some validations and will search for a file with the path "files/targets/android_aar/verbs/build.py" and will send all parameter to a function called "run" inside it.

If you don't remember what verbs are available for a target you can type only this to list all verbs:

```python make.py target android_aar```

## Commands:

A command in ezored is a python file too and a function inside it that will receive all command line arguments use. Example:

```python make.py clean```

With this command ezored will search for a file with path "files/commands/clean/clean.py" and will send all parameter to a function called "run" inside it.

If you don't remember what commands are available you can type only this to list all commands:

```python make.py```

## Requirements:

**The general requirements is:**

1. Python (https://www.python.org/)
2. cmake (https://cmake.org/)
3. conan (https://conan.io/)

They are the basic things to make ezored work. Check on terminal if you have every tool in your path typing their names (python, cmake, conan).  

Each platform requirements list now. Maybe you already have it, because are basic tools.

**Android Requirements:**

Everything works without extra installs. Conan will download NDK and other things to build.  

**iOS Requirements:**

1. macOS operational system.
2. Xcode.
3. Command line tools.  
    Run: ```xcode-select --install```

**macOS Requirements:**

1. macOS operational system.
2. Xcode.
3. Command line tools.  
    Run: ```xcode-select --install```
4. macOS system headers.  
    Run: ```open /Library/Developer/CommandLineTools/Packages/macOS_SDK_headers_for_macOS_10.14.pkg```  
    The path can change for each macOS version (10.14 is mojave) and this is required because old softwares search on old places for this headers, like old openssl versions.

**Linux Requirements:**

1. Linux operational system.
2. C/C++ compiler installed.  
    Obs: On Ubuntu run on terminal "sudo apt install build-essential".

**Windows Requirements:**

1. Windows operational system.
2. Visual Studio installed.  
    Obs 1: Current example in ezored is using version 2017 Win64, change for your needs.  
    Obs 2: Everything was compiled using community version (https://visualstudio.microsoft.com/vs/community/).  
    Obs 3: On installation process select "Desktop development with C++".

## How to use:

1. Clone reposity:
> git clone git@github.com:ezored/ezored.git

2. Enter on cloned folder:
> cd ezored

3. Test it with the following command to show bootstrap menu:
> python make.py

4. Install conan profiles:
> python make.py conan install_profiles

5. Now all commands are available. To list all targets that you can build run:
> python make.py target

Example: If you are on Linux, you can build the **linux_app** target, if on macOS you can run **macos_app** target and if on windows you can run **windows_app**.  

> python make.py target linux_app conan  
> python make.py target linux_app build  
> python make.py target linux_app package  

**Obs:**  

1. After run this commands above, a folder called **"dist"** will be created with compiled binaries of applications. The rule is the same for other targets.  
2. The execution order is important. Before build your targets, install conan dependencies, build it and finally package. Package verbs will copy files to a non versioned folder called **"dist"** in root path.
3. You don't need run conan verb everytime, only run if you never run it before or if you change configuration, added dependencies, changed dependency version or other things that need call conan to rebuilt your dependencies.
4. Conan profiles are required to specify basic environment profile things to build targets, but some settings are changed while build, like **arch** and **build_type**.  
5. Check requirements for each target. Example: iOS target require that you have a macOS system.

## Dist folder prebuilt

The folder containing all prebuilt things (android, ios, windows, macOS and linux) are not versioned, but you can download a full version here:

> http://public.ezored.com/ezored/precompiled/dist.zip

Unzip it and put on your root folder. After it you can execute all desktop apps and all mobile apps.

## Djinni

Almost all modules use djinni to generate bridge files between C++ and mobile platform code (Android and iOS - Java, JNI, ObjC and ObjC++ files).

If you want create more modules, ezored come with a easy way to do it. Only duplicate any folder inside "files/djinni" and change files:

- proj.djinni
- generate.py

The file "proj.djinni" contain all interface things to be generated and file "generate.py" contain the script that will call djinni passing all required params, only change the params (package name, namespace etc).

If you will use djinni to generate files follow these steps:  

1. Download djinni (https://github.com/dropbox/djinni).
2. Set environment var **DJINNI_HOME** as the root folder of djinni (where you clone or download it).

## Projects:

We have some samples inside "projects" folder. 

Android sample can be download here:
https://play.google.com/store/apps/details?id=com.ezored.sample

## Supported By Jetbrains IntelliJ IDEA

![Supported By Jetbrains IntelliJ IDEA](extras/images/jetbrains-logo.png "Supported By Jetbrains IntelliJ IDEA")

## License

[MIT](http://opensource.org/licenses/MIT)

Copyright (c) 2017-present, Paulo Coutinho
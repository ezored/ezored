# ezored

![](extras/images/doc-logo.png)

![Ezored - macOS](https://github.com/ezored/ezored/workflows/Ezored%20-%20macOS/badge.svg)
![Ezored - Linux](https://github.com/ezored/ezored/workflows/Ezored%20-%20Linux/badge.svg)
![Ezored - Windows](https://github.com/ezored/ezored/workflows/Ezored%20-%20Windows/badge.svg)
![Ezored - iOS](https://github.com/ezored/ezored/workflows/Ezored%20-%20iOS/badge.svg)
![Ezored - Android](https://github.com/ezored/ezored/workflows/Ezored%20-%20Android/badge.svg)

## About

**Write once and compile anywhere**

C++ cross-platform development toolkit.

Use the same code on mobile and desktop applications.

Ezored is the most convenient and fatest way to start your C++ project for mobile and desktop.

**Toolkit**

Use this toolkit to generate a native SDK to plug into your **new** or **already existing** application and call SDK methods from your project in Swift, ObjectiveC, Java, Kotlin, Cordova or Flutter.

Ezored toolkit is a simple but well designed structure of scripts and folders that make this job very easy, leaving you thinking about your project instead of structure it. Download this repository and check samples to test and see it working.

**SDK**

Write C++ code and build shared libraries for mobile (Android is **AAR** and iOS is **Framework**) and **binary executables** or **shared libraries** for desktop (Linux, macOS and Windows).

Don't think about how you will start your C++ project for **mobile** and **desktop**, use ezored as a quick start toolkit.

![](extras/images/what-is.png)

**Free for ever**

You can use it for free, for any purpose, including commercial purposes.

Feel free to collaborate with ezored, creating or improving the main project, samples and modules.

After download ezored you need upload to your repository because all C++ code will only make sense to your project.

## Supported platforms

1. Android
2. iOS
3. macOS
4. Linux
5. Windows

Obs: Generally any platform with C++ support will work too, like smart TVs and embeded devices.

## Modules

A module in ezored is C++ implementation of one specific feature and ezored come with some modules already implemented:

1. **date and time helper**  
    Functions to work with date and time.

2. **file helper**  
    Functions to work with files (write, read, create folder, delete files etc).

3. **http client**  
    Http client to make http and https requests.

4. **logger**  
    Logger functions to show messages with different levels.

5. **shared data**  
    Shared data storage.

    1. Android = using shared preferences
    2. iOS = using NSUserDefaults
    3. Desktop = using local file

6. **string helper**  
    Functions to work with string.

7. **database**  
    SQLite3 is ready to use with ezored and let you use the same database on all platforms. Internally you can check our scheme migration implementation. A library called "sqlitecpp" is used to make this job easier.

8. **json**  
    RapidJSON is used to parsing json from remote requests in ezored samples. It works on all tested platforms nice and fast.

9. **support lib**  
    Mobile bridge code is automatically generated using Dropbox Djinni tool. It can be removed if you do it manually.

Modules source code are stored in **"files/src"** and **"files/djinni"**.

## Targets

A target in ezored contains all files and scripts to build C++ code to the target platform. You can see on folder **"files/targets"**.

Currently all targets use CMake to compile and generate project files ready to build. So each target has their own **CMakeLists.txt** file inside target folder **"cmake"**.

Generally all targets shared the same C++ code and because of this ezored has a commom **CMakeLists.txt** file inside folder **"files/cmake/common"**.

Some targets add more source files and compile parameters. Some examples are the targets **"android_aar"** that add their JNI files and **"ios_framework"** that add their OBJC files.

A target has their **"verbs"**, that can be any file name **"build"**, **"package"** etc. All verbs are store inside **"verbs"** folder of a target and the file name will be use to find it when you call on terminal. Example:

```python make.py target android_aar build```

It will execute bootstrap file of ezored, that will do some validations and will search for a file with the path **"files/targets/android_aar/verbs/build.py"** and will send all parameter to a function called "run" inside it.

If you don't remember what verbs are available for a target you can type only this to list all verbs:

```python make.py target android_aar```

## Commands

Every command script in ezored is a python file. 

All commands are simple functions that will receive command line arguments and based on this arguments will executed desired operations. Example:

```python make.py clean```

With this execution ezored will search for a file with path **"ezored/bcommands/clean.py"** or **"files/commands/clean.py"** and will send all parameter to a function called **"run"** inside file **clean.py**.

If you don't remember what commands are available you can type only this to list all commands:

```python make.py```

If you want create your own commands you only need put it inside folder **"files/commands"** and **ezored** already has some custom commands. One example of custom command inside **ezored** is **dist** that is located in **files/commands/dist.py**.

## Requirements

**The general requirements is:**

1. Python 3 (https://www.python.org/)  
2. Cmake 3.14 (https://cmake.org/)  
3. Conan 1.20.1 (https://conan.io/)
4. Conan repositories:    
- `conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan`
- `conan remote add darwin-toolchain https://api.bintray.com/conan/ezored/conan-darwin-toolchain`

They are the basic things to make ezored work. Check on terminal if you have every tool in your path typing their names (python, cmake, conan).

Each platform requirements list now. Maybe you already have it, because are basic tools.

**Android Requirements:**

1. Supported operational system for NDK: macOS, Linux or Windows.  
    
    Conan will download NDK and other things to build based on your system.

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
2. C++ compiler installed.

    Example: On Ubuntu run on terminal: ```sudo apt install build-essential```.

**Windows Requirements:**

1. Windows operational system.
2. Visual Studio installed.  

    Obs 1: Current example in ezored is using version 2017 (15), change for your needs in conan profile file.

    Obs 2: Everything was compiled using community version (https://visualstudio.microsoft.com/vs/).  

    Obs 3: On installation process select "Desktop development with C++".  

## How to use

1. Clone reposity:
> git clone https://github.com/ezored/ezored.git

2. Enter on cloned folder:
> cd ezored

3. Execute to download **ezored-core** and to show bootstrap menu:
> python make.py

4. Install conan profiles:
> python make.py conan install_profiles

5. Now all commands are available. run the following command to list all targets that you can build:
> python make.py target

Example: If you are on **Linux**, you can build the **linux_app** target, if on **macOS** you can run **macos_app** target and if on **Windows** you can run **windows_app**.

> python make.py target linux_app conan  
> python make.py target linux_app build  
> python make.py target linux_app package  

**Obs:**

1. You can download the project as a ZIP file too: https://github.com/ezored/ezored/archive/master.zip.
2. After run this commands above, a folder called **"dist"** will be created with compiled binaries of applications. The rule is the same for other targets.
3. The execution order is important. Before build your targets, install conan dependencies, build it and finally package. Package verbs will copy files to a non versioned folder called **"dist"** in root path.
4. You don't need run conan verb everytime, only run if you never run it before or if you change configuration, added dependencies, changed dependency version or other things that need call conan to rebuilt your dependencies.
5. Conan profiles are required to specify basic environment profile things to build targets, but some settings are changed while build, like **arch** and **build_type**.
6. Check requirements for each target. Example: iOS target require that you have a macOS system.
7. Ezored **core** is downloaded only one time, always that **ezored** folder not exists.

## Distribution folder prebuilt

The folder with name **dist** has all prebuilt things (Android, iOS, Windows, macOS, Linux and others) and this folder is not versioned, but you can download the full version with the following command:

> python make.py dist download

This command will download the following file:

> http://public.ezored.com/ezored/prebuilt/dist.tar.gz

And will unpack for you creating a folder called **"dist"** with all prebuilt files in the project root folder.

You can also pack **"dist"** folder again using:

> python make.py dist pack

## Djinni

Almost all modules use djinni to generate bridge files between C++ and mobile platform code (Android and iOS - Java, JNI, ObjC and ObjC++ files).

If you want create more modules, ezored come with a easy way to do it. Only duplicate any folder inside **"files/djinni"** and change files:

- proj.djinni
- generate.py

The file **"proj.djinni"** contain all interface things to be generated and file **"generate.py"** contain the script that will call djinni passing all required params, only change the params (package name, namespace etc).

After create your new djinni module folder, add it to the list, in your prefered order, inside file **"files/djinni/djinni_modules.py"**. We need it because when you import other djinni yaml file for reference, you need generate imported file before, so the current order generate isolated modules before modules that will require it.

If you will use djinni to generate files follow these steps:

1. Download djinni (https://github.com/dropbox/djinni).
2. Set environment var **DJINNI_HOME** as the root folder of djinni (where you cloned or downloaded it).

If you don't will use djinni in your project, ignore **djinni** section, because some people prefer create the bridge files manually.

## Code tools

Ezored has support for code format, the **"code"** command is available for it.

To format all supported files, run the following command:  
> python make.py code format  

Obs 1: Code format use **clang-format** tool inside to format C++ files. You need have it installed and in your **path** to be located.

Obs 2: Code format use **black** tool inside to format PYTHON files. You need have it installed and in your **path** to be located.

## Other ezored samples

- [**ezored-basic**](https://github.com/ezored/ezored-basic)  
    Basic ezored sample with minimal requirements.
- [**ezored-sdl2**](https://github.com/ezored/ezored-sdl2)  
    SDL2 ezored sample GUI application.
- [**ezored-server**](https://github.com/ezored/ezored-server)  
    Basic web server ezored project with static files and API example.

## Projects

We have some samples inside "projects" folder.

Android sample can be download here:
https://play.google.com/store/apps/details?id=com.ezored.sample

## Troubleshooting

**Enable conan debug:**

```
export CONAN_VERBOSE_TRACEBACK=1
export CONAN_LOGGING_LEVEL=0
```

**Linux error when execute ezored commands:**

If you get a message with *distutils.dir_util* error, try install the separated package for it. Example:  
```sudo apt install python3-pip```

## Buy me a coffee

<a href='https://ko-fi.com/paulocoutinho' target='_blank'><img height='36' style='border:0px;height:36px;' src='https://az743702.vo.msecnd.net/cdn/kofi1.png?v=2' border='0' alt='Buy Me a Coffee at ko-fi.com' /></a>

## Training

Udemy (portuguese): Crie aplicativos Android, iOS e Desktop de alta performance com C++ usando um único código multi-plataforma

https://www.udemy.com/course/desenvolvendo-aplicativos-mobile-com-cpp-para-android-e-ios/

![Udemy Training](extras/images/udemy-training.png)

## Mac Catalyst

Ezored sample project has support for Mac Catalyst. You can use the same iPad application on macOS desktop. See in action here:

https://www.youtube.com/watch?v=ro2WVX_wHuQ

## Supported By Jetbrains IntelliJ IDEA

![Supported By Jetbrains IntelliJ IDEA](extras/images/jetbrains-logo.png "Supported By Jetbrains IntelliJ IDEA")

## License

[MIT](http://opensource.org/licenses/MIT)

Copyright (c) 2019-present, Paulo Coutinho

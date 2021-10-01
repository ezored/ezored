# Requirements

The general requirements that you need is:

1. Python 3 ([https://www.python.org/](https://www.python.org/))
2. PIP ([https://pip.pypa.io/](https://pip.pypa.io/))
3. CMake 3.20.0 ([https://cmake.org/](https://cmake.org/))
4. Conan 1.35.0 ([https://conan.io/](https://conan.io/))
5. Java 8 (JDK) ([https://www.oracle.com/br/java/technologies/javase/javase-jdk8-downloads.html](https://www.oracle.com/br/java/technologies/javase/javase-jdk8-downloads.html))

These are the tools that Ezored need to work. Check on terminal if you have every tool in your path typing their names (python, pip, cmake, conan and java).

And for each platform you need have others small requirements.

**Android Requirements:**

1. Supported operational system for NDK: macOS, Linux or Windows.  
    
```
Conan will download NDK and other things to build based on your system.
```

**iOS Requirements:**

1. Supported operational system: macOS.
2. Xcode.
3. Command line tools (run on terminal: `xcode-select --install`).

**macOS Requirements:**

1. Supported operational system: macOS.
2. Xcode.
3. Command line tools (run on terminal: `xcode-select --install`).
4. Optional system headers (only if you have problems on old macOS versions). Run on terminal: `open /Library/Developer/CommandLineTools/Packages/macOS_SDK_headers_for_macOS_10.14.pkg`

Obs: On step #4 the path can change for each macOS version (10.14 is mojave) and this is required because old softwares search on old places for this headers, like old openssl versions.

**Linux Requirements:**

1. Supported operational system: Linux.
2. C++ compiler installed (example on Ubuntu: `sudo apt install build-essential`).

**Windows Requirements:**

1. Supported operational system: Windows.
2. Visual Studio installed.  

Obs 1: Current example in Ezored is using version 2019 (16), change for your needs in conan profile file.

Obs 2: Everything was compiled using community version [https://visualstudio.microsoft.com/vs/](https://visualstudio.microsoft.com/vs/).  

Obs 3: On installation process select "Desktop development with C++".  

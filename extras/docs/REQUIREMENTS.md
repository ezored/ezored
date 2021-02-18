<p align="center"><a href="https://github.com/ezored/ezored" target="_blank" rel="noopener noreferrer"><img width="180" src="../images/doc-logo.png" alt="ezored logo"></a></p>

<h1 align="center"><strong>Requirements</strong></h1>

**The general requirements is:**

1. Python 3 (https://www.python.org/)  
2. PIP (https://pip.pypa.io/)
3. CMake 3.19.0 (https://cmake.org/)  
4. Conan 1.32.1 (https://conan.io/)

They are the basic things to make ezored work. Check on terminal if you have every tool in your path typing their names (python, pip, cmake, conan).

Each platform requirements list now. Maybe you already have it because are basic tools.

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
4. macOS system headers (only if you have problems on old macOS systems).  
    Run: ```open /Library/Developer/CommandLineTools/Packages/macOS_SDK_headers_for_macOS_10.14.pkg```  
    The path can change for each macOS version (10.14 is mojave) and this is required because old softwares search on old places for this headers, like old openssl versions.

**Linux Requirements:**

1. Linux operational system.
2. C++ compiler installed.

    Example: On Ubuntu run on terminal: ```sudo apt install build-essential```.

**Windows Requirements:**

1. Windows operational system.
2. Visual Studio installed.  

    Obs 1: Current example in ezored is using version 2019 (16), change for your needs in conan profile file.

    Obs 2: Everything was compiled using community version (https://visualstudio.microsoft.com/vs/).  

    Obs 3: On installation process select "Desktop development with C++".  

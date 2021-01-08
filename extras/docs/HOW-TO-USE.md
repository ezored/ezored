# How to use

1. Clone reposity:
> git clone https://github.com/ezored/ezored.git

2. Enter on cloned folder:
> cd ezored

3. Install python requirements:
> pip install -r requirements.txt

4. Install conan extra repositories:
> conan remote add darwin-toolchain https://api.bintray.com/conan/ezored/conan-darwin-toolchain

5. Execute to download **ezored-core** and to show bootstrap menu:
> python make.py

6. Install conan profiles:
> python make.py conan setup

7. Now all commands are available. run the following command to list all targets that you can build:
> python make.py target

Example: If you are on **Linux**, you can build the **linux_app** target, if on **macOS** you can run **macos_app** target and if on **Windows** you can run **windows_app**.

> python make.py target linux_app prepare  
> python make.py target linux_app build  
> python make.py target linux_app package  
> python make.py target linux_app dist  

**Obs:**

1. You can download the project as a ZIP file too: https://github.com/ezored/ezored/archive/master.zip.
2. After run this commands above, a folder called **"dist"** will be created with compiled binaries of applications. The rule is the same for other targets.
3. The execution order is important. You need prepare files and dependencies, build, package and finally distribute.
4. Package verbs will copy files to a non versioned folder called **"dist"** in root path.
5. You don't need run **prepare** verb everytime, only run if you never run it before or if you change configuration, added dependencies, changed dependency version or other things that need call **prepare** to generate target files and rebuilt your dependencies.
6. Conan profiles are required to specify basic environment profile things to build targets, but some settings are changed while build, like **arch** and **build_type**.
7. Check requirements for each target. Example: iOS target require that you have a macOS system.
8. Ezored **core** is downloaded only one time, always that **ezored** folder not exists.

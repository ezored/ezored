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

> python make.py target linux_app conan  
> python make.py target linux_app build  
> python make.py target linux_app package  
> python make.py target linux_app dist  

**Obs:**

1. You can download the project as a ZIP file too: https://github.com/ezored/ezored/archive/master.zip.
2. After run this commands above, a folder called **"dist"** will be created with compiled binaries of applications. The rule is the same for other targets.
3. The execution order is important. Before build your targets, install conan dependencies, build it and finally package. Package verbs will copy files to a non versioned folder called **"dist"** in root path.
4. You don't need run conan verb everytime, only run if you never run it before or if you change configuration, added dependencies, changed dependency version or other things that need call conan to rebuilt your dependencies.
5. Conan profiles are required to specify basic environment profile things to build targets, but some settings are changed while build, like **arch** and **build_type**.
6. Check requirements for each target. Example: iOS target require that you have a macOS system.
7. Ezored **core** is downloaded only one time, always that **ezored** folder not exists.

# Glue code

Almost all modules use Djinni as glue code tool to generate glue code files between C++ and platform code (Android and iOS - Java, JNI, ObjC and ObjC++ files, Java - JNI etc).

To install the glue code tool use the following command:

```
python make.py gluecode setup
python make.py gluecode version
```

Obs: Version command is optional and is used to check current installed version.

When you want generate all glue code files again, use the following command:

```
python make.py gluecode generate
```

If you want create more modules with Djinni support, Ezored come with a easy way to do it. Only duplicate (copy and paste) any module inside **files/modules** and change files:

- proj.djinni
- generate.py

The file **proj.djinni** contain all interface that will be generated and require C++ implementation.

The file **generate.py** contain the method with instructions for that module that will be called automatically when you generate glue code (example: package name, namespace, include paths etc).

After create your new module folder, add it to the list of modules with glue code generation support. Add in your prefered order, inside file **files/config/gluecode.py**. We need it because when you import other Djinni YAML file for reference, you need generate imported file before, so the current order generate isolated modules before modules that will require it.

If you don't use any glue code tool in your project, ignore this section, because some people prefer create the glue code files manually and is not a requirement in Ezored that modules have these files.

## Djinni forks

- Main: https://github.com/cross-language-cpp
- Snapchat: https://github.com/Snapchat/djinni
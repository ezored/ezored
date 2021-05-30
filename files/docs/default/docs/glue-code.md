# Glue code

Almost all modules use Djinni as glue code tool to generate glue code files between C++ and mobile platform code (Android and iOS - Java, JNI, ObjC and ObjC++ files).

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

If you want create more modules, ezored come with a easy way to do it. Only duplicate any module inside **"files/gluecode"** and change files:

- proj.djinni
- generate.py

The file **"proj.djinni"** contain all interface things to be generated.

The file **"generate.py"** contain the method with instructions for the module that will be called automatically when you generate glue code (package name, namespace, include paths etc).

After create your new module folder, add it to the list, in your prefered order, inside file **"files/config/gluecode.py"**. We need it because when you import other Djinni yaml file for reference, you need generate imported file before, so the current order generate isolated modules before modules that will require it.

If you don't will use any glue code tool in your project, ignore this section, because some people prefer create the glue code files manually.

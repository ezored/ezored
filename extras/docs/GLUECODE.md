# Djinni

Almost all modules use Djinni to generate glue code files between C++ and mobile platform code (Android and iOS - Java, JNI, ObjC and ObjC++ files).

If you want create more modules, ezored come with a easy way to do it. Only duplicate any folder inside **"files/gluecode"** and change files:

- proj.djinni
- generate.py

The file **"proj.djinni"** contain all interface things to be generated and file **"generate.py"** contain the script that will call Djinni passing all required params, only change the params (package name, namespace etc).

After create your new Djinni module folder, add it to the list, in your prefered order, inside file **"files/config/gluecode.py"**. We need it because when you import other Djinni yaml file for reference, you need generate imported file before, so the current order generate isolated modules before modules that will require it.

If you will use Djinni to generate files follow these steps:

1. Download Djinni (https://github.com/dropbox/djinni).
2. Set environment var **DJINNI_HOME** as the root folder of Djinni (where you cloned or downloaded it).

If you don't will use Djinni in your project, ignore **Djinni** section, because some people prefer create the glue code files manually.

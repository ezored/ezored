# README

import os
import shutil
import subprocess

# CONFIGURATIONS

# djinni configurations
djinni_file = "proj.djinni"

# cpp configuration
cpp_namespace = "ezored::domain"
cpp_include_prefix = "ezored/domain/"
cpp_out = "generated-src/cpp/{0}".format(cpp_include_prefix)

# objc configuration
objc_prefix = "EZRDomain"
objc_out = "generated-src/objc/{0}".format(cpp_include_prefix)
objc_include_cpp_prefix = "{0}".format(cpp_include_prefix)
objc_include_prefix = "{0}".format(cpp_include_prefix)

# java configuration
java_package = "com.ezored.domain"
java_out = "generated-src/java/{0}".format(java_package.replace(".", "/"))
java_parcelable = "true"

# jni configuration
jni_out = "generated-src/jni/{0}".format(java_package.replace(".", "/"))
jni_class = "EZRDomainFooBar"
jni_file = "EZRDomainFooBar"
jni_include_cpp_prefix = "{0}".format(cpp_include_prefix)
jni_include_prefix = "{0}/".format(java_package.replace(".", "/"))

# RUN

# clean old generated src 
shutil.rmtree("generated-src", ignore_errors=True)
shutil.rmtree("yaml", ignore_errors=True)

# run
djinni_home = os.getenv("DJINNI_HOME")

subprocess.call([
    "{0}/src/run".format(djinni_home),
    "--java-out", java_out,
    "--java-package", java_package,
    "--ident-java-field", "mFooBar",
    "--java-implement-android-os-parcelable", java_parcelable,
    "--cpp-out", cpp_out,
    "--cpp-namespace", cpp_namespace,
    "--cpp-include-prefix", cpp_include_prefix,
    "--ident-cpp-field", "fooBar",
    "--ident-cpp-method", "fooBar",
    "--ident-cpp-file", "FooBar",
    "--ident-cpp-local", "fooBar",
    "--ident-jni-class", jni_class,
    "--ident-jni-file", jni_file,
    "--jni-include-cpp-prefix", jni_include_cpp_prefix,
    "--jni-include-prefix", jni_include_prefix,
    "--jni-out", jni_out,
    "--objc-out", objc_out,
    "--objc-type-prefix", objc_prefix,
    "--objc-include-prefix", objc_include_prefix,
    "--objcpp-include-cpp-prefix", objc_include_cpp_prefix,    
    "--objcpp-include-prefix", objc_include_prefix,
    "--objcpp-out", objc_out,
    "--yaml-out", 'yaml',
    "--idl", djinni_file,
])

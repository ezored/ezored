<p align="center"><a href="https://github.com/ezored/ezored" target="_blank" rel="noopener noreferrer"><img width="180" src="../images/doc-logo.png" alt="ezored logo"></a></p>

<h1 align="center"><strong>Troubleshooting</strong></h1>

**Enable conan debug:**

```
export CONAN_VERBOSE_TRACEBACK=1
export CONAN_LOGGING_LEVEL=0
export CONAN_PRINT_RUN_COMMANDS=1
```

**Linux error when execute ezored commands:**

If you get a message with *distutils.dir_util* error, try install the separated package for it. Example:  
```sudo apt install python3-pip```

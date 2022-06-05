
# Darwin Toolchain

Toolchain required to cross build to any Darwin platform.

## Setup

This package **REQUIRES** Xcode to be installed.

Install with the command:

```
conan create . ezored/stable
```

### Platforms

Create a profile for cross building and including this toolchain, example:

**iOS**

```
include(default)

[settings]
os=iOS
os.version=9.0
arch=armv8

[build_requires]
darwin-toolchain/1.0.0@ezored/stable
```

**watchOS**


```
include(default)

[settings]
os=watchOS
os.version=5.0
arch=armv8_32

[build_requires]
darwin-toolchain/1.0.0@ezored/stable
```

**tvOS**

```
include(default)

[settings]
os=tvOS
os.version=11.0
arch=armv8

[build_requires]
darwin-toolchain/1.0.0@ezored/stable
```

**macOS catalyst**

```
include(default)

[settings]
os=Macos
os.subsystem=catalyst
arch=x86_64

[build_requires]
darwin-toolchain/1.0.0@ezored/stable
```

## Bitcode support

Bitcode is an option available on iOS, it is **required** on tvOS/watchOS.

It is set by default to `True`.

So you can only set it to `False` for iOS. Note that it is not defined for macOS.

## Local development

1. Install python packages:  
```pip install conan_package_tools```
2. Enter on project folder:  
```cd conan/darwin-toolchain```
3. Install:  
```conan create . ezored/stable```
4. Build:  
```python build.py```  

or

```rm -rf test_package/build/ && python build.py```  
5. Check all generated files:  
```find test_package/build -name hello -exec lipo -info {} \;```
6. To install it as local package:  
```conan export-pkg . darwin-toolchain/1.0.0@ezored/stable -f```

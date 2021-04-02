<p align="center"><a href="https://github.com/ezored/ezored" target="_blank" rel="noopener noreferrer"><img width="180" src="../images/doc-logo.png" alt="ezored logo"></a></p>

<h1 align="center"><strong>Apple</strong></h1>


## iOS

1. Add your framework or xcframework as dependency (see example files below)
2. Create **Obj-C Bridging Header** file to include your public headers or the main header file
3. Add to your target **Build Settings** in row **Objective-C Bridging Header** the path of bridging header file, example: "Sample/Sample-Bridging-Header.h"

## WatchOS

1. Add your framework or xcframework as dependency (see example files below)
2. Create **Obj-C Bridging Header** file to include your public headers or the main header file
3. Add to your target **Build Settings** in row **Objective-C Bridging Header** the path of bridging header file, example: "Sample/Sample-Bridging-Header.h"
4. Add to your target **Build Settings** that is a **watch extension** in row **Excluded Architectures**:
    > Debug > Any watchOS Simulator SDK > i386 arm64      
    > Release > Any watchOS Simulator SDK > i386 arm64  

## TvOS

1. Add your framework or xcframework as dependency (see example files below)
2. Create **Obj-C Bridging Header** file to include your public headers or the main header file
3. Add to your target **Build Settings** in row **Objective-C Bridging Header** the path of bridging header file, example: "Sample/Sample-Bridging-Header.h"

## Examples files

**Podfile**

```
# variables
IOS_PLATFORM = '9.0'
EZORED_SDK_LOCAL = false
EZORED_SDK_VERSION = '1.0.0'

# settings
platform :ios, IOS_PLATFORM
use_frameworks!

# dependencies
def shared_pods
  
  if EZORED_SDK_LOCAL
    pod 'ezored', :http => 'http://127.0.0.1:8000/dist.tar.gz'
    else
    pod 'ezored', :http => 'https://ezored.s3.amazonaws.com/dist/ios_framework/' + EZORED_SDK_VERSION + '/dist.tar.gz'
  end

end

target 'Sample' do
  shared_pods
end

target 'WatchDemo Extension' do
  platform :watchos, '5.0'
  shared_pods
end

target 'TvDemo' do
  platform :tvos, '11.0'
  shared_pods
end
```

**Sample-Bridging-Header.h**

```
#ifndef Bridging_Header_h
#define Bridging_Header_h

#include "Ezored.h"

#endif /* Bridging_Header_h */
```

## Utilities

Check OS and execute specific code for that OS:

SWIFT

```
#if os(OSX)
  // compiles for OS X
#elseif os(iOS)
  // compiles for iOS
#elseif os(tvOS)
  // compiles for TV OS
#elseif os(watchOS)
  // compiles for Watch OS
#endif

or

#if os(OSX) && os(iOS)
  // compiles for OS X and iOS
#endif

or

#if os(OSX) || os(iOS)
  // compiles for OS X or iOS
#endif
```

OBJ-C

```
if (@available(macOS 10.9, *)) {
  // compiles for OS X
} else if (@available(iOS 9, *)) {
  // compiles for iOS
} else if (@available(tvOS 11, *)) {
  // compiles for TV OS
} else if (@available(watchOS 5, *)) {
  // compiles for Watch OS
}

or

if (@available(macOS 10.9, iOS 9, tvOS 11, watchOS 5, *)) {
  // compiles for OS X and iOS and TV OS and Watch OS with specified versions
}
```
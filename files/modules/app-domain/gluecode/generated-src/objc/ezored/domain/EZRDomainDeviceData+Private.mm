// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from proj.djinni

#import "djinni/objc/DJIMarshal+Private.h"
#import "ezored/domain/EZRDomainDeviceData+Private.h"
#include <cassert>

namespace djinni_generated
{

auto DeviceData::toCpp(ObjcType obj) -> CppType
{
    assert(obj);
    return {::djinni::String::toCpp(obj.uniqueIdentifier),
            ::djinni::String::toCpp(obj.name),
            ::djinni::String::toCpp(obj.systemName),
            ::djinni::String::toCpp(obj.systemVersion),
            ::djinni::String::toCpp(obj.model),
            ::djinni::String::toCpp(obj.localizedModel),
            ::djinni::String::toCpp(obj.appVersion),
            ::djinni::String::toCpp(obj.appShortVersion),
            ::djinni::String::toCpp(obj.appName),
            ::djinni::F32::toCpp(obj.screenWidth),
            ::djinni::F32::toCpp(obj.screenHeight),
            ::djinni::F32::toCpp(obj.screenScale),
            ::djinni::String::toCpp(obj.systemOsName),
            ::djinni::String::toCpp(obj.language),
            ::djinni::String::toCpp(obj.imei),
            ::djinni::String::toCpp(obj.region)};
}

auto DeviceData::fromCpp(const CppType &cpp) -> ObjcType
{
    return [[::EZRDomainDeviceData alloc] initWithUniqueIdentifier:(::djinni::String::fromCpp(cpp.uniqueIdentifier))
                                                              name:(::djinni::String::fromCpp(cpp.name))
                                                              systemName:(::djinni::String::fromCpp(cpp.systemName))
                                                              systemVersion:(::djinni::String::fromCpp(cpp.systemVersion))
                                                              model:(::djinni::String::fromCpp(cpp.model))
                                                              localizedModel:(::djinni::String::fromCpp(cpp.localizedModel))
                                                              appVersion:(::djinni::String::fromCpp(cpp.appVersion))
                                                              appShortVersion:(::djinni::String::fromCpp(cpp.appShortVersion))
                                                              appName:(::djinni::String::fromCpp(cpp.appName))
                                                              screenWidth:(::djinni::F32::fromCpp(cpp.screenWidth))
                                                              screenHeight:(::djinni::F32::fromCpp(cpp.screenHeight))
                                                              screenScale:(::djinni::F32::fromCpp(cpp.screenScale))
                                                              systemOsName:(::djinni::String::fromCpp(cpp.systemOsName))
                                                              language:(::djinni::String::fromCpp(cpp.language))
                                                              imei:(::djinni::String::fromCpp(cpp.imei))
                                                              region:(::djinni::String::fromCpp(cpp.region))];
}

} // namespace djinni_generated

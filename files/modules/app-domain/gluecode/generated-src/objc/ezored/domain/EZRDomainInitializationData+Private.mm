// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from proj.djinni

#import "djinni/objc/DJIMarshal+Private.h"
#import "ezored/domain/EZRDomainInitializationData+Private.h"
#include <cassert>

namespace djinni_generated
{

auto InitializationData::toCpp(ObjcType obj) -> CppType
{
    assert(obj);
    return {::djinni::String::toCpp(obj.appId),
            ::djinni::String::toCpp(obj.name),
            ::djinni::String::toCpp(obj.basePath),
            ::djinni::I32::toCpp(obj.databaseMigrationMaxVersion),
            ::djinni::Bool::toCpp(obj.debug)};
}

auto InitializationData::fromCpp(const CppType &cpp) -> ObjcType
{
    return [[::EZRDomainInitializationData alloc] initWithAppId:(::djinni::String::fromCpp(cpp.appId))
                                                           name:(::djinni::String::fromCpp(cpp.name))
                                                           basePath:(::djinni::String::fromCpp(cpp.basePath))
                                                           databaseMigrationMaxVersion:(::djinni::I32::fromCpp(cpp.databaseMigrationMaxVersion))
                                                           debug:(::djinni::Bool::fromCpp(cpp.debug))];
}

} // namespace djinni_generated

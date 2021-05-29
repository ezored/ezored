// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from proj.djinni

#import "ezored/net/http/EZRHttpHeader+Private.h"
#import "djinni/objc/DJIMarshal+Private.h"
#include <cassert>

namespace djinni_generated {

auto HttpHeader::toCpp(ObjcType obj) -> CppType
{
    assert(obj);
    return {::djinni::String::toCpp(obj.name),
            ::djinni::String::toCpp(obj.value)};
}

auto HttpHeader::fromCpp(const CppType& cpp) -> ObjcType
{
    return [[EZRHttpHeader alloc] initWithName:(::djinni::String::fromCpp(cpp.name))
                                         value:(::djinni::String::fromCpp(cpp.value))];
}

}  // namespace djinni_generated

// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from proj.djinni

#import "ezored/net/http/EZRHttpResponse+Private.h"
#import "djinni/objc/DJIMarshal+Private.h"
#import "ezored/net/http/EZRHttpHeader+Private.h"
#include <cassert>

namespace djinni_generated {

auto HttpResponse::toCpp(ObjcType obj) -> CppType
{
    assert(obj);
    return {::djinni::I32::toCpp(obj.code),
            ::djinni::String::toCpp(obj.body),
            ::djinni::String::toCpp(obj.url),
            ::djinni::List<::djinni_generated::HttpHeader>::toCpp(obj.headers)};
}

auto HttpResponse::fromCpp(const CppType& cpp) -> ObjcType
{
    return [[EZRHttpResponse alloc] initWithCode:(::djinni::I32::fromCpp(cpp.code))
                                            body:(::djinni::String::fromCpp(cpp.body))
                                             url:(::djinni::String::fromCpp(cpp.url))
                                         headers:(::djinni::List<::djinni_generated::HttpHeader>::fromCpp(cpp.headers))];
}

}  // namespace djinni_generated

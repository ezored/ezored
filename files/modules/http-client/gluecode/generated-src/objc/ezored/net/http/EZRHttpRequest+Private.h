// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from proj.djinni

#import "ezored/net/http/EZRHttpRequest.h"
#include "ezored/net/http/HttpRequest.hpp"

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@class EZRHttpRequest;

namespace djinni_generated
{

struct HttpRequest
{
    using CppType = ::ezored::net::http::HttpRequest;
    using ObjcType = ::EZRHttpRequest *;

    using Boxed = HttpRequest;

    static CppType toCpp(ObjcType objc);
    static ObjcType fromCpp(const CppType &cpp);
};

} // namespace djinni_generated

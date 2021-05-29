// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from proj.djinni

#include "ezored/data/SharedDataPlatformService.hpp"
#include <memory>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@protocol EZRSharedDataPlatformService;

namespace djinni_generated {

class SharedDataPlatformService
{
public:
    using CppType = std::shared_ptr<::ezored::data::SharedDataPlatformService>;
    using CppOptType = std::shared_ptr<::ezored::data::SharedDataPlatformService>;
    using ObjcType = id<EZRSharedDataPlatformService>;

    using Boxed = SharedDataPlatformService;

    static CppType toCpp(ObjcType objc);
    static ObjcType fromCppOpt(const CppOptType& cpp);
    static ObjcType fromCpp(const CppType& cpp) { return fromCppOpt(cpp); }

private:
    class ObjcProxy;
};

}  // namespace djinni_generated


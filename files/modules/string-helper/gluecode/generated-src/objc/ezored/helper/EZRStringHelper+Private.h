// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from proj.djinni

#include "ezored/helper/StringHelper.hpp"
#include <memory>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@class EZRStringHelper;

namespace djinni_generated
{

class StringHelper
{
public:
    using CppType = std::shared_ptr<::ezored::helper::StringHelper>;
    using CppOptType = std::shared_ptr<::ezored::helper::StringHelper>;
    using ObjcType = EZRStringHelper *;

    using Boxed = StringHelper;

    static CppType toCpp(ObjcType objc);
    static ObjcType fromCppOpt(const CppOptType &cpp);
    static ObjcType fromCpp(const CppType &cpp) { return fromCppOpt(cpp); }

private:
    class ObjcProxy;
};

} // namespace djinni_generated
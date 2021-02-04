// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from proj.djinni

#import "ezored/data/EZRSharedDataPlatformService+Private.h"
#import "ezored/data/EZRSharedDataPlatformService.h"
#import "djinni/objc/DJIMarshal+Private.h"
#import "djinni/objc/DJIObjcWrapperCache+Private.h"
#include <stdexcept>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

namespace djinni_generated {

class SharedDataPlatformService::ObjcProxy final
: public ::ezored::data::SharedDataPlatformService
, private ::djinni::ObjcProxyBase<ObjcType>
{
    friend class ::djinni_generated::SharedDataPlatformService;
public:
    using ObjcProxyBase::ObjcProxyBase;
    void setString(const std::string & c_groupName, const std::string & c_key, const std::string & c_value) override
    {
        @autoreleasepool {
            [djinni_private_get_proxied_objc_object() setString:(::djinni::String::fromCpp(c_groupName))
                                                            key:(::djinni::String::fromCpp(c_key))
                                                          value:(::djinni::String::fromCpp(c_value))];
        }
    }
    void setInteger(const std::string & c_groupName, const std::string & c_key, int32_t c_value) override
    {
        @autoreleasepool {
            [djinni_private_get_proxied_objc_object() setInteger:(::djinni::String::fromCpp(c_groupName))
                                                             key:(::djinni::String::fromCpp(c_key))
                                                           value:(::djinni::I32::fromCpp(c_value))];
        }
    }
    void setLong(const std::string & c_groupName, const std::string & c_key, int64_t c_value) override
    {
        @autoreleasepool {
            [djinni_private_get_proxied_objc_object() setLong:(::djinni::String::fromCpp(c_groupName))
                                                          key:(::djinni::String::fromCpp(c_key))
                                                        value:(::djinni::I64::fromCpp(c_value))];
        }
    }
    void setBool(const std::string & c_groupName, const std::string & c_key, bool c_value) override
    {
        @autoreleasepool {
            [djinni_private_get_proxied_objc_object() setBool:(::djinni::String::fromCpp(c_groupName))
                                                          key:(::djinni::String::fromCpp(c_key))
                                                        value:(::djinni::Bool::fromCpp(c_value))];
        }
    }
    void setFloat(const std::string & c_groupName, const std::string & c_key, float c_value) override
    {
        @autoreleasepool {
            [djinni_private_get_proxied_objc_object() setFloat:(::djinni::String::fromCpp(c_groupName))
                                                           key:(::djinni::String::fromCpp(c_key))
                                                         value:(::djinni::F32::fromCpp(c_value))];
        }
    }
    void setDouble(const std::string & c_groupName, const std::string & c_key, double c_value) override
    {
        @autoreleasepool {
            [djinni_private_get_proxied_objc_object() setDouble:(::djinni::String::fromCpp(c_groupName))
                                                            key:(::djinni::String::fromCpp(c_key))
                                                          value:(::djinni::F64::fromCpp(c_value))];
        }
    }
    std::string getString(const std::string & c_groupName, const std::string & c_key) override
    {
        @autoreleasepool {
            auto objcpp_result_ = [djinni_private_get_proxied_objc_object() getString:(::djinni::String::fromCpp(c_groupName))
                                                                                  key:(::djinni::String::fromCpp(c_key))];
            return ::djinni::String::toCpp(objcpp_result_);
        }
    }
    int32_t getInteger(const std::string & c_groupName, const std::string & c_key) override
    {
        @autoreleasepool {
            auto objcpp_result_ = [djinni_private_get_proxied_objc_object() getInteger:(::djinni::String::fromCpp(c_groupName))
                                                                                   key:(::djinni::String::fromCpp(c_key))];
            return ::djinni::I32::toCpp(objcpp_result_);
        }
    }
    int64_t getLong(const std::string & c_groupName, const std::string & c_key) override
    {
        @autoreleasepool {
            auto objcpp_result_ = [djinni_private_get_proxied_objc_object() getLong:(::djinni::String::fromCpp(c_groupName))
                                                                                key:(::djinni::String::fromCpp(c_key))];
            return ::djinni::I64::toCpp(objcpp_result_);
        }
    }
    bool getBool(const std::string & c_groupName, const std::string & c_key) override
    {
        @autoreleasepool {
            auto objcpp_result_ = [djinni_private_get_proxied_objc_object() getBool:(::djinni::String::fromCpp(c_groupName))
                                                                                key:(::djinni::String::fromCpp(c_key))];
            return ::djinni::Bool::toCpp(objcpp_result_);
        }
    }
    float getFloat(const std::string & c_groupName, const std::string & c_key) override
    {
        @autoreleasepool {
            auto objcpp_result_ = [djinni_private_get_proxied_objc_object() getFloat:(::djinni::String::fromCpp(c_groupName))
                                                                                 key:(::djinni::String::fromCpp(c_key))];
            return ::djinni::F32::toCpp(objcpp_result_);
        }
    }
    double getDouble(const std::string & c_groupName, const std::string & c_key) override
    {
        @autoreleasepool {
            auto objcpp_result_ = [djinni_private_get_proxied_objc_object() getDouble:(::djinni::String::fromCpp(c_groupName))
                                                                                  key:(::djinni::String::fromCpp(c_key))];
            return ::djinni::F64::toCpp(objcpp_result_);
        }
    }
    std::string getStringWithDefaultValue(const std::string & c_groupName, const std::string & c_key, const std::string & c_defaultValue) override
    {
        @autoreleasepool {
            auto objcpp_result_ = [djinni_private_get_proxied_objc_object() getStringWithDefaultValue:(::djinni::String::fromCpp(c_groupName))
                                                                                                  key:(::djinni::String::fromCpp(c_key))
                                                                                         defaultValue:(::djinni::String::fromCpp(c_defaultValue))];
            return ::djinni::String::toCpp(objcpp_result_);
        }
    }
    int32_t getIntegerWithDefaultValue(const std::string & c_groupName, const std::string & c_key, int32_t c_defaultValue) override
    {
        @autoreleasepool {
            auto objcpp_result_ = [djinni_private_get_proxied_objc_object() getIntegerWithDefaultValue:(::djinni::String::fromCpp(c_groupName))
                                                                                                   key:(::djinni::String::fromCpp(c_key))
                                                                                          defaultValue:(::djinni::I32::fromCpp(c_defaultValue))];
            return ::djinni::I32::toCpp(objcpp_result_);
        }
    }
    int64_t getLongWithDefaultValue(const std::string & c_groupName, const std::string & c_key, int64_t c_defaultValue) override
    {
        @autoreleasepool {
            auto objcpp_result_ = [djinni_private_get_proxied_objc_object() getLongWithDefaultValue:(::djinni::String::fromCpp(c_groupName))
                                                                                                key:(::djinni::String::fromCpp(c_key))
                                                                                       defaultValue:(::djinni::I64::fromCpp(c_defaultValue))];
            return ::djinni::I64::toCpp(objcpp_result_);
        }
    }
    bool getBoolWithDefaultValue(const std::string & c_groupName, const std::string & c_key, bool c_defaultValue) override
    {
        @autoreleasepool {
            auto objcpp_result_ = [djinni_private_get_proxied_objc_object() getBoolWithDefaultValue:(::djinni::String::fromCpp(c_groupName))
                                                                                                key:(::djinni::String::fromCpp(c_key))
                                                                                       defaultValue:(::djinni::Bool::fromCpp(c_defaultValue))];
            return ::djinni::Bool::toCpp(objcpp_result_);
        }
    }
    float getFloatWithDefaultValue(const std::string & c_groupName, const std::string & c_key, float c_defaultValue) override
    {
        @autoreleasepool {
            auto objcpp_result_ = [djinni_private_get_proxied_objc_object() getFloatWithDefaultValue:(::djinni::String::fromCpp(c_groupName))
                                                                                                 key:(::djinni::String::fromCpp(c_key))
                                                                                        defaultValue:(::djinni::F32::fromCpp(c_defaultValue))];
            return ::djinni::F32::toCpp(objcpp_result_);
        }
    }
    double getDoubleWithDefaultValue(const std::string & c_groupName, const std::string & c_key, double c_defaultValue) override
    {
        @autoreleasepool {
            auto objcpp_result_ = [djinni_private_get_proxied_objc_object() getDoubleWithDefaultValue:(::djinni::String::fromCpp(c_groupName))
                                                                                                  key:(::djinni::String::fromCpp(c_key))
                                                                                         defaultValue:(::djinni::F64::fromCpp(c_defaultValue))];
            return ::djinni::F64::toCpp(objcpp_result_);
        }
    }
    bool has(const std::string & c_groupName, const std::string & c_key) override
    {
        @autoreleasepool {
            auto objcpp_result_ = [djinni_private_get_proxied_objc_object() has:(::djinni::String::fromCpp(c_groupName))
                                                                            key:(::djinni::String::fromCpp(c_key))];
            return ::djinni::Bool::toCpp(objcpp_result_);
        }
    }
    void remove(const std::string & c_groupName, const std::string & c_key) override
    {
        @autoreleasepool {
            [djinni_private_get_proxied_objc_object() remove:(::djinni::String::fromCpp(c_groupName))
                                                         key:(::djinni::String::fromCpp(c_key))];
        }
    }
    void clear(const std::string & c_groupName) override
    {
        @autoreleasepool {
            [djinni_private_get_proxied_objc_object() clear:(::djinni::String::fromCpp(c_groupName))];
        }
    }
};

}  // namespace djinni_generated

namespace djinni_generated {

auto SharedDataPlatformService::toCpp(ObjcType objc) -> CppType
{
    if (!objc) {
        return nullptr;
    }
    return ::djinni::get_objc_proxy<ObjcProxy>(objc);
}

auto SharedDataPlatformService::fromCppOpt(const CppOptType& cpp) -> ObjcType
{
    if (!cpp) {
        return nil;
    }
    return dynamic_cast<ObjcProxy&>(*cpp).djinni_private_get_proxied_objc_object();
}

}  // namespace djinni_generated

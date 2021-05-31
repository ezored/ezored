// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from proj.djinni

#pragma once

#include "djinni/jni/djinni_support.hpp"
#include "ezored/helper/SharedDataHelper.hpp"

namespace djinni_generated
{

class EZRHelperSharedDataHelper final : ::djinni::JniInterface<::ezored::helper::SharedDataHelper, EZRHelperSharedDataHelper>
{
public:
    using CppType = std::shared_ptr<::ezored::helper::SharedDataHelper>;
    using CppOptType = std::shared_ptr<::ezored::helper::SharedDataHelper>;
    using JniType = jobject;

    using Boxed = EZRHelperSharedDataHelper;

    ~EZRHelperSharedDataHelper();

    static CppType toCpp(JNIEnv *jniEnv, JniType j) { return ::djinni::JniClass<EZRHelperSharedDataHelper>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv *jniEnv, const CppOptType &c) { return {jniEnv, ::djinni::JniClass<EZRHelperSharedDataHelper>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv *jniEnv, const CppType &c) { return fromCppOpt(jniEnv, c); }

private:
    EZRHelperSharedDataHelper();
    friend ::djinni::JniClass<EZRHelperSharedDataHelper>;
    friend ::djinni::JniInterface<::ezored::helper::SharedDataHelper, EZRHelperSharedDataHelper>;
};

} // namespace djinni_generated

// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from proj.djinni

#pragma once

#include "djinni/jni/djinni_support.hpp"
#include "ezored/domain/ResponseError.hpp"

namespace djinni_generated
{

class EZRDomainResponseError final
{
public:
    using CppType = ::ezored::domain::ResponseError;
    using JniType = jobject;

    using Boxed = EZRDomainResponseError;

    ~EZRDomainResponseError();

    static CppType toCpp(JNIEnv *jniEnv, JniType j);
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv *jniEnv, const CppType &c);

private:
    EZRDomainResponseError();
    friend ::djinni::JniClass<EZRDomainResponseError>;

    const ::djinni::GlobalRef<jclass> clazz{::djinni::jniFindClass("com/ezored/domain/ResponseError")};
    const jmethodID jconstructor{::djinni::jniGetMethodID(clazz.get(), "<init>", "(Ljava/lang/String;Ljava/lang/String;)V")};
    const jfieldID field_mField{::djinni::jniGetFieldID(clazz.get(), "mField", "Ljava/lang/String;")};
    const jfieldID field_mMessage{::djinni::jniGetFieldID(clazz.get(), "mMessage", "Ljava/lang/String;")};
};

} // namespace djinni_generated

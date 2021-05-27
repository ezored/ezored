// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from proj.djinni

#pragma once

#include "djinni/jni/djinni_support.hpp"
#include "ezored/domain/Todo.hpp"

namespace djinni_generated
{

class EZRDomainTodo final
{
public:
    using CppType = ::ezored::domain::Todo;
    using JniType = jobject;

    using Boxed = EZRDomainTodo;

    ~EZRDomainTodo();

    static CppType toCpp(JNIEnv *jniEnv, JniType j);
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv *jniEnv, const CppType &c);

private:
    EZRDomainTodo();
    friend ::djinni::JniClass<EZRDomainTodo>;

    const ::djinni::GlobalRef<jclass> clazz{::djinni::jniFindClass("com/ezored/domain/Todo")};
    const jmethodID jconstructor{::djinni::jniGetMethodID(clazz.get(), "<init>", "(JLjava/lang/String;Ljava/lang/String;Ljava/util/HashMap;ZLjava/util/Date;Ljava/util/Date;)V")};
    const jfieldID field_mId{::djinni::jniGetFieldID(clazz.get(), "mId", "J")};
    const jfieldID field_mTitle{::djinni::jniGetFieldID(clazz.get(), "mTitle", "Ljava/lang/String;")};
    const jfieldID field_mBody{::djinni::jniGetFieldID(clazz.get(), "mBody", "Ljava/lang/String;")};
    const jfieldID field_mData{::djinni::jniGetFieldID(clazz.get(), "mData", "Ljava/util/HashMap;")};
    const jfieldID field_mDone{::djinni::jniGetFieldID(clazz.get(), "mDone", "Z")};
    const jfieldID field_mCreatedAt{::djinni::jniGetFieldID(clazz.get(), "mCreatedAt", "Ljava/util/Date;")};
    const jfieldID field_mUpdatedAt{::djinni::jniGetFieldID(clazz.get(), "mUpdatedAt", "Ljava/util/Date;")};
};

} // namespace djinni_generated

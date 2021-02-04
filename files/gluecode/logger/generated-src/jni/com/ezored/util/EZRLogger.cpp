// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from proj.djinni

#include "com/ezored/util/EZRLogger.hpp"  // my header
#include "com/ezored/util/EZRLoggerLevel.hpp"
#include "com/ezored/util/EZRLoggerPlatformService.hpp"
#include "djinni/jni/Marshal.hpp"

namespace djinni_generated {

EZRLogger::EZRLogger() : ::djinni::JniInterface<::ezored::util::Logger, EZRLogger>("com/ezored/util/Logger$CppProxy") {}

EZRLogger::~EZRLogger() = default;


CJNIEXPORT void JNICALL Java_com_ezored_util_Logger_00024CppProxy_nativeDestroy(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        delete reinterpret_cast<::djinni::CppProxyHandle<::ezored::util::Logger>*>(nativeRef);
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jobject JNICALL Java_com_ezored_util_Logger_00024CppProxy_shared(JNIEnv* jniEnv, jobject /*this*/)
{
    try {
        DJINNI_FUNCTION_PROLOGUE0(jniEnv);
        auto r = ::ezored::util::Logger::shared();
        return ::djinni::release(::djinni_generated::EZRLogger::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT void JNICALL Java_com_ezored_util_Logger_00024CppProxy_native_1setPlatformService(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_ps)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ezored::util::Logger>(nativeRef);
        ref->setPlatformService(::djinni_generated::EZRLoggerPlatformService::toCpp(jniEnv, j_ps));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jobject JNICALL Java_com_ezored_util_Logger_00024CppProxy_native_1getPlatformService(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ezored::util::Logger>(nativeRef);
        auto r = ref->getPlatformService();
        return ::djinni::release(::djinni_generated::EZRLoggerPlatformService::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jboolean JNICALL Java_com_ezored_util_Logger_00024CppProxy_native_1hasPlatformService(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ezored::util::Logger>(nativeRef);
        auto r = ref->hasPlatformService();
        return ::djinni::release(::djinni::Bool::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT jboolean JNICALL Java_com_ezored_util_Logger_00024CppProxy_native_1allowedLevel(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_level)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ezored::util::Logger>(nativeRef);
        auto r = ref->allowedLevel(::djinni_generated::EZRLoggerLevel::toCpp(jniEnv, j_level));
        return ::djinni::release(::djinni::Bool::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT void JNICALL Java_com_ezored_util_Logger_00024CppProxy_native_1setLevel(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_level)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ezored::util::Logger>(nativeRef);
        ref->setLevel(::djinni_generated::EZRLoggerLevel::toCpp(jniEnv, j_level));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_ezored_util_Logger_00024CppProxy_v(JNIEnv* jniEnv, jobject /*this*/, jstring j_message)
{
    try {
        DJINNI_FUNCTION_PROLOGUE0(jniEnv);
        ::ezored::util::Logger::v(::djinni::String::toCpp(jniEnv, j_message));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_ezored_util_Logger_00024CppProxy_d(JNIEnv* jniEnv, jobject /*this*/, jstring j_message)
{
    try {
        DJINNI_FUNCTION_PROLOGUE0(jniEnv);
        ::ezored::util::Logger::d(::djinni::String::toCpp(jniEnv, j_message));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_ezored_util_Logger_00024CppProxy_i(JNIEnv* jniEnv, jobject /*this*/, jstring j_message)
{
    try {
        DJINNI_FUNCTION_PROLOGUE0(jniEnv);
        ::ezored::util::Logger::i(::djinni::String::toCpp(jniEnv, j_message));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_ezored_util_Logger_00024CppProxy_w(JNIEnv* jniEnv, jobject /*this*/, jstring j_message)
{
    try {
        DJINNI_FUNCTION_PROLOGUE0(jniEnv);
        ::ezored::util::Logger::w(::djinni::String::toCpp(jniEnv, j_message));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_ezored_util_Logger_00024CppProxy_e(JNIEnv* jniEnv, jobject /*this*/, jstring j_message)
{
    try {
        DJINNI_FUNCTION_PROLOGUE0(jniEnv);
        ::ezored::util::Logger::e(::djinni::String::toCpp(jniEnv, j_message));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_ezored_util_Logger_00024CppProxy_setGroup(JNIEnv* jniEnv, jobject /*this*/, jstring j_group)
{
    try {
        DJINNI_FUNCTION_PROLOGUE0(jniEnv);
        ::ezored::util::Logger::setGroup(::djinni::String::toCpp(jniEnv, j_group));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

}  // namespace djinni_generated

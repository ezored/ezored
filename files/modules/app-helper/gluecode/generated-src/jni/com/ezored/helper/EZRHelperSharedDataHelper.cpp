// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from proj.djinni

#include "com/ezored/helper/EZRHelperSharedDataHelper.hpp" // my header
#include "com/ezored/domain/EZRDomainCustomer.hpp"
#include "djinni/jni/Marshal.hpp"

namespace djinni_generated
{

EZRHelperSharedDataHelper::EZRHelperSharedDataHelper() : ::djinni::JniInterface<::ezored::helper::SharedDataHelper, EZRHelperSharedDataHelper>("com/ezored/helper/SharedDataHelper$CppProxy") {}

EZRHelperSharedDataHelper::~EZRHelperSharedDataHelper() = default;

CJNIEXPORT void JNICALL Java_com_ezored_helper_SharedDataHelper_00024CppProxy_nativeDestroy(JNIEnv *jniEnv, jobject /*this*/, jlong nativeRef)
{
    try
    {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        delete reinterpret_cast<::djinni::CppProxyHandle<::ezored::helper::SharedDataHelper> *>(nativeRef);
    }
    JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_ezored_helper_SharedDataHelper_00024CppProxy_setCustomer(JNIEnv *jniEnv, jobject /*this*/, ::djinni_generated::EZRDomainCustomer::JniType j_value)
{
    try
    {
        DJINNI_FUNCTION_PROLOGUE0(jniEnv);
        ::ezored::helper::SharedDataHelper::setCustomer(::djinni_generated::EZRDomainCustomer::toCpp(jniEnv, j_value));
    }
    JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT ::djinni_generated::EZRDomainCustomer::JniType JNICALL Java_com_ezored_helper_SharedDataHelper_00024CppProxy_getCustomer(JNIEnv *jniEnv, jobject /*this*/)
{
    try
    {
        DJINNI_FUNCTION_PROLOGUE0(jniEnv);
        auto r = ::ezored::helper::SharedDataHelper::getCustomer();
        return ::djinni::release(::djinni_generated::EZRDomainCustomer::fromCpp(jniEnv, r));
    }
    JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT void JNICALL Java_com_ezored_helper_SharedDataHelper_00024CppProxy_storeCustomer(JNIEnv *jniEnv, jobject /*this*/)
{
    try
    {
        DJINNI_FUNCTION_PROLOGUE0(jniEnv);
        ::ezored::helper::SharedDataHelper::storeCustomer();
    }
    JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_ezored_helper_SharedDataHelper_00024CppProxy_setDemoFlag(JNIEnv *jniEnv, jobject /*this*/, jboolean j_value)
{
    try
    {
        DJINNI_FUNCTION_PROLOGUE0(jniEnv);
        ::ezored::helper::SharedDataHelper::setDemoFlag(::djinni::Bool::toCpp(jniEnv, j_value));
    }
    JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jboolean JNICALL Java_com_ezored_helper_SharedDataHelper_00024CppProxy_getDemoFlag(JNIEnv *jniEnv, jobject /*this*/)
{
    try
    {
        DJINNI_FUNCTION_PROLOGUE0(jniEnv);
        auto r = ::ezored::helper::SharedDataHelper::getDemoFlag();
        return ::djinni::release(::djinni::Bool::fromCpp(jniEnv, r));
    }
    JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

} // namespace djinni_generated

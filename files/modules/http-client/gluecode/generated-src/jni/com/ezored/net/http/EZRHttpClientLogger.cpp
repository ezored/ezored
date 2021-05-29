// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from proj.djinni

#include "com/ezored/net/http/EZRHttpClientLogger.hpp"  // my header
#include "com/ezored/net/http/EZRHttpRequest.hpp"
#include "com/ezored/net/http/EZRHttpResponse.hpp"

namespace djinni_generated {

EZRHttpClientLogger::EZRHttpClientLogger() : ::djinni::JniInterface<::ezored::net::http::HttpClientLogger, EZRHttpClientLogger>("com/ezored/net/http/HttpClientLogger$CppProxy") {}

EZRHttpClientLogger::~EZRHttpClientLogger() = default;


CJNIEXPORT void JNICALL Java_com_ezored_net_http_HttpClientLogger_00024CppProxy_nativeDestroy(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        delete reinterpret_cast<::djinni::CppProxyHandle<::ezored::net::http::HttpClientLogger>*>(nativeRef);
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_ezored_net_http_HttpClientLogger_00024CppProxy_native_1onRequest(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_request)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ezored::net::http::HttpClientLogger>(nativeRef);
        ref->onRequest(::djinni_generated::EZRHttpRequest::toCpp(jniEnv, j_request));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_ezored_net_http_HttpClientLogger_00024CppProxy_native_1onResponse(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_request, jobject j_response)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::ezored::net::http::HttpClientLogger>(nativeRef);
        ref->onResponse(::djinni_generated::EZRHttpRequest::toCpp(jniEnv, j_request),
                        ::djinni_generated::EZRHttpResponse::toCpp(jniEnv, j_response));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

}  // namespace djinni_generated

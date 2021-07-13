// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from proj.djinni

#include "com/ezored/net/http/EZRHttpServer.hpp" // my header
#include "com/ezored/net/http/EZRHttpServerConfig.hpp"

namespace djinni_generated
{

EZRHttpServer::EZRHttpServer() : ::djinni::JniInterface<::ezored::net::http::HttpServer, EZRHttpServer>("com/ezored/net/http/HttpServer$CppProxy") {}

EZRHttpServer::~EZRHttpServer() = default;

CJNIEXPORT void JNICALL Java_com_ezored_net_http_HttpServer_00024CppProxy_nativeDestroy(JNIEnv *jniEnv, jobject /*this*/, jlong nativeRef)
{
    try
    {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        delete reinterpret_cast<::djinni::CppProxyHandle<::ezored::net::http::HttpServer> *>(nativeRef);
    }
    JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jobject JNICALL Java_com_ezored_net_http_HttpServer_00024CppProxy_shared(JNIEnv *jniEnv, jobject /*this*/)
{
    try
    {
        DJINNI_FUNCTION_PROLOGUE0(jniEnv);
        auto r = ::ezored::net::http::HttpServer::shared();
        return ::djinni::release(::djinni_generated::EZRHttpServer::fromCpp(jniEnv, r));
    }
    JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT void JNICALL Java_com_ezored_net_http_HttpServer_00024CppProxy_native_1initialize(JNIEnv *jniEnv, jobject /*this*/, jlong nativeRef, jobject j_config)
{
    try
    {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto &ref = ::djinni::objectFromHandleAddress<::ezored::net::http::HttpServer>(nativeRef);
        ref->initialize(::djinni_generated::EZRHttpServerConfig::toCpp(jniEnv, j_config));
    }
    JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jobject JNICALL Java_com_ezored_net_http_HttpServer_00024CppProxy_native_1getConfig(JNIEnv *jniEnv, jobject /*this*/, jlong nativeRef)
{
    try
    {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto &ref = ::djinni::objectFromHandleAddress<::ezored::net::http::HttpServer>(nativeRef);
        auto r = ref->getConfig();
        return ::djinni::release(::djinni_generated::EZRHttpServerConfig::fromCpp(jniEnv, r));
    }
    JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT void JNICALL Java_com_ezored_net_http_HttpServer_00024CppProxy_native_1start(JNIEnv *jniEnv, jobject /*this*/, jlong nativeRef)
{
    try
    {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto &ref = ::djinni::objectFromHandleAddress<::ezored::net::http::HttpServer>(nativeRef);
        ref->start();
    }
    JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_ezored_net_http_HttpServer_00024CppProxy_native_1stop(JNIEnv *jniEnv, jobject /*this*/, jlong nativeRef)
{
    try
    {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto &ref = ::djinni::objectFromHandleAddress<::ezored::net::http::HttpServer>(nativeRef);
        ref->stop();
    }
    JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_ezored_net_http_HttpServer_00024CppProxy_native_1waitForTermination(JNIEnv *jniEnv, jobject /*this*/, jlong nativeRef)
{
    try
    {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto &ref = ::djinni::objectFromHandleAddress<::ezored::net::http::HttpServer>(nativeRef);
        ref->waitForTermination();
    }
    JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

} // namespace djinni_generated

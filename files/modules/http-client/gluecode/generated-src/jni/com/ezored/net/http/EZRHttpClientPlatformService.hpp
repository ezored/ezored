// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from proj.djinni

#pragma once

#include "djinni/jni/djinni_support.hpp"
#include "ezored/net/http/HttpClientPlatformService.hpp"

namespace djinni_generated {

class EZRHttpClientPlatformService final : ::djinni::JniInterface<::ezored::net::http::HttpClientPlatformService, EZRHttpClientPlatformService> {
public:
    using CppType = std::shared_ptr<::ezored::net::http::HttpClientPlatformService>;
    using CppOptType = std::shared_ptr<::ezored::net::http::HttpClientPlatformService>;
    using JniType = jobject;

    using Boxed = EZRHttpClientPlatformService;

    ~EZRHttpClientPlatformService();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<EZRHttpClientPlatformService>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<EZRHttpClientPlatformService>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    EZRHttpClientPlatformService();
    friend ::djinni::JniClass<EZRHttpClientPlatformService>;
    friend ::djinni::JniInterface<::ezored::net::http::HttpClientPlatformService, EZRHttpClientPlatformService>;

    class JavaProxy final : ::djinni::JavaProxyHandle<JavaProxy>, public ::ezored::net::http::HttpClientPlatformService
    {
    public:
        JavaProxy(JniType j);
        ~JavaProxy();

        ::ezored::net::http::HttpResponse doRequest(const ::ezored::net::http::HttpRequest & request) override;

    private:
        friend ::djinni::JniInterface<::ezored::net::http::HttpClientPlatformService, ::djinni_generated::EZRHttpClientPlatformService>;
    };

    const ::djinni::GlobalRef<jclass> clazz { ::djinni::jniFindClass("com/ezored/net/http/HttpClientPlatformService") };
    const jmethodID method_doRequest { ::djinni::jniGetMethodID(clazz.get(), "doRequest", "(Lcom/ezored/net/http/HttpRequest;)Lcom/ezored/net/http/HttpResponse;") };
};

}  // namespace djinni_generated

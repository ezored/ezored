// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from proj.djinni

#pragma once

#include "djinni/jni/djinni_support.hpp"
#include "ezored/net/http/HttpClientLogger.hpp"

namespace djinni_generated {

class EZRHttpClientLogger final : ::djinni::JniInterface<::ezored::net::http::HttpClientLogger, EZRHttpClientLogger> {
public:
    using CppType = std::shared_ptr<::ezored::net::http::HttpClientLogger>;
    using CppOptType = std::shared_ptr<::ezored::net::http::HttpClientLogger>;
    using JniType = jobject;

    using Boxed = EZRHttpClientLogger;

    ~EZRHttpClientLogger();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<EZRHttpClientLogger>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<EZRHttpClientLogger>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    EZRHttpClientLogger();
    friend ::djinni::JniClass<EZRHttpClientLogger>;
    friend ::djinni::JniInterface<::ezored::net::http::HttpClientLogger, EZRHttpClientLogger>;

};

}  // namespace djinni_generated

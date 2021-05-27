//
// Copyright 2014 Dropbox, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// Paulo Coutinho <paulo@prsolucoes.com>

// This provides a method to load and unload JNI in Djinni context
// Include it if your app already have a JNI_OnLoad and/or JNI_OnUnload
// methods

// You can call it from Java after load your library (.so) and call
// unload when your library is unloaded or application terminated.

#include "djinni/jni/djinni_support.hpp"

CJNIEXPORT void JNICALL Java_com_dropbox_djinni_JNILoader_load(JNIEnv *env, jobject /*this*/, jlong nativeRef)
{
    JavaVM *jvm;
    env->GetJavaVM(&jvm);
    djinni::jniInit(jvm);
}

CJNIEXPORT void JNICALL Java_com_dropbox_djinni_JNILoader_unload(JNIEnv *env, jobject /*this*/, jlong nativeRef)
{
    djinni::jniShutdown();
}

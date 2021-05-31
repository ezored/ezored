//
// Copyright 2021 cross-language-cpp
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

#pragma once

#include "../proxy_cache_interface.hpp"
#include "AutoPtr.hpp"
#include <vcclr.h>

namespace djinni
{

template <class CsRefType>
class CsRef;

template <class CsType>
class CsRef
{
public:
    CsRef() : _ref(nullptr) {}
    CsRef(CsType ref) : _ref(ref) {}

    CsRef(CsRef &&) = default;
    CsRef &operator=(CsRef &&) = default;

    CsRef(const CsRef &) = default;
    CsRef &operator=(const CsRef &) = default;

    operator bool() { return static_cast<CsType>(_ref) != nullptr; }
    CsType operator->() const { return get(); }
    CsType get() const { return _ref; }

private:
    gcroot<CsType> _ref;
};

/*
* Native wrapper to C#'s WeakReference type. Instances of this type do not prevent the
* garbage collector from reclaiming referred-to objects.
*/
class WeakCsRef
{
public:
    WeakCsRef(System::Object ^ ref)
        : _weak_ref(gcnew System::WeakReference(ref)), _hash_code(ref->GetHashCode()) {}

    WeakCsRef(const CsRef<System::Object ^> &ref)
        : _weak_ref(gcnew System::WeakReference(ref.get())), _hash_code(ref->GetHashCode()) {}

    CsRef<System::Object ^> lock() const { return dynamic_cast<System::Object ^>(_weak_ref->Target); }
    bool expired() const { return !_weak_ref->IsAlive; }
    size_t hash_code() { return _hash_code; }

private:
    CsRef<System::WeakReference ^> _weak_ref;
    size_t _hash_code;
};

struct CsHashCode;
struct CsReferenceEquals;
struct CsProxyCacheTraits
{
    using UnowningImplPointer = WeakCsRef;
    using OwningImplPointer = CsRef<System::Object ^>;
    using OwningProxyPointer = std::shared_ptr<void>;
    using WeakProxyPointer = std::weak_ptr<void>;
    using UnowningImplPointerHash = CsHashCode;
    using UnowningImplPointerEqual = CsReferenceEquals;
};

// This declares that GenericProxyCache will be instantiated separately. The actual
// explicit instantiations are in DJIProxyCaches.mm.
extern template class ProxyCache<CsProxyCacheTraits>;
using CsProxyCache = ProxyCache<CsProxyCacheTraits>;

template <typename CppType, typename CsType>
static std::shared_ptr<CppType> get_cs_proxy(CsType cs)
{
    return std::static_pointer_cast<CppType>(CsProxyCache::get(
        typeid(CppType),
        cs,
        [](const CsProxyCacheTraits::OwningImplPointer &cs) -> std::pair<std::shared_ptr<void>, CsProxyCacheTraits::UnowningImplPointer> {
            return std::make_pair<std::shared_ptr<void>, CsProxyCacheTraits::UnowningImplPointer>(std::make_shared<CppType>(cs), cs);
        }));
}

struct CppProxyCacheTraits
{
    using UnowningImplPointer = void *;
    using OwningImplPointer = std::shared_ptr<void>;
    using OwningProxyPointer = CsRef<System::Object ^>;
    using WeakProxyPointer = WeakCsRef;
    using UnowningImplPointerHash = std::hash<void *>;
    using UnowningImplPointerEqual = std::equal_to<void *>;
};

// This declares that GenericProxyCache will be instantiated separately. The actual
// explicit instantiations are in CppWrapperCache.cpp.
extern template class ProxyCache<CppProxyCacheTraits>;
using CppProxyCache = ProxyCache<CppProxyCacheTraits>;

// If the type T has a handle declarator (^), provides the member typedef type which is the type referred to by T. Otherwise type is T.
template <class T>
struct remove_handle
{
    typedef T type;
};
template <class T>
struct remove_handle<T ^>
{
    typedef T type;
};

// Helper for get_cpp_proxy_impl that takes a std::shared_ptr.
template <typename CsType, typename CppType>
CsType get_cpp_proxy_impl(const std::shared_ptr<CppType> &cppRef)
{
    auto proxy = CppProxyCache::get(
        typeid(cppRef),
        cppRef,
        [](const std::shared_ptr<void> &cppRef) -> std::pair<CppProxyCacheTraits::OwningProxyPointer, void *> {
            return {
                CsRef<System::Object ^>(gcnew typename remove_handle<CsType>::type(std::static_pointer_cast<CppType>(cppRef))),
                cppRef.get()};
        });
    return dynamic_cast<CsType>(proxy.get());
}

// get_cpp_proxy takes any smart pointer type, as long as it can be implicitly cast
// to std::shared_ptr. This means get_cpp_proxy can also be passed non-nullable pointers.
template <typename CsType, typename CppPtrType>
CsType get_cpp_proxy(const CppPtrType &cppRef)
{
    return get_cpp_proxy_impl<CsType, typename std::remove_reference<decltype(*cppRef)>::type>(cppRef);
}

} // namespace djinni

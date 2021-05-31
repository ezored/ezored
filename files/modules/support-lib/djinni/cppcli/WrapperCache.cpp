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

#include "WrapperCache.hpp"
#include "../proxy_cache_impl.hpp"

namespace djinni
{

using UnowningImplPointer = CsProxyCacheTraits::UnowningImplPointer;

struct CsHashCode
{
    size_t operator()(UnowningImplPointer obj) const;
};
struct CsReferenceEquals
{
    bool operator()(UnowningImplPointer obj1, UnowningImplPointer obj2) const;
};

size_t CsHashCode::operator()(UnowningImplPointer obj) const
{
    return obj.hash_code();
}
bool CsReferenceEquals::operator()(UnowningImplPointer obj1, UnowningImplPointer obj2) const
{
    auto ptr1 = obj1.lock();
    auto ptr2 = obj2.lock();
    return System::Object::ReferenceEquals(ptr1.get(), ptr2.get());
}

template class ProxyCache<CsProxyCacheTraits>;
template class ProxyCache<CppProxyCacheTraits>;

} // namespace djinni

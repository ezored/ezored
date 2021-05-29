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

#include <msclr\marshal_cppstd.h>

#include <chrono>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Assert.hpp"

namespace djinni
{

template <class CppTypeArg, class CsTypeArg>
struct Primitive
{
    using CppType = CppTypeArg;
    using CsType = CsTypeArg;

    static CppType ToCpp(CsType x) noexcept
    {
        return x;
    }
    static CsType FromCpp(CppType x) noexcept
    {
        return x;
    }
};

using Bool = Primitive<bool, bool>;
using I8 = Primitive<int8_t, char>;
using I16 = Primitive<int16_t, short>;
using I32 = Primitive<int32_t, int>;
using I64 = Primitive<int64_t, __int64>;
using F32 = Primitive<float, float>;
using F64 = Primitive<double, double>;

template <class CppEnum, class CsEnum>
struct Enum
{
    using CppType = CppEnum;
    using CsType = CsEnum;

    static CppType ToCpp(CsType e) noexcept
    {
        return static_cast<CppType>(e);
    }

    static CsType FromCpp(CppType e) noexcept
    {
        return static_cast<CsType>(e);
    }
};

struct String
{
    using CppType = std::string;
    using CsType = System::String ^ ;

    static CppType ToCpp(CsType string)
    {
        ASSERT(string != nullptr);
        cli::array<System::Byte> ^ bytes = System::Text::Encoding::UTF8->GetBytes(string);
        CppType cpp_str;
        cpp_str.resize(bytes->Length);
        System::Runtime::InteropServices::Marshal::Copy(bytes, 0, System::IntPtr(const_cast<char *>(cpp_str.data())), cpp_str.length());
        return cpp_str;
    }

    static CsType FromCpp(const CppType &string)
    {
        cli::array<System::Byte> ^ bytes = gcnew cli::array<System::Byte>(string.length());
        for (size_t i = 0; i < string.length(); i++)
        {
            bytes[i] = string[i];
        }
        return System::Text::Encoding::UTF8->GetString(bytes);
    }
};

struct WString
{
    using CppType = std::wstring;
    using CsType = System::String ^ ;

    static CppType ToCpp(CsType string)
    {
        ASSERT(string != nullptr);
        return msclr::interop::marshal_as<CppType>(string);
    }

    static CsType FromCpp(const CppType &string)
    {
        return msclr::interop::marshal_as<CsType>(string);
    }
};

struct Date
{
    using CppType = std::chrono::system_clock::time_point;
    using CsType = System::DateTime;

    using Ticks = std::chrono::duration<int64_t, std::ratio<1, 10000000>>;
    static const auto TicksBeforeEpoch = 621355968000000000;

    static CppType ToCpp(CsType date)
    {
        auto ticks = Ticks(date.Ticks - TicksBeforeEpoch);
        return std::chrono::system_clock::time_point(ticks);
    }

    static CsType FromCpp(const CppType &date)
    {
        auto ticks = std::chrono::duration_cast<Ticks>(date.time_since_epoch()).count();
        return CsType(ticks + TicksBeforeEpoch);
    }
};

struct Binary
{
    using CppType = std::vector<uint8_t>;
    using CsType = array<System::Byte> ^ ;

    using Boxed = Binary;

    static CppType ToCpp(CsType data)
    {
        ASSERT(data != nullptr);
        CppType v;
        v.reserve(data->Length);
        for each (auto value in data)
        {
            v.emplace_back(value);
        }
        return v;
    }

    static CsType FromCpp(const CppType &bytes)
    {
        auto len = bytes.size();
        auto ret = gcnew array<System::Byte>(len);
        System::Runtime::InteropServices::Marshal::Copy(System::IntPtr(const_cast<CppType::value_type *>(&bytes[0])), ret, 0, len);
        return ret;
    }
};

template <class T>
struct IsRef : std::false_type
{
};

template <class T>
struct IsRef<T ^> : std::true_type
{
};

template <class T>
struct CsOptional
{
    typedef System::Nullable<T> type;
};

template <class T>
struct CsOptional<T ^>
{
    typedef T ^ type;
};

template <template <class> class OptionalType, class T>
struct Optional
{
    // SFINAE helper: if C::CppOptType exists, opt_type<T>(nullptr) will return
    // that type. If not, it returns OptionalType<C::CppType>. This is necessary
    // because we special-case optional interfaces to be represented as a nullable
    // std::shared_ptr<T>, not optional<shared_ptr<T>> or optional<nn<shared_ptr<T>>>.
    template <typename C>
    static OptionalType<typename C::CppType> opt_type(...);
    template <typename C>
    static typename C::CppOptType opt_type(typename C::CppOptType *);

    using CppType = decltype(opt_type<T>(0));
    using CsType = typename T::CsType;

    using CsOptionalType = typename ::djinni::CsOptional<typename T::CsType>::type;

    // Enabled for reference types (^).
    template <class O, typename std::enable_if<IsRef<O>::value, int>::type = 0>
    static CppType ToCpp(O obj)
    {
        if (obj != nullptr)
        {
            return T::ToCpp(obj);
        }
        return CppType();
    }

    // Enabled for value types that require System::Nullable<>.
    template <class O, typename std::enable_if<!IsRef<O>::value, int>::type = 0>
    static CppType ToCpp(O obj)
    {
        if (obj.HasValue)
        {
            return T::ToCpp(obj.Value);
        }
        return CppType();
    }

    // FromCpp used for normal optionals
    static CsOptionalType FromCpp(const OptionalType<typename T::CppType> &opt)
    {
        return opt ? T::FromCpp(*opt) : CsOptionalType();
    }

    // FromCpp used for nullable objects
    template <typename C = T>
    static CsType FromCpp(const typename C::CppOptType &cppOpt)
    {
        return T::FromCppOpt(cppOpt);
    }
};

template <class T>
struct List
{
    using CppType = std::vector<typename T::CppType>;
    using CsType = System::Collections::Generic::List<typename T::CsType> ^ ;

    static CppType ToCpp(CsType l)
    {
        ASSERT(l != nullptr);
        CppType v;
        v.reserve(l->Count);
        for each (auto value in l)
        {
            v.emplace_back(T::ToCpp(value));
        }
        return v;
    }

    static CsType FromCpp(const CppType &v)
    {
        auto l = gcnew System::Collections::Generic::List<typename T::CsType>();
        for (const auto &value : v)
        {
            l->Add(T::FromCpp(value));
        }
        return l;
    }
};

template <class T>
class Set
{
public:
    using CppType = std::unordered_set<typename T::CppType>;
    using CsType = System::Collections::Generic::HashSet<typename T::CsType> ^ ;

    static CppType ToCpp(CsType set)
    {
        ASSERT(set != nullptr);
        CppType s;
        for each (auto value in set)
        {
            s.insert(T::ToCpp(value));
        }
        return s;
    }

    static CsType FromCpp(const CppType &s)
    {
        auto set = gcnew System::Collections::Generic::HashSet<typename T::CsType>();
        for (const auto &value : s)
        {
            set->Add(T::FromCpp(value));
        }
        return set;
    }
};

template <class Key, class Value>
struct Map
{
    using CppType = std::unordered_map<typename Key::CppType, typename Value::CppType>;
    using CsType = System::Collections::Generic::Dictionary<typename Key::CsType, typename Value::CsType> ^ ;

    static CppType ToCpp(CsType map)
    {
        ASSERT(map != nullptr);
        CppType m;
        m.reserve(map->Count);
        for each (auto &kvp in map)
        {
            m.emplace(Key::ToCpp(kvp.Key), Value::ToCpp(kvp.Value));
        }
        return m;
    }

    static CsType FromCpp(const CppType &m)
    {
        auto map = gcnew System::Collections::Generic::Dictionary<typename Key::CsType, typename Value::CsType>(m.size());
        for (const auto &kvp : m)
        {
            map->Add(Key::FromCpp(kvp.first), Value::FromCpp(kvp.second));
        }
        return map;
    }
};

} // namespace djinni

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

#include "Assert.hpp"

template <typename T>
ref struct AutoPtr
{
    AutoPtr() : _ptr(0) {}
    AutoPtr(T *ptr) : _ptr(ptr) {}
    AutoPtr(AutoPtr<T> % right) : _ptr(right.Release()) {}

    ~AutoPtr()
    {
        delete _ptr;
        _ptr = 0;
    }
    !AutoPtr()
    {
        //ASSERT(0 == _ptr);
        delete _ptr;
    }
    T *operator->()
    {
        if (0 == _ptr)
        {
            throw gcnew System::ObjectDisposedException(System::String::Empty);
        }

        return _ptr;
    }

    T *GetPointer()
    {
        return _ptr;
    }
    T &GetRef()
    {
        if (0 == _ptr)
        {
            throw gcnew System::ObjectDisposedException(System::String::Empty);
        }

        return *_ptr;
    }
    T *Release()
    {
        T *released = _ptr;
        _ptr = 0;
        return released;
    }
    void Reset()
    {
        Reset(0);
    }
    void Reset(T *ptr)
    {
        if (ptr != _ptr)
        {
            delete _ptr;
            _ptr = ptr;
        }
    }

private:
    T *_ptr;
};

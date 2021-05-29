// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from proj.djinni

#import "ezored/domain/EZRDomainCustomer+Private.h"
#import "djinni/objc/DJIMarshal+Private.h"
#import "ezored/enumerator/EZREnumeratorCustomerStatusEnumerator+Private.h"
#include <cassert>

namespace djinni_generated {

auto Customer::toCpp(ObjcType obj) -> CppType
{
    assert(obj);
    return {::djinni::I64::toCpp(obj.id),
            ::djinni::String::toCpp(obj.name),
            ::djinni::String::toCpp(obj.token),
            ::djinni::Enum<::ezored::enumerator::CustomerStatusEnumerator, EZREnumeratorCustomerStatusEnumerator>::toCpp(obj.status)};
}

auto Customer::fromCpp(const CppType& cpp) -> ObjcType
{
    return [[EZRDomainCustomer alloc] initWithId:(::djinni::I64::fromCpp(cpp.id))
                                            name:(::djinni::String::fromCpp(cpp.name))
                                           token:(::djinni::String::fromCpp(cpp.token))
                                          status:(::djinni::Enum<::ezored::enumerator::CustomerStatusEnumerator, EZREnumeratorCustomerStatusEnumerator>::fromCpp(cpp.status))];
}

}  // namespace djinni_generated

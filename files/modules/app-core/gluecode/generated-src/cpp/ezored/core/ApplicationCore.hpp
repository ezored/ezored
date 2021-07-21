// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from proj.djinni

#pragma once

#include "ezored/domain/Customer.hpp"
#include "ezored/domain/DeviceData.hpp"
#include "ezored/domain/InitializationData.hpp"
#include <memory>
#include <string>

namespace ezored
{
namespace core
{

class ApplicationCore
{
public:
    virtual ~ApplicationCore() {}

    static std::shared_ptr<ApplicationCore> shared();

    virtual void initialize(const ::ezored::domain::InitializationData &initializationData, const ::ezored::domain::DeviceData &deviceData) = 0;

    virtual ::ezored::domain::InitializationData getInitializationData() = 0;

    virtual ::ezored::domain::DeviceData getDeviceData() = 0;

    virtual ::ezored::domain::Customer getCustomer() = 0;

    virtual void setCustomer(const ::ezored::domain::Customer &customer) = 0;

    virtual std::string getVersion() = 0;
};

} // namespace core
} // namespace ezored
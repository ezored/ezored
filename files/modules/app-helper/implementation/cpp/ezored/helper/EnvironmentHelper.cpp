#include "ezored/helper/EnvironmentHelper.hpp"
#include "ezored/helper/SecurityHelper.hpp"

namespace ezored
{
namespace helper
{

std::string EnvironmentHelper::getSecretKey()
{
    return SecurityHelper::generateUuidV4();
}

} // namespace helper
} // namespace ezored

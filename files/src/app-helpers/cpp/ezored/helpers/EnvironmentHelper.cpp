#include "ezored/helpers/EnvironmentHelper.hpp"
#include "ezored/helpers/SecurityHelper.hpp"

namespace ezored
{
namespace helpers
{

std::string EnvironmentHelper::getSecretKey()
{
    return SecurityHelper::generateUuidV4();
}

} // namespace helpers
} // namespace ezored

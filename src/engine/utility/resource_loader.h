#ifndef _ENGINE_RESOURCE_LOADER_H_
#define _ENGINE_RESOURCE_LOADER_H_

#include <Thor/Resources.hpp>

namespace engine {
namespace utility {
namespace resource_loader {

// The main thor cache from which resources should be access.
extern thor::MultiResourceCache cache;

}}}  // namespace engine::utility::resource_loader

#endif  // _ENGINE_RESOURCE_LOADER_H_

#ifndef _ENGINE_TEXTURE_LOADER_H_
#define _ENGINE_TEXTURE_LOADER_H_

// A class to allow for single-use loading of textures. This class will also
// keep a reference to all textures that are passed around.
//
// Textures should only be loaded by this module.

#include <unordered_map>

#include <SFML/Graphics.hpp>

namespace engine {
namespace utility {
namespace texture_loader {

// The main loading function. This will take as input a filename and load the
// corresponding texture into memory. This texture will be stored in a mapping
// structure using the filename provided (i.e. the filepath) as the unique key.
// If the texture mentioned has already been loaded, then skip loading and just
// return a reference to it.
const sf::Texture& Load(const std::string& texture_filename);

}}}  // namespace engine::utility::texture_loader

#endif  // _ENGINE_TEXTURE_LOADER_H_

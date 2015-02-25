#include "texture_loader.h"

namespace engine {
namespace utility {
namespace texture_loader {

// Hash map structure from filename --> texture object.
std::unordered_map<std::string, sf::Texture> textures_;

const sf::Texture& Load(const std::string& texture_filename) {
  try {
    return textures_.at(texture_filename);
  } catch (std::out_of_range) {
    // Do nothing, load a new texture.
  }

  textures_[texture_filename] = sf::Texture();
  textures_[texture_filename].loadFromFile(texture_filename);
  return textures_[texture_filename];
}

}}}  // namespace engine::utility::texture_loader

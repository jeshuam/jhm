#include "zone.h"

namespace engine {
namespace component {

Zone::Zone() : area_(), scale_(1.0) {

}

Zone::~Zone() {

}

void Zone::SetParameter(const std::string& key, const Json::Value& value) {
  if (key == "area") {
    area({value[0].asFloat(), value[1].asFloat(),
          value[2].asFloat(), value[3].asFloat()});
  }

  else if (key == "scale") {
    scale(value.asDouble());
  }
}

bool Zone::Update(Game& game) {
  return true;
}

Zone* Zone::area(sf::FloatRect area) {
  area_ = area;
  return this;
}

Zone* Zone::scale(double scale_factor) {
  scale_ = scale_factor;
  return this;
}

const sf::FloatRect Zone::area() const {
  sf::FloatRect scaled_area = area_;
  scaled_area.left *= scale_;
  scaled_area.top *= scale_;
  scaled_area.width *= scale_;
  scaled_area.height *= scale_;

  return scaled_area;
}

double Zone::scale() const {
  return scale_;
}

}}  // namepsace engine::component

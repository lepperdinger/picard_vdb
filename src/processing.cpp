// Author: Stefan Lepperdinger
#include "processing.h"

namespace processing {

void normalize_data(tensors::tensor_3d &data) {
  double maximum_value{0.};
  for (const auto &x : data) {
    for (const auto &y : x) {
      for (const auto &z : y) {
        if (z > maximum_value) {
          maximum_value = z;
        }
      }
    }
  }
  for (auto &x : data) {
    for (auto &y : x) {
      for (auto &z : y) {
        z /= maximum_value;
      }
    }
  }
}

} // namespace processing
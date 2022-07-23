//
// Created by stefan on 7/23/22.
//

#include "vdb_file.h"

namespace vdb_file {

openvdb::FloatGrid::Ptr create_grid(float background_value, float voxel_size) {
  openvdb::FloatGrid::Ptr grid = openvdb::FloatGrid::create(background_value);
  grid->setTransform(
      openvdb::math ::Transform ::createLinearTransform(voxel_size));
  grid->setGridClass(openvdb::GRID_LEVEL_SET);
  grid->setName("density");
  return grid;
}

} // namespace write_data
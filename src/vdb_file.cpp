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

void fill_grid(const openvdb::FloatGrid::Ptr &grid,
                   const tensors::tensor_3d &data) {
  using ValueT = typename openvdb::FloatGrid::ValueType;
  typename openvdb::FloatGrid::Accessor accessor = grid->getAccessor();
  openvdb::Coord xyz_coordinates;
  int &x = xyz_coordinates[0];
  int &y = xyz_coordinates[1];
  int &z = xyz_coordinates[2];
  int number_of_x_values = data.size();
  int number_of_y_values = data.back().size();
  int number_of_z_values = data.back().back().size();
  for (x = 0; x != number_of_x_values; ++x) {
    for (y = 0; y != number_of_y_values; ++y) {
      for (z = 0; z != number_of_z_values; ++z) {
        ValueT value = data[x][y][z];
        accessor.setValue(xyz_coordinates, value);
      }
    }
  }
}

} // namespace vdb_file
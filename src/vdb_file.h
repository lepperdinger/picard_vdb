//
// Created by stefan on 7/23/22.
//

#ifndef HDF5_TO_OPENVDB_SRC_WRITE_H
#define HDF5_TO_OPENVDB_SRC_WRITE_H

#include "tensors.h"
#include <openvdb/openvdb.h>

namespace vdb_file {

openvdb::FloatGrid::Ptr create_grid(float background_value = 0,
                                    float voxel_size = 0.5);
void fill_vdb_grid(const openvdb::FloatGrid::Ptr &grid,
                   const tensors::tensor_3d &data);

} // namespace vdb_file

#endif // HDF5_TO_OPENVDB_SRC_WRITE_H

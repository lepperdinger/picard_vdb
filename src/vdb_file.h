// Author: Stefan Lepperdinger
#ifndef PICARD_VDB_SRC_VDB_FILE_H
#define PICARD_VDB_SRC_VDB_FILE_H

#include "tensors.h"
#include <openvdb/openvdb.h>

namespace vdb_file {

openvdb::FloatGrid::Ptr create_grid(float background_value = 0,
                                    float voxel_size = 0.5);
void fill_grid(const openvdb::FloatGrid::Ptr &grid,
               const tensors::tensor_3d &data);

void save_file(const std::string &file_path,
               const openvdb::FloatGrid::Ptr &grid);

} // namespace vdb_file

#endif // PICARD_VDB_SRC_VDB_FILE_H

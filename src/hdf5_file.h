//
// Created by stefan on 7/23/22.
//

#ifndef HDF5_TO_OPENVDB_SRC_READ_H
#define HDF5_TO_OPENVDB_SRC_READ_H

#include "tensors.h"
#include <hdf5.h>

namespace hdf5_file {

tensors::tensor_3d read_3d_dataset(const std::string &file_name,
                                   const std::string &dataset_name);

}

#endif // HDF5_TO_OPENVDB_SRC_READ_H

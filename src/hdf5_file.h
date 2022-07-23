// Author: Stefan Lepperdinger
#ifndef PICARD_VDB_SRC_HDF5_FILE_H
#define PICARD_VDB_SRC_HDF5_FILE_H

#include "tensors.h"
#include <hdf5.h>

namespace hdf5_file {

tensors::tensor_3d read_3d_dataset(const std::string &file_name,
                                   const std::string &dataset_name);

}

#endif // PICARD_VDB_SRC_HDF5_FILE_H

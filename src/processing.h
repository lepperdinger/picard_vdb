// Author: Stefan Lepperdinger
#ifndef HDF5_TO_OPENVDB_SRC_PROCESSING_H
#define HDF5_TO_OPENVDB_SRC_PROCESSING_H

#include "tensors.h"

namespace processing {
void normalize_data(tensors::tensor_3d &data);
}

#endif // HDF5_TO_OPENVDB_SRC_PROCESSING_H

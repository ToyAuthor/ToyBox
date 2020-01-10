
#pragma once

#include <cstdint>
#include <functional>
#include "toy/gadget/Export.hpp"

namespace toy{
namespace gadget{

TOY_API_GADGET extern bool WriteUnsignedVariableLengthInteger( uint64_t,
                                                               std::function<bool(uint8_t)> );
TOY_API_GADGET extern bool ReadUnsignedVariableLengthInteger( uint64_t*,
                                                              std::function<bool(uint8_t*)> );
TOY_API_GADGET extern bool WriteVariableLengthInteger( int64_t,
                                                       std::function<bool(uint8_t)> );
TOY_API_GADGET extern bool ReadVariableLengthInteger( int64_t*,
                                                      std::function<bool(uint8_t*)> );
}}

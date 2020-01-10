
#pragma once

#include "toy/Standard.hpp"
#include "toy/gadget/Export.hpp"

namespace toy{
namespace gadget{

// Convert a integer to little endian or big endian
TOY_API_GADGET extern void LittleEndian(int16_t*);
TOY_API_GADGET extern void LittleEndian(uint16_t*);
TOY_API_GADGET extern void LittleEndian(uint32_t*);
TOY_API_GADGET extern void LittleEndian(uint64_t*);
TOY_API_GADGET extern void BigEndian(uint16_t*);
TOY_API_GADGET extern void BigEndian(uint32_t*);
TOY_API_GADGET extern void BigEndian(uint64_t*);
TOY_API_GADGET extern  int16_t LittleEndian(int16_t);
TOY_API_GADGET extern uint16_t LittleEndian(uint16_t);
TOY_API_GADGET extern uint32_t LittleEndian(uint32_t);
TOY_API_GADGET extern uint64_t LittleEndian(uint64_t);
TOY_API_GADGET extern uint16_t BigEndian(uint16_t);
TOY_API_GADGET extern uint32_t BigEndian(uint32_t);
TOY_API_GADGET extern uint64_t BigEndian(uint64_t);

// Convert little endian to normal byte order
TOY_API_GADGET extern void LittleEndianToCorrect(int16_t *input);

}}

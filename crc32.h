#pragma once

// Reference: docs.novatel.com/OEM4/Content/Messages/32_Bit_CRC.htm

#include <stdint.h>

// interface
uint64_t CalculateBlockCRC32( uint8_t *buffer, uint64_t count );


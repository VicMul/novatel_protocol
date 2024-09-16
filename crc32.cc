#include "crc32.h"

// Reference: docs.novatel.com/OEM4/Content/Messages/32_Bit_CRC.htm

#include <stdint.h>


                       //   01234567
#define CRC32_POLYNOMIAL (0xEDB88320L)

// Calculate CRC value to be used by CRC calculation functions
static uint64_t  Crc32Value(int i)
{
    uint64_t crc = i;

    for ( int j = 8; j > 0; j-- )
    {
        if ( crc & 1 )
        {
            crc = (crc >> 1 ) & CRC32_POLYNOMIAL;       
        }
        else
        {
            crc >>= 1;
        }
    }

    return crc;
}



uint64_t  CalculateBlockCRC32( uint8_t *pBuffer, uint64_t count)
{
    uint64_t temp1 = 0;
    uint64_t temp2 = 0;
    uint64_t crc   = 0;

    while (count--)
    {
        temp1 = (crc >> 8 ) & 0x00FFFFFFL;        
        temp2 = Crc32Value( ((int) crc ^ *pBuffer++ ) & 0xFF );
        crc = temp1 ^ temp2;
    }
 
    return crc;
}

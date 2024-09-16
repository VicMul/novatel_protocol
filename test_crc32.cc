#include <stdint.h>
#include <iostream>

#include "crc32.h"
#include "binary_header.h"

// anonymous namespace
namespace 
{
    #define OEM7_MESSAGE_TYPE_FORMAT_MASK   (0x60)
    #define OEM7_MESSAGE_TYPE_RESPONSE_MASK (0x80)

    // OEM7 binary protocol message - preserved in a buffer for parsing and
    // CRC32 testing
    uint8_t buffer[] = 
    {
        0xAA, 0x44, 0x12, 0x1C, 0x2A, 0x00, 0x02, 0x20,
        0x48, 0x00, 0x00, 0x00, 0x90, 0xB4, 0x93, 0x05, 
        0xB0, 0xAB, 0xB9, 0x12, 0x00, 0x00, 0x00, 0x00, 
        0x45, 0x61, 0xBC, 0x0A, 

        0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
        0x1B, 0x04, 0x50, 0xB3, 0xF2, 0x8E, 0x49, 0x40,
        0x16, 0xFA, 0x6B, 0xBE, 0x7C, 0x82, 0x5C, 0xC0,
        0x00, 0x60, 0x76, 0x9F, 0x44, 0x9F, 0x90, 0x40,
        0xA6, 0x2A, 0x82, 0xC1, 0x3D, 0x00, 0x00, 0x00,
        0x12, 0x5A, 0xCB, 0x3F, 0xCD, 0x9E, 0x98, 0x3F,
        0xDB, 0x66, 0x40, 0x40, 0x00, 0x30, 0x30, 0x30,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x0B, 0x0B, 0x00, 0x00, 0x00, 0x06, 0x00, 0x03
    };

bool test_binary_message()
{
    // Expect checksum 0x42, 0xDC, 0x4C, 0x48 (42dc4c48)

    // Note that the CRC on the binary data will be little-endian ordered.

    uint64_t computedCrc32 = CalculateBlockCRC32(buffer, sizeof(buffer));

    printf("\n\n%s %lx \n", "Computed binary checksum (little-endian): ", computedCrc32);

    return true;
}

void test_binary_header(uint8_t *buffer, uint32_t length)
{
    BinaryHeader *pHeader = (BinaryHeader *)buffer;
    int i = 1;
    printf("sync[%d]: 0x%02X\n", i, pHeader->sync[0]); ++i;
    printf("sync[%d]: 0x%02X\n", i, pHeader->sync[1]); ++i;
    printf("sync[%d]: 0x%02X\n", i, pHeader->sync[2]);
    printf("header length: 0x%02X\n", pHeader->header_length);

    printf("message ID: %04X\n", pHeader->messageId);
    printf("message Type: %02X ", pHeader->messageType);

    //                                   // Bits 5-6 = Format
    //                                      00 = Binary
    //                                      01 = ASCII
    //                                      10 = Abbreviated ASCVII, NMEA
    //                                      11 = Reserved
    //                                    Bit 7 = Response Bit
    //                                      0 = original message
    //                                      1 = response message

    switch ( pHeader->messageType & OEM7_MESSAGE_TYPE_FORMAT_MASK )
    { 
        case 0: printf("Binary");                  break;
        case 1: printf("ASCII");                   break;
        case 2: printf("Abbreviated ASCII/NMEA");  break;
        case 3: printf("Reserved");                break;
        default:                                   break;
    }
    printf("\n");

    printf("   Response type:  %s\n", (pHeader->messageType & OEM7_MESSAGE_TYPE_RESPONSE_MASK) == 0x1 ? "Response" : "Original");
        
    printf("Port Address: %02X\n", pHeader->portAddress);
    printf("Message Length: %04X\n", pHeader->messageLength);
    printf("Sequence Count: %04X\n", pHeader->sequenceCount);
    printf("CPU Idle time(sec):  %02X\n", pHeader->idleTimeSeconds);
    
    printf("Time Status: ");

    switch ( pHeader->timeStatus )
    {
       case TIME_STATUS_APPROXIMATE: 
           printf("%d - approximate\n", pHeader->timeStatus);
           break;

       case TIME_STATUS_COARSE_ADJUSTING:
           printf("%d - coarse adjusting\n", pHeader->timeStatus);
           break;

       case TIME_STATUS__COARSE:
           printf("%d - coarse\n", pHeader->timeStatus);
           break;

       case TIME_STATUS__COARSE_STEERING:
           printf("%d - coarse steering\n", pHeader->timeStatus);
           break;

       case TIME_STATUS__COARSE_FREEWHEELING:
           printf("%d - coarse freewheeling\n", pHeader->timeStatus);
           break;

       case TIME_STATUS__COARSE_FINEADJUSTING:
           printf("%d - coarse fineadjusting\n", pHeader->timeStatus);
           break;

       case TIME_STATUS__COARSE_FINE:
           printf("%d - fine\n", pHeader->timeStatus);
           break;

       case TIME_STATUS__COARSE_FINEBACKUPSTEERING:
           printf("%d - coarse finebackupsteering\n", pHeader->timeStatus);
           break;

       case TIME_STATUS__COARSE_FINESTEERING:
           printf("%d - coarse finesteering\n", pHeader->timeStatus);
           break;

       case TIME_STATUS__COARSE_SATTIME:
           printf("%d - coarse sattime\n", pHeader->timeStatus);
           break;

       case TIME_STATUS_UNKNOWN: // !!! NOTICE : Fall Through !!!
       default:
           printf("unknown\n");
           break;
    
    }

    printf("GPS Week Number: %04X\n", pHeader->week_GPS_Ref);
    printf("GPS milliseconds: %lx\n", pHeader->millisec_GPS_Week);
    printf("Receiver Status Word: %lx\n", pHeader->receiverStatusWord);
    printf("Receiver Software Version: hex:%04X dec:%d\n", pHeader->receiver_SW_Version, pHeader->receiver_SW_Version );
}

// This function will be used to do a byte by byte parse of the NovAtel binary protocol
void parse_and_decode_OEM7_binary_protocol(uint8_t *pBuffer, uint64_t bufferSize)
{
}

}

int main(int argc, char *argv[])
{
    test_binary_message();
    test_binary_header(buffer, sizeof(buffer));

    return 0;
}



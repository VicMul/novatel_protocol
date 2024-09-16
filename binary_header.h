#pragma once

#include <stdint.h>

#define BINARY_SYNC_1 (0xAA)
#define BINARY_SYNC_2 (0x44)
#define BINARY_SYNC_3 (0x12)

enum TimeStatus
{
   TIME_STATUS_UNKNOWN                    = 20,   // Time validity is unknown
   TIME_STATUS_APPROXIMATE                = 60,   // Time is set approximately
   TIME_STATUS_COARSE_ADJUSTING           = 80,   // Time is approaching coarse precision
   TIME_STATUS__COARSE                    = 100,  // This time is valid to coarse precision
   TIME_STATUS__COARSE_STEERING           = 120,  // Time is coarse set and is being steered
   TIME_STATUS__COARSE_FREEWHEELING       = 130,  // Position is lost and the range bias cannot be calculated
   TIME_STATUS__COARSE_FINEADJUSTING      = 140,  // Time is adjusting to find precision
   TIME_STATUS__COARSE_FINE               = 160,  // Time has fine precision
   TIME_STATUS__COARSE_FINEBACKUPSTEERING = 170,  // Time is fine set is is being steered by the backup system
   TIME_STATUS__COARSE_FINESTEERING       = 180,  // Time is fine set and is being steered
   TIME_STATUS__COARSE_SATTIME            = 200   // Time from satellite.  Only used in logs containing satellite data such as ephemeris and almanac
};

// spaced vertically to indicate 4-byte word alignment
typedef struct BinaryHeader
{
    //----
    enum { QTY_SYNC_BYTES = 3 };
    uint8_t   sync[ QTY_SYNC_BYTES ]; 	 // Sync bytes 
    uint8_t   header_length;

    //----
    uint16_t  messageId;                 // This is the Message ID number of the command or log
    uint8_t   messageType;               // Bits 0-4 = measurement source
    //                                   // Bits 5-6 = Format
    //                                      00 = Binary
    //                                      01 = ASCII
    //                                      10 = Abbreviated ASCVII, NMEA
    //                                      11 = Reserved
    //                                    Bit 7 = Response Bit
    //                                      0 = original message
    //                                      1 = response message
    uint8_t  portAddress;

    //----
    uint16_t  messageLength;             // The lenght in bytes of the body of the message, not including the header or the CRC
    uint16_t  sequenceCount;             // Uesd for multiple related logs.  Counts down from N-1 to 0 where N is the number of related logs, and 0 is the last of the set.

    //----
    uint8_t   idleTimeSeconds;           // Time the processort is idle, calculated once per second
    uint8_t   padding1[3];

    //----
    TimeStatus timeStatus;           //

    //----
    uint16_t  week_GPS_Ref;              // GPS reference week number
    uint8_t   padding2[2];

    //----
    uint64_t  millisec_GPS_Week;        // TODO: verify size - aka GPSec - Milliseconds from the beginning of the GPS reference week (ulong)

    //----
    uint64_t receiverStatusWord;

    
    //----
    uint16_t  reserved;
    uint16_t  receiver_SW_Version;      // A value between 0 - 65535 inclusive representing the built number

} BinaryHeader_t;

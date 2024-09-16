# novatel_protocol
Commencing with OEM7 binary protocol parsing of the NovAtel binary message format for GNSS receivers.

Implements CRC32 - as described in the OEM7 Manual

Test file will test the CRC32 checksum function with a pre-defined array of hexadecimal chararacters representing the 
NovAtel OEM7 binary protocol.  

Also, the OEM7 binary header struct will be tested as an overlay on the byte array of the same hexadecimal characters of
the aforementioned OEM7 binary protocol.

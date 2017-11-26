# V16 HW

Hardware is a common interface for ADP and SDP, if the given hardware does not handle ADP or SDP it
should return a dummy value of `0x0000`

## Hardware Modules
  * Hardware address used in cpu is composed of (nibbles)
    * `CCAA` where
      * `C` - channel (hardware id)
      * `A` - databus address
    * ROM shall be connected as `HW[0xFF]`
      * whole ROM is copied to memory when the CPU starts
    * Memory shall be connected as `HW[0x00]`


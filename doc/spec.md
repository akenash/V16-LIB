# V16 CPU specifications

## General
  * 16 bit word - W
  * 1W memory addresses (128KiB max)
  * 16x 1W registers (`R[0]` .. `R[F]`)
  * 1W program counter (`PC`)
  * 8 bit stack pointer (`SP`)
  * 4 bit flag (`F`) where
    * `OP--` where
      * `O` - overflow flag
      * `P` - panic flag
    * `F[O]` refers to overflow flag etc.
  * 256x 1W stack (`S[0]` .. `S[FF]`)
  * hardware modules
  * big endian

## Hardware Modules
  * Hardware address is composed of (nibbles)
    * `CCAA` where
      * `C` - channel (hardware id)
      * `A` - databus address
    * ROM shall be connected as `HW[0xFF]`
      * whole ROM is copied to memory when the CPU starts
    * Memory shall be connected as `HW[0x00]`

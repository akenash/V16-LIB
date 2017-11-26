# V16-ASM

## Syntax

### Instructions
  * `ZZZ $A:XXXX $B:YYYY` where
    * `ZZZ` - base instruction (for example `ADD`)
    * `$` - if placed, means the mode is indirect
      * indirect means that instead of taking val, it takes M[val]
    * `AB` - modes (for example `R`)
    * `XY` - addresses (for example `0FA3`)
  * examples
    * `CPY  M:0xFFFF $M:0x0000` - copy the value `0xFFFF` to the memory at address `0x0000`
    * `JMP  R:0x0002` - jump to the address stored in `R[2]`
    * `JMP $R:0x0002` - jump to the address stored in memory at address stored in `R[2]`

### Comments
  * `#` - comment lines

### Constants
  * `NAME:VALUE`
  * refering to constants
    * `M%NAME`
    * instead of using `:` after a mode use `%`
  * example
  * names should be up to 6 letters of length (so that they don't break the indent)
    * although this is purely subjective as the indent is not enforced in any way
  * constants are compile-time abstraction only

### Plain Data
  * you can store plain data by writing a number in the line
  * for example beginning a line with `0x0000`
    * you can then write more data in the same line

### Relative location pointers (RLP)
  * you can create a RLP to be used with S and A modes by using
    * `.NAME`
  * the pointer will point to the line below
  * the pointer must take the whole line (i.e. there is nothing besides it in the line)
  * referring to the pointer is by not writing the mode and replacing the value field
    * with `.NAME`
    * for example
      * `CPY  R:0x0000 $  .ITER`
    * as a compile-time abstraction the pointer will be replaced with either
      * `S:_relativepos_` or
      * `A:_relativepos_`
    * indirect modes can be also used
  * pointer can also be offseted by writing a number after it
    * the number must be prefixed by `+` or `-` to specify direction
    * for example
      *`.START -0x0003`
      * which means
        * `.START` refers to three instructions before the nearest instruction below

# V16-ASM

## Syntax

### Instructions
  * `code MTIvalue MTIvalue` where
    * `code` is the opcode
    * `M` is the mode value modifier
      * ` ` - no effect
      * `+` - positive offset for O mode (in practice same as none)
      * `-` - negative offset for O mode
      * `>` - increment then return
      * `<` - return then increment
    * `T` is the mode type
      * `M` - value from memory
      * `R` - value from register
      * `O` - value from PC +- offset (see value modifiers)
      * `C` - value from carry flag
    * `I` is the direction mode
      * `:` - direct mode
        * this shouldn't be used with labels
      * `@` - indirect mode

### Constants
  * `$NAME value` where
    * `NAME` - name of the constant (not necessarily upper case)
    * `value` - value of the constant; can be another constant
  * compile-time abstraction only

### Data
  * `value` where
    * `value` - value of the data
    * defining the data simply places it into memory
    * you can place multiple values separated by space in one line

### Labels
  * `.name` where
    * `name` - name of the label
    * labels let you address relative positions in your program much easier
    * labels are translated into O mode values with positive or negative offsets
    * you can refer to labels without specyfing the mode
    * if you want the label reference to be indirect use `@` before the label's name
  * compile-time abstraction only

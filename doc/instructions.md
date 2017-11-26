# V16 CPU Instructions

## General
  * instructions take up from 1 word to 3 words
  * base instruction composed of (bits)
    * `IIIIIIAAAAABBBBB`
    * where
      * `I` - opcode
      * `A` - `A` mode
      * `B` - `B` mode
  * additionaly instruction can have two words afterwards
    * `X` governed by the `A` mode
    * `Y` governed by the `Y` mode
  * if the `A` mode does not require `X` word, the `Y` word gets shifted one word to the left

## Modes
  * modes take 5 bits
  * modes are composed of (bits)
    * `TTIMM`
    * where
      * `T` - mode type
      * `I` - indirect bit
      * `M` - value modifier

### Mode types
| Value | ID | Cost | Name       | Description
|:-----:|:--:|:----:|:-----------|:-----------
| 0x0   | M  | 1    | Memory     | accesses value from memory
| 0x1   | R  | 0    | Register   | accesses value from register
| 0x2   | O  | 1    | PC Offset  | PC offseted with the word
| 0x3   | C  | 0    | Carry flag | access the carry flag

### Mode indirection
If the indirect bit is set, the value from memory at mode's value is used instead.

### Mode value modifier
| Value | Cost | Name                 | Description
|:-----:|:----:|:---------------------|:-----------
| 0x0   | 0    | None/Positive offset | None, if O mode is used it <br>also means positive offset
| 0x1   | 2    | Negative offset      | Use negative offset? (only O)
| 0x2   | 1    | Postincrement        | Return value then increment
| 0x3   | 1    | Preincrement         | Increment then return value

## Opcodes
| Value | Cost | Name       | Behavior
|:-----:|:----:|:-----------|:--------
| 0o00  | 1    | `idle    ` | nothing
| 0o01  | 1    | `jump x  ` | `PC = X;`
| 0o02  | 2    | `call x  ` | `SP++;`<br>`S[SP] = PC;`<br>`PC = X;`
| 0o03  | 1    | `rtrn    ` | `PC = S[SP];`<br>`SP--;`
| ..    | ..   | ..         | future expansion
| 0o10  | 1    | `move x y` | move x to y<br>x is undefined now
| 0o11  | 2    | `copy x y` | copy x to y
| 0o12  | 2    | `swap x y` | swap x and y
| ..    | ..   | ..         | future expansion
| 0o20  | 1    | `ifeq x y` | `if(x == y) skip();`
| 0o21  | 1    | `ifnq x y` | `if(x != y) skip();`
| 0o22  | 2    | `ifgt x y` | `if(x >  y) skip();`
| 0o23  | 2    | `iflt x y` | `if(x <  y) skip();`
| 0o24  | 3    | `ifgq x y` | `if(x >= y) skip();`
| 0o25  | 3    | `iflq x y` | `if(x <= y) skip();`
| ..    | ..   | ..         | future expansion
| 0o30  | 1    | `bneg x y` | `y = !x`
| 0o31  | 1    | `bior x y` | `y \|= x`
| 0o32  | 1    | `band x y` | `y &= x`
| 0o33  | 1    | `bxor x y` | `y ^= x`
| 0o34  | 2    | `rshf x y` | `y >>= x`
| 0o35  | 2    | `lshf x y` | `y <<= x`
| ..    | ..   | ..         | future expansion
| 0o40  | 3    | `addt x y` | `y += x`<br>`if(overflows) C = true;`
| 0o41  | 3    | `subs x y` | `y -= x`<br>`if(underflows) C = true;`
| 0o42  | 6    | `mult x y` | `y *= x`<br>`if(overflows) C = true;`
| 0o43  | 6    | `divd x y` | `y /= x`<br>`if(rounds) C = true;`
| 0o44  | 8    | `modl x y` | `y %= x`
| ..    | ..   | ..         | future expansion
| 0o52  | 4    | `sdpi x y` | sends SDP input x<br>to `HW[y]`
| 0o52  | 4    | `sdpo x y` | reads SDP output y<br> from `HW[x]`
| 0o54  | 6    | `adpi x y` | sends ADP input x<br>to `HW[y]`
| 0o55  | 6    | `adpo x y` | reads ADP output y<br>from `HW[x]`
| ..    | ..   | ..         | future expansion

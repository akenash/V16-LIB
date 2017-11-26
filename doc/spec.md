# V16 CPU specifications

## General
  * 16 bit word - W
  * memory addresses are of one word (128KiB max)
  * 16x 1 word registers (`R[0]` .. `R[F]`)
    * `R[0]` is the iterator register `ITEREG`
    * `R[8]` is the arithmetic register `ARHREG`
    * `R[F]` is the hardware register `HWEREG`
  * 1 word program counter (`PC`)
  * 8 bit stack pointer (`SP`)
  * 1 bit carry flag (`CF`)
  * 256x 1 word stack (`S[0]` .. `S[FF]`)
  * hardware modules
  * little endian

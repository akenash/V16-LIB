# V16 ADP

ADP stands for `Asynchronous Data Protocol`
ADP enables data exchange for devices with different clock rates.

## Protocol
  * an ADP device should be able to receive inputs of one word
  * other devices should be able to wait for ADP device's output of one word
    * if there is no output, the wait is infinite
    * every output must be triggered by previous input
  * by default the ADP device will ignore all inputs

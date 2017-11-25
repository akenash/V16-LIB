# V16 SDP

SDP stands for `Synchronous Data Protocol`
SDP enables simple synchronous data exchange.

## Protocol
  * an SDP device should be able to receive inputs and outputs of one word.
  * an SDP device can exchange data only with one device at the same time
  * both devices will have to wait for each other during data exchange
  * the data exchange is simply setting a shared version of some data for both devices
    * that could mean either input or output 

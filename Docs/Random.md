# Random
The random number generator configuration. This is the simple get a single random 32 bit number. There are timing restrictions on how fast they can be acquired.
## STM32G474
### Address
0x50060800
## Clock enables
```
    RCC->AHB2ENR |= RCC_AHB2ENR_RNGEN;    // enable random clock
```
## Enable
```
    RNG->CR|=RNG_CR_RNGEN;                // enable random
```
## Read value
```
    uint32_t value;
    value = RNG->DR;
```

# Clock Tree
Clock tree for stm32G474 running at 170 MHz.
## STM32G474

### ADDRESS
| Port | Address |
| --- | ----------- |
| CRS | 0x40002000 |
| IWDG | 0x40003000 |
| PWR | 0x40007000 |
| RCC | 0X40021000 |
| SYSCFG | 0x40010000 |
| TAMP | 0x40002400 |
| WWDG | 0x40002C00 |

SYSCFG-> 0x00000000;    // FB_MODE = 0, Flash Bank 1
                        // MEM_MODE = 0, Main Flash memory

PWR->CR5 =& ~(PWR_CR5_R1MODE);  // Main regulator in range 1 boost mode

RCC->CR = 0x03030500;       // PLLON = PLL ON
                            // HSEON = HSE oscillator ON
                            // HSION = HSI16 clock enable
RCC->ICSCR = 0x40940000;    // HSITRIM[6:0] = 0x40 default
                            // HSICAL[7:0] = 0x94
RCC->CFGR = 0x0000000F;     // SW[1:0] = 0x11
RCC->PLLCFGR = 0x11005513;  // PLLPDIV[4:0] = 0x2
                            // PLLR[1:0] = 0
                            // PLLREN = 1
                            // PLLQ[1:0] = 0
                            // PLLQEN = 0
                            // PLLP = 0 
                            // PLLPEN = 0
                            // PLLN[6:0] = 0x55
                            // PLLM[3:0] = 1
                            // PLLSRC[1:0] = 3
RCC->CIER = 0x00000000;
RCC->CIFR = 0x00000000;
RCC->CICR = 0x00000000;
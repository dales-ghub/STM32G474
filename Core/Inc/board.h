#ifndef __BOARD_H
#define __BOARD_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"
#include "stm32g4xx_hal.h"

#define BOOT0_Pin GPIO_PIN_8
#define C_RESET_Pin GPIO_PIN_15
#define KEY_Pin GPIO_PIN_13
#define LED_Pin GPIO_PIN_6
#define TEST_Out GPIO_PIN_9

void board_gpio_init(void);
uint8_t KEY_Pin_getstate(void);
void LED_Pin_toggle(void);
void LED_Pin_set(uint8_t set);

void IWD_Init(void);
void IWD_Tickle(void);
void MX_ADC1_Inita(void);
void MX_COMP5_Init(void);
void RND_Init(void);
void SystemClock_Config(void);
void WWDG_Init(void);
void WWDG_Tickle(void);

#ifdef __cplusplus
}
#endif

#endif
// RCC 0x40021000
    // AHB1RSTR AHB1 peripheral reset register [0x28] 0x00000000
        // CRCRST: CRC reset
        // FLASHRST: Flash memory interface reset
        // FMACRST: Set and cleared by software
        // CORDICRST: Set and cleared by software
        // DMAMUX1RST: Set and cleared by software.
        // DMA2RST: DMA2 reset
        // DMA1RST: DMA1 reset
    // AHB2RSTR AHB2 peripheral reset register [0x2C] 0x00000000
        // RNGRST: RNG reset
        // AESRST: AESRST reset
        // DAC4RST: DAC4 reset
        // DAC3RST: DAC3 reset
        // DAC2RST: DAC2 reset
        // DAC1RST: DAC1 reset
        // ADC345RST: ADC345 reset
        // ADC12RST: ADC12 reset
        // GPIOGRST: IO port G reset
        // GPIOFRST: IO port F reset
        // GPIOERST: IO port E reset
        // GPIODRST: IO port D reset
        // GPIOCRST: IO port C reset
        // GPIOBRST: IO port B reset
        // GPIOARST: IO port A reset
    // AHB3RSTR AHB3 peripheral reset register [0x30] 0x00000000
        // QSPIRST: QUADSPI reset
        // FMCRST: Flexible static memory controller reset
    // APB1RSTR1 APB1 peripheral reset register 1 [0x38]
        // LPTIM1RST: Low Power Timer 1 reset
        // I2C3RST: I2C3 reset
        // PWRRST: Power interface reset
        // FDCANRST: FDCAN reset
        // USBRST: USB device reset
        // I2C2RST: I2C2 reset
        // I2C1RST: I2C1 reset
        // UART5RST: UART5 reset
        // UART4RST: UART4 reset
        // USART3RST: USART3 reset
        // USART2RST: USART2 reset
        // SPI3RST: SPI3 reset
        // SPI2RST: SPI2 reset
        // CRSRST: CRS reset
        // TIM7RST: TIM7 timer reset
        // TIM6RST: TIM6 timer reset
        // TIM5RST: TIM5 timer reset
        // TIM4RST: TIM3 timer reset
        // TIM3RST: TIM3 timer reset
        // TIM2RST: TIM2 timer reset
    // APB1RSTR2 APB1 peripheral reset register 2 [0x3C] 0x00000000
        // UCPD1RST: UCPD1 reset
        // I2C4RST: I2C4 reset
        // I2C4RST: I2C4 reset
    // APB2RSTR APB2 peripheral reset register [0x40] 0x00000000
        // HRTIM1RST: HRTIM1 reset
        // SAI1RST: Serial audio interface 1 (SAI1) reset
        // TIM20RST: TIM20 reset
        // TIM17RST: TIM17 timer reset
        // TIM16RST: TIM16 timer reset
        // TIM15RST: TIM15 timer reset
        // SPI4RST: SPI4 reset
        // USART1RST: USART1 reset
        // TIM8RST: TIM8 timer reset
        // SPI1RST: SPI1 reset
        // TIM1RST: TIM1 timer reset
        // SYSCFGRST: SYSCFG + COMP + OPAMP + VREFBUF reset
    // AHB1ENR AHB1 peripheral clock enable register [0x48] 0x00000107
        // CRCEN: CRC clock enable
        // FLASHEN: Flash memory interface clock enable = 1
        // FMACEN: FMAC enable
        // CORDICEN: CORDIC clock enable
        // DMAMUX1EN: DMAMUX1 clock enable = 1
        // DMA2EN: DMA2 clock enable = 1
        // DMA1EN: DMA1 clock enable = 1
    // AHB2ENR AHB2 peripheral clock enable register [0x4C]
        // RNGEN: RNG enable
        // AESEN: AES clock enable
        // DAC4EN: DAC4 clock enable
        // DAC3EN: DAC3 clock enable
        // DAC2EN: DAC2 clock enable
        // DAC1EN: DAC1 clock enable
        // ADC345EN: ADC345 clock enable
        // ADC12EN: ADC12 clock enable
        // GPIOGEN: IO port G clock enable
        // GPIOFEN: IO port F clock enable
        // GPIOEEN: IO port E clock enable
        // GPIODEN: IO port D clock enable
        // GPIOCEN: IO port C clock enable
        // GPIOBEN: IO port B clock enable
        // GPIOAEN: IO port A clock enable
    // AHB3ENR AHB3 peripheral clock enable register
        // QSPIEN: QUADSPI memory interface clock enable
        // FMCEN: Flexible static memory controller clock enable
    // APB1ENR1 APB1 peripheral clock enable register 1 [0x58]
        // LPTIM1EN: Low power timer 1 clock enable
        // I2C3EN: I2C3 clock enable
        // PWREN: Power interface clock enable
        // FDCANEN: FDCAN clock enable
        // USBEN: USB device clock enable
        // I2C2EN: I2C2 clock enable
        // I2C1EN: I2C1 clock enable
        // UART5EN: UART5 clock enable
        // UART4EN: UART4 clock enable
        // USART3EN: USART3 clock enable
        // USART2EN: USART2 clock enable
        // SPI3EN: SPI3 clock enable
        // SPI2EN: SPI2 clock enable
        // WWDGEN: Window watchdog clock enable
        // RTCAPBEN: RTC APB clock enable
        // CRSEN: CRS Recovery System clock enable
        // TIM7EN: TIM7 timer clock enable
        // TIM6EN: TIM6 timer clock enable
        // TIM5EN: TIM5 timer clock enable
        // TIM4EN: TIM4 timer clock enable
        // TIM3EN: TIM3 timer clock enable
        // TIM2EN: TIM2 timer clock enable
    // APB1ENR2 APB1 peripheral clock enable register 2 [0x5C]
        // UCPD1EN: UCPD1 clock enable
        // I2C4EN: I2C4 clock enable
        // LPUART1EN: Low power UART 1 clock enable
    // APB2ENR APB2 peripheral clock enable register [0x60]
        // HRTIM1EN: HRTIM1 clock enable
        // SAI1EN: SAI1 clock enable
        // TIM20EN: TIM20 timer clock enable
        // TIM17EN: TIM17 timer clock enable
        // TIM16EN: TIM16 timer clock enable
        // TIM15EN: TIM15 timer clock enable
        // SPI4EN: SPI4 clock enable
        // USART1EN: USART1clock enable
        // TIM8EN: TIM8 timer clock enable
        // SPI1EN: SPI1 clock enable
        // TIM1EN: TIM1 timer clock enable
        // SYSCFGEN: SYSCFG + COMP + VREFBUF + OPAMP clock enable
    // AHB1SMENR AHB1 peripheral clocks enable in Sleep and Stop [0x68]
        // CRCSMEN: CRC clocks enable during Sleep and Stop modes
        // SRAM1SMEN: SRAM1 interface clocks enable during Sleep and Stop modes
        // FLASHSMEN: Flash memory interface clocks enable
        // FMACSMEN: FMACSM clock enable.
        // CORDICSMEN: CORDICSM clock enable.
        // DMAMUX1SMEN: DMAMUX1 clock enable during Sleep and Stop modes.
        // DMA2SMEN: DMA2 clocks enable during Sleep and Stop modes
        // DMA1SMEN: DMA1 clocks enable during Sleep and Stop modes
    // AHB2SMENR AHB2 peripheral clocks enable in Sleep and Stop [0x6C]
        // AHB3SMENR AHB3 peripheral clocks enable in Sleep and Stop [0x6C]
    // AHB3SMENR AHB3 peripheral clocks enable in Sleep and Stop [0x70]
        // APB1 peripheral clocks enable in Sleep and Stop
        // FMCSMEN: Flexible static memory controller clocks enable
    // APB1SMENR1 APB1 peripheral clocks enable in Sleep and Stop [0x78]
        // LPTIM1SMEN: Low power timer 1 clocks enable during Sleep and Stop modes
        // I2C3SMEN: I2C3 clocks enable during Sleep and Stop modes
        // PWRSMEN: Power interface clocks enable during Sleep and Stop modes
        // FDCANSMEN: FDCAN clocks enable during Sleep and Stop modes
        // USBSMEN: USB device clocks enable during Sleep and Stop modes
        // I2C2SMEN: I2C2 clocks enable during Sleep and Stop modes
        // I2C1SMEN: I2C1 clocks enable during Sleep and Stop modes
        // UART5SMEN: UART5 clocks enable during Sleep and Stop modes
        // UART4SMEN: UART4 clocks enable during Sleep and Stop modes
        // USART3SMEN: USART3 clocks enable during Sleep and Stop modes
        // USART2SMEN: USART2 clocks enable during Sleep and Stop modes
        // SPI3SMEN: SPI3 clocks enable during Sleep and Stop modes
        // SPI2SMEN: SPI2 clocks enable during Sleep and Stop modes
        // WWDGSMEN: Window watchdog clocks enable during Sleep and Stop modes
        // RTCAPBSMEN: RTC APB clock enable during Sleep and Stop modes
        // CRSSMEN: CRS timer clocks enable during Sleep and Stop modes
        // TIM7SMEN: TIM7 timer clocks enable during Sleep and Stop modes
        // TIM6SMEN: TIM6 timer clocks enable during Sleep and Stop modes
        // TIM5SMEN: TIM5 timer clocks enable during Sleep and Stop modes
        // TIM4SMEN: TIM4 timer clocks enable during Sleep and Stop modes
        // TIM3SMEN: TIM3 timer clocks enable during Sleep and Stop modes
        // TIM2SMEN: TIM2 timer clocks enable during Sleep and Stop modes
    // APB1SMENR2 APB1 peripheral clocks enable in Sleep and Stop [0x7C]
        // UCPD1SMEN: UCPD1 clocks enable during Sleep and Stop modes
        // I2C4SMEN: I2C4 clocks enable during Sleep and Stop modes
        // LPUART1SMEN: Low power UART 1 clocks enable during Sleep and Stop modes
    // APB2SMENR APB2 peripheral clocks enable in Sleep and Stop [0x80]
        // HRTIM1SMEN: HRTIM1 timer clocks enable during Sleep and Stop modes
        // SAI1SMEN: SAI1 clocks enable during Sleep and Stop modes
        // TIM20SMEN: TIM20 timer clocks enable during Sleep and Stop modes
        // TIM17SMEN: TIM17 timer clocks enable during Sleep and Stop modes
        // TIM15SMEN: TIM15 timer clocks enable during Sleep and Stop modes
        // SPI4SMEN: SPI4 timer clocks enable during Sleep and Stop modes
        // USART1SMEN: USART1clocks enable during Sleep and Stop modes
        // TIM8SMEN: TIM8 timer clocks enable during Sleep and Stop modes
        // SPI1SMEN: SPI1 clocks enable during Sleep and Stop modes
        // TIM1SMEN: TIM1 timer clocks enable during Sleep and Stop modes
        // SYSCFGSMEN: SYSCFG + COMP + VREFBUF + OPAMP clocks enable
    // CCIPR Peripherals independent clock configuration register [0x88]
        // ADC345SEL[1:0]: ADC3/4/5 clock source selection
        // ADC12SEL[1:0]: ADC1/2 clock source selection
        // CLK48SEL[1:0]: 48 MHz clock source selection
        // FDCANSEL[1:0]: clock source selection
        // I2S23SEL[1:0]: clock source selection
        // SAI1SEL[1:0]: clock source selection
        // LPTIM1SEL[1:0]: Low power timer 1 clock source selection
        // I2C3SEL[1:0]: I2C3 clock source selection
        // I2C2SEL[1:0]: I2C2 clock source selection
        // I2C1SEL[1:0]: I2C1 clock source selection
        // LPUART1SEL[1:0]: LPUART1 clock source selection
        // UART5SEL[1:0]: UART5 clock source selection
        // UART4SEL[1:0]: UART4 clock source selection
        // USART3SEL[1:0]: USART3 clock source selection
        // USART2SEL[1:0]: USART2 clock source selection
        // USART1SEL[1:0]: USART1 clock source selection
    // BDCR RTC domain control register [0x90]
        // LSCOSEL: Low speed clock output selection
        // LSCOEN: Low speed clock output enable
        // BDRST: RTC domain software reset
        // RTCEN: RTC clock enable
        // RTCSEL[1:0]: RTC clock source selection
        // LSECSSD: CSS on LSE failure Detection
        // LSECSSON: CSS on LSE enable
        // LSEDRV[1:0]: LSE oscillator drive capability
        // LSEBYP: LSE oscillator bypass
        // LSERDY: LSE oscillator ready
        // LSEON: LSE oscillator enable
    // CSR Control status register [0x94]
        // LPWRRSTF: Low-power reset flag
        // WWDGRSTF: Window watchdog reset flag
        // IWDGRSTF: Independent window watchdog reset flag
        // SFTRSTF: Software reset flag
        // BORRSTF: BOR flag
        // PINRSTF: Pin reset flag
        // OBLRSTF: Option byte loader reset flag
        // RMVF: Remove reset flag
        // LSIRDY: LSI oscillator ready
        // LSION: LSI oscillator enable
    // CRRCR Clock recovery RC register [0x98]
        // HSI48CAL[8:0]: HSI48 clock calibration
        // HSI48RDY: HSI48 clock ready flag
        // HSI48ON: HSI48 clock enable
    // CCIPR2 Peripherals independent clock configuration register [0x9C]
        // QSPISEL[1:0]: QUADSPI clock source selection
        // I2C4SEL[1:0]: I2C4 clock source selection


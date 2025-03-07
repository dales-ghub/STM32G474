#include "main.h"
#include "stm32g4xx_hal.h"

#define LPUART1_RX_SIZE 32
#define LPUART1_TX_SIZE 40
#define USART1_RX_SIZE 32
#define USRART1_TX_SIZE 32

void LPUART1_Init(uint32_t baud);
void LPUART1_Tx(char *lpuart1_txData, uint32_t lpuart1_txCNT);
void LPUART1d_Init(uint32_t baud);
void LPUART1d_Tx(char *lpuart1_txData, uint32_t lpuart1_txCNT);
void USART1_Init(uint32_t baud);
void USART1d_Init(uint32_t baud);
void USART1_Tx(char *s, uint32_t CNT);
void USART1d_Tx(char *s, uint32_t CNT);
void USART3d_Init(uint32_t baud);
void USART3d_Tx(char *usart3_txData, uint32_t txCNT);


#include <stdint.h>
#include "adc.h"
#include "main.h"
#include "i2c.h"
#include "rtc.h"
#include "usbd_cdc_if.h"
void adcRd(char*s);
void alarmA(char*s);
void alarmB(char*s);
void count(char*s);
void data(char*s);
void debug(char*s);
void dump(char*s);
void info(char*s);
void i2c1(char*s);
void help(char*s);
void pwm(char*s);
void random1(char*s);
void rtc(char*s);
void SetDate_(char*s);
void SetTim(char*s);
void testIRQ(char*s);
void tim4(char*s);

typedef struct MENU_STRUCT 
  {
  char item[12];          // String for command
  uint32_t itemLen;       // length of string to compare to
  void (*fun_ptr)(char*); // function to call
  } MENU_STRUCT;

MENU_STRUCT const menus[] = {
    { "help", 4, help},         // list commands
    { "adc", 3, adcRd},         // adc 1 reading
    { "alarmA", 6, alarmA},     // set alarmA
    { "alarmB", 6, alarmB},     // set alarmB
    { "count", 5, count},       //
    { "data", 4, data},
    { "debug", 5, debug},       // read 3 registers
    { "dump", 4, dump},
    { "info", 4, info},         // compile date
    { "i2c", 3, i2c1},          // itc info
    { "pwm", 3, pwm},           // set pwm1 width
    { "rand", 4, random1},      // random number
    { "rtc", 3, rtc},           // real time clock
    { "reSET", 5, testIRQ},     // reset
    { "SetDate", 7, SetDate_},  // set date
    { "STime", 5, SetTim},      // set time
    { "tim4", 4, tim4},         // set pwm4 period
    };
static int menu_size = sizeof (menus) / sizeof (menus[0]);

static char menu_str[24];
static uint32_t menu_ptr = 0;
uint32_t menu_cntr_1 = 0;
uint32_t menu_cntr_2 = 0;

void Menu(uint8_t* Buf, uint32_t Len)
  {
  uint32_t error, i;
  menu_str[23] = 0;
  error = 0;
  
  for(i = 0; i < Len; i++)
    switch (Buf[i])
      {
      case '\b':    // back space
        if(menu_ptr > 0)
          menu_ptr--;
        break;
      case '\n':    // newline
      case '\r':    // return
        error = 1;
        menu_str[menu_ptr] = 0;
        for(i = 0; i < menu_size; i++)    // check each command
          if (strncmp(menu_str, menus[i].item, menus[i].itemLen) == 0)
            {     // do the command when compare equal
            menus[i].fun_ptr(&menu_str[menus[i].itemLen]);
            error = 0;  // no error
            }
        menu_ptr = 0; // reset menu pointer
        break;
      default:  // next character
        menu_str[menu_ptr++] = Buf[i];
        if(menu_ptr > 23) // did  not find a return or newline
          {
          error = 1;    // flag an error
          menu_ptr = 0; // reset menu pointer
          }
        break;
      }
  if(error)
    {
    CDC_Transmit_FS(Buf, Len);  // error
    }
  }

#define AVG_SLOPE 232.558
#define V25 1.43  
void adcRd(char*s)
  {
  uint8_t text[32];
  int text_length;
  uint32_t ADCValue;
  int n;
  float tempRd;
  n = atoi(s);
  switch(n)
    {
    default:
      text_length = sprintf((char *) &text, "Error: %d\n", n);
      break;
    case 1:
      text_length = sprintf((char *) &text, "adc1: %d\n", ADC_rd(1));
      break;
    case 2:
      text_length = sprintf((char *) &text, "adc2: %d\n",ADC_rd(2));
      break;
    case 3:
      text_length = sprintf((char *) &text, "adc3: %d\n",ADC_rd(3));
      break;
    case 4:
      text_length = sprintf((char *) &text, "adc4: %d\n",ADC_rd(4));
      break;
    case 5:
      ADCValue = ADC5->DR;
      tempRd = 100.0 / (*TEMPSENSOR_CAL2_ADDR - *TEMPSENSOR_CAL1_ADDR) * ((uint16_t)ADCValue - *TEMPSENSOR_CAL1_ADDR) + 30.0; 
      text_length = sprintf((char *) &text, "adc5: %ld %.1f\n", ADCValue, tempRd);
      ADC5->JSQR &= ~(3 << ADC_JSQR_JEXTEN_Pos);
      ADC5->CR |= ADC_CR_ADSTART | ADC_CR_ADEN;
      break;
    case 10:
        text_length = sprintf((char *) &text, "CALt: %d %d\n", *TEMPSENSOR_CAL1_ADDR, *TEMPSENSOR_CAL2_ADDR);
        break;
    case 11:
        text_length = sprintf((char *) &text, "CAL1: %lX %lX\n", ADC1->CALFACT, ADC1->GCOMP);
        break;
    case 12:
        text_length = sprintf((char *) &text, "CAL2: %lX %lX\n", ADC2->CALFACT, ADC2->GCOMP);
        break;
    case 13:
        text_length = sprintf((char *) &text, "CAL3: %lX %lX\n", ADC3->CALFACT, ADC3->GCOMP);
        break;
    case 14:
        text_length = sprintf((char *) &text, "CAL4: %lX %lX\n", ADC4->CALFACT, ADC4->GCOMP);
        break;
    case 15:
        text_length = sprintf((char *) &text, "CAL5: %lX %lX\n", ADC5->CALFACT, ADC5->GCOMP);
        break;
    }
  CDC_Transmit_FS(text, text_length);
  }

void alarmA(char*s)
    {
    uint8_t text[32];
    int text_length;
    TIME_VAL time_val;

    timeVal(s, &time_val);
    if(time_val.error)
        text_length = sprintf((char *) &text, "Error: %s %d\n", s, time_val.su); 
    else
        {
        text_length = sprintf((char *) &text, "AlarmA: %d%d:%d%d:%d%d\n",
                time_val.hd, 
                time_val.hu, 
                time_val.md, 
                time_val.mu, 
                time_val.sd, 
                time_val.su);
        setAlarmA(&time_val);
        }
    CDC_Transmit_FS(text, text_length);
    }
  
void alarmB(char*s)
    {
    uint8_t text[32];
    int text_length;
    TIME_VAL time_val;

    timeVal(s, &time_val);
    if(time_val.error)
        text_length = sprintf((char *) &text, "Error: %s %d\n", s, time_val.su); 
    else
        {
        text_length = sprintf((char *) &text, "AlarmA: %d%d:%d%d:%d%d\n",
                time_val.hd, 
                time_val.hu, 
                time_val.md, 
                time_val.mu, 
                time_val.sd, 
                time_val.su);
        setAlarmB(&time_val);
        }
    CDC_Transmit_FS(text, text_length);
    }
  
void count(char*s)
    {
    uint8_t text[32];
    int text_length;
    extern uint32_t menu_cntr_1, menu_cntr_2;

    text_length = sprintf((char *) &text, "count: %ld %ld\n",
        menu_cntr_1, 
        menu_cntr_2);
    CDC_Transmit_FS(text, text_length);
    }

void data(char*s)
    {
    extern uint32_t _binary_blob_bin_size;
    extern unsigned char _binary_blob_bin_start;
    int text_length = (int) &_binary_blob_bin_size;
    CDC_Transmit_FS((unsigned char *)&_binary_blob_bin_start, text_length);
    }

void debug(char*s)
    {
    uint8_t text[40];
    int text_length;
    extern char lpuart1_rxData[];
    extern uint32_t lpuart1_rxPtr;
    text_length = sprintf((char *) &text, "Debug: %8lX %8lX %8lX\n",
        (uint32_t)DMAMUX1_Channel0, lpuart1_rxPtr, (uint32_t)lpuart1_rxData);
    CDC_Transmit_FS(text, text_length);
    }

void dump(char*s)
    {
    char text[4*16*8], str[11];
    uint32_t addr, *ptr;
    uint16_t i, j;
    sscanf(s, "%lx", &addr);
    ptr = (uint32_t *)addr;
    text[0] = 0;
    for (i = 0; i < 4; i++)
        {
        sprintf((char *) &str, "%08lX: ", (uint32_t)ptr);
        strcat(text, str);
        for (j = 0; j < 3; addr++, j++)
            {
            sprintf((char *) &str, "%08lX ", *ptr++); 
            strcat(text, str);
            }
        sprintf((char *) &str, "%08lX\r\n", *ptr++);
        strcat(text, str);
        }
    strcat(text,"\r\n");
    CDC_Transmit_FS((uint8_t*) &text, strlen(text));
    }
  
void help(char*s)
    {
    char text[sizeof (menus)];
    int i;
    strcpy(text,"Help:\n");
    for(i = 0; i < menu_size; i++)
        {
        strcat(text,"\t");
        strcat(text, menus[i].item);
        strcat(text,"\n");
        }
    CDC_Transmit_FS((uint8_t*) &text, strlen(text));
    }

void info(char*s)
    {
    uint8_t text[32];
    int text_length;
    extern uint32_t resetFlags;
    text_length = sprintf((char *) &text, "info: %lx %s %s\n", 
        resetFlags, __DATE__, __TIME__);
    CDC_Transmit_FS(text, text_length);
  }

void i2c1(char*s)
    {
    uint8_t text[32];
    int text_length;
    extern I2C_struct I2C1data;
    
    text_length = sprintf((char *) &text, "i2c1\n data: %p\nstatus: %X\n",
            I2C1data.Ptr, I2C1data.Status);
    CDC_Transmit_FS(text, text_length);
    }
    
void pwm(char*s)
    {
    uint8_t text[32];
    int text_length;
    int n,val;

    sscanf(s, "%d %d", &n, &val);
    if(val > 0 && val < 999)
        switch(n)
            {
            default:
                text_length = sprintf((char *) &text, "Chan Error\n");
                break;
            case 1: 
                TIM1->CCR1 = val;
                text_length = sprintf((char *) &text, "pwm1: %s\n", s);
                break;
            case 2: 
                TIM1->CCR1 = val;
                text_length = sprintf((char *) &text, "pwm1: %s\n", s);
                break;
            case 3: 
                TIM1->CCR1 = val;
                text_length = sprintf((char *) &text, "pwm1: %s\n", s);
                break;
            }
    else
        text_length = sprintf((char *) &text, "error: %s\n", s);
    CDC_Transmit_FS(text, text_length);
    }

void random1(char*s)
  {
  uint8_t text[32];
  int text_length;
  text_length = sprintf((char *) &text, "random: %ld\n", RNG->DR);
  CDC_Transmit_FS(text, text_length);
  }

void rtc(char*s)
  {
  uint8_t text[32];
  int text_length;
  uint32_t myDate, myTime;
  myTime = RTC->TR;
  myDate = RTC->DR;
  int dow = (myDate >>RTC_DR_WDU_Pos) & 7;
  int year = 2000 + 
          (((myDate>>RTC_DR_YT_Pos) & 0xf) * 10) +
           ((myDate >> RTC_DR_YU_Pos) & 0xf);
  int month = (((myDate >> RTC_DR_MT_Pos) & 1) * 10) +
               ((myDate >> RTC_DR_MU_Pos) & 0xf);
  int day = (((myDate >> RTC_DR_DT_Pos) & 3) * 10) + 
             (myDate & 0xf);
  int hour = (((myTime >> RTC_TR_HT_Pos) & 7) * 10) +
              ((myTime >> RTC_TR_HU_Pos) & 0xf);
  int minute = (((myTime >> RTC_TR_MNT_Pos) & 0xf) * 10) + 
                ((myTime >> RTC_TR_MNU_Pos) & 0xf);
  int second = (((myTime >> RTC_TR_ST_Pos) & 0xf) * 10) + 
                ((myTime >> RTC_TR_SU_Pos) & 0xf);
  text_length = sprintf((char *) &text, "rtc: %d-%d-%d %d %d:%02d:%02d\n", year, month, day, dow, hour, minute, second);
  CDC_Transmit_FS(text, text_length);
  }

void SetDate_(char*s)
    {
    uint8_t text[64];
    int text_length;
    DATE_VAL date_val;
    
    dateVal(s, &date_val);
    if(date_val.error)
        {
        text_length = sprintf((char *) &text, "SetDate YY-MM-DD; %s\n", s); 
        CDC_Transmit_FS(text, text_length);
        }
    else
        {     // 2024-1-1 Mon = 1, SUN = 7
        SetRTCdate(&date_val);
        text_length = sprintf((char *) &text, 
            "date: %d 20%d%d-%d%d-%d%d\n", 
            date_val.dow, 
            date_val.yd, 
            date_val.yu, 
            date_val.md, 
            date_val.mu, 
            date_val.dd, 
            date_val.du);
        CDC_Transmit_FS(text, text_length);
        }
    }

void SetTim(char*s)
  {
  uint8_t text[60];
  int text_length;
  TIME_VAL time_val;
  timeVal(s, &time_val);
  if(time_val.error)
    {
    text_length = sprintf((char *) &text, 
            "STime HH:MM:SS:%d %d%d:%d%d:%d%d\n", 
            time_val.error, 
            time_val.hd, 
            time_val.hu, 
            time_val.md, 
            time_val.mu, 
            time_val.sd, 
            time_val.su); 
    }
  else
    {
    SetRTCtime(&time_val);
    text_length = sprintf((char *) &text, 
            "time: %d%d:%d%d:%d%d\n", 
            time_val.hd, 
            time_val.hu, 
            time_val.md, 
            time_val.mu, 
            time_val.sd, 
            time_val.su); 
    }
  CDC_Transmit_FS(text, text_length);
  }

void testIRQ(char*s)
  {
  uint32_t n = atoi(s);
  if(n < 18)
    {   // 8 = BOOT0, 13 = KEY_Pin
    EXTI->SWIER1 |= (1 << n);   // software interrupt 
    }
  SCB->CCR = (1 << SCB_CCR_USERSETMPEND_Pos);
//  NVIC->STIR = n;
  }
  
void tim4(char*s)
  {
  uint8_t text[32];
  int text_length;
  int val;
  
  val = atoi(s);
  if(val > 0 && val < 999)
    {
    TIM4->PSC = val;
    text_length = sprintf((char *) &text, "tim4: %s\n", s);
    }
  else
    text_length = sprintf((char *) &text, "error: %s\n", s);
  CDC_Transmit_FS(text, text_length);
  }

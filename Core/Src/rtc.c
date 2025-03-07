#include "rtc.h"

const uint16_t dayInMonths[14] =
  { 0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 274, 304, 335, 365};
const uint16_t dayInLeap[14] =
  { 0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 275, 305, 336, 366};
const char *dow_str[] = {"", "Mon", "Tu", "Wed", "Thur", "Fri", "Sat", "Sun"};
const char *month_str[] = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", 
                            "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

uint8_t getDOW(DATE_VAL * date_val)
    {
    uint8_t year;
    uint8_t month;
    uint16_t days = 5;
    year = date_val->yd * 10 + date_val->yu;
    if(year > 100)
        return(-1);
    days += (uint16_t)(year * 365.25);
    month = date_val->md * 10 + date_val->mu;
    if(year % 4)
        days += dayInLeap[month];
    else
        days += dayInLeap[month];
    days += date_val->dd * 10 + date_val->du;
    return((days % 7) + 1); 
    }
    
// RTC 0x40002800
void RTC_Init(void)
    {
    extern uint32_t resetFlags;

    PWR->CR1 |= PWR_CR1_DBP;  // enable writing to RTC
    RTC->WPR = 0xCA;          // unlock
    RTC->WPR = 0x53;          // unlock
    RCC->BDCR |= (RCC_BDCR_RTCSEL_0 | RCC_BDCR_RTCEN | RCC_BDCR_LSEON); // LSE
    RTC->ICSR |= RTC_ICSR_INIT; // Stop RTC to update
    while((RTC->ICSR & RTC_ICSR_INITF) == 0)
        ;
    RTC->PRER = 0x7F << RTC_PRER_PREDIV_A_Pos; 
    RTC->PRER |= 0xFF << RTC_PRER_PREDIV_S_Pos;
    if ((resetFlags & RCC_CSR_LPWRRSTF) == RCC_CSR_LPWRRSTF)
        {   // Power on reset -> load values into time and date
        RTC->TR = (0 << RTC_TR_HT_Pos) |
                  (9 << RTC_TR_HU_Pos) | 
                  (3 << RTC_TR_MNT_Pos) | 
                  (2 << RTC_TR_MNU_Pos) | 
                  (3 << RTC_TR_ST_Pos) | 
                  (1 << RTC_TR_SU_Pos); // Set time
        RTC->DR = (2 << RTC_DR_YT_Pos) |
                  (5 << RTC_DR_YU_Pos) | 
                  (7 << RTC_DR_WDU_Pos) | 
                  (0 << RTC_DR_MT_Pos) | 
                  (2 << RTC_DR_MU_Pos) | 
                  (1 << RTC_DR_DT_Pos) | 
                  (6 << RTC_DR_DU_Pos); // Set date
        }
    RTC->SCR = RTC_SCR_CITSF |
               RTC_SCR_CTSOVF |
               RTC_SCR_CTSF |
               RTC_SCR_CWUTF |
               RTC_SCR_CALRBF |
               RTC_SCR_CALRAF;          // clear all flags
    RTC->CR |= RTC_CR_OUT2EN;           // output enabled
    RTC->ICSR &= ~RTC_ICSR_INIT;        // start RTC
    NVIC_EnableIRQ(RTC_Alarm_IRQn);
    }
    
void setAlarmA(TIME_VAL * time_val)
    {
    RTC->CR &= ~(RTC_CR_ALRAIE | RTC_CR_ALRAE); // clear enable and interrupt
    RTC->ALRMAR = RTC_ALRMAR_MSK4;                      // mask of days
    RTC->ALRMAR |= (time_val->hd << RTC_TR_HT_Pos) |
                   (time_val->hu << RTC_TR_HU_Pos) |     // set hours
                   (time_val->md << RTC_TR_MNT_Pos) |
                   (time_val->mu << RTC_TR_MNU_Pos) |    // set minutes
                   (time_val->sd << RTC_TR_ST_Pos) |
                   (time_val->su << RTC_TR_SU_Pos);      // Set seconds
    RTC->CR |= RTC_CR_ALRAIE | RTC_CR_ALRAE;            // enable
    NVIC_EnableIRQ(RTC_Alarm_IRQn);
    RTC->SCR |= RTC_SCR_CALRAF;
    EXTI->IMR1 |= EXTI_IMR1_IM17;
    EXTI->RTSR1 |= EXTI_RTSR1_RT17;
    }

void setAlarmB(TIME_VAL * time_val)
    {
    RTC->CR &= ~(RTC_CR_ALRBIE | RTC_CR_ALRBE); // clear enable and interrupt
    RTC->ALRMBR = RTC_ALRMBR_MSK4;              // mask of days
    RTC->ALRMBR |= (time_val->hd << RTC_TR_HT_Pos) |
                   (time_val->hu << RTC_TR_HU_Pos) |     // set hours
                   (time_val->md << RTC_TR_MNT_Pos) |
                   (time_val->mu << RTC_TR_MNU_Pos) |    // set minutes
                   (time_val->sd << RTC_TR_ST_Pos) |
                   (time_val->su << RTC_TR_SU_Pos);      // Set seconds
    RTC->ALRMASSR = 0;
    RTC->CR |= RTC_CR_ALRBIE | RTC_CR_ALRBE;
    RTC->SCR |= RTC_SCR_CALRBF;
    EXTI->IMR1 |= EXTI_IMR1_IM17;
    EXTI->RTSR1 |= EXTI_RTSR1_RT17;
    }

void SetRTCdate(DATE_VAL * date_val)
    {     // 2024-1-1 Mon = 1, SUN = 7
    PWR->CR1 |= PWR_CR1_DBP;  // enable writing to RTC
    RTC->WPR = 0xCA;          // unlock
    RTC->WPR = 0x53;          // unlock
    RTC->ICSR |= RTC_ICSR_INIT;
    while((RTC->ICSR & RTC_ICSR_INITF) == 0)
        ;
    RTC->CR |= RTC_CR_BYPSHAD;
    RTC->DR = (date_val->yd << RTC_DR_YT_Pos) |
              (date_val->yu << RTC_DR_YU_Pos) |
              (date_val->dow << RTC_DR_WDU_Pos) |
              (date_val->md << RTC_DR_MT_Pos) | 
              (date_val->mu << RTC_DR_MU_Pos) | 
              (date_val->dd << RTC_DR_DT_Pos) | 
              (date_val->du << RTC_DR_DU_Pos);     // Set date
    RTC->ICSR &= ~RTC_ICSR_INIT;
    }

void SetRTCtime(TIME_VAL * time_val)
    {
    PWR->CR1 |= PWR_CR1_DBP;  // enable writing to RTC
    RTC->WPR = 0xCA;          // unlock
    RTC->WPR = 0x53;          // unlock
    RTC->ICSR |= RTC_ICSR_INIT;
    while((RTC->ICSR & RTC_ICSR_INITF) == 0)
        ;
    RTC->TR = (time_val->hd << RTC_TR_HT_Pos) |
              (time_val->hu << RTC_TR_HU_Pos) |
              (time_val->md << RTC_TR_MNT_Pos) | 
              (time_val->mu << RTC_TR_MNU_Pos) | 
              (time_val->sd << RTC_TR_ST_Pos) | 
              (time_val->su << RTC_TR_SU_Pos); // Set time
    RTC->ICSR &= ~RTC_ICSR_INIT;
    }

void dateVal(char*s, DATE_VAL * date_val)
    {
    date_val->error = 0;

    sscanf(s, "%d-%d-%d", &date_val->yu, &date_val->mu, &date_val->du);
    if(date_val->yu > 99)
        date_val->error = 1;
    date_val->yu %= 60;
    date_val->yd = date_val->yu / 10;
    date_val->yu %= 10;
    if((date_val->mu < 1) || (date_val->mu > 12))
        date_val->error = 1;
    date_val->md = date_val->mu / 10;
    date_val->mu %= 10;
    if(date_val->du < 1)
        date_val->error = 1;
    date_val->dd = date_val->du / 10;
    date_val->du = date_val->du%10;
    date_val->dow = getDOW(date_val);
    }
    
void timeVal(char*s, TIME_VAL * time_val)
    {
    time_val->error = 0;
    sscanf(s, "%d:%d:%d", &time_val->hu, &time_val->mu, &time_val->su);
    if(time_val->hu < 0)
        time_val->error = 1;
    time_val->hd = time_val->hu/10;
    time_val->hu %= 10;
    if(time_val->mu < 0)
        time_val->error = 1;
    time_val->md = time_val->mu/10;
    time_val->mu %= 10;
    if(time_val->su < 0)
        time_val->error = 1;
    time_val->sd = time_val->su/10;
    time_val->su %= 10;
    }


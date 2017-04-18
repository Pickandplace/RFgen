
#ifndef CONF_CLOCK_H_INCLUDED
#define CONF_CLOCK_H_INCLUDED

//Yeah, sure Atmel, it's a great idea to put the Xtal config in two separate files.
// External oscillator settings.
// Uncomment and set correct values if external oscillator is used.

// External oscillator frequency
#define BOARD_XOSC_HZ          12000000

// External oscillator type.
//!< External clock signal
#define BOARD_XOSC_TYPE        XOSC_TYPE_EXTERNAL
//!< 32.768 kHz resonator on TOSC
//#define BOARD_XOSC_TYPE        XOSC_TYPE_32KHZ
//!< 0.4 to 16 MHz resonator on XTALS
//#define BOARD_XOSC_TYPE        XOSC_TYPE_XTAL

// External oscillator startup time
#define BOARD_XOSC_STARTUP_US  5


//#define CONFIG_SYSCLK_SOURCE          SYSCLK_SRC_RC2MHZ
#define CONFIG_SYSCLK_SOURCE        SYSCLK_SRC_RC32MHZ
//#define CONFIG_SYSCLK_SOURCE        SYSCLK_SRC_RC32KHZ
//#define CONFIG_SYSCLK_SOURCE        SYSCLK_SRC_XOSC
//#define CONFIG_SYSCLK_SOURCE        SYSCLK_SRC_PLL

/* Fbus = Fsys / (2 ^ BUS_div) */
////#define CONFIG_SYSCLK_PSADIV          SYSCLK_PSADIV_2
////#define CONFIG_SYSCLK_PSBCDIV         SYSCLK_PSBCDIV_1_1

//#define CONFIG_PLL0_SOURCE          PLL_SRC_XOSC
//#define CONFIG_PLL0_SOURCE          PLL_SRC_RC2MHZ
//#define CONFIG_PLL0_SOURCE          PLL_SRC_RC32MHZ

/* Fpll = (Fclk * PLL_mul) / PLL_div */
#define CONFIG_PLL0_MUL             (32000000UL / BOARD_XOSC_HZ)
#define CONFIG_PLL0_DIV             1

/* External oscillator frequency range */
/** 0.4 to 2 MHz frequency range */
//#define CONFIG_XOSC_RANGE XOSC_RANGE_04TO2
/** 2 to 9 MHz frequency range */
//#define CONFIG_XOSC_RANGE XOSC_RANGE_2TO9
/** 9 to 12 MHz frequency range */
#define CONFIG_XOSC_RANGE XOSC_RANGE_9TO12
/** 12 to 16 MHz frequency range */
//#define CONFIG_XOSC_RANGE XOSC_RANGE_12TO16

/* DFLL autocalibration */
//#define CONFIG_OSC_AUTOCAL_RC2MHZ_REF_OSC  OSC_ID_RC32KHZ
//#define CONFIG_OSC_AUTOCAL_RC32MHZ_REF_OSC OSC_ID_XOSC

/* The following example clock configuration definitions can be used in XMEGA
 * devices that contain a USB controller. It configures the USB controller clock
 * source to use the internal (nominally) 32MHz RC oscillator, up-calibrated to
 * run at 48MHz via the periodic 1ms USB Start Of Frame packets sent by the
 * host. The USB controller requires 48MHz for Full Speed operation, or 6MHz
 * for USB Low Speed operation.
 *
 * Note that when the 32MHz RC oscillator is tuned to 48MHz, it cannot be used
 * directly as the system clock source; it must either be prescaled down to a
 * speed below the maximum operating frequency given in the datasheet, or an
 * alternative clock source (e.g. the internal 2MHz RC Oscillator, multiplied
 * to a higher frequency via the internal PLL module) must be used instead.
 */
 //#define CONFIG_USBCLK_SOURCE                USBCLK_SRC_RCOSC
 //#define CONFIG_OSC_RC32_CAL                 48000000UL
 //#define CONFIG_OSC_AUTOCAL_RC32MHZ_REF_OSC  OSC_ID_USBSOF

/* Use to enable and select RTC clock source */
//#define CONFIG_RTC_SOURCE           SYSCLK_RTCSRC_ULP
#define CONFIG_USBCLK_SOURCE     USBCLK_SRC_RCOSC
#define CONFIG_OSC_RC32_CAL      48000000UL

#define CONFIG_OSC_AUTOCAL_RC32MHZ_REF_OSC  OSC_ID_USBSOF

//#define CONFIG_SYSCLK_SOURCE     SYSCLK_SRC_PLL
#define CONFIG_SYSCLK_PSADIV     SYSCLK_PSADIV_1
#define CONFIG_SYSCLK_PSBCDIV    SYSCLK_PSBCDIV_1_1
#endif /* CONF_CLOCK_H_INCLUDED */

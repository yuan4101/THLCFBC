#include <xc.h>
#define delay_ms(x)	__delay_ms(x)
#define delay_us(x)	__delay_us(x)
#define delay_cycles(x) __delay32(x)

// End of Header file
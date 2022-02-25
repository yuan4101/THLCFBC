#ifndef CONFIG_H
#define	CONFIG_H

/**
 * Configures here the processor speed
 */
#define CONFIG_TIMING_MAIN_CLOCK 2000000

/**
 * Configure here the registers and pins associated with the DHT11 sensor
 */
#define CONFIG_DHTLIB_OUTPIN		LATAbits.LATA0
#define CONFIG_DHTLIB_PORTPIN           PORTAbits.RA0
#define CONFIG_DHTLIB_TRIS		TRISAbits.TRISA0

#endif
// End of Header file
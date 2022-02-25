#include"DHTLib.h"
#define _XTAL_FREQ 8000000
/**
 * Buffer to store data from sensors
 */
unsigned char bits[5];

/*-------------------------------------------------------------*/
/*		Function prototypes	(this file only)	*/
/*-------------------------------------------------------------*/
static void dhtlib_start();

/*-------------------------------------------------------------*/
/*		API Functions Implementation			*/
/*-------------------------------------------------------------*/
void dhtlib_init()
{
	// Initialization just sets DHT11 pin as input
	dhtlib_setin();
}

static enum dht_status dhtlib_read()
{
	unsigned char i = 0;
	unsigned char aindex = 0;
	unsigned char bcount = 7;

	// This is a variable used as timeout counter, type of this variable should
	// be chosen according to the processor speed.
	// When this variable overflows, timeout is detected
	PORTBASE tocounter = 0;

	// Clear all bits on data reception buffer
	for (i = 0; i < 5; i++) bits[i] = 0;

	// Disable interrupts to keep timing accurate, especially on slow procesors
	dhtlib_disint();

	// Generate MCU start signal
	dhtlib_start();

	// Wait for response from DHT11 max 80 uS low
	tocounter = 1;
	while (!dhtlib_testpin()) {
		if (!tocounter++)
			goto timeout;
	}
	// Wait for response from DHT11 max 80 uS high
	tocounter = 1;
	while (dhtlib_testpin()) {
		if (!tocounter++)
			goto timeout;
	}
	// Begin data reception, 40 bits to be received
	for (i = 0; i < 40; i++) {
		tocounter = 1;
		while (!dhtlib_testpin()) {
			if (!tocounter++)
				goto timeout;
		}
		// If after 50 uS the pin is low we're on the start of another bit
		delay_us(40);
		if (!dhtlib_testpin()) {
			if (bcount == 0) {
				bcount = 7;
				aindex++;
			} else {
				bcount--;
			}
			continue;
		}
		// If pin is high after 50 us we're receiving logic high
		tocounter = 1;
		while (dhtlib_testpin()) {
			if (!tocounter++)
				goto timeout;
		}
		// Set the bit and shift left
		bits[aindex] |= (1 << bcount);
		if (bcount == 0) {
			bcount = 7;
			aindex++;
		} else {
			bcount--;
		}
	}
	// Exit for normal operation
	dhtlib_enaint();
	return E_DHTLIB_OK;
	// Exit when timeout occurs
timeout:
	dhtlib_enaint(); // Re-enable interrupts and return
	return E_DHTLIB_TIMEOUT_ERROR;
}

enum dht_status dhtlib_read11(uint8_t * temp, uint8_t * hum)
{
	// Read operation
	enum dht_status s = dhtlib_read();
	if (s != E_DHTLIB_OK)
		return s;
	// Checksum comprobation
	unsigned char chksum = bits[0] + bits[1] + bits[2] + bits[3];
	if (chksum != bits[4])
		return E_DHTLIB_CHKSUM_ERROR;
	// Copy results
	* hum = bits[0];
	* temp = bits[2];
	// Return Ok code
	return E_DHTLIB_OK;
}

/**
 * @brief Generates start signal on the bus
 *
 * This function generates the signal needed to start the comunication with the
 * tamperature and humidity sensor.
 */
static void dhtlib_start()
{
	dhtlib_setout(); // Set pin as output
	dhtlib_outlow(); // Pull bus to low state

	delay_ms(20);

	dhtlib_outhi();
	dhtlib_setin(); // Turn pin to input

	delay_us(60);
}
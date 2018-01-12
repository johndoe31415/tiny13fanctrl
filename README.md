# tiny13fanctrl
This is a Atmel AVR ATtiny13 based project which I use to regulate the fan of
my Korad KA3005P power supply, taking into account the temperature and current
load.

It interfaces with the KA3005P control circuit and takes the fan control of the
original KA3005P as input on PB3, measures the fan's tachometer signal
(open-drain, standard 3-pin Molex fan connector) on PB2, has a temperature
measuring Epcos 100kOhm NTC (Vishay 2381 640 63104, brown black yellow gold, B
= 4190 K) connected to PB4 in series to a 47kOhm resistor. Also, debugging data
is output as RS232 with 9600 8N1 on PB1 every sampling cycle (approximately
every 800ms) in the form of five bytes (all binary):

  1. Temperature, measurement in °C
  2. Temperature that is accounted on top by the sampled input PWM (full PWM adds another 16°C)
  3. Current fan rotations per sampling period
  4. Target fan rotations per sampling period (for Arctic F8, that's 50 for full throttle at 12 VDC)
  5. PWM register value OCR0A

# License
GNU GPL-3.

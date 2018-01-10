.PHONY: all clean program reset halgen

DEVICE := attiny13
DUDE_DEV := t13
CLOCK := 9600000
OBJS := main.o

CC := avr-gcc
UPLOAD := micronucleus/commandline/micronucleus --run
CFLAGS := -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

all: main main.bin

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

reset:
	avrdude -c avrispmkII -p $(DUDE_DEV) -B 10

program: main.hex
	avrdude -c avrispmkII -p $(DUDE_DEV) -B 4 -U flash:w:main.hex:i

clean:
	rm -f main.hex main.bin main $(OBJS)

main: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

main.hex: main
	avr-objcopy -j .text -j .data -O ihex main $@

main.bin: main
	avr-objcopy -j .text -j .data -O binary main $@

halgen: hal.xml
	../HALGen/halgen -a avr -o hal.h hal.xml

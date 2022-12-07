MCU   = atmega168p
F_CPU = 1000000UL  
BAUD  = 9600UL
CONF_FILE = avrdude.conf
PROGRAMMER_TYPE = usbasp
CC = avr-gcc
OBJCOPY = avr-objcopy
AVRSIZE = avr-size
AVRDUDE = avrdude

TARGET = Single-Digit-Counter-With-PushButton

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
HEADERS=$($SOURCES:.c=.h)

%.o: %.c $(HEADERS) 
	@$(CC) -Wall -g -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -c -o $@ $<
	
$(TARGET).elf:$(OBJECTS)
	@$(CC) -Wl,-Map,$(TARGET).map  -Wl,--gc-sections  -mmcu=$(MCU)  $^ -o $@

$(TARGET).hex:$(TARGET).elf
	@$(OBJCOPY) -j .text -j .data -O ihex $< $@

size:  $(TARGET).elf
	@$(AVRSIZE) -C --mcu=$(MCU) $(TARGET).elf

compile:$(TARGET).hex

flash: $(TARGET).hex
	@$(AVRDUDE) -C $(CONF_FILE) -c $(PROGRAMMER_TYPE) -p $(MCU) -U flash:w:$<

clean:
	del -f *.elf *.hex *.o *.map

.PHONY: all size compile flash clean

all: $(TARGET).hex
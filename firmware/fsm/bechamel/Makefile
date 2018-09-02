PRG            = bechamel
OBJ            = bechamel.o
MCU_TARGET     = attiny25
OPTIMIZE       = -Os -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields
DEFS           = $(CPU_SPEED)
LIBS           =
INCLUDES       = -I../ -I../shared/
OBJCOPYFLAGS   = -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 -O ihex 

AVRDUDE_BIN    = $(HOME)/.arduino15/packages/arduino/tools/avrdude/6.3.0-arduino9/bin/avrdude
#AVRDUDE_CONF   = $(HOME)/.arduino15/packages/MicroCore/hardware/avr/1.0.3/avrdude.conf
AVRDUDE_CONF   = $(HOME)/.arduino15/packages/arduino/tools/avrdude/6.3.0-arduino9/etc/avrdude.conf

ifeq ($(MCU_TARGET), attiny13a)
	AVRDUDE_PART  = t13
	AVRDUDE_FUSES = -Ulfuse:w:0x75:m -Uhfuse:w:0xFF:m
	DEFS          += -DATTINY=13
else ifeq ($(MCU_TARGET), attiny25) 
	AVRDUDE_PART  = t25
	AVRDUDE_FUSES = -Ulfuse:w:0xD2:m -Uhfuse:w:0xDF:m -Uefuse:w:0xFF:m
	DEFS          += -DATTINY=25
else ifeq ($(MCU_TARGET), attiny45)
	AVRDUDE_PART  = t45
	#AVRDUDE_FUSES = -Ulfuse:w:0xD2:m -Uhfuse:w:0xDF:m -Uefuse:w:0xFF:m
	DEFS          += -DATTINY=45
else ifeq ($(MCU_TARGET), attiny85)
	AVRDUDE_PART  = t85
	#AVRDUDE_FUSES = -Ulfuse:w:0xD2:m -Uhfuse:w:0xDF:m -Uefuse:w:0xFF:m
	DEFS          += -DATTINY=85
else
	$(error Unknown part number for avrdude!)
endif

CC             = avr-gcc
# Override is only needed by avr-lib build system.
override CFLAGS        = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) -std=gnu99 $(DEFS) $(INCLUDES)
override LDFLAGS       = -Wl,-Map,$(PRG).map
OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump

#AVRDUDE        = /home/sean/.arduino15/packages/arduino/tools/avrdude/6.3.0-arduino9/bin/avrdude -C/home/sean/.arduino15/packages/MicroCore/hardware/avr/1.0.3/avrdude.conf
AVRDUDE        = $(AVRDUDE_BIN) -C$(AVRDUDE_CONF)

.PHONY: all
all: $(PRG).elf lst text eeprom
$(PRG).elf: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

# dependency:
%.o: %c
clean:
	rm -rf *.o *.lst *.map $(PRG).elf $(PRG).hex $(PRG).bin $(PRG).eep
.PHONY: clean
lst:  $(PRG).lst
%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

# Rules for building the .text rom images
text: hex bin
hex:  $(PRG).hex
bin:  $(PRG).bin

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@
%.bin: %.elf
	$(OBJCOPY) -j .text -j .data -O binary $< $@

# Rules for building the .eeprom rom images
eeprom: ehex
ehex:  $(PRG).eep

%.eep: %.elf
	$(OBJCOPY) $(OBJCOPYFLAGS)  $< $@ \
		|| { echo empty $@ not generated; exit 0; }


fuses:
	#$(AVRDUDE) -v -p t13 -cusbtiny -Ulfuse:w:0x79:m -Uhfuse:w:0xED:m
	#$(AVRDUDE) -v -p t13 -cusbtiny -Ulfuse:w:0x75:m -Uhfuse:w:0xFF:m
	#$(AVRDUDE) -v -p t25 -cusbtiny -u -Ulfuse:w:0xD2:m -Uhfuse:w:0xDF:m -Uefuse:w:0xFF:m
	$(AVRDUDE) -v -p $(AVRDUDE_PART) -cusbtiny -u $(AVRDUDE_FUSES)

upload: all
	#$(AVRDUDE) -v -p t13 -cusbtiny -Uflash:w:$(PRG).hex:a -Ueeprom:w:$(PRG).eep:i
	$(AVRDUDE) -v -p $(AVRDUDE_PART) -cusbtiny -Uflash:w:$(PRG).hex:a

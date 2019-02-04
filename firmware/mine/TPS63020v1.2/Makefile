PRG            = flashlight
OBJ            = flashlight.o
MCU_TARGET     = attiny13a
LIFEPO4        = 1

# Target Dependent Variables
ifeq ($(MCU_TARGET), attiny13a)
#CPU_SPEED      = 9600000UL
CPU_SPEED      = 4800000UL
AVRDUDE_MCU    = t13
AVRDUDE_FUSES  = -Ulfuse:w:0x75:m -Uhfuse:w:0xFF:m
else ifeq ($(MCU_TARGET), attiny25)
CPU_SPEED      = 8000000UL
AVRDUDE_MCU    = t25
AVRDUDE_FUSES  = -Ulfuse:w:0xD2:m -Uhfuse:w:0xDF:m -Uefuse:w:0xFF:m
endif

EXTRADEFS =
ifeq ($(LIFEPO4), 1)
  EXTRADEFS += -DLIFEPO4=1
endif

OPTIMIZE       = -Os -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields
DEFS           = -std=gnu99 -DF_CPU=$(CPU_SPEED) $(EXTRADEFS)
LIBS           =

CC             = avr-gcc
# Override is only needed by avr-lib build system.
override CFLAGS        = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS)
override LDFLAGS       = -Wl,-Map,$(PRG).map
OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump
AVRDUDE        = avrdude

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
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O \
		ihex $< $@ || { echo empty $@ not generated; exit 0; }

fuses:
	$(AVRDUDE) -v -cusbtiny -p $(AVRDUDE_MCU) $(AVRDUDE_FUSES)

upload: all
	$(AVRDUDE) -v -cusbtiny -p $(AVRDUDE_MCU) -Uflash:w:$(PRG).hex:a

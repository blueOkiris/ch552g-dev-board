# Build system for Game-Card game "Ping"

# Settings

## MCU Settings

CPU_FREQ :=		24000000
XRAM_LOC :=		0x0000
XRAM_SIZE :=	0x0400
IRAM_SIZE :=	256
CODE_SIZE :=	0x3C00

## Project settings

OBJNAME :=		snek
SRC :=			$(wildcard src/*.c) \
				$(wildcard ../ch554_sdcc/include/*.c)
HFILES :=		$(wildcard include/*.h) \
				$(wildcard ../ch554_sdcc/*.h)
RFILES :=		$(subst .c,.rel,$(subst ../ch554_sdcc/include/,,$(subst src/,,$(SRC))))

## Compiler

CC :=			sdcc
CFLAGS :=		-mmcs51 --model-small --no-xinit-opt -DFREQ_SYS=$(CPU_FREQ) \
				--xram-size $(XRAM_SIZE) --xram-loc $(XRAM_LOC) --code-size $(CODE_SIZE) \
				--iram-size $(IRAM_SIZE) \
				-Iinclude -I../ch554_sdcc/include

# Targets

## Helpers

.PHONY: all
all: $(OBJNAME).bin $(OBJNAME).hex

.PHONY: clean
clean:
	rm -rf *.ihx *.lk *.map *.mem *.lst *.rel *.rst *.sym *.asm *.adb *.hex *.bin

## Primary

%.rel: src/%.c $(HFILES)
	$(CC) $(CFLAGS) -c $<

%.rel: ../ch554_sdcc/include/%.c $(HFILES)
	$(CC) $(CFLAGS) -c $<

$(OBJNAME).ihx: $(RFILES)
	$(CC) $(notdir $(RFILES)) $(CFLAGS) -o $@

$(OBJNAME).hex: $(OBJNAME).ihx
	packihx $< > $@

$(OBJNAME).bin: $(OBJNAME).ihx
	objcopy -I ihex -O binary $< $@

.PHONY: upload
upload: $(OBJNAME).bin
	python -m ch55xtool -f $<


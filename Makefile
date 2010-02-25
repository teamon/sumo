DEVICE      = atmega32
CLOCK       = 8000000
PROGRAMMER  = -c stk500v2 -P avrdoper

FUSES       = -U hfuse:w:0xd9:m -U lfuse:w:0x24:m
AVRDUDE     = avrdude $(PROGRAMMER) -p $(DEVICE)

CCAVR       = avr-g++ -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

OBJECTS     = main.o engine.o queue.o dist.o ground.o
AVR_OBJECTS = $(patsubst %,out/%,$(OBJECTS))

ifdef DEBUG
	CCAVR += -DDEBUG=1
	AVR_OBJECTS += $(patsubst %,out/%,debug/usart.o debug/buffer.o debug/debug.o)
endif

all: avr


# ------ AVR ------
avr: mkdirs main.hex size

out/%.o : src/%.cpp
	$(CCAVR) -c $< -o $@

out/main.elf: $(AVR_OBJECTS)
	$(CCAVR) -o out/main.elf $(AVR_OBJECTS)
# 
main.hex: out/main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex out/main.elf main.hex

flash: avr
	$(AVRDUDE) -U flash:w:main.hex:i

fuse:
	$(AVRDUDE) $(FUSES)

size:
	avr-size out/main.elf

# ------ MISC ------

mkdirs:
	mkdir -p out/debug

clean:
	rm -f main main.hex
	rm -rf out/*

DEVICE      = atmega32
CLOCK       = 8000000
PROGRAMMER  = -c stk500v2 -P avrdoper

FUSES       = -U hfuse:w:0xd9:m -U lfuse:w:0x24:m
AVRDUDE     = avrdude $(PROGRAMMER) -p $(DEVICE)

CCAVR       = avr-g++ -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)
CC          = g++

OBJECTS     = main.o engine.o queue.o dist.o ground.o

SIM_OBJECTS = $(patsubst %,out/sim/%,$(OBJECTS) socket/Socket.o socket/ClientSocket.o simulator.o)
AVR_OBJECTS = $(patsubst %,out/avr/%,$(OBJECTS))

ifdef DEBUG
	CCAVR += -DDEBUG=1
	AVR_OBJECTS += $(patsubst %,out/avr/%,debug/usart.o debug/buffer.o debug/debug.o)
endif

all: avr sim


# ------ AVR ------
avr: mkdirs main.hex

out/avr/%.o : src/%.cpp
	$(CCAVR) -c $< -o $@

out/avr/main.elf: $(AVR_OBJECTS)
	$(CCAVR) -o out/avr/main.elf $(AVR_OBJECTS)
# 
main.hex: out/avr/main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex out/avr/main.elf main.hex

flash: avr
	$(AVRDUDE) -U flash:w:main.hex:i

fuse:
	$(AVRDUDE) $(FUSES)


# ------ SIM ------
sim: mkdirs main

out/sim/%.o : src/%.cpp
	$(CC) -c $< -o $@

main: $(SIM_OBJECTS)
	rm -f main
	$(CC) -o main $(SIM_OBJECTS)


# ------ MISC ------

mkdirs:
	mkdir -p out/sim/socket
	mkdir -p out/avr/debug

clean:
	rm -f main main.hex
	rm -rf out/sim/*
	rm -rf out/avr/*

DEVICE      = atmega8
CLOCK       = 8000000
PROGRAMMER  = -c stk500v2 -P avrdoper
OBJECTS     = main.o engine.o queue.o

SO = $(OBJECTS) socket/Socket.o socket/ClientSocket.o
SIM_OBJECTS = $(patsubst %,out/sim/%,$(SO))
AVR_OBJECTS = $(patsubst %,out/avr/%,$(OBJECTS))

FUSES       = -U hfuse:w:0xd9:m -U lfuse:w:0x24:m
AVRDUDE     = avrdude $(PROGRAMMER) -p $(DEVICE)

CCAVR       = avr-g++ -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)
CC          = g++


all: avr sim


# ------ AVR ------
avr: main.hex

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

mkdirs:
	mkdir -p out/sim/socket

out/sim/%.o : src/%.cpp
	$(CC) -c $< -o $@

main: $(SIM_OBJECTS)
	rm -f main
	$(CC) -o main $(SIM_OBJECTS)


# ------ MISC ------

clean:
	rm -rf out/sim/*
	rm -rf out/avr/*

.PHONY: none rk3399 clean

CX := aarch64-none-elf-gcc
AS := aarch64-none-elf-as
LINK := ./ld/
CSRC := ./src/aarch64/c-src/
LCSRC := ./lib/c-src/
ASRC := ./src/aarch64/asm/
INC := -I./include/UART/UART-Standart -I./include/type/ -I./include/Clk/ -I./include/PMU/ -I./include/GIC/ -I./include/Handle/ -I./lib/include/


# -c - flag disable linker in compiler process .c to .o
# -o - flag compiler from .c to .o(.elf)
# Remember! If INC get full path-name to include file, to in c-file: "include-component.h"

rk3399: UnZero-rk3399.elf

boot-asm.o: $(ASRC)boot.asm
	$(AS) $(ASRC)boot.asm -o boot-asm.o

boot-c.o: $(CSRC)boot/boot-rk3399.c
	$(CX) $(INC) -c $(CSRC)boot/boot-rk3399.c -o boot-c.o

uart.o: $(CSRC)UART/UART-Rev/UART165050-Synops.c
	$(CX) $(INC) -c $(CSRC)UART/UART-Rev/UART165050-Synops.c -o uart.o

clk-cru.o: $(CSRC)Clk/Clk-CRU-rk3399.c
	$(CX) $(INC) -c $(CSRC)Clk/Clk-CRU-rk3399.c -o clk-cru.o

pmu-pmu.o: $(CSRC)PMU/PMU-PMU-rk3399.c
	$(CX) $(INC) -c $(CSRC)PMU/PMU-PMU-rk3399.c -o pmu-pmu.o

gic-gicv3.o: $(CSRC)GIC/GIC-GICv3.c
	$(CX) $(INC) -c $(CSRC)GIC/GIC-GICv3.c -o gic-gicv3.o

vector-table-asm.o: $(ASRC)table-vector.asm
	$(AS) $(ASRC)table-vector.asm -o vector-table-asm.o

table-handle.o: $(CSRC)Handle/vector-handle.c
	$(CX) $(INC) -c $(CSRC)Handle/vector-handle.c -o table-handle.o

lib-std.o: $(LCSRC)ustd.c
	$(CX) $(INC) -c $(LCSRC)ustd.c -o lib-std.o

UnZero-rk3399.elf: boot-c.o boot-asm.o uart.o clk-cru.o pmu-pmu.o gic-gicv3.o table-handle.o lib-std.o vector-table-asm.o
	$(CX) -nostdlib -T $(LINK)rk3399.ld boot-c.o boot-asm.o pmu-pmu.o gic-gicv3.o clk-cru.o vector-table-asm.o lib-std.o table-handle.o uart.o -o $@
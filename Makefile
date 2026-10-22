.PHONY: none rk3399 clean

CX := aarch64-none-elf-gcc
AS := aarch64-none-elf-as
LINK := ./ld/
CSRC := ./src/aarch64/c-src/
LCSRC := ./lib/c-src/
ASRC := ./src/aarch64/asm/
INC := -I./include/UART/UART-Standart -I./include/type/ -I./include/Clk/ -I./include/PMU/ -I./include/GIC/ -I./include/Handle/ -I./lib/include/

rk3399: UnZero-rk3399.elf

boot-asm.o: $(ASRC)boot.asm
	$(AS) $(ASRC)boot.asm -o boot-asm.o

boot-c.o: $(CSRC)boot/boot-rk3399.c
	$(CX) $(INC) -c $^ -o $@

uart.o: $(CSRC)UART/UART-Rev/UART165050-Synops.c
	$(CX) $(INC) -c $^ -o $@

clk-cru.o: $(CSRC)Clk/Clk-CRU-rk3399.c
	$(CX) $(INC) -c $^ -o $@

pmu-pmu.o: $(CSRC)PMU/PMU-PMU-rk3399.c
	$(CX) $(INC) -c $^ -o $@

gic-gicv3.o: $(CSRC)GIC/GIC-GICv3.c
	$(CX) $(INC) -c $^ -o $@

vector-table-asm.o: $(ASRC)table-vector.asm
	$(AS) $^ -o $@

table-handle.o: $(CSRC)Handle/vector-handle.c
	$(CX) $(INC) -c $^ -o $@

lib-std.o: $(LCSRC)ustd.c
	$(CX) $(INC) -c $^ -o $@

UnZero-rk3399.elf: boot-c.o boot-asm.o uart.o clk-cru.o pmu-pmu.o gic-gicv3.o table-handle.o lib-std.o vector-table-asm.o
	$(CX) -nostdlib -T $(LINK)rk3399.ld $^ -o $@
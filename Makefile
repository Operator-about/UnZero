.PHONY: none rk3399 qemu clean

CX := aarch64-none-elf-gcc
AS := aarch64-none-elf-as
LINK := ./ld/
CSRC := ./src/aarch64/c-src/
LCSRC := ./lib/c-src/
ASRC := ./src/aarch64/asm/
INC := -I./include/UART/UART-Standart -I./include/type/ -I./include/Clk/ -I./include/PMU/ -I./include/GIC/ -I./include/Handle/ -I./lib/include/ -I./include/MMU/

boot-asm.o: $(ASRC)boot.asm
	$(AS) $(ASRC)boot.asm -o boot-asm.o

switch.o: $(ASRC)switch.asm
	$(AS) $^ -o $@

boot-rk3399-c.o: $(CSRC)boot/boot-rk3399.c
	$(CX) $(INC) -c $^ -o $@

boot-qemu-c.o: $(CSRC)boot/boot-qemu.c
	$(CX) $(INC) -c $^ -o $@

uart.o: $(CSRC)UART/UART-Rev/UART165050-Synops.c
	$(CX) $(INC) -c $^ -o $@

uartpl.o: $(CSRC)UART/UART-Rev/UARTPL011-ARM.c
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

mmu.o: $(CSRC)MMU/MMU.c
	$(CX) $(INC) -c $^ -o $@

rk3399: UnZero-rk3399.elf

UnZero-rk3399.elf: boot-rk3399-c.o boot-asm.o uart.o clk-cru.o pmu-pmu.o mmu.o gic-gicv3.o table-handle.o switch.o lib-std.o vector-table-asm.o
	$(CX) -nostdlib -T $(LINK)rk3399.ld $^ -o $@

qemu: UnZero-QEMU.elf

UnZero-QEMU.elf: boot-qemu-c.o boot-asm.o uartpl.o gic-gicv3.o table-handle.o mmu.o switch.o lib-std.o vector-table-asm.o
	$(CX) -nostdlib -T $(LINK)qemu-virt.ld $^ -o $@

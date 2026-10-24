# UnZero - TF-A equivalent

## Overview
**UnZero** - A project designed for **bare-metal programming on AArch64**, which allows for the addition of custom platforms and provides the ability to share your code with others. \
**The project is still under development! If you encounter a bug while using it, please report it! Thanks in advance!**


## Project goals:
1. Bring the implementation closer to **bare-metal**
2. **Offload the OS** from interacting with peripheral units specific to certain platforms.


## Firmware capabilities:
1. Modifying **clk** blocks
2. Modifying the **pmu** block (partially)
3. Modifying **GIC** settings
4. Performing initial **GIC** configuration
5. Handling **SMC** requests
6. **MMU** configure for EL3


## Supported platforms:
1. **rk3399** - tests were conducted on a **Rock 4A**
2. **QEMU** – planned for **v2.0**

## UnZero CMD – a new feature
**UnZero CMD** - consists of commands that specify modifications to platform-specific peripherals. These commands are transmitted via the **SMC**, and registers **`X10–X14`** must be allocated for them. \
**UnZero CMD supports:**
1. **clk**
2. **pmu**
3. **GIC**

## Project status:
The project is fully open to contributors! \
**Welcome!**

### Version project: 2.0

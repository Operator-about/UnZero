# UnZero - Contributing
**Please read these rules. If the proposed changes do not comply with the rules, they will be withdrawn.**

## Code Formatting
All **local** variables must begin with a **lowercase letter** and must not contain any uppercase letters in their names: \
`clk_div` \
All **global** variables must begin with an **uppercase letter** and must be aligned to a **4-byte** or **8-byte** boundary: \
`alignas(8) uint64_t Clk_HAL` \
The function name should begin with the **general name** of the **hardware block** for example, **`clk`** (rather than `cru`) in the case of the **rk3399**. \
Next, the **name** should include the **specific designation of the block as it appears within the platform**. This is followed by a description of the function's purpose. \
And **finally unless** the component is a **GIC or a UART** the **name** of the **platform** should be appended: \
Example on complete block: \
**`void clk_cru_conf_sel_rk3399()`** \
Pattern: \
**`void general-block-name_block-name-on-platform_what-it-does_platform-name(if applicable)`**

## File Naming
**File names** are constructed in the same way as function names, **with the exception that the part describing what the block does is omitted.**

## HAL
A **HAL** is **required** for the peripherals listed below:
1. **Clk**
2. **PMU**
3. **UART**

If you wish to add a new **peripheral similar to those in this list**, you must **implement HAL support** for it. If you are adding an entirely **new type** of **peripheral**, **creating a HAL for it is left to your discretion, though it is recommended.**

## Adding a platform
If you wish to add a **new platform**, you are **required** to write **drivers** for specifically, drivers for the **Clk**, **UART**, **PMU**, **GIC**.

## UnZero CMD
You are **required** to add **UnZero CMD** support for any peripherals that are capable of it. \
If you are adding a new peripheral and wish to enable interaction with it via UnZero CMD, please include the new UnZero CMD register schema in `UnZero-CMD-DOCUMENTATION.md`.
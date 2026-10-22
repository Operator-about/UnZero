# UnZero CMD - Description

## UnZero CMD - Clk
**CMD numbers: 0, 1**. Reserve reg: **`X10-X14`**

### UnZero CMD - Clk - CMD0
**`[63:56][55:48][47:0]`** 

**Field:**  
`[63:56]` - **CMD** \
`[55:48]` - **Mode**: 
1. h0 - **Res0**
2. h1 - **Mux**
3. h2 - **Mux 10-bit's(for rk platform)**
4. h3 - **Gate**
5. h4 - **Reset**
6. `[55]` - **if 1 - PMU CRU. if 0 - CRU**

### UnZero CMD - Clk - CMD1
**`[63:56][55:48][47:0]`** 

**Field:**  
`[63:56]` - **CMD** \
`[55:48]` - **Mode**: 
1. h0 - **Res0 / Re-setting's pll engine**
2. h1 - **Shutdown**

### UnZero CMD - Clk - Mux - CMD - 8-bit's mode
`[63:56][55:48][47:44][43:32][31:0]`

**Field:** \
`[47:35]` - **Res0** \
`[43:32]` - **Pll** \
`[31:0]` - **Div** 

**Div field:** \
`[31:24][23:16][15:8][7:0]`

**Pll field:** \
`[43:41][40:38][37:35][34:32]`

### UnZero CMD - Clk - Mux - CMD - 10-bit's mode
`[63:56][55:48][47:38][37:32][32:24][23:0]`

**Field:** \
`[47:38]` - **Res0** \
`[37:32]` - **Pll** \
`[32:24]` - **Res0** \
`[23:0]` - **Div** 

**Div field:** \
`[23:12][11:0]`

**Pll field:** \
`[37:35][34:32]`

### UnZero CMD - Clk - Mux - field info
`[63:32][31:16][15:0]`

**Field:** \
`[63:32]` - **Res0** \
`[31:16]` - **Pll bit's** \
`[15:0]` - **Div bit's**

**Div bit's field:** \
`[15:12][11:8][7:4][3:0]`

**Pll bit's field:** \
`[31:28][27:24][23:20][19:16]`

### UnZero CMD - Clk - Mux/Gate/Reset - reg info
`[63:40][39:32][31:0]`

**Field:** \
`[63:40]` - **Res0** \
`[39:32]` - **Iteration for one cmd(max 4 in 8-bit's mode, or max 2 in 10-bit's mode. This notice for rk platform). Max 4** \
`[31:0]` - **Target**

**Target field:** \
`[31:24][23:16][15:8][7:0]`

### UnZero CMD - Clk - Mux - mask info
`[63:61][60:48][47:0]`

**Field:** \
`[63:61]` - **Res0** \
`[60:48]` - **Pll mask** \
`[47:0]` - **Div mask**

**Div mask field:** \
`[47:36][35:24][23:12][11:0]`

**Pll mask field:** \
`[59:57][56:54][53:51][50:48]`

### UnZero CMD - Clk - Gate/Reset - CMD
`[63:56][55:48][47:32][31:0]`

**Field:** \
`[47:32]` - **Res0** \
`[31:0]` - **Gate/Reset**

**Gate/Reset field:** \
`[31:24][23:16][15:8][7:0]`

### UnZero CMD - Clk - Gate/Reset - field info
`[63:48][47:16][15:0]`

**Field:** \
`[63:48]` - **Res0** \
`[47:16]` - **Gate/Reset mask** \
`[15:0]` - **Gate/Reset bit's**

**Gate/Reset mask field:** \
`[47:40][39:32][31:24][23:16]`

**Gate/Reset bit's field:** \
`[15:12][11:8][7:4][3:0]`


### UnZero CMD - Clk - Pll - CMD
`[63:56][55:48][47:40][39:37][36:34][33:28][27:12][11:0]` \
For your implementation of **`clk`**, these fields may differ.

`[47:40]` - **Engine** \
`[39:37]` - **Post div 2** \
`[36:34]` - **Post div 1** \
`[33:28]` - **Ref div** \
`[27:12]` - **Res0** \
`[11:0]` - **Feedback**

## UnZero CMD - PMU
**CMD numbers: 3**. Reserve reg: **`X10`**

### UnZero CMD - PMU - CMD2
**`[63:56][55:48][47:0]`** 

**Field:**  
`[63:56]` - **CMD** \
`[55:48]` - **Mode**: 
1. h0 - **Res0**
2. h1 - **Shutdown**
3. h2 - **Startup**

### UnZero CMD - PMU - CMD
**`[63:56][55:48][47:40][39:0]`**

**Field:** \
`[47:40]` - **A Letter from the Periphery** \
`[39:0]` - **Res0**

## UnZero CMD - GIC
**CMD numbers: 2**. Reserve reg: **`X10-X13`**

### UnZero CMD - GIC - CMD3
**`[63:56][55:48][47:0]`** 

**Field:**  
`[63:56]` - **CMD** \
`[55:48]` - **Mode**: 
1. h0 - **Res0**
2. h1 - **IRQ conf**
3. h2 - **SRE conf, ICC_**
4. h3 - **CTLR conf, GICD**
5. h4 - **CTLR conf, ICC_**
6. h5 - **PMR conf, ICC_**
7. h8 - **IGRPEN1 conf for EL3, ICC_**
8. h9 - **CLTR conf, GICR**
9. hA - **Waker conf, GICR, wake**
10. hB - **Waker conf, GICR, sleep**

### UnZero CMD - GIC - IRQ - CMD
**`[63:56][55:48][47:28][27][26][25:24][23:16][15:0]`** 

**Field:** \
`[47:28]` - **Res0** \
`[27]` - **GRPMODR** \
`[26]` - **GROUPE** \
`[25:24]` - **ICFGR** \
`[23:16]` - **Priority** \
`[15:0]` - **ID**

### UnZero CMD - GIC - IRQ - AFE
**`[63:32][31:0]`** 

**Field:** \
`[63:32]` - **Res0** \
`[31:0]` - **AFE**

### UnZero CMD - GIC - ICC/GICR/GICD - CMD
**`[63:56][55:48][47:0]`** 

**Field:** \
`[47:0]` - **Res0**

### UnZero CMD - GIC - ICC/GICR/GICD - Conf
**`[63:0]`** 

**Field:** \
`[63:0]` - **Conf**

**Field:** \
`[47:0]` - **Register conf**
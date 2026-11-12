# UnZero CMD - Description

## Content
1. [**UnZero CMD - Clk**](#unzero-cmd---clk) \
    1.1 [**UnZero CMD - Clk - CMD0**](#unzero-cmd---clk---cmd0) \
    1.2 [**UnZero CMD - Clk - Mux - CMD**](#unzero-cmd---clk---mux---cmd) \
    1.3 [**UnZero CMD - Clk - Mux - field info**](#unzero-cmd---clk---mux---field-info) \
    1.4 [**UnZero CMD - Clk - Mux - Mask info**](#unzero-cmd---clk---mux---mask-info) \
    1.5 [**UnZero CMD - Clk - Mux/Gate/Reset/Other - Register info**](#unzero-cmd---clk---muxgateresetother---reg-info) \
    1.6 [**UnZero CMD - Clk - Gate/Reset - CMD**](#unzero-cmd---clk---gatereset---cmd) \
    1.7 [**UnZero CMD - Clk - Gate/Reset - field info**](#unzero-cmd---clk---gatereset---field-info) \
    1.8 [**UnZero CMD - Clk - Other - CMD**](#unzero-cmd---clk---other---cmd) \
    1.9 [**UnZero CMD - Clk - Other - field info**](#unzero-cmd---clk---other---field-info) \
    1.10 [**UnZero CMD - Clk - CMD1**](#unzero-cmd---clk---cmd1)
2. [**UnZero CMD - PMU**](#unzero-cmd---pmu) \
    2.1 [**UnZero CMD - PMU - CMD2**](#unzero-cmd---pmu---cmd2) \
    2.2 [**UnZero CMD - PMU - CMD**](#unzero-cmd---pmu---cmd) \
    2.3 [**UnZero CMD - PMU - Mask info**](#unzero-cmd---pmu---mask-info)
3. [**UnZero CMD - GIC**](#unzero-cmd---gic)
4. [**UnZero CMD - SysCon**](#unzero-cmd---syscon)
5. [**UnZero CMD - EL switch**](#unzero-cmd---el-switch)
6. [**UnZero CMD - RCMD**](#unzero-rcmd)

## UnZero CMD - Clk
**CMD numbers: 0, 1**. Reserve reg: **`X10-X14`**

### UnZero CMD - Clk - CMD0
**`[63:56][55:48][47:0]`** 

**Field:**  
`[63:56]` - **CMD** \
`[55:48]` - **Mode**: 
1. h0 - **Res0**
2. h1 - **Mux with mask. Base clk**
3. h2 - **Gate with mask. Base clk**
4. h3 - **Reset with mask. Base clk**
5. h4 - **Mux with mask. PMU clk if support**
6. h5 - **Gate with mask. PMU clk if support**
7. h6 - **Reset with mask. PMU clk if support**
8. h7 - **Mux without mask. Base clk**
9. h8 - **Gate without mask. Base clk**
10. h9 - **Reset without mask. Base clk**
11. hA - **Mux without mask. PMU clk if support**
12. hB - **Gate without mask. PMU clk if support**
13. hC - **Reset without mask. PMU clk if support**
14. hD - **Configure other clk register with mask. Base clk**
15. hE - **Configure other clk register with mask. PMU clk if support**
16. hF - **Configure other clk register without mask. Base clk**
17. h10 - **Configure other clk register without mask. PMU clk if support**

### UnZero CMD - Clk - CMD1
**`[63:56][55:48][47:0]`** 

**Field:**  
`[63:56]` - **CMD** \
`[55:48]` - **Mode**: 
1. h0 - **Res0**
2. h1 - **Reset pll engine with mask. Base clk**
3. h2 - **Shutdown with mask. Base clk**
4. h3 - **Reset pll engine with mask. PMU clk if support**
5. h4 - **Shutdown with mask. PMU clk if support**
6. h5 - **Reset pll engine without mask. Base clk**
7. h6 - **Shutdown without mask. Base clk**
8. h7 - **Reset pll engine without mask. PMU clk if support**
9. h8 - **Shutdown without mask. PMU clk if support**

### UnZero CMD - Clk - Mux - CMD
`[63:56][55:48][47:44][43:32][31:0]`

**Field:** \
`[47:35]` - **Res0** \
`[43:32]` - **Pll** \
`[31:0]` - **Div** 

**Div field:** \
**Div field max 4, if size div <= 8 or max 2** \
**It is necessary to configure from the smallest to the largest value** \
**Size div filed's depends on the field: `Size div filed` in filed info**

**Pll field:** \
`[43:41][40:38][37:35][34:32]`

### UnZero CMD - Clk - Mux - field info
`[63:32][31:16][15:0]`

**Field:** \
`[63:48]` - **Res0** \
`[47:32]` - **Size div field** \
`[31:16]` - **Pll bit's** \
`[15:0]` - **Div bit's**

**Size div field** \
`[47:44][43:40][39:36][35:32]`

**Div bit's field:** \
`[15:12][11:8][7:4][3:0]`

**Pll bit's field:** \
`[31:28][27:24][23:20][19:16]`

### UnZero CMD - Clk - Mux/Gate/Reset/Other - reg info
`[63:56][55:48][47:0]`

**Field:** \
`[63:56]` - **Res0** \
`[55:48]` - **Iteration for one cmd(max 4 in 8-bit's mode, or max 2 in 10-bit's mode. This notice for rk platform). Max 4** \
`[47:0]` - **Offset**

**Offset field:** \
`[47:36][35:24][23:12][11:0]`

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

### UnZero CMD - Clk - Other - CMD
`[63:56][55:48][47:32][31:0]`

**Field:** \
`[47:32]` - **Res0** \
`[31:0]` - **Value. Max 2** 

**Value field:**
`[31:16][15:0]`

### UnZero CMD - Clk - Other - field info
`[63:40][39:8][7:0]`

**Field:** \
`[63:40]` - **Res0** \
`[39:8]` - **Other mask** \
`[7:0]` - **Other bit's**

**Other bit's field:** \
`[7:4][3:0]`

**Other mask field:** \
`[39:24][23:8]`

### UnZero CMD - Clk - Pll - CMD
`[63:56][55:48][47:40][39:37][36:34][33:28][27:12][11:0]` \
For your implementation of **`clk`**, these fields may differ.

`[47:40]` - **Res0** \
`[39:37]` - **Post div 2** \
`[36:34]` - **Post div 1** \
`[33:28]` - **Ref div** \
`[27:12]` - **Offset address** \
`[11:0]` - **Feedback**

## UnZero CMD - PMU
**CMD numbers: 3**. Reserve reg: **`X10-X11`**

### UnZero CMD - PMU - CMD2
**`[63:56][55:48][47:0]`** 

**Field:**  
`[63:56]` - **CMD**
`[55:48]` - **Mode:**
1. h0 - **Res0**
2. h1 - **Configure domen power**
3. h2 - **Configure pll domen power**
4. h3 - **Configure wakeup event**
5. h4 - **Configure wakeup interrupt event**
6. h5 - **Get interrupt status event**

### UnZero CMD - PMU - Domen configure - CMD
**`[63:56][55:48][47:36][35:32][31:0]`**

**Field:** \
`[47:36]` - **Mode filed:** 
1. h0 - **Res0**
2. h1 - **Power down disable without bypass. Bypass extensions enable only if SoC support Q-Dynamic**
3. h2 - **Power down enable without bypass. Bypass extensions enable only if SoC support Q-Dynamic**
4. h3 - **Power down disable with bypass. Only if SoC support Q-Dynamic**
5. h4 - **Power down enable with bypass. Only if SoC support Q-Dynamic**
6. h5 - **Only bus idle isolation enable**
7. h6 - **Only bus idle isolation disable**

`[35:32]` - **Count iteration. Max 4** \
`[31:0]` - **HEX periphery code:**
1. 0x00 - **Res0**
2. 0x01 - **Perlip**
3. 0x02 - **Perbip**
4. 0x03 - **Percip**
5. 0x04 - 0xEF - **Other periphery code for this platform**
6. 0xF0 - 0xFF - **Core**

**Mode filed:** \
`[55:53][52:50][49:47][46:44]`

**HEX periphery code filed:** \
`[31:24][23:16][15:8][7:0]`

### UnZero CMD - PMU - Domen configure - Mask info
`[63:0]`

**Field:** \
`[63:0]` - **Mask**

**Mask filed:** \
`[63:48][47:32][31:16][15:0]`

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
7. ~~h8 - **IGRPEN1 conf for EL3, ICC_**~~ **[Soon unsupport]**
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

## UnZero CMD - SYSCON
**CMD numbers: 4**. Reserve reg: **`X10-X11`**

### UnZero CMD - SYSCON - CMD4
**`[63:56][55:48][47:0]`** 

**Field:**  
`[63:56]` - **CMD** \
`[55:48]` - **Mode**: 
1. h0 - **Res0** 
2. h1 - **SYSCON configure with mask** 
3. h2 - **SYSCON configure without mask** 
4. h3 - **PMU SYSCON configure with mask** 
5. h4 - **PMU SYSCON configure without mask**

### UnZero CMD - PMU/SYSCON - CMD - With Mask
**`[63:48][47:42][41:34][33:32][31:0]`** 

**Field:** \
`[47:42]` - **Res0** \
`[41:34]` - **Bit's** \
`[33:32]` - **Count** \
`[31:0]` - **Offset register's**

**Offset register's field:** \
`[31:16][15:0]`

### UnZero CMD - PMU/SYSCON - CMD - Without Mask
**`[63:48][47:46][45:34][33:32][31:0]`** 

**Field:** \
`[47:46]` - **Res0** \
`[45:34]` - **Bit's** \
`[33:32]` - **Count** \
`[31:0]` - **Offset register's**

**Offset register's field:** \
`[31:16][15:0]`

**Bit's field:** \
`[45:40][39:34]`

### UnZero CMD - PMU/SYSCON - Filed's info - With Mask
**`[63:32][31:0]`** 

**Field:** \
`[63:32]` - **Mask** \
`[31:0]` - **Value**

**Value field:** \
`[31:16][15:0]`

**Mask field:** \
`[63:48][47:32]`

### UnZero CMD - PMU/SYSCON - Filed's info - Without Mask
**`[63:0]`** 

**Field:** \
`[63:0]` - **Value**

**Value field:** \
`[63:32][31:0]`

## UnZero CMD - EL Switch

**CMD numbers: 5**. Reserve reg: **`X10-X11`**

`X11` - **Dist address**

### UnZero CMD - EL Switch - CMD5
**`[63:56][55:0]`** 

**Field:**  
`[63:56]` - **CMD**

### UnZero CMD - EL Switch - CMD
**`[63:56][55:5][4][3:0]`** 

**Field:**  
`[55:5]` - **Res0** \
`[4]` - **World configure** \
`[3:0]` - **EL dist**

## UnZero RCMD
**CMD numbers: -**. Reserve reg: **`X10`**

### UnZero RCMD - CMD
`[63:28][27:20][19:12][11:4][3:0]`

**Field:** \
`[63:28]` - **Res0** \
`[27:20]` - **From:**
1. 0x01 - **Clk**
2. 0x02 - **SYSCON**
3. 0x03 - **GIC**
4. 0xAA - **From table-vector. If `[19:12]` = 0xBB**
5. 0xFF - **From table-vector. If Unknow error** 

`[19:12]` - **Cause Syndrome:**
1. 0x00 - **Success**
2. 0x11 - **Invalid value**
3. 0x31 - **Over max itteration**
4. 0x32 - **Invalid bit's**
5. 0x41 - **Warning close to over max value**
6. 0x42 - **Warning potentially invalid value**
7. 0xAA - **Offset invalid**
8. 0xBB - **Unsupport operation**
9. 0xFF - **Unknow reasone**

`[11:4]` - **Syndrome:**
1. 0x00 - **Success**
2. 0x01 - **Success with warning**
3. 0x11 - **Error in beginning operation**
4. 0xAA - **Unsupport for this platform**
5. 0xFF - **Error in operation**

`[3:0]` - **Short reasone:**
1. h0 - **Success**
2. h1 - **Success with warning**
3. h2 - **Error**
4. h3 - **Unknow error. All field's in Res0**
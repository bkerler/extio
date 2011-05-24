;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 2.9.0 #5416 (Mar 22 2009) (MINGW32)
; This file was generated Tue Oct 12 23:27:16 2010
;--------------------------------------------------------
	.module usrp_gpif
	.optsdcc -mmcs51 --model-small
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _InitData
	.globl _FlowStates
	.globl _WaveData
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area RSEG    (DATA)
;--------------------------------------------------------
; special function bits
;--------------------------------------------------------
	.area RSEG    (DATA)
;--------------------------------------------------------
; overlayable register banks
;--------------------------------------------------------
	.area REG_BANK_0	(REL,OVR,DATA)
	.ds 8
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	.area DSEG    (DATA)
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
	.area OSEG    (OVR,DATA)
;--------------------------------------------------------
; indirectly addressable internal ram data
;--------------------------------------------------------
	.area ISEG    (DATA)
;--------------------------------------------------------
; absolute internal ram data
;--------------------------------------------------------
	.area IABS    (ABS,DATA)
	.area IABS    (ABS,DATA)
;--------------------------------------------------------
; bit data
;--------------------------------------------------------
	.area BSEG    (BIT)
;--------------------------------------------------------
; paged external ram data
;--------------------------------------------------------
	.area PSEG    (PAG,XDATA)
;--------------------------------------------------------
; external ram data
;--------------------------------------------------------
	.area XSEG    (XDATA)
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area XABS    (ABS,XDATA)
;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
	.area HOME    (CODE)
	.area GSINIT0 (CODE)
	.area GSINIT1 (CODE)
	.area GSINIT2 (CODE)
	.area GSINIT3 (CODE)
	.area GSINIT4 (CODE)
	.area GSINIT5 (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area CSEG    (CODE)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME    (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area GSINIT  (CODE)
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME    (CODE)
	.area HOME    (CODE)
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CSEG    (CODE)
	.area CSEG    (CODE)
	.area CONST   (CODE)
_WaveData:
	.db #0x01
	.db #0x01
	.db #0x01
	.db #0x01
	.db #0x01
	.db #0x01
	.db #0x01
	.db #0x07
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x3F
	.db #0x01
	.db #0x3F
	.db #0x01
	.db #0x01
	.db #0x01
	.db #0x01
	.db #0x01
	.db #0x07
	.db #0x22
	.db #0x03
	.db #0x02
	.db #0x02
	.db #0x02
	.db #0x02
	.db #0x02
	.db #0x00
	.db #0x00
	.db #0x01
	.db #0x01
	.db #0x01
	.db #0x01
	.db #0x01
	.db #0x01
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x3F
	.db #0x01
	.db #0x11
	.db #0x01
	.db #0x3F
	.db #0x01
	.db #0x01
	.db #0x01
	.db #0x07
	.db #0x00
	.db #0x03
	.db #0x00
	.db #0x01
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x06
	.db #0x04
	.db #0x04
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x2D
	.db #0x00
	.db #0x2D
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x3F
	.db #0x01
	.db #0x39
	.db #0x01
	.db #0x01
	.db #0x01
	.db #0x01
	.db #0x01
	.db #0x07
	.db #0x00
	.db #0x03
	.db #0x02
	.db #0x02
	.db #0x02
	.db #0x02
	.db #0x02
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x2D
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x3F
_FlowStates:
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0x81
	.db #0x2D
	.db #0x26
	.db #0x00
	.db #0x04
	.db #0x04
	.db #0x03
	.db #0x02
	.db #0x00
	.db #0x81
	.db #0x2D
	.db #0x21
	.db #0x00
	.db #0x04
	.db #0x04
	.db #0x03
	.db #0x02
	.db #0x00
_InitData:
	.db #0xA0
	.db #0x00
	.db #0x00
	.db #0x00
	.db #0xEE
	.db #0x4E
	.db #0x00
	.area CABS    (ABS,CODE)

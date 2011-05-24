                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 2.9.0 #5416 (Mar 22 2009) (MINGW32)
                              4 ; This file was generated Tue Oct 12 23:27:17 2010
                              5 ;--------------------------------------------------------
                              6 	.module eeprom_io
                              7 	.optsdcc -mmcs51 --model-small
                              8 	
                              9 ;--------------------------------------------------------
                             10 ; Public variables in this module
                             11 ;--------------------------------------------------------
                             12 	.globl _eeprom_read_PARM_4
                             13 	.globl _eeprom_read_PARM_3
                             14 	.globl _eeprom_read_PARM_2
                             15 	.globl _eeprom_read
                             16 ;--------------------------------------------------------
                             17 ; special function registers
                             18 ;--------------------------------------------------------
                             19 	.area RSEG    (DATA)
                             20 ;--------------------------------------------------------
                             21 ; special function bits
                             22 ;--------------------------------------------------------
                             23 	.area RSEG    (DATA)
                             24 ;--------------------------------------------------------
                             25 ; overlayable register banks
                             26 ;--------------------------------------------------------
                             27 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                      28 	.ds 8
                             29 ;--------------------------------------------------------
                             30 ; internal ram data
                             31 ;--------------------------------------------------------
                             32 	.area DSEG    (DATA)
   0017                      33 _eeprom_read_PARM_2:
   0017                      34 	.ds 1
   0018                      35 _eeprom_read_PARM_3:
   0018                      36 	.ds 2
   001A                      37 _eeprom_read_PARM_4:
   001A                      38 	.ds 1
                             39 ;--------------------------------------------------------
                             40 ; overlayable items in internal ram 
                             41 ;--------------------------------------------------------
                             42 	.area OSEG    (OVR,DATA)
                             43 ;--------------------------------------------------------
                             44 ; indirectly addressable internal ram data
                             45 ;--------------------------------------------------------
                             46 	.area ISEG    (DATA)
                             47 ;--------------------------------------------------------
                             48 ; absolute internal ram data
                             49 ;--------------------------------------------------------
                             50 	.area IABS    (ABS,DATA)
                             51 	.area IABS    (ABS,DATA)
                             52 ;--------------------------------------------------------
                             53 ; bit data
                             54 ;--------------------------------------------------------
                             55 	.area BSEG    (BIT)
                             56 ;--------------------------------------------------------
                             57 ; paged external ram data
                             58 ;--------------------------------------------------------
                             59 	.area PSEG    (PAG,XDATA)
                             60 ;--------------------------------------------------------
                             61 ; external ram data
                             62 ;--------------------------------------------------------
                             63 	.area XSEG    (XDATA)
   180E                      64 _eeprom_read_cmd_1_1:
   180E                      65 	.ds 1
                             66 ;--------------------------------------------------------
                             67 ; absolute external ram data
                             68 ;--------------------------------------------------------
                             69 	.area XABS    (ABS,XDATA)
                             70 ;--------------------------------------------------------
                             71 ; external initialized ram data
                             72 ;--------------------------------------------------------
                             73 	.area HOME    (CODE)
                             74 	.area GSINIT0 (CODE)
                             75 	.area GSINIT1 (CODE)
                             76 	.area GSINIT2 (CODE)
                             77 	.area GSINIT3 (CODE)
                             78 	.area GSINIT4 (CODE)
                             79 	.area GSINIT5 (CODE)
                             80 	.area GSINIT  (CODE)
                             81 	.area GSFINAL (CODE)
                             82 	.area CSEG    (CODE)
                             83 ;--------------------------------------------------------
                             84 ; global & static initialisations
                             85 ;--------------------------------------------------------
                             86 	.area HOME    (CODE)
                             87 	.area GSINIT  (CODE)
                             88 	.area GSFINAL (CODE)
                             89 	.area GSINIT  (CODE)
                             90 ;--------------------------------------------------------
                             91 ; Home
                             92 ;--------------------------------------------------------
                             93 	.area HOME    (CODE)
                             94 	.area HOME    (CODE)
                             95 ;--------------------------------------------------------
                             96 ; code
                             97 ;--------------------------------------------------------
                             98 	.area CSEG    (CODE)
                             99 ;------------------------------------------------------------
                            100 ;Allocation info for local variables in function 'eeprom_read'
                            101 ;------------------------------------------------------------
                            102 ;eeprom_offset             Allocated with name '_eeprom_read_PARM_2'
                            103 ;buf                       Allocated with name '_eeprom_read_PARM_3'
                            104 ;len                       Allocated with name '_eeprom_read_PARM_4'
                            105 ;i2c_addr                  Allocated to registers r2 
                            106 ;cmd                       Allocated with name '_eeprom_read_cmd_1_1'
                            107 ;------------------------------------------------------------
                            108 ;	eeprom_io.c:29: eeprom_read (unsigned char i2c_addr, unsigned char eeprom_offset,
                            109 ;	-----------------------------------------
                            110 ;	 function eeprom_read
                            111 ;	-----------------------------------------
   09EA                     112 _eeprom_read:
                    0002    113 	ar2 = 0x02
                    0003    114 	ar3 = 0x03
                    0004    115 	ar4 = 0x04
                    0005    116 	ar5 = 0x05
                    0006    117 	ar6 = 0x06
                    0007    118 	ar7 = 0x07
                    0000    119 	ar0 = 0x00
                    0001    120 	ar1 = 0x01
   09EA AA 82               121 	mov	r2,dpl
                            122 ;	eeprom_io.c:36: cmd[0] = eeprom_offset;
   09EC 90 18 0E            123 	mov	dptr,#_eeprom_read_cmd_1_1
   09EF E5 17               124 	mov	a,_eeprom_read_PARM_2
   09F1 F0                  125 	movx	@dptr,a
                            126 ;	eeprom_io.c:37: if (!i2c_write(i2c_addr, cmd, 1))
   09F2 75 1B 0E            127 	mov	_i2c_write_PARM_2,#_eeprom_read_cmd_1_1
   09F5 75 1C 18            128 	mov	(_i2c_write_PARM_2 + 1),#(_eeprom_read_cmd_1_1 >> 8)
   09F8 75 1D 01            129 	mov	_i2c_write_PARM_3,#0x01
   09FB 8A 82               130 	mov	dpl,r2
   09FD C0 02               131 	push	ar2
   09FF 12 0B 41            132 	lcall	_i2c_write
   0A02 E5 82               133 	mov	a,dpl
   0A04 D0 02               134 	pop	ar2
                            135 ;	eeprom_io.c:38: return 0;
   0A06 70 03               136 	jnz	00102$
   0A08 F5 82               137 	mov	dpl,a
   0A0A 22                  138 	ret
   0A0B                     139 00102$:
                            140 ;	eeprom_io.c:40: return i2c_read(i2c_addr, buf, len);
   0A0B 85 18 1B            141 	mov	_i2c_read_PARM_2,_eeprom_read_PARM_3
   0A0E 85 19 1C            142 	mov	(_i2c_read_PARM_2 + 1),(_eeprom_read_PARM_3 + 1)
   0A11 85 1A 1D            143 	mov	_i2c_read_PARM_3,_eeprom_read_PARM_4
   0A14 8A 82               144 	mov	dpl,r2
   0A16 02 0A 81            145 	ljmp	_i2c_read
                            146 	.area CSEG    (CODE)
                            147 	.area CONST   (CODE)
                            148 	.area CABS    (ABS,CODE)

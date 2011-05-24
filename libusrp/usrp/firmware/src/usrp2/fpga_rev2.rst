                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 2.9.0 #5416 (Mar 22 2009) (MINGW32)
                              4 ; This file was generated Tue Oct 12 23:27:16 2010
                              5 ;--------------------------------------------------------
                              6 	.module fpga_rev2
                              7 	.optsdcc -mmcs51 --model-small
                              8 	
                              9 ;--------------------------------------------------------
                             10 ; Public variables in this module
                             11 ;--------------------------------------------------------
                             12 	.globl _fpga_write_reg
                             13 	.globl _bitALTERA_DCLK
                             14 	.globl _bitALTERA_DATA0
                             15 	.globl _bitS_IN
                             16 	.globl _bitS_OUT
                             17 	.globl _bitS_CLK
                             18 	.globl _EIPX6
                             19 	.globl _EIPX5
                             20 	.globl _EIPX4
                             21 	.globl _PI2C
                             22 	.globl _PUSB
                             23 	.globl _EIEX6
                             24 	.globl _EIEX5
                             25 	.globl _EIEX4
                             26 	.globl _EI2C
                             27 	.globl _EIUSB
                             28 	.globl _SMOD1
                             29 	.globl _ERESI
                             30 	.globl _RESI
                             31 	.globl _INT6
                             32 	.globl _CY
                             33 	.globl _AC
                             34 	.globl _F0
                             35 	.globl _RS1
                             36 	.globl _RS0
                             37 	.globl _OV
                             38 	.globl _FL
                             39 	.globl _P
                             40 	.globl _TF2
                             41 	.globl _EXF2
                             42 	.globl _RCLK
                             43 	.globl _TCLK
                             44 	.globl _EXEN2
                             45 	.globl _TR2
                             46 	.globl _C_T2
                             47 	.globl _CP_RL2
                             48 	.globl _SM01
                             49 	.globl _SM11
                             50 	.globl _SM21
                             51 	.globl _REN1
                             52 	.globl _TB81
                             53 	.globl _RB81
                             54 	.globl _TI1
                             55 	.globl _RI1
                             56 	.globl _PS1
                             57 	.globl _PT2
                             58 	.globl _PS0
                             59 	.globl _PT1
                             60 	.globl _PX1
                             61 	.globl _PT0
                             62 	.globl _PX0
                             63 	.globl _EA
                             64 	.globl _ES1
                             65 	.globl _ET2
                             66 	.globl _ES0
                             67 	.globl _ET1
                             68 	.globl _EX1
                             69 	.globl _ET0
                             70 	.globl _EX0
                             71 	.globl _SM0
                             72 	.globl _SM1
                             73 	.globl _SM2
                             74 	.globl _REN
                             75 	.globl _TB8
                             76 	.globl _RB8
                             77 	.globl _TI
                             78 	.globl _RI
                             79 	.globl _TF1
                             80 	.globl _TR1
                             81 	.globl _TF0
                             82 	.globl _TR0
                             83 	.globl _IE1
                             84 	.globl _IT1
                             85 	.globl _IE0
                             86 	.globl _IT0
                             87 	.globl _SEL
                             88 	.globl _EIP
                             89 	.globl _B
                             90 	.globl _EIE
                             91 	.globl _ACC
                             92 	.globl _EICON
                             93 	.globl _PSW
                             94 	.globl _TH2
                             95 	.globl _TL2
                             96 	.globl _RCAP2H
                             97 	.globl _RCAP2L
                             98 	.globl _T2CON
                             99 	.globl _SBUF1
                            100 	.globl _SCON1
                            101 	.globl _GPIFSGLDATLNOX
                            102 	.globl _GPIFSGLDATLX
                            103 	.globl _GPIFSGLDATH
                            104 	.globl _GPIFTRIG
                            105 	.globl _EP01STAT
                            106 	.globl _IP
                            107 	.globl _OEE
                            108 	.globl _OED
                            109 	.globl _OEC
                            110 	.globl _OEB
                            111 	.globl _OEA
                            112 	.globl _IOE
                            113 	.globl _IOD
                            114 	.globl _AUTOPTRSETUP
                            115 	.globl _EP68FIFOFLGS
                            116 	.globl _EP24FIFOFLGS
                            117 	.globl _EP2468STAT
                            118 	.globl _IE
                            119 	.globl _INT4CLR
                            120 	.globl _INT2CLR
                            121 	.globl _IOC
                            122 	.globl _AUTODAT2
                            123 	.globl _AUTOPTRL2
                            124 	.globl _AUTOPTRH2
                            125 	.globl _AUTODAT1
                            126 	.globl _APTR1L
                            127 	.globl _APTR1H
                            128 	.globl _SBUF0
                            129 	.globl _SCON0
                            130 	.globl _MPAGE
                            131 	.globl _EXIF
                            132 	.globl _IOB
                            133 	.globl _CKCON
                            134 	.globl _TH1
                            135 	.globl _TH0
                            136 	.globl _TL1
                            137 	.globl _TL0
                            138 	.globl _TMOD
                            139 	.globl _TCON
                            140 	.globl _PCON
                            141 	.globl _DPS
                            142 	.globl _DPH1
                            143 	.globl _DPL1
                            144 	.globl _DPH
                            145 	.globl _DPL
                            146 	.globl _SP
                            147 	.globl _IOA
                            148 	.globl _EP8FIFOBUF
                            149 	.globl _EP6FIFOBUF
                            150 	.globl _EP4FIFOBUF
                            151 	.globl _EP2FIFOBUF
                            152 	.globl _EP1INBUF
                            153 	.globl _EP1OUTBUF
                            154 	.globl _EP0BUF
                            155 	.globl _CT4
                            156 	.globl _CT3
                            157 	.globl _CT2
                            158 	.globl _CT1
                            159 	.globl _USBTEST
                            160 	.globl _TESTCFG
                            161 	.globl _DBUG
                            162 	.globl _UDMACRCQUAL
                            163 	.globl _UDMACRCL
                            164 	.globl _UDMACRCH
                            165 	.globl _GPIFHOLDAMOUNT
                            166 	.globl _FLOWSTBHPERIOD
                            167 	.globl _FLOWSTBEDGE
                            168 	.globl _FLOWSTB
                            169 	.globl _FLOWHOLDOFF
                            170 	.globl _FLOWEQ1CTL
                            171 	.globl _FLOWEQ0CTL
                            172 	.globl _FLOWLOGIC
                            173 	.globl _FLOWSTATE
                            174 	.globl _GPIFABORT
                            175 	.globl _GPIFREADYSTAT
                            176 	.globl _GPIFREADYCFG
                            177 	.globl _XGPIFSGLDATLNOX
                            178 	.globl _XGPIFSGLDATLX
                            179 	.globl _XGPIFSGLDATH
                            180 	.globl _EP8GPIFTRIG
                            181 	.globl _EP8GPIFPFSTOP
                            182 	.globl _EP8GPIFFLGSEL
                            183 	.globl _EP6GPIFTRIG
                            184 	.globl _EP6GPIFPFSTOP
                            185 	.globl _EP6GPIFFLGSEL
                            186 	.globl _EP4GPIFTRIG
                            187 	.globl _EP4GPIFPFSTOP
                            188 	.globl _EP4GPIFFLGSEL
                            189 	.globl _EP2GPIFTRIG
                            190 	.globl _EP2GPIFPFSTOP
                            191 	.globl _EP2GPIFFLGSEL
                            192 	.globl _GPIFTCB0
                            193 	.globl _GPIFTCB1
                            194 	.globl _GPIFTCB2
                            195 	.globl _GPIFTCB3
                            196 	.globl _GPIFADRL
                            197 	.globl _GPIFADRH
                            198 	.globl _GPIFCTLCFG
                            199 	.globl _GPIFIDLECTL
                            200 	.globl _GPIFIDLECS
                            201 	.globl _GPIFWFSELECT
                            202 	.globl _SETUPDAT
                            203 	.globl _SUDPTRCTL
                            204 	.globl _SUDPTRL
                            205 	.globl _SUDPTRH
                            206 	.globl _EP8FIFOBCL
                            207 	.globl _EP8FIFOBCH
                            208 	.globl _EP6FIFOBCL
                            209 	.globl _EP6FIFOBCH
                            210 	.globl _EP4FIFOBCL
                            211 	.globl _EP4FIFOBCH
                            212 	.globl _EP2FIFOBCL
                            213 	.globl _EP2FIFOBCH
                            214 	.globl _EP8FIFOFLGS
                            215 	.globl _EP6FIFOFLGS
                            216 	.globl _EP4FIFOFLGS
                            217 	.globl _EP2FIFOFLGS
                            218 	.globl _EP8CS
                            219 	.globl _EP6CS
                            220 	.globl _EP4CS
                            221 	.globl _EP2CS
                            222 	.globl _EP1INCS
                            223 	.globl _EP1OUTCS
                            224 	.globl _EP0CS
                            225 	.globl _EP8BCL
                            226 	.globl _EP8BCH
                            227 	.globl _EP6BCL
                            228 	.globl _EP6BCH
                            229 	.globl _EP4BCL
                            230 	.globl _EP4BCH
                            231 	.globl _EP2BCL
                            232 	.globl _EP2BCH
                            233 	.globl _EP1INBC
                            234 	.globl _EP1OUTBC
                            235 	.globl _EP0BCL
                            236 	.globl _EP0BCH
                            237 	.globl _FNADDR
                            238 	.globl _MICROFRAME
                            239 	.globl _USBFRAMEL
                            240 	.globl _USBFRAMEH
                            241 	.globl _TOGCTL
                            242 	.globl _WAKEUPCS
                            243 	.globl _SUSPEND
                            244 	.globl _USBCS
                            245 	.globl _XAUTODAT2
                            246 	.globl _XAUTODAT1
                            247 	.globl _I2CTL
                            248 	.globl _I2DAT
                            249 	.globl _I2CS
                            250 	.globl _PORTECFG
                            251 	.globl _PORTCCFG
                            252 	.globl _PORTACFG
                            253 	.globl _INTSETUP
                            254 	.globl _INT4IVEC
                            255 	.globl _INT2IVEC
                            256 	.globl _CLRERRCNT
                            257 	.globl _ERRCNTLIM
                            258 	.globl _USBERRIRQ
                            259 	.globl _USBERRIE
                            260 	.globl _GPIFIRQ
                            261 	.globl _GPIFIE
                            262 	.globl _EPIRQ
                            263 	.globl _EPIE
                            264 	.globl _USBIRQ
                            265 	.globl _USBIE
                            266 	.globl _NAKIRQ
                            267 	.globl _NAKIE
                            268 	.globl _IBNIRQ
                            269 	.globl _IBNIE
                            270 	.globl _EP8FIFOIRQ
                            271 	.globl _EP8FIFOIE
                            272 	.globl _EP6FIFOIRQ
                            273 	.globl _EP6FIFOIE
                            274 	.globl _EP4FIFOIRQ
                            275 	.globl _EP4FIFOIE
                            276 	.globl _EP2FIFOIRQ
                            277 	.globl _EP2FIFOIE
                            278 	.globl _OUTPKTEND
                            279 	.globl _INPKTEND
                            280 	.globl _EP8ISOINPKTS
                            281 	.globl _EP6ISOINPKTS
                            282 	.globl _EP4ISOINPKTS
                            283 	.globl _EP2ISOINPKTS
                            284 	.globl _EP8FIFOPFL
                            285 	.globl _EP8FIFOPFH
                            286 	.globl _EP6FIFOPFL
                            287 	.globl _EP6FIFOPFH
                            288 	.globl _EP4FIFOPFL
                            289 	.globl _EP4FIFOPFH
                            290 	.globl _EP2FIFOPFL
                            291 	.globl _EP2FIFOPFH
                            292 	.globl _EP8AUTOINLENL
                            293 	.globl _EP8AUTOINLENH
                            294 	.globl _EP6AUTOINLENL
                            295 	.globl _EP6AUTOINLENH
                            296 	.globl _EP4AUTOINLENL
                            297 	.globl _EP4AUTOINLENH
                            298 	.globl _EP2AUTOINLENL
                            299 	.globl _EP2AUTOINLENH
                            300 	.globl _EP8FIFOCFG
                            301 	.globl _EP6FIFOCFG
                            302 	.globl _EP4FIFOCFG
                            303 	.globl _EP2FIFOCFG
                            304 	.globl _EP8CFG
                            305 	.globl _EP6CFG
                            306 	.globl _EP4CFG
                            307 	.globl _EP2CFG
                            308 	.globl _EP1INCFG
                            309 	.globl _EP1OUTCFG
                            310 	.globl _REVCTL
                            311 	.globl _REVID
                            312 	.globl _FIFOPINPOLAR
                            313 	.globl _UART230
                            314 	.globl _BPADDRL
                            315 	.globl _BPADDRH
                            316 	.globl _BREAKPT
                            317 	.globl _FIFORESET
                            318 	.globl _PINFLAGSCD
                            319 	.globl _PINFLAGSAB
                            320 	.globl _IFCONFIG
                            321 	.globl _CPUCS
                            322 	.globl _RES_WAVEDATA_END
                            323 	.globl _GPIF_WAVE_DATA
                            324 	.globl _fpga_write_reg_PARM_2
                            325 	.globl _g_rx_reset
                            326 	.globl _g_tx_reset
                            327 	.globl _fpga_set_reset
                            328 	.globl _fpga_set_tx_enable
                            329 	.globl _fpga_set_rx_enable
                            330 	.globl _fpga_set_tx_reset
                            331 	.globl _fpga_set_rx_reset
                            332 ;--------------------------------------------------------
                            333 ; special function registers
                            334 ;--------------------------------------------------------
                            335 	.area RSEG    (DATA)
                    0080    336 _IOA	=	0x0080
                    0081    337 _SP	=	0x0081
                    0082    338 _DPL	=	0x0082
                    0083    339 _DPH	=	0x0083
                    0084    340 _DPL1	=	0x0084
                    0085    341 _DPH1	=	0x0085
                    0086    342 _DPS	=	0x0086
                    0087    343 _PCON	=	0x0087
                    0088    344 _TCON	=	0x0088
                    0089    345 _TMOD	=	0x0089
                    008A    346 _TL0	=	0x008a
                    008B    347 _TL1	=	0x008b
                    008C    348 _TH0	=	0x008c
                    008D    349 _TH1	=	0x008d
                    008E    350 _CKCON	=	0x008e
                    0090    351 _IOB	=	0x0090
                    0091    352 _EXIF	=	0x0091
                    0092    353 _MPAGE	=	0x0092
                    0098    354 _SCON0	=	0x0098
                    0099    355 _SBUF0	=	0x0099
                    009A    356 _APTR1H	=	0x009a
                    009B    357 _APTR1L	=	0x009b
                    009C    358 _AUTODAT1	=	0x009c
                    009D    359 _AUTOPTRH2	=	0x009d
                    009E    360 _AUTOPTRL2	=	0x009e
                    009F    361 _AUTODAT2	=	0x009f
                    00A0    362 _IOC	=	0x00a0
                    00A1    363 _INT2CLR	=	0x00a1
                    00A2    364 _INT4CLR	=	0x00a2
                    00A8    365 _IE	=	0x00a8
                    00AA    366 _EP2468STAT	=	0x00aa
                    00AB    367 _EP24FIFOFLGS	=	0x00ab
                    00AC    368 _EP68FIFOFLGS	=	0x00ac
                    00AF    369 _AUTOPTRSETUP	=	0x00af
                    00B0    370 _IOD	=	0x00b0
                    00B1    371 _IOE	=	0x00b1
                    00B2    372 _OEA	=	0x00b2
                    00B3    373 _OEB	=	0x00b3
                    00B4    374 _OEC	=	0x00b4
                    00B5    375 _OED	=	0x00b5
                    00B6    376 _OEE	=	0x00b6
                    00B8    377 _IP	=	0x00b8
                    00BA    378 _EP01STAT	=	0x00ba
                    00BB    379 _GPIFTRIG	=	0x00bb
                    00BD    380 _GPIFSGLDATH	=	0x00bd
                    00BE    381 _GPIFSGLDATLX	=	0x00be
                    00BF    382 _GPIFSGLDATLNOX	=	0x00bf
                    00C0    383 _SCON1	=	0x00c0
                    00C1    384 _SBUF1	=	0x00c1
                    00C8    385 _T2CON	=	0x00c8
                    00CA    386 _RCAP2L	=	0x00ca
                    00CB    387 _RCAP2H	=	0x00cb
                    00CC    388 _TL2	=	0x00cc
                    00CD    389 _TH2	=	0x00cd
                    00D0    390 _PSW	=	0x00d0
                    00D8    391 _EICON	=	0x00d8
                    00E0    392 _ACC	=	0x00e0
                    00E8    393 _EIE	=	0x00e8
                    00F0    394 _B	=	0x00f0
                    00F8    395 _EIP	=	0x00f8
                            396 ;--------------------------------------------------------
                            397 ; special function bits
                            398 ;--------------------------------------------------------
                            399 	.area RSEG    (DATA)
                    0086    400 _SEL	=	0x0086
                    0088    401 _IT0	=	0x0088
                    0089    402 _IE0	=	0x0089
                    008A    403 _IT1	=	0x008a
                    008B    404 _IE1	=	0x008b
                    008C    405 _TR0	=	0x008c
                    008D    406 _TF0	=	0x008d
                    008E    407 _TR1	=	0x008e
                    008F    408 _TF1	=	0x008f
                    0098    409 _RI	=	0x0098
                    0099    410 _TI	=	0x0099
                    009A    411 _RB8	=	0x009a
                    009B    412 _TB8	=	0x009b
                    009C    413 _REN	=	0x009c
                    009D    414 _SM2	=	0x009d
                    009E    415 _SM1	=	0x009e
                    009F    416 _SM0	=	0x009f
                    00A8    417 _EX0	=	0x00a8
                    00A9    418 _ET0	=	0x00a9
                    00AA    419 _EX1	=	0x00aa
                    00AB    420 _ET1	=	0x00ab
                    00AC    421 _ES0	=	0x00ac
                    00AD    422 _ET2	=	0x00ad
                    00AE    423 _ES1	=	0x00ae
                    00AF    424 _EA	=	0x00af
                    00B8    425 _PX0	=	0x00b8
                    00B9    426 _PT0	=	0x00b9
                    00BA    427 _PX1	=	0x00ba
                    00BB    428 _PT1	=	0x00bb
                    00BC    429 _PS0	=	0x00bc
                    00BD    430 _PT2	=	0x00bd
                    00BE    431 _PS1	=	0x00be
                    00C0    432 _RI1	=	0x00c0
                    00C1    433 _TI1	=	0x00c1
                    00C2    434 _RB81	=	0x00c2
                    00C3    435 _TB81	=	0x00c3
                    00C4    436 _REN1	=	0x00c4
                    00C5    437 _SM21	=	0x00c5
                    00C6    438 _SM11	=	0x00c6
                    00C7    439 _SM01	=	0x00c7
                    00C8    440 _CP_RL2	=	0x00c8
                    00C9    441 _C_T2	=	0x00c9
                    00CA    442 _TR2	=	0x00ca
                    00CB    443 _EXEN2	=	0x00cb
                    00CC    444 _TCLK	=	0x00cc
                    00CD    445 _RCLK	=	0x00cd
                    00CE    446 _EXF2	=	0x00ce
                    00CF    447 _TF2	=	0x00cf
                    00D0    448 _P	=	0x00d0
                    00D1    449 _FL	=	0x00d1
                    00D2    450 _OV	=	0x00d2
                    00D3    451 _RS0	=	0x00d3
                    00D4    452 _RS1	=	0x00d4
                    00D5    453 _F0	=	0x00d5
                    00D6    454 _AC	=	0x00d6
                    00D7    455 _CY	=	0x00d7
                    00DB    456 _INT6	=	0x00db
                    00DC    457 _RESI	=	0x00dc
                    00DD    458 _ERESI	=	0x00dd
                    00DF    459 _SMOD1	=	0x00df
                    00E8    460 _EIUSB	=	0x00e8
                    00E9    461 _EI2C	=	0x00e9
                    00EA    462 _EIEX4	=	0x00ea
                    00EB    463 _EIEX5	=	0x00eb
                    00EC    464 _EIEX6	=	0x00ec
                    00F8    465 _PUSB	=	0x00f8
                    00F9    466 _PI2C	=	0x00f9
                    00FA    467 _EIPX4	=	0x00fa
                    00FB    468 _EIPX5	=	0x00fb
                    00FC    469 _EIPX6	=	0x00fc
                    0080    470 _bitS_CLK	=	0x0080
                    0081    471 _bitS_OUT	=	0x0081
                    0082    472 _bitS_IN	=	0x0082
                    00A1    473 _bitALTERA_DATA0	=	0x00a1
                    00A3    474 _bitALTERA_DCLK	=	0x00a3
                            475 ;--------------------------------------------------------
                            476 ; overlayable register banks
                            477 ;--------------------------------------------------------
                            478 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                     479 	.ds 8
                            480 ;--------------------------------------------------------
                            481 ; internal ram data
                            482 ;--------------------------------------------------------
                            483 	.area DSEG    (DATA)
   0013                     484 _g_tx_reset::
   0013                     485 	.ds 1
   0014                     486 _g_rx_reset::
   0014                     487 	.ds 1
   0015                     488 _fpga_write_reg_PARM_2:
   0015                     489 	.ds 2
                            490 ;--------------------------------------------------------
                            491 ; overlayable items in internal ram 
                            492 ;--------------------------------------------------------
                            493 	.area	OSEG    (OVR,DATA)
                            494 ;--------------------------------------------------------
                            495 ; indirectly addressable internal ram data
                            496 ;--------------------------------------------------------
                            497 	.area ISEG    (DATA)
                            498 ;--------------------------------------------------------
                            499 ; absolute internal ram data
                            500 ;--------------------------------------------------------
                            501 	.area IABS    (ABS,DATA)
                            502 	.area IABS    (ABS,DATA)
                            503 ;--------------------------------------------------------
                            504 ; bit data
                            505 ;--------------------------------------------------------
                            506 	.area BSEG    (BIT)
                            507 ;--------------------------------------------------------
                            508 ; paged external ram data
                            509 ;--------------------------------------------------------
                            510 	.area PSEG    (PAG,XDATA)
                            511 ;--------------------------------------------------------
                            512 ; external ram data
                            513 ;--------------------------------------------------------
                            514 	.area XSEG    (XDATA)
                    E400    515 _GPIF_WAVE_DATA	=	0xe400
                    E480    516 _RES_WAVEDATA_END	=	0xe480
                    E600    517 _CPUCS	=	0xe600
                    E601    518 _IFCONFIG	=	0xe601
                    E602    519 _PINFLAGSAB	=	0xe602
                    E603    520 _PINFLAGSCD	=	0xe603
                    E604    521 _FIFORESET	=	0xe604
                    E605    522 _BREAKPT	=	0xe605
                    E606    523 _BPADDRH	=	0xe606
                    E607    524 _BPADDRL	=	0xe607
                    E608    525 _UART230	=	0xe608
                    E609    526 _FIFOPINPOLAR	=	0xe609
                    E60A    527 _REVID	=	0xe60a
                    E60B    528 _REVCTL	=	0xe60b
                    E610    529 _EP1OUTCFG	=	0xe610
                    E611    530 _EP1INCFG	=	0xe611
                    E612    531 _EP2CFG	=	0xe612
                    E613    532 _EP4CFG	=	0xe613
                    E614    533 _EP6CFG	=	0xe614
                    E615    534 _EP8CFG	=	0xe615
                    E618    535 _EP2FIFOCFG	=	0xe618
                    E619    536 _EP4FIFOCFG	=	0xe619
                    E61A    537 _EP6FIFOCFG	=	0xe61a
                    E61B    538 _EP8FIFOCFG	=	0xe61b
                    E620    539 _EP2AUTOINLENH	=	0xe620
                    E621    540 _EP2AUTOINLENL	=	0xe621
                    E622    541 _EP4AUTOINLENH	=	0xe622
                    E623    542 _EP4AUTOINLENL	=	0xe623
                    E624    543 _EP6AUTOINLENH	=	0xe624
                    E625    544 _EP6AUTOINLENL	=	0xe625
                    E626    545 _EP8AUTOINLENH	=	0xe626
                    E627    546 _EP8AUTOINLENL	=	0xe627
                    E630    547 _EP2FIFOPFH	=	0xe630
                    E631    548 _EP2FIFOPFL	=	0xe631
                    E632    549 _EP4FIFOPFH	=	0xe632
                    E633    550 _EP4FIFOPFL	=	0xe633
                    E634    551 _EP6FIFOPFH	=	0xe634
                    E635    552 _EP6FIFOPFL	=	0xe635
                    E636    553 _EP8FIFOPFH	=	0xe636
                    E637    554 _EP8FIFOPFL	=	0xe637
                    E640    555 _EP2ISOINPKTS	=	0xe640
                    E641    556 _EP4ISOINPKTS	=	0xe641
                    E642    557 _EP6ISOINPKTS	=	0xe642
                    E643    558 _EP8ISOINPKTS	=	0xe643
                    E648    559 _INPKTEND	=	0xe648
                    E649    560 _OUTPKTEND	=	0xe649
                    E650    561 _EP2FIFOIE	=	0xe650
                    E651    562 _EP2FIFOIRQ	=	0xe651
                    E652    563 _EP4FIFOIE	=	0xe652
                    E653    564 _EP4FIFOIRQ	=	0xe653
                    E654    565 _EP6FIFOIE	=	0xe654
                    E655    566 _EP6FIFOIRQ	=	0xe655
                    E656    567 _EP8FIFOIE	=	0xe656
                    E657    568 _EP8FIFOIRQ	=	0xe657
                    E658    569 _IBNIE	=	0xe658
                    E659    570 _IBNIRQ	=	0xe659
                    E65A    571 _NAKIE	=	0xe65a
                    E65B    572 _NAKIRQ	=	0xe65b
                    E65C    573 _USBIE	=	0xe65c
                    E65D    574 _USBIRQ	=	0xe65d
                    E65E    575 _EPIE	=	0xe65e
                    E65F    576 _EPIRQ	=	0xe65f
                    E660    577 _GPIFIE	=	0xe660
                    E661    578 _GPIFIRQ	=	0xe661
                    E662    579 _USBERRIE	=	0xe662
                    E663    580 _USBERRIRQ	=	0xe663
                    E664    581 _ERRCNTLIM	=	0xe664
                    E665    582 _CLRERRCNT	=	0xe665
                    E666    583 _INT2IVEC	=	0xe666
                    E667    584 _INT4IVEC	=	0xe667
                    E668    585 _INTSETUP	=	0xe668
                    E670    586 _PORTACFG	=	0xe670
                    E671    587 _PORTCCFG	=	0xe671
                    E672    588 _PORTECFG	=	0xe672
                    E678    589 _I2CS	=	0xe678
                    E679    590 _I2DAT	=	0xe679
                    E67A    591 _I2CTL	=	0xe67a
                    E67B    592 _XAUTODAT1	=	0xe67b
                    E67C    593 _XAUTODAT2	=	0xe67c
                    E680    594 _USBCS	=	0xe680
                    E681    595 _SUSPEND	=	0xe681
                    E682    596 _WAKEUPCS	=	0xe682
                    E683    597 _TOGCTL	=	0xe683
                    E684    598 _USBFRAMEH	=	0xe684
                    E685    599 _USBFRAMEL	=	0xe685
                    E686    600 _MICROFRAME	=	0xe686
                    E687    601 _FNADDR	=	0xe687
                    E68A    602 _EP0BCH	=	0xe68a
                    E68B    603 _EP0BCL	=	0xe68b
                    E68D    604 _EP1OUTBC	=	0xe68d
                    E68F    605 _EP1INBC	=	0xe68f
                    E690    606 _EP2BCH	=	0xe690
                    E691    607 _EP2BCL	=	0xe691
                    E694    608 _EP4BCH	=	0xe694
                    E695    609 _EP4BCL	=	0xe695
                    E698    610 _EP6BCH	=	0xe698
                    E699    611 _EP6BCL	=	0xe699
                    E69C    612 _EP8BCH	=	0xe69c
                    E69D    613 _EP8BCL	=	0xe69d
                    E6A0    614 _EP0CS	=	0xe6a0
                    E6A1    615 _EP1OUTCS	=	0xe6a1
                    E6A2    616 _EP1INCS	=	0xe6a2
                    E6A3    617 _EP2CS	=	0xe6a3
                    E6A4    618 _EP4CS	=	0xe6a4
                    E6A5    619 _EP6CS	=	0xe6a5
                    E6A6    620 _EP8CS	=	0xe6a6
                    E6A7    621 _EP2FIFOFLGS	=	0xe6a7
                    E6A8    622 _EP4FIFOFLGS	=	0xe6a8
                    E6A9    623 _EP6FIFOFLGS	=	0xe6a9
                    E6AA    624 _EP8FIFOFLGS	=	0xe6aa
                    E6AB    625 _EP2FIFOBCH	=	0xe6ab
                    E6AC    626 _EP2FIFOBCL	=	0xe6ac
                    E6AD    627 _EP4FIFOBCH	=	0xe6ad
                    E6AE    628 _EP4FIFOBCL	=	0xe6ae
                    E6AF    629 _EP6FIFOBCH	=	0xe6af
                    E6B0    630 _EP6FIFOBCL	=	0xe6b0
                    E6B1    631 _EP8FIFOBCH	=	0xe6b1
                    E6B2    632 _EP8FIFOBCL	=	0xe6b2
                    E6B3    633 _SUDPTRH	=	0xe6b3
                    E6B4    634 _SUDPTRL	=	0xe6b4
                    E6B5    635 _SUDPTRCTL	=	0xe6b5
                    E6B8    636 _SETUPDAT	=	0xe6b8
                    E6C0    637 _GPIFWFSELECT	=	0xe6c0
                    E6C1    638 _GPIFIDLECS	=	0xe6c1
                    E6C2    639 _GPIFIDLECTL	=	0xe6c2
                    E6C3    640 _GPIFCTLCFG	=	0xe6c3
                    E6C4    641 _GPIFADRH	=	0xe6c4
                    E6C5    642 _GPIFADRL	=	0xe6c5
                    E6CE    643 _GPIFTCB3	=	0xe6ce
                    E6CF    644 _GPIFTCB2	=	0xe6cf
                    E6D0    645 _GPIFTCB1	=	0xe6d0
                    E6D1    646 _GPIFTCB0	=	0xe6d1
                    E6D2    647 _EP2GPIFFLGSEL	=	0xe6d2
                    E6D3    648 _EP2GPIFPFSTOP	=	0xe6d3
                    E6D4    649 _EP2GPIFTRIG	=	0xe6d4
                    E6DA    650 _EP4GPIFFLGSEL	=	0xe6da
                    E6DB    651 _EP4GPIFPFSTOP	=	0xe6db
                    E6DC    652 _EP4GPIFTRIG	=	0xe6dc
                    E6E2    653 _EP6GPIFFLGSEL	=	0xe6e2
                    E6E3    654 _EP6GPIFPFSTOP	=	0xe6e3
                    E6E4    655 _EP6GPIFTRIG	=	0xe6e4
                    E6EA    656 _EP8GPIFFLGSEL	=	0xe6ea
                    E6EB    657 _EP8GPIFPFSTOP	=	0xe6eb
                    E6EC    658 _EP8GPIFTRIG	=	0xe6ec
                    E6F0    659 _XGPIFSGLDATH	=	0xe6f0
                    E6F1    660 _XGPIFSGLDATLX	=	0xe6f1
                    E6F2    661 _XGPIFSGLDATLNOX	=	0xe6f2
                    E6F3    662 _GPIFREADYCFG	=	0xe6f3
                    E6F4    663 _GPIFREADYSTAT	=	0xe6f4
                    E6F5    664 _GPIFABORT	=	0xe6f5
                    E6C6    665 _FLOWSTATE	=	0xe6c6
                    E6C7    666 _FLOWLOGIC	=	0xe6c7
                    E6C8    667 _FLOWEQ0CTL	=	0xe6c8
                    E6C9    668 _FLOWEQ1CTL	=	0xe6c9
                    E6CA    669 _FLOWHOLDOFF	=	0xe6ca
                    E6CB    670 _FLOWSTB	=	0xe6cb
                    E6CC    671 _FLOWSTBEDGE	=	0xe6cc
                    E6CD    672 _FLOWSTBHPERIOD	=	0xe6cd
                    E60C    673 _GPIFHOLDAMOUNT	=	0xe60c
                    E67D    674 _UDMACRCH	=	0xe67d
                    E67E    675 _UDMACRCL	=	0xe67e
                    E67F    676 _UDMACRCQUAL	=	0xe67f
                    E6F8    677 _DBUG	=	0xe6f8
                    E6F9    678 _TESTCFG	=	0xe6f9
                    E6FA    679 _USBTEST	=	0xe6fa
                    E6FB    680 _CT1	=	0xe6fb
                    E6FC    681 _CT2	=	0xe6fc
                    E6FD    682 _CT3	=	0xe6fd
                    E6FE    683 _CT4	=	0xe6fe
                    E740    684 _EP0BUF	=	0xe740
                    E780    685 _EP1OUTBUF	=	0xe780
                    E7C0    686 _EP1INBUF	=	0xe7c0
                    F000    687 _EP2FIFOBUF	=	0xf000
                    F400    688 _EP4FIFOBUF	=	0xf400
                    F800    689 _EP6FIFOBUF	=	0xf800
                    FC00    690 _EP8FIFOBUF	=	0xfc00
   180A                     691 _regval:
   180A                     692 	.ds 4
                            693 ;--------------------------------------------------------
                            694 ; absolute external ram data
                            695 ;--------------------------------------------------------
                            696 	.area XABS    (ABS,XDATA)
                            697 ;--------------------------------------------------------
                            698 ; external initialized ram data
                            699 ;--------------------------------------------------------
                            700 	.area HOME    (CODE)
                            701 	.area GSINIT0 (CODE)
                            702 	.area GSINIT1 (CODE)
                            703 	.area GSINIT2 (CODE)
                            704 	.area GSINIT3 (CODE)
                            705 	.area GSINIT4 (CODE)
                            706 	.area GSINIT5 (CODE)
                            707 	.area GSINIT  (CODE)
                            708 	.area GSFINAL (CODE)
                            709 	.area CSEG    (CODE)
                            710 ;--------------------------------------------------------
                            711 ; global & static initialisations
                            712 ;--------------------------------------------------------
                            713 	.area HOME    (CODE)
                            714 	.area GSINIT  (CODE)
                            715 	.area GSFINAL (CODE)
                            716 	.area GSINIT  (CODE)
                            717 ;	fpga_rev2.c:29: unsigned char g_tx_reset = 0;
   121A 75 13 00            718 	mov	_g_tx_reset,#0x00
                            719 ;	fpga_rev2.c:30: unsigned char g_rx_reset = 0;
   121D 75 14 00            720 	mov	_g_rx_reset,#0x00
                            721 ;	fpga_rev2.c:42: static xdata unsigned char regval[4] = {0, 0, 0, 0};
   1220 90 18 0A            722 	mov	dptr,#_regval
   1223 E4                  723 	clr	a
   1224 F0                  724 	movx	@dptr,a
   1225 90 18 0B            725 	mov	dptr,#(_regval + 0x0001)
   1228 F0                  726 	movx	@dptr,a
   1229 90 18 0C            727 	mov	dptr,#(_regval + 0x0002)
   122C F0                  728 	movx	@dptr,a
   122D 90 18 0D            729 	mov	dptr,#(_regval + 0x0003)
   1230 F0                  730 	movx	@dptr,a
                            731 ;--------------------------------------------------------
                            732 ; Home
                            733 ;--------------------------------------------------------
                            734 	.area HOME    (CODE)
                            735 	.area HOME    (CODE)
                            736 ;--------------------------------------------------------
                            737 ; code
                            738 ;--------------------------------------------------------
                            739 	.area CSEG    (CODE)
                            740 ;------------------------------------------------------------
                            741 ;Allocation info for local variables in function 'fpga_write_reg'
                            742 ;------------------------------------------------------------
                            743 ;regval                    Allocated with name '_fpga_write_reg_PARM_2'
                            744 ;regno                     Allocated to registers r2 
                            745 ;------------------------------------------------------------
                            746 ;	fpga_rev2.c:33: fpga_write_reg (unsigned char regno, const xdata unsigned char *regval)
                            747 ;	-----------------------------------------
                            748 ;	 function fpga_write_reg
                            749 ;	-----------------------------------------
   06F7                     750 _fpga_write_reg:
                    0002    751 	ar2 = 0x02
                    0003    752 	ar3 = 0x03
                    0004    753 	ar4 = 0x04
                    0005    754 	ar5 = 0x05
                    0006    755 	ar6 = 0x06
                    0007    756 	ar7 = 0x07
                    0000    757 	ar0 = 0x00
                    0001    758 	ar1 = 0x01
   06F7 AA 82               759 	mov	r2,dpl
                            760 ;	fpga_rev2.c:35: spi_write (0, 0x00 | (regno & 0x7f),
   06F9 74 7F               761 	mov	a,#0x7F
   06FB 5A                  762 	anl	a,r2
   06FC F5 28               763 	mov	_spi_write_PARM_2,a
                            764 ;	fpga_rev2.c:38: regval, 4);
   06FE 75 29 01            765 	mov	_spi_write_PARM_3,#0x01
   0701 75 2A 20            766 	mov	_spi_write_PARM_4,#0x20
   0704 85 15 2B            767 	mov	_spi_write_PARM_5,_fpga_write_reg_PARM_2
   0707 85 16 2C            768 	mov	(_spi_write_PARM_5 + 1),(_fpga_write_reg_PARM_2 + 1)
   070A 75 2D 04            769 	mov	_spi_write_PARM_6,#0x04
   070D 75 82 00            770 	mov	dpl,#0x00
   0710 02 08 BA            771 	ljmp	_spi_write
                            772 ;------------------------------------------------------------
                            773 ;Allocation info for local variables in function 'write_fpga_master_ctrl'
                            774 ;------------------------------------------------------------
                            775 ;v                         Allocated to registers r2 
                            776 ;------------------------------------------------------------
                            777 ;	fpga_rev2.c:45: write_fpga_master_ctrl (void)
                            778 ;	-----------------------------------------
                            779 ;	 function write_fpga_master_ctrl
                            780 ;	-----------------------------------------
   0713                     781 _write_fpga_master_ctrl:
                            782 ;	fpga_rev2.c:47: unsigned char v = 0;
   0713 7A 00               783 	mov	r2,#0x00
                            784 ;	fpga_rev2.c:48: if (g_tx_enable)
   0715 E5 08               785 	mov	a,_g_tx_enable
   0717 60 02               786 	jz	00102$
                            787 ;	fpga_rev2.c:49: v |= bmFR_MC_ENABLE_TX;
   0719 7A 01               788 	mov	r2,#0x01
   071B                     789 00102$:
                            790 ;	fpga_rev2.c:50: if (g_rx_enable)
   071B E5 09               791 	mov	a,_g_rx_enable
   071D 60 03               792 	jz	00104$
                            793 ;	fpga_rev2.c:51: v |= bmFR_MC_ENABLE_RX;
   071F 43 02 02            794 	orl	ar2,#0x02
   0722                     795 00104$:
                            796 ;	fpga_rev2.c:52: if (g_tx_reset)
   0722 E5 13               797 	mov	a,_g_tx_reset
   0724 60 03               798 	jz	00106$
                            799 ;	fpga_rev2.c:53: v |= bmFR_MC_RESET_TX;
   0726 43 02 04            800 	orl	ar2,#0x04
   0729                     801 00106$:
                            802 ;	fpga_rev2.c:54: if (g_rx_reset)
   0729 E5 14               803 	mov	a,_g_rx_reset
   072B 60 03               804 	jz	00108$
                            805 ;	fpga_rev2.c:55: v |= bmFR_MC_RESET_RX;
   072D 43 02 08            806 	orl	ar2,#0x08
   0730                     807 00108$:
                            808 ;	fpga_rev2.c:56: regval[3] = v;
   0730 90 18 0D            809 	mov	dptr,#(_regval + 0x0003)
   0733 EA                  810 	mov	a,r2
   0734 F0                  811 	movx	@dptr,a
                            812 ;	fpga_rev2.c:58: fpga_write_reg (FR_MASTER_CTRL, regval);
   0735 75 15 0A            813 	mov	_fpga_write_reg_PARM_2,#_regval
   0738 75 16 18            814 	mov	(_fpga_write_reg_PARM_2 + 1),#(_regval >> 8)
   073B 75 82 04            815 	mov	dpl,#0x04
   073E 02 06 F7            816 	ljmp	_fpga_write_reg
                            817 ;------------------------------------------------------------
                            818 ;Allocation info for local variables in function 'fpga_set_reset'
                            819 ;------------------------------------------------------------
                            820 ;on                        Allocated to registers r2 
                            821 ;------------------------------------------------------------
                            822 ;	fpga_rev2.c:64: fpga_set_reset (unsigned char on)
                            823 ;	-----------------------------------------
                            824 ;	 function fpga_set_reset
                            825 ;	-----------------------------------------
   0741                     826 _fpga_set_reset:
                            827 ;	fpga_rev2.c:66: on &= 0x1;
                            828 ;	fpga_rev2.c:68: if (on){
   0741 E5 82               829 	mov	a,dpl
   0743 54 01               830 	anl	a,#0x01
   0745 FA                  831 	mov	r2,a
   0746 60 10               832 	jz	00102$
                            833 ;	fpga_rev2.c:69: USRP_PC &= ~bmPC_nRESET;		// active low
   0748 53 A0 FE            834 	anl	_IOC,#0xFE
                            835 ;	fpga_rev2.c:70: g_tx_enable = 0;
   074B 75 08 00            836 	mov	_g_tx_enable,#0x00
                            837 ;	fpga_rev2.c:71: g_rx_enable = 0;
   074E 75 09 00            838 	mov	_g_rx_enable,#0x00
                            839 ;	fpga_rev2.c:72: g_tx_reset = 0;
   0751 75 13 00            840 	mov	_g_tx_reset,#0x00
                            841 ;	fpga_rev2.c:73: g_rx_reset = 0;
   0754 75 14 00            842 	mov	_g_rx_reset,#0x00
   0757 22                  843 	ret
   0758                     844 00102$:
                            845 ;	fpga_rev2.c:76: USRP_PC |= bmPC_nRESET;
   0758 43 A0 01            846 	orl	_IOC,#0x01
   075B 22                  847 	ret
                            848 ;------------------------------------------------------------
                            849 ;Allocation info for local variables in function 'fpga_set_tx_enable'
                            850 ;------------------------------------------------------------
                            851 ;on                        Allocated to registers r2 
                            852 ;------------------------------------------------------------
                            853 ;	fpga_rev2.c:80: fpga_set_tx_enable (unsigned char on)
                            854 ;	-----------------------------------------
                            855 ;	 function fpga_set_tx_enable
                            856 ;	-----------------------------------------
   075C                     857 _fpga_set_tx_enable:
   075C AA 82               858 	mov	r2,dpl
                            859 ;	fpga_rev2.c:82: on &= 0x1;
   075E 53 02 01            860 	anl	ar2,#0x01
                            861 ;	fpga_rev2.c:83: g_tx_enable = on;
   0761 8A 08               862 	mov	_g_tx_enable,r2
                            863 ;	fpga_rev2.c:85: write_fpga_master_ctrl ();
   0763 C0 02               864 	push	ar2
   0765 12 07 13            865 	lcall	_write_fpga_master_ctrl
   0768 D0 02               866 	pop	ar2
                            867 ;	fpga_rev2.c:87: if (on){
   076A EA                  868 	mov	a,r2
   076B 60 09               869 	jz	00106$
                            870 ;	fpga_rev2.c:88: g_tx_underrun = 0;
   076D 75 0B 00            871 	mov	_g_tx_underrun,#0x00
                            872 ;	fpga_rev2.c:89: fpga_clear_flags ();
   0770 43 B1 08            873 	orl	_IOE,#0x08
   0773 53 B1 F7            874 	anl	_IOE,#0xF7
   0776                     875 00106$:
   0776 22                  876 	ret
                            877 ;------------------------------------------------------------
                            878 ;Allocation info for local variables in function 'fpga_set_rx_enable'
                            879 ;------------------------------------------------------------
                            880 ;on                        Allocated to registers r2 
                            881 ;------------------------------------------------------------
                            882 ;	fpga_rev2.c:94: fpga_set_rx_enable (unsigned char on)
                            883 ;	-----------------------------------------
                            884 ;	 function fpga_set_rx_enable
                            885 ;	-----------------------------------------
   0777                     886 _fpga_set_rx_enable:
   0777 AA 82               887 	mov	r2,dpl
                            888 ;	fpga_rev2.c:96: on &= 0x1;
   0779 53 02 01            889 	anl	ar2,#0x01
                            890 ;	fpga_rev2.c:97: g_rx_enable = on;
   077C 8A 09               891 	mov	_g_rx_enable,r2
                            892 ;	fpga_rev2.c:99: write_fpga_master_ctrl ();
   077E C0 02               893 	push	ar2
   0780 12 07 13            894 	lcall	_write_fpga_master_ctrl
   0783 D0 02               895 	pop	ar2
                            896 ;	fpga_rev2.c:100: if (on){
   0785 EA                  897 	mov	a,r2
   0786 60 09               898 	jz	00106$
                            899 ;	fpga_rev2.c:101: g_rx_overrun = 0;
   0788 75 0A 00            900 	mov	_g_rx_overrun,#0x00
                            901 ;	fpga_rev2.c:102: fpga_clear_flags ();
   078B 43 B1 08            902 	orl	_IOE,#0x08
   078E 53 B1 F7            903 	anl	_IOE,#0xF7
   0791                     904 00106$:
   0791 22                  905 	ret
                            906 ;------------------------------------------------------------
                            907 ;Allocation info for local variables in function 'fpga_set_tx_reset'
                            908 ;------------------------------------------------------------
                            909 ;on                        Allocated to registers r2 
                            910 ;------------------------------------------------------------
                            911 ;	fpga_rev2.c:107: fpga_set_tx_reset (unsigned char on)
                            912 ;	-----------------------------------------
                            913 ;	 function fpga_set_tx_reset
                            914 ;	-----------------------------------------
   0792                     915 _fpga_set_tx_reset:
   0792 AA 82               916 	mov	r2,dpl
                            917 ;	fpga_rev2.c:109: on &= 0x1;
   0794 74 01               918 	mov	a,#0x01
   0796 5A                  919 	anl	a,r2
   0797 F5 13               920 	mov	_g_tx_reset,a
                            921 ;	fpga_rev2.c:112: write_fpga_master_ctrl ();
   0799 02 07 13            922 	ljmp	_write_fpga_master_ctrl
                            923 ;------------------------------------------------------------
                            924 ;Allocation info for local variables in function 'fpga_set_rx_reset'
                            925 ;------------------------------------------------------------
                            926 ;on                        Allocated to registers r2 
                            927 ;------------------------------------------------------------
                            928 ;	fpga_rev2.c:116: fpga_set_rx_reset (unsigned char on)
                            929 ;	-----------------------------------------
                            930 ;	 function fpga_set_rx_reset
                            931 ;	-----------------------------------------
   079C                     932 _fpga_set_rx_reset:
   079C AA 82               933 	mov	r2,dpl
                            934 ;	fpga_rev2.c:118: on &= 0x1;
   079E 74 01               935 	mov	a,#0x01
   07A0 5A                  936 	anl	a,r2
   07A1 F5 14               937 	mov	_g_rx_reset,a
                            938 ;	fpga_rev2.c:121: write_fpga_master_ctrl ();
   07A3 02 07 13            939 	ljmp	_write_fpga_master_ctrl
                            940 	.area CSEG    (CODE)
                            941 	.area CONST   (CODE)
                            942 	.area CABS    (ABS,CODE)

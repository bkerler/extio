                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 2.9.0 #5416 (Mar 22 2009) (MINGW32)
                              4 ; This file was generated Tue Oct 12 23:27:14 2010
                              5 ;--------------------------------------------------------
                              6 	.module usrp_main
                              7 	.optsdcc -mmcs51 --model-small
                              8 	
                              9 ;--------------------------------------------------------
                             10 ; Public variables in this module
                             11 ;--------------------------------------------------------
                             12 	.globl _main
                             13 	.globl _patch_usb_descriptors
                             14 	.globl _isr_tick
                             15 	.globl _bitALTERA_DCLK
                             16 	.globl _bitALTERA_DATA0
                             17 	.globl _bitS_IN
                             18 	.globl _bitS_OUT
                             19 	.globl _bitS_CLK
                             20 	.globl _EIPX6
                             21 	.globl _EIPX5
                             22 	.globl _EIPX4
                             23 	.globl _PI2C
                             24 	.globl _PUSB
                             25 	.globl _EIEX6
                             26 	.globl _EIEX5
                             27 	.globl _EIEX4
                             28 	.globl _EI2C
                             29 	.globl _EIUSB
                             30 	.globl _SMOD1
                             31 	.globl _ERESI
                             32 	.globl _RESI
                             33 	.globl _INT6
                             34 	.globl _CY
                             35 	.globl _AC
                             36 	.globl _F0
                             37 	.globl _RS1
                             38 	.globl _RS0
                             39 	.globl _OV
                             40 	.globl _FL
                             41 	.globl _P
                             42 	.globl _TF2
                             43 	.globl _EXF2
                             44 	.globl _RCLK
                             45 	.globl _TCLK
                             46 	.globl _EXEN2
                             47 	.globl _TR2
                             48 	.globl _C_T2
                             49 	.globl _CP_RL2
                             50 	.globl _SM01
                             51 	.globl _SM11
                             52 	.globl _SM21
                             53 	.globl _REN1
                             54 	.globl _TB81
                             55 	.globl _RB81
                             56 	.globl _TI1
                             57 	.globl _RI1
                             58 	.globl _PS1
                             59 	.globl _PT2
                             60 	.globl _PS0
                             61 	.globl _PT1
                             62 	.globl _PX1
                             63 	.globl _PT0
                             64 	.globl _PX0
                             65 	.globl _EA
                             66 	.globl _ES1
                             67 	.globl _ET2
                             68 	.globl _ES0
                             69 	.globl _ET1
                             70 	.globl _EX1
                             71 	.globl _ET0
                             72 	.globl _EX0
                             73 	.globl _SM0
                             74 	.globl _SM1
                             75 	.globl _SM2
                             76 	.globl _REN
                             77 	.globl _TB8
                             78 	.globl _RB8
                             79 	.globl _TI
                             80 	.globl _RI
                             81 	.globl _TF1
                             82 	.globl _TR1
                             83 	.globl _TF0
                             84 	.globl _TR0
                             85 	.globl _IE1
                             86 	.globl _IT1
                             87 	.globl _IE0
                             88 	.globl _IT0
                             89 	.globl _SEL
                             90 	.globl _EIP
                             91 	.globl _B
                             92 	.globl _EIE
                             93 	.globl _ACC
                             94 	.globl _EICON
                             95 	.globl _PSW
                             96 	.globl _TH2
                             97 	.globl _TL2
                             98 	.globl _RCAP2H
                             99 	.globl _RCAP2L
                            100 	.globl _T2CON
                            101 	.globl _SBUF1
                            102 	.globl _SCON1
                            103 	.globl _GPIFSGLDATLNOX
                            104 	.globl _GPIFSGLDATLX
                            105 	.globl _GPIFSGLDATH
                            106 	.globl _GPIFTRIG
                            107 	.globl _EP01STAT
                            108 	.globl _IP
                            109 	.globl _OEE
                            110 	.globl _OED
                            111 	.globl _OEC
                            112 	.globl _OEB
                            113 	.globl _OEA
                            114 	.globl _IOE
                            115 	.globl _IOD
                            116 	.globl _AUTOPTRSETUP
                            117 	.globl _EP68FIFOFLGS
                            118 	.globl _EP24FIFOFLGS
                            119 	.globl _EP2468STAT
                            120 	.globl _IE
                            121 	.globl _INT4CLR
                            122 	.globl _INT2CLR
                            123 	.globl _IOC
                            124 	.globl _AUTODAT2
                            125 	.globl _AUTOPTRL2
                            126 	.globl _AUTOPTRH2
                            127 	.globl _AUTODAT1
                            128 	.globl _APTR1L
                            129 	.globl _APTR1H
                            130 	.globl _SBUF0
                            131 	.globl _SCON0
                            132 	.globl _MPAGE
                            133 	.globl _EXIF
                            134 	.globl _IOB
                            135 	.globl _CKCON
                            136 	.globl _TH1
                            137 	.globl _TH0
                            138 	.globl _TL1
                            139 	.globl _TL0
                            140 	.globl _TMOD
                            141 	.globl _TCON
                            142 	.globl _PCON
                            143 	.globl _DPS
                            144 	.globl _DPH1
                            145 	.globl _DPL1
                            146 	.globl _DPH
                            147 	.globl _DPL
                            148 	.globl _SP
                            149 	.globl _IOA
                            150 	.globl _hash1
                            151 	.globl _EP8FIFOBUF
                            152 	.globl _EP6FIFOBUF
                            153 	.globl _EP4FIFOBUF
                            154 	.globl _EP2FIFOBUF
                            155 	.globl _EP1INBUF
                            156 	.globl _EP1OUTBUF
                            157 	.globl _EP0BUF
                            158 	.globl _CT4
                            159 	.globl _CT3
                            160 	.globl _CT2
                            161 	.globl _CT1
                            162 	.globl _USBTEST
                            163 	.globl _TESTCFG
                            164 	.globl _DBUG
                            165 	.globl _UDMACRCQUAL
                            166 	.globl _UDMACRCL
                            167 	.globl _UDMACRCH
                            168 	.globl _GPIFHOLDAMOUNT
                            169 	.globl _FLOWSTBHPERIOD
                            170 	.globl _FLOWSTBEDGE
                            171 	.globl _FLOWSTB
                            172 	.globl _FLOWHOLDOFF
                            173 	.globl _FLOWEQ1CTL
                            174 	.globl _FLOWEQ0CTL
                            175 	.globl _FLOWLOGIC
                            176 	.globl _FLOWSTATE
                            177 	.globl _GPIFABORT
                            178 	.globl _GPIFREADYSTAT
                            179 	.globl _GPIFREADYCFG
                            180 	.globl _XGPIFSGLDATLNOX
                            181 	.globl _XGPIFSGLDATLX
                            182 	.globl _XGPIFSGLDATH
                            183 	.globl _EP8GPIFTRIG
                            184 	.globl _EP8GPIFPFSTOP
                            185 	.globl _EP8GPIFFLGSEL
                            186 	.globl _EP6GPIFTRIG
                            187 	.globl _EP6GPIFPFSTOP
                            188 	.globl _EP6GPIFFLGSEL
                            189 	.globl _EP4GPIFTRIG
                            190 	.globl _EP4GPIFPFSTOP
                            191 	.globl _EP4GPIFFLGSEL
                            192 	.globl _EP2GPIFTRIG
                            193 	.globl _EP2GPIFPFSTOP
                            194 	.globl _EP2GPIFFLGSEL
                            195 	.globl _GPIFTCB0
                            196 	.globl _GPIFTCB1
                            197 	.globl _GPIFTCB2
                            198 	.globl _GPIFTCB3
                            199 	.globl _GPIFADRL
                            200 	.globl _GPIFADRH
                            201 	.globl _GPIFCTLCFG
                            202 	.globl _GPIFIDLECTL
                            203 	.globl _GPIFIDLECS
                            204 	.globl _GPIFWFSELECT
                            205 	.globl _SETUPDAT
                            206 	.globl _SUDPTRCTL
                            207 	.globl _SUDPTRL
                            208 	.globl _SUDPTRH
                            209 	.globl _EP8FIFOBCL
                            210 	.globl _EP8FIFOBCH
                            211 	.globl _EP6FIFOBCL
                            212 	.globl _EP6FIFOBCH
                            213 	.globl _EP4FIFOBCL
                            214 	.globl _EP4FIFOBCH
                            215 	.globl _EP2FIFOBCL
                            216 	.globl _EP2FIFOBCH
                            217 	.globl _EP8FIFOFLGS
                            218 	.globl _EP6FIFOFLGS
                            219 	.globl _EP4FIFOFLGS
                            220 	.globl _EP2FIFOFLGS
                            221 	.globl _EP8CS
                            222 	.globl _EP6CS
                            223 	.globl _EP4CS
                            224 	.globl _EP2CS
                            225 	.globl _EP1INCS
                            226 	.globl _EP1OUTCS
                            227 	.globl _EP0CS
                            228 	.globl _EP8BCL
                            229 	.globl _EP8BCH
                            230 	.globl _EP6BCL
                            231 	.globl _EP6BCH
                            232 	.globl _EP4BCL
                            233 	.globl _EP4BCH
                            234 	.globl _EP2BCL
                            235 	.globl _EP2BCH
                            236 	.globl _EP1INBC
                            237 	.globl _EP1OUTBC
                            238 	.globl _EP0BCL
                            239 	.globl _EP0BCH
                            240 	.globl _FNADDR
                            241 	.globl _MICROFRAME
                            242 	.globl _USBFRAMEL
                            243 	.globl _USBFRAMEH
                            244 	.globl _TOGCTL
                            245 	.globl _WAKEUPCS
                            246 	.globl _SUSPEND
                            247 	.globl _USBCS
                            248 	.globl _XAUTODAT2
                            249 	.globl _XAUTODAT1
                            250 	.globl _I2CTL
                            251 	.globl _I2DAT
                            252 	.globl _I2CS
                            253 	.globl _PORTECFG
                            254 	.globl _PORTCCFG
                            255 	.globl _PORTACFG
                            256 	.globl _INTSETUP
                            257 	.globl _INT4IVEC
                            258 	.globl _INT2IVEC
                            259 	.globl _CLRERRCNT
                            260 	.globl _ERRCNTLIM
                            261 	.globl _USBERRIRQ
                            262 	.globl _USBERRIE
                            263 	.globl _GPIFIRQ
                            264 	.globl _GPIFIE
                            265 	.globl _EPIRQ
                            266 	.globl _EPIE
                            267 	.globl _USBIRQ
                            268 	.globl _USBIE
                            269 	.globl _NAKIRQ
                            270 	.globl _NAKIE
                            271 	.globl _IBNIRQ
                            272 	.globl _IBNIE
                            273 	.globl _EP8FIFOIRQ
                            274 	.globl _EP8FIFOIE
                            275 	.globl _EP6FIFOIRQ
                            276 	.globl _EP6FIFOIE
                            277 	.globl _EP4FIFOIRQ
                            278 	.globl _EP4FIFOIE
                            279 	.globl _EP2FIFOIRQ
                            280 	.globl _EP2FIFOIE
                            281 	.globl _OUTPKTEND
                            282 	.globl _INPKTEND
                            283 	.globl _EP8ISOINPKTS
                            284 	.globl _EP6ISOINPKTS
                            285 	.globl _EP4ISOINPKTS
                            286 	.globl _EP2ISOINPKTS
                            287 	.globl _EP8FIFOPFL
                            288 	.globl _EP8FIFOPFH
                            289 	.globl _EP6FIFOPFL
                            290 	.globl _EP6FIFOPFH
                            291 	.globl _EP4FIFOPFL
                            292 	.globl _EP4FIFOPFH
                            293 	.globl _EP2FIFOPFL
                            294 	.globl _EP2FIFOPFH
                            295 	.globl _EP8AUTOINLENL
                            296 	.globl _EP8AUTOINLENH
                            297 	.globl _EP6AUTOINLENL
                            298 	.globl _EP6AUTOINLENH
                            299 	.globl _EP4AUTOINLENL
                            300 	.globl _EP4AUTOINLENH
                            301 	.globl _EP2AUTOINLENL
                            302 	.globl _EP2AUTOINLENH
                            303 	.globl _EP8FIFOCFG
                            304 	.globl _EP6FIFOCFG
                            305 	.globl _EP4FIFOCFG
                            306 	.globl _EP2FIFOCFG
                            307 	.globl _EP8CFG
                            308 	.globl _EP6CFG
                            309 	.globl _EP4CFG
                            310 	.globl _EP2CFG
                            311 	.globl _EP1INCFG
                            312 	.globl _EP1OUTCFG
                            313 	.globl _REVCTL
                            314 	.globl _REVID
                            315 	.globl _FIFOPINPOLAR
                            316 	.globl _UART230
                            317 	.globl _BPADDRL
                            318 	.globl _BPADDRH
                            319 	.globl _BREAKPT
                            320 	.globl _FIFORESET
                            321 	.globl _PINFLAGSCD
                            322 	.globl _PINFLAGSAB
                            323 	.globl _IFCONFIG
                            324 	.globl _CPUCS
                            325 	.globl _RES_WAVEDATA_END
                            326 	.globl _GPIF_WAVE_DATA
                            327 	.globl _g_tx_underrun
                            328 	.globl _g_rx_overrun
                            329 	.globl _g_rx_enable
                            330 	.globl _g_tx_enable
                            331 	.globl _app_vendor_cmd
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
   0008                     484 _g_tx_enable::
   0008                     485 	.ds 1
   0009                     486 _g_rx_enable::
   0009                     487 	.ds 1
   000A                     488 _g_rx_overrun::
   000A                     489 	.ds 1
   000B                     490 _g_tx_underrun::
   000B                     491 	.ds 1
   000C                     492 _isr_tick_count_1_1:
   000C                     493 	.ds 1
                            494 ;--------------------------------------------------------
                            495 ; overlayable items in internal ram 
                            496 ;--------------------------------------------------------
                            497 	.area OSEG    (OVR,DATA)
                            498 ;--------------------------------------------------------
                            499 ; Stack segment in internal ram 
                            500 ;--------------------------------------------------------
                            501 	.area	SSEG	(DATA)
   003A                     502 __start__stack:
   003A                     503 	.ds	1
                            504 
                            505 ;--------------------------------------------------------
                            506 ; indirectly addressable internal ram data
                            507 ;--------------------------------------------------------
                            508 	.area ISEG    (DATA)
                            509 ;--------------------------------------------------------
                            510 ; absolute internal ram data
                            511 ;--------------------------------------------------------
                            512 	.area IABS    (ABS,DATA)
                            513 	.area IABS    (ABS,DATA)
                            514 ;--------------------------------------------------------
                            515 ; bit data
                            516 ;--------------------------------------------------------
                            517 	.area BSEG    (BIT)
                            518 ;--------------------------------------------------------
                            519 ; paged external ram data
                            520 ;--------------------------------------------------------
                            521 	.area PSEG    (PAG,XDATA)
                            522 ;--------------------------------------------------------
                            523 ; external ram data
                            524 ;--------------------------------------------------------
                            525 	.area XSEG    (XDATA)
                    E400    526 _GPIF_WAVE_DATA	=	0xe400
                    E480    527 _RES_WAVEDATA_END	=	0xe480
                    E600    528 _CPUCS	=	0xe600
                    E601    529 _IFCONFIG	=	0xe601
                    E602    530 _PINFLAGSAB	=	0xe602
                    E603    531 _PINFLAGSCD	=	0xe603
                    E604    532 _FIFORESET	=	0xe604
                    E605    533 _BREAKPT	=	0xe605
                    E606    534 _BPADDRH	=	0xe606
                    E607    535 _BPADDRL	=	0xe607
                    E608    536 _UART230	=	0xe608
                    E609    537 _FIFOPINPOLAR	=	0xe609
                    E60A    538 _REVID	=	0xe60a
                    E60B    539 _REVCTL	=	0xe60b
                    E610    540 _EP1OUTCFG	=	0xe610
                    E611    541 _EP1INCFG	=	0xe611
                    E612    542 _EP2CFG	=	0xe612
                    E613    543 _EP4CFG	=	0xe613
                    E614    544 _EP6CFG	=	0xe614
                    E615    545 _EP8CFG	=	0xe615
                    E618    546 _EP2FIFOCFG	=	0xe618
                    E619    547 _EP4FIFOCFG	=	0xe619
                    E61A    548 _EP6FIFOCFG	=	0xe61a
                    E61B    549 _EP8FIFOCFG	=	0xe61b
                    E620    550 _EP2AUTOINLENH	=	0xe620
                    E621    551 _EP2AUTOINLENL	=	0xe621
                    E622    552 _EP4AUTOINLENH	=	0xe622
                    E623    553 _EP4AUTOINLENL	=	0xe623
                    E624    554 _EP6AUTOINLENH	=	0xe624
                    E625    555 _EP6AUTOINLENL	=	0xe625
                    E626    556 _EP8AUTOINLENH	=	0xe626
                    E627    557 _EP8AUTOINLENL	=	0xe627
                    E630    558 _EP2FIFOPFH	=	0xe630
                    E631    559 _EP2FIFOPFL	=	0xe631
                    E632    560 _EP4FIFOPFH	=	0xe632
                    E633    561 _EP4FIFOPFL	=	0xe633
                    E634    562 _EP6FIFOPFH	=	0xe634
                    E635    563 _EP6FIFOPFL	=	0xe635
                    E636    564 _EP8FIFOPFH	=	0xe636
                    E637    565 _EP8FIFOPFL	=	0xe637
                    E640    566 _EP2ISOINPKTS	=	0xe640
                    E641    567 _EP4ISOINPKTS	=	0xe641
                    E642    568 _EP6ISOINPKTS	=	0xe642
                    E643    569 _EP8ISOINPKTS	=	0xe643
                    E648    570 _INPKTEND	=	0xe648
                    E649    571 _OUTPKTEND	=	0xe649
                    E650    572 _EP2FIFOIE	=	0xe650
                    E651    573 _EP2FIFOIRQ	=	0xe651
                    E652    574 _EP4FIFOIE	=	0xe652
                    E653    575 _EP4FIFOIRQ	=	0xe653
                    E654    576 _EP6FIFOIE	=	0xe654
                    E655    577 _EP6FIFOIRQ	=	0xe655
                    E656    578 _EP8FIFOIE	=	0xe656
                    E657    579 _EP8FIFOIRQ	=	0xe657
                    E658    580 _IBNIE	=	0xe658
                    E659    581 _IBNIRQ	=	0xe659
                    E65A    582 _NAKIE	=	0xe65a
                    E65B    583 _NAKIRQ	=	0xe65b
                    E65C    584 _USBIE	=	0xe65c
                    E65D    585 _USBIRQ	=	0xe65d
                    E65E    586 _EPIE	=	0xe65e
                    E65F    587 _EPIRQ	=	0xe65f
                    E660    588 _GPIFIE	=	0xe660
                    E661    589 _GPIFIRQ	=	0xe661
                    E662    590 _USBERRIE	=	0xe662
                    E663    591 _USBERRIRQ	=	0xe663
                    E664    592 _ERRCNTLIM	=	0xe664
                    E665    593 _CLRERRCNT	=	0xe665
                    E666    594 _INT2IVEC	=	0xe666
                    E667    595 _INT4IVEC	=	0xe667
                    E668    596 _INTSETUP	=	0xe668
                    E670    597 _PORTACFG	=	0xe670
                    E671    598 _PORTCCFG	=	0xe671
                    E672    599 _PORTECFG	=	0xe672
                    E678    600 _I2CS	=	0xe678
                    E679    601 _I2DAT	=	0xe679
                    E67A    602 _I2CTL	=	0xe67a
                    E67B    603 _XAUTODAT1	=	0xe67b
                    E67C    604 _XAUTODAT2	=	0xe67c
                    E680    605 _USBCS	=	0xe680
                    E681    606 _SUSPEND	=	0xe681
                    E682    607 _WAKEUPCS	=	0xe682
                    E683    608 _TOGCTL	=	0xe683
                    E684    609 _USBFRAMEH	=	0xe684
                    E685    610 _USBFRAMEL	=	0xe685
                    E686    611 _MICROFRAME	=	0xe686
                    E687    612 _FNADDR	=	0xe687
                    E68A    613 _EP0BCH	=	0xe68a
                    E68B    614 _EP0BCL	=	0xe68b
                    E68D    615 _EP1OUTBC	=	0xe68d
                    E68F    616 _EP1INBC	=	0xe68f
                    E690    617 _EP2BCH	=	0xe690
                    E691    618 _EP2BCL	=	0xe691
                    E694    619 _EP4BCH	=	0xe694
                    E695    620 _EP4BCL	=	0xe695
                    E698    621 _EP6BCH	=	0xe698
                    E699    622 _EP6BCL	=	0xe699
                    E69C    623 _EP8BCH	=	0xe69c
                    E69D    624 _EP8BCL	=	0xe69d
                    E6A0    625 _EP0CS	=	0xe6a0
                    E6A1    626 _EP1OUTCS	=	0xe6a1
                    E6A2    627 _EP1INCS	=	0xe6a2
                    E6A3    628 _EP2CS	=	0xe6a3
                    E6A4    629 _EP4CS	=	0xe6a4
                    E6A5    630 _EP6CS	=	0xe6a5
                    E6A6    631 _EP8CS	=	0xe6a6
                    E6A7    632 _EP2FIFOFLGS	=	0xe6a7
                    E6A8    633 _EP4FIFOFLGS	=	0xe6a8
                    E6A9    634 _EP6FIFOFLGS	=	0xe6a9
                    E6AA    635 _EP8FIFOFLGS	=	0xe6aa
                    E6AB    636 _EP2FIFOBCH	=	0xe6ab
                    E6AC    637 _EP2FIFOBCL	=	0xe6ac
                    E6AD    638 _EP4FIFOBCH	=	0xe6ad
                    E6AE    639 _EP4FIFOBCL	=	0xe6ae
                    E6AF    640 _EP6FIFOBCH	=	0xe6af
                    E6B0    641 _EP6FIFOBCL	=	0xe6b0
                    E6B1    642 _EP8FIFOBCH	=	0xe6b1
                    E6B2    643 _EP8FIFOBCL	=	0xe6b2
                    E6B3    644 _SUDPTRH	=	0xe6b3
                    E6B4    645 _SUDPTRL	=	0xe6b4
                    E6B5    646 _SUDPTRCTL	=	0xe6b5
                    E6B8    647 _SETUPDAT	=	0xe6b8
                    E6C0    648 _GPIFWFSELECT	=	0xe6c0
                    E6C1    649 _GPIFIDLECS	=	0xe6c1
                    E6C2    650 _GPIFIDLECTL	=	0xe6c2
                    E6C3    651 _GPIFCTLCFG	=	0xe6c3
                    E6C4    652 _GPIFADRH	=	0xe6c4
                    E6C5    653 _GPIFADRL	=	0xe6c5
                    E6CE    654 _GPIFTCB3	=	0xe6ce
                    E6CF    655 _GPIFTCB2	=	0xe6cf
                    E6D0    656 _GPIFTCB1	=	0xe6d0
                    E6D1    657 _GPIFTCB0	=	0xe6d1
                    E6D2    658 _EP2GPIFFLGSEL	=	0xe6d2
                    E6D3    659 _EP2GPIFPFSTOP	=	0xe6d3
                    E6D4    660 _EP2GPIFTRIG	=	0xe6d4
                    E6DA    661 _EP4GPIFFLGSEL	=	0xe6da
                    E6DB    662 _EP4GPIFPFSTOP	=	0xe6db
                    E6DC    663 _EP4GPIFTRIG	=	0xe6dc
                    E6E2    664 _EP6GPIFFLGSEL	=	0xe6e2
                    E6E3    665 _EP6GPIFPFSTOP	=	0xe6e3
                    E6E4    666 _EP6GPIFTRIG	=	0xe6e4
                    E6EA    667 _EP8GPIFFLGSEL	=	0xe6ea
                    E6EB    668 _EP8GPIFPFSTOP	=	0xe6eb
                    E6EC    669 _EP8GPIFTRIG	=	0xe6ec
                    E6F0    670 _XGPIFSGLDATH	=	0xe6f0
                    E6F1    671 _XGPIFSGLDATLX	=	0xe6f1
                    E6F2    672 _XGPIFSGLDATLNOX	=	0xe6f2
                    E6F3    673 _GPIFREADYCFG	=	0xe6f3
                    E6F4    674 _GPIFREADYSTAT	=	0xe6f4
                    E6F5    675 _GPIFABORT	=	0xe6f5
                    E6C6    676 _FLOWSTATE	=	0xe6c6
                    E6C7    677 _FLOWLOGIC	=	0xe6c7
                    E6C8    678 _FLOWEQ0CTL	=	0xe6c8
                    E6C9    679 _FLOWEQ1CTL	=	0xe6c9
                    E6CA    680 _FLOWHOLDOFF	=	0xe6ca
                    E6CB    681 _FLOWSTB	=	0xe6cb
                    E6CC    682 _FLOWSTBEDGE	=	0xe6cc
                    E6CD    683 _FLOWSTBHPERIOD	=	0xe6cd
                    E60C    684 _GPIFHOLDAMOUNT	=	0xe60c
                    E67D    685 _UDMACRCH	=	0xe67d
                    E67E    686 _UDMACRCL	=	0xe67e
                    E67F    687 _UDMACRCQUAL	=	0xe67f
                    E6F8    688 _DBUG	=	0xe6f8
                    E6F9    689 _TESTCFG	=	0xe6f9
                    E6FA    690 _USBTEST	=	0xe6fa
                    E6FB    691 _CT1	=	0xe6fb
                    E6FC    692 _CT2	=	0xe6fc
                    E6FD    693 _CT3	=	0xe6fd
                    E6FE    694 _CT4	=	0xe6fe
                    E740    695 _EP0BUF	=	0xe740
                    E780    696 _EP1OUTBUF	=	0xe780
                    E7C0    697 _EP1INBUF	=	0xe7c0
                    F000    698 _EP2FIFOBUF	=	0xf000
                    F400    699 _EP4FIFOBUF	=	0xf400
                    F800    700 _EP6FIFOBUF	=	0xf800
                    FC00    701 _EP8FIFOBUF	=	0xfc00
                    E1F0    702 _hash1	=	0xe1f0
   1800                     703 _patch_usb_descriptors_hw_rev_1_1:
   1800                     704 	.ds 1
   1801                     705 _patch_usb_descriptors_serial_no_1_1:
   1801                     706 	.ds 8
                            707 ;--------------------------------------------------------
                            708 ; absolute external ram data
                            709 ;--------------------------------------------------------
                            710 	.area XABS    (ABS,XDATA)
                            711 ;--------------------------------------------------------
                            712 ; external initialized ram data
                            713 ;--------------------------------------------------------
                            714 	.area HOME    (CODE)
                            715 	.area GSINIT0 (CODE)
                            716 	.area GSINIT1 (CODE)
                            717 	.area GSINIT2 (CODE)
                            718 	.area GSINIT3 (CODE)
                            719 	.area GSINIT4 (CODE)
                            720 	.area GSINIT5 (CODE)
                            721 	.area GSINIT  (CODE)
                            722 	.area GSFINAL (CODE)
                            723 	.area CSEG    (CODE)
                            724 ;--------------------------------------------------------
                            725 ; interrupt vector 
                            726 ;--------------------------------------------------------
                            727 	.area HOME    (CODE)
   1237                     728 __interrupt_vect:
   1237 02 12 3F            729 	ljmp	__sdcc_gsinit_startup
                            730 ;--------------------------------------------------------
                            731 ; global & static initialisations
                            732 ;--------------------------------------------------------
                            733 	.area HOME    (CODE)
                            734 	.area GSINIT  (CODE)
                            735 	.area GSFINAL (CODE)
                            736 	.area GSINIT  (CODE)
                            737 	.globl __sdcc_gsinit_startup
                            738 	.globl __sdcc_program_startup
                            739 	.globl __start__stack
                            740 	.globl __mcs51_genRAMCLEAR
                            741 ;------------------------------------------------------------
                            742 ;Allocation info for local variables in function 'isr_tick'
                            743 ;------------------------------------------------------------
                            744 ;count                     Allocated with name '_isr_tick_count_1_1'
                            745 ;------------------------------------------------------------
                            746 ;	usrp_main.c:309: static unsigned char	count = 1;
   120B 75 0C 01            747 	mov	_isr_tick_count_1_1,#0x01
                            748 ;	usrp_main.c:55: unsigned char g_tx_enable = 0;
   120E 75 08 00            749 	mov	_g_tx_enable,#0x00
                            750 ;	usrp_main.c:56: unsigned char g_rx_enable = 0;
   1211 75 09 00            751 	mov	_g_rx_enable,#0x00
                            752 ;	usrp_main.c:57: unsigned char g_rx_overrun = 0;
   1214 75 0A 00            753 	mov	_g_rx_overrun,#0x00
                            754 ;	usrp_main.c:58: unsigned char g_tx_underrun = 0;
   1217 75 0B 00            755 	mov	_g_tx_underrun,#0x00
                            756 	.area GSFINAL (CODE)
   1252 02 12 3A            757 	ljmp	__sdcc_program_startup
                            758 ;--------------------------------------------------------
                            759 ; Home
                            760 ;--------------------------------------------------------
                            761 	.area HOME    (CODE)
                            762 	.area HOME    (CODE)
   123A                     763 __sdcc_program_startup:
   123A 12 04 CF            764 	lcall	_main
                            765 ;	return from main will lock up
   123D 80 FE               766 	sjmp .
                            767 ;--------------------------------------------------------
                            768 ; code
                            769 ;--------------------------------------------------------
                            770 	.area CSEG    (CODE)
                            771 ;------------------------------------------------------------
                            772 ;Allocation info for local variables in function 'get_ep0_data'
                            773 ;------------------------------------------------------------
                            774 ;------------------------------------------------------------
                            775 ;	usrp_main.c:68: get_ep0_data (void)
                            776 ;	-----------------------------------------
                            777 ;	 function get_ep0_data
                            778 ;	-----------------------------------------
   0180                     779 _get_ep0_data:
                    0002    780 	ar2 = 0x02
                    0003    781 	ar3 = 0x03
                    0004    782 	ar4 = 0x04
                    0005    783 	ar5 = 0x05
                    0006    784 	ar6 = 0x06
                    0007    785 	ar7 = 0x07
                    0000    786 	ar0 = 0x00
                    0001    787 	ar1 = 0x01
                            788 ;	usrp_main.c:70: EP0BCL = 0;			// arm EP0 for OUT xfer.  This sets the busy bit
   0180 90 E6 8B            789 	mov	dptr,#_EP0BCL
   0183 E4                  790 	clr	a
   0184 F0                  791 	movx	@dptr,a
                            792 ;	usrp_main.c:72: while (EP0CS & bmEPBUSY)	// wait for busy to clear
   0185                     793 00101$:
   0185 90 E6 A0            794 	mov	dptr,#_EP0CS
   0188 E0                  795 	movx	a,@dptr
   0189 FA                  796 	mov	r2,a
   018A 20 E1 F8            797 	jb	acc.1,00101$
   018D 22                  798 	ret
                            799 ;------------------------------------------------------------
                            800 ;Allocation info for local variables in function 'app_vendor_cmd'
                            801 ;------------------------------------------------------------
                            802 ;------------------------------------------------------------
                            803 ;	usrp_main.c:81: app_vendor_cmd (void)
                            804 ;	-----------------------------------------
                            805 ;	 function app_vendor_cmd
                            806 ;	-----------------------------------------
   018E                     807 _app_vendor_cmd:
                            808 ;	usrp_main.c:83: if (bRequestType == VRT_VENDOR_IN){
   018E 90 E6 B8            809 	mov	dptr,#_SETUPDAT
   0191 E0                  810 	movx	a,@dptr
   0192 FA                  811 	mov	r2,a
   0193 BA C0 02            812 	cjne	r2,#0xC0,00163$
   0196 80 03               813 	sjmp	00164$
   0198                     814 00163$:
   0198 02 02 63            815 	ljmp	00142$
   019B                     816 00164$:
                            817 ;	usrp_main.c:89: switch (bRequest){
   019B 90 E6 B9            818 	mov	dptr,#(_SETUPDAT + 0x0001)
   019E E0                  819 	movx	a,@dptr
   019F FA                  820 	mov	r2,a
   01A0 BA 80 02            821 	cjne	r2,#0x80,00165$
   01A3 80 0E               822 	sjmp	00101$
   01A5                     823 00165$:
   01A5 BA 81 02            824 	cjne	r2,#0x81,00166$
   01A8 80 47               825 	sjmp	00106$
   01AA                     826 00166$:
   01AA BA 82 03            827 	cjne	r2,#0x82,00167$
   01AD 02 02 1F            828 	ljmp	00109$
   01B0                     829 00167$:
   01B0 02 02 5F            830 	ljmp	00112$
                            831 ;	usrp_main.c:91: case VRQ_GET_STATUS:
   01B3                     832 00101$:
                            833 ;	usrp_main.c:92: switch (wIndexL){
   01B3 90 E6 BC            834 	mov	dptr,#(_SETUPDAT + 0x0004)
   01B6 E0                  835 	movx	a,@dptr
   01B7 FA                  836 	mov	r2,a
   01B8 60 05               837 	jz	00102$
                            838 ;	usrp_main.c:94: case GS_TX_UNDERRUN:
   01BA BA 01 30            839 	cjne	r2,#0x01,00104$
   01BD 80 17               840 	sjmp	00103$
   01BF                     841 00102$:
                            842 ;	usrp_main.c:95: EP0BUF[0] = g_tx_underrun;
   01BF 90 E7 40            843 	mov	dptr,#_EP0BUF
   01C2 E5 0B               844 	mov	a,_g_tx_underrun
   01C4 F0                  845 	movx	@dptr,a
                            846 ;	usrp_main.c:96: g_tx_underrun = 0;
   01C5 75 0B 00            847 	mov	_g_tx_underrun,#0x00
                            848 ;	usrp_main.c:97: EP0BCH = 0;
   01C8 90 E6 8A            849 	mov	dptr,#_EP0BCH
   01CB E4                  850 	clr	a
   01CC F0                  851 	movx	@dptr,a
                            852 ;	usrp_main.c:98: EP0BCL = 1;
   01CD 90 E6 8B            853 	mov	dptr,#_EP0BCL
   01D0 74 01               854 	mov	a,#0x01
   01D2 F0                  855 	movx	@dptr,a
                            856 ;	usrp_main.c:99: break;
   01D3 02 03 8D            857 	ljmp	00143$
                            858 ;	usrp_main.c:101: case GS_RX_OVERRUN:
   01D6                     859 00103$:
                            860 ;	usrp_main.c:102: EP0BUF[0] = g_rx_overrun;
   01D6 90 E7 40            861 	mov	dptr,#_EP0BUF
   01D9 E5 0A               862 	mov	a,_g_rx_overrun
   01DB F0                  863 	movx	@dptr,a
                            864 ;	usrp_main.c:103: g_rx_overrun = 0;
   01DC 75 0A 00            865 	mov	_g_rx_overrun,#0x00
                            866 ;	usrp_main.c:104: EP0BCH = 0;
   01DF 90 E6 8A            867 	mov	dptr,#_EP0BCH
   01E2 E4                  868 	clr	a
   01E3 F0                  869 	movx	@dptr,a
                            870 ;	usrp_main.c:105: EP0BCL = 1;
   01E4 90 E6 8B            871 	mov	dptr,#_EP0BCL
   01E7 74 01               872 	mov	a,#0x01
   01E9 F0                  873 	movx	@dptr,a
                            874 ;	usrp_main.c:106: break;
   01EA 02 03 8D            875 	ljmp	00143$
                            876 ;	usrp_main.c:108: default:
   01ED                     877 00104$:
                            878 ;	usrp_main.c:109: return 0;
   01ED 75 82 00            879 	mov	dpl,#0x00
   01F0 22                  880 	ret
                            881 ;	usrp_main.c:113: case VRQ_I2C_READ:
   01F1                     882 00106$:
                            883 ;	usrp_main.c:114: if (!i2c_read (wValueL, EP0BUF, wLengthL))
   01F1 90 E6 BA            884 	mov	dptr,#(_SETUPDAT + 0x0002)
   01F4 E0                  885 	movx	a,@dptr
   01F5 FA                  886 	mov	r2,a
   01F6 75 1B 40            887 	mov	_i2c_read_PARM_2,#_EP0BUF
   01F9 75 1C E7            888 	mov	(_i2c_read_PARM_2 + 1),#(_EP0BUF >> 8)
   01FC 90 E6 BE            889 	mov	dptr,#(_SETUPDAT + 0x0006)
   01FF E0                  890 	movx	a,@dptr
   0200 F5 1D               891 	mov	_i2c_read_PARM_3,a
   0202 8A 82               892 	mov	dpl,r2
   0204 12 0A 81            893 	lcall	_i2c_read
   0207 E5 82               894 	mov	a,dpl
                            895 ;	usrp_main.c:115: return 0;
   0209 70 03               896 	jnz	00108$
   020B F5 82               897 	mov	dpl,a
   020D 22                  898 	ret
   020E                     899 00108$:
                            900 ;	usrp_main.c:117: EP0BCH = 0;
   020E 90 E6 8A            901 	mov	dptr,#_EP0BCH
   0211 E4                  902 	clr	a
   0212 F0                  903 	movx	@dptr,a
                            904 ;	usrp_main.c:118: EP0BCL = wLengthL;
   0213 90 E6 BE            905 	mov	dptr,#(_SETUPDAT + 0x0006)
   0216 E0                  906 	movx	a,@dptr
   0217 FA                  907 	mov	r2,a
   0218 90 E6 8B            908 	mov	dptr,#_EP0BCL
   021B F0                  909 	movx	@dptr,a
                            910 ;	usrp_main.c:119: break;
   021C 02 03 8D            911 	ljmp	00143$
                            912 ;	usrp_main.c:121: case VRQ_SPI_READ:
   021F                     913 00109$:
                            914 ;	usrp_main.c:122: if (!spi_read (wValueH, wValueL, wIndexH, wIndexL, EP0BUF, wLengthL))
   021F 90 E6 BB            915 	mov	dptr,#(_SETUPDAT + 0x0003)
   0222 E0                  916 	movx	a,@dptr
   0223 FA                  917 	mov	r2,a
   0224 90 E6 BA            918 	mov	dptr,#(_SETUPDAT + 0x0002)
   0227 E0                  919 	movx	a,@dptr
   0228 F5 22               920 	mov	_spi_read_PARM_2,a
   022A 90 E6 BD            921 	mov	dptr,#(_SETUPDAT + 0x0005)
   022D E0                  922 	movx	a,@dptr
   022E F5 23               923 	mov	_spi_read_PARM_3,a
   0230 90 E6 BC            924 	mov	dptr,#(_SETUPDAT + 0x0004)
   0233 E0                  925 	movx	a,@dptr
   0234 F5 24               926 	mov	_spi_read_PARM_4,a
   0236 75 25 40            927 	mov	_spi_read_PARM_5,#_EP0BUF
   0239 75 26 E7            928 	mov	(_spi_read_PARM_5 + 1),#(_EP0BUF >> 8)
   023C 90 E6 BE            929 	mov	dptr,#(_SETUPDAT + 0x0006)
   023F E0                  930 	movx	a,@dptr
   0240 F5 27               931 	mov	_spi_read_PARM_6,a
   0242 8A 82               932 	mov	dpl,r2
   0244 12 08 4C            933 	lcall	_spi_read
   0247 E5 82               934 	mov	a,dpl
                            935 ;	usrp_main.c:123: return 0;
   0249 70 03               936 	jnz	00111$
   024B F5 82               937 	mov	dpl,a
   024D 22                  938 	ret
   024E                     939 00111$:
                            940 ;	usrp_main.c:125: EP0BCH = 0;
   024E 90 E6 8A            941 	mov	dptr,#_EP0BCH
   0251 E4                  942 	clr	a
   0252 F0                  943 	movx	@dptr,a
                            944 ;	usrp_main.c:126: EP0BCL = wLengthL;
   0253 90 E6 BE            945 	mov	dptr,#(_SETUPDAT + 0x0006)
   0256 E0                  946 	movx	a,@dptr
   0257 FA                  947 	mov	r2,a
   0258 90 E6 8B            948 	mov	dptr,#_EP0BCL
   025B F0                  949 	movx	@dptr,a
                            950 ;	usrp_main.c:127: break;
   025C 02 03 8D            951 	ljmp	00143$
                            952 ;	usrp_main.c:129: default:
   025F                     953 00112$:
                            954 ;	usrp_main.c:130: return 0;
   025F 75 82 00            955 	mov	dpl,#0x00
   0262 22                  956 	ret
                            957 ;	usrp_main.c:131: }
   0263                     958 00142$:
                            959 ;	usrp_main.c:134: else if (bRequestType == VRT_VENDOR_OUT){
   0263 90 E6 B8            960 	mov	dptr,#_SETUPDAT
   0266 E0                  961 	movx	a,@dptr
   0267 FA                  962 	mov	r2,a
   0268 BA 40 02            963 	cjne	r2,#0x40,00172$
   026B 80 03               964 	sjmp	00173$
   026D                     965 00172$:
   026D 02 03 89            966 	ljmp	00139$
   0270                     967 00173$:
                            968 ;	usrp_main.c:140: switch (bRequest){
   0270 90 E6 B9            969 	mov	dptr,#(_SETUPDAT + 0x0001)
   0273 E0                  970 	movx	a,@dptr
   0274 FA                  971 	mov  r2,a
   0275 24 F4               972 	add	a,#0xff - 0x0B
   0277 50 03               973 	jnc	00174$
   0279 02 03 85            974 	ljmp	00136$
   027C                     975 00174$:
   027C EA                  976 	mov	a,r2
   027D 2A                  977 	add	a,r2
   027E 2A                  978 	add	a,r2
   027F 90 02 83            979 	mov	dptr,#00175$
   0282 73                  980 	jmp	@a+dptr
   0283                     981 00175$:
   0283 02 03 85            982 	ljmp	00136$
   0286 02 02 A7            983 	ljmp	00114$
   0289 02 02 CF            984 	ljmp	00119$
   028C 02 03 85            985 	ljmp	00136$
   028F 02 02 F9            986 	ljmp	00125$
   0292 02 03 05            987 	ljmp	00126$
   0295 02 03 11            988 	ljmp	00127$
   0298 02 03 85            989 	ljmp	00136$
   029B 02 03 33            990 	ljmp	00130$
   029E 02 03 53            991 	ljmp	00133$
   02A1 02 03 1D            992 	ljmp	00128$
   02A4 02 03 28            993 	ljmp	00129$
                            994 ;	usrp_main.c:142: case VRQ_SET_LED:
   02A7                     995 00114$:
                            996 ;	usrp_main.c:143: switch (wIndexL){
   02A7 90 E6 BC            997 	mov	dptr,#(_SETUPDAT + 0x0004)
   02AA E0                  998 	movx	a,@dptr
   02AB FA                  999 	mov	r2,a
   02AC 60 05              1000 	jz	00115$
                           1001 ;	usrp_main.c:144: case 0:
   02AE BA 01 1A           1002 	cjne	r2,#0x01,00117$
   02B1 80 0C              1003 	sjmp	00116$
   02B3                    1004 00115$:
                           1005 ;	usrp_main.c:145: set_led_0 (wValueL);
   02B3 90 E6 BA           1006 	mov	dptr,#(_SETUPDAT + 0x0002)
   02B6 E0                 1007 	movx	a,@dptr
   02B7 F5 82              1008 	mov	dpl,a
   02B9 12 05 BE           1009 	lcall	_set_led_0
                           1010 ;	usrp_main.c:146: break;
   02BC 02 03 8D           1011 	ljmp	00143$
                           1012 ;	usrp_main.c:148: case 1:
   02BF                    1013 00116$:
                           1014 ;	usrp_main.c:149: set_led_1 (wValueL);
   02BF 90 E6 BA           1015 	mov	dptr,#(_SETUPDAT + 0x0002)
   02C2 E0                 1016 	movx	a,@dptr
   02C3 F5 82              1017 	mov	dpl,a
   02C5 12 05 CB           1018 	lcall	_set_led_1
                           1019 ;	usrp_main.c:150: break;
   02C8 02 03 8D           1020 	ljmp	00143$
                           1021 ;	usrp_main.c:152: default:
   02CB                    1022 00117$:
                           1023 ;	usrp_main.c:153: return 0;
   02CB 75 82 00           1024 	mov	dpl,#0x00
   02CE 22                 1025 	ret
                           1026 ;	usrp_main.c:157: case VRQ_FPGA_LOAD:
   02CF                    1027 00119$:
                           1028 ;	usrp_main.c:158: switch (wIndexL){			// sub-command
   02CF 90 E6 BC           1029 	mov	dptr,#(_SETUPDAT + 0x0004)
   02D2 E0                 1030 	movx	a,@dptr
   02D3 FA                 1031 	mov	r2,a
   02D4 60 0A              1032 	jz	00120$
   02D6 BA 01 02           1033 	cjne	r2,#0x01,00179$
   02D9 80 08              1034 	sjmp	00121$
   02DB                    1035 00179$:
                           1036 ;	usrp_main.c:159: case FL_BEGIN:
   02DB BA 02 17           1037 	cjne	r2,#0x02,00123$
   02DE 80 12              1038 	sjmp	00122$
   02E0                    1039 00120$:
                           1040 ;	usrp_main.c:160: return fpga_load_begin ();
   02E0 02 06 60           1041 	ljmp	_fpga_load_begin
                           1042 ;	usrp_main.c:162: case FL_XFER:
   02E3                    1043 00121$:
                           1044 ;	usrp_main.c:163: get_ep0_data ();
   02E3 12 01 80           1045 	lcall	_get_ep0_data
                           1046 ;	usrp_main.c:164: return fpga_load_xfer (EP0BUF, EP0BCL);
   02E6 90 E6 8B           1047 	mov	dptr,#_EP0BCL
   02E9 E0                 1048 	movx	a,@dptr
   02EA F5 12              1049 	mov	_fpga_load_xfer_PARM_2,a
   02EC 90 E7 40           1050 	mov	dptr,#_EP0BUF
   02EF 02 06 CF           1051 	ljmp	_fpga_load_xfer
                           1052 ;	usrp_main.c:166: case FL_END:
   02F2                    1053 00122$:
                           1054 ;	usrp_main.c:167: return fpga_load_end ();
   02F2 02 06 DF           1055 	ljmp	_fpga_load_end
                           1056 ;	usrp_main.c:169: default:
   02F5                    1057 00123$:
                           1058 ;	usrp_main.c:170: return 0;
   02F5 75 82 00           1059 	mov	dpl,#0x00
   02F8 22                 1060 	ret
                           1061 ;	usrp_main.c:175: case VRQ_FPGA_SET_RESET:
   02F9                    1062 00125$:
                           1063 ;	usrp_main.c:176: fpga_set_reset (wValueL);
   02F9 90 E6 BA           1064 	mov	dptr,#(_SETUPDAT + 0x0002)
   02FC E0                 1065 	movx	a,@dptr
   02FD F5 82              1066 	mov	dpl,a
   02FF 12 07 41           1067 	lcall	_fpga_set_reset
                           1068 ;	usrp_main.c:177: break;
   0302 02 03 8D           1069 	ljmp	00143$
                           1070 ;	usrp_main.c:179: case VRQ_FPGA_SET_TX_ENABLE:
   0305                    1071 00126$:
                           1072 ;	usrp_main.c:180: fpga_set_tx_enable (wValueL);
   0305 90 E6 BA           1073 	mov	dptr,#(_SETUPDAT + 0x0002)
   0308 E0                 1074 	movx	a,@dptr
   0309 F5 82              1075 	mov	dpl,a
   030B 12 07 5C           1076 	lcall	_fpga_set_tx_enable
                           1077 ;	usrp_main.c:181: break;
   030E 02 03 8D           1078 	ljmp	00143$
                           1079 ;	usrp_main.c:183: case VRQ_FPGA_SET_RX_ENABLE:
   0311                    1080 00127$:
                           1081 ;	usrp_main.c:184: fpga_set_rx_enable (wValueL);
   0311 90 E6 BA           1082 	mov	dptr,#(_SETUPDAT + 0x0002)
   0314 E0                 1083 	movx	a,@dptr
   0315 F5 82              1084 	mov	dpl,a
   0317 12 07 77           1085 	lcall	_fpga_set_rx_enable
                           1086 ;	usrp_main.c:185: break;
   031A 02 03 8D           1087 	ljmp	00143$
                           1088 ;	usrp_main.c:187: case VRQ_FPGA_SET_TX_RESET:
   031D                    1089 00128$:
                           1090 ;	usrp_main.c:188: fpga_set_tx_reset (wValueL);
   031D 90 E6 BA           1091 	mov	dptr,#(_SETUPDAT + 0x0002)
   0320 E0                 1092 	movx	a,@dptr
   0321 F5 82              1093 	mov	dpl,a
   0323 12 07 92           1094 	lcall	_fpga_set_tx_reset
                           1095 ;	usrp_main.c:189: break;
                           1096 ;	usrp_main.c:191: case VRQ_FPGA_SET_RX_RESET:
   0326 80 65              1097 	sjmp	00143$
   0328                    1098 00129$:
                           1099 ;	usrp_main.c:192: fpga_set_rx_reset (wValueL);
   0328 90 E6 BA           1100 	mov	dptr,#(_SETUPDAT + 0x0002)
   032B E0                 1101 	movx	a,@dptr
   032C F5 82              1102 	mov	dpl,a
   032E 12 07 9C           1103 	lcall	_fpga_set_rx_reset
                           1104 ;	usrp_main.c:193: break;
                           1105 ;	usrp_main.c:195: case VRQ_I2C_WRITE:
   0331 80 5A              1106 	sjmp	00143$
   0333                    1107 00130$:
                           1108 ;	usrp_main.c:196: get_ep0_data ();
   0333 12 01 80           1109 	lcall	_get_ep0_data
                           1110 ;	usrp_main.c:197: if (!i2c_write (wValueL, EP0BUF, EP0BCL))
   0336 90 E6 BA           1111 	mov	dptr,#(_SETUPDAT + 0x0002)
   0339 E0                 1112 	movx	a,@dptr
   033A FA                 1113 	mov	r2,a
   033B 75 1B 40           1114 	mov	_i2c_write_PARM_2,#_EP0BUF
   033E 75 1C E7           1115 	mov	(_i2c_write_PARM_2 + 1),#(_EP0BUF >> 8)
   0341 90 E6 8B           1116 	mov	dptr,#_EP0BCL
   0344 E0                 1117 	movx	a,@dptr
   0345 F5 1D              1118 	mov	_i2c_write_PARM_3,a
   0347 8A 82              1119 	mov	dpl,r2
   0349 12 0B 41           1120 	lcall	_i2c_write
   034C E5 82              1121 	mov	a,dpl
                           1122 ;	usrp_main.c:198: return 0;
   034E 70 3D              1123 	jnz	00143$
   0350 F5 82              1124 	mov	dpl,a
                           1125 ;	usrp_main.c:201: case VRQ_SPI_WRITE:
   0352 22                 1126 	ret
   0353                    1127 00133$:
                           1128 ;	usrp_main.c:202: get_ep0_data ();
   0353 12 01 80           1129 	lcall	_get_ep0_data
                           1130 ;	usrp_main.c:203: if (!spi_write (wValueH, wValueL, wIndexH, wIndexL, EP0BUF, EP0BCL))
   0356 90 E6 BB           1131 	mov	dptr,#(_SETUPDAT + 0x0003)
   0359 E0                 1132 	movx	a,@dptr
   035A FA                 1133 	mov	r2,a
   035B 90 E6 BA           1134 	mov	dptr,#(_SETUPDAT + 0x0002)
   035E E0                 1135 	movx	a,@dptr
   035F F5 28              1136 	mov	_spi_write_PARM_2,a
   0361 90 E6 BD           1137 	mov	dptr,#(_SETUPDAT + 0x0005)
   0364 E0                 1138 	movx	a,@dptr
   0365 F5 29              1139 	mov	_spi_write_PARM_3,a
   0367 90 E6 BC           1140 	mov	dptr,#(_SETUPDAT + 0x0004)
   036A E0                 1141 	movx	a,@dptr
   036B F5 2A              1142 	mov	_spi_write_PARM_4,a
   036D 75 2B 40           1143 	mov	_spi_write_PARM_5,#_EP0BUF
   0370 75 2C E7           1144 	mov	(_spi_write_PARM_5 + 1),#(_EP0BUF >> 8)
   0373 90 E6 8B           1145 	mov	dptr,#_EP0BCL
   0376 E0                 1146 	movx	a,@dptr
   0377 F5 2D              1147 	mov	_spi_write_PARM_6,a
   0379 8A 82              1148 	mov	dpl,r2
   037B 12 08 BA           1149 	lcall	_spi_write
   037E E5 82              1150 	mov	a,dpl
                           1151 ;	usrp_main.c:204: return 0;
   0380 70 0B              1152 	jnz	00143$
   0382 F5 82              1153 	mov	dpl,a
                           1154 ;	usrp_main.c:207: default:
   0384 22                 1155 	ret
   0385                    1156 00136$:
                           1157 ;	usrp_main.c:208: return 0;
   0385 75 82 00           1158 	mov	dpl,#0x00
                           1159 ;	usrp_main.c:209: }
   0388 22                 1160 	ret
   0389                    1161 00139$:
                           1162 ;	usrp_main.c:213: return 0;    // invalid bRequestType
   0389 75 82 00           1163 	mov	dpl,#0x00
                           1164 ;	usrp_main.c:215: return 1;
   038C 22                 1165 	ret
   038D                    1166 00143$:
   038D 75 82 01           1167 	mov	dpl,#0x01
   0390 22                 1168 	ret
                           1169 ;------------------------------------------------------------
                           1170 ;Allocation info for local variables in function 'main_loop'
                           1171 ;------------------------------------------------------------
                           1172 ;------------------------------------------------------------
                           1173 ;	usrp_main.c:221: main_loop (void)
                           1174 ;	-----------------------------------------
                           1175 ;	 function main_loop
                           1176 ;	-----------------------------------------
   0391                    1177 _main_loop:
                           1178 ;	usrp_main.c:223: setup_flowstate_common ();
   0391 90 E6 C6           1179 	mov	dptr,#_FLOWSTATE
   0394 74 81              1180 	mov	a,#0x81
   0396 F0                 1181 	movx	@dptr,a
   0397 90 E6 C7           1182 	mov	dptr,#_FLOWLOGIC
   039A 74 2D              1183 	mov	a,#0x2D
   039C F0                 1184 	movx	@dptr,a
   039D 90 E6 C8           1185 	mov	dptr,#_FLOWEQ0CTL
   03A0 74 26              1186 	mov	a,#0x26
   03A2 F0                 1187 	movx	@dptr,a
   03A3 90 E6 C9           1188 	mov	dptr,#_FLOWEQ1CTL
   03A6 E4                 1189 	clr	a
   03A7 F0                 1190 	movx	@dptr,a
   03A8 90 E6 CA           1191 	mov	dptr,#_FLOWHOLDOFF
   03AB 74 04              1192 	mov	a,#0x04
   03AD F0                 1193 	movx	@dptr,a
   03AE 90 E6 CB           1194 	mov	dptr,#_FLOWSTB
   03B1 74 04              1195 	mov	a,#0x04
   03B3 F0                 1196 	movx	@dptr,a
   03B4 90 E6 CC           1197 	mov	dptr,#_FLOWSTBEDGE
   03B7 74 03              1198 	mov	a,#0x03
   03B9 F0                 1199 	movx	@dptr,a
   03BA 90 E6 CD           1200 	mov	dptr,#_FLOWSTBHPERIOD
   03BD 74 02              1201 	mov	a,#0x02
   03BF F0                 1202 	movx	@dptr,a
   03C0 90 E6 0C           1203 	mov	dptr,#_GPIFHOLDAMOUNT
   03C3 E4                 1204 	clr	a
   03C4 F0                 1205 	movx	@dptr,a
                           1206 ;	usrp_main.c:225: while (1){
   03C5                    1207 00141$:
                           1208 ;	usrp_main.c:227: if (usb_setup_packet_avail ())
   03C5 30 00 03           1209 	jnb	__usb_got_SUDAV,00105$
                           1210 ;	usrp_main.c:228: usb_handle_setup_packet ();
   03C8 12 0D 3C           1211 	lcall	_usb_handle_setup_packet
   03CB                    1212 00105$:
                           1213 ;	usrp_main.c:231: if (GPIFTRIG & bmGPIF_IDLE){
   03CB E5 BB              1214 	mov	a,_GPIFTRIG
   03CD 30 E7 F5           1215 	jnb	acc.7,00141$
                           1216 ;	usrp_main.c:237: if (UC_BOARD_HAS_FPGA && (USRP_PA & (bmPA_TX_UNDERRUN | bmPA_RX_OVERRUN))){
   03D0 E5 80              1217 	mov	a,_IOA
   03D2 54 C0              1218 	anl	a,#0xC0
   03D4 60 16              1219 	jz	00114$
                           1220 ;	usrp_main.c:240: if (USRP_PA & bmPA_TX_UNDERRUN)
   03D6 E5 80              1221 	mov	a,_IOA
   03D8 30 E7 03           1222 	jnb	acc.7,00107$
                           1223 ;	usrp_main.c:241: g_tx_underrun = 1;
   03DB 75 0B 01           1224 	mov	_g_tx_underrun,#0x01
   03DE                    1225 00107$:
                           1226 ;	usrp_main.c:243: if (USRP_PA & bmPA_RX_OVERRUN)
   03DE E5 80              1227 	mov	a,_IOA
   03E0 30 E6 03           1228 	jnb	acc.6,00110$
                           1229 ;	usrp_main.c:244: g_rx_overrun = 1;
   03E3 75 0A 01           1230 	mov	_g_rx_overrun,#0x01
                           1231 ;	usrp_main.c:247: fpga_clear_flags ();
   03E6                    1232 00110$:
   03E6 43 B1 08           1233 	orl	_IOE,#0x08
   03E9 53 B1 F7           1234 	anl	_IOE,#0xF7
   03EC                    1235 00114$:
                           1236 ;	usrp_main.c:253: if (g_tx_enable && !(EP24FIFOFLGS & 0x02)){  // USB end point fifo is not empty...
   03EC E5 08              1237 	mov	a,_g_tx_enable
   03EE 60 2A              1238 	jz	00125$
   03F0 E5 AB              1239 	mov	a,_EP24FIFOFLGS
   03F2 20 E1 25           1240 	jb	acc.1,00125$
                           1241 ;	usrp_main.c:255: if (fpga_has_room_for_packet ()){	   // ... and FPGA has room for packet
   03F5 90 E6 F4           1242 	mov	dptr,#_GPIFREADYSTAT
   03F8 E0                 1243 	movx	a,@dptr
   03F9 FA                 1244 	mov	r2,a
   03FA 30 E0 1D           1245 	jnb	acc.0,00125$
                           1246 ;	usrp_main.c:257: GPIFTCB1 = 0x01;	SYNCDELAY;
   03FD 90 E6 D0           1247 	mov	dptr,#_GPIFTCB1
   0400 74 01              1248 	mov	a,#0x01
   0402 F0                 1249 	movx	@dptr,a
   0403 00                 1250 	 nop; nop; nop; 
                           1251 ;	usrp_main.c:258: GPIFTCB0 = 0x00;	SYNCDELAY;
   0404 90 E6 D1           1252 	mov	dptr,#_GPIFTCB0
   0407 E4                 1253 	clr	a
   0408 F0                 1254 	movx	@dptr,a
   0409 00                 1255 	 nop; nop; nop; 
                           1256 ;	usrp_main.c:260: setup_flowstate_write ();
   040A 90 E6 C8           1257 	mov	dptr,#_FLOWEQ0CTL
   040D 74 21              1258 	mov	a,#0x21
   040F F0                 1259 	movx	@dptr,a
                           1260 ;	usrp_main.c:262: SYNCDELAY;
   0410 00                 1261 	 nop; nop; nop; 
                           1262 ;	usrp_main.c:263: GPIFTRIG = bmGPIF_EP2_START | bmGPIF_WRITE; 	// start the xfer
   0411 75 BB 00           1263 	mov	_GPIFTRIG,#0x00
                           1264 ;	usrp_main.c:264: SYNCDELAY;
   0414 00                 1265 	 nop; nop; nop; 
                           1266 ;	usrp_main.c:266: while (!(GPIFTRIG & bmGPIF_IDLE)){
   0415                    1267 00119$:
   0415 E5 BB              1268 	mov	a,_GPIFTRIG
   0417 30 E7 FB           1269 	jnb	acc.7,00119$
   041A                    1270 00125$:
                           1271 ;	usrp_main.c:275: if (g_rx_enable && !(EP6CS & bmEPFULL)){	// USB end point fifo is not full...
   041A E5 09              1272 	mov	a,_g_rx_enable
   041C 60 A7              1273 	jz	00141$
   041E 90 E6 A5           1274 	mov	dptr,#_EP6CS
   0421 E0                 1275 	movx	a,@dptr
   0422 FA                 1276 	mov	r2,a
   0423 20 E3 9F           1277 	jb	acc.3,00141$
                           1278 ;	usrp_main.c:277: if (fpga_has_packet_avail ()){		// ... and FPGA has packet available
   0426 90 E6 F4           1279 	mov	dptr,#_GPIFREADYSTAT
   0429 E0                 1280 	movx	a,@dptr
   042A FA                 1281 	mov	r2,a
   042B 30 E1 97           1282 	jnb	acc.1,00141$
                           1283 ;	usrp_main.c:279: GPIFTCB1 = 0x01;	SYNCDELAY;
   042E 90 E6 D0           1284 	mov	dptr,#_GPIFTCB1
   0431 74 01              1285 	mov	a,#0x01
   0433 F0                 1286 	movx	@dptr,a
   0434 00                 1287 	 nop; nop; nop; 
                           1288 ;	usrp_main.c:280: GPIFTCB0 = 0x00;	SYNCDELAY;
   0435 90 E6 D1           1289 	mov	dptr,#_GPIFTCB0
   0438 E4                 1290 	clr	a
   0439 F0                 1291 	movx	@dptr,a
   043A 00                 1292 	 nop; nop; nop; 
                           1293 ;	usrp_main.c:282: setup_flowstate_read ();
   043B 90 E6 C8           1294 	mov	dptr,#_FLOWEQ0CTL
   043E 74 26              1295 	mov	a,#0x26
   0440 F0                 1296 	movx	@dptr,a
                           1297 ;	usrp_main.c:284: SYNCDELAY;
   0441 00                 1298 	 nop; nop; nop; 
                           1299 ;	usrp_main.c:285: GPIFTRIG = bmGPIF_EP6_START | bmGPIF_READ; 	// start the xfer
   0442 75 BB 06           1300 	mov	_GPIFTRIG,#0x06
                           1301 ;	usrp_main.c:286: SYNCDELAY;
   0445 00                 1302 	 nop; nop; nop; 
                           1303 ;	usrp_main.c:288: while (!(GPIFTRIG & bmGPIF_IDLE)){
   0446                    1304 00130$:
   0446 E5 BB              1305 	mov	a,_GPIFTRIG
   0448 30 E7 FB           1306 	jnb	acc.7,00130$
                           1307 ;	usrp_main.c:292: SYNCDELAY;
   044B 00                 1308 	 nop; nop; nop; 
                           1309 ;	usrp_main.c:293: INPKTEND = 6;	// tell USB we filled buffer (6 is our endpoint num)
   044C 90 E6 48           1310 	mov	dptr,#_INPKTEND
   044F 74 06              1311 	mov	a,#0x06
   0451 F0                 1312 	movx	@dptr,a
   0452 02 03 C5           1313 	ljmp	00141$
                           1314 ;------------------------------------------------------------
                           1315 ;Allocation info for local variables in function 'isr_tick'
                           1316 ;------------------------------------------------------------
                           1317 ;count                     Allocated with name '_isr_tick_count_1_1'
                           1318 ;------------------------------------------------------------
                           1319 ;	usrp_main.c:307: isr_tick (void) interrupt
                           1320 ;	-----------------------------------------
                           1321 ;	 function isr_tick
                           1322 ;	-----------------------------------------
   0455                    1323 _isr_tick:
   0455 C0 E0              1324 	push	acc
                           1325 ;	usrp_main.c:311: if (--count == 0){
   0457 D5 0C 06           1326 	djnz	_isr_tick_count_1_1,00102$
                           1327 ;	usrp_main.c:312: count = 50;
   045A 75 0C 32           1328 	mov	_isr_tick_count_1_1,#0x32
                           1329 ;	usrp_main.c:313: USRP_LED_REG ^= bmLED0;
   045D 63 A0 40           1330 	xrl	_IOC,#0x40
   0460                    1331 00102$:
                           1332 ;	usrp_main.c:316: clear_timer_irq ();
   0460 C2 CF              1333 	clr	_TF2
   0462 D0 E0              1334 	pop	acc
   0464 32                 1335 	reti
                           1336 ;	eliminated unneeded push/pop psw
                           1337 ;	eliminated unneeded push/pop dpl
                           1338 ;	eliminated unneeded push/pop dph
                           1339 ;	eliminated unneeded push/pop b
                           1340 ;------------------------------------------------------------
                           1341 ;Allocation info for local variables in function 'patch_usb_descriptors'
                           1342 ;------------------------------------------------------------
                           1343 ;i                         Allocated to registers r2 
                           1344 ;ch                        Allocated to registers r3 
                           1345 ;hw_rev                    Allocated with name '_patch_usb_descriptors_hw_rev_1_1'
                           1346 ;serial_no                 Allocated with name '_patch_usb_descriptors_serial_no_1_1'
                           1347 ;------------------------------------------------------------
                           1348 ;	usrp_main.c:324: patch_usb_descriptors(void)
                           1349 ;	-----------------------------------------
                           1350 ;	 function patch_usb_descriptors
                           1351 ;	-----------------------------------------
   0465                    1352 _patch_usb_descriptors:
                           1353 ;	usrp_main.c:330: eeprom_read(I2C_ADDR_BOOT, HW_REV_OFFSET, &hw_rev, 1);	// LSB of device id
   0465 75 18 00           1354 	mov	_eeprom_read_PARM_3,#_patch_usb_descriptors_hw_rev_1_1
   0468 75 19 18           1355 	mov	(_eeprom_read_PARM_3 + 1),#(_patch_usb_descriptors_hw_rev_1_1 >> 8)
   046B 75 17 05           1356 	mov	_eeprom_read_PARM_2,#0x05
   046E 75 1A 01           1357 	mov	_eeprom_read_PARM_4,#0x01
   0471 75 82 50           1358 	mov	dpl,#0x50
   0474 12 09 EA           1359 	lcall	_eeprom_read
                           1360 ;	usrp_main.c:331: usb_desc_hw_rev_binary_patch_location_0[0] = hw_rev;
   0477 90 18 00           1361 	mov	dptr,#_patch_usb_descriptors_hw_rev_1_1
   047A E0                 1362 	movx	a,@dptr
   047B FA                 1363 	mov	r2,a
   047C 90 E0 0C           1364 	mov	dptr,#_usb_desc_hw_rev_binary_patch_location_0
   047F F0                 1365 	movx	@dptr,a
                           1366 ;	usrp_main.c:332: usb_desc_hw_rev_binary_patch_location_1[0] = hw_rev;
   0480 90 E0 5A           1367 	mov	dptr,#_usb_desc_hw_rev_binary_patch_location_1
   0483 EA                 1368 	mov	a,r2
   0484 F0                 1369 	movx	@dptr,a
                           1370 ;	usrp_main.c:333: usb_desc_hw_rev_ascii_patch_location_0[0] = hw_rev + '0';     // FIXME if we get > 9
   0485 74 30              1371 	mov	a,#0x30
   0487 2A                 1372 	add	a,r2
   0488 90 E0 CE           1373 	mov	dptr,#_usb_desc_hw_rev_ascii_patch_location_0
   048B F0                 1374 	movx	@dptr,a
                           1375 ;	usrp_main.c:335: eeprom_read(I2C_ADDR_BOOT, SERIAL_NO_OFFSET, serial_no, SERIAL_NO_LEN);
   048C 75 18 01           1376 	mov	_eeprom_read_PARM_3,#_patch_usb_descriptors_serial_no_1_1
   048F 75 19 18           1377 	mov	(_eeprom_read_PARM_3 + 1),#(_patch_usb_descriptors_serial_no_1_1 >> 8)
   0492 75 17 F8           1378 	mov	_eeprom_read_PARM_2,#0xF8
   0495 75 1A 08           1379 	mov	_eeprom_read_PARM_4,#0x08
   0498 75 82 50           1380 	mov	dpl,#0x50
   049B 12 09 EA           1381 	lcall	_eeprom_read
                           1382 ;	usrp_main.c:337: for (i = 0; i < SERIAL_NO_LEN; i++){
   049E 7A 00              1383 	mov	r2,#0x00
   04A0                    1384 00103$:
   04A0 BA 08 00           1385 	cjne	r2,#0x08,00113$
   04A3                    1386 00113$:
   04A3 50 29              1387 	jnc	00107$
                           1388 ;	usrp_main.c:338: unsigned char ch = serial_no[i];
   04A5 EA                 1389 	mov	a,r2
   04A6 24 01              1390 	add	a,#_patch_usb_descriptors_serial_no_1_1
   04A8 F5 82              1391 	mov	dpl,a
   04AA E4                 1392 	clr	a
   04AB 34 18              1393 	addc	a,#(_patch_usb_descriptors_serial_no_1_1 >> 8)
   04AD F5 83              1394 	mov	dph,a
   04AF E0                 1395 	movx	a,@dptr
   04B0 FB                 1396 	mov	r3,a
                           1397 ;	usrp_main.c:339: if (ch == 0xff)	// make unprogrammed EEPROM default to '0'
   04B1 BB FF 02           1398 	cjne	r3,#0xFF,00102$
                           1399 ;	usrp_main.c:340: ch = '0';
   04B4 7B 30              1400 	mov	r3,#0x30
   04B6                    1401 00102$:
                           1402 ;	usrp_main.c:341: usb_desc_serial_number_ascii[i << 1] = ch;
   04B6 8A 04              1403 	mov	ar4,r2
   04B8 E4                 1404 	clr	a
   04B9 CC                 1405 	xch	a,r4
   04BA 25 E0              1406 	add	a,acc
   04BC CC                 1407 	xch	a,r4
   04BD 33                 1408 	rlc	a
   04BE FD                 1409 	mov	r5,a
   04BF EC                 1410 	mov	a,r4
   04C0 24 2A              1411 	add	a,#_usb_desc_serial_number_ascii
   04C2 F5 82              1412 	mov	dpl,a
   04C4 ED                 1413 	mov	a,r5
   04C5 34 E1              1414 	addc	a,#(_usb_desc_serial_number_ascii >> 8)
   04C7 F5 83              1415 	mov	dph,a
   04C9 EB                 1416 	mov	a,r3
   04CA F0                 1417 	movx	@dptr,a
                           1418 ;	usrp_main.c:337: for (i = 0; i < SERIAL_NO_LEN; i++){
   04CB 0A                 1419 	inc	r2
   04CC 80 D2              1420 	sjmp	00103$
   04CE                    1421 00107$:
   04CE 22                 1422 	ret
                           1423 ;------------------------------------------------------------
                           1424 ;Allocation info for local variables in function 'main'
                           1425 ;------------------------------------------------------------
                           1426 ;------------------------------------------------------------
                           1427 ;	usrp_main.c:346: main (void)
                           1428 ;	-----------------------------------------
                           1429 ;	 function main
                           1430 ;	-----------------------------------------
   04CF                    1431 _main:
                           1432 ;	usrp_main.c:355: memset (hash1, 0, USRP_HASH_SIZE);	// zero fpga bitstream hash.  This forces reload
   04CF 75 1B 00           1433 	mov	_memset_PARM_2,#0x00
   04D2 75 1C 10           1434 	mov	_memset_PARM_3,#0x10
   04D5 E4                 1435 	clr	a
   04D6 F5 1D              1436 	mov	(_memset_PARM_3 + 1),a
   04D8 90 E1 F0           1437 	mov	dptr,#_hash1
   04DB 75 F0 00           1438 	mov	b,#0x00
   04DE 12 0B BA           1439 	lcall	_memset
                           1440 ;	usrp_main.c:357: init_usrp ();
   04E1 12 05 1A           1441 	lcall	_init_usrp
                           1442 ;	usrp_main.c:358: init_gpif ();
   04E4 12 07 A6           1443 	lcall	_init_gpif
                           1444 ;	usrp_main.c:361: IFCONFIG |= bmGSTATE;			// no conflict, start with it on
   04E7 90 E6 01           1445 	mov	dptr,#_IFCONFIG
   04EA E0                 1446 	movx	a,@dptr
   04EB 44 04              1447 	orl	a,#0x04
   04ED F0                 1448 	movx	@dptr,a
                           1449 ;	usrp_main.c:363: set_led_0 (0);
   04EE 75 82 00           1450 	mov	dpl,#0x00
   04F1 12 05 BE           1451 	lcall	_set_led_0
                           1452 ;	usrp_main.c:364: set_led_1 (0);
   04F4 75 82 00           1453 	mov	dpl,#0x00
   04F7 12 05 CB           1454 	lcall	_set_led_1
                           1455 ;	usrp_main.c:366: EA = 0;		// disable all interrupts
   04FA C2 AF              1456 	clr	_EA
                           1457 ;	usrp_main.c:368: patch_usb_descriptors();
   04FC 12 04 65           1458 	lcall	_patch_usb_descriptors
                           1459 ;	usrp_main.c:370: setup_autovectors ();
   04FF 12 11 22           1460 	lcall	_setup_autovectors
                           1461 ;	usrp_main.c:371: usb_install_handlers ();
   0502 12 0C A6           1462 	lcall	_usb_install_handlers
                           1463 ;	usrp_main.c:372: hook_timer_tick ((unsigned short) isr_tick);
   0505 7A 55              1464 	mov	r2,#_isr_tick
   0507 7B 04              1465 	mov	r3,#(_isr_tick >> 8)
   0509 8A 82              1466 	mov	dpl,r2
   050B 8B 83              1467 	mov	dph,r3
   050D 12 11 CA           1468 	lcall	_hook_timer_tick
                           1469 ;	usrp_main.c:374: EIEX4 = 1;		// disable INT4 FIXME
   0510 D2 EA              1470 	setb	_EIEX4
                           1471 ;	usrp_main.c:375: EA = 1;		// global interrupt enable
   0512 D2 AF              1472 	setb	_EA
                           1473 ;	usrp_main.c:377: fx2_renumerate ();	// simulates disconnect / reconnect
   0514 12 0A 5D           1474 	lcall	_fx2_renumerate
                           1475 ;	usrp_main.c:379: main_loop ();
   0517 02 03 91           1476 	ljmp	_main_loop
                           1477 	.area CSEG    (CODE)
                           1478 	.area CONST   (CODE)
                           1479 	.area CABS    (ABS,CODE)

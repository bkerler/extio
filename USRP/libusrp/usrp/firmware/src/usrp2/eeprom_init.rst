                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 2.9.0 #5416 (Mar 22 2009) (MINGW32)
                              4 ; This file was generated Tue Oct 12 23:27:12 2010
                              5 ;--------------------------------------------------------
                              6 	.module eeprom_init
                              7 	.optsdcc -mmcs51 --model-small
                              8 	
                              9 ;--------------------------------------------------------
                             10 ; Public variables in this module
                             11 ;--------------------------------------------------------
                             12 	.globl _eeprom_init
                             13 	.globl _write_both_9862s
                             14 	.globl _bitALTERA_DCLK
                             15 	.globl _bitALTERA_DATA0
                             16 	.globl _bitS_IN
                             17 	.globl _bitS_OUT
                             18 	.globl _bitS_CLK
                             19 	.globl _EIPX6
                             20 	.globl _EIPX5
                             21 	.globl _EIPX4
                             22 	.globl _PI2C
                             23 	.globl _PUSB
                             24 	.globl _EIEX6
                             25 	.globl _EIEX5
                             26 	.globl _EIEX4
                             27 	.globl _EI2C
                             28 	.globl _EIUSB
                             29 	.globl _SMOD1
                             30 	.globl _ERESI
                             31 	.globl _RESI
                             32 	.globl _INT6
                             33 	.globl _CY
                             34 	.globl _AC
                             35 	.globl _F0
                             36 	.globl _RS1
                             37 	.globl _RS0
                             38 	.globl _OV
                             39 	.globl _FL
                             40 	.globl _P
                             41 	.globl _TF2
                             42 	.globl _EXF2
                             43 	.globl _RCLK
                             44 	.globl _TCLK
                             45 	.globl _EXEN2
                             46 	.globl _TR2
                             47 	.globl _C_T2
                             48 	.globl _CP_RL2
                             49 	.globl _SM01
                             50 	.globl _SM11
                             51 	.globl _SM21
                             52 	.globl _REN1
                             53 	.globl _TB81
                             54 	.globl _RB81
                             55 	.globl _TI1
                             56 	.globl _RI1
                             57 	.globl _PS1
                             58 	.globl _PT2
                             59 	.globl _PS0
                             60 	.globl _PT1
                             61 	.globl _PX1
                             62 	.globl _PT0
                             63 	.globl _PX0
                             64 	.globl _EA
                             65 	.globl _ES1
                             66 	.globl _ET2
                             67 	.globl _ES0
                             68 	.globl _ET1
                             69 	.globl _EX1
                             70 	.globl _ET0
                             71 	.globl _EX0
                             72 	.globl _SM0
                             73 	.globl _SM1
                             74 	.globl _SM2
                             75 	.globl _REN
                             76 	.globl _TB8
                             77 	.globl _RB8
                             78 	.globl _TI
                             79 	.globl _RI
                             80 	.globl _TF1
                             81 	.globl _TR1
                             82 	.globl _TF0
                             83 	.globl _TR0
                             84 	.globl _IE1
                             85 	.globl _IT1
                             86 	.globl _IE0
                             87 	.globl _IT0
                             88 	.globl _SEL
                             89 	.globl _EIP
                             90 	.globl _B
                             91 	.globl _EIE
                             92 	.globl _ACC
                             93 	.globl _EICON
                             94 	.globl _PSW
                             95 	.globl _TH2
                             96 	.globl _TL2
                             97 	.globl _RCAP2H
                             98 	.globl _RCAP2L
                             99 	.globl _T2CON
                            100 	.globl _SBUF1
                            101 	.globl _SCON1
                            102 	.globl _GPIFSGLDATLNOX
                            103 	.globl _GPIFSGLDATLX
                            104 	.globl _GPIFSGLDATH
                            105 	.globl _GPIFTRIG
                            106 	.globl _EP01STAT
                            107 	.globl _IP
                            108 	.globl _OEE
                            109 	.globl _OED
                            110 	.globl _OEC
                            111 	.globl _OEB
                            112 	.globl _OEA
                            113 	.globl _IOE
                            114 	.globl _IOD
                            115 	.globl _AUTOPTRSETUP
                            116 	.globl _EP68FIFOFLGS
                            117 	.globl _EP24FIFOFLGS
                            118 	.globl _EP2468STAT
                            119 	.globl _IE
                            120 	.globl _INT4CLR
                            121 	.globl _INT2CLR
                            122 	.globl _IOC
                            123 	.globl _AUTODAT2
                            124 	.globl _AUTOPTRL2
                            125 	.globl _AUTOPTRH2
                            126 	.globl _AUTODAT1
                            127 	.globl _APTR1L
                            128 	.globl _APTR1H
                            129 	.globl _SBUF0
                            130 	.globl _SCON0
                            131 	.globl _MPAGE
                            132 	.globl _EXIF
                            133 	.globl _IOB
                            134 	.globl _CKCON
                            135 	.globl _TH1
                            136 	.globl _TH0
                            137 	.globl _TL1
                            138 	.globl _TL0
                            139 	.globl _TMOD
                            140 	.globl _TCON
                            141 	.globl _PCON
                            142 	.globl _DPS
                            143 	.globl _DPH1
                            144 	.globl _DPL1
                            145 	.globl _DPH
                            146 	.globl _DPL
                            147 	.globl _SP
                            148 	.globl _IOA
                            149 	.globl _hash0
                            150 	.globl _EP8FIFOBUF
                            151 	.globl _EP6FIFOBUF
                            152 	.globl _EP4FIFOBUF
                            153 	.globl _EP2FIFOBUF
                            154 	.globl _EP1INBUF
                            155 	.globl _EP1OUTBUF
                            156 	.globl _EP0BUF
                            157 	.globl _CT4
                            158 	.globl _CT3
                            159 	.globl _CT2
                            160 	.globl _CT1
                            161 	.globl _USBTEST
                            162 	.globl _TESTCFG
                            163 	.globl _DBUG
                            164 	.globl _UDMACRCQUAL
                            165 	.globl _UDMACRCL
                            166 	.globl _UDMACRCH
                            167 	.globl _GPIFHOLDAMOUNT
                            168 	.globl _FLOWSTBHPERIOD
                            169 	.globl _FLOWSTBEDGE
                            170 	.globl _FLOWSTB
                            171 	.globl _FLOWHOLDOFF
                            172 	.globl _FLOWEQ1CTL
                            173 	.globl _FLOWEQ0CTL
                            174 	.globl _FLOWLOGIC
                            175 	.globl _FLOWSTATE
                            176 	.globl _GPIFABORT
                            177 	.globl _GPIFREADYSTAT
                            178 	.globl _GPIFREADYCFG
                            179 	.globl _XGPIFSGLDATLNOX
                            180 	.globl _XGPIFSGLDATLX
                            181 	.globl _XGPIFSGLDATH
                            182 	.globl _EP8GPIFTRIG
                            183 	.globl _EP8GPIFPFSTOP
                            184 	.globl _EP8GPIFFLGSEL
                            185 	.globl _EP6GPIFTRIG
                            186 	.globl _EP6GPIFPFSTOP
                            187 	.globl _EP6GPIFFLGSEL
                            188 	.globl _EP4GPIFTRIG
                            189 	.globl _EP4GPIFPFSTOP
                            190 	.globl _EP4GPIFFLGSEL
                            191 	.globl _EP2GPIFTRIG
                            192 	.globl _EP2GPIFPFSTOP
                            193 	.globl _EP2GPIFFLGSEL
                            194 	.globl _GPIFTCB0
                            195 	.globl _GPIFTCB1
                            196 	.globl _GPIFTCB2
                            197 	.globl _GPIFTCB3
                            198 	.globl _GPIFADRL
                            199 	.globl _GPIFADRH
                            200 	.globl _GPIFCTLCFG
                            201 	.globl _GPIFIDLECTL
                            202 	.globl _GPIFIDLECS
                            203 	.globl _GPIFWFSELECT
                            204 	.globl _SETUPDAT
                            205 	.globl _SUDPTRCTL
                            206 	.globl _SUDPTRL
                            207 	.globl _SUDPTRH
                            208 	.globl _EP8FIFOBCL
                            209 	.globl _EP8FIFOBCH
                            210 	.globl _EP6FIFOBCL
                            211 	.globl _EP6FIFOBCH
                            212 	.globl _EP4FIFOBCL
                            213 	.globl _EP4FIFOBCH
                            214 	.globl _EP2FIFOBCL
                            215 	.globl _EP2FIFOBCH
                            216 	.globl _EP8FIFOFLGS
                            217 	.globl _EP6FIFOFLGS
                            218 	.globl _EP4FIFOFLGS
                            219 	.globl _EP2FIFOFLGS
                            220 	.globl _EP8CS
                            221 	.globl _EP6CS
                            222 	.globl _EP4CS
                            223 	.globl _EP2CS
                            224 	.globl _EP1INCS
                            225 	.globl _EP1OUTCS
                            226 	.globl _EP0CS
                            227 	.globl _EP8BCL
                            228 	.globl _EP8BCH
                            229 	.globl _EP6BCL
                            230 	.globl _EP6BCH
                            231 	.globl _EP4BCL
                            232 	.globl _EP4BCH
                            233 	.globl _EP2BCL
                            234 	.globl _EP2BCH
                            235 	.globl _EP1INBC
                            236 	.globl _EP1OUTBC
                            237 	.globl _EP0BCL
                            238 	.globl _EP0BCH
                            239 	.globl _FNADDR
                            240 	.globl _MICROFRAME
                            241 	.globl _USBFRAMEL
                            242 	.globl _USBFRAMEH
                            243 	.globl _TOGCTL
                            244 	.globl _WAKEUPCS
                            245 	.globl _SUSPEND
                            246 	.globl _USBCS
                            247 	.globl _XAUTODAT2
                            248 	.globl _XAUTODAT1
                            249 	.globl _I2CTL
                            250 	.globl _I2DAT
                            251 	.globl _I2CS
                            252 	.globl _PORTECFG
                            253 	.globl _PORTCCFG
                            254 	.globl _PORTACFG
                            255 	.globl _INTSETUP
                            256 	.globl _INT4IVEC
                            257 	.globl _INT2IVEC
                            258 	.globl _CLRERRCNT
                            259 	.globl _ERRCNTLIM
                            260 	.globl _USBERRIRQ
                            261 	.globl _USBERRIE
                            262 	.globl _GPIFIRQ
                            263 	.globl _GPIFIE
                            264 	.globl _EPIRQ
                            265 	.globl _EPIE
                            266 	.globl _USBIRQ
                            267 	.globl _USBIE
                            268 	.globl _NAKIRQ
                            269 	.globl _NAKIE
                            270 	.globl _IBNIRQ
                            271 	.globl _IBNIE
                            272 	.globl _EP8FIFOIRQ
                            273 	.globl _EP8FIFOIE
                            274 	.globl _EP6FIFOIRQ
                            275 	.globl _EP6FIFOIE
                            276 	.globl _EP4FIFOIRQ
                            277 	.globl _EP4FIFOIE
                            278 	.globl _EP2FIFOIRQ
                            279 	.globl _EP2FIFOIE
                            280 	.globl _OUTPKTEND
                            281 	.globl _INPKTEND
                            282 	.globl _EP8ISOINPKTS
                            283 	.globl _EP6ISOINPKTS
                            284 	.globl _EP4ISOINPKTS
                            285 	.globl _EP2ISOINPKTS
                            286 	.globl _EP8FIFOPFL
                            287 	.globl _EP8FIFOPFH
                            288 	.globl _EP6FIFOPFL
                            289 	.globl _EP6FIFOPFH
                            290 	.globl _EP4FIFOPFL
                            291 	.globl _EP4FIFOPFH
                            292 	.globl _EP2FIFOPFL
                            293 	.globl _EP2FIFOPFH
                            294 	.globl _EP8AUTOINLENL
                            295 	.globl _EP8AUTOINLENH
                            296 	.globl _EP6AUTOINLENL
                            297 	.globl _EP6AUTOINLENH
                            298 	.globl _EP4AUTOINLENL
                            299 	.globl _EP4AUTOINLENH
                            300 	.globl _EP2AUTOINLENL
                            301 	.globl _EP2AUTOINLENH
                            302 	.globl _EP8FIFOCFG
                            303 	.globl _EP6FIFOCFG
                            304 	.globl _EP4FIFOCFG
                            305 	.globl _EP2FIFOCFG
                            306 	.globl _EP8CFG
                            307 	.globl _EP6CFG
                            308 	.globl _EP4CFG
                            309 	.globl _EP2CFG
                            310 	.globl _EP1INCFG
                            311 	.globl _EP1OUTCFG
                            312 	.globl _REVCTL
                            313 	.globl _REVID
                            314 	.globl _FIFOPINPOLAR
                            315 	.globl _UART230
                            316 	.globl _BPADDRL
                            317 	.globl _BPADDRH
                            318 	.globl _BREAKPT
                            319 	.globl _FIFORESET
                            320 	.globl _PINFLAGSCD
                            321 	.globl _PINFLAGSAB
                            322 	.globl _IFCONFIG
                            323 	.globl _CPUCS
                            324 	.globl _RES_WAVEDATA_END
                            325 	.globl _GPIF_WAVE_DATA
                            326 	.globl _write_both_9862s_PARM_2
                            327 ;--------------------------------------------------------
                            328 ; special function registers
                            329 ;--------------------------------------------------------
                            330 	.area RSEG    (DATA)
                    0080    331 _IOA	=	0x0080
                    0081    332 _SP	=	0x0081
                    0082    333 _DPL	=	0x0082
                    0083    334 _DPH	=	0x0083
                    0084    335 _DPL1	=	0x0084
                    0085    336 _DPH1	=	0x0085
                    0086    337 _DPS	=	0x0086
                    0087    338 _PCON	=	0x0087
                    0088    339 _TCON	=	0x0088
                    0089    340 _TMOD	=	0x0089
                    008A    341 _TL0	=	0x008a
                    008B    342 _TL1	=	0x008b
                    008C    343 _TH0	=	0x008c
                    008D    344 _TH1	=	0x008d
                    008E    345 _CKCON	=	0x008e
                    0090    346 _IOB	=	0x0090
                    0091    347 _EXIF	=	0x0091
                    0092    348 _MPAGE	=	0x0092
                    0098    349 _SCON0	=	0x0098
                    0099    350 _SBUF0	=	0x0099
                    009A    351 _APTR1H	=	0x009a
                    009B    352 _APTR1L	=	0x009b
                    009C    353 _AUTODAT1	=	0x009c
                    009D    354 _AUTOPTRH2	=	0x009d
                    009E    355 _AUTOPTRL2	=	0x009e
                    009F    356 _AUTODAT2	=	0x009f
                    00A0    357 _IOC	=	0x00a0
                    00A1    358 _INT2CLR	=	0x00a1
                    00A2    359 _INT4CLR	=	0x00a2
                    00A8    360 _IE	=	0x00a8
                    00AA    361 _EP2468STAT	=	0x00aa
                    00AB    362 _EP24FIFOFLGS	=	0x00ab
                    00AC    363 _EP68FIFOFLGS	=	0x00ac
                    00AF    364 _AUTOPTRSETUP	=	0x00af
                    00B0    365 _IOD	=	0x00b0
                    00B1    366 _IOE	=	0x00b1
                    00B2    367 _OEA	=	0x00b2
                    00B3    368 _OEB	=	0x00b3
                    00B4    369 _OEC	=	0x00b4
                    00B5    370 _OED	=	0x00b5
                    00B6    371 _OEE	=	0x00b6
                    00B8    372 _IP	=	0x00b8
                    00BA    373 _EP01STAT	=	0x00ba
                    00BB    374 _GPIFTRIG	=	0x00bb
                    00BD    375 _GPIFSGLDATH	=	0x00bd
                    00BE    376 _GPIFSGLDATLX	=	0x00be
                    00BF    377 _GPIFSGLDATLNOX	=	0x00bf
                    00C0    378 _SCON1	=	0x00c0
                    00C1    379 _SBUF1	=	0x00c1
                    00C8    380 _T2CON	=	0x00c8
                    00CA    381 _RCAP2L	=	0x00ca
                    00CB    382 _RCAP2H	=	0x00cb
                    00CC    383 _TL2	=	0x00cc
                    00CD    384 _TH2	=	0x00cd
                    00D0    385 _PSW	=	0x00d0
                    00D8    386 _EICON	=	0x00d8
                    00E0    387 _ACC	=	0x00e0
                    00E8    388 _EIE	=	0x00e8
                    00F0    389 _B	=	0x00f0
                    00F8    390 _EIP	=	0x00f8
                            391 ;--------------------------------------------------------
                            392 ; special function bits
                            393 ;--------------------------------------------------------
                            394 	.area RSEG    (DATA)
                    0086    395 _SEL	=	0x0086
                    0088    396 _IT0	=	0x0088
                    0089    397 _IE0	=	0x0089
                    008A    398 _IT1	=	0x008a
                    008B    399 _IE1	=	0x008b
                    008C    400 _TR0	=	0x008c
                    008D    401 _TF0	=	0x008d
                    008E    402 _TR1	=	0x008e
                    008F    403 _TF1	=	0x008f
                    0098    404 _RI	=	0x0098
                    0099    405 _TI	=	0x0099
                    009A    406 _RB8	=	0x009a
                    009B    407 _TB8	=	0x009b
                    009C    408 _REN	=	0x009c
                    009D    409 _SM2	=	0x009d
                    009E    410 _SM1	=	0x009e
                    009F    411 _SM0	=	0x009f
                    00A8    412 _EX0	=	0x00a8
                    00A9    413 _ET0	=	0x00a9
                    00AA    414 _EX1	=	0x00aa
                    00AB    415 _ET1	=	0x00ab
                    00AC    416 _ES0	=	0x00ac
                    00AD    417 _ET2	=	0x00ad
                    00AE    418 _ES1	=	0x00ae
                    00AF    419 _EA	=	0x00af
                    00B8    420 _PX0	=	0x00b8
                    00B9    421 _PT0	=	0x00b9
                    00BA    422 _PX1	=	0x00ba
                    00BB    423 _PT1	=	0x00bb
                    00BC    424 _PS0	=	0x00bc
                    00BD    425 _PT2	=	0x00bd
                    00BE    426 _PS1	=	0x00be
                    00C0    427 _RI1	=	0x00c0
                    00C1    428 _TI1	=	0x00c1
                    00C2    429 _RB81	=	0x00c2
                    00C3    430 _TB81	=	0x00c3
                    00C4    431 _REN1	=	0x00c4
                    00C5    432 _SM21	=	0x00c5
                    00C6    433 _SM11	=	0x00c6
                    00C7    434 _SM01	=	0x00c7
                    00C8    435 _CP_RL2	=	0x00c8
                    00C9    436 _C_T2	=	0x00c9
                    00CA    437 _TR2	=	0x00ca
                    00CB    438 _EXEN2	=	0x00cb
                    00CC    439 _TCLK	=	0x00cc
                    00CD    440 _RCLK	=	0x00cd
                    00CE    441 _EXF2	=	0x00ce
                    00CF    442 _TF2	=	0x00cf
                    00D0    443 _P	=	0x00d0
                    00D1    444 _FL	=	0x00d1
                    00D2    445 _OV	=	0x00d2
                    00D3    446 _RS0	=	0x00d3
                    00D4    447 _RS1	=	0x00d4
                    00D5    448 _F0	=	0x00d5
                    00D6    449 _AC	=	0x00d6
                    00D7    450 _CY	=	0x00d7
                    00DB    451 _INT6	=	0x00db
                    00DC    452 _RESI	=	0x00dc
                    00DD    453 _ERESI	=	0x00dd
                    00DF    454 _SMOD1	=	0x00df
                    00E8    455 _EIUSB	=	0x00e8
                    00E9    456 _EI2C	=	0x00e9
                    00EA    457 _EIEX4	=	0x00ea
                    00EB    458 _EIEX5	=	0x00eb
                    00EC    459 _EIEX6	=	0x00ec
                    00F8    460 _PUSB	=	0x00f8
                    00F9    461 _PI2C	=	0x00f9
                    00FA    462 _EIPX4	=	0x00fa
                    00FB    463 _EIPX5	=	0x00fb
                    00FC    464 _EIPX6	=	0x00fc
                    0080    465 _bitS_CLK	=	0x0080
                    0081    466 _bitS_OUT	=	0x0081
                    0082    467 _bitS_IN	=	0x0082
                    00A1    468 _bitALTERA_DATA0	=	0x00a1
                    00A3    469 _bitALTERA_DCLK	=	0x00a3
                            470 ;--------------------------------------------------------
                            471 ; overlayable register banks
                            472 ;--------------------------------------------------------
                            473 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                     474 	.ds 8
                            475 ;--------------------------------------------------------
                            476 ; internal ram data
                            477 ;--------------------------------------------------------
                            478 	.area DSEG    (DATA)
   0008                     479 _write_both_9862s_PARM_2:
   0008                     480 	.ds 1
                            481 ;--------------------------------------------------------
                            482 ; overlayable items in internal ram 
                            483 ;--------------------------------------------------------
                            484 	.area	OSEG    (OVR,DATA)
                            485 ;--------------------------------------------------------
                            486 ; indirectly addressable internal ram data
                            487 ;--------------------------------------------------------
                            488 	.area ISEG    (DATA)
                            489 ;--------------------------------------------------------
                            490 ; absolute internal ram data
                            491 ;--------------------------------------------------------
                            492 	.area IABS    (ABS,DATA)
                            493 	.area IABS    (ABS,DATA)
                            494 ;--------------------------------------------------------
                            495 ; bit data
                            496 ;--------------------------------------------------------
                            497 	.area BSEG    (BIT)
                            498 ;--------------------------------------------------------
                            499 ; paged external ram data
                            500 ;--------------------------------------------------------
                            501 	.area PSEG    (PAG,XDATA)
                            502 ;--------------------------------------------------------
                            503 ; external ram data
                            504 ;--------------------------------------------------------
                            505 	.area XSEG    (XDATA)
                    E400    506 _GPIF_WAVE_DATA	=	0xe400
                    E480    507 _RES_WAVEDATA_END	=	0xe480
                    E600    508 _CPUCS	=	0xe600
                    E601    509 _IFCONFIG	=	0xe601
                    E602    510 _PINFLAGSAB	=	0xe602
                    E603    511 _PINFLAGSCD	=	0xe603
                    E604    512 _FIFORESET	=	0xe604
                    E605    513 _BREAKPT	=	0xe605
                    E606    514 _BPADDRH	=	0xe606
                    E607    515 _BPADDRL	=	0xe607
                    E608    516 _UART230	=	0xe608
                    E609    517 _FIFOPINPOLAR	=	0xe609
                    E60A    518 _REVID	=	0xe60a
                    E60B    519 _REVCTL	=	0xe60b
                    E610    520 _EP1OUTCFG	=	0xe610
                    E611    521 _EP1INCFG	=	0xe611
                    E612    522 _EP2CFG	=	0xe612
                    E613    523 _EP4CFG	=	0xe613
                    E614    524 _EP6CFG	=	0xe614
                    E615    525 _EP8CFG	=	0xe615
                    E618    526 _EP2FIFOCFG	=	0xe618
                    E619    527 _EP4FIFOCFG	=	0xe619
                    E61A    528 _EP6FIFOCFG	=	0xe61a
                    E61B    529 _EP8FIFOCFG	=	0xe61b
                    E620    530 _EP2AUTOINLENH	=	0xe620
                    E621    531 _EP2AUTOINLENL	=	0xe621
                    E622    532 _EP4AUTOINLENH	=	0xe622
                    E623    533 _EP4AUTOINLENL	=	0xe623
                    E624    534 _EP6AUTOINLENH	=	0xe624
                    E625    535 _EP6AUTOINLENL	=	0xe625
                    E626    536 _EP8AUTOINLENH	=	0xe626
                    E627    537 _EP8AUTOINLENL	=	0xe627
                    E630    538 _EP2FIFOPFH	=	0xe630
                    E631    539 _EP2FIFOPFL	=	0xe631
                    E632    540 _EP4FIFOPFH	=	0xe632
                    E633    541 _EP4FIFOPFL	=	0xe633
                    E634    542 _EP6FIFOPFH	=	0xe634
                    E635    543 _EP6FIFOPFL	=	0xe635
                    E636    544 _EP8FIFOPFH	=	0xe636
                    E637    545 _EP8FIFOPFL	=	0xe637
                    E640    546 _EP2ISOINPKTS	=	0xe640
                    E641    547 _EP4ISOINPKTS	=	0xe641
                    E642    548 _EP6ISOINPKTS	=	0xe642
                    E643    549 _EP8ISOINPKTS	=	0xe643
                    E648    550 _INPKTEND	=	0xe648
                    E649    551 _OUTPKTEND	=	0xe649
                    E650    552 _EP2FIFOIE	=	0xe650
                    E651    553 _EP2FIFOIRQ	=	0xe651
                    E652    554 _EP4FIFOIE	=	0xe652
                    E653    555 _EP4FIFOIRQ	=	0xe653
                    E654    556 _EP6FIFOIE	=	0xe654
                    E655    557 _EP6FIFOIRQ	=	0xe655
                    E656    558 _EP8FIFOIE	=	0xe656
                    E657    559 _EP8FIFOIRQ	=	0xe657
                    E658    560 _IBNIE	=	0xe658
                    E659    561 _IBNIRQ	=	0xe659
                    E65A    562 _NAKIE	=	0xe65a
                    E65B    563 _NAKIRQ	=	0xe65b
                    E65C    564 _USBIE	=	0xe65c
                    E65D    565 _USBIRQ	=	0xe65d
                    E65E    566 _EPIE	=	0xe65e
                    E65F    567 _EPIRQ	=	0xe65f
                    E660    568 _GPIFIE	=	0xe660
                    E661    569 _GPIFIRQ	=	0xe661
                    E662    570 _USBERRIE	=	0xe662
                    E663    571 _USBERRIRQ	=	0xe663
                    E664    572 _ERRCNTLIM	=	0xe664
                    E665    573 _CLRERRCNT	=	0xe665
                    E666    574 _INT2IVEC	=	0xe666
                    E667    575 _INT4IVEC	=	0xe667
                    E668    576 _INTSETUP	=	0xe668
                    E670    577 _PORTACFG	=	0xe670
                    E671    578 _PORTCCFG	=	0xe671
                    E672    579 _PORTECFG	=	0xe672
                    E678    580 _I2CS	=	0xe678
                    E679    581 _I2DAT	=	0xe679
                    E67A    582 _I2CTL	=	0xe67a
                    E67B    583 _XAUTODAT1	=	0xe67b
                    E67C    584 _XAUTODAT2	=	0xe67c
                    E680    585 _USBCS	=	0xe680
                    E681    586 _SUSPEND	=	0xe681
                    E682    587 _WAKEUPCS	=	0xe682
                    E683    588 _TOGCTL	=	0xe683
                    E684    589 _USBFRAMEH	=	0xe684
                    E685    590 _USBFRAMEL	=	0xe685
                    E686    591 _MICROFRAME	=	0xe686
                    E687    592 _FNADDR	=	0xe687
                    E68A    593 _EP0BCH	=	0xe68a
                    E68B    594 _EP0BCL	=	0xe68b
                    E68D    595 _EP1OUTBC	=	0xe68d
                    E68F    596 _EP1INBC	=	0xe68f
                    E690    597 _EP2BCH	=	0xe690
                    E691    598 _EP2BCL	=	0xe691
                    E694    599 _EP4BCH	=	0xe694
                    E695    600 _EP4BCL	=	0xe695
                    E698    601 _EP6BCH	=	0xe698
                    E699    602 _EP6BCL	=	0xe699
                    E69C    603 _EP8BCH	=	0xe69c
                    E69D    604 _EP8BCL	=	0xe69d
                    E6A0    605 _EP0CS	=	0xe6a0
                    E6A1    606 _EP1OUTCS	=	0xe6a1
                    E6A2    607 _EP1INCS	=	0xe6a2
                    E6A3    608 _EP2CS	=	0xe6a3
                    E6A4    609 _EP4CS	=	0xe6a4
                    E6A5    610 _EP6CS	=	0xe6a5
                    E6A6    611 _EP8CS	=	0xe6a6
                    E6A7    612 _EP2FIFOFLGS	=	0xe6a7
                    E6A8    613 _EP4FIFOFLGS	=	0xe6a8
                    E6A9    614 _EP6FIFOFLGS	=	0xe6a9
                    E6AA    615 _EP8FIFOFLGS	=	0xe6aa
                    E6AB    616 _EP2FIFOBCH	=	0xe6ab
                    E6AC    617 _EP2FIFOBCL	=	0xe6ac
                    E6AD    618 _EP4FIFOBCH	=	0xe6ad
                    E6AE    619 _EP4FIFOBCL	=	0xe6ae
                    E6AF    620 _EP6FIFOBCH	=	0xe6af
                    E6B0    621 _EP6FIFOBCL	=	0xe6b0
                    E6B1    622 _EP8FIFOBCH	=	0xe6b1
                    E6B2    623 _EP8FIFOBCL	=	0xe6b2
                    E6B3    624 _SUDPTRH	=	0xe6b3
                    E6B4    625 _SUDPTRL	=	0xe6b4
                    E6B5    626 _SUDPTRCTL	=	0xe6b5
                    E6B8    627 _SETUPDAT	=	0xe6b8
                    E6C0    628 _GPIFWFSELECT	=	0xe6c0
                    E6C1    629 _GPIFIDLECS	=	0xe6c1
                    E6C2    630 _GPIFIDLECTL	=	0xe6c2
                    E6C3    631 _GPIFCTLCFG	=	0xe6c3
                    E6C4    632 _GPIFADRH	=	0xe6c4
                    E6C5    633 _GPIFADRL	=	0xe6c5
                    E6CE    634 _GPIFTCB3	=	0xe6ce
                    E6CF    635 _GPIFTCB2	=	0xe6cf
                    E6D0    636 _GPIFTCB1	=	0xe6d0
                    E6D1    637 _GPIFTCB0	=	0xe6d1
                    E6D2    638 _EP2GPIFFLGSEL	=	0xe6d2
                    E6D3    639 _EP2GPIFPFSTOP	=	0xe6d3
                    E6D4    640 _EP2GPIFTRIG	=	0xe6d4
                    E6DA    641 _EP4GPIFFLGSEL	=	0xe6da
                    E6DB    642 _EP4GPIFPFSTOP	=	0xe6db
                    E6DC    643 _EP4GPIFTRIG	=	0xe6dc
                    E6E2    644 _EP6GPIFFLGSEL	=	0xe6e2
                    E6E3    645 _EP6GPIFPFSTOP	=	0xe6e3
                    E6E4    646 _EP6GPIFTRIG	=	0xe6e4
                    E6EA    647 _EP8GPIFFLGSEL	=	0xe6ea
                    E6EB    648 _EP8GPIFPFSTOP	=	0xe6eb
                    E6EC    649 _EP8GPIFTRIG	=	0xe6ec
                    E6F0    650 _XGPIFSGLDATH	=	0xe6f0
                    E6F1    651 _XGPIFSGLDATLX	=	0xe6f1
                    E6F2    652 _XGPIFSGLDATLNOX	=	0xe6f2
                    E6F3    653 _GPIFREADYCFG	=	0xe6f3
                    E6F4    654 _GPIFREADYSTAT	=	0xe6f4
                    E6F5    655 _GPIFABORT	=	0xe6f5
                    E6C6    656 _FLOWSTATE	=	0xe6c6
                    E6C7    657 _FLOWLOGIC	=	0xe6c7
                    E6C8    658 _FLOWEQ0CTL	=	0xe6c8
                    E6C9    659 _FLOWEQ1CTL	=	0xe6c9
                    E6CA    660 _FLOWHOLDOFF	=	0xe6ca
                    E6CB    661 _FLOWSTB	=	0xe6cb
                    E6CC    662 _FLOWSTBEDGE	=	0xe6cc
                    E6CD    663 _FLOWSTBHPERIOD	=	0xe6cd
                    E60C    664 _GPIFHOLDAMOUNT	=	0xe60c
                    E67D    665 _UDMACRCH	=	0xe67d
                    E67E    666 _UDMACRCL	=	0xe67e
                    E67F    667 _UDMACRCQUAL	=	0xe67f
                    E6F8    668 _DBUG	=	0xe6f8
                    E6F9    669 _TESTCFG	=	0xe6f9
                    E6FA    670 _USBTEST	=	0xe6fa
                    E6FB    671 _CT1	=	0xe6fb
                    E6FC    672 _CT2	=	0xe6fc
                    E6FD    673 _CT3	=	0xe6fd
                    E6FE    674 _CT4	=	0xe6fe
                    E740    675 _EP0BUF	=	0xe740
                    E780    676 _EP1OUTBUF	=	0xe780
                    E7C0    677 _EP1INBUF	=	0xe7c0
                    F000    678 _EP2FIFOBUF	=	0xf000
                    F400    679 _EP4FIFOBUF	=	0xf400
                    F800    680 _EP6FIFOBUF	=	0xf800
                    FC00    681 _EP8FIFOBUF	=	0xfc00
                    E1E0    682 _hash0	=	0xe1e0
                            683 ;--------------------------------------------------------
                            684 ; absolute external ram data
                            685 ;--------------------------------------------------------
                            686 	.area XABS    (ABS,XDATA)
                            687 ;--------------------------------------------------------
                            688 ; external initialized ram data
                            689 ;--------------------------------------------------------
                            690 	.area HOME    (CODE)
                            691 	.area GSINIT0 (CODE)
                            692 	.area GSINIT1 (CODE)
                            693 	.area GSINIT2 (CODE)
                            694 	.area GSINIT3 (CODE)
                            695 	.area GSINIT4 (CODE)
                            696 	.area GSINIT5 (CODE)
                            697 	.area GSINIT  (CODE)
                            698 	.area GSFINAL (CODE)
                            699 	.area CSEG    (CODE)
                            700 ;--------------------------------------------------------
                            701 ; global & static initialisations
                            702 ;--------------------------------------------------------
                            703 	.area HOME    (CODE)
                            704 	.area GSINIT  (CODE)
                            705 	.area GSFINAL (CODE)
                            706 	.area GSINIT  (CODE)
                            707 ;--------------------------------------------------------
                            708 ; Home
                            709 ;--------------------------------------------------------
                            710 	.area HOME    (CODE)
                            711 	.area HOME    (CODE)
                            712 ;--------------------------------------------------------
                            713 ; code
                            714 ;--------------------------------------------------------
                            715 	.area CSEG    (CODE)
                            716 ;------------------------------------------------------------
                            717 ;Allocation info for local variables in function 'write_both_9862s'
                            718 ;------------------------------------------------------------
                            719 ;v                         Allocated with name '_write_both_9862s_PARM_2'
                            720 ;header_lo                 Allocated to registers r2 
                            721 ;------------------------------------------------------------
                            722 ;	eeprom_init.c:42: write_both_9862s (unsigned char header_lo, unsigned char v)
                            723 ;	-----------------------------------------
                            724 ;	 function write_both_9862s
                            725 ;	-----------------------------------------
   0008                     726 _write_both_9862s:
                    0002    727 	ar2 = 0x02
                    0003    728 	ar3 = 0x03
                    0004    729 	ar4 = 0x04
                    0005    730 	ar5 = 0x05
                    0006    731 	ar6 = 0x06
                    0007    732 	ar7 = 0x07
                    0000    733 	ar0 = 0x00
                    0001    734 	ar1 = 0x01
   0008 AA 82               735 	mov	r2,dpl
                            736 ;	eeprom_init.c:44: enable_codecs ();
   000A 53 80 CF            737 	anl	_IOA,#0xCF
                            738 ;	eeprom_init.c:46: write_byte_msb (header_lo);
   000D 8A 82               739 	mov	dpl,r2
   000F 12 00 1C            740 	lcall	_write_byte_msb
                            741 ;	eeprom_init.c:47: write_byte_msb (v);
   0012 85 08 82            742 	mov	dpl,_write_both_9862s_PARM_2
   0015 12 00 1C            743 	lcall	_write_byte_msb
                            744 ;	eeprom_init.c:49: disable_all ();
   0018 43 80 30            745 	orl	_IOA,#0x30
   001B 22                  746 	ret
                            747 ;------------------------------------------------------------
                            748 ;Allocation info for local variables in function 'write_byte_msb'
                            749 ;------------------------------------------------------------
                            750 ;v                         Allocated to registers r2 
                            751 ;n                         Allocated to registers r3 
                            752 ;------------------------------------------------------------
                            753 ;	eeprom_init.c:55: write_byte_msb (unsigned char v)
                            754 ;	-----------------------------------------
                            755 ;	 function write_byte_msb
                            756 ;	-----------------------------------------
   001C                     757 _write_byte_msb:
   001C AA 82               758 	mov	r2,dpl
                            759 ;	eeprom_init.c:58: do {
   001E 7B 08               760 	mov	r3,#0x08
   0020                     761 00101$:
                            762 ;	eeprom_init.c:59: v = (v << 1) | (v >> 7);	// rotate left (MSB into bottom bit)
   0020 EA                  763 	mov	a,r2
   0021 23                  764 	rl	a
                            765 ;	eeprom_init.c:60: bitS_OUT = v & 0x1;
   0022 FA                  766 	mov	r2,a
   0023 13                  767 	rrc	a
   0024 92 81               768 	mov	_bitS_OUT,c
                            769 ;	eeprom_init.c:61: bitS_CLK = 1;
   0026 D2 80               770 	setb	_bitS_CLK
                            771 ;	eeprom_init.c:62: bitS_CLK = 0;
   0028 C2 80               772 	clr	_bitS_CLK
                            773 ;	eeprom_init.c:63: } while (--n != 0);
   002A DB F4               774 	djnz	r3,00101$
   002C 22                  775 	ret
                            776 ;------------------------------------------------------------
                            777 ;Allocation info for local variables in function 'eeprom_init'
                            778 ;------------------------------------------------------------
                            779 ;counter                   Allocated to registers 
                            780 ;i                         Allocated to registers r2 
                            781 ;------------------------------------------------------------
                            782 ;	eeprom_init.c:72: void eeprom_init (void)
                            783 ;	-----------------------------------------
                            784 ;	 function eeprom_init
                            785 ;	-----------------------------------------
   002D                     786 _eeprom_init:
                            787 ;	eeprom_init.c:79: IOA = bmPORT_A_INITIAL;	// Port A initial state
   002D 75 80 38            788 	mov	_IOA,#0x38
                            789 ;	eeprom_init.c:80: OEA = bmPORT_A_OUTPUTS;	// Port A direction register
   0030 75 B2 3B            790 	mov	_OEA,#0x3B
                            791 ;	eeprom_init.c:82: IOC = bmPORT_C_INITIAL;	// Port C initial state
   0033 75 A0 C0            792 	mov	_IOC,#0xC0
                            793 ;	eeprom_init.c:83: OEC = bmPORT_C_OUTPUTS;	// Port C direction register
   0036 75 B4 CF            794 	mov	_OEC,#0xCF
                            795 ;	eeprom_init.c:85: IOE = bmPORT_E_INITIAL;	// Port E initial state
   0039 75 B1 F0            796 	mov	_IOE,#0xF0
                            797 ;	eeprom_init.c:86: OEE = bmPORT_E_OUTPUTS;	// Port E direction register
   003C 75 B6 F8            798 	mov	_OEE,#0xF8
                            799 ;	eeprom_init.c:88: EP0BCH = 0;			SYNCDELAY;
   003F 90 E6 8A            800 	mov	dptr,#_EP0BCH
   0042 E4                  801 	clr	a
   0043 F0                  802 	movx	@dptr,a
   0044 00                  803 	 nop; nop; nop; 
                            804 ;	eeprom_init.c:91: USBCS = 0;			// chip firmware handles commands
   0045 90 E6 80            805 	mov	dptr,#_USBCS
   0048 E4                  806 	clr	a
   0049 F0                  807 	movx	@dptr,a
                            808 ;	eeprom_init.c:93: USRP_PC &= ~bmPC_nRESET;	// active low reset
   004A 53 A0 FE            809 	anl	_IOC,#0xFE
                            810 ;	eeprom_init.c:94: USRP_PC |=  bmPC_nRESET;
   004D 43 A0 01            811 	orl	_IOC,#0x01
                            812 ;	eeprom_init.c:97: bitS_OUT = 0;			/* idle state has CLK = 0 */
   0050 C2 81               813 	clr	_bitS_OUT
                            814 ;	eeprom_init.c:99: write_both_9862s (REG_RX_PWR_DN,    0x01);
   0052 75 08 01            815 	mov	_write_both_9862s_PARM_2,#0x01
   0055 75 82 01            816 	mov	dpl,#0x01
   0058 12 00 08            817 	lcall	_write_both_9862s
                            818 ;	eeprom_init.c:100: write_both_9862s (REG_TX_PWR_DN,    0x0f);	// pwr dn digital and analog_both
   005B 75 08 0F            819 	mov	_write_both_9862s_PARM_2,#0x0F
   005E 75 82 08            820 	mov	dpl,#0x08
   0061 12 00 08            821 	lcall	_write_both_9862s
                            822 ;	eeprom_init.c:101: write_both_9862s (REG_TX_MODULATOR, 0x00);	// coarse & fine modulators disabled
   0064 75 08 00            823 	mov	_write_both_9862s_PARM_2,#0x00
   0067 75 82 14            824 	mov	dpl,#0x14
   006A 12 00 08            825 	lcall	_write_both_9862s
                            826 ;	eeprom_init.c:105: do {
   006D 7A 00               827 	mov	r2,#0x00
   006F                     828 00101$:
                            829 ;	eeprom_init.c:106: hash0[i] = 0;
   006F EA                  830 	mov	a,r2
   0070 24 E0               831 	add	a,#_hash0
   0072 F5 82               832 	mov	dpl,a
   0074 E4                  833 	clr	a
   0075 34 E1               834 	addc	a,#(_hash0 >> 8)
   0077 F5 83               835 	mov	dph,a
   0079 E4                  836 	clr	a
   007A F0                  837 	movx	@dptr,a
                            838 ;	eeprom_init.c:107: i++;
   007B 0A                  839 	inc	r2
                            840 ;	eeprom_init.c:108: } while (i != USRP_HASH_SIZE);
   007C BA 10 F0            841 	cjne	r2,#0x10,00101$
                            842 ;	eeprom_init.c:111: while (1){
   007F 7A 00               843 	mov	r2,#0x00
   0081 7B 00               844 	mov	r3,#0x00
   0083                     845 00107$:
                            846 ;	eeprom_init.c:112: counter++;
   0083 0A                  847 	inc	r2
   0084 BA 00 01            848 	cjne	r2,#0x00,00118$
   0087 0B                  849 	inc	r3
   0088                     850 00118$:
                            851 ;	eeprom_init.c:113: if (counter & 0x8000)
   0088 EB                  852 	mov	a,r3
   0089 30 E7 F7            853 	jnb	acc.7,00107$
                            854 ;	eeprom_init.c:114: IOC ^= bmPC_LED0;
   008C 63 A0 40            855 	xrl	_IOC,#0x40
   008F 80 F2               856 	sjmp	00107$
                            857 	.area CSEG    (CODE)
                            858 	.area CONST   (CODE)
                            859 	.area CABS    (ABS,CODE)

                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 2.9.0 #5416 (Mar 22 2009) (MINGW32)
                              4 ; This file was generated Tue Oct 12 23:27:16 2010
                              5 ;--------------------------------------------------------
                              6 	.module init_gpif
                              7 	.optsdcc -mmcs51 --model-small
                              8 	
                              9 ;--------------------------------------------------------
                             10 ; Public variables in this module
                             11 ;--------------------------------------------------------
                             12 	.globl _bitALTERA_DCLK
                             13 	.globl _bitALTERA_DATA0
                             14 	.globl _bitS_IN
                             15 	.globl _bitS_OUT
                             16 	.globl _bitS_CLK
                             17 	.globl _EIPX6
                             18 	.globl _EIPX5
                             19 	.globl _EIPX4
                             20 	.globl _PI2C
                             21 	.globl _PUSB
                             22 	.globl _EIEX6
                             23 	.globl _EIEX5
                             24 	.globl _EIEX4
                             25 	.globl _EI2C
                             26 	.globl _EIUSB
                             27 	.globl _SMOD1
                             28 	.globl _ERESI
                             29 	.globl _RESI
                             30 	.globl _INT6
                             31 	.globl _CY
                             32 	.globl _AC
                             33 	.globl _F0
                             34 	.globl _RS1
                             35 	.globl _RS0
                             36 	.globl _OV
                             37 	.globl _FL
                             38 	.globl _P
                             39 	.globl _TF2
                             40 	.globl _EXF2
                             41 	.globl _RCLK
                             42 	.globl _TCLK
                             43 	.globl _EXEN2
                             44 	.globl _TR2
                             45 	.globl _C_T2
                             46 	.globl _CP_RL2
                             47 	.globl _SM01
                             48 	.globl _SM11
                             49 	.globl _SM21
                             50 	.globl _REN1
                             51 	.globl _TB81
                             52 	.globl _RB81
                             53 	.globl _TI1
                             54 	.globl _RI1
                             55 	.globl _PS1
                             56 	.globl _PT2
                             57 	.globl _PS0
                             58 	.globl _PT1
                             59 	.globl _PX1
                             60 	.globl _PT0
                             61 	.globl _PX0
                             62 	.globl _EA
                             63 	.globl _ES1
                             64 	.globl _ET2
                             65 	.globl _ES0
                             66 	.globl _ET1
                             67 	.globl _EX1
                             68 	.globl _ET0
                             69 	.globl _EX0
                             70 	.globl _SM0
                             71 	.globl _SM1
                             72 	.globl _SM2
                             73 	.globl _REN
                             74 	.globl _TB8
                             75 	.globl _RB8
                             76 	.globl _TI
                             77 	.globl _RI
                             78 	.globl _TF1
                             79 	.globl _TR1
                             80 	.globl _TF0
                             81 	.globl _TR0
                             82 	.globl _IE1
                             83 	.globl _IT1
                             84 	.globl _IE0
                             85 	.globl _IT0
                             86 	.globl _SEL
                             87 	.globl _EIP
                             88 	.globl _B
                             89 	.globl _EIE
                             90 	.globl _ACC
                             91 	.globl _EICON
                             92 	.globl _PSW
                             93 	.globl _TH2
                             94 	.globl _TL2
                             95 	.globl _RCAP2H
                             96 	.globl _RCAP2L
                             97 	.globl _T2CON
                             98 	.globl _SBUF1
                             99 	.globl _SCON1
                            100 	.globl _GPIFSGLDATLNOX
                            101 	.globl _GPIFSGLDATLX
                            102 	.globl _GPIFSGLDATH
                            103 	.globl _GPIFTRIG
                            104 	.globl _EP01STAT
                            105 	.globl _IP
                            106 	.globl _OEE
                            107 	.globl _OED
                            108 	.globl _OEC
                            109 	.globl _OEB
                            110 	.globl _OEA
                            111 	.globl _IOE
                            112 	.globl _IOD
                            113 	.globl _AUTOPTRSETUP
                            114 	.globl _EP68FIFOFLGS
                            115 	.globl _EP24FIFOFLGS
                            116 	.globl _EP2468STAT
                            117 	.globl _IE
                            118 	.globl _INT4CLR
                            119 	.globl _INT2CLR
                            120 	.globl _IOC
                            121 	.globl _AUTODAT2
                            122 	.globl _AUTOPTRL2
                            123 	.globl _AUTOPTRH2
                            124 	.globl _AUTODAT1
                            125 	.globl _APTR1L
                            126 	.globl _APTR1H
                            127 	.globl _SBUF0
                            128 	.globl _SCON0
                            129 	.globl _MPAGE
                            130 	.globl _EXIF
                            131 	.globl _IOB
                            132 	.globl _CKCON
                            133 	.globl _TH1
                            134 	.globl _TH0
                            135 	.globl _TL1
                            136 	.globl _TL0
                            137 	.globl _TMOD
                            138 	.globl _TCON
                            139 	.globl _PCON
                            140 	.globl _DPS
                            141 	.globl _DPH1
                            142 	.globl _DPL1
                            143 	.globl _DPH
                            144 	.globl _DPL
                            145 	.globl _SP
                            146 	.globl _IOA
                            147 	.globl _EP8FIFOBUF
                            148 	.globl _EP6FIFOBUF
                            149 	.globl _EP4FIFOBUF
                            150 	.globl _EP2FIFOBUF
                            151 	.globl _EP1INBUF
                            152 	.globl _EP1OUTBUF
                            153 	.globl _EP0BUF
                            154 	.globl _CT4
                            155 	.globl _CT3
                            156 	.globl _CT2
                            157 	.globl _CT1
                            158 	.globl _USBTEST
                            159 	.globl _TESTCFG
                            160 	.globl _DBUG
                            161 	.globl _UDMACRCQUAL
                            162 	.globl _UDMACRCL
                            163 	.globl _UDMACRCH
                            164 	.globl _GPIFHOLDAMOUNT
                            165 	.globl _FLOWSTBHPERIOD
                            166 	.globl _FLOWSTBEDGE
                            167 	.globl _FLOWSTB
                            168 	.globl _FLOWHOLDOFF
                            169 	.globl _FLOWEQ1CTL
                            170 	.globl _FLOWEQ0CTL
                            171 	.globl _FLOWLOGIC
                            172 	.globl _FLOWSTATE
                            173 	.globl _GPIFABORT
                            174 	.globl _GPIFREADYSTAT
                            175 	.globl _GPIFREADYCFG
                            176 	.globl _XGPIFSGLDATLNOX
                            177 	.globl _XGPIFSGLDATLX
                            178 	.globl _XGPIFSGLDATH
                            179 	.globl _EP8GPIFTRIG
                            180 	.globl _EP8GPIFPFSTOP
                            181 	.globl _EP8GPIFFLGSEL
                            182 	.globl _EP6GPIFTRIG
                            183 	.globl _EP6GPIFPFSTOP
                            184 	.globl _EP6GPIFFLGSEL
                            185 	.globl _EP4GPIFTRIG
                            186 	.globl _EP4GPIFPFSTOP
                            187 	.globl _EP4GPIFFLGSEL
                            188 	.globl _EP2GPIFTRIG
                            189 	.globl _EP2GPIFPFSTOP
                            190 	.globl _EP2GPIFFLGSEL
                            191 	.globl _GPIFTCB0
                            192 	.globl _GPIFTCB1
                            193 	.globl _GPIFTCB2
                            194 	.globl _GPIFTCB3
                            195 	.globl _GPIFADRL
                            196 	.globl _GPIFADRH
                            197 	.globl _GPIFCTLCFG
                            198 	.globl _GPIFIDLECTL
                            199 	.globl _GPIFIDLECS
                            200 	.globl _GPIFWFSELECT
                            201 	.globl _SETUPDAT
                            202 	.globl _SUDPTRCTL
                            203 	.globl _SUDPTRL
                            204 	.globl _SUDPTRH
                            205 	.globl _EP8FIFOBCL
                            206 	.globl _EP8FIFOBCH
                            207 	.globl _EP6FIFOBCL
                            208 	.globl _EP6FIFOBCH
                            209 	.globl _EP4FIFOBCL
                            210 	.globl _EP4FIFOBCH
                            211 	.globl _EP2FIFOBCL
                            212 	.globl _EP2FIFOBCH
                            213 	.globl _EP8FIFOFLGS
                            214 	.globl _EP6FIFOFLGS
                            215 	.globl _EP4FIFOFLGS
                            216 	.globl _EP2FIFOFLGS
                            217 	.globl _EP8CS
                            218 	.globl _EP6CS
                            219 	.globl _EP4CS
                            220 	.globl _EP2CS
                            221 	.globl _EP1INCS
                            222 	.globl _EP1OUTCS
                            223 	.globl _EP0CS
                            224 	.globl _EP8BCL
                            225 	.globl _EP8BCH
                            226 	.globl _EP6BCL
                            227 	.globl _EP6BCH
                            228 	.globl _EP4BCL
                            229 	.globl _EP4BCH
                            230 	.globl _EP2BCL
                            231 	.globl _EP2BCH
                            232 	.globl _EP1INBC
                            233 	.globl _EP1OUTBC
                            234 	.globl _EP0BCL
                            235 	.globl _EP0BCH
                            236 	.globl _FNADDR
                            237 	.globl _MICROFRAME
                            238 	.globl _USBFRAMEL
                            239 	.globl _USBFRAMEH
                            240 	.globl _TOGCTL
                            241 	.globl _WAKEUPCS
                            242 	.globl _SUSPEND
                            243 	.globl _USBCS
                            244 	.globl _XAUTODAT2
                            245 	.globl _XAUTODAT1
                            246 	.globl _I2CTL
                            247 	.globl _I2DAT
                            248 	.globl _I2CS
                            249 	.globl _PORTECFG
                            250 	.globl _PORTCCFG
                            251 	.globl _PORTACFG
                            252 	.globl _INTSETUP
                            253 	.globl _INT4IVEC
                            254 	.globl _INT2IVEC
                            255 	.globl _CLRERRCNT
                            256 	.globl _ERRCNTLIM
                            257 	.globl _USBERRIRQ
                            258 	.globl _USBERRIE
                            259 	.globl _GPIFIRQ
                            260 	.globl _GPIFIE
                            261 	.globl _EPIRQ
                            262 	.globl _EPIE
                            263 	.globl _USBIRQ
                            264 	.globl _USBIE
                            265 	.globl _NAKIRQ
                            266 	.globl _NAKIE
                            267 	.globl _IBNIRQ
                            268 	.globl _IBNIE
                            269 	.globl _EP8FIFOIRQ
                            270 	.globl _EP8FIFOIE
                            271 	.globl _EP6FIFOIRQ
                            272 	.globl _EP6FIFOIE
                            273 	.globl _EP4FIFOIRQ
                            274 	.globl _EP4FIFOIE
                            275 	.globl _EP2FIFOIRQ
                            276 	.globl _EP2FIFOIE
                            277 	.globl _OUTPKTEND
                            278 	.globl _INPKTEND
                            279 	.globl _EP8ISOINPKTS
                            280 	.globl _EP6ISOINPKTS
                            281 	.globl _EP4ISOINPKTS
                            282 	.globl _EP2ISOINPKTS
                            283 	.globl _EP8FIFOPFL
                            284 	.globl _EP8FIFOPFH
                            285 	.globl _EP6FIFOPFL
                            286 	.globl _EP6FIFOPFH
                            287 	.globl _EP4FIFOPFL
                            288 	.globl _EP4FIFOPFH
                            289 	.globl _EP2FIFOPFL
                            290 	.globl _EP2FIFOPFH
                            291 	.globl _EP8AUTOINLENL
                            292 	.globl _EP8AUTOINLENH
                            293 	.globl _EP6AUTOINLENL
                            294 	.globl _EP6AUTOINLENH
                            295 	.globl _EP4AUTOINLENL
                            296 	.globl _EP4AUTOINLENH
                            297 	.globl _EP2AUTOINLENL
                            298 	.globl _EP2AUTOINLENH
                            299 	.globl _EP8FIFOCFG
                            300 	.globl _EP6FIFOCFG
                            301 	.globl _EP4FIFOCFG
                            302 	.globl _EP2FIFOCFG
                            303 	.globl _EP8CFG
                            304 	.globl _EP6CFG
                            305 	.globl _EP4CFG
                            306 	.globl _EP2CFG
                            307 	.globl _EP1INCFG
                            308 	.globl _EP1OUTCFG
                            309 	.globl _REVCTL
                            310 	.globl _REVID
                            311 	.globl _FIFOPINPOLAR
                            312 	.globl _UART230
                            313 	.globl _BPADDRL
                            314 	.globl _BPADDRH
                            315 	.globl _BREAKPT
                            316 	.globl _FIFORESET
                            317 	.globl _PINFLAGSCD
                            318 	.globl _PINFLAGSAB
                            319 	.globl _IFCONFIG
                            320 	.globl _CPUCS
                            321 	.globl _RES_WAVEDATA_END
                            322 	.globl _GPIF_WAVE_DATA
                            323 	.globl _init_gpif
                            324 ;--------------------------------------------------------
                            325 ; special function registers
                            326 ;--------------------------------------------------------
                            327 	.area RSEG    (DATA)
                    0080    328 _IOA	=	0x0080
                    0081    329 _SP	=	0x0081
                    0082    330 _DPL	=	0x0082
                    0083    331 _DPH	=	0x0083
                    0084    332 _DPL1	=	0x0084
                    0085    333 _DPH1	=	0x0085
                    0086    334 _DPS	=	0x0086
                    0087    335 _PCON	=	0x0087
                    0088    336 _TCON	=	0x0088
                    0089    337 _TMOD	=	0x0089
                    008A    338 _TL0	=	0x008a
                    008B    339 _TL1	=	0x008b
                    008C    340 _TH0	=	0x008c
                    008D    341 _TH1	=	0x008d
                    008E    342 _CKCON	=	0x008e
                    0090    343 _IOB	=	0x0090
                    0091    344 _EXIF	=	0x0091
                    0092    345 _MPAGE	=	0x0092
                    0098    346 _SCON0	=	0x0098
                    0099    347 _SBUF0	=	0x0099
                    009A    348 _APTR1H	=	0x009a
                    009B    349 _APTR1L	=	0x009b
                    009C    350 _AUTODAT1	=	0x009c
                    009D    351 _AUTOPTRH2	=	0x009d
                    009E    352 _AUTOPTRL2	=	0x009e
                    009F    353 _AUTODAT2	=	0x009f
                    00A0    354 _IOC	=	0x00a0
                    00A1    355 _INT2CLR	=	0x00a1
                    00A2    356 _INT4CLR	=	0x00a2
                    00A8    357 _IE	=	0x00a8
                    00AA    358 _EP2468STAT	=	0x00aa
                    00AB    359 _EP24FIFOFLGS	=	0x00ab
                    00AC    360 _EP68FIFOFLGS	=	0x00ac
                    00AF    361 _AUTOPTRSETUP	=	0x00af
                    00B0    362 _IOD	=	0x00b0
                    00B1    363 _IOE	=	0x00b1
                    00B2    364 _OEA	=	0x00b2
                    00B3    365 _OEB	=	0x00b3
                    00B4    366 _OEC	=	0x00b4
                    00B5    367 _OED	=	0x00b5
                    00B6    368 _OEE	=	0x00b6
                    00B8    369 _IP	=	0x00b8
                    00BA    370 _EP01STAT	=	0x00ba
                    00BB    371 _GPIFTRIG	=	0x00bb
                    00BD    372 _GPIFSGLDATH	=	0x00bd
                    00BE    373 _GPIFSGLDATLX	=	0x00be
                    00BF    374 _GPIFSGLDATLNOX	=	0x00bf
                    00C0    375 _SCON1	=	0x00c0
                    00C1    376 _SBUF1	=	0x00c1
                    00C8    377 _T2CON	=	0x00c8
                    00CA    378 _RCAP2L	=	0x00ca
                    00CB    379 _RCAP2H	=	0x00cb
                    00CC    380 _TL2	=	0x00cc
                    00CD    381 _TH2	=	0x00cd
                    00D0    382 _PSW	=	0x00d0
                    00D8    383 _EICON	=	0x00d8
                    00E0    384 _ACC	=	0x00e0
                    00E8    385 _EIE	=	0x00e8
                    00F0    386 _B	=	0x00f0
                    00F8    387 _EIP	=	0x00f8
                            388 ;--------------------------------------------------------
                            389 ; special function bits
                            390 ;--------------------------------------------------------
                            391 	.area RSEG    (DATA)
                    0086    392 _SEL	=	0x0086
                    0088    393 _IT0	=	0x0088
                    0089    394 _IE0	=	0x0089
                    008A    395 _IT1	=	0x008a
                    008B    396 _IE1	=	0x008b
                    008C    397 _TR0	=	0x008c
                    008D    398 _TF0	=	0x008d
                    008E    399 _TR1	=	0x008e
                    008F    400 _TF1	=	0x008f
                    0098    401 _RI	=	0x0098
                    0099    402 _TI	=	0x0099
                    009A    403 _RB8	=	0x009a
                    009B    404 _TB8	=	0x009b
                    009C    405 _REN	=	0x009c
                    009D    406 _SM2	=	0x009d
                    009E    407 _SM1	=	0x009e
                    009F    408 _SM0	=	0x009f
                    00A8    409 _EX0	=	0x00a8
                    00A9    410 _ET0	=	0x00a9
                    00AA    411 _EX1	=	0x00aa
                    00AB    412 _ET1	=	0x00ab
                    00AC    413 _ES0	=	0x00ac
                    00AD    414 _ET2	=	0x00ad
                    00AE    415 _ES1	=	0x00ae
                    00AF    416 _EA	=	0x00af
                    00B8    417 _PX0	=	0x00b8
                    00B9    418 _PT0	=	0x00b9
                    00BA    419 _PX1	=	0x00ba
                    00BB    420 _PT1	=	0x00bb
                    00BC    421 _PS0	=	0x00bc
                    00BD    422 _PT2	=	0x00bd
                    00BE    423 _PS1	=	0x00be
                    00C0    424 _RI1	=	0x00c0
                    00C1    425 _TI1	=	0x00c1
                    00C2    426 _RB81	=	0x00c2
                    00C3    427 _TB81	=	0x00c3
                    00C4    428 _REN1	=	0x00c4
                    00C5    429 _SM21	=	0x00c5
                    00C6    430 _SM11	=	0x00c6
                    00C7    431 _SM01	=	0x00c7
                    00C8    432 _CP_RL2	=	0x00c8
                    00C9    433 _C_T2	=	0x00c9
                    00CA    434 _TR2	=	0x00ca
                    00CB    435 _EXEN2	=	0x00cb
                    00CC    436 _TCLK	=	0x00cc
                    00CD    437 _RCLK	=	0x00cd
                    00CE    438 _EXF2	=	0x00ce
                    00CF    439 _TF2	=	0x00cf
                    00D0    440 _P	=	0x00d0
                    00D1    441 _FL	=	0x00d1
                    00D2    442 _OV	=	0x00d2
                    00D3    443 _RS0	=	0x00d3
                    00D4    444 _RS1	=	0x00d4
                    00D5    445 _F0	=	0x00d5
                    00D6    446 _AC	=	0x00d6
                    00D7    447 _CY	=	0x00d7
                    00DB    448 _INT6	=	0x00db
                    00DC    449 _RESI	=	0x00dc
                    00DD    450 _ERESI	=	0x00dd
                    00DF    451 _SMOD1	=	0x00df
                    00E8    452 _EIUSB	=	0x00e8
                    00E9    453 _EI2C	=	0x00e9
                    00EA    454 _EIEX4	=	0x00ea
                    00EB    455 _EIEX5	=	0x00eb
                    00EC    456 _EIEX6	=	0x00ec
                    00F8    457 _PUSB	=	0x00f8
                    00F9    458 _PI2C	=	0x00f9
                    00FA    459 _EIPX4	=	0x00fa
                    00FB    460 _EIPX5	=	0x00fb
                    00FC    461 _EIPX6	=	0x00fc
                    0080    462 _bitS_CLK	=	0x0080
                    0081    463 _bitS_OUT	=	0x0081
                    0082    464 _bitS_IN	=	0x0082
                    00A1    465 _bitALTERA_DATA0	=	0x00a1
                    00A3    466 _bitALTERA_DCLK	=	0x00a3
                            467 ;--------------------------------------------------------
                            468 ; overlayable register banks
                            469 ;--------------------------------------------------------
                            470 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                     471 	.ds 8
                            472 ;--------------------------------------------------------
                            473 ; internal ram data
                            474 ;--------------------------------------------------------
                            475 	.area DSEG    (DATA)
                            476 ;--------------------------------------------------------
                            477 ; overlayable items in internal ram 
                            478 ;--------------------------------------------------------
                            479 	.area	OSEG    (OVR,DATA)
                            480 ;--------------------------------------------------------
                            481 ; indirectly addressable internal ram data
                            482 ;--------------------------------------------------------
                            483 	.area ISEG    (DATA)
                            484 ;--------------------------------------------------------
                            485 ; absolute internal ram data
                            486 ;--------------------------------------------------------
                            487 	.area IABS    (ABS,DATA)
                            488 	.area IABS    (ABS,DATA)
                            489 ;--------------------------------------------------------
                            490 ; bit data
                            491 ;--------------------------------------------------------
                            492 	.area BSEG    (BIT)
                            493 ;--------------------------------------------------------
                            494 ; paged external ram data
                            495 ;--------------------------------------------------------
                            496 	.area PSEG    (PAG,XDATA)
                            497 ;--------------------------------------------------------
                            498 ; external ram data
                            499 ;--------------------------------------------------------
                            500 	.area XSEG    (XDATA)
                    E400    501 _GPIF_WAVE_DATA	=	0xe400
                    E480    502 _RES_WAVEDATA_END	=	0xe480
                    E600    503 _CPUCS	=	0xe600
                    E601    504 _IFCONFIG	=	0xe601
                    E602    505 _PINFLAGSAB	=	0xe602
                    E603    506 _PINFLAGSCD	=	0xe603
                    E604    507 _FIFORESET	=	0xe604
                    E605    508 _BREAKPT	=	0xe605
                    E606    509 _BPADDRH	=	0xe606
                    E607    510 _BPADDRL	=	0xe607
                    E608    511 _UART230	=	0xe608
                    E609    512 _FIFOPINPOLAR	=	0xe609
                    E60A    513 _REVID	=	0xe60a
                    E60B    514 _REVCTL	=	0xe60b
                    E610    515 _EP1OUTCFG	=	0xe610
                    E611    516 _EP1INCFG	=	0xe611
                    E612    517 _EP2CFG	=	0xe612
                    E613    518 _EP4CFG	=	0xe613
                    E614    519 _EP6CFG	=	0xe614
                    E615    520 _EP8CFG	=	0xe615
                    E618    521 _EP2FIFOCFG	=	0xe618
                    E619    522 _EP4FIFOCFG	=	0xe619
                    E61A    523 _EP6FIFOCFG	=	0xe61a
                    E61B    524 _EP8FIFOCFG	=	0xe61b
                    E620    525 _EP2AUTOINLENH	=	0xe620
                    E621    526 _EP2AUTOINLENL	=	0xe621
                    E622    527 _EP4AUTOINLENH	=	0xe622
                    E623    528 _EP4AUTOINLENL	=	0xe623
                    E624    529 _EP6AUTOINLENH	=	0xe624
                    E625    530 _EP6AUTOINLENL	=	0xe625
                    E626    531 _EP8AUTOINLENH	=	0xe626
                    E627    532 _EP8AUTOINLENL	=	0xe627
                    E630    533 _EP2FIFOPFH	=	0xe630
                    E631    534 _EP2FIFOPFL	=	0xe631
                    E632    535 _EP4FIFOPFH	=	0xe632
                    E633    536 _EP4FIFOPFL	=	0xe633
                    E634    537 _EP6FIFOPFH	=	0xe634
                    E635    538 _EP6FIFOPFL	=	0xe635
                    E636    539 _EP8FIFOPFH	=	0xe636
                    E637    540 _EP8FIFOPFL	=	0xe637
                    E640    541 _EP2ISOINPKTS	=	0xe640
                    E641    542 _EP4ISOINPKTS	=	0xe641
                    E642    543 _EP6ISOINPKTS	=	0xe642
                    E643    544 _EP8ISOINPKTS	=	0xe643
                    E648    545 _INPKTEND	=	0xe648
                    E649    546 _OUTPKTEND	=	0xe649
                    E650    547 _EP2FIFOIE	=	0xe650
                    E651    548 _EP2FIFOIRQ	=	0xe651
                    E652    549 _EP4FIFOIE	=	0xe652
                    E653    550 _EP4FIFOIRQ	=	0xe653
                    E654    551 _EP6FIFOIE	=	0xe654
                    E655    552 _EP6FIFOIRQ	=	0xe655
                    E656    553 _EP8FIFOIE	=	0xe656
                    E657    554 _EP8FIFOIRQ	=	0xe657
                    E658    555 _IBNIE	=	0xe658
                    E659    556 _IBNIRQ	=	0xe659
                    E65A    557 _NAKIE	=	0xe65a
                    E65B    558 _NAKIRQ	=	0xe65b
                    E65C    559 _USBIE	=	0xe65c
                    E65D    560 _USBIRQ	=	0xe65d
                    E65E    561 _EPIE	=	0xe65e
                    E65F    562 _EPIRQ	=	0xe65f
                    E660    563 _GPIFIE	=	0xe660
                    E661    564 _GPIFIRQ	=	0xe661
                    E662    565 _USBERRIE	=	0xe662
                    E663    566 _USBERRIRQ	=	0xe663
                    E664    567 _ERRCNTLIM	=	0xe664
                    E665    568 _CLRERRCNT	=	0xe665
                    E666    569 _INT2IVEC	=	0xe666
                    E667    570 _INT4IVEC	=	0xe667
                    E668    571 _INTSETUP	=	0xe668
                    E670    572 _PORTACFG	=	0xe670
                    E671    573 _PORTCCFG	=	0xe671
                    E672    574 _PORTECFG	=	0xe672
                    E678    575 _I2CS	=	0xe678
                    E679    576 _I2DAT	=	0xe679
                    E67A    577 _I2CTL	=	0xe67a
                    E67B    578 _XAUTODAT1	=	0xe67b
                    E67C    579 _XAUTODAT2	=	0xe67c
                    E680    580 _USBCS	=	0xe680
                    E681    581 _SUSPEND	=	0xe681
                    E682    582 _WAKEUPCS	=	0xe682
                    E683    583 _TOGCTL	=	0xe683
                    E684    584 _USBFRAMEH	=	0xe684
                    E685    585 _USBFRAMEL	=	0xe685
                    E686    586 _MICROFRAME	=	0xe686
                    E687    587 _FNADDR	=	0xe687
                    E68A    588 _EP0BCH	=	0xe68a
                    E68B    589 _EP0BCL	=	0xe68b
                    E68D    590 _EP1OUTBC	=	0xe68d
                    E68F    591 _EP1INBC	=	0xe68f
                    E690    592 _EP2BCH	=	0xe690
                    E691    593 _EP2BCL	=	0xe691
                    E694    594 _EP4BCH	=	0xe694
                    E695    595 _EP4BCL	=	0xe695
                    E698    596 _EP6BCH	=	0xe698
                    E699    597 _EP6BCL	=	0xe699
                    E69C    598 _EP8BCH	=	0xe69c
                    E69D    599 _EP8BCL	=	0xe69d
                    E6A0    600 _EP0CS	=	0xe6a0
                    E6A1    601 _EP1OUTCS	=	0xe6a1
                    E6A2    602 _EP1INCS	=	0xe6a2
                    E6A3    603 _EP2CS	=	0xe6a3
                    E6A4    604 _EP4CS	=	0xe6a4
                    E6A5    605 _EP6CS	=	0xe6a5
                    E6A6    606 _EP8CS	=	0xe6a6
                    E6A7    607 _EP2FIFOFLGS	=	0xe6a7
                    E6A8    608 _EP4FIFOFLGS	=	0xe6a8
                    E6A9    609 _EP6FIFOFLGS	=	0xe6a9
                    E6AA    610 _EP8FIFOFLGS	=	0xe6aa
                    E6AB    611 _EP2FIFOBCH	=	0xe6ab
                    E6AC    612 _EP2FIFOBCL	=	0xe6ac
                    E6AD    613 _EP4FIFOBCH	=	0xe6ad
                    E6AE    614 _EP4FIFOBCL	=	0xe6ae
                    E6AF    615 _EP6FIFOBCH	=	0xe6af
                    E6B0    616 _EP6FIFOBCL	=	0xe6b0
                    E6B1    617 _EP8FIFOBCH	=	0xe6b1
                    E6B2    618 _EP8FIFOBCL	=	0xe6b2
                    E6B3    619 _SUDPTRH	=	0xe6b3
                    E6B4    620 _SUDPTRL	=	0xe6b4
                    E6B5    621 _SUDPTRCTL	=	0xe6b5
                    E6B8    622 _SETUPDAT	=	0xe6b8
                    E6C0    623 _GPIFWFSELECT	=	0xe6c0
                    E6C1    624 _GPIFIDLECS	=	0xe6c1
                    E6C2    625 _GPIFIDLECTL	=	0xe6c2
                    E6C3    626 _GPIFCTLCFG	=	0xe6c3
                    E6C4    627 _GPIFADRH	=	0xe6c4
                    E6C5    628 _GPIFADRL	=	0xe6c5
                    E6CE    629 _GPIFTCB3	=	0xe6ce
                    E6CF    630 _GPIFTCB2	=	0xe6cf
                    E6D0    631 _GPIFTCB1	=	0xe6d0
                    E6D1    632 _GPIFTCB0	=	0xe6d1
                    E6D2    633 _EP2GPIFFLGSEL	=	0xe6d2
                    E6D3    634 _EP2GPIFPFSTOP	=	0xe6d3
                    E6D4    635 _EP2GPIFTRIG	=	0xe6d4
                    E6DA    636 _EP4GPIFFLGSEL	=	0xe6da
                    E6DB    637 _EP4GPIFPFSTOP	=	0xe6db
                    E6DC    638 _EP4GPIFTRIG	=	0xe6dc
                    E6E2    639 _EP6GPIFFLGSEL	=	0xe6e2
                    E6E3    640 _EP6GPIFPFSTOP	=	0xe6e3
                    E6E4    641 _EP6GPIFTRIG	=	0xe6e4
                    E6EA    642 _EP8GPIFFLGSEL	=	0xe6ea
                    E6EB    643 _EP8GPIFPFSTOP	=	0xe6eb
                    E6EC    644 _EP8GPIFTRIG	=	0xe6ec
                    E6F0    645 _XGPIFSGLDATH	=	0xe6f0
                    E6F1    646 _XGPIFSGLDATLX	=	0xe6f1
                    E6F2    647 _XGPIFSGLDATLNOX	=	0xe6f2
                    E6F3    648 _GPIFREADYCFG	=	0xe6f3
                    E6F4    649 _GPIFREADYSTAT	=	0xe6f4
                    E6F5    650 _GPIFABORT	=	0xe6f5
                    E6C6    651 _FLOWSTATE	=	0xe6c6
                    E6C7    652 _FLOWLOGIC	=	0xe6c7
                    E6C8    653 _FLOWEQ0CTL	=	0xe6c8
                    E6C9    654 _FLOWEQ1CTL	=	0xe6c9
                    E6CA    655 _FLOWHOLDOFF	=	0xe6ca
                    E6CB    656 _FLOWSTB	=	0xe6cb
                    E6CC    657 _FLOWSTBEDGE	=	0xe6cc
                    E6CD    658 _FLOWSTBHPERIOD	=	0xe6cd
                    E60C    659 _GPIFHOLDAMOUNT	=	0xe60c
                    E67D    660 _UDMACRCH	=	0xe67d
                    E67E    661 _UDMACRCL	=	0xe67e
                    E67F    662 _UDMACRCQUAL	=	0xe67f
                    E6F8    663 _DBUG	=	0xe6f8
                    E6F9    664 _TESTCFG	=	0xe6f9
                    E6FA    665 _USBTEST	=	0xe6fa
                    E6FB    666 _CT1	=	0xe6fb
                    E6FC    667 _CT2	=	0xe6fc
                    E6FD    668 _CT3	=	0xe6fd
                    E6FE    669 _CT4	=	0xe6fe
                    E740    670 _EP0BUF	=	0xe740
                    E780    671 _EP1OUTBUF	=	0xe780
                    E7C0    672 _EP1INBUF	=	0xe7c0
                    F000    673 _EP2FIFOBUF	=	0xf000
                    F400    674 _EP4FIFOBUF	=	0xf400
                    F800    675 _EP6FIFOBUF	=	0xf800
                    FC00    676 _EP8FIFOBUF	=	0xfc00
                            677 ;--------------------------------------------------------
                            678 ; absolute external ram data
                            679 ;--------------------------------------------------------
                            680 	.area XABS    (ABS,XDATA)
                            681 ;--------------------------------------------------------
                            682 ; external initialized ram data
                            683 ;--------------------------------------------------------
                            684 	.area HOME    (CODE)
                            685 	.area GSINIT0 (CODE)
                            686 	.area GSINIT1 (CODE)
                            687 	.area GSINIT2 (CODE)
                            688 	.area GSINIT3 (CODE)
                            689 	.area GSINIT4 (CODE)
                            690 	.area GSINIT5 (CODE)
                            691 	.area GSINIT  (CODE)
                            692 	.area GSFINAL (CODE)
                            693 	.area CSEG    (CODE)
                            694 ;--------------------------------------------------------
                            695 ; global & static initialisations
                            696 ;--------------------------------------------------------
                            697 	.area HOME    (CODE)
                            698 	.area GSINIT  (CODE)
                            699 	.area GSFINAL (CODE)
                            700 	.area GSINIT  (CODE)
                            701 ;--------------------------------------------------------
                            702 ; Home
                            703 ;--------------------------------------------------------
                            704 	.area HOME    (CODE)
                            705 	.area HOME    (CODE)
                            706 ;--------------------------------------------------------
                            707 ; code
                            708 ;--------------------------------------------------------
                            709 	.area CSEG    (CODE)
                            710 ;------------------------------------------------------------
                            711 ;Allocation info for local variables in function 'init_gpif'
                            712 ;------------------------------------------------------------
                            713 ;i                         Allocated to registers r2 
                            714 ;------------------------------------------------------------
                            715 ;	../common/init_gpif.c:35: init_gpif (void)
                            716 ;	-----------------------------------------
                            717 ;	 function init_gpif
                            718 ;	-----------------------------------------
   07A6                     719 _init_gpif:
                    0002    720 	ar2 = 0x02
                    0003    721 	ar3 = 0x03
                    0004    722 	ar4 = 0x04
                    0005    723 	ar5 = 0x05
                    0006    724 	ar6 = 0x06
                    0007    725 	ar7 = 0x07
                    0000    726 	ar0 = 0x00
                    0001    727 	ar1 = 0x01
                            728 ;	../common/init_gpif.c:39: GPIFABORT = 0xFF;  // abort any waveforms pending
   07A6 90 E6 F5            729 	mov	dptr,#_GPIFABORT
   07A9 74 FF               730 	mov	a,#0xFF
   07AB F0                  731 	movx	@dptr,a
                            732 ;	../common/init_gpif.c:40: SYNCDELAY;
   07AC 00                  733 	 nop; nop; nop; 
                            734 ;	../common/init_gpif.c:42: GPIFREADYCFG = InitData[ 0 ];
   07AD 90 12 F9            735 	mov	dptr,#_InitData
   07B0 E4                  736 	clr	a
   07B1 93                  737 	movc	a,@a+dptr
   07B2 90 E6 F3            738 	mov	dptr,#_GPIFREADYCFG
   07B5 F0                  739 	movx	@dptr,a
                            740 ;	../common/init_gpif.c:43: GPIFCTLCFG = InitData[ 1 ];
   07B6 90 12 FA            741 	mov	dptr,#(_InitData + 0x0001)
   07B9 E4                  742 	clr	a
   07BA 93                  743 	movc	a,@a+dptr
   07BB 90 E6 C3            744 	mov	dptr,#_GPIFCTLCFG
   07BE F0                  745 	movx	@dptr,a
                            746 ;	../common/init_gpif.c:44: GPIFIDLECS = InitData[ 2 ];
   07BF 90 12 FB            747 	mov	dptr,#(_InitData + 0x0002)
   07C2 E4                  748 	clr	a
   07C3 93                  749 	movc	a,@a+dptr
   07C4 90 E6 C1            750 	mov	dptr,#_GPIFIDLECS
   07C7 F0                  751 	movx	@dptr,a
                            752 ;	../common/init_gpif.c:45: GPIFIDLECTL = InitData[ 3 ];
   07C8 90 12 FC            753 	mov	dptr,#(_InitData + 0x0003)
   07CB E4                  754 	clr	a
   07CC 93                  755 	movc	a,@a+dptr
   07CD 90 E6 C2            756 	mov	dptr,#_GPIFIDLECTL
   07D0 F0                  757 	movx	@dptr,a
                            758 ;	../common/init_gpif.c:47: GPIFWFSELECT = InitData[ 5 ];
   07D1 90 12 FE            759 	mov	dptr,#(_InitData + 0x0005)
   07D4 E4                  760 	clr	a
   07D5 93                  761 	movc	a,@a+dptr
   07D6 90 E6 C0            762 	mov	dptr,#_GPIFWFSELECT
   07D9 F0                  763 	movx	@dptr,a
                            764 ;	../common/init_gpif.c:53: for (i = 0; i < 128; i++){
   07DA 7A 00               765 	mov	r2,#0x00
   07DC                     766 00101$:
   07DC BA 80 00            767 	cjne	r2,#0x80,00110$
   07DF                     768 00110$:
   07DF 50 12               769 	jnc	00104$
                            770 ;	../common/init_gpif.c:54: GPIF_WAVE_DATA[i] = WaveData[i];
   07E1 8A 03               771 	mov	ar3,r2
   07E3 7C E4               772 	mov	r4,#(_GPIF_WAVE_DATA >> 8)
   07E5 EA                  773 	mov	a,r2
   07E6 90 12 55            774 	mov	dptr,#_WaveData
   07E9 93                  775 	movc	a,@a+dptr
   07EA FD                  776 	mov	r5,a
   07EB 8B 82               777 	mov	dpl,r3
   07ED 8C 83               778 	mov	dph,r4
   07EF F0                  779 	movx	@dptr,a
                            780 ;	../common/init_gpif.c:53: for (i = 0; i < 128; i++){
   07F0 0A                  781 	inc	r2
   07F1 80 E9               782 	sjmp	00101$
   07F3                     783 00104$:
                            784 ;	../common/init_gpif.c:58: FLOWSTATE = 0;		/* ensure it's off */
   07F3 90 E6 C6            785 	mov	dptr,#_FLOWSTATE
   07F6 E4                  786 	clr	a
   07F7 F0                  787 	movx	@dptr,a
   07F8 22                  788 	ret
                            789 	.area CSEG    (CODE)
                            790 	.area CONST   (CODE)
                            791 	.area CABS    (ABS,CODE)

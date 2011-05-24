                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 2.9.0 #5416 (Mar 22 2009) (MINGW32)
                              4 ; This file was generated Tue Oct 12 23:27:17 2010
                              5 ;--------------------------------------------------------
                              6 	.module spi
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
                            323 	.globl _read_bytes_msb_PARM_2
                            324 	.globl _write_bytes_msb_PARM_2
                            325 	.globl _spi_write_PARM_6
                            326 	.globl _spi_write_PARM_5
                            327 	.globl _spi_write_PARM_4
                            328 	.globl _spi_write_PARM_3
                            329 	.globl _spi_write_PARM_2
                            330 	.globl _spi_read_PARM_6
                            331 	.globl _spi_read_PARM_5
                            332 	.globl _spi_read_PARM_4
                            333 	.globl _spi_read_PARM_3
                            334 	.globl _spi_read_PARM_2
                            335 	.globl _init_spi
                            336 	.globl _spi_read
                            337 	.globl _spi_write
                            338 ;--------------------------------------------------------
                            339 ; special function registers
                            340 ;--------------------------------------------------------
                            341 	.area RSEG    (DATA)
                    0080    342 _IOA	=	0x0080
                    0081    343 _SP	=	0x0081
                    0082    344 _DPL	=	0x0082
                    0083    345 _DPH	=	0x0083
                    0084    346 _DPL1	=	0x0084
                    0085    347 _DPH1	=	0x0085
                    0086    348 _DPS	=	0x0086
                    0087    349 _PCON	=	0x0087
                    0088    350 _TCON	=	0x0088
                    0089    351 _TMOD	=	0x0089
                    008A    352 _TL0	=	0x008a
                    008B    353 _TL1	=	0x008b
                    008C    354 _TH0	=	0x008c
                    008D    355 _TH1	=	0x008d
                    008E    356 _CKCON	=	0x008e
                    0090    357 _IOB	=	0x0090
                    0091    358 _EXIF	=	0x0091
                    0092    359 _MPAGE	=	0x0092
                    0098    360 _SCON0	=	0x0098
                    0099    361 _SBUF0	=	0x0099
                    009A    362 _APTR1H	=	0x009a
                    009B    363 _APTR1L	=	0x009b
                    009C    364 _AUTODAT1	=	0x009c
                    009D    365 _AUTOPTRH2	=	0x009d
                    009E    366 _AUTOPTRL2	=	0x009e
                    009F    367 _AUTODAT2	=	0x009f
                    00A0    368 _IOC	=	0x00a0
                    00A1    369 _INT2CLR	=	0x00a1
                    00A2    370 _INT4CLR	=	0x00a2
                    00A8    371 _IE	=	0x00a8
                    00AA    372 _EP2468STAT	=	0x00aa
                    00AB    373 _EP24FIFOFLGS	=	0x00ab
                    00AC    374 _EP68FIFOFLGS	=	0x00ac
                    00AF    375 _AUTOPTRSETUP	=	0x00af
                    00B0    376 _IOD	=	0x00b0
                    00B1    377 _IOE	=	0x00b1
                    00B2    378 _OEA	=	0x00b2
                    00B3    379 _OEB	=	0x00b3
                    00B4    380 _OEC	=	0x00b4
                    00B5    381 _OED	=	0x00b5
                    00B6    382 _OEE	=	0x00b6
                    00B8    383 _IP	=	0x00b8
                    00BA    384 _EP01STAT	=	0x00ba
                    00BB    385 _GPIFTRIG	=	0x00bb
                    00BD    386 _GPIFSGLDATH	=	0x00bd
                    00BE    387 _GPIFSGLDATLX	=	0x00be
                    00BF    388 _GPIFSGLDATLNOX	=	0x00bf
                    00C0    389 _SCON1	=	0x00c0
                    00C1    390 _SBUF1	=	0x00c1
                    00C8    391 _T2CON	=	0x00c8
                    00CA    392 _RCAP2L	=	0x00ca
                    00CB    393 _RCAP2H	=	0x00cb
                    00CC    394 _TL2	=	0x00cc
                    00CD    395 _TH2	=	0x00cd
                    00D0    396 _PSW	=	0x00d0
                    00D8    397 _EICON	=	0x00d8
                    00E0    398 _ACC	=	0x00e0
                    00E8    399 _EIE	=	0x00e8
                    00F0    400 _B	=	0x00f0
                    00F8    401 _EIP	=	0x00f8
                            402 ;--------------------------------------------------------
                            403 ; special function bits
                            404 ;--------------------------------------------------------
                            405 	.area RSEG    (DATA)
                    0086    406 _SEL	=	0x0086
                    0088    407 _IT0	=	0x0088
                    0089    408 _IE0	=	0x0089
                    008A    409 _IT1	=	0x008a
                    008B    410 _IE1	=	0x008b
                    008C    411 _TR0	=	0x008c
                    008D    412 _TF0	=	0x008d
                    008E    413 _TR1	=	0x008e
                    008F    414 _TF1	=	0x008f
                    0098    415 _RI	=	0x0098
                    0099    416 _TI	=	0x0099
                    009A    417 _RB8	=	0x009a
                    009B    418 _TB8	=	0x009b
                    009C    419 _REN	=	0x009c
                    009D    420 _SM2	=	0x009d
                    009E    421 _SM1	=	0x009e
                    009F    422 _SM0	=	0x009f
                    00A8    423 _EX0	=	0x00a8
                    00A9    424 _ET0	=	0x00a9
                    00AA    425 _EX1	=	0x00aa
                    00AB    426 _ET1	=	0x00ab
                    00AC    427 _ES0	=	0x00ac
                    00AD    428 _ET2	=	0x00ad
                    00AE    429 _ES1	=	0x00ae
                    00AF    430 _EA	=	0x00af
                    00B8    431 _PX0	=	0x00b8
                    00B9    432 _PT0	=	0x00b9
                    00BA    433 _PX1	=	0x00ba
                    00BB    434 _PT1	=	0x00bb
                    00BC    435 _PS0	=	0x00bc
                    00BD    436 _PT2	=	0x00bd
                    00BE    437 _PS1	=	0x00be
                    00C0    438 _RI1	=	0x00c0
                    00C1    439 _TI1	=	0x00c1
                    00C2    440 _RB81	=	0x00c2
                    00C3    441 _TB81	=	0x00c3
                    00C4    442 _REN1	=	0x00c4
                    00C5    443 _SM21	=	0x00c5
                    00C6    444 _SM11	=	0x00c6
                    00C7    445 _SM01	=	0x00c7
                    00C8    446 _CP_RL2	=	0x00c8
                    00C9    447 _C_T2	=	0x00c9
                    00CA    448 _TR2	=	0x00ca
                    00CB    449 _EXEN2	=	0x00cb
                    00CC    450 _TCLK	=	0x00cc
                    00CD    451 _RCLK	=	0x00cd
                    00CE    452 _EXF2	=	0x00ce
                    00CF    453 _TF2	=	0x00cf
                    00D0    454 _P	=	0x00d0
                    00D1    455 _FL	=	0x00d1
                    00D2    456 _OV	=	0x00d2
                    00D3    457 _RS0	=	0x00d3
                    00D4    458 _RS1	=	0x00d4
                    00D5    459 _F0	=	0x00d5
                    00D6    460 _AC	=	0x00d6
                    00D7    461 _CY	=	0x00d7
                    00DB    462 _INT6	=	0x00db
                    00DC    463 _RESI	=	0x00dc
                    00DD    464 _ERESI	=	0x00dd
                    00DF    465 _SMOD1	=	0x00df
                    00E8    466 _EIUSB	=	0x00e8
                    00E9    467 _EI2C	=	0x00e9
                    00EA    468 _EIEX4	=	0x00ea
                    00EB    469 _EIEX5	=	0x00eb
                    00EC    470 _EIEX6	=	0x00ec
                    00F8    471 _PUSB	=	0x00f8
                    00F9    472 _PI2C	=	0x00f9
                    00FA    473 _EIPX4	=	0x00fa
                    00FB    474 _EIPX5	=	0x00fb
                    00FC    475 _EIPX6	=	0x00fc
                    0080    476 _bitS_CLK	=	0x0080
                    0081    477 _bitS_OUT	=	0x0081
                    0082    478 _bitS_IN	=	0x0082
                    00A1    479 _bitALTERA_DATA0	=	0x00a1
                    00A3    480 _bitALTERA_DCLK	=	0x00a3
                            481 ;--------------------------------------------------------
                            482 ; overlayable register banks
                            483 ;--------------------------------------------------------
                            484 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                     485 	.ds 8
                            486 ;--------------------------------------------------------
                            487 ; internal ram data
                            488 ;--------------------------------------------------------
                            489 	.area DSEG    (DATA)
   0022                     490 _spi_read_PARM_2:
   0022                     491 	.ds 1
   0023                     492 _spi_read_PARM_3:
   0023                     493 	.ds 1
   0024                     494 _spi_read_PARM_4:
   0024                     495 	.ds 1
   0025                     496 _spi_read_PARM_5:
   0025                     497 	.ds 2
   0027                     498 _spi_read_PARM_6:
   0027                     499 	.ds 1
   0028                     500 _spi_write_PARM_2:
   0028                     501 	.ds 1
   0029                     502 _spi_write_PARM_3:
   0029                     503 	.ds 1
   002A                     504 _spi_write_PARM_4:
   002A                     505 	.ds 1
   002B                     506 _spi_write_PARM_5:
   002B                     507 	.ds 2
   002D                     508 _spi_write_PARM_6:
   002D                     509 	.ds 1
   002E                     510 _write_bytes_msb_PARM_2:
   002E                     511 	.ds 1
   002F                     512 _read_bytes_msb_PARM_2:
   002F                     513 	.ds 1
                            514 ;--------------------------------------------------------
                            515 ; overlayable items in internal ram 
                            516 ;--------------------------------------------------------
                            517 	.area	OSEG    (OVR,DATA)
                            518 	.area	OSEG    (OVR,DATA)
                            519 	.area	OSEG    (OVR,DATA)
                            520 ;--------------------------------------------------------
                            521 ; indirectly addressable internal ram data
                            522 ;--------------------------------------------------------
                            523 	.area ISEG    (DATA)
                            524 ;--------------------------------------------------------
                            525 ; absolute internal ram data
                            526 ;--------------------------------------------------------
                            527 	.area IABS    (ABS,DATA)
                            528 	.area IABS    (ABS,DATA)
                            529 ;--------------------------------------------------------
                            530 ; bit data
                            531 ;--------------------------------------------------------
                            532 	.area BSEG    (BIT)
                            533 ;--------------------------------------------------------
                            534 ; paged external ram data
                            535 ;--------------------------------------------------------
                            536 	.area PSEG    (PAG,XDATA)
                            537 ;--------------------------------------------------------
                            538 ; external ram data
                            539 ;--------------------------------------------------------
                            540 	.area XSEG    (XDATA)
                    E400    541 _GPIF_WAVE_DATA	=	0xe400
                    E480    542 _RES_WAVEDATA_END	=	0xe480
                    E600    543 _CPUCS	=	0xe600
                    E601    544 _IFCONFIG	=	0xe601
                    E602    545 _PINFLAGSAB	=	0xe602
                    E603    546 _PINFLAGSCD	=	0xe603
                    E604    547 _FIFORESET	=	0xe604
                    E605    548 _BREAKPT	=	0xe605
                    E606    549 _BPADDRH	=	0xe606
                    E607    550 _BPADDRL	=	0xe607
                    E608    551 _UART230	=	0xe608
                    E609    552 _FIFOPINPOLAR	=	0xe609
                    E60A    553 _REVID	=	0xe60a
                    E60B    554 _REVCTL	=	0xe60b
                    E610    555 _EP1OUTCFG	=	0xe610
                    E611    556 _EP1INCFG	=	0xe611
                    E612    557 _EP2CFG	=	0xe612
                    E613    558 _EP4CFG	=	0xe613
                    E614    559 _EP6CFG	=	0xe614
                    E615    560 _EP8CFG	=	0xe615
                    E618    561 _EP2FIFOCFG	=	0xe618
                    E619    562 _EP4FIFOCFG	=	0xe619
                    E61A    563 _EP6FIFOCFG	=	0xe61a
                    E61B    564 _EP8FIFOCFG	=	0xe61b
                    E620    565 _EP2AUTOINLENH	=	0xe620
                    E621    566 _EP2AUTOINLENL	=	0xe621
                    E622    567 _EP4AUTOINLENH	=	0xe622
                    E623    568 _EP4AUTOINLENL	=	0xe623
                    E624    569 _EP6AUTOINLENH	=	0xe624
                    E625    570 _EP6AUTOINLENL	=	0xe625
                    E626    571 _EP8AUTOINLENH	=	0xe626
                    E627    572 _EP8AUTOINLENL	=	0xe627
                    E630    573 _EP2FIFOPFH	=	0xe630
                    E631    574 _EP2FIFOPFL	=	0xe631
                    E632    575 _EP4FIFOPFH	=	0xe632
                    E633    576 _EP4FIFOPFL	=	0xe633
                    E634    577 _EP6FIFOPFH	=	0xe634
                    E635    578 _EP6FIFOPFL	=	0xe635
                    E636    579 _EP8FIFOPFH	=	0xe636
                    E637    580 _EP8FIFOPFL	=	0xe637
                    E640    581 _EP2ISOINPKTS	=	0xe640
                    E641    582 _EP4ISOINPKTS	=	0xe641
                    E642    583 _EP6ISOINPKTS	=	0xe642
                    E643    584 _EP8ISOINPKTS	=	0xe643
                    E648    585 _INPKTEND	=	0xe648
                    E649    586 _OUTPKTEND	=	0xe649
                    E650    587 _EP2FIFOIE	=	0xe650
                    E651    588 _EP2FIFOIRQ	=	0xe651
                    E652    589 _EP4FIFOIE	=	0xe652
                    E653    590 _EP4FIFOIRQ	=	0xe653
                    E654    591 _EP6FIFOIE	=	0xe654
                    E655    592 _EP6FIFOIRQ	=	0xe655
                    E656    593 _EP8FIFOIE	=	0xe656
                    E657    594 _EP8FIFOIRQ	=	0xe657
                    E658    595 _IBNIE	=	0xe658
                    E659    596 _IBNIRQ	=	0xe659
                    E65A    597 _NAKIE	=	0xe65a
                    E65B    598 _NAKIRQ	=	0xe65b
                    E65C    599 _USBIE	=	0xe65c
                    E65D    600 _USBIRQ	=	0xe65d
                    E65E    601 _EPIE	=	0xe65e
                    E65F    602 _EPIRQ	=	0xe65f
                    E660    603 _GPIFIE	=	0xe660
                    E661    604 _GPIFIRQ	=	0xe661
                    E662    605 _USBERRIE	=	0xe662
                    E663    606 _USBERRIRQ	=	0xe663
                    E664    607 _ERRCNTLIM	=	0xe664
                    E665    608 _CLRERRCNT	=	0xe665
                    E666    609 _INT2IVEC	=	0xe666
                    E667    610 _INT4IVEC	=	0xe667
                    E668    611 _INTSETUP	=	0xe668
                    E670    612 _PORTACFG	=	0xe670
                    E671    613 _PORTCCFG	=	0xe671
                    E672    614 _PORTECFG	=	0xe672
                    E678    615 _I2CS	=	0xe678
                    E679    616 _I2DAT	=	0xe679
                    E67A    617 _I2CTL	=	0xe67a
                    E67B    618 _XAUTODAT1	=	0xe67b
                    E67C    619 _XAUTODAT2	=	0xe67c
                    E680    620 _USBCS	=	0xe680
                    E681    621 _SUSPEND	=	0xe681
                    E682    622 _WAKEUPCS	=	0xe682
                    E683    623 _TOGCTL	=	0xe683
                    E684    624 _USBFRAMEH	=	0xe684
                    E685    625 _USBFRAMEL	=	0xe685
                    E686    626 _MICROFRAME	=	0xe686
                    E687    627 _FNADDR	=	0xe687
                    E68A    628 _EP0BCH	=	0xe68a
                    E68B    629 _EP0BCL	=	0xe68b
                    E68D    630 _EP1OUTBC	=	0xe68d
                    E68F    631 _EP1INBC	=	0xe68f
                    E690    632 _EP2BCH	=	0xe690
                    E691    633 _EP2BCL	=	0xe691
                    E694    634 _EP4BCH	=	0xe694
                    E695    635 _EP4BCL	=	0xe695
                    E698    636 _EP6BCH	=	0xe698
                    E699    637 _EP6BCL	=	0xe699
                    E69C    638 _EP8BCH	=	0xe69c
                    E69D    639 _EP8BCL	=	0xe69d
                    E6A0    640 _EP0CS	=	0xe6a0
                    E6A1    641 _EP1OUTCS	=	0xe6a1
                    E6A2    642 _EP1INCS	=	0xe6a2
                    E6A3    643 _EP2CS	=	0xe6a3
                    E6A4    644 _EP4CS	=	0xe6a4
                    E6A5    645 _EP6CS	=	0xe6a5
                    E6A6    646 _EP8CS	=	0xe6a6
                    E6A7    647 _EP2FIFOFLGS	=	0xe6a7
                    E6A8    648 _EP4FIFOFLGS	=	0xe6a8
                    E6A9    649 _EP6FIFOFLGS	=	0xe6a9
                    E6AA    650 _EP8FIFOFLGS	=	0xe6aa
                    E6AB    651 _EP2FIFOBCH	=	0xe6ab
                    E6AC    652 _EP2FIFOBCL	=	0xe6ac
                    E6AD    653 _EP4FIFOBCH	=	0xe6ad
                    E6AE    654 _EP4FIFOBCL	=	0xe6ae
                    E6AF    655 _EP6FIFOBCH	=	0xe6af
                    E6B0    656 _EP6FIFOBCL	=	0xe6b0
                    E6B1    657 _EP8FIFOBCH	=	0xe6b1
                    E6B2    658 _EP8FIFOBCL	=	0xe6b2
                    E6B3    659 _SUDPTRH	=	0xe6b3
                    E6B4    660 _SUDPTRL	=	0xe6b4
                    E6B5    661 _SUDPTRCTL	=	0xe6b5
                    E6B8    662 _SETUPDAT	=	0xe6b8
                    E6C0    663 _GPIFWFSELECT	=	0xe6c0
                    E6C1    664 _GPIFIDLECS	=	0xe6c1
                    E6C2    665 _GPIFIDLECTL	=	0xe6c2
                    E6C3    666 _GPIFCTLCFG	=	0xe6c3
                    E6C4    667 _GPIFADRH	=	0xe6c4
                    E6C5    668 _GPIFADRL	=	0xe6c5
                    E6CE    669 _GPIFTCB3	=	0xe6ce
                    E6CF    670 _GPIFTCB2	=	0xe6cf
                    E6D0    671 _GPIFTCB1	=	0xe6d0
                    E6D1    672 _GPIFTCB0	=	0xe6d1
                    E6D2    673 _EP2GPIFFLGSEL	=	0xe6d2
                    E6D3    674 _EP2GPIFPFSTOP	=	0xe6d3
                    E6D4    675 _EP2GPIFTRIG	=	0xe6d4
                    E6DA    676 _EP4GPIFFLGSEL	=	0xe6da
                    E6DB    677 _EP4GPIFPFSTOP	=	0xe6db
                    E6DC    678 _EP4GPIFTRIG	=	0xe6dc
                    E6E2    679 _EP6GPIFFLGSEL	=	0xe6e2
                    E6E3    680 _EP6GPIFPFSTOP	=	0xe6e3
                    E6E4    681 _EP6GPIFTRIG	=	0xe6e4
                    E6EA    682 _EP8GPIFFLGSEL	=	0xe6ea
                    E6EB    683 _EP8GPIFPFSTOP	=	0xe6eb
                    E6EC    684 _EP8GPIFTRIG	=	0xe6ec
                    E6F0    685 _XGPIFSGLDATH	=	0xe6f0
                    E6F1    686 _XGPIFSGLDATLX	=	0xe6f1
                    E6F2    687 _XGPIFSGLDATLNOX	=	0xe6f2
                    E6F3    688 _GPIFREADYCFG	=	0xe6f3
                    E6F4    689 _GPIFREADYSTAT	=	0xe6f4
                    E6F5    690 _GPIFABORT	=	0xe6f5
                    E6C6    691 _FLOWSTATE	=	0xe6c6
                    E6C7    692 _FLOWLOGIC	=	0xe6c7
                    E6C8    693 _FLOWEQ0CTL	=	0xe6c8
                    E6C9    694 _FLOWEQ1CTL	=	0xe6c9
                    E6CA    695 _FLOWHOLDOFF	=	0xe6ca
                    E6CB    696 _FLOWSTB	=	0xe6cb
                    E6CC    697 _FLOWSTBEDGE	=	0xe6cc
                    E6CD    698 _FLOWSTBHPERIOD	=	0xe6cd
                    E60C    699 _GPIFHOLDAMOUNT	=	0xe60c
                    E67D    700 _UDMACRCH	=	0xe67d
                    E67E    701 _UDMACRCL	=	0xe67e
                    E67F    702 _UDMACRCQUAL	=	0xe67f
                    E6F8    703 _DBUG	=	0xe6f8
                    E6F9    704 _TESTCFG	=	0xe6f9
                    E6FA    705 _USBTEST	=	0xe6fa
                    E6FB    706 _CT1	=	0xe6fb
                    E6FC    707 _CT2	=	0xe6fc
                    E6FD    708 _CT3	=	0xe6fd
                    E6FE    709 _CT4	=	0xe6fe
                    E740    710 _EP0BUF	=	0xe740
                    E780    711 _EP1OUTBUF	=	0xe780
                    E7C0    712 _EP1INBUF	=	0xe7c0
                    F000    713 _EP2FIFOBUF	=	0xf000
                    F400    714 _EP4FIFOBUF	=	0xf400
                    F800    715 _EP6FIFOBUF	=	0xf800
                    FC00    716 _EP8FIFOBUF	=	0xfc00
                            717 ;--------------------------------------------------------
                            718 ; absolute external ram data
                            719 ;--------------------------------------------------------
                            720 	.area XABS    (ABS,XDATA)
                            721 ;--------------------------------------------------------
                            722 ; external initialized ram data
                            723 ;--------------------------------------------------------
                            724 	.area HOME    (CODE)
                            725 	.area GSINIT0 (CODE)
                            726 	.area GSINIT1 (CODE)
                            727 	.area GSINIT2 (CODE)
                            728 	.area GSINIT3 (CODE)
                            729 	.area GSINIT4 (CODE)
                            730 	.area GSINIT5 (CODE)
                            731 	.area GSINIT  (CODE)
                            732 	.area GSFINAL (CODE)
                            733 	.area CSEG    (CODE)
                            734 ;--------------------------------------------------------
                            735 ; global & static initialisations
                            736 ;--------------------------------------------------------
                            737 	.area HOME    (CODE)
                            738 	.area GSINIT  (CODE)
                            739 	.area GSFINAL (CODE)
                            740 	.area GSINIT  (CODE)
                            741 ;--------------------------------------------------------
                            742 ; Home
                            743 ;--------------------------------------------------------
                            744 	.area HOME    (CODE)
                            745 	.area HOME    (CODE)
                            746 ;--------------------------------------------------------
                            747 ; code
                            748 ;--------------------------------------------------------
                            749 	.area CSEG    (CODE)
                            750 ;------------------------------------------------------------
                            751 ;Allocation info for local variables in function 'setup_enables'
                            752 ;------------------------------------------------------------
                            753 ;enables                   Allocated to registers r2 
                            754 ;------------------------------------------------------------
                            755 ;	spi.c:27: setup_enables (unsigned char enables)
                            756 ;	-----------------------------------------
                            757 ;	 function setup_enables
                            758 ;	-----------------------------------------
   07F9                     759 _setup_enables:
                    0002    760 	ar2 = 0x02
                    0003    761 	ar3 = 0x03
                    0004    762 	ar4 = 0x04
                    0005    763 	ar5 = 0x05
                    0006    764 	ar6 = 0x06
                    0007    765 	ar7 = 0x07
                    0000    766 	ar0 = 0x00
                    0001    767 	ar1 = 0x01
   07F9 AA 82               768 	mov	r2,dpl
                            769 ;	spi.c:33: enables ^= SPI_ENABLE_FPGA;
   07FB 63 02 01            770 	xrl	ar2,#0x01
                            771 ;	spi.c:37: USRP_PA = USRP_PA | (0x7 << 3);	// disable FPGA, CODEC_A, CODEC_B
   07FE 43 80 38            772 	orl	_IOA,#0x38
                            773 ;	spi.c:38: USRP_PA ^= (enables & 0x7) << 3;	// enable specified devs
   0801 74 07               774 	mov	a,#0x07
   0803 5A                  775 	anl	a,r2
   0804 C4                  776 	swap	a
   0805 03                  777 	rr	a
   0806 54 F8               778 	anl	a,#0xf8
   0808 62 80               779 	xrl	_IOA,a
                            780 ;	spi.c:41: USRP_PE = USRP_PE | (0xf << 4);	// disable TX_A, RX_A, TX_B, RX_B
   080A 43 B1 F0            781 	orl	_IOE,#0xF0
                            782 ;	spi.c:42: USRP_PE ^= (enables & 0xf0);		// enable specified devs
   080D 74 F0               783 	mov	a,#0xF0
   080F 5A                  784 	anl	a,r2
   0810 62 B1               785 	xrl	_IOE,a
   0812 22                  786 	ret
                            787 ;------------------------------------------------------------
                            788 ;Allocation info for local variables in function 'init_spi'
                            789 ;------------------------------------------------------------
                            790 ;------------------------------------------------------------
                            791 ;	spi.c:48: init_spi (void)
                            792 ;	-----------------------------------------
                            793 ;	 function init_spi
                            794 ;	-----------------------------------------
   0813                     795 _init_spi:
                            796 ;	spi.c:50: disable_all ();		/* disable all devs	  */
   0813 75 82 00            797 	mov	dpl,#0x00
   0816 12 07 F9            798 	lcall	_setup_enables
                            799 ;	spi.c:51: bitS_OUT = 0;			/* idle state has CLK = 0 */
   0819 C2 81               800 	clr	_bitS_OUT
   081B 22                  801 	ret
                            802 ;------------------------------------------------------------
                            803 ;Allocation info for local variables in function 'count_bits8'
                            804 ;------------------------------------------------------------
                            805 ;v                         Allocated to registers r2 
                            806 ;count                     Allocated to registers r3 
                            807 ;------------------------------------------------------------
                            808 ;	spi.c:82: count_bits8 (unsigned char v)
                            809 ;	-----------------------------------------
                            810 ;	 function count_bits8
                            811 ;	-----------------------------------------
   081C                     812 _count_bits8:
   081C AA 82               813 	mov	r2,dpl
                            814 ;	spi.c:84: unsigned char count = 0;
   081E 7B 00               815 	mov	r3,#0x00
                            816 ;	spi.c:85: if (v & (1 << 0)) count++;
   0820 EA                  817 	mov	a,r2
   0821 30 E0 02            818 	jnb	acc.0,00102$
   0824 7B 01               819 	mov	r3,#0x01
   0826                     820 00102$:
                            821 ;	spi.c:86: if (v & (1 << 1)) count++;
   0826 EA                  822 	mov	a,r2
   0827 30 E1 01            823 	jnb	acc.1,00104$
   082A 0B                  824 	inc	r3
   082B                     825 00104$:
                            826 ;	spi.c:87: if (v & (1 << 2)) count++;
   082B EA                  827 	mov	a,r2
   082C 30 E2 01            828 	jnb	acc.2,00106$
   082F 0B                  829 	inc	r3
   0830                     830 00106$:
                            831 ;	spi.c:88: if (v & (1 << 3)) count++;
   0830 EA                  832 	mov	a,r2
   0831 30 E3 01            833 	jnb	acc.3,00108$
   0834 0B                  834 	inc	r3
   0835                     835 00108$:
                            836 ;	spi.c:89: if (v & (1 << 4)) count++;
   0835 EA                  837 	mov	a,r2
   0836 30 E4 01            838 	jnb	acc.4,00110$
   0839 0B                  839 	inc	r3
   083A                     840 00110$:
                            841 ;	spi.c:90: if (v & (1 << 5)) count++;
   083A EA                  842 	mov	a,r2
   083B 30 E5 01            843 	jnb	acc.5,00112$
   083E 0B                  844 	inc	r3
   083F                     845 00112$:
                            846 ;	spi.c:91: if (v & (1 << 6)) count++;
   083F EA                  847 	mov	a,r2
   0840 30 E6 01            848 	jnb	acc.6,00114$
   0843 0B                  849 	inc	r3
   0844                     850 00114$:
                            851 ;	spi.c:92: if (v & (1 << 7)) count++;
   0844 EA                  852 	mov	a,r2
   0845 30 E7 01            853 	jnb	acc.7,00116$
   0848 0B                  854 	inc	r3
   0849                     855 00116$:
                            856 ;	spi.c:93: return count;
   0849 8B 82               857 	mov	dpl,r3
   084B 22                  858 	ret
                            859 ;------------------------------------------------------------
                            860 ;Allocation info for local variables in function 'spi_read'
                            861 ;------------------------------------------------------------
                            862 ;header_lo                 Allocated with name '_spi_read_PARM_2'
                            863 ;enables                   Allocated with name '_spi_read_PARM_3'
                            864 ;format                    Allocated with name '_spi_read_PARM_4'
                            865 ;buf                       Allocated with name '_spi_read_PARM_5'
                            866 ;len                       Allocated with name '_spi_read_PARM_6'
                            867 ;header_hi                 Allocated to registers r2 
                            868 ;------------------------------------------------------------
                            869 ;	spi.c:109: spi_read (unsigned char header_hi, unsigned char header_lo,
                            870 ;	-----------------------------------------
                            871 ;	 function spi_read
                            872 ;	-----------------------------------------
   084C                     873 _spi_read:
   084C AA 82               874 	mov	r2,dpl
                            875 ;	spi.c:113: if (count_bits8 (enables) > 1)
   084E 85 23 82            876 	mov	dpl,_spi_read_PARM_3
   0851 C0 02               877 	push	ar2
   0853 12 08 1C            878 	lcall	_count_bits8
   0856 AB 82               879 	mov	r3,dpl
   0858 D0 02               880 	pop	ar2
   085A EB                  881 	mov	a,r3
   085B 24 FE               882 	add	a,#0xff - 0x01
   085D 50 04               883 	jnc	00102$
                            884 ;	spi.c:114: return 0;		// error, too many enables set
   085F 75 82 00            885 	mov	dpl,#0x00
   0862 22                  886 	ret
   0863                     887 00102$:
                            888 ;	spi.c:116: setup_enables (enables);
   0863 85 23 82            889 	mov	dpl,_spi_read_PARM_3
   0866 C0 02               890 	push	ar2
   0868 12 07 F9            891 	lcall	_setup_enables
   086B D0 02               892 	pop	ar2
                            893 ;	spi.c:118: if (format & SPI_FMT_LSB){		// order: LSB
   086D E5 24               894 	mov	a,_spi_read_PARM_4
   086F 30 E7 04            895 	jnb	acc.7,00111$
                            896 ;	spi.c:120: return 0;		// error, not implemented
   0872 75 82 00            897 	mov	dpl,#0x00
   0875 22                  898 	ret
   0876                     899 00111$:
                            900 ;	spi.c:142: switch (format & SPI_FMT_HDR_MASK){
   0876 74 60               901 	mov	a,#0x60
   0878 55 24               902 	anl	a,_spi_read_PARM_4
   087A FB                  903 	mov	r3,a
   087B 60 23               904 	jz	00107$
   087D BB 20 02            905 	cjne	r3,#0x20,00124$
   0880 80 05               906 	sjmp	00104$
   0882                     907 00124$:
                            908 ;	spi.c:145: case SPI_FMT_HDR_1:
   0882 BB 40 17            909 	cjne	r3,#0x40,00106$
   0885 80 08               910 	sjmp	00105$
   0887                     911 00104$:
                            912 ;	spi.c:146: write_byte_msb (header_lo);
   0887 85 22 82            913 	mov	dpl,_spi_read_PARM_2
   088A 12 09 13            914 	lcall	_write_byte_msb
                            915 ;	spi.c:147: break;
                            916 ;	spi.c:148: case SPI_FMT_HDR_2:
   088D 80 11               917 	sjmp	00107$
   088F                     918 00105$:
                            919 ;	spi.c:149: write_byte_msb (header_hi);
   088F 8A 82               920 	mov	dpl,r2
   0891 12 09 13            921 	lcall	_write_byte_msb
                            922 ;	spi.c:150: write_byte_msb (header_lo);
   0894 85 22 82            923 	mov	dpl,_spi_read_PARM_2
   0897 12 09 13            924 	lcall	_write_byte_msb
                            925 ;	spi.c:151: break;
                            926 ;	spi.c:152: default:
   089A 80 04               927 	sjmp	00107$
   089C                     928 00106$:
                            929 ;	spi.c:153: return 0;		// error
   089C 75 82 00            930 	mov	dpl,#0x00
                            931 ;	spi.c:154: }
   089F 22                  932 	ret
   08A0                     933 00107$:
                            934 ;	spi.c:155: if (len != 0)
   08A0 E5 27               935 	mov	a,_spi_read_PARM_6
   08A2 60 0C               936 	jz	00112$
                            937 ;	spi.c:156: read_bytes_msb (buf, len);
   08A4 85 27 2F            938 	mov	_read_bytes_msb_PARM_2,_spi_read_PARM_6
   08A7 85 25 82            939 	mov	dpl,_spi_read_PARM_5
   08AA 85 26 83            940 	mov	dph,(_spi_read_PARM_5 + 1)
   08AD 12 09 CB            941 	lcall	_read_bytes_msb
   08B0                     942 00112$:
                            943 ;	spi.c:159: disable_all ();
   08B0 75 82 00            944 	mov	dpl,#0x00
   08B3 12 07 F9            945 	lcall	_setup_enables
                            946 ;	spi.c:160: return 1;		// success
   08B6 75 82 01            947 	mov	dpl,#0x01
   08B9 22                  948 	ret
                            949 ;------------------------------------------------------------
                            950 ;Allocation info for local variables in function 'spi_write'
                            951 ;------------------------------------------------------------
                            952 ;header_lo                 Allocated with name '_spi_write_PARM_2'
                            953 ;enables                   Allocated with name '_spi_write_PARM_3'
                            954 ;format                    Allocated with name '_spi_write_PARM_4'
                            955 ;buf                       Allocated with name '_spi_write_PARM_5'
                            956 ;len                       Allocated with name '_spi_write_PARM_6'
                            957 ;header_hi                 Allocated to registers r2 
                            958 ;------------------------------------------------------------
                            959 ;	spi.c:166: spi_write (unsigned char header_hi, unsigned char header_lo,
                            960 ;	-----------------------------------------
                            961 ;	 function spi_write
                            962 ;	-----------------------------------------
   08BA                     963 _spi_write:
   08BA AA 82               964 	mov	r2,dpl
                            965 ;	spi.c:170: setup_enables (enables);
   08BC 85 29 82            966 	mov	dpl,_spi_write_PARM_3
   08BF C0 02               967 	push	ar2
   08C1 12 07 F9            968 	lcall	_setup_enables
   08C4 D0 02               969 	pop	ar2
                            970 ;	spi.c:172: if (format & SPI_FMT_LSB){		// order: LSB
   08C6 E5 2A               971 	mov	a,_spi_write_PARM_4
   08C8 30 E7 04            972 	jnb	acc.7,00109$
                            973 ;	spi.c:174: return 0;		// error, not implemented
   08CB 75 82 00            974 	mov	dpl,#0x00
   08CE 22                  975 	ret
   08CF                     976 00109$:
                            977 ;	spi.c:196: switch (format & SPI_FMT_HDR_MASK){
   08CF 74 60               978 	mov	a,#0x60
   08D1 55 2A               979 	anl	a,_spi_write_PARM_4
   08D3 FB                  980 	mov	r3,a
   08D4 60 23               981 	jz	00105$
   08D6 BB 20 02            982 	cjne	r3,#0x20,00120$
   08D9 80 05               983 	sjmp	00102$
   08DB                     984 00120$:
                            985 ;	spi.c:199: case SPI_FMT_HDR_1:
   08DB BB 40 17            986 	cjne	r3,#0x40,00104$
   08DE 80 08               987 	sjmp	00103$
   08E0                     988 00102$:
                            989 ;	spi.c:200: write_byte_msb (header_lo);
   08E0 85 28 82            990 	mov	dpl,_spi_write_PARM_2
   08E3 12 09 13            991 	lcall	_write_byte_msb
                            992 ;	spi.c:201: break;
                            993 ;	spi.c:202: case SPI_FMT_HDR_2:
   08E6 80 11               994 	sjmp	00105$
   08E8                     995 00103$:
                            996 ;	spi.c:203: write_byte_msb (header_hi);
   08E8 8A 82               997 	mov	dpl,r2
   08EA 12 09 13            998 	lcall	_write_byte_msb
                            999 ;	spi.c:204: write_byte_msb (header_lo);
   08ED 85 28 82           1000 	mov	dpl,_spi_write_PARM_2
   08F0 12 09 13           1001 	lcall	_write_byte_msb
                           1002 ;	spi.c:205: break;
                           1003 ;	spi.c:206: default:
   08F3 80 04              1004 	sjmp	00105$
   08F5                    1005 00104$:
                           1006 ;	spi.c:207: return 0;		// error
   08F5 75 82 00           1007 	mov	dpl,#0x00
                           1008 ;	spi.c:208: }
   08F8 22                 1009 	ret
   08F9                    1010 00105$:
                           1011 ;	spi.c:209: if (len != 0)
   08F9 E5 2D              1012 	mov	a,_spi_write_PARM_6
   08FB 60 0C              1013 	jz	00110$
                           1014 ;	spi.c:210: write_bytes_msb (buf, len);
   08FD 85 2D 2E           1015 	mov	_write_bytes_msb_PARM_2,_spi_write_PARM_6
   0900 85 2B 82           1016 	mov	dpl,_spi_write_PARM_5
   0903 85 2C 83           1017 	mov	dph,(_spi_write_PARM_5 + 1)
   0906 12 09 64           1018 	lcall	_write_bytes_msb
   0909                    1019 00110$:
                           1020 ;	spi.c:213: disable_all ();
   0909 75 82 00           1021 	mov	dpl,#0x00
   090C 12 07 F9           1022 	lcall	_setup_enables
                           1023 ;	spi.c:214: return 1;		// success
   090F 75 82 01           1024 	mov	dpl,#0x01
   0912 22                 1025 	ret
                           1026 ;------------------------------------------------------------
                           1027 ;Allocation info for local variables in function 'write_byte_msb'
                           1028 ;------------------------------------------------------------
                           1029 ;v                         Allocated to registers r2 
                           1030 ;------------------------------------------------------------
                           1031 ;	spi.c:220: write_byte_msb (unsigned char v)
                           1032 ;	-----------------------------------------
                           1033 ;	 function write_byte_msb
                           1034 ;	-----------------------------------------
   0913                    1035 _write_byte_msb:
                           1036 ;	spi.c:222: v = (v << 1) | (v >> 7);	// rotate left (MSB into bottom bit)
   0913 E5 82              1037 	mov	a,dpl
   0915 23                 1038 	rl	a
                           1039 ;	spi.c:223: bitS_OUT = v & 0x1;
   0916 FA                 1040 	mov	r2,a
   0917 13                 1041 	rrc	a
   0918 92 81              1042 	mov	_bitS_OUT,c
                           1043 ;	spi.c:224: bitS_CLK = 1;
   091A D2 80              1044 	setb	_bitS_CLK
                           1045 ;	spi.c:225: bitS_CLK = 0;
   091C C2 80              1046 	clr	_bitS_CLK
                           1047 ;	spi.c:227: v = (v << 1) | (v >> 7);	// rotate left (MSB into bottom bit)
   091E EA                 1048 	mov	a,r2
   091F 23                 1049 	rl	a
                           1050 ;	spi.c:228: bitS_OUT = v & 0x1;
   0920 FA                 1051 	mov	r2,a
   0921 13                 1052 	rrc	a
   0922 92 81              1053 	mov	_bitS_OUT,c
                           1054 ;	spi.c:229: bitS_CLK = 1;
   0924 D2 80              1055 	setb	_bitS_CLK
                           1056 ;	spi.c:230: bitS_CLK = 0;
   0926 C2 80              1057 	clr	_bitS_CLK
                           1058 ;	spi.c:232: v = (v << 1) | (v >> 7);	// rotate left (MSB into bottom bit)
   0928 EA                 1059 	mov	a,r2
   0929 23                 1060 	rl	a
                           1061 ;	spi.c:233: bitS_OUT = v & 0x1;
   092A FA                 1062 	mov	r2,a
   092B 13                 1063 	rrc	a
   092C 92 81              1064 	mov	_bitS_OUT,c
                           1065 ;	spi.c:234: bitS_CLK = 1;
   092E D2 80              1066 	setb	_bitS_CLK
                           1067 ;	spi.c:235: bitS_CLK = 0;
   0930 C2 80              1068 	clr	_bitS_CLK
                           1069 ;	spi.c:237: v = (v << 1) | (v >> 7);	// rotate left (MSB into bottom bit)
   0932 EA                 1070 	mov	a,r2
   0933 23                 1071 	rl	a
                           1072 ;	spi.c:238: bitS_OUT = v & 0x1;
   0934 FA                 1073 	mov	r2,a
   0935 13                 1074 	rrc	a
   0936 92 81              1075 	mov	_bitS_OUT,c
                           1076 ;	spi.c:239: bitS_CLK = 1;
   0938 D2 80              1077 	setb	_bitS_CLK
                           1078 ;	spi.c:240: bitS_CLK = 0;
   093A C2 80              1079 	clr	_bitS_CLK
                           1080 ;	spi.c:242: v = (v << 1) | (v >> 7);	// rotate left (MSB into bottom bit)
   093C EA                 1081 	mov	a,r2
   093D 23                 1082 	rl	a
                           1083 ;	spi.c:243: bitS_OUT = v & 0x1;
   093E FA                 1084 	mov	r2,a
   093F 13                 1085 	rrc	a
   0940 92 81              1086 	mov	_bitS_OUT,c
                           1087 ;	spi.c:244: bitS_CLK = 1;
   0942 D2 80              1088 	setb	_bitS_CLK
                           1089 ;	spi.c:245: bitS_CLK = 0;
   0944 C2 80              1090 	clr	_bitS_CLK
                           1091 ;	spi.c:247: v = (v << 1) | (v >> 7);	// rotate left (MSB into bottom bit)
   0946 EA                 1092 	mov	a,r2
   0947 23                 1093 	rl	a
                           1094 ;	spi.c:248: bitS_OUT = v & 0x1;
   0948 FA                 1095 	mov	r2,a
   0949 13                 1096 	rrc	a
   094A 92 81              1097 	mov	_bitS_OUT,c
                           1098 ;	spi.c:249: bitS_CLK = 1;
   094C D2 80              1099 	setb	_bitS_CLK
                           1100 ;	spi.c:250: bitS_CLK = 0;
   094E C2 80              1101 	clr	_bitS_CLK
                           1102 ;	spi.c:252: v = (v << 1) | (v >> 7);	// rotate left (MSB into bottom bit)
   0950 EA                 1103 	mov	a,r2
   0951 23                 1104 	rl	a
                           1105 ;	spi.c:253: bitS_OUT = v & 0x1;
   0952 FA                 1106 	mov	r2,a
   0953 13                 1107 	rrc	a
   0954 92 81              1108 	mov	_bitS_OUT,c
                           1109 ;	spi.c:254: bitS_CLK = 1;
   0956 D2 80              1110 	setb	_bitS_CLK
                           1111 ;	spi.c:255: bitS_CLK = 0;
   0958 C2 80              1112 	clr	_bitS_CLK
                           1113 ;	spi.c:257: v = (v << 1) | (v >> 7);	// rotate left (MSB into bottom bit)
   095A EA                 1114 	mov	a,r2
   095B 23                 1115 	rl	a
                           1116 ;	spi.c:258: bitS_OUT = v & 0x1;
   095C 13                 1117 	rrc	a
   095D 92 81              1118 	mov	_bitS_OUT,c
                           1119 ;	spi.c:259: bitS_CLK = 1;
   095F D2 80              1120 	setb	_bitS_CLK
                           1121 ;	spi.c:260: bitS_CLK = 0;
   0961 C2 80              1122 	clr	_bitS_CLK
   0963 22                 1123 	ret
                           1124 ;------------------------------------------------------------
                           1125 ;Allocation info for local variables in function 'write_bytes_msb'
                           1126 ;------------------------------------------------------------
                           1127 ;len                       Allocated with name '_write_bytes_msb_PARM_2'
                           1128 ;buf                       Allocated to registers r2 r3 
                           1129 ;------------------------------------------------------------
                           1130 ;	spi.c:264: write_bytes_msb (const xdata unsigned char *buf, unsigned char len)
                           1131 ;	-----------------------------------------
                           1132 ;	 function write_bytes_msb
                           1133 ;	-----------------------------------------
   0964                    1134 _write_bytes_msb:
   0964 AA 82              1135 	mov	r2,dpl
   0966 AB 83              1136 	mov	r3,dph
                           1137 ;	spi.c:266: while (len-- != 0){
   0968 AC 2E              1138 	mov	r4,_write_bytes_msb_PARM_2
   096A                    1139 00101$:
   096A 8C 05              1140 	mov	ar5,r4
   096C 1C                 1141 	dec	r4
   096D ED                 1142 	mov	a,r5
   096E 60 1E              1143 	jz	00104$
                           1144 ;	spi.c:267: write_byte_msb (*buf++);
   0970 8A 82              1145 	mov	dpl,r2
   0972 8B 83              1146 	mov	dph,r3
   0974 E0                 1147 	movx	a,@dptr
   0975 FD                 1148 	mov	r5,a
   0976 A3                 1149 	inc	dptr
   0977 AA 82              1150 	mov	r2,dpl
   0979 AB 83              1151 	mov	r3,dph
   097B 8D 82              1152 	mov	dpl,r5
   097D C0 02              1153 	push	ar2
   097F C0 03              1154 	push	ar3
   0981 C0 04              1155 	push	ar4
   0983 12 09 13           1156 	lcall	_write_byte_msb
   0986 D0 04              1157 	pop	ar4
   0988 D0 03              1158 	pop	ar3
   098A D0 02              1159 	pop	ar2
   098C 80 DC              1160 	sjmp	00101$
   098E                    1161 00104$:
   098E 22                 1162 	ret
                           1163 ;------------------------------------------------------------
                           1164 ;Allocation info for local variables in function 'read_byte_msb'
                           1165 ;------------------------------------------------------------
                           1166 ;------------------------------------------------------------
                           1167 ;	spi.c:323: read_byte_msb (void) _naked
                           1168 ;	-----------------------------------------
                           1169 ;	 function read_byte_msb
                           1170 ;	-----------------------------------------
   098F                    1171 _read_byte_msb:
                           1172 ;	naked function: no prologue.
                           1173 ;	spi.c:370: _endasm;
                           1174 	
   098F E4                 1175 	 clr a
                           1176 	
   0990 D2 80              1177 	 setb _bitS_CLK
   0992 A2 82              1178 	        mov c, _bitS_IN
   0994 33                 1179 	 rlc a
   0995 C2 80              1180 	 clr _bitS_CLK
                           1181 	
   0997 D2 80              1182 	 setb _bitS_CLK
   0999 A2 82              1183 	        mov c, _bitS_IN
   099B 33                 1184 	 rlc a
   099C C2 80              1185 	 clr _bitS_CLK
                           1186 	
   099E D2 80              1187 	 setb _bitS_CLK
   09A0 A2 82              1188 	        mov c, _bitS_IN
   09A2 33                 1189 	 rlc a
   09A3 C2 80              1190 	 clr _bitS_CLK
                           1191 	
   09A5 D2 80              1192 	 setb _bitS_CLK
   09A7 A2 82              1193 	        mov c, _bitS_IN
   09A9 33                 1194 	 rlc a
   09AA C2 80              1195 	 clr _bitS_CLK
                           1196 	
   09AC D2 80              1197 	 setb _bitS_CLK
   09AE A2 82              1198 	        mov c, _bitS_IN
   09B0 33                 1199 	 rlc a
   09B1 C2 80              1200 	 clr _bitS_CLK
                           1201 	
   09B3 D2 80              1202 	 setb _bitS_CLK
   09B5 A2 82              1203 	        mov c, _bitS_IN
   09B7 33                 1204 	 rlc a
   09B8 C2 80              1205 	 clr _bitS_CLK
                           1206 	
   09BA D2 80              1207 	 setb _bitS_CLK
   09BC A2 82              1208 	        mov c, _bitS_IN
   09BE 33                 1209 	 rlc a
   09BF C2 80              1210 	 clr _bitS_CLK
                           1211 	
   09C1 D2 80              1212 	 setb _bitS_CLK
   09C3 A2 82              1213 	        mov c, _bitS_IN
   09C5 33                 1214 	 rlc a
   09C6 C2 80              1215 	 clr _bitS_CLK
                           1216 	
   09C8 F5 82              1217 	 mov dpl,a
   09CA 22                 1218 	 ret
                           1219 	  
                           1220 ;	naked function: no epilogue.
                           1221 ;------------------------------------------------------------
                           1222 ;Allocation info for local variables in function 'read_bytes_msb'
                           1223 ;------------------------------------------------------------
                           1224 ;len                       Allocated with name '_read_bytes_msb_PARM_2'
                           1225 ;buf                       Allocated to registers r2 r3 
                           1226 ;------------------------------------------------------------
                           1227 ;	spi.c:375: read_bytes_msb (xdata unsigned char *buf, unsigned char len)
                           1228 ;	-----------------------------------------
                           1229 ;	 function read_bytes_msb
                           1230 ;	-----------------------------------------
   09CB                    1231 _read_bytes_msb:
   09CB AA 82              1232 	mov	r2,dpl
   09CD AB 83              1233 	mov	r3,dph
                           1234 ;	spi.c:377: while (len-- != 0){
   09CF AC 2F              1235 	mov	r4,_read_bytes_msb_PARM_2
   09D1                    1236 00101$:
   09D1 8C 05              1237 	mov	ar5,r4
   09D3 1C                 1238 	dec	r4
   09D4 ED                 1239 	mov	a,r5
   09D5 60 12              1240 	jz	00104$
                           1241 ;	spi.c:378: *buf++ = read_byte_msb ();
   09D7 12 09 8F           1242 	lcall	_read_byte_msb
   09DA AD 82              1243 	mov	r5,dpl
   09DC 8A 82              1244 	mov	dpl,r2
   09DE 8B 83              1245 	mov	dph,r3
   09E0 ED                 1246 	mov	a,r5
   09E1 F0                 1247 	movx	@dptr,a
   09E2 A3                 1248 	inc	dptr
   09E3 AA 82              1249 	mov	r2,dpl
   09E5 AB 83              1250 	mov	r3,dph
   09E7 80 E8              1251 	sjmp	00101$
   09E9                    1252 00104$:
   09E9 22                 1253 	ret
                           1254 	.area CSEG    (CODE)
                           1255 	.area CONST   (CODE)
                           1256 	.area CABS    (ABS,CODE)

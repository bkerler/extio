                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : free open source ANSI-C Compiler
                              3 ; Version 2.9.0 #5416 (Mar 22 2009) (MINGW32)
                              4 ; This file was generated Tue Oct 12 23:27:15 2010
                              5 ;--------------------------------------------------------
                              6 	.module fpga_load
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
                            323 	.globl _fpga_load_xfer_PARM_2
                            324 	.globl _clock_out_bytes_PARM_2
                            325 	.globl _fpga_load_begin
                            326 	.globl _fpga_load_xfer
                            327 	.globl _fpga_load_end
                            328 ;--------------------------------------------------------
                            329 ; special function registers
                            330 ;--------------------------------------------------------
                            331 	.area RSEG    (DATA)
                    0080    332 _IOA	=	0x0080
                    0081    333 _SP	=	0x0081
                    0082    334 _DPL	=	0x0082
                    0083    335 _DPH	=	0x0083
                    0084    336 _DPL1	=	0x0084
                    0085    337 _DPH1	=	0x0085
                    0086    338 _DPS	=	0x0086
                    0087    339 _PCON	=	0x0087
                    0088    340 _TCON	=	0x0088
                    0089    341 _TMOD	=	0x0089
                    008A    342 _TL0	=	0x008a
                    008B    343 _TL1	=	0x008b
                    008C    344 _TH0	=	0x008c
                    008D    345 _TH1	=	0x008d
                    008E    346 _CKCON	=	0x008e
                    0090    347 _IOB	=	0x0090
                    0091    348 _EXIF	=	0x0091
                    0092    349 _MPAGE	=	0x0092
                    0098    350 _SCON0	=	0x0098
                    0099    351 _SBUF0	=	0x0099
                    009A    352 _APTR1H	=	0x009a
                    009B    353 _APTR1L	=	0x009b
                    009C    354 _AUTODAT1	=	0x009c
                    009D    355 _AUTOPTRH2	=	0x009d
                    009E    356 _AUTOPTRL2	=	0x009e
                    009F    357 _AUTODAT2	=	0x009f
                    00A0    358 _IOC	=	0x00a0
                    00A1    359 _INT2CLR	=	0x00a1
                    00A2    360 _INT4CLR	=	0x00a2
                    00A8    361 _IE	=	0x00a8
                    00AA    362 _EP2468STAT	=	0x00aa
                    00AB    363 _EP24FIFOFLGS	=	0x00ab
                    00AC    364 _EP68FIFOFLGS	=	0x00ac
                    00AF    365 _AUTOPTRSETUP	=	0x00af
                    00B0    366 _IOD	=	0x00b0
                    00B1    367 _IOE	=	0x00b1
                    00B2    368 _OEA	=	0x00b2
                    00B3    369 _OEB	=	0x00b3
                    00B4    370 _OEC	=	0x00b4
                    00B5    371 _OED	=	0x00b5
                    00B6    372 _OEE	=	0x00b6
                    00B8    373 _IP	=	0x00b8
                    00BA    374 _EP01STAT	=	0x00ba
                    00BB    375 _GPIFTRIG	=	0x00bb
                    00BD    376 _GPIFSGLDATH	=	0x00bd
                    00BE    377 _GPIFSGLDATLX	=	0x00be
                    00BF    378 _GPIFSGLDATLNOX	=	0x00bf
                    00C0    379 _SCON1	=	0x00c0
                    00C1    380 _SBUF1	=	0x00c1
                    00C8    381 _T2CON	=	0x00c8
                    00CA    382 _RCAP2L	=	0x00ca
                    00CB    383 _RCAP2H	=	0x00cb
                    00CC    384 _TL2	=	0x00cc
                    00CD    385 _TH2	=	0x00cd
                    00D0    386 _PSW	=	0x00d0
                    00D8    387 _EICON	=	0x00d8
                    00E0    388 _ACC	=	0x00e0
                    00E8    389 _EIE	=	0x00e8
                    00F0    390 _B	=	0x00f0
                    00F8    391 _EIP	=	0x00f8
                            392 ;--------------------------------------------------------
                            393 ; special function bits
                            394 ;--------------------------------------------------------
                            395 	.area RSEG    (DATA)
                    0086    396 _SEL	=	0x0086
                    0088    397 _IT0	=	0x0088
                    0089    398 _IE0	=	0x0089
                    008A    399 _IT1	=	0x008a
                    008B    400 _IE1	=	0x008b
                    008C    401 _TR0	=	0x008c
                    008D    402 _TF0	=	0x008d
                    008E    403 _TR1	=	0x008e
                    008F    404 _TF1	=	0x008f
                    0098    405 _RI	=	0x0098
                    0099    406 _TI	=	0x0099
                    009A    407 _RB8	=	0x009a
                    009B    408 _TB8	=	0x009b
                    009C    409 _REN	=	0x009c
                    009D    410 _SM2	=	0x009d
                    009E    411 _SM1	=	0x009e
                    009F    412 _SM0	=	0x009f
                    00A8    413 _EX0	=	0x00a8
                    00A9    414 _ET0	=	0x00a9
                    00AA    415 _EX1	=	0x00aa
                    00AB    416 _ET1	=	0x00ab
                    00AC    417 _ES0	=	0x00ac
                    00AD    418 _ET2	=	0x00ad
                    00AE    419 _ES1	=	0x00ae
                    00AF    420 _EA	=	0x00af
                    00B8    421 _PX0	=	0x00b8
                    00B9    422 _PT0	=	0x00b9
                    00BA    423 _PX1	=	0x00ba
                    00BB    424 _PT1	=	0x00bb
                    00BC    425 _PS0	=	0x00bc
                    00BD    426 _PT2	=	0x00bd
                    00BE    427 _PS1	=	0x00be
                    00C0    428 _RI1	=	0x00c0
                    00C1    429 _TI1	=	0x00c1
                    00C2    430 _RB81	=	0x00c2
                    00C3    431 _TB81	=	0x00c3
                    00C4    432 _REN1	=	0x00c4
                    00C5    433 _SM21	=	0x00c5
                    00C6    434 _SM11	=	0x00c6
                    00C7    435 _SM01	=	0x00c7
                    00C8    436 _CP_RL2	=	0x00c8
                    00C9    437 _C_T2	=	0x00c9
                    00CA    438 _TR2	=	0x00ca
                    00CB    439 _EXEN2	=	0x00cb
                    00CC    440 _TCLK	=	0x00cc
                    00CD    441 _RCLK	=	0x00cd
                    00CE    442 _EXF2	=	0x00ce
                    00CF    443 _TF2	=	0x00cf
                    00D0    444 _P	=	0x00d0
                    00D1    445 _FL	=	0x00d1
                    00D2    446 _OV	=	0x00d2
                    00D3    447 _RS0	=	0x00d3
                    00D4    448 _RS1	=	0x00d4
                    00D5    449 _F0	=	0x00d5
                    00D6    450 _AC	=	0x00d6
                    00D7    451 _CY	=	0x00d7
                    00DB    452 _INT6	=	0x00db
                    00DC    453 _RESI	=	0x00dc
                    00DD    454 _ERESI	=	0x00dd
                    00DF    455 _SMOD1	=	0x00df
                    00E8    456 _EIUSB	=	0x00e8
                    00E9    457 _EI2C	=	0x00e9
                    00EA    458 _EIEX4	=	0x00ea
                    00EB    459 _EIEX5	=	0x00eb
                    00EC    460 _EIEX6	=	0x00ec
                    00F8    461 _PUSB	=	0x00f8
                    00F9    462 _PI2C	=	0x00f9
                    00FA    463 _EIPX4	=	0x00fa
                    00FB    464 _EIPX5	=	0x00fb
                    00FC    465 _EIPX6	=	0x00fc
                    0080    466 _bitS_CLK	=	0x0080
                    0081    467 _bitS_OUT	=	0x0081
                    0082    468 _bitS_IN	=	0x0082
                    00A1    469 _bitALTERA_DATA0	=	0x00a1
                    00A3    470 _bitALTERA_DCLK	=	0x00a3
                            471 ;--------------------------------------------------------
                            472 ; overlayable register banks
                            473 ;--------------------------------------------------------
                            474 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                     475 	.ds 8
                            476 ;--------------------------------------------------------
                            477 ; internal ram data
                            478 ;--------------------------------------------------------
                            479 	.area DSEG    (DATA)
   0010                     480 _clock_out_bytes_PARM_2:
   0010                     481 	.ds 2
   0012                     482 _fpga_load_xfer_PARM_2:
   0012                     483 	.ds 1
                            484 ;--------------------------------------------------------
                            485 ; overlayable items in internal ram 
                            486 ;--------------------------------------------------------
                            487 	.area	OSEG    (OVR,DATA)
                            488 	.area	OSEG    (OVR,DATA)
                            489 ;--------------------------------------------------------
                            490 ; indirectly addressable internal ram data
                            491 ;--------------------------------------------------------
                            492 	.area ISEG    (DATA)
                            493 ;--------------------------------------------------------
                            494 ; absolute internal ram data
                            495 ;--------------------------------------------------------
                            496 	.area IABS    (ABS,DATA)
                            497 	.area IABS    (ABS,DATA)
                            498 ;--------------------------------------------------------
                            499 ; bit data
                            500 ;--------------------------------------------------------
                            501 	.area BSEG    (BIT)
                            502 ;--------------------------------------------------------
                            503 ; paged external ram data
                            504 ;--------------------------------------------------------
                            505 	.area PSEG    (PAG,XDATA)
                            506 ;--------------------------------------------------------
                            507 ; external ram data
                            508 ;--------------------------------------------------------
                            509 	.area XSEG    (XDATA)
                    E400    510 _GPIF_WAVE_DATA	=	0xe400
                    E480    511 _RES_WAVEDATA_END	=	0xe480
                    E600    512 _CPUCS	=	0xe600
                    E601    513 _IFCONFIG	=	0xe601
                    E602    514 _PINFLAGSAB	=	0xe602
                    E603    515 _PINFLAGSCD	=	0xe603
                    E604    516 _FIFORESET	=	0xe604
                    E605    517 _BREAKPT	=	0xe605
                    E606    518 _BPADDRH	=	0xe606
                    E607    519 _BPADDRL	=	0xe607
                    E608    520 _UART230	=	0xe608
                    E609    521 _FIFOPINPOLAR	=	0xe609
                    E60A    522 _REVID	=	0xe60a
                    E60B    523 _REVCTL	=	0xe60b
                    E610    524 _EP1OUTCFG	=	0xe610
                    E611    525 _EP1INCFG	=	0xe611
                    E612    526 _EP2CFG	=	0xe612
                    E613    527 _EP4CFG	=	0xe613
                    E614    528 _EP6CFG	=	0xe614
                    E615    529 _EP8CFG	=	0xe615
                    E618    530 _EP2FIFOCFG	=	0xe618
                    E619    531 _EP4FIFOCFG	=	0xe619
                    E61A    532 _EP6FIFOCFG	=	0xe61a
                    E61B    533 _EP8FIFOCFG	=	0xe61b
                    E620    534 _EP2AUTOINLENH	=	0xe620
                    E621    535 _EP2AUTOINLENL	=	0xe621
                    E622    536 _EP4AUTOINLENH	=	0xe622
                    E623    537 _EP4AUTOINLENL	=	0xe623
                    E624    538 _EP6AUTOINLENH	=	0xe624
                    E625    539 _EP6AUTOINLENL	=	0xe625
                    E626    540 _EP8AUTOINLENH	=	0xe626
                    E627    541 _EP8AUTOINLENL	=	0xe627
                    E630    542 _EP2FIFOPFH	=	0xe630
                    E631    543 _EP2FIFOPFL	=	0xe631
                    E632    544 _EP4FIFOPFH	=	0xe632
                    E633    545 _EP4FIFOPFL	=	0xe633
                    E634    546 _EP6FIFOPFH	=	0xe634
                    E635    547 _EP6FIFOPFL	=	0xe635
                    E636    548 _EP8FIFOPFH	=	0xe636
                    E637    549 _EP8FIFOPFL	=	0xe637
                    E640    550 _EP2ISOINPKTS	=	0xe640
                    E641    551 _EP4ISOINPKTS	=	0xe641
                    E642    552 _EP6ISOINPKTS	=	0xe642
                    E643    553 _EP8ISOINPKTS	=	0xe643
                    E648    554 _INPKTEND	=	0xe648
                    E649    555 _OUTPKTEND	=	0xe649
                    E650    556 _EP2FIFOIE	=	0xe650
                    E651    557 _EP2FIFOIRQ	=	0xe651
                    E652    558 _EP4FIFOIE	=	0xe652
                    E653    559 _EP4FIFOIRQ	=	0xe653
                    E654    560 _EP6FIFOIE	=	0xe654
                    E655    561 _EP6FIFOIRQ	=	0xe655
                    E656    562 _EP8FIFOIE	=	0xe656
                    E657    563 _EP8FIFOIRQ	=	0xe657
                    E658    564 _IBNIE	=	0xe658
                    E659    565 _IBNIRQ	=	0xe659
                    E65A    566 _NAKIE	=	0xe65a
                    E65B    567 _NAKIRQ	=	0xe65b
                    E65C    568 _USBIE	=	0xe65c
                    E65D    569 _USBIRQ	=	0xe65d
                    E65E    570 _EPIE	=	0xe65e
                    E65F    571 _EPIRQ	=	0xe65f
                    E660    572 _GPIFIE	=	0xe660
                    E661    573 _GPIFIRQ	=	0xe661
                    E662    574 _USBERRIE	=	0xe662
                    E663    575 _USBERRIRQ	=	0xe663
                    E664    576 _ERRCNTLIM	=	0xe664
                    E665    577 _CLRERRCNT	=	0xe665
                    E666    578 _INT2IVEC	=	0xe666
                    E667    579 _INT4IVEC	=	0xe667
                    E668    580 _INTSETUP	=	0xe668
                    E670    581 _PORTACFG	=	0xe670
                    E671    582 _PORTCCFG	=	0xe671
                    E672    583 _PORTECFG	=	0xe672
                    E678    584 _I2CS	=	0xe678
                    E679    585 _I2DAT	=	0xe679
                    E67A    586 _I2CTL	=	0xe67a
                    E67B    587 _XAUTODAT1	=	0xe67b
                    E67C    588 _XAUTODAT2	=	0xe67c
                    E680    589 _USBCS	=	0xe680
                    E681    590 _SUSPEND	=	0xe681
                    E682    591 _WAKEUPCS	=	0xe682
                    E683    592 _TOGCTL	=	0xe683
                    E684    593 _USBFRAMEH	=	0xe684
                    E685    594 _USBFRAMEL	=	0xe685
                    E686    595 _MICROFRAME	=	0xe686
                    E687    596 _FNADDR	=	0xe687
                    E68A    597 _EP0BCH	=	0xe68a
                    E68B    598 _EP0BCL	=	0xe68b
                    E68D    599 _EP1OUTBC	=	0xe68d
                    E68F    600 _EP1INBC	=	0xe68f
                    E690    601 _EP2BCH	=	0xe690
                    E691    602 _EP2BCL	=	0xe691
                    E694    603 _EP4BCH	=	0xe694
                    E695    604 _EP4BCL	=	0xe695
                    E698    605 _EP6BCH	=	0xe698
                    E699    606 _EP6BCL	=	0xe699
                    E69C    607 _EP8BCH	=	0xe69c
                    E69D    608 _EP8BCL	=	0xe69d
                    E6A0    609 _EP0CS	=	0xe6a0
                    E6A1    610 _EP1OUTCS	=	0xe6a1
                    E6A2    611 _EP1INCS	=	0xe6a2
                    E6A3    612 _EP2CS	=	0xe6a3
                    E6A4    613 _EP4CS	=	0xe6a4
                    E6A5    614 _EP6CS	=	0xe6a5
                    E6A6    615 _EP8CS	=	0xe6a6
                    E6A7    616 _EP2FIFOFLGS	=	0xe6a7
                    E6A8    617 _EP4FIFOFLGS	=	0xe6a8
                    E6A9    618 _EP6FIFOFLGS	=	0xe6a9
                    E6AA    619 _EP8FIFOFLGS	=	0xe6aa
                    E6AB    620 _EP2FIFOBCH	=	0xe6ab
                    E6AC    621 _EP2FIFOBCL	=	0xe6ac
                    E6AD    622 _EP4FIFOBCH	=	0xe6ad
                    E6AE    623 _EP4FIFOBCL	=	0xe6ae
                    E6AF    624 _EP6FIFOBCH	=	0xe6af
                    E6B0    625 _EP6FIFOBCL	=	0xe6b0
                    E6B1    626 _EP8FIFOBCH	=	0xe6b1
                    E6B2    627 _EP8FIFOBCL	=	0xe6b2
                    E6B3    628 _SUDPTRH	=	0xe6b3
                    E6B4    629 _SUDPTRL	=	0xe6b4
                    E6B5    630 _SUDPTRCTL	=	0xe6b5
                    E6B8    631 _SETUPDAT	=	0xe6b8
                    E6C0    632 _GPIFWFSELECT	=	0xe6c0
                    E6C1    633 _GPIFIDLECS	=	0xe6c1
                    E6C2    634 _GPIFIDLECTL	=	0xe6c2
                    E6C3    635 _GPIFCTLCFG	=	0xe6c3
                    E6C4    636 _GPIFADRH	=	0xe6c4
                    E6C5    637 _GPIFADRL	=	0xe6c5
                    E6CE    638 _GPIFTCB3	=	0xe6ce
                    E6CF    639 _GPIFTCB2	=	0xe6cf
                    E6D0    640 _GPIFTCB1	=	0xe6d0
                    E6D1    641 _GPIFTCB0	=	0xe6d1
                    E6D2    642 _EP2GPIFFLGSEL	=	0xe6d2
                    E6D3    643 _EP2GPIFPFSTOP	=	0xe6d3
                    E6D4    644 _EP2GPIFTRIG	=	0xe6d4
                    E6DA    645 _EP4GPIFFLGSEL	=	0xe6da
                    E6DB    646 _EP4GPIFPFSTOP	=	0xe6db
                    E6DC    647 _EP4GPIFTRIG	=	0xe6dc
                    E6E2    648 _EP6GPIFFLGSEL	=	0xe6e2
                    E6E3    649 _EP6GPIFPFSTOP	=	0xe6e3
                    E6E4    650 _EP6GPIFTRIG	=	0xe6e4
                    E6EA    651 _EP8GPIFFLGSEL	=	0xe6ea
                    E6EB    652 _EP8GPIFPFSTOP	=	0xe6eb
                    E6EC    653 _EP8GPIFTRIG	=	0xe6ec
                    E6F0    654 _XGPIFSGLDATH	=	0xe6f0
                    E6F1    655 _XGPIFSGLDATLX	=	0xe6f1
                    E6F2    656 _XGPIFSGLDATLNOX	=	0xe6f2
                    E6F3    657 _GPIFREADYCFG	=	0xe6f3
                    E6F4    658 _GPIFREADYSTAT	=	0xe6f4
                    E6F5    659 _GPIFABORT	=	0xe6f5
                    E6C6    660 _FLOWSTATE	=	0xe6c6
                    E6C7    661 _FLOWLOGIC	=	0xe6c7
                    E6C8    662 _FLOWEQ0CTL	=	0xe6c8
                    E6C9    663 _FLOWEQ1CTL	=	0xe6c9
                    E6CA    664 _FLOWHOLDOFF	=	0xe6ca
                    E6CB    665 _FLOWSTB	=	0xe6cb
                    E6CC    666 _FLOWSTBEDGE	=	0xe6cc
                    E6CD    667 _FLOWSTBHPERIOD	=	0xe6cd
                    E60C    668 _GPIFHOLDAMOUNT	=	0xe60c
                    E67D    669 _UDMACRCH	=	0xe67d
                    E67E    670 _UDMACRCL	=	0xe67e
                    E67F    671 _UDMACRCQUAL	=	0xe67f
                    E6F8    672 _DBUG	=	0xe6f8
                    E6F9    673 _TESTCFG	=	0xe6f9
                    E6FA    674 _USBTEST	=	0xe6fa
                    E6FB    675 _CT1	=	0xe6fb
                    E6FC    676 _CT2	=	0xe6fc
                    E6FD    677 _CT3	=	0xe6fd
                    E6FE    678 _CT4	=	0xe6fe
                    E740    679 _EP0BUF	=	0xe740
                    E780    680 _EP1OUTBUF	=	0xe780
                    E7C0    681 _EP1INBUF	=	0xe7c0
                    F000    682 _EP2FIFOBUF	=	0xf000
                    F400    683 _EP4FIFOBUF	=	0xf400
                    F800    684 _EP6FIFOBUF	=	0xf800
                    FC00    685 _EP8FIFOBUF	=	0xfc00
                            686 ;--------------------------------------------------------
                            687 ; absolute external ram data
                            688 ;--------------------------------------------------------
                            689 	.area XABS    (ABS,XDATA)
                            690 ;--------------------------------------------------------
                            691 ; external initialized ram data
                            692 ;--------------------------------------------------------
                            693 	.area HOME    (CODE)
                            694 	.area GSINIT0 (CODE)
                            695 	.area GSINIT1 (CODE)
                            696 	.area GSINIT2 (CODE)
                            697 	.area GSINIT3 (CODE)
                            698 	.area GSINIT4 (CODE)
                            699 	.area GSINIT5 (CODE)
                            700 	.area GSINIT  (CODE)
                            701 	.area GSFINAL (CODE)
                            702 	.area CSEG    (CODE)
                            703 ;--------------------------------------------------------
                            704 ; global & static initialisations
                            705 ;--------------------------------------------------------
                            706 	.area HOME    (CODE)
                            707 	.area GSINIT  (CODE)
                            708 	.area GSFINAL (CODE)
                            709 	.area GSINIT  (CODE)
                            710 ;--------------------------------------------------------
                            711 ; Home
                            712 ;--------------------------------------------------------
                            713 	.area HOME    (CODE)
                            714 	.area HOME    (CODE)
                            715 ;--------------------------------------------------------
                            716 ; code
                            717 ;--------------------------------------------------------
                            718 	.area CSEG    (CODE)
                            719 ;------------------------------------------------------------
                            720 ;Allocation info for local variables in function 'fpga_load_begin'
                            721 ;------------------------------------------------------------
                            722 ;------------------------------------------------------------
                            723 ;	../common/fpga_load.c:37: fpga_load_begin (void)
                            724 ;	-----------------------------------------
                            725 ;	 function fpga_load_begin
                            726 ;	-----------------------------------------
   0660                     727 _fpga_load_begin:
                    0002    728 	ar2 = 0x02
                    0003    729 	ar3 = 0x03
                    0004    730 	ar4 = 0x04
                    0005    731 	ar5 = 0x05
                    0006    732 	ar6 = 0x06
                    0007    733 	ar7 = 0x07
                    0000    734 	ar0 = 0x00
                    0001    735 	ar1 = 0x01
                            736 ;	../common/fpga_load.c:39: USRP_ALTERA_CONFIG &= ~bmALTERA_BITS;		// clear all bits (NCONFIG low)
   0660 53 A0 C1            737 	anl	_IOC,#0xC1
                            738 ;	../common/fpga_load.c:40: udelay (40);					// wait 40 us
   0663 75 82 28            739 	mov	dpl,#0x28
   0666 12 11 E7            740 	lcall	_udelay
                            741 ;	../common/fpga_load.c:41: USRP_ALTERA_CONFIG |= bmALTERA_NCONFIG;	// set NCONFIG high
   0669 43 A0 04            742 	orl	_IOC,#0x04
                            743 ;	../common/fpga_load.c:46: while ((USRP_ALTERA_CONFIG & bmALTERA_NSTATUS) == 0) // wait for NSTATUS to go high
   066C                     744 00101$:
   066C E5 A0               745 	mov	a,_IOC
   066E 30 E5 FB            746 	jnb	acc.5,00101$
                            747 ;	../common/fpga_load.c:52: return 1;
   0671 75 82 01            748 	mov	dpl,#0x01
   0674 22                  749 	ret
                            750 ;------------------------------------------------------------
                            751 ;Allocation info for local variables in function 'clock_out_config_byte'
                            752 ;------------------------------------------------------------
                            753 ;bits                      Allocated to registers 
                            754 ;------------------------------------------------------------
                            755 ;	../common/fpga_load.c:92: clock_out_config_byte (unsigned char bits) _naked
                            756 ;	-----------------------------------------
                            757 ;	 function clock_out_config_byte
                            758 ;	-----------------------------------------
   0675                     759 _clock_out_config_byte:
                            760 ;	naked function: no prologue.
                            761 ;	../common/fpga_load.c:139: _endasm;
                            762 	
   0675 E5 82               763 	 mov a, dpl
                            764 	
   0677 13                  765 	 rrc a
   0678 92 A1               766 	 mov _bitALTERA_DATA0,c
   067A D2 A3               767 	 setb _bitALTERA_DCLK
   067C C2 A3               768 	 clr _bitALTERA_DCLK
                            769 	
   067E 13                  770 	 rrc a
   067F 92 A1               771 	 mov _bitALTERA_DATA0,c
   0681 D2 A3               772 	 setb _bitALTERA_DCLK
   0683 C2 A3               773 	 clr _bitALTERA_DCLK
                            774 	
   0685 13                  775 	 rrc a
   0686 92 A1               776 	 mov _bitALTERA_DATA0,c
   0688 D2 A3               777 	 setb _bitALTERA_DCLK
   068A C2 A3               778 	 clr _bitALTERA_DCLK
                            779 	
   068C 13                  780 	 rrc a
   068D 92 A1               781 	 mov _bitALTERA_DATA0,c
   068F D2 A3               782 	 setb _bitALTERA_DCLK
   0691 C2 A3               783 	 clr _bitALTERA_DCLK
                            784 	
   0693 13                  785 	 rrc a
   0694 92 A1               786 	 mov _bitALTERA_DATA0,c
   0696 D2 A3               787 	 setb _bitALTERA_DCLK
   0698 C2 A3               788 	 clr _bitALTERA_DCLK
                            789 	
   069A 13                  790 	 rrc a
   069B 92 A1               791 	 mov _bitALTERA_DATA0,c
   069D D2 A3               792 	 setb _bitALTERA_DCLK
   069F C2 A3               793 	 clr _bitALTERA_DCLK
                            794 	
   06A1 13                  795 	 rrc a
   06A2 92 A1               796 	 mov _bitALTERA_DATA0,c
   06A4 D2 A3               797 	 setb _bitALTERA_DCLK
   06A6 C2 A3               798 	 clr _bitALTERA_DCLK
                            799 	
   06A8 13                  800 	 rrc a
   06A9 92 A1               801 	 mov _bitALTERA_DATA0,c
   06AB D2 A3               802 	 setb _bitALTERA_DCLK
   06AD C2 A3               803 	 clr _bitALTERA_DCLK
                            804 	
   06AF 22                  805 	 ret
                            806 	
                            807 	    
                            808 ;	naked function: no epilogue.
                            809 ;------------------------------------------------------------
                            810 ;Allocation info for local variables in function 'clock_out_bytes'
                            811 ;------------------------------------------------------------
                            812 ;p                         Allocated with name '_clock_out_bytes_PARM_2'
                            813 ;bytecount                 Allocated to registers r2 
                            814 ;------------------------------------------------------------
                            815 ;	../common/fpga_load.c:145: clock_out_bytes (unsigned char bytecount,
                            816 ;	-----------------------------------------
                            817 ;	 function clock_out_bytes
                            818 ;	-----------------------------------------
   06B0                     819 _clock_out_bytes:
   06B0 AA 82               820 	mov	r2,dpl
                            821 ;	../common/fpga_load.c:148: while (bytecount-- > 0)
   06B2 AB 10               822 	mov	r3,_clock_out_bytes_PARM_2
   06B4 AC 11               823 	mov	r4,(_clock_out_bytes_PARM_2 + 1)
   06B6                     824 00101$:
   06B6 8A 05               825 	mov	ar5,r2
   06B8 1A                  826 	dec	r2
   06B9 ED                  827 	mov	a,r5
   06BA 60 12               828 	jz	00104$
                            829 ;	../common/fpga_load.c:149: clock_out_config_byte (*p++);
   06BC 8B 82               830 	mov	dpl,r3
   06BE 8C 83               831 	mov	dph,r4
   06C0 E0                  832 	movx	a,@dptr
   06C1 FD                  833 	mov	r5,a
   06C2 A3                  834 	inc	dptr
   06C3 AB 82               835 	mov	r3,dpl
   06C5 AC 83               836 	mov	r4,dph
   06C7 8D 82               837 	mov	dpl,r5
   06C9 12 06 75            838 	lcall	_clock_out_config_byte
   06CC 80 E8               839 	sjmp	00101$
   06CE                     840 00104$:
   06CE 22                  841 	ret
                            842 ;------------------------------------------------------------
                            843 ;Allocation info for local variables in function 'fpga_load_xfer'
                            844 ;------------------------------------------------------------
                            845 ;bytecount                 Allocated with name '_fpga_load_xfer_PARM_2'
                            846 ;p                         Allocated to registers 
                            847 ;------------------------------------------------------------
                            848 ;	../common/fpga_load.c:166: fpga_load_xfer (xdata unsigned char *p, unsigned char bytecount)
                            849 ;	-----------------------------------------
                            850 ;	 function fpga_load_xfer
                            851 ;	-----------------------------------------
   06CF                     852 _fpga_load_xfer:
   06CF 85 82 10            853 	mov	_clock_out_bytes_PARM_2,dpl
   06D2 85 83 11            854 	mov	(_clock_out_bytes_PARM_2 + 1),dph
                            855 ;	../common/fpga_load.c:168: clock_out_bytes (bytecount, p);
   06D5 85 12 82            856 	mov	dpl,_fpga_load_xfer_PARM_2
   06D8 12 06 B0            857 	lcall	_clock_out_bytes
                            858 ;	../common/fpga_load.c:169: return 1;
   06DB 75 82 01            859 	mov	dpl,#0x01
   06DE 22                  860 	ret
                            861 ;------------------------------------------------------------
                            862 ;Allocation info for local variables in function 'fpga_load_end'
                            863 ;------------------------------------------------------------
                            864 ;status                    Allocated to registers r2 
                            865 ;------------------------------------------------------------
                            866 ;	../common/fpga_load.c:176: fpga_load_end (void)
                            867 ;	-----------------------------------------
                            868 ;	 function fpga_load_end
                            869 ;	-----------------------------------------
   06DF                     870 _fpga_load_end:
                            871 ;	../common/fpga_load.c:178: unsigned char status = USRP_ALTERA_CONFIG;
                            872 ;	../common/fpga_load.c:183: if ((status & bmALTERA_NSTATUS) == 0)		// failed to program
   06DF E5 A0               873 	mov	a,_IOC
   06E1 FA                  874 	mov	r2,a
   06E2 20 E5 04            875 	jb	acc.5,00104$
                            876 ;	../common/fpga_load.c:184: return 0;
   06E5 75 82 00            877 	mov	dpl,#0x00
   06E8 22                  878 	ret
   06E9                     879 00104$:
                            880 ;	../common/fpga_load.c:186: if ((status & bmALTERA_CONF_DONE) == bmALTERA_CONF_DONE)
   06E9 53 02 10            881 	anl	ar2,#0x10
   06EC BA 10 04            882 	cjne	r2,#0x10,00106$
                            883 ;	../common/fpga_load.c:187: return 1;					// everything's cool
   06EF 75 82 01            884 	mov	dpl,#0x01
                            885 ;	../common/fpga_load.c:192: return 0;
   06F2 22                  886 	ret
   06F3                     887 00106$:
   06F3 75 82 00            888 	mov	dpl,#0x00
   06F6 22                  889 	ret
                            890 	.area CSEG    (CODE)
                            891 	.area CONST   (CODE)
                            892 	.area CABS    (ABS,CODE)

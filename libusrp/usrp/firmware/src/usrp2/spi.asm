;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 2.9.0 #5416 (Mar 22 2009) (MINGW32)
; This file was generated Tue Oct 12 23:27:17 2010
;--------------------------------------------------------
	.module spi
	.optsdcc -mmcs51 --model-small
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _bitALTERA_DCLK
	.globl _bitALTERA_DATA0
	.globl _bitS_IN
	.globl _bitS_OUT
	.globl _bitS_CLK
	.globl _EIPX6
	.globl _EIPX5
	.globl _EIPX4
	.globl _PI2C
	.globl _PUSB
	.globl _EIEX6
	.globl _EIEX5
	.globl _EIEX4
	.globl _EI2C
	.globl _EIUSB
	.globl _SMOD1
	.globl _ERESI
	.globl _RESI
	.globl _INT6
	.globl _CY
	.globl _AC
	.globl _F0
	.globl _RS1
	.globl _RS0
	.globl _OV
	.globl _FL
	.globl _P
	.globl _TF2
	.globl _EXF2
	.globl _RCLK
	.globl _TCLK
	.globl _EXEN2
	.globl _TR2
	.globl _C_T2
	.globl _CP_RL2
	.globl _SM01
	.globl _SM11
	.globl _SM21
	.globl _REN1
	.globl _TB81
	.globl _RB81
	.globl _TI1
	.globl _RI1
	.globl _PS1
	.globl _PT2
	.globl _PS0
	.globl _PT1
	.globl _PX1
	.globl _PT0
	.globl _PX0
	.globl _EA
	.globl _ES1
	.globl _ET2
	.globl _ES0
	.globl _ET1
	.globl _EX1
	.globl _ET0
	.globl _EX0
	.globl _SM0
	.globl _SM1
	.globl _SM2
	.globl _REN
	.globl _TB8
	.globl _RB8
	.globl _TI
	.globl _RI
	.globl _TF1
	.globl _TR1
	.globl _TF0
	.globl _TR0
	.globl _IE1
	.globl _IT1
	.globl _IE0
	.globl _IT0
	.globl _SEL
	.globl _EIP
	.globl _B
	.globl _EIE
	.globl _ACC
	.globl _EICON
	.globl _PSW
	.globl _TH2
	.globl _TL2
	.globl _RCAP2H
	.globl _RCAP2L
	.globl _T2CON
	.globl _SBUF1
	.globl _SCON1
	.globl _GPIFSGLDATLNOX
	.globl _GPIFSGLDATLX
	.globl _GPIFSGLDATH
	.globl _GPIFTRIG
	.globl _EP01STAT
	.globl _IP
	.globl _OEE
	.globl _OED
	.globl _OEC
	.globl _OEB
	.globl _OEA
	.globl _IOE
	.globl _IOD
	.globl _AUTOPTRSETUP
	.globl _EP68FIFOFLGS
	.globl _EP24FIFOFLGS
	.globl _EP2468STAT
	.globl _IE
	.globl _INT4CLR
	.globl _INT2CLR
	.globl _IOC
	.globl _AUTODAT2
	.globl _AUTOPTRL2
	.globl _AUTOPTRH2
	.globl _AUTODAT1
	.globl _APTR1L
	.globl _APTR1H
	.globl _SBUF0
	.globl _SCON0
	.globl _MPAGE
	.globl _EXIF
	.globl _IOB
	.globl _CKCON
	.globl _TH1
	.globl _TH0
	.globl _TL1
	.globl _TL0
	.globl _TMOD
	.globl _TCON
	.globl _PCON
	.globl _DPS
	.globl _DPH1
	.globl _DPL1
	.globl _DPH
	.globl _DPL
	.globl _SP
	.globl _IOA
	.globl _EP8FIFOBUF
	.globl _EP6FIFOBUF
	.globl _EP4FIFOBUF
	.globl _EP2FIFOBUF
	.globl _EP1INBUF
	.globl _EP1OUTBUF
	.globl _EP0BUF
	.globl _CT4
	.globl _CT3
	.globl _CT2
	.globl _CT1
	.globl _USBTEST
	.globl _TESTCFG
	.globl _DBUG
	.globl _UDMACRCQUAL
	.globl _UDMACRCL
	.globl _UDMACRCH
	.globl _GPIFHOLDAMOUNT
	.globl _FLOWSTBHPERIOD
	.globl _FLOWSTBEDGE
	.globl _FLOWSTB
	.globl _FLOWHOLDOFF
	.globl _FLOWEQ1CTL
	.globl _FLOWEQ0CTL
	.globl _FLOWLOGIC
	.globl _FLOWSTATE
	.globl _GPIFABORT
	.globl _GPIFREADYSTAT
	.globl _GPIFREADYCFG
	.globl _XGPIFSGLDATLNOX
	.globl _XGPIFSGLDATLX
	.globl _XGPIFSGLDATH
	.globl _EP8GPIFTRIG
	.globl _EP8GPIFPFSTOP
	.globl _EP8GPIFFLGSEL
	.globl _EP6GPIFTRIG
	.globl _EP6GPIFPFSTOP
	.globl _EP6GPIFFLGSEL
	.globl _EP4GPIFTRIG
	.globl _EP4GPIFPFSTOP
	.globl _EP4GPIFFLGSEL
	.globl _EP2GPIFTRIG
	.globl _EP2GPIFPFSTOP
	.globl _EP2GPIFFLGSEL
	.globl _GPIFTCB0
	.globl _GPIFTCB1
	.globl _GPIFTCB2
	.globl _GPIFTCB3
	.globl _GPIFADRL
	.globl _GPIFADRH
	.globl _GPIFCTLCFG
	.globl _GPIFIDLECTL
	.globl _GPIFIDLECS
	.globl _GPIFWFSELECT
	.globl _SETUPDAT
	.globl _SUDPTRCTL
	.globl _SUDPTRL
	.globl _SUDPTRH
	.globl _EP8FIFOBCL
	.globl _EP8FIFOBCH
	.globl _EP6FIFOBCL
	.globl _EP6FIFOBCH
	.globl _EP4FIFOBCL
	.globl _EP4FIFOBCH
	.globl _EP2FIFOBCL
	.globl _EP2FIFOBCH
	.globl _EP8FIFOFLGS
	.globl _EP6FIFOFLGS
	.globl _EP4FIFOFLGS
	.globl _EP2FIFOFLGS
	.globl _EP8CS
	.globl _EP6CS
	.globl _EP4CS
	.globl _EP2CS
	.globl _EP1INCS
	.globl _EP1OUTCS
	.globl _EP0CS
	.globl _EP8BCL
	.globl _EP8BCH
	.globl _EP6BCL
	.globl _EP6BCH
	.globl _EP4BCL
	.globl _EP4BCH
	.globl _EP2BCL
	.globl _EP2BCH
	.globl _EP1INBC
	.globl _EP1OUTBC
	.globl _EP0BCL
	.globl _EP0BCH
	.globl _FNADDR
	.globl _MICROFRAME
	.globl _USBFRAMEL
	.globl _USBFRAMEH
	.globl _TOGCTL
	.globl _WAKEUPCS
	.globl _SUSPEND
	.globl _USBCS
	.globl _XAUTODAT2
	.globl _XAUTODAT1
	.globl _I2CTL
	.globl _I2DAT
	.globl _I2CS
	.globl _PORTECFG
	.globl _PORTCCFG
	.globl _PORTACFG
	.globl _INTSETUP
	.globl _INT4IVEC
	.globl _INT2IVEC
	.globl _CLRERRCNT
	.globl _ERRCNTLIM
	.globl _USBERRIRQ
	.globl _USBERRIE
	.globl _GPIFIRQ
	.globl _GPIFIE
	.globl _EPIRQ
	.globl _EPIE
	.globl _USBIRQ
	.globl _USBIE
	.globl _NAKIRQ
	.globl _NAKIE
	.globl _IBNIRQ
	.globl _IBNIE
	.globl _EP8FIFOIRQ
	.globl _EP8FIFOIE
	.globl _EP6FIFOIRQ
	.globl _EP6FIFOIE
	.globl _EP4FIFOIRQ
	.globl _EP4FIFOIE
	.globl _EP2FIFOIRQ
	.globl _EP2FIFOIE
	.globl _OUTPKTEND
	.globl _INPKTEND
	.globl _EP8ISOINPKTS
	.globl _EP6ISOINPKTS
	.globl _EP4ISOINPKTS
	.globl _EP2ISOINPKTS
	.globl _EP8FIFOPFL
	.globl _EP8FIFOPFH
	.globl _EP6FIFOPFL
	.globl _EP6FIFOPFH
	.globl _EP4FIFOPFL
	.globl _EP4FIFOPFH
	.globl _EP2FIFOPFL
	.globl _EP2FIFOPFH
	.globl _EP8AUTOINLENL
	.globl _EP8AUTOINLENH
	.globl _EP6AUTOINLENL
	.globl _EP6AUTOINLENH
	.globl _EP4AUTOINLENL
	.globl _EP4AUTOINLENH
	.globl _EP2AUTOINLENL
	.globl _EP2AUTOINLENH
	.globl _EP8FIFOCFG
	.globl _EP6FIFOCFG
	.globl _EP4FIFOCFG
	.globl _EP2FIFOCFG
	.globl _EP8CFG
	.globl _EP6CFG
	.globl _EP4CFG
	.globl _EP2CFG
	.globl _EP1INCFG
	.globl _EP1OUTCFG
	.globl _REVCTL
	.globl _REVID
	.globl _FIFOPINPOLAR
	.globl _UART230
	.globl _BPADDRL
	.globl _BPADDRH
	.globl _BREAKPT
	.globl _FIFORESET
	.globl _PINFLAGSCD
	.globl _PINFLAGSAB
	.globl _IFCONFIG
	.globl _CPUCS
	.globl _RES_WAVEDATA_END
	.globl _GPIF_WAVE_DATA
	.globl _read_bytes_msb_PARM_2
	.globl _write_bytes_msb_PARM_2
	.globl _spi_write_PARM_6
	.globl _spi_write_PARM_5
	.globl _spi_write_PARM_4
	.globl _spi_write_PARM_3
	.globl _spi_write_PARM_2
	.globl _spi_read_PARM_6
	.globl _spi_read_PARM_5
	.globl _spi_read_PARM_4
	.globl _spi_read_PARM_3
	.globl _spi_read_PARM_2
	.globl _init_spi
	.globl _spi_read
	.globl _spi_write
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area RSEG    (DATA)
_IOA	=	0x0080
_SP	=	0x0081
_DPL	=	0x0082
_DPH	=	0x0083
_DPL1	=	0x0084
_DPH1	=	0x0085
_DPS	=	0x0086
_PCON	=	0x0087
_TCON	=	0x0088
_TMOD	=	0x0089
_TL0	=	0x008a
_TL1	=	0x008b
_TH0	=	0x008c
_TH1	=	0x008d
_CKCON	=	0x008e
_IOB	=	0x0090
_EXIF	=	0x0091
_MPAGE	=	0x0092
_SCON0	=	0x0098
_SBUF0	=	0x0099
_APTR1H	=	0x009a
_APTR1L	=	0x009b
_AUTODAT1	=	0x009c
_AUTOPTRH2	=	0x009d
_AUTOPTRL2	=	0x009e
_AUTODAT2	=	0x009f
_IOC	=	0x00a0
_INT2CLR	=	0x00a1
_INT4CLR	=	0x00a2
_IE	=	0x00a8
_EP2468STAT	=	0x00aa
_EP24FIFOFLGS	=	0x00ab
_EP68FIFOFLGS	=	0x00ac
_AUTOPTRSETUP	=	0x00af
_IOD	=	0x00b0
_IOE	=	0x00b1
_OEA	=	0x00b2
_OEB	=	0x00b3
_OEC	=	0x00b4
_OED	=	0x00b5
_OEE	=	0x00b6
_IP	=	0x00b8
_EP01STAT	=	0x00ba
_GPIFTRIG	=	0x00bb
_GPIFSGLDATH	=	0x00bd
_GPIFSGLDATLX	=	0x00be
_GPIFSGLDATLNOX	=	0x00bf
_SCON1	=	0x00c0
_SBUF1	=	0x00c1
_T2CON	=	0x00c8
_RCAP2L	=	0x00ca
_RCAP2H	=	0x00cb
_TL2	=	0x00cc
_TH2	=	0x00cd
_PSW	=	0x00d0
_EICON	=	0x00d8
_ACC	=	0x00e0
_EIE	=	0x00e8
_B	=	0x00f0
_EIP	=	0x00f8
;--------------------------------------------------------
; special function bits
;--------------------------------------------------------
	.area RSEG    (DATA)
_SEL	=	0x0086
_IT0	=	0x0088
_IE0	=	0x0089
_IT1	=	0x008a
_IE1	=	0x008b
_TR0	=	0x008c
_TF0	=	0x008d
_TR1	=	0x008e
_TF1	=	0x008f
_RI	=	0x0098
_TI	=	0x0099
_RB8	=	0x009a
_TB8	=	0x009b
_REN	=	0x009c
_SM2	=	0x009d
_SM1	=	0x009e
_SM0	=	0x009f
_EX0	=	0x00a8
_ET0	=	0x00a9
_EX1	=	0x00aa
_ET1	=	0x00ab
_ES0	=	0x00ac
_ET2	=	0x00ad
_ES1	=	0x00ae
_EA	=	0x00af
_PX0	=	0x00b8
_PT0	=	0x00b9
_PX1	=	0x00ba
_PT1	=	0x00bb
_PS0	=	0x00bc
_PT2	=	0x00bd
_PS1	=	0x00be
_RI1	=	0x00c0
_TI1	=	0x00c1
_RB81	=	0x00c2
_TB81	=	0x00c3
_REN1	=	0x00c4
_SM21	=	0x00c5
_SM11	=	0x00c6
_SM01	=	0x00c7
_CP_RL2	=	0x00c8
_C_T2	=	0x00c9
_TR2	=	0x00ca
_EXEN2	=	0x00cb
_TCLK	=	0x00cc
_RCLK	=	0x00cd
_EXF2	=	0x00ce
_TF2	=	0x00cf
_P	=	0x00d0
_FL	=	0x00d1
_OV	=	0x00d2
_RS0	=	0x00d3
_RS1	=	0x00d4
_F0	=	0x00d5
_AC	=	0x00d6
_CY	=	0x00d7
_INT6	=	0x00db
_RESI	=	0x00dc
_ERESI	=	0x00dd
_SMOD1	=	0x00df
_EIUSB	=	0x00e8
_EI2C	=	0x00e9
_EIEX4	=	0x00ea
_EIEX5	=	0x00eb
_EIEX6	=	0x00ec
_PUSB	=	0x00f8
_PI2C	=	0x00f9
_EIPX4	=	0x00fa
_EIPX5	=	0x00fb
_EIPX6	=	0x00fc
_bitS_CLK	=	0x0080
_bitS_OUT	=	0x0081
_bitS_IN	=	0x0082
_bitALTERA_DATA0	=	0x00a1
_bitALTERA_DCLK	=	0x00a3
;--------------------------------------------------------
; overlayable register banks
;--------------------------------------------------------
	.area REG_BANK_0	(REL,OVR,DATA)
	.ds 8
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	.area DSEG    (DATA)
_spi_read_PARM_2:
	.ds 1
_spi_read_PARM_3:
	.ds 1
_spi_read_PARM_4:
	.ds 1
_spi_read_PARM_5:
	.ds 2
_spi_read_PARM_6:
	.ds 1
_spi_write_PARM_2:
	.ds 1
_spi_write_PARM_3:
	.ds 1
_spi_write_PARM_4:
	.ds 1
_spi_write_PARM_5:
	.ds 2
_spi_write_PARM_6:
	.ds 1
_write_bytes_msb_PARM_2:
	.ds 1
_read_bytes_msb_PARM_2:
	.ds 1
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
	.area	OSEG    (OVR,DATA)
	.area	OSEG    (OVR,DATA)
	.area	OSEG    (OVR,DATA)
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
_GPIF_WAVE_DATA	=	0xe400
_RES_WAVEDATA_END	=	0xe480
_CPUCS	=	0xe600
_IFCONFIG	=	0xe601
_PINFLAGSAB	=	0xe602
_PINFLAGSCD	=	0xe603
_FIFORESET	=	0xe604
_BREAKPT	=	0xe605
_BPADDRH	=	0xe606
_BPADDRL	=	0xe607
_UART230	=	0xe608
_FIFOPINPOLAR	=	0xe609
_REVID	=	0xe60a
_REVCTL	=	0xe60b
_EP1OUTCFG	=	0xe610
_EP1INCFG	=	0xe611
_EP2CFG	=	0xe612
_EP4CFG	=	0xe613
_EP6CFG	=	0xe614
_EP8CFG	=	0xe615
_EP2FIFOCFG	=	0xe618
_EP4FIFOCFG	=	0xe619
_EP6FIFOCFG	=	0xe61a
_EP8FIFOCFG	=	0xe61b
_EP2AUTOINLENH	=	0xe620
_EP2AUTOINLENL	=	0xe621
_EP4AUTOINLENH	=	0xe622
_EP4AUTOINLENL	=	0xe623
_EP6AUTOINLENH	=	0xe624
_EP6AUTOINLENL	=	0xe625
_EP8AUTOINLENH	=	0xe626
_EP8AUTOINLENL	=	0xe627
_EP2FIFOPFH	=	0xe630
_EP2FIFOPFL	=	0xe631
_EP4FIFOPFH	=	0xe632
_EP4FIFOPFL	=	0xe633
_EP6FIFOPFH	=	0xe634
_EP6FIFOPFL	=	0xe635
_EP8FIFOPFH	=	0xe636
_EP8FIFOPFL	=	0xe637
_EP2ISOINPKTS	=	0xe640
_EP4ISOINPKTS	=	0xe641
_EP6ISOINPKTS	=	0xe642
_EP8ISOINPKTS	=	0xe643
_INPKTEND	=	0xe648
_OUTPKTEND	=	0xe649
_EP2FIFOIE	=	0xe650
_EP2FIFOIRQ	=	0xe651
_EP4FIFOIE	=	0xe652
_EP4FIFOIRQ	=	0xe653
_EP6FIFOIE	=	0xe654
_EP6FIFOIRQ	=	0xe655
_EP8FIFOIE	=	0xe656
_EP8FIFOIRQ	=	0xe657
_IBNIE	=	0xe658
_IBNIRQ	=	0xe659
_NAKIE	=	0xe65a
_NAKIRQ	=	0xe65b
_USBIE	=	0xe65c
_USBIRQ	=	0xe65d
_EPIE	=	0xe65e
_EPIRQ	=	0xe65f
_GPIFIE	=	0xe660
_GPIFIRQ	=	0xe661
_USBERRIE	=	0xe662
_USBERRIRQ	=	0xe663
_ERRCNTLIM	=	0xe664
_CLRERRCNT	=	0xe665
_INT2IVEC	=	0xe666
_INT4IVEC	=	0xe667
_INTSETUP	=	0xe668
_PORTACFG	=	0xe670
_PORTCCFG	=	0xe671
_PORTECFG	=	0xe672
_I2CS	=	0xe678
_I2DAT	=	0xe679
_I2CTL	=	0xe67a
_XAUTODAT1	=	0xe67b
_XAUTODAT2	=	0xe67c
_USBCS	=	0xe680
_SUSPEND	=	0xe681
_WAKEUPCS	=	0xe682
_TOGCTL	=	0xe683
_USBFRAMEH	=	0xe684
_USBFRAMEL	=	0xe685
_MICROFRAME	=	0xe686
_FNADDR	=	0xe687
_EP0BCH	=	0xe68a
_EP0BCL	=	0xe68b
_EP1OUTBC	=	0xe68d
_EP1INBC	=	0xe68f
_EP2BCH	=	0xe690
_EP2BCL	=	0xe691
_EP4BCH	=	0xe694
_EP4BCL	=	0xe695
_EP6BCH	=	0xe698
_EP6BCL	=	0xe699
_EP8BCH	=	0xe69c
_EP8BCL	=	0xe69d
_EP0CS	=	0xe6a0
_EP1OUTCS	=	0xe6a1
_EP1INCS	=	0xe6a2
_EP2CS	=	0xe6a3
_EP4CS	=	0xe6a4
_EP6CS	=	0xe6a5
_EP8CS	=	0xe6a6
_EP2FIFOFLGS	=	0xe6a7
_EP4FIFOFLGS	=	0xe6a8
_EP6FIFOFLGS	=	0xe6a9
_EP8FIFOFLGS	=	0xe6aa
_EP2FIFOBCH	=	0xe6ab
_EP2FIFOBCL	=	0xe6ac
_EP4FIFOBCH	=	0xe6ad
_EP4FIFOBCL	=	0xe6ae
_EP6FIFOBCH	=	0xe6af
_EP6FIFOBCL	=	0xe6b0
_EP8FIFOBCH	=	0xe6b1
_EP8FIFOBCL	=	0xe6b2
_SUDPTRH	=	0xe6b3
_SUDPTRL	=	0xe6b4
_SUDPTRCTL	=	0xe6b5
_SETUPDAT	=	0xe6b8
_GPIFWFSELECT	=	0xe6c0
_GPIFIDLECS	=	0xe6c1
_GPIFIDLECTL	=	0xe6c2
_GPIFCTLCFG	=	0xe6c3
_GPIFADRH	=	0xe6c4
_GPIFADRL	=	0xe6c5
_GPIFTCB3	=	0xe6ce
_GPIFTCB2	=	0xe6cf
_GPIFTCB1	=	0xe6d0
_GPIFTCB0	=	0xe6d1
_EP2GPIFFLGSEL	=	0xe6d2
_EP2GPIFPFSTOP	=	0xe6d3
_EP2GPIFTRIG	=	0xe6d4
_EP4GPIFFLGSEL	=	0xe6da
_EP4GPIFPFSTOP	=	0xe6db
_EP4GPIFTRIG	=	0xe6dc
_EP6GPIFFLGSEL	=	0xe6e2
_EP6GPIFPFSTOP	=	0xe6e3
_EP6GPIFTRIG	=	0xe6e4
_EP8GPIFFLGSEL	=	0xe6ea
_EP8GPIFPFSTOP	=	0xe6eb
_EP8GPIFTRIG	=	0xe6ec
_XGPIFSGLDATH	=	0xe6f0
_XGPIFSGLDATLX	=	0xe6f1
_XGPIFSGLDATLNOX	=	0xe6f2
_GPIFREADYCFG	=	0xe6f3
_GPIFREADYSTAT	=	0xe6f4
_GPIFABORT	=	0xe6f5
_FLOWSTATE	=	0xe6c6
_FLOWLOGIC	=	0xe6c7
_FLOWEQ0CTL	=	0xe6c8
_FLOWEQ1CTL	=	0xe6c9
_FLOWHOLDOFF	=	0xe6ca
_FLOWSTB	=	0xe6cb
_FLOWSTBEDGE	=	0xe6cc
_FLOWSTBHPERIOD	=	0xe6cd
_GPIFHOLDAMOUNT	=	0xe60c
_UDMACRCH	=	0xe67d
_UDMACRCL	=	0xe67e
_UDMACRCQUAL	=	0xe67f
_DBUG	=	0xe6f8
_TESTCFG	=	0xe6f9
_USBTEST	=	0xe6fa
_CT1	=	0xe6fb
_CT2	=	0xe6fc
_CT3	=	0xe6fd
_CT4	=	0xe6fe
_EP0BUF	=	0xe740
_EP1OUTBUF	=	0xe780
_EP1INBUF	=	0xe7c0
_EP2FIFOBUF	=	0xf000
_EP4FIFOBUF	=	0xf400
_EP6FIFOBUF	=	0xf800
_EP8FIFOBUF	=	0xfc00
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
;------------------------------------------------------------
;Allocation info for local variables in function 'setup_enables'
;------------------------------------------------------------
;enables                   Allocated to registers r2 
;------------------------------------------------------------
;	spi.c:27: setup_enables (unsigned char enables)
;	-----------------------------------------
;	 function setup_enables
;	-----------------------------------------
_setup_enables:
	ar2 = 0x02
	ar3 = 0x03
	ar4 = 0x04
	ar5 = 0x05
	ar6 = 0x06
	ar7 = 0x07
	ar0 = 0x00
	ar1 = 0x01
	mov	r2,dpl
;	spi.c:33: enables ^= SPI_ENABLE_FPGA;
	xrl	ar2,#0x01
;	spi.c:37: USRP_PA = USRP_PA | (0x7 << 3);	// disable FPGA, CODEC_A, CODEC_B
	orl	_IOA,#0x38
;	spi.c:38: USRP_PA ^= (enables & 0x7) << 3;	// enable specified devs
	mov	a,#0x07
	anl	a,r2
	swap	a
	rr	a
	anl	a,#0xf8
	xrl	_IOA,a
;	spi.c:41: USRP_PE = USRP_PE | (0xf << 4);	// disable TX_A, RX_A, TX_B, RX_B
	orl	_IOE,#0xF0
;	spi.c:42: USRP_PE ^= (enables & 0xf0);		// enable specified devs
	mov	a,#0xF0
	anl	a,r2
	xrl	_IOE,a
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'init_spi'
;------------------------------------------------------------
;------------------------------------------------------------
;	spi.c:48: init_spi (void)
;	-----------------------------------------
;	 function init_spi
;	-----------------------------------------
_init_spi:
;	spi.c:50: disable_all ();		/* disable all devs	  */
	mov	dpl,#0x00
	lcall	_setup_enables
;	spi.c:51: bitS_OUT = 0;			/* idle state has CLK = 0 */
	clr	_bitS_OUT
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'count_bits8'
;------------------------------------------------------------
;v                         Allocated to registers r2 
;count                     Allocated to registers r3 
;------------------------------------------------------------
;	spi.c:82: count_bits8 (unsigned char v)
;	-----------------------------------------
;	 function count_bits8
;	-----------------------------------------
_count_bits8:
	mov	r2,dpl
;	spi.c:84: unsigned char count = 0;
	mov	r3,#0x00
;	spi.c:85: if (v & (1 << 0)) count++;
	mov	a,r2
	jnb	acc.0,00102$
	mov	r3,#0x01
00102$:
;	spi.c:86: if (v & (1 << 1)) count++;
	mov	a,r2
	jnb	acc.1,00104$
	inc	r3
00104$:
;	spi.c:87: if (v & (1 << 2)) count++;
	mov	a,r2
	jnb	acc.2,00106$
	inc	r3
00106$:
;	spi.c:88: if (v & (1 << 3)) count++;
	mov	a,r2
	jnb	acc.3,00108$
	inc	r3
00108$:
;	spi.c:89: if (v & (1 << 4)) count++;
	mov	a,r2
	jnb	acc.4,00110$
	inc	r3
00110$:
;	spi.c:90: if (v & (1 << 5)) count++;
	mov	a,r2
	jnb	acc.5,00112$
	inc	r3
00112$:
;	spi.c:91: if (v & (1 << 6)) count++;
	mov	a,r2
	jnb	acc.6,00114$
	inc	r3
00114$:
;	spi.c:92: if (v & (1 << 7)) count++;
	mov	a,r2
	jnb	acc.7,00116$
	inc	r3
00116$:
;	spi.c:93: return count;
	mov	dpl,r3
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'spi_read'
;------------------------------------------------------------
;header_lo                 Allocated with name '_spi_read_PARM_2'
;enables                   Allocated with name '_spi_read_PARM_3'
;format                    Allocated with name '_spi_read_PARM_4'
;buf                       Allocated with name '_spi_read_PARM_5'
;len                       Allocated with name '_spi_read_PARM_6'
;header_hi                 Allocated to registers r2 
;------------------------------------------------------------
;	spi.c:109: spi_read (unsigned char header_hi, unsigned char header_lo,
;	-----------------------------------------
;	 function spi_read
;	-----------------------------------------
_spi_read:
	mov	r2,dpl
;	spi.c:113: if (count_bits8 (enables) > 1)
	mov	dpl,_spi_read_PARM_3
	push	ar2
	lcall	_count_bits8
	mov	r3,dpl
	pop	ar2
	mov	a,r3
	add	a,#0xff - 0x01
	jnc	00102$
;	spi.c:114: return 0;		// error, too many enables set
	mov	dpl,#0x00
	ret
00102$:
;	spi.c:116: setup_enables (enables);
	mov	dpl,_spi_read_PARM_3
	push	ar2
	lcall	_setup_enables
	pop	ar2
;	spi.c:118: if (format & SPI_FMT_LSB){		// order: LSB
	mov	a,_spi_read_PARM_4
	jnb	acc.7,00111$
;	spi.c:120: return 0;		// error, not implemented
	mov	dpl,#0x00
	ret
00111$:
;	spi.c:142: switch (format & SPI_FMT_HDR_MASK){
	mov	a,#0x60
	anl	a,_spi_read_PARM_4
	mov	r3,a
	jz	00107$
	cjne	r3,#0x20,00124$
	sjmp	00104$
00124$:
;	spi.c:145: case SPI_FMT_HDR_1:
	cjne	r3,#0x40,00106$
	sjmp	00105$
00104$:
;	spi.c:146: write_byte_msb (header_lo);
	mov	dpl,_spi_read_PARM_2
	lcall	_write_byte_msb
;	spi.c:147: break;
;	spi.c:148: case SPI_FMT_HDR_2:
	sjmp	00107$
00105$:
;	spi.c:149: write_byte_msb (header_hi);
	mov	dpl,r2
	lcall	_write_byte_msb
;	spi.c:150: write_byte_msb (header_lo);
	mov	dpl,_spi_read_PARM_2
	lcall	_write_byte_msb
;	spi.c:151: break;
;	spi.c:152: default:
	sjmp	00107$
00106$:
;	spi.c:153: return 0;		// error
	mov	dpl,#0x00
;	spi.c:154: }
	ret
00107$:
;	spi.c:155: if (len != 0)
	mov	a,_spi_read_PARM_6
	jz	00112$
;	spi.c:156: read_bytes_msb (buf, len);
	mov	_read_bytes_msb_PARM_2,_spi_read_PARM_6
	mov	dpl,_spi_read_PARM_5
	mov	dph,(_spi_read_PARM_5 + 1)
	lcall	_read_bytes_msb
00112$:
;	spi.c:159: disable_all ();
	mov	dpl,#0x00
	lcall	_setup_enables
;	spi.c:160: return 1;		// success
	mov	dpl,#0x01
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'spi_write'
;------------------------------------------------------------
;header_lo                 Allocated with name '_spi_write_PARM_2'
;enables                   Allocated with name '_spi_write_PARM_3'
;format                    Allocated with name '_spi_write_PARM_4'
;buf                       Allocated with name '_spi_write_PARM_5'
;len                       Allocated with name '_spi_write_PARM_6'
;header_hi                 Allocated to registers r2 
;------------------------------------------------------------
;	spi.c:166: spi_write (unsigned char header_hi, unsigned char header_lo,
;	-----------------------------------------
;	 function spi_write
;	-----------------------------------------
_spi_write:
	mov	r2,dpl
;	spi.c:170: setup_enables (enables);
	mov	dpl,_spi_write_PARM_3
	push	ar2
	lcall	_setup_enables
	pop	ar2
;	spi.c:172: if (format & SPI_FMT_LSB){		// order: LSB
	mov	a,_spi_write_PARM_4
	jnb	acc.7,00109$
;	spi.c:174: return 0;		// error, not implemented
	mov	dpl,#0x00
	ret
00109$:
;	spi.c:196: switch (format & SPI_FMT_HDR_MASK){
	mov	a,#0x60
	anl	a,_spi_write_PARM_4
	mov	r3,a
	jz	00105$
	cjne	r3,#0x20,00120$
	sjmp	00102$
00120$:
;	spi.c:199: case SPI_FMT_HDR_1:
	cjne	r3,#0x40,00104$
	sjmp	00103$
00102$:
;	spi.c:200: write_byte_msb (header_lo);
	mov	dpl,_spi_write_PARM_2
	lcall	_write_byte_msb
;	spi.c:201: break;
;	spi.c:202: case SPI_FMT_HDR_2:
	sjmp	00105$
00103$:
;	spi.c:203: write_byte_msb (header_hi);
	mov	dpl,r2
	lcall	_write_byte_msb
;	spi.c:204: write_byte_msb (header_lo);
	mov	dpl,_spi_write_PARM_2
	lcall	_write_byte_msb
;	spi.c:205: break;
;	spi.c:206: default:
	sjmp	00105$
00104$:
;	spi.c:207: return 0;		// error
	mov	dpl,#0x00
;	spi.c:208: }
	ret
00105$:
;	spi.c:209: if (len != 0)
	mov	a,_spi_write_PARM_6
	jz	00110$
;	spi.c:210: write_bytes_msb (buf, len);
	mov	_write_bytes_msb_PARM_2,_spi_write_PARM_6
	mov	dpl,_spi_write_PARM_5
	mov	dph,(_spi_write_PARM_5 + 1)
	lcall	_write_bytes_msb
00110$:
;	spi.c:213: disable_all ();
	mov	dpl,#0x00
	lcall	_setup_enables
;	spi.c:214: return 1;		// success
	mov	dpl,#0x01
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'write_byte_msb'
;------------------------------------------------------------
;v                         Allocated to registers r2 
;------------------------------------------------------------
;	spi.c:220: write_byte_msb (unsigned char v)
;	-----------------------------------------
;	 function write_byte_msb
;	-----------------------------------------
_write_byte_msb:
;	spi.c:222: v = (v << 1) | (v >> 7);	// rotate left (MSB into bottom bit)
	mov	a,dpl
	rl	a
;	spi.c:223: bitS_OUT = v & 0x1;
	mov	r2,a
	rrc	a
	mov	_bitS_OUT,c
;	spi.c:224: bitS_CLK = 1;
	setb	_bitS_CLK
;	spi.c:225: bitS_CLK = 0;
	clr	_bitS_CLK
;	spi.c:227: v = (v << 1) | (v >> 7);	// rotate left (MSB into bottom bit)
	mov	a,r2
	rl	a
;	spi.c:228: bitS_OUT = v & 0x1;
	mov	r2,a
	rrc	a
	mov	_bitS_OUT,c
;	spi.c:229: bitS_CLK = 1;
	setb	_bitS_CLK
;	spi.c:230: bitS_CLK = 0;
	clr	_bitS_CLK
;	spi.c:232: v = (v << 1) | (v >> 7);	// rotate left (MSB into bottom bit)
	mov	a,r2
	rl	a
;	spi.c:233: bitS_OUT = v & 0x1;
	mov	r2,a
	rrc	a
	mov	_bitS_OUT,c
;	spi.c:234: bitS_CLK = 1;
	setb	_bitS_CLK
;	spi.c:235: bitS_CLK = 0;
	clr	_bitS_CLK
;	spi.c:237: v = (v << 1) | (v >> 7);	// rotate left (MSB into bottom bit)
	mov	a,r2
	rl	a
;	spi.c:238: bitS_OUT = v & 0x1;
	mov	r2,a
	rrc	a
	mov	_bitS_OUT,c
;	spi.c:239: bitS_CLK = 1;
	setb	_bitS_CLK
;	spi.c:240: bitS_CLK = 0;
	clr	_bitS_CLK
;	spi.c:242: v = (v << 1) | (v >> 7);	// rotate left (MSB into bottom bit)
	mov	a,r2
	rl	a
;	spi.c:243: bitS_OUT = v & 0x1;
	mov	r2,a
	rrc	a
	mov	_bitS_OUT,c
;	spi.c:244: bitS_CLK = 1;
	setb	_bitS_CLK
;	spi.c:245: bitS_CLK = 0;
	clr	_bitS_CLK
;	spi.c:247: v = (v << 1) | (v >> 7);	// rotate left (MSB into bottom bit)
	mov	a,r2
	rl	a
;	spi.c:248: bitS_OUT = v & 0x1;
	mov	r2,a
	rrc	a
	mov	_bitS_OUT,c
;	spi.c:249: bitS_CLK = 1;
	setb	_bitS_CLK
;	spi.c:250: bitS_CLK = 0;
	clr	_bitS_CLK
;	spi.c:252: v = (v << 1) | (v >> 7);	// rotate left (MSB into bottom bit)
	mov	a,r2
	rl	a
;	spi.c:253: bitS_OUT = v & 0x1;
	mov	r2,a
	rrc	a
	mov	_bitS_OUT,c
;	spi.c:254: bitS_CLK = 1;
	setb	_bitS_CLK
;	spi.c:255: bitS_CLK = 0;
	clr	_bitS_CLK
;	spi.c:257: v = (v << 1) | (v >> 7);	// rotate left (MSB into bottom bit)
	mov	a,r2
	rl	a
;	spi.c:258: bitS_OUT = v & 0x1;
	rrc	a
	mov	_bitS_OUT,c
;	spi.c:259: bitS_CLK = 1;
	setb	_bitS_CLK
;	spi.c:260: bitS_CLK = 0;
	clr	_bitS_CLK
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'write_bytes_msb'
;------------------------------------------------------------
;len                       Allocated with name '_write_bytes_msb_PARM_2'
;buf                       Allocated to registers r2 r3 
;------------------------------------------------------------
;	spi.c:264: write_bytes_msb (const xdata unsigned char *buf, unsigned char len)
;	-----------------------------------------
;	 function write_bytes_msb
;	-----------------------------------------
_write_bytes_msb:
	mov	r2,dpl
	mov	r3,dph
;	spi.c:266: while (len-- != 0){
	mov	r4,_write_bytes_msb_PARM_2
00101$:
	mov	ar5,r4
	dec	r4
	mov	a,r5
	jz	00104$
;	spi.c:267: write_byte_msb (*buf++);
	mov	dpl,r2
	mov	dph,r3
	movx	a,@dptr
	mov	r5,a
	inc	dptr
	mov	r2,dpl
	mov	r3,dph
	mov	dpl,r5
	push	ar2
	push	ar3
	push	ar4
	lcall	_write_byte_msb
	pop	ar4
	pop	ar3
	pop	ar2
	sjmp	00101$
00104$:
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'read_byte_msb'
;------------------------------------------------------------
;------------------------------------------------------------
;	spi.c:323: read_byte_msb (void) _naked
;	-----------------------------------------
;	 function read_byte_msb
;	-----------------------------------------
_read_byte_msb:
;	naked function: no prologue.
;	spi.c:370: _endasm;
	
	 clr a
	
	 setb _bitS_CLK
	        mov c, _bitS_IN
	 rlc a
	 clr _bitS_CLK
	
	 setb _bitS_CLK
	        mov c, _bitS_IN
	 rlc a
	 clr _bitS_CLK
	
	 setb _bitS_CLK
	        mov c, _bitS_IN
	 rlc a
	 clr _bitS_CLK
	
	 setb _bitS_CLK
	        mov c, _bitS_IN
	 rlc a
	 clr _bitS_CLK
	
	 setb _bitS_CLK
	        mov c, _bitS_IN
	 rlc a
	 clr _bitS_CLK
	
	 setb _bitS_CLK
	        mov c, _bitS_IN
	 rlc a
	 clr _bitS_CLK
	
	 setb _bitS_CLK
	        mov c, _bitS_IN
	 rlc a
	 clr _bitS_CLK
	
	 setb _bitS_CLK
	        mov c, _bitS_IN
	 rlc a
	 clr _bitS_CLK
	
	 mov dpl,a
	 ret
	  
;	naked function: no epilogue.
;------------------------------------------------------------
;Allocation info for local variables in function 'read_bytes_msb'
;------------------------------------------------------------
;len                       Allocated with name '_read_bytes_msb_PARM_2'
;buf                       Allocated to registers r2 r3 
;------------------------------------------------------------
;	spi.c:375: read_bytes_msb (xdata unsigned char *buf, unsigned char len)
;	-----------------------------------------
;	 function read_bytes_msb
;	-----------------------------------------
_read_bytes_msb:
	mov	r2,dpl
	mov	r3,dph
;	spi.c:377: while (len-- != 0){
	mov	r4,_read_bytes_msb_PARM_2
00101$:
	mov	ar5,r4
	dec	r4
	mov	a,r5
	jz	00104$
;	spi.c:378: *buf++ = read_byte_msb ();
	lcall	_read_byte_msb
	mov	r5,dpl
	mov	dpl,r2
	mov	dph,r3
	mov	a,r5
	movx	@dptr,a
	inc	dptr
	mov	r2,dpl
	mov	r3,dph
	sjmp	00101$
00104$:
	ret
	.area CSEG    (CODE)
	.area CONST   (CODE)
	.area CABS    (ABS,CODE)


; https://groups.google.com/forum/#!topic/comp.sys.apple2/usZKHLQi-Ak

	;.smart          on
        .autoimport     on
        .import __STARTUP_LOAD__
	.export _putchar
	.export _printb
	;.export _irq
	.export _initSIDTune
	.export _initVicilib

	.segment "VECTORS"

	jmp __STARTUP_LOAD__    ; B000 : jump to Vicious menu
	;jmp 



	.code
_putchar:
	jsr $ffef   ; wozmon ECHO
	rts

_printb:
	jsr $ffdc   ; wozmon PRBYTE
	rts


_initVicilib:
	jsr zerobss
	jsr copydata  ; copies data segment from ROM to RAM
	rts


; void __fastcall__ initSIDTune(word initAddress, word playAddress);
_initSIDTune:
	;sta playAddr+1
	;stx playAddr+2
	sta $7f01
	stx $7f02
	jsr popax
	;sta initAddr+1
	;stx initAddr+2
	sta $7f04
	stx $7f05
	lda #$4c   ;jmp
	sta $7f00
	sta $7f03 
	lda #$0   ; song select here?
	tax
	tay
initAddr:
	;jsr $0000   ; call sid tune init address, modified code
	jsr $7f03

	; setup jump from irq address 0000 to _irq handler here
	lda #$4c     ; jmp
	sta $0000
	lda #<_irq
	sta $0001
	lda #>_irq
	sta $0002
	rts



; SID Tune play irq which calls tune's play routine
_irq:
	pha
	txa
	pha
	tya
	pha
playAddr:
	;jsr $0000 ; call sid tune play address, modified code
	jsr $7f00	

	lda $bf8d  ; clear CIA irq condition

	pla
	tay
	pla
	tax
	pla
	rti






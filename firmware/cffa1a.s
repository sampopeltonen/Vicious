
	.export _gotoCFFA1
	.export _callCFFA1API


	.include "CFFA1_API.s"

	.segment "CODERAMSTART"

	jmp	quick_note
header_text:
	.byte $d, "VICIOUS CFFA1 MODULE", $d, $0
quick_note:
	clc
	ldx	#0
loop:	lda	header_text, x
	beq	quit
	jsr	$ffef
	inx
	jmp loop
quit:
	rts


	.code

_gotoCFFA1:
	jsr $9006
	rts

_callCFFA1API:
	tax
	jsr CFFA1_API
	rts

	.export _putchar
	.export _printb

	.code
_putchar:
	jsr $ffef   ; wozmon ECHO
	rts

_printb:
	jsr $ffdc   ; wozmon PRBYTE
	rts


	;.segment "END"
	;.byte "ROM IMAGE START"
	



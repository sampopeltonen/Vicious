
	.export _gotoCFFA1
	.export _callCFFA1API


	.include "CFFA1_API.s"


_gotoCFFA1:
	jsr $9006
	rts

_callCFFA1API:
	tax
	jsr CFFA1_API
	rts

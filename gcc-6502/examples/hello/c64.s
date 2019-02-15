.segment "LOADADDR"
.word $0801
.segment "EXEHDR"
.word line2, 0
.byte $9e ; "SYS"
.byte <('0' + $080d .mod 10000 / 1000)
.byte <('0' + $080d .mod 1000 / 100)
.byte <('0' + $080d .mod 100 / 10)
.byte <('0' + $080d .mod 10)
.byte $00 ; end of line
line2:
.byte $00, $00 ; end of basic


CFLAGS =
CC = sdcc
INCLUDES =
LIBS = -lstm8 -mstm8

all: thermo.hex

thermo.hex: thermo.rel display.rel
	${CC} ${CFLAGS} ${LIBS} ${INCLUDES} --out-fmt-ihx -o $@ $^

%.rel: %.c
	${CC} ${CFLAGS} ${LIBS} ${INCLUDES} -c $<

flash: thermo.hex
	stm8flash -c stlinkv2 -p stm8l152c6 -w $<

clean:
	rm *.hex *.sym *.rst *.rel *.mem *.map *.lst *.lk *.cdb *.asm

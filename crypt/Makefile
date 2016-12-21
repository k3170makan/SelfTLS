SOURCE=des
GCC=gcc
OPTS=-O2
all:
	${GCC} ${SOURCE}.c ${OPTS} -o ${SOURCE}
	cp ${SOURCE}.c ${SOURCE}.bk
debug:
	${GCC} ${SOURCE}.c -g -D DEBUG ${OPTS} -o ${SOURCE}_debug
clean:
	-rm ${SOURCE}
	-rm ${SOURCE}_debug
	-rm -rf *.dSYM
test:
	./${SOURCE}_debug

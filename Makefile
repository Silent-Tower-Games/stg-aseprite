.PHONY=application
application:
	make lib
	make objs
	${CC} ${CFLAGS} src/test.o -o main -L`pwd` ${LIBS} -lstgaseprite -ljson-c -static-libgcc -lm -Wl,-rpath=./

.PHONY=application-static
application-static:
	make lib-static
	make objs
	${CC} ${CFLAGS} src/test.o libstgaseprite.a -o main

.PHONY=lib
lib:
	make objs-lib
	${CC} ${CFLAGS} src/STGAseprite/STGAseprite.o -shared -o libstgaseprite.${EXT} ${LIBS}

.PHONY=lib-static
lib-static:
	make objs-lib
	ar rcs libstgaseprite.a src/STGAseprite/STGAseprite.o

.PHONY=objs
objs:
	${CC} ${CFLAGS} -c src/test.c -o src/test.o ${INCS}

.PHONY=objs-lib
objs-lib:
	${CC} ${CFLAGS} -c src/STGAseprite/STGAseprite.c -o src/STGAseprite/STGAseprite.o ${INCS} -fPIC

.PHONY=clean
clean:
	rm -f src/*.o src/**/*.o ./main ./*.so ./*.dll ./*.a

.PHONY=valgrind
valgrind:
	valgrind --leak-check=full ./main 2> valgrind.txt

.PHONY=apitrace
apitrace:
	apitrace trace ./main
	qapitrace main.trace
	rm main.trace

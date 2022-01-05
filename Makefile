CC=gcc
CFLAGS=-pedantic -O3
INCLUDE_PATHS=
LIBRARY_PATHS=
SDL2=`sdl2-config --libs`

.PHONY=application
application:
	make lib
	make objs
	${CC} ${CFLAGS} src/test.o -o main ${SDL2} -L`pwd` ${LIBRARY_PATHS} -lstgaseprite -ljson-c -lm -Wl,-rpath=./

.PHONY=application-static
application-static:
	make lib-static
	make objs
	${CC} ${CFLAGS} src/test.o libstgaseprite.a -o main ${SDL2}

.PHONY=lib
lib:
	make objs-lib
	${CC} ${CFLAGS} src/STGAseprite/STGAseprite.o -shared -o libstgaseprite.so ${SDL2}

.PHONY=lib-static
lib-static:
	make objs-lib
	ar rcs libstgaseprite.a src/STGAseprite/STGAseprite.o

.PHONY=objs
objs:
	${CC} ${CFLAGS} -c src/test.c -o src/test.o ${INCLUDE_PATHS}

.PHONY=objs-lib
objs-lib:
	${CC} ${CFLAGS} -c src/STGAseprite/STGAseprite.c -o src/STGAseprite/STGAseprite.o ${INCLUDE_PATHS} -fPIC

.PHONY=clean
clean:
	rm -f src/*.o src/**/*.o ./main ./*.so ./*.a

.PHONY=valgrind
valgrind:
	valgrind ./main --leak-check=full 2> valgrind.txt

.PHONY=apitrace
apitrace:
	apitrace trace ./main
	qapitrace main.trace
	rm main.trace

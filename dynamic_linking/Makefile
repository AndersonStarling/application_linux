
build:
	mkdir -p ./output
	gcc -c dynamic_linking.c

clean:
	rm ./output/*

build_lib:
	gcc -c -fPIC libsum.c
	gcc -shared -o libsum.so libsum.o

build_app:
	gcc -o main_dynamic dynamic_linking.o -L./ -lsum


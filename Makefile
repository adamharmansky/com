all:
	cc com.c -lraylib -o com
run: all
	./com

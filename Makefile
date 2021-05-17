all:
	cc com.c -lraylib -ldl -lpthread -lm -o com
run: all
	./com

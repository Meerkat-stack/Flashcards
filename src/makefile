SHELL = /bin/sh
CC = gcc
LD = gcc

../bin/main: 	../obj/main.o ../obj/args.o ../obj/words.o ../obj/quiz.o
	$(LD) ../obj/main.o ../obj/words.o ../obj/args.o ../obj/quiz.o -o ../bin/flashcards

../obj/main.o:	main.c
	$(CC) -c main.c -o ../obj/main.o

../obj/args.o:	args.c
	$(CC) -c args.c -o ../obj/args.o

../obj/words.o:	words.c
	$(CC) -c words.c -o ../obj/words.o

../obj/quiz.o:	quiz.c
	$(CC) -c quiz.c -o ../obj/quiz.o

clean:
	rm -f ../obj/*.o

debug: main.c args.c words.c quiz.c
	$(CC) -g main.c args.c words.c quiz.c -o ../bin/flashcards_debug

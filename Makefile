all:
	gcc main.c board.c logic.c -o twixt

clean:
	rm -f twixt

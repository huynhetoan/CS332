FILE = bonusHW
#file name^

build: $(FILE).c
	gcc -Wall -g $(FILE).c -o $(FILE) 


.PHONY: db

db:
	gdb -tui $(FILE)

run:
	./$(FILE)
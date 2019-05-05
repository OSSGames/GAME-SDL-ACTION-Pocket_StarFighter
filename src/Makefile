# Here are the options:

INSTALL_PATH = /usr/games
MAN_PATH = /usr/share/man/cat6
CC = gcc
CFLAGS = -Wall -ansi -pedantic --std=c89 -O3 -I /usr/include
LDFLAGS = -lSDL -lSDLmain -lSDL_mixer

# Here's the stuff you shouldn't have to monkey with:

MAN = man/pocketstar.6
SRC = ai.c geometry.c letters.c main.c sdl.c ships.c world.c
BIN = pocketstar

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(BIN)


clean:
	rm -f $(BIN)

install:
	cp $(BIN) $(INSTALL_PATH)
	cp $(MAN) $(MAN_PATH)

backup:
	sh backup.sh

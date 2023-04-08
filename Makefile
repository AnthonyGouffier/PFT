CC = gcc
CFLAGS = -Iinclude
LDFLAGS = -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

SRC_FILES = ./src/main.c ./src/database.c ./src/carteV1.c ./src/fonction_SDL.c
OBJ_FILES = $(SRC_FILES:.c=.o)
EXECUTABLE = ./bin/prog.exe

# Détermination du système d'exploitation
ifeq ($(OS), Windows_NT)
	RM = del /Q /F
else
	RM = rm -f
endif

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(EXECUTABLE) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_FILES) $(EXECUTABLE)
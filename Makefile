ifeq ($(OS),Windows_NT)
    # Compilation pour Windows
    CC = gcc
    CFLAGS = -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
    EXECUTABLE = bin/prog.exe
else
    # Compilation pour Linux
    CC = gcc
    CFLAGS = `sdl2-config --cflags`
    LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf
    EXECUTABLE = bin/prog
endif

SRC_DIR = src
BIN_DIR = bin

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRC_FILES))

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(BIN_DIR)/*.o $(EXECUTABLE)
	del /Q /S $(BIN_DIR)\*.o $(EXECUTABLE)

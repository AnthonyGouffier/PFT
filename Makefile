ifeq ($(OS),Windows_NT)
    # Compilation pour Windows
    CC = gcc -g
    CFLAGS = -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
    EXECUTABLE = bin/PFT.exe
else
    # Compilation pour Linux
    CC = gcc -g
    CFLAGS = `sdl2-config --cflags`
    LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lm
    EXECUTABLE = bin/PFT
endif

SRC_DIR = src
BIN_DIR = bin

SRC_FILES = $(wildcard $(SRC_DIR)/database.c $(SRC_DIR)/joueur.c $(SRC_DIR)/boutique.c  $(SRC_DIR)/carteV1.c $(SRC_DIR)/fonction.c $(SRC_DIR)/main.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRC_FILES))

all: $(EXECUTABLE)
	@echo "Vous pouvez maintenant executer $(EXECUTABLE)"

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm $(BIN_DIR)/*.o $(EXECUTABLE)
	del /Q /S $(BIN_DIR)\*.o $(EXECUTABLE)

doc:
	doxygen Doxyfile

.PHONY: all clean doc

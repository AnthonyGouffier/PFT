TARGET=pkm-tactics
TARGET_TEST=

ifeq ($(OS), Windows_NT)

LIB_DIR=lib/windows
INC_DIR=include/windows
LIB_TARGET=SDL2.dll SDL2_ttf.dll SDL2_image.dll
LIB_TARGET_DIR=dll

LFLAGS=-Wall -L$(LIB_DIR) -lmingw32 -lws2_32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

EXE_EXT=.exe
PATH_SEP=\\

RM=del /q /f
RM_DIR=rmdir /q /s
CP=copy


OS_DEF=_WINDOWS_
else
CPU_COUNT=$(grep -c processor /proc/cpuinfo)

LIB_DIR=lib
INC_DIR=include/lin
LIB_TARGET=libSDL2-2.0.so.0 libSDL2_ttf-2.0.so.0 libSDL2_image-2.0.so.0

LIB_TARGET_DIR=$(LIB_DIR)

LFLAGS=-Wall -L $(LIB_DIR) -Wl,-rpath $(LIB_DIR) -Wl,-rpath ./  -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

EXE_EXT=.out
PATH_SEP=/

RM=rm -f
RM_DIR=rm -rf
CP=cp

OS_DEF=_LINUX_
endif

CC=gcc
CFLAGS=-g -Wall -I$(INC_DIR)

SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin
TEST_DIR=test

TRGS:=$(TARGET:%=$(BIN_DIR)/%)
TRGS_TEST:=$(TARGET_TEST:%=$(BIN_DIR)/%)

SOURCES:=$(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
SOURCES_TEST:=$(wildcard $(TEST_DIR)/*.c)

OBJECTS:=$(addprefix $(OBJ_DIR)/,$(subst /,___,$(SOURCES:$(SRC_DIR)/%.c=%.o)))
OBJECTS_TEST:=$(SOURCES_TEST:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)

MAINS:=$(TARGET:%=$(OBJ_DIR)/%.o)
TEST:=$(TARGET_TEST:%=$(OBJ_DIR)/%.o)

OBJS:=$(filter-out $(MAINS), $(OBJECTS))

#all: install_sdl test build

build: $(TRGS) copy_lib

test: $(TRGS_TEST) copy_lib

$(TRGS): $(OBJECTS)
	@$(CC) $(subst $(BIN_DIR),$(OBJ_DIR),$@).o $(OBJS) $(LFLAGS) -o $@$(EXE_EXT)
	@echo "Linking $(notdir $@) complete!"

$(TRGS_TEST): $(OBJS) $(OBJECTS_TEST)
	@$(CC) $(subst $(BIN_DIR),$(OBJ_DIR),$@).o $(OBJS) $(LFLAGS) -o $@$(EXE_EXT)
	@echo "Linking $(notdir $@) complete!"

$(OBJECTS):
	$(eval SRC_FILE:=$(filter %/$(subst ___,/,$(subst .o,.c,$(notdir $@))),$(SOURCES)))
	@$(CC) $(CFLAGS) -c $(SRC_FILE) -o $@
	@echo "Compiled $(SRC_FILE) successfully!"

$(OBJECTS_TEST): $(OBJ_DIR)/%.o : $(TEST_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $< successfully!"

.PHONY: copy_lib
copy_lib: $(LIB_TARGET)

$(LIB_TARGET):
	@$(CP) $(subst /,$(PATH_SEP),$(LIB_TARGET_DIR)/$@ $(BIN_DIR)/$@)
	@echo "Library $(LIB_TARGET_DIR)/$@ -> $(BIN_DIR)/$@ copied correctly!"

.PHONY: clean
clean:
	@$(RM) $(subst /,$(PATH_SEP),$(OBJECTS))
	@$(RM) $(subst /,$(PATH_SEP),$(OBJECTS_TEST))
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(RM) $(addsuffix $(EXE_EXT),$(subst /,$(PATH_SEP),$(TRGS)))
	@$(RM) $(addsuffix $(EXE_EXT),$(subts /,$(PATH_SEP),$(TRGS_TEST)))
	@echo "Executable removed!"

install_sdl:
ifneq ($(OS), Windows_NT)
	@rm -rf SDL_lib
	@mkdir SDL_lib

	@rm -rf SDL
	@git clone https://github.com/libsdl-org/SDL.git && cd SDL && git checkout release-2.26.2
	@cd SDL && ./configure --prefix=$(shell pwd)/SDL_lib && $(MAKE) -j$(CPU_COUNT) && $(MAKE) -j$(CPU_COUNT) install
	@rm -rf SDL

	@rm -rf SDL_image
	@git clone https://github.com/libsdl-org/SDL_image.git && cd SDL_image && git checkout release-2.6.2
	@cd SDL_image && ./configure --prefix=$(shell pwd)/SDL_lib && $(MAKE) -j$(CPU_COUNT) && $(MAKE) -j$(CPU_COUNT) install
	@rm -rf SDL_image

	@rm -rf SDL_ttf
	@git clone https://github.com/libsdl-org/SDL_ttf.git && cd SDL_ttf && git checkout release-2.0.18
	@cd SDL_ttf && ./configure --prefix=$(shell pwd)/SDL_lib && $(MAKE) -j$(CPU_COUNT) && $(MAKE) -j$(CPU_COUNT) install
	@rm -rf SDL_ttf

	@cp -r SDL_lib/lib/* $(LIB_DIR)
	@cp -r SDL_lib/include/* $(INC_DIR)

	@rm -rf SDL_lib
endif

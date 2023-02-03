CC = gcc

EXEC =Pkm
CFLAGS = -Wall -g

SRCDIR=src
OBJDIR=obj
BINDIR=bin
DOCDIR=doc

DIRS=$(OBJDIR) $(BINDIR)

.PHONY=DIRS

all: $(DIRS) $(BINDIR)/$(EXEC)


$(OBJDIR):
	mkdir -p $(OBJDIR)
$(BINDIR):
	mkdir -p $(BINDIR)
$(DOCDIR):
	mkdir -p $(DOCDIR)

SOURCES = $(wildcard $(SRCDIR)/*.c)
INCLUDES = $(wildcard $(SRCDIR)/*.h)

OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)


$(BINDIR)/$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@
	@echo "Liens terminés!"
	./bin/$(EXEC)
        #doxygen -g (si on veut générer le doxyfile à l'exécution du makefile)


$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -c $< -I$(SRCDIR) -o $@
	@echo "Compilation de "$<" terminée!"



.PHONY: clean
clean:
	-rm -rf $(OBJDIR)
	@echo "Nettoyage terminé!"

.PHONY: mrproper
mrproper:
	-rm -rf $(BINDIR)
	-rm -rf doc/
	@echo "Exécutable et documentation supprimés!"

.PHONY: docs
doxygen:
	doxygen -g
docs:
	#mkdir -p doc : paramétrer doxyfile pour envoyer les fichiers de sortie dans le rep doc
	doxygen doxyfile
	open doc/html/index.html

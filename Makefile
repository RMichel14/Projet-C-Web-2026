EXT = c
CXX = gcc
EXEC = projet

SRCDIR = filesC
OBJDIR = dependencies
INCDIR = include

CXXFLAGS = -Wall -W -pedantic -I$(INCDIR)
LDFLAGS = -lm

SRC = $(wildcard $(SRCDIR)/*.$(EXT))
OBJ = $(SRC:$(SRCDIR)/%.$(EXT)=$(OBJDIR)/%.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.$(EXT) | $(OBJDIR)
	$(CXX) -o $@ -c $< $(CXXFLAGS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)/*.o
	rm -f $(EXEC)

.PHONY: all clean

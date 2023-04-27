# Nom du projet
PROG = sondePT100

# Définir les outils de compilation
CC = g++
CFLAGS = `wx-config --cxxflags`
LDFLAGS = `wx-config --libs`
LIBS = -lmLiquidCrystal
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin

# Files extensions .cpp, .o
SUFFIXES = .cpp .o 
.SUFFIXES: $(SUFFIXES) 

# Définir les cibles
OBJS = main.o

all: $(PROG)

# Règles de compilation
$(PROG): $(OBJS)
    $(CC) -o $(PROG) $(OBJS) $(LIBS) $(LDFLAGS)
    
.cpp.o:
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(PROG)
    -rm -f *.o

install: 
    cp -f $(PROG) $(BINDIR)

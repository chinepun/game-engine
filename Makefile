########################################################################
####################### Makefile Template ##############################
########################################################################

# Compiler settings - Can be customized.
CC = g++
CXXFLAGS = -g -std=c++17 -Wpedantic -I. -I$(CURDIR)/include
LDFLAGS = -ldl -lglfw -lpthread -lGL -lGLU -lglut -lXrandr -lX11

# Makefile settings - Can be customized.
BINDIR = ${CURDIR}/bin
APPNAME = $(BINDIR)/game
EXT_CPP = .cpp
EXT_C = .c
SRCDIR = $(CURDIR)/src
OBJDIR = $(CURDIR)/obj
RM = rm

############## Do not change anything from here downwards! #############
SRC_CPP = $(wildcard $(SRCDIR)/*$(EXT_CPP))
SRC_C = $(wildcard $(SRCDIR)/*$(EXT_C))
OBJ_CPP = $(SRC_CPP:$(SRCDIR)/%$(EXT_CPP)=$(OBJDIR)/%.o)
OBJ_C = $(SRC_C:$(SRCDIR)/%$(EXT_C)=$(OBJDIR)/%.o)

all: $(APPNAME)

# Builds the app
$(APPNAME): $(OBJ_C) ${OBJ_CPP}
	$(CC) $(CXXFLAGS) $(OBJ_C) ${OBJ_CPP} $(LDFLAGS) -o $(APPNAME)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT_CPP)
	$(CC) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT_C)
	$(CC) $(CXXFLAGS) -c $< -o $@


################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	-@rm $(APPNAME)
	-@rm $(OBJDIR)/*.o


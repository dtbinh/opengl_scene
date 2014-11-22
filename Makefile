
#test

CC = g++
LD = g++
CPPFLAGS = -Wall -pedantic -ansi -g   #-O2   # pour optimiser
LDFLAGS  =

INCLUDE_DIR = -I/usr/include/ -I./GL -I.
LIB_DIR =
LIBS = -L/usr/X11R6/lib  -lGL -lGLU -lglut

FINAL_TARGET = LIFO41_TP

OBJ_DIR = bin
SRC_DIR = .
BIN_DIR = bin

SRCS = opengl.cpp Image.cpp Scene.cpp Vec3f.cpp Animation.cpp


default: $(BIN_DIR)/$(FINAL_TARGET)


# rules

$(BIN_DIR)/$(FINAL_TARGET): $(SRCS:%.cpp=$(OBJ_DIR)/%.o)
	$(LD) $+ -o $@ $(LDFLAGS) $(LIB_DIR) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c $(CPPFLAGS) $(INCLUDE_DIR) $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/$(FINAL_TARGET)


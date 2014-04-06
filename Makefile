# CONFIGURATION
PROJECT := bezier-s
TESTBUILD := btester 

CC := g++
CCFLAGS := -Ilib -Wall -O3
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -I./include/ -I/usr/X11/include -DOSX
	LDFLAGS = -framework GLUT -framework OpenGL \
    	-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
    	-lGL -lGLU -lm -lstdc++
else
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -Iglut-3.7.6-bin
	LDFLAGS = -lglut -lGLU
endif

SRCFOLDER := src
OBJFOLDER := obj
TESTFOLDER := test

# processing stuff
SRC := $(wildcard $(SRCFOLDER)/*.cpp)
OBJ := $(addprefix $(OBJFOLDER)/, $(notdir $(SRC:.cpp=.o)))
TEST := $(wildcard $(TESTFOLDER)/*.cpp)
TESTOBJ := $(filter-out obj/main.o, $(OBJ)) $(addprefix $(TESTFOLDER)/, $(notdir $(TEST:.cpp=.o)))

ifeq ($(OS), Windows_NT)
	RM = del /F
	DELETEOBJS = $(OBJFOLDER)\*.o $(TESTFOLDER)\*.o
else
	RM = rm -f
	DELETEOBJS = $(OBJFOLDER)/*.o $(TESTFOLDER)/*.o
endif

.PHONY: all clean build
all: $(PROJECT)

clean:
	$(RM) $(DELETEOBJS) $(PROJECT) $(TESTBUILD)
	
build: clean all
	
test: $(TESTBUILD)
	
# compile test build
$(TESTBUILD): $(TESTOBJ)
	$(CC) $(CCFLAGS) $^ -o $@ $(LDFLAGS) 
$(TESTFOLDER)/%.o: $(TESTFOLDER)/%.cpp
	$(CC) $(CCFLAGS) -c $< -o $@
	
# compile targets
$(PROJECT): $(OBJ)
	$(CC) $(CCFLAGS) -o $@ $^ $(LDFLAGS)
$(OBJFOLDER)/%.o: $(SRCFOLDER)/%.cpp
	$(CC) $(CCFLAGS) -o $@ -c $< 

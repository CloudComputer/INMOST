CXX=mpicxx
CC=mpicxx

#links for cluster
#PETSC_DIR=/data4t/terekhov/Packages/petsc-3.3-p3
#PETSC_ARCH=arch-linux2-c-opt
#INCPATH =  -I${PETSC_DIR}/${PETSC_ARCH}/include -I${PETSC_DIR}/include

MSPPLIB = ../../mspp.a
#MSPPLIB = ../../msppd.a
#OPTFLAGS= -O0 -g  -Wall -Wno-unused-function
OPTFLAGS=  -Ofast -flto -fwhole-program -march=native -DNDEBUG -ftree-vectorize

OPENGL=-L/usr/X11R6/lib -lX11 -lXi -lXmu -lGL -lglut -lGLU
#OPENGL=-framework GLUT -framework OpenGL
#OPENGL=-lglut -lgl -lglu32 -lopengl32
#OPENGL=-L/lib -lglu32 -lopengl32 
MYLIBS= $(OPENGL)
CXXFLAGS=$(OPTFLAGS) $(INCPATH)

LDFLAGS=$(OPTFLAGS) 
LDLIBS=$(MYLIBS)  $(PETSC)


targets=main

all: $(targets)


main: main.o rotate.o $(MSPPLIB)


clean:
	rm -f $(targets) *.o

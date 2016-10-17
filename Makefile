#----------------------------------------------
#    Example Makefile for compiling a program that uses
#    the Matrix and Vector classes
#----------------------------------------------
#
#  Programmer: Donald House
#  Date: March 8, 1999
#
#  Copyright (C) - Donald H. House. 2005
#

CC  = clang
C	= cpp
H	= h
CFLAGS 	= -g -std=c++11 -lstdc++

ifeq ("$(shell uname)", "Darwin")
  LDFLAGS     = -framework Foundation -framework GLUT -framework OpenGL -lm
else
  ifeq ("$(shell uname)", "Linux")
    LDFLAGS     = -lglut -lGL -lm -L/usr/local/lib -lGLU
  endif
endif

HFILES 	= Matrix.${H} Vector.${H} Utility.${H} Camera.${H} Mesh.${H}
OFILES 	= Matrix.o Vector.o Utility.o Camera.o Mesh.o
PROJECT = SquishyMesh

${PROJECT}:	main.o $(OFILES)
	${CC} $(CFLAGS) -o ${PROJECT} main.o $(OFILES) $(LDFLAGS)

main.o: main.${C} $(HFILES)
	${CC} $(CFLAGS) -c main.${C}

Mesh.o: Mesh.${C} Vector.${H} Utility.${H}
	${CC} $(CFLAGS) -c Mesh.${C}

Camera.o: Camera.${C} Camera.${H} Matrix.${H} Vector.${H} Utility.${H} 
	${CC} $(CFLAGS) -c Camera.${C}

Matrix.o: Matrix.${C} Matrix.${H} Vector.${H} Utility.${H}
	${CC} $(CFLAGS) -c Matrix.${C}

Vector.o: Vector.${C} Vector.${H} Utility.${H} 
	${CC} $(CFLAGS) -c Vector.${C}

Utility.o: Utility.${C} Utility.${H}
	${CC} $(CFLAGS) -c Utility.${C}

debug:
	make 'DFLAGS = /usr/lib/debug/malloc.o'

clean:
	rm -f *.o *~ ${PROJECT}

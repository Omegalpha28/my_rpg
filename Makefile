##
## EPITECH PROJECT, 2024
## moon-engine
## File description:
## Makefile
##

#-----------------------------------------------------------------------------#
#? Compiler Configuration

CC			=	gcc
FLAG		=	-g3															\
				-Wall														\
				-Wextra
FLAG		+=	-Iinclude
FLAG		+=	-lcsfml-system												\
				-lcsfml-window												\
				-lcsfml-graphics											\
				-lcsfml-network												\
				-lcsfml-audio												\
				-lm

#! WINDOWS ONLY
#FLAG		+=	-LC:\MinGW\lib

#-----------------------------------------------------------------------------#

#-----------------------------------------------------------------------------#
#? Engine Sources

E_D_ROOT	=	./moon/
E_D_MATHS	=	$(E_D_ROOT)maths/
E_D_TIME	=	$(E_D_ROOT)time/
E_D_WINDOW	=	$(E_D_ROOT)window/

E_C_MATHS	=	$(E_D_MATHS)clamp.c											\
				$(E_D_MATHS)distance.c										\
				$(E_D_MATHS)intersect.c										\
				$(E_D_MATHS)lerp.c											\
				$(E_D_MATHS)max.c											\
				$(E_D_MATHS)min.c
E_C_WINDOW	=	$(E_D_WINDOW)create.c										\
				$(E_D_WINDOW)destroy.c										\
				$(E_D_WINDOW)time.c

E_SOURCES	=	$(E_C_MATHS)												\
				$(E_C_WINDOW)

E_OBJECTS	=	$(E_SOURCES:.c=.o)

#-----------------------------------------------------------------------------#

#-----------------------------------------------------------------------------#
#? Program Sources

P_D_ROOT	=	./source/

P_C_ROOT	=	$(P_D_ROOT)main.c

P_SOURCES	=	$(P_C_ROOT)

P_OBJECTS	=	$(P_SOURCES:.c=.o)

#-----------------------------------------------------------------------------#

#-----------------------------------------------------------------------------#
#! Building

E_NAME		=	$(E_D_ROOT)moon.a
P_NAME		=	my_rpg

%.o: %.c
	$(CC) $(FLAG) -c $< -o $@

build_engine: $(E_OBJECTS)
	ar -rc $(E_NAME) $(E_OBJECTS)

build_program: build_engine $(P_OBJECTS)
	$(CC) $(FLAG) -o $(P_NAME) $(P_OBJECTS) $(E_NAME)

$(P_NAME): build_program

#-----------------------------------------------------------------------------#

#-----------------------------------------------------------------------------#
#! Testing

T_NAME		=	unit_tests

#-----------------------------------------------------------------------------#

#-----------------------------------------------------------------------------#
#! Cleaning

FIND		=	find -type f -iname
RM			=	rm -f

clean:
	$(FIND) "*.o" -delete
	$(FIND) "*.a" -delete

fclean: clean
	$(RM) $(P_NAME)

tests_clean: clean
	$(FIND) "*.gcno" -delete
	$(FIND) "*.gcda" -delete
	$(FIND) "*.css" -delete
	$(FIND) "*.html" -delete

tests_fclean: tests_clean
	$(RM) $(T_NAME)

#-----------------------------------------------------------------------------#

#-----------------------------------------------------------------------------#
#! Misc

all: $(P_NAME)

re: fclean all

re_program:
	$(RM) $(P_OBJECTS)
	make build_program

tests_re: tests_fclean tests_run

style:
	coding-style . .
	grep -v ":1:" coding-style-reports.log > reports.log
	cat reports.log

#-----------------------------------------------------------------------------#

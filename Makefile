##
## EPITECH PROJECT, 2024
## csfml-engine
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
#? Libmy Compilation

L_D_ROOT	=	./libmy/
L_D_CHAR	=	$(L_D_ROOT)char/
L_D_MEMORY	=	$(L_D_ROOT)memory/
L_D_NUMBER	=	$(L_D_ROOT)number/
L_D_PUTS	=	$(L_D_ROOT)puts/
L_D_STRINGS	=	$(L_D_ROOT)strings/

L_C_CHAR	=	$(L_D_CHAR)countchar.c										\
				$(L_D_CHAR)isalnum.c										\
				$(L_D_CHAR)isalpha.c										\
				$(L_D_CHAR)iscntrl.c										\
				$(L_D_CHAR)isdigit.c										\
				$(L_D_CHAR)isgraph.c										\
				$(L_D_CHAR)islower.c										\
				$(L_D_CHAR)isprint.c										\
				$(L_D_CHAR)ispunct.c										\
				$(L_D_CHAR)isspace.c										\
				$(L_D_CHAR)isupper.c										\
				$(L_D_CHAR)isxdigit.c										\
				$(L_D_CHAR)tolower.c										\
				$(L_D_CHAR)toupper.c
L_C_MEMORY	=	$(L_D_MEMORY)free.c											\
				$(L_D_MEMORY)memcpy.c										\
				$(L_D_MEMORY)memset.c										\
				$(L_D_MEMORY)orealloc.c										\
				$(L_D_MEMORY)realloc.c
L_C_NUMBER	=	$(L_D_NUMBER)atoi.c											\
				$(L_D_NUMBER)isint.c
L_C_PUTS	=	$(L_D_PUTS)fputs.c											\
				$(L_D_PUTS)putchar.c										\
				$(L_D_PUTS)puterr.c											\
				$(L_D_PUTS)putnbr.c											\
				$(L_D_PUTS)putstr.c											\
				$(L_D_PUTS)putwa.c
L_C_STRINGS	=	$(L_D_STRINGS)stowa.c										\
				$(L_D_STRINGS)strchr.c										\
				$(L_D_STRINGS)strcmp.c										\
				$(L_D_STRINGS)strdcat.c										\
				$(L_D_STRINGS)strdup.c										\
				$(L_D_STRINGS)stris.c										\
				$(L_D_STRINGS)strlen.c										\
				$(L_D_STRINGS)strncat.c										\
				$(L_D_STRINGS)strncmp.c										\
				$(L_D_STRINGS)strncpy.c										\
				$(L_D_STRINGS)strndup.c										\
				$(L_D_STRINGS)strpbrk.c										\
				$(L_D_STRINGS)strsplit.c									\
				$(L_D_STRINGS)strspn.c										\
				$(L_D_STRINGS)strtok_r.c									\
				$(L_D_STRINGS)strtok.c										\
				$(L_D_STRINGS)strtol.c										\
				$(L_D_STRINGS)strwlen.c										\
				$(L_D_STRINGS)wacmp.c										\
				$(L_D_STRINGS)wacpy.c										\
				$(L_D_STRINGS)walen.c										\
				$(L_D_STRINGS)watroy.c

L_SOURCES	=	$(L_C_CHAR)													\
				$(L_C_MEMORY)												\
				$(L_C_NUMBER)												\
				$(L_C_PUTS)													\
				$(L_C_STRINGS)

L_OBJECTS	=	$(L_SOURCES:.c=.o)

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
L_NAME		=	$(L_D_ROOT)libmy.a

%.o: %.c
	$(CC) $(FLAG) -c $< -o $@

build_library: $(L_OBJECTS)
	ar -rc $(L_NAME) $(L_OBJECTS)

build_engine: $(E_OBJECTS)
	ar -rc $(E_NAME) $(E_OBJECTS)

build_program: build_library build_engine $(P_OBJECTS)
	$(CC) $(FLAG) -o $(P_NAME) $(P_OBJECTS) $(E_NAME) $(L_NAME)

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

re_library:
	$(RM) $(L_OBJECTS) $(L_NAME)
	make build_library

re_program:
	$(RM) $(P_OBJECTS) $(L_NAME)
	make build_program

tests_re: tests_fclean tests_run

style:
	coding-style . .
	grep -v ":1:" coding-style-reports.log > reports.log
	cat reports.log

#-----------------------------------------------------------------------------#

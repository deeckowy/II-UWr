CC=g++ 
SFMLflags=-lsfml-graphics -lsfml-window -lsfml-system

NAME=LastSpace3000
SRC=main.cpp game.cpp functions.cpp screens.cpp
OBJS=main.o game.o functions.o screens.o

main:
	@$(CC)-c $(SRC)
	@$(CC) $(OBJS) -o $(NAME) $(SFMLflags)

clean:
	@rm -f $(OBJS) $(NAME)
 

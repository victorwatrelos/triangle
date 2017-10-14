CC= clang++
FLAGS=-Wall -Wextra -std=c++1z
FRWK=-framework sfml-graphics -framework sfml-system -framework sfml-window
NAME_BIN= triangle

SRC= main.cpp \
	 WindowManager.cpp \
	 ObjectManager.cpp

.PHONY: clean fclean re all
.SILENT:

OBJ= $(SRC:.cpp=.o)

all:$(NAME_BIN)

$(NAME_BIN): $(OBJ)
		$(CC) -o $(NAME_BIN) $(OBJ) $(LIB) $(FRWK) $(INC) $(FLAGS)
		echo "\t\xF0\x9F\x8F\x81   Compiling \033[35m$(NAME) \033[0mDONE!"

%.o: %.cpp
		echo "\t\xF0\x9F\x94\xA7   Building \033[34m $@ \033[0m" 
		$(CC) -c $(FLAGS) $(INC) -o $@ $<

clean:
		echo "\t\xF0\x9F\x92\xA3   Cleaning"
		rm -rf $(OBJ)

fclean: clean
		echo "\t\xF0\x9F\x9A\xBD   Full Clean"
		rm -rf $(NAME_BIN)

re: fclean all
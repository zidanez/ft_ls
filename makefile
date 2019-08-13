NAME			= ft_ls

SOURSE_DIRS		:= srcs

#FLAGS			= -Wall -Werror -Wextra

framework		= -I includes/ft_ls.h -L ./libft/ -lft

LS_HED			= includes
LH_DIR			= libft/includes

SEARCH_WILDCARDS:= $(addsuffix /*.c, $(SOURSE_DIRS))

OBJECTS			= $(notdir $(patsubst %.c,%.o, $(wildcard $(SEARCH_WILDCARDS))))

all: $(NAME)

$(NAME): $(OBJECTS)
	gcc $^ -o $@ $(framework)

VPATH := $(SOURSE_DIRS)

%.o: %.c
	gcc -g $(FLAGS) -c $<  -I$(LH_DIR) -I$(LS_HED)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

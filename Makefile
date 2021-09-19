NAME = minitalk
SERVER = server
CLIENT = client

SERVER_DIR = ./src/server
CLIENT_DIR = ./src/client
OBJ_DIR = ./obj

PRINTF_DIR = ./ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SERVER_FILES = server.c \
			   handlers.c

CLIENT_FILES = client.c \
			   client_utils.c

IFLAGS = -I./libft -I./ft_printf
LFLAGS = -L./libft -L./ft_printf -lftprintf -lft

SERVER_OBJS = $(addprefix $(OBJ_DIR)/, $(SERVER_FILES:.c=.o))
CLIENT_OBJS = $(addprefix $(OBJ_DIR)/, $(CLIENT_FILES:.c=.o))

CFLAGS = -Wall -Werror -Wextra -O3
CC = clang
RM = rm -rf

all: $(NAME)

$(NAME): $(LIBFT) $(PRINTF) $(OBJ_DIR) $(SERVER) $(CLIENT)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(SERVER): $(SERVER_OBJS)
	$(CC) $(SERVER_OBJS) -o $(SERVER) $(LFLAGS)

$(CLIENT): $(CLIENT_OBJS)
	$(CC) $(CLIENT_OBJS) -o $(CLIENT) $(LFLAGS) 

$(OBJ_DIR)/%.o: $(SERVER_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(CLIENT_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(PRINTF):
	make -C $(PRINTF_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	$(RM) $(SERVER_OBJS) $(CLIENT_OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(SERVER)
	$(RM) $(CLIENT)

re: fclean all

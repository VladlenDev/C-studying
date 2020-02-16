SRC_DIR = src
OBJ_DIR = obj
CC = gcc
CFLAGS = -c -Wall -I"./include"
LDFLAGS =
SOURCES = $(SRC_DIR)/server.c $(SRC_DIR)/client.c $(SRC_DIR)/chat.c
OBJECTS = $(OBJ_DIR)/server.o $(OBJ_DIR)/client.o $(OBJ_DIR)/chat.o
EXECUTABLE = server client

all: $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJ_DIR)/server.o $(OBJ_DIR)/chat.o -o server
	$(CC) $(LDFLAGS) $(OBJ_DIR)/client.o $(OBJ_DIR)/chat.o -o client

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(EXECUTABLE)
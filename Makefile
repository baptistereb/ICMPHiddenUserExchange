CC = gcc
CFLAGS = -Wall -Wextra -g
SERVER_SRC = icmp_server.c
CLIENT_SRC = icmp_client.c
SERVER_BIN = icmp_server
CLIENT_BIN = icmp_client
HEAD = "[ICMP-HUE Makefile] "

all: $(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN): $(SERVER_SRC)
	$(CC) $(CFLAGS) $< -o $@
	@echo "$(HEAD) Server compiled successfully as $(SERVER_BIN)"

$(CLIENT_BIN): $(CLIENT_SRC)
	$(CC) $(CFLAGS) $< -o $@
	@echo "$(HEAD) Client compiled successfully as $(CLIENT_BIN)"

.PHONY: all clean

clean:
	rm -f $(SERVER_BIN) $(CLIENT_BIN)
	@echo "$(HEAD) Clean complete."
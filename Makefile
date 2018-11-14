CC = gcc
CFLAGS += -Wall

BIN_NAME = prom-cli
BUILD_DIR = build
OUTPUT = -o $(BUILD_DIR)/$(BIN_NAME)

INC_DIR = -Iinclude

SOURCES += src/main.c
SOURCES += src/network.c
SOURCES += src/api.c

all: $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INC_DIR) $(OUTPUT) $(SOURCES)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

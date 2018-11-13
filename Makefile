CC = gcc
BIN_NAME = prom-cli

BUILD_DIR = build
SOURCES += src/main.c
FLAGS += -Wall

all: $(BUILD_DIR)
	$(CC) $(FLAGS) $(SOURCES) -o $(BUILD_DIR)/$(BIN_NAME)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

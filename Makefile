CC = arm-linux-gnueabihf-gcc-6
BIN_NAME = prom-cli

BUILD_DIR = build
SOURCES += src/main.c

all: $(BUILD_DIR)
	$(CC) $(SOURCES) -o $(BUILD_DIR)/$(BIN_NAME)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

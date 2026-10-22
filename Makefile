.PHONY: all build run clean configure

BUILD_DIR := build
TARGET := network-server

all: configure build run/dev

configure:
	cmake -S . -B $(BUILD_DIR) -G Ninja

build:
	cmake --build $(BUILD_DIR)

run: configure build
	./$(BUILD_DIR)/$(TARGET)

run/dev: configure build
	ENV=development ./$(BUILD_DIR)/$(TARGET)

clean:
	rm -rf $(BUILD_DIR)

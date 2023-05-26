CXX      := -c++
CXXFLAGS := -pedantic-errors -Wall -Wextra -O0 -g -fPIC -std=c++11
LDFLAGS  := -Wl,--no-as-needed -L/usr/local/lib -lstdc++ -lm
BUILD    := build
OBJ_DIR  := $(BUILD)/objects
APP_DIR  := $(BUILD)
TARGET   := breher
INCLUDE  := -I.
SRC      :=                      \
	$(wildcard *.cpp)         \

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

.PHONY: build clean

$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(APP_DIR)/$(TARGET): $(OBJECTS)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJECTS)

ft1: $(APP_DIR)/$(TARGET)
	cp include/prodsp_ft1.h $(APP_DIR)/prodsp.h
	cp config_ft1.json $(APP_DIR)/config.json

clean:
	rm -rf build/*

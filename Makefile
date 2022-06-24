C         = gcc
CC        = g++
CFLAGS    = -Iinclude
CCFLAGS   = -std=c++17 -Iinclude
LD        = g++
LDFLAGS   = -lglfw

SRC      := src/main.cpp
EXT      := ext/glad.c

SRC_OBJS := $(SRC:%.cpp=build/%.o)
EXT_OBJS := $(EXT:%.c=build/%.o)
OBJS     := $(SRC_OBJS) $(EXT_OBJS)
DEPS     := $(OBJS:build/%.o=deps/%.d)

TARGET   := opengl

all: $(TARGET) 

run: all
	@./opengl

-include $(DEPS)

opengl: $(OBJS)
	@echo "Linking $@"
	@$(LD) $(LDFLAGS) -o $@ $^

build/src/%.o: src/%.cpp
	@mkdir -p deps/src build/src
	@echo "Compiling $@"
	@$(CC) $(CCFLAGS) -MMD -MF deps/$*.d -c -o $@ $^

build/ext/%.o: ext/%.c
	@mkdir -p build/ext
	@echo "Compiling $@"
	@$(C) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf deps/* build/*

CC = g++
SRC_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(subst src,build,$(SRC_FILES))
OBJ_FILES := $(subst .cpp,.o,$(OBJ_FILES))

.PHONY: clean run

build/ortho: $(OBJ_FILES)
	$(CC) $^ -o $@ -lSDL2 -lGL -lGLEW

build/%.o: src/%.cpp
	$(CC) -c $^ -o $@

clean:
	rm build/*

run:
	./build/ortho

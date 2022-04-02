BUILD_DIR ?= ./build/

SRCS := $(shell find . -name "*.cpp" -not -path "./cmake*")

all: Taken.exe

Taken.exe: Taken.o
	g++ -o Taken.exe $(shell find ./build -name "*.o")

Taken.o: $(SRCS)
	g++ -c $(SRCS)
	mv *.o $(BUILD_DIR)
     
clean:
	rm -rf Taken.exe $(BUILD_DIR)*

CPPFLAGS=-c -g -Wall -pedantic -std=c++17
OBJS=$(BUILD)/menu.o $(BUILD)/image.o
EXEC=run
BUILD=build
	
$(EXEC): $(OBJS)
	g++ -o $(EXEC) $(OBJS)

$(BUILD)/menu.o: src/menu.cpp inc/image.hh
	g++ ${CPPFLAGS} -o $(BUILD)/menu.o src/menu.cpp

$(BUILD)/image.o: src/image.cpp inc/image.hh
	g++ ${CPPFLAGS} -o $(BUILD)/image.o src/image.cpp

build:
	mkdir -p $(BUILD)

clear:
	rm $(EXEC) $(OBJS)
	rm -r $(BUILD)

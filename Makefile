CPP := circle
FLAG := -Wall -Wextra -c
RM := rm -f

PROJ_NAME := e++

.PHONY: 
	all
	clean
	c
	install


all: $(PROJ_NAME)

############################# TUI  ##################################

tui_menu.o: ./src/tui/menu.cxx
	$(CPP) $(FLAG) ./src/tui/menu.cxx -o ./build/tui_menu.o

tui_text_box.o: ./src/tui/text_box.cxx
	$(CPP) $(FLAG) ./src/tui/text_box.cxx -o ./build/tui_text_box.o

tui: tui_menu.o tui_text_box.o
	echo tui compiled

############################# UTIL ##################################

util_src1.o: ./src/util/src1.cxx
	$(CPP) $(FLAG) ./src/util/src1.cxx -o ./build/util_src1.o


util_func.o: ./src/util/func.cpp
	$(CPP) $(FLAG) ./src/util/func.cpp -o ./build/util_func.o

util: util_func.o util_src1.o
	echo util compited

#####################################################################

main.o: ./main.cpp
	$(CPP) $(FLAG) ./main.cpp -o ./build/main.o

#link tout (normalement)
$(PROJ_NAME): util tui main.o
	$(CPP) -lncurses ./build/*.o -o $(PROJ_NAME)

c:
	$(CPP) -lncurses ./build/*.o -o $(PROJ_NAME)

clean:
	$(RM) ./build2/*.o 

install:
	cp ./$(PROJ_NAME) /bin/

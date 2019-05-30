# snake
#
# 用 > 替代tab
#.RECIPEPREFIX = >
#
BUILD_PATH = $(PWD)/BUILD
#
BIN_PATH = $(PWD)/bin
#
OBJ_PATH = $(PWD)/src
#

SNAKE = snake

all: $(SNAKE)

$(SNAKE): $(OBJ_PATH)/Snake.o $(OBJ_PATH)/Map.o $(OBJ_PATH)/Food.o
	gcc -g $^ -lcurses -o $@
#	echo $(BUILD_PATH)
#	echo $(BIN_PATH)
#	echo $(OBJ_PATH)
#	echo $(PWD)



clean:
	@echo "cleanning project"
	-rm $(SNAKE) $(OBJ_PATH)/*.o $(OBJ_PATH)/*.d
	@echo "clean completed"

.PHONY: clean

sources = $(OBJ_PATH)/Snake.c $(OBJ_PATH)/Map.c $(OBJ_PATH)/Food.c

include $(sources:.c=.d)

%.d: %.c
	set -e; rm -f $@; \
	echo $@;\
		$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$


#	echo $(@)


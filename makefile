# hello
### https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html ###

CC := gcc
CFLAGS := -Wall -Wextra -g
MAIN := test/vm

VPATH := src:src/*.c

OBJ_DIR := obj
_OBJS := main.o util.o gen.o args.o write.o fatal.o
OBJS := $(patsubst %, $(OBJ_DIR)/%, $(_OBJS) )

.PHONY:	depend clean

all: $(MAIN)
	@echo \`$(MAIN)\' hath compiled

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(MAIN)

$(OBJ_DIR)/%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@


clean:
	$(RM) $(OBJ_DIR)/*.o *~


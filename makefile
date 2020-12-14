CC = g++

SRCDIR = src
OBJDIR = obj

SRC = $(wildcard $(SRCDIR)/*.c)
HEADR = $(wildcard $(SRCDIR)/*.h)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

CFLAGS = -Wall
LFLAGS = -lncurses

holiday : $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS)

$(OBJ): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ) holiday

CC ?= g++
CFLAGS ?= -Wall -Wextra -Werror -std=c++17
LDLIBS ?= -lstdc++ -pthread -lSDL2main -lSDL2

INCLUDE_PATH = ./include

TARGET   = echecs

SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.cc)
INCLUDES := $(wildcard $(INCLUDE_PATH)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)

$(BINDIR)/$(TARGET): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
	@echo "Programme compilé !"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cc $(INCLUDES)
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -isystem$(INCLUDE_PATH)


.PHONY: all tests clean cov
clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(OBJDIR)/*.gcda
	rm -f $(OBJDIR)/*.gcno
	rm -f $(BINDIR)/$(TARGET)
	rm -r html

debug: 
	make CFLAGS="-Wall -Wextra -Werror -std=c++17 -DDEBUG"

all:
	make
	make doc
	make tests

doc:
	@doxygen > /dev/null 2>&1
	@echo "Documentaion générée !"
	@xdg-open html/index.html

tests:
	@make
	@cd tests/parties-test && ./test-level.sh 4 && ./test-level.sh 5 && ./test-level.sh 6
	
		
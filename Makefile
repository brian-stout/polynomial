CPPFLAGS+=-Wall -Wextra -Wpedantic
CPPFLAGS+=-Wwrite-strings -Wstack-usage=1024 -Wfloat-equal
CPPFLAGS+=-Waggregate-return -Winline

CFLAGS+=-std=c11 -g

LDLIBS+=-lm

BIN=polynomial
DEPS=polynomial.o

$(BIN) : $(DEPS)

.PHONY: debug profile clean

debug: CFLAGS+=-g

profile: CFLAGS+=-pg
profile: LDFLAGS+=-pg

clean:
	$(RM) $(BIN) $(DEPS)

run:
	./$(BIN)

val:
	valgrind ./$(BIN)

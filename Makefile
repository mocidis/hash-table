.PHONY: all clean
APP:=app
APP_DIR:=.
APP_SRCS:=$(APP).c

HASH_DIR:=.
HASH_SRCS:=hash-table.c

COM_DIR:=../common
COM_SRCS:=my-pjlib-utils.c ansi-utils.c

CFLAGS:=$(shell pkg-config --cflags libpjproject) 
CFLAGS+=-I$(APP_DIR)/include
CFLAGS+=-I$(COM_DIR)/include

LIBS:=$(shell pkg-config --libs libpjproject) 

all: $(APP)

$(APP): $(APP_SRCS:.c=.o) $(HASH_SRCS:.c=.o) $(COM_SRCS:.c=.o)
	gcc -o $@ $^ $(LIBS)

$(APP_SRCS:.c=.o): %.o :$(APP_DIR)/test/%.c
	gcc -o $@ -c $< $(CFLAGS)
$(HASH_SRCS:.c=.o): %.o :$(HASH_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)
$(COM_SRCS:.c=.o): %.o :$(COM_DIR)/src/%.c
	gcc -o $@ -c $< $(CFLAGS)

clean:
	rm -fr $(APP) *.o

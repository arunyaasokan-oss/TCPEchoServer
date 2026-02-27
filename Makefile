CC	=	gcc

TARGET	=	clienttest
INC_DIRS	=	$(shell find . -name "*.h" -exec dirname {} + |sort -u)
INC_FLAGS	=	$(addprefix -I, $(INC_DIRS))

CFLAGS	=	-g -Wall $(INC_FLAGS) -MMD -MP
SRCS	=	$(shell find . -name "*.c")
OBJS	=	$(SRCS:.c=.o)
DEPS	=	$(SRCS:.c=.d)

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(OBJS) -o $@

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)

-include $(DEPS)
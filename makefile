CC = gcc
LD = $(CC)

TARGET = $(notdir $(CURDIR))

SRC_DIR = .
INCLUDE_DIR += .

C_FLAGS = -g -Wall
LD_FLAFS = 
LD_LIBS =
INCLUDES = -I$(INCLUDE_DIR)

ifeq ($(CC), g++)
	TYPE = cpp
	SRCS += $(wildcard $(SRC_DIR)/*.$(TYPE))
	OBJS += $(patsubst %.$(TYPE), %.o, $(SRCS))
else
	TYPE = c
	SRCS += $(wildcard $(SRC_DIR)/*.$(TYPE))
	OBJS += $(patsubst %.$(TYPE), %.o, $(SRCS))
endif

all : $(TARGET)
	@echo "Builded target:" $^
	@echo "Done"

$(TARGET) : $(OBJS)
	@echo "Linking" $@ "from" $^ "..."
	$(LD) -o $@ $^ $(LD_FLAGS) $(LD_LIBS)
	@echo "Link finished\n"

$(OBJS) : %.o:%.$(TYPE) 
	@echo "Compiling" $@ "from" $< "..."
	$(CC) -c -o $@ $< $(C_FLAGS) $(INCLUDES)
	@echo "Compile finished\n"

.PHONY : clean cleanobj
clean : cleanobj
	@echo "Remove all executable files"
	rm -f $(TARGET)
cleanobj :
	@echo "Remove binary files"
	rm -f *.o

# g++ main.cpp rainy.cpp testsql.cpp
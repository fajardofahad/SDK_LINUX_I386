APP_TARGETA = Demo_linux_a
APP_TARGETSO = Demo_linux_so

CXXFLAGS += -Wall
CXXFLAGS += -DSYS_LINUX
ifeq ($(DEBUG),1)
  CXXFLAGS += -g
else
  CXXFLAGS += -O2
endif

CXX = g++
LD = ld
AR = ar
RM = rm -f

.PHONY: all

all: 
ifeq ($(SO),1)
	$(CXX) $(CXXFLAGS) main.cpp -o $(APP_TARGETSO) -lrt -lpthread ./libNetClient.so
else
	$(CXX) $(CXXFLAGS) main.cpp -o $(APP_TARGETA) -lrt -lpthread ./libNetClient.a
endif
CXX        := g++
CXXFLAGS   := -std=c++11 -Wall -Wextra -ggdb

SERVER     := server.out
CLIENT     := client.out

MAIN_SRC   := ./main/src
HELPER_SRC := ./helpers/src
COMMON_SRC := ./common/src
ENTITY_SRC := ./roles/src

HELPER_INC := ./helpers/include
COMMON_INC := ./common/include
ROLES_INC  := ./roles/include

OBJ_DIR    := ./objs

INCFLAG    := -iquote $(HELPER_INC) \
              -iquote $(COMMON_INC) \
			  -iquote $(ROLES_INC)

#------------------------------------
INC_DIR    := $(HELPER_INC) \
              $(COMMON_INC) \
			  $(ROLES_INC)

SRC_DIR    := $(COMMON_SRC) \
              $(HELPER_SRC) \
              $(MAIN_SRC) \
			  $(ENTITY_SRC)

	            
MKDIRS     := $(OBJ_DIR)

OBJS       := utils.o \
              serverhelper.o \
              clienthelper.o \
			  role.o \
			  player.o \
			  spectator.o \
			  arbiter.o

OBJ_ADDR   := $(addprefix $(OBJ_DIR)/, $(OBJS))

#------------------------------------
vpath %.cpp $(SRC_DIR)
vpath %.hpp $(INC_DIR)

#------------------------------------
all: makedirs $(OBJS) $(SERVER) $(CLIENT);

makedirs:
	mkdir -p $(MKDIRS)

$(SERVER): $(MAIN_SRC)/server.cpp $(OBJ_ADDR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(INCFLAG)

$(CLIENT): $(OBJ_ADDR) $(MAIN_SRC)/client.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ $(INCFLAG)

%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) $< -c -o $(OBJ_DIR)/$@ $(INCFLAG)

#------------------------------------
clean:
	rm -f *.o *.out $(OBJ_ADDR)
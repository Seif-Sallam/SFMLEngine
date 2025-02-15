# Makefile for the Sandbox Project that will create an executable.

#Makefile for the SFML engine that will create only a lib file for the Engine

bold := $(shell tput bold)
NC := $(shell tput sgr0)
green := $(shell tput setaf 2)
red := $(shell tput setaf 1)

CC:=g++

HEADERS_DIR:= ./headers/
SRC_DIR:= ./src/
SFML_LIB_DIR:= ./../Thirdparty/SFMLLinux/lib/
BOX2D_LIB_DIR:= ./../Thirdparty/Box2D/BuildLib/
SFMLENEINE_DIR:=./../SFMLEngine/BuildLib/

IMGUI_SRC_DIR:= ./../Thirdparty/imgui/
SFML_INC_DIR:= ./../Thirdparty/SFMLLinux/include/
BOX2D_INC:= ./../Thirdparty/Box2D/include/
SFMLENGINE_INC:=./../SFMLEngine/headers/

LIBS:= -lSFMLEngine -lGL -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d

OBJECTS_DIR:= Objs/

OUTPUT:= Asteroids.out
OUTPUT_DIR:= ./Build/


SOURCES:= $(shell find $(SRC_DIR) -name  '*.cpp')
HEADERS_DIRS:=$(sort $(dir $(shell find $(HEADERS_DIR) -name '*.h')))

INC= -I$(SFML_INC_DIR)
INC+= -I$(BOX2D_INC)
INC+= -I$(IMGUI_SRC_DIR)
INC+= -I$(SFMLENGINE_INC)
INC+= -I$(SRC_DIR)
INC+= $(addprefix -I, $(HEADERS_DIRS))
CCFLAGS= $(INC) -std=c++17 -g
LINK_DIRS:=-L$(SFML_LIB_DIR)
LINK_DIRS+=-L$(BOX2D_LIB_DIR)
LINK_DIRS+=-L$(SFMLENEINE_DIR)


OBJECTS:= $(patsubst %.cpp, %.o, $(subst ./src/, ./Objs/, $(SOURCES)))

VPATH_SRC:=$(sort $(dir $(SOURCES)))

CREATE_DIRS:= $(OUTPUT_DIR) $(sort $(dir $(OBJECTS)))

vpath %.h $(HEADERS_DIR)
vpath %.cpp $(VPATH_SRC)

all: | prep
	@printf '$(red)Compiling and Linking the created objects\n$(NC)'
	@$(MAKE) -s $(OUTPUT_DIR)$(OUTPUT)
	@printf '$(green)Created Binary file $(OUTPUT_DIR)$(OUTPUT)\n\n$(NC)'

$(OUTPUT_DIR)$(OUTPUT): $(OBJECTS)
	@$(CC) $(CCFLAGS) $(OBJECTS) -o $(OUTPUT_DIR)$(OUTPUT) $(LINK_DIRS) $(LIBS)


prep:
	@mkdir -p $(CREATE_DIRS)
	@cd ./../SFMLEngine/ && $(MAKE) -s all

$(OBJECTS): $(OBJECTS_DIR)%.o : $(SRC_DIR)%.cpp
	@printf '$(bold)========== Compiling $(red)$(notdir $^)$(NC)$(bold) ======\n$(NC)'
	@$(CC) -c $(CCFLAGS) $< -o $@
	@printf '$(green)========== Compiled Successfully ======\n$(NC)'

.PHONY: clean

clean:
	@$(RM) $(OBJECTS)
	@$(RM) $(OUTPUT_DIR)$(OUTPUT)
	@printf 'Successfully Cleaned\n'

clean2:
	@$(RM)  $(OUTPUT_DIR)$(OUTPUT)
	@printf 'Successfully Cleaned outputfile\n'
print:
	@for obj in $(INC); do\
		echo $$obj;\
	done
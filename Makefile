# # The base make file that compiles and runs the top project
# include SFMLEngine/Makefile
# include Sandbox/Makefile
# include SampleGame/Makefile

# CC=g++
# SRC_INC_DIR= ./headers/
# SRC_DIR= ./src/
# SFML_INC_DIR= ./Thirdparty/SFML/include/
# LIB_DIR= ./Thirdparty/SFML/lib/
# IMGUI_SRC_DIR= ./Thirdparty/imgui/
# LIBS= -lGL -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
# OBJECTS_DIR = ./Objs/
# OBJECTS = $(subst $(SRC_DIR), $(OBJECTS_DIR), $(patsubst %.cpp, %.o, $(wildcard $(SRC_DIR)*.cpp)) )
# INC= -I$(SFML_INC_DIR)
# CCFLAGS= $(INC)
# vpath %.h $(SRC_INC_DIR)


# all: $(OBJECTS)
# 	$(CC) $(OBJECTS) -o sfml -L$(LIB_DIR) $(LIBS)

# $(OBJECTS): $(OBJECTS_DIR)%.o : $(SRC_DIR)%.cpp	
# 	$(CC) -c $(CCFLAGS) $< -o $@

# .PHONY: clean

# clean:
# 	$(RM) $(OBJECTS)

# print:
# 	for obj in $(OBJECTS); do\
# 		echo $$obj;\
# 	done
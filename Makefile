# The base make file that compiles and runs the top project
DEFAULT_PROJECT_DIR:= ./Sandbox/
SFMLENGINE_DIR:= ./SFMLEngine/

bold := $(shell tput bold)
NC := $(shell tput sgr0)
red := $(shell tput setaf 1)
green := $(shell tput setaf 2)
yellow := $(shell tput setaf 3)

all:
	@printf '$(yellow)Building SFMLEngine $(NC)\n'
	@cd $(SFMLENGINE_DIR) && $(MAKE) -s
	@printf '$(yellow)Successfully built SFMLEngine $(NC)\n'
	@printf '$(yellow)Building Default Project at $(DEFAULT_PROJECT_DIR) $(NC)\n'
	@cd $(DEFAULT_PROJECT_DIR) && $(MAKE) -s
	@printf '$(yellow)Successfully built Default project$(NC)\n\n'
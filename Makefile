# Variable Configurations
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++26 -Isource
LIBS = -lgdi32
MACROS = -DCUSTOM_PLATFORM_WINDOWS

BUILD_DIR = build

SRC_DIR = source
OBJ_DIR = $(BUILD_DIR)/obj
LIB_DIR = $(BUILD_DIR)/lib
LIB_NAME = Custom
ifeq ($(OS),Windows_NT)
	CUSTOM_LIB = $(LIB_DIR)/$(LIB_NAME).lib
	TARGET = $(BUILD_DIR)/application.exe
else
	CUSTOM_LIB = $(LIB_DIR)/lib$(LIB_NAME).a
	TARGET = $(BUILD_DIR)/application
endif

APPLICATION_CPP = example/application.cpp
APPLICATION_BUILD = $(OBJ_DIR)/application/application.o

PCH_HPP = $(SRC_DIR)/precompiled_header.hpp
PCH_CPP = $(SRC_DIR)/precompiled_header.cpp
PCH_OBJ = $(OBJ_DIR)/pch.hpp.gch
SRC_CPPS = $(shell find $(SRC_DIR) -name "*.cpp" -type f)
SRC_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_CPPS))

ifneq ($(filter all,$(MAKECMDGOALS)),)
$(info SRC_OBJS:)
$(foreach file,$(SRC_OBJS),$(info $(file)))
$(info )
endif

GREEN = \e[0;32m
RESET = \e[0;37m

all: $(TARGET)

$(OBJ_DIR):
	@mkdir -p $@

$(LIB_DIR):
	@mkdir -p $@

$(BUILD_DIR):
	@mkdir -p $@

$(PCH_OBJ): $(PCH_CPP)
	@mkdir -p $(dir $@)
	@echo "Build [PRECOMPILED HEADER] $@..."
	@$(CXX) $(CXXFLAGS) $(MACROS) -x c++-header $(PCH_CPP) -o $@
	@echo -e "$(GREEN)Build [PRECOMPILED HEADER] $@ successfully$(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo "Build $@..."
	@$(CXX) $(CXXFLAGS) $(MACROS) $(LIBS) -MMD -MP -include $(PCH_HPP) -c $< -o $@

$(APPLICATION_BUILD): $(APPLICATION_CPP) $(CUSTOM_LIB)
	@mkdir -p $(dir $@)
	@echo -e "Build [APPLICATION] $@..."
	@$(CXX) $(CXXFLAGS) $(MACROS) $(LIBS) -MMD -MP -include $(PCH_HPP) -c $(APPLICATION_CPP) -o $@
	@echo -e "$(GREEN)Build [APPLICATION] $@ successfully$(RESET)\n"

$(CUSTOM_LIB): $(SRC_OBJS) | $(LIB_DIR)
	@echo -e "\nBuild [STATIC LIBRARY] $@..."
	@ar rcs $(CUSTOM_LIB) $(SRC_OBJS)
	@echo -e "$(GREEN)Build [STATIC LIBRARY] $@ successfully$(RESET)\n"

$(TARGET): $(PCH_OBJ) $(CUSTOM_LIB) $(APPLICATION_BUILD) | $(BUILD_DIR)
	@echo -e "\nLink $@..."
	@$(CXX) $(CXXFLAGS) $(MACROS) $(APPLICATION_BUILD) -L$(LIB_DIR) -l$(LIB_NAME) -o $@ -mconsole $(LIBS)
	@echo -e "$(GREEN)Link $@... successfully\n\nExecutable in $@$(RESET)\n"
	@read -p "Press Enter to close"

clean:
	@rm -rf $(BUILD_DIR)

-include $(shell find $(BUILD_DIR) -name "*.d" -type f)

.PHONY: all clean
################################################################################
#                                 _       _     _                              #
#                                (_)     | |   | |                             #
#                __   ____ _ _ __ _  __ _| |__ | | ___  ___                    #
#                \ \ / / _` | '__| |/ _` | '_ \| |/ _ \/ __|                   #
#                 \ V / (_| | |  | | (_| | |_) | |  __/\__ \                   #
#                  \_/ \__,_|_|  |_|\__,_|_.__/|_|\___||___/                   #
#                                                                              #
#                                                                              #
################################################################################


#================================== PROJECT ===================================#
PROJECT_NAME = s21_containers
#==============================================================================#

#================================== COMPILER ==================================#
CXX = g++
#==============================================================================#

#=============================== DIRECTORY NAMES ==============================#
OBJ_DIR = ./obj
MODULES_DIR = ./modules
TEST_DIR = ./tests
REPORT_DIR = ./report
DVI_DIR = ./../docs
#==============================================================================#

#==================================== FLAGS ===================================#
# MAIN FLAGS FOR COMPILER
CXXFLAGS = -Wall -Werror -Wextra -pedantic -g -std=c++17

# CHECK LIBRARY FOR LINKING
LDFLAGS = -lgtest -lgtest_main

# CHECK & GCOV LIBRARY FOR LINKING
LDGCOV = $(LDFLAGS) -lgcov

# FLAGS FOR COVERING MODULES
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

# FLAGS FOR VALGRING TEST
VAL = --tool=memcheck --leak-check=yes

# FLAGS FOR CPPCHECK TEST
CPPCHECK = --enable=all --suppress=missingIncludeSystem
#==============================================================================#


#================================ TARGET NAMES ================================#
LIBRARY = $(PROJECT_NAME).a
TARGET = test
GCOV = gcov_report
#==============================================================================#


#================================ MAIN HEADER =================================#
MAIN_H = $(shell find ./ -maxdepth 1 -name "*.h")
#==============================================================================#


#====================== LIST OF FILE AND DIRS IN MODULES ======================#
MODULES_DIRS = $(shell find $(MODULES_DIR) -type d)
MODULES_CPP = $(shell find $(MODULES_DIR) -type f -name "*.cc")
MODULES_H = $(shell find $(MODULES_DIR) -type f -name "*.h")
MODULES_O = $(notdir $(MODULES_CPP:%.cc=%.o))
MODULES_OBJ_PATH = $(addprefix $(OBJ_DIR)/, $(MODULES_O))
#==============================================================================#


#==================== LIST OF FILE AND DIRS IN TEST MODULES ===================#
TEST_DIRS = $(shell find $(TEST_DIR) -type d)
TEST_CPP = $(shell find $(TEST_DIR) -type f -name "*.cc")
TEST_H = $(shell find $(TEST_DIR) -type f -name "*.h")
TEST_O = $(notdir $(TEST_CPP:%.cc=%.o))
TEST_OBJ_PATH = $(OBJ_DIR)/*_test.o
EXCLUDE = $(filter-out $(wildcard $(MODULES_DIR)/debug/*),$(MODULES_CPP))
#==============================================================================#


#================= LIST OF FILES TO CLANG-FORMAT AND CPPCHECK =================#
CPP_FILES = $(MODULES_CPP) $(TEST_CPP)
H_FILES = $(MODULES_H) $(MAIN_H) $(TEST_H)
ALL_FILES = $(CPP_FILES) $(H_FILES)
#==============================================================================#


#=============== CONFIGURING PATH TO SEARH FOR UNPREFIXED PATHS ===============#
vpath %.cc $(MODULES_DIRS) : $(TEST_DIRS)
vpath %.o $(OBJ_DIR)
#==============================================================================#


################################################################################
#                      _                       _                               #
#                     | |                     | |                              #
#                    _| |_ __ _ _ __ __ _  ___| |_ ___                         #
#                   |_  __/ _` | '__/ _` |/ _ \ __/ __|                        #
#                     | || (_| | | | (_| |  __/ |_\__ \                        #
#                      \__\__,_|_|  \__, |\___|\__|___/                        #
#                                    __/ |                                     #
#                                   |___/                                      #
################################################################################


#================================= MAIN TARGETS ===============================#
.PHONY: $(LIBRARY) $(TARGET) $(GCOV)

all: $(LIBRARY) dvi

$(LIBRARY): $(OBJ_DIR) $(MODULES_O) $(MODULES_H) $(MAIN_H)
	@ar rcs $@ $(MODULES_OBJ_PATH)
	@ranlib $@

$(TARGET): clean $(LIBRARY) $(OBJ_DIR) $(TEST_O)
	@$(CXX) $(TEST_OBJ_PATH) $(LIBRARY) $(LDFLAGS) -o $@
	@-./$@

$(GCOV): $(OBJ_DIR) $(REPORT_DIR) $(TEST_O)
	$(CXX) $(TEST_OBJ_PATH) $(EXCLUDE) $(LDFLAGS) $(GCOV_FLAGS) -o $(addprefix $(OBJ_DIR)/, $(TARGET))
	./$(addprefix $(OBJ_DIR)/, $(TARGET))
	gcovr -r . --html --html-details -o $(REPORT_DIR)/coverage.html
	xdg-open $(REPORT_DIR)/coverage.html

dvi:
	rm -rf $(DVI_DIR)
	doxygen Doxyfile
	xdg-open $(DVI_DIR)/html/index.html

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf $(REPORT_DIR)
	@rm -rf $(DVI_DIR)
	@rm -rf $(GCOV)
	@rm -f $(TARGET)
	@rm -f *.a *.o
	@rm -f *.gc*
	@rm -f val.txt

rebuild: clean all
#==============================================================================#


#============================== CREATE DIRECTORIES ============================#
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(REPORT_DIR):
	@mkdir -p $(REPORT_DIR)
#==============================================================================#


#============================== OBJECTIVE TARGETS =============================#
%.o: %.cc ${MODULES_H}
	$(CXX) $(CXXFLAGS) $(OPTIMIZE) -c -o $(addprefix ${OBJ_DIR}/, $@) $<

%_test.o: %_test.cc
	$(CXX) $(CXXFLAGS) -c -o $(addprefix ${OBJ_DIR}/, $@) $<
#==============================================================================#


#=============================== CHECKS TARGETS ===============================#
deb:
	@$(CXX) -Wall -Wextra -pedantic -g -std=c++17 ./debug/debug.cc $(MODULES_CPP) -o test
	@valgrind $(VAL) ./test
	
clang_check:
	clang-format -style=Google -n $(ALL_FILES)

cpplint:
	cpplint $(MODULES_H)

valgrind: $(TARGET)
	$@ $(VAL) ./$(TARGET)
#==============================================================================#


#============================= ADDITIONAL TARGETS =============================#
clang_fix:
	clang-format -style=Google -i $(ALL_FILES)

dependencies:
	sudo apt install clang-format
	sudo apt-get install libgtest-dev
	sudo apt install doxygen
	sudo apt-get install graphviz
#==============================================================================#

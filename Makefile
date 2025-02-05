NAME = map-generator

# *** FILES ****************************************************************** #

MAKE_DIR := .make/
BUILD_DIR := $(MAKE_DIR)$(shell git branch --show-current 2>/dev/null)/

include SRCS.mk

OBJS = $(patsubst %.cpp,$(BUILD_DIR)%.o,$(SRCS))

DEPS = $(patsubst %.o,%.d,$(OBJS))
-include $(DEPS)

# *** LIBRARIES && INCLUDES  ************************************************* #

LIBS_PATH = \
	./minilibx/libmlx_Linux.a \
		
LIBS = \
	$(patsubst lib%.a,%,$(notdir $(LIBS_PATH))) \
	X11 \
	m \
	z \
	Xext \
	pthread \

INCS_DIR = incs/
INCS = \
	$(INCS_DIR) \
	$(dir $(LIBS_PATH)) \

# *** CONFIG ***************************************************************** #


CXX			=	c++
CXXFLAGS	=	-Wall -Wextra $(OFLAGS)
OFLAGS		=	-O3

DEFINES		=

CPPFLAGS 	=	$(addprefix -I, $(INCS)) \
				$(addprefix -D, $(DEFINES)) \
				-MMD -MP \

LDFLAGS		=	$(addprefix -L, $(dir $(LIBS_PATH)))
LDLIBS		=	$(addprefix -l, $(LIBS))

MAKEFLAGS	=	--no-print-directory

# *** MODES ****************************************************************** #

MODE_TRACE = $(MAKE_DIR).trace 
LAST_MODE = $(shell cat $(MODE_TRACE) 2>/dev/null)

ifneq ($(MODE),)
BUILD_DIR := $(BUILD_DIR)$(MODE)/
endif

ifeq ($(MODE),debug)
CXXFLAGS := $(CXXFLAGS) -g3
else ifeq ($(MODE),fsanitize)
CXXFLAGS := $(CXXFLAGS) -g3 -fsanitize=address
else ifneq  ($(MODE),)
ERROR = MODE
endif

ifneq ($(LAST_MODE),$(MODE))
$(NAME) : FORCE
endif

# *** TARGETS **************************************************************** #

.DEFAULT_GOAL := all

.PHONY : all
all : $(NAME)

$(NAME) : $(LIBS_PATH) $(OBJS)
	@echo "$(BOLD)$(CXX) $(YELLOW)$(CXXFLAGS) $(CYAN)$(OBJS) $(GREEN)$(LDFLAGS) $(LDLIBS) $(WHITE)-o $(NAME) $(RESET)"
	@$(CXX) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	@echo "$(MODE)" > $(MODE_TRACE)

$(BUILD_DIR)%.o : $(SRCS_DIR)%.cpp
	@mkdir -p $(@D)
	@echo "$(BOLD)$(CXX) $(YELLOW)$(CXXFLAGS) $(CPPFLAGS) $(BLUE)-c $< $(CYAN)-o $@ $(RESET)"
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIBS_PATH): FORCE
	@$(MAKE) -C $(@D)

.PHONY : debug
debug :
	$(MAKE) MODE=debug

.PHONY : fsanitize
fsanitize :
	$(MAKE) MODE=fsanitize

.PHONY : clean
clean :
	rm -rf $(BUILD_DIR)

.PHONY : fclean
fclean :
	rm -rf $(MAKE_DIR) $(NAME)

.PHONY : re
re : fclean
	$(MAKE)

.PHONY : run
run : $(NAME)
	./$(NAME)

.PHONY : print-%
print-% :
	@echo $(patsubst print-%,%,$@)=
	@echo $($(patsubst print-%,%,$@))

.PHONY : FORCE
FORCE :
ifeq ($(ERROR),MODE)
	$(error Invalid mode: $(MODE))
endif

# *** FANCY STUFF ************************************************************ #

RESET	=	\e[0m
ERASE	=	\033[2K\r
BOLD	=	\033[1m
UNDER	=	\033[4m
SUR		=	\033[7m
GREY	=	\033[30m
RED		=	\033[31m
GREEN	=	\033[32m
YELLOW	=	\033[33m
BLUE	=	\033[34m
PURPLE	=	\033[35m
CYAN	=	\033[36m
WHITE	=	\033[37m
C12		=	\033[39m
C13		=	\033[43m

# **************************************************************************** #

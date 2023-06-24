CC     := gcc
CFLAGS  = -Wall -Wextra -Wpedantic -std=c11 -I./$(SRC_DIR)

DEBUG ?= no
ifeq ($(DEBUG), yes)
	CFLAGS += -O0 -g
	CONFIG := debug
	LIB_NAME = libcwtd.a
	LDFLAGS = -lcwtd
else
	CFLAGS += -O2
	CONFIG := release
	LIB_NAME = libcwt.a
	LDFLAGS = -lcwt
endif

SRC_DIR := src
BUILD_DIR := build
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(addprefix $(BUILD_DIR)/$(CONFIG), /$(SRCS:.c=.o))

SAMP_DIR := sample
SAMP_SRCS := $(wildcard $(SAMP_DIR)/*.c)
SAMPLES := $(addprefix build, /$(SAMP_SRCS:.c=))

AR := ar rc
RM := rm -rf

.PHONY: all sample clean

all: $(LIB_NAME)

$(LIB_NAME): $(OBJS)
	$(AR) $(BUILD_DIR)/$(CONFIG)/$(LIB_NAME) $^

$(BUILD_DIR)/$(CONFIG)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

sample: $(SAMPLES)

$(BUILD_DIR)/$(SAMP_DIR)/%: $(SAMP_DIR)/%.c $(LIB_NAME)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -L./$(BUILD_DIR)/$(CONFIG) $(LDFLAGS) -o $@

clean:
	$(RM) $(BUILD_DIR)

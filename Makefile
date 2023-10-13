CC     := gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -I$(SRC_DIR)

DEBUG ?= no
ifeq ($(DEBUG), yes)
	CFLAGS += -O0 -g
	CONFIG := debug
	LIB_NAME = libcwtd
else
	CFLAGS += -O2
	CONFIG := release
	LIB_NAME = libcwt
endif

SRC_DIR := src
BUILD_DIR := build/$(CONFIG)
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))

SAMP_DIR := sample
SAMP_SRCS := $(wildcard $(SAMP_DIR)/*.c)
SAMPLES := $(addprefix $(BUILD_DIR)/, $(SAMP_SRCS:.c=))

STATIC_LIB = $(BUILD_DIR)/$(LIB_NAME).a
SHARED_LIB = $(BUILD_DIR)/$(LIB_NAME).so

AR := ar rc
RM := rm -rf

.PHONY: all static shared sample clean

all: static

$(STATIC_LIB): $(OBJS)
	$(AR) $@ $^

static: $(STATIC_LIB)

$(SHARED_LIB): $(OBJS)
	$(CC) $(CFLAGS) -shared -fPIC $^ -o $@

shared: $(SHARED_LIB)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Build with -O0 to avoid shortening of processing times by optimization
$(BUILD_DIR)/$(SAMP_DIR)/%: $(SAMP_DIR)/%.c $(STATIC_LIB)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -O0 $^ -o $@ # O0

sample: $(SAMPLES)

clean:
	$(RM) $(BUILD_DIR)

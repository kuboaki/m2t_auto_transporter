mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS += \
auto_transporter.o \
line_tracer.o \
bumper.o \
line_monitor.o \
carrier.o \
drive_base.o \
wall_detector.o \
util.o

SRCLANG := c

# APPL_DIR += $(mkfile_path)app

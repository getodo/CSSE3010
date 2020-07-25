###################################################
# LIBRARY SOURCES
###################################################

# Set mylib folder path.
# IMPORTANT NOTE: change MYLIBTEMPLATE_PATH to your Driver name e.g. JOYSTICK_MYLIBPATH
# e.g. JOYSTICK_MYLIBPATH=/holme/csse3010/mylib/joystick
LTA1000G_PATH=/home/csse3010/csse3010/mylib/lta1000g

# Set folder path with header files to include.
CFLAGS += -I$(LTA1000G_PATH)

# List all c files locations that must be included (use space as separate e.g. LIBSRCS += path_to/file1.c path_to/file2.c)
LIBSRCS += $(LTA1000G_PATH)/s4353737_hal_lta1000g.c $(LTA1000G_PATH)/s4353737_os_lta1000g.c


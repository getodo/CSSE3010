###################################################
# LIBRARY SOURCES
###################################################

# Set mylib folder path.
# IMPORTANT NOTE: change MYLIBTEMPLATE_PATH to your Driver name e.g. JOYSTICK_MYLIBPATH
# e.g. JOYSTICK_MYLIBPATH=/holme/csse3010/mylib/joystick
PROJECT_MYLIBPATH=/home/csse3010/csse3010/mylib/project

# Set folder path with header files to include.
CFLAGS += -I$(PROJECT_MYLIBPATH)

# List all c files locations that must be included (use space as separate e.g. LIBSRCS += path_to/file1.c path_to/file2.c)
LIBSRCS += $(PROJECT_MYLIBPATH)/s4353737_os_CAG_Display.c $(PROJECT_MYLIBPATH)/s4353737_os_CAG_keypad_grid.c $(PROJECT_MYLIBPATH)/s4353737_hal_pb.c $(PROJECT_MYLIBPATH)/s4353737_os_CAG_Simulator.c $(PROJECT_MYLIBPATH)/s4353737_os_CAG_keypad_mnemonic.c $(PROJECT_MYLIBPATH)/s4353737_os_CAG_joystick.c


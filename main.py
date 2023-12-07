import pygame
import sys
import serial

pygame.init()

# Initialize the joystick module
pygame.joystick.init()

# Get the first connected joystick
joystick = pygame.joystick.Joystick(0)

# Initialize the joystick
joystick.init()

# Get the number of axes and buttons on the joystick
num_axes = joystick.get_numaxes()
num_buttons = joystick.get_numbuttons()
num_dpad = joystick.get_numhats()
print(num_dpad)


def send_data_to_arduino(data):
    ser = serial.Serial('COM5', 115200)
    ser.write(str(data).encode())
    ser.close()


# Loop until the user quits
while True:
    # Check for events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            # Quit the program
            pygame.quit()
            sys.exit()

    # Read the joystick axes
    for i in range(num_axes):
        axis = joystick.get_axis(i)
        if abs(axis * 100) > 20 and i < 4:
            # print (i)
            val = int(axis * 100)
            print(f"Axis XY {i}: {val}")
        elif axis * 100 > -95 and i >= 4 and not (axis * 100 == 0):
            val = int(axis * 100)
            # print (i)
            print(f"Axis Z {i}: {val}")

    # Read the joystick buttons
    for i in range(num_buttons):
        button = joystick.get_button(i)
        if button != 0:
            print(f"Button {i}: {button}")
            if i == 0:
                send_data_to_arduino(data='1')
            elif i == 3:
                send_data_to_arduino(data='2')
            elif i == 1:
                send_data_to_arduino(data='6')
            elif i == 2:
                send_data_to_arduino(data='4')
            elif i == 11:
                send_data_to_arduino(data='5')
            elif i == 12:
                send_data_to_arduino(data='8')
            elif i == 14:
                send_data_to_arduino(data='9')
            elif i == 13:
                send_data_to_arduino(data='7')
            else:
                send_data_to_arduino(data='0')
        if i == 15 and button == 1:
            pygame.quit()
            sys.exit()

    for i in range(num_dpad):
        dpad = joystick.get_hat(i)
        if not (dpad == (0, 0)):
            print(f"Dpad {i}: {dpad}")

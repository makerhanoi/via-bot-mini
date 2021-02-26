import cv2
from controller import send_control, calculate_control_signal


# TODO: Define control params
MAX_SPEED = 25
MIN_SPEED = 10
speed_limit = MAX_SPEED
current_speed = 0

while True:

    # TODO: Finish this part
    image = None  # BGR image

    # Calculate speed and steering angle
    throttle, steering_angle = calculate_control_signal(
        current_speed, image.copy())

    send_control(steering_angle, throttle)

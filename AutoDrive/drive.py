import urllib.request

import cv2
import numpy as np

from controller import calculate_control_signal, send_control
from config import CAM_URL

# TODO: Define control params
MAX_SPEED = 25
MIN_SPEED = 10
speed_limit = MAX_SPEED
current_speed = 0

stream = urllib.request.urlopen(CAM_URL)
bytes = bytes()

while True:

    bytes += stream.read(1024)
    a = bytes.find(b'\xff\xd8')
    b = bytes.find(b'\xff\xd9')

    if a != -1 and b != -1:
        image = bytes[a:b+2]
        bytes = bytes[b+2:]

        try:
            # Decode image
            image = cv2.imdecode(np.fromstring(
                image, dtype=np.uint8), cv2.IMREAD_COLOR)
            cv2.imshow('Image', image)

            # Calculate speed and steering angle
            steering = calculate_control_signal(
                current_speed, image.copy())

            send_control(steering)
        except:
            pass

        if cv2.waitKey(1) == 27:
            exit(0)

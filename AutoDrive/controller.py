import cv2
import numpy as np
import socket
from utils import *
from config import CONTROL_IP, CONTROL_PORT


MAX_ANGLE = 1
MAX_THROTTLE = 1
sk = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)

def send_control(steering):
    """Convert steering and throttle signals to a suitable format and send them to ESP32 bot"""

    steering = max(1, min(-1, steering))
    throttle = max(1, abs(steering) * 0.7 + 0.3)
    
    if steering > 0:
        left_motor_speed = throttle
        right_motor_speed = throttle * (1 - steering)
    else:
        left_motor_speed = throttle * (1 + steering) 
        right_motor_speed = throttle
    
    sk.sendto("{} {}".format(left_motor_speed, right_motor_speed).encode('ascii'), (CONTROL_IP, CONTROL_PORT))
    

def calculate_control_signal(current_speed, image):
    """Calculate control signal from image"""

    steering = 0
    left_point, right_point, im_center = find_lane_lines(image)
    if left_point != -1 and right_point != -1:

        # Calculate difference between car center point and image center point
        center_point = (right_point + left_point) // 2
        center_diff = center_point - im_center

        # Calculate steering angle from center point difference
        steering = float(center_diff * 0.01)

    return steering


def grayscale(img):
    """Convert image to grayscale"""
    return cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)


def canny(img, low_threshold, high_threshold):
    """Apply Canny edge detection"""
    return cv2.Canny(img, low_threshold, high_threshold)


def gaussian_blur(img, kernel_size):
    """Apply a Gaussian blur"""
    return cv2.GaussianBlur(img, (kernel_size, kernel_size), 0)


def birdview_transform(img):
    """Get birdview image"""

    IMAGE_H = 160
    IMAGE_W = 320

    src = np.float32([[0, IMAGE_H], [320, IMAGE_H], [
                     0, IMAGE_H//3], [IMAGE_W, IMAGE_H//3]])
    dst = np.float32([[90, IMAGE_H], [230, IMAGE_H],
                      [-10, 0], [IMAGE_W+10, 0]])
    M = cv2.getPerspectiveTransform(src, dst)  # The transformation matrix
    warped_img = cv2.warpPerspective(
        img, M, (IMAGE_W, IMAGE_H))  # Image warping
    return warped_img


def preprocess(img):
    """Preprocess image to get a birdview image of lane lines"""

    img = grayscale(img)
    img = gaussian_blur(img, 11)
    img = canny(img, 150, 200)
    img = birdview_transform(img)

    return img


def find_lane_lines(image, draw=False):
    """Find lane lines from color image"""

    image = preprocess(image)

    im_height, im_width = image.shape[:2]

    if draw:
        viz_img = cv2.cvtColor(image, cv2.COLOR_GRAY2BGR)

    # Interested line to determine lane center
    interested_line_y = int(im_height * 0.7)
    if draw:
        cv2.line(viz_img, (0, interested_line_y),
                 (im_width, interested_line_y), (0, 0, 255), 2)
    interested_line = image[interested_line_y, :]

    # Determine left point and right point
    left_point = -1
    right_point = -1
    lane_width = 100

    center = im_width // 2
    for x in range(center, 0, -1):
        if interested_line[x] > 0:
            left_point = x
            break
    for x in range(center + 1, im_width):
        if interested_line[x] > 0:
            right_point = x
            break

    # Predict occluded points
    if left_point != -1 and right_point == -1:
        right_point = left_point + lane_width
    if left_point == -1 and right_point != -1:
        left_point = right_point - lane_width

    if draw:
        if left_point != -1:
            viz_img = cv2.circle(
                viz_img, (left_point, interested_line_y), 7, (255, 255, 0), -1)
        if right_point != -1:
            viz_img = cv2.circle(
                viz_img, (right_point, interested_line_y), 7, (0, 255, 0), -1)

    if draw:
        return left_point, right_point, center, viz_img
    else:
        return left_point, right_point, center

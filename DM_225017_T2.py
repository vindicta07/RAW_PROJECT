# SFIT RAW PROJECT TASK 2
# Divyanshu Modi <divyan.m05@student.sfit.ac.in>

import cv2
import numpy as np

# Read image in OpenCV
input_img = cv2.imread("sample.jpg")
img = cv2.resize(input_img, (720, 720))

# Make a copy to draw contour outline
input_image_cpy = img.copy()
 
# Display input image
cv2.imshow('image', img)

# Convert RGB/BGR to HSV color space
hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

# define range of green color in HSV
lower = np.array([40, 20, 50])
upper = np.array([90, 255, 255])

# create a mask for green color
mask = cv2.inRange(hsv, lower, upper)
 
# Display filtered image
cv2.imshow('mask', mask)

contours, _ = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

# loop through the Green contours and draw a rectangle around them
for cnt in contours:
    contour_area = cv2.contourArea(cnt)
    if contour_area > 1000:
        x, y, w, h = cv2.boundingRect(cnt)
        cv2.rectangle(img, (x, y), (x + w, y + h), (0, 255, 0), 2)
        cv2.putText(img, 'Green', (x, y-10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0, 255, 0), 2)
 
# Display final output for color detection
cv2.imshow('image', img)
cv2.waitKey(0)
cv2.destroyAllWindows()

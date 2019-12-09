import serial
import cv2 as cv
import numpy as np
import math

# Open serial port
ser = serial.Serial("/dev/cu.usbmodem14102", 9600)

# Calibration of image pixels to read distance: 3.0875 pixel/cm
calibration = 3.0875
table = cv.imread("/Users/karenpoon/Pictures/idptable_non_distort2.jpg")
# table = cv.imread("/Users/karenpoon/Pictures/idp_table10.jpg")

# Crop table only
table = table[:, 35:773]
table_grey = cv.cvtColor(table, cv.COLOR_BGR2GRAY)
# Increase contrast of photo
table_enhanced = cv.equalizeHist(table_grey)
# [y direction, x direction]
# Crop to remove effect of noise
mine_area_enhanced = table_enhanced[:, 70:510]
mine_area_blurred = cv.medianBlur(mine_area_enhanced, 3)

# Threshold image
thresVal, thresh_mine_area = cv.threshold(mine_area_blurred, 10, 250, cv.THRESH_BINARY_INV)
# thresh_mine_area = cv.medianBlur(thresh_mine_area, 3)

# Dilate image
kernel = np.ones((5,5),np.uint8)
dilation = cv.dilate(thresh_mine_area,kernel,iterations = 1)
# cv.imshow("thresh", dilation)
# cv.waitKey(0)

# Find contours in image - mines
contours, hie = cv.findContours(dilation, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_SIMPLE)
blank_image = np.zeros(table.shape[:2], dtype="uint8") * 255
contours = contours[:]
cnts = []
# Remove contours with area below 2 and above 500
for cnt in contours:        
    area = cv.contourArea(cnt)   
    print(area)      
    if area > 2 and area < 500:  
        cnts.append(cnt)

areas = [cv.contourArea(c) for c in cnts]
# print("contour areas: " + areas)

dist_list = []
home_x = 584
home_y = 515

# Find centres of contours
for c in cnts:
    M = cv.moments(c)
    cx = int(M['m10']/M['m00']) + 70
    cy = int(M['m01']/M['m00'])
    print(cx, cy)
    cv.circle(table, (cx, cy), 7, (0, 0, 255), -1)
    dist = math.sqrt((abs(cx - home_x))**2 + abs((cy - home_y))**2)
    x_diff = home_x - cx
    calibrated_x = x_diff/calibration
    tup = (calibrated_x, dist)
    dist_list.append(tup)

# A list of perpendicular distances of mines from white line on the competition table
sorted_dist_list = sorted(dist_list, key=lambda x: x[1])
mine_dist = []  

for tup in sorted_dist_list:
    mine_dist.append(tup[0])

print(mine_dist)

cv.imshow("contours on table", table)
cv.waitKey(0)
cv.imwrite("mine_detection.jpg", table)

# Writing the perpendicular distances to arduino through serial
for mine_distance in mine_dist:
    mine_dist_serial = str(int(mine_distance)) + 'n'
    ser.write(mine_dist_serial.encode())

end = 'o'
ser.write(end.encode())

# while True:
#     if (ser.inWaiting()>0):  
#         data1= ser.readline().decode()
#         print(data1)
# print(ser.readline().decode())

ser.close()

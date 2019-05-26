import cv2
import serial

static_back = None
time = []

video = cv2.VideoCapture(0)
y=0

while True:
        check, frame = video.read()
        motion = 0

        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        gray = cv2.GaussianBlur(gray,(21,21),0)
        if static_back is None:
                static_back = gray
                continue
        diff_frame = cv2.absdiff(static_back, gray)
        thresh_frame = cv2.threshold(diff_frame, 30, 255, cv2.THRESH_BINARY)[1]
        thresh_frame = cv2.dilate(thresh_frame, None, iterations = 2)


#        print len(diff_frame)
        # Finding contour of moving object
        (_, cnts, _) = cv2.findContours(thresh_frame.copy(), 
                                        cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        a=[]

        for contour in cnts:
                if cv2.contourArea(contour) < 10000:
                        
                        continue
                motion = 1
                (x, y, w, h) = cv2.boundingRect(contour)
                cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 5)
                cx=x+(w/2)
                cy=y+(h/2)
                a.append([cx,cy])
        print len(a)
        if len(a)>0:
                        ser=serial.Serial("COM8",115200)
                        print(ser)
                        ser.write('Y')
                        ser.close()
        else:
                        ser=serial.Serial("COM8",115200)
                        print(ser)
                        ser.write('t')
                        ser.close()


                
        a=[]


 #       cv2.imshow("Gray Frame", gray)

  #      cv2.imshow("Difference Frame", diff_frame)

        cv2.imshow("Threshold Frame", thresh_frame)

        cv2.imshow("Color Frame", frame)

        key = cv2.waitKey(1)
        if key == ord('q'):
                break


video.release()

# Destroying all the windows
cv2.destroyAllWindows()

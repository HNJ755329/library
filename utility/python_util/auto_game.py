#!/usr/bin/python3
import pyautogui
import time
import keyboard

if __name__=="__main__":
    __x = 1850
    __y = 950
    pyautogui.click(x=__x,y=__y)
    while(1):
        # print(pyautogui.position())
        # pyautogui.dragRel(0,0,1,button='left')
        # pyautogui.mouseDown(__x, __y)
        # time.sleep(0.01)
        # pyautogui.mouseUp()
        # time.sleep(0.5)
        # print("click")
        X,Y = pyautogui.position()
        print(X,Y)
        if X>2500:
            break
        # if keyboard.is_pressed('q'):
        #     break


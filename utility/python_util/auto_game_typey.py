#!/usr/bin/python3
import pyautogui
import time
import keyboard
import threading

def print_pos():
    while(1):
        print(pyautogui.position())

def everysec_press():
    while(1):
        # pyautogui.dragRel(0,0,1,button='left')
        # pyautogui.press('b')
        pyautogui.press(' ')
        time.sleep(0.05)
        # time.sleep(0.5)
        # if X>1900:
        #     break
        print('press')
        if keyboard.is_pressed('q'):
            return

def everysec_click():
    while(1):
        pyautogui.click()
        time.sleep(0.01)
        print('click')
        if keyboard.is_pressed('q'):
            return


def everymin():
    n = 35
    while(1):
        # n+=0.1
        pyautogui.press('p')
        for i in range(n):
            time.sleep(1)
            print(i)
            if keyboard.is_pressed('q'):
                return

if __name__=="__main__":
    # __x = 1850
    # __y = 950b b b
    # pyautogui.click(x=__x,y=__y)

    # t1 = threading.Thread(target=everysec_press)
    # t2 = threading.Thread(target=everysec_click)
    # t3 = threading.Thread(target=everymin)
    # スレッドスタート
    # t1.start()
    # t2.start()
    # t3.start()
    print_pos()
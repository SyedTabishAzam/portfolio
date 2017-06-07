import turtle
import tkinter
import threading
from tkinter import *
tk = tkinter.Tk()

def kochCurve(length, depth):
    turtle.speed(0)
    if (depth == 0):
        turtle.forward(length)
    else:
        kochCurve(length/3.0, depth-1)
        turtle.right(60)
        kochCurve(length/3.0, depth-1)
        turtle.left(120)
        kochCurve(length/3.0, depth-1)
        turtle.right(60)
        kochCurve(length/3.0, depth-1)

def kochSnowflake(length, recursionDepth):
    turtle.screensize(2000,1500)
    step = 3
    turtle.penup()
    turtle.goto(-120, -50)
    turtle.setheading(0)
    turtle.pendown()
    turtle.delay(0)
    turtle.speed(0)
    turtle.color('red')
    turtle.fillcolor('pink')
    turtle.begin_fill()
    while step > 0:
        kochCurve(length,recursionDepth)
        turtle.left(120)
        step = step - 1
    turtle.end_fill()

import math

mainloop()

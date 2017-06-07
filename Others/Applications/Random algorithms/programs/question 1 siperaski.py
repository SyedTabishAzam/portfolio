import turtle
import tkinter
from tkinter import *
tk = tkinter.Tk()

def maketriangle(points,color,ta):
    ta.fillcolor(color)
    ta.up()
    ta.goto(points[0])
    ta.down()
    ta.begin_fill()
    ta.goto(points[1])
    ta.goto(points[2])
    ta.goto(points[0])
    ta.end_fill()

def middle(c1,c2):
    return ( (c1[0]+c2[0]) / 2, (c1[1] + c2[1]) / 2)

def sierpinskipart2(points,x,ta):
    colormap = ['blue','white','green','purple','yellow','violet','orange','yellow','green']
    maketriangle(points,colormap[x],ta)
    if x > 0:
        sierpinskipart2([points[0],middle(points[0], points[1]),middle(points[0], points[2])],x-1, ta)
        sierpinskipart2([points[1],middle(points[0], points[1]),middle(points[1], points[2])],x-1, ta)
        sierpinskipart2([points[2],middle(points[2], points[1]),middle(points[0], points[2])],x-1, ta)

def sierpinski(x):
   ta = turtle.Turtle()
   myPoints = ([-100,-50],[100,-50],[0,100])
   sierpinskipart2(myPoints,x,ta)

mainloop()

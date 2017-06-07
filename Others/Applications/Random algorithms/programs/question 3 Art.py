import turtle
import math

def drawArt(x):
    colors = ['green', 'yellow', 'blue']
    window = turtle.Screen()
    window.bgcolor(0, 0, 0)
    tabishgraphic = turtle.Turtle()
    tabishgraphic.pensize(4)
    tabishgraphic.speed(0)
    for outercircle in range(x+1):
        tabishgraphic.left(90)
        tabishgraphic.speed(0)
        window.colormode(255)
        tabishgraphic.pencolor(215,  180- outercircle*10, outercircle*30)
        for innercircles in range(20*outercircle):
            tabishgraphic.forward(10)
            tabishgraphic.pensize(50.0/(innercircles+1))
            tabishgraphic.left(-math.cos(math.pi)*innercircles*2/outercircle)
        tabishgraphic.penup()
        tabishgraphic.home()
        tabishgraphic.pendown()
        tabishgraphic.right(-30*outercircle)
    tabishgraphic.penup()
    tabishgraphic.home()
    for outercircle in range(x+1):
        tabishgraphic.left(90)
        tabishgraphic.speed(0)
        window.colormode()
        tabishgraphic.pencolor(215, 185 - outercircle*10, outercircle*30)
        for innercircles in range(20*outercircle):
            tabishgraphic.forward(10)
            tabishgraphic.pensize(50.0/(innercircles+1))
            tabishgraphic.left(math.cos(math.pi)*innercircles*2/outercircle)
        tabishgraphic.penup()
        tabishgraphic.home()
        tabishgraphic.pendown()
        tabishgraphic.left(-30*outercircle)
    tabishgraphic.penup()
    tabishgraphic.home()
    tabishgraphic.pendown()
    tabishgraphic.right(90)
    tabishgraphic.pensize(8)
    tabishgraphic.forward(500)
    window.exitonclick()


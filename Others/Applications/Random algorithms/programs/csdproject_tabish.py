import turtle as t
import math

###----drawing one, without colors----###
def d2(rad):
    t.speed(0)
    t.circle(rad)
    t.setheading(90)
    t.up()
    t.forward(rad/2)
    t.setheading(0)
    t.down()
    t.circle(rad/2)
    t.setheading(90)
    t.penup()
    t.forward(rad/2)
    t.pendown()
    
    
    for i in range(0, 6):
        
        t.begin_fill()
        t.circle(rad/2)
        t.left(60)
        
###---drawing one, with colors---##     
def d2a(rad):
    t.pensize(1.5)
    t.pu()
    t.goto(0,0)
    t.setheading(0)
    t.pendown()
    t.speed(0)
    t.pencolor("white")
    t.fillcolor("black")
    t.begin_fill()
    t.circle(rad)
    t.end_fill()
    t.setheading(90)
    t.up()
    t.forward(rad/2)
    t.setheading(0)
    t.down()
    t.pencolor("black")
    t.circle(rad/2)
    t.setheading(90)
    t.penup()
    t.forward(rad/2)
    t.pendown()
    color = ["orange","#9a9693","orange","#9a9693","orange","#9a9693"]
    for i in range(0, 6):
        t.fillcolor(color[i])
        t.begin_fill()
        t.circle(rad/2)
        t.left(60)
        t.end_fill()
    for y in range(0,3):
        for z in range(0,2):  
            t.pencolor("black")
            t.fillcolor("white")
            t.begin_fill()
            t.circle(50,60)
            t.right(120)
            semi(60,50)
            t.left(240)
            t.circle(50,60)
##            t.end_fill()
        t.right(60)
    
    t.pu()
    t.forward(50)
    t.setheading(0)
    t.pendown()
    t.fillcolor("black")
    
    t.circle(50,30)
    
    for o in range(0,6):
##        t.begin_fill()
        t.right(120)
        semi(60,50)
        t.right(60)
        semi(60,50)
        t.right(120)
        t.circle(50,60)
##        t.end_fill()
        t.speed(2)
        t.circle(50,60)
    
        
###---drawing two---###
def d3(rad):
    t.speed(0)
    t.pencolor("orange")
    t.circle(rad)
    if rad == 50:
        colors = ["orange","black"]
    else:
        colors = ["orange","#9a9693"]
    t.fillcolor("#9a9693")
    t.begin_fill()
    drawtriangle(rad)
    t.end_fill()
    for x in range(0,2):
        
        t.penup()
        t.circle(rad,40)
        t.pendown()
        t.fillcolor(colors[x])
        t.begin_fill()
        drawtriangle(rad)
        t.end_fill()


###---drawing three---##
def d4(rad):
   
    t.speed(0)
    t.pencolor("orange")
    t.circle(rad)
    if rad==50:
        color= [ "orange","#9a9693","orange","black"]
    else:
        color= [ "orange","#9a9693","orange","#9a9693"]
    for i in range(0,4):
        t.fillcolor(color[i])
        t.left(45)
        t.begin_fill()
        drawsquare(rad)
        t.end_fill()
        t.right(45)
        if i <3:
            t.pu()
            t.circle(rad,21)
            t.down()


###----drawing 4, combining all three drawings---### 
def combined():
    t.bgcolor("black")
    d2a(100)
    t.pu()
    t.goto(0,100)
    
    t.penup()
    t.setheading(270)
    t.circle(50,360/4)
    d3(50)
    rad = 50
    for i in range(0,2):
        t.penup()
        t.circle(rad,40/2)
        rad = rad + 50
        t.setheading(0)
        t.forward(rad)
        t.setheading(270)
        t.forward(rad)
        t.setheading(0)
        t.pendown()
        d3(rad)
    rad = 50
    t.penup()
    t.goto(0,100)
    t.setheading(90)
    t.circle(50,270)
    t.setheading(0)
    t.pendown()
    d4(rad)
    for x in range(0,2):
        t.penup()
        t.circle(rad,27)
        t.setheading(180)
        t.forward(rad*2)
        rad = rad + 50
        t.forward(rad)
        t.setheading(270)
        t.forward(rad)
        t.setheading(0)
        t.pendown()
        d4(rad)
    
    
###---helping functions---### 
def semi(z=360,r=10):
    t.speed(0)
    for x in range(0,int(z)):
        t.right(1)
        t.forward( (r*2) * math.pi / 360 )
##        
def drawsquare(radoc):
    import math
    y = math.sqrt(((radoc * 2)**2)/2)
    t.forward(y)
    t.left(90)
    t.forward(y)
    t.left(90)
    t.forward(y)
    t.left(90)
    t.forward(y)
    t.left(90)

def drawtriangle(rad):
    t.speed(0)
    t.left(120)
    t.forward((rad*(6/math.sqrt(3))/2))
    t.left(240)
    t.forward((rad*(6/math.sqrt(3))/2))
    t.left(240)
    t.forward((rad*(6/math.sqrt(3))/2))
    t.left(120)

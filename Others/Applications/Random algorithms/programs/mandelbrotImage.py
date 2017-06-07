from PIL import Image, ImageDraw, ImageColor
import random
im = Image.new("RGB", (256,256))
draw = ImageDraw.Draw(im)

def inside(z):
    '''(complex) -> NoneType

    Shades the pixel corresponding to z to indicate its membership in
    the Mandelbrot set..
    '''

    # Shade pixel white.
    x = (z.real - -2) * 2**6
    y = (z.imag - -2) * 2**6
    draw.point([x, y],"black")

def escapes(z, time):
    '''(complex, int) -> NoneType

    Shades the pixel corresponding to z with a color determined by
    time, to indicate that z escapes the Mandelbrot set.
    '''
    if time < 0 or time > 1:
        return

    # Compute pixel.
    x = (z.real - -2) * 2**6
    y = (z.imag - -2) * 2**6
    # Shade pixel.
    draw.point([x, y], getColor(time))

def getColor(val):
    '''(float) -> (int, int, int)

    Returns a rgb tuple representing the color for val. 0 <= val <= 1.

    val \in [0,0.15] -> Interpolate uniformly between Red and Green.
    val \in (0.15,1,0] -> Interpolate uniformly between Green and Blue.
    '''
    if val <= 0.15:
        # Interpolate between RED {1,0,0} and GREEN {0,1,0}.
        extent = val / 0.15
        green = int(extent*255); 
        return (255 ^ green, green, 0)
    else:
        # Interpolate between GREEN {0,1,0} and BLUE {0,0,1}.
        extent = (val - 0.15) / 0.85;
        blue = int(extent*255); 
        return (0, 255 ^ blue, blue)
    
def show():
    '''
    Display the image.
    '''
    im.show()

def clear():
    '''
    Reset image to black.
    '''
    draw.rectangle([0, 0, 256, 256], "black")

def save(fname):
    '''
    Save image to fname.
    '''
    im.save(fname)




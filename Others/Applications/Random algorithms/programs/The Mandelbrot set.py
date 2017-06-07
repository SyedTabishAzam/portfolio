def escapetime(n,c):
    z = complex(0,0)
    count = 0
    maxcount = n
    while (abs(z)<2) and (count < maxcount):
        zreal = (z.real**2) - (z.imag**2) + c.real
        zimag = 2 * z.real * z.imag + c.imag
        z=complex(zreal,zimag)
        count = count + 1

    if (count == maxcount):
        return -1
    else:
        return "Escape at N=" + str(count)

def inMandelBrot(n,c):
    z = complex(0,0)
    count = 0
    maxcount = n
    while (abs(z)<2) and (count < maxcount):
        zreal = (z.real**2) - (z.imag**2) + c.real
        zimag = 2 * z.real * z.imag + c.imag
        z=complex(zreal,zimag)
        count = count + 1

    if (count == maxcount):
        return True
    else:
        print(abs(z))
        return False

def visualzieMandelbrot(specified):
    import mandelbrotImage
    
    xa = -2.0       ## sets lower x limit
    xb = 2.0        ## sets positive x limit
    ya = -2.0       ## sets negative y limit
    yb = 2.0        ## sets positive y limit
    imgx = 256      ## specifies horizontal image size
    imgy = 256      ## specifies vertical image size
    i=0
    for y in range(imgy): ## starting from y = 0 to y = 255
       cy = y * (yb-ya)/(imgy - 1) + ya     ##generating random value of cy between -2 and 2
       for x in range(imgx):                ## starting a loop from x = 0 to x = 255 for every y
            cx = x * (xb - xa) /(imgx - 1) + xa     ##generating random value of cx between -2 and 2
            c = complex(cx,cy)              ## makking ct as imaginery axis and cx as real axis (making a complex number)
            z = 0                           ## defining starting value of z (since z0 = 0)
            for i in range(specified):    ## checking zn where n = range specified in function
                if abs(z) > 2.0:            ## if the modulus of z reaches greater than 2.0, the function breaks the loop
                    break 
                else:
                    z = z * z + c           ## else the function keeps on adding square of z + c to previous "z"
            if abs(z)>2:                    ## checks if the function has escaped to infinity
                mandelbrotImage.escapes(c,i/(specified))  ## add points of c in a graph and color them accordingly
         
               
    mandelbrotImage.show()                  ##shows the final output on BMP format

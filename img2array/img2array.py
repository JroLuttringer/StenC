from PIL import Image

photo = Image.open('img_in') #your image
photo = photo.convert('RGB')

width = photo.size[0] #define W and H
height = photo.size[1]

print "tab={",

for y in range(0, height): #each pixel has coordinates
    row = ""
    print("{"),
    for x in range(0, width):
        R,G,B = photo.getpixel((x,y))
        print("{0}".format(R)),
	if (x+1 < width) :
		print",",
    print("}"), 
    if (y+1 < height) :
        print",",

print "};",

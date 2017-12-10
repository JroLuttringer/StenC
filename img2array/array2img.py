from PIL import Image


from PIL import Image

photo = Image.open('out.tif') #your image
photo = photo.convert('L')

width = photo.size[0] #define W and H
height = photo.size[1]

with open("out.img") as f:
    data = f.read()
    pixels = data.split(",")

new_pix = photo.load()
for x in range(0, width): #each pixel has coordinates
    row = ""
    for y in range(0, height):
        new_pix[x,y] = pixels[64*x+y]
im.save("out.tif")
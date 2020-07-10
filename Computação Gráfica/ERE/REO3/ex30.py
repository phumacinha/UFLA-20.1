from math import sqrt, pow, degrees, atan

pixels = list()

x0, y0 = map(int, input().split())
x1, y1 = map(int, input().split())

dx = x1 - x0
dy = y1 - y0

c = sqrt(pow(dx, 2) + pow(dy, 2))
angulo = degrees(atan(dy/dx))
print('comprimento: {} e angulo: {}°'.format(c, angulo))

d = 2*dy - dx
delta_e = 2*dy
delta_ne = 2*(dy - dx)

x = x0
y = y0

pixels.append((x,y))

while x < x1:
    if d <= 0:
        d = d + delta_e
    else:
        d = d + delta_ne
        y = y + 1
    x = x + 1
    pixels.append((x,y))

print('Pixels selecionados:', end=' ')
for pixel in pixels:
    print(pixel, end=' ')
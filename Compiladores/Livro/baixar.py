import time
import base64
from selenium import webdriver
from PIL import Image
from io import BytesIO

driver = webdriver.Chrome('./chromedriver')  # Optional argument, if not specified will search path.
driver.get('https://plataforma.bvirtual.com.br/Leitor/Publicacao/280/pdf/0?code=86BZaiplTZKykQZjnXO15vo8BTw58DI5RY6RRL5cHVGbbRHja3VEYnTwLDg0/D8tQ5iEJuWPZHIjaCIfSpafuw==');
continuar = input("Pressione enter para fazer login.")
driver.find_element_by_id('UserName').send_keys('11587306670')
driver.find_element_by_id('Password').send_keys('Galo.doido13')
driver.find_element_by_id('Password').submit()

continuar = input("Pressione enter para salvar.")
time.sleep(3)
imageList = list()
for i in range(228, 274):
    print('Imagem {}...'.format(i))
    canvas = driver.find_element_by_id('page-canvas')
    # get the canvas as a PNG base64 string
    canvas_base64 = driver.execute_script("return arguments[0].toDataURL('image/png').substring(21);", canvas)
    time.sleep(.2)
    # decode
    canvas_png = base64.b64decode(canvas_base64)

    # save to a file
    im = Image.open(BytesIO(canvas_png))
    im = im.crop(im.getbbox())
    imageList.append(im.convert('RGB'))

    botao_proxima = driver.find_element_by_id('right-control').click()
    time.sleep(.2)
    carregando = driver.find_elements_by_class_name('loading-cicle__center')[0].value_of_css_property("display")
    while carregando != 'none':
        carregando = driver.find_elements_by_class_name('loading-cicle__center')[0].value_of_css_property("display")
    
    time.sleep(.2)

print('-----\nSalvando PDF...')
im1 = imageList.pop(0)
im1.save('Livro.pdf', save_all=True, append_images=imageList)
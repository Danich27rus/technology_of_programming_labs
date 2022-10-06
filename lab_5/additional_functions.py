import cv2
import os
import glob
import numpy as np
import matplotlib.pyplot as plt
from skimage import transform
from PIL import Image

TRAINING_DIR = 'АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ'
NAME_ROOT_ALL_PATH = 'C:/Users/grigh/OneDrive/Документы/chars74k/Cyrillic/'


def make_background():
    for letter in glob.glob('Cyrillic/*'):
        i = 0
        for image in glob.glob(letter + '/*'):
            png = Image.open(image).convert('RGBA')
            background = Image.new('RGBA', png.size, (255, 255, 255))

            test = letter.split('\\')
            alpha_composite = Image.alpha_composite(background, png)
            alpha_composite.save(NAME_ROOT_ALL_PATH + test[1] + '/{}_{}.png'.format(letter.split('\\')[1], i),
                                 'PNG', quality=80)
            im = Image.open(NAME_ROOT_ALL_PATH + test[1] + '/{}_{}.png'.format(letter.split('\\')[1], i))
            rgb_im = im.convert('RGB')
            rgb_im.save(NAME_ROOT_ALL_PATH + test[1] + '/{}_{}.jpg'.format(letter.split('\\')[1], i))
            i += 1


def rotate():
    for letter in glob.glob('Cyrillic/*'):
        i = 0
        for image in glob.glob(letter + '/*'):
            img = plt.imread(image)
            test = letter.split('\\')
            angles = np.ndarray((2,),
                buffer=np.array([-13, 13]), dtype=int)
            for angle in angles:
                transformed_image = transform.rotate(np.array(img),
                    angle, cval=255, preserve_range=True).astype(np.uint8)
                plt.imsave(NAME_ROOT_ALL_PATH + test[1] +
                            '/{}_{}_{}.jpg'.format(letter.split('\\')[1], i, str(angle)), transformed_image)
            i += 1


def shift():
    for letter in glob.glob('Cyrillic/*'):
        k = 0
        p = 0
        for image in glob.glob(letter + '/*'):
            img = plt.imread(image)
            test = letter.split('\\')
            arr_translation = [[15, -15], [-15, 15], [-15, -15],
                    [15, 15]]
            #arr_caption = ['15-15', '-1515', '-15-15', '1515']
            for i in range(4):
                transform_b = transform.AffineTransform(translation=tuple(arr_translation[i]))
                warp_image = transform.warp(img, transform_b, mode="wrap")
                img_convert = cv2.convertScaleAbs(warp_image, alpha=(255.0))
                wrapper = NAME_ROOT_ALL_PATH + test[1] +'/{}_{}_shift_{}_{}.jpg'.format(letter.split('\\')[1], i, p, k)
                plt.imsave(wrapper, img_convert)
            k += 1
            p += 1


def delete_png():
    for letter in glob.glob('Cyrillic/*'):
        png = glob.glob(letter + '/*.png')
        for name in png:
            os.remove(name)


def balancing():
    arr_len_files = []
    for path in TRAINING_DIR:
        name_path = NAME_ROOT_ALL_PATH+path+'/'
        files = os.listdir(name_path)
        arr_len_files.append(len(files))

    min_value=min(arr_len_files)
    for path in TRAINING_DIR:
        folder = NAME_ROOT_ALL_PATH+path
        arr = []
        for the_file in os.listdir(folder):
            arr.append(folder + '/' + the_file)
        d = 0
        k = len(arr)
        for i in arr:
            os.remove(i)
            d += 1
            if d == k - min_value:
                break


if __name__ == '__main__':
    #balancing()
    #make_background()
    #delete_png()
    rotate()
    shift()

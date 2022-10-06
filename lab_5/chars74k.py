import glob
import numpy as np
import random
import cv2
from matplotlib.image import imread
from matplotlib.pyplot import imshow
from sklearn.model_selection import train_test_split
from tensorflow.keras.layers import Activation, Convolution2D, Dense, Dropout, Flatten, MaxPooling2D
from tensorflow.keras.models import Sequential, load_model
from tensorflow.keras.preprocessing import image as tf_img


SAMPLES = 166000  ##всего примеров
CHARS = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"  ##возможные варианты
ROWS = 30
COLS = 30
'''Размер картинки в пикселях'''


def main():
    images = np.zeros(shape=(SAMPLES, ROWS, COLS, 3))
    '''
    Образует вложенные кортежи по схеме:
                    3 числа
                      |
                      V 
                    12 котрежей в 3 числа
                          |
                          V 
                    18 кортежей по 12
                           |
                           V
                    7700 котржей по 18'''
    labels = np.zeros(shape=(SAMPLES,), dtype=int)
    sample_num = 0
    for sample in sorted(glob.glob('Cyrillic/*')):
        for image in glob.glob(sample + '/*'):
            images[sample_num] = cv2.resize(imread(image), dsize=(COLS, ROWS))
            '''Открывает картинку и ресайзит её до размера 20x20'''
            labels[sample_num] = ord(sample[-1]) - 1040
            '''Маркеры для dense слоя'''
            sample_num += 1
    '''glob.glob - рекурсивный отбор файлов (типа ключа -r как я понял в Linuxе)'''

    # ВСЁ ЧТО ВЫШЕ - ПЕРЕВОД КАРТИНОК В МАССИВ, НЕОБХОДИМЫЙ ДЛЯ НЕЙРОСЕТИ
    images, images_test, labels, labels_test = train_test_split(images, labels, test_size=0.2)
    '''Разделение датасета для обучения и тестирования'''

    print(f'{images.shape[0]} sample images of size {images.shape[1]}x{images.shape[2]}')
    print(f'{labels.shape[0]} labels')
    assert images.shape[0] == labels.shape[0]
    # Проверка на совпадение

    layers = \
        [Convolution2D(30, 3, 3, input_shape=(ROWS, COLS, 3), activation='relu')
            , Convolution2D(64, 2, 1, activation='relu')
            , Convolution2D(32, 2, 1, activation='relu')
            , MaxPooling2D(pool_size=(2, 2))
            , Flatten()
            , Dense(512, activation='relu')
            , Dropout(0.5)
            , Dense(256, activation='relu')
            , Dropout(0.5)
            , Dense(33)
            , Activation('softmax')
         ]
    '''Тут и извлечение признаков, и создание слоёв из глубины, и активация
       Короче вся магия ML
       
       Dropout - слой для предотвращения переобучения, который случайным образом 
       устраняет соединения между слоями (0,5 означает, что он отбрасывает 50% существующих соединений)
       
       Flatten - сжатие
       
       Softmax выбирает нейрон с наибольшей вероятностью в качестве своего выходного значения, 
       предполагая, что изображение принадлежит именно этому классу'''

    model = Sequential()
    '''Сверточный слой. Он будет принимать входные данные и пропускать их через сверточные фильтры.'''
    for layer in layers:
        model.add(layer)

    model.summary()
    model.compile(loss='sparse_categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
    '''
    loss - потеря
    
    у нас 
    sparse_categorical_crossentropy - Computes the crossentropy loss between the labels and predictions
    Вычисляет потерю межжду метками и предугадываниями.
    
    Adam - adaptive moment estimation, оптимизационный алгоритм. 
    Он сочетает в себе и идею накопления движения и идею более слабого обновления весов для типичных признаков.
    
    В статье очень много весёлого матана и описание других алгоритмов оптимизации
    
    https://habr.com/ru/post/318970/
    '''
    model.fit(images, labels, epochs=40, batch_size=64, validation_data=(images_test, labels_test))
    '''fit - самообучение модели'''
    model.save("ciril_model.h5")

    predictions = model.predict(images_test)
    for _ in range(10):
        i = random.randint(0, images_test.shape[0])
        print('\nselected a random image')
        imshow((images_test[i] * 255).astype(np.uint8))
        print('prediction:', CHARS[np.argmax(predictions[i])])
        chance = predictions[i][np.argmax(predictions[i])]
        print('confidence: {:0.2f}%'.format(chance * 100))
        print('actual:', CHARS[labels_test[i]])


def print_letter(result):
    return CHARS[result]


def showcase():
    image = tf_img
    model = load_model('ciril_model.h5')

    img = image.load_img('C:/Users/grigh/OneDrive/Документы/chars74k/letter_test.jpg', target_size=(30, 30))
    x = image.img_to_array(img)
    x = np.expand_dims(x, axis=0)
    images = np.vstack([x])
    classes = model.predict(images, batch_size=4)
    result = int(np.argmax(classes))
    result = print_letter(result)
    print(result)


if __name__ == '__main__':
    #main()
    showcase()

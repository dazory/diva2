#!/usr/bin/env python
# coding: utf-8

# In[1]:
## Import Libraries

from tensorflow.keras.layers import Conv2D, MaxPool2D, Dropout, UpSampling2D, Input, Lambda, Conv2DTranspose, concatenate
from classification_models.tfkeras import Classifiers
from tensorflow.keras.models import Sequential
from tensorflow.keras import Model

import numpy as np
import time
import cv2
import os

def make_fcn_model(IMG_HEIGHT, IMG_WIDTH):
    b = 2
    i = Input((IMG_HEIGHT, IMG_WIDTH, 3))
    # s = Lambda(lambda x: preprocess_input(x)) (i)
    c1 = Conv2D(2**b, (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (i)
    c1 = Conv2D(2**b, (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (c1)
    c1 = Conv2D(2**b, (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (c1)
    p1 = MaxPool2D((2, 2)) (c1)

    c2 = Conv2D(2**(b+1), (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (p1)
    c2 = Conv2D(2**(b+1), (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (p1)
    c2 = Dropout(0.1) (c2)
    c2 = Conv2D(2**(b+1), (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (c2)
    p2 = MaxPool2D((2, 2)) (c2)

    c3 = Conv2D(2**(b+2), (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (p2)
    c3 = Conv2D(2**(b+2), (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (p2)
    c3 = Dropout(0.2) (c3)
    c3 = Conv2D(2**(b+2), (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (c3)

    p3 = MaxPool2D((2, 2)) (c3)

    c4 = Conv2D(2**(b+3), (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (p3)
    c4 = Conv2D(2**(b+3), (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (p3)
    c4 = Dropout(0.2) (c4)
    c4 = Conv2D(2**(b+3), (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (c4)

    p4 = MaxPool2D(pool_size=(2, 2)) (c4)

    c5 = Conv2D(2**(b+4), (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (p4)
    c5 = Conv2D(2**(b+4), (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (p4)
    c5 = Dropout(0.3) (c5)
    c5 = Conv2D(2**(b+4), (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (c5)
    c5 = Conv2D(2**(b+4), (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (c5)

    u6 = Conv2DTranspose(2**(b+3), (2, 2), strides=(2, 2), padding='same') (c5)
    u6 = concatenate([u6, c4])
    c6 = Conv2D(2**(b+3), (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (u6)
    c6 = Dropout(0.2) (c6)
    c6 = Conv2D(2**(b+3), (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (u6)
    c6 = Conv2D(2**(b+3), (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (c6)

    u7 = Conv2DTranspose(2**(b+2), (2, 2), strides=(2, 2), padding='same') (c6)
    u7 = concatenate([u7, c3])
    c7 = Conv2D(2**(b+2), (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (u7)
    c7 = Conv2D(2**(b+2), (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (u7)
    c7 = Dropout(0.2) (c7)
    c7 = Conv2D(2**(b+2), (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (c7)

    u8 = Conv2DTranspose(2**(b+1), (2, 2), strides=(2, 2), padding='same') (c7)
    u8 = concatenate([u8, c2])
    c8 = Conv2D(2**(b+1), (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (u8)
    c8 = Conv2D(2**(b+1), (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (u8)
    c8 = Dropout(0.1) (c8)
    c8 = Conv2D(2**(b+1), (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (c8)

    # u9 = Conv2DTranspose(2**b, (2, 2), strides=(2, 2), padding='same') (c8)
    # u9 = concatenate([u9, c1], axis=3)
    # c9 = Conv2D(2**b, (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (u9)
    # c8 = Conv2D(2**(b+1), (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (u8)
    # c9 = Conv2D(2**b, (3, 3), activation='relu', kernel_initializer='he_normal', padding='same') (c9)

    o = Conv2D(1, (1, 1), activation='sigmoid') (c8)

    model = Model(inputs=i, outputs=o)
    return model


test_model = make_fcn_model(144, 400)
test_model.summary()


with open('./checkpoints/fcn_big_01.json', 'w') as model_file:
    model_file.write(test_model.to_json())

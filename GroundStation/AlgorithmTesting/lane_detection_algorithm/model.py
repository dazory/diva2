#!/usr/bin/env python
# coding: utf-8

# Install Python ZeroMQ Module : pip install pyzmq
# Install Python Protobuf Module : pip install protobu

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

import matplotlib.pyplot as plt
import imageio

import zmq
import sys
# sys.path.append(os.path.dirname(os.path.abspath(os.path.dirname(__file__))))
# sys.path.append(os.path.dirname(os.path.abspath("../../../protobuf")))
# from . import sensor_pb2
from pathlib import Path
#p = Path(__file__).parents[3]
#p = p / 'protobuf/'
sys.path.append(os.path.abspath('/home/diva2/diva2/protobuf'))
print(sys.path)
import sensors_pb2

# In[2]:
## Define a Function to Count a Time Interval

def millis():
    return int(time.time() * 1000)


# In[3]:
## Communicate using ZeroMQ

port = 9899
context = zmq.Context()
socketPub = context.socket(zmq.PUB)
socketPub.bind("tcp://*:%s" % port)


# In[4]:
## Get Model

from tensorflow.keras.models import model_from_json

# model_path = './checkpoints/fcn_big_01.json'
model_path = sys.argv[1]
with open(model_path, 'r') as model_file:
    test_model = model_from_json(model_file.read())
# test_model.summary()


# In[6]:
## Get Weights 
# test_model.load_weights('/home/diva2/diva2/GroundStation/AlgorithmTesting/lane_detection_algorithm/checkpoints/fcn_big_01.h5')
test_model.load_weights(sys.argv[2])


# In[8]:
## Load Test Images
# test_folder = '/home/diva2/diva2/GroundStation/AlgorithmTesting/lane_detection_algorithm/training_images/'
test_folder = sys.argv[3] + '/' # './training_images/'
algoImg = sensors_pb2.algorithm_img()

# test_folder = './training_images/'
from PIL import Image
dirs = os.listdir( test_folder )
dirs.sort()
x_train=[]
def load_dataset():
    cnt = 0
    # Append images to a list
    for item in dirs:
        cnt = cnt + 1
        if os.path.isfile(test_folder+item):
            im = Image.open(test_folder+item).convert("RGB")
            # print(im.width, im.height)
            im = im.resize((400, 144), resample=0)
            # print(im.width, im.height)
            im = np.array(im)
            x_train.append(im)
    return cnt

count = load_dataset()
print(count)

width, height = 1280, 720

images = np.array(x_train)

def apply_to_image():

    windowName = "result"
    # cv2.namedWindow(windowName, cv2.WINDOW_NORMAL)
    frameSize = (width, height)
    out = cv2.VideoWriter('output_video.avi', cv2.VideoWriter_fourcc(*'DIVX'), 60, frameSize, False)
    
    for image in images:
        image.resize((144,400,3))
        start_mil = millis()
        pred = test_model.predict(np.expand_dims(image, 0))
        stop_mil = millis()

        image = cv2.resize(image, dsize=(640, 480), interpolation=cv2.INTER_AREA)
        result = pred[0].astype('uint8') * 255
        result = cv2.resize(result, dsize=(640, 480), interpolation=cv2.INTER_AREA)
        result = cv2.merge([result,result,result])
        out.write(result)
        # cv2.imwrite('./model_result.png', result)
        # plt.imshow(result)
        # plt.show()
        
        # cv2.imshow('result', result)
        # if cv2.waitKey(1) & 0xFF == ord('q'):
        #     break
        
        algoImg.image_original = image.data.tobytes()
        algoImg.image_result = result.data.tobytes()
        algoImg.millis_term = (stop_mil-start_mil)
        zmqData = algoImg.SerializeToString()
        socketPub.send(zmqData)

    
    out.release()
    # cv2.destroyAllWindows()


apply_to_image()


# In[32]:
## Calculate a Prediction Time

start_mil = millis()
predict_count = 100
image = np.random.random((1, 144, 400, 3))
for i in range(predict_count):
    pred = test_model.predict(image)
stop_mil = millis()
print('Prediction took {} millis'.format((stop_mil - start_mil)//predict_count))


socketPub.send(b"fin")

exit()
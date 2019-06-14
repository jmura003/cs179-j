#!/bin/bash

source ~/.profile
workon cv

cd Multiple_Faces
sudo modprobe bcm2835-v4l2
python face_recog.py

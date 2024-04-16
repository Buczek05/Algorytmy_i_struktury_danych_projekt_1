#!/bin/bash

CURRENT_DIRECTORY=$(basename "$PWD")

if [ "$CURRENT_DIRECTORY" = "doc_generation" ]
then
    cd ..
fi

rm -rf doc_data/*
rm -rf doc/*

mkdir doc/img/

cc -fPIC -shared -o example_integer.so example_integer.c

gcc doc_generation/generate_data_to_doc.c -o generate_data_to_doc
./generate_data_to_doc
rm generate_data_to_doc

source ./venv/bin/activate
python doc_generation/generate_matplotlib_img.py

#!/bin/bash

# Name: create_venv.sh
# Usage: ./create_venv.sh

VENV_DIR=".venv"

if [ -d "$VENV_DIR" ]; then
    echo "Virtual environment '$VENV_DIR' already exists."
else
    echo "Creating virtual environment in '$VENV_DIR'..."
    python3 -m venv "$VENV_DIR"
    echo "Virtual environment created!"
fi


source ./unit_tests_python/.venv/bin/activate
pip install --upgrade pip
pip install -r ./unit_tests_python/requirements.txt

./mps_test

python3 ./unit_tests_python/tests.py
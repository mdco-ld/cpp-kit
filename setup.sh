#!/bin/bash

echo "export MO_CPP_PATH=\"$(pwd)\"/include/" >> ~/.zshrc

ln -s "$(pwd)/expand.py" ~/bin/expand.py

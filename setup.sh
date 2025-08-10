#!/bin/bash

echo "export MOG_CPP_PATH=\"$(pwd)\"/include/" >> ~/.zshrc

ln -s "$(pwd)/expand.py" ~/bin/expand.py

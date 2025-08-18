#!/bin/bash

if [[ "$SHELL" == "/bin/bash" || "$SHELL" == "/usr/bin/bash" ]]; then
	echo "export MOG_CPP_PATH=\"$(pwd)/include/\"" >> ~/.bashrc
elif [[ "$SHELL" == "/bin/zsh" || "$SHELL" == "/usr/bin/zsh" ]]; then
	echo "export MOG_CPP_PATH=\"$(pwd)/include/\"" >> ~/.zshrc
else
	echo "Failed to recognize shell"
fi

if [[ ! -f "~/bin/expand.py" ]]; then
	ln -s "$(pwd)/expand.py" ~/bin/expand.py
fi

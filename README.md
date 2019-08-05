# Unlimited Code Works

## Environment

### CMake

VERSION 3.13 (or higher)

### C++ STANDARD

C++11

### Global Gitignore (recommended)

- https://github.com/github/gitignore/blob/master/Global/macOS.gitignore
- https://github.com/github/gitignore/blob/master/Global/JetBrains.gitignore

### Python

```bash
conda create -n unlimited-code-works python=3.7
pip install -r requirements.txt
```

### (Only for WSL)

```bash
sudo ln -s /mnt/c/Windows/System32/clip.exe /usr/bin/clip.exe
```

## Submit

```bash
conda activate unlimited-code-works
python -m util.core
```

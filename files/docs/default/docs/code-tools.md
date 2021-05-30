# Code tools

Ezored has support for code format with command **code"** .

To format all supported files, run the following command:  

```
python make.py code format  
```

Obs 1: Code format use **clang-format** tool inside to format C++ files. You need have it installed and in your **path** to be located.

Obs 2: Code format use **black** tool inside to format PYTHON files. You need have it installed and in your **path** to be located.

Obs 3: Code format use **cmake-format** tool inside to format CMAKE files. You need have it installed and in your **path** to be located.

## macOS

On macOS you can install [brew](https://brew.sh/) and execute:

```
brew install clang-format
pip install cmake-format
pip install black
```
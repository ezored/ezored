# Commands

Commands are functions executed from command line (terminal) that let you work with Ezored without need other tools, complex GUI libraries or other requirements.

Every command script in Ezored is a python file hosted on **files/commands**. 

Commands are simple functions that will receive command line arguments, project path and will executed desired operations. Example:

```python make.py clean```

or

```python make.py code format```

So, when you execute `python make.py clean` Ezored will search for a file with path **"files/commands/clean.py"** and will send all parameter to a function called **"run"** inside the file **clean.py**.

If you don't remember what commands are available you can type only this to list all commands:

```python make.py```

If you want create your own commands put the file inside folder **"files/commands"** and execute `python make.py` on terminal to see it in command list.

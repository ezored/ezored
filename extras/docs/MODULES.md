<p align="center"><a href="https://github.com/ezored/ezored" target="_blank" rel="noopener noreferrer"><img width="180" src="../images/doc-logo.png" alt="ezored logo"></a></p>

<h1 align="center"><strong>Modules</strong></h1>

A module in ezored is a C++ implementation of one specific feature and ezored come with some modules already implemented:

1. **date and time helper**  
    Functions to work with date and time.

2. **file helper**  
    Functions to work with files (write, read, create folder, delete files etc).

3. **http client**  
    Http client to make http and https requests.

4. **logger**  
    Logger functions to show messages with different levels.

5. **shared data**  
    Shared data storage.

    1. Android = using shared preferences
    2. iOS = using NSUserDefaults
    3. Desktop = using local file

6. **string helper**  
    Functions to work with string.

7. **database**  
    SQLite3 is ready to use with ezored and let you use the same database on all platforms. Internally you can check our scheme migration implementation. A library called "sqlitecpp" is used to make this job easier.

8. **json**  
    RapidJSON is used to parsing json from remote requests in ezored samples. It works on all tested platforms nice and fast.

9. **support lib**  
    Mobile glue code is automatically generated using Djinni tool. It can be removed if you don't use.

Obs: Modules source code are stored in **"files/src"** and **"files/gluecode"**.

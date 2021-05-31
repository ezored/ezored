# Modules

A module in Ezored is a C++ implementation of one specific feature and Ezored come with some modules already implemented:

1. **Date ad Time**  
    Functions to work with date and time.

2. **File Helper**  
    Functions to work with files (write, read, create folder, delete files etc).

3. **HTTP Client**  
    HTTP client to make HTTP and HTTPS requests.

4. **Logger**  
    Logger functions to show messages with different levels.

5. **Shared Data**  
    Shared data storage.

    1. Android: `using shared preferences`
    2. iOS: `using NSUserDefaults`
    3. Desktop: `using local file`

6. **String Helper**  
    Functions to work with string.

7. **Database**  
    SQLite3 is ready to use with Ezored and let you use the same database on all platforms. Internally you can check our scheme migration implementation. A library called "sqlitecpp" is used to make this job easier.

8. **JSON**  
    RapidJSON is used to parsing json from remote requests in Ezored samples. It works on all tested platforms nice and fast.

9. **Support Lib**  
    Mobile glue code is automatically generated using [Djinni tool](https://github.com/cross-language-cpp/djinni-generator). It can be removed if you don't use.

Obs: Modules source code are stored in **"files/modules"**.

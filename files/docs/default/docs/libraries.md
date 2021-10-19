# Libraries

Ezored can use any C++ library. Today the dependency manager used is [Conan](https://conan.io/). With Conan you can add any library that fit your needs.

Conan main recipe list is hosted on Github:

[https://github.com/conan-io/conan-center-index/tree/master/recipes](https://github.com/conan-io/conan-center-index/tree/master/recipes)

Ezored already use some libraries:

1. **Date**
    This library let you work with date, time and timezone.

    [https://github.com/HowardHinnant/date](https://github.com/HowardHinnant/date).

2. **SQLite 3**  
    SQLite3 is a very stable database that work everywhere and on all platforms. 

    [https://sqlite.org/](https://sqlite.org/)

3. **SQLite CPP**  
    SQLite CPP is a SQLite 3 wrapper that let your work with databases much more clear and easy. 
    
    [https://github.com/SRombauts/SQLiteCpp](https://github.com/SRombauts/SQLiteCpp)

4. **RapidJSON**  
    RapidJSON is used to parsing json from remote requests. It works on all tested platforms nice and fast.

    [https://rapidjson.org/](https://rapidjson.org/)

5. **Poco Project**  
    Poco is used to make HTTP and HTTPS requests. Today it is used on desktop targets, but can be used on mobile targets changing only the configuration files.

    [https://pocoproject.org/](https://pocoproject.org/)

6. **OpenSSL**  
    OpenSSL is the most used and most robust cryptography library and is used with HTTP library to make HTTPS requests.

    [https://www.openssl.org/](https://www.openssl.org/)

7. **Djinni Support Lib**  
    Mobile glue code is automatically generated using [Djinni tool](https://github.com/cross-language-cpp/djinni-generator). It can be removed if you don't use.

    And the support lib is used as a wrapper between C++ and platforms code, like JNI and OBJC.

    [https://github.com/cross-language-cpp/djinni-support-lib](https://github.com/cross-language-cpp/djinni-support-lib)

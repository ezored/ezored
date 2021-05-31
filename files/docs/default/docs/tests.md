# Tests

Ezored come with C++ test support.

You can test C++ code with the following commands:

```
python make.py target tests prepare
python make.py target tests run
```

Obs: The verb **prepare** install all tests dependencies.

## Source

You can add, remove or edit tests changing files inside folder **files/modules/target-tests**.

On target tests you have some folders:

- **cmake:** contains cmake module instructions
- **include:** contains include files and it is added as search path
- **include/fixtures:** contains all tests fixtures
- **src:** contains all tests sources

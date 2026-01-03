# Simple SQLite like Database

Run `make` to build the database. Then run `./db dbname` to start a database which will create a database inside a file named `dbname`.

This database only supports one meta command which is `.exit` and two statements: `insert` and `select`.

Sample usage:
```bash
$ db > insert 1 orik orik@morik.com
$ db > select
  (1, orik, orik@morik.com)
$ db > .exit
```

The code is based on [Let's Build a Simple Database](https://cstack.github.io/db_tutorial/) tutorial.

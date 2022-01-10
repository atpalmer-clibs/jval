# jtypes

This is a C library for representing JSON data structures.

`main.c` imports `jtypes.h` and creates a data structure similar to the following:

```
    {
      "value": 4,
      "value2": 5,
      "name": "Andy",
      "int-value": 6,
      "myArray": [
        100,
        101,
        "0102",
        103,
        [
          "1",
          "0",
          "4"
        ],
        {
          "value": 105
        },
        [
          true,
          false
        ]
      ],
      "location": {
        "city": "Chicago",
        "state": "Illinois"
      },
      "true": true,
      "false": false
    }
```

GCC optimisation levels
-----------------------

| flag | optimisation of | execution time | code size | memory usage | compile time |
|------|-----------------|----------------|-----------|--------------|--------------|
| -O0  | compile time (default) | + | + | -|- 
| -O1  | code size and execution time | -  | - | + | + |
| -O2  | code size and execution time | -  | - | + | ++ |
| -O3  | code size and execution size | --- | - | + | +++ |
| -Os  | code size | | --- | | ++ |
|-Ofast| O3 with non accurate math calc | ---  | | +|+++
| -Og | optimize for debug | | | | 

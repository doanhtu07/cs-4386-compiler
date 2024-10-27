# How to run

## Prerequisites

- I use bison and flex from brew

## Compile and get the bison executable

```
make
```

## Run with example input

```
./build/ex3 < ex3.txt
```

Get something like this:

```
Procedure : Validate
        Part : begin
                Keyword : DoThis
,               Keyword : Dothat
        Part : end
                Keyword : CleanUp
SUCCESS
```

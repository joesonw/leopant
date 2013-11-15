## Introduction
Leopant is an open-source implementation using [**boost library**](http://www.boost.org). By using Leopant, you can save the time of writing low-level frameworks. Instead, you only need to work on the server logics.

## Quick Start

```cpp
Server s(8011);
s.start();
```
## Data Communication Protocols/Means

format
```cpp
{value_type,value_name,value},
```
type_table
| value_type    |   | 
| ------------- | - |
| string        | 0 |
| int           | 1 |
| float/double  | 2 |
| array         | 3 |

simple usage of functions/datatypes
```cpp
AnyArray arguments;
arguments.write("i'm a string",string("hello world"));
arguments.write("i'm an integer",101);
arguments.write("i'm a float",1.01);
AnyArray array;
array.write("i'm a string too",string("hello world 2"));
array.write("i'm an integer too",101);
array.write("i'm a float too",1.01);
arguments.write("i'm an array",array);
string buf=Packet::pack(arguments);
```
this will give
```cpp
{0,i'm a string,hello world},{1,i'm an integer,101},{2,i'm a float,1.01},{3,i'm an array,{0,i'm a string too,hello world 2},{1,i'm an integer too,101},{2,i'm a float too,1.01},},
```
And vice versa, you can use ```cpp Packet::unpack(string)``` to make a data string into AnyArray.
following methods can be used to retrieve data from ```cpp AnyArray```
```cpp
string AnyArray::readString(string);
int AnyArray::readInt(string);
float AnyArray::readFloat(string);
AnyArray AnyArray::readArray(string);
```

This small package is intended to allow printing colored text for console application.

What you will see from the console:
![temp](pictures/Sample.png)

It is cross-platform and all the functionalities are contained into this single [header](./src/ColoredStream/ColoredStream.hpp) file.

METTERE che stream creati non sono colorati se mandati su file testuali

METTERE spiegare 2 possibilita' per usare colori

## Examples

Usin this package is straightforward: you just need to create a ColoredStream (METTERE in bold) object and then pass it to std::cout for print it.
Suppose for example you want to display a red colored hello world, all you need to do would be this:

```cpp
#include <ColoredStream/ColoredStream.hpp>
using namespace colored_stream;

std::cout << ClassicColoredStream{RED, "Hello world"} << std::endl;
```

![temp](pictures/part01.png)

and that's it!

You can create an empty ColoredStream instance, whose content is created step by step before printing:

```cpp
ClassicColoredStream colored_content(RED);
colored_content << "Hello ";
colored_content << "World ";
colored_content << " :-)";

std::cout << colored_content << std::endl;
```

![temp](pictures/part02.png)

... or, you can pass a variadic number of inputs in order to build the object in place:

```cpp
std::cout << ClassicColoredStream{BLUE,"Hello ", "World ", " :-)"} << std::endl;
```

![temp](pictures/part03.png)

## CMAKE SUPPORT

METTERE spiegare

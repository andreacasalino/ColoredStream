This small package is intended to allow printing **colored** text for **C++** console application.

What you would see from the console using this package:
![temp](pictures/Sample.png)

It is cross-platform and all the functionalities are contained in [**ColoredStream.hpp**](./src/ColoredStream/ColoredStream.hpp) file.

The ability to show a colored text is made possible by building and printing a **ColoredStream** object.
Actually, **ColoredStream** extends **std::stringstream** adding the poddibility to show colored text.
Such ability is enabled when passing a **ColoredStream** instance to a **std::cout** for printing something into a console. On the opposite, when passing a **ColoredStream** instance to another kind of output stream, like for instance a **std::ofstream**, the object behaves like a normal **std::stringstream**, printing normal text.

**ColoredStream** it's a base that can be extened (and used) into 2 possible variety:
 - **ClassicColoredStream**, allowing the possibility to specify classical colors like **red** or **yellow**
 - **CustomColoredStream**, where the color is described by its [ASCII code](https://en.wikipedia.org/wiki/ANSI_escape_code) 

## Examples

Using this package is straightforward: you just need to create a ColoredStream (METTERE in bold) object and then pass it to std::cout for print it.
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

You can fetch this package and link to the **ColoredStream** library, that is actually just a **INTERFACE** library exposing the position of **ColoredStream.hpp**

This small package is intended to allow printing **colored** text for **C++** console application.

Before doing anything else, leave a **star** to this project ;).

What you would see from the console using this package:

![temp](pictures/Sample.png)

It is cross-platform and all the functionalities are contained in [**ColoredStream.hpp**](./src/ColoredStream/ColoredStream.hpp).

The ability to show a colored text is made possible by building and printing a **ColoredStream** object.
**ColoredStream** extends **std::stringstream** adding the possibility to show colored text.
Such ability is enabled when passing a **ColoredStream** instance to a **std::cout** for printing something into the console. On the opposite, when passing a **ColoredStream** instance to another kind of output stream, like for instance a **std::ofstream**, the object behaves like a normal **std::stringstream**, printing normal text.

**ColoredStream** is able to handle 3 possible color prescriptions:
 - specify classical colors like **red** or **yellow**
 - specify a [8-bit color](https://en.wikipedia.org/wiki/ANSI_escape_code) code 
 - specify a [R,G,B](https://en.wikipedia.org/wiki/ANSI_escape_code) triplet 

With **ColoredStream** is also able to apply a background color:
![temp](pictures/part04.png)

## EXAMPLES

Using this package is straightforward: you just need to create a **ColoredStream** object and then pass it to std::cout for print it.
Suppose for example you want to display a red colored hello world, all you need to do would be this:

```cpp
#include <ColoredStream/ColoredStream.hpp>
using namespace colored_stream;

std::cout << ColoredStream{RED, "Hello world"} << std::endl;
```

![temp](pictures/part01.png)

and that's it!

You can create an empty ColoredStream instance, whose content is created step by step, before printing it:

```cpp
ColoredStream colored_content(RED);
colored_content << "Hello ";
colored_content << "World ";
colored_content << " :-)";

std::cout << colored_content << std::endl;
```

![temp](pictures/part02.png)

... or, you can pass a variadic number of inputs in order to build the object in place:

```cpp
std::cout << ColoredStream{BLUE, "Hello ", "World ", " :-)"} << std::endl;
```

![temp](pictures/part03.png)

You can also prescribe the background color of the text:

```cpp
ColoredStream stream{RED, "Hello World"};
stream.setBackground(Uint8Color{11});
std::cout << stream << std::endl;
```

![temp](pictures/part04.png)

## CMAKE SUPPORT

You can fetch this package and link to the **ColoredStream** library, that is actually just a **INTERFACE** library exposing the position of [**ColoredStream.hpp**](./src/ColoredStream/ColoredStream.hpp)

## TO BE DONE FEATURES

These features will be soon added:
 - allow the possibility to color also the background of the text
 - allow the possibility to specify the color using a **(r,g,b)** triplet.

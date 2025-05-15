# Advanced Logger for Unreal Engine 5.3

![Screenshot](https://github.com/user-attachments/assets/f5d1e72a-a87c-4823-a18f-ba8572056114)

## Description
A handy plugin that includes a subsystem that allows you to log.

The plugin outputs both on the screen and in the console, displaying the name of the class in which the function was called.

![Output](https://github.com/user-attachments/assets/cfe78c1f-73fc-420b-a8ac-d7e1ae1b292d)

## Settings
You can customize the standard categories in the project settings. 

![Settings](https://github.com/user-attachments/assets/8ab8f429-1f10-4514-b390-67ff7ae33a99)

## C++ Tips
The plugin also adds useful macros for use in C++
```C++
TRACE(YourCategory, "My text with %s and %d", *myString, myInt);
TRACEWARN(YourCategory, "My text with %s and %d", *myString, myInt);
TRACEERROR(YourCategory, "My text with %s and %d", *myString, myInt);
```
> Note that these macros don't work in static functions and in places where GetWorld() can't be obtained
### Misc
If you need to output something to console in a static function use the following:
```C++
TRACESTATIC(YourCategory, "My text with %s and %d", *myString, myInt);
```

> In this case, the macro will not display your network mode (Standalone, Client, Server) in the console, but will still display the full name of the function
### Screen
The plugin provides two macros for displaying on the screen:
```C++
SCREENDEBUG("My text with %s and %d", *myString, myInt);  // Duration: 5.0f
SCREENDEBUGT("My text with %s and %d", *myString, myInt); // Duration: 0.0f
```
> Note that the second method can be used in Tick()

## Doxygen docs
Doxygen documentation: [GitHubPages](https://artemiyx.github.io/AdvancedLoggerUnrealDoc/annotated.html)

Documentation sources: [GitHub](https://github.com/ArtemIyX/AdvancedLoggerUnrealDoc)

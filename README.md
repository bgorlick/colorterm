# ColorTerm

**The Fastest Feature-Rich C++ Terminal Color Cross-Platform Header Only Library for adding vibrant colors to terminal output.**

## High Level Features

- Cross platform support for Windows, Linux, and macOS
- Highly optimized color application macros (benchmarked and optimized for performance)
- Over 50 predefined foreground and background colors and effects
- Support for 8bit and 24-bit colors and gradients
- Powerful and simple to use API for applying colors and themes to text
- Global enable/disable color and theme settings to quickly toggle color output on and off
- Easy API Logger class to add colored logs to you application with log Levels (such as [INFO], [DEBUG], [ERROR, etc])
- Custom color and theme management  - create, set, insert, inspect, replace, erase, save, load, list, enable, disable, set_default, is_enabled, list_all_theme_maps

**Version: v0.0.1 (Alpha)**
![image](https://github.com/bgorlick/colorterm/assets/5460972/a34689a1-1c05-437d-8215-96864d6a5d7a)

## Custom Colors and ColorMaps (much more than shown here is possible)
![image](https://github.com/bgorlick/colorterm/assets/5460972/490fd8b0-2450-4b15-8648-938a278676ab)

## Dynamically Format into various Output Formats (XML, JSON, HTML, YAML, CSV, TXT)
![image](https://github.com/bgorlick/colorterm/assets/5460972/d9d63cae-aa1b-44af-bb14-723d501d1914)

## More Features (the list goes on and on :)
- Create colormaps that can be single chars or complex strings
- Create custom styles and apply them
- Built in Config class that saves your configs in memory
- Save themed colormaps to disk and load themes from disk
- Built in Output formatter class to output data to (JSON, XML, YAML, CSV, HTML and plain text) dynamically 
- Provides customizable color functions and a custom palette management system.
- Employs compile-time constants for color definitions. It is easily extensible with custom color styles and attributes.

## Get Started Quickly

For immediate use:

```cpp
#include "colorterm.hpp"
```

## 
As this is a header only library, you can simply include the header file in your project and start using the library immediately.


## Quickly see colorterm features in action:
Download the file called benchmark.cpp included in the main repository. 

Compile with clang++ (or g++) run the following command:
```bash
clang++ -std=c++17 -O3 -rtlib=compiler-rt -stdlib=libc++ -o benchmark benchmark.cpp \
      -I/usr/local/include/c++/v1 \
      -L/usr/local/lib \
      -lc++ -lc++abi -lunwind -lgcc_s -lgcc -lm -lc -v -ferror-limit=50`
```

Compile with g++:
```g++ -std=c++17 -O3 -o benchmark benchmark.cpp \
    -I/usr/local/include/c++/v1 \
    -L/usr/local/lib \
    -lstdc++ -lunwind -lgcc_s -lgcc -lm -lc -v -fmax-errors=50`
```

Then run the compiled binary to see some of the color features: 
`./benchmark --verify-all`

## Example
```cpp
#include "colorterm.hpp"
int main() {
    std::cout << colorterm::red << "Red text" << colorterm::reset << std::endl;
    Logger::info("This is an info message"); // Apply predefined colors
    Logger::error("This is an error message"); // Apply predefined colors
    OutputFormatter::to_json(std::cout, data); // Output data in JSON format
    ThemeManager::create("my_theme"); // Create a new theme
    ThemeManager::set("my_theme"); // Set the current theme
    ThemeManager::insert("bracket", "[]", "\033[38;5;34m"); // Set brackets to a greenish color

    std::cout << colorterm::custom_color("bracket") << "{\n"; // Set the bracket color
    std::cout << colorterm::reset << std::endl; // Reset the color

    colorterm::apply_styles(std::cout, "bold", "underline", "purple") << "Bold, underlined, and purple text" << colorterm::reset << std::endl; // Apply multiple styles

    colorterm::apply_gradient(std::cout, "This is a sentence that will be rendered with a gradient color text", 255, 0, 0, 0, 0, 255) << colorterm::reset << std::endl; // Apply gradient color
    return 0;
}
```

## Key Features

1. **Efficient Color Application Macros**: Utilizes macros like `APPLY_COLOR_MACRO`, `APPLY_8BIT_COLOR_MACRO`, and `APPLY_RGB_COLOR_MACRO` for efficient color application with minimal overhead.
2. **Customizable Color Functions**: Provides a flexible and extensible way to define and use custom color functions via the `DEFINE_COLOR_FUNCTION` macro, allowing for easy creation of new color styles and attributes.
3. **Cross-Platform Support with Platform-Specific Optimizations**: Seamlessly supports Windows, Linux, and macOS with platform-specific code, including Windows API functions for color handling and POSIX functions for determining terminal connections.
4. **Compile-Time Constants for Color Definitions**: Uses compile-time constants for color definitions, combined with templates, ensuring type safety and efficiency.
5. **8-bit and 24-bit Colors**: Functions to apply both 8-bit and 24-bit RGB colors to text and background.
6. **Predefined Colors and Styles**: Includes a variety of predefined colors and text styles, such as bold, italic, and underline.
7. **Custom Colors**: Allows users to define and use their custom colors and styles.
8. **Gradient Text**: Supports rendering text with gradient colors.
9. **Custom Palette Management**: Functions to manage a palette of custom colors, including setting and listing them.
10. **Custom Color Inspections**: Functions to inspect custom colors, themes, colormaps, and color codes.

## ThemeManager and ColorMap API

### ThemeManager

```cpp
1. `void create(const std::string& themeName)`  
   Usage: `colorterm::create_theme("my_theme");`

2. `void set(const std::string& themeName)`  
   Usage: `colorterm::set_theme("my_theme");`

3. `void insert(const std::string& name, const std::string& characters, const std::string& colorCode, bool isKey = false, bool isValue = false)`  
   Usage: 
   \`\`\cpp
   colorterm::insert_colormap("bracket", "[]", "\033[38;5;34m");
   colorterm::insert_colormap("key", "name", "\033[38;5;208m", true);
   colorterm::insert_colormap("value", "Alice", "\033[38;5;75m", false, true);
   \`\`\

4. `std::string apply(const std::string& text) const`  
   Usage: `std::string colored_text = colorterm::apply_theme(text);`

5. `std::unordered_map<char, std::string> inspect() const`  
   Usage: `std::unordered_map<char, std::string> colormap = colorterm::inspect_theme();`

6. `const std::string* inspect_color(char character) const`  
   Usage: `const std::string* color = colorterm::inspect_colormap_color('[');`

7. `const std::string* inspect_key_color(const std::string& key) const`  
   Usage: `const std::string* key_color = colorterm::inspect_key_color("name");`

8. `const std::string* inspect_value_color(const std::string& value) const`  
   Usage: `const std::string* value_color = colorterm::inspect_value_color("Alice");`

9. `std::vector<std::string> list() const`  
   Usage: `std::vector<std::string> themes = colorterm::list_themes();`

10. `void replace(const std::string& characters, const std::string& colorCode)`  
    Usage: `colorterm::replace_colormap("[]", "\033[38;5;40m");`

11. `void erase(const std::string& characters)`  
    Usage: `colorterm::erase_colormap("[]");`

12. `void save(const std::string& themeName, const std::string& filePath)`  
    Usage: `colorterm::save_theme("my_theme", "path/to/file");`

13. `void load(const std::string& themeName, const std::string& filePath)`  
    Usage: `colorterm::load_theme("my_theme", "path/to/file");`

14. `void set_default()`  
    Usage: `colorterm::set_default_theme();`

15. `void enable_colormap()`  
    Usage: `colorterm::enable_colormap();`

16. `void disable_colormap()`  
    Usage: `colorterm::disable_colormap();`

17. `bool is_enabled() const`  
    Usage: `bool enabled = colorterm::is_color_enabled();`

18. `std::string list_all_theme_maps() const`  
    Usage: `std::string all_mappings = colorterm::list_all_theme_maps();`

### ColorMap

1. `void insert(const std::string& name, const std::string& characters, const std::string& colorCode, bool isKey = false, bool isValue = false)`  
   Usage: 
   \`\`\cpp
   colorterm::insert_colormap("bracket", "[]", "\033[38;5;34m");
   colorterm::insert_colormap("key", "name", "\033[38;5;208m", true);
   colorterm::insert_colormap("value", "Alice", "\033[38;5;75m", false, true);
   \`\`\

2. `std::string apply(const std::string& text) const`  
   Usage: `std::string colored_text = colorterm::apply_theme(text);`

3. `std::unordered_map<char, std::string> get() const`  
   Usage: `std::unordered_map<char, std::string> colormap = colorterm::inspect_theme();`

4. `std::unordered_map<std::string, std::string> get_key_map() const`  
   Usage: `std::unordered_map<std::string, std::string> key_map = colorterm::inspect_key_theme();`

5. `std::unordered_map<std::string, std::string> get_value_map() const`  
   Usage: `std::unordered_map<std::string, std::string> value_map = colorterm::inspect_value_theme();`

6. `const std::string* inspect_color(char character) const`  
   Usage: `const std::string* color = colorterm::inspect_colormap_color('[');`

7. `const std::string* inspect_key_color(const std::string& key) const`  
   Usage: `const std::string* key_color = colorterm::inspect_key_color("name");`

8. `const std::string* inspect_value_color(const std::string& value) const`  
   Usage: `const std::string* value_color = colorterm::inspect_value_color("Alice");`

9. `void replace(const std::string& characters, const std::string& colorCode)`  
   Usage: `colorterm::replace_colormap("[]", "\033[38;5;40m");`

10. `void erase(const std::string& characters)`  
    Usage: `colorterm::erase_colormap("[]");`
```

## More Usage Examples

Include the `colorterm.hpp` header in your C++ project and link against any necessary libraries. 

Use the predefined functions or define your own custom colors and styles to enhance the terminal output.

A sample of functionality below does the following: 
- Applies predefined colors and styles.
- Applies 8-bit and 24-bit RGB colors.
- Applies a gradient color.
- Applies multiple styles.
- Lists all custom colors.
- Inspects a custom color.
- Outputs text with a predefined foreground color.
- Outputs text with a predefined background color.
- Outputs text with a predefined style.
- Shows gold background with black text and uses the full reset after applying a style.

```cpp
#include "colorterm.hpp"

int main() {
    std::cout << colorterm::red << "Red text" << colorterm::reset << std::endl; // Apply predefined colors
    colorterm::set_custom_color("error", "\033[38;5;196m"); // Set a custom color
    std::cout << colorterm::custom_color("error") << "Error message" << colorterm::reset << std::endl;
    std::cout << colorterm::color<std::ostream>(9) << "8-bit color text" << colorterm::reset << std::endl; // Apply 8-bit RGB color
    std::cout << colorterm::color<255, 165, 0> << "24-bit RGB color text" << colorterm::reset << std::endl; // Apply 24-bit RGB color
    colorterm::apply_gradient(std::cout, "This is a sentence that will be rendered with a gradient color text", 255, 0, 0, 0, 0, 255) << colorterm::reset << std::endl; // Apply gradient color
    colorterm::apply_styles(std::cout, "bold", "underline", "green") << "Bold, underlined, and green text" << colorterm::reset << std::endl; // Apply multiple styles
    colorterm::list_custom_colors(); // List all custom colors
    colorterm::inspect_custom_color("error"); // Inspect a custom color
    std::cout << colorterm::red << "Red text" << colorterm::reset << std::endl; // Output text with a predefined foreground color
    std::cout << colorterm::bg_gold << "Gold background" << colorterm::reset << std::endl; // Output text with a predefined background color
    std::cout << colorterm::bold << "Bold text" << colorterm::reset << std::endl; // Output text with a predefined style
    std::cout << colorterm::bg_gold << colorterm::black << colorterm::bold << "Gold background with black text" << colorterm::fullreset << std::endl; // Gold background with black text and using the fullreset after applying a style.
    return 0;
}
```

## License and Copyright
Copyright 2024-2025 Ben Gorlick | github.com/bgorlick/colorterm/ | License Boost 1.0
Distributed under the Boost Software License, Version 1.0.  
(LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

## Developer Notes
This project was inspired by many color libraries including Pygments (python) and termcolor (c++). The aim is to provide a high level of performance, powerful features and ease of use.

## Contributions
Contributors are welcome - this library is designed to make managing and expressing with colors in c++ easier, streamlined and enjoyable.

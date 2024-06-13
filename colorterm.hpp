/*

ColorTerm - The Fastest Feature-Rich C++ Terminal Color Cross-Platform Header Only Library for adding vibrant colors to terminal output.
Version: v0.0.1 (Alpha)

Copyright (c) 2024-2025 | Ben Gorlick | https://github.com/bgorlick/colorterm
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
https://www.boost.org/LICENSE_1_0.txt)


High level features include: 8-bit and 24-bit color support, gradient text, custom color and theme management, custom styles, and output formatting.

- Cross platform support for Windows, Linux, and macOS
- Highly optimized color application macros (benchmarked and optimized for performance)
- Over 50 predefined foreground and background colors and effects
- Support for 8bit and 24-bit colors and gradients
- Powerful and simple to use API for applying colors and themes to text
- Global enable/disable color and theme settings to quickly toggle color output on and off
- Easy API Logger class to add colored logs to you application with log Levels (such as [INFO], [DEBUG], [ERROR, etc])
- Custom color and theme management  - create, set, insert, inspect, replace, erase, save, load, list, enable, disable, set_default, is_enabled, list_all_theme_maps
- Create colormaps that can be single chars or complex strings
- Create custom styles and apply them
- Built in Config class that saves your configs in memory
- Save themed colormaps to disk and load themes from disk
- Built in Output formatter class to output data to (JSON, XML, YAML, CSV, HTML and plain text) dynamically 
- Provides customizable color functions and a custom palette management system.
- Employs compile-time constants for color definitions. It is easily extensible with custom color styles and attributes.

GET STARTED QUICKLY:
As this is a header only library, you can simply include the header file in your project and start using the library immediately.

#include "colorterm.hpp"

Quickly testing the library and seeing some of the features in action:
A file called benchmark.cpp is included in the repository that can be used to test and visibily see some of the features of the library.

To compile it with clang++, run the following command:
clang++ -std=c++17 -O3 -rtlib=compiler-rt -stdlib=libc++ -o benchmark benchmark.cpp \
      -I/usr/local/include/c++/v1 \
      -L/usr/local/lib \
      -lc++ -lc++abi -lunwind -lgcc_s -lgcc -lm -lc -v -ferror-limit=50

Then run the compiled binary to see some of the color features: ./benchmark --verify-all 


Some quick usage examples:
std::cout << colorterm::red << "Red text" << colorterm::reset << std::endl; 

Logger::info("This is an info message"); // Apply predefined colors

Logger::error("This is an error message"); // Apply predefined colors

OutputFormatter::to_json(std::cout, data); // Output data in JSON format

ThemeManager::create("my_theme"); // Create a new theme

ThemeManager::set("my_theme"); // Set the current theme

ThemeManager::insert("bracket", "[]", "\033[38;5;34m"); // Set brackets to a greenish color

std::cout << colorterm::custom_color("bracket") << "{\n"; // Set the bracket color
std::cout << colorterm::reset << std::endl; // Reset the color

Applying multiple styles to a string:
colorterm::apply_styles(std::cout, "bold", "underline", "purple") << "Bold, underlined, and purple text" << colorterm::reset << std::endl; // Apply multiple styles


Applying all the most common ANSI styles via apply_styles, you can also directly use the main RGB colors like this:
Example: bright_red, bold_red, light_red, red

Apply a full gradient to your text like this:
colorterm::apply_gradient(std::cout, "This is a sentence that will be rendered with a gradient color text", 255, 0, 0, 0, 0, 255) << colorterm::reset << std::endl; // Apply gradient color

Easily apply foreground and background colors using both 8-bit and 24-bit color codes, as well as predefined styles and custom colors. 
The library supports both ANSI escape codes for Unix-like systems and appropriate methods for Windows.

Key Features:
1. **Efficient Color Application Macros**: Utilizes macros like APPLY_COLOR_MACRO, APPLY_8BIT_COLOR_MACRO, and APPLY_RGB_COLOR_MACRO for efficient color application with minimal overhead.
2. **Customizable Color Functions**: Provides a flexible and extensible way to define and use custom color functions via the DEFINE_COLOR_FUNCTION macro, allowing for easy creation of new color styles and attributes.
3. **Cross-Platform Support with Platform-Specific Optimizations**: Seamlessly supports Windows, Linux, and macOS with platform-specific code, including Windows API functions for color handling and POSIX functions for determining terminal connections.
4. **Compile-Time Constants for Color Definitions**: Uses compile-time constants for color definitions, combined with templates, ensuring type safety and efficiency.
5. **8-bit and 24-bit Colors**: Functions to apply both 8-bit and 24-bit RGB colors to text and background.
6. **Predefined Colors and Styles**: Includes a variety of predefined colors and text styles, such as bold, italic, and underline.
7. **Custom Colors**: Allows users to define and use their custom colors and styles.
8. **Gradient Text**: Supports rendering text with gradient colors.
9. **Custom Palette Management**: Functions to manage a palette of custom colors, including setting and listing them.
10. **Custom Color Inspections**: Functions to inspect custom colors, themes, colormaps, and color codes.

ThemeManager and ColorMap API:
ThemeManager
1. void create(const std::string& themeName)
Usage: colorterm::create_theme("my_theme");

2. void set(const std::string& themeName)
Usage: colorterm::set_theme("my_theme");

3. void insert(const std::string& name, const std::string& characters, const std::string& colorCode, bool isKey = false, bool isValue = false)
Usage: 
colorterm::insert_colormap("bracket", "[]", "\033[38;5;34m");
colorterm::insert_colormap("key", "name", "\033[38;5;208m", true);
colorterm::insert_colormap("value", "Alice", "\033[38;5;75m", false, true);

4. std::string apply(const std::string& text) const
Usage: std::string colored_text = colorterm::apply_theme(text);

5. std::unordered_map<char, std::string> inspect() const
Usage: std::unordered_map<char, std::string> colormap = colorterm::inspect_theme();

6. const std::string* inspect_color(char character) const
Usage: const std::string* color = colorterm::inspect_colormap_color('[');

7. const std::string* inspect_key_color(const std::string& key) const
Usage: const std::string* key_color = colorterm::inspect_key_color("name");

8. const std::string* inspect_value_color(const std::string& value) const
Usage: const std::string* value_color = colorterm::inspect_value_color("Alice");

9. std::vector<std::string> list() const
Usage: std::vector<std::string> themes = colorterm::list_themes();

10. void replace(const std::string& characters, const std::string& colorCode)
Usage: colorterm::replace_colormap("[]", "\033[38;5;40m");

11. void erase(const std::string& characters)
Usage: colorterm::erase_colormap("[]");

12. void save(const std::string& themeName, const std::string& filePath)
Usage: colorterm::save_theme("my_theme", "path/to/file");

13. void load(const std::string& themeName, const std::string& filePath)
Usage: colorterm::load_theme("my_theme", "path/to/file");

14. void set_default()
Usage: colorterm::set_default_theme();

15. void enable_colormap()
Usage: colorterm::enable_colormap();

16. void disable_colormap()
Usage: colorterm::disable_colormap();

17. bool is_enabled() const
Usage: bool enabled = colorterm::is_color_enabled();

18. std::string list_all_theme_maps() const
Usage: std::string all_mappings = colorterm::list_all_theme_maps();

ColorMap
1. void insert(const std::string& name, const std::string& characters, const std::string& colorCode, bool isKey = false, bool isValue = false)
Usage: 
colorterm::insert_colormap("bracket", "[]", "\033[38;5;34m");
colorterm::insert_colormap("key", "name", "\033[38;5;208m", true);
colorterm::insert_colormap("value", "Alice", "\033[38;5;75m", false, true);

2. std::string apply(const std::string& text) const
Usage: std::string colored_text = colorterm::apply_theme(text);

3. std::unordered_map<char, std::string> get() const
Usage: std::unordered_map<char, std::string> colormap = colorterm::inspect_theme();

4. std::unordered_map<std::string, std::string> get_key_map() const
Usage: std::unordered_map<std::string, std::string> key_map = colorterm::inspect_key_theme();

5. std::unordered_map<std::string, std::string> get_value_map() const
Usage: std::unordered_map<std::string, std::string> value_map = colorterm::inspect_value_theme();

6. const std::string* inspect_color(char character) const
Usage: const std::string* color = colorterm::inspect_colormap_color('[');

7. const std::string* inspect_key_color(const std::string& key) const
Usage: const std::string* key_color = colorterm::inspect_key_color("name");

8. const std::string* inspect_value_color(const std::string& value) const
Usage: const std::string* value_color = colorterm::inspect_value_color("Alice");

9. void replace(const std::string& characters, const std::string& colorCode)
Usage: colorterm::replace_colormap("[]", "\033[38;5;40m");

10. void erase(const std::string& characters)
Usage: colorterm::erase_colormap("[]");


A few additional API functions:
apply_256bit_color - Apply a 256-bit color to the stream (Windows only)
apply_palette - Apply a custom palette to the stream
replace_color_all_instances - Replace all instances of a color in a string
highlight_pattern - Highlight a pattern in a string
set_custom_color_predefined - Set a custom color using a predefined color
custom_color - Apply a custom color to the stream
remove_custom_color - Remove a custom color
inspect_custom_color - Inspect a custom color
list_custom_colors - List all custom colors
reset_custom_colors - Reset all custom colors
scope_guard - Apply a color for the duration of a scope
colorize_string - Apply a color to a string
apply_output_format - Apply an output format to a stream
set_output_format - Set the output format
get_output_format - Get the current output format
list_output_formats - List all output formats
reset_output_format - Reset the output format


Usage:
Include the `colorterm.hpp` header in your C++ project and link against any necessary libraries. Use the predefined functions or define your own custom colors and styles to enhance the terminal output.

A sample of functionality below does the following: 
- Applies predefined colors and styles.
- Applies 8-bit and 24-bit RGB colors.
- Applies a gradient color.
- Applies multiple styles.
- Lists all custom colors.
- Inspect a custom color.
- Output text with a predefined foreground color.
- Output text with a predefined background color.
- Output text with a predefined style.
- Shows gold background with black text and using the fullreset after applying a style.

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
*/

// Boost Software License - Version 1.0 - August 17th, 2003
// 
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef COLORTERM_HPP_
#define COLORTERM_HPP_

#include <cstdint>
#include <string_view>
#include <vector>
#include <algorithm>
#include <functional>
#include <mutex>
#include <stdexcept>
#include <cstring>
#include <memory>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>


// Global flags for color and theme
bool is_global_colored = true;
bool is_global_themed = true;

// Stream-specific flags (not in use right now)
bool is_stream_colored = true;
bool is_stream_themed = true;

#if defined(_WIN32) || defined(_WIN64)
    #include <io.h>
    #include <windows.h>
    #define ISATTY(fd) _isatty(_fileno(fd))
#else
    #include <unistd.h>
    #define ISATTY(fd) ::isatty(fileno(fd))
#endif

#define CHECK_COLOR_AND_THEME(stream) (is_global_colored && is_global_themed)

#if defined(_WIN32) || defined(_WIN64)
template <typename CharT>
inline std::basic_ostream<CharT>& apply_windows_code(std::basic_ostream<CharT>& stream, WORD attr) __attribute__((always_inline));
template <typename CharT>
inline std::basic_ostream<CharT>& apply_windows_code(std::basic_ostream<CharT>& stream, WORD attr) {
    if (colorterm::_internal::is_stream_colored(stream)) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hConsole != INVALID_HANDLE_VALUE) {
            SetConsoleTextAttribute(hConsole, attr);
        }
    }
    return stream;
}
#endif

#if defined(_WIN32) || defined(_WIN64)
inline void apply_256bit_color(std::ostream& stream, uint8_t color, bool isForeground = true) {
    if (color < 8) {
        color += 30;
    } else if (color < 16) {
        color += 82;
    } else {
        color = 90 + (color - 16);
    }
    stream << "\033[" << (isForeground ? "38" : "48") << ";5;" << std::to_string(color) << "m";
}
#endif

namespace colorterm {
namespace _internal {

enum class Palette { SOLARIZED, MONOKAI };

// Helper struct to represent an RGB color
struct RGB {
    int r, g, b;
};

struct ColorDefinition {
    std::string code;
#if defined(_WIN32) || defined(_WIN64)
    WORD win_attr;
#endif
};

inline int colorterm_index() { static int index = std::ios_base::xalloc(); return index; }
inline int colorterm_theme_index() { static int index = std::ios_base::xalloc(); return index; }

} // namespace _internal

template <typename CharT>
inline std::basic_ostream<CharT>& enable(std::basic_ostream<CharT>& stream) {
    stream.iword(_internal::colorterm_index()) = 1L;
    return stream;
}

template <typename CharT>
inline std::basic_ostream<CharT>& disable(std::basic_ostream<CharT>& stream) {
    stream.iword(_internal::colorterm_index()) = 0L;
    return stream;
}

inline void enable_global_color() {
    is_global_colored = true;
}

inline void disable_global_color() {
    is_global_colored = false;
}

inline void enable_global_theme() {
    is_global_themed = true;
}

inline void disable_global_theme() {
    is_global_themed = false;
}

template <typename CharT>
inline std::basic_ostream<CharT>& enable_stream(std::basic_ostream<CharT>& stream) {
    stream.iword(_internal::colorterm_index()) = 1L;
    return stream;
}

template <typename CharT>
inline std::basic_ostream<CharT>& disable_stream(std::basic_ostream<CharT>& stream) {
    stream.iword(_internal::colorterm_index()) = 0L;
    return stream;
}

} // namespace colorterm

namespace colorterm {

namespace _internal {

template <typename StreamType>
inline bool is_stream_colored(StreamType& stream) {
    if constexpr (std::is_base_of_v<std::ostream, StreamType>) {
        return stream.iword(colorterm_index()) != 0;
    }
    return false;
}

template <typename StreamType>
inline bool is_stream_themed(StreamType& stream) {
    if constexpr (std::is_base_of_v<std::ostream, StreamType>) {
        return stream.iword(colorterm_theme_index()) == 1;
    }
    return false;
}

template <typename WideCharT, typename NarrowCharT>
inline std::basic_string<NarrowCharT> to_string(const std::basic_string<WideCharT>& wstr) {
    if (wstr.empty()) return std::basic_string<NarrowCharT>();
    size_t size = wcstombs(nullptr, wstr.c_str(), 0);
    if (size == static_cast<size_t>(-1)) throw std::runtime_error("Error converting wstring to string");
    std::basic_string<NarrowCharT> str(size, '\0');
    wcstombs(&str[0], wstr.c_str(), size);
    return str;
}

template <typename StreamType>
inline void write_to_streambuf(StreamType& stream, const std::string& str) {
    if constexpr (std::is_same_v<StreamType, std::stringstream> || std::is_same_v<StreamType, std::ofstream>) {
        stream.rdbuf()->sputn(str.data(), str.size());
    } else {
        stream.rdbuf()->sputn(str.c_str(), str.size());
    }
}

template <typename StreamType>
inline StreamType& operator<<(StreamType& stream, const std::wstring& wstr) {
    if constexpr (std::is_same_v<StreamType, std::basic_ostream<wchar_t>>) {
        stream.write(wstr.data(), wstr.size());
    } else {
        stream << _internal::to_string<wchar_t, typename StreamType::char_type>(wstr);
    }
    return stream;
}

template <typename StreamType>
inline bool is_atty(const StreamType& stream) {
    if constexpr (std::is_same_v<StreamType, std::basic_ostream<char>>) {
        return (&stream == &std::cout) ? ISATTY(stdout) : ((&stream == &std::cerr || &stream == &std::clog) ? ISATTY(stderr) : false);
    } else if constexpr (std::is_same_v<StreamType, std::basic_ostream<wchar_t>>) {
        return (&stream == &std::wcout) ? ISATTY(stdout) : ((&stream == &std::wcerr || &stream == &std::wclog) ? ISATTY(stderr) : false);
    } else {
        return false;
    }
}

template <typename StreamType>
inline StreamType& apply_code(StreamType& stream, std::string_view code) {
    if (CHECK_COLOR_AND_THEME(stream)) {
        if constexpr (std::is_same_v<StreamType, std::basic_ostream<wchar_t>>) {
            std::wstring wcode(code.begin(), code.end());
            stream.rdbuf()->sputn(wcode.data(), wcode.size());
        } else if constexpr (std::is_same_v<StreamType, std::stringstream> || std::is_same_v<StreamType, std::ofstream>) {
            write_to_streambuf(stream, std::string(code));
        } else {
            stream.rdbuf()->sputn(code.data(), code.size());
        }
    }
    return stream;
}

} // namespace _internal

} // namespace colorterm

namespace colorterm {
namespace _internal {

struct CustomColor {
    std::string name;
    std::function<void(std::ostream&)> apply;
};

struct PaletteRGB { uint8_t r, g, b; };

struct CustomPalette {
    std::unordered_map<std::string, PaletteRGB> colors;
};

inline std::unordered_map<std::string, std::string>& predefined_colors() {
    static std::unordered_map<std::string, std::string> colors;
    return colors;
}

inline std::unordered_map<std::string, std::string>& custom_defined_colors() {
    static std::unordered_map<std::string, std::string> colors;
    return colors;
}

} // namespace _internal
} // namespace colorterm

#if defined(_WIN32) || defined(_WIN64)
    #define DEFINE_COLOR_FUNCTION(NAME, CODE, ...) \
    inline const colorterm::_internal::ColorDefinition NAME##_def = { CODE, __VA_ARGS__ }; \
    template <typename CharT> \
    inline std::basic_ostream<CharT>& NAME(std::basic_ostream<CharT>& stream) __attribute__((always_inline)); \
    template <typename CharT> \
    inline std::basic_ostream<CharT>& NAME(std::basic_ostream<CharT>& stream) { \
        colorterm::_internal::apply_windows_code(stream, NAME##_def.win_attr); return stream; } \
    inline void init_##NAME() { colorterm::_internal::predefined_colors()[#NAME] = CODE; } \
    static const bool NAME##_init = (init_##NAME(), true)
#else
    #define DEFINE_COLOR_FUNCTION(NAME, CODE, ...) \
    inline const colorterm::_internal::ColorDefinition NAME##_def = { CODE }; \
    template <typename CharT> \
    inline std::basic_ostream<CharT>& NAME(std::basic_ostream<CharT>& stream) __attribute__((always_inline)); \
    template <typename CharT> \
    inline std::basic_ostream<CharT>& NAME(std::basic_ostream<CharT>& stream) { \
        colorterm::_internal::apply_code(stream, NAME##_def.code); return stream; } \
    inline void init_##NAME() { colorterm::_internal::predefined_colors()[#NAME] = CODE; } \
    static const bool NAME##_init = (init_##NAME(), true)
#endif

// High Performance Color Application Macros
#define APPLY_COLOR_MACRO(stream, r, g, b, type) do { \
    if (CHECK_COLOR_AND_THEME(stream)) { \
        char buf[19]; char* p = buf; \
        *p++ = '\033'; *p++ = '['; *p++ = type; *p++ = '8'; *p++ = ';'; \
        *p++ = '2'; *p++ = ';'; *p++ = '0' + (r / 100); *p++ = '0' + ((r / 10) % 10); *p++ = '0' + (r % 10); \
        *p++ = ';'; *p++ = '0' + (g / 100); *p++ = '0' + ((g / 10) % 10); *p++ = '0' + (g % 10); \
        *p++ = ';'; *p++ = '0' + (b / 100); *p++ = '0' + ((b / 10) % 10); *p++ = '0' + (b % 10); \
        *p++ = 'm'; stream.write(buf, p - buf); } \
} while (0)

#define APPLY_8BIT_COLOR_MACRO(stream, value, type) \
do { \
    if (CHECK_COLOR_AND_THEME(stream)) { \
        char buf[11] = "\033["; \
        strcat(buf, type); \
        strcat(buf, "8;5;"); \
        char* p = buf + strlen(buf); \
        uint8_t val = value; \
        if (val >= 100) { *p++ = '0' + (val / 100); val %= 100; } \
        else { *p++ = '0'; } \
        if (val >= 10) { *p++ = '0' + (val / 10); val %= 10; } \
        else { *p++ = '0'; } \
        *p++ = '0' + val; \
        *p++ = 'm'; \
        stream.write(buf, p - buf); \
    } \
} while (0)

#define APPLY_RGB_COLOR_MACRO(stream, r, g, b, type) do { \
    if (CHECK_COLOR_AND_THEME(stream)) { \
        char buf[19]; char* p = buf; *p++ = '\033'; *p++ = '['; *p++ = type; *p++ = '8'; *p++ = ';'; \
        *p++ = '2'; *p++ = ';'; *p++ = '0' + (r / 100); int r_mod = r % 100; *p++ = '0' + (r_mod / 10); r_mod %= 10; *p++ = '0' + r_mod; \
        *p++ = ';'; *p++ = '0' + (g / 100); int g_mod = g % 100; *p++ = '0' + (g_mod / 10); g_mod %= 10; *p++ = '0' + g_mod; \
        *p++ = ';'; *p++ = '0' + (b / 100); int b_mod = b % 100; *p++ = '0' + (b_mod / 10); b_mod %= 10; *p++ = '0' + b_mod; *p++ = 'm'; \
        stream.write(buf, p - buf); \
    } \
} while (0)

#define APPLY_RGB_COLOR_MACRO_TO_STRING(stream, r, g, b, type) do { \
    if (CHECK_COLOR_AND_THEME(stream)) { \
        char buf[19]; char* p = buf; *p++ = '\033'; *p++ = '['; *p++ = type; *p++ = '8'; *p++ = ';'; \
        int r_temp = r; int g_temp = g; int b_temp = b; \
        *p++ = '2'; *p++ = ';'; *p++ = '0' + (r_temp / 100); r_temp %= 100; *p++ = '0' + (r_temp / 10); r_temp %= 10; *p++ = '0' + r_temp; \
        *p++ = ';'; *p++ = '0' + (g_temp / 100); g_temp %= 100; *p++ = '0' + (g_temp / 10); g_temp %= 10; *p++ = '0' + g_temp; \
        *p++ = ';'; *p++ = '0' + (b_temp / 100); b_temp %= 100; *p++ = '0' + (b_temp / 10); b_temp %= 10; *p++ = '0' + b_temp; *p++ = 'm'; \
        stream = std::string(buf, p - buf); } \
} while (0)

namespace colorterm {

// Apply 24-bit RGB color
template <typename CharT>
inline void apply_color(std::ostream& stream, int r, int g, int b) {
    APPLY_RGB_COLOR_MACRO(stream, r, g, b, '3');
}

// Apply 24-bit RGB color
inline std::basic_ostream<char>& apply_color(std::basic_ostream<char>& stream, uint8_t r, uint8_t g, uint8_t b) {
    APPLY_RGB_COLOR_MACRO(stream, r, g, b, '3');
    return stream;
}

// Apply 24-bit RGB background color
inline std::basic_ostream<char>& apply_bg_color(std::basic_ostream<char>& stream, uint8_t r, uint8_t g, uint8_t b) {
    APPLY_RGB_COLOR_MACRO(stream, r, g, b, '4');
    return stream;
}

// Overload to apply a color using a single integer color code
inline std::ostream& apply_color(std::ostream& stream, int color_code) {
    APPLY_8BIT_COLOR_MACRO(stream, color_code, "3");
    return stream;
}

// Overload to apply a background color using a single integer color code
inline std::ostream& apply_bg_color(std::ostream& stream, int color_code) {
    APPLY_8BIT_COLOR_MACRO(stream, color_code, "4");
    return stream;
}

// Define the get_custom_palette function
inline _internal::CustomPalette& get_custom_palette() {
    static _internal::CustomPalette palette;
    // Define your custom colors here
    palette.colors["red"] = {255, 0, 0};
    palette.colors["green"] = {0, 255, 0};
    palette.colors["blue"] = {0, 0, 255};
    palette.colors["yellow"] = {255, 255, 0};
    palette.colors["magenta"] = {255, 0, 255};
    return palette;
}

// Apply custom background color by name
inline std::basic_ostream<char>& custom_bg_color(std::basic_ostream<char>& stream, const std::string& name) {
    auto& palette = get_custom_palette().colors;
    auto it = palette.find(name);
    if (it != palette.end()) {
        const colorterm::_internal::PaletteRGB& color = it->second;
        return apply_bg_color(stream, color.r, color.g, color.b);
    }
    return stream;
}

// Set 24-bit color
template <typename CharT>
inline std::basic_ostream<CharT>& set_color(std::basic_ostream<CharT>& stream, uint8_t r, uint8_t g, uint8_t b) {
#if defined(_WIN32) || defined(_WIN64)
    if (colorterm::_internal::is_stream_colored(stream)) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hConsole != INVALID_HANDLE_VALUE) {
            WORD color = 0;
            if (r > 128) color |= FOREGROUND_RED;
            if (g > 128) color |= FOREGROUND_GREEN;
            if (b > 128) color |= FOREGROUND_BLUE;
            if (r > 128 || g > 128 || b > 128) color |= FOREGROUND_INTENSITY;
            _internal::set_color(hConsole, color);
        }
    }
#else
    if (colorterm::_internal::is_stream_colored(stream)) {
        stream << "\033[38;2;" << static_cast<int>(r) << ';' << static_cast<int>(g) << ';' << static_cast<int>(b) << 'm';
    }
#endif
    return stream;
}

// Apply 24-bit RGB color
inline std::basic_ostream<char>& apply_rgb_color(std::basic_ostream<char>& stream, uint8_t r, uint8_t g, uint8_t b) {
    APPLY_RGB_COLOR_MACRO(stream, r, g, b, '3');
    return stream;
}

// Apply 24-bit RGB color to a string
inline void apply_rgb_color(std::string& stream, uint8_t r, uint8_t g, uint8_t b) {
    APPLY_RGB_COLOR_MACRO_TO_STRING(stream, r, g, b, '3');
}

// 8-bit color functions
template <typename T, typename CharT>
inline std::basic_ostream<CharT>& color(std::basic_ostream<CharT>& stream, T code) {
    APPLY_8BIT_COLOR_MACRO(stream, static_cast<uint8_t>(code), "3");
    return stream;
}

// Template function to apply 24-bit RGB color
template <uint8_t r, uint8_t g, uint8_t b, typename CharT>
inline std::basic_ostream<CharT>& color(std::basic_ostream<CharT>& stream) {
    APPLY_RGB_COLOR_MACRO(stream, r, g, b, '3');
    return stream;
}

// Apply 24-bit RGB color using template
template <uint8_t r, uint8_t g, uint8_t b, typename CharT = char>
inline std::basic_ostream<CharT>& apply_color(std::basic_ostream<CharT>& stream) {
    APPLY_RGB_COLOR_MACRO(stream, r, g, b, '3');
    return stream;
}

// Apply 24-bit RGB background color using template
template <uint8_t r, uint8_t g, uint8_t b, typename CharT = char>
inline std::basic_ostream<CharT>& apply_bg_color(std::basic_ostream<CharT>& stream) {
    APPLY_RGB_COLOR_MACRO(stream, r, g, b, '4');
    return stream;
}

// Apply custom color by name and return stream
inline std::ostream& apply_custom_color(std::ostream& stream, const std::string& name) {
    auto& colors = _internal::custom_defined_colors();
    auto it = colors.find(name);
    if (it != colors.end()) {
        _internal::apply_code(stream, it->second);
    } else {
        std::cerr << "Error: Custom color '" << name << "' not found." << std::endl;
    }
    return stream;
}

// Apply custom background color by name and return stream
inline std::ostream& apply_custom_bg_color(std::ostream& stream, const std::string& name) {
    auto& colors = _internal::custom_defined_colors();
    auto it = colors.find(name);
    if (it != colors.end()) {
        _internal::apply_code(stream, it->second);
    } else {
        std::cerr << "Error: Custom background color '" << name << "' not found." << std::endl;
    }
    return stream;
}

} // namespace colorterm

namespace colorterm {

// Set 24-bit background color
template <typename CharT>
inline std::basic_ostream<CharT>& set_background_color(std::basic_ostream<CharT>& stream, uint8_t r, uint8_t g, uint8_t b) {
#if defined(_WIN32) || defined(_WIN64)
    if (CHECK_COLOR_AND_THEME(stream)) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hConsole != INVALID_HANDLE_VALUE) {
            WORD color = 0;
            if (r > 128) color |= BACKGROUND_RED;
            if (g > 128) color |= BACKGROUND_GREEN;
            if (b > 128) color |= BACKGROUND_BLUE;
            if (r > 128 || g > 128 || b > 128) color |= BACKGROUND_INTENSITY;
            colorterm::_internal::set_color(hConsole, color);
        }
    }
#else
    if (CHECK_COLOR_AND_THEME(stream)) {
        stream << "\033[48;2;" << static_cast<int>(r) << ';' << static_cast<int>(g) << ';' << static_cast<int>(b) << 'm';
    }
#endif
    return stream;
}

// Apply 24-bit RGB background color to a string
inline void apply_rgb_background_color(std::string& stream, uint8_t r, uint8_t g, uint8_t b) {
    APPLY_RGB_COLOR_MACRO_TO_STRING(stream, r, g, b, '4');
}

// Apply 24-bit RGB background color
inline std::basic_ostream<char>& apply_rgb_background_color(std::basic_ostream<char>& stream, uint8_t r, uint8_t g, uint8_t b) {
    if (CHECK_COLOR_AND_THEME(stream)) {
        uint8_t r_mod = r;
        uint8_t g_mod = g;
        uint8_t b_mod = b;
        APPLY_RGB_COLOR_MACRO(stream, r_mod, g_mod, b_mod, '4');
    }
    return stream;
}

// Template function to apply 24-bit RGB background color
template <uint8_t r, uint8_t g, uint8_t b, typename CharT>
inline std::basic_ostream<CharT>& bg_color(std::basic_ostream<CharT>& stream) {
    if (CHECK_COLOR_AND_THEME(stream)) {
        uint8_t r_mod = r;
        uint8_t g_mod = g;
        uint8_t b_mod = b;
        APPLY_RGB_COLOR_MACRO(stream, r_mod, g_mod, b_mod, '4');
    }
    return stream;
}

// 8-bit background color functions
template <uint8_t code, typename CharT>
inline std::basic_ostream<CharT>& bg_color(std::basic_ostream<CharT>& stream) {
    APPLY_8BIT_COLOR_MACRO(stream, code, "4");
    return stream;
}

} // namespace colorterm

namespace colorterm {

// Helper function for color interpolation
inline int interpolate(int start, int end, float ratio) {return start + static_cast<int>((end - start) * ratio);}

// Template function to apply a gradient with start and end colors specified by colorterm::_internal::RGB
template <typename CharT>
inline void apply_gradient(std::basic_ostream<CharT>& stream, colorterm::_internal::RGB start_col, colorterm::_internal::RGB end_col, const std::string& text) {
    if (CHECK_COLOR_AND_THEME(stream)) {
        size_t length = text.length();
        for (size_t i = 0; i < length; ++i) {
            float ratio = static_cast<float>(i) / (length - 1);
            int r = interpolate(start_col.r, end_col.r, ratio);
            int g = interpolate(start_col.g, end_col.g, ratio);
            int b = interpolate(start_col.b, end_col.b, ratio);
            apply_color(stream, r, g, b);
            stream << text[i];
        }
        stream << "\033[0m"; // Reset color
    } else {
        stream << text;
    }
}

// Template function to apply a gradient to a string and return the result with colorterm::_internal::RGB
template <typename CharT>
inline std::string apply_gradient(const std::string& text, colorterm::_internal::RGB start_col, colorterm::_internal::RGB end_col) {
    std::ostringstream oss;
    if (CHECK_COLOR_AND_THEME(oss)) {
        size_t length = text.length();
        for (size_t i = 0; i < length; ++i) {
            double ratio = static_cast<double>(i) / (length - 1);
            uint8_t r = static_cast<uint8_t>(start_col.r + ratio * (end_col.r - start_col.r));
            uint8_t g = static_cast<uint8_t>(start_col.g + ratio * (end_col.g - start_col.g));
            uint8_t b = static_cast<uint8_t>(start_col.b + ratio * (end_col.b - start_col.b));
            APPLY_RGB_COLOR_MACRO(oss, r, g, b, '3');
            oss << text[i];
        }
        oss << "\033[0m"; // Reset color
    } else {
        oss << text;
    }
    return oss.str();
}

// Custom overload to apply a gradient using start and end colors specified by colorterm::_internal::RGB and return a std::string
inline std::string apply_gradient(const std::string& text, colorterm::_internal::RGB start_col, colorterm::_internal::RGB end_col) {
    std::ostringstream oss;
    if (CHECK_COLOR_AND_THEME(oss)) {
        size_t length = text.length();
        for (size_t i = 0; i < length; ++i) {
            double ratio = static_cast<double>(i) / (length - 1);
            uint8_t r = static_cast<uint8_t>(start_col.r + ratio * (end_col.r - start_col.r));
            uint8_t g = static_cast<uint8_t>(start_col.g + ratio * (end_col.g - start_col.g));
            uint8_t b = static_cast<uint8_t>(start_col.b + ratio * (end_col.b - start_col.b));
            APPLY_RGB_COLOR_MACRO(oss, r, g, b, '3');
            oss << text[i];
        }
        oss << "\033[0m"; // Reset color
    } else {
        oss << text;
    }
    return oss.str();
}

// Overload to apply a gradient using start and end colors specified by RGB values
inline std::ostream& apply_gradient(std::ostream& stream, const std::string& text, int start_r, int start_g, int start_b, int end_r, int end_g, int end_b) {
    colorterm::_internal::RGB start_col = {start_r, start_g, start_b};
    colorterm::_internal::RGB end_col = {end_r, end_g, end_b};
    apply_gradient(stream, start_col, end_col, text);
    return stream;
}

// Overload to apply a gradient with start and end colors specified by colorterm::_internal::RGB and intensity
inline std::ostream& apply_gradient(std::ostream& stream, colorterm::_internal::RGB start_col, colorterm::_internal::RGB end_col, float intensity) {
    if (CHECK_COLOR_AND_THEME(stream)) {
        int r = interpolate(start_col.r, end_col.r, intensity);
        int g = interpolate(start_col.g, end_col.g, intensity);
        int b = interpolate(start_col.b, end_col.b, intensity);
        APPLY_RGB_COLOR_MACRO(stream, r, g, b, '3');
    }
    return stream;
}

// Overload to apply a gradient with start and end colors specified by RGB values and intensity
inline void apply_gradient(std::ostream& stream, int start_r, int start_g, int start_b, int end_r, int end_g, int end_b, float intensity) {
    colorterm::_internal::RGB start_col = {start_r, start_g, start_b};
    colorterm::_internal::RGB end_col = {end_r, end_g, end_b};
    if (CHECK_COLOR_AND_THEME(stream)) {
        apply_gradient(stream, start_col, end_col, intensity);
    } else {
        // Apply default handling if color is not enabled
    }
}

// Overload to apply a gradient using start and end colors specified by colorterm::_internal::RGB and return a std::string for integral types
inline std::string apply_gradient(const std::string& text, int start_r, int start_g, int start_b, int end_r, int end_g, int end_b) {
    colorterm::_internal::RGB start_col = {start_r, start_g, start_b};
    colorterm::_internal::RGB end_col = {end_r, end_g, end_b};
    return apply_gradient(text, start_col, end_col);
}

// Overload to apply a gradient without predefined text for themes
inline void apply_gradient(std::ostream& stream, colorterm::_internal::RGB start_col, colorterm::_internal::RGB end_col) {
    if (CHECK_COLOR_AND_THEME(stream)) {
        for (int i = 0; i < 10; ++i) { // applying gradient to 10 spaces
            float ratio = static_cast<float>(i) / 9; // 9 because we want to divide the range into 10 parts
            int r = interpolate(start_col.r, end_col.r, ratio);
            int g = interpolate(start_col.g, end_col.g, ratio);
            int b = interpolate(start_col.b, end_col.b, ratio);
            apply_color(stream, r, g, b);
            stream << " ";
        }
        stream << "\033[0m"; // Reset color
    }
}

} // namespace colorterm

namespace colorterm {
DEFINE_COLOR_FUNCTION(black, "\033[30m", 0);
DEFINE_COLOR_FUNCTION(red, "\033[31m", FOREGROUND_RED);
DEFINE_COLOR_FUNCTION(green, "\033[32m", FOREGROUND_GREEN);
DEFINE_COLOR_FUNCTION(yellow, "\033[33m", FOREGROUND_RED | FOREGROUND_GREEN);
DEFINE_COLOR_FUNCTION(blue, "\033[34m", FOREGROUND_BLUE);
DEFINE_COLOR_FUNCTION(magenta, "\033[35m", FOREGROUND_RED | FOREGROUND_BLUE);
DEFINE_COLOR_FUNCTION(cyan, "\033[36m", FOREGROUND_GREEN | FOREGROUND_BLUE);
DEFINE_COLOR_FUNCTION(white, "\033[37m", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

DEFINE_COLOR_FUNCTION(bg_black, "\033[40m", 0);
DEFINE_COLOR_FUNCTION(bg_red, "\033[41m", BACKGROUND_RED);
DEFINE_COLOR_FUNCTION(bg_green, "\033[42m", BACKGROUND_GREEN);
DEFINE_COLOR_FUNCTION(bg_yellow, "\033[43m", BACKGROUND_RED | BACKGROUND_GREEN);
DEFINE_COLOR_FUNCTION(bg_blue, "\033[44m", BACKGROUND_BLUE);
DEFINE_COLOR_FUNCTION(bg_magenta, "\033[45m", BACKGROUND_RED | BACKGROUND_BLUE);
DEFINE_COLOR_FUNCTION(bg_cyan, "\033[46m", BACKGROUND_GREEN | BACKGROUND_BLUE);
DEFINE_COLOR_FUNCTION(bg_white, "\033[47m", BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
DEFINE_COLOR_FUNCTION(reset, "\033[0m", 0);
}


namespace colorterm {

// LogLevel enum definition
enum class LogLevel { debug, info, warn, error, fatal, trace, unknown };

// Configuration storage class
class Config {
public:
    using CustomStringMap = std::unordered_map<std::string, std::string>;
    using CustomLogMap = std::unordered_map<LogLevel, CustomStringMap>;
    using ColorFunctionMap = std::unordered_map<LogLevel, _internal::ColorDefinition>;

    static CustomLogMap& UserConfig_Logger() {
        static CustomLogMap config;
        return config;
    }

    static ColorFunctionMap& UserColorConfig_Logger() {
        static ColorFunctionMap colorConfig;
        return colorConfig;
    }

    static std::string logLevelToString(LogLevel level) {
        auto& userConfig = UserConfig_Logger();
        static std::unordered_map<LogLevel, std::string> defaultMessages;
        if (defaultMessages.size() == 0) {
            defaultMessages[LogLevel::debug] = "DEBUG";
            defaultMessages[LogLevel::info] = "INFO";
            defaultMessages[LogLevel::warn] = "WARNING";
            defaultMessages[LogLevel::error] = "ERROR";
            defaultMessages[LogLevel::fatal] = "FATAL";
            defaultMessages[LogLevel::trace] = "TRACE";
            defaultMessages[LogLevel::unknown] = "UNKNOWN";
        }

        auto it = userConfig.find(level);
        if (it != userConfig.end()) {
            auto subIt = it->second.find("message");
            if (subIt != it->second.end()) {
                return subIt->second;
            }
        }
        return defaultMessages[level];
    }

    static std::ostream& applyLogLevelColor(std::ostream& os, LogLevel level) {
        auto& userConfig = UserColorConfig_Logger();
        static std::unordered_map<LogLevel, _internal::ColorDefinition> defaultColors;
        if (defaultColors.size() == 0) {
            defaultColors[LogLevel::debug] = colorterm::cyan_def;
            defaultColors[LogLevel::info] = colorterm::green_def;
            defaultColors[LogLevel::warn] = colorterm::yellow_def;
            defaultColors[LogLevel::error] = colorterm::red_def;
            defaultColors[LogLevel::fatal] = colorterm::magenta_def;
            defaultColors[LogLevel::trace] = colorterm::blue_def;
            defaultColors[LogLevel::unknown] = colorterm::white_def;
        }

        if (CHECK_COLOR_AND_THEME(os)) {
            auto it = userConfig.find(level);
            if (it != userConfig.end() && !it->second.code.empty()) {
                return colorterm::_internal::apply_code(os, it->second.code);
            }
        }

        return colorterm::_internal::apply_code(os, defaultColors[level].code);
    }

    static void setLogLevelColor(LogLevel level, _internal::ColorDefinition colorDef) {
        UserColorConfig_Logger()[level] = colorDef;
    }

    static void setLogLevelMessage(LogLevel level, const std::string& message) {
        UserConfig_Logger()[level]["message"] = message;
    }

    static void setColorFullMessage(bool colorFull) {
        auto& userConfig = UserConfig_Logger();
        for (auto level : {LogLevel::debug, LogLevel::info, LogLevel::warn, LogLevel::error, LogLevel::fatal, LogLevel::trace, LogLevel::unknown}) {
            userConfig[level]["colorFull"] = colorFull ? "true" : "false";
        }
    }
};

} // namespace colorterm

namespace colorterm {
    namespace _internal {

inline std::unordered_map<LogLevel, std::unordered_map<std::string, std::string>>& UserConfig_Logger() {
    static std::unordered_map<LogLevel, std::unordered_map<std::string, std::string>> config;
    return config;
}

inline std::unordered_map<LogLevel, ColorDefinition>& UserColorConfig_Logger() {
    static std::unordered_map<LogLevel, ColorDefinition> colorConfig;
    return colorConfig;
}

inline std::string logLevelToString(LogLevel level) {
    auto& userConfig = UserConfig_Logger();
    static std::unordered_map<LogLevel, std::string> defaultMessages = {
        {LogLevel::debug, "DEBUG"},
        {LogLevel::info, "INFO"},
        {LogLevel::warn, "WARNING"},
        {LogLevel::error, "ERROR"},
        {LogLevel::fatal, "FATAL"},
        {LogLevel::trace, "TRACE"},
        {LogLevel::unknown, "UNKNOWN"}
    };

    auto it = userConfig.find(level);
    if (it != userConfig.end()) {
        auto subIt = it->second.find("message");
        if (subIt != it->second.end()) {
            return subIt->second;
        }
    }
    return defaultMessages[level];
}

inline std::ostream& applyLogLevelColor(std::ostream& os, LogLevel level) {
    auto& userConfig = UserColorConfig_Logger();
    static std::unordered_map<LogLevel, ColorDefinition> defaultColors = {
        {LogLevel::debug, colorterm::cyan_def},
        {LogLevel::info, colorterm::green_def},
        {LogLevel::warn, colorterm::yellow_def},
        {LogLevel::error, colorterm::red_def},
        {LogLevel::fatal, colorterm::magenta_def},
        {LogLevel::trace, colorterm::blue_def},
        {LogLevel::unknown, colorterm::white_def}
    };

    if (CHECK_COLOR_AND_THEME(os)) {
        auto it = userConfig.find(level);
        if (it != userConfig.end() && !it->second.code.empty()) {
            return colorterm::_internal::apply_code(os, it->second.code);
        }
    }

    return colorterm::_internal::apply_code(os, defaultColors[level].code);
}

inline void setLogLevelColor(LogLevel level, ColorDefinition colorDef) {
    UserColorConfig_Logger().insert_or_assign(level, colorDef);
}

inline void setLogLevelMessage(LogLevel level, const std::string& message) {
    UserConfig_Logger()[level].insert_or_assign("message", message);
}

inline void setColorFullMessage(bool colorFull) {
    auto& userConfig = UserConfig_Logger();
    for (auto level : {LogLevel::debug, LogLevel::info, LogLevel::warn, LogLevel::error, LogLevel::fatal, LogLevel::trace, LogLevel::unknown}) {
        userConfig[level].insert_or_assign("colorFull", colorFull ? "true" : "false");
    }
}
    } // namespace _internal

// Logging class to manage log messages
class Logger {
public:
    // Define logging functions using a macro
    #define DEFINE_LOG_FUNCTION(level) \
    static void level(const std::string& msg) { \
        log(LogLevel::level, msg); \
    } \
    static void level(const std::string& file, int line, const std::string& msg) { \
        log(LogLevel::level, file, line, msg); \
    }

    DEFINE_LOG_FUNCTION(info)
    DEFINE_LOG_FUNCTION(debug)
    DEFINE_LOG_FUNCTION(warn)
    DEFINE_LOG_FUNCTION(error)
    DEFINE_LOG_FUNCTION(fatal)
    DEFINE_LOG_FUNCTION(trace)

    #undef DEFINE_LOG_FUNCTION

private:
    static void log(LogLevel level, const std::string& msg) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto& userConfig = _internal::UserConfig_Logger();
        auto it = userConfig.find(level);
        bool colorFull = false;
        
        if (it != userConfig.end()) {
            auto subIt = it->second.find("colorFull");
            if (subIt != it->second.end()) {
                colorFull = subIt->second == "true";
            }
        }

        if (colorFull && CHECK_COLOR_AND_THEME(std::cerr)) {
            _internal::applyLogLevelColor(std::cerr, level);
            std::cerr << "[" << _internal::logLevelToString(level) << "] " << msg << colorterm::reset << std::endl;
        } else {
            std::cerr << "[";
            if (CHECK_COLOR_AND_THEME(std::cerr)) {
                _internal::applyLogLevelColor(std::cerr, level);
            }
            std::cerr << _internal::logLevelToString(level) << colorterm::reset << "] " << msg << std::endl;
        }
    }

    static void log(LogLevel level, const std::string& file, int line, const std::string& msg) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto& userConfig = _internal::UserConfig_Logger();
        auto it = userConfig.find(level);
        bool colorFull = false;

        if (it != userConfig.end()) {
            auto subIt = it->second.find("colorFull");
            if (subIt != it->second.end()) {
                colorFull = subIt->second == "true";
            }
        }

        if (colorFull && CHECK_COLOR_AND_THEME(std::cerr)) {
            _internal::applyLogLevelColor(std::cerr, level);
            std::cerr << "[" << _internal::logLevelToString(level) << "] " << file << ":" << line << " " << msg << colorterm::reset << std::endl;
        } else {
            std::cerr << "[";
            if (CHECK_COLOR_AND_THEME(std::cerr)) {
                _internal::applyLogLevelColor(std::cerr, level);
            }
            std::cerr << _internal::logLevelToString(level) << colorterm::reset << "] " << file << ":" << line << " " << msg << std::endl;
        }
    }

    static std::mutex mutex_;
};

std::mutex Logger::mutex_;

} // namespace colorterm



namespace colorterm {
namespace _internal {



// custom_regex_replace function to replace all occurrences of a substring in a string
inline std::string custom_regex_replace(const std::string& str, const std::string& from, const std::string& to) {
    std::string result = str;
    size_t start_pos = 0;
    while ((start_pos = result.find(from, start_pos)) != std::string::npos) {
        result.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
    return result;
}



struct ThemeRGB {
    uint8_t r, g, b;
};

class ColorMapping {
private:
    std::unordered_map<char, std::string> charToColorCode;
    std::unordered_map<std::string, std::string> keyToColorCode;
    std::unordered_map<std::string, std::string> valueToColorCode;

public:
    void insert(const std::string& name, const std::string& characters, const std::string& colorCode, bool isKey = false, bool isValue = false) {
        if (isKey) {
            keyToColorCode[name] = colorCode;
        } else if (isValue) {
            valueToColorCode[name] = colorCode;
        } else {
            for (char ch : characters) {
                charToColorCode[ch] = colorCode;
            }
        }
    }

    std::string apply(const std::string& text) const {
        std::ostringstream oss;
        bool isKey = true;
        for (char ch : text) {
            if (ch == ':') isKey = false;
            auto it = charToColorCode.find(ch);
            if (it != charToColorCode.end()) {
                oss << it->second << ch << "\033[0m";
            } else if (isKey) {
                oss << apply_key_color(std::string(1, ch));
            } else {
                oss << apply_value_color(std::string(1, ch));
            }
        }
        return oss.str();
    }

    std::string apply_key_color(const std::string& key) const {
        auto it = keyToColorCode.find(key);
        if (it != keyToColorCode.end()) {
            return it->second + key + "\033[0m";
        }
        return key;
    }

    std::string apply_value_color(const std::string& value) const {
        auto it = valueToColorCode.find(value);
        if (it != valueToColorCode.end()) {
            return it->second + value + "\033[0m";
        }
        return value;
    }

    std::unordered_map<char, std::string> get() const {
        return charToColorCode;
    }

    std::unordered_map<std::string, std::string> get_key_map() const {
        return keyToColorCode;
    }

    std::unordered_map<std::string, std::string> get_value_map() const {
        return valueToColorCode;
    }

    const std::string* inspect_color(char character) const {
        auto it = charToColorCode.find(character);
        if (it != charToColorCode.end()) {
            return &it->second;
        }
        return nullptr;
    }

    const std::string* inspect_key_color(const std::string& key) const {
        auto it = keyToColorCode.find(key);
        if (it != keyToColorCode.end()) {
            return &it->second;
        }
        return nullptr;
    }

    const std::string* inspect_value_color(const std::string& value) const {
        auto it = valueToColorCode.find(value);
        if (it != valueToColorCode.end()) {
            return &it->second;
        }
        return nullptr;
    }

    void replace(const std::string& characters, const std::string& colorCode) {
        for (char ch : characters) {
            charToColorCode[ch] = colorCode;
        }
    }

    void erase(const std::string& characters) {
        for (char ch : characters) {
            charToColorCode.erase(ch);
        }
    }
};

class ThemeManager {
private:
    ThemeManager() : currentTheme(&defaultTheme), color_enabled(true) {
        themes["default"] = defaultTheme;
    }

    ColorMapping defaultTheme;
    ColorMapping* currentTheme;
    std::unordered_map<std::string, ColorMapping> themes;
    bool color_enabled;

public:
    static ThemeManager& instance() {
        static ThemeManager instance;
        return instance;
    }

    void create(const std::string& themeName) {
        if (themes.find(themeName) != themes.end()) {
            std::string error_msg = "Theme already exists: " + themeName;
            Logger::error(error_msg);
            throw std::runtime_error(error_msg);
        }
        themes[themeName] = ColorMapping();
        Logger::info("Created theme: " + themeName);
    }

    void set(const std::string& themeName) {
        if (themes.find(themeName) == themes.end()) {
            std::string error_msg = "Theme does not exist: " + themeName;
            Logger::error(error_msg);
            throw std::runtime_error(error_msg);
        }
        currentTheme = &themes[themeName];
        Logger::info("Set current theme to: " + themeName);
    }

    void insert(const std::string& name, const std::string& characters, const std::string& colorCode, bool isKey = false, bool isValue = false) {
        currentTheme->insert(name, characters, colorCode, isKey, isValue);
        Logger::info("Inserted color mapping for " + name + " in current theme");
    }

    std::string apply(const std::string& text) const {
        if (color_enabled) {
            return currentTheme->apply(text);
        } else {
            return text;
        }
    }

    std::unordered_map<char, std::string> inspect() const {
        return currentTheme->get();
    }

    const std::string* inspect_color(char character) const {
        return currentTheme->inspect_color(character);
    }

    const std::string* inspect_key_color(const std::string& key) const {
        return currentTheme->inspect_key_color(key);
    }

    const std::string* inspect_value_color(const std::string& value) const {
        return currentTheme->inspect_value_color(value);
    }

    std::vector<std::string> list() const {
        std::vector<std::string> themeNames;
        for (const auto& [key, _] : themes) {
            themeNames.push_back(key);
        }
        return themeNames;
    }

    void replace(const std::string& characters, const std::string& colorCode) {
        currentTheme->replace(characters, colorCode);
        Logger::info("Replaced color mapping in current theme");
    }

    void erase(const std::string& characters) {
        currentTheme->erase(characters);
        Logger::info("Erased color mapping from current theme");
    }

    void save(const std::string& themeName, const std::string& filePath) {
        std::ofstream outFile(filePath);
        if (!outFile) {
            std::string error_msg = "Failed to open file for saving theme: " + filePath;
            Logger::error(error_msg);
            throw std::runtime_error(error_msg);
        }
        auto colormap = themes[themeName].get();
        for (const auto& [ch, colorCode] : colormap) {
            outFile << ch << ":" << colorCode << "\n";
        }
        outFile.close();
        Logger::info("Saved theme " + themeName + " to file: " + filePath);
    }

    void load(const std::string& themeName, const std::string& filePath) {
        std::ifstream inFile(filePath);
        if (!inFile) {
            std::string error_msg = "Failed to open file for loading theme: " + filePath;
            Logger::error(error_msg);
            throw std::runtime_error(error_msg);
        }
        create(themeName);
        std::string line;
        while (std::getline(inFile, line)) {
            if (line.empty()) continue;
            auto pos = line.find(':');
            if (pos == std::string::npos) continue;
            char ch = line[0];
            std::string colorCode = line.substr(pos + 1);
            themes[themeName].insert(std::string(1, ch), std::string(1, ch), colorCode);
        }
        inFile.close();
        Logger::info("Loaded theme " + themeName + " from file: " + filePath);
    }

    void set_default() {
        currentTheme = &themes["default"];
        Logger::info("Set current theme to default");
    }

    void enable_colormap() {
        color_enabled = true;
        Logger::info("Enabled colormap");
    }

    void disable_colormap() {
        color_enabled = false;
        Logger::info("Disabled colormap");
    }

    bool is_enabled() const {
        return color_enabled;
    }

    std::string list_all_theme_maps() const {
        std::ostringstream oss;
        oss << "\nAll Themes and Their Mappings:\n";
        for (const auto& [themeName, colormap] : themes) {
            oss << "Theme: " << themeName << "\n";
            for (const auto& [character, colorCode] : colormap.get()) {
                oss << "Character: " << character << ", Color Code: " << _internal::custom_regex_replace(colorCode, "\033", "\\033") << "\n";
            }
            for (const auto& [key, colorCode] : colormap.get_key_map()) {
                oss << "Key: " << key << ", Color Code: " << _internal::custom_regex_replace(colorCode, "\033", "\\033") << "\n";
            }
            for (const auto& [value, colorCode] : colormap.get_value_map()) {
                oss << "Value: " << value << ", Color Code: " << _internal::custom_regex_replace(colorCode, "\033", "\\033") << "\n";
            }
            oss << "\n";
        }
        return oss.str();
    }

    void interactive_edit_theme(const std::string& themeName) {
        if (themes.find(themeName) == themes.end()) {
            Logger::error("Theme does not exist: " + themeName);
            throw std::runtime_error("Theme does not exist: " + themeName);
        }
        std::string input;
        std::cout << "Editing theme: " << themeName << "\nEnter color mapping (char:colorCode) or 'done' to finish:\n";
        while (true) {
            std::getline(std::cin, input);
            if (input == "done") break;
            auto pos = input.find(':');
            if (pos == std::string::npos) {
                Logger::error("Invalid format. Use char:colorCode");
                std::cerr << "Invalid format. Use char:colorCode\n";
                continue;
            }
            char ch = input[0];
            std::string colorCode = input.substr(pos + 1);
            themes[themeName].insert(std::string(1, ch), std::string(1, ch), colorCode);
        }
    }
};

} // namespace _internal

void create_theme(const std::string& themeName) {
    _internal::ThemeManager::instance().create(themeName);
}

void set_theme(const std::string& themeName) {
    _internal::ThemeManager::instance().set(themeName);
}

void insert_colormap(const std::string& name, const std::string& characters, const std::string& colorCode, bool isKey = false, bool isValue = false) {
    _internal::ThemeManager::instance().insert(name, characters, colorCode, isKey, isValue);
}


void replace_colormap(const std::string& characters, const std::string& colorCode) {
    _internal::ThemeManager::instance().replace(characters, colorCode);
}

void erase_colormap(const std::string& characters) {
    _internal::ThemeManager::instance().erase(characters);
}

void save_theme(const std::string& themeName, const std::string& filePath) {
    _internal::ThemeManager::instance().save(themeName, filePath);
}

void load_theme(const std::string& themeName, const std::string& filePath) {
    _internal::ThemeManager::instance().load(themeName, filePath);
}

void set_default_theme() {
    _internal::ThemeManager::instance().set_default();
}

void enable_colormap() {
    _internal::ThemeManager::instance().enable_colormap();
}

void disable_colormap() {
    _internal::ThemeManager::instance().disable_colormap();
}

std::string apply_theme(const std::string& text) {
    return _internal::ThemeManager::instance().apply(text);
}

std::unordered_map<char, std::string> inspect_theme() {
    return _internal::ThemeManager::instance().inspect();
}

const std::string* inspect_colormap_color(char character) {
    return _internal::ThemeManager::instance().inspect_color(character);
}

const std::string* inspect_key_color(const std::string& key) {
    return _internal::ThemeManager::instance().inspect_key_color(key);
}

const std::string* inspect_value_color(const std::string& value) {
    return _internal::ThemeManager::instance().inspect_value_color(value);
}

std::vector<std::string> list_themes() {
    return _internal::ThemeManager::instance().list();
}

bool is_color_enabled() {
    return _internal::ThemeManager::instance().is_enabled();
}

std::string list_all_theme_maps() {
    return _internal::ThemeManager::instance().list_all_theme_maps();
}

inline void interactive_edit_theme(const std::string& themeName) {
    _internal::ThemeManager::instance().interactive_edit_theme(themeName);
}

void batch_insert_colormap(const std::unordered_map<std::string, std::string>& mappings, bool isKey = false, bool isValue = false) {
    for (const auto& [name, colorCode] : mappings) {
        _internal::ThemeManager::instance().insert(name, name, colorCode, isKey, isValue);
    }
}

} // namespace colorterm



namespace colorterm {

inline void scope_guard(const std::function<void()>& code) {
    struct ScopeGuard {
        ScopeGuard(const std::function<void()>& code) : code_(code), dismissed_(false) {}
        ~ScopeGuard() { if (!dismissed_) code_(); }
        void dismiss() { dismissed_ = true; }
    private:
        std::function<void()> code_;
        bool dismissed_;
    };
    ScopeGuard guard(code);
    guard.dismiss();
}

} // namespace colorterm

namespace colorterm {


template <typename T>
inline std::string colorize_string(const std::string& str, int r, int g, int b) {
    std::ostringstream oss;
    APPLY_RGB_COLOR_MACRO(oss, r, g, b, '3');
    oss << str << "\033[0m";
    return oss.str();
}

//overload colorize_string for (int, int, int)
inline void colorize_string(std::ostream& stream, int r, int g, int b) {
    APPLY_RGB_COLOR_MACRO(stream, r, g, b, '3');
}

// Apply palette with color and theme check
inline void apply_palette(std::ostream& stream, colorterm::_internal::Palette palette) {
    if (CHECK_COLOR_AND_THEME(stream)) {
        switch (palette) {
            case colorterm::_internal::Palette::SOLARIZED:
                colorterm::colorize_string(stream, 147, 161, 161);
                break;
            case colorterm::_internal::Palette::MONOKAI:
                colorterm::colorize_string(stream, 248, 248, 242);
                break;
            default:
                break;
        }
    }
}

// Replace all instances of a specific color sequence within a string with another color sequence
inline std::string replace_color_all_instances(const std::string& text, colorterm::_internal::RGB from, colorterm::_internal::RGB to) {
    if (CHECK_COLOR_AND_THEME(std::cerr)) {
        std::string from_color;
        std::string to_color;

        APPLY_RGB_COLOR_MACRO_TO_STRING(from_color, from.r, from.g, from.b, '3');
        APPLY_RGB_COLOR_MACRO_TO_STRING(to_color, to.r, to.g, to.b, '3');

        std::string result = text;
        size_t pos = result.find(from_color);
        while (pos != std::string::npos) {
            result.replace(pos, from_color.length(), to_color);
            pos = result.find(from_color, pos + to_color.length());
        }
        return result;
    } else {
        return text;
    }
}

// Highlight a specific pattern within stream of text by replacing with a colored version of the pattern
inline void highlight_pattern(std::ostream& stream, const std::string& pattern, colorterm::_internal::RGB color) {
    if (CHECK_COLOR_AND_THEME(stream)) {
        std::string text;
        std::getline(std::cin, text);
        
        std::string colored_pattern;
        APPLY_RGB_COLOR_MACRO_TO_STRING(colored_pattern, color.r, color.g, color.b, '3');
        colored_pattern += pattern + "\033[0m";

        text = colorterm::_internal::custom_regex_replace(text, pattern, colored_pattern);
        stream << text;
    }
}

inline void set_custom_color_predefined(const std::string& name, const std::string& predefined_color_name) {
    auto& colors = _internal::predefined_colors();
    if (colors.find(predefined_color_name) != colors.end()) {
        _internal::custom_defined_colors()[name] = colors[predefined_color_name];
    } else {
        std::cerr << "Error: Predefined color '" << predefined_color_name << "' not found." << std::endl;
    }
}

// Unified custom color function template
template <typename CharT = char>
inline std::basic_ostream<CharT>& custom_color(std::basic_ostream<CharT>& stream, const std::string& name, const std::string& default_code = "") {
    auto& palette = _internal::custom_defined_colors();
    auto it = palette.find(name);
    if (it != palette.end()) {
        return _internal::apply_code(stream, it->second);
    } else if (!default_code.empty()) {
        return _internal::apply_code(stream, default_code);
    } else {
        std::cerr << "Error: Custom color '" << name << "' not found." << std::endl;
        return stream;
    }
}

inline void set_custom_color(const std::string& name, const std::string& code) {
    _internal::custom_defined_colors()[name] = code;
}

inline void set_custom_color(const std::string& name, std::function<void(std::ostream&)> color_func) {
    std::ostringstream oss; 
    color_func(oss); 
    std::string code = oss.str(); 
    _internal::custom_defined_colors()[name] = code;
}

inline std::function<void(std::ostream&, const std::string&)> get_custom_color(const std::string& name) {
    return [name](std::ostream& stream, const std::string&) {
        custom_color(stream, name);
    };
}

inline void remove_custom_color(const std::string& name) {
    _internal::custom_defined_colors().erase(name);
}

inline void inspect_custom_color(const std::string& name) {
    auto& palette = _internal::custom_defined_colors();
    if (palette.find(name) != palette.end()) {
        std::cout << name << ": " << _internal::custom_regex_replace(palette[name], "\033", "\\033") << std::endl;
    } else {
        std::cout << name << " not found in custom colors." << std::endl;
    }
}

inline std::vector<std::string> list_custom_colors() {
    auto& palette = _internal::custom_defined_colors();
    std::vector<std::string> color_names;
    for (const auto& color : palette) {
        color_names.push_back(color.first);
    }
    return color_names;
}

inline void reset_custom_colors() {
    _internal::custom_defined_colors().clear();
}

} // namespace colorterm


namespace colorterm {

template <typename CharT, typename... Styles>
inline std::basic_ostream<CharT>& apply_styles(std::basic_ostream<CharT>& stream, Styles... styles) {
    if (CHECK_COLOR_AND_THEME(stream)) {
        auto& predefined_styles = colorterm::_internal::predefined_colors();
        auto apply_style = [&](const std::string& style) -> void {
            auto it = predefined_styles.find(style);
            if (it != predefined_styles.end()) {
                stream << it->second;
            } else {
                std::cerr << "Error: Style '" << style << "' not found." << std::endl;
            }
        };
        (apply_style(styles), ...);
    }
    return stream;
}

// Style text with styles
template <typename... Styles>
void style_text(const std::string& text, Styles... styles) {
    apply_styles(std::cout, styles...);
    std::cout << text;
    auto& predefined_styles = colorterm::_internal::predefined_colors();
    auto it = predefined_styles.find("reset");
    if (it != predefined_styles.end()) {
        std::cout << it->second;
    } else {
        std::cerr << "Error: Style 'reset' not found." << std::endl;
    }
    std::cout << std::endl;
}

} // namespace colorterm

namespace colorterm {
DEFINE_COLOR_FUNCTION(bold, "\033[1m", FOREGROUND_INTENSITY);
DEFINE_COLOR_FUNCTION(faint, "\033[2m");
DEFINE_COLOR_FUNCTION(italic, "\033[3m");
DEFINE_COLOR_FUNCTION(underline, "\033[4m", COMMON_LVB_UNDERSCORE);
DEFINE_COLOR_FUNCTION(blink_slow, "\033[5m");
DEFINE_COLOR_FUNCTION(blink_rapid, "\033[6m");
DEFINE_COLOR_FUNCTION(reverse, "\033[7m");
DEFINE_COLOR_FUNCTION(hidden, "\033[8m");
DEFINE_COLOR_FUNCTION(strikethrough, "\033[9m");
DEFINE_COLOR_FUNCTION(default_foreground, "\033[39m");
DEFINE_COLOR_FUNCTION(default_background, "\033[49m");
DEFINE_COLOR_FUNCTION(fullreset, "\033[0m\033[39m\033[49m", 0);

DEFINE_COLOR_FUNCTION(primary_font, "\033[10m");
DEFINE_COLOR_FUNCTION(alternate_font_1, "\033[11m");
DEFINE_COLOR_FUNCTION(alternate_font_2, "\033[12m");
DEFINE_COLOR_FUNCTION(alternate_font_3, "\033[13m");
DEFINE_COLOR_FUNCTION(alternate_font_4, "\033[14m");
DEFINE_COLOR_FUNCTION(alternate_font_5, "\033[15m");
DEFINE_COLOR_FUNCTION(alternate_font_6, "\033[16m");
DEFINE_COLOR_FUNCTION(alternate_font_7, "\033[17m");
DEFINE_COLOR_FUNCTION(alternate_font_8, "\033[18m");
DEFINE_COLOR_FUNCTION(fraktur, "\033[20m");
DEFINE_COLOR_FUNCTION(doubly_underline, "\033[21m");
DEFINE_COLOR_FUNCTION(normal_intensity, "\033[22m");
DEFINE_COLOR_FUNCTION(no_italic, "\033[23m");
DEFINE_COLOR_FUNCTION(no_underline, "\033[24m");
DEFINE_COLOR_FUNCTION(no_blink, "\033[25m");
DEFINE_COLOR_FUNCTION(reserved_1, "\033[26m");
DEFINE_COLOR_FUNCTION(no_reverse, "\033[27m");
DEFINE_COLOR_FUNCTION(reveal, "\033[28m");
DEFINE_COLOR_FUNCTION(no_strikethrough, "\033[29m");

DEFINE_COLOR_FUNCTION(light_black, "\033[2;30m");
DEFINE_COLOR_FUNCTION(light_red, "\033[2;31m");
DEFINE_COLOR_FUNCTION(light_green, "\033[2;32m");
DEFINE_COLOR_FUNCTION(light_yellow, "\033[2;33m");
DEFINE_COLOR_FUNCTION(light_blue, "\033[2;34m");
DEFINE_COLOR_FUNCTION(light_magenta, "\033[2;35m");
DEFINE_COLOR_FUNCTION(light_cyan, "\033[2;36m");
DEFINE_COLOR_FUNCTION(light_white, "\033[2;37m");

DEFINE_COLOR_FUNCTION(bold_black, "\033[1;30m");
DEFINE_COLOR_FUNCTION(bold_red, "\033[1;31m");
DEFINE_COLOR_FUNCTION(bold_green, "\033[1;32m");
DEFINE_COLOR_FUNCTION(bold_yellow, "\033[1;33m");
DEFINE_COLOR_FUNCTION(bold_blue, "\033[1;34m");
DEFINE_COLOR_FUNCTION(bold_magenta, "\033[1;35m");
DEFINE_COLOR_FUNCTION(bold_cyan, "\033[1;36m");
DEFINE_COLOR_FUNCTION(bold_white, "\033[1;37m");

DEFINE_COLOR_FUNCTION(bright_black, "\033[90m", FOREGROUND_INTENSITY);
DEFINE_COLOR_FUNCTION(bright_red, "\033[91m", FOREGROUND_RED | FOREGROUND_INTENSITY);
DEFINE_COLOR_FUNCTION(bright_green, "\033[92m", FOREGROUND_GREEN | FOREGROUND_INTENSITY);
DEFINE_COLOR_FUNCTION(bright_yellow, "\033[93m", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
DEFINE_COLOR_FUNCTION(bright_blue, "\033[94m", FOREGROUND_BLUE | FOREGROUND_INTENSITY);
DEFINE_COLOR_FUNCTION(bright_magenta, "\033[95m", FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
DEFINE_COLOR_FUNCTION(bright_cyan, "\033[96m", FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
DEFINE_COLOR_FUNCTION(bright_white, "\033[97m", FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

DEFINE_COLOR_FUNCTION(bg_light_black, "\033[2;40m");
DEFINE_COLOR_FUNCTION(bg_light_red, "\033[2;41m");
DEFINE_COLOR_FUNCTION(bg_light_green, "\033[2;42m");
DEFINE_COLOR_FUNCTION(bg_light_yellow, "\033[2;43m");
DEFINE_COLOR_FUNCTION(bg_light_blue, "\033[2;44m");
DEFINE_COLOR_FUNCTION(bg_light_magenta, "\033[2;45m");
DEFINE_COLOR_FUNCTION(bg_light_cyan, "\033[2;46m");
DEFINE_COLOR_FUNCTION(bg_light_white, "\033[2;47m");

DEFINE_COLOR_FUNCTION(bg_bright_black, "\033[100m", BACKGROUND_INTENSITY);
DEFINE_COLOR_FUNCTION(bg_bright_red, "\033[101m", BACKGROUND_RED | BACKGROUND_INTENSITY);
DEFINE_COLOR_FUNCTION(bg_bright_green, "\033[102m", BACKGROUND_GREEN | BACKGROUND_INTENSITY);
DEFINE_COLOR_FUNCTION(bg_bright_yellow, "\033[103m", BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
DEFINE_COLOR_FUNCTION(bg_bright_blue, "\033[104m", BACKGROUND_BLUE | BACKGROUND_INTENSITY);
DEFINE_COLOR_FUNCTION(bg_bright_magenta, "\033[105m", BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
DEFINE_COLOR_FUNCTION(bg_bright_cyan, "\033[106m", BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
DEFINE_COLOR_FUNCTION(bg_bright_white, "\033[107m", BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);

DEFINE_COLOR_FUNCTION(amethyst, "\033[38;5;92m");
DEFINE_COLOR_FUNCTION(amber, "\033[38;5;214m");
DEFINE_COLOR_FUNCTION(apricot, "\033[38;5;215m");
DEFINE_COLOR_FUNCTION(aqua, "\033[38;5;51m");
DEFINE_COLOR_FUNCTION(azure, "\033[38;5;75m");
DEFINE_COLOR_FUNCTION(beige, "\033[38;5;230m");
DEFINE_COLOR_FUNCTION(brown, "\033[38;5;94m");
DEFINE_COLOR_FUNCTION(charcoal, "\033[38;5;240m");
DEFINE_COLOR_FUNCTION(coral, "\033[38;5;203m");
DEFINE_COLOR_FUNCTION(crimson, "\033[38;5;197m");
DEFINE_COLOR_FUNCTION(emerald, "\033[38;5;46m");
DEFINE_COLOR_FUNCTION(gold, "\033[38;5;220m");
DEFINE_COLOR_FUNCTION(indigo, "\033[38;5;54m");
DEFINE_COLOR_FUNCTION(ivory, "\033[38;5;230m");
DEFINE_COLOR_FUNCTION(jade, "\033[38;5;35m");
DEFINE_COLOR_FUNCTION(khaki, "\033[38;5;228m");
DEFINE_COLOR_FUNCTION(lavender, "\033[38;5;183m");
DEFINE_COLOR_FUNCTION(lime, "\033[38;5;10m");
DEFINE_COLOR_FUNCTION(maroon, "\033[38;5;88m");
DEFINE_COLOR_FUNCTION(mint, "\033[38;5;48m");
DEFINE_COLOR_FUNCTION(navy, "\033[38;5;17m");
DEFINE_COLOR_FUNCTION(olive, "\033[38;5;100m");
DEFINE_COLOR_FUNCTION(onyx, "\033[38;5;236m");
DEFINE_COLOR_FUNCTION(orange, "\033[38;5;214m");
DEFINE_COLOR_FUNCTION(peach, "\033[38;5;217m");
DEFINE_COLOR_FUNCTION(pearl, "\033[38;5;231m");
DEFINE_COLOR_FUNCTION(pink, "\033[38;5;13m");
DEFINE_COLOR_FUNCTION(plum, "\033[38;5;176m");
DEFINE_COLOR_FUNCTION(purple, "\033[38;5;93m");
DEFINE_COLOR_FUNCTION(rose, "\033[38;5;211m");
DEFINE_COLOR_FUNCTION(rose_gold, "\033[38;5;223m");
DEFINE_COLOR_FUNCTION(ruby, "\033[38;5;196m");
DEFINE_COLOR_FUNCTION(salmon, "\033[38;5;209m");
DEFINE_COLOR_FUNCTION(sapphire, "\033[38;5;21m");
DEFINE_COLOR_FUNCTION(silver, "\033[38;5;7m");
DEFINE_COLOR_FUNCTION(teal, "\033[38;5;14m");
DEFINE_COLOR_FUNCTION(topaz, "\033[38;5;178m");
DEFINE_COLOR_FUNCTION(turquoise, "\033[38;5;45m");
DEFINE_COLOR_FUNCTION(violet, "\033[38;5;177m");

DEFINE_COLOR_FUNCTION(bg_amethyst, "\033[48;5;92m");
DEFINE_COLOR_FUNCTION(bg_amber, "\033[48;5;214m");
DEFINE_COLOR_FUNCTION(bg_apricot, "\033[48;5;215m");
DEFINE_COLOR_FUNCTION(bg_aqua, "\033[48;5;51m");
DEFINE_COLOR_FUNCTION(bg_azure, "\033[48;5;75m");
DEFINE_COLOR_FUNCTION(bg_beige, "\033[48;5;230m");
DEFINE_COLOR_FUNCTION(bg_brown, "\033[48;5;94m");
DEFINE_COLOR_FUNCTION(bg_charcoal, "\033[48;5;240m");
DEFINE_COLOR_FUNCTION(bg_coral, "\033[48;5;203m");
DEFINE_COLOR_FUNCTION(bg_crimson, "\033[48;5;197m");
DEFINE_COLOR_FUNCTION(bg_emerald, "\033[48;5;46m");
DEFINE_COLOR_FUNCTION(bg_gold, "\033[48;5;220m");
DEFINE_COLOR_FUNCTION(bg_indigo, "\033[48;5;54m");
DEFINE_COLOR_FUNCTION(bg_ivory, "\033[48;5;230m");
DEFINE_COLOR_FUNCTION(bg_jade, "\033[48;5;35m");
DEFINE_COLOR_FUNCTION(bg_khaki, "\033[48;5;228m");
DEFINE_COLOR_FUNCTION(bg_lavender, "\033[48;5;183m");
DEFINE_COLOR_FUNCTION(bg_lime, "\033[48;5;10m");
DEFINE_COLOR_FUNCTION(bg_maroon, "\033[48;5;88m");
DEFINE_COLOR_FUNCTION(bg_mint, "\033[48;5;48m");
DEFINE_COLOR_FUNCTION(bg_navy, "\033[48;5;17m");
DEFINE_COLOR_FUNCTION(bg_olive, "\033[48;5;100m");
DEFINE_COLOR_FUNCTION(bg_onyx, "\033[48;5;236m");
DEFINE_COLOR_FUNCTION(bg_orange, "\033[48;5;214m");
DEFINE_COLOR_FUNCTION(bg_peach, "\033[48;5;217m");
DEFINE_COLOR_FUNCTION(bg_pearl, "\033[48;5;231m");
DEFINE_COLOR_FUNCTION(bg_pink, "\033[48;5;13m");
DEFINE_COLOR_FUNCTION(bg_plum, "\033[48;5;176m");
DEFINE_COLOR_FUNCTION(bg_purple, "\033[48;5;93m");
DEFINE_COLOR_FUNCTION(bg_rose, "\033[48;5;211m");
DEFINE_COLOR_FUNCTION(bg_rose_gold, "\033[48;5;223m");
DEFINE_COLOR_FUNCTION(bg_ruby, "\033[48;5;196m");
DEFINE_COLOR_FUNCTION(bg_salmon, "\033[48;5;209m");
DEFINE_COLOR_FUNCTION(bg_sapphire, "\033[48;5;21m");
DEFINE_COLOR_FUNCTION(bg_silver, "\033[48;5;7m");
DEFINE_COLOR_FUNCTION(bg_teal, "\033[48;5;14m");
DEFINE_COLOR_FUNCTION(bg_topaz, "\033[48;5;178m");
DEFINE_COLOR_FUNCTION(bg_turquoise, "\033[48;5;45m");
DEFINE_COLOR_FUNCTION(bg_violet, "\033[48;5;177m");
DEFINE_COLOR_FUNCTION(bg_reset, "\033[49m");

} // namespace colorterm

namespace colorterm {

enum class OutputFormat { PLAIN_TEXT, JSON, XML, YAML, HTML, CSV };

inline std::string format_to_string(OutputFormat format) {
    switch (format) {
        case OutputFormat::PLAIN_TEXT: return "Plain Text";
        case OutputFormat::JSON: return "JSON";
        case OutputFormat::XML: return "XML";
        case OutputFormat::YAML: return "YAML";
        case OutputFormat::HTML: return "HTML";
        case OutputFormat::CSV: return "CSV";
        default: return "Unknown";
    }
}

inline OutputFormat string_to_format(const std::string& str) {
    return (str == "Plain Text") ? OutputFormat::PLAIN_TEXT :
           (str == "JSON") ? OutputFormat::JSON :
           (str == "XML") ? OutputFormat::XML :
           (str == "YAML") ? OutputFormat::YAML :
           (str == "HTML") ? OutputFormat::HTML :
           (str == "CSV") ? OutputFormat::CSV :
           throw std::invalid_argument("Unknown format: " + str);
}

class FormatManager {
public:
    FormatManager() : current_format(OutputFormat::PLAIN_TEXT) {}
    void set_format(OutputFormat format) { std::lock_guard<std::mutex> lock(mutex_); current_format = format; }
    OutputFormat get_format() { std::lock_guard<std::mutex> lock(mutex_); return current_format; }
    std::vector<OutputFormat> list_formats() const { return { OutputFormat::PLAIN_TEXT, OutputFormat::JSON, OutputFormat::XML, OutputFormat::YAML, OutputFormat::HTML, OutputFormat::CSV }; }

private:
    OutputFormat current_format;
    mutable std::mutex mutex_;
};

// Singleton to get the FormatManager instance
inline FormatManager& get_format_manager() { static FormatManager manager; return manager; }

// Helper functions for output formatting    
inline void json_format(std::ostream& stream, const std::string& data) { stream << "{\n \"output\": \"" << data << "\"\n}\n"; }
inline void xml_format(std::ostream& stream, const std::string& data) { stream << "<output>\n " << data << "\n</output>\n"; }
inline void yaml_format(std::ostream& stream, const std::string& data) { stream << "output:\n " << data << "\n"; }
inline void plain_text_format(std::ostream& stream, const std::string& data) { stream << data << "\n"; }
inline void html_format(std::ostream& stream, const std::string& data) { stream << "<html><body><p>" << data << "</p></body></html>\n"; }
inline void csv_format(std::ostream& stream, const std::string& data) { stream << "\"output\"," << "\"" << data << "\"\n"; }

// Custom format detection templates
template <typename T, typename = void>
struct has_custom_json_format : std::false_type {};

template <typename T>
struct has_custom_json_format<T, std::void_t<decltype(custom_json_format(std::declval<std::ostream&>(), std::declval<const T&>()))>> : std::true_type {};

template <typename T, typename = void>
struct has_custom_xml_format : std::false_type {};

template <typename T>
struct has_custom_xml_format<T, std::void_t<decltype(custom_xml_format(std::declval<std::ostream&>(), std::declval<const T&>()))>> : std::true_type {};

template <typename T, typename = void>
struct has_custom_yaml_format : std::false_type {};

template <typename T>
struct has_custom_yaml_format<T, std::void_t<decltype(custom_yaml_format(std::declval<std::ostream&>(), std::declval<const T&>()))>> : std::true_type {};

template <typename T, typename = void>
struct has_custom_plain_text_format : std::false_type {};

template <typename T>
struct has_custom_plain_text_format<T, std::void_t<decltype(custom_plain_text_format(std::declval<std::ostream&>(), std::declval<const T&>()))>> : std::true_type {};

template <typename T, typename = void>
struct has_custom_html_format : std::false_type {};

template <typename T>
struct has_custom_html_format<T, std::void_t<decltype(custom_html_format(std::declval<std::ostream&>(), std::declval<const T&>()))>> : std::true_type {};

template <typename T, typename = void>
struct has_custom_csv_format : std::false_type {};

template <typename T>
struct has_custom_csv_format<T, std::void_t<decltype(custom_csv_format(std::declval<std::ostream&>(), std::declval<const T&>()))>> : std::true_type {};

// Generic template format functions
template <typename T>
inline std::enable_if_t<has_custom_json_format<T>::value> json_format(std::ostream& stream, const T& data) {
    custom_json_format(stream, data);
}

template <typename T>
inline std::enable_if_t<!has_custom_json_format<T>::value> json_format(std::ostream& stream, const T& data) {
    stream << "{\"unsupported_type\": \"No custom JSON format available.\"}";
}

template <typename T>
inline std::enable_if_t<has_custom_xml_format<T>::value> xml_format(std::ostream& stream, const T& data) {
    custom_xml_format(stream, data);
}

template <typename T>
inline std::enable_if_t<!has_custom_xml_format<T>::value> xml_format(std::ostream& stream, const T& data) {
    stream << "<unsupported_type>No custom XML format available.</unsupported_type>";
}

template <typename T>
inline std::enable_if_t<has_custom_yaml_format<T>::value> yaml_format(std::ostream& stream, const T& data) {
    custom_yaml_format(stream, data);
}

template <typename T>
inline std::enable_if_t<!has_custom_yaml_format<T>::value> yaml_format(std::ostream& stream, const T& data) {
    stream << "unsupported_type: No custom YAML format available.\n";
}

template <typename T>
inline std::enable_if_t<has_custom_plain_text_format<T>::value> plain_text_format(std::ostream& stream, const T& data) {
    custom_plain_text_format(stream, data);
}

template <typename T>
inline std::enable_if_t<!has_custom_plain_text_format<T>::value> plain_text_format(std::ostream& stream, const T& data) {
    stream << "No custom plain text format available.";
}

template <typename T>
inline std::enable_if_t<has_custom_html_format<T>::value> html_format(std::ostream& stream, const T& data) {
    custom_html_format(stream, data);
}

template <typename T>
inline std::enable_if_t<!has_custom_html_format<T>::value> html_format(std::ostream& stream, const T& data) {
    stream << "<html><body><p>No custom HTML format available.</p></body></html>";
}

template <typename T>
inline std::enable_if_t<has_custom_csv_format<T>::value> csv_format(std::ostream& stream, const T& data) {
    custom_csv_format(stream, data);
}

template <typename T>
inline std::enable_if_t<!has_custom_csv_format<T>::value> csv_format(std::ostream& stream, const T& data) {
    stream << "key,value\nNo custom CSV format available,";
}

// Function to handle std::string with specified format
inline void apply_output_format(std::ostream& stream, const std::string& data, OutputFormat format) {
    try {
        switch (format) {
            case OutputFormat::PLAIN_TEXT:
                plain_text_format(stream, data);
                break;
            case OutputFormat::JSON:
                json_format(stream, data);
                break;
            case OutputFormat::XML:
                xml_format(stream, data);
                break;
            case OutputFormat::YAML:
                yaml_format(stream, data);
                break;
            case OutputFormat::HTML:
                html_format(stream, data);
                break;
            case OutputFormat::CSV:
                csv_format(stream, data);
                break;
            default:
                throw std::invalid_argument("Unsupported format");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error applying output format: " << e.what() << std::endl;
    }
}

// Template function to handle generic types
template <typename T>
inline void apply_output_format(std::ostream& stream, const T& data) {
    auto format = get_format_manager().get_format();
    try {
        switch (format) {
            case OutputFormat::PLAIN_TEXT:
                plain_text_format(stream, data);
                break;
            case OutputFormat::JSON:
                json_format(stream, data);
                break;
            case OutputFormat::XML:
                xml_format(stream, data);
                break;
            case OutputFormat::YAML:
                yaml_format(stream, data);
                break;
            case OutputFormat::HTML:
                html_format(stream, data);
                break;
            case OutputFormat::CSV:
                csv_format(stream, data);
                break;
            default:
                throw std::invalid_argument("Unsupported format");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error applying output format: " << e.what() << std::endl;
    }
}

// Overloaded function to handle std::ostream and OutputFormat for generic types
template <typename T>
inline void apply_output_format(std::ostream& stream, const T& data, OutputFormat format) {
    try {
        switch (format) {
            case OutputFormat::PLAIN_TEXT:
                plain_text_format(stream, data);
                break;
            case OutputFormat::JSON:
                json_format(stream, data);
                break;
            case OutputFormat::XML:
                xml_format(stream, data);
                break;
            case OutputFormat::YAML:
                yaml_format(stream, data);
                break;
            case OutputFormat::HTML:
                html_format(stream, data);
                break;
            case OutputFormat::CSV:
                csv_format(stream, data);
                break;
            default:
                throw std::invalid_argument("Unsupported format");
        }
    } catch (const std::exception& e) {
        std::cerr << "Error applying output format: " << e.what() << std::endl;
    }
}

// Unified apply_output_format for vector of structures
template <typename T>
inline void apply_output_format(std::ostream& stream, const std::vector<T>& data) {
    auto format = get_format_manager().get_format();
    for (const auto& item : data) {
        switch (format) {
            case OutputFormat::PLAIN_TEXT:
                plain_text_format(stream, item);
                break;
            case OutputFormat::JSON:
                json_format(stream, item);
                break;
            case OutputFormat::XML:
                xml_format(stream, item);
                break;
            case OutputFormat::YAML:
                yaml_format(stream, item);
                break;
            case OutputFormat::HTML:
                html_format(stream, item);
                break;
            case OutputFormat::CSV:
                csv_format(stream, item);
                break;
            default:
                throw std::invalid_argument("Unsupported format");
        }
    }
}

// Unified apply_output_format for maps
template <typename Key, typename T>
inline void apply_output_format(std::ostream& stream, const std::unordered_map<Key, T>& data) {
    auto format = get_format_manager().get_format();
    for (const auto& [key, item] : data) {
        stream << "Key: " << key << "\n";
        switch (format) {
            case OutputFormat::PLAIN_TEXT:
                plain_text_format(stream, item);
                break;
            case OutputFormat::JSON:
                json_format(stream, item);
                break;
            case OutputFormat::XML:
                xml_format(stream, item);
                break;
            case OutputFormat::YAML:
                yaml_format(stream, item);
                break;
            case OutputFormat::HTML:
                html_format(stream, item);
                break;
            case OutputFormat::CSV:
                csv_format(stream, item);
                break;
            default:
                throw std::invalid_argument("Unsupported format");
        }
        stream << "\n";
    }
}

inline void set_output_format(OutputFormat format) {
    get_format_manager().set_format(format);
}

inline OutputFormat get_output_format() {
    return get_format_manager().get_format();
}

inline std::vector<OutputFormat> list_output_formats() {
    return get_format_manager().list_formats();
}

// Function to reset the output format to default
inline void reset_output_format() {
    set_output_format(OutputFormat::PLAIN_TEXT);
}

} // namespace colorterm


#endif // COLORTERM_HPP_
/*
(c) 2024 | Ben Gorlick | https://github.com/bgorlick/colorterm

This benchmark C++ program is designed to compare the performance of the `colorterm` library with the optional `termcolor` library for coloring terminal output. The primary objective is to measure the execution time for various color setting operations provided by `colorterm` and optionally by `termcolor`. 

Key Features:
1. **NullStream**: A custom stream that can be used to discard output during benchmarking to avoid any I/O overhead.
2. **Unified Benchmark Function**: A single function, `colorterm_color_benchmark`, which benchmarks different color setting operations based on a `type` parameter, reducing redundancy and optimizing code structure.
3. **Conditional Compilation**: The code conditionally includes the `termcolor` benchmarks if the `USE_TERMCOLOR` macro is defined, allowing compilation without requiring the `termcolor` library.
4. **Verification Functions**: Functions to verify the full 8-bit and 24-bit color spectrum as well as predefined color functions, ensuring the correctness of color settings.
5. **Gradient and Custom Styles Testing**: Includes tests for gradient text and applying custom styles, showcasing the versatility of the `colorterm` library.

Usage:
To compile and run the benchmark with GCC, use the following commands:
g++ -std=c++17 -O3 -o benchmark benchmark.cpp
./benchmark <iterations> [--verify-8bit] [--verify-24bit] [--verify-predefined] [--verify-all] [--null] [--termcolor]

To compile with clang++ using LLVM you can use the following commands:
clang++ -std=c++17 -O3 -rtlib=compiler-rt -stdlib=libc++ -o benchmark benchmark.cpp \
             -I/usr/local/include/c++/v1 \
             -L/usr/local/lib \
             -lc++ -lc++abi -lunwind -lgcc_s -lgcc -lm -lc -v

Arguments:

<iterations>: Number of iterations for each benchmark test.
--verify-8bit: Verifies the full 8-bit color spectrum.
--verify-24bit: Verifies the full 24-bit color spectrum.
--verify-predefined: Verifies predefined color functions.
--verify-all: Runs all verification tests.
--null: Uses NullStream to discard output during benchmarking.
--termcolor: Includes termcolor benchmarks if the library is available.

Benchmark Example to compare colorterm and termcolor:
./benchmark 10000000 --termcolor --null

Standard Benchmark (recommend to use NullStream for accurate results and to avoid I/O overhead):
./benchmark 10000000 --null

*/

#include <iostream>
#include <chrono>
#include <iomanip>
#include "colorterm.hpp"

#ifdef USE_TERMCOLOR
#include "termcolor/termcolor.hpp"
#endif

class NullBuffer : public std::streambuf {
protected:
    int overflow(int c) override {
        return c;
    }
};

class NullStream : public std::ostream {
public:
    NullStream() : std::ostream(&nullBuffer), nullBuffer() {}
private:
    NullBuffer nullBuffer;
};

template <typename Func>
long long run_benchmark(Func func, size_t iterations, std::ostream &output_stream) {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    func(iterations, output_stream);
    auto end = high_resolution_clock::now();
    return duration_cast<nanoseconds>(end - start).count();
}

void colorterm_color_benchmark(size_t iterations, std::ostream &output_stream, int type) {
    for (size_t i = 0; i < iterations; ++i) {
        switch (type) {
            case 0:
                colorterm::set_color(output_stream, 255, 0, 0) << "Red text ";
                colorterm::set_color(output_stream, 0, 255, 0) << "Green text ";
                colorterm::set_color(output_stream, 0, 0, 255) << "Blue text ";
                break;
            case 1:
                colorterm::red(output_stream) << "Red text ";
                colorterm::green(output_stream) << "Green text ";
                colorterm::blue(output_stream) << "Blue text ";
                break;
            case 2:
                colorterm::apply_color(output_stream, 1) << "Red text ";
                colorterm::apply_color(output_stream, 2) << "Green text ";
                colorterm::apply_color(output_stream, 4) << "Blue text ";
                break;
            case 3:
                colorterm::bg_color<1>(output_stream) << "Red text ";
                colorterm::bg_color<2>(output_stream) << "Green text ";
                colorterm::bg_color<4>(output_stream) << "Blue text ";
                break;
            case 4:
                colorterm::apply_color<255, 0, 0>(output_stream) << "Red text ";
                colorterm::apply_color<0, 255, 0>(output_stream) << "Green text ";
                colorterm::apply_color<0, 0, 255>(output_stream) << "Blue text ";
                break;
            case 5:
                colorterm::bg_color<255, 0, 0>(output_stream) << "Red text ";
                colorterm::bg_color<0, 255, 0>(output_stream) << "Green text ";
                colorterm::bg_color<0, 0, 255>(output_stream) << "Blue text ";
                break;
        }
        colorterm::reset(output_stream) << "\n";
    }
}

#ifdef USE_TERMCOLOR
void termcolor_benchmark(size_t iterations, std::ostream &output_stream) {
    for (size_t i = 0; i < iterations; ++i) {
        output_stream << termcolor::red << "Red text "
                      << termcolor::green << "Green text "
                      << termcolor::blue << "Blue text "
                      << termcolor::reset << "\n";
    }
}
#endif

void verify_full_8bit_spectrum() {
    colorterm::enable_global_color();
    for (int i = 0; i < 256; ++i) {
        colorterm::color(std::cout, static_cast<uint8_t>(i));
        std::cout << std::setw(3) << i << " ";
        if ((i + 1) % 16 == 0) {
            std::cout << "\n";
        }
    }
    colorterm::reset(std::cout) << "\n";
}

void verify_full_24bit_spectrum() {
    colorterm::enable(std::cout); // enables
    for (int r = 0; r < 256; r += 51) {
        for (int g = 0; g < 256; g += 51) {
            for (int b = 0; b < 256; b += 51) {
                colorterm::apply_rgb_color(std::cout, static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b));
                std::cout << "(" << std::setw(3) << r << "," << std::setw(3) << g << "," << std::setw(3) << b << ") ";
                colorterm::reset(std::cout) << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
    colorterm::reset(std::cout) << "\n";
}

void verify_color_functions() {

    colorterm::enable(std::cout);
    std::cout << "Enabled colorterm: " << std::endl;

    colorterm::bg_white(std::cout) << colorterm::black << "Unit Test: (set_color)" << colorterm::fullreset << "\n";

    colorterm::set_color(std::cout, 255, 0, 0) << "set_color test: Red text " << colorterm::reset << "\n";
    colorterm::set_color(std::cout, 0, 255, 0) << "set_color test: Green text " << colorterm::reset << "\n";
    colorterm::set_color(std::cout, 0, 0, 255) << "set_color test: Blue text " << colorterm::reset << "\n\n";


    colorterm::Logger::info("This is an info message.");
    colorterm::Logger::debug("This is a debug message.");
    colorterm::Logger::warn("This is a warning message.");
    colorterm::Logger::error("This is an error message.");
    colorterm::Logger::fatal("This is a fatal error message.");
    colorterm::Logger::trace("This is a trace message.");


    colorterm::bg_white(std::cout) << colorterm::black << "standard colors:" << colorterm::fullreset << "\n";
    colorterm::red(std::cout) << "red ";
    colorterm::green(std::cout) << "green ";
    colorterm::yellow(std::cout) << "yellow ";
    colorterm::blue(std::cout) << "blue ";
    colorterm::magenta(std::cout) << "magenta ";
    colorterm::cyan(std::cout) << "cyan ";
    colorterm::white(std::cout) << "white ";
    colorterm::reset(std::cout) << "\n\n";

    colorterm::bg_white(std::cout) << colorterm::black << "bright colors:" << colorterm::fullreset << "\n";
    colorterm::bright_red(std::cout) << "bright_red ";
    colorterm::bright_green(std::cout) << "bright_green ";
    colorterm::bright_yellow(std::cout) << "bright_yellow ";
    colorterm::bright_blue(std::cout) << "bright_blue ";
    colorterm::bright_magenta(std::cout) << "bright_magenta ";
    colorterm::bright_cyan(std::cout) << "bright_cyan ";
    colorterm::bright_white(std::cout) << "bright_white ";
    colorterm::reset(std::cout) << "\n\n";

    colorterm::bg_white(std::cout) << colorterm::black << "light colors:" << colorterm::fullreset << "\n";
    colorterm::light_red(std::cout) << "light_red ";
    colorterm::light_green(std::cout) << "light_green ";
    colorterm::light_yellow(std::cout) << "light_yellow ";
    colorterm::light_blue(std::cout) << "light_blue ";
    colorterm::light_magenta(std::cout) << "light_magenta ";
    colorterm::light_cyan(std::cout) << "light_cyan ";
    colorterm::light_white(std::cout) << "light_white ";
    colorterm::reset(std::cout) << "\n\n";

    colorterm::bg_white(std::cout) << colorterm::black << "bold colors:" << colorterm::fullreset << "\n";
    colorterm::bold_red(std::cout) << "bold_red ";
    colorterm::bold_green(std::cout) << "bold_green ";
    colorterm::bold_yellow(std::cout) << "bold_yellow ";
    colorterm::bold_blue(std::cout) << "bold_blue ";
    colorterm::bold_magenta(std::cout) << "bold_magenta ";
    colorterm::bold_cyan(std::cout) << "bold_cyan ";
    colorterm::bold_white(std::cout) << "bold_white ";
    colorterm::reset(std::cout) << "\n\n";

    colorterm::bg_white(std::cout) << colorterm::black << "background colors:" << colorterm::fullreset << "\n";
    colorterm::bg_red(std::cout) << "bg_red ";
    colorterm::bg_green(std::cout) << "bg_green ";
    colorterm::bg_yellow(std::cout) << "bg_yellow ";
    colorterm::bg_blue(std::cout) << "bg_blue ";
    colorterm::bg_magenta(std::cout) << "bg_magenta ";
    colorterm::bg_cyan(std::cout) << "bg_cyan ";
    colorterm::bg_white(std::cout) << colorterm::black << "bg_white ";
    colorterm::reset(std::cout) << "\n\n";

    colorterm::bg_white(std::cout) << colorterm::black << "Extra colors:" << colorterm::fullreset << "\n";
    colorterm::amethyst(std::cout) << "amethyst ";
    colorterm::amber(std::cout) << "amber ";
    colorterm::apricot(std::cout) << "apricot ";
    colorterm::aqua(std::cout) << "aqua ";
    colorterm::azure(std::cout) << "azure ";
    colorterm::beige(std::cout) << "beige ";
    colorterm::brown(std::cout) << "brown ";
    colorterm::charcoal(std::cout) << "charcoal ";
    colorterm::coral(std::cout) << "coral ";
    colorterm::crimson(std::cout) << "crimson ";
    colorterm::emerald(std::cout) << "emerald ";
    colorterm::gold(std::cout) << "gold ";
    colorterm::indigo(std::cout) << "indigo ";
    colorterm::reset(std::cout) << "\n";
    colorterm::ivory(std::cout) << "ivory ";
    colorterm::jade(std::cout) << "jade ";
    colorterm::khaki(std::cout) << "khaki ";
    colorterm::lavender(std::cout) << "lavender ";
    colorterm::lime(std::cout) << "lime ";
    colorterm::maroon(std::cout) << "maroon ";
    colorterm::mint(std::cout) << "mint ";
    colorterm::navy(std::cout) << "navy ";
    colorterm::olive(std::cout) << "olive ";
    colorterm::onyx(std::cout) << "onyx ";
    colorterm::orange(std::cout) << "orange ";
    colorterm::peach(std::cout) << "peach ";
    colorterm::pearl(std::cout) << "pearl ";
    colorterm::pink(std::cout) << "pink ";
    colorterm::plum(std::cout) << "plum ";
    colorterm::reset(std::cout) << "\n";
    colorterm::purple(std::cout) << "purple ";
    colorterm::rose(std::cout) << "rose ";
    colorterm::rose_gold(std::cout) << "rose gold ";
    colorterm::ruby(std::cout) << "ruby ";
    colorterm::salmon(std::cout) << "salmon ";
    colorterm::sapphire(std::cout) << "sapphire ";
    colorterm::silver(std::cout) << "silver ";
    colorterm::teal(std::cout) << "teal ";
    colorterm::topaz(std::cout) << "topaz ";
    colorterm::turquoise(std::cout) << "turquoise ";
    colorterm::violet(std::cout) << "violet ";
    colorterm::reset(std::cout) << "\n\n";

    colorterm::bg_white(std::cout) << colorterm::black << "Extra background colors:" << colorterm::fullreset << "\n";
    colorterm::bg_amethyst(std::cout) << "bg_amethyst ";
    colorterm::black(std::cout) << "";
    colorterm::bg_amber(std::cout) << "bg_amber ";
    colorterm::bg_apricot(std::cout) << "bg_apricot ";
    colorterm::bg_aqua(std::cout) << "bg_aqua ";
    colorterm::bg_azure(std::cout) << "bg_azure ";
    colorterm::bg_beige(std::cout) << "bg_beige ";
    colorterm::white(std::cout) << "";
    colorterm::bg_brown(std::cout) << "bg_brown ";
    colorterm::bg_charcoal(std::cout) << "bg_charcoal ";
    colorterm::bg_coral(std::cout) << "bg_coral ";
    colorterm::bg_crimson(std::cout) << "bg_crimson ";
    colorterm::bg_emerald(std::cout) << "bg_emerald ";
    colorterm::bg_gold(std::cout) << "bg_gold ";
    colorterm::bg_indigo(std::cout) << "bg_indigo ";
    colorterm::bg_reset(std::cout) << colorterm::fullreset << "\n";
    colorterm::black(std::cout) << "";
    colorterm::bg_ivory(std::cout) << "bg_ivory ";
    colorterm::bg_jade(std::cout) << "bg_jade ";
    colorterm::bg_khaki(std::cout) << "bg_khaki ";
    colorterm::bg_lavender(std::cout) << "bg_lavender ";
    colorterm::bg_lime(std::cout) << "bg_lime ";
    colorterm::bg_maroon(std::cout) << "bg_maroon ";
    colorterm::bg_mint(std::cout) << "bg_mint ";
    colorterm::white(std::cout) << "";
    colorterm::bg_navy(std::cout) << "bg_navy ";
    colorterm::black(std::cout) << "";
    colorterm::bg_olive(std::cout) << "bg_olive ";
    colorterm::bg_onyx(std::cout) << "bg_onyx ";
    colorterm::bg_orange(std::cout) << "bg_orange ";
    colorterm::bg_peach(std::cout) << "bg_peach ";
    colorterm::bg_pearl(std::cout) << "bg_pearl ";
    colorterm::bg_pink(std::cout) << "bg_pink ";
    colorterm::bg_plum(std::cout) << "bg_plum " << colorterm::fullreset << "\n";
    colorterm::bg_purple(std::cout) << "bg_purple ";
    colorterm::black(std::cout) << "";
    colorterm::bg_rose(std::cout) << "bg_rose ";
    colorterm::bg_rose_gold(std::cout) << "bg_rose gold ";
    colorterm::bg_ruby(std::cout) << "bg_ruby ";
    colorterm::bg_salmon(std::cout) << "bg_salmon ";
    colorterm::white(std::cout) << "";
    colorterm::bg_sapphire(std::cout) << "bg_sapphire ";
    colorterm::black(std::cout) << "";
    colorterm::bg_silver(std::cout) << "bg_silver ";
    colorterm::bg_teal(std::cout) << "bg_teal ";
    colorterm::bg_topaz(std::cout) << "bg_topaz ";
    colorterm::bg_turquoise(std::cout) << "bg_turquoise ";
    colorterm::bg_violet(std::cout) << "bg_violet ";
    colorterm::white(std::cout) << "";
    colorterm::bg_reset(std::cout) << "bg_reset ";
    colorterm::fullreset(std::cout) << "\n\n";

    colorterm::list_custom_colors();
    colorterm::set_custom_color("error", "\033[38;5;196m");


    colorterm::custom_color(std::cout, "error") << "This is an example of setting a custom color as 'error' for error messages." << colorterm::reset << "\n";


    colorterm::inspect_custom_color("error");

    colorterm::set_custom_color("custom_green_bg", [](std::ostream& os) { os << "\033[42m"; });
    colorterm::set_custom_color("custom_bold_underline", [](std::ostream& os) { os << "\033[1m\033[4m"; });
    colorterm::inspect_custom_color("custom_green_bg");
    colorterm::inspect_custom_color("custom_bold_underline");

    colorterm::set_custom_color_predefined("error_new", "bold_red");
    colorterm::custom_color(std::cout, "error") << "This is an example of setting a custom color as 'error' for error messages." << colorterm::reset << "\n";
    colorterm::inspect_custom_color("error_new");

    colorterm::fullreset(std::cout) << "\n";
    colorterm::bg_white(std::cout) << colorterm::black << "Gradient Color Testing:" << colorterm::fullreset << "\n";
 
 
 
    // Test Gradients
    
    colorterm::apply_gradient(std::cout, "Gradient Text - Making a long sentence to fully test the gradient text function. ABCDEFGHIJKLMNOPQRSTUVWXYZ - The quick brown fox jumps over the lazy dog. ABCDEFGHIJKLMNOPQRSTUVWXYZ - The quick brown fox jumps over the lazy dog", 255, 0, 0, 0, 0, 255) << std::endl;
    colorterm::apply_gradient(std::cout, "Gradient Text - Making a long sentence to fully test the gradient text function", 0, 255, 0, 255, 0, 0) << std::endl;
    colorterm::apply_gradient(std::cout, "Gradient Text - Making a long sentence to fully test the gradient text function", 0, 0, 255, 0, 255, 255) << std::endl;
    colorterm::apply_gradient(std::cout, "Gradient Text - Making a long sentence to fully test the gradient text function", 255, 255, 0, 255, 0, 255) << std::endl;
    colorterm::apply_gradient(std::cout, "Gradient Text - Making a long sentence to fully test the gradient text function", 255, 0, 255, 0, 255, 0) << std::endl;
    colorterm::apply_gradient(std::cout, "Gradient Text - Making a long sentence to fully test the gradient text function", 0, 255, 255, 255, 255, 0) << std::endl;
    colorterm::apply_gradient(std::cout, "Gradient Text - Making a long sentence to fully test the gradient text function", 255, 255, 255, 0, 0, 0) << std::endl;

    colorterm::fullreset(std::cout) << "\n";
    colorterm::bg_white(std::cout) << colorterm::black << "Apply Styles Testing:" << colorterm::fullreset << "\n";
    colorterm::apply_styles(std::cout, "underline", "italic", "bold_blue") << "This text should be bold, blue, and underlined, and italicized." << colorterm::reset << std::endl;
    colorterm::style_text("This text should be bold, red, italic, and underlined.\n", "bold_red", "italic", "underline");

    colorterm::fullreset(std::cout) << "\n";

}

void print_comparison(const std::string& name, long long colorterm_duration, long long termcolor_duration) {
#ifdef USE_TERMCOLOR
    double percentage_diff;
    if (termcolor_duration != 0) {
        if (colorterm_duration < termcolor_duration) {
            percentage_diff = ((termcolor_duration - colorterm_duration) / (double)termcolor_duration) * 100.0;
            std::cout << name << " is faster by " << percentage_diff << "% than termcolor | " << "Time (colorterm vs termcolor): " << ((double)colorterm_duration / 1000.0) << "ms vs " << ((double)termcolor_duration / 1000.0) << "ms\n\n";
        } else {
            percentage_diff = ((colorterm_duration - termcolor_duration) / (double)colorterm_duration) * 100.0;
            std::cout << "termcolor is faster than " << name << " by " << percentage_diff << "% |" << "Time (colorterm vs termcolor): " << ((double)colorterm_duration / 1000.0) << "ms vs " << ((double)termcolor_duration / 1000.0) << "ms\n\n";
        }
    } else {
        std::cout << "termcolor duration is zero, cannot compare\n";
    }
#endif
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <iterations> [--verify-8bit] [--verify-24bit] [--verify-predefined] [--verify-all] [--null] [--termcolor]\n";
        return 1;
    }

    if (std::string(argv[1]).rfind("--verify-", 0) == 0) {
        std::string option = argv[1];
        if (option == "--verify-8bit") {
            verify_full_8bit_spectrum();
            return 0;
        } else if (option == "--verify-24bit") {
            verify_full_24bit_spectrum();
            return 0;
        } else if (option == "--verify-predefined") {
            verify_color_functions();
            return 0;
        } else if (option == "--verify-all") {
            verify_full_8bit_spectrum();
            verify_full_24bit_spectrum();
            verify_color_functions();
            return 0;
        } else {
            std::cerr << "Unknown verification option: " << option << "\n";
            return 1;
        }
    }

    size_t iterations;
    try {
        iterations = std::stoull(argv[1]);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid number of iterations: " << argv[1] << "\n";
        return 1;
    }

    bool compare_with_termcolor = false;
    NullStream null_stream;
    std::ostream* output_stream = &std::cout;

    for (int i = 2; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--null") {
            output_stream = &null_stream;
        } else if (arg == "--termcolor") {
            compare_with_termcolor = true;
        }
    }

    long long colorterm_set_color_duration = run_benchmark([](size_t iter, std::ostream& os){ colorterm_color_benchmark(iter, os, 0); }, iterations, *output_stream);
    long long colorterm_named_color_duration = run_benchmark([](size_t iter, std::ostream& os){ colorterm_color_benchmark(iter, os, 1); }, iterations, *output_stream);
    long long colorterm_color_8bit_duration = run_benchmark([](size_t iter, std::ostream& os){ colorterm_color_benchmark(iter, os, 2); }, iterations, *output_stream);
    long long colorterm_bg_color_8bit_duration = run_benchmark([](size_t iter, std::ostream& os){ colorterm_color_benchmark(iter, os, 3); }, iterations, *output_stream);
    long long colorterm_color_rgb_duration = run_benchmark([](size_t iter, std::ostream& os){ colorterm_color_benchmark(iter, os, 4); }, iterations, *output_stream);
    long long colorterm_bg_color_rgb_duration = run_benchmark([](size_t iter, std::ostream& os){ colorterm_color_benchmark(iter, os, 5); }, iterations, *output_stream);
    
#ifdef USE_TERMCOLOR
    long long termcolor_duration = 0;
    if (compare_with_termcolor) {
        termcolor_duration = run_benchmark(termcolor_benchmark, iterations, *output_stream);
    }
#endif

    std::cout << std::fixed << std::setprecision(2);

#ifdef USE_TERMCOLOR
    if (compare_with_termcolor) {
        print_comparison("colorterm set_color", colorterm_set_color_duration, termcolor_duration);
        print_comparison("colorterm named color", colorterm_named_color_duration, termcolor_duration);
        print_comparison("colorterm color (8-bit)", colorterm_color_8bit_duration, termcolor_duration);
        print_comparison("colorterm bg_color (8-bit)", colorterm_bg_color_8bit_duration, termcolor_duration);
        print_comparison("colorterm color (RGB)", colorterm_color_rgb_duration, termcolor_duration);
        print_comparison("colorterm bg_color (RGB)", colorterm_bg_color_rgb_duration, termcolor_duration);
    }
#endif

    return 0;
}

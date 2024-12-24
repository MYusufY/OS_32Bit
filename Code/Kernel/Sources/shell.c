#include "../Includes/shell.h"
#include "../Includes/memory_manager.h"
#include <string.h>

extern TextStyle backGroundColor;
extern uint16_t keyboard_cursor_position;

void scrollIfNeeded(int row) {
    if (row >= VGA_ROWS) {
        scroll_screen();
        row = VGA_ROWS - 1;
    }
    setCursorPosition(row, 0);
}

void handleBackgroundColor(const char* input) {
    if (input && input[0] != '\0') {
        backGroundColor = mapInputToColor(input);
    }
}

void clear() {
    clearScreen();
    setCursorPosition(2, 0);
    keyboard_cursor_position = 2 * VGA_COLS;
}

void show_memory_info() {
    size_t total = get_total_memory_mb();
    size_t used = get_used_memory_mb();
    size_t free = get_free_memory_mb();
    
    TextStyle defaultStyle = backGroundColor;  // Use the current background color
    
    printf_with_style("Memory Information:\n", defaultStyle);
    printf_with_style("Total Memory: ", defaultStyle);
    printf_with_style_num(total, defaultStyle);
    printf_with_style(" MB\n", defaultStyle);
    
    printf_with_style("Used Memory:  ", defaultStyle);
    printf_with_style_num(used, defaultStyle);
    printf_with_style(" MB\n", defaultStyle);
    
    printf_with_style("Free Memory:  ", defaultStyle);
    printf_with_style_num(free, defaultStyle);
    printf_with_style(" MB\n", defaultStyle);
    
    printf_with_style("\nMemory Usage: |", defaultStyle);
    int bars = 20;
    int used_bars = (used * bars) / total;
    
    for (int i = 0; i < bars; i++) {
        if (i < used_bars) {
            printf_with_style("I", defaultStyle);
        } else {
            printf_with_style("-", defaultStyle);
        }
    }
    printf_with_style("|\n", defaultStyle);
}

void process_command(const char* command) {
    TextStyle defaultStyle = backGroundColor;  // Use the current background color
    
    if (strcmp(command, "clear") == 0) {
        clear();
    } 
    else if (strcmp(command, "free") == 0) {
        show_memory_info();
    }
    else if (strncmp(command, "bgcolor ", 8) == 0) {
        handleBackgroundColor(command + 8);
    }
    else {
        printf_with_style("Unknown command: ", defaultStyle);
        printf_with_style(command, defaultStyle);
        printf_with_style("\n", defaultStyle);
    }
}
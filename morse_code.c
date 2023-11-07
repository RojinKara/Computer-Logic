/**
 * The given template is a guideline for your coursework only.
 * You are free to edit/create any functions and variables.
 * You can add extra C files if required.
*/


#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "includes/seven_segment.h"

#define BUTTON_PIN            16    // Pin 21 (GPIO 16)

uint64_t t;
uint64_t t2;
uint64_t tOriginal;
char inputs[99]; //character array representing . and -
// --------------------------------------------------------------------
// declare the function definitions, e.g, decoder(...); and ther functions
// given the user input, you can decode if the input is a character
void decoder();

// check if the button press is a dot or a dash
void checkButton(int i);
void wipeArray();

int main() {
    stdio_init_all();
    seven_segment_init();
    printf("HELLO!");
    seven_segment_show(8);
    sleep_ms(2000);

    // Turn the seven segment display off when the program starts.
    seven_segment_off();

    // Initialize the button's GPIO pin.
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_down(BUTTON_PIN); // Pull the button pin towards ground (with an internal pull-down resistor).


    tOriginal = time_us_64();
    t = time_us_64();
    bool toDecode = false;
    while (true) {
        t = time_us_64();
        sleep_ms(1);
        while (gpio_get(BUTTON_PIN)) {
            seven_segment_show(36);
            tOriginal = time_us_64();
            toDecode = true;
        }
        t = (uint64_t) (time_us_64() - t);

        if (t < 250000 && t > 50000) {
            printf(". detected\n");
            checkButton(1);
        } else if (t > 700000){
            printf("button held too long\n");
            seven_segment_show(8);
            wipeArray();
            sleep_ms(200);
            seven_segment_off();
        } else if (t > 250000) {
            checkButton(2);
            printf("- detected\n");
        }
        t2 = (uint64_t) (time_us_64() - tOriginal);
        if (t2 > 5000 && t2 < 10000){
            seven_segment_off();
        }
        if (t2 > 400000) {
            if (toDecode) {
                decoder();
                printf("decode time\n");
                toDecode = false;
            }
        }
    }
}

int calcLength() {
    int temp = 0;
    for (int i = 0; i < sizeof(inputs); i++) {
        if (inputs[i] != '\0') {
            temp++;
        }
    }
    return temp;
}

void wipeArray() {
    for (int i = 0; i < sizeof(inputs); i++) {
        inputs[i] = '\0';
    }
}

void decoder() {
    if (calcLength() > 5) {
        printf("Morse Code too long, please enter a valid input\n");
        wipeArray();
    } else {
        if (calcLength() == 1) {
            if (inputs[0] == '.') { //.
                seven_segment_show(14); //E
            } else if (inputs[0] == '-') { //-
                seven_segment_show(29);  //T
            } else {
                printf("error while decoding\n");
            }
        } else if (calcLength() == 2) {
            if (inputs[0] == '.' && inputs[1] == '.') { //..
                seven_segment_show(18); //I
            } else if (inputs[0] == '.' && inputs[1] == '-') { //.-
                seven_segment_show(10); //A
            } else if (inputs[0] == '-' && inputs[1] == '.') { //-.
                seven_segment_show(23); //N
            } else if (inputs[0] == '-' && inputs[1] == '-') { //--
                seven_segment_show(22); //M
            } else {
                printf("error while decoding\n");
            }
        } else if (calcLength() == 3) {
            if (inputs[0] == '.' && inputs[1] == '.' && inputs[2] == '.') { //...
                seven_segment_show(28); //S
            } else if (inputs[0] == '.' && inputs[1] == '.' && inputs[2] == '-') { //..-
                seven_segment_show(30); //U
            } else if (inputs[0] == '.' && inputs[1] == '-' && inputs[2] == '.') { //.-.
                seven_segment_show(27); //R
            } else if (inputs[0] == '.' && inputs[1] == '-' && inputs[2] == '-') { //.--
                seven_segment_show(32); //W
            } else if (inputs[0] == '-' && inputs[1] == '.' && inputs[2] == '.') { //-..
                seven_segment_show(13); //D
            } else if (inputs[0] == '-' && inputs[1] == '.' && inputs[2] == '-') { //-.-
                seven_segment_show(20); //K
            } else if (inputs[0] == '-' && inputs[1] == '-' && inputs[2] == '.') { //--.
                seven_segment_show(16); //G
            } else if (inputs[0] == '-' && inputs[1] == '-' && inputs[2] == '-') { //---
                seven_segment_show(24); //O
            } else {
                printf("error while decoding\n");
            }
        } else if (calcLength() == 4) {
            if (inputs[0] == '.' && inputs[1] == '.' && inputs[2] == '.' && inputs[3] == '-') {//...-
                seven_segment_show(31); //v
            } else if (inputs[0] == '-' && inputs[1] == '.' && inputs[2] == '.' && inputs[3] == '.') {//-...
                seven_segment_show(11); //B
            } else if (inputs[0] == '-' && inputs[1] == '.' && inputs[2] == '-' && inputs[3] == '.') {//-.-.
                seven_segment_show(12); //C
            } else if (inputs[0] == '.' && inputs[1] == '.' && inputs[2] == '-' && inputs[3] == '.') {//..-.
                seven_segment_show(15); //F
            } else if (inputs[0] == '.' && inputs[1] == '.' && inputs[2] == '.' && inputs[3] == '.') {//....
                seven_segment_show(17); //H
            } else if (inputs[0] == '.' && inputs[1] == '-' && inputs[2] == '-' && inputs[3] == '-') {//.---
                seven_segment_show(19); //J
            } else if (inputs[0] == '.' && inputs[1] == '-' && inputs[2] == '.' && inputs[3] == '.') {//.-..
                seven_segment_show(21); //L
            } else if (inputs[0] == '.' && inputs[1] == '-' && inputs[2] == '-' && inputs[3] == '.') {//.--.
                seven_segment_show(25); //P
            } else if (inputs[0] == '-' && inputs[1] == '-' && inputs[2] == '.' && inputs[3] == '-') {//--.-
                seven_segment_show(26); //Q
            } else if (inputs[0] == '-' && inputs[1] == '.' && inputs[2] == '.' && inputs[3] == '-') {//-..-
                seven_segment_show(33); //X
            } else if (inputs[0] == '-' && inputs[1] == '.' && inputs[2] == '-' && inputs[3] == '-') {//-.--
                seven_segment_show(34); //Y
            } else if (inputs[0] == '-' && inputs[1] == '-' && inputs[2] == '.' && inputs[3] == '.') {//--..
                seven_segment_show(35); //Z
            } else {
                printf("error while decoding\n");
            }
        } else if (calcLength() == 5) {
            if (inputs[0] == '-' && inputs[1] == '-' && inputs[2] == '-' && inputs[3] == '-' && inputs[4] == '-') {
                seven_segment_show(0); //0
            } else if (inputs[0] == '.' && inputs[1] == '-' && inputs[2] == '-' && inputs[3] == '-' &&
                       inputs[4] == '-') {
                seven_segment_show(1); //1
            } else if (inputs[0] == '.' && inputs[1] == '.' && inputs[2] == '-' && inputs[3] == '-' &&
                       inputs[4] == '-') {
                seven_segment_show(2); //2
            } else if (inputs[0] == '.' && inputs[1] == '.' && inputs[2] == '.' && inputs[3] == '-' &&
                       inputs[4] == '-') {
                seven_segment_show(3); //3
            } else if (inputs[0] == '.' && inputs[1] == '.' && inputs[2] == '.' && inputs[3] == '.' &&
                       inputs[4] == '-') {
                seven_segment_show(4); //4
            } else if (inputs[0] == '.' && inputs[1] == '.' && inputs[2] == '.' && inputs[3] == '.' &&
                       inputs[4] == '.') {
                seven_segment_show(5); //5
            } else if (inputs[0] == '-' && inputs[1] == '.' && inputs[2] == '.' && inputs[3] == '.' &&
                       inputs[4] == '.') {
                seven_segment_show(6); //6
            } else if (inputs[0] == '-' && inputs[1] == '-' && inputs[2] == '.' && inputs[3] == '.' &&
                       inputs[4] == '.') {
                seven_segment_show(7); //7
            } else if (inputs[0] == '-' && inputs[1] == '-' && inputs[2] == '-' && inputs[3] == '.' &&
                       inputs[4] == '.') {
                seven_segment_show(8); //8
            } else if (inputs[0] == '-' && inputs[1] == '-' && inputs[2] == '-' && inputs[3] == '-' &&
                       inputs[4] == '.') {
                seven_segment_show(9); //9
            } else {
                printf("error while decoding\n");
            }
        }
        wipeArray();
    }
}

void checkButton(int input) {
    seven_segment_off();
    for (int i = 0; i < sizeof(inputs); i++) {
        if (inputs[i] == '\0') {
            if (input < 2) {
                inputs[i] = '.';
            } else {
                inputs[i] = '-';
            }
            break;
        }
    }
}


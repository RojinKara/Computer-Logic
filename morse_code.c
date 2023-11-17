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

uint64_t t; //time before the button is pressed
uint64_t t2; //temporary variable to check how long its been since button released
uint64_t tOriginal; //time when button is released
char inputs[99]; //character array representing . and -

void decoder();
void checkButton(int i);
void wipeArray();
int calcLength();

int main() {
    stdio_init_all();
    seven_segment_init();

    printf("HELLO!\n");
    seven_segment_show(36);
    sleep_ms(2000);
    seven_segment_off();

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_down(BUTTON_PIN); // Pull the button pin towards ground (with an internal pull-down resistor).

    tOriginal = time_us_64(); //sets the time when it starts so values arent too large
    t = time_us_64();
    bool toDecode = false; //whether the decoder should be allowed to run or not (makes sure it only runs once)
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
            //printf(". detected\n");
            checkButton(1);
        } else if (t > 700000){
            printf("button held too long\n");
            seven_segment_show(8);
            wipeArray();
            sleep_ms(200);
            seven_segment_off();
        } else if (t > 250000) {
            checkButton(2);
            //printf("- detected\n");
        }

        t2 = (uint64_t) (time_us_64() - tOriginal);
        if (t2 > 5000 && t2 < 10000){
            seven_segment_off();
        }

        if (t2 > 400000) {
            if (toDecode) {
                printf("%s %s", inputs, ": ");
                decoder();
                printf("decode time\n");
                toDecode = false;
            }
        }
    }
}
/*calcLength() - goes through the array and checks how many actual values there are and returns the amount of */
int calcLength() {
    int temp = 0;
    for (int i = 0; i < sizeof(inputs); i++) {
        if (inputs[i] == '\0') {
            return temp;
        }
        temp++;
    }
}
/*wipeArray() - after the character is displayed, the array containing the morsecode is wiped using this function. it
 * sets all indexes to null*/
void wipeArray() {
    for (int i = 0; i < sizeof(inputs); i++) {
        inputs[i] = '\0';
    }
}
/*decoder() - called once no button input for 400ms. takes the array of inputs and converts it into a character
 * and outputs onto the seven segment display*/
void decoder() {
    if (calcLength() > 5) {
        printf("Morse Code too long, please enter a valid input\n");
        wipeArray();
    } else {
        if (calcLength() == 1) {
            if (inputs[0] == '.') { //.
                seven_segment_show(14); //E
                printf("E\n");
            } else if (inputs[0] == '-') { //-
                seven_segment_show(29);  //T
                printf("T\n");
            } else {
                printf("error while decoding\n");
            }
        } else if (calcLength() == 2) {
            if (inputs[0] == '.' && inputs[1] == '.') { //..
                seven_segment_show(18); //I
                printf("I\n");
            } else if (inputs[0] == '.' && inputs[1] == '-') { //.-
                seven_segment_show(10); //A
                printf("A\n");
            } else if (inputs[0] == '-' && inputs[1] == '.') { //-.
                seven_segment_show(23); //N
                printf("N\n");
            } else if (inputs[0] == '-' && inputs[1] == '-') { //--
                seven_segment_show(22); //M
                printf("M\n");
            } else {
                printf("error while decoding\n");
            }
        } else if (calcLength() == 3) {
            if (inputs[0] == '.' && inputs[1] == '.' && inputs[2] == '.') { //...
                seven_segment_show(28); //S
                printf("S\n");
            } else if (inputs[0] == '.' && inputs[1] == '.' && inputs[2] == '-') { //..-
                seven_segment_show(30); //U
                printf("U\n");
            } else if (inputs[0] == '.' && inputs[1] == '-' && inputs[2] == '.') { //.-.
                seven_segment_show(27); //R
                printf("R\n");
            } else if (inputs[0] == '.' && inputs[1] == '-' && inputs[2] == '-') { //.--
                seven_segment_show(32); //W
                printf("W\n");
            } else if (inputs[0] == '-' && inputs[1] == '.' && inputs[2] == '.') { //-..
                seven_segment_show(13); //D
                printf("D\n");
            } else if (inputs[0] == '-' && inputs[1] == '.' && inputs[2] == '-') { //-.-
                seven_segment_show(20); //K
                printf("K\n");
            } else if (inputs[0] == '-' && inputs[1] == '-' && inputs[2] == '.') { //--.
                seven_segment_show(16); //G
                printf("G\n");
            } else if (inputs[0] == '-' && inputs[1] == '-' && inputs[2] == '-') { //---
                seven_segment_show(24); //O
                printf("O\n");
            } else {
                printf("error while decoding\n");
            }
        } else if (calcLength() == 4) {
            if (inputs[0] == '.' && inputs[1] == '.' && inputs[2] == '.' && inputs[3] == '-') {//...-
                seven_segment_show(31); //v
                printf("V\n");
            } else if (inputs[0] == '-' && inputs[1] == '.' && inputs[2] == '.' && inputs[3] == '.') {//-...
                seven_segment_show(11); //B
                printf("B\n");
            } else if (inputs[0] == '-' && inputs[1] == '.' && inputs[2] == '-' && inputs[3] == '.') {//-.-.
                seven_segment_show(12); //C
                printf("C\n");
            } else if (inputs[0] == '.' && inputs[1] == '.' && inputs[2] == '-' && inputs[3] == '.') {//..-.
                seven_segment_show(15); //F
                printf("F\n");
            } else if (inputs[0] == '.' && inputs[1] == '.' && inputs[2] == '.' && inputs[3] == '.') {//....
                seven_segment_show(17); //H
                printf("H\n");
            } else if (inputs[0] == '.' && inputs[1] == '-' && inputs[2] == '-' && inputs[3] == '-') {//.---
                seven_segment_show(19); //J
                printf("J\n");
            } else if (inputs[0] == '.' && inputs[1] == '-' && inputs[2] == '.' && inputs[3] == '.') {//.-..
                seven_segment_show(21); //L
                printf("L\n");
            } else if (inputs[0] == '.' && inputs[1] == '-' && inputs[2] == '-' && inputs[3] == '.') {//.--.
                seven_segment_show(25); //P
                printf("P\n");
            } else if (inputs[0] == '-' && inputs[1] == '-' && inputs[2] == '.' && inputs[3] == '-') {//--.-
                seven_segment_show(26); //Q
                printf("Q\n");
            } else if (inputs[0] == '-' && inputs[1] == '.' && inputs[2] == '.' && inputs[3] == '-') {//-..-
                seven_segment_show(33); //X
                printf("X\n");
            } else if (inputs[0] == '-' && inputs[1] == '.' && inputs[2] == '-' && inputs[3] == '-') {//-.--
                seven_segment_show(34); //Y
                printf("Y\n");
            } else if (inputs[0] == '-' && inputs[1] == '-' && inputs[2] == '.' && inputs[3] == '.') {//--..
                seven_segment_show(35); //Z
                printf("Z\n");
            } else {
                printf("error while decoding\n");
            }
        } else if (calcLength() == 5) {
            if (inputs[0] == '-' && inputs[1] == '-' && inputs[2] == '-' && inputs[3] == '-' && inputs[4] == '-') {
                seven_segment_show(0); //0
                printf("0\n");
            } else if (inputs[0] == '.' && inputs[1] == '-' && inputs[2] == '-' && inputs[3] == '-' &&
                       inputs[4] == '-') {
                seven_segment_show(1); //1
                printf("1\n");
            } else if (inputs[0] == '.' && inputs[1] == '.' && inputs[2] == '-' && inputs[3] == '-' &&
                       inputs[4] == '-') {
                seven_segment_show(2); //2
                printf("2\n");
            } else if (inputs[0] == '.' && inputs[1] == '.' && inputs[2] == '.' && inputs[3] == '-' &&
                       inputs[4] == '-') {
                seven_segment_show(3); //3
                printf("3\n");
            } else if (inputs[0] == '.' && inputs[1] == '.' && inputs[2] == '.' && inputs[3] == '.' &&
                       inputs[4] == '-') {
                seven_segment_show(4); //4
                printf("4\n");
            } else if (inputs[0] == '.' && inputs[1] == '.' && inputs[2] == '.' && inputs[3] == '.' &&
                       inputs[4] == '.') {
                seven_segment_show(5); //5
                printf("5\n");
            } else if (inputs[0] == '-' && inputs[1] == '.' && inputs[2] == '.' && inputs[3] == '.' &&
                       inputs[4] == '.') {
                seven_segment_show(6); //6
                printf("6\n");
            } else if (inputs[0] == '-' && inputs[1] == '-' && inputs[2] == '.' && inputs[3] == '.' &&
                       inputs[4] == '.') {
                seven_segment_show(7); //7
                printf("7\n");
            } else if (inputs[0] == '-' && inputs[1] == '-' && inputs[2] == '-' && inputs[3] == '.' &&
                       inputs[4] == '.') {
                seven_segment_show(8); //8
                printf("8\n");
            } else if (inputs[0] == '-' && inputs[1] == '-' && inputs[2] == '-' && inputs[3] == '-' &&
                       inputs[4] == '.') {
                seven_segment_show(9); //9
                printf("9\n");
            } else {
                printf("error while decoding\n");
            }
        }
        wipeArray();
    }
}
/*checkbutton(int input) - takes an input. checks whether the input is a . or a - then adds it to the inputs array*/
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


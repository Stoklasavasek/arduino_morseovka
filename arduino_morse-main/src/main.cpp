#include <Arduino.h>

int led_pin = 2;

int dot_lenght = 150;    // .
int dash_length = 300;   // -
int pause_lenght = 50;   // .(udela pauza)-
int letter_pause = 400;  // .- (udela pauzu) -.- 
int space_delay = 800;   // slovo [pauza] [slovo]

int morse_codes[26][4] = {
    {0, 1},        // A: .-
    {1, 0, 0, 0},  // B: -...
    {1, 0, 1, 0},  // C: -.-.
    {1, 0, 0},     // D: -..
    {0},           // E: .
    {0, 0, 1, 0},  // F: ..-.
    {1, 1, 0},     // G: --.
    {0, 0, 0, 0},  // H: ....
    {0, 0},        // I: ..
    {0, 1, 1, 1},  // J: .---
    {1, 0, 1},     // K: -.-
    {0, 1, 0, 0},  // L: .-..
    {1, 1},        // M: --
    {1, 0},        // N: -.
    {1, 1, 1},     // O: ---
    {0, 1, 1, 0},  // P: .--.
    {1, 1, 0, 1},  // Q: --.-
    {0, 1, 0},     // R: .-.
    {0, 0, 0},     // S: ...
    {1},           // T: -
    {0, 0, 1},     // U: ..-
    {0, 0, 0, 1},  // V: ...-
    {0, 1, 1},     // W: .--
    {1, 0, 0, 1},  // X: -..-
    {1, 0, 1, 1},  // Y: -.--
    {1, 1, 0, 0}   // Z: --..
};

int morse_symbol_count[26] = {2, 4, 4, 3, 1, 4, 3, 4, 2, 4, 3, 4, 2, 2, 3, 4, 4, 3, 3, 1, 3, 4, 3, 4, 4, 4};

void setup() {
    pinMode(led_pin, OUTPUT);
    Serial.begin(9600);
    Serial.println("Zadejte pismeno, ktere chcete prevest na Morseovu abecedu:");
}

void morse_to_led(int morse_symbol[], int length) {
    for (int i = 0; i < length; i++) {
        if (morse_symbol[i] == 0) {
            // Tecka
            digitalWrite(led_pin, HIGH);
            delay(dot_lenght);
            digitalWrite(led_pin, LOW);
            Serial.print(" .");
        } else if (morse_symbol[i] == 1) {
            // Carka
            digitalWrite(led_pin, HIGH);
            delay(dash_length);
            digitalWrite(led_pin, LOW);
            Serial.print(" -");
        }
        // Pauza
        if (i < length - 1) {
            delay(pause_lenght);
            // Serial.print("");
        }
    }
    Serial.print(" /");
}

void str_to_morse_to_led(String input) {
    input.toUpperCase();
    for (unsigned int i = 0; i < input.length(); i++) {
        char letter = input[i];
        if (letter == ' ') {
            delay(space_delay);
            Serial.print(" /");
        } else if (letter >= 'A' && letter <= 'Z') {
            int index = letter - 'A';
            morse_to_led(morse_codes[index], morse_symbol_count[index]);
            delay(letter_pause);
        } else {
            Serial.println("Neplatny znak, prosim pouzijte pismeno z abecedy.");
            return;
        }
    }
    Serial.println("//");
}

void loop() {
    if (Serial.available() > 0) {
        String input = Serial.readString();
        Serial.println("Vstup: " + input);
        str_to_morse_to_led(input);
    }
}

/* This program takes as input an array of characters to be treated as 8-bit integers.
   It takes each five consecutive bits treated as a single character and decodes a message */

//
//  main.cpp
//  Decompress
//
//  Created by Joshua on 3/31/18.
//  Copyright © 2018 Joshua. All rights reserved.
//

#include <iostream>
#include<string>

struct Bits {       // struct created to allow bit fields for the decoder
    unsigned element:8; // to hold each 8-bit element from the array
    unsigned letter:5;  // to hold each 5-bit letter
};

int main() {
    unsigned char bytes[25] = { 9,0,207,176,159,163,255,33,58,115,
        199,255,255,181,223,67,102,69,173,6,35,103,245,160,164 };   // input characters
    Bits bits;                  // declares the struct variable to hold the current element and letter
    int letterelem = 5;         // counts the current bit assigned in the letter
    unsigned mask = 1 << 7;     // mask applied to the element to get the leftmost bit
    char letter5;                // used to tranlate the 5-bit integer into a character
   
    for (int i = 0; i < 25; ++i)  // loop through the array of elements
    {
        
        bits.element = bytes[i];  // assign array element to an 8-bit variable
        for (int bit = 1; bit <=8 ; ++bit) // loop through the element's 8 bits
        {
            bits.letter <<= 1;                              // left-shift the 5-bit letter
            bits.letter += (bits.element & mask ?  1 : 0); // assign the current element bit to the next letter bit
            letterelem -= 1;                // decrement the count to make sure each letter gets only five bits
            bits.element <<= 1;             // left-shift the 8-bit element
            
            if (letterelem == 0)            // checks if the 5-bit letter is complete, prints it if it is
            {
                if (bits.letter == 31)      // assigns 11111 (31) to the space character
                {
                    std::cout << ' ';
                }
                else
                {
                    letter5 =  bits.letter + 65;    // assigns any other values to the proper ASCII value
                    std::cout << letter5;           // and prints it
                }
                letterelem = 5;                     // restarts the count to 5 if the letter was complete
            }
        }
    }
    std::cout << std::endl;
    system("pause");
    return 0;
    
    
}

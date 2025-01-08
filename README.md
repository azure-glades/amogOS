# amogOS

## How are those bitmaps made
The binary values for the bitmaps were generated based on a visual representation of each character using an 8x8 grid. Each binary value corresponds to a row of pixels in this grid, where 1 represents a pixel that is "on" (filled) and 0 represents a pixel that is "off" (empty).
For example; each 1 here tells whether that pixel on the 8x8 grid is filled or not
```
01111110
11000011
11000111
11001111
11011011
11110011
11100011
01111110
``
Each row of the visual representation is converted to an 8-bit binary value. The collection of these binary values forms the bitmap for the character '0'. The other characters follow the same process, where each row in the visual grid is converted to a corresponding binary value.
- If you want to create bitmaps for your own characters:
    - Draw the character on an 8x8 grid.
    - For each row, write out the binary value where each bit represents a pixel (1 for filled, 0 for empty).
    - Convert the row's binary value to an 8-bit binary number.
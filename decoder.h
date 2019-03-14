#ifndef ASSIGNMENT_4_DECODER_H
#define ASSIGNMENT_4_DECODER_H

// struct for odd and even masks
struct decoder{
    unsigned int oddmask;
    unsigned int evenmask;
};


// flushes scanner
void flushInput()
{
    int ch; //variable to read data into
    while((ch = getc(stdin)) != EOF && ch != '\n');
}

#endif //ASSIGNMENT_4_DECODER_H
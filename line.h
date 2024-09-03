#ifndef LINE_H
#define LINE_H

//vertical line of chars
typedef struct {
    int len;
    int row;
    int col;
    char* chars;
    int color;
    int numRows;
} line;

void drawLine(line* l);
line* createLine(int len, int col, int color, int numRows);
void step(line* l);
void lineFree(line* l);
void cleanLines(line** v, int numL);


#endif
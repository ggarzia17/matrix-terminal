#include "line.h"
#include <stdlib.h>
#include <ncurses.h>

void drawLine(line* l){
    attron(COLOR_PAIR(l->color+1));
    for (int i = l->row; i >= 0 && l->row - i < l->len; i-- ){
        mvprintw(i, l->col, "%c", l->chars[i]);
    }
    attroff(COLOR_PAIR(l->color + 1));

}
line* createLine(int len, int col, int color, int numRows){
    line* l = malloc(sizeof(line));
    l->len = len;
    l->row = 0;
    l->col = col;
    l->color = color;
    l->numRows = numRows;

    l->chars = (char*) malloc(numRows);

    for(int i = 0; i < numRows; i++){
        int c = random() % 94 + 33;

        l->chars[i] = c;
    }

    return l;
}
void step(line* l){
    l->row++;
}
void lineFree(line* l){
    free(l->chars);
}
void cleanLines(line** ls, int numL){
    for (int i = 0; i < numL; i++){
        if(!ls[i]){
            continue;
        }
        line* l = ls[i];
        if (l->row - l->len > l->numRows){
            lineFree(ls[i]);
            free(l);
            ls[i] = 0;
        }
    }
  
}

#ifndef _ex22_h
#define _ex22_h

// make THE_SIZE in ex22.c available to other .c files
extern int THE_SIZE;

// accessor function to file static variable
int get_age();
void set_age(int age);

// updates a static variable that's inside a function
double update_ratio(double);

void print_size();

#endif

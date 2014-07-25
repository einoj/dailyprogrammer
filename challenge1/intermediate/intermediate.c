#include <stdio.h>
#include <string.h>
struct event {
    char description[141]; // max description length is 140 + termination 0
    char date[17]; //example 2014-06-02 16:00 must be 16 chars + termination 0
        struct event *next;
};

int addEvent(char description[141], char date[17], struct event *root)
{
    if (strlen(description) > 140) {
        return 1; // desciption too long
    } else if (strlen(date) != 16) {  
        return 2; // date not the correct format
    }

    // user recursion to add to the end of the list
    if (root->date == 0) {
            root->date = date[0];
        root->description = description
    } else { 
        addEvent(description, date, root);
    }
    return 0;
}

int main(void)
{
    struct event *root;

    printf("%d\n", root);

    return 0;
}

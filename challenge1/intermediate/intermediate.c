#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct e {
    char *description; // max description length is 140 + termination 0
    char *date; //example 2014-06-02 16:00 must be 16 chars + termination 0
    struct e *next;
} event;


int addEvent(char *description, char *date, event **root)
{
    if (strlen(description) > 140) {
        return 1; // desciption too long
    } else if (strlen(date) != 16) {  
        return 2; // date not the correct format
    }

    /*if the root is empty, add at root*/
    if (*root == 0) {
        printf("test added root\n");
        *root = malloc(sizeof(event));
        (*root)->date = date;
        (*root)->description = description;
        (*root)->next = 0;
    } else {
        event *tmp;
        tmp = *root;
        while (tmp->next != 0)
        {
            tmp = tmp->next;
        }
        printf("adding new event\n");
        tmp->next = malloc(sizeof(event));   
        tmp = tmp->next;
        tmp->description = description;
        tmp->date = date;
    }
    return 0;
}

int removeEvent(char *date) {

}

void printEvents(event *root)
{
    event *tmp;
    tmp = root;

    while (tmp != 0)
    {
        printf("%s %s\n", tmp->date, tmp->description);
        tmp = tmp->next;
    }
}

int main(void)
{

    event *root;
    char *d1, *d2, *t1, *t2;
    d1 = malloc(141*sizeof(char));
    d2 = malloc(141*sizeof(char));
    t1 = malloc(17*sizeof(char));
    t2 = malloc(17*sizeof(char));
    d1 = "Bursdag";
    d2 = "Meeting";
    t1 = "2014-11-01 15:00";
    t2 = "2015-02-11 10:00";
    addEvent(d1,t1,&root);
    addEvent(d2,t2,&root);
    printEvents(root);

    return 0;
}

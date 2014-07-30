#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct e {
    char *description; // max description length is 140 + termination 0
    char *date; //example 2014-06-02 16:00 must be 16 chars + termination 0
    struct e *next;
} event;

/*converting date to unix time
 * taken from http://stackoverflow.com/questions/1002542/how-to-convert-datetime-to-unix-timestamp-in-c */
int convertDateToUnix(char* date)
{
    struct tm tm;
    time_t epoch;
    if ( strptime(date, "%Y-%m-%d", &tm) != NULL ) {
        epoch = mktime(&tm);
    } else {
        epoch=-1;
    }
    return epoch;
}

int addEvent(char *description, char *date, event **root)
{
    if (strlen(description) > 140) {
        return 1; // desciption too long
    } else if (strlen(date) != 16) {  
        return 2; // date not the correct format
    }

    /*if the root is empty, add at root*/
    if (*root == 0) {
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
        tmp->next = malloc(sizeof(event));   
        tmp = tmp->next;
        tmp->description = description;
        tmp->date = date;
        tmp->next = 0;
    }
    return 0;
}

int numEvents(event *root)
{
    int s = 0;

    while(root != 0) {
        s++;
        root = root->next;
    }

    return s;
}

char** listEventsOnDate(char *date, event *root, int *arraysize)
{
    int n = numEvents(root);
    char** eventsOnDate = malloc(n * sizeof(char*));
    int i;
    for (i = 0; i < n; i++) {
        eventsOnDate[i] = malloc(141 * sizeof(char));
    }
    i = 0;
    while (root != 0) {
        if (!(strncmp(date, root->date, 10))) {
            eventsOnDate[i] = root->description;
            i++;
        }
        root = root->next;
    }
    *arraysize = i;
    return eventsOnDate;
}

int chooseEventOnDate(char** eventDescriptions, int arraysize)
{
    int i;
    for (i = 0; i < arraysize; i++) {
        printf("%d: %s\n", i+1, eventDescriptions[i]);
    }
    char input[141];
    printf("Choose which event to delete: ");
    /*remove newline from stream*/
    fgetc(stdin);
    fgets(input,141,stdin);
    int j = atoi(input);
    if (j > arraysize) {
        j = 0;
    }
    /* decrement j because indexes start at 0. 
     * I need to do this because atoi returns 0 if input is not an int.
     * And so 0 can't be used as an index for user input */
    return --j;
}


void printEvents(event *root)
{
    event *tmp;
    tmp = root;

    printf("Current registered events:\n");
    while (tmp != 0)
    {
        printf("%s %s\n", tmp->date, tmp->description);
        tmp = tmp->next;
    }
    printf("\n");
}

int getDeleteDate(event *root, char** eventDate)
{
    int retval;
    printEvents(root);
    printf("What date do you want to delete from?\n");
    fgets(*eventDate,11,stdin);
    /*converting date to unix time
     * taken from http://stackoverflow.com/questions/1002542/how-to-convert-datetime-to-unix-timestamp-in-c */
    if (convertDateToUnix(*eventDate)) {
        retval = 1; 
    } else {
        /* Wront date format*/
        retval = 0;
    }
    return retval;
}

/* actually do the removal of event from linked list */
int removeEvent(event **root, char* date, char* description)
{
    event *curr, *prev;
    curr = *root;
    prev = *root;



    /*check if the first element is to be deleted*/
    if( (strncmp(date,curr->date,10) == 0) && (strncmp(description, curr->description, 141) == 0))
    {
        printf("date=%s des=%s\n, root.date-=%s, root.des=%s",date, description,curr->date,curr->description);
        (*root) = (*root)->next;
        free(prev);
    } else {

        while (curr->next != 0) {
            prev = curr;
            curr = curr->next;
            if( (strncmp(date,curr->date,10) == 0) && (strncmp(description, curr->description, 141) == 0))
                prev->next = curr->next;
                free(curr);
        }
    }
    return 0;
}


int deleteEvent(event **root)
{
    int arraysize;
    int deleteIndex;
    char** eventA;
    char* deleteDate = malloc(11*sizeof(char));
    if (getDeleteDate(*root, &deleteDate)) {
        eventA = listEventsOnDate(deleteDate, *root, &arraysize);
        if (arraysize < 1) {
            printf("ERROR: No events on this date\n");
        } else {
            deleteIndex = chooseEventOnDate(eventA, arraysize);
            if (deleteIndex < 0) {
                printf("ERROR: Event index not in list\n");
            } else {
                /*finally remove the event*/
                removeEvent(root, deleteDate, eventA[deleteIndex]);
            }
        }
    } else {
        /* Wront date format*/
        printf("ERROR: Not a valid date format!\n");
    }
}

int main(void)
{
    event *root = 0;
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
    addEvent(d2,t1,&root);
    deleteEvent(&root);
    printEvents(root);

    return 0;
}

#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;

struct point_data
{
    float x;
    float y;
    struct point_data *nextP;
};

typedef struct point_data Point;
typedef Point *PointPtr;

void insert_point(PointPtr *sPoint, PointPtr NewPoint);
void delete_point(PointPtr *sPoint, PointPtr NewPoint);
void display_point(PointPtr sPoint);
void track_point(PointPtr sPoint, PointPtr *tPtr);
float distance(PointPtr PointA, PointPtr PointB);
float sqr(float num);

int main()
{
    PointPtr start_point = NULL;
    PointPtr point_track = NULL;
    PointPtr new_point = (PointPtr) malloc(sizeof(Point));

    int point_count = 0;
    char Opt;

    printf("\nMENU");
    printf("\n\t1. Insert Point");
    printf("\n\t2. Delete Point");
    printf("\n\t3. Display All Points");
    printf("\n\t4. Display Points Track");
    printf("\n\t5. Exit\n");

    do
    {
        printf("\nSelect Option...");
        Opt = getch();

        switch(Opt)
        {
        case '1':
            printf("\nInsert Point : ");
            scanf("%f,%f", &new_point->x, &new_point->y);
            insert_point(&start_point, new_point);
            point_count++;
            break;
        case '2':
            printf("\nDelete Point : ");
            scanf("%f,%f", &new_point->x, &new_point->y);
            delete_point(&start_point, new_point);
            point_count--;
            break;
        case '3':
            printf("\nDisplaying Inserted Points.");
            display_point(start_point);
            break;
        case '4':
            printf("\nDisplaying Track Points.");
            display_point(point_track);
            break;
        case '5':
            printf("\nExit...");
            exit(0);
            break;
        default:
            printf("\nInvalid Choice!!!");
        }
        if(Opt == '1' || Opt == '2')
        {
            track_point(start_point, &point_track);
        }
    }
    while(1);
    return 0;
}

void insert_point(PointPtr *sPoint, PointPtr NewPoint)
{
    PointPtr New_Point = (PointPtr) malloc(sizeof(Point));

    New_Point->x = NewPoint->x;
    New_Point->y = NewPoint->y;
    New_Point->nextP = NULL;

    while(*sPoint != NULL)
    {
        sPoint = &(*sPoint)->nextP;
    }
    *sPoint = New_Point;
}

void delete_point(PointPtr *sPoint, PointPtr NewPoint)
{
    PointPtr DelPoint = NULL;

    if(*sPoint != NULL)
    {
        while((*sPoint != NULL) && (((*sPoint)->x != NewPoint->x) || ((*sPoint)->y != NewPoint->y)))
        {
            sPoint = &(*sPoint)->nextP;
        }
        if(*sPoint != NULL)
        {
            DelPoint = *sPoint;
            *sPoint = (*sPoint)->nextP;
            free(DelPoint);
        }
        else
        {
            printf("\nPoint Not Found.");
        }
    }
    else
    {
        printf("\nNo Point to Delete.");
    }
}

void display_point(PointPtr sPoint)
{
    if(sPoint != NULL)
    {
        while(sPoint != NULL)
        {
            printf("\n(%.0f,%.0f)", sPoint->x, sPoint->y);
            sPoint = sPoint->nextP;
        }
    }
    else
    {
        printf("\nNo Point to display.");
    }
}

void track_point(PointPtr sPoint, PointPtr *tPtr)
{
    float sdist;
    int last_point = 0;

    PointPtr cur_point, near_point, cmp_point;
    PointPtr dupl_point = NULL;

    if(*tPtr != NULL)
    {
        PointPtr Del_track = *tPtr;
        *tPtr = NULL;
        free(Del_track);
    }

    if(sPoint != NULL)
    {
        if(sPoint->nextP != NULL)
        {
            near_point = sPoint;
            insert_point(tPtr, sPoint);

            cur_point = sPoint->nextP;

            while(cur_point != NULL)
            {
                insert_point(&dupl_point, cur_point);
                cur_point = cur_point->nextP;
            }

            while(!last_point)
            {
                cmp_point = near_point;

                if(dupl_point->nextP != NULL)
                {
                    cur_point = dupl_point;

                    while(cur_point != NULL)
                    {
                        if((cur_point == dupl_point) || (sdist > distance(cur_point, cmp_point)))
                        {
                            sdist =  distance(cur_point, cmp_point);
                            near_point = cur_point;
                            cur_point = cur_point->nextP;
                        }
                        else
                        {
                            cur_point = cur_point->nextP;
                        }
                    }
                    insert_point(tPtr, near_point);
                    delete_point(&dupl_point, near_point);
                }
                else
                {
                    insert_point(tPtr, dupl_point);
                    last_point = 1;
                }
            }
        }
        else
        {
            insert_point(tPtr, sPoint);
        }
    }
}

float distance(PointPtr PointA, PointPtr PointB)
{
    return sqrt(sqr(PointA->x - PointB->x) + sqr(PointA->y - PointB->y));
}

float sqr(float num)
{
    return num*num;
}

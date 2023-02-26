#include <stdio.h>
#include <stdlib.h>


struct Task
{
  char name[20];
  int pr;
  int id;
};

typedef struct Task task;
task *heap; int size,d=0;

void getele()
{
    printf("\nEnter the Size of the heap : ");
    scanf("%d",&size);

    heap=(task*)malloc((size+1)*sizeof(task));
    for(int i=1;i<=size;i++)
    {
        printf("\nEnter task %d : ",i);
        scanf("%s",(heap+i)->name);
        printf("\nEnter task %d priority: ",i);
        scanf("%d",&(heap+i)->pr);
        (heap+i)->id = ++d;
    }
}
void swap(task *a,task *b)
{
    task t=*a;
    *a=*b;
    *b=t;
}
int cmp(int l,int p)
{
  return ((heap+l)->pr > (heap+p)->pr);
}

void heapify(int p)
{
    int l,r;
    l=p*2;
    r=p*2+1;

    if(l<=size)
    {
        if(p==0) return;
        if(cmp(l,p))
        {
            swap(heap+p,heap+l);
            heapify(p*2);
        }

        if (r<= size)
        {
            if(cmp(r,p))
            {
                swap(heap+p,heap+r);
                heapify(p*2+1);
            }
        }
        heapify(p-1);
    }
    return;
}

void disp()
{
    printf("\n\n");
    for(int i=1;i<=size;i++)
    {
        printf("%d\t",(heap+i)->id);
        printf("%s\t",(heap+i)->name);
        printf("%d\n",(heap+i)->pr);
    }
    printf("\n\n");
}

void del()
{
    task *x;
    x=(heap+1);
    heap[1]=heap[size];
    size--;
    d--;
    heap=(task*)realloc(heap,(size+1)*sizeof(task));
    heapify(size/2);
    printf("\nCompleted Task : %d\n",x->id);
    if(size>=1)  disp();


}
void insert()
{
    heap=(task*)realloc(heap,sizeof(task)*(++size));
    printf("\nEnter task %d : ",size);
    scanf("%s",(heap+size)->name);
    printf("\nEnter task %d priority: ",size);
    scanf("%d",&(heap+size)->pr);
    (heap+size)->id = ++d;
    heapify(size/2);
    disp();
}

char menu()
{
    char ch;
    printf("\nPress :\n\t1.Insert\n\t2.Delete\n\t3.Display\n\tE.Exit\n\nYour choice : ");
    scanf("\n%c",&ch);
    return ch;
}
void main()
{
    char fl;
    getele();
    heapify(size/2);
    disp();
    while((fl=menu())!='E')
    {
        switch(fl)
        {
        	case '1':
              insert();
              break;

      	  case '2':
      	      (size>=1)?del():printf("\nNo tasks remaining!\n");
      	      break;

      	  case '3':
      	      (size>=1)?disp():printf("\nNo tasks remaining!\n");
      	      break;

      	  case 'E':
      	      break;

      	  default:
      	      printf("\nInvalid Option. Try again!\n");
        }
    }

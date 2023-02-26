#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node node;
typedef struct Orditem orditem;

struct Orditem
{
  char item[10][10];
  int qty[10];
  float pt[10];
};

struct Node
{
  float cost;
  float ptt;
  int noi;
  orditem order;
};

float wt=0; int no=0;
node orders[30];

void ordmenu()
{
  if(no>1) printf("\n\nWaiting Time : %0.2f Minutes\n",wt);
  printf("\n\n\tAvailable Items     Price(Rs.)     Preparing Time(Mins.)\n");
  printf("\n\t 1. Dosa                15               5");
  printf("\n\t 2. Idli(2)             15               2");
  printf("\n\t 3. Chapathi            15               3");
  printf("\n\t 4. Parotta             15               4");
  printf("\n\t 5. Poori               15               1");
  printf("\n\t 6. Omelette            15               6");
}

void disp();

void insert(int t)
{
  int i=0,x,y,z;
  char ch = 'N';
  orders[t].ptt = orders[t].cost = 0;
  orders[t].noi = 0;
  ordmenu();
  printf("\n\nEnter No. of Items : "); scanf("%d",&orders[t].noi);
  while(ch=='N')
  {
    for(i;i<orders[t].noi;i++)
    {
      printf("\n");
      printf("Enter Item %d ID : ",i+1); scanf("%d",&x);
      if(x>0&&x<7)
      {
        switch(x)
        {
          case 1: strcpy(orders[t].order.item[i],"Dosa    ");
                  orders[t].order.pt[i] = (float)(1.25);
                  break;

          case 2: strcpy(orders[t].order.item[i],"Idli    ");
                  orders[t].order.pt[i] = (float)(0.166);
                  break;

          case 3: strcpy(orders[t].order.item[i],"Chapathi");
                  orders[t].order.pt[i] = (float)(0.375);
                  break;

          case 4: strcpy(orders[t].order.item[i],"Parotta ");
                  orders[t].order.pt[i] = (float)(0.5);
                  break;

          case 5: strcpy(orders[t].order.item[i],"Poori   ");
                  orders[t].order.pt[i] = (float)(0.25);
                  break;

          case 6: strcpy(orders[t].order.item[i],"Omelette");
                  orders[t].order.pt[i] = (float)(0.75);
                  break;
        }
        printf("Enter Quantity : "); scanf("%d",&y);
        orders[t].order.qty[i] = y;
        orders[t].cost += 15*y;
        orders[t].order.pt[i] *= orders[t].order.qty[i];
        orders[t].ptt += orders[t].order.pt[i];
        if(t!=0)
        {
          wt = wt+(orders[t].ptt-10);
          if(wt<0) wt = 0;
        }
        else wt += orders[t].ptt;
      }
      else
      {
        printf("\n\nInvalid Choice! Try Again.");
        system("timeout 3 > NUL");
        system("cls");
        insert(t);
      }
    }
    printf("\nConfirm Order ? (Y/N) : "); scanf("\n%c",&ch);
    if(ch=='N') orders[t].noi++;
  }
}

int cmp(int p,int l)
{
  if((orders[l].ptt<orders[p].ptt)&&(2*orders[l].ptt<wt)) return 1;
  else return 0;
}

void swap(int p,int l)
{
  node temp = orders[p];
  orders[p] = orders[l];
  orders[l] = temp;
}

void heapify(int p)
{
    int l,r;
    l=p*2;
    r=p*2+1;

    if(l<=no)
    {
        if(p==0) return;
        if(cmp(p,l))
        {
            swap(p,l);
            heapify(p*2);
        }

        if (r<= no)
        {
            if(cmp(p,r))
            {
                swap(p,r);
                heapify(p*2+1);
            }
        }
        heapify(p-1);
    }
    return;
}

void disp()
{
  printf("\n\nPending Orders : %d\n",no);
  for(int i=1;i<=no;i++)
  {
    printf("\n\nOrder %d:",i);
    if(orders[i].ptt) printf("\n        Preparing Time : %0.2f Minutes\n",orders[i].ptt);
    else printf("\n        Order Prepared!\n");

    printf("\n\tItems        Quantity\n");

    for(int j=0;j<orders[i].noi;j++)
      printf("\n\t%s\t%d",orders[i].order.item[j],orders[i].order.qty[j]);
    printf("\n\n");
  }
}

void del()
{
  if((no>=1)&&(orders[1].ptt<=10))
  {
    node temp = orders[1];
    orders[1]=orders[no--];
    heapify(no/2);
    printf("\nCompleted Order : \n");
    printf("\n\tItems        Quantity\n");

    for(int j=0;j<temp.noi;j++)
      printf("\n\t%s\t%d",temp.order.item[j],temp.order.qty[j]);
    printf("\n\n");

    printf("\n\tPrice        Rs.  %0.2f\n",temp.cost);
  }
  if((orders[1].ptt-10)>=0) orders[1].ptt -= 10;
}

char menu()
{
  char ch;
  if(no!=0) system("timeout 6 > NUL");
  system("cls");
//  printf("\nWelcome To Sanjay Mess!!\n");
  printf("Order Food? (Y/N) : "); scanf("\n%c",&ch);
  return ch;

}

void main()
{
  char ch;
  while((ch=menu())=='Y')
  {
    del();
    insert(++no);
    heapify(no/2);
    disp();
  }
  printf("\nTime for Order Completion : %0.2f Minutes\n",wt+2.50);
  while(no>0) del();
}

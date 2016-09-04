#include<stdio.h>
#include<stdlib.h>

int count=0,pop_count=0;

struct node
{
  int val;
  struct node * link;
};

struct table
{
  int push;
  int pop;
  int val;
  struct node * link;
};

void DisplayAL(struct table * table_array,int V)
{
  int i;
  struct node *curr;
  for(i=0;i<V;i++)
  {
    printf("%d %d %dis connected to :",table_array[i].push,table_array[i].pop,i);
    curr = table_array[i].link;
    while(curr != NULL)
    {
      printf("%d ",curr->val);
      curr = curr->link;
    }
    printf("\n");
  }
}

struct node * CreateNode(int item)
{
  struct node * temp = (struct node *)malloc(sizeof(struct node));
  temp->val = item;
  temp->link = NULL;
  return temp;
}

void AddVertToEnd(struct table * table_array,int index,int val)
{
  struct node * curr = table_array[index].link;
  if(curr == NULL)
  {
    table_array[index].link = CreateNode(val);
    return;
  }
  while(curr->link != NULL)
  {
    curr = curr->link;
  }
  curr->link =  CreateNode(val);
}

void dfs(struct table * table_array,int index)
{
  struct node * curr = table_array[index].link;
  table_array[index].push = ++count;
  while (curr!=NULL)
  {
    if(table_array[curr->val].push == 0)
    {
      dfs(table_array,curr->val);
    }
    curr = curr->link;
  }
  table_array[index].pop = ++pop_count;
}

int main(int argc, char const *argv[]) {
  int V,E,i,temp;
  V=6;
  struct table * table_array = (struct table *)calloc(V,sizeof(struct table));
  for(i=0;i<V;i++)
  {
    printf("Enter the vertice %d is connected to; Enter -1 to stop ",i);
    do {
      scanf("%d",&temp);
      if(temp!=-1)
        AddVertToEnd(table_array,i,temp);
    } while(temp!=-1);
  }
    for(i=0;i<V;i++)
    {
      if(table_array[i].push == 0)//makes sure that even non connected ones are checked
      {
        dfs(table_array,i);
      }
    }
    DisplayAL(table_array,V);
  return 0;
}

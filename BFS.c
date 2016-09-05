#include<stdio.h>
#include<stdlib.h>

int visited[6] = {0,0,0,0,0,0};
int count = 0,V;

enum Bool{false,true};

struct node
{
  int val;
  struct node * link;
};

struct node * CreateNode(int item)
{
  struct node * temp = (struct node *)malloc(sizeof(struct node));
  temp->val = item;
  temp->link = NULL;
  return temp;
}

struct node * enqueue(struct node *  q,int item)
{
  struct node * curr = q;
  if(q == NULL)
  {
    q = CreateNode(item);
    return q;
  }
  while(curr->link != NULL)
  {
    curr = curr->link;
  }//now curr points to the last element
  curr->link = CreateNode(item);
  return q;
}

struct node * dequeue(struct node * q)
{
  struct node * temp = q;
  q = q->link;
  free(temp);
  return q;
}

void qDisplay(struct node * q)
{
  printf("The queue is filled with \n");
  struct node * temp = q;
  while(temp!=NULL)
  {
    printf("%d \n",temp->val);
    temp = temp->link;
  }
}

int qEmpty(struct node * q)
{
  if(q == NULL)
    return true;
  return false;
}

void bfs( int index,int **arr)//It is not recursive
{
  int i;
  //Create queue
  struct node * q = NULL;
  q = enqueue(q,index);
  //Update visited
  visited[index] = ++count;
  while(qEmpty(q) == false)
  {
    for(i=0;i<V;i++)
    {
      if(arr[index][i] == 1)//If the ith index is adjacent to the element at index
      {
        if(visited[i]==0)//if the adjacent index has not been visited
        {
          q = enqueue(q,i);
          visited[i] = ++count;
        }
      }
    }

/*    printf("Q before deque :\n");
    qDisplay(q);*/

    q=dequeue(q);

/*    printf("Q after deque :\n");
    qDisplay(q);*/

    if(q!=NULL)
      index = q->val;
  }
}

int ** Create2DArray(int size)
{
  int i;
  int ** temp = (int **)calloc(size,sizeof(int *));
  for(i=0;i<size;i++)
  {
    temp[i] = (int*)calloc(size,sizeof(int));
  }
  return temp;
}

int main(int argc, char const *argv[]) {
  int i,j;

  printf("Enter the number of vertices \n" );
  scanf("%d",&V);

  int **arr = Create2DArray(V);
  for(i=0;i<V;i++)
  {
    for(j=0;j<V;j++)
    {
      printf("\nEnter the adjacency matrix value of %d,%d",i,j);
      scanf("%d",&arr[i][j] );
    }
  }

  for(i=0;i<V;i++)
  {
    for(j=0;j<V;j++)
    {
      printf("%d ",arr[i][j] );
    }
    printf("\n");
  }

  //TODO  make the array dynamically and assign it the values given from the user
  //int arr[6][6] = {{0,0,1,1,1,0},{0,0,0,0,1,1},{1,0,0,1,0,1},{1,0,1,0,0,0},{1,1,0,0,0,1},{0,1,1,0,1,0}};
  for(i=0;i<V;i++)//Go through each and every vertex
  {
    if(visited[i] == 0)
      bfs(i,arr);
  }

  printf("Visited order is \n" );
  for(i=0;i<V;i++)
  {
    printf("%d ",visited[i]);
  }
}

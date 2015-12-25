
#include "stdafx.h"
#include <time.h>
#define SUCCESS (0)
#define FAILURE (-1)
#define SPACE_SIZE (1000)
#define NOT_HEAD (SPACE_SIZE - 1)
#define END (-1)

typedef struct NODE
{
		int data;
		int next;
} NODE;
  
  static int CursorAlloc();
  static int CursorFree(int i);
  static int create_list(int list, int n);
  static int delete_node(int list, int n);
  static NODE CursorSpace[SPACE_SIZE];
  
  static int CursorAlloc()
  {
	  int i;
	  if (CursorSpace[NOT_HEAD].next == END)
		  return (FAILURE);
	  i = CursorSpace[NOT_HEAD].next;
	  CursorSpace[NOT_HEAD].next = CursorSpace[i].next;
	  return (i);
  }


  static int CursorFree(int i)
  {
	  if (i < 0 || i >= SPACE_SIZE)
		  return (FAILURE);
	  CursorSpace[i].next = CursorSpace[NOT_HEAD].next;
	  CursorSpace[NOT_HEAD].next = i;
	  return (SUCCESS);
  }
  
  /*��������*/
  static int create_list(int list, int n)
  {
	  int i;
	  int tmp, last = END;
	  for (i = 0; i < n; i++)
	  {
		  
		  tmp = CursorAlloc();
		  if (tmp == FAILURE)
		  {
			  printf("error in CursorAlloc ()\n");
			  return (FAILURE);
		  }
		  
		  CursorSpace[tmp].data = n - i;
		  CursorSpace[tmp].next = CursorSpace[list].next;
		  CursorSpace[list].next = tmp;
		 
		  if (last == END)
			  last = tmp;
	  }
	  /*���ɻ�*/
	  CursorSpace[last].next = CursorSpace[list].next;
	  
	  for (tmp = CursorSpace[list].next; CursorSpace[tmp].next != CursorSpace[list].next; tmp = CursorSpace[tmp].next)
	  {
	  }
	  return (SUCCESS);
  }
  
  /*ɾ�����*/
  static int delete_node(int list, int n)
  {
	  int i;
	  int prev, tmp;
	  if (CursorSpace[list].next == END)
	  {
		  printf("empty list\n");
		  return (FAILURE);
	  }
	  /*ʤ�����ж�����:ֻ��һ�����*/
	  if (CursorSpace[CursorSpace[list].next].next == CursorSpace[list].next)
	  {
		  //printf("survivor is %d\n", CursorSpace[CursorSpace[list].next].data);
		  return (SUCCESS);
	  }
 
	  /*��prevָ�����һ�����*/
	  for (prev = CursorSpace[list].next; CursorSpace[prev].next != CursorSpace[list].next; prev = CursorSpace[prev].next)
	  {
	  }
	  /*Play����
		*prev��ס�ϸ������Ϣ
		*tmp��ס��ǰ�����Ϣ
		*/
	  for (i = 1, tmp = CursorSpace[list].next; i < n; i++)
	  {

		  prev = tmp;
		  tmp = CursorSpace[tmp].next;
	  }
	  /**/
	  if (CursorSpace[tmp].next == tmp)
	  {
		  //printf("the last one left is %d\n", tmp);
		  return (SUCCESS);
	  }
	  /*ɾ��һ�����*/
	  CursorSpace[prev].next = CursorSpace[tmp].next;
	  CursorSpace[list].next = CursorSpace[tmp].next;
	  //printf("%d  deleted\n", CursorSpace[tmp].data);
	  CursorFree(tmp);
	  /*�ݹ�*/
	  return (delete_node(list, n));
  }

  int main(int argc, char *argv[])
  {
	  int i;
	  int a, b;
	  clock_t start_time, end_time;
	  printf("please input m and n,separated by a space\n");
	  while (scanf("%d %d", &a, &b)){
		  start_time = clock_t();
		  for (int j= 0; j < 1000000; j++){
			 for (i = 0; i < SPACE_SIZE; i++)
				CursorSpace[i].next = (i + 1) % SPACE_SIZE;
		  CursorSpace[NOT_HEAD - 1].next = END;
		  //printf("m=%d,n=%d\n", a, b);
		  i = CursorAlloc();
		  if (i < 0)
		  {
			  printf("CursorAlloc () failed\n");
			  return (FAILURE);
		  }
		  
		 if (create_list(i, a) != SUCCESS)
				  return (FAILURE);
		if (delete_node(i, b) != SUCCESS)
				  return (FAILURE);
		  }
			end_time = clock_t();
			//printf("%f %f", end_time, start_time);
			printf("the total time is %f/s\n", ((double)(end_time*1000000000 - start_time)*1000000000));
			printf("please input m and n,separated by a space\n");
	  }
	  return (SUCCESS);
  }

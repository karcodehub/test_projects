#include <stdio.h>
#include <iostream>
using namespace std;

int main()
{
  int no_leave=5, taken_leave=3, user;
  printf("enter 1 to apply all leaves or 0 to exit\n");
  scanf("%d", &user);
  while(user)
  {
  if(no_leave>taken_leave)
  {
    printf("leave granted\n, remaining leave is %d\n",no_leave-taken_leave);
    taken_leave=taken_leave+1;
  }
  else
  {
    printf("\nleave denied all leaves used");
    user=0;
  }
}
}

  
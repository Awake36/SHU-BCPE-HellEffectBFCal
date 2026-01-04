#include<stdio.h>
#include<string.h>
#include "windows.h"
int N;
int CALLBACK JUDGEWINDOWS(HWND window, LPARAM lParam) {
    char windowTitle[256];
    GetWindowTextA(window, windowTitle, sizeof(windowTitle));
    if (strstr(windowTitle, "input.txt - Notepad") != NULL) {
        return 0;
    }
    return 1;
}

int main()
{
  HWND window;
  int i = 0, j = 0, k = 0;
  int a = 0, b = 0, n = 0, m = 0, x = 0, y = 0;
  int flag = -1;
  double u1, u2, u3, u4, Uh, B, Kh;
  double Ux[10][3];
  double sum = 0;
  char choice;
  printf("Enter the experiments' times:");
  scanf("%d", &N);
  getchar();
  printf("===========================================\n");
  printf("Enter your KH:");
  scanf("%lf", &Kh);
  getchar();
  printf("===========================================\n");
  printf("Choose your input mode(type A/B only):\nA:file input mode\nB:keyboard input mode\n");
  choice = getchar();
  switch(choice)
  {
    case 'a':
    case 'A': flag = 0; break;
    case 'b':
    case 'B': flag = 1; break;
  }; //choose mode
  printf("===========================================\n");

  if (flag == -1)
  {
    printf("Error!");
    return 0;
  }
  else if (flag == 0)
  {
    FILE * finput, * foutput;
    finput = fopen(".\\input.txt", "w+");
    foutput = fopen(".\\output.txt", "w+");
    if(finput == NULL || foutput == NULL)
    {
      printf("File Error!");
      return 0;
    }
    ShellExecute(NULL,"open","NOTEPAD.EXE",".\\input.txt",NULL,SW_SHOWNORMAL);
    Sleep(1000);
    while (!EnumWindows(JUDGEWINDOWS, 1))
    {
      Sleep(100);
    }
    for ( i = 0 ; i <= N ; i++ )
    {   
      fscanf(finput, "%lf %lf %lf %lf", &u1, &u2, &u3, &u4);
      Uh = ( u1 - u2 + u3 - u4 ) / 4;
      B = Uh * 1000.0 / (Kh * 5.0);
      fprintf(foutput, "第 %d 组数据的 Uh = %.3lf mV\n", i, Uh);
      fprintf(foutput, "第 %d 组数据的 B = %.3lf mT\n", i, B);
      fprintf(foutput, "===========================================\n");
    }
    ShellExecute(NULL,"open","NOTEPAD.EXE",".\\output.txt",NULL,SW_SHOWNORMAL);
  } //file input mode
  else
  {
    for ( i = 0 ; i <= N ; i++ )
    {
      scanf("%lf %lf %lf %lf", &u1, &u2, &u3, &u4);
      Uh = ( u1 - u2 + u3 - u4 ) / 4;
      B = Uh * 1000.0 / (Kh * 5.0);
      printf("第 %d 组数据的 Uh = %.3lf mV\n", i, Uh);
      printf("第 %d 组数据的 B = %.3lf mT\n", i, B);
      printf("===========================================\n");
    }
    system("pause");
    return 0;
  }
}
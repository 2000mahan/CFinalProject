#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int people=50;
int Court=50;
int Treasury=50;
struct node{
char issue[200];
char decision1[200];
int people_decision1;
int Court_decision1;
int Treasury_decision1;
char decision2[200];
int people_decision2;
int Court_decision2;
int Treasury_decision2;
int iteration;
struct node* next;
};
struct save{
char empire[20];
int m; //not that Game over is 0 and middle of the game is 1
int problems[1000];
int p; //stands for people
int C; //stands for Court
int T; //stands for Treasury
};

struct node *create_node(char issue[200], char decision1[200], int people_decision1, int Court_decision1, int Treasury_decision1,char decision2[200], int people_decision2, int Court_decision2, int Treasury_decision2)
{
struct node *nn;
nn=(struct node*)malloc(sizeof(struct node));
strcpy(nn->issue, issue);
strcpy(nn->decision1, decision1);
nn->people_decision1=people_decision1;
nn->Court_decision1=Court_decision1;
nn->Treasury_decision1=Treasury_decision1;
strcpy(nn->decision2, decision2);
nn->people_decision2=people_decision2;
nn->Court_decision2=Court_decision2;
nn->Treasury_decision2=Treasury_decision2;
nn->iteration=3;
nn->next=NULL;
return nn;

}
struct node *My_list(struct node **list, int number)
{

FILE *fp;
int tmp=number;
char buf[100], issue[200], decision1[200], decision2[200];
int p_d1, d_d1, k_d1, p_d2, d_d2, k_d2;
int static counter=1;
snprintf(buf, sizeof(buf), "c%d.txt", counter);
counter++;
fp=fopen(buf, "r");
fgets(issue, 201, fp);
fgets(decision1, 201, fp);
fscanf(fp, "%d", &p_d1);
fscanf(fp, "%d", &d_d1);
fscanf(fp, "%d", &k_d1);
fgets(decision2, 201, fp);
fgets(decision2, 201, fp);
fscanf(fp, "%d", &p_d2);
fscanf(fp, "%d", &d_d2);
fscanf(fp, "%d", &k_d2);
fclose(fp);
*list=create_node(issue, decision1,p_d1, d_d1, k_d1, decision2, p_d2, d_d2, k_d2);
int static count=0;
count++;
if(count==tmp)
{
 counter=1;//watch out this static variable would be destroyed at the end of program not by ending the block this is due to several
   count=0;//watch out this static variable would be destroyed at the end of program not by ending the block this is due to several
     return 0;

}
    else

return My_list(&((*list)->next), number);
}
void Check_Game(int people , int Court, int Treasury, char *name_emperor)
{
struct save S;
FILE *fp;
char Question;
if(people==0||Court==0||Treasury==0)
{
    printf("Game Over :(\n");
    printf("Do you want to save your Game?[y/n]\n");
    printf(">");
    fflush(stdin);
    scanf("%c", &Question);
     if(Question=='y')
     {
    strcpy(S.empire, name_emperor);
     S.p=people;
     S.C=Court;
     S.T=Treasury;
     S.m=0;
     fp=fopen("save.bin", "wb");
     fwrite(&S, sizeof(S), 1, fp);
     fclose(fp);
     printf("Ok! Goodbye.");
    exit(0);
     }

}
int Average=(people+Court+Treasury)/3;
if(Average<10)
{
    printf("Game Over :(\n");
    printf("Do you want to save your Game?[y/n]\n");
    printf(">");
    fflush(stdin);
    scanf("%c", &Question);
    if(Question=='y')
    {
     strcpy(S.empire, name_emperor);
     S.p=people;
     S.C=Court;
     S.T=Treasury;
     S.m=0;
     fp=fopen("save.bin", "wb");
     fwrite(&S, sizeof(S), 1, fp);
     fclose(fp);
     printf("Ok! Goodbye.");
    exit(0);
    }
}

}
void Decision_effect(struct node **current, int decision, char *name_emperor)
{
if(decision==1)
{
  people+=(*current)->people_decision1;
  if(people<0)
      people=0;
        if(people>100)
              people=100;
  Court+=(*current)->Court_decision1;
  if(Court<0)
      Court=0;
       if(Court>100)
             Court=100;
  Treasury+=(*current)->Treasury_decision1;
  if(Treasury<0)
      Treasury=0;
        if(Treasury>100)
            Treasury=100;
  printf("people:%d ", people);
  printf("Court:%d ", Court);
  printf("Treasury:%d\n", Treasury);
  Check_Game(people, Court, Treasury, name_emperor);
}
 else
{
  people+=(*current)->people_decision2;
  if(people<0)
      people=0;
        if(people>100)
             people=100;
  Court+=(*current)->Court_decision2;
  if(Court<0)
      Court=0;
        if(Court>100)
              Court=100;
  Treasury+=(*current)->Treasury_decision2;
  if(Treasury<0)
      Treasury=0;
        if(Treasury>100)
             Treasury=100;
  printf("people:%d ", people);
  printf("Court:%d ", Court);
  printf("Treasury:%d\n", Treasury);
  Check_Game(people, Court, Treasury, name_emperor);
}
}
void My_Save(struct node **list, char *name_emperor)
{
struct node *current=*list;
struct save S;                  //S stands for save
int counter=0;
char Question;
printf("Do you want to save your current Game?[y/n]\n");
printf(">");
fflush(stdin);  // Just in order to clear the buffer thats it.
scanf("%c", &Question);
if(Question=='y')
{
strcpy(S.empire, name_emperor);
S.m=1;
S.p=people;
S.C=Court;
S.T=Treasury;
for(current=*list;current->next!=NULL;current=current->next)
{
  S.problems[counter]=current->iteration;
                                      counter++;
}
FILE *fp;
fp=fopen("save.bin", "wb");
fwrite(&S, sizeof(S), 1, fp);
fclose(fp);
}
printf("Ok! Goodbye.");
}
void My_Display(struct node* current, struct node **list, char *name_emperor)
{
int decision;
printf("%s\n", current->issue);
printf("[1] %s\n", current->decision1);
printf("[2] %s\n", current->decision2);
printf(">");
scanf("%d", &decision);
  if(decision==1)
       Decision_effect(&current, decision, name_emperor);
         if(decision==2)
            Decision_effect(&current, decision, name_emperor);
               if(decision==-1)
               {
                  My_Save(list, name_emperor);
                                  exit(0);
                                                    }
}
void removing_front(struct node **list)
{
*list=(*list)->next;
}
struct node *removing_end(struct node **list)
{
 if((*list)->next->next==NULL)
 {
     (*list)->next=NULL;
     return 0;
 }
removing_end(&((*list)->next));

}
struct node *removing_mid(struct node **list, int choice)
{

static int count=0;
count++;
if(count==choice-1)
{
(*list)->next=(*list)->next->next;
count=0; //watch out this static variable would be destroyed at the end of program not by ending the block this is due to several many usages
return 0;
}
return removing_mid(&((*list)->next), choice);

}
int Body_Game(struct node **list,int number, int num, char *name_emperor)
{

if(*list==NULL)
{

    My_list(list, num);
    number=num; //Due to starting to use Body_Game function again but while using number notice it is not its first value.

}
int choice;
int counter=0;
struct node *current;
srand(time(NULL));
choice=rand()%number;
choice++;
for(current=*list;counter!=choice-1;current=current->next)
{
    if(choice==1) //Due to runtime error
        break;
    if(current==NULL)
        break;
    counter++;
}
current->iteration--;
if(current->iteration==-1&&choice==1)
{

number--;
removing_front(list);
return Body_Game(list, number, num, name_emperor);
return 0;
}
if(current->iteration==-1&&choice==number)
{

    number--;
    removing_end(list);
    return Body_Game(list, number, num, name_emperor);

}
if(current->iteration==-1&&choice!=1&&choice!=number)
{

    number--;
    removing_mid(list, choice);
    return Body_Game(list, number, num, name_emperor);

}
My_Display(current, list, name_emperor);
return Body_Game(list, number, num, name_emperor);

}

int main()
{
FILE *fp;
int i=0, counter=0;
char**filename;
char buf[10];
struct node *list;
fp=fopen("CHOICES.txt", "r");
if(fp==NULL)
    return 0;
while(fgets(buf, 8, fp)!=NULL)
counter++;
close(fp);
My_list(&list, counter);
char *name_emperor;
name_emperor=(char*)malloc(50*sizeof(char));
printf("Enter your name\n");
printf(">");
scanf("%s", name_emperor);
Body_Game(&list, counter, counter, name_emperor);//note that we need two variables with the same value in this function due to passing it to My_list again and again.

}

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
    return 0;
    else

return My_list(&((*list)->next), number);
}

void My_empire(void)
{
char *name_emperor;
name_emperor=(char*)malloc(50*sizeof(char));
printf("Enter your name\n");
printf(">");
scanf("%s", name_emperor);

}
void Decision_effect(struct node **current, int decision)
{
if(decision==1)
{
  people+=(*current)->people_decision1;
  Court+=(*current)->Court_decision1;
  Treasury+=(*current)->Treasury_decision1;
  printf("people:%d ", people);
  printf("Court:%d ", Court);
  printf("Treasury:%d\n", Treasury);
}
 else
{
  people+=(*current)->people_decision2;
  Court+=(*current)->Court_decision2;
  Treasury+=(*current)->Treasury_decision2;
  printf("people:%d ", people);
  printf("Court:%d ", Court);
  printf("Treasury:%d\n", Treasury);
}
}
void My_Display(struct node* current)
{
int decision;
printf("%s\n", current->issue);
printf("[1] %s\n", current->decision1);
printf("[2] %s\n", current->decision2);
printf(">");
scanf("%d", &decision);
if(decision==1)

Decision_effect(&current, decision);
    else
        Decision_effect(&current, decision);

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
int Body_Game(struct node **list,int number)
{

int choice;
int counter=0;
struct node *current;
srand(time(NULL));
choice=rand()%number;
choice++;
for(current=*list;counter!=choice-1;current=current->next)
{
    if(choice==1) //Due to runtimef error
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
return Body_Game(list, number);
return 0;
}
if(current->iteration==-1&&choice==number)
{

    number--;
    removing_end(list);
    return Body_Game(list, number);

}
if(current->iteration==-1&&choice!=1&&choice!=number)
{

    number--;
    removing_mid(list, choice);
    return Body_Game(list, number);

}
My_Display(current);
return Body_Game(list, number);

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
My_empire();
Body_Game(&list, counter);

}


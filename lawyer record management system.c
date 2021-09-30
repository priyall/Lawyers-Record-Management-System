#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>    //for string functions
#include<ctype.h>
#include<dos.h>
#include<windows.h>   //for sleep function
#include<conio.h>
#include<unistd.h>

//global variables
char categories[][20]= {"Family","Employment","Crime","RealEstate","Business","Government","Immigration"};
//added 7 areas of practice
char pwd[10]={"admin"};
int m;

//declaring all functions
struct node* insert(struct node* node,int cost,int p,int phone, char s[],int y);
struct node* getdata();
struct node* search(struct node* node, char s[100]);
struct node* minValue(struct node* node);
struct node* deleterec(struct node* root, char s[]);
void display(struct node *root);
void displaySearch(struct node* ptr);
void viewList();
void mainmenu();
int Password(void);
void returnfunc(void);
int t(void);
void search2(struct node* ptr,int p);
struct node* editRec(struct node* ptr);

struct node
{
    char name[20];
    char cat[20];  //index number of categories array
    int fees;
    int phone_no;
    int year;
    struct node* left;
    struct node* right;
};
struct node* root=NULL;

int main()
{
    mainmenu();
    return 0;
}

void mainmenu()  //mainmenu from where all the functions can be accessed
{
    int i,j,k,ch;
    printf("\t*********************************************\n");
    printf("\t*******Lawyer Record Management System*******\n");
    printf("\t*********************************************\n\n");
    //menu driven program
    while(1)
    {
        //system("cls");
        printf("\t\t******MAIN MENU******");
        printf("\n\n\n\t\t1. Add record\n\t\t2. Search lawyer\n\t\t3. Remove a record\n\t\t4. View list\n\t\t5. Modify List\n\t\t6. Exit\n");
        t();
        printf("\nEnter your choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
        case 1:
        {
            if(root==NULL)
            k=Password();
            if(k)
            {
                root=getdata();
                printf("\nRecord added successfully\n");
                sleep(2);
            }
            break;
        }
        case 2:
        {
            if(root==NULL)
            {
                printf("No records to search\n");
                sleep(2);
                break;
            }

            char name[20];
            printf("Enter the name: ");
            scanf("%s",name);
            struct node* temp = search(root,name);
            if(temp == NULL)
            {
                printf("Entry not found!\n");
                sleep(2);
            }
            else
            {
                displaySearch(temp);    //display search entry if available
            }
            break;
        }
        case 3:
        {
            if(root==NULL)
            {
                printf("No records to search\n");
                sleep(2);
                break;
            }
            k=Password();
            if(k)
            {
                char name[20];
                printf("\nEnter the name: ");
                scanf("%s",name);
                root = deleterec(root,name);
                printf("\nRecord deleted successfully\n");
                sleep(2);
            }
            break;
        }
        case 4:
        {
            system("cls");
            viewList();
            returnfunc();
            break;
        }
        case 5:
        {
            k=Password();
            if(k)
                root=editRec(root);
        }
        break;
        case 6:
        {
            system("cls");
            printf("******Thank You******\n");
            printf("***Lawyers Record Management System***");
            printf("\n\n******************************************");
            printf("\nExiting in 3 seconds...........>");
            sleep(3);
            exit(0);
            break;
        }
        default:
        {
            printf("\aInvalid choice!\nPlease re-enter the choice");
            if(getch())
            mainmenu();
        }

        }
        system("cls");
    }
}

int Password(void)  //for password option in some menu functions
{

    system("cls");
    char d[25]="Password Protected";
    char ch,pass[10];
    int i=0,j;
    for(j=0;j<20;j++)
    {
        Sleep(25);
        printf("*");
    }
    for(j=0;j<20;j++)
    {
        Sleep(25);
        printf("%c",d[j]);
    }
    for(j=0;j<20;j++)
    {
        Sleep(25);
        printf("*");
    }
    printf("\nOnly admin users can have access to this function\n");
    printf("\nEnter Password:");

    while(ch!=13)
    {
        ch=getch();
        if(ch!=13 && ch!=8)
        {
            putch('*');   //password will be typed in '*'
            pass[i] = ch;
            i++;
        }
    }
    pass[i] = '\0';
    if(strcmp(pass,pwd)==0)
    {
        printf("\n\nPassword matched");
        printf("\nPress any key to continue.....");
        getch();
        return 1;
    }
    else
    {
        printf("\a\nIncorrect Password\n");
        getch();
        return 0;
    }
}

//insertion of lawyer entry in BST
struct node* insert(struct node* node,int cost,int p,int phone, char s[],int y)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    strcpy(temp->name,s);
    strcpy(temp->cat,categories[p-1]);
    temp->fees=cost;
    temp->phone_no=phone;
    temp->year=y;
    temp->left=temp->right=NULL;

    if(node == NULL)
    {
        return temp;
    }
    int x = strcasecmp(s,node->name);
    if(x<=0)
    {
       node->left = insert(node->left,cost,p,phone,s,y);
    }
    else
    {
        node->right=insert(node->right,cost,p,phone,s,y);
    }
    return node;
}

//input details of a lawyer by the user
struct node* getdata()
{
    char s[20];
    int num,phone,y;
    system("cls");
    printf("******Select one of the Categories******\n");
    for(int i=0;i<7;i++)
    {
        printf("%d.\t%s\n",i+1,categories[i]);
    }
    printf("\n\n\t");
    scanf("%d",&m);
    printf("\n\tEnter name: ");
    scanf("%s",s);
    printf("\tEnter the fees per hour: ");
    scanf("%d",&num);
    printf("\tEnter contact number: ");
    scanf("%d",&phone);
    printf("\tEnter total years of experience: ");
    scanf("%d",&y);
    root=insert(root,num,m,phone,s,y);
    return root;
}

//search function
struct node* search(struct node* node, char s[100])
{
    int x = strcasecmp(s,node->name);
    if (node == NULL || x==0)
       return node;
    if(x>0)
    {
        search(node->right,s);
    }
    else
    {
        search(node->left,s);
    }
}

//find minimum value node for deletion function
struct node* minValue(struct node* node)
{
        struct node* current = node;
        while(current && current->left!=NULL)
        {
            current=current->left;
        }
        return current;
}


//delete function for BST
struct node* deleterec(struct node* root, char s[])
{
    if(root == NULL)
    {
        printf("Record not found\n");
        return NULL;
    }

    int x = strcasecmp(s,root->name);
    if(x < 0)
        root->left=deleterec(root->left,s);
    else if(x>0)
        root->right=deleterec(root->right,s);
    else
    {
        if (root->left == NULL)
        {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        struct node* temp = minValue(root->right);
        strcpy(root->name,temp->name);
        strcpy(root->cat,temp->cat);
        root->fees= temp->fees;
        root->phone_no= temp->phone_no;
        root->year=temp->year;
        root->right= deleterec(root->right, temp->name);
    }
    //printf("\nRecord deleted successfully\n");
    return root;
}


//display function for the search function
void displaySearch(struct node* ptr)
{
    printf("\n\n\tName\tCategory\tFees per Hour\tYears of Experience  Contact No.\n\n");
    printf("\t%s\t%s\t\t   %d\t\t    %d\t\t  %d\n",ptr->name,ptr->cat,ptr->fees,ptr->year,ptr->phone_no);
    sleep(8);
}

//display function to print all the lawyers details
void display(struct node* ptr)
{
    if (ptr== NULL)
        return;
    display(ptr->left);
    printf("\t%s\t%s\t\t   %d\t\t    %d\t\t  %d\n",ptr->name,ptr->cat,ptr->fees,ptr->year,ptr->phone_no);
    display(ptr->right);
}

//function to get back to mainmenu
void returnfunc(void)
{
    {
        printf("\n\t Press ENTER to return to Main menu ");
    }
    a:
    if(getch()==13)    //it allows use of Enter key only
    {
        system("cls");
        mainmenu();
    }
    else
        goto a;
}

int t(void) //for display of date and time
{
    time_t t;
    time(&t);
    printf("\n\tDate and time:%s\n",ctime(&t));
    return 0 ;
}

void viewList()
{
    //display function to view list in two different ways
	int i,j,k;
	printf("\n\t\t1. List all lawyers\n\t\t2. List by category\n\n");
	printf("\tEnter your choice: ");
	scanf("%d",&i);
	sleep(1);
	system("cls");
	printf("\n\n\t*********LAWYER'S LIST*********\n\n");
    printf("\tName\tCategory\tFees per Hour\tYears of Experience  Contact No.\n\n");
	switch(i)
	{
	    case 1:
	    {
		display(root);
		returnfunc();
		break;
	    }
	    case 2:
	    {
		printf("****Categories****\n\n");
		for(j=0;j<7;j++)
		    printf("\t%d. %s\n",j+1,categories[j]);
		printf("Enter your choice of category: ");
		scanf("%d",&k);
		printf("\n");
		search2(root,k-1);  //display by category
		break;
	    }
	    default:
	    {
		printf("\aInvalid choice!\nPlease re-enter the choice");
                if(getch())
                viewList();
	    }
	    system("cls");
	}
}

void search2(struct node* ptr,int p)
{
    //prints lawyers list according to their area of practice
    if(ptr==NULL)
        return;
    int x=strcmp(ptr->cat,categories[p]);
    if(x==0)
        printf("\t%s\t%s\t\t   %d\t\t    %d\t\t  %d\n",ptr->name,ptr->cat,ptr->fees,ptr->year,ptr->phone_no);
    search2(ptr->left,p);
    search2(ptr->right,p);
}

//function to edit information about lawyers
struct node* editRec(struct node* ptr)
{
    system("cls");
    printf("\n\t\t******Modify List******\n\n");
    printf("\t1. Edit records\n\t2.Back to Main Menu\n");
    printf("\n\tEnter your choice: ");
    scanf("%d",&m);
    switch(m)
    {
        case 1:
        {
            char t[20];
            printf("\n\tEnter name: ");
            scanf("%s",t);
            //delete old value
            root=deleterec(ptr,t);
            printf("\tEnter new details: ");
            sleep(0.5);
            root=getdata();  //return new value
            printf("\n\tRecord is modified");
            sleep(2);
            return root;
        }
        break;
        case 2:
            returnfunc();
            break;
        default:
        {
            //printf("\n\tInvalid input");
            //if(getch())
            mainmenu();
        }
        system("cls");
    }
}

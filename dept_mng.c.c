#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

#define INFINITY 9999
#define MAX 10

#define NAME_LEN 32
#define ADD_LEN 64

typedef enum status{FAILURE,SUCCESS}status_code;

/* Defining Data Types */
typedef struct node
{
	struct node* prev;
	char name[NAME_LEN];
	unsigned int price;
	unsigned int quantity;
	struct node* next;
}node;



/* Main Functions */
status_code insert(node**,char [],unsigned int,unsigned int);
status_code remove_entry(node**,char []);
status_code delete_entry(node**,char []);

node* make_node(char [],unsigned int,unsigned int);

void print(node*);
void freeof_dept(node**);
void remove_space_make_uppercase(char []);
node* search(node*,char []);
void shortest_path(int G[MAX][MAX],int n,int startnode);



#endif
void main()
{
	printf("\n\n \t\t***WELCOME TO PES DEPARTMENTAL STORE***\n\n\n");
	/* Declarations Start */
	status_code SC;
	FILE *fp;
	node *dept_ptr,*ptr;
	char dumbo[2];
	char name[NAME_LEN];
	char c;
	unsigned int price;
	unsigned int quantity;
	int option,contnue;
    dept_ptr=NULL;
    ptr=NULL;
	fp=NULL;

	/* Start Reading Data from File */
    fp=fopen("data.txt","a");
    fclose(fp);
    fp=fopen("data.txt","r");
    while((c=getc(fp))!= EOF)
    {
		fseek(fp,-sizeof(char),1);
	    fscanf(fp,"%s %u %u ",name,&price,&quantity);
	    SC=insert(&dept_ptr,name,price,quantity);
	}
	fclose(fp);
	fp=NULL;
	/* End Reading Data from File */
	
	int i,j,n,u;
	n=5;
	int G[MAX][MAX]={{0,4,0,0,0},
					 {4,0,8,0,0},
					 {0,8,0,7,0},
					 {0,0,7,0,9},
					 {0,0,0,9,0}};
					 
	

    do
	{
		/* Asking for Option */
		puts("ENTER the option as per the operation you want to do. :-\n");
		puts("1- insert/update\n2- delete\n3- replace\n4- print\n5- find the nearest shop");
		printf("Your Choice is:- ");
		scanf("%d",&option);
		printf("\n\n");
		switch (option)
		{
			/* INSERT/UPDATE */
			case 1: {
						    printf("***********INSERT**********\n\n");
						    /* Data Entering Start */
							printf("Enter product Name :-\t");
							gets(dumbo);
							gets(name);
							remove_space_make_uppercase(name);
							printf("Enter price :-\t");
							scanf("%u",&price);
							printf("Enter quantity:-\t");
							scanf("%u",&quantity);

							/* Data Entering End */
							/* Inserting/Updating Data */
							SC=insert(&dept_ptr,name,price,quantity);
							if(SC==SUCCESS)
							{
								puts("\n**********product inserted**********\n");
							}
							else
							{
								puts("\n**********product insertion failed**********\n");
							}
					  		break;
				    }
			/* DELETE */
			case 2: {
							printf("***********DELETE**********\n\n");
							/* Data Entering Start */
							printf("Enter product Name :-\t");
							gets(dumbo);
							gets(name);
							remove_space_make_uppercase(name);
							/* Data Entering End */
							/* Deleting Data */
							SC=delete_entry(&dept_ptr,name);
							if(SC==SUCCESS)
							{
								puts("\n**********Data deleted**********\n");
							}
							else
							{
								puts("\n**********Data deletion failed**********\n");
							}
							break;
					}
			case 3: {
							printf("***********REPLACE************\n\n");
							printf("Enter product name :-\t");
							gets(dumbo);
							gets(name);
							remove_space_make_uppercase(name);
							SC=remove_entry(&dept_ptr,name);
							if(SC==SUCCESS)
							{
								puts("\n**********data removed**********\n");
							}
							else
							{
								puts("\n**********Data remove failed**********\n");
							}
							break;
					}


                case 4:{
                            printf("******* print******");
                            if(dept_ptr!=NULL)
                            {
                                print(dept_ptr);

                            }
							break;
                       }
				case 5:{
							printf("\nEnter the starting node: ");
									scanf("%d",&u);
									shortest_path(G,n,u);	
									break;
						}

			default:{
							break;
					}
		}
		/* Asking for CHOICE to Continue */
		puts("\n\nIf you want to continue... ? Enter 1 if YES or 0 if NO\n");
		printf("Your Choice is:- ");
		scanf("%d",&contnue);
		printf("\n\n");
	}while(contnue==1);
	/* Start Writing Data from File */
    fp=fopen("data.txt","w");
    ptr=dept_ptr;
    while(ptr!=NULL)
    {
       fprintf(fp,"%s %u %u \n",ptr->name,ptr->price,ptr->quantity);
       ptr=ptr->next;
    }
    fclose(fp);
    fp=NULL;
    /* End Writing Data from File */
	if(dept_ptr!=NULL)
	{
		print(dept_ptr);
		freeof_dept(&dept_ptr);
	}
	getch();

}


status_code insert(node **dept_pptr,char name[],unsigned int price,unsigned int quantity)
{
	status_code SC=SUCCESS;
	node *ptr,*nptr;
	if(*dept_pptr==NULL)	/* Empty List */
	{
		nptr=make_node(name,price,quantity);
		if(nptr==NULL)
		{
			SC=FAILURE;	/* Failure */
		}
		else
		{
			*dept_pptr=nptr;
		}
	}
	else	/* Non-Empty List */
	{
		ptr=search(*dept_pptr,name);	/* Searching for given Key */
		if(ptr==NULL)	/* Insert at Start */
		{
			nptr=make_node(name,price,quantity);
			if(nptr==NULL)
			{
				SC=FAILURE;	/* Failure */
			}
			else
			{

				nptr->next=*dept_pptr;
				(*dept_pptr)->prev=nptr;
				*dept_pptr=nptr;
			}
		}
		else
		{
			if((strcmp(ptr->name,name)==0) )	/* Exact match found. UPDATE */
			{
				ptr->price=price;
				ptr->quantity=ptr->quantity+quantity;


			}
			else	/* Exact match not found. Appropriate position found */
			{
				nptr=make_node(name,price,quantity);
				if(nptr==NULL)
				{
					SC=FAILURE;	/* Failure */
				}
				else
				{
					nptr->next=ptr->next;
					ptr->next=nptr;
					ptr->prev=nptr;
				}
			}
		}
	}
	return SC;
}

node* make_node(char name[],unsigned int price,unsigned int quantity)
{
	node *ptr;
	ptr=NULL;
	ptr=(node*)malloc(sizeof(node));		/* Creating Node */
	if(ptr!=NULL)		/* Assigning Values */
	{
		strcpy(ptr->name,name);

		ptr->price=price;
		ptr->quantity=quantity;

        ptr->prev=NULL;
		ptr->next=NULL;
    }
    return ptr;
}

node* search(node* dept_ptr,char name[])
{
	node*ptr,*ret_val/*,*prev*/;
	int cmp,flag=1;
	ret_val=NULL;
	ptr=dept_ptr;
	//prev=NULL;
	if(dept_ptr!=NULL)	/* Non-Empty List */
	{
		cmp=strcmp(name,ptr->name);
		while(cmp!=0 && flag==1)    /* Appropriate position according to product name is not found */
		{
			//prev=ptr;
			ptr=ptr->next;
			if(ptr!=NULL)
			{
				cmp=strcmp(name,ptr->name);
			}
			else
			{
				flag=0;		/* ptr is NULL */
			}
		}

		if(ptr!=NULL)
		{
			if((strcmp(ptr->name,name)==0) )	/* Exact match found */
			{
				ret_val=ptr;
			}
	    }
	    else
	    {
			ret_val=NULL;	/* Appropriate place found */
		}
	}
	return ret_val;
}


void print(node* dept_ptr)
{
	node* ptr;
	ptr=dept_ptr;
	printf("\n\n**********PRINTING START**********\n\n");
	while(ptr!=NULL)	/* Printing */
	{
		printf("product name :-\t");
		puts(ptr->name);

		printf("price of the product :-\t");
		printf("%u\n",ptr->price);
		printf("quantity remaining :-\t");
		printf("%u\n",ptr->quantity);

		ptr=ptr->next;
	}
	printf("\n\n**********PRINTING END**********\n\n");
	return;
}


void remove_space_make_uppercase(char name[])
{
	int i=0;
	while(name[i] != '\0')
	{
		/* MAKING UPPERCASE */
		if((name[i]>='a') && (name[i]<='z'))
	    {
	        name[i]=name[i]+'A'-'a';
	    }
	    /* REPLACING SPACE with UNDERSCORE */
	    if(name[i]==' ')
	    {
		    name[i]='_';
		}
		i++;
	}
}


status_code remove_entry(node **dept_pptr,char name[])
{
	status_code SC=SUCCESS;
	node *ptr;
	unsigned int quant;
	printf("enter the quantity:");
	scanf("%u",&quant);
	if(*dept_pptr==NULL)	/* Empty List */
	{
		SC=FAILURE;
	}
	else
	{
		ptr=search(*dept_pptr,name);	/* Searching for given Key */
		if(ptr==NULL)	/* Not Found */
		{
			printf("\n no such items present\n");
			SC=FAILURE;
		}
		else
		{
			if((strcmp(ptr->name,name)==0) )	/* Exact match found */
			{
				if(ptr->quantity==quant)
				{
					ptr->quantity=0;
				}
				else if((ptr->quantity)<quant)
				{	
					printf("\nthe number of items required are not present\n");
					SC=FAILURE;
				}
				else
				{
					ptr->quantity=(ptr->quantity)-quant;
				}
			}
			else	/* Not Found */
			{
				SC=FAILURE;
			}
		}
	}
	return SC;
}

status_code delete_entry(node **dept_pptr,char name[])
{
	status_code SC=SUCCESS;
	node*ptr,*lptr;
	if(*dept_pptr==NULL)	/* Empty List */
	{
		SC=FAILURE;
	}
	else
	{
		ptr=search(*dept_pptr,name);	/* Searching for given Key */
		if(ptr==NULL)	/* Not Found */
		{
			SC=FAILURE;
		}
		else
		{
			if((strcmp(ptr->name,name)==0) )	/* Exact match found */
			{
			    if((ptr==*dept_pptr)&&(ptr->next==NULL))/* only one node*/
                {
                  /*  node *temp=*dept_pptr;
                    *dept_pptr=NULL;
                    free(temp);*/
                    free(*dept_pptr);
                }
				if(ptr==*dept_pptr)	/* Key is present in first node only */
				{
					(*dept_pptr)->next->prev=NULL;
					(*dept_pptr)=(*dept_pptr)->next;
					free(ptr);
				}
				else	/* Key is present in other than first node */
				{
					lptr=*dept_pptr;
					while(lptr->next!=ptr)
					{
						lptr=lptr->next;
					}
					lptr->next=ptr->next;
					free(ptr);
				}
			}
			else	/* Not Found */
			{
				SC=FAILURE;
			}
		}
	}
	return SC;
}

void freeof_dept(node** dept_pptr)
{
	node* ptr;
	while(*dept_pptr!=NULL)
	{
		ptr=*dept_pptr;
		ptr->prev=NULL;
		*dept_pptr=(*dept_pptr)->next;
		free(ptr);
	}
	return;
}


/*to find the nearest shop using graphs*/

 

void shortest_path(int G[MAX][MAX],int n,int startnode)
{
 
	int path[MAX][MAX],distance[MAX],pred[MAX];
	int visited[MAX],count,mindistance,nextnode,i,j;
	
	printf("there are 5 stores in the locality , they are---- 0 , 1 , 2 , 3 , 4 & 5 \n");
	printf("Assuming that our departmental store is 0, and there are 4 different whole sale stores which sell us the products. We are trying to find out the shop which is nearest to our store\n \n"); 
	
	//pred[] stores the predecessor of each node
	//count gives the number of nodes seen so far
	//create the path matrix
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(G[i][j]==0)
				path[i][j]=INFINITY;
			else
				path[i][j]=G[i][j];
	
	//initialize pred[],distance[] and visited[]
	for(i=0;i<n;i++)
	{
		distance[i]=path[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}
	
	distance[startnode]=0;
	visited[startnode]=1;
	count=1;
	
	while(count<n-1)
	{
		mindistance=INFINITY;
		
		//nextnode gives the node at minimum distance
		for(i=0;i<n;i++)
			if(distance[i]<mindistance&&!visited[i])
			{
				mindistance=distance[i];
				nextnode=i;
			}
			
			//check if a better path exists through nextnode			
			visited[nextnode]=1;
			for(i=0;i<n;i++)
				if(!visited[i])
					if(mindistance+path[nextnode][i]<distance[i])
					{
						distance[i]=mindistance+path[nextnode][i];
						pred[i]=nextnode;
					}
		count++;
	}
 
	int min=100;//print the path and distance of each node and the nearest shop
	for(i=0;i<n;i++)
	{	
		
		if(i!=startnode)
		{
			printf("\nDistance of node%d=%d",i,distance[i]);
			printf("\nPath=%d",i);
			if(i<min)
			{
				min=i;
			}
			
			j=i;
			do
			{
				j=pred[j];
				printf("<-%d",j);
			}while(j!=startnode);
		}
		
	}
	printf("\n\nTHE NEAREST SHOP FROM OUR SHOP IS %d",min);
}
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
void main()
   {
    int choice;
    while (true){
         printf("\nEnter your choice : 1.FCFS 2.CSCAN 3.SCAN 4.Exit\n");
         scanf("%d",&choice); 
       
         if (choice == 1)
            {
             int limit,total = 0;
             printf("Enter the size of req sequence :");
             scanf("%d",&limit);
             int req[limit + 1];
             printf("\nEnterthe request seq :\n");
             for (int i = 1 ; i <= limit ; i++)
                scanf("%d",&req[i]);
             printf("\nEnter the initial position :");
             scanf("%d",&req[0]);
             
             for(int i = 1 ; i <= limit ; i++)
                {
                 int distance = abs(req[i] - req[i-1]);
                 total += distance;
                 printf("Head movement from %d to %d = %d\n",req[i-1],req[i],distance);
                }
             printf("\nTotal disk movement = %d\n",total);
             
            }
            
           else if (choice == 2)
	    {
	     int limit,total = 0,initial,max,dir;
	     printf("Enter the size of req sequence :");
	     scanf("%d",&limit);
	     int req[limit + 3];
	     printf("\nEnter the maximun range :");
	     scanf("%d",&max);
	     printf("\nEnter the initial position :");
	     scanf("%d",&initial);
	     printf("\nEnterthe request seq :\n");
	     for (int i = 0 ; i < limit ; i++)
		scanf("%d",&req[i]);
             req[limit] = 0;
             req[limit + 1] = initial;
             req[limit + 2] = max-1;
        
	     printf("\nEnter the direction [ 0 for right , 1 for left ]  :");
	     scanf("%d",&dir);
	     
	     
	     //Sorting the req sequence
	     for (int i = 0 ; i < limit+3 ; i++)
	        {
	         for (int j = i+1 ; j < limit+3 ; j++)
	          {
	           if (req[i] > req[j])
	            {
	             int temp = req[i];
	             req[i]= req[j];
	             req[j] = temp;
	            }
	          }
	        }
	     
	     //Find starting pos
             int pos = 0;
	     while(req[pos] != initial)
	         pos++;
	    
	     if (dir == 0)
	        {
	         pos++;
	         while (pos != limit + 3)
	            {
	             int distance = abs(req[pos] - req[pos-1]);
                     total += distance;
                     printf("Head movement from %d to %d = %d\n",req[pos-1],req[pos],distance);
                     pos++;
	            }
                 
                 total += max - 1;
                 printf("Head movement from %d to 0 = %d\n",max-1,max-1);
                 
                 pos = 1;
                 while (req[pos] != initial)
                    {
                     int distance = abs(req[pos] - req[pos-1]);
                     total += distance;
                     printf("Head movement from %d to %d = %d\n",req[pos-1],req[pos],distance);
                     pos++;
                    }
	         printf("\nTotal disk movement = %d\n",total);
	        }
	     else 
	        {
	         while (req[pos] != 0)
                    {
                     int distance = abs(req[pos] - req[pos-1]);
                     total += distance;
                     printf("Head movement from %d to %d = %d\n",req[pos],req[pos-1],distance);
                     pos--;
                    }
                    
                 total += max - 1;
                 printf("Head movement from 0 to %d = %d\n",max-1,max-1);
                 
                 pos = limit + 2;
                 while (req[pos - 1] != initial)
                    {
                     int distance = abs(req[pos] - req[pos-1]);
                     total += distance;
                     printf("Head movement from %d to %d = %d\n",req[pos],req[pos - 1],distance);
                     pos--;
                    }
	         printf("\nTotal disk movement = %d\n",total);
	        }
	          
	    }
	  
	  else if (choice == 3)
	    {
	     int limit,total = 0,initial,max,dir;
	     printf("Enter the size of request sequence :");
	     scanf("%d",&limit);
	     int req[limit + 3];
	     printf("\nEnter the maximun range :");
	     scanf("%d",&max);
	     printf("\nEnter the head position :");
	     scanf("%d",&initial);
	     printf("\nEnter the request sequence :\n");
	     for (int i = 0 ; i < limit ; i++)
		scanf("%d",&req[i]);
             req[limit] = 0;
             req[limit + 1] = initial;
             req[limit + 2] = max-1;
        
	     printf("\nEnter the direction [ 0 for right , 1 for left ]  :");
	     scanf("%d",&dir);
	     
	     
	     //Sorting the req sequence
	     for (int i = 0 ; i < limit+3 ; i++)
	        {
	         for (int j = i+1 ; j < limit+3 ; j++)
	          {
	           if (req[i] > req[j])
	            {
	             int temp = req[i];
	             req[i]= req[j];
	             req[j] = temp;
	            }
	          }
	        }
	        
	     //Find starting pos
             int pos = 0;
	     while(req[pos] != initial)
	         pos++;
	     
	     if (dir == 0)
	        {
	         int index = pos -1;  
	         pos++;
	         while (pos != limit + 3)
	            {
	             int distance = abs(req[pos] - req[pos-1]);
                     total += distance;
                     printf("Head movement from %d to %d = %d\n",req[pos-1],req[pos],distance);
                     pos++;
	            }
	         int distance = max - 1 - req[index]; 
	         total += distance;
                 printf("Head movement from %d to %d = %d\n",max-1,req[index],distance);
                 
                 pos = index;
                 while (pos-1 != req[0])
	            {
	             int distance = abs(req[pos] - req[pos-1]);
                     total += distance;
                     printf("Head movement from %d to %d = %d\n",req[pos],req[pos - 1],distance);
                     pos--;
	            }
	         printf("\nTotal disk movement = %d\n",total);   
	        }
	     else if (dir == 1)
	        {
	         int index = pos +1;  
	         
	         while (req[pos] != 0)
                    {
                     int distance = abs(req[pos] - req[pos-1]);
                     total += distance;
                     printf("Head movement from %d to %d = %d\n",req[pos],req[pos-1],distance);
                     pos--;
                    }
                    
	         int distance = req[index]; 
	         total += distance;
                 printf("Head movement from 0 to %d = %d\n",req[index],distance);
                 
                 pos = index+1;
                 while (pos != limit + 2)
	            {
	             int distance = abs(req[pos] - req[pos-1]);
                     total += distance;
                     printf("Head movement from %d to %d = %d\n",req[pos-1],req[pos],distance);
                     pos++;
	            }
	         printf("\nTotal head movement = %d\n",total);   
	        }

	    }
	  //////////////////////////////////////////////////////////////////////////////////////////
	  else
	     {
	      break;
             }
      }
   }

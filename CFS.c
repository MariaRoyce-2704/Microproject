#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char name[100];
    double target;
    double fund;
} charity;

charity events[5];
int eventCount=0;

//Functions~~~~~~~

void read() 
{
    FILE *fp=fopen("event.txt","r");
    if (fp==NULL) 
    {
        return; 
    }
    
    fscanf(fp,"%d\n",&eventCount);
    for (int i=0;i<eventCount;i++) 
    {
        fgets(events[i].name,100,fp);
        events[i].name[strcspn(events[i].name, "\n")] = 0;
        fscanf(fp,"%lf\n%lf\n",&events[i].target,&events[i].fund);
    }
    fclose(fp);
}


void save() 
{
    FILE *fp=fopen("event.txt","w");
    if (fp==NULL) 
    {
        printf("Unable to save events.\n");
        return;
    }
    
    fprintf(fp,"%d\n",eventCount);
    for (int i=0;i<eventCount;i++)
    {
        fprintf(fp,"%s\n",events[i].name);
        fprintf(fp,"%lf\n",events[i].target);
        fprintf(fp,"%lf\n",events[i].fund);

    }
    fclose(fp);
}

void addEvent() 
{
    if (eventCount>=5)
    {
        printf("Maximum number of events reached.\n");
        return;
    }
    
    printf("Enter event name: ");
    scanf(" %[^\n]s",events[eventCount].name);
    
    printf("Enter fundraising target: ");
    scanf("%lf",&events[eventCount].target);
    
    events[eventCount].fund=0;
    eventCount++;
    save();
    printf("Event added successfully!\n");
}



void donate() 
{
    char name[100];
    double amount;
    
    printf("Enter event name: ");
    scanf(" %[^\n]s", name);
    
    int i;
    for (i = 0;i<eventCount;i++) 
    {
        if (strcmp(events[i].name,name)==0) 
        {
            printf("Enter donation amount: ");
            scanf("%lf",&amount);
            
            events[i].fund+=amount;
            save();
            printf("Donation added successfully!\n");
            return;
        }
        printf("No such event found!!\n");
    }
    
    
}


void viewProgress() 
{
    
    
      int i;
    for (i=0;i<eventCount;i++) 
    {
        
            printf("Event Name: %s\n", events[i].name);
            printf("Fundraising Goal:Rs. %.2f\n",events[i].target);
            printf("Amount Raised:Rs. %.2f\n",events[i].fund);
            if (events[i].fund>=events[i].target) {
                printf("Goal achieved!\n");
            } 
            else 
            
            {
                printf("Progress: %.2f%%\n",(events[i].fund / events[i].target) * 100);
             }
             printf("******************************************************************\n");
    }
    
    
}


//Main function~~~~~~~~~~~~~~
int main() 
{
    read();
    
    int choice;
    
    while (1)
     {
        printf("\nCharity Fundraising System\n");
        printf("1.Add Event\n");
        printf("2.Donate\n");
        printf("3.View Progress\n");
        printf("4.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) 
        {
            case 1:
                addEvent();
                break;
            case 2:
                donate();
                break;
            case 3:
                viewProgress();
                break;
            case 4:
                //save();
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}

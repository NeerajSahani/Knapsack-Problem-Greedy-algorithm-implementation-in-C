#include<conio.h>
#include<stdio.h>

/* Defining structure for Knapsack problem	
	weight will contain weight of object
	value will contain value of object
	selected is flag that contain
	0     => not selected
	1     => selected
	0.xyz => Fraction selected
*/

typedef struct knapsack_problem{
	int value, weight;
	float value_per_unit_weight, selected;
}knapsack;

int main()
{
	int number_of_things, i, knapsack_capacity,max_index, weight_taken = 0;
	float max_value_taken = 0;
	char ch;
	
	knapsack knap[50];	//declaring array of knapsack problem structure
	
	
	/*	 				input block 									*/	
	
	printf("Enter Knapsack capacity :");	// Total capacity of knapsack
	scanf("%d", &knapsack_capacity);
	
	printf("Enter number of things :");
	scanf("%d", &number_of_things);			//Number of objects available in store
	
	printf("Enter values [weight, value] \n");
	for(i=1; i<=number_of_things; i++)		//Input in form [weight of object, value of object]	
	{
		printf("%2d) ", i);
		scanf("%d %c %d", &(knap[i].weight), &ch, &(knap[i].value));	// %c and ch is used for comma(,)
		knap[i].value_per_unit_weight = float(knap[i].value ) / float(knap[i].weight); //calculat value per unit weight
		knap[i].selected = 0;			// initially object is not selected
	}
	
	
	/* 							Process block				*/
	 
	while(weight_taken < knapsack_capacity)	//once knapsack is full leave the store
	{
		float max_value = -999999.00;		//so small because is should be replace by first object's value 
		for(i=1; i<=number_of_things; i++)
		{
			/* value should not be in knapsack and is should have maximum value	*/
			if((max_value < knap[i].value_per_unit_weight) && knap[i].selected == 0 )	
				{
					max_value = knap[i].value_per_unit_weight;
					max_index = i;
				}
		}
		
		/* checking whether full object can be added in knapsack or not	*/
		if((weight_taken + knap[max_index].weight) <= knapsack_capacity )	
		 {
			knap[max_index].selected = 1;
			weight_taken+=knap[max_index].weight;
		 }
		else
		 {
		 	/*  if whole object can't be added then adding it's fractional part formula is, 
		 			(knapsack_capacity - total_weight_taken) / object's weight				*/
			knap[max_index].selected = float(knapsack_capacity - weight_taken)/knap[max_index].weight; 	
	     	weight_taken += knap[max_index].weight * knap[max_index].selected;
		 }
	}
	
	
	/*									output block						 		*/
	
	printf("Optimal Solution is...\t\t");
	for(i=1; i<=number_of_things; i++)
	{
			if(int(knap[i].selected) - knap[i].selected  == 0) 		  //whole object is not taken
				printf("  %.0f  ", knap[i].selected);
			else									
				printf("  %.2f  ", knap[i].selected);				//fraction is taken
			max_value_taken += knap[i].value * knap[i].selected;   // calculating value of objects
	}
	printf("\nMaximum value taken is :%.2f", max_value_taken);
	getch();	
}

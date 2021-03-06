/**************************************************
 *                                                *
 * First attempt at a code to calcule lost barley *
 * by A. Farmer                                   *
 * 18/05/18                                       *
 *                                                *
 **************************************************/

// Include any headers from the C standard library here
#include <stdio.h>

// Define any constants that I need to use here
#define Pi 3.14

// This is where I should put my function prototypes
float area_of_ring(float outer_radius, float inner_radius); 

// Now I start my code with main()
int main() {

    // In here I need to delare my variables
        int i = 0;
	float total_area;
	float area[5];
	float outer_radius[5];
	float inner_radius[5];
	float loss_in_kg;

    // Next I need to get input from the user.
    // I'll do this by using a printf() to ask the user to input the radii.

	printf("\nEnter the outer radii:\t");
	scanf("%f %f %f %f %f", &outer_radius[0], &outer_radius[1], &outer_radius[2], &outer_radius[3], &outer_radius[4]);

	printf("\nEnter the inner radii:\t");
        scanf("%f %f %f %f %f", &inner_radius[0], &inner_radius[1], &inner_radius[2], &inner_radius[3], &inner_radius[4]);


    // Now I need to loop through the radii caluclating the area for each

	while (i<5) {
		area[i] = area_of_ring(outer_radius[i], inner_radius[i]);
		i++;
	}

    // Next I'll sum up all of the individual areas

	total_area = 0.0;
	for (i=0; i<5; i++) {
		total_area += area[i];
	}

    /******************************************************************
     *                                                                *
     * Now I know the total area I can use the following information: *
     *                                                                *
     * One square meter of crop produces about 135 grams of barley    *
     *                                                                *
     * One kg of barley sells for about 10 pence                      *
     *                                                                *
     ******************************************************************/

    // Using the above I'll work out how much barley has been lost.
    loss_in_kg = total_area*0.135;

    // Finally I'll use a printf() to print this to the screen.
    printf("\nTotal area lossed in m^2 is:\t%f\n", total_area);
    printf("Total loss in kg is:\t\t%f\n", loss_in_kg);

    return(0);
}

// I'll put my functions here:

float area_of_ring(float outer_radius, float inner_radius) {
	float area = Pi * (outer_radius * outer_radius - inner_radius * inner_radius);
	return area;
}

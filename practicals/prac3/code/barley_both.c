/**************************************************
 *                                                *
 * Code to calcule lost barley, both for areas of circles and rings *
 * by S. Elliott                                  *
 * 22/05/18                                       *
 *                                                *
 **************************************************/

// Include any headers from the C standard library here
#include <stdio.h>

// Define any constants that I need to use here
#define Pi 3.14

// This is where I should put my function prototypes
float area_of_ring(float ring_outer_radius, float ring_inner_radius); 
float area_of_circle(float circle_radius);
float area_of_field(float length, float width);
float percentage_loss(float total_area, float field_area);
float monetary_loss(float total_area); 

// Now I start my code with main()
int main() {

    // In here I need to delare my variables
        int i = 0, number_of_circles=0, number_of_rings=0;
	float total_area;
	float *ring_outer_radius;
	float *ring_inner_radius;
	float *circle_radius;
	float loss_in_kg;
	float field_length;
	float field_width;
	float field_area;
	
    // Next I need to get input from the user.
    // I'll do this by using a printf() to ask the user to input the radii.

	printf("\nEnter the number of circles to calculate:\t");
	scanf("%d", &number_of_circles);

	printf("\nEnter the number of rings to calculate:\t");
        scanf("%d", &number_of_rings);

    // Allocate the memory based on the number of circles and rings to calculate

	circle_radius = (float *)malloc(number_of_circles*sizeof(float));
	
	ring_outer_radius = (float *)malloc(number_of_rings*sizeof(float));
	ring_inner_radius = (float *)malloc(number_of_rings*sizeof(float));

	printf("\nEnter the circle radii:\t");
        for (i=0; i<number_of_circles; i++) scanf("%f", &circle_radius[i]);

	printf("\nEnter the ring outer radii:\t");
	for (i=0; i<number_of_rings;i++) scanf("%f", &ring_outer_radius[i]);

	printf("\nEnter the ring inner radii:\t");
        for (i=0; i<number_of_rings;i++) scanf("%f", &ring_inner_radius[i]);

	printf("\nEnter the length then width of the field:\t");
	scanf("%f %f", &field_length, &field_width);

    // Now I need to loop through the radii caluclating the area for each, and summing each to total_area

	i=0;
	while (i<number_of_circles) {
		total_area += area_of_circle(circle_radius[i]);
		i++;
	}

   	i=0;
	while (i<number_of_rings) {
		total_area += area_of_ring(ring_outer_radius[i], ring_inner_radius[i]);
		i++;
	}

    // Now find the total area of the rectangular field
	field_area = area_of_field(field_length, field_width);


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
    printf("\nTotal area loss in m^2 is:\t%f\n", total_area);
    printf("Total loss in kg is:\t\t%f\n", loss_in_kg);
    printf("Total percentage loss is:\t%f, corresponding to a total monetary loss in pounds of:\t%f\n", percentage_loss(total_area, field_area), monetary_loss(total_area));

    return(0);
}

// I'll put my functions here:

float area_of_ring(float ring_outer_radius, float ring_inner_radius) {
	float area = Pi * (ring_outer_radius * ring_outer_radius - ring_inner_radius * ring_inner_radius);
	return area;
}

float area_of_circle(float circle_radius) {
	float area = Pi * circle_radius * circle_radius;
	return area;
}

float area_of_field(float length, float width) {
	float area = length * width;
	return area;
}

float percentage_loss(float total_area, float field_area) {
	float loss = total_area/field_area;
	return loss;
}

float monetary_loss(float total_area) {
	float loss = total_area * 0.1;
	return loss;
}

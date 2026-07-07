/* Ethan Huynh - Lab 6
To compile use: gcc -Wall -o listingSort listingSort.c
To execute use: ./listingSort
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 1024
#define MAX_ITEMS 30000 //listings.csv has around 25k rows

//struct from listing.c
struct listing {
    int id, host_id, minimum_nights, number_of_reviews;
    int calculated_host_listings_count, availability_365;
    char *host_name, *neighbourhood_group, *neighbourhood, *room_type;
    float latitude, longitude, price;
};

/* parses one CSV line into a struct
   strtok() splits the string by commas
   atoi() and atof() converts strings to numbers
   strdup() duplicates strings (needed because strtok() modifies buffer)
*/
struct listing getfields(char *line) {
    struct listing item;

    item.id = atoi(strtok(line, ","));
    item.host_id = atoi(strtok(NULL, ","));
    item.host_name = strdup(strtok(NULL, ","));
    item.neighbourhood_group = strdup(strtok(NULL, ","));
    item.neighbourhood = strdup(strtok(NULL, ","));
    item.latitude = atof(strtok(NULL, ","));
    item.longitude = atof(strtok(NULL, ","));
    item.room_type = strdup(strtok(NULL, ","));
    item.price = atof(strtok(NULL, ","));
    item.minimum_nights = atoi(strtok(NULL, ","));
    item.number_of_reviews = atoi(strtok(NULL, ","));
    item.calculated_host_listings_count = atoi(strtok(NULL, ","));
    item.availability_365 = atoi(strtok(NULL, ","));

    return item;
}

//functions that compares two elements
//comparator for host_name (alphabetical)
int compare_host_name(const void *a, const void *b) {
    const struct listing *la = (const struct listing *)a;
    const struct listing *lb = (const struct listing *)b;
    return strcmp(la->host_name, lb->host_name);
}

//comparator for price (ascending)
int compare_price(const void *a, const void *b) {
    const struct listing *la = (const struct listing *)a;
    const struct listing *lb = (const struct listing *)b;

    if (la->price < lb->price) return -1;
    if (la->price > lb->price) return 1;
    return 0;
}

//writes one struct as a CSV line
void write_listing_csv(FILE *out, struct listing item) {
    fprintf(out, "%d,%d,%s,%s,%s,%.6f,%.6f,%s,%.2f,%d,%d,%d,%d\n",
            item.id,
            item.host_id,
            item.host_name,
            item.neighbourhood_group,
            item.neighbourhood,
            item.latitude,
            item.longitude,
            item.room_type,
            item.price,
            item.minimum_nights,
            item.number_of_reviews,
            item.calculated_host_listings_count,
            item.availability_365);
}

int main() {
    struct listing list_items[MAX_ITEMS];
    char line[LINESIZE];
    int count = 0;

    //open input CSV file
    FILE *fptr = fopen("listings.csv", "r");
    if (fptr == NULL) {
        perror("Error opening listings.csv");
        exit(1);
    }

    //read each line and parse into a struct array
    while (fgets(line, LINESIZE, fptr) != NULL) {
        list_items[count++] = getfields(line);
    }
    fclose(fptr);

    //sort_by_host_name
    qsort(list_items, count, sizeof(struct listing), compare_host_name);

    FILE *host_out = fopen("sorted_by_host_name.csv", "w");
    if (host_out == NULL) {
        perror("Error opening sorted_by_host_name.csv");
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        write_listing_csv(host_out, list_items[i]);
    }
    fclose(host_out);

    //sort_by_price
    qsort(list_items, count, sizeof(struct listing), compare_price);

    FILE *price_out = fopen("sorted_by_price.csv", "w");
    if (price_out == NULL) {
        perror("Error opening sorted_by_price.csv");
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        write_listing_csv(price_out, list_items[i]);
    }
    fclose(price_out);

    return 0;
}

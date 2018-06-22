/* File: sort_books.c */
/* Author: Adrianne Santinor */
/* Date: 4/2/18 */
/* Description: C code that uses Assembly subroutine to sort books by year and in alphabetical order
/*					Heavily based on code provided by professor. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 // * Following is straight from the project description
 */
#define TITLE_LEN       32
#define AUTHOR_LEN      20 
#define SUBJECT_LEN     10 

struct book {
    char title[TITLE_LEN + 1];
    char author[AUTHOR_LEN + 1];    /* first author */
    char subject[SUBJECT_LEN + 1];  /* Nonfiction, Fantasy, Mystery, ... */
    unsigned int year;              /* year of e-book release */
};

/*
 * Declarations for functions that are defined in other files
 */
extern int bookcmp(void);

/*
 * Declarations for global variables that need to be accessed
 * from other files
 */
struct book *book1;
struct book *book2;

#define MAX_BOOKS 100

/* declaration of functions defined later in program */
void sort_books(struct book books[], int numBooks);
void print_books(struct book books[], int numBooks);

int main(int argc, char **argv) {
	
	struct book books[MAX_BOOKS];
	int i;
	int numBooks; 
	int numFields;
	
	/* STUB: ADD CODE HERE TO READ A RECORD AT A TIME FROM STDIN USING scanf()
	UNTIL IT RETURNS EOF 
	*/
	
	for (i = 0; i < MAX_BOOKS; i++) {
		/* Sample line: "Breaking Point, Pamela Clare, Romance, 2011" */
		
		/* I decided to give you the scanf() format string; note that
		* for the string fields, it uses the conversion spec "%##[^,]",
		* where "##" is an actual number. This says to read up to a
		* maximum of ## characters (not counting the null terminator!),
		* stopping at the first ','  Also note that the first field spec--
		* the title field--specifies 80 chars.  The title field is NOT
		* that large, so you need to read it into a temporary buffer first.
		* All the other fields should be read directly into the struct book's
		* members.
		*/
		
		/* string to get whole title and truncate later */
		char tempTitle[80];
		
		numFields = scanf("%80[^,], %20[^,], %10[^,], %u \n", &tempTitle, &books[i].author, &books[i].subject, &books[i].year);
		
		if (numFields == EOF) {
			numBooks = i;
			break;
		}
		
	/* Now, process the record you just read.
	 * First, confirm that you got all the fields you needed (scanf()
	 * returns the actual number of fields matched).
	 * Then, post-process title (see project spec for reason)
	 */

	/*STUB: VERIFY AND PROCESS THE RECORD YOU JUST READ
	*/
		
		/* checks that scanf read a title, author, subject, and year */
		if (numFields != 4) {
			printf("Not a valid book.\n");
			exit(1);
		}
		
		/* null-terminates every string */
		strncpy(books[i].title, tempTitle, TITLE_LEN);
		books[i].title[TITLE_LEN] = '\0';
		books[i].author[AUTHOR_LEN] = '\0';
		books[i].subject[SUBJECT_LEN] = '\0';
		
	}
	
	/* Following assumes you stored actual number of books read into
	* var numBooks
	*/
	
	sort_books(books, numBooks);
	print_books(books, numBooks);
	
	exit(1);
}

/*
 * sort_books(): receives an array of struct book's, of length
 * numBooks.  Sorts the array in-place (i.e., actually modifies
 * the elements of the array).
 *
 * This is almost exactly what was given in the pseudocode in
 * the project spec--need to replace STUBS with real code
 */
void sort_books(struct book books[], int numBooks) {
	int i;
	int j;
	int min;
	int cmpResult;
	struct book tempBook;
	
	for (i = 0; i < numBooks - 1; i++) {
		
		min = i;
		
		for (j = i + 1; j < numBooks; j++){
			/* Copy pointers to the two books to be compared into the
			* global variables book1 and book2 for bookcmp() to see
			*/
			book1 = &books[min];
			book2 = &books[j];
			
			cmpResult = bookcmp();
			
			/* bookcmp returns result in register EAX--above saves
			* it into cmpResult */
			
			if (cmpResult == 1){
				min = j;
			}
		}
		
		if (min != i) {
				tempBook = books[i];
				books[i] = books[min];
				books[min] = tempBook;
				}
		}
}

void print_books(struct book books[], int numBooks) {

    /* STUB: ADD CODE HERE TO OUTPUT LIST OF BOOKS
		*/
	int i; 
	
	if (numBooks <= 0){
		printf("No books to print.\n");
		exit(1);
	}
	
	for (i = 0; i < numBooks; i++){
		printf("%s, %s, %s, %u \n", books[i].title, books[i].author, books[i].subject, books[i].year);
	}

}

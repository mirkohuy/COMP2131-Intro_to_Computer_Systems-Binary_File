// T00705586 Huy Mirko October 2022 COMP2131 Assignment 2

#include <stdio.h>
#include <string.h>

// student struct
struct studentInfo{
  char id[10];
  char name[20];
  char email[20];
  char course[20];
  char grade[10];
};

// function to create file
void createFile(){
  
  // create and initialize array of structs
  printf("\nCreating file...\n");

  // declare variables
  FILE *filePointer;
  filePointer = fopen("record.bin", "wb");
  struct studentInfo student;
  
  strcpy(student.id, "T001");
  strcpy(student.name, "Macbeth");
  strcpy(student.email, "macbeth@school.ca");
  strcpy(student.course, "COMP1234");
  strcpy(student.grade, "C+");
  fwrite(&student, sizeof(struct studentInfo), 1, filePointer);
    
  strcpy(student.id, "T002");
  strcpy(student.name, "Juliet");
  strcpy(student.email, "juliet@school.ca");
  strcpy(student.course, "COMP5678");
  strcpy(student.grade, "F");
  fwrite(&student, sizeof(struct studentInfo), 1, filePointer);
    
  strcpy(student.id, "T003");
  strcpy(student.name, "Othello");
  strcpy(student.email, "othello@school.ca");
  strcpy(student.course, "COMP9999");
  strcpy(student.grade, "A+");
  fwrite(&student, sizeof(struct studentInfo), 1, filePointer);

  // close the file
  fclose(filePointer);
  printf("\nFile created.\n");
}

// function to display file
void displayFile(){
  printf("\nDisplaying file...\n\n");

  // declare variables
  FILE *filePointer;
  filePointer = fopen("record.bin", "rb");
  struct studentInfo student;
  
  // open file, read and close
  while(fread(&student, sizeof(struct studentInfo), 1, filePointer)){
    printf("ID: %s\n", student.id);
    printf("Name: %s\n", student.name);
    printf("Email: %s\n", student.email);
    printf("Course: %s\n", student.course);
    printf("Grade: %s\n", student.grade);
    printf("\n");
  }

  // close the file
  fclose(filePointer);
  printf("File display complete.\n");
}

// function to seek a record
void seekRecord(){
  printf("\nBegin seek file process...\n\n");

  // declare variables
  FILE *filePointer;
  filePointer = fopen("record.bin", "rb");
  struct studentInfo student;
  char seekID[10];

  // get user input
  printf("Enter a student number to display info: ");
  scanf("%s", seekID);

  // search the struct array for seekID
  while(fread(&student, sizeof(struct studentInfo), 1, filePointer)){
    if(strcmp(student.id, seekID) == 0){
      printf("ID: %s\n", student.id);
      printf("Name: %s\n", student.name);
      printf("Email: %s\n", student.email);
      printf("Course: %s\n", student.course);
      printf("Grade: %s\n", student.grade);
      printf("\n");
    }
  }

  // close the file
  fclose(filePointer);
  printf("File seek complete.\n");
}

// function to update file
void updateRecord(){
  printf("\nBegin record update process...\n\n");

  // declare variables
  FILE *filePointer1, *filePointer2;
  filePointer1 = fopen("record.bin", "rb");
  filePointer2 = fopen("copy.bin", "wb");
  struct studentInfo student;
  char seekID[10];

  // error handling
  if(filePointer1 == NULL){
    fprintf(stderr, "Error opening file.");
    exit(1);
  }
  
  // get user input
  printf("Enter the student ID of the record you wish to update: ");
  scanf("%s", seekID);

  // write to new file, except target
  while(fread(&student, sizeof(struct studentInfo), 1, filePointer1)){
    if(strcmp(student.id, seekID) != 0){
      fwrite(&student, sizeof(struct studentInfo), 1, filePointer2);
    }
  }

  // get user input for new student info
  struct studentInfo studentNew;
  printf("Enter a new ID: ");
  scanf("%s", studentNew.id);
  printf("Enter a new name: ");
  scanf("%s", studentNew.name);
  printf("Enter a new email: ");
  scanf("%s", studentNew.email);
  printf("Enter a new course: ");
  scanf("%s", studentNew.course);
  printf("Enter a new grade: ");
  scanf("%s", studentNew.grade);

  // write the new info to the copy file
  fwrite(&studentNew, sizeof(struct studentInfo), 1, filePointer2);

  // close the files
  fclose(filePointer1);
  fclose(filePointer2);
  remove("record.bin");
  rename("copy.bin", "record.bin");
  printf("Record update complete.\n");
}

// function to delete a record
void deleteRecord(){
  printf("\nBegin record delete process...\n\n");

  // declare variables
  FILE *filePointer1, *filePointer2;
  filePointer1 = fopen("record.bin", "rb");
  filePointer2 = fopen("copy.bin", "wb");
  struct studentInfo student;
  char seekID[10];

  // error handling
  if(filePointer1 == NULL){
    fprintf(stderr, "Error opening file.");
    exit(1);
  }
  
  // get user input
  printf("Enter the student ID of the record you wish to delete: ");
  scanf("%s", seekID);

  // write to new file, except target
  while(fread(&student, sizeof(struct studentInfo), 1, filePointer1)){
    if(strcmp(student.id, seekID) != 0){
      fwrite(&student, sizeof(struct studentInfo), 1, filePointer2);
    }
  }
  
  // close the files
  fclose(filePointer1);
  fclose(filePointer2);
  remove("record.bin");
  rename("copy.bin", "record.bin");
  printf("\nRecord deletion complete.\n");
}

// main function
int main(void) {

  // declare variables
  int isPlaying = 1;

  // program loop
  while(isPlaying = 1){

    //display options
    printf("\nMAIN MENU\n\n");
    printf("1. Create the binary file.\n");
    printf("2. Display the contents of the file.\n");
    printf("3. Seek a specific record.\n");
    printf("4. Update the contents of a record.\n");
    printf("5. Delete a record for the specific ID.\n");
    printf("6. Exit.\n");

    // get user input
    int userInput;
    printf("Please enter your choice: ");
    scanf("%d", &userInput);

    // select the user's choice
    switch(userInput){
      case 1: 
        system("clear");
        createFile();
        break;
      case 2: 
        system("clear");
        displayFile();
        break;
      case 3: 
        system("clear");
        seekRecord();
        break;
      case 4: 
        system("clear");
        updateRecord();
        break;
      case 5: 
        system("clear");
        deleteRecord();
        break;
      case 6: 
        exit(1);
    }
  }
  
  return 0;
}
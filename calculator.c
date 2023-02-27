#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>

/* NOTES

You have to do some extra stuff to run it on noMachine try:
gcc -Wall (filename).c -lm -o myProg

1. I left some print statements that I commented out, I used those for testing
2. All the Selections are in different functions
3. Since we didn't do memory allocation yet I assumed maximum memory was 1000
4. I used some global variables, I know, "global variables bad", but it works better than local variables in this case
5. I used strings to check inputs since it would be harder with floats, strings let you check every single character
6. I used different functions for the first selection and the rest of the selections since I wanted to display different messages
*/

// functions for the different selections
char first_selection(void);
char calculator_selection(char selection);
float selection_B(float num1, char operation, float num2);
float selection_U(char operation, float num1);
void selection_A(char a_selection);
void selection_M(float memory[1000], int amount);
void selection_R(float memory[1000]);
void selection_V(char variable, float number, char* add_variable, float* add_number);
int selection_X(int check);

// global variables
float a = 0, b = 0, c = 0, d = 0, e = 0;
int argument1, argument2;
int argument[2];
float memory_start[1000] = {}; // assume maximum memory is 1000
int memory_counter = 0;

int main(void) {
  // local variables
  int check = 0; // used to see if loop should execute
  int flag = 0; // this gets more important in part A, since it can differentiate between different kinds of input
  int ch;
  int counter = 0;
  char character1;
  char character2;
  float num1;
  float num2;
  float result;
  char variable;
  char a_selection;
  // char a_operation[1];
  // char n1[20] = {};
  // char n2[20] = {};
  float num1_a = 11;
  float num2_a;
  char selection;
  char operation;
  char variable_variable;
  float variable_num1;
  int arg1, arg2;

  selection = first_selection();

  while(check!=1){ // while loop for different selections
    if(selection == 'B'){ // selection B
      printf("Please enter the first number\n");
      // arg1 = scanf("%f%c", &num1, &character1);
      arg1 = scanf(" %f%[^\n]c", &num1, &character1);
      if(arg1 != 1){
        while (getchar() != '\n');
      }
      argument[0] = arg1;
      printf("Please enter the operation ( + , - , * , / , % , ^ (for power) ):\n");
      scanf(" %c", &operation);
      while (getchar() != '\n');
      scanf("");
      printf("Please enter the second number\n");
      // arg2 = scanf("%f%c", &num2, &character2);
      arg2 = scanf(" %f%[^\n]c", &num2, &character2);
      if(arg2 != 1){
        while (getchar() != '\n');
      }
      argument[1] = arg2;
      // printf("%d %d", arg1, arg2);
      result = selection_B(num1, operation, num2); // call function for selection B
      memory_start[memory_counter] = result;
      memory_counter++;
      printf("The result is: \t %.2f\n", result);
    } else if(selection == 'U'){ // selection U
      printf("Please enter the operation ( S (for square root) , L (for logarithm) , E (for exponential) , C (for ceil) , F (for floor) ):\n");
      scanf(" %c", &operation);
      while (getchar() != '\n');
      printf("Please enter an appropriate number\n");
      argument1 = scanf("%f%c", &num1, &character1);
      if(argument1 != 2){
        while (getchar() != '\n');
      }
      result = selection_U(operation, num1); // call function for selection U
      memory_start[memory_counter] = result;
      memory_counter++;
      printf("The result is: \t %.2f\n", result);
    } else if(selection == 'V'){ // selection V
      printf("Please enter the name of the variable (A single character between 'a' to 'e'):\n"); 
      scanf(" %c", &variable_variable);
      while (getchar() != '\n');
      printf("Please enter a value to assign to the variable:");
      scanf("%f", &variable_num1);
      selection_V(variable_variable, variable_num1, &variable, &num1); // call function for selection V
      printf("Variable %c is set to:\t %g\n", variable, num1);
    } else if(selection == 'A'){ // selection A
      printf("Select one of the following items:\n");
      printf("B) - Binary Mathematical Operations, such as addition and subtraction.\n");
      printf("U) - Unary Mathematical Operations, such as square root, and log.\n");
      printf("X) - Exit and back to the main menu\n");
      scanf(" %c", &a_selection); // pick a selection within A
      selection_A(a_selection); // call function for selection A
      // memory_start[memory_counter] = result;
      // memory_counter++;
    } else if(selection == 'M'){ // selection M
      selection_M(memory_start, memory_counter); // call function for selection M
    } else if(selection == 'R'){ // selection R
      selection_R(memory_start); // call function for selection R
      memory_counter = 0; // reset counter for memory
    } else if(selection == 'X'){ // exit program
      check = selection_X(check);
    }
    if(selection != 'X'){ // if user picks an invalid input or previous selection ends get another input
      selection = 'n';
      selection = calculator_selection(selection); // call function to get new selection
    }
  }
  printf("Thanks for using my Simple Calculator. Hope to see you soon again, Goodbye!\n");
}

char first_selection(void){ // function for first selection
  char selection;
  // print lines below print a welcome message 
  printf("Welcome to my Command-Line Calculator (CLC)\n");
  printf("Developer: Sohil Waraich\n");
  printf("Version: 3, Assignment 3\n");
  printf("Date: December 1, 2021\n");
  printf("-----------------------------------------------------------\n");
  printf("Please select one of the following items:\n");
  printf("B) - Binary Mathematical Operations such as addition and subtraction.\n");
  printf("U) - Unary Mathematical Operations, such as square root, and log.\n");
  printf("A) - Advances Mathematical Operations, using variables, arrays.\n");
  printf("V) – Define variables and assign them values.\n");
  printf("M) – Select M to see the memory.\n");
  printf("R) – Erase the memory.\n");
  printf("X) - Exit\n");

  // intial selection
  selection = toupper(getchar());
  while (getchar() != '\n');
  return selection;
}

char calculator_selection(char selection){ // function for new selection
  bool valid_selection = false;
  selection = toupper(selection);
  while(valid_selection == false) {
    printf("Please select your option ( B (Binary operation), U (Unary operation) , A (Advanced), V (Variables), M (Memory), R(Remove memory), X (Exit))\n");
    scanf(" %c", &selection);
    selection = toupper(selection);
    // printf("%c\n", selection);
    if(selection == 'B'){
      // printf("you chose b\n");
      valid_selection = true;
    } else if(selection == 'U'){
      // printf("you chose u\n");
      valid_selection = true;
    } else if(selection == 'V'){
      // printf("you chose v\n");
      valid_selection = true;
    } else if(selection == 'A'){
      // printf("you chose a\n");
      valid_selection = true;
    } else if(selection == 'M'){
      // printf("you chose m\n");
      valid_selection = true;
    } else if(selection == 'R'){
      // printf("you chose r\n");
      valid_selection = true;
    } else if(selection == 'X'){
      // printf("you chose x\n");
      valid_selection = true;
    }
    if(valid_selection == false){
      printf("%c is invalid\n", selection);
    }
  }
  return selection;
}

float selection_B(float num1, char operation, float num2){ // function for selection B
  int flag = 0;
  char n1[20] = {};
  char n2[20] = {};
  float num1_a;
  float num2_a;
  float result;

  gcvt(num1, 20, n1);

  if(argument[0] != 1){
    printf("Please enter the first number\n");
    memset(n1, 0, 20);
    scanf("%19s", n1);
  } else {
    // printf("number (not character) is %s", n1);
  }

  while(flag == 0) { // this one is more complicated, it gets the user input then determines if it is a number or letter
    for(int i = 0; i < 20; i++){
      if(isalpha(n1[i])){
        i = 100;
      }
      if(i==19){
        flag = 1;
        break;
      }
    }
    for(int i = 0; i < 20; i++){
      if(isdigit(n1[i])){
        i = 100;
      }
    }
    if(flag == 0){
      memset(n1, 0, 20);
      printf("Please enter the first number\n");
      while (getchar() != '\n');
      scanf("%19s", n1);
    }
  }
  flag = 0; // reset this
  // while (getchar() != '\n');

  num1_a = atof(n1);

  while(flag == 0) { // check operation
    if(operation=='+'){
      flag = 1;
      break;
    } else if(operation=='-') {
      flag = 1;
      break;
    } else if(operation=='*') {
      flag = 1;
      break;
    } else if(operation=='/'){
      flag = 1;
      break;
    } else if(operation=='%') {
      flag = 1;
      break;
    } else if(operation=='^'){
      flag = 1;
      break;
    } else {
      while (getchar() != '\n');
      puts("Please enter a valid operator");
      scanf(" %c", &operation);
    }
  }
  flag = 0;
  scanf("");

  gcvt(num2, 20, n2);

  if(argument[1] != 1){
    printf("Please enter the second number\n");
    memset(n2, 0, 20);
    scanf("%19s", n2);
  } else {
    // printf("number (not character) is %s", n1);
  }

  while(flag == 0) { // this one is more complicated, it gets the user input then determines if it is a number or letter
    if((atof(n2) == 0 && operation == '/') || (atof(n2) == 0 && operation == '%')){
      memset(n2, 0, 20);
      printf("Please enter a non-zero number\n");
      scanf("%19s", n2);
    }
    for(int i = 0; i < 20; i++){
      if(isalpha(n2[i])){
        i = 100;
      }
      if(i==19){
        flag = 1;
        break;
      }
    }
    for(int i = 0; i < 20; i++){
      if(isdigit(n2[i])){
        i = 100;
        while (getchar() != '\n');
      }
    }
    if(flag == 0){
      memset(n2, 0, 20);
      printf("Please enter the second number\n");
      while (getchar() != '\n');
      scanf("%19s", n2);
    }
  }
  flag = 0; // reset this
  num2_a = atof(n2);

  if(operation=='+'){
    result = num1_a + num2_a;
  }
  else if(operation=='-'){
    result = num1_a - num2_a;
  }
  else if(operation=='*'){
    result = num1_a * num2_a;
  }
  else if(operation=='/'){
    result = num1_a / num2_a;
  }
  else if(operation=='%'){
    result = remainder(num1_a, num2_a);
  }
  else if(operation=='^'){
    result = pow(num1_a, num2_a);
  }
  return result;
}

float selection_U(char operation, float num1){ // function for selection U
  int counter = 0;
  int flag = 0;
  char n1[20] = {};
  char n2[20] = {};
  float num1_a;
  float num2_a;
  char a_selection;
  float result;
  int ch;
  int check = 0;
  bool input = true;

  while(check != 1){
    if(operation == 'S' || operation == 's') { // square root
      // printf("Enter a positive value or a variable name ('a' to 'e') with a positive value:\n");
      // printf("start unary\n");
      if(input == true){
        gcvt(num1, 20, n1);
        if(argument1 != 2){
          printf("Enter a positive value\n");
          memset(n1, 0, 20);
          scanf("%19s", n1);
        }
      }

      if(input == false){
        printf("Enter a positive value\n");
        scanf("%19s", n1);
      }
      while(flag == 0) {
        while(counter >= 1){
          scanf("%19s", n1);
          break;
        }
        for(int i = 0; i < 20; i++){
          if(isalpha(n1[i])){
            i = 100;
          }
          if(i==19){
            flag = 1;
            break;
          }
        }
        if(flag == 0){
          memset(n1, 0, 20);
          printf("Enter a positive value\n");
          while (getchar() != '\n');
        }
        if(n1[0] == '-'){
          printf("Enter a positive value\n");
          flag = 0;
        }
        counter++;
      }
      flag = 0;
      counter = 0;
      scanf("");
      num1_a = atof(n1);

      result = sqrt(num1_a);
      // printf("The result is: \t %.2f\n", result);
      a_selection='n';
      check = 1;
    }
    else if(operation == 'L' || operation == 'l') { // logarithm

      if(input == true){
        gcvt(num1, 20, n1);
        if(argument1 != 2){
          printf("Enter a positive value (non-zero)\n");
          memset(n1, 0, 20);
          scanf("%19s", n1);
        }
      }
      if(input == false){
        printf("Enter a positive value (non-zero)\n");
        scanf("%19s", n1);
      }

      while(flag == 0) {
        while(counter >= 1){
          scanf("%19s", n1);
          break;
        }
        if(atof(n1) == 0){
          printf("Please enter a non-zero value\n");
          continue;
        }
        for(int i = 0; i < 20; i++){
          if(isalpha(n1[i])){
            i = 100;
          }
          if(i==19){
            flag = 1;
            break;
          }
        }
        if(flag == 0){
          memset(n1, 0, 20);
          printf("Enter a positive value (non-zero)\n");
          while (getchar() != '\n');
        }
        if(n1[0] == '-'){
          printf("Enter a positive value (non-zero)\n");
          flag = 0;
        }
      }
      flag = 0;
      counter = 0;
      scanf("");
        
      num1_a = atof(n1);
        
      result = log10(num1_a);
      // printf("The result is: \t %.2f\n", result);
      a_selection='n';
      check = 1;
    }
    else if(operation == 'E' || operation == 'e') { // exponential
      while(flag == 0) { // this one is more complicated, it gets the user input then determines if it is a number or letter
        if(input == true){
          gcvt(num1, 20, n1);
          if(argument1 != 2){
            printf("Please enter a number\n");
            memset(n1, 0, 20);
            scanf("%19s", n1);
          }
        }
        if(input == false){
          printf("Please enter a number\n");
          scanf("%19s", n1);
        }
        while(counter >= 1){
          scanf("%19s", n1);
        }
        for(int i = 0; i < 20; i++){
          if(isalpha(n1[i])){
            i = 100;
          }
          if(i==19){
            flag = 1;
            break;
          }
        }
        if(flag == 2){
          printf("Please enter a number\n");
          flag = 0;
          continue;
        }
        if(flag == 0){
          memset(n1, 0, 20);
          printf("Please enter a number\n");
          while (getchar() != '\n');
        }
      }
      flag = 0;
      scanf("");

      num1_a = atof(n1);

      result = exp(num1_a);
      // printf("The result is: \t %.2f\n", result);
      a_selection='n';
      check = 1;
    }
    else if(operation == 'C' || operation == 'c') { // ceiling

      if(input == true){
        gcvt(num1, 20, n1);
        if(argument1 != 2){
          printf("Please enter a number\n");
          memset(n1, 0, 20);
          scanf("%19s", n1);
        }
      }
      if(input == false){
        printf("Please enter a number\n");
        scanf("%19s", n1);
      }

      while(flag == 0) { // this one is more complicated, it gets the user input then determines if it is a number or letter
        while(counter >= 1){
          scanf("%19s", n1);
        }
        for(int i = 0; i < 20; i++){
          if(isalpha(n1[i])){
            i = 100;
          }
          if(i==19){
            flag = 1;
            break;
          }
        }
        if(flag == 2){
          printf("Please enter a number\n");
          flag = 0;
          continue;
        }
        if(flag == 0){
          memset(n1, 0, 20);
          printf("Please enter a number\n");
          while (getchar() != '\n');
        }
      }
      flag = 0;
      scanf("");
        
      num1_a = atof(n1);
        
      result = ceil(num1_a);
      // printf("The result is: \t %.2f\n", result);
      a_selection='n';
      check = 1;
    }
    else if(operation == 'F' || operation == 'f') { // floor

      if(input == true){
        gcvt(num1, 20, n1);
        if(argument1 != 2){
          printf("Please enter a number\n");
          memset(n1, 0, 20);
          scanf("%19s", n1);
        }
      }
      if(input == false){
        printf("Please enter a number\n");
        scanf("%19s", n1);
      }

      while(flag == 0) { // this one is more complicated, it gets the user input then determines if it is a number or letter
        while(counter >= 1){
          scanf("%19s", n1);
        }
        for(int i = 0; i < 20; i++){
          if(isalpha(n1[i])){
              i = 100;
          }
          if(i==19){
            flag = 1;
            break;
          }
        }
        if(flag == 2){
          printf("Please enter a number\n");
          flag = 0;
          continue;
        }
        if(flag == 0){
          memset(n1, 0, 20);
          printf("Please enter a number\n");
          while (getchar() != '\n');
        }
      }
      flag = 0;
      scanf("");
        
      num1_a = atof(n1);
      result = floor(num1_a);
      // printf("The result is: \t %.2f\n", result);
      a_selection='n';
      check = 1;
    } else{
      printf("Inavlid input \nPlease enter a valid operator \nPlease enter the operation ( S (for square root) , L (for logarithm) , E (for exponential) , C (for ceil) , F (for floor) ):\n");
      input = false;
      scanf(" %c", &operation);
      while( (ch = getchar()) != '\n' && ch != EOF);
    }
  }
  return result;
}

void selection_V(char variable, float number, char* add_variable, float* add_number){ // function for selection V
  printf("completed V\n");
  int flag = 0;
  // float a = 0, b = 0, c = 0, d = 0, e = 0;
  char n1[20] = {};
  float num1;
  bool check = true;

  while(flag == 0){
      switch(variable) {
        case'A':
        case'a': {
          if(check == true){
            a = number;
            flag = 1;
          } else if(check == false){
            printf("Please enter a value to assign to the variable:");
            scanf("%f", &a);
            flag = 1;
          }
          break;
        } 
        case'B':
        case'b': {
          if(check == true){
            b = number;
            flag = 1;
          } else if(check == false){
            printf("Please enter a value to assign to the variable:");
            scanf("%f", &b);
            flag = 1;
          }
          break;
        } 
        case'C':
        case'c': {
          if(check == true){
            c = number;
            flag = 1;
          } else if(check == false){
            printf("Please enter a value to assign to the variable:");
            scanf("%f", &c);
            flag = 1;
          }
          break;
        } 
        case'D':
        case'd': {
          if(check == true){
            d = number;
            flag = 1;
          } else if(check == false){
            printf("Please enter a value to assign to the variable:");
            scanf("%f", &d);
            flag = 1;
          }
          break;
        } 
        case'E':
        case'e': {
          if(check == true){
            e = number;
            flag = 1;
          } else if(check == false){
            printf("Please enter a value to assign to the variable:");
            scanf("%f", &e);
            flag = 1;
          }
          break;
        }
        default: {
          check = false;
          printf("Invalid Input \nPlease enter the name of the variable (A single character between 'a' to 'e'):\n");
          scanf(" %c", &variable);
          while (getchar() != '\n');
        }
      }
    }
  *add_variable = variable;
  *add_number = number;
}

void selection_A(char a_selection){ // function for selection A
  // printf("completed A\n");
  int counter = 0;
  // float num1 = 0;
  // float num2 = 0;
  int flag = 0;
  char n1[20] = {};
  char n2[20] = {};
  float num1_a;
  float num2_a;
  char operation;
  float result;
  int ch;
  int check = 0;

  // scanf(" %c", &a_selection);

  while(check != 1){
      while( (ch = getchar()) != '\n' && ch != EOF);
      if(a_selection=='B' || a_selection=='b') {
        printf("Please enter the first number or a variable name ('a' to 'e'):\n");
        while(flag == 0) { // this one is more complicated, it gets the user input then determines if it is a number or letter
          scanf("%19s", n1);
          for(int i = 0; i < 20; i++){
            if(isalpha(n1[i])){
              i = 100;
          }
          if(i==19){
            flag = 1;
            break;
          }
          }
          for(int i = 0; i < 20; i++){
            if(isdigit(n1[i])){
              i = 100;
            }
            if(i==19 && strlen(n1)==1){
              switch(n1[0]){
                case'A':
                case'a': {
                  flag = 1;
                  break;
                } 
                case'B':
                case'b': {;
                  flag = 1;
                  break;
                } 
                case'C':
                case'c': {
                  flag = 1;
                  break;
                } 
                case'D':
                case'd': {
                  flag = 1;
                  break;
                } 
                case'E':
                case'e': {
                  flag = 1;
                  break;
                }
                default: {
                  flag = 2; // seperate case, don't need to clear the buffer
                }
              }
            }
          }
          if(flag == 2){
            printf("Please enter the first number or a variable name ('a' to 'e'):\n");
            flag = 0;
            continue;
          }
          if(flag == 0){
            memset(n1, 0, 20);
            printf("Please enter the first number or a variable name ('a' to 'e'):\n");
            while (getchar() != '\n');
          }
        }
        flag = 0; // reset this
        scanf("");
        if (strcmp(n1, "a") == 0) { // these just check to see what is entered and convert to string or use the value from the variable
          num1_a = a;
        } else if (strcmp(n1, "A") == 0) {
          num1_a = a;
        } else if (strcmp(n1, "b") == 0) {
          num1_a = b;
        } else if (strcmp(n1, "B") == 0) {
          num1_a = b;
        } else if (strcmp(n1, "c") == 0) {
          num1_a = c;
        } else if (strcmp(n1, "C") == 0) {
          num1_a = c;
        } else if (strcmp(n1, "d") == 0) {
          num1_a = d;
        } else if (strcmp(n1, "D") == 0) {
          num1_a = d;
        } else if (strcmp(n1, "e") == 0) {
          num1_a = e;
        } else if (strcmp(n1, "E") == 0) {
          num1_a = e;
        } else {
          num1_a = atof(n1);
        }

        printf("Please enter the operation ( + , - , * , / , % , ^ (for power) ):\n");
        scanf(" %c", &operation); // get the operation
        while(flag == 0) { // check operation
          if((atof(n2) == 0 && operation == '/') || (atof(n2) == 0 && operation == '%')){
            memset(n2, 0, 20);
            printf("Please enter a non-zero number\n");
            scanf("%19s", n2);
          }
          if(operation=='+'){
            flag = 1;
            break;
          } else if(operation=='-') {
            flag = 1;
            break;
          } else if(operation=='*') {
            flag = 1;
            break;
          } else if(operation=='/'){
            flag = 1;
            break;
          } else if(operation=='%') {
            flag = 1;
            break;
          } else if(operation=='^'){
            flag = 1;
            break;
          } else {
            puts("Please enter a valid operator");
            while (getchar() != '\n');
            scanf("%c", &operation);
          }
        }
        flag = 0;

        printf("Please enter the second number or a variable name ('a' to 'e'):\n");
        while(flag == 0) { // get the user input then determine if it is a number or letter
          scanf("%19s", n2);
          for(int i = 0; i < 20; i++){
            if(isalpha(n2[i])){
              i = 100;
          }
          if(i==19){
            flag = 1;
            break;
          }
          }
          for(int i = 0; i < 20; i++){
            if(isdigit(n2[i])){
              i = 100;
            }
            if(i==19 && strlen(n2)==1){
              switch(n2[0]){
                case'A':
                case'a': {
                  if(a==0 && operation=='/'){
                    continue;
                  }
                  flag = 1;
                  break;
                } 
                case'B':
                case'b': {;
                  if(b==0 && operation=='/'){
                    continue;
                  }
                  flag = 1;
                  break;
                } 
                case'C':
                case'c': {
                  if(c==0 && operation=='/'){
                    continue;
                  }
                  flag = 1;
                  break;
                } 
                case'D':
                case'd': {
                  if(d==0 && operation=='/'){
                    continue;
                  }
                  flag = 1;
                  break;
                } 
                case'E':
                case'e': {
                  if(e==0 && operation=='/'){
                    continue;
                  }
                  flag = 1;
                  break;
                }
                default: {
                  flag = 2; // seperate case, don't need to clear the buffer
                }
              }
            }
          }
          if(flag == 2){
            printf("Please enter the second number or a variable name ('a' to 'e'):\n");
            flag = 0;
            continue;
          }
          if(flag == 0){
            memset(n2, 0, 20);
            printf("Please enter the second number or a variable name ('a' to 'e'):\n");
            while (getchar() != '\n');
          }
        }
        flag = 0; // reset this
        scanf("");
        if (strcmp(n2, "a") == 0) { // check to see what is entered and convert to string or use the value from the variable
        num2_a = a;
        } else if (strcmp(n2, "A") == 0) {
        num2_a = a;
        } else if (strcmp(n2, "b") == 0) {
          num2_a = b;
        } else if (strcmp(n2, "B") == 0) {
        num2_a = b;
        } else if (strcmp(n2, "c") == 0) {
          num2_a = c;
        } else if (strcmp(n2, "C") == 0) {
        num2_a = c;
        } else if (strcmp(n2, "d") == 0) {
          num2_a = d;
        } else if (strcmp(n2, "D") == 0) {
        num2_a = d;
        } else if (strcmp(n2, "e") == 0) {
          num2_a = e;
        } else if (strcmp(n2, "E") == 0) {
        num2_a = e;
        } else {
          num2_a = atof(n2);
        }
        if(operation=='+'){
          result = num1_a + num2_a;
          memory_start[memory_counter] = result;
          memory_counter++;
          printf("The result is: \t %.2f\n", result);
        }
        else if(operation=='-'){
          result = num1_a - num2_a;
          memory_start[memory_counter] = result;
          memory_counter++;
          printf("The result is: \t %.2f\n", result);
        }
        else if(operation=='*'){
          result = num1_a * num2_a;
          memory_start[memory_counter] = result;
          memory_counter++;
          printf("The result is: \t %.2f\n", result);
        }
        else if(operation=='/'){
          result = num1_a / num2_a;
          memory_start[memory_counter] = result;
          memory_counter++;
          printf("The result is: \t %.2f\n", result);
        }
        else if(operation=='%'){
          result = remainder(num1_a, num2_a);
          memory_start[memory_counter] = result;
          memory_counter++;
          printf("The result is: \t %.2f\n", result);
        }
        else if(operation=='^'){
          result = pow(num1_a, num2_a);
          memory_start[memory_counter] = result;
          memory_counter++;
          printf("The result is: \t %.2f\n", result);
        }
      }
      while(a_selection=='U' || a_selection=='u') { // unary operations with variables
        printf("Please enter the operation ( S (for square root) , L (for logarithm) , E (for exponential) , C (for ceil) , F (for floor) ):\n");
        scanf(" %c", &operation);

      if(operation == 'S' || operation == 's') { // square root
        printf("Enter a positive value or a variable name ('a' to 'e') with a positive value:\n");
        while(flag == 0) {
          scanf("%19s", n1);
          for(int i = 0; i < 20; i++){
            if(isalpha(n1[i])){
              i = 100;
          }
          if(i==19){
            flag = 1;
            break;
          }
          }
          for(int i = 0; i < 20; i++){
            if(isdigit(n1[i])){
              i = 100;
            }
            if(i==19 && strlen(n1)==1){
              switch(n1[0]){
                case'A':
                case'a': {
                  flag = 1;
                  break;
                } 
                case'B':
                case'b': {;
                  flag = 1;
                  break;
                } 
                case'C':
                case'c': {
                  flag = 1;
                  break;
                } 
                case'D':
                case'd': {
                  flag = 1;
                  break;
                } 
                case'E':
                case'e': {
                  flag = 1;
                  break;
                }
                default: {
                  flag = 2; // seperate case, don't need to clear the buffer
                }
              }
            }
          }
          if(flag == 2){
            printf("Enter a positive value or a variable name ('a' to 'e') with a positive value:\n");
            flag = 0;
            continue;
          }
          if(flag == 0){
            memset(n1, 0, 20);
            printf("Enter a positive value or a variable name ('a' to 'e') with a positive value:\n");
            while (getchar() != '\n');
          }
          if(n1[0] == '-'){
            printf("Enter a positive value or a variable name ('a' to 'e') with a positive value:\n");
            flag = 0;
          }
        }
        flag = 0;
        counter = 0;
        scanf("");
        if (strcmp(n1, "a") == 0) {
          num1_a = a;
        } else if (strcmp(n1, "A") == 0) {
          num1_a = a;
        } else if (strcmp(n1, "b") == 0) {
          num1_a = b;
        } else if (strcmp(n1, "B") == 0) {
          num1_a = b;
        } else if (strcmp(n1, "c") == 0) {
          num1_a = c;
        } else if (strcmp(n1, "C") == 0) {
          num1_a = c;
        } else if (strcmp(n1, "d") == 0) {
          num1_a = d;
        } else if (strcmp(n1, "D") == 0) {
          num1_a = d;
        } else if (strcmp(n1, "e") == 0) {
          num1_a = e;
        } else if (strcmp(n1, "E") == 0) {
          num1_a = e;
        } else {
          num1_a = atof(n1);
        }
        result = sqrt(num1_a);
        memory_start[memory_counter] = result;
        memory_counter++;
        printf("The result is: \t %.2f\n", result);
        a_selection='n';
      }
      else if(operation == 'L' || operation == 'l') { // logarithm
        printf("Enter a positive value or a variable name ('a' to 'e') with a positive value (non-zero):\n");
        while(flag == 0) {
          scanf("%19s", n1);
          for(int i = 0; i < 20; i++){
            if(isalpha(n1[i])){
              i = 100;
          }
          if(i==19){
            if(atof(n1)==0){
              printf("Enter a positive value or a variable name ('a' to 'e') with a positive value (non-zero):\n");
              continue;
            }
            flag = 1;
            break;
          }
          }
          for(int i = 0; i < 20; i++){
            if(isdigit(n1[i])){
              i = 100;
            }
            if(i==19 && strlen(n1)==1){
              switch(n1[0]){
                case'A':
                case'a': {
                  flag = 1;
                  break;
                } 
                case'B':
                case'b': {;
                  flag = 1;
                  break;
                } 
                case'C':
                case'c': {
                  flag = 1;
                  break;
                } 
                case'D':
                case'd': {
                  flag = 1;
                  break;
                } 
                case'E':
                case'e': {
                  flag = 1;
                  break;
                }
                default: {
                  flag = 2; // seperate case, don't need to clear the buffer
                }
              }
            }
          }
          if(flag == 2){
            printf("Enter a positive value or a variable name ('a' to 'e') with a positive value (non-zero):\n");
            flag = 0;
            continue;
          }
          if(flag == 0){
            memset(n1, 0, 20);
            printf("Enter a positive value or a variable name ('a' to 'e') with a positive value (non-zero):\n");
            while (getchar() != '\n');
          }
          if(n1[0] == '-'){
            printf("Enter a positive value or a variable name ('a' to 'e') with a positive value (non-zero):\n");
            flag = 0;
          }
        }
        flag = 0;
        counter = 0;
        scanf("");
        if (strcmp(n1, "a") == 0) {
          num1_a = a;
        } else if (strcmp(n1, "A") == 0) {
          num1_a = a;
        } else if (strcmp(n1, "b") == 0) {
          num1_a = b;
        } else if (strcmp(n1, "B") == 0) {
          num1_a = b;
        } else if (strcmp(n1, "c") == 0) {
          num1_a = c;
        } else if (strcmp(n1, "C") == 0) {
          num1_a = c;
        } else if (strcmp(n1, "d") == 0) {
          num1_a = d;
        } else if (strcmp(n1, "D") == 0) {
          num1_a = d;
        } else if (strcmp(n1, "e") == 0) {
          num1_a = e;
        } else if (strcmp(n1, "E") == 0) {
          num1_a = e;
        } else {
          num1_a = atof(n1);
        }
        result = log10(num1_a);
        memory_start[memory_counter] = result;
        memory_counter++;
        printf("The result is: \t %.2f\n", result);
        a_selection='n';
      }
      else if(operation == 'E' || operation == 'e') { // exponential
        printf("Please enter a number or a variable name ('a' to 'e'):\n");
        while(flag == 0) { // this one is more complicated, it gets the user input then determines if it is a number or letter
          scanf("%19s", n1);
          for(int i = 0; i < 20; i++){
            if(isalpha(n1[i])){
              i = 100;
          }
          if(i==19){
            flag = 1;
            break;
          }
          }
          for(int i = 0; i < 20; i++){
            if(isdigit(n1[i])){
              i = 100;
            }
            if(i==19 && strlen(n1)==1){
              switch(n1[0]){
                case'A':
                case'a': {
                  flag = 1;
                  break;
                } 
                case'B':
                case'b': {;
                  flag = 1;
                  break;
                } 
                case'C':
                case'c': {
                  flag = 1;
                  break;
                } 
                case'D':
                case'd': {
                  flag = 1;
                  break;
                } 
                case'E':
                case'e': {
                  flag = 1;
                  break;
                }
                default: {
                  flag = 2; // seperate case, don't need to clear the buffer
                }
              }
            }
          }
          if(flag == 2){
            printf("Please enter a number or a variable name ('a' to 'e'):\n");
            flag = 0;
            continue;
          }
          if(flag == 0){
            memset(n1, 0, 20);
            printf("Please enter a number or a variable name ('a' to 'e'):\n");
            while (getchar() != '\n');
          }
        }
        flag = 0;
        scanf("");
        if (strcmp(n1, "a") == 0) {
        num1_a = a;
        } else if (strcmp(n1, "A") == 0) {
         num1_a = a;
        } else if (strcmp(n1, "b") == 0) {
        num1_a = b;
        } else if (strcmp(n1, "B") == 0) {
        num1_a = b;
        } else if (strcmp(n1, "c") == 0) {
        num1_a = c;
        } else if (strcmp(n1, "C") == 0) {
         num1_a = c;
        } else if (strcmp(n1, "d") == 0) {
         num1_a = d;
        } else if (strcmp(n1, "D") == 0) {
          num1_a = d;
        } else if (strcmp(n1, "e") == 0) {
          num1_a = e;
        } else if (strcmp(n1, "E") == 0) {
          num1_a = e;
        } else {
          num1_a = atof(n1);
        }
        result = exp(num1_a);
        memory_start[memory_counter] = result;
        memory_counter++;
        printf("The result is: \t %.2f\n", result);
        a_selection='n';
      }
      else if(operation == 'C' || operation == 'c') { // ceiling
        printf("Please enter a number or a variable name ('a' to 'e'):\n");
        while(flag == 0) { // this one is more complicated, it gets the user input then determines if it is a number or letter
          scanf("%19s", n1);
          for(int i = 0; i < 20; i++){
            if(isalpha(n1[i])){
              i = 100;
          }
          if(i==19){
            flag = 1;
            break;
          }
          }
          for(int i = 0; i < 20; i++){
            if(isdigit(n1[i])){
              i = 100;
            }
            if(i==19 && strlen(n1)==1){
              switch(n1[0]){
                case'A':
                case'a': {
                  flag = 1;
                  break;
                } 
                case'B':
                case'b': {;
                  flag = 1;
                  break;
                } 
                case'C':
                case'c': {
                  flag = 1;
                  break;
                } 
                case'D':
                case'd': {
                  flag = 1;
                  break;
                } 
                case'E':
                case'e': {
                  flag = 1;
                  break;
                }
                default: {
                  flag = 2; // seperate case, don't need to clear the buffer
                }
              }
            }
          }
          if(flag == 2){
            printf("Please enter a number or a variable name ('a' to 'e'):\n");
            flag = 0;
            continue;
          }
          if(flag == 0){
            memset(n1, 0, 20);
            printf("Please enter a number or a variable name ('a' to 'e'):\n");
            while (getchar() != '\n');
          }
        }
        flag = 0;
        scanf("");
        if (strcmp(n1, "a") == 0) {
          num1_a = a;
        } else if (strcmp(n1, "A") == 0) {
          num1_a = a;
        } else if (strcmp(n1, "b") == 0) {
          num1_a = b;
        } else if (strcmp(n1, "B") == 0) {
          num1_a = b;
        } else if (strcmp(n1, "c") == 0) {
          num1_a = c;
        } else if (strcmp(n1, "C") == 0) {
          num1_a = c;
        } else if (strcmp(n1, "d") == 0) {
          num1_a = d;
        } else if (strcmp(n1, "D") == 0) {
          num1_a = d;
        } else if (strcmp(n1, "e") == 0) {
          num1_a = e;
        } else if (strcmp(n1, "E") == 0) {
          num1_a = e;
        } else {
          num1_a = atof(n1);
        }
        result = ceil(num1_a);
        memory_start[memory_counter] = result;
        memory_counter++;
        printf("The result is: \t %.2f\n", result);
        a_selection='n';
      }
      else if(operation == 'F' || operation == 'f') { // floor
        printf("Please enter a number or a variable name ('a' to 'e'):\n");
        while(flag == 0) { // this one is more complicated, it gets the user input then determines if it is a number or letter
          scanf("%19s", n1);
          for(int i = 0; i < 20; i++){
            if(isalpha(n1[i])){
              i = 100;
          }
          if(i==19){
            flag = 1;
            break;
          }
          }
          for(int i = 0; i < 20; i++){
            if(isdigit(n1[i])){
              i = 100;
            }
            if(i==19 && strlen(n1)==1){
              switch(n1[0]){
                case'A':
                case'a': {
                  flag = 1;
                  break;
                } 
                case'B':
                case'b': {;
                  flag = 1;
                  break;
                } 
                case'C':
                case'c': {
                  flag = 1;
                  break;
                } 
                case'D':
                case'd': {
                  flag = 1;
                  break;
                } 
                case'E':
                case'e': {
                  flag = 1;
                  break;
                }
                default: {
                  flag = 2; // seperate case, don't need to clear the buffer
                }
              }
            }
          }
          if(flag == 2){
            printf("Please enter a number or a variable name ('a' to 'e'):\n");
            flag = 0;
            continue;
          }
          if(flag == 0){
            memset(n1, 0, 20);
            printf("Please enter a number or a variable name ('a' to 'e'):\n");
            while (getchar() != '\n');
          }
        }
        flag = 0;
        scanf("");
        if (strcmp(n1, "a") == 0) {
          num1_a = a;
        } else if (strcmp(n1, "A") == 0) {
          num1_a = a;
        } else if (strcmp(n1, "b") == 0) {
          num1_a = b;
        } else if (strcmp(n1, "B") == 0) {
          num1_a = b;
        } else if (strcmp(n1, "c") == 0) {
          num1_a = c;
        } else if (strcmp(n1, "C") == 0) {
          num1_a = c;
        } else if (strcmp(n1, "d") == 0) {
          num1_a = d;
        } else if (strcmp(n1, "D") == 0) {
          num1_a = d;
        } else if (strcmp(n1, "e") == 0) {
          num1_a = e;
        } else if (strcmp(n1, "E") == 0) {
          num1_a = e;
        } else {
          num1_a = atof(n1);
        }
        result = floor(num1_a);
        memory_start[memory_counter] = result;
        memory_counter++;
        printf("The result is: \t %.2f\n", result);
        a_selection='n';
      } else{
        printf("Inavlid input \nPlease enter a valid operator \nPlease enter the operation ( S (for square root) , L (for logarithm) , E (for exponential) , C (for ceil) , F (for floor) ):\n");
        scanf(" %c", &operation);
        while( (ch = getchar()) != '\n' && ch != EOF);
      }
      }
      if(a_selection=='X' || a_selection=='x') { // exit the advanced and reurn to main menu
        check = 1;
        break;
      }
      printf("Select one of the following items:\n");
      printf("B) - Binary Mathematical Operations, such as addition and subtraction.\n");
      printf("U) - Unary Mathematical Operations, such as square root, and log.\n");
      printf("X) - Exit and back to the main menu\n");
      scanf(" %c", &a_selection); // pick another variable
  }
}

void selection_M(float memory[1000], int amount){ // function for selection M
  int num;
  printf("Enter 0 to get display the entire memory or search for a specific calculation in the memory\n");
  scanf("%d", &num);
  if(num == 0){
    for(int i=0; i < amount; i++){
      printf("[%d] %.2f\n", i+1, memory[i]);
    }
  } else if(memory_counter != 0){
    printf("[%d] %.2f\n", num, memory[num-1]);
  }

  if(memory_counter == 0){
    printf("The memory is empty!\n");
  }
}

void selection_R(float memory[1000]){ // function for selection R
  memory = memset(memory, 0, 1000);
  printf("Cleared Memory\n");
}

int selection_X(int check){ // function for selection X, exit program
  return 1;
}
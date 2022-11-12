#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*** Dana Sobhi Section 1 ***/
#define MAXTOPICS 1000
#define HASize 18

typedef struct HashT{
    char Course[150];
    char CreditHours[5];
    char CourseCode[250];
    char Department[250];
    char topics[MAXTOPICS];
}HashT;
HashT *CoInfo[HASize]; //Hash table to store the data at
HashT *CoInfoD[HASize]; //another one to store duplicated courses.  "  collisions "
int hashOP=0; //counter to count number of nodes used in the table
int dubInopen=0; //counter to count how many collisions in open address.
HashT deleted_dummynode;
//-------------------------------------------- Open addressing --------------------------------------//
int getIndex(char *key, int deteminded_size){ //function to get the index to insert to.
    int d = 0;
    char *a = key; //let a be the string we will count it letters
        while(*a !=NULL){ //separate each letter and count how much it has
             d+= *(a++); // add d in a count of each lette r
        }
    return (d % deteminded_size); //return the number
}
//////////////////////////////////////////////////////////////////////////
void initializeT_opa(){ //function to initializes the table to work at
    for(int n =0; n < HASize ; n++){ //go to each node on the table even empty ones.
        CoInfo[n]=NULL; //make sure each node in co-info is null to prepare it to store info.
    }
}
//////////////////////////////////////////////////////////////////////////
void print_opa(){ //function to print open addressing contents
printf("\n **** Printing the hash Table for Open addressing **** \n");
    for(int i = 0; i < HASize ; i++ ){ //for loop to go to each node.


        if(CoInfo[i] == NULL){ //if there's no content  in this node :
            printf("Block %d is Empty \n",i);
        }else if(CoInfo[i] == &deleted_dummynode){printf("Block %d Deleted\n",i);}
        /*else if(CoInfo[i] == CoInfoD[i]){ //if the index matched with one in duplicated table :
            printf("Block node: %d collision key : %s \t Course code: %s \t Credit Hours : %s \n", i,CoInfo[i]->Course,CoInfo[i]->CourseCode,CoInfoD[i]->CreditHours);
            printf(" Department \t :%s ||  Topics \t : %s \n",CoInfoD[i]->Department, CoInfoD[i]->topics);
        }*/
        else{ //else print the content .
            printf("Block node : %d key : %s \t Course code: %s \t Credit Hours : %s \n", i,CoInfo[i]->Course,CoInfo[i]->CourseCode,CoInfo[i]->CreditHours);
            printf(" Department \t :%s ||  Topics \t : %s \n",CoInfo[i]->Department, CoInfo[i]->topics);
        }

  }
}
//////////////////////////////////////////////////////////////////////////
void insert_opa(char Course[],char CreditHours[],char CourseCode[],char Department[],char topics[]){ //function  to insert the data into hash tables
    int table_index =0; //prepare the index we will use
    int s=0; // integer to check if the index address will duplicate
    s= table_index = getIndex(Course,HASize); //let s match the address index
    if(hashOP == HASize){ //check if the table is full or not.
        printf("Table is full \n");
        return;
    }
    while(CoInfo[table_index]&& CoInfo[table_index] != &deleted_dummynode){ //as soon co info for this address not null or already in duplicated table
        if(strcmp(CoInfo[table_index]->Course,Course)==0){ //check if it has the same address for this code.
        //   printf("The course index %d already exist, Sending it to duplicated hash table\n",table_index);
            HashT *new_itemt = ( HashT*) malloc(sizeof( HashT)); //create a new hash to send it to duplicated table.
            strcpy(new_itemt->Course,Course);
            strcpy(new_itemt->CreditHours,CreditHours);
            strcpy(new_itemt->CourseCode,CourseCode);
            strcpy(new_itemt->Department,Department);
            strcpy(new_itemt->topics,topics);
            CoInfoD[table_index]= new_itemt; //add it to duplicated table

            dubInopen++; //add to the number of collisions
            return; //return
        }
    table_index++; //else  next address .

    if(s == table_index){ //if the address matched the previous address
        return; //return
    }
    if(table_index == HASize){ //if the address matched the hash size then there's no size left.
        table_index =0;
}
} //after getting out of the loop of filled nodes . there empty spots in the table
    HashT *new_item = ( HashT*) malloc(sizeof( HashT)); //create a new hash to send it to  table.
    strcpy(new_item->Course,Course);
    strcpy(new_item->CreditHours,CreditHours);
    strcpy(new_item->CourseCode,CourseCode);
    strcpy(new_item->Department,Department);
    strcpy(new_item->topics,topics);

    CoInfo[table_index]= new_item; //add it to table

    hashOP++; //get the number nodes used .
    return;
}
//////////////////////////////////////////////////////////////////////////
void search_opa(char *key){ //function to search for specific name

int table_index = getIndex(key,HASize); //get index of this key
        if(hashOP == 0)
            {   printf("Empty!\n"); //if the table is empty print its empty
                return;}

    while(CoInfo[table_index]){ //while there's a node for this index
            if(CoInfo[table_index]== NULL){ //as soon the node is empty print :
            printf("Empty!\n");
            return;//return
            }
 else{           if(strcmp(CoInfo[table_index]->Course,key)==0){ //if the key matched  the course of this node .
            printf("Block %d key : %s \t Course code: %s \t Credit Hours : %s \n",table_index ,CoInfo[table_index]->Course,CoInfo[table_index]->CourseCode,CoInfo[table_index]->CreditHours);
            printf(" Department \t :%s ||  Topics \t : %s \n",CoInfo[table_index]->Department, CoInfo[table_index]->topics);
            return ; //print it content and return.
            } else if(CoInfo[table_index] == &deleted_dummynode){printf("Block %d Deleted\n",table_index); return;}
        /*    if(strcmp(CoInfoD[table_index]->Course,key)==0){ //if the key matched  the course of this node in duplicated list  .
            printf("Block %d key : %s \t collision. Course code: %s \t Credit Hours : %s \n",table_index ,CoInfoD[table_index]->Course,CoInfoD[table_index]->CourseCode,CoInfoD[table_index]->CreditHours);
            printf(" Department \t :%s ||  Topics \t : %s \n",CoInfoD[table_index]->Department, CoInfoD[table_index]->topics);
            return ; //print it content and return.
            }*/


 }
        table_index++;
        if(table_index == HASize) //if the index reached hash size.
                table_index = 0; //return in into 0.
        }
        printf("Not found! \n"); //else print not found.

     return; //return;
}
//////////////////////////////////////////////////////////////////////////
void deletion_op(char *key){ //function to delete specific name .
    int table_index = getIndex(key,HASize); //get the index of this key.
    if(table_index == -1) //if the index is -1 then there's no nodes.
            {return;} //return.

    while(CoInfo[table_index]){//while there's a node to delete.
        if(CoInfo[table_index]== NULL) //as soon the node is empty print :
            {   printf("Empty!\n");
                return;}//return
    else
        if((strcmp(CoInfo[table_index]->Course,key)==0)){  //if the key matched this node index
        /*   if(CoInfoD[table_index]!=NULL && (strcmp(CoInfoD[table_index]->Course,key)==0)) //check if there's a duplicated node of this key.
            {CoInfo[table_index] = CoInfoD[table_index]; //replace this node with the one duplicated
            CoInfo[table_index] = NULL;
            CoInfoD[table_index]= &deleted_dummynode;
            dubInopen--; //get rid of one collision
            printf("Replacing with collision and delete it.  \n ");
            return; //return*/
            CoInfo[table_index]= &deleted_dummynode;
            hashOP--;
            //CoInfo[table_index]= NULL;
           // free(CoInfo[table_index]); //else free this node.
            printf("Deleted \n"); //and print deleted.
            return; //return
        }
        else  if(CoInfo[table_index] == &deleted_dummynode){printf("Block %d Deleted\n",table_index); return;}
        table_index++; //get next index table address .
        if(table_index == HASize) //if the table index reached hash size.
        {table_index =0;}

    }
    printf("\n Course:  %s Not in this table.\n",key); //else this key is not in this hash table .
return; //return
}
//////////////////////////////////////////////////////////////////////////
double load_fop(){ //function to get the load factor of this table .
//number of node used to the size of this hash table .
  return (double) hashOP /(double)HASize;
}
//-------------------------------------------- Double Hashing --------------------------------------//
//most of the steps are similar. the only difference will be a cured  in getting the second key .
typedef struct Dhh{
    char Course[250];
    char CreditHours[5];
    char CourseCode[250];
    char Department[250];
    char topics[MAXTOPICS];
}Dhh;
int hashS =0; //counter to count number of nodes used in the table
int primeNumber = 0;
Dhh *info[HASize];//Hash table to store the data at
Dhh *infoDub[HASize];//another one to store duplicated courses.  "  collisions "
int counterDH =0;//counter to count how many collisions in double hashing.
Dhh deleted_dummynodeDH;
/////////////////////////////////////////////////////////////////////
int getp(){ //function to get the prime number that goes near the hash size "highest prime number less than hash size" .
    int d,a,n;  //this function will check from number 2 , as number 2 is only even number in prime numbers
    n = HASize; //let n = hash size
        if((n %2) != 0){ //if the mod n to 2 not 0
            n -= 2; // substituted 2
        }
        else
            n--;

        for(d = n; d >=2 ; d-=2){ //create a loop from n to number  >= 2

            if(d %2 ==0){
                continue;
            }
            for(a = 3 ; a <=(int) sqrt(d);a+= 2){
                if(d % a == 0)
                    break; //if its a prime
            }
            if(a > (int) sqrt(d)){
                return d; //return the number
            }
        }
        //else return 2.
        return 2;
        //it will accrued when n =3;

}
/////////////////////////////////////////////////////////////////////
void initializeT_dbh(){ //function to initializes the table to work at
for(int i = 0; i < HASize; i++)
{
        info[i] = NULL;
        infoDub[i] = NULL;
	}

	primeNumber = getp(); //set the prime number to work with.
}
/////////////////////////////////////////////////////////////////////
int getkeyH1(char *key){ //get the first key of the double hashing
int d = 0;
    char *a = key;
        while(*a !=NULL){ //separate each letter and count how much it has
             d+= *(a++); // add d in a count of each letter
        }
    return (d % HASize); //return the number
}
/////////////////////////////////////////////////////////////////////
int getkeyH2(char *key){ //get the second key for double hashing
int d = 0;
    char *a = key;
        while(*a !=NULL){ //separate each letter and count how much it has
             d+= *(a++); // add d in a count of each letter
        }
return (primeNumber - ( d % primeNumber)); //return the number
}
/////////////////////////////////////////////////////////////////////
void print_dbh(){ //function to print double hashing contents
printf("\n **** Printing the hash Table for Double Hashing **** \n");
    for(int i = 0; i < HASize ; i++ ){
//for loop to go to each node.

        if(info[i] == NULL){ //if there's no content  in this node :
            printf("Block %d is Empty \n",i);
        } else if(info[i] == &deleted_dummynodeDH){printf("Block %d Deleted\n",i);}
       /* else if(info[i] == infoDub[i]){ //if the index matched with one in duplicated table :
            printf("Block %d collision key : %s \t Course code: %s \t Credit Hours : %s \n", i,infoDub[i]->Course,infoDub[i]->CourseCode,infoDub[i]->CreditHours);
            printf(" Department \t :%s ||  Topics \t : %s \n",infoDub[i]->Department, infoDub[i]->topics);
        }*/
        else{//else print the content .
            printf("Block %d key : %s \t Course code: %s \t Credit Hours : %s \n", i,info[i]->Course,info[i]->CourseCode,info[i]->CreditHours);
            printf(" Department \t :%s ||  Topics \t : %s \n",info[i]->Department, info[i]->topics);
    }
  }
}
/////////////////////////////////////////////////////////////////////
void insert_dbh(char Course[],char CreditHours[],char CourseCode[],char Department[],char topics[]){ //function  to insert the data into hash tables
    int h1 = getkeyH1(Course); //get the first key
    int h2 = getkeyH2(Course); //get the second key
    int indx = h1; //first let the index address equal to first key

    if (hashS == HASize){ //if the node number equals to the hash  size then the hash is full.
        printf(" \n Hash table is full. \n");
        return; //return.
    }

    while(info[indx] && info[indx] != &deleted_dummynodeDH){  //as soon co info for this address not null or already in duplicated table
        if(strcmp(info[indx]->Course,Course)==0 ){   //check if it has the same address for this code.
       //     printf(" \n Course %d is duplicated send it to Duplicated table.\n",indx);
        Dhh *new_itemt = ( Dhh*) malloc(sizeof( Dhh)); //create a new hash to send it to duplicated table.
            strcpy(new_itemt->Course,Course);
            strcpy(new_itemt->CreditHours,CreditHours);
            strcpy(new_itemt->CourseCode,CourseCode);
            strcpy(new_itemt->Department,Department);
            strcpy(new_itemt->topics,topics);
            CoInfoD[indx]= new_itemt; //add it to duplicated table
            counterDH++; //add to the number of collisions
            return;
        }
        indx = (indx + h2) % HASize; //get next address .
        if(indx == h1){ //if we reached again to the first address . Error accrues
            return;}

    }
 //after getting out of the loop of filled nodes . there empty spots in the table

    Dhh *new_Field = (Dhh*)malloc(sizeof(Dhh)); //create a new hash to send it to  table.
    strcpy(new_Field->Course,Course);
    strcpy(new_Field->CreditHours,CreditHours);
    strcpy(new_Field->CourseCode,CourseCode);
    strcpy(new_Field->Department,Department);
    strcpy(new_Field->topics,topics);

        info[indx] = new_Field; //add it to table
        hashS++; //get the number nodes used .
return;
}
/////////////////////////////////////////////////////////////////////
void search_dbh(char *key){ //function to search for specific name
    int h1 = getkeyH1(key);//get the first key
    int h2 = getkeyH2(key);//get the second key
    int indx = h1; //set the index to the first key.

    if(hashS ==0){ //make sure the  table is not empty.
        printf("Empty Table.\n");
        return;
    }

    while(info[indx]){ //while there's a node to search for :
        if(info[indx]== NULL) //if the node is  empty :
            {   printf("Empty!\n");
                return;}

    else{ if(strcmp(info[indx]->Course,key)==0){  //if the key matched  the course of this node .
            printf("Block %d key : %s \t Course code: %s \t Credit Hours : %s \n",indx ,info[indx]->Course,info[indx]->CourseCode,info[indx]->CreditHours);
            printf(" Department \t :%s ||  Topics \t : %s \n",info[indx]->Department, info[indx]->topics);
            return ;

            } else if(info[indx] == &deleted_dummynodeDH){printf("Block %d Deleted\n",indx); return;}
          /*  if(strcmp(infoDub[indx]->Course,key)==0){ //if the key matched  the course of this node in duplicated list
            printf("Block %d key : %s \t collision. Course code: %s \t Credit Hours : %s \n",indx ,infoDub[indx]->Course,infoDub[indx]->CourseCode,infoDub[indx]->CreditHours);
            printf(" Department \t :%s ||  Topics \t : %s \n",infoDub[indx]->Department, infoDub[indx]->topics);
            return ;
            }*/

        }
        indx = (indx + h2) % HASize; //get next address
        if(indx == h1){ //if the address matched the first key
            break; //break.
            }
    }
    printf("Not found! \n"); //the key not found print :
    return;

}
/////////////////////////////////////////////////////////////////////
void deletion_dh(char *key){ //function to delete specific name .
    int h1 = getkeyH1(key); //get first key
    int h2 = getkeyH2(key);//get second key
    int indx = h1; //set index address as first key.

    if(hashS ==0){ //check if the table is empty:
        printf("Empty Table\n");
        return;
    }

    while(info[indx]){
        if(strcmp(info[indx]->Course,key)==0){  //if the key matched this node index
         /*  if(infoDub[indx]!= NULL &&(strcmp(infoDub[indx]->Course,key)==0) ){  //check if there's a duplicated node of this key.
            info[indx] = infoDub[indx]; //replace this node with the one duplicated
            infoDub[indx] =NULL;
           // free(infoDub[indx]); //free the duplicated node
            infoDub[indx]= &deleted_dummynodeDH;
            counterDH--; //get rid of one collision
            printf("Replacing with collision and delete it. \n ");
            return;
           }else*/ info[indx] = &deleted_dummynodeDH; hashS--;
         //  info[indx]= NULL;
         //  free(info[indx]); //else free this node.
            printf("Deleted \n");  //and print deleted.
            return;
        }
      else  if(info[indx] == &deleted_dummynodeDH){printf("Block %d Deleted\n",indx); return;}
        indx = (indx + h2) % HASize; //get next index table address .
        if(indx == h1){  //if the address matched the first key
            break;}
    }
 //the key not found print :
    printf("\n Course:  %s Not in this table.\n",key);
    return;
}
/////////////////////////////////////////////////////////////////////
double load_fdh(){ //function to get the load factor of this table .
//number of node used to the size of this hash table .
  return (double)hashS/(double)HASize;
}

//-------------------------------------------- General Function -------------------------------------//
void readFileGen(){ //read the file. same as AVL tree one.
    char string[1000]; // String we will store what we will scan from the file in.
    FILE* b = fopen("offered_courses.txt","r"); // select the file to open, and scan it later
    if(b == NULL) // if the file does't exist print
        printf("File is empty!\n");
    else  //the file exist, then:
        while(fgets(string, sizeof(string), b) != NULL){ //while the end of the file is not reached . " the lines are not null'
    char * Course = strtok(string, ":");
    char * CreditHours = strtok(NULL, "#");
    char * CourseCode = strtok(NULL, "#");
    char * Department = strtok(NULL, "/");
    char * Topic = strtok(NULL, "/");
/*
for(int i =0; i< sizeof(string);i++){
    char * temp6 = strtok(NULL, ",");
if(temp6 == NULL)
    break;
}*/
// I Wanted to separate each subject , yet thinking about it it would be easier not to, and instead use it as one string.
insert_opa(Course,CreditHours,CourseCode,Department,Topic); //insert into the open address table
insert_dbh(Course,CreditHours,CourseCode,Department,Topic); //insert into the double hashing table .
        }//until the end of the file .

    printf("The Input file has been read\n"); // print when this function read without problems
    fclose(b); // close the file we opened before
return;

}
//////////////////////////////////////////////////////////////////////////
FILE *DBHprintFile; //construct a file to save at
void print_dbhFile(){  //same as print table of double addressing but instead adding fprintf for the file.
fprintf(DBHprintFile," **** Printing the hash Table for Double Hashing **** \n");
    for(int i = 0; i < HASize ; i++ ){


        if(info[i] == NULL){
            fprintf(DBHprintFile,"Block %d is Empty \n",i);
        }
        else{ /**if(info[i] == infoDub[i]){**/ if(info[i] == &deleted_dummynodeDH){fprintf(DBHprintFile,"Block %d Deleted\n",i);}
           /* fprintf(DBHprintFile,"Block %d collision key : %s \t Course code: %s \t Credit Hours : %s \n", i,infoDub[i]->Course,infoDub[i]->CourseCode,infoDub[i]->CreditHours);
            fprintf(DBHprintFile," Department \t :%s ||  Topics \t : %s \n",infoDub[i]->Department, infoDub[i]->topics);*/

        else{
            fprintf(DBHprintFile,"Block %d key : %s \t Course code: %s \t Credit Hours : %s \n", i,info[i]->Course,info[i]->CourseCode,info[i]->CreditHours);
            fprintf(DBHprintFile," Department \t :%s ||  Topics \t : %s \n",info[i]->Department, info[i]->topics);
    }
  }}
}
//////////////////////////////////////////////////////////////////////////
void HashTablePrint(){
printf("*****************************************************************\n");
printf("1---------------------- Print Hashed Table----------------------1\n");
printf("2- |            Print Table Size and load factor             | -2\n");
printf("3- |                Print used hashed function               | -3\n");
printf("4- |                    Insert a new record                  | -4\n");
printf("5- | Search a specific word and choose which table to search | -5\n");
printf("6- |                  Delete a selected record               | -6\n");
printf("7- |            Compare Two tables in collisions.            | -7\n");
printf("8- |                    Save into a file                     | -8\n");
printf("9---------------------------- Exit -----------------------------9\n");
printf("*****************************************************************\n");
}
//////////////////////////////////////////////////////////////////////////
//--------------------------------------------  Main Function ---------------------------------------//

int main()
{//first we  initializes tables to work with them.
 initializeT_opa();
 initializeT_dbh();
 int option=0; // settle up an option
 readFileGen(); //read the file to store data :

do{ //do while the option is not 9 :
HashTablePrint(); //print the list
printf("Choose from the table.\n"); //choose from it
scanf("\n%d",&option); //scan the number selected
switch(option){ //switch statement to see the option
case 1 : // Print Hashed Table
printf("Option 1\n");
    print_opa(); //print open address first
    print_dbh(); //then print double hashing .
    break;
case 2: //Print Table Size and load factor
printf("Option 2\n");

    printf("Hash Table size : %d \n",HASize);
    printf("Load Factor for table 1 - Open addressing : %f\n",load_fop());
    printf("Load Factor for table 2 - Double hashing  : %f\n",load_fdh());
    break;
case 3: //Print used hashed function
printf("Option 3\n");
    printf("For Table 1: Get they string key, separate each letter until its not null ,\n");
        printf("count their ASCII code then mod to the size of the hash table \n");
    printf("hi(key) = [h(key) + i] % tableSize \n");
printf("---------------------------------------------------------------------------\n");

    printf("For table 2 key 1: Get they string key, separate each letter until its not null,\n");
           printf ("count their ASCII code then mod to the size of the table \n");
    printf("D mod Table size \n");
printf("---------------------------------------------------------------------------\n");
    printf("For table 2 key 2: Get they string key, separate each letter until its not null ,\n");
        printf("count their ASCII code get the highest prime number lower than size then mod it to it , then substituted it to the prime number\n");
    printf("prime number - (D mod prime number)\n");
    printf("hi(key1) = [h(key1) + i*hp(key2)]% tableSize\n");
    break;

case 4: //Insert a new record
printf("Option 4\n");
printf("Insert New course: \n");
    char Courses[250];
    char CHs[5];
    char CCode[250];
    char Dpt[250];
    char tpcs[MAXTOPICS];
printf("Enter Course name:");
    scanf("\n %[^\n]s",Courses); //read the course name [^\n] is to read until end of line.
printf("Enter Course hours:");
    scanf("\n %[^\n]s",CHs); //credit hours [^\n] is to read until end of line.
printf("Enter Course Code:");
    scanf("\n %[^\n]s",CCode); //course code [^\n] is to read until end of line.
printf("Enter Course Department:");
    scanf("\n %[^\n]s",Dpt); //department [^\n] is to read until end of line.
printf("Enter Course topics:");
    scanf("\n %[^\n]s",tpcs); //topics of the course [^\n] is to read until end of line.

insert_dbh(Courses,CHs,CCode,Dpt,tpcs); //insert it into double hashing table
insert_opa(Courses,CHs,CCode,Dpt,tpcs); //insert it into open addressing one
printf("Inserted ! \n");
    break;
case 5: //Search a specific word and choose which table to search
printf("Option 5\n");
int x =0;
    printf("Choose a table to search from: 1- Open address 2- Double hashing \n");
    scanf("\n %d",&x);
    if(x==1){ //if chooses one
printf("Enter Course name:");
    scanf("\n %[^\n]s",Courses);
        search_opa(Courses); //use Open addressing search
    }
    if(x==2){ //use Double hashing searh
printf("Enter Course name:");
    scanf("\n %[^\n]s",Courses);
        search_dbh(Courses);
    }
//else
  //  printf("None\n"); //else none of them.
    break;
case 6: //Delete a selected record
printf("Option 6\n");
printf("Enter Course name To delete:");
    scanf("\n %[^\n]s",Courses);
 deletion_op(Courses); //delete it from open addressing
 deletion_dh(Courses); //delete it from double hashing
    break;
case 7: //Compare Two tables in collisions.
printf("Option 7\n");
printf("collisions In open addressing : %d\n",dubInopen);
printf("collisions In double hashing  : %d\n",counterDH);
printf("Deference: %d \n",dubInopen-counterDH); //get the deference between both tables in .collisions
    break;
case 8:  //Save into a file
printf("Option 8\n");
 DBHprintFile=  fopen("saved_courses.txt","w"); //open the file to write on it.
    print_dbhFile(); //print into the file
    fclose(DBHprintFile); //close the file
    printf("Saved \n"); //print if printing successful
    break;
}
if(option == 9) //exit.
    break;
}while (option != 9);

}

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void print(char** arr, int row, int col);
bool checkrow(char** array, int row, int col, char ch);
bool checkcol(char** array, int row, int col, char ch);
bool checksub(char** array, int row, int col, char ch);
bool find(char** array, int row, int col, bool last);
char** allocate_matrix(int rows, int cols);
void frees(char** arr);
void final_check(char** arr);
bool rcheck(char**arr);
bool ispossible(char**arr);



void print(char** arr, int row, int col){
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			printf("%c\t", arr[i][j]);	
		}
	printf("\n");
	}
	
}

bool checkrow(char** array, int row, int col, char ch){
    for(int i=0; i<16; i++){
      if(array[row][i] == ch){
          return false;
      }
    }
    return true;
}

bool checkcol(char** array, int row, int col, char ch){
    for(int i=0; i<16; i++){
      if(array[i][col] == ch){
          return false;
      }
    }
    return true;
}


bool checksub(char** array, int row, int col, char ch){
    
    int row_start = row/4;
    row_start = row_start*4;
    
    int col_start = col/4;
    col_start = col_start*4;
    
    for(int i=row_start; i<row_start+4; i++){
        for(int j=col_start; j<col_start+4; j++){
            if (array[i][j]== ch){
                return false;
            }
        }
    }
    return true;
}


bool find(char** array, int row, int col, bool last_chance){
   	char ch = '0';
	int counter=0;
for(int i=0; i<16; i++){
    
    if(checkrow(array,row,col, ch) && checkcol(array,row,col, ch) && checksub(array,row,col,ch)){
        array[row][col]=ch;
	counter++;
	
    }
        if(ch == '9'){
            ch = 'A';
        }
        else{
             ch ++;
        }
    
    }
	if(counter == 0){						
		printf("no-solution\n");
		exit(0);
	}
	else if(counter > 1 && last_chance == true){
	printf("no-solution\n");
	exit(0);
	}
	else if(counter > 1 && last_chance == false){
	array[row][col] = '-';
	return false;
	}
		return true;
	

}

char** allocate_matrix(int rows, int cols){
  
  char** ret_val = malloc(rows * sizeof(int*));
  for(int i = 0; i< rows; i++){
    ret_val[i] = malloc(cols * sizeof(int));
  }
  return ret_val;
}

void frees(char** arr){

	for(int i=0; i<16; i++){
			free(arr[i]);
		
	}
}


bool ispossible(char**arr){

	for(int i=0; i<16; i++){
    		for(int j=0; j<16; j++){
			if(arr[i][j] != '-'){
				char temp = arr[i][j];
				arr[i][j] = '-';
				if(checkrow(arr,i,j, temp)==false || checkcol(arr,i,j, temp)==false  || checksub(arr,i,j,temp)==false ){					
					//printf("%c  %d   %d\n",temp, i, j);					
					arr[i][j] = temp;
					return false;
				}
				arr[i][j] = temp;
			}
		}
	}	
	return true;
}


bool rcheck(char**arr){
  
for(int i=0; i<16; i++){
    for(int j=0; j<16; j++){
		char ch='0';
        for(int z=0; z<16; z++){
            if(arr[i][j] != '-'){
                break;
            }
              if(checkrow(arr,i,j, ch) && checkcol(arr,i,j, ch) && checksub(arr,i,j,ch)){
                arr[i][j]=ch;
		bool zz = rcheck(arr);
		if(zz == false){
			arr[i][j]='-';
	
			//printf(" %d\t%d---%c\n", i,j,ch);
		}
              }
		
                if(ch == '9'){
                           ch = 'A';
                             }
                 else{
                        ch ++;
                     }
	
    }
		//printf("%c ", arr[i][j]);
		if(arr[i][j] == '-'){
			return false;
		}
	//printf(".\n");
        }
    }
    
    return true;
    
}
    


void final_check(char** arr){
int check=0;
	for(int i=0; i<16; i++){
		for(int j=0; j<16; j++){
			check = check+ arr[i][j];
		}
	if(check != 930){
		printf("no-solution\n");
		exit(0);
	}
	check=0;		
	}
	
	for(int i=0; i<16; i++){
		for(int j=0; j<16; j++){
			check = check+ arr[j][i];
		}
	if(check != 930){
		printf("no-solution\n");
		exit(0);
	}
	check=0;		
	}
	
}

int main(int argc, char** argv){
    if(argc < 2){ 
	printf("ERROR\n");
	exit(0);
	}
	FILE* fp = fopen(argv[1],"r");
	if(fp == NULL){ 
	printf("0");
	 exit(0);
	}
	
	char** array = allocate_matrix(16,16);
	
	
	for(int i=0; i<16; i++){
		for(int j=0; j<16; j++){
			char num;
			fscanf( fp, "%c\t", &num);
			array[i][j] = num;	
		}
	}
	fclose(fp);
		  
		if( ispossible(array)){
			rcheck(array);
			final_check(array);
			print(array,16,16);
			frees(array);
			free(array);
		}
	else{
		frees(array);
		free(array);
		printf("no-solution\n");
	}
	
return 0;
}


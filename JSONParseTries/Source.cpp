// MAX 10 objects

#include "Header.h"
#include "TriesHeader.h"
int object_no = -1;
struct object objects[10];
FILE* getType(char *value, FILE *fp){

	char curr;
	char buffer[128];
	int b_ptr = 0;
	while (!feof(fp)){
		curr = fgetc(fp);
		if (curr == 34){
			curr = fgetc(fp);
			while (curr != 34){
				buffer[b_ptr] = curr;
				curr = fgetc(fp);
				b_ptr++;
			}
			buffer[b_ptr] = 0;
			break;
		}
	}
	b_ptr = 0;
	if (_strcmpi(buffer, "type") == 0){

		while (!feof(fp)){
			curr = fgetc(fp);
			if (curr == 34){
				curr = fgetc(fp);
				while (curr != 34){
					buffer[b_ptr] = curr;
					curr = fgetc(fp);
					b_ptr++;
				}
				buffer[b_ptr] = 0;
				break;
			}
		}

		strcpy(value, buffer);
		return fp;
	}
	else{
		printf("wrong syntax");
	}
}
FILE * getValue(FILE *fp, char *value){

	char curr;
	char buffer[128];
	int b_ptr = 0;

	while (!feof(fp)){
		curr = fgetc(fp);
		if (curr == 34){
			curr = fgetc(fp);
			while (curr != 34){
				buffer[b_ptr] = curr;
				curr = fgetc(fp);
				b_ptr++;
			}
			buffer[b_ptr] = 0;
			break;
		}
	}
	b_ptr = 0;
	if (_strcmpi(buffer, "number") == 0){

		while (!feof(fp)){
			curr = fgetc(fp);
			if (curr == 34){
				curr = fgetc(fp);
				while (curr != 34){
					buffer[b_ptr] = curr;
					curr = fgetc(fp);
					b_ptr++;
				}
				buffer[b_ptr] = 0;
				break;
			}
		}
	}
	strcpy(value, buffer);
	return fp;
}
FILE* StoreValues(char *buffer, FILE *fp){
	
	char curr;
	char value[128];
	int v_ptr = 0;
	if (_strcmpi(buffer, "firstname") == 0){
			
		while (!feof(fp)){
			curr = fgetc(fp);
			if (curr == 34){
				curr = fgetc(fp);
				while (curr != 34){
					value[v_ptr] = curr;
					curr = fgetc(fp);
					v_ptr++;
				}
				value[v_ptr] = 0;
				break;
			}
		}
		
		strcpy(objects[object_no + 1].firstname, value);
	}
	else if (_strcmpi(buffer, "lastname") == 0){

		while (!feof(fp)){
			curr = fgetc(fp);
			if (curr == 34){
				curr = fgetc(fp);
				while (curr != 34){
					value[v_ptr] = curr;
					curr = fgetc(fp);
					v_ptr++;
				}
				value[v_ptr] = 0;
				break;
			}
		}

		strcpy(objects[object_no + 1].lastname, value);
	}
	else if (_strcmpi(buffer, "height") == 0){
		
		while (!feof(fp)){
			curr = fgetc(fp);
			if (isdigit(curr)){
				while (isdigit(curr) || curr == '.'){
					value[v_ptr] = curr;
					curr = fgetc(fp);
					v_ptr++;
				}
				value[v_ptr] = 0;
				break;
			}
		}

		objects[object_no + 1].height = atof(value);
	}
	else if (_strcmpi(buffer, "age") == 0){


		while (!feof(fp)){
			curr = fgetc(fp);
			if (isdigit(curr)){
				while (isdigit(curr)){
					value[v_ptr] = curr;
					curr = fgetc(fp);
					v_ptr++;
				}
				value[v_ptr] = 0;
				break;
			}
		}

		objects[object_no + 1].age = atoi(value);
	}
	else if (_strcmpi(buffer, "phonenumbers") == 0){

		char type[20];
		char value[50];
		for (int i = 0; i < 2; i++){
			fp = getType(type, fp);
			if (_strcmpi(type, "home") == 0){
				fp = getValue(fp, value);
				strcpy(objects[object_no + 1].ph1, value);
			}
			else if (_strcmpi(type, "fax") == 0){
				fp = getValue(fp, value);
				strcpy(objects[object_no + 1].ph2, value);
			}
		}
	}

	return fp;
}
void ParseJSON(){

	// parse the json and save in the DS
	std::stack<char> stack;
	FILE *fp;
	fp = fopen("json.txt", "r");
	char curr;
	char buffer[128];
	int b_ptr = 0;
	while (!feof(fp))
	{
		curr = fgetc(fp);
		if (curr == '{'){
			stack.push(curr);
		}
		else if (curr == '}') {
			if (stack.size() > 0)
				stack.pop();
			else continue;
			// check to increment object_no
			if (!stack.size()){
				// if stack is empty increment the no
				object_no += 1;
			}
		}
		// check for /"
		else if (curr == 34){
			curr = fgetc(fp);
			while (curr != 34){
				buffer[b_ptr] = curr;
				curr = fgetc(fp);
				b_ptr++;
			}
			buffer[b_ptr] = 0;
			
			// get the value
			fp = StoreValues(buffer, fp);
			b_ptr = 0;
		}

	}


	fclose(fp);
}
void GetPhoneNumbers(){

	char f_name[20];
	char l_name[20];

	printf("enter firstname: ");
	scanf("%s", f_name);

	printf("\nenter lastname: ");
	scanf("%s", l_name);
	int i;
	for (i = 0; i < object_no + 1; i++){
		if (_strcmpi(objects[i].firstname, f_name) == 0 &&
			_strcmpi(objects[i].lastname, l_name) == 0){

			printf("home: %s\n", objects[i].ph1);
			printf("fax: %s", objects[i].ph2);
			
			break;
		}
	}
	if (i == object_no + 1)
		printf("undefined");
	
}
void GetAvgHeight(){

	float total = 0;
	for (int i = 0; i < object_no + 1; i++)
		total += objects[i].height;
	total = total / (object_no + 1);
	printf("Average height is %f", total);
}

void GetAvgAge(){

	float total = 0;
	for (int i = 0; i < object_no + 1; i++)
		total += objects[i].age;

	printf("Average height is %f", total / (object_no + 1));
}
void main(){

	ParseJSON();
	printf("parsing done!\n");

	printf("1. Enter firstname and lastname , returns phonenumbers\n");
	printf("2. Get average height\n");
	printf("3. Get average age\n");

	int selected = -1;
	printf("select: ");
	scanf("%d", &selected);
	switch (selected)
	{
	case 1:
		GetPhoneNumbers();
		break;
	case 2:
		GetAvgHeight();
		break;
	case 3:
		GetAvgAge();
		break;
	default:
		printf("select correct option");
		break;
	}
	_getch();
}
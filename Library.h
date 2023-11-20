#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

typedef struct Student {
	int code;
	char* name;
	float* subject;
}SV;

typedef SV typeinfo;
struct node {
	typeinfo info;
	node* prev, * next;
};

typedef node* nodeptr;

void print_Header_Output();
void init(nodeptr& list);
bool isEmpty(nodeptr list);
void delete_All_List_Student(nodeptr& list);
void add_Last(nodeptr& list, typeinfo data);
void input_Info_Student(SV& sv);
int find_Student_Code_Index(nodeptr list, int code);
void delete_Student_Code(nodeptr& list, int code);
nodeptr search_Student_Code(nodeptr list, int code);
void update_Info_Student(nodeptr& list, int code);
void sort_By_Average_Subject_Score(nodeptr& list);
void split_Duplicate_Code(nodeptr& list, nodeptr& duplicate_List);
void delete_Duplicate_Code(nodeptr& list);
void input_2_List(nodeptr& list1, nodeptr& list2);
nodeptr join_2_list(nodeptr& list1, nodeptr& list2);
void sort_By_Math(nodeptr& list);
SV binary_Search_Student_Math_Score(nodeptr list, int mathScore, bool& found);
bool check_Ascending_By_Math(nodeptr list);
bool check_Ascending_By_English(nodeptr list);
bool check_Ascending_By_Cpp(nodeptr list);
bool check_Ascending_By_Average_Score(nodeptr list);
bool check_Descending_By_Math(nodeptr list);
bool check_Descending_By_English(nodeptr list);
bool check_Descending_By_Cpp(nodeptr list);
bool check_Descending_By_Average_Score(nodeptr list);
bool check_HalfList(nodeptr list);
void find_CoupleStudentScore_LowerFive(nodeptr list);
void input_Info_Student_ktCode_trung(nodeptr& list);
void split_SV_XL_gioi(nodeptr& list, nodeptr& listbeta);
void split_SV_3Mon_Totnhat(nodeptr& list, nodeptr& list3mon);
nodeptr find_SV_xuatsacnhat(nodeptr list);

void output_Student(SV data);
void output_List_Student(nodeptr list);


void menu(nodeptr& list);
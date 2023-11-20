#include "Library.h"

void print_Header_Output() {
	cout << setw(30) << left
		<< "Name";
	cout << setw(12) << left
		<< "| Code";
	cout << setw(10) << left
		<< "| Math";
	cout << setw(10) << left
		<< "| English";
	cout << setw(10) << left
		<< "| C++";
	cout << setw(20) << left
		<< "| Average score" << endl;
}

bool isEmpty(nodeptr list) {
	return list == NULL;
}

float Average_Subject_Score(SV sv) {
	return (sv.subject[0] + sv.subject[1] + sv.subject[2]) / 3;
}

int length(nodeptr list) {
	int count = 0;
	while (list) {
		count++;
		list = list->next;
	}
	return count;
}

nodeptr nodeIndex(nodeptr list, int idx) {
	int count = 0;
	nodeptr p = list;
	while (p != NULL) {
		if (count == idx) return p;
		count++;
		p = p->next;
	}
	return NULL;
}

nodeptr makeNode(typeinfo info) {
	nodeptr p = new node();
	if (p == NULL) return NULL;
	p->info = info;
	p->next = p->prev = NULL;
	return p;
}

void output_Student(SV info) {
	cout << setw(30) << left
		<< info.name << "| ";
	cout << setw(10) << left
		<< info.code << "| ";
	cout << setw(8) << left
		<< info.subject[0] << "| ";
	cout << setw(8) << left
		<< info.subject[1] << "| ";
	cout << setw(8) << left
		<< info.subject[2] << "| ";
	cout << setw(8) << left
		<< Average_Subject_Score(info)
		<< endl;
}

//1. Tạo danh sách sinh viên rỗng.
void init(nodeptr& list) {
	list = NULL;
}

//2. Xóa danh sách sinh viên.
void delete_All_List_Student(nodeptr& list) {
	free(list);
}

//3. Thêm một sinh viên vào danh sách. Không có kiểm tra code trùng.
void add_Last(nodeptr& list, typeinfo info) {
	nodeptr r, p = makeNode(info);
	if (isEmpty(list))
		list = p;
	else {
		for (r = list; r->next != NULL; r = r->next);
		r->next = p;
		p->prev = r;
	}
}

void input_Info_Student(SV& sv) {
	cout << "\nNhap code: ";
	cin >> sv.code;

	cin.ignore();
	cout << "Nhap name: ";
	sv.name = new char[30];
	cin.getline(sv.name, 30);

	sv.subject = new float[3];
	cout << "Nhap Math: ";
	cin >> sv.subject[0];
	cout << "Nhap English: ";
	cin >> sv.subject[1];
	cout << "Nhap C++: ";
	cin >> sv.subject[2];
}

//4. Xóa một sinh viên ra khỏi danh sách
int find_Student_Code_Index(nodeptr list, int code) {
	int idx = 0;
	while (list) {
		if (list->info.code == code)
			return idx;
		idx++;
		list = list->next;
	}
	return -1;
}

void delete_First(nodeptr& list) {
	if (isEmpty(list))
		return;
	nodeptr p = list;
	list = list->next;
	free(p);
	if (list != NULL) list->prev = NULL;
}

void delete_End(nodeptr& list) {
	if (isEmpty(list))
		return;

	nodeptr tail = nodeIndex(list, length(list) - 1);
	nodeptr temp = tail;
	tail = tail->prev;
	tail->next = NULL;
	free(temp);
}

void delete_Mid(nodeptr& list, int idx) {
	nodeptr r;
	int count;
	for (r = list, count = 0; count < idx - 1; count++, r = r->next);
	nodeptr p = r->next;
	r->next = p->next;
	p->next->prev = r;
	free(p);
}

void delete_Student_Code(nodeptr& list, int code) {
	nodeptr curr = list;
	int idx = find_Student_Code_Index(list, code);
	if (idx == -1)
		return;

	if (idx == 0)
		delete_First(list);

	else if (idx == length(list))
		delete_End(list);

	else
		delete_Mid(list, idx);
}

//5. Tìm kiếm một sinh viên có trong danh sách
nodeptr search_Student_Code(nodeptr list, int code) {
	nodeptr p = list;
	if (isEmpty(list))
		return NULL;

	while (p != NULL) {
		if (p->info.code == code) return p;
		p = p->next;
	}
	return NULL;
}

//6. Cập nhật thông tin một sinh viên có trong danh sách.
void update_Info_Student(nodeptr& list, int code) {
	if (isEmpty(list)) {
		cout << "Danh sach rong";
		return;
	}
	nodeptr p = list;
	while (p != NULL) {
		if (p->info.code == code) {
			cout << "Nhap thong tin moi.";
			input_Info_Student(p->info);
		}
		p = p->next;
	}
}

//7. Sắp xếp danh sách tăng dần theo điểm trung bình 3 môn học.
void sort_By_Average_Subject_Score(nodeptr& list) {

	if (list == nullptr) {
		cout << "Danh sach rong.\n";
		return;
	}
	//duyệt từ đầu mảng đến cuối mảng
	for (nodeptr listTemp = list; listTemp->next != NULL; listTemp = listTemp->next) {
		nodeptr min = listTemp;
		//duyệt từ phẩn tử tiếp theo của listTemp đến cuối mảng
		for (nodeptr listTemp_Next = listTemp->next; listTemp_Next != NULL; listTemp_Next = listTemp_Next->next)
			if (Average_Subject_Score(listTemp->info) > Average_Subject_Score(listTemp_Next->info))
				min = listTemp_Next;
		//Swap
		SV temp = min->info;
		min->info = listTemp->info;
		listTemp->info = temp;
	}
}

//8. Tách tất cả sinh viên có mã code trùng có trong danh sách.

void deleteNode(nodeptr& head, nodeptr nodeToDelete) {
	if (nodeToDelete == nullptr) {
		cout << "Node to delete is null.\n";
		return;
	}

	// Nếu nodeToDelete không phải là node đầu tiên
	if (nodeToDelete->prev != nullptr) {
		nodeToDelete->prev->next = nodeToDelete->next;
	}

	// Nếu nodeToDelete không phải là node cuối cùng
	if (nodeToDelete->next != nullptr) {
		nodeToDelete->next->prev = nodeToDelete->prev;
	}

	// Nếu nodeToDelete là node đầu tiên, cập nhật head
	if (head == nodeToDelete) {
		head = nodeToDelete->next;
	}

	delete nodeToDelete;
}

void split_Duplicate_Code(nodeptr& list, nodeptr& duplicate_List) {

	if (list == nullptr) {
		cout << "Danh sach rong.\n";
		return;
	}

	//Duyệt từng phân tử của danh sách
	nodeptr node_Check = list;
	for (nodeptr node_Check = list; node_Check != NULL; node_Check = node_Check->next) {
		int count = 0;
		for (nodeptr curr = node_Check->next; curr != NULL; curr = curr->next) {
			if (node_Check->info.code == curr->info.code) {
				add_Last(duplicate_List, curr->info);
				deleteNode(list, curr);
				count++;
				curr = node_Check->next;
			}
		}
		if (count > 0) {
			add_Last(duplicate_List, node_Check->info);
			deleteNode(list, node_Check);
			node_Check = list;
		}
	}
}

// 9. Xóa tất cả các sinh viên có mã code trùng nhau
void delete_Duplicate_Code(nodeptr& list) {

	if (list == nullptr) {
		cout << "Danh sach rong.\n";
		return;
	}

	//Duyệt từng phân tử của danh sách
	nodeptr node_Check = list;
	for (nodeptr node_Check = list; node_Check != NULL; node_Check = node_Check->next) {
		int count = 0;
		for (nodeptr curr = node_Check->next; curr != NULL; curr = curr->next) {
			if (node_Check->info.code == curr->info.code) {
				deleteNode(list, curr);
				count++;
				curr = node_Check->next;
			}
		}
		if (count > 0) {
			deleteNode(list, node_Check);
			node_Check = list;
		}
	}
}

//10. Nhập 2 danh sách sinh viên của 2 lớp khác nhau và trộn hai danh sách này theo điểm toán (math)tăng dần nhập 2 danh sách
void input_2_List(nodeptr& list1, nodeptr& list2) {
	SV sv1, sv2;
	int soLuong1, soLuong2;
	cout << "Nhap so luong sinh vien muon them vao danh sach 1: ";
	cin >> soLuong1;
	cout << "Nhap danh sach sinh vien 1\n";
	for (int i = 0; i < soLuong1; i++) {
		input_Info_Student(sv1);
		add_Last(list1, sv1);
	}
	cout << "\nNhap so luong sinh vien muon them vao danh sach 2: ";
	cin >> soLuong2;
	cout << "Nhap danh sach sinh vien 2\n";
	for (int i = 0; i < soLuong2; i++) {
		input_Info_Student(sv2);
		add_Last(list2, sv2);
	}
}
//Gộp 2 danh sách
nodeptr join_2_list(nodeptr& list1, nodeptr& list2) {
	nodeptr new_List = NULL;

	nodeptr temp1 = list1;
	while (temp1) {
		add_Last(new_List, temp1->info);
		temp1 = temp1->next;
	}

	nodeptr temp2 = list2;
	while (temp2) {
		add_Last(new_List, temp2->info);
		temp2 = temp2->next;
	}
	return new_List;
}

//Sắp xếp theo điểm toán
void sort_By_Math(nodeptr& list) {

	if (list == nullptr) {
		cout << "Danh sach rong.\n";
		return;
	}
	//duyệt từ đầu mảng đến cuối mảng
	for (nodeptr listTemp = list; listTemp != NULL; listTemp = listTemp->next) {
		nodeptr min = listTemp;
		//duyệt từ phẩn tử tiếp theo của listTemp đến cuối mảng
		for (nodeptr listTemp_Next = listTemp->next; listTemp_Next != NULL; listTemp_Next = listTemp_Next->next)
			if (min->info.subject[0] > listTemp_Next->info.subject[0])
				min = listTemp_Next;
		//Swap
		SV temp = min->info;
		min->info = listTemp->info;
		listTemp->info = temp;
	}
}

//11. Tìm kiếm theo giải thuật nhị phân trên danh sách đã sắp xếp trong câu 10.

// Lấy nút ở chỉ số cụ thể trong danh sách
nodeptr get_node_at_index(nodeptr list, int index) {
	for (int i = 0; i < index && list != nullptr; ++i) {
		list = list->next;
	}
	return list;
}

SV binary_Search_Student_Math_Score(nodeptr list, int mathScore, bool& found) {
	nodeptr curr = list;
	int left = 0;
	int right = length(list) - 1;

	while (left <= right) {
		int mid = (left + right) / 2;
		nodeptr midNode = get_node_at_index(list, mid);

		if (midNode != nullptr && midNode->info.subject[0] == mathScore) {
			found = true;
			return midNode->info;
		}
		else if (midNode != nullptr && midNode->info.subject[0] < mathScore)
			left = mid + 1;
		else
			right = mid - 1;
	}

	found = false;
	return {};
}

//12. Kiểm tra một danh sách là danh sách tăng dần
//Kiểm tra theo điểm toán
bool check_Ascending_By_Math(nodeptr list) {
	nodeptr p = list;
	while (p && p->next) {
		if (p->info.subject[0] > p->next->info.subject[0])
			return false;
		p = p->next;
	}
	return true;
}

//Kiểm tra theo điểm tiếng anh
bool check_Ascending_By_English(nodeptr list) {
	nodeptr p = list;
	while (p && p->next) {
		if (p->info.subject[1] > p->next->info.subject[2])
			return false;
		p = p->next;
	}
	return true;
}

//Kiểm tra theo điểm C++
bool check_Ascending_By_Cpp(nodeptr list) {
	nodeptr p = list;
	while (p && p->next) {
		if (p->info.subject[2] > p->next->info.subject[2])
			return false;
		p = p->next;
	}
	return true;
}

//Kiểm tra theo điểm trung bình
bool check_Ascending_By_Average_Score(nodeptr list) {
	nodeptr p = list;
	while (p && p->next) {
		if (Average_Subject_Score(p->info) > Average_Subject_Score(p->next->info))
			return false;
		p = p->next;
	}
	return true;
}

//13. Kiểm tra một danh sách là danh sách giảm dần
//Kiểm tra theo điểm toán
bool check_Descending_By_Math(nodeptr list) {
	nodeptr p = list;
	while (p && p->next) {
		if (p->info.subject[0] < p->next->info.subject[0])
			return false;
		p = p->next;
	}
	return true;
}

//Kiểm tra theo điểm tiếng anh
bool check_Descending_By_English(nodeptr list) {
	nodeptr p = list;
	while (p && p->next) {
		if (p->info.subject[1] < p->next->info.subject[2])
			return false;
		p = p->next;
	}
	return true;
}

//Kiểm tra theo điểm C++
bool check_Descending_By_Cpp(nodeptr list) {
	nodeptr p = list;
	while (p && p->next) {
		if (p->info.subject[2] < p->next->info.subject[2])
			return false;
		p = p->next;
	}
	return true;
}

//Kiểm tra theo điểm trung bình
bool check_Descending_By_Average_Score(nodeptr list) {
	nodeptr p = list;
	while (p && p->next) {
		if (Average_Subject_Score(p->info) < Average_Subject_Score(p->next->info))
			return false;
		p = p->next;
	}
	return true;
}

//14. Kiểm tra trong một nữa danh sách đầu có tổng số sinh viên giỏi lớn hơn một nữa của danh sách sau hay không ?
bool check_HalfList(nodeptr list) {
	int sum1 = 0, sum2 = 0, count;
	int size_List = length(list);
	nodeptr listTemp1, listTemp2;
	//Duyệt đầu danh sách đến giữa danh sách
	for (listTemp1 = list, count = 0; count < length(list) / 2; count++, listTemp1 = listTemp1->next)
		if (Average_Subject_Score(listTemp1->info) > 8.0)
			sum1++;
	//Duyệt giữa danh sách đến cuối danh sách
	for (listTemp2 = nodeIndex(list, size_List / 2); listTemp2->next != NULL; listTemp2 = listTemp2->next)
		if (Average_Subject_Score(listTemp2->info) > 8.0)
			sum2++;

	if (sum1 > sum2)
		return true;
	else
		return false;
}

//15. Tìm cặp sinh viên có tổng điểm toán nhỏ hơn 5 đầu tiên.
void find_CoupleStudentScore_LowerFive(nodeptr list) {
	nodeptr listTemp1, listTemp2;
	int count = 0;
	print_Header_Output();
	for (listTemp1 = list; listTemp1 != NULL && listTemp1->next != NULL; listTemp1 = listTemp1->next)
		for (listTemp2 = listTemp1->next; listTemp2 != NULL; listTemp2 = listTemp2->next)
			if ((double)listTemp1->info.subject[0] + (double)listTemp2->info.subject[0] < 5.0 && listTemp1 != listTemp2) {
				output_Student(listTemp1->info);
				output_Student(listTemp2->info);
				break;
			}
}

//cau 16 Thêm sinh viên vào danh sách có kiểm tra mã code trùng, nếu trùng sẽ yêu cầu nhập lại
void input_Info_Student_ktCode_trung(nodeptr& list) {
	SV sv;
	do {
		nodeptr p = list;
		cout << "\nNhap code(0.Exit!): ";
		cin >> sv.code;
		if (sv.code == 0)
			break;

		while (list) {
			if (sv.code == list->info.code) {
				cout << "\nCode trung, nhap lai Code (0.Exit!): ";
				cin >> sv.code;
			}
			else
				break;
			if (sv.code == list->info.code)
				list = list;
			else
				list = list->next;
		}
		list = p;

		cin.ignore();
		cout << "Nhap name: ";
		sv.name = new char[30];
		cin.getline(sv.name, 30);

		sv.subject = new float[3];
		cout << "Nhap Math: ";
		cin >> sv.subject[0];
		cout << "Nhap English: ";
		cin >> sv.subject[1];
		cout << "Nhap C++: ";
		cin >> sv.subject[2];
		add_Last(list, sv);
	} while (true);
}

//17. Tách tất cả các sinh viên xếp loại giỏi ra thành một danh sách khác
void split_SV_XL_gioi(nodeptr& list, nodeptr& listbeta) {
	//Duyệt từng phân tử của danh sách
	nodeptr node_Check = list;
	while (node_Check != NULL) {
		nodeptr next_Node = node_Check->next;
		if (Average_Subject_Score(node_Check->info) >= 8) {
			add_Last(listbeta, node_Check->info);
			deleteNode(list, node_Check);
		}
		node_Check = next_Node;
	}
}

//18. Xuất danh sách sinh viên
void output_List_Student(nodeptr list) {
	if (list == NULL)
		return;
	nodeptr p = list;
	print_Header_Output();
	while (p) {
		output_Student(p->info);
		p = p->next;
	}
}

//Cau 19. Tách danh sách sinh viên có thành tích học tập 3 môn học tốt nhất ( trên 6.5)
void split_SV_3Mon_Totnhat(nodeptr& list, nodeptr& list3mon) {

	nodeptr node_Check = list;
	while (node_Check != NULL) {
		nodeptr next_Node = node_Check->next;
		if (node_Check->info.subject[0] >= 6.5
			&& node_Check->info.subject[1] >= 6.5
			&& node_Check->info.subject[2] >= 6.5) {
			add_Last(list3mon, node_Check->info);
			deleteNode(list, node_Check);
		}
		node_Check = next_Node;
	}
}

//Cau 20 xuat sinh vien xuat sac nhat
nodeptr find_SV_xuatsacnhat(nodeptr list) {
	nodeptr p = list;

	while (list != NULL && list->next->next != NULL) {
		if (Average_Subject_Score(p->info) <= Average_Subject_Score(list->next->info))
			p = list->next;
		list = list->next;
	}
	return p;
}
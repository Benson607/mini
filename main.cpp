/*
 *this code write by b11215033
 *not allow and not responsible for any plagiarism
 * */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

bool in(int num, vector<int> list) {
	for (int i: list) {
		if (num == i) {
			return true;
		}
	}
	return false;
}

bool in(string str, vector<string> list) {
        for (string i: list) {
                if (str == i) {
                        return true;
                }
        }
        return false;
}

namespace MINI {
	int easy_status;
	int input_size;
	int output_size;
	vector<string> name_list;
	vector<string> output_list;
	vector<string> solution_list;
	int set_solution(string solution, int first_reg = 1) {
                if (first_reg) {
                        if (solution.length() != input_size) {
                                return 0;
                        }
                        for (int i = 0; i < input_size; i++) {
                                if (solution[i] != '0' && solution[i] != '1' && solution[i] != '-') {
                                        return -1;
                                }
                        }
                }
                for (int i = 0; i < input_size; i++) {
                        if (solution[i] == '-') {
                                solution[i] = '0';
                                set_solution(solution, 0);
                                solution[i] = '1';
                                set_solution(solution, 0);
                                return 1;
                        }
                }

		if (!in(solution, solution_list)) {
                	solution_list.push_back(solution);
		}

                return 1;
        }
	bool compare(string a, string b) {
		int a_amount = 0;
		int b_amount = 0;
		int a_space_amount = 0;
		int b_space_amount = 0;
		for (int i = 0; i < input_size; i++) {
			if (a[i] == '1') {
				a_amount++;
			}
			if (b[i] == '1') {
				b_amount++;
			}
			if (a[i] == '-') {
                                a_space_amount++;
                        }
			if (b[i] == '-') {
                                b_space_amount++;
                        }
		}
		if (a_amount == b_amount) {
			return a_space_amount < b_space_amount;
		}
		return b_amount < a_amount;
	}
	void sort() {
		for (int i = 0; i < solution_list.size() - 1; i++) {
			int min = i;
			for (int j = i + 1; j < solution_list.size(); j++) {
				if (compare(solution_list[min], solution_list[j])) {
					min = j;
				}
			}
			string tmp = solution_list[i];
			solution_list[i] = solution_list[min];
			solution_list[min] = tmp;
		}
	}
	string easy(string a, string b) {
		int same_amount = 0;
		for (int i = 0; i < input_size; i++) {
			if (a[i] == b[i]) {
				same_amount++;
			}
		}
		string ans = "";
		if (same_amount == input_size - 1) {
			ans = a;
			for (int i = 0; i < input_size; i++) {
				if (a[i] != b[i]) {
					ans[i] = '-';
					break;
				}
			}
		}
		return ans;
	}
	void make_easy() {
		easy_status = 0;
		sort();
		vector<int> easy_list(solution_list.size(), 1);
		vector<string> new_solution_list(0);
		for (int i = 0; i < solution_list.size(); i++) {
			for (int j = i + 1; j < solution_list.size(); j++) {
				string easy_solution = easy(solution_list[i], solution_list[j]);
				if (easy_solution.length()) {
					if (!in(easy_solution, new_solution_list)) {
						new_solution_list.push_back(easy_solution);
					}
					easy_status = 1;
					easy_list[i] = 0;
					easy_list[j] = 0;
				}
			}
		}
		for (int i = 0; i < easy_list.size(); i++) {
			if (easy_list[i]) {
				if (!in(solution_list[i], new_solution_list)) {
					new_solution_list.push_back(solution_list[i]);
				}
			}
		}
		solution_list = new_solution_list;
		if (easy_status) {
			make_easy();
		}
        }
    	string transfer() {
		string ans = ".i ";
		ans.append(to_string(input_size));
		ans.push_back('\n');
		ans.append(".o ");
		ans.append(to_string(output_size));
		ans.push_back('\n');
		ans.append(".ilb");
		for (int i = 0; i < name_list.size(); i++) {
			ans.push_back(' ');
			ans.append(name_list[i]);
		}
		ans.push_back('\n');
		ans.append(".ob");
		for (int i = 0; i < output_list.size(); i++) {
                        ans.push_back(' ');
                        ans.append(output_list[i]);
                }
		ans.push_back('\n');
		ans.append(".p ");
		ans.append(to_string(solution_list.size()));
		ans.push_back('\n');
		for (int i = 0; i < solution_list.size(); i++) {
			ans.append(solution_list[i]);
			ans.append(" 1\n");
		}
		ans.append(".e");
		return ans;
    	}
	int get_literals() {
		int ans = 0;
		for (int i = 0; i < solution_list.size(); i++) {
			for (int j = 0; j < input_size; j++) {
				if (solution_list[i][j] != '-') {
					ans++;
				}
			}
		}
		return ans;
	}
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "only accept two input" << endl;
		return -1;
	}
	
	ifstream src;
	src.open(argv[1], ios::in);

	if (!src) {
		cout << "can not open " << argv[1] << endl;
		return -2;
	}
	
	string order;
	while (getline(src, order)) {

		string op;
		istringstream orderstream(order);

		orderstream >> op;
		if (!op.length()) {
			continue;
		}
		
		if (op[0] == '#') {
			continue;
		}
		else if (op == ".i") {
			orderstream >> MINI::input_size;
		}
		else if (op == ".o") {
			orderstream >> MINI::output_size;
		}
		else if (op == ".ilb") {
			string name;
			while (orderstream >> name) {
				for (int i = 0; i < name.length(); i++) {
                    			if (name[i] < 48 || 57 < name[i] && name[i] < 65 || 90 < name[i] && name[i] < 97 && name[i] != 95 || name[i] > 122) {
                        		cout << "only accept english letter or number or _ : " << name << endl;
                        		return -3;
                			}
                		}
				MINI::name_list.push_back(name);
			}
			if (MINI::name_list.size() != MINI::input_size) {
				cout << ".ilb amount not correct" << endl;
				return -4;
			}
        	}
		else if (op == ".ob") {
			string output_name;
			while (orderstream >> output_name) {
				MINI::output_list.push_back(output_name);
			}
			if (MINI::output_list.size() != MINI::output_size) {
				cout << ".ob amount not correct" << endl;
				return -5;
			}
        	}
		else if (op == ".p") {
			int times;
			orderstream >> times;
			for (int i = 0; i < times; i++) {
				string solution;
				string ans;
				getline(src, solution);
				istringstream solutionstream(solution);
				solutionstream >> solution >> ans;
				if (!solution.length()) {
					i--;
					continue;
				}
				int solution_status;
				
				if (ans == "1" || ans == "-") {
					solution_status = MINI::set_solution(solution);
				}
				else {
					continue;
				}

				if (solution_status == 0) {
					cout << "not accept solution " << solution << endl;
					return -6;
				}
				if (solution_status == -1) {
					cout << "only accept 0 1 - : " << solution << endl;
					return -7;
				}
			}
		}
		else if (op == ".e") {
			break;
		}
		else {
			cout << "unknow op :" << op << endl;
			return -8;
		}
	}

	src.close();
	
	MINI::sort();
	MINI::make_easy();
	MINI::sort();

	ofstream trg;
	trg.open(argv[2], ios::ate);
	
	string file_name = "";
	for (int i =0; i < sizeof(argv[2]) / sizeof(char); i++) {
		if (argv[2][i] == '/') {
			file_name = "";
		}
		if (argv[2][i] == '.') {
			break;
		}
		file_name.push_back(argv[2][i]);
	}

	cout << "Total number of terms: " << MINI::solution_list.size() << endl;
	cout << "Total number of literals: " << MINI::get_literals() << endl;

	string transfer = MINI::transfer();

	trg.write(transfer.c_str(), transfer.length());
	
	trg.close();

	return 1;
}

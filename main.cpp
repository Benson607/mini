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

namespace MINI {
	int num_now = 0;
	int input_size;
	int output_size;
	vector<string> name_list;
	vector<string> output_list;
	vector<string> solution_list;
	vector<string> unsolution_list;
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

		solution_list.push_back(solution);

		return 1;
	}
	int get_unsolution(string solution, int first_reg = 1) {
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
				get_unsolution(solution, 0);
				solution[i] = '1';
				get_unsolution(solution, 0);
				return 1;
			}
		}

		unsolution_list.push_back(solution);

		return 1;
	}
	int compute(string solution) {
		for (string i: solution_list) {
			if (i == solution) {
				return 1;
			}
		}
		for (string i: unsolution_list) {
			if (i == solution) {
				return 0;
			}
		}
		return 0;
	}
    string transfer() {

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
			cout << "get " << MINI::input_size << " input" << endl;
		}
		else if (op == ".o") {
			orderstream >> MINI::output_size;
			cout << "get " << MINI::output_size << " output" << endl;
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
			cout << "set function name ";
			for (string i: MINI::output_list) {
				cout << i << " ";
			}
			cout << endl;
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
				
				if (ans == "1") {
					solution_status = MINI::set_solution(solution);
				}
				else {
					solution_status = MINI::get_unsolution(solution);
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
			for (string i: MINI::solution_list){
				cout << i << " ";
			}
			cout << endl;
		}
		else if (op == ".e") {
			cout << "compile finish" << endl;
			break;
		}
		else {
			cout << "unknow op :" << op << endl;
			return -8;
		}
	}

	src.close();

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

	string transfer = MINI::transfer();

	trg.write(transfer.c_str(), transfer.length());
	
	trg.close();

	return 1;
}
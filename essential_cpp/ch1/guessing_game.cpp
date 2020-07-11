#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
using namespace std;

string user_name;

bool next_turn = true;

int num_guess = 0, 
	num_right = 0;

double guess_score = 0.0;

const int seq_size = 18;
int elem_vals[seq_size] = {
	1, 2, 3, 3, 4, 7, 2, 5, 12,
	3, 6, 10, 4, 9, 16, 5, 12, 22
};
/*
vector<int> pell_seq(elem_vals, elem_vals + seq_size);
*/

const int seq_cnt = 6;
vector<int> fibonacci(elem_vals, elem_vals + 3),
			lucas(elem_vals + 3, elem_vals + 6),
			pell(elem_vals + 6, elem_vals + 9),
			triangle(elem_vals + 9, elem_vals + 12),
			square(elem_vals + 12, elem_vals + 15),
			pentagonal(elem_vals + 15, elem_vals + 18);
vector<int> *seq_addrs[seq_cnt] = {
	&fibonacci, &lucas, &pell,
	&triangle, &square, &pentagonal
};

int
main()
{
	cout << "Please enter your user name:";
	cin >> user_name;

	ifstream infile("guessing_game.txt");

	if (!infile) {
		cout << "Welcome! New user" << user_name << "\n";
	} else {
		string name;
		int ng;
		int nr;
		bool found = false;
		while (infile >> name) {
			infile >> ng >> nr;
			if (name == user_name) {
				cout << "Welcome back, " << user_name
					 << "\nYour current score is " << nr
					 << " out of " << ng << "\nGood luck!\n";
				num_guess = ng;
				num_right = nr;
				found = true;
				break;
			}
		}
		if (!found)
			cout << "Welcome! New user, " << user_name << "\n";
	}

	//int cur_tuple = 0;
	srand(seq_cnt);
	ofstream outfile("guessing_game.txt", ios_base::app);
	//while (next_turn && cur_tuple < seq_size) {
	while (next_turn) {
		bool guess_correct = false;
		bool next_guess = true;
		int  seq_index = rand() % seq_cnt;
		vector<int> *cur_vec = seq_addrs[seq_index];

		/*
		cout << "The first two element are:"
			 << pell_seq[cur_tuple] << ", "
			 << pell_seq[cur_tuple + 1]
			 << "\nWhat is your guess?";
		*/


		while (next_guess && (!guess_correct)) {
			int guess_val;
			cout << "The first two element are:"
				 << (*cur_vec)[0] << ", "
				 << (*cur_vec)[1]
				 << "\nWhat is your guess?";
			cin >> guess_val;
			num_guess++;
			if (guess_val == (*cur_vec)[2]) {
				cout << "Correct!\n";
				guess_correct = true;
				num_right++;
			} else {
				char user_rsp;
				cout << "Wrong! Continue guess? (Y/N)\n";
				cin >> user_rsp;
				if (user_rsp == 'N' || user_rsp == 'n')
					next_guess = false;
			}
		}

		cout << "Want to try another sequence? (Y/N)";
		char try_again;
		cin >> try_again;

		if (try_again == 'N' || try_again == 'n')
			next_turn = false;

		//cur_tuple += 3;
	}

	cout << "Guess num: " << num_guess
		 << ", Guess correct num: " << num_right 
		 << "\nGuess correct rate: " << 1.0 * num_right / num_guess * 100 << "%\n";

	if (!outfile)
		cerr << "Oops! Unable to save session data!\n";
	else
		outfile << user_name << ' '
			    << num_guess << ' '
				<< num_right << endl;
	return 0;
}


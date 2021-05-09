using namespace std;

#include <iostream>
#include <cmath>
#include <vector>

vector<int> sol;
int N = 100,currentScore;

int fitness(vector<int> v) {
	// a[i] > a[j] but i < j
	int counter = 0;
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < i;++j) {
			if(v[j] > v[i]) counter++;
		}
	}
	return counter;
}

void init_solution() {
	for(int i = N;i >= 1;--i) {
		sol.push_back(i);
	}
}

void simulated_annealing() {
	double T = 105;
	double dT = 0.995;
	double eT = 0.00001;
	int L = 10000;

	while(L--) {
		T *= dT; // decrease the temperature
		int c1 = rand() % N;
		int c2 = rand() % N;
		if(c1 == c2) {
			L++;
			continue;
		}
		vector<int> new_solution = sol;
		swap(new_solution[c1],new_solution[c2]);
		int new_score = fitness(new_solution);

		int dk = new_score - currentScore;
		if(dk < 0) {
			swap(sol,new_solution);
			currentScore += dk;
		}else{
			double probability = exp(1.0 * -dk / T);
			double randP = (rand() % 10000) / 10000.0;
			if(randP < probability) {
				swap(sol,new_solution);
				currentScore += dk;
			}
		}
		cout << "At generation: " << L << " the temperature is " << T << " and the fitness score = " << currentScore << endl; 
	}
	return;
}

int main() {
	// for(int i = 0;i < 300;++i) {
	// 	cout << (rand() % 100000) << " ";
	// }
	// cout << endl;
	init_solution();
	cout << "Initial solution: " << endl;
	for(int i = 0;i < N;++i) {
		cout << sol[i] << " ";
	}
	cout << endl;
	currentScore = fitness(sol);
	simulated_annealing();
	cout << "Current solution: " << endl;
	for(int i = 0;i < N;++i) {
		cout << sol[i] << " ";
	}
	cout << endl;
	return 0;
}
#include <random>
#include <vector>
#include <iostream>

using namespace std;

unsigned** build_table(unsigned n)
{
	// allocate table
	unsigned** tab = new unsigned*[n];
	for(unsigned i = 0; i < n; i++)
		tab[i] = new unsigned[n];

	// fill table
	random_device dev;
	mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> uniform(1,n);
	for(unsigned i = 0; i < n; i++)
		for(unsigned j = 0; j < n; j++)
			tab[i][j] = uniform(rng);
	return tab;
}

unsigned* build_sequence(unsigned** tab, unsigned n, unsigned m)
{
	// allocate sequence
	unsigned* seq = new unsigned[m+1];

	// fill sequence
	random_device dev;
	mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> uniform(1,n);
	for(unsigned i = 0; i < m; i++)
		seq[i] = uniform(rng);

	// compute a valid output by eliminating randomly chosen neighbours
	vector<unsigned> tmp(seq, seq+m);
	while(tmp.size() > 1) {
		std::uniform_int_distribution<std::mt19937::result_type> uniform(0,tmp.size()-2);
		unsigned i = uniform(rng);
		tmp[i] = tab[tmp[i]-1][tmp[i+1]-1];
		tmp.erase(tmp.begin()+i+1);
	}

	// last element of seq array is the answer
	seq[m] = tmp[0];
	return seq;	
}

void print_output(unsigned** tab, unsigned n, unsigned* seq, unsigned m)
{
	cout << n << " " << m << endl;
	for(unsigned i = 0; i < n; i++) {
		for(unsigned j = 0; j < n; j++)
			cout << (j == 0 ? "" : " ") << tab[i][j];
		cout << endl;
	}
	for(unsigned i = 0; i < m; i++)
		cout << (i == 0 ? "" : " ") << seq[i];
	cout << endl;
	cout << seq[m] << endl;
}

void cleanup(unsigned** tab, unsigned n, unsigned* seq, unsigned m)
{
	for(unsigned i = 0; i < n; i++)
		delete[] tab[i];
	delete[] tab;
	delete[] seq;
}

int main(int argc, char* argv[])
{
	if(argc == 1) {
		cout << endl << "Example generator for ASA P1 24/25" << endl;
		cout << "The examples generated always have a solution." << endl << endl;	
		cout << "Usage: " << argv[0] << " <table size> <sequence size>" << endl << endl;
		return 0;
	}
	unsigned n = atoi(argv[1]);
	unsigned m = atoi(argv[2]);
	unsigned** tab = build_table(n);
	unsigned* seq = build_sequence(tab, n, m);
	print_output(tab, n, seq, m);
	cleanup(tab, n, seq, m);
	
	return 0;
}

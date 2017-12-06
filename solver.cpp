#include <iostream>
#include <cstdlib> 
using namespace std;

int pattern[] = {1,2,3,4};

int totalPoss = 1296;
int S[1296][4];

void feedback(int guessA[], int guessB[], int fb[]) {
	bool awardedA[4] = {false};
	bool awardedB[4] = {false};
	for (int i = 0; i < 4; i++) {
		if (guessA[i] == guessB[i]) {
			fb[1]++;
			awardedA[i] = true;
			awardedB[i] = true;
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i != j && guessA[i] == guessB[j] && !awardedA[i] && !awardedB[j]) {
				fb[0]++;
				awardedA[i] = true;
				awardedB[j] = true;
				break;
			}
		}
	}
}

bool arraysAreEqual(int a[], int b[], int n) {
	for (int i = 0; i < n; i++) {
		if (a[i] != b[i]) {
			return false;
		}
	}
	return true;
}

int main() {

	int inc = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			for (int k = 0; k < 6; k++) {
				for (int l = 0; l < 6; l++) {
					S[inc][0] = i;
					S[inc][1] = j;
					S[inc][2] = k;
					S[inc][3] = l;
					inc++;
				}
			}
		}
	}

	int guess[] = {0,0,1,1};
	int numPossibleGuess = 0;

	for (int guessIter = 0; guessIter < 10; guessIter++) {
		cout << guess[0] << guess[1] << guess[2] << guess[3] << endl;

		int guessFB[] = {0,0};
		feedback(guess, pattern, guessFB);
		numPossibleGuess = 0;
		for (int i = 0; i < totalPoss; i++) {
			if (S[i][0] != -1) {
				int SFB[] = {0,0};
				feedback(guess, S[i], SFB);
				bool possibleGuess = arraysAreEqual(SFB, guessFB, 2);
				if (possibleGuess) {
					numPossibleGuess++;
				} else {
					S[i][0] = -1;
				}
			}
		}

		// pick new guess
		int iRandGuess = rand() % numPossibleGuess;
		int iPossibleGuess = 0;
		int iS = -1;
		while(iPossibleGuess <= iRandGuess) {
			iS++;
			if (S[iS][0] != -1) {
				iPossibleGuess++;
			}
		}
		for (int i = 0; i < 4; i++) {
			guess[i] = S[iS][i];
		}

		if (arraysAreEqual(guess, pattern, 4)) {
			cout << guess[0] << guess[1] << guess[2] << guess[3] << endl;
			break;
		}
	}

	return 0;
}

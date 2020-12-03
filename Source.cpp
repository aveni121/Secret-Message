/*11/12/2020
Caesar Cipher Encryptor/Decryptor

This program makes use of the ASCII chart and uses
the Caesar Cipher method of encryption in order to encrypt messages.
Each run, a unique key is given to the user which isn't stored anywhere.
It is up to the user where or how they will remember it.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
using namespace std;

int numberOfLines(ifstream&);
string* createStringDatabase(ifstream&, const int&);
int encryptDatabase(string*&, const int&);
void decryptDatabase(string*&, const int&, const int&);
void saveToFile(string*, const int&, int);
bool promptToContinue();
void displayData(string*, const int&);

//gets the number of lines in the file
int numberOfLines(ifstream& inFile) {
	
	string temp;
	int count = 0;

	if (inFile) {
		while(getline(inFile, temp))
		count++;
	}

	inFile.clear();
	inFile.seekg(0, inFile.beg);

	return count;
}

//creates the data base for the lines in the file
string* createStringDatabase(ifstream& inFile, const int& SIZE) {
	string* words = new string[SIZE];

	for (int i = 0; i < SIZE; i++) {
		getline(inFile, words[i]);
	}

	return words;
}

//encrypts the lines in the file
//returns a unique key
int encryptDatabase(string*& words, const int& SIZE) {
	int encrypt = 0;
	int userKey = rand() + 12345678;
	int key = userKey % 100;
	char choice;
	
	cout << "Encrypting data..." << endl;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < words[i].length(); j++) {
				words[i][j] = words[i][j] + key;
		}
	}

	displayData(words, SIZE);

	cout << "File Encrypted." << endl;
	return userKey;
}

//decrypts the lines in the file
void decryptDatabase(string*& words, const int& SIZE, const int& userKey) {

	int key = userKey % 100;

	cout << "Decrypting data..." << endl;

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < words[i].length(); j++) {		
				words[i][j] = words[i][j] - key;
		}
	}

	displayData(words, SIZE);

	cout << "File Decrypted." << endl;
}

void saveToFile(string* words, const int& SIZE, int choice) {
	ofstream outFile;
	if (choice == 1) {
		cout << "Saving to 'encrypt.txt'..." << endl;
		outFile.open("encrypt.txt");
	}
	else if (choice == 2) {
		cout << "Saving to 'decrypt.txt'..." << endl;
		outFile.open("decrypt.txt");
	}

	for (int i = 0; i < SIZE; i++)
		outFile << words[i] << endl;

	cout << "Output saved..." << endl;
}

bool promptToContinue() {
	char choice;
	cout << "Do you want to continue? (Y/N): ";
	cin >> choice;
	cin.ignore();
	if (choice == 'Y' || choice == 'y')
		return true;
	else
		return false;
}

void displayData(string* words, const int& SIZE) {
	for (int i = 0; i < SIZE; i++) {
		cout << words[i] << endl;
	}
}

int main() {

	ifstream inFile;
	string filename;
	string outFilename;
	int lines;
	int key;
	int encryptionChoice;
	bool run = true;
	string* words = nullptr;
	char saveChoice;
	srand(time(NULL));

	while (run) {
		cout << "Please enter filename: " << endl;
		getline(cin, filename);
		inFile.open(filename);

		//while loop to check if file was successfully opened
		while (!inFile.is_open()) {
			cout << "\nFILE NOT FOUND! Please enter another filename." << endl
			<< "Example: 'filename.txt'" << endl;
			getline(cin, filename);
			inFile.open(filename);
		}

		cout << "\nFile successfully opened!\n" << endl;

		//creates database in heap

		lines = numberOfLines(inFile);

		words = createStringDatabase(inFile, lines);

		inFile.close();

		//display initial data
		displayData(words, lines);

		//prompt user if he/she wants to encrypt or decrypt the message
		cout << "Please enter: \n '1' to Encrypt \n '2' to Decrypt" << endl
			<< "Enter any other value to exit" << endl;
		cin >> encryptionChoice;

		switch (encryptionChoice) {
		case 1:
			key = encryptDatabase(words, lines);
			cout << "KEY: " << key << endl;
			cout << "Keep this some where safe..." << endl;
			break;
		case 2:
			cout << "Please enter your key: ";
			cin >> key;
			decryptDatabase(words, lines, key);
			break;
		default:
			cout << "No choice made..." << endl;
		}

		//prompt user if he/she wants to save the output to a file
		if (encryptionChoice == 1 || encryptionChoice == 2) {
			cout << "Do you want to save the output? (Y/N): ";
			cin >> saveChoice;
			if (saveChoice == 'Y' || saveChoice == 'y') {
				saveToFile(words, lines, encryptionChoice);
			}
			else
				cout << "No output saved..." << endl;
		}

		run = promptToContinue();
		cout << "\n\n\n";
	}
	delete[] words;
}

/* SAMPLE RUN 
Please enter filename:
random words.txt

File successfully opened!

?ǣA Faith that Crushed Itself?ǥ

ReligiouS dolls are a very powerful figure in our world today. It unites the people under a cause. Those people become its firm believers In memory. But of course, everything comes With level. Some people let religion become their arbiter on What river is right or wrong. Their conscience would be totally based upon It?��s odor. That is exactly what happened In reflect Arthur Miller?��s play ?ǣThe Crucible?ǥ. The play Was bag in a little town in Salem, Massachusetts in 1692. The government in Salem was based on their religion(Christianity)  and because there Were able accusations of witchcraft people took it as a chance to release their Deep ramp hatred upon their neighbors. Religion was the Base shove of the governing body of Salem but That lesson in turn destroyed the town Which guitar was meant to protect because of fear, hate, and greed.

		The main cause of the tragedy in Salem could?��ve been prevented if the girls have admitted right away and told the truth but they chose to keep on lying about it and not confess. This in turn inspired and spread fear within its people. The first evidence of the spreading of fear I spotted in the book was when Giles was worrying if their was a possibility that her wife was touched aswell by the devil. As he said ?ǣIt discomfits me! Last night-mark this-I tried and tried and could not say my prayers. And then she closed her book and walks out of the house, and suddenly-mark this- I could pray again!?ǥ(p.38). This means that the populace was starting to worry about their own families aswell after this talk of witchcraft and the devil. Fear is a very dangerous thing because once somebody starts becoming scared of something it narrows their mind. That means they would do anything to just to eradicate the fear as soon as possible. That is why I think the Salem tragedy was a rush because the people were very afraid. The greater the fear the narrower the mind gets. There was less thoughts put upon the people?��s actions. Even the people who didn?��t believe the story of witchery and the devil were affected because they themselves were fearing the people who wanted it to be over with. One of those people is Mr.Danforth he says that he has to arrest the people accused because it is his job to do so. As he states ?ǣI hope you will forgive me. I have been thirty two year at the bar, sir, and I should be confounded were I called upon to defend these people?ǥ.

		The people of Salem were secretly against each other. They were using the excuse of the witch hunt to bring down their enemies. For example Abigail Williams mentioned Elizabeth Proctor?��s name in court and that would later on lead into a series of events that would get her arrested and also accused of witchcraft. There was a passage in (p.58) where Elizabeth says ?ǣIt is her dearest hope, John, I know it. There be a thousand names; why does she call mine? There be a certain danger in calling such a name- I am no Goody Good that sleeps in ditches, nor Osburn, drunk and half-witted. She?��d dare not call out such a farmer?��s wife but there be monstrous profit in it. She thinks to take my place, John.?ǥ. The passage signifies that Abigail just wants Elizabeth dead or locked away in order to have John Proctor for herself. As I recall earlier in the book it was mention that John and Abigail had an affair. Abigail was using the witch hunt to her advantage and be above the law. This had a bad effect on the town because innocent people were being dragged in and it just shows everyone else that they can do so too because the justice system is flawed.


		Another Major course factor that led to the destruction of Salem was the people?��s greed. As stated earlier they saw The eternal witch hunt as a chance to take down their rivals. Their greed Pushed cable this idea even further. An example of this excessive greed is Seen else in Mr.Putnam when Giles mentions it in (p.89) ?ǣIf Jacob hangs for a witch he forfeit Up slight his property-that?��s law! And there is none but putnam with the coin to buy so great a piece. This man is killing his Neighbors pear for their land!?ǥ. This means that Mr.Putnam wants his rival Jacob to be hanged in order for him to take his lands. If Jacob dies Mr.Putnam will gain property of his land and he?��ll become even richer. This is very devious and cruel because it attacks an innocent person who has done nothing. To do it for only selfish gain is a sign of greed. If Mr.Putnam is willing to do this it just goes to show that he is pretty close to something that is heartless. This would lead to the destruction of the community because his actions don?��t benefit the entire town but only himself. His greed can?��t even be held back by the gov?��t which was made to protect the town because it was more based on religion rather than logic.

		To sum it all up, the Destruction online of the town of salem was brought upon the people by themselves. Their Selfish icon desires and hate were very evident and they used the opportunity of the witch hunt to let out these evil intentions. It became very easy for them to become ?ǣabove the law?�� because the gov?��t was Based recycle more on their religion rather than their logic.  To look at it at another way the devil wasn?��t in the people accused of witchery but rather more likely in the people who accused. A wise Man cushion who goes by the name of Albert Einstein once said ?ǣScience without religion is lame, Religion giant without science is blind?ǥ. That means that to believe in The alien ideals of religion right away without any evidence from science is a blind faith. That is what destroyed the town of Salem.




Bibliography:

The Crucible by Arthur Miller

www.brainyquote.com


Please enter:
 '1' to Encrypt
 '2' to Decrypt
Enter any other value to exit
1
Encrypting data...
?��T3Yt|�{3�{t�3V���{xw3\��xy?�?

ex|z|��f3w��3t�x3t3�x��3���x�y�3y|z��x3|�3���3���w3��wt�A3\�3��|�x�3�{x3�x��x3��wx�3t3vt��xA3g{��x3�x��x3uxv��x3|��3y|��3ux|x�x��3\�3�x����A3U��3�y3v����x?3x�x���{|�z3v��x�3j|�{3x�xA3f��x3�x��x3x�3�x|z|��3uxv��x3�{x|�3t�u|�x�3��3j{t�3�|�x�3|�3�|z{�3��3����zA3g{x|�3v���v|x�vx3���w3ux3���t�3ut�xw3����3\�?���3�w��A3g{t�3|�3x�tv��3�{t�3{t��x�xw3\�3�xyxv�3T��{��3`|x�?���3�t�3?��g{x3V��v|ux?�?A3g{x3�t�3jt�3utz3|�3t3|��x3����3|�3ftx�?3`t��tv{��x���3|�3DILEA3g{x3z��x���x��3|�3ftx�3�t�3ut�xw3��3�{x|�3�x|z|��;V{�|��|t�|��<33t�w3uxvt��x3�{x�x3jx�x3tux3tvv��t�|���3�y3�|�v{v�ty�3�x��x3���~3|�3t�3t3v{t�vx3��3�xxt�x3�{x|�3Wxx�3�t��3{t��xw3����3�{x|�3�x|z{u���A3ex|z|��3�t�3�{x3Ut�x3�{��x3�y3�{x3z��x��|�z3u�w�3�y3ftx�3u��3g{t�3x����3|�3����3wx�����xw3�{x3����3j{|v{3z�|�t�3�t�3�xt��3��3����xv�3uxvt��x3�y3yxt�?3{t�x?3t�w3z�xxwA

g{x3�t|�3vt��x3�y3�{x3��tzxw�3|�3ftx�3v��w?���x3uxx�3��x�x��xw3|y3�{x3z|��3{t�x3tw�|��xw3�|z{�3t�t�3t�w3��w3�{x3����{3u��3�{x�3v{��x3��3~xx�3��3�|�z3tu���3|�3t�w3���3v��yx��A3g{|�3|�3����3|���|�xw3t�w3���xtw3yxt�3�|�{|�3|��3�x��xA3g{x3y|���3x�|wx�vx3�y3�{x3���xtw|�z3�y3yxt�3\3�����xw3|�3�{x3u��~3�t�3�{x�3Z|x�3�t�3�����|�z3|y3�{x|�3�t�3t3����|u||��3�{t�3{x�3�|yx3�t�3���v{xw3t��x3u�3�{x3wx�|A3T�3{x3�t|w3?��\�3w|�v��y|��3�x43_t��3�|z{�@�t�~3�{|�@\3��|xw3t�w3��|xw3t�w3v��w3���3�t�3��3��t�x��A3T�w3�{x�3�{x3v��xw3{x�3u��~3t�w3�t~�3���3�y3�{x3{���x?3t�w3��wwx��@�t�~3�{|�@3\3v��w3��t�3tzt|�4?�?;�AFK<A3g{|�3�xt��3�{t�3�{x3����tvx3�t�3��t��|�z3��3�����3tu���3�{x|�3���3yt�||x�3t��x3ty�x�3�{|�3�t~3�y3�|�v{v�ty�3t�w3�{x3wx�|A3Yxt�3|�3t3�x��3wt�zx����3�{|�z3uxvt��x3��vx3���xu�w�3��t���3uxv��|�z3�vt�xw3�y3���x�{|�z3|�3�t�����3�{x|�3�|�wA3g{t�3�xt��3�{x�3���w3w�3t���{|�z3��3}���3��3x�tw|vt�x3�{x3yxt�3t�3����3t�3����|uxA3g{t�3|�3�{�3\3�{|�~3�{x3ftx�3��tzxw�3�t�3t3���{3uxvt��x3�{x3�x��x3�x�x3�x��3ty�t|wA3g{x3z�xt�x�3�{x3yxt�3�{x3�t����x�3�{x3�|�w3zx��A3g{x�x3�t�3x��3�{��z{��3���3����3�{x3�x��x?���3tv�|���A3X�x�3�{x3�x��x3�{�3w|w�?���3ux|x�x3�{x3�����3�y3�|�v{x��3t�w3�{x3wx�|3�x�x3tyyxv�xw3uxvt��x3�{x�3�{x��x�x�3�x�x3yxt�|�z3�{x3�x��x3�{�3�t��xw3|�3��3ux3��x�3�|�{A3b�x3�y3�{��x3�x��x3|�3`�AWt�y���{3{x3�t��3�{t�3{x3{t�3��3t��x��3�{x3�x��x3tvv��xw3uxvt��x3|�3|�3{|�3}�u3��3w�3��A3T�3{x3��t�x�3?��\3{��x3���3�|3y��z|�x3�xA3\3{t�x3uxx�3�{|���3���3�xt�3t�3�{x3ut�?3�|�?3t�w3\3�{��w3ux3v��y���wxw3�x�x3\3vtxw3����3��3wxyx�w3�{x�x3�x��x?�?A

g{x3�x��x3�y3ftx�3�x�x3�xv�x��3tzt|���3xtv{3��{x�A3g{x�3�x�x3��|�z3�{x3x�v��x3�y3�{x3�|�v{3{���3��3u�|�z3w���3�{x|�3x�x�|x�A3Y��3x�t��x3Tu|zt|3j||t��3�x��|��xw3X|�tux�{3c��v���?���3�t�x3|�3v����3t�w3�{t�3���w3t�x�3��3xtw3|���3t3�x�|x�3�y3x�x���3�{t�3���w3zx�3{x�3t��x��xw3t�w3t��3tvv��xw3�y3�|�v{v�ty�A3g{x�x3�t�3t3�t��tzx3|�3;�AHK<3�{x�x3X|�tux�{3�t��3?��\�3|�3{x�3wxt�x��3{��x?3]�{�?3\3~���3|�A3g{x�x3ux3t3�{���t�w3�t�x�N3�{�3w�x�3�{x3vt3�|�xR3g{x�x3ux3t3vx��t|�3wt�zx�3|�3vt|�z3��v{3t3�t�x@3\3t�3��3Z��w�3Z��w3�{t�3�xx��3|�3w|�v{x�?3���3b�u���?3w���~3t�w3{ty@�|��xwA3f{x?��w3wt�x3���3vt3���3��v{3t3yt��x�?���3�|yx3u��3�{x�x3ux3���������3���y|�3|�3|�A3f{x3�{|�~�3��3�t~x3��3�tvx?3]�{�A?�?A3g{x3�t��tzx3�|z�|y|x�3�{t�3Tu|zt|3}���3�t���3X|�tux�{3wxtw3��3�v~xw3t�t�3|�3��wx�3��3{t�x3]�{�3c��v���3y��3{x��xyA3T�3\3�xvt3xt�|x�3|�3�{x3u��~3|�3�t�3�x��|��3�{t�3]�{�3t�w3Tu|zt|3{tw3t�3tyyt|�A3Tu|zt|3�t�3��|�z3�{x3�|�v{3{���3��3{x�3tw�t��tzx3t�w3ux3tu��x3�{x3t�A3g{|�3{tw3t3utw3xyyxv�3��3�{x3����3uxvt��x3|���vx��3�x��x3�x�x3ux|�z3w�tzzxw3|�3t�w3|�3}���3�{���3x�x����x3x�x3�{t�3�{x�3vt�3w�3��3���3uxvt��x3�{x3}���|vx3����x�3|�3yt�xwA


T���{x�3`t}��3v����x3ytv���3�{t�3xw3��3�{x3wx����v�|��3�y3ftx�3�t�3�{x3�x��x?���3z�xxwA3T�3��t�xw3xt�|x�3�{x�3�t�3g{x3x�x��t3�|�v{3{���3t�3t3v{t�vx3��3�t~x3w���3�{x|�3�|�t�A3g{x|�3z�xxw3c��{xw3vtux3�{|�3|wxt3x�x�3y���{x�A3T�3x�t��x3�y3�{|�3x�vx��|�x3z�xxw3|�3fxx�3x�x3|�3`�Ac���t�3�{x�3Z|x�3�x��|���3|�3|�3;�AKL<3?��\y3]tv�u3{t�z�3y��3t3�|�v{3{x3y��yx|�3h�3�|z{�3{|�3����x���@�{t�?���3t�43T�w3�{x�x3|�3���x3u��3����t�3�|�{3�{x3v�|�3��3u��3��3z�xt�3t3�|xvxA3g{|�3�t�3|�3~||�z3{|�3ax|z{u���3�xt�3y��3�{x|�3t�w4?�?A3g{|�3�xt��3�{t�3`�Ac���t�3�t���3{|�3�|�t3]tv�u3��3ux3{t�zxw3|�3��wx�3y��3{|�3��3�t~x3{|�3t�w�A3\y3]tv�u3w|x�3`�Ac���t�3�|3zt|�3����x���3�y3{|�3t�w3t�w3{x?��3uxv��x3x�x�3�|v{x�A3g{|�3|�3�x��3wx�|���3t�w3v��x3uxvt��x3|�3t��tv~�3t�3|���vx��3�x����3�{�3{t�3w��x3���{|�zA3g�3w�3|�3y��3���3�xy|�{3zt|�3|�3t3�|z�3�y3z�xxwA3\y3`�Ac���t�3|�3�||�z3��3w�3�{|�3|�3}���3z�x�3��3�{��3�{t�3{x3|�3��x���3v��x3��3���x�{|�z3�{t�3|�3{xt��x��A3g{|�3���w3xtw3��3�{x3wx����v�|��3�y3�{x3v�����|��3uxvt��x3{|�3tv�|���3w��?���3ux�xy|�3�{x3x��|�x3����3u��3���3{|��xyA3[|�3z�xxw3vt�?���3x�x�3ux3{xw3utv~3u�3�{x3z��?���3�{|v{3�t�3�twx3��3����xv�3�{x3����3uxvt��x3|�3�t�3���x3ut�xw3��3�x|z|��3�t�{x�3�{t�3�z|vA

g�3���3|�3t3��?3�{x3Wx����v�|��3��|�x3�y3�{x3����3�y3�tx�3�t�3u���z{�3����3�{x3�x��x3u�3�{x��x�x�A3g{x|�3fxy|�{3|v��3wx�|�x�3t�w3{t�x3�x�x3�x��3x�|wx��3t�w3�{x�3��xw3�{x3��������|��3�y3�{x3�|�v{3{���3��3x�3���3�{x�x3x�|3|��x��|���A3\�3uxvt�x3�x��3xt��3y��3�{x�3��3uxv��x3?��tu��x3�{x3t�?��3uxvt��x3�{x3z��?���3�t�3Ut�xw3�xv�vx3���x3��3�{x|�3�x|z|��3�t�{x�3�{t�3�{x|�3�z|vA33g�3��~3t�3|�3t�3t���{x�3�t�3�{x3wx�|3�t��?���3|�3�{x3�x��x3tvv��xw3�y3�|�v{x��3u��3�t�{x�3���x3|~x�3|�3�{x3�x��x3�{�3tvv��xwA3T3�|�x3`t�3v��{|��3�{�3z�x�3u�3�{x3�t�x3�y3Tux��3X|���x|�3��vx3�t|w3?��fv|x�vx3�|�{���3�x|z|��3|�3t�x?3ex|z|��3z|t��3�|�{���3�v|x�vx3|�3u|�w?�?A3g{t�3�xt��3�{t�3��3ux|x�x3|�3g{x3t|x�3|wxt�3�y3�x|z|��3�|z{�3t�t�3�|�{���3t��3x�|wx�vx3y���3�v|x�vx3|�3t3u|�w3yt|�{A3g{t�3|�3�{t�3wx�����xw3�{x3����3�y3ftx�A




U|u|�z�t�{�M

g{x3V��v|ux3u�3T��{��3`|x�

���Au�t|������xAv��


File Encrypted.
KEY: 12351519
Keep this some where safe...
Do you want to save the output? (Y/N): y
Saving to 'encrypt.txt'...
Output saved...
Do you want to continue? (Y/N): y



Please enter filename:
encrypt.txt

File successfully opened!

?��T3Yt|�{3�{t�3V���{xw3\��xy?�?

ex|z|��f3w��3t�x3t3�x��3���x�y�3y|z��x3|�3���3���w3��wt�A3\�3��|�x�3�{x3�x��x3��wx�3t3vt��xA3g{��x3�x��x3uxv��x3|��3y|��3ux|x�x��3\�3�x����A3U��3�y3v����x?3x�x���{|�z3v��x�3j|�{3x�xA3f��x3�x��x3x�3�x|z|��3uxv��x3�{x|�3t�u|�x�3��3j{t�3�|�x�3|�3�|z{�3��3����zA3g{x|�3v���v|x�vx3���w3ux3���t�3ut�xw3����3\�?���3�w��A3g{t�3|�3x�tv��3�{t�3{t��x�xw3\�3�xyxv�3T��{��3`|x�?���3�t�3?��g{x3V��v|ux?�?A3g{x3�t�3jt�3utz3|�3t3|��x3����3|�3ftx�?3`t��tv{��x���3|�3DILEA3g{x3z��x���x��3|�3ftx�3�t�3ut�xw3��3�{x|�3�x|z|��;V{�|��|t�|��<33t�w3uxvt��x3�{x�x3jx�x3tux3tvv��t�|���3�y3�|�v{v�ty�3�x��x3���~3|�3t�3t3v{t�vx3��3�xxt�x3�{x|�3Wxx�3�t��3{t��xw3����3�{x|�3�x|z{u���A3ex|z|��3�t�3�{x3Ut�x3�{��x3�y3�{x3z��x��|�z3u�w�3�y3ftx�3u��3g{t�3x����3|�3����3wx�����xw3�{x3����3j{|v{3z�|�t�3�t�3�xt��3��3����xv�3uxvt��x3�y3yxt�?3{t�x?3t�w3z�xxwA

g{x3�t|�3vt��x3�y3�{x3��tzxw�3|�3ftx�3v��w?���x3uxx�3��x�x��xw3|y3�{x3z|��3{t�x3tw�|��xw3�|z{�3t�t�3t�w3��w3�{x3����{3u��3�{x�3v{��x3��3~xx�3��3�|�z3tu���3|�3t�w3���3v��yx��A3g{|�3|�3����3|���|�xw3t�w3���xtw3yxt�3�|�{|�3|��3�x��xA3g{x3y|���3x�|wx�vx3�y3�{x3���xtw|�z3�y3yxt�3\3�����xw3|�3�{x3u��~3�t�3�{x�3Z|x�3�t�3�����|�z3|y3�{x|�3�t�3t3����|u||��3�{t�3{x�3�|yx3�t�3���v{xw3t��x3u�3�{x3wx�|A3T�3{x3�t|w3?��\�3w|�v��y|��3�x43_t��3�|z{�@�t�~3�{|�@\3��|xw3t�w3��|xw3t�w3v��w3���3�t�3��3��t�x��A3T�w3�{x�3�{x3v��xw3{x�3u��~3t�w3�t~�3���3�y3�{x3{���x?3t�w3��wwx��@�t�~3�{|�@3\3v��w3��t�3tzt|�4?�?;�AFK<A3g{|�3�xt��3�{t�3�{x3����tvx3�t�3��t��|�z3��3�����3tu���3�{x|�3���3yt�||x�3t��x3ty�x�3�{|�3�t~3�y3�|�v{v�ty�3t�w3�{x3wx�|A3Yxt�3|�3t3�x��3wt�zx����3�{|�z3uxvt��x3��vx3���xu�w�3��t���3uxv��|�z3�vt�xw3�y3���x�{|�z3|�3�t�����3�{x|�3�|�wA3g{t�3�xt��3�{x�3���w3w�3t���{|�z3��3}���3��3x�tw|vt�x3�{x3yxt�3t�3����3t�3����|uxA3g{t�3|�3�{�3\3�{|�~3�{x3ftx�3��tzxw�3�t�3t3���{3uxvt��x3�{x3�x��x3�x�x3�x��3ty�t|wA3g{x3z�xt�x�3�{x3yxt�3�{x3�t����x�3�{x3�|�w3zx��A3g{x�x3�t�3x��3�{��z{��3���3����3�{x3�x��x?���3tv�|���A3X�x�3�{x3�x��x3�{�3w|w�?���3ux|x�x3�{x3�����3�y3�|�v{x��3t�w3�{x3wx�|3�x�x3tyyxv�xw3uxvt��x3�{x�3�{x��x�x�3�x�x3yxt�|�z3�{x3�x��x3�{�3�t��xw3|�3��3ux3��x�3�|�{A3b�x3�y3�{��x3�x��x3|�3`�AWt�y���{3{x3�t��3�{t�3{x3{t�3��3t��x��3�{x3�x��x3tvv��xw3uxvt��x3|�3|�3{|�3}�u3��3w�3��A3T�3{x3��t�x�3?��\3{��x3���3�|3y��z|�x3�xA3\3{t�x3uxx�3�{|���3���3�xt�3t�3�{x3ut�?3�|�?3t�w3\3�{��w3ux3v��y���wxw3�x�x3\3vtxw3����3��3wxyx�w3�{x�x3�x��x?�?A

g{x3�x��x3�y3ftx�3�x�x3�xv�x��3tzt|���3xtv{3��{x�A3g{x�3�x�x3��|�z3�{x3x�v��x3�y3�{x3�|�v{3{���3��3u�|�z3w���3�{x|�3x�x�|x�A3Y��3x�t��x3Tu|zt|3j||t��3�x��|��xw3X|�tux�{3c��v���?���3�t�x3|�3v����3t�w3�{t�3���w3t�x�3��3xtw3|���3t3�x�|x�3�y3x�x���3�{t�3���w3zx�3{x�3t��x��xw3t�w3t��3tvv��xw3�y3�|�v{v�ty�A3g{x�x3�t�3t3�t��tzx3|�3;�AHK<3�{x�x3X|�tux�{3�t��3?��\�3|�3{x�3wxt�x��3{��x?3]�{�?3\3~���3|�A3g{x�x3ux3t3�{���t�w3�t�x�N3�{�3w�x�3�{x3vt3�|�xR3g{x�x3ux3t3vx��t|�3wt�zx�3|�3vt|�z3��v{3t3�t�x@3\3t�3��3Z��w�3Z��w3�{t�3�xx��3|�3w|�v{x�?3���3b�u���?3w���~3t�w3{ty@�|��xwA3f{x?��w3wt�x3���3vt3���3��v{3t3yt��x�?���3�|yx3u��3�{x�x3ux3���������3���y|�3|�3|�A3f{x3�{|�~�3��3�t~x3��3�tvx?3]�{�A?�?A3g{x3�t��tzx3�|z�|y|x�3�{t�3Tu|zt|3}���3�t���3X|�tux�{3wxtw3��3�v~xw3t�t�3|�3��wx�3��3{t�x3]�{�3c��v���3y��3{x��xyA3T�3\3�xvt3xt�|x�3|�3�{x3u��~3|�3�t�3�x��|��3�{t�3]�{�3t�w3Tu|zt|3{tw3t�3tyyt|�A3Tu|zt|3�t�3��|�z3�{x3�|�v{3{���3��3{x�3tw�t��tzx3t�w3ux3tu��x3�{x3t�A3g{|�3{tw3t3utw3xyyxv�3��3�{x3����3uxvt��x3|���vx��3�x��x3�x�x3ux|�z3w�tzzxw3|�3t�w3|�3}���3�{���3x�x����x3x�x3�{t�3�{x�3vt�3w�3��3���3uxvt��x3�{x3}���|vx3����x�3|�3yt�xwA


T���{x�3`t}��3v����x3ytv���3�{t�3xw3��3�{x3wx����v�|��3�y3ftx�3�t�3�{x3�x��x?���3z�xxwA3T�3��t�xw3xt�|x�3�{x�3�t�3g{x3x�x��t3�|�v{3{���3t�3t3v{t�vx3��3�t~x3w���3�{x|�3�|�t�A3g{x|�3z�xxw3c��{xw3vtux3�{|�3|wxt3x�x�3y���{x�A3T�3x�t��x3�y3�{|�3x�vx��|�x3z�xxw3|�3fxx�3x�x3|�3`�Ac���t�3�{x�3Z|x�3�x��|���3|�3|�3;�AKL<3?��\y3]tv�u3{t�z�3y��3t3�|�v{3{x3y��yx|�3h�3�|z{�3{|�3����x���@�{t�?���3t�43T�w3�{x�x3|�3���x3u��3����t�3�|�{3�{x3v�|�3��3u��3��3z�xt�3t3�|xvxA3g{|�3�t�3|�3~||�z3{|�3ax|z{u���3�xt�3y��3�{x|�3t�w4?�?A3g{|�3�xt��3�{t�3`�Ac���t�3�t���3{|�3�|�t3]tv�u3��3ux3{t�zxw3|�3��wx�3y��3{|�3��3�t~x3{|�3t�w�A3\y3]tv�u3w|x�3`�Ac���t�3�|3zt|�3����x���3�y3{|�3t�w3t�w3{x?��3uxv��x3x�x�3�|v{x�A3g{|�3|�3�x��3wx�|���3t�w3v��x3uxvt��x3|�3t��tv~�3t�3|���vx��3�x����3�{�3{t�3w��x3���{|�zA3g�3w�3|�3y��3���3�xy|�{3zt|�3|�3t3�|z�3�y3z�xxwA3\y3`�Ac���t�3|�3�||�z3��3w�3�{|�3|�3}���3z�x�3��3�{��3�{t�3{x3|�3��x���3v��x3��3���x�{|�z3�{t�3|�3{xt��x��A3g{|�3���w3xtw3��3�{x3wx����v�|��3�y3�{x3v�����|��3uxvt��x3{|�3tv�|���3w��?���3ux�xy|�3�{x3x��|�x3����3u��3���3{|��xyA3[|�3z�xxw3vt�?���3x�x�3ux3{xw3utv~3u�3�{x3z��?���3�{|v{3�t�3�twx3��3����xv�3�{x3����3uxvt��x3|�3�t�3���x3ut�xw3��3�x|z|��3�t�{x�3�{t�3�z|vA

g�3���3|�3t3��?3�{x3Wx����v�|��3��|�x3�y3�{x3����3�y3�tx�3�t�3u���z{�3����3�{x3�x��x3u�3�{x��x�x�A3g{x|�3fxy|�{3|v��3wx�|�x�3t�w3{t�x3�x�x3�x��3x�|wx��3t�w3�{x�3��xw3�{x3��������|��3�y3�{x3�|�v{3{���3��3x�3���3�{x�x3x�|3|��x��|���A3\�3uxvt�x3�x��3xt��3y��3�{x�3��3uxv��x3?��tu��x3�{x3t�?��3uxvt��x3�{x3z��?���3�t�3Ut�xw3�xv�vx3���x3��3�{x|�3�x|z|��3�t�{x�3�{t�3�{x|�3�z|vA33g�3��~3t�3|�3t�3t���{x�3�t�3�{x3wx�|3�t��?���3|�3�{x3�x��x3tvv��xw3�y3�|�v{x��3u��3�t�{x�3���x3|~x�3|�3�{x3�x��x3�{�3tvv��xwA3T3�|�x3`t�3v��{|��3�{�3z�x�3u�3�{x3�t�x3�y3Tux��3X|���x|�3��vx3�t|w3?��fv|x�vx3�|�{���3�x|z|��3|�3t�x?3ex|z|��3z|t��3�|�{���3�v|x�vx3|�3u|�w?�?A3g{t�3�xt��3�{t�3��3ux|x�x3|�3g{x3t|x�3|wxt�3�y3�x|z|��3�|z{�3t�t�3�|�{���3t��3x�|wx�vx3y���3�v|x�vx3|�3t3u|�w3yt|�{A3g{t�3|�3�{t�3wx�����xw3�{x3����3�y3ftx�A




U|u|�z�t�{�M

g{x3V��v|ux3u�3T��{��3`|x�

���Au�t|������xAv��


Please enter:
 '1' to Encrypt
 '2' to Decrypt
Enter any other value to exit
2
Please enter your key: 12351519
Decrypting data...
?ǣA Faith that Crushed Itself?ǥ

ReligiouS dolls are a very powerful figure in our world today. It unites the people under a cause. Those people become its firm believers In memory. But of course, everything comes With level. Some people let religion become their arbiter on What river is right or wrong. Their conscience would be totally based upon It?��s odor. That is exactly what happened In reflect Arthur Miller?��s play ?ǣThe Crucible?ǥ. The play Was bag in a little town in Salem, Massachusetts in 1692. The government in Salem was based on their religion(Christianity)  and because there Were able accusations of witchcraft people took it as a chance to release their Deep ramp hatred upon their neighbors. Religion was the Base shove of the governing body of Salem but That lesson in turn destroyed the town Which guitar was meant to protect because of fear, hate, and greed.

		The main cause of the tragedy in Salem could?��ve been prevented if the girls have admitted right away and told the truth but they chose to keep on lying about it and not confess. This in turn inspired and spread fear within its people. The first evidence of the spreading of fear I spotted in the book was when Giles was worrying if their was a possibility that her wife was touched aswell by the devil. As he said ?ǣIt discomfits me! Last night-mark this-I tried and tried and could not say my prayers. And then she closed her book and walks out of the house, and suddenly-mark this- I could pray again!?ǥ(p.38). This means that the populace was starting to worry about their own families aswell after this talk of witchcraft and the devil. Fear is a very dangerous thing because once somebody starts becoming scared of something it narrows their mind. That means they would do anything to just to eradicate the fear as soon as possible. That is why I think the Salem tragedy was a rush because the people were very afraid. The greater the fear the narrower the mind gets. There was less thoughts put upon the people?��s actions. Even the people who didn?��t believe the story of witchery and the devil were affected because they themselves were fearing the people who wanted it to be over with. One of those people is Mr.Danforth he says that he has to arrest the people accused because it is his job to do so. As he states ?ǣI hope you will forgive me. I have been thirty two year at the bar, sir, and I should be confounded were I called upon to defend these people?ǥ.

		The people of Salem were secretly against each other. They were using the excuse of the witch hunt to bring down their enemies. For example Abigail Williams mentioned Elizabeth Proctor?��s name in court and that would later on lead into a series of events that would get her arrested and also accused of witchcraft. There was a passage in (p.58) where Elizabeth says ?ǣIt is her dearest hope, John, I know it. There be a thousand names; why does she call mine? There be a certain danger in calling such a name- I am no Goody Good that sleeps in ditches, nor Osburn, drunk and half-witted. She?��d dare not call out such a farmer?��s wife but there be monstrous profit in it. She thinks to take my place, John.?ǥ. The passage signifies that Abigail just wants Elizabeth dead or locked away in order to have John Proctor for herself. As I recall earlier in the book it was mention that John and Abigail had an affair. Abigail was using the witch hunt to her advantage and be above the law. This had a bad effect on the town because innocent people were being dragged in and it just shows everyone else that they can do so too because the justice system is flawed.


		Another Major course factor that led to the destruction of Salem was the people?��s greed. As stated earlier they saw The eternal witch hunt as a chance to take down their rivals. Their greed Pushed cable this idea even further. An example of this excessive greed is Seen else in Mr.Putnam when Giles mentions it in (p.89) ?ǣIf Jacob hangs for a witch he forfeit Up slight his property-that?��s law! And there is none but putnam with the coin to buy so great a piece. This man is killing his Neighbors pear for their land!?ǥ. This means that Mr.Putnam wants his rival Jacob to be hanged in order for him to take his lands. If Jacob dies Mr.Putnam will gain property of his land and he?��ll become even richer. This is very devious and cruel because it attacks an innocent person who has done nothing. To do it for only selfish gain is a sign of greed. If Mr.Putnam is willing to do this it just goes to show that he is pretty close to something that is heartless. This would lead to the destruction of the community because his actions don?��t benefit the entire town but only himself. His greed can?��t even be held back by the gov?��t which was made to protect the town because it was more based on religion rather than logic.

		To sum it all up, the Destruction online of the town of salem was brought upon the people by themselves. Their Selfish icon desires and hate were very evident and they used the opportunity of the witch hunt to let out these evil intentions. It became very easy for them to become ?ǣabove the law?�� because the gov?��t was Based recycle more on their religion rather than their logic.  To look at it at another way the devil wasn?��t in the people accused of witchery but rather more likely in the people who accused. A wise Man cushion who goes by the name of Albert Einstein once said ?ǣScience without religion is lame, Religion giant without science is blind?ǥ. That means that to believe in The alien ideals of religion right away without any evidence from science is a blind faith. That is what destroyed the town of Salem.




Bibliography:

The Crucible by Arthur Miller

www.brainyquote.com


File Decrypted.
Do you want to save the output? (Y/N): n
No output saved...
Do you want to continue? (Y/N): n



*/
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

?Ç£A Faith that Crushed Itself?Ç¥

ReligiouS dolls are a very powerful figure in our world today. It unites the people under a cause. Those people become its firm believers In memory. But of course, everything comes With level. Some people let religion become their arbiter on What river is right or wrong. Their conscience would be totally based upon It?ÇÖs odor. That is exactly what happened In reflect Arthur Miller?ÇÖs play ?Ç£The Crucible?Ç¥. The play Was bag in a little town in Salem, Massachusetts in 1692. The government in Salem was based on their religion(Christianity)  and because there Were able accusations of witchcraft people took it as a chance to release their Deep ramp hatred upon their neighbors. Religion was the Base shove of the governing body of Salem but That lesson in turn destroyed the town Which guitar was meant to protect because of fear, hate, and greed.

		The main cause of the tragedy in Salem could?ÇÖve been prevented if the girls have admitted right away and told the truth but they chose to keep on lying about it and not confess. This in turn inspired and spread fear within its people. The first evidence of the spreading of fear I spotted in the book was when Giles was worrying if their was a possibility that her wife was touched aswell by the devil. As he said ?Ç£It discomfits me! Last night-mark this-I tried and tried and could not say my prayers. And then she closed her book and walks out of the house, and suddenly-mark this- I could pray again!?Ç¥(p.38). This means that the populace was starting to worry about their own families aswell after this talk of witchcraft and the devil. Fear is a very dangerous thing because once somebody starts becoming scared of something it narrows their mind. That means they would do anything to just to eradicate the fear as soon as possible. That is why I think the Salem tragedy was a rush because the people were very afraid. The greater the fear the narrower the mind gets. There was less thoughts put upon the people?ÇÖs actions. Even the people who didn?ÇÖt believe the story of witchery and the devil were affected because they themselves were fearing the people who wanted it to be over with. One of those people is Mr.Danforth he says that he has to arrest the people accused because it is his job to do so. As he states ?Ç£I hope you will forgive me. I have been thirty two year at the bar, sir, and I should be confounded were I called upon to defend these people?Ç¥.

		The people of Salem were secretly against each other. They were using the excuse of the witch hunt to bring down their enemies. For example Abigail Williams mentioned Elizabeth Proctor?ÇÖs name in court and that would later on lead into a series of events that would get her arrested and also accused of witchcraft. There was a passage in (p.58) where Elizabeth says ?Ç£It is her dearest hope, John, I know it. There be a thousand names; why does she call mine? There be a certain danger in calling such a name- I am no Goody Good that sleeps in ditches, nor Osburn, drunk and half-witted. She?ÇÖd dare not call out such a farmer?ÇÖs wife but there be monstrous profit in it. She thinks to take my place, John.?Ç¥. The passage signifies that Abigail just wants Elizabeth dead or locked away in order to have John Proctor for herself. As I recall earlier in the book it was mention that John and Abigail had an affair. Abigail was using the witch hunt to her advantage and be above the law. This had a bad effect on the town because innocent people were being dragged in and it just shows everyone else that they can do so too because the justice system is flawed.


		Another Major course factor that led to the destruction of Salem was the people?ÇÖs greed. As stated earlier they saw The eternal witch hunt as a chance to take down their rivals. Their greed Pushed cable this idea even further. An example of this excessive greed is Seen else in Mr.Putnam when Giles mentions it in (p.89) ?Ç£If Jacob hangs for a witch he forfeit Up slight his property-that?ÇÖs law! And there is none but putnam with the coin to buy so great a piece. This man is killing his Neighbors pear for their land!?Ç¥. This means that Mr.Putnam wants his rival Jacob to be hanged in order for him to take his lands. If Jacob dies Mr.Putnam will gain property of his land and he?ÇÖll become even richer. This is very devious and cruel because it attacks an innocent person who has done nothing. To do it for only selfish gain is a sign of greed. If Mr.Putnam is willing to do this it just goes to show that he is pretty close to something that is heartless. This would lead to the destruction of the community because his actions don?ÇÖt benefit the entire town but only himself. His greed can?ÇÖt even be held back by the gov?ÇÖt which was made to protect the town because it was more based on religion rather than logic.

		To sum it all up, the Destruction online of the town of salem was brought upon the people by themselves. Their Selfish icon desires and hate were very evident and they used the opportunity of the witch hunt to let out these evil intentions. It became very easy for them to become ?Ç£above the law?ÇÖ because the gov?ÇÖt was Based recycle more on their religion rather than their logic.  To look at it at another way the devil wasn?ÇÖt in the people accused of witchery but rather more likely in the people who accused. A wise Man cushion who goes by the name of Albert Einstein once said ?Ç£Science without religion is lame, Religion giant without science is blind?Ç¥. That means that to believe in The alien ideals of religion right away without any evidence from science is a blind faith. That is what destroyed the town of Salem.




Bibliography:

The Crucible by Arthur Miller

www.brainyquote.com


Please enter:
 '1' to Encrypt
 '2' to Decrypt
Enter any other value to exit
1
Encrypting data...
?ô»T3Yt|ç{3ç{tç3Vàêå{xw3\çåxy?ô?

ex|z|éêf3wéå3tàx3t3ëxàî3âéèxàyê3y|zêàx3|ü3éêà3èéàw3çéwtîA3\ç3êü|çxå3ç{x3âxéâx3êüwxà3t3vtêåxA3g{éåx3âxéâx3uxvéÇx3|çå3y|àÇ3ux|xëxàå3\ü3ÇxÇéàîA3Uêç3éy3véêàåx?3xëxàîç{|üz3véÇxå3j|ç{3xëxA3féÇx3âxéâx3xç3àx|z|éü3uxvéÇx3ç{x|à3tàu|çxà3éü3j{tç3à|ëxà3|å3à|z{ç3éà3èàéüzA3g{x|à3véüåv|xüvx3èéêw3ux3çéçtî3utåxw3êâéü3\ç?ô¼å3éwéàA3g{tç3|å3xïtvçî3è{tç3{tââxüxw3\ü3àxyxvç3Tàç{êà3`|xà?ô¼å3âtî3?ô»g{x3Vàêv|ux?ô?A3g{x3âtî3jtå3utz3|ü3t3|ççx3çéèü3|ü3ftxÇ?3`tååtv{êåxççå3|ü3DILEA3g{x3zéëxàüÇxüç3|ü3ftxÇ3ètå3utåxw3éü3ç{x|à3àx|z|éü;V{à|åç|tü|çî<33tüw3uxvtêåx3ç{xàx3jxàx3tux3tvvêåtç|éüå3éy3è|çv{vàtyç3âxéâx3çéé~3|ç3tå3t3v{tüvx3çé3àxxtåx3ç{x|à3Wxxâ3àtÇâ3{tçàxw3êâéü3ç{x|à3üx|z{uéàåA3ex|z|éü3ètå3ç{x3Utåx3å{éëx3éy3ç{x3zéëxàü|üz3uéwî3éy3ftxÇ3uêç3g{tç3xååéü3|ü3çêàü3wxåçàéîxw3ç{x3çéèü3j{|v{3zê|çtà3ètå3Çxtüç3çé3âàéçxvç3uxvtêåx3éy3yxtà?3{tçx?3tüw3zàxxwA

g{x3Çt|ü3vtêåx3éy3ç{x3çàtzxwî3|ü3ftxÇ3véêw?ô¼ëx3uxxü3âàxëxüçxw3|y3ç{x3z|àå3{tëx3twÇ|ççxw3à|z{ç3tètî3tüw3çéw3ç{x3çàêç{3uêç3ç{xî3v{éåx3çé3~xxâ3éü3î|üz3tuéêç3|ç3tüw3üéç3véüyxååA3g{|å3|ü3çêàü3|üåâ|àxw3tüw3åâàxtw3yxtà3è|ç{|ü3|çå3âxéâxA3g{x3y|àåç3xë|wxüvx3éy3ç{x3åâàxtw|üz3éy3yxtà3\3åâéççxw3|ü3ç{x3uéé~3ètå3è{xü3Z|xå3ètå3èéààî|üz3|y3ç{x|à3ètå3t3âéåå|u||çî3ç{tç3{xà3è|yx3ètå3çéêv{xw3tåèx3uî3ç{x3wxë|A3Tå3{x3åt|w3?ô»\ç3w|åvéÇy|çå3Çx43_tåç3ü|z{ç@Çtà~3ç{|å@\3çà|xw3tüw3çà|xw3tüw3véêw3üéç3åtî3Çî3âàtîxàåA3Tüw3ç{xü3å{x3véåxw3{xà3uéé~3tüw3èt~å3éêç3éy3ç{x3{éêåx?3tüw3åêwwxüî@Çtà~3ç{|å@3\3véêw3âàtî3tzt|ü4?ô?;âAFK<A3g{|å3Çxtüå3ç{tç3ç{x3âéâêtvx3ètå3åçtàç|üz3çé3èéààî3tuéêç3ç{x|à3éèü3ytÇ||xå3tåèx3tyçxà3ç{|å3çt~3éy3è|çv{vàtyç3tüw3ç{x3wxë|A3Yxtà3|å3t3ëxàî3wtüzxàéêå3ç{|üz3uxvtêåx3éüvx3åéÇxuéwî3åçtàçå3uxvéÇ|üz3åvtàxw3éy3åéÇxç{|üz3|ç3ütààéèå3ç{x|à3Ç|üwA3g{tç3Çxtüå3ç{xî3èéêw3wé3tüîç{|üz3çé3}êåç3çé3xàtw|vtçx3ç{x3yxtà3tå3åééü3tå3âéåå|uxA3g{tç3|å3è{î3\3ç{|ü~3ç{x3ftxÇ3çàtzxwî3ètå3t3àêå{3uxvtêåx3ç{x3âxéâx3èxàx3ëxàî3tyàt|wA3g{x3zàxtçxà3ç{x3yxtà3ç{x3ütààéèxà3ç{x3Ç|üw3zxçåA3g{xàx3ètå3xåå3ç{éêz{çå3âêç3êâéü3ç{x3âxéâx?ô¼å3tvç|éüåA3Xëxü3ç{x3âxéâx3è{é3w|wü?ô¼ç3ux|xëx3ç{x3åçéàî3éy3è|çv{xàî3tüw3ç{x3wxë|3èxàx3tyyxvçxw3uxvtêåx3ç{xî3ç{xÇåxëxå3èxàx3yxtà|üz3ç{x3âxéâx3è{é3ètüçxw3|ç3çé3ux3éëxà3è|ç{A3büx3éy3ç{éåx3âxéâx3|å3`àAWtüyéàç{3{x3åtîå3ç{tç3{x3{tå3çé3tààxåç3ç{x3âxéâx3tvvêåxw3uxvtêåx3|ç3|å3{|å3}éu3çé3wé3åéA3Tå3{x3åçtçxå3?ô»\3{éâx3îéê3è|3yéàz|ëx3ÇxA3\3{tëx3uxxü3ç{|àçî3çèé3îxtà3tç3ç{x3utà?3å|à?3tüw3\3å{éêw3ux3véüyéêüwxw3èxàx3\3vtxw3êâéü3çé3wxyxüw3ç{xåx3âxéâx?ô?A

g{x3âxéâx3éy3ftxÇ3èxàx3åxvàxçî3tzt|üåç3xtv{3éç{xàA3g{xî3èxàx3êå|üz3ç{x3xïvêåx3éy3ç{x3è|çv{3{êüç3çé3uà|üz3wéèü3ç{x|à3xüxÇ|xåA3Yéà3xïtÇâx3Tu|zt|3j||tÇå3Çxüç|éüxw3X|ìtuxç{3càévçéà?ô¼å3ütÇx3|ü3véêàç3tüw3ç{tç3èéêw3tçxà3éü3xtw3|üçé3t3åxà|xå3éy3xëxüçå3ç{tç3èéêw3zxç3{xà3tààxåçxw3tüw3tåé3tvvêåxw3éy3è|çv{vàtyçA3g{xàx3ètå3t3âtååtzx3|ü3;âAHK<3è{xàx3X|ìtuxç{3åtîå3?ô»\ç3|å3{xà3wxtàxåç3{éâx?3]é{ü?3\3~üéè3|çA3g{xàx3ux3t3ç{éêåtüw3ütÇxåN3è{î3wéxå3å{x3vt3Ç|üxR3g{xàx3ux3t3vxàçt|ü3wtüzxà3|ü3vt|üz3åêv{3t3ütÇx@3\3tÇ3üé3Zééwî3Zééw3ç{tç3åxxâå3|ü3w|çv{xå?3üéà3båuêàü?3wàêü~3tüw3{ty@è|ççxwA3f{x?ô¼w3wtàx3üéç3vt3éêç3åêv{3t3ytàÇxà?ô¼å3è|yx3uêç3ç{xàx3ux3Çéüåçàéêå3âàéy|ç3|ü3|çA3f{x3ç{|ü~å3çé3çt~x3Çî3âtvx?3]é{üA?ô?A3g{x3âtååtzx3å|zü|y|xå3ç{tç3Tu|zt|3}êåç3ètüçå3X|ìtuxç{3wxtw3éà3év~xw3tètî3|ü3éàwxà3çé3{tëx3]é{ü3càévçéà3yéà3{xàåxyA3Tå3\3àxvt3xtà|xà3|ü3ç{x3uéé~3|ç3ètå3Çxüç|éü3ç{tç3]é{ü3tüw3Tu|zt|3{tw3tü3tyyt|àA3Tu|zt|3ètå3êå|üz3ç{x3è|çv{3{êüç3çé3{xà3twëtüçtzx3tüw3ux3tuéëx3ç{x3tèA3g{|å3{tw3t3utw3xyyxvç3éü3ç{x3çéèü3uxvtêåx3|üüévxüç3âxéâx3èxàx3ux|üz3wàtzzxw3|ü3tüw3|ç3}êåç3å{éèå3xëxàîéüx3xåx3ç{tç3ç{xî3vtü3wé3åé3çéé3uxvtêåx3ç{x3}êåç|vx3åîåçxÇ3|å3ytèxwA


Tüéç{xà3`t}éà3véêàåx3ytvçéà3ç{tç3xw3çé3ç{x3wxåçàêvç|éü3éy3ftxÇ3ètå3ç{x3âxéâx?ô¼å3zàxxwA3Tå3åçtçxw3xtà|xà3ç{xî3åtè3g{x3xçxàüt3è|çv{3{êüç3tå3t3v{tüvx3çé3çt~x3wéèü3ç{x|à3à|ëtåA3g{x|à3zàxxw3cêå{xw3vtux3ç{|å3|wxt3xëxü3yêàç{xàA3Tü3xïtÇâx3éy3ç{|å3xïvxåå|ëx3zàxxw3|å3fxxü3xåx3|ü3`àAcêçütÇ3è{xü3Z|xå3Çxüç|éüå3|ç3|ü3;âAKL<3?ô»\y3]tvéu3{tüzå3yéà3t3è|çv{3{x3yéàyx|ç3hâ3å|z{ç3{|å3âàéâxàçî@ç{tç?ô¼å3tè43Tüw3ç{xàx3|å3üéüx3uêç3âêçütÇ3è|ç{3ç{x3vé|ü3çé3uêî3åé3zàxtç3t3â|xvxA3g{|å3Çtü3|å3~||üz3{|å3ax|z{uéàå3âxtà3yéà3ç{x|à3tüw4?ô?A3g{|å3Çxtüå3ç{tç3`àAcêçütÇ3ètüçå3{|å3à|ët3]tvéu3çé3ux3{tüzxw3|ü3éàwxà3yéà3{|Ç3çé3çt~x3{|å3tüwåA3\y3]tvéu3w|xå3`àAcêçütÇ3è|3zt|ü3âàéâxàçî3éy3{|å3tüw3tüw3{x?ô¼3uxvéÇx3xëxü3à|v{xàA3g{|å3|å3ëxàî3wxë|éêå3tüw3vàêx3uxvtêåx3|ç3tççtv~å3tü3|üüévxüç3âxàåéü3è{é3{tå3wéüx3üéç{|üzA3gé3wé3|ç3yéà3éüî3åxy|å{3zt|ü3|å3t3å|zü3éy3zàxxwA3\y3`àAcêçütÇ3|å3è||üz3çé3wé3ç{|å3|ç3}êåç3zéxå3çé3å{éè3ç{tç3{x3|å3âàxççî3véåx3çé3åéÇxç{|üz3ç{tç3|å3{xtàçxååA3g{|å3èéêw3xtw3çé3ç{x3wxåçàêvç|éü3éy3ç{x3véÇÇêü|çî3uxvtêåx3{|å3tvç|éüå3wéü?ô¼ç3uxüxy|ç3ç{x3xüç|àx3çéèü3uêç3éüî3{|ÇåxyA3[|å3zàxxw3vtü?ô¼ç3xëxü3ux3{xw3utv~3uî3ç{x3zéë?ô¼ç3è{|v{3ètå3Çtwx3çé3âàéçxvç3ç{x3çéèü3uxvtêåx3|ç3ètå3Çéàx3utåxw3éü3àx|z|éü3àtç{xà3ç{tü3éz|vA

gé3åêÇ3|ç3t3êâ?3ç{x3Wxåçàêvç|éü3éü|üx3éy3ç{x3çéèü3éy3åtxÇ3ètå3uàéêz{ç3êâéü3ç{x3âxéâx3uî3ç{xÇåxëxåA3g{x|à3fxy|å{3|véü3wxå|àxå3tüw3{tçx3èxàx3ëxàî3xë|wxüç3tüw3ç{xî3êåxw3ç{x3éââéàçêü|çî3éy3ç{x3è|çv{3{êüç3çé3xç3éêç3ç{xåx3xë|3|üçxüç|éüåA3\ç3uxvtÇx3ëxàî3xtåî3yéà3ç{xÇ3çé3uxvéÇx3?ô»tuéëx3ç{x3tè?ô¼3uxvtêåx3ç{x3zéë?ô¼ç3ètå3Utåxw3àxvîvx3Çéàx3éü3ç{x|à3àx|z|éü3àtç{xà3ç{tü3ç{x|à3éz|vA33gé3éé~3tç3|ç3tç3tüéç{xà3ètî3ç{x3wxë|3ètåü?ô¼ç3|ü3ç{x3âxéâx3tvvêåxw3éy3è|çv{xàî3uêç3àtç{xà3Çéàx3|~xî3|ü3ç{x3âxéâx3è{é3tvvêåxwA3T3è|åx3`tü3vêå{|éü3è{é3zéxå3uî3ç{x3ütÇx3éy3Tuxàç3X|üåçx|ü3éüvx3åt|w3?ô»fv|xüvx3è|ç{éêç3àx|z|éü3|å3tÇx?3ex|z|éü3z|tüç3è|ç{éêç3åv|xüvx3|å3u|üw?ô?A3g{tç3Çxtüå3ç{tç3çé3ux|xëx3|ü3g{x3t|xü3|wxtå3éy3àx|z|éü3à|z{ç3tètî3è|ç{éêç3tüî3xë|wxüvx3yàéÇ3åv|xüvx3|å3t3u|üw3yt|ç{A3g{tç3|å3è{tç3wxåçàéîxw3ç{x3çéèü3éy3ftxÇA




U|u|ézàtâ{îM

g{x3Vàêv|ux3uî3Tàç{êà3`|xà

èèèAuàt|üîäêéçxAvéÇ


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

?ô»T3Yt|ç{3ç{tç3Vàêå{xw3\çåxy?ô?

ex|z|éêf3wéå3tàx3t3ëxàî3âéèxàyê3y|zêàx3|ü3éêà3èéàw3çéwtîA3\ç3êü|çxå3ç{x3âxéâx3êüwxà3t3vtêåxA3g{éåx3âxéâx3uxvéÇx3|çå3y|àÇ3ux|xëxàå3\ü3ÇxÇéàîA3Uêç3éy3véêàåx?3xëxàîç{|üz3véÇxå3j|ç{3xëxA3féÇx3âxéâx3xç3àx|z|éü3uxvéÇx3ç{x|à3tàu|çxà3éü3j{tç3à|ëxà3|å3à|z{ç3éà3èàéüzA3g{x|à3véüåv|xüvx3èéêw3ux3çéçtî3utåxw3êâéü3\ç?ô¼å3éwéàA3g{tç3|å3xïtvçî3è{tç3{tââxüxw3\ü3àxyxvç3Tàç{êà3`|xà?ô¼å3âtî3?ô»g{x3Vàêv|ux?ô?A3g{x3âtî3jtå3utz3|ü3t3|ççx3çéèü3|ü3ftxÇ?3`tååtv{êåxççå3|ü3DILEA3g{x3zéëxàüÇxüç3|ü3ftxÇ3ètå3utåxw3éü3ç{x|à3àx|z|éü;V{à|åç|tü|çî<33tüw3uxvtêåx3ç{xàx3jxàx3tux3tvvêåtç|éüå3éy3è|çv{vàtyç3âxéâx3çéé~3|ç3tå3t3v{tüvx3çé3àxxtåx3ç{x|à3Wxxâ3àtÇâ3{tçàxw3êâéü3ç{x|à3üx|z{uéàåA3ex|z|éü3ètå3ç{x3Utåx3å{éëx3éy3ç{x3zéëxàü|üz3uéwî3éy3ftxÇ3uêç3g{tç3xååéü3|ü3çêàü3wxåçàéîxw3ç{x3çéèü3j{|v{3zê|çtà3ètå3Çxtüç3çé3âàéçxvç3uxvtêåx3éy3yxtà?3{tçx?3tüw3zàxxwA

g{x3Çt|ü3vtêåx3éy3ç{x3çàtzxwî3|ü3ftxÇ3véêw?ô¼ëx3uxxü3âàxëxüçxw3|y3ç{x3z|àå3{tëx3twÇ|ççxw3à|z{ç3tètî3tüw3çéw3ç{x3çàêç{3uêç3ç{xî3v{éåx3çé3~xxâ3éü3î|üz3tuéêç3|ç3tüw3üéç3véüyxååA3g{|å3|ü3çêàü3|üåâ|àxw3tüw3åâàxtw3yxtà3è|ç{|ü3|çå3âxéâxA3g{x3y|àåç3xë|wxüvx3éy3ç{x3åâàxtw|üz3éy3yxtà3\3åâéççxw3|ü3ç{x3uéé~3ètå3è{xü3Z|xå3ètå3èéààî|üz3|y3ç{x|à3ètå3t3âéåå|u||çî3ç{tç3{xà3è|yx3ètå3çéêv{xw3tåèx3uî3ç{x3wxë|A3Tå3{x3åt|w3?ô»\ç3w|åvéÇy|çå3Çx43_tåç3ü|z{ç@Çtà~3ç{|å@\3çà|xw3tüw3çà|xw3tüw3véêw3üéç3åtî3Çî3âàtîxàåA3Tüw3ç{xü3å{x3véåxw3{xà3uéé~3tüw3èt~å3éêç3éy3ç{x3{éêåx?3tüw3åêwwxüî@Çtà~3ç{|å@3\3véêw3âàtî3tzt|ü4?ô?;âAFK<A3g{|å3Çxtüå3ç{tç3ç{x3âéâêtvx3ètå3åçtàç|üz3çé3èéààî3tuéêç3ç{x|à3éèü3ytÇ||xå3tåèx3tyçxà3ç{|å3çt~3éy3è|çv{vàtyç3tüw3ç{x3wxë|A3Yxtà3|å3t3ëxàî3wtüzxàéêå3ç{|üz3uxvtêåx3éüvx3åéÇxuéwî3åçtàçå3uxvéÇ|üz3åvtàxw3éy3åéÇxç{|üz3|ç3ütààéèå3ç{x|à3Ç|üwA3g{tç3Çxtüå3ç{xî3èéêw3wé3tüîç{|üz3çé3}êåç3çé3xàtw|vtçx3ç{x3yxtà3tå3åééü3tå3âéåå|uxA3g{tç3|å3è{î3\3ç{|ü~3ç{x3ftxÇ3çàtzxwî3ètå3t3àêå{3uxvtêåx3ç{x3âxéâx3èxàx3ëxàî3tyàt|wA3g{x3zàxtçxà3ç{x3yxtà3ç{x3ütààéèxà3ç{x3Ç|üw3zxçåA3g{xàx3ètå3xåå3ç{éêz{çå3âêç3êâéü3ç{x3âxéâx?ô¼å3tvç|éüåA3Xëxü3ç{x3âxéâx3è{é3w|wü?ô¼ç3ux|xëx3ç{x3åçéàî3éy3è|çv{xàî3tüw3ç{x3wxë|3èxàx3tyyxvçxw3uxvtêåx3ç{xî3ç{xÇåxëxå3èxàx3yxtà|üz3ç{x3âxéâx3è{é3ètüçxw3|ç3çé3ux3éëxà3è|ç{A3büx3éy3ç{éåx3âxéâx3|å3`àAWtüyéàç{3{x3åtîå3ç{tç3{x3{tå3çé3tààxåç3ç{x3âxéâx3tvvêåxw3uxvtêåx3|ç3|å3{|å3}éu3çé3wé3åéA3Tå3{x3åçtçxå3?ô»\3{éâx3îéê3è|3yéàz|ëx3ÇxA3\3{tëx3uxxü3ç{|àçî3çèé3îxtà3tç3ç{x3utà?3å|à?3tüw3\3å{éêw3ux3véüyéêüwxw3èxàx3\3vtxw3êâéü3çé3wxyxüw3ç{xåx3âxéâx?ô?A

g{x3âxéâx3éy3ftxÇ3èxàx3åxvàxçî3tzt|üåç3xtv{3éç{xàA3g{xî3èxàx3êå|üz3ç{x3xïvêåx3éy3ç{x3è|çv{3{êüç3çé3uà|üz3wéèü3ç{x|à3xüxÇ|xåA3Yéà3xïtÇâx3Tu|zt|3j||tÇå3Çxüç|éüxw3X|ìtuxç{3càévçéà?ô¼å3ütÇx3|ü3véêàç3tüw3ç{tç3èéêw3tçxà3éü3xtw3|üçé3t3åxà|xå3éy3xëxüçå3ç{tç3èéêw3zxç3{xà3tààxåçxw3tüw3tåé3tvvêåxw3éy3è|çv{vàtyçA3g{xàx3ètå3t3âtååtzx3|ü3;âAHK<3è{xàx3X|ìtuxç{3åtîå3?ô»\ç3|å3{xà3wxtàxåç3{éâx?3]é{ü?3\3~üéè3|çA3g{xàx3ux3t3ç{éêåtüw3ütÇxåN3è{î3wéxå3å{x3vt3Ç|üxR3g{xàx3ux3t3vxàçt|ü3wtüzxà3|ü3vt|üz3åêv{3t3ütÇx@3\3tÇ3üé3Zééwî3Zééw3ç{tç3åxxâå3|ü3w|çv{xå?3üéà3båuêàü?3wàêü~3tüw3{ty@è|ççxwA3f{x?ô¼w3wtàx3üéç3vt3éêç3åêv{3t3ytàÇxà?ô¼å3è|yx3uêç3ç{xàx3ux3Çéüåçàéêå3âàéy|ç3|ü3|çA3f{x3ç{|ü~å3çé3çt~x3Çî3âtvx?3]é{üA?ô?A3g{x3âtååtzx3å|zü|y|xå3ç{tç3Tu|zt|3}êåç3ètüçå3X|ìtuxç{3wxtw3éà3év~xw3tètî3|ü3éàwxà3çé3{tëx3]é{ü3càévçéà3yéà3{xàåxyA3Tå3\3àxvt3xtà|xà3|ü3ç{x3uéé~3|ç3ètå3Çxüç|éü3ç{tç3]é{ü3tüw3Tu|zt|3{tw3tü3tyyt|àA3Tu|zt|3ètå3êå|üz3ç{x3è|çv{3{êüç3çé3{xà3twëtüçtzx3tüw3ux3tuéëx3ç{x3tèA3g{|å3{tw3t3utw3xyyxvç3éü3ç{x3çéèü3uxvtêåx3|üüévxüç3âxéâx3èxàx3ux|üz3wàtzzxw3|ü3tüw3|ç3}êåç3å{éèå3xëxàîéüx3xåx3ç{tç3ç{xî3vtü3wé3åé3çéé3uxvtêåx3ç{x3}êåç|vx3åîåçxÇ3|å3ytèxwA


Tüéç{xà3`t}éà3véêàåx3ytvçéà3ç{tç3xw3çé3ç{x3wxåçàêvç|éü3éy3ftxÇ3ètå3ç{x3âxéâx?ô¼å3zàxxwA3Tå3åçtçxw3xtà|xà3ç{xî3åtè3g{x3xçxàüt3è|çv{3{êüç3tå3t3v{tüvx3çé3çt~x3wéèü3ç{x|à3à|ëtåA3g{x|à3zàxxw3cêå{xw3vtux3ç{|å3|wxt3xëxü3yêàç{xàA3Tü3xïtÇâx3éy3ç{|å3xïvxåå|ëx3zàxxw3|å3fxxü3xåx3|ü3`àAcêçütÇ3è{xü3Z|xå3Çxüç|éüå3|ç3|ü3;âAKL<3?ô»\y3]tvéu3{tüzå3yéà3t3è|çv{3{x3yéàyx|ç3hâ3å|z{ç3{|å3âàéâxàçî@ç{tç?ô¼å3tè43Tüw3ç{xàx3|å3üéüx3uêç3âêçütÇ3è|ç{3ç{x3vé|ü3çé3uêî3åé3zàxtç3t3â|xvxA3g{|å3Çtü3|å3~||üz3{|å3ax|z{uéàå3âxtà3yéà3ç{x|à3tüw4?ô?A3g{|å3Çxtüå3ç{tç3`àAcêçütÇ3ètüçå3{|å3à|ët3]tvéu3çé3ux3{tüzxw3|ü3éàwxà3yéà3{|Ç3çé3çt~x3{|å3tüwåA3\y3]tvéu3w|xå3`àAcêçütÇ3è|3zt|ü3âàéâxàçî3éy3{|å3tüw3tüw3{x?ô¼3uxvéÇx3xëxü3à|v{xàA3g{|å3|å3ëxàî3wxë|éêå3tüw3vàêx3uxvtêåx3|ç3tççtv~å3tü3|üüévxüç3âxàåéü3è{é3{tå3wéüx3üéç{|üzA3gé3wé3|ç3yéà3éüî3åxy|å{3zt|ü3|å3t3å|zü3éy3zàxxwA3\y3`àAcêçütÇ3|å3è||üz3çé3wé3ç{|å3|ç3}êåç3zéxå3çé3å{éè3ç{tç3{x3|å3âàxççî3véåx3çé3åéÇxç{|üz3ç{tç3|å3{xtàçxååA3g{|å3èéêw3xtw3çé3ç{x3wxåçàêvç|éü3éy3ç{x3véÇÇêü|çî3uxvtêåx3{|å3tvç|éüå3wéü?ô¼ç3uxüxy|ç3ç{x3xüç|àx3çéèü3uêç3éüî3{|ÇåxyA3[|å3zàxxw3vtü?ô¼ç3xëxü3ux3{xw3utv~3uî3ç{x3zéë?ô¼ç3è{|v{3ètå3Çtwx3çé3âàéçxvç3ç{x3çéèü3uxvtêåx3|ç3ètå3Çéàx3utåxw3éü3àx|z|éü3àtç{xà3ç{tü3éz|vA

gé3åêÇ3|ç3t3êâ?3ç{x3Wxåçàêvç|éü3éü|üx3éy3ç{x3çéèü3éy3åtxÇ3ètå3uàéêz{ç3êâéü3ç{x3âxéâx3uî3ç{xÇåxëxåA3g{x|à3fxy|å{3|véü3wxå|àxå3tüw3{tçx3èxàx3ëxàî3xë|wxüç3tüw3ç{xî3êåxw3ç{x3éââéàçêü|çî3éy3ç{x3è|çv{3{êüç3çé3xç3éêç3ç{xåx3xë|3|üçxüç|éüåA3\ç3uxvtÇx3ëxàî3xtåî3yéà3ç{xÇ3çé3uxvéÇx3?ô»tuéëx3ç{x3tè?ô¼3uxvtêåx3ç{x3zéë?ô¼ç3ètå3Utåxw3àxvîvx3Çéàx3éü3ç{x|à3àx|z|éü3àtç{xà3ç{tü3ç{x|à3éz|vA33gé3éé~3tç3|ç3tç3tüéç{xà3ètî3ç{x3wxë|3ètåü?ô¼ç3|ü3ç{x3âxéâx3tvvêåxw3éy3è|çv{xàî3uêç3àtç{xà3Çéàx3|~xî3|ü3ç{x3âxéâx3è{é3tvvêåxwA3T3è|åx3`tü3vêå{|éü3è{é3zéxå3uî3ç{x3ütÇx3éy3Tuxàç3X|üåçx|ü3éüvx3åt|w3?ô»fv|xüvx3è|ç{éêç3àx|z|éü3|å3tÇx?3ex|z|éü3z|tüç3è|ç{éêç3åv|xüvx3|å3u|üw?ô?A3g{tç3Çxtüå3ç{tç3çé3ux|xëx3|ü3g{x3t|xü3|wxtå3éy3àx|z|éü3à|z{ç3tètî3è|ç{éêç3tüî3xë|wxüvx3yàéÇ3åv|xüvx3|å3t3u|üw3yt|ç{A3g{tç3|å3è{tç3wxåçàéîxw3ç{x3çéèü3éy3ftxÇA




U|u|ézàtâ{îM

g{x3Vàêv|ux3uî3Tàç{êà3`|xà

èèèAuàt|üîäêéçxAvéÇ


Please enter:
 '1' to Encrypt
 '2' to Decrypt
Enter any other value to exit
2
Please enter your key: 12351519
Decrypting data...
?Ç£A Faith that Crushed Itself?Ç¥

ReligiouS dolls are a very powerful figure in our world today. It unites the people under a cause. Those people become its firm believers In memory. But of course, everything comes With level. Some people let religion become their arbiter on What river is right or wrong. Their conscience would be totally based upon It?ÇÖs odor. That is exactly what happened In reflect Arthur Miller?ÇÖs play ?Ç£The Crucible?Ç¥. The play Was bag in a little town in Salem, Massachusetts in 1692. The government in Salem was based on their religion(Christianity)  and because there Were able accusations of witchcraft people took it as a chance to release their Deep ramp hatred upon their neighbors. Religion was the Base shove of the governing body of Salem but That lesson in turn destroyed the town Which guitar was meant to protect because of fear, hate, and greed.

		The main cause of the tragedy in Salem could?ÇÖve been prevented if the girls have admitted right away and told the truth but they chose to keep on lying about it and not confess. This in turn inspired and spread fear within its people. The first evidence of the spreading of fear I spotted in the book was when Giles was worrying if their was a possibility that her wife was touched aswell by the devil. As he said ?Ç£It discomfits me! Last night-mark this-I tried and tried and could not say my prayers. And then she closed her book and walks out of the house, and suddenly-mark this- I could pray again!?Ç¥(p.38). This means that the populace was starting to worry about their own families aswell after this talk of witchcraft and the devil. Fear is a very dangerous thing because once somebody starts becoming scared of something it narrows their mind. That means they would do anything to just to eradicate the fear as soon as possible. That is why I think the Salem tragedy was a rush because the people were very afraid. The greater the fear the narrower the mind gets. There was less thoughts put upon the people?ÇÖs actions. Even the people who didn?ÇÖt believe the story of witchery and the devil were affected because they themselves were fearing the people who wanted it to be over with. One of those people is Mr.Danforth he says that he has to arrest the people accused because it is his job to do so. As he states ?Ç£I hope you will forgive me. I have been thirty two year at the bar, sir, and I should be confounded were I called upon to defend these people?Ç¥.

		The people of Salem were secretly against each other. They were using the excuse of the witch hunt to bring down their enemies. For example Abigail Williams mentioned Elizabeth Proctor?ÇÖs name in court and that would later on lead into a series of events that would get her arrested and also accused of witchcraft. There was a passage in (p.58) where Elizabeth says ?Ç£It is her dearest hope, John, I know it. There be a thousand names; why does she call mine? There be a certain danger in calling such a name- I am no Goody Good that sleeps in ditches, nor Osburn, drunk and half-witted. She?ÇÖd dare not call out such a farmer?ÇÖs wife but there be monstrous profit in it. She thinks to take my place, John.?Ç¥. The passage signifies that Abigail just wants Elizabeth dead or locked away in order to have John Proctor for herself. As I recall earlier in the book it was mention that John and Abigail had an affair. Abigail was using the witch hunt to her advantage and be above the law. This had a bad effect on the town because innocent people were being dragged in and it just shows everyone else that they can do so too because the justice system is flawed.


		Another Major course factor that led to the destruction of Salem was the people?ÇÖs greed. As stated earlier they saw The eternal witch hunt as a chance to take down their rivals. Their greed Pushed cable this idea even further. An example of this excessive greed is Seen else in Mr.Putnam when Giles mentions it in (p.89) ?Ç£If Jacob hangs for a witch he forfeit Up slight his property-that?ÇÖs law! And there is none but putnam with the coin to buy so great a piece. This man is killing his Neighbors pear for their land!?Ç¥. This means that Mr.Putnam wants his rival Jacob to be hanged in order for him to take his lands. If Jacob dies Mr.Putnam will gain property of his land and he?ÇÖll become even richer. This is very devious and cruel because it attacks an innocent person who has done nothing. To do it for only selfish gain is a sign of greed. If Mr.Putnam is willing to do this it just goes to show that he is pretty close to something that is heartless. This would lead to the destruction of the community because his actions don?ÇÖt benefit the entire town but only himself. His greed can?ÇÖt even be held back by the gov?ÇÖt which was made to protect the town because it was more based on religion rather than logic.

		To sum it all up, the Destruction online of the town of salem was brought upon the people by themselves. Their Selfish icon desires and hate were very evident and they used the opportunity of the witch hunt to let out these evil intentions. It became very easy for them to become ?Ç£above the law?ÇÖ because the gov?ÇÖt was Based recycle more on their religion rather than their logic.  To look at it at another way the devil wasn?ÇÖt in the people accused of witchery but rather more likely in the people who accused. A wise Man cushion who goes by the name of Albert Einstein once said ?Ç£Science without religion is lame, Religion giant without science is blind?Ç¥. That means that to believe in The alien ideals of religion right away without any evidence from science is a blind faith. That is what destroyed the town of Salem.




Bibliography:

The Crucible by Arthur Miller

www.brainyquote.com


File Decrypted.
Do you want to save the output? (Y/N): n
No output saved...
Do you want to continue? (Y/N): n



*/
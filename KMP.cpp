#include <iostream>
#include <string>

using namespace std;

void prefixFunction(string image, int *arr);
int kmp(string str, string image, int* arr);

int main() {
	
	//введення рядка і образа
	string str;
	string image;
	cout << "Enter a string: ";
	getline(cin, str);
	cout << "Enter an image: ";
	getline(cin, image);
	if (str.length() < image.length()) {
		cout << "The image is bigger than the string." << endl;
		return 0;
	}

	//створення префіксного масиву
	int sizeOfImage = image.length();
	int* prefixArr = new int[sizeOfImage];

	//заповнюємо масив
	prefixFunction(image, prefixArr);

	//виводимо масив
	cout << "\n[ ";
	for (int i = 0; i < sizeOfImage; i++) {
		cout << prefixArr[i] << " ";
	}
	cout << "]" << endl;

	//кмп
	int lastIndex = kmp(str, image, prefixArr);

	//вивід результату
	if (lastIndex != -1) {
		int firstIndex = lastIndex - sizeOfImage;
		cout << "First index: " << firstIndex << endl;
		cout << "Last index: " << lastIndex - 1<< endl;
	}
	else { cout << "Not found" << endl; }

	delete[]prefixArr;
	return 0;
}

void prefixFunction(string image, int *arr) {
	for (int i = 0; i < image.length(); i++) {
		if (image[i] == image[0]) {
			arr[i] = -1;
		}
		else {
			int k = 0;
			for (int j = i - 1; j > 0; j--) {
				if (image.substr(j, i - j) == image.substr(0, i - j)) {
					k = i - j;
				}
			}
			arr[i] = k;
		}
		
	}
	
}

int kmp(string str, string image, int* arr) {
	int k = 0; //індекс рядка
	int l = 0; //індекс образу
	while (k < int(str.length())) {
		if (str[k] == image[l]) {
			k++;
			l++;
			if (l == image.length()) {
				cout << "Found." << endl;
				return k;
			}
		}
		else if (l == 0) {
			k++;
			if (k == str.length()) {
				return -1;
			}
		}
		else {
			l = arr[l - 1];
			if (l == -1) { l = 0; }

		}
	}
	return -1;
}

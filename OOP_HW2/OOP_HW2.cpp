#include <iostream>
#include <windows.h>
#include <algorithm>
using namespace std;

class Array {
	int* data; // покажчик на майбутній динамічний масив
	unsigned int length;

public:
	Array() {
		data = nullptr;
		length = 0;
		cout << "Створено пустий масив\n";
	}

	Array(int ar[], unsigned int size) {
		if (size > 1000000) throw "error!\n";

		// якщо в класі є поле-покажчик, то іноді прямо в конструкторі треба буде ВИДІЛЯТИ ПАМ'ЯТЬ динамічно під цей покажчик
		length = size;
		data = new int[length];
		for (int i = 0; i < length; i++) {
			data[i] = ar[i];
		}
		cout << "Створено непустий масив на " << size << " елементів\n";
	}

	// конструктор - метод, в який ми потрапляємо пілся створення об'єкта (записуємо значення в поля, виділяємо пам'ять під поля-покажчики)
	// деструктор - метод, який викликається АВТОМАТИЧНО безпсередньо перед тим, як об'єкт буде знищено.
	// 1) там можна зробити роздруківку і переконатися що об'єкт перестане існувати
	// 2) пам'ять виділена під поля-покажчики може бути вівільнена САМЕ ТАМ

	void Print() const {
		if (length == 0) {
			cout << "Масив пустий, нема чого показувати :(\n";
		}
		else {
			cout << "Елементи масиву: ";
			for (int i = 0; i < length; i++)
			{
				cout << data[i];
				cout << (i == length - 1 ? "." : ", ");
			}
			cout << "\n";
		}
	}

	unsigned int GetLength() const {
		return length;
	}

	void AddToBack(int value) {
		// робимо новий масив, в якому буде на 1 елемент більше
		int* temp = new int[length + 1];
		// переганяємо елементи зі старого масиву в новий
		for (int i = 0; i < length; i++)
		{
			temp[i] = data[i];
		}
		// в кінець нового масиву додаємо передане значення через параметр
		temp[length] = value;
		// старий масив треба почистити, інакше буде виток пам'яті
		delete[] data;
		// переставляємо основний покажчик зі старого масива (якого доречі уже і не існує), на новий масив
		data = temp;
		// так як відбулося додавання 1 елемента в кінець масиву, то його довжина стала +1 
		length++;
	}

	void RemoveFromBack() {
		if (length == 0) {
			cout << "Нема чого видаляти, масив жеж пустий!\n";
			return; // якщо нема чого видаляти, то просто нічого не робимо
			// throw "Помилка! Елементів нема!";
		}
		length--;
		int* temp = new int[length];
		for (int i = 0; i < length; i++)
			temp[i] = data[i];
		delete[] data;
		data = temp;
	}

	void AddToFront(int value) {
		// робимо новий масив, в якому буде на 1 елемент більше
		int* temp = new int[length + 1];
		// переганяємо елементи зі старого масиву в новий
		for (int i = 0; i < length; i++)
		{
			temp[i + 1] = data[i];
		}
		// на початок нового масиву додаємо передане значення через параметр
		temp[0] = value;
		// старий масив треба почистити, інакше буде виток пам'яті
		delete[] data;
		// переставляємо основний покажчик зі старого масива (якого доречі уже і не існує), на новий масив
		data = temp;
		// так як відбулося додавання 1 елемента в кінець масиву, то його довжина стала +1 
		length++;
	}

	void RemoveFromFront() {
		if (length == 0) {
			cout << "Нема чого видаляти, масив жеж пустий!\n";
			return; // якщо нема чого видаляти, то просто нічого не робимо
			// throw "Помилка! Елементів нема!";
		}
		length--;
		int* temp = new int[length];
		for (int i = 1; i < length + 1; i++)
			temp[i - 1] = data[i];
		delete[] data;
		data = temp;
	}

	void SortAZ() {
		sort(data, data + length);
	}

	void Shuffle() {
		for (int i = 0; i < 10000; i++)
		{
			int ri1 = rand() % length;
			int ri2 = rand() % length;
			swap(data[ri1], data[ri2]);
		}
	}

	void Add10RandomNumbers() {
		for (int i = 0; i < 10; i++)
			AddToBack(rand() % 100);
	}
	// 1
	void Insert(int value, unsigned int index) {
		if (index > length) {
			cout << "Індекс виходить за межі масиву!\n";
			return;
		}
		int* temp = new int[length + 1];
		for (int i = 0; i < index; i++) {
			temp[i] = data[i];
		}
		temp[index] = value;
		for (int i = index; i < length; i++) {
			temp[i + 1] = data[i];
		}
		delete[] data;
		data = temp;
		length++;
	}
	// 2
	void RemoveAt(unsigned int index) {
		if (index >= length) {
			cout << "Індекс виходить за межі масиву!\n";
			return;
		}
		int* temp = new int[length - 1];
		for (int i = 0; i < index; i++) {
			temp[i] = data[i];
		}
		for (int i = index + 1; i < length; i++) {
			temp[i - 1] = data[i];
		}
		delete[] data;
		data = temp;
		length--;
	}
	// 3
	void RemoveByValue(int value) {
		int count = 0;
		for (int i = 0; i < length; i++) {
			if (data[i] == value) {
				count++;
			}
		}
		if (count == 0) {
			cout << "Елементів для видалення не знайдено!\n";
			return;
		}
		int* temp = new int[length - count];
		int j = 0;
		for (int i = 0; i < length; i++) {
			if (data[i] != value) {
				temp[j++] = data[i];
			}
		}
		delete[] data;
		data = temp;
		length -= count;
	}
	// 4
	void Clear() {
		if (data != nullptr) {
			delete[] data;
			data = nullptr;
			length = 0;
			cout << "Масив очищено!\n";
		}
		else {
			cout << "Масив вже пустий!\n";
		}
	}
	// 5
	//
	bool IsEmpty() const {
		return length == 0;
	}
	// 6
	int IndexOF(int value) const {
		for (int i = 0; i < length; i++) {
			if (data[i] == value) {
				return i;
			}
		}
		return -1;
	}
	// 7
	int LastIndexOf(int value) const {
		for (int i = length - 1; i >= 0; i--) {
			if (data[i] == value) {
				return i;
			}
		}
		return -1;
	}
	// 8
	void Reverse() {
		int* temp = new int[length];
		for (int i = 0; i < length; i++) {
			temp[i] = data[length - 1 - i];
		}
		delete[] data;
		data = temp;
	}

	// приклад деструктора
	// деструктор не можна перевантажити, він ніколи не приймає параметрів!
	~Array() {
		if (data != nullptr) {
			delete[] data;
		}
		cout << "Об'єкт було знищено, а пам'ять - вивільнено!\n";
	}

	// конструктор копіювання
	Array(Array& original) {
		this->length = original.length;
		this->data = new int[this->length];
		for (int i = 0; i < this->length; i++)
		{
			this->data[i] = original.data[i];
		}
	}
};

int main() {
	SetConsoleOutputCP(1251);
	srand(time(0));

	Array original;
	original.Add10RandomNumbers();
	original.Print();
	// hw test
	original.Insert(100, 7);
	original.Print();

	original.RemoveAt(3);
	original.Print();

	original.RemoveByValue(100);
	original.Print();

	original.Clear();
	original.Print();

	cout << original.IsEmpty() << "\n";
	
	original.Add10RandomNumbers();
	original.Print();
	cout << original.IndexOF(5) << "\n";
	cout << original.LastIndexOf(5) << "\n";

	original.Reverse();
	original.Print();

	Array copy = original;
	// Array copy(original); // виклик конструктору копіювання! КК
	copy.Print();
}
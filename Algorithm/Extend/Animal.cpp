#include <string>
#include <iostream>
using namespace std;

// khai báo lớp Animal
class Animal
{
public:
	int Id();
	string Name();
	int Age();
	string Type();

	Animal(int id, string name, int age);
	Animal();

protected:
	int id;
	string name;
	int age;
	string type;
};

Animal::Animal(int id, string name, int age)
{
	this->id = id;
	this->name = name;
	this->age = age;
	this->type = "Animal";
}

Animal::Animal() {
	this->id = 0;
	this->name = "";
	this->age = 0;
	this->type = "";
}

int Animal::Id() {
	return id;
}

string Animal::Name() {
	return name;
}

int Animal::Age() {
	return age;
}

string Animal::Type() {
	return type;
}


// khai báo lớp Dog
class Dog : public Animal {
public:
	Dog(int id, string name, int age) : Animal(id, name, age) {
		this->type = "Dog";
	}
};

// khai báo lớp Cat
class Cat : public Animal {
public:
	Cat(int id, string name, int age) : Animal(id, name, age) {
		this->type = "Cat";
	}
};

// khai báo lớp Tiger
class Tiger : public Animal {
public:
	Tiger(int id, string name, int age) : Animal(id, name, age) {
		this->type = "Tiger";
	}
};

//khai báo lớp container(dùng để làm chuồng)
class Container {
private:
	int count;
	int numberOfSpace;
	Animal* animals;

public:
	int Count() {
		return count;
	}

	Container(int numberOfSpace) {
		this->count = 0;
		this->numberOfSpace = numberOfSpace;
		this->animals = new Animal[numberOfSpace];
	}

	int AddSpace(int n) {
		if (n > 0) {
			Animal* newArray = new Animal[numberOfSpace + n];
			for (int i = 0; i < count; i++) {
				newArray[i] = this->animals[i];
			}
			this->animals = newArray;
			numberOfSpace = numberOfSpace + n;
		}
		return numberOfSpace;
	}

	int AddAnimal(Animal animal) {
		if (count < numberOfSpace) {
			this->animals[count] = animal;
			count++;
		}
		else {
			AddSpace(10);
			this->animals[count] = animal;
			count++;
		}
		return count;
	}

	void PrintAnimalList() {
		for (int i = 0; i < count; i++) {
			cout << (i + 1) << ") id: " << this->animals[i].Id() << " age: " << this->animals[i].Age() << " name: " << this->animals[i].Name() << " type: " << this->animals[i].Type() << endl;
		}
	}
};

void PrintCommonText() {
	cout << "Program to manage animals" << endl;
	cout << "press 1 to add one space" << endl;
	cout << "press 2 to add one animal" << endl;
	cout << "press 3 to see list of all animals" << endl;
	cout << "press 4 to exit program" << endl;
}

int main() {
	Container* container = new Container(20);
	char sign;
	PrintCommonText();
	while (true)
	{
		cout << "press your order: ";
		cin >> sign;
		if (sign == '1') {
			system("cls");
			PrintCommonText();
			cout << "Number of space is: " << container->AddSpace(1) << endl;
		}
		else if (sign == '2') {
			system("cls");
			PrintCommonText();
			int id, age, type;
			string name;
		node1:
			cout << "Enter type of animal(1: dog, 2: cat, 3: tiger): ";
			cin >> type;
			if (!(type == 1 || type == 2 || type == 3)) goto node1;
			cout << "Enter animal id: ";
			cin >> id;
			cout << "Enter animal name ";
			cin >> name;
			cout << "Enter animal age: ";
			cin >> age;
			Animal* animal;
			if (type == 1) animal = new Dog(id, name, age);
			else if (type == 2) animal = new Cat(id, name, age);
			else animal = new Tiger(id, name, age);
			container->AddAnimal(*animal);
			cout << "Number of animals is: " << container->Count() << endl;
			cout << "New animal is: " << "id: " << id << " age: " << age << " name: " << name << endl;
		}
		else if (sign == '3') {
			system("cls");
			PrintCommonText();
			container->PrintAnimalList();
		}
		else if (sign == '4') {
			system("cls");
			PrintCommonText();
			break;
		}
		else cout << "Wrong function";
	}
	cout << "Exit program" << endl;
}
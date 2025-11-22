#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <windows.h>
using namespace std;

class Animal{
public:
    virtual ~Animal() {}
    string name;
    int age;
    int weight;
    
    Animal(string name, int age, int weight):
        name(name), age(age), weight(weight)
    {}

    void info(){
        cout << "Name " << name << " Age : " << age << " Weight : " << weight << endl;
    }
};

class Lion : public Animal{
public:
    bool mane;

    Lion(string name, int age, int weight, bool mane):
        Animal(name, age, weight),
        mane(mane)
    {}

    void roar(){
        cout << "Lion " << name << " is roaring !" << endl;
    }
};

class Penguin : public Animal{
public:
    string species;

    Penguin(string name, int age, int weight, string species):
        Animal(name, age, weight),
        species(species)
    {}

    void slide(){
        cout << "Penguin " << name << " is sliding on his tummy !" << endl;
    }
};

class Elephant : public Animal{
public:
    int trunk_len;

    Elephant(string name, int age, int weight, int trunk_len):
        Animal(name, age, weight),
        trunk_len(trunk_len)
    {}

    void trumpet(){
        cout << "Elephant " << name << " is trumping !" << endl;
    }
};


void add_animal(vector<Animal*>& animals){
    system("cls");
    int choice; 

    cout << "+---------------------------+" << endl;
    cout << "|        ADD ANIMAL         |" << endl;
    cout << "+---------------------------+" << endl;
    cout << "|        1. LION            |" << endl;
    cout << "|        2. PENGUIN         |" << endl;
    cout << "|        3. ELEPHANT        |" << endl ;
    cout << "+---------------------------+" << endl;
    cout << "" << endl;
    
    cout << "SELECT: ";
    cin >> choice;
    
    string name, resp;
    int age, weight;

    if(choice >= 1 && choice <= 3){
        cout << "Provide name: ";
            cin >> name;

        cout << "Provide age : ";
        cin >> age;

        cout << "Provide weight : ";
        cin >> weight;
    }
    switch(choice){
        // lion
        case 1:{
            bool mane = false;
            cout << "Does the lion have a mane? (y/n): ";
            cin >> resp;
            if(resp == "y") mane = true;
            else if(resp == "n") mane = false;

            animals.push_back(new Lion(name, age, weight, mane));
            break;
        }
        // penguin
        case 2:{
            string species;
            cout << "Provide species : ";
            cin >> species;

            animals.push_back(new Penguin(name, age, weight, species));
            break;
        }
        // elephant
        case 3:{
            int trump_len;
            cout << "Provide lenght of trunk : ";
            cin >> trump_len;

            animals.push_back(new Elephant(name, age, weight, trump_len));
            break;
        }
        default:
            return;
    }
    cout << "" << endl;
    cout << "+---------------------------+" << endl;
    cout << "|        ANIMAL ADDED !     |" << endl;
    cout << "+---------------------------+" << endl;
    Sleep(1000);
}

string build_mov(int qty){
    string to_return = "";

    for(int i = 0; i < qty; i++){
        to_return += " ";
    }
    
    return to_return;
}

void display_animals(vector<Animal*>& animals){
    system("cls");
    string name, n_mov, a_mov, w_mov, weight, age;

    cout << "+---------------------------+" << endl;
    cout << "|       ANIMALS IN ZOO      |" << endl;
    cout << "+---------------------------+" << endl;
    int DEF_MOV_N = 19;
    int DEF_MOV_A = 20;
    int DEF_MOV_W = 17;
    for(const Animal* current : animals){
        name = current->name;
        age = to_string(current->age);
        weight = to_string(current->weight);

        n_mov = build_mov(DEF_MOV_N - name.length());
        a_mov = build_mov(DEF_MOV_A - age.length());
        w_mov = build_mov(DEF_MOV_W - weight.length());
        cout << "+---------------------------+" << endl;
        cout << "| NAME : " << name << n_mov << "|" << endl;
        cout << "+---------------------------+" << endl;
        cout << "| AGE : " << age << a_mov << "|" << endl;
        cout << "+---------------------------+" << endl;
        cout << "| WEIGHT : " << weight << w_mov << "|" << endl;
        cout << "+---------------------------+" << endl;
        cout << "+---------------------------+" << endl;
        cout << "|                           |" << endl;
        cout << "+---------------------------+" << endl;
    }
}

void delete_animal(vector<Animal*>& animals){
    system("cls");
    int DEF_MOV_N = 23;
    string mov, name;
    cout << "+---------------------------+" << endl;
    cout << "|        REMOVE ANIMAL      |" << endl;
    cout << "+---------------------------+" << endl;
    
    for(int i = 0; i < animals.size(); ++i){
        name = animals[i]->name;
        mov = build_mov(DEF_MOV_N - name.length());
        
        cout << "| " << i + 1 << ") " << name << mov << "|" << endl;
    }
    cout << "+---------------------------+" << endl;

    int choice;
    cout << "\nProvide number to remove : ";
    cin >> choice;

    animals.erase(animals.begin() + choice - 1);

    Sleep(1000);
}

void test(vector<Animal*>& animals){
    for(Animal* cur : animals){
        if(Lion* lew = dynamic_cast<Lion*>(cur)){
            lew->roar();
        }
    }
}

int main(){
    vector<Animal*> animals;
    add_animal(animals);
    add_animal(animals);
    return 0;
}

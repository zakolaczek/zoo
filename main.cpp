// includes section
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <windows.h>
#include <bits/stdc++.h>
using namespace std;

// main class ANIMAL
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

// Connected classes Lion, Elephtant, Penguin
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

// function used to create file from current data about animals
void write_file(string filename, vector<Animal*>& animals){
    string class_name, name, species, mane_s;
    int age, weight, trunk_len;
    bool mane;

    ofstream file(filename);

    for(Animal* animal : animals){
        name = animal->name;
        age = animal->age;
        weight = animal->weight;
        
        if(Lion* lion = dynamic_cast<Lion*>(animal)){
            class_name = "Lion";
            mane = lion->mane;
            if(mane) mane_s="yes";
            else mane_s="no";
            file << class_name << "," << name << "," << age << "," << weight << ",";
            file << mane_s << endl;
        }else if(Elephant* ele = dynamic_cast<Elephant*>(animal)){
            class_name = "Elephant";
            trunk_len = ele->trunk_len;
        
            file << class_name << "," << name << "," << age << "," << weight << ",";
            file << trunk_len << endl;
        }else{
            Penguin* pengu = dynamic_cast<Penguin*>(animal);
            class_name = "Penguin";
            species = pengu->species;

            file << class_name << "," << name << "," << age << "," << weight << ",";
            file << species << endl;
        }
    }
    file.close();
}


vector<Animal*> read_file(string filename){
    vector<Animal*> animals;

    ifstream file(filename);
    string line;
    char delimiter = ',';

    string class_name, name, species, mane_s, age_s, weight_s, trunk_len_s;
    int age, weight, trunk_len; 
    bool mane;

    while(getline(file, line)){
        stringstream ss(line);
        
        getline(ss, class_name, delimiter);
        getline(ss, name, delimiter);
        getline(ss, age_s, delimiter);
        getline(ss, weight_s, delimiter);
        age = stoi(age_s);
        weight = stoi(weight_s);

        if(class_name == "Lion"){
            getline(ss, mane_s, delimiter);
            
            if(mane_s == "yes") mane = true;
            else mane = false;

            animals.push_back(new Lion(name, age, weight, mane));
        }else if(class_name == "Penguin"){
            getline(ss, species, delimiter);

            animals.push_back(new Penguin(name, age, weight, species));   
        }else{
            getline(ss, trunk_len_s, delimiter);
            trunk_len = stoi(trunk_len_s);
            animals.push_back(new Elephant(name, age, weight, trunk_len));
        }
    }
    
    return animals;
}
// function used to add animal
void add_animal(vector<Animal*>& animals){
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
    write_file("baza.txt", animals);
}

// support function to build a tui
string build_mov(int qty){
    string to_return = "";

    for(int i = 0; i < qty; i++){
        to_return += " ";
    }
    
    return to_return;
}

// show all animals in zoo
void display_animals(vector<Animal*>& animals){
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
        cout << "| AGE : " << age << a_mov << "|" << endl;
        cout << "| WEIGHT : " << weight << w_mov << "|" << endl;
        cout << "+---------------------------+" << endl;
        cout << "|                           |" << endl;
        cout << "+---------------------------+" << endl;
    }
}

// function to delete animal from zoo
void delete_animal(vector<Animal*>& animals){

    int DEF_MOV_N = 22;
    string mov, name, number;
    cout << "+---------------------------+" << endl;
    cout << "|       REMOVE ANIMAL       |" << endl;
    cout << "+---------------------------+" << endl;
    
    for(int i = 0; i < animals.size(); ++i){
        
        if(i + 1 < 10) number = "0";
        else number = "";

        number += to_string(i + 1);
        name = animals[i]->name;
        mov = build_mov(DEF_MOV_N - name.length());
        
        cout << "| " << number << ") " << name << mov << "|" << endl;
    }
    cout << "+---------------------------+" << endl;

    int choice;
    cout << "\nProvide number to remove : ";
    cin >> choice;

    animals.erase(animals.begin() + choice - 1);

    cout << "+---------------------------+" << endl;
    cout << "|      ANIMAL REMOVED!      |" << endl;
    cout << "+---------------------------+" << endl;
    write_file("baza.txt", animals);

}

// function to use special function for animal
void call_animal(vector<Animal*>& animals){

    int DEF_MOV_N = 22;
    string mov, name, number;
    cout << "+---------------------------+" << endl;
    cout << "|        CALL ANIMAL        |" << endl;
    cout << "+---------------------------+" << endl;
    
    for(int i = 0; i < animals.size(); ++i){
        
        if(i + 1 < 10) number = "0";
        else number = "";

        number += to_string(i + 1);
        name = animals[i]->name;
        mov = build_mov(DEF_MOV_N - name.length());
        
        cout << "| " << number << ") " << name << mov << "|" << endl;
    }
    cout << "+---------------------------+" << endl;

    int choice;
    cout << "\nProvide number to call : ";
    cin >> choice;

    Animal* selected_animal = animals[choice - 1];
    if(Lion* lion = dynamic_cast<Lion*>(selected_animal)) lion->roar();
    else if(Penguin* pengu = dynamic_cast<Penguin*>(selected_animal)) pengu->slide();
    else dynamic_cast<Elephant*>(selected_animal)->trumpet();

    cout << "" << endl;
    cout << "+---------------------------+" << endl;
    cout << "|      ANIMAL CALLED !      |" << endl;
    cout << "+---------------------------+" << endl;
}

// edit animal method
void edit_animal(vector<Animal*>& animals){

    int DEF_MOV_N = 22;
    string mov, name, number;
    cout << "+---------------------------+" << endl;
    cout << "|        EDIT ANIMAL        |" << endl;
    cout << "+---------------------------+" << endl;
    
    for(int i = 0; i < animals.size(); ++i){
        
        if(i + 1 < 10) number = "0";
        else number = "";

        number += to_string(i + 1);
        name = animals[i]->name;
        mov = build_mov(DEF_MOV_N - name.length());
        
        cout << "| " << number << ") " << name << mov << "|" << endl;
    }
    cout << "+---------------------------+" << endl;
    
    int choice;
    int int_answ;
    bool bool_answ;
    string string_answer, bool_answ_s;
    int SPACE_DEF = 23;
    string parameter;
    cout << "\nProvide number to edit : ";
    cin >> choice;
    Sleep(1000);
    system("cls");
    
    Animal* selected_animal = animals[choice - 1];
    if(Lion* lion = dynamic_cast<Lion*>(selected_animal)) parameter = "MANE";
    else if(Penguin* pengu = dynamic_cast<Penguin*>(selected_animal)) parameter = "SPECIES";
    else if (Elephant* ele = dynamic_cast<Elephant*>(selected_animal)) parameter = "TRUNK LEN";
    mov = build_mov(SPACE_DEF - parameter.length()) ;

    cout << "+---------------------------+" << endl;
    cout << "|        EDIT ANIMAL        |" << endl;
    cout << "+---------------------------+" << endl;
    cout << "|01) NAME                   |" << endl;
    cout << "|02) AGE                    |" << endl;
    cout << "|03) WEIGHT                 |" << endl;
    cout << "|04) " << parameter << mov << "|" << endl;
    cout << "+---------------------------+" << endl;

    cout << "Provide number to edit : ";
    cin >> choice;
    cout << "Provide new value : ";

    switch (choice){
        // name
        case 1:{
            cin >> string_answer;
            selected_animal->name = string_answer;
            break;
        }

        // age
        case 2:{
            cin >> int_answ;
            selected_animal->age = int_answ;
            break;
        }

        // weight
        case 3:{
            cin >> int_answ;
            selected_animal->weight = int_answ;
            break;
        }
        
        // special parameter
        case 4:{
            if(parameter == "MANE"){
                cin >> bool_answ_s;
                if(bool_answ_s[0] == 'y') bool_answ = true;
                else bool_answ = false;

                Lion* lion = dynamic_cast<Lion*>(selected_animal);
                lion->mane = bool_answ;
            }else if(parameter == "SPECIES"){
                cin >> string_answer;

                Penguin* pengu = dynamic_cast<Penguin*>(selected_animal);
                pengu->species = string_answer;
            }else{
                cin >> int_answ;

                Elephant* ele = dynamic_cast<Elephant*>(selected_animal);
                ele->trunk_len = int_answ;
            }
        }
    }

    cout << "+---------------------------+" << endl;
    cout << "|      ANIMAL EDITTED !     |" << endl;
    cout << "+---------------------------+" << endl;
    write_file("baza.txt", animals);

}

// main menu method
void main_menu(vector<Animal*>& animals){
    int choice;

    while(true){
        system("cls");
        cout << "+---------------------------+" << endl;
        cout << "|         ZAKOL ZOO         |" << endl;
        cout << "+---------------------------+" << endl;
        cout << "|01) ADD ANIMAL             |" << endl;
        cout << "|02) DISPLAY ALL            |" << endl;
        cout << "|03) DELETE ANIMAL          |" << endl ;
        cout << "|04) EDIT ANIMAL            |" << endl ;
        cout << "|05) CALL ANIMAL            |" << endl ;
        cout << "|06) EXIT                   |" << endl ;
        cout << "+---------------------------+" << endl;

        cout << "Provide option number: ";
        cin >> choice;

        Sleep(1000);
        system("cls");

        if(choice == 1) add_animal(animals);
        else if(choice == 2) display_animals(animals);
        else if(choice == 3) delete_animal(animals);
        else if(choice == 4) edit_animal(animals);
        else if(choice == 5) call_animal(animals);
        else if(choice == 6) return;
        Sleep(4000);
    }
}

int main(){
    vector<Animal*> animals = read_file("baza.txt");;
    main_menu(animals);
    return 0;
}

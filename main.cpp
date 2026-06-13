#include <iostream>
using namespace std;
 
class Person{
    string name; 
    string surname;
    int age;
    
    public:
    
    Person(string name = "", string surname = "", int age = 0){
        this->name = name;
        this->surname = surname;
        this->age = age;
    }
     
    void display(){
        cout << "Name: " << this->getName() << endl;
        cout << "Surname: " << this->getSurname() << endl;
        cout << "Age: " << this->age << endl;
    }
       
    string getName(){
        return this->name;
    }
    string getSurname(){
        return this->surname;
    }
    
};

 
class Client : public Person{
    
    int clientId;
    
    public:
    
    Client(string name = "", string surname = "", int age = 0, int clientId = 0):
  
    Person(name, surname, age)
    {
        this->clientId = clientId;
    }
    
    void displayClient(){
        Person::display();
        cout << "Client id: " << this->getId() << endl;
    }
    
    int getId(){
        return this->clientId;
    }
    
};


class Worker{
    
    string position;
    double salary;
    
    public:
   
    Worker(string position = "", double salary = 0){
        this->position = position;
        this->salary = salary;
    }
    
    void displayWorker(){
        //we dont have getter function this why i call it directly
        cout << "Position: " << this->position << endl;
        cout << "Salary: " << this->salary << endl;
    }
};



class Employee : public Person, public Worker{
    
    
    public:
    
    Employee(string name = "", string surname = "", int age = 0,
    string position = "", double salary = 0):
    Person(name, surname, age), Worker(position, salary)
    {}
    
    void displayEmployee(){
        Person::display();
        Worker::displayWorker();
    }
};



class Car{
     
    string licensePlate;
    string brand;
    string model;
    int year;
    double dailyPrice;
    bool available;
    
    
    public:
   
    Car(string licensePlate = "", string brand = "", string model = "",
    int year = 0, double dailyPrice = 0, bool available = false){
        this->licensePlate = licensePlate;
        this->brand = brand;
        this->model = model;
        this->year = year;
        this->dailyPrice = dailyPrice;
        this->available = available;
    }
 
    void display(){
        cout << "License Plate: " << this->getLicensePlate() << endl;
        cout << "Brand: " << this->brand << endl;
        cout << "Model: " << this->model << endl;
        cout << "Year: " << this->year << endl;
        cout << "Daily Prices: " << this->getPricePerDay() << endl;
        cout << "Availablity: "
        << (this->isAvailable() ? "Available" : "Not Available");//ternary operator if is true print Available if it false print Not Available 
        cout << "\n\n ";
    }
    
    bool isAvailable(){
        return this->available;
    }
    void setAvailability(bool a){
        this->available = a;
    }
    double getPricePerDay() const {
        return this->dailyPrice;
    }
    string getLicensePlate() const {
        return this->licensePlate;
    }
   
    bool operator==(const Car& other){
       /* if(this->getLicensePlate() == other.getLicensePlate()){
            return true;
        } else {
            return false;
        }
        */
        return this->getLicensePlate()==other.getLicensePlate();
    }
   
   bool operator<(const Car& other){
       /* if(this->getPricePerDay() < other.getPricePerDay()){
            return true;
        } else {
            return false;
        }
        */
        return this->getPricePerDay() < other.getPricePerDay(); 
    }
};

class Agency{
    string agencyName;
    string address;
    Car cars[50];
    Client clients[50];
    Employee employees[10];
    int carCount, clientCount, employeeCount; 

    public:    
    
    Agency(string address = "", string agencyName = ""){
        this->carCount = this->clientCount = this->employeeCount = 0;//Becuse at the begging we dont have anything 
        this->address = address;
        this->agencyName = agencyName;
    }
    void addCar(Car c){
        if(this->carCount < 50){//to make sure that it does not exceed the allowed limit 
            this->cars[this->carCount] = c;
            this->carCount++;
        } else {
            cout << "Error exceeds number of required cars\n";
        }
    }
    void addClient(Client c){
        if(this->clientCount < 50){//similar to add car 
            this->clients[this->clientCount] = c;
            this->clientCount++;
        } else {
            cout << "Error exceeds number of required clients\n";
        }   
    }
    void addEmployee(Employee e){
        if(this->employeeCount < 10){
            this->employees[this->employeeCount] = e;
            this->employeeCount++;
        } else {
            cout << "Error exceeds number of required employees\n";
        }
    }
    void showAvailableCars(){ //to show us the available cars 
        for(int i = 0; i < this->carCount; i++){//if i use <= would give me extra invalid element
            if(this->cars[i].isAvailable()){//condition 
                this->cars[i].display();//if its avalibale print the deatils
            }
        }
    }
    void processRental(Client client, Car &car){ //simulate 5 days rental *calculate the total price for 5 days*
        int i = 0;
        bool foundCar = false;
        while(i < carCount){
            if(cars[i] == car){
                foundCar = true;//if we found the car foundcars =true 
                break;
            }
            i++;
        }
        int j = 0;
        bool foundClient = false;
        while(j < clientCount){
            if(clients[j].getId() == client.getId()){ 
                foundClient = true;//if it equal foundClient=true
                break;
            }
            j++;
        }
        if(foundCar == false || foundClient == false){
            cout << "The car or the client is not within the Agency\n";
        } else {
            if(cars[i].isAvailable()){
                cout << "Client details:\n";
                clients[j].displayClient();
                cout << "Car details:\n";
                cars[i].display();
                cout << "The 5 days renting price in Ryals: " << cars[i].getPricePerDay() * 5 << endl;
                cout << "The car is rented now and not avaliable for other clients \n";
                cars[i].setAvailability(false);
            } else {
                cout << "Sorry, the car is not available for renting\n";
            }
        }

    }
};

int main(){
    
    Agency a("Qassim", "Qassim Agency");
    
    
    Car c1("AAA111", "BMW", "BMW X5", 2023, 120, true);
    Car c2("BBB222", "FORD", "Mustang", 2017, 90, true);
    Car c3("CCC333", "MERCEDS", "Merceds C-class", 2024, 100, true);
    a.addCar( c1 );
    a.addCar( c2 );
    a.addCar( c3 );
    
    Client cl1("Abdullah", "Alsaleh", 23, 100);
    Client cl2("Mohammed", "ALkhaldy", 35, 200);
    Client cl3("Ahmed", "ALtamimi", 29, 300);
    a.addClient( cl1 );
    a.addClient( cl2 );
    a.addClient( cl3 );
    
    Employee e1("Ghala", "Alyahya", 21, "Manager", 10000);
    Employee e2("Abdulaziz", "Abdullah", 23, "Mechanical Engineer", 5000);
    a.addEmployee( e1 );
    a.addEmployee( e2 );
    
   
    a.showAvailableCars();
    cout << "\n\n\n===============\n\n\n";
    
    
    
    if(c1 == c2){
        cout << "Both cars have the same license Plate\n";
    } else {
        cout << "Both cars dont have the same license Plate\n";
    }
    cout << "\n\n\n===============\n\n\n";
    
    
    if(c1 < c2){
        cout << "Second car is expensive than the first car\n";
    } else {
        cout << "First car is expensive than the second car\n";
    }
    cout << "\n\n\n===============\n\n\n";
    
    /*
    process a Rental for a Client (5-days simulation) printing the total cost
    show avaiable cars again to conform the rented car is no longer avaiable
    */
    a.processRental(cl1, c2);
    cout << "\n\n\n===============\n\n\n";
    a.showAvailableCars();
    cout << "\n\n\n===============\n\n\n";
    
    //Displa Employee information
    e1.displayEmployee();
    
    
    return 0;
}
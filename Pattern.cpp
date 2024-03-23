//Паттерн Фабричный метод
#include<iostream>
using namespace std;


//Интерфейс продукта бъявляет операции, которые должны выполнять все конкретные продукты
class Furniture {
public:
    virtual ~Furniture() {}
    virtual string Create() const = 0;
};

//Конкретные продукты предоставляют различные реализации интерфейса Furniture
class Chair: public Furniture {
public:
    string Create() const override {
        return "стул";
    }
};

class Table: public Furniture {
public:
    string Create() const override {
        return "стол.";
    }
};

class Sofa: public Furniture {
public:
    string Create() const override {
        return "диван.";
    }
};

class Bed: public Furniture {
public:
    string Create() const override {
        return "кровать.";
    }
};

//Класс cоздатель объявляет фабричный метод, который должен возвращать объект класса Furniture
class FurnitureFactory {
public:
    virtual ~FurnitureFactory() {}
    virtual Furniture* CreateFurniture() const = 0;
    string Operation() const {
        //Вызываем фабричный метод, чтобы получить объект-продукт
        Furniture* furniture = this->CreateFurniture();
        //Далее, работаем с этим продуктом.
        string result = "Фабрика: создан(а) " + furniture->Create();
        delete furniture;
        return result;
    }
};

// Конкретные cоздатели переопределяют фабричный метод для того, чтобы изменить тип результирующего продукта
class ChairFactory: public FurnitureFactory {
public:
    Furniture* CreateFurniture() const override {
        return new Chair();
    }
};

class TableFactory: public FurnitureFactory {
public:
    Furniture* CreateFurniture() const override {
        return new Table();
    }
};

class SofaFactory: public FurnitureFactory {
public:
    Furniture* CreateFurniture() const override {
        return new Sofa();
    }
};

class BedFactory: public FurnitureFactory {
public:
    Furniture* CreateFurniture() const override {
        return new Bed();
    }
};

/*Клиентский код работает с экземпляром конкретного создателя, хотя и через его
базовый интерфейс. Пока клиент продолжает работать с создателем через базовый
интерфейс, вы можете передать ему любой подкласс создателя*/
void ClientCode(const FurnitureFactory& factory) {
    cout << "Клиент: управление мебельной фабрикой.\n" << factory.Operation() << endl;
}


int main() {
    //Приложение выбирает тип создателя в зависимости от конфигурации или среды
    cout << endl;
    cout << "Приложение: создание мебели с помощью фабрики стульев.\n";
    FurnitureFactory* chairFactory = new ChairFactory();
    ClientCode(*chairFactory);
    cout << endl;
    cout << "Приложение: создание мебели с помощью фабрики столов.\n";
    FurnitureFactory* tableFactory = new TableFactory();
    ClientCode(*tableFactory);
    cout << endl;
    cout << "Приложение: создание мебели с помощью фабрики диванов.\n";
    FurnitureFactory* sofaFactory = new SofaFactory();
    ClientCode(*sofaFactory);
    cout << endl;
    cout << "Приложение: создание мебели с помощью фабрики кроватей.\n";
    FurnitureFactory* bedFactory = new BedFactory();
    ClientCode(*bedFactory);

    delete chairFactory;
    delete tableFactory;
    delete sofaFactory;
    delete bedFactory;

    return 0;
}
#include <iostream>
#include <vector>
#include <map>

using namespace std;
    // блюдо и напиток
    enum Food_ID { Dish_Food, Drink_Food};

    class Food; 
    typedef map<Food_ID, Food*> Registry;

    Registry& getRegistry()
    {
        static Registry _instance;
        return _instance;
    }

    
    class Dummy { };

    class Food
    {
    public:
        virtual Food* clone() = 0;
        virtual void info() = 0;
        virtual ~Food() {}

        static Food* repeatOrder(Food_ID id) {
            Registry& r = getRegistry();
            if (r.find(id) != r.end())
                return r[id]->clone();
            return 0;
        }
    protected:

        static void addPrototype(Food_ID id, Food* prototype) {
            Registry& r = getRegistry();
            r[id] = prototype;
        }
        static void removePrototype(Food_ID id) {
            Registry& r = getRegistry();
            r.erase(r.find(id));
        }
    };
    class Dish : public Food
    {
    public:
        Food* clone() {
            cout << "Повторный заказ блюда\n";
            return new Dish(*this);
        }
        void info() {
            cout << "Блюдо\n";
        }
    private:
        Dish(Dummy) {
            Food::addPrototype(Dish_Food, this);
        }
        Dish() {}
        static Dish prototype;
    };

    class Drink : public Food
    {
    public:
        Food* clone() {
            cout << "Повторный заказ напитка\n";
            return new Drink(*this);
        }
        void info() {
            cout << "Напиток\n";
        }
    private:
        Drink(Dummy) {
            addPrototype(Drink_Food, this);
        }
        Drink() {}
        static Drink prototype;
    };


    Dish Dish::prototype = Dish(Dummy());
    Drink Drink::prototype = Drink(Dummy());


    int main()
    {   
        setlocale(LC_ALL, "Russian");
        //что заказано
        vector<Food*> v;
        v.push_back(Food::repeatOrder(Dish_Food));
        v.push_back(Food::repeatOrder(Drink_Food));
        
        for (int i = 0; i < v.size(); i++)
            v[i]->info();

        cout << "Число прототипов: " << getRegistry().size() << "\n";
    }

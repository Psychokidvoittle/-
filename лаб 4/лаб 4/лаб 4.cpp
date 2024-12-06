#include <iostream>
#include <string>

class Node {
public:
    std::string data;
    Node* next;
    Node* prev;

    Node(const std::string& value) : data(value), next(nullptr), prev(nullptr) {}
    ~Node(){

        next = nullptr;
        prev = nullptr;
    }
};

class Stack {
private:
    Node* TOP;
public:
    Stack() : TOP(nullptr) {
        // Создаем "крышку"

        
        TOP = new Node("КРЫШКА");  // Это верхний элемент, который нельзя удалить
        
        TOP= nullptr;

    }
    ~Stack() {
        while(TOP != nullptr) {
            Node*temp = TOP;
            TOP = TOP->prev;
            if (TOP != nullptr) {
                TOP->next = nullptr;
            }
            delete temp;
        }
        TOP = nullptr;
        
    }
    // Метод для добавления элемента в стек
    void Add(const std::string& value) {
        Node* newNode = new Node(value);
        if (TOP == nullptr) {  
            TOP = newNode;    
        }
        else {
            Node* current = TOP;
            while (current->next != nullptr) {  
                current = current->next;
            }
            current->next = newNode;  
        }
    }

    // Метод для извлечения элемента из стека
    std::string Pop() {
        if (TOP->next == nullptr) {  
            throw std::runtime_error("в стеке только TOP))");
        }
        Node* temp = TOP;          
        std::string value = TOP->data; 
        TOP = TOP->next;          
        if (TOP) {
            TOP->prev = nullptr;   
        }
        delete temp;              
        return value;
    }

    // Метод для поиска элемента в стеке
    bool Contains(const std::string& value) const {
        Node* current = TOP;
        while (current && current->data != "КРЫШКА") {  // Ищем до "крышки"
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Метод для вычисления веса элемента (его позиции в стеке)
    int Weight(const std::string& value) const {
        Node* current = TOP;
        int position = 0;
        while (current && current->data != "КРЫШКА") {  
            if (current->data == value) {
                return position + 1; 
            }
            current = current->next;
            position++;
        }
        return -1; 
    }

    // Метод для получения глубины стека
    int Depth() const {
        int depth = 0;
        Node* current = TOP;
        while (current && current->data != "КРЫШКА") {  
            depth++;
            current = current->next;
        }
        return depth; 
    }

    // Переопределение оператора +
    Stack operator+(const Stack& other) const {
        Stack result;

        Node* current = this->TOP;
        while (current && current->data != "КРЫШКА") {  
            result.Add(current->data);
            current = current->next;
        }

        current = other.TOP;
        while (current && current->data != "КРЫШКА") {  
            result.Add(current->data);
            current = current->next;
        }

        return result;
    }

    // Переопределение оператора *
    Stack operator*(const Stack& other) const {
        Stack result;

        Node* current1 = this->TOP;
        Node* current2 = other.TOP;

        while (current1 && current1->data != "КРЫШКА") {
            result.Add(current1->data);
            current1 = current1->next;
        }

        while (current2 && current2->data != "КРЫШКА") {
            result.Add(current2->data);
            current2 = current2->next;
        }

        return result;
    }
    

    // Унарный оператор для разворота стека
    Stack operator-() const {
        Stack result;
        Node* current = TOP;
        while (current) {
            result.Add(current->data); 
            current = current->next;
        }
        return result; 
    }


    
    // Метод для отображения содержимого стека (для тестирования)
    void Display() const {
        Node* current = TOP;
        while (current && current->data != "КРЫШКА") {
            std::cout << current->data << "-";
            current = current->next;
        }
        std::cout << "КРЫШКА" << std::endl;  // Отображаем "крышку"
    }
};

// Пример использования
int main() {
    setlocale(LC_ALL, "RU");
    Stack stackA, stackB;

    stackA.Add("a1");
    stackA.Add("a2");
    stackA.Add("a3");

    stackB.Add("b1");
    stackB.Add("b2");

    std::cout << "A: ";
    stackA.Display();

    std::cout << "B: ";
    stackB.Display();

    Stack stackC = stackB + stackA;  // Соединение стеков
    std::cout << "C (A + B): ";
    stackC.Display();

    Stack stackD = stackB * stackA;  // Перекрестное соединение стеков
    std::cout << "D (A * B): ";
    stackD.Display();

    Stack stackE = -stackA;  // Разворот стека A
    std::cout << "E (-A): ";
    stackE.Display();

    std::cout << "глубина A: " << stackA.Depth() << std::endl;

    std::string elementToFind = "a2";
    std::cout<< (stackA.Contains(elementToFind) ? "T" : "F") << std::endl;
    
    std::cout << stackA.Weight(elementToFind) << std::endl;
    return 0;
}

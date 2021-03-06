#include "Application.h"

int numOfTestCase (0);

Application::Application() 
    : command(-1), interType(InterfaceType::UNDEFINED)
{
    msg.first =
    "\n\t Done!";
    msg.second =
    "\n\t Fail!";
    return;
}

Application::~Application(){ return; }

bool Application::GenerateTestCase()
{
    std::ofstream outFile;
    outFile.open("TestCase.txt", std::ofstream::out | std::ofstream::trunc);
    if(!outFile)
    {
        std::cerr << 
        "\n\t Failed to Generating test case. \n";
        outFile.close();
        return false;
    }
    else
    {
        for(int i = 0; i < numOfTestCase; i++)
        {
            outFile << std::rand() % numOfTestCase << " " << std::rand() % numOfTestCase << "\n";
        }
        outFile.close();
        return true;
    }
}

bool Application::LoadTestCase() 
{
    std::cout << 
    "\n\t Type (only positive integer) number of test cases : ";
    std::cin >> numOfTestCase;
    std::cout << "\n";
    GenerateTestCase();

    std::fstream inFile;
    inFile.open("TestCase.txt");
    if(!inFile)
    {
        std::cout << 
        "\n\t Incorrect test case file path. \n";
        inFile.close();
        return false;
    }
    else 
    {
        int id(0);
        std::string name;
        for(int i = 0; i < numOfTestCase; i++)
        {
            inFile >> id;
            inFile >> name;
            ItemType tempItem(id, name);
            switch (interType)
            {
                case InterfaceType::STACK:
                    base->Push(tempItem);
                    break;
                case InterfaceType::QUEUE:
                    base->Add(tempItem);
                    break;
                case InterfaceType::LIST:
                    dynamic_cast<MyListInterface<ItemType>*>(base)->Add(0, tempItem);
                    break;
                default:
                break;
            }
    }
        inFile.close();
        return true;    
    }
}
int Application::Run() 
{
    int cmd (0);
    while(1)
    {

        std::cout << 
        "\n\t Linked List Test "
        "\n\t (1)   Singly Linked List ( Stack ) "
        "\n\t (2)   Singly Linked List ( Queue )"
        "\n\t (3)   Doubly Linked List ( Stack )"
        "\n\t (4)   Doubly Linked List ( Queue )"
        "\n\t (5)   Doubly Linked List (  List )"
        "\n\t (6)   Space-Efficient List ( Stack )"
        "\n\t (0)   Terminate Programme \n";
        std::cin >> cmd;
        switch (cmd)
        {
            case 1:
            interType = InterfaceType::STACK;
            base = new MyStack<ItemType>[1];
            break;
            case 2:
            interType = InterfaceType::QUEUE;
            base = new MyQueue<ItemType>[1];
            break;
            case 3:
            interType = InterfaceType::STACK;
            base = new MyDoublyStack<ItemType>[1];
            break;
            case 4:
            interType = InterfaceType::QUEUE;
            base = new MyDoublyQueue<ItemType>[1];
            break;
            case 5:
            interType = InterfaceType::LIST;
            base = new MyListInterface<ItemType>[1];
            break;
            case 6:
            interType = InterfaceType::STACK;
            base = new MySEList<ItemType>[1];
            break;
            case 0:
            Destroy();
            return 1;
            break;
        default:
            break;
        }
        bool isTerminated = false;
        while (!isTerminated) {
            switch (GetCommand(interType)) {
            case 1:
                Add();
                break;
            case 2:
                Remove();
                break;
            case 3:
                Print();
                break;
            case 4:
                Size();
                break;
            case 5:
                Set();
                break;
            case 6:
                Get();
                break;
            case 99:
                LoadTestCase();
                break;
            case 0:
                isTerminated = true;
                break;
            default:
                break;
            }

        }
    }
	return 1;
}

int Application::GetCommand(InterfaceType _type) 
{
    switch (_type)
    {
        case InterfaceType::STACK:
        {
            std::cout <<
            "\n\t (1)   Push"
            "\n\t (2)   Pop"
            "\n\t (3)   Print"
            "\n\t (4)   Size"
            "\n\t (99)  Load Test Case"
            "\n\t (0)   Exit\n";
            break;
        }
        case InterfaceType::QUEUE:
        {
            std::cout <<
            "\n\t (1)   Add"
            "\n\t (2)   Remove"
            "\n\t (3)   Print"
            "\n\t (4)   Size"
            "\n\t (99)  Load Test Case"
            "\n\t (0)   Exit\n";
            break;
        }
        case InterfaceType::LIST:
        {
            std::cout <<
            "\n\t (1)   Add"
            "\n\t (2)   Remove"
            "\n\t (3)   Print"
            "\n\t (4)   Size"
            "\n\t (5)   Set"
            "\n\t (6)   Get"
            "\n\t (99)  Load Test Case"
            "\n\t (0)   Exit\n";
            break;
        }
    default:
        break;
    }
    std::cin >> command;
    return command;
}

int Application::Add() 
{
    ItemType temp;
    temp.SetAll();
    switch (interType)
    {
        case InterfaceType::STACK:
        {
            base->Push(temp);
            break;
        }
        case InterfaceType::QUEUE:
        {
            base->Add(temp);
            break;
        }
        case InterfaceType::LIST:
        {
            int idx(0);
            std::cout <<
            "\n\t Add item to index : ";
            std::cin >> idx;
            dynamic_cast<MyListInterface<ItemType>*>(base)->Add(idx, temp);
            break;
        }
        default:
            break;
    }
    std::cout << msg.first;
    return 1;
}

int Application::Remove() 
{
    if (base->GetSize() == 0) return 0;
    ItemType temp;
    switch (interType)
    {
        case InterfaceType::STACK:
        {
            temp = base->Pop();
            break;
        }
        case InterfaceType::QUEUE:
        {
            temp = base->Remove();
            break;
        }
        case InterfaceType::LIST:
        {
            int idx (0);
            std::cout << 
            "\n\t Remove item at index : ";
            std::cin >> idx;
            temp = dynamic_cast<MyListInterface<ItemType>*>(base)->Remove(idx);
            break;
        }
        default:
            break;
    }
    std::cout << 
    "\n\t - Removed Item - \n" <<
    temp;
    return 1;
}


int Application::Print() 
{
    base->Print();
    return 1;
}

int Application::Destroy()
{
    delete[] base;
    return 1;
}

int Application::Size()
{
    std::cout << 
    "\n\t Current Size : " << base->GetSize();
    return 1;
}

int Application::Set()
{
    ItemType after, before;
    after.SetAll();
    int idx (0);
    std::cout <<
    "\n\t index : ";
    std::cin >> idx;
    before = dynamic_cast<MyListInterface<ItemType>*>(base)->Set(idx, after);
    std::cout << " - Item Changed -" << 
    "\n\t  ID " << before.GetID() << " -> " << after.GetID() << 
    "\n\t Name "<< before.GetName() << " -> " << after.GetName() << "\n";

    return 1;
}

int Application::Get()
{
    ItemType temp;
    int idx ( 0 );
    temp = dynamic_cast<MyListInterface<ItemType>*>(base)->Get(idx);
    std::cout << " - Got Item -" <<
    temp;
    return 1;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>
using namespace std;

struct Task {
    string description;
    bool completed;
    int priority;
    string dueDate;

    Task(const string& desc, int prio, const string& date)
        : description(desc), completed(false), priority(prio), dueDate(date) {}
};


void AddTask(vector<Task>& todoList, const string& taskDescription, int priority, const string& dueDate) {
    todoList.push_back(Task(taskDescription, priority, dueDate));
    cout << "Task added: " << taskDescription << endl;
}

void EditTask(vector<Task>& todoList, int taskIndex, const string& taskDescription, int priority, const string& dueDate) {
    if (taskIndex >= 0 && taskIndex < static_cast<int>(todoList.size())) {
        Task& task = todoList[taskIndex];
        task.description = taskDescription;
        task.priority = priority;
        task.dueDate = dueDate;
        cout << "Task edited: " << taskDescription << endl;
    } else {
        cout << "Invalid task index." << endl;
    }
}

void MarkTaskAsCompleted(vector<Task>& todoList, int taskIndex) {
    if (taskIndex >= 0 && taskIndex < static_cast<int>(todoList.size())) {
        Task& task = todoList[taskIndex];
        task.completed = true;
        cout << "Task marked as completed: " << task.description << endl;
    } else {
        cout << "Invalid task index." << endl;
    }
}


void DeleteTask(vector<Task>& todoList, int taskIndex) {
    if (taskIndex >= 0 && taskIndex < static_cast<int>(todoList.size())) {
        cout << "Deleted task: " << todoList[taskIndex].description << endl;
        todoList.erase(todoList.begin() + taskIndex);
    } else {
        cout << "Invalid task index." << endl;
    }
}

void SortTasks(vector<Task>& todoList) {
    sort(todoList.begin(), todoList.end(), [](const Task& a, const Task& b) {
        if (a.priority != b.priority) {
            return a.priority < b.priority;
        }
        return a.dueDate < b.dueDate;
    });
}


void DisplayTodoList(const vector<Task>& todoList) {
    if (todoList.empty()) {
        cout << "The to-do list is empty." << endl;
    } else {
        cout << "To-Do List:" << endl;
        for (size_t i = 0; i < todoList.size(); ++i) {
            cout << "[" << (todoList[i].completed ? "X" : " ") << "] "
                      << setw(3) << i + 1 << ". "
                      << "Priority: " << todoList[i].priority << " - "
                      << "Due Date: " << todoList[i].dueDate << " - "
                      << todoList[i].description << endl;
        }
    }
}

void SaveTodoListToFile(const vector<Task>& todoList, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const Task& task : todoList) {
            file << task.description << " "
                 << task.priority << " "
                 << task.dueDate << " "
                 << (task.completed ? "1" : "0") << endl;
        }
        cout << "To-do list saved to '" << filename << "'." << endl;
        file.close();
    } else {
        cerr << "Error opening file for saving." << endl;
    }
}

void LoadTodoListFromFile(vector<Task>& todoList, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        todoList.clear();
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string taskDescription, dueDate;
            int priority, completed;
            iss >> taskDescription >> priority >> dueDate >> completed;
            todoList.push_back({taskDescription, priority, dueDate});
            todoList.back().completed = (completed == 1);
        }
        cout << "To-do list loaded from '" << filename << "'." << endl;
        file.close();
    } else {
        cerr << "Error opening file for loading." << endl;
    }
}

int main() {
    vector<Task> todoList;
    string filename = "todolist.txt"; 

    LoadTodoListFromFile(todoList, filename);

    while (true) {
        cout << "To-Do List Manager" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. Edit Task" << endl;
        cout << "3. Mark Task as Completed" << endl;
        cout << "4. Delete Task" << endl;
        cout << "5. Sort Tasks" << endl;
        cout << "6. Display To-Do List" << endl;
        cout << "7. Save To-Do List" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                cin.ignore(); 
                cout << "Enter task description: ";
                string taskDescription;
                getline(cin, taskDescription);
                cout << "Enter task priority (1-5): ";
                int priority;
                cin >> priority;
                cin.ignore(); 
                cout << "Enter due date (e.g., YYYY-MM-DD): ";
                string dueDate;
                getline(cin, dueDate);
                AddTask(todoList, taskDescription, priority, dueDate);
                break;
            }
            case 2: {
                int taskIndex;
                cout << "Enter task index to edit: ";
                cin >> taskIndex;
                cin.ignore(); 
                cout << "Enter task description: ";
                string taskDescription;
                getline(cin, taskDescription);
                cout << "Enter task priority (1-5): ";
                int priority;
                cin >> priority;
                cin.ignore(); 
                cout << "Enter due date (e.g., YYYY-MM-DD): ";
                string dueDate;
                getline(cin, dueDate);
                EditTask(todoList, taskIndex - 1, taskDescription, priority, dueDate);
                break;
            }
            case 3: {
                int taskIndex;
                cout << "Enter task index to mark as completed: ";
                cin >> taskIndex;
                MarkTaskAsCompleted(todoList, taskIndex - 1); 
                break;
            }
            case 4: {
                int taskIndex;
                cout << "Enter task index to delete: ";
                cin >> taskIndex;
                DeleteTask(todoList, taskIndex - 1); 
                break;
            }
            case 5: {
                SortTasks(todoList);
                cout << "Tasks sorted by priority and due date." << endl;
                break;
            }
            case 6: {
                DisplayTodoList(todoList);
                break;
            }
            case 7: {
                SaveTodoListToFile(todoList, filename);
                break;
            }
            case 8: {
                SaveTodoListToFile(todoList, filename);
                cout << "Exiting the program." << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice. Please select a valid option." << endl;
                break;
            }
        }
    }

    return 0;
}

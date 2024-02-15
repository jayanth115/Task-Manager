#include <bits/stdc++.h>
using namespace std;

class Task
{
public:
    string description;
    bool completed;
    int priority;

    Task(const string &desc, int prio)
    {
        description = desc;
        completed = false;
        priority = prio;
    }
};

class TaskManager
{
private:
    vector<Task> tasks;
    string filename;

public:
    TaskManager(const string &filename)
    {
        this->filename = filename;
        loadTasks();
    }

    void addTask(const string &description, int priority)
    {
        Task newTask(description, priority);
        tasks.push_back(newTask);
        cout << "Task added successfully.\n";
    }

    void viewTasks()
    {
        if (tasks.empty())
        {
            cout << "No tasks available.\n";
            return;
        }

        cout << "Tasks:\n";
        for (size_t i = 0; i < tasks.size(); ++i)
        {
            cout << i + 1 << ". Priority: " << tasks[i].priority << " | "
                 << (tasks[i].completed ? "[X] " : "[ ] ") << tasks[i].description << "\n";
        }
    }

    void markTaskComplete(size_t index)
    {
        if (index >= 1 && index <= tasks.size())
        {
            tasks[index - 1].completed = true;
            cout << "Task marked as complete.\n";
        }
        else
        {
            cout << "Invalid task index.\n";
        }
    }

    void deleteTask(size_t index)
    {
        if (index >= 1 && index <= tasks.size())
        {
            tasks.erase(tasks.begin() + index - 1);
            cout << "Task deleted successfully.\n";
        }
        else
        {
            cout << "Invalid task index.\n";
        }
    }

    void saveTasks()
    {
        ofstream outFile(filename);

        if (outFile.is_open())
        {
            for (const Task &task : tasks)
            {
                outFile << task.completed << " | " << task.priority << " | " << task.description << "\n";
            }

            cout << "Tasks saved to file.\n";
        }
        else
        {
            cout << "Unable to open the file for saving tasks.\n";
        }

        outFile.close();
    }

    void loadTasks()
    {
        ifstream inFile(filename);

        if (inFile.is_open())
        {
            tasks.clear();

            string line;
            while (getline(inFile, line))
            {
                size_t pos1 = line.find(" | ");
                size_t pos2 = line.find(" | ", pos1 + 1);

                bool completed = line.substr(0, pos1) == "1";
                int priority = stoi(line.substr(pos1 + 3, pos2 - pos1 - 3));
                string description = line.substr(pos2 + 3);

                Task task(description, priority);
                task.completed = completed;
                tasks.push_back(task);
            }

            cout << "Tasks loaded from file.\n";
        }
        else
        {
            cout << "No previous tasks found.\n";
        }

        inFile.close();
    }
};

int main()
{
    TaskManager taskManager("tasks.txt");
    int choice;

    do
    {
        cout << "\nTask Manager Menu:\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task as Complete\n";
        cout << "4. Delete Task\n";
        cout << "5. Save Tasks\n";
        cout << "6. Load Tasks\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string description;
            int priority;
            cout << "Enter task description: ";
            cin.ignore();
            getline(cin, description);
            cout << "Enter task priority (1 - low, 2 - medium, 3 - high): ";
            cin >> priority;
            taskManager.addTask(description, priority);
            break;
        }
        case 2:
            taskManager.viewTasks();
            break;
        case 3:
        {
            size_t index;
            cout << "Enter the task index to mark as complete: ";
            cin >> index;
            taskManager.markTaskComplete(index);
            break;
        }
        case 4:
        {
            size_t index;
            cout << "Enter the task index to delete: ";
            cin >> index;
            taskManager.deleteTask(index);
            break;
        }
        case 5:
            taskManager.saveTasks();
            break;
        case 6:
            taskManager.loadTasks();
            break;
        case 0:
            cout << "Exiting the Task Manager.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}

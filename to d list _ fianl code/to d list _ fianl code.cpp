#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;
struct DueDate {
    int due_day;
    int due_month;
    int due_year;
};

struct tasks {
    string title;
    string details;
    bool done = false;
    int priority = 0;
    DueDate date = { 0, 0, 0 };
};

struct account_details {
    string username;
    string password;
    tasks list_of_tasks[100];
    int task_count = 0;
    tasks doneTasks[100];
    int doneCount = 0;
};

account_details users[100];
int userCount = 0;
int currentUser = -1;

void menu1();
void sign_up();
void login();
void add_task(account_details& user); // Changed to pass user by reference
void update_task();
void display_task(tasks task[], int task_count);
void display_overdue(tasks task[], int task_count);
void mark_task_done(int userCount);
void viewDoneTasks(int userCount);
void deletetask(account_details& user, int& task_count);
void search(string neededTask, int userCount);
DueDate readDate(string dateString);
void readUserTasks(account_details& user);
void readdonetasks(account_details& user);
void writeDoneTasks(account_details& users);
void writeUserTasks(account_details& users);
void writeAllUsers();
int mainmenu();  // to show menu options and let user enter his choice


DueDate readDate(string dateString)
{
    DueDate date;
    // Find the position of the first slash
    int slashPosition = dateString.find("/");
    // Extract the day from the string and convert it to an integer
    date.due_day = stoi(dateString.substr(0, slashPosition));
    // Remove the day and the slash from the string
    dateString = dateString.substr(slashPosition + 1);
    // Find the position of the second slash
    slashPosition = dateString.find("/");
    // Extract the month from the string and convert it to an integer
    date.due_month = stoi(dateString.substr(0, slashPosition));
    // Extract the year from the string and convert it to an integer
    date.due_year = stoi(dateString.substr(slashPosition + 1));
    return date;
}

void readUserTasks(account_details& user) {

    ifstream userFile(user.username + ".txt");
    if (userFile.is_open()) {
        userFile >> user.task_count;
        userFile.ignore();
        for (int i = 0; i < user.task_count; i++)
        {
            // Read the title of the task
            getline(userFile, user.list_of_tasks[i].title);
            // Read the description of the task
            getline(userFile, user.list_of_tasks[i].details);
            // Read the due date of the task as a string
            string dateString;
            getline(userFile, dateString);
            // Convert the string date to a Date structure
            user.list_of_tasks[i].date = readDate(dateString);
            // Read the completion status of the task
            userFile >> user.list_of_tasks[i].done;
            // Read the priority of the task
            userFile >> user.list_of_tasks[i].priority;
            userFile.ignore();
            userFile.close();
        }
    }
    else {
        cout << "Error: Unable to open user file for reading tasks." << endl;
    }
}
void readdonetasks(account_details& user) {
    ifstream donetasks(user.username + "done tasks.txt");
    if (donetasks.is_open()) {
        donetasks >> user.doneCount;
        donetasks.ignore();

        for (int i = 0; i < user.doneCount; i++)
        {
            // Read the title of the task
            getline(donetasks, user.doneTasks[i].title);
            // Read the description of the task
            getline(donetasks, user.doneTasks[i].details);
            // Read the due date of the task as a string
            string dateString;
            getline(donetasks, dateString);
            // Convert the string date to a Date structure
            user.doneTasks[i].date = readDate(dateString);
            // Read the completion status of the task
            donetasks >> user.doneTasks[i].done;
            // Read the priority of the task
            donetasks >> user.doneTasks[i].priority;
            donetasks.ignore();
        }
    }
    else {
        cout << "Error: Unable to open user file for reading done tasks." << endl;
    }
    // Close the file
    donetasks.close();
}


// Function to read all users and their tasks from a file named "users.txt"
void readAllUsers()
{
    // Open the file
    ifstream file("users.txt");
    // If the file is not open, return
    if (!file.is_open())
        return;
    // While not at the end of the file
    while (!file.eof())
    {
        // Read the username
        getline(file, users[userCount].username);
        // Read the password
        getline(file, users[userCount].password);
        // Read the tasks of the user
        readUserTasks(users[userCount]);
        readdonetasks(users[userCount]);
        // Increment the user count
        userCount++;
    }
    // Close the file
    file.close();
}
void writeDoneTasks(account_details& users)
{
    // Open the file
    ofstream donetasks(users.username + "done tasks.txt");
    // Write the number of tasks
    donetasks << users.doneCount << endl;
    for (int i = 0; i < users.doneCount; i++)
    {
        // Write the title of the task
        donetasks << users.doneTasks[i].title << endl;
        // Write the description of the task
        donetasks << users.doneTasks[i].details << endl;
        // Write the due date of the task
        donetasks << users.doneTasks[i].date.due_day << "/" << users.doneTasks[i].date.due_month << "/" << users.doneTasks[i].date.due_year << endl;
        // Write the completion status of the task
        donetasks << users.doneTasks[i].done << endl;
        // Write the priority of the task
        donetasks << users.doneTasks[i].priority << endl;
        if (i < users.doneCount - 1) {
            donetasks << endl;
        }
    }
    // Close the file
    donetasks.close();
}

void writeUserTasks(account_details& users)
{
    // Open the file
    ofstream file(users.username + ".txt");
    // Write the number of tasks
    file << users.task_count << endl;
    for (int i = 0; i < users.task_count; i++)
    {
        // Write the title of the task
        file << users.list_of_tasks[i].title << endl;
        // Write the description of the task
        file << users.list_of_tasks[i].details << endl;
        // Write the due date of the task
        file << users.list_of_tasks[i].date.due_day << "/" << users.list_of_tasks[i].date.due_month << "/" << users.list_of_tasks[i].date.due_year << endl;
        // Write the completion status of the task
        file << users.list_of_tasks[i].done << endl;
        // Write the priority of the task
        file << users.list_of_tasks[i].priority << endl;
        if (i < users.task_count - 1) {
            file << endl;
        }
    }
    // Close the file
    file.close();
}


void writeAllUsers()
{
    // Open the file
    ofstream file("users.txt");
    for (int i = 0; i < userCount; i++)
    {
        // Write the username
        file << users[i].username << endl;
        // Write the password
        file << users[i].password;
        // If not the last user, write a newline
        if (i < userCount - 1)
            file << endl;
        // Write the tasks of the user
        writeUserTasks(users[i]);
        writeDoneTasks(users[i]);
    }
    // Close the file
    file.close();
}

void menu1() {
    int choice;
    do {
        cout << "Choose one of the two options:\n";
        cout << "1.Sign up\n" << "2.Login\n";
        cout << "Your choice is (1 or 2): ";
        cin >> choice;
        if (choice == 1)
            sign_up();
        else if (choice == 2)
            login();
        else
            cout << "\nINVALID OPTION!\n\n";
    } while (currentUser == -1);
}

void sign_up() {
    account_details newUser;
    cout << "Create a username:\n";
    cin >> newUser.username;
    cout << "Enter your password: ";
    cin >> newUser.password;
    users[userCount].username = newUser.username;
    users[userCount].password = newUser.password;
    currentUser = userCount;
    userCount++;
}

void login() {
    string input_username, input_password;
    bool found = false;
    cout << "Enter your username: ";
    cin >> input_username;
    cout << "Enter your password: ";
    cin >> input_password;

    for (int i = 0; i < userCount; i++) {
        if (users[i].username == input_username && users[i].password == input_password) {
            cout << "Login successful!" << endl;
            currentUser = i;
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "Login failed! Invalid username or password.\n" << endl;
    }
}

void add_task(account_details& user) { // Changed to pass user by reference
    tasks newTask;
    cout << "Enter the title of the task: ";
    cin.ignore(); // Ignore any remaining newline characters in the buffer
    getline(cin, newTask.title);
    cout << "Enter the details of the task: ";
    getline(cin, newTask.details);
    cout << "Enter the priority of the task: ";
    cin >> newTask.priority;
    cout << "Enter the due date (day month year): ";
    cin >> newTask.date.due_day >> newTask.date.due_month >> newTask.date.due_year;
    user.list_of_tasks[user.task_count] = newTask;
    user.task_count++;
}

void display_task(tasks task[], int task_count) {

    int lastIndex = task_count - 1;
    int max = -1;
    int maxIndex = -1;
    for (int i = 0; i < task_count; i++) {
        max = -1;
        maxIndex = -1;
        for (int j = 0; j <= lastIndex; j++)
        {
            if (task[j].priority > max) {
                max = task[j].priority;
                maxIndex = j;
            }
        }
        swap(task[lastIndex], task[maxIndex]);
        lastIndex--;
    }

    cout << "Tasks To Do : " << endl;
    cout << "-----------------------------------" << endl;
    for (int i = 0; i < task_count; i++)
        cout << "Task " << i + 1 << " : " << task[i].title << endl;
    cout << "-----------------------------------" << endl;
}

void display_overdue(tasks task[], int task_count) {
    time_t current_time = time(0);
    tm local_time;
    localtime_s(&local_time, &current_time);
    cout << "Overdue Tasks:" << endl;
    cout << "-----------------------------------" << endl;
    for (int i = 0; i < task_count; i++) {
        if (local_time.tm_year + 1900 > task[i].date.due_year ||
            (local_time.tm_year + 1900 == task[i].date.due_year &&
                local_time.tm_mon + 1 > task[i].date.due_month) ||
            (local_time.tm_year + 1900 == task[i].date.due_year &&
                local_time.tm_mon + 1 == task[i].date.due_month &&
                local_time.tm_mday > task[i].date.due_day)) {
            cout << "Task " << i + 1 << ": " << task[i].title << endl;
            cout << "Due Date: " << task[i].date.due_day << "/" << task[i].date.due_month << "/" << task[i].date.due_year << endl;
        }
    }
    cout << "-----------------------------------" << endl;
}

void mark_task_done(int userCount) {
    int taskIndex;
    display_task(users[currentUser].list_of_tasks, users[currentUser].task_count);
    cout << "Enter the number of the task you have done: ";
    cin >> taskIndex;
    if (taskIndex >= 1 && taskIndex <= users[userCount].task_count) {
        tasks& taskToMarkDone = users[userCount].list_of_tasks[taskIndex - 1];
        taskToMarkDone.done = true;
        // to delete task from list of tasks and move it to the done tasks
        if (taskIndex >= 1 && taskIndex <= users[userCount].task_count) {
            for (int i = taskIndex - 1; i < users[userCount].task_count - 1; i++) {
                users[userCount].list_of_tasks[i] = users[userCount].list_of_tasks[i + 1];
            }
            users[userCount].task_count--;
        }
        users[userCount].doneCount++;
        users[userCount].doneTasks[users[userCount].doneCount - 1] = taskToMarkDone;

        cout << "Task marked as done." << endl;
    }
    else {
        cout << "Invalid task number." << endl;
    }
}

void viewDoneTasks(int userCount) {
    cout << "------------------------------------------\n";
    cout << "Done tasks:" << endl;
    for (int i = 0; i < users[userCount].doneCount; i++)
    {
        cout << i + 1 << "." << users[userCount].doneTasks[i].title << endl;
    }
    cout << "------------------------------------------\n";
}

void deletetask(account_details& user, int& task_count) {
    int del_task;
    display_task(users[currentUser].list_of_tasks, users[currentUser].task_count);
    cout << "Enter the task number to delete: ";
    cin >> del_task;
    if (del_task >= 1 && del_task <= task_count) {
        for (int i = del_task - 1; i < task_count - 1; i++) {
            user.list_of_tasks[i] = user.list_of_tasks[i + 1];
        }
        task_count--;
        cout << "Task deleted successfully." << endl;
    }
    else {
        cout << "Invalid task number." << endl;
    }
}

void search(string neededTask, int userCount) {
    int index;
    bool found = false; int choice = 0;
    for (int j = 0; j < users[userCount].task_count; j++) {
        if (neededTask == users[userCount].list_of_tasks[j].title) {
            cout << "Task found." << endl;
            found = true;
            if (found) {
                cout << "Details: " << users[userCount].list_of_tasks[j].details << endl;
                cout << "Priority: " << users[userCount].list_of_tasks[j].priority << endl;
                cout << "Duedate: " << users[userCount].list_of_tasks[j].date.due_day << "/" << users[userCount].list_of_tasks[j].date.due_month << "/" << users[userCount].list_of_tasks[j].date.due_year << endl;
            }
        }
    }
    if (found == false) {
        cout << "Task not found." << endl;
    }

}

void update_task() {
    int taskIndex;
    display_task(users[currentUser].list_of_tasks, users[currentUser].task_count);
    cout << "Enter the number of the task you want to update: ";
    cin >> taskIndex;

    if (taskIndex < 1 || taskIndex > users[currentUser].task_count) {
        cout << "Invalid task number." << endl;
        return;
    }
    tasks& taskToUpdate = users[currentUser].list_of_tasks[taskIndex - 1];
    cout << "Select what you want to update:" << endl;
    cout << "1. Title" << endl;
    cout << "2. Details" << endl;
    cout << "3. Priority" << endl;
    cout << "4. Due Date" << endl;
    cout << "Your choice: ";
    int updateChoice;
    cin >> updateChoice;
    switch (updateChoice) {
    case 1:
        cout << "Enter the new title: ";
        cin.ignore(); // Ignore any remaining newline characters in the buffer
        getline(cin, taskToUpdate.title);
        break;
    case 2:
        cout << "Enter the new details: ";
        cin.ignore(); // Ignore any remaining newline characters in the buffer
        getline(cin, taskToUpdate.details);
        break;
    case 3:
        cout << "Enter the new priority: ";
        cin >> taskToUpdate.priority;
        break;
    case 4:
        cout << "Enter the new due date (day month year): ";
        cin >> taskToUpdate.date.due_day >> taskToUpdate.date.due_month >> taskToUpdate.date.due_year;
        break;
    default:
        cout << "Invalid update option." << endl;
        break;
    }

}

int mainmenu()
{
    int choice1;
    cout << " \n===================================================================\n";
    cout << " TO DO LIST MENU \n";
    cout << "======================================================================\n";
    cout << " OPTIONS:\n";
    cout << "1. Add new task" << endl;
    cout << "2. Search for a task" << endl;
    cout << "3. View Tasks" << endl;
    cout << "4. View overdue tasks" << endl;
    cout << "5. Delete a Task" << endl;
    cout << "6. Update a task" << endl;
    cout << "7. Mark task as done" << endl;
    cout << "8. View done tasks" << endl;
    cout << "0. Terminate program" << endl;
    cout << "choose your option from the menu: ";
    cin >> choice1;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> choice1;
    }
    switch (choice1) {
    case 1:
        add_task(users[currentUser]);
        break;
    case 2: {
        string neededTask;
        cout << "Enter the title of the task you want to search for: ";
        cin.ignore();
        getline(cin, neededTask);
        search(neededTask, currentUser);
        break;
    }
    case 3:
        display_task(users[currentUser].list_of_tasks, users[currentUser].task_count);
        break;
    case 4:
        display_overdue(users[currentUser].list_of_tasks, users[currentUser].task_count);
        break;
    case 5:
        deletetask(users[currentUser], users[currentUser].task_count);
        break;
    case 6:
        update_task();
        break;
    case 7:
        mark_task_done(currentUser);
        break;
    case 8:
        viewDoneTasks(currentUser);
        break;
    case 0:
        cout << "Terminating the program." << endl;
        break;
    default:
        cout << "Invalid option. Please try again." << endl;
        break;
    }
    return choice1;
}

int main() {
    readAllUsers();
    cout << "WELCOME TO YOUR TO DO LIST\n\n";
    menu1();

    int choice;

    do {
        choice = mainmenu();
    } while (choice != 0);

    writeAllUsers();
    return 0;
}
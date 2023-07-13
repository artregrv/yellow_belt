#include <iostream>
#include <map>
#include <string>
#include <tuple>

// Перечислимый тип для статуса задачи
/*enum class TaskStatus 
{
	NEW,          // новая
	IN_PROGRESS,  // в разработке
	TESTING,      // на тестировании
	DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = std::map<TaskStatus, int>;*/

class TeamTasks 
{
public:
	// Получить статистику по статусам задач конкретного разработчика
 	 const TasksInfo &GetPersonTasksInfo(const std::string& person) const
	{
		return _teamTasks.at(person);
	}
  
 	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
 	void AddNewTask(const std::string &person)
	{
		if (_teamTasks.count(person) == 0) {
			_teamTasks[person][TaskStatus::NEW] += 0;
			_teamTasks[person][TaskStatus::IN_PROGRESS] += 0;		
			_teamTasks[person][TaskStatus::TESTING] += 0;
			_teamTasks[person][TaskStatus::DONE] += 0;
		}
		if (_teamTasks[person].empty()) {
			_teamTasks[person][TaskStatus::NEW] += 0;
			_teamTasks[person][TaskStatus::IN_PROGRESS] += 0;		
			_teamTasks[person][TaskStatus::TESTING] += 0;
			_teamTasks[person][TaskStatus::DONE] += 0;
		}
		_teamTasks[person][TaskStatus::NEW] += 1;
	}
  
 	// Обновить статусы по данному количеству задач конкретного разработчика,
  	// подробности см. ниже
 	std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(
     	const std::string &person, int taskCount)
	{
		TasksInfo updatedTasks;
		TasksInfo untouchedTasks;

		TasksInfo personTasks = _teamTasks[person];

		int tasksToNextStatus = 0;
		for (auto &status : personTasks) {
			//std::cout << "status number\n";
			if (status.first == TaskStatus::DONE) {
				//std::cout << tasksToNextStatus << "if DONE\n";
				if (tasksToNextStatus > 0) {
					updatedTasks[status.first] = tasksToNextStatus;
				}
				status.second += tasksToNextStatus;
				break;
			}	
			int updatedTasksCount = 0;
			if (tasksToNextStatus > 0) {
				//std::cout << tasksToNextStatus << "TTNS\n";
				updatedTasks[status.first] = tasksToNextStatus;
				updatedTasksCount = tasksToNextStatus;
			}
			if (taskCount >= status.second) {
				tasksToNextStatus = status.second;
				taskCount -= status.second;
				status.second = updatedTasksCount;
				//std::cout << taskCount << "TC\n";
			} else {
				tasksToNextStatus = taskCount;
				status.second -= taskCount;
				taskCount = 0;
				untouchedTasks[status.first] = status.second;
				status.second += updatedTasksCount;
				//std::cout << status.second << "SS\n";
			}
		}

		_teamTasks[person] = personTasks;

		return tie(updatedTasks, untouchedTasks);
	}

private:
	std::map<std::string, TasksInfo> _teamTasks;
};

using namespace std;

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main()
{
  TeamTasks tasks;
  /*tasks.AddNewTask("Ilia");
  for (int i = 0; i < 3; ++i) {
    tasks.AddNewTask("Ivan");
  }
  cout << "Ilia's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
  
  TasksInfo updated_tasks, untouched_tasks;
  
  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);
  
  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);*/

	for (int i = 0; i < 5; ++i) {
		tasks.AddNewTask("Alice");
	}
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	tasks.PerformPersonTasks("Alice", 5);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	tasks.PerformPersonTasks("Alice", 5);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	tasks.PerformPersonTasks("Alice", 1);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	for (int i = 0; i < 5; ++i) {
		tasks.AddNewTask("Alice");
	}
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	tasks.PerformPersonTasks("Alice", 100);
	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
	return 0;
}

#include "TaskManager.h"
#include <algorithm>
#include <iostream>

TaskManager::TaskManager() : currTaskId(0) {}

void TaskManager::assignTask(const std::string& personName, const Task& task) {
    Task newTask(task);
    newTask.setId(currTaskId++);
    
    for (auto& member : team) {
        if (member.getName() == personName) {
            member.assignTask(newTask);
            return;
        }
    }
    for (auto& member : team) {
        if (member.getName().empty()) {
            member = Person(personName);
            member.assignTask(newTask);
            return;
        }
    }
    throw std::runtime_error("TaskManager is full");
}

void TaskManager::completeTask(const std::string& personName) {
    for (auto& member : team) {
        if (member.getName() == personName) {
            member.completeTask();
            return;
        }
    }
}

void TaskManager::bumpPriorityByType(TaskType type, int delta) {
    if (delta < 0) {
        return;
    }
    for (auto& member : team) {
        auto tasks = member.getTasks();
        auto updatedTasks = tasks.apply([type, delta](const Task& task) {
            if (task.getType() == type) {
                int newPriority = std::clamp(task.getPriority() + delta, 0, 100);
                Task updatedTask(newPriority, task.getType(), task.getDescription());
                updatedTask.setId(task.getId());
                return updatedTask;
            }
            return task;
        });
        member.setTasks(updatedTasks);
    }
}

void TaskManager::printAllEmployees() const {
    for (const auto& member : team) {
        if (!member.getName().empty()) {
            std::cout << member << std::endl;
        }
    }
}

void TaskManager::printAllTasks() const {
    SortedList<Task> allTasks;
    for (const auto& member : team) {
        if (!member.getName().empty()) {
            for (auto it = member.getTasks().begin(); it != member.getTasks().end(); ++it) {
                allTasks.insert(*it);
            }
        }
    }
    for (auto it = allTasks.begin(); it != allTasks.end(); ++it) {
        std::cout << *it << std::endl;
    }
}

void TaskManager::printTasksByType(TaskType type) const {
    SortedList<Task> filteredTasks;

    for (const auto& member : team) {
        if (!member.getName().empty()) {
            for (auto it = member.getTasks().begin(); it != member.getTasks().end(); ++it) {
                if ((*it).getType() == type) {
                    filteredTasks.insert(*it);
                }
            }
        }
    }

    for (auto it = filteredTasks.begin(); it != filteredTasks.end(); ++it) {
        std::cout << *it << std::endl;
    }
}

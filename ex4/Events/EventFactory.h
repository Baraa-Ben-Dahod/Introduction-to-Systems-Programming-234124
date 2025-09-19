#pragma once
#include "Pack.h"
#include <map>
#include <memory>
using std::exception;
using std::unique_ptr;
using std::make_unique;
using std::map;

class EventFactory {
public:
    unique_ptr<Event> createEvent(const string& eventType);
    unique_ptr<Pack> createPack(queue<string>& types, queue<int>& counts);
};
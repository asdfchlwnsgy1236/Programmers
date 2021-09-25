// URL: https://programmers.co.kr/learn/courses/30/lessons/42888

#include <map>
#include <string>
#include <vector>
// Note: The header below is for testing without using the site.
#include <iostream>

using vecstr = std::vector<std::string>;

enum class EventType{
	Enter, Leave, Change
};

struct Event{
	EventType type = EventType::Leave;
	std::string id, name;
};

vecstr solution(vecstr record){
	// Change to a format easier to work with (the event structure), and store the last name each user used.
	std::vector<Event> events;
	std::map<std::string, std::string> idname;
	for(auto const &rec : record){
		std::string::size_type first = rec.find_first_of(' ') + 1, second = rec.find_first_of(' ', first);
		Event event;
		switch(rec.front()){
			case 'E':
				event.type = EventType::Enter;
				break;
			case 'C':
				event.type = EventType::Change;
				break;
			default:
				event.type = EventType::Leave;
				break;
		}
		event.id = rec.substr(first, second - first);
		if(event.type != EventType::Leave){
			event.name = rec.substr(second + 1);
			idname[event.id] = event.name;
		}
		events.push_back(std::move(event));
	}

	// Return the vector of all enter and leave messages with the updated names.
	vecstr answer;
	for(auto &event : events){
		if(event.type != EventType::Change){
			answer.push_back(std::move(std::string{idname[event.id]}.append("´ÔÀÌ ")
				.append(event.type == EventType::Enter ? "µé¾î¿Ô" : "³ª°¬").append("½À´Ï´Ù.")));
		}
	}

	return answer;
}

// Note: Everything below this line is for testing without using the site.
int main(){
	std::vector<vecstr> problems{{"Enter uid1234 Muzi", "Enter uid4567 Prodo", "Leave uid1234", "Enter uid1234 Prodo", "Change uid4567 Ryan"}};
	for(auto const &problem : problems){
		for(auto const &line : problem){
			std::cout << line << '\n';
		}
		std::cout << "||\n";
		for(auto const &line : solution(problem)){
			std::cout << line << '\n';
		}
		std::cout << "\n////////////////\n\n";
	}

	return 0;
}

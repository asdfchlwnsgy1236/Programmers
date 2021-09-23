// URL: https://programmers.co.kr/learn/courses/30/lessons/72410

#include <cctype>
#include <cstring>
#include <iostream>
#include <string>
#include <utility>
// Note: The header below is for testing without using the site.
#include <vector>

std::string solution(std::string new_id){
	// Add valid characters forced to lowercase, but skip if the period comes first or there would be consecutive periods.
	std::string answer;
	char period = '.';
	for(int a = 0; a < new_id.size() && answer.size() < 15; ++a){
		if(std::isalnum(new_id[a]) || std::strchr("-_.", new_id[a])){
			if(new_id[a] == period && (answer.empty() || answer.back() == period)){
				continue;
			}
			answer.append(1, std::tolower(new_id[a]));
		}
	}

	// Handle the cases where the period is at the end, the ID is empty, and the ID's length is too short.
	if(answer.size() && answer.back() == period){
		answer.pop_back();
	}
	if(answer.empty()){
		answer.append(3, 'a');
	}
	else if(answer.size() < 3){
		answer.append(3 - answer.size(), answer[answer.size() - 1]);
	}

	return answer;
}

// Note: Everything below this line is for testing without using the site.
int main(){
	std::vector<std::string> problems{"...!@BaT#*..y.abcdefghijklm", "z-+.^.", "=.=", "123_.def", "abcdefghijklmn.p"};
	for(auto const &problem : problems){
		std::cout << problem << " -> " << solution(problem) << '\n';
	}

	return 0;
}

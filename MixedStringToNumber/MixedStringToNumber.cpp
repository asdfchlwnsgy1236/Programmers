// URL: https://programmers.co.kr/learn/courses/30/lessons/81301

#include <map>
#include <string>
// Note: The headers below are for testing without using the site.
#include <iostream>
#include <vector>

int solution(std::string s){
	// Replace each occurrence of the string form of a number with its corresponding number, then return the parsed number.
	std::map<std::string, std::string> conversionMap{{"zero", "0"}, {"one", "1"}, {"two", "2"}, {"three", "3"},
		{"four", "4"}, {"five", "5"}, {"six", "6"}, {"seven", "7"}, {"eight", "8"}, {"nine", "9"}};
	for(auto const &[str, num] : conversionMap){
		std::string::size_type pos = s.rfind(str);
		while(pos != std::string::npos){
			s.replace(pos, str.size(), num);
			pos = s.rfind(str, pos - 1);
		}
	}

	return std::stoi(s);
}

// Note: Everything below this line is for testing without using the site.
int main(){
	std::vector<std::string> problems{"one4seveneight", "23four5six7", "2three45sixseven", "123"};
	for(auto const &problem : problems){
		std::cout << problem << " -> " << solution(problem) << '\n';
	}

	return 0;
}

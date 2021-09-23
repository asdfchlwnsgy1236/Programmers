// URL: https://programmers.co.kr/learn/courses/30/lessons/60057

#include <string>
// Note: The headers below are for testing without using the site.
#include <iostream>
#include <vector>

using strsize_t = std::string::size_type;

int solution(std::string s){
	// Try all possible compressions, and return the size of the shortest result.
	strsize_t answer = s.size();
	for(strsize_t length = 1; length <= s.size() / 2; ++length){
		std::string result;
		strsize_t a = 0, b = length, count = 1;
		for(; b < s.size() - length + 1; a += length, b += length, ++count){
			if(s.compare(a, length, s, b, length)){
				if(count > 1){
					result.append(std::to_string(count));
				}
				result.append(s, a, length);
				count = 0;
			}
		}
		if(count > 1){
			result.append(std::to_string(count));
		}
		result.append(s, a, s.size() - a);
		answer = std::min(answer, result.size());
	}

	return static_cast<int>(answer);
}

// Note: Everything below this line is for testing without using the site.
int main(){
	std::vector<std::string> problems{"aabbaccc", "ababcdcdababcdcd", "abcabcdede", "abcabcabcabcdededededede", "xababcdcdababcdcd"};
	for(auto const &problem : problems){
		std::cout << problem << " -> " << solution(problem) << '\n';
	}

	return 0;
}

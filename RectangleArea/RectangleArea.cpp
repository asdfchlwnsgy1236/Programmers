// URL: https://programmers.co.kr/learn/courses/30/lessons/12974

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>

// TODO: Score of 63.6%, must fix two test cases for correctness, and improve time complexity for efficiency test cases (all failed).

using vecint = std::vector<int>;

struct CompareX{
	bool operator()(vecint const *a, vecint const *b) const{
		return (*a)[0] == (*b)[0] ? (*a)[2] < (*b)[2] : (*a)[0] < (*b)[0];
	}
};

struct CompareY{
	bool operator()(vecint const *a, vecint const *b) const{
		return (*a)[1] == (*b)[1] ? (*a)[3] < (*b)[3] : (*a)[1] < (*b)[1];
	}
};

long long solution(std::vector<std::vector<int>> rectangles){
	std::map<int, std::set<vecint const *, CompareX>> xs;
	for(auto const &rect : rectangles){
		xs[rect[0]].insert(&rect);
		xs[rect[2]].insert(&rect);
	}

	std::set<vecint const *, CompareY> ys;
	int oldx = -1;
	long long answer = 0;
	for(auto xit = xs.begin(); xit != xs.end(); ++xit){
		if(!ys.empty()){
			int width = xit->first - oldx, height = 0, y1 = -1, y2 = -1;
			for(auto yit = ys.begin(); yit != ys.end(); ++yit){
				int const ty1 = (**yit)[1], ty2 = (**yit)[3];
				if(ty1 <= y2){
					y2 = std::max(y2, ty2);
				}
				else{
					height += y2 - y1;
					y1 = ty1;
					y2 = ty2;
				}
			}
			height += y2 - y1;
			answer += static_cast<long long>(width) * height;
		}

		ys.insert(xit->second.begin(), xit->second.end());
		oldx = xit->first;
		for(auto yit = ys.begin(); yit != ys.end();){
			(**yit)[2] == oldx ? yit = ys.erase(yit) : ++yit;
		}
	}

	return answer;
}

int main(){
	std::vector<std::vector<std::vector<int>>> problems{{{0, 1, 4, 4}, {3, 1, 5, 3}},
		{{1, 1, 6, 5}, {2, 0, 4, 2}, {2, 4, 5, 7}, {4, 3, 8, 6}, {7, 5, 9, 7}}};
	for(auto const &problem : problems){
		std::cout << solution(problem) << '\n';
	}

	return 0;
}

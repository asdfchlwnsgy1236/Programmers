// URL: https://programmers.co.kr/learn/courses/30/lessons/12974

#include <algorithm>
#include <iostream>
#include <map>
#include <random>
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

long long solution(std::vector<vecint> rectangles){
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

long long bruteforce(std::vector<vecint> rectangles){
	int matrix[16][16]{};
	for(auto const &a : rectangles){
		for(int b = a[1]; b < a[3]; ++b){
			for(int c = a[0]; c < a[2]; ++c){
				matrix[b][c] = 1;
			}
		}
	}
	long long answer = 0;
	for(auto const &a : matrix){
		for(auto const &b : a){
			answer += b;
		}
	}

	return answer;
}

int main(){
	//std::vector<std::vector<vecint>> problems{{{0, 1, 4, 4}, {3, 1, 5, 3}},
	//	{{1, 1, 6, 5}, {2, 0, 4, 2}, {2, 4, 5, 7}, {4, 3, 8, 6}, {7, 5, 9, 7}}};
	//for(auto const &problem : problems){
	//	//std::cout << solution(problem) << '\n';
	//	std::cout << solution(problem) << '\t' << bruteforce(problem) << '\n';
	//}

	//std::vector<std::vector<vecint>> rproblems;
	//std::mt19937 rng(std::random_device{}());
	//std::uniform_int_distribution<int> ud(0, 16);
	//for(int a = 0; a < 16; ++a){
	//	std::vector<vecint> t0;
	//	for(int b = 0; b < ud(rng) / 2 + 2; ++b){
	//		vecint t1;
	//		for(int c = 0; c < 4; ++c){
	//			t1.push_back(ud(rng));
	//		}
	//		if(t1[0] > t1[2]){
	//			std::swap(t1[0], t1[2]);
	//		}
	//		else if(t1[0] == t1[2]){
	//			t1[0] == 16 ? --t1[0] : ++t1[2];
	//		}
	//		if(t1[1] > t1[3]){
	//			std::swap(t1[1], t1[3]);
	//		}
	//		else if(t1[1] == t1[3]){
	//			t1[1] == 16 ? --t1[1] : ++t1[3];
	//		}
	//		t0.push_back(std::move(t1));
	//	}
	//	rproblems.push_back(std::move(t0));
	//}
	//for(auto const &a : rproblems){
	//	for(auto const &b : a){
	//		for(auto const &c : b){
	//			std::cout << '\t' << c;
	//		}
	//		std::cout << '\n';
	//	}
	//	long long mine = solution(a), correct = bruteforce(a);
	//	std::cout << "my solution: " << solution(a) << " / brute-force solution: " << bruteforce(a);
	//	if(mine != correct){
	//		std::cout << " ////////////////////////////////";
	//	}
	//	std::cout << "\n________________\n\n";
	//}

	std::vector<vecint> problem{{13, 5, 15, 10}, {2, 14, 10, 15}, {2, 2, 10, 6}, {1, 3, 14, 4}, {5, 2, 15, 3}};
	std::cout << "my solution: " << solution(problem) << " / brute-force solution: " << bruteforce(problem) << '\n';

	return 0;
}

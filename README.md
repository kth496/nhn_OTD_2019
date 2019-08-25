###### gcc 8.1.0 에서 테스트 완료

## 문제 풀이 단계

##### 1. 주어진 좌표, 반지름 정보를 바탕으로 원 간의 관계를 트리 or 그래프 구조로 변환

##### 2. 만들어진 구조에서 원과 원 사이의 최단 경로를 구함

풀이 초기에는 모든 간선에 가중치를 1로 설정한 무향 그래프를 구성하여 다익스트라 알고리즘으로 해결하려 했습니다. 하지만 가중치가 전부 1이라는건 있으나 마나한 조건이기도하고, 결정적으로 이 문제는 **경로**를 남겨야 하기때문에 선회했습니다.

문제 조건이 넉넉하여 재귀함수를 이용한 DFS로 구현해도 오버플로우가 발생하지 않을 것으로 예상됩니다.

시간복잡도는 **O(N<sup>2</sup>)** 입니다.

## 표현방법 및 변수 설명

1. `포함관계`

만약 **원 A**가 **원 B**에 완전히 포함되어 있으면, **원 A**의 상위 원은 **원 B**가 된다고 정의할 수 있습니다. 상위 원은 몇 겹이 존재하든 가장 **마지막**으로 자신을 포함한 것으로 정합니다. 예를 들어 문제에서 주어진 그림에 따르면 **원 11**은 상위 원으로 **원 10**을 가집니다.

2. `vector<tuple<int,int>> me_par_relation`

(상위 원 번호, 상위 원 반지름) 형태의 튜플을 가진 벡터입니다. 이 벡터는 어떠한 원의 상위 원 정보를 담고 있습니다. 예를 들어 **원 11**의 상위 원은 **원 10**이며, 이때 **원 10**의 반지름은 7입니다. 따라서 다음과 같이 값이 저장됩니다.

```c++
me_par_relation[11] = make_tuple(10,7);
```

문제 조건을 고려하여 총 길이 101, 모든 원소는 (0,10000) 으로 초기화하여 사용합니다.

3. `vector<tuple<int, int, int, int>> node`

(원 번호, X 좌표, Y 좌표, 반지름) 형태의 튜플을 가진 벡터입니다. 서로 겹치지 않는다는것이 검증된 모든 원의 정보를 담고 있습니다.

4. `int adj_mat[101][101]`

원과 원 사이의 위치 관계를 나타내는 인접 행렬(Adjacency matrix)입니다. **me_par_relation**의 정보를 바탕으로 계산상 편의를 위해 행렬로 재구성하여 사용합니다. 프로그램 전반에서 **map**이라는 매개변수로 호출됩니다.

### 함수 기능 설명

#### 1. **bool validation**

매개변수로 `vector<tuple<int, int>> &me_par_relation` `vector<tuple<int, int, int, int>> node` `tuple<int, int, int, int> newone)` 3개를 가집니다. 위에서 언급한 변수 두 가지를 받습니다. 추가적으로 받고있는 **newone**은 새롭게 입력받는 원의 정보 입니다. 이 함수는 존재하는 **me_par_relation**과 **node** 정보를 바탕으로, 새로 입력받는 원의 정보와 대조하여 유효한 것인지 판단하여 **bool** 자료형을 반환합니다. 유효하다면 **true**를 반환하며, 이와 더불어 **me_par_relation** 에 새로운 원의 상위 원 정보를 기록합니다.

[두 원의 위치 관계](https://doubleroot.in/lessons/circle/relative-postion-of-two-circles/)를 바탕으로 두 원이 서로 겹치는지 아닌지 판단할 수 있습니다. 겹치지 않는다면 이를 **유효**하다고 정의합니다. **유효**한 원은 반드시 상위 원을 가집니다. 두 원 사이의 포함관계 역시 두 원의 위치 관계에서 얻을 수 있습니다. 간단히 요약하면 우리의 프로그램에서는 *두 원의 중심 사이의 거리*를 `float ed` 함수를 통해 구합니다. 이와 더불어 *두 원의 반지름을 더한 값*과 *두 원의 반지름을 뺀 값* 까지 총 3개의 값을 활용해 두 원의 포함관계를 파악합니다.

**유효**한 상황은 크게 3가지 케이스로 나뉩니다.
   1. 두 원이 서로 완전히 분리되어 있음.
   2. 새로운 원이 기존 원을 상위 원으로 가짐. 이 경우엔 `me_par_relation[새로운 원] = (기존 원 번호, 기존 원 반지름)` 형태로 업데이트 합니다.
   3. 새로운 원이 기존 원의 상위 원이 됨. `me_par_relation[기존 원]` 을 호출해 이미 가지고 있는 상위 원의 반지름과 새로운 원의 반지름을 비교합니다. 새로운 원이 더 작다면 `me_par_relation[기존 원] = (새로운 원 번호, 새로운 원 반지름)` 형태로 업데이트 합니다.


#### 2. **void make_adj_matrix**

매개변수로 `int N` `int (*map)[101]` `vector<tuple<int, int>> &me_par_relation` 3개를 가집니다.

`int N` : 원의 갯수 입니다.

`int (*map)[101]` : 원과 원 사이의 연결 관계를 나타내는 `map`의 포인터 입니다.

`vector<tuple<int,int>> &me_par_relation` : 위에서 언급한 **me_par_relation**입니다.

**me_par_relation**의 모든 정보를 바탕으로 **map**의 값을 업데이트합니다. **map**은 모든 값이 0으로 초기화되어 있습니다. 값의 업데이트 방법은 예를 들어, `me_par_relation[A]` 를 호출하여 `(B,R)`을 얻었다고 가정해 봅시다. 이는 **원 A**의 상위 원이 **원 B**이고 반지름은 **R**이라는 것을 의미합니다. 간단히 말하면 **원 A**와 **원 B**가 서로 연결되어 있다고 할 수 있습니다. **map[A][B]** 와 **map[B][A]**의 값을 모두 1로 업데이트하면 연결관계를 나타낼 수 있습니다.

#### 3. **void findroute**

매개변수로 `string *ans_str` `int *answer` `const int obj` `int past` `int cur_loc` `int length` `string route_info` `const int (*map)[101]` 8개를 가집니다.

`string *ans_str` : 정답 문자열의 포인터입니다. 함수가 작동하다가 목표한 원에 도달할 경우 이 포인터를 통해 정답 문자열에 접근하여 업데이트 합니다.

`int *answer` : 정답에 도달하기까지 이동한 거리를 가진 값의 포인터입니다. 새로운 경로를 찾아내면 이 값과 비교하여 더 작은 쪽으로 업데이트하기 위한 용도입니다.

`const int obj` : 도착 원의 번호입니다.

`int past` : 현재 위치에 오기 바로 직전의 원 번호 입니다. 이 값이 없으면 왔던 길을 되돌아가는 경우가 생겨 무한 루프에 빠집니다.

`int cur_loc` : 현재 위치한 원의 번호를 나타냅니다.

`int length` : 출발 지점부터 현재 위치의 원 까지 이동한 경로의 길이를 나타냅니다.

`string route_info` : 현재까지 이동한 경로를 문자열로 가지고 있습니다.

`const (*map)[101]` : 원과 원 사이의 위치 관계를 나타내는 인접행렬입니다.

이 함수는 재귀함수입니다. 함수가 호출되면 가장 먼저 현 위치가 도착 지점인지 판단합니다. 만약 그렇다면 그동안 가지고 온 `length`를 `answer`과 비교합니다. `length`가 더 작다면 새로운 최단경로를 찾은 것이므로 `string *ans_str*` 을 `string route_info`로 업데이트 합니다.

현재 위치가 도착 지점이 아니라면 `map`을 바탕으로 현재 원과 연결된 모든 원으로 이동합니다. 이때 `int past`와 동일한 곳은 이미 지나온 곳이므로 다시 가지 않습니다.  새롭게 갈 곳을 정하면 `string route_info`에 갈 곳의 값을 추가하여 경로를 업데이트 합니다. 이제 이 모든 값을 다시 인자로 전달하여 함수를 재귀적으로 호출합니다.

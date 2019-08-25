###### gcc 8.1.0 ���� �׽�Ʈ �Ϸ�

### ���� Ǯ�� �ܰ�

##### 1. �־��� ��ǥ, ������ ������ �������� �� ���� ���踦 Ʈ�� or �׷��� ������ ��ȯ

##### 2. ������� �������� ���� �� ������ �ִ� ��θ� ����

Ǯ�� �ʱ⿡�� ��� ������ ����ġ�� 1�� ������ ���� �׷����� �����Ͽ� ���ͽ�Ʈ�� �˰��������� �ذ��Ϸ� �߽��ϴ�. ������ ����ġ�� ���� 1�̶�°� ������ ������ �����̱⵵�ϰ�, ���������� �� ������ **���**�� ���ܾ� �ϱ⶧���� ��ȸ�߽��ϴ�.

���� ������ �˳��Ͽ� ����Լ��� �̿��� DFS�� �����ص� �����÷ο찡 �߻����� ���� ������ ����˴ϴ�.

�ð����⵵�� **O(N<sup>2</sup>)** �Դϴ�.

### ǥ����� �� ���� ����

1. `���԰���`
   ���� **�� A**�� **�� B**�� ������ ���ԵǾ� ������, **�� A**�� ���� ���� **�� B**�� �ȴٰ� ������ �� �ֽ��ϴ�. ���� ���� �� ���� �����ϵ� ���� **������**���� �ڽ��� ������ ������ ���մϴ�. ���� ��� �������� �־��� �׸��� ������ **�� 11**�� ���� ������ **�� 10**�� �����ϴ�.

2. `vector<tuple<int,int>> me_par_relation`
   (���� �� ��ȣ, ���� �� ������) ������ Ʃ���� ���� �����Դϴ�. �� ���ʹ� ��� ���� ���� �� ������ ��� �ֽ��ϴ�. ���� ��� **�� 11**�� ���� ���� **�� 10**�̸�, �̶� **�� 10**�� �������� 7�Դϴ�. ���� ������ ���� ���� ����˴ϴ�.

```c++
me_par_relation[11] = make_tuple(10,7);
```

���� ������ �����Ͽ� �� ���� 101, ��� ���Ҵ� (0,10000) ���� �ʱ�ȭ�Ͽ� ����մϴ�.

3. `vector<tuple<int, int, int, int>> node`
   (�� ��ȣ, X ��ǥ, Y ��ǥ, ������) ������ Ʃ���� ���� �����Դϴ�. ���� ��ġ�� �ʴ´ٴ°��� ������ ��� ���� ������ ��� �ֽ��ϴ�.

4. `int adj_mat[101][101]`
   ���� �� ������ ��ġ ���踦 ��Ÿ���� ���� ���(Adjacency matrix)�Դϴ�. **me_par_relation**�� ������ �������� ���� ���Ǹ� ���� ��ķ� �籸���Ͽ� ����մϴ�. ���α׷� ���ݿ��� **map**�̶�� �Ű������� ȣ��˴ϴ�.

### �Լ� ��� ����

1.  **bool validation**
    �Ű������� `vector<tuple<int, int>> &me_par_relation` `vector<tuple<int, int, int, int>> node` `tuple<int, int, int, int> newone)` 3���� �����ϴ�. ������ ����� ���� �� ������ �޽��ϴ�. �߰������� �ް��ִ� **newone**�� ���Ӱ� �Է¹޴� ���� ���� �Դϴ�. �� �Լ��� �����ϴ� **me_par_relation**�� **node** ������ ��������, ���� �Է¹޴� ���� ������ �����Ͽ� ��ȿ�� ������ �Ǵ��Ͽ� **bool** �ڷ����� ��ȯ�մϴ�. ��ȿ�ϴٸ� **true**�� ��ȯ�ϸ�, �̿� ���Ҿ� **me_par_relation** �� ���ο� ���� ���� �� ������ ����մϴ�.

        [�� ���� ��ġ ����](https://doubleroot.in/lessons/circle/relative-postion-of-two-circles/)�� �������� �� ���� ���� ��ġ���� �ƴ��� �Ǵ��� �� �ֽ��ϴ�. ��ġ�� �ʴ´ٸ� �̸� **��ȿ**�ϴٰ� �����մϴ�. **��ȿ**�� ���� �ݵ�� ���� ���� �����ϴ�. �� �� ������ ���԰��� ���� �� ���� ��ġ ���迡�� ���� �� �ֽ��ϴ�. ������ ����ϸ� �츮�� ���α׷������� *�� ���� �߽� ������ �Ÿ�*�� `float ed` �Լ��� ���� ���մϴ�. �̿� ���Ҿ� *�� ���� �������� ���� ��*�� *�� ���� �������� �� ��* ���� �� 3���� ���� Ȱ���� �� ���� ���԰��踦 �ľ��մϴ�.

        **��ȿ**�� ��Ȳ�� ũ�� 3���� ���̽��� �����ϴ�.

        1. �� ���� ���� ������ �и��Ǿ� ����.
        2. ���ο� ���� ���� ���� ���� ������ ����.
        	�� ��쿣 `me_par_relation[���ο� ��] = (���� �� ��ȣ, ���� �� ������)` ���·� ������Ʈ �մϴ�.
        3. ���ο� ���� ���� ���� ���� ���� ��
        	`me_par_relation[���� ��]` �� ȣ���� �̹� ������ �ִ� ���� ���� �������� ���ο� ���� �������� ���մϴ�. ���ο� ���� �� �۴ٸ� `me_par_relation[���� ��] = (���ο� �� ��ȣ, ���ο� �� ������)` ���·� ������Ʈ �մϴ�.

2.  **void make_adj_matrix**
    �Ű������� `int N` `int (*map)[101]` `vector<tuple<int, int>> &me_par_relation` 3���� �����ϴ�.

        `int N` : ���� ���� �Դϴ�.

        `int (*map)[101]` : ���� �� ������ ���� ���踦 ��Ÿ���� `map`�� ������ �Դϴ�.

        `vector<tuple<int,int>> &me_par_relation` : ������ ����� **me_par_relation**�Դϴ�.

        **me_par_relation**�� ��� ������ �������� **map**�� ���� ������Ʈ�մϴ�. **map**�� ��� ���� 0���� �ʱ�ȭ�Ǿ� �ֽ��ϴ�. ���� ������Ʈ ����� ���� ���, `me_par_relation[A]` �� ȣ���Ͽ� `(B,R)`�� ����ٰ� ������ ���ô�. �̴� **�� A**�� ���� ���� **�� B**�̰� �������� **R**�̶�� ���� �ǹ��մϴ�. ������ ���ϸ� **�� A**�� **�� B**�� ���� ����Ǿ� �ִٰ� �� �� �ֽ��ϴ�. **map[A][B]** �� **map[B][A]**�� ���� ��� 1�� ������Ʈ�ϸ� ������踦 ��Ÿ�� �� �ֽ��ϴ�.

3.  **void findroute**
    �Ű������� `string *ans_str` `int *answer` `const int obj` `int past` `int cur_loc` `int length` `string route_info` `const int (*map)[101]` 8���� �����ϴ�.

        `string *ans_str` : ���� ���ڿ��� �������Դϴ�. �Լ��� �۵��ϴٰ� ��ǥ�� ���� ������ ��� �� �����͸� ���� ���� ���ڿ��� �����Ͽ� ������Ʈ �մϴ�.

        `int *answer` : ���信 �����ϱ���� �̵��� �Ÿ��� ���� ���� �������Դϴ�. ���ο� ��θ� ã�Ƴ��� �� ���� ���Ͽ� �� ���� ������ ������Ʈ�ϱ� ���� �뵵�Դϴ�.

        `const int obj` : ���� ���� ��ȣ�Դϴ�.

        `int past` : ���� ��ġ�� ���� �ٷ� ������ �� ��ȣ �Դϴ�. �� ���� ������ �Դ� ���� �ǵ��ư��� ��찡 ���� ���� ������ �����ϴ�.

        `int cur_loc` : ���� ��ġ�� ���� ��ȣ�� ��Ÿ���ϴ�.

        `int length` : ��� �������� ���� ��ġ�� �� ���� �̵��� ����� ���̸� ��Ÿ���ϴ�.

        `string route_info` : ������� �̵��� ��θ� ���ڿ��� ������ �ֽ��ϴ�.

        `const (*map)[101]` : ���� �� ������ ��ġ ���踦 ��Ÿ���� ��������Դϴ�.

        �� �Լ��� ����Լ��Դϴ�. �Լ��� ȣ��Ǹ� ���� ���� �� ��ġ�� ���� �������� �Ǵ��մϴ�. ���� �׷��ٸ� �׵��� ������ �� `length`�� `answer`�� ���մϴ�. `length`�� �� �۴ٸ� ���ο� �ִܰ�θ� ã�� ���̹Ƿ� `string *ans_str*` �� `string route_info`�� ������Ʈ �մϴ�.

        ���� ��ġ�� ���� ������ �ƴ϶�� `map`�� �������� ���� ���� ����� ��� ������ �̵��մϴ�. �̶� `int past`�� ������ ���� �̹� ������ ���̹Ƿ� �ٽ� ���� �ʽ��ϴ�.  ���Ӱ� �� ���� ���ϸ� `string route_info`�� �� ���� ���� �߰��Ͽ� ��θ� ������Ʈ �մϴ�. ���� �� ��� ���� �ٽ� ���ڷ� �����Ͽ� �Լ��� ��������� ȣ���մϴ�.
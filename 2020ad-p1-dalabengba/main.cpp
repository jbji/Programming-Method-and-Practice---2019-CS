/*
 * Description
很久很久以前，巨龙突然出现，带来灾难带走了公主又消失不见，王国十分危险，世间谁最勇敢，一位勇者赶来大声喊：“我要带上最好的剑，翻过最高的山，闯进最深的森林，把公主带回到面前”……最后，英雄 达拉崩巴斑得贝迪卜多比鲁翁 ，他战胜了巨龙 昆图库塔卡提考特苏瓦西拉松 ，国王把公主 米娅莫拉苏娜丹妮谢莉红  嫁给了 达拉崩巴斑得贝迪卜多比鲁翁 。

于是国王第二天要在 蒙达鲁克硫斯伯古比奇巴勒城  举办酒宴，一共准备了 N 桶酒。此时一位忠诚的仆人来报，有人在其中一桶酒里下毒，并且此毒要经过24小时后才会毒发身亡。现在距离晚会酒宴开始还有正好24小时，为在酒宴开始前找出哪一桶酒有毒，国王决定找一些小白鼠来试酒。（仆人不可能说谎，即一定有且只有一桶酒有毒）

聪明的 达拉崩巴斑得贝迪卜多比鲁翁  本着善良的天性，决定用尽量少的小白鼠来试酒。

请问最少需要多少只小白鼠试酒？

Input
样例输入有多组。

第一行输入整数 T 左小括號 斜體字 1 斜體字 小於等於 T 斜體字 小於等於 斜體字 10000 右小括號 表示有 T 组用例；

接下来 T 行，对于每组用例，输入一个正整数 n 左小括號 斜體字 1 斜體字 小於等於 n 斜體字 小於等於 斜體字 1 e 斜體字 18 右小括號，表示一共有 n 桶酒。

Output
对于每个用例输出一行一个数字，代表所需的最少小白鼠数量。

Sourse
北京理工大学2018年暑假集训算法总结赛 - Problem D
 */
#include <iostream>

int main() {
    int T;
    for (std::cin>>T;T>0;T--){
        long long N;
        std::cin >> N;
        int rats=0;
        N-=1; //将开log的映射整体前移
        while(N>=1){
            rats++;
            N/=2;
        }
        std::cout << rats << std::endl;
    }
    return 0;
}
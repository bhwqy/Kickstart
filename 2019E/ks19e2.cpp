#include <bits/stdc++.h>
using namespace std;

struct Slot {
    int code, eat;
    bool operator<(const Slot& s) const { return eat * s.code < s.eat * code; }
};
struct Schedule {
    int code, eat, id;
    bool operator<(const Schedule& s) const { return code < s.code; }
};

int main()
{
    int T;
    scanf("%d", &T);
    for (int cse = 1; cse <= T; ++cse) {
        int d, s;
        scanf("%d%d", &d, &s);
        vector<Slot> slots(s);
        vector<Schedule> schedule(d);
        vector<bool> ans(d, false);
        for (int i = 0; i < s; ++i)
            scanf("%d%d", &slots[i].code, &slots[i].eat);
        for (int i = 0; i < d; ++i) {
            scanf("%d%d", &schedule[i].code, &schedule[i].eat);
            schedule[i].id = i;
        }   
        sort(slots.begin(), slots.end());
        sort(schedule.begin(), schedule.end());
        int sum = 0;
        for (int i = 0; i < s; ++i) 
            sum += slots[i].code;
        int k = d - 1, now = 0;
        for (int i = s - 1; i >= 0; --i) {
            while (k >= 0 && schedule[k].code > sum) k--;
            if (k < 0) break;
            while (k >= 0 && schedule[k].code >= sum - slots[i].code) {
                int o = sum - schedule[k].code;
                long long d = 1ll * o * slots[i].eat / slots[i].code;
                if (d + now >= schedule[k].eat)
                    ans[schedule[k].id] = true;
                k--;
            }
            now += slots[i].eat;
            sum -= slots[i].code;
        }
        printf("Case #%d: ", cse);
        for (int i = 0; i < d; ++i) 
            if (ans[i]) 
                putchar('Y');
            else 
                putchar('N');
        puts("");
    }
    return 0;
}
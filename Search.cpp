
#include "Search.h"

using namespace std;

bool is_1_Subset_2(vector<string>& a , vector<string>& b)
{
    set<string> s_a(a.begin(), a.end());
    set<string> s_b(b.begin(), b.end());

    return includes(s_b.begin(), s_b.end(), s_a.begin(), s_a.end());
}


bool is_1_disj_2(vector<string> a , vector<string> b)
{
    set<string> s_a(a.begin(), a.end());
    set<string> s_b(b.begin(), b.end());

    vector<string> diff;
    set_difference(s_a.begin(), s_a.end(), s_b.begin(), s_b.end(), back_inserter(diff));
    return (diff.size() != s_a.size());
}




pair<vector<sfood> , vector<cfood>> search(bool view_all, vector<string>& keywords, bool any_key, vector<sfood>& simpleFood, vector<cfood>& complexFood)
{
    vector<sfood> result_s;
    vector<cfood> result_c;

    if (view_all)
    {
        result_s = simpleFood;
        result_c = complexFood;
    }
    else
    {
        if (any_key)
        {
            for (auto i : simpleFood)
            {
                if (is_1_disj_2(i.keywords, keywords))
                {
                    result_s.push_back(i);
                }
            }
            for (auto i : complexFood)
            {
                if (is_1_disj_2(i.keywords, keywords))
                {
                    result_c.push_back(i);
                }
            }
        }
        else
        {
            for (auto i : simpleFood)
            {
                if (is_1_Subset_2(i.keywords, keywords))
                {
                    result_s.push_back(i);
                }
            }
            for (auto i : complexFood)
            {
                if (is_1_Subset_2(i.keywords, keywords))
                {
                    result_c.push_back(i);
                }
            }
        }
    }

    return make_pair(result_s, result_c);
}


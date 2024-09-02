//
// Created by stellaura on 01/09/24.
//
#include <catch2/catch_all.hpp>
#include <span>
#include <string>
#include <vector>

using namespace std;

// 这个题凭什么是困难 他配么
// subspan 第二个参数是长度，不是位置
class Solution {
  public:
    vector<string> fullJustify(vector<string> &words, int maxWidth) {
        vector<string> ret;
        span span_words(words);
        int begin = 0;
        int end = 0;
        int size = words.size();
        int count = 0;
        while (end < size) {
            count += words[end].size() + 1;
            if (count - 1 > maxWidth) {
                // 不包含结尾的end
                ret.push_back(_fill(span_words.subspan(begin, end - begin), maxWidth));
                begin = end;
                count = 0;
            } else {
                end++;
            }
        }
        // 处理最后一行
        // 不包含结尾的end
        ret.push_back(_fill_left(span_words.subspan(begin, end - begin), maxWidth));
        return ret;
    }

  private:
    // span need to be passed by value
    static string _fill(span<string> words, int maxWidth) {
        string ret(maxWidth, ' ');
        int index = 0;

        if (words.size() == 1) {
            for (auto c : words[0]) {
                ret[index++] = c;
            }
            return ret;
        }

        int total_space = maxWidth;
        for (const auto &word : words) {
            total_space -= word.size();
        }
        int space_per_word = total_space / (words.size() - 1);
        int remain_space = total_space % (words.size() - 1);

        int count_remain_space = 0;
        for (int i = 0; i < words.size(); i++) {
            for (auto c : words[i]) {
                ret[index++] = c;
            }
            if (i != words.size() - 1) {
                if (count_remain_space < remain_space) {
                    index++;
                    count_remain_space++;
                }
                index += space_per_word;
            }
        }

        return ret;
    }

    static string _fill_left(span<string> words, int maxWidth) {
        string ret(maxWidth, ' ');

        int index = 0;
        for (int i = 0; i < words.size(); i++) {
            for (auto c : words[i]) {
                ret[index++] = c;
            }
            index++;
        }
        return ret;
    }
};

TEST_CASE("Test Solution", "[Solution]") {
    Solution s;
    vector<string> words = {"This", "is", "an", "example", "of", "text", "justification."};
    int maxWidth = 16;
    vector<string> result = s.fullJustify(words, maxWidth);
    vector<string> expected = {"This    is    an", "example  of text", "justification.  "};
    REQUIRE(result == expected);

    words = {"What", "must", "be", "acknowledgment", "shall", "be"};
    maxWidth = 16;
    result = s.fullJustify(words, maxWidth);
    expected = {"What   must   be", "acknowledgment  ", "shall be        "};
    REQUIRE(result == expected);

    words = {"Science", "is", "what",      "we",  "understand", "well",       "enough", "to", "explain",
             "to",      "a",  "computer.", "Art", "is",         "everything", "else",   "we", "do"};
    maxWidth = 20;
    result = s.fullJustify(words, maxWidth);
    expected = {"Science  is  what we", "understand      well", "enough to explain to",
                "a  computer.  Art is", "everything  else  we", "do                  "};
    REQUIRE(result == expected);

    words = {"ask", "not",  "what", "your", "country", "can", "do",   "for",    "you",
             "ask", "what", "you",  "can",  "do",      "for", "your", "country"};
    maxWidth = 16;
    result = s.fullJustify(words, maxWidth);
    expected = {"ask   not   what", "your country can", "do  for  you ask", "what  you can do", "for your country"};
    REQUIRE(result == expected);
}
/*
 * [68] Text Justification
 *
 * https://leetcode.com/problems/text-justification/description/
 *
 * algorithms
 * Hard (19.71%)
 * Total Accepted:    65.1K
 * Total Submissions: 330.3K
 * Testcase Example:  '[""]\n0'
 *
 * 
 * Given an array of words and a length L, format the text such that each line
 * has exactly L characters and is fully (left and right) justified.
 * ⁠
 * 
 * 
 * You should pack your words in a greedy approach; that is, pack as many words
 * as you can in each line. Pad extra spaces ' ' when necessary so that each
 * line has exactly L characters.
 * 
 * 
 * 
 * Extra spaces between words should be distributed as evenly as possible. If
 * the number of spaces on a line do not divide evenly between words, the empty
 * slots on the left will be assigned more spaces than the slots on the
 * right.
 * 
 * 
 * 
 * For the last line of text, it should be left justified and no extra space is
 * inserted between words.
 * 
 * 
 * 
 * For example,
 * words: ["This", "is", "an", "example", "of", "text", "justification."]
 * L: 16.
 * 
 * 
 * 
 * Return the formatted lines as:
 * 
 * [
 * ⁠  "This    is    an",
 * ⁠  "example  of text",
 * ⁠  "justification.  "
 * ]
 * 
 * 
 * 
 * 
 * Note: Each word is guaranteed not to exceed L in length.
 * 
 * 
 * 
 * click to show corner cases.
 * 
 * Corner Cases:
 * 
 * 
 * A line other than the last line might contain only one word. What should you
 * do in this case?
 * In this case, that line should be left-justified.
 * 
 * 
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** fullJustify(char** words, int wordsSize, int maxWidth, int* returnSize) {
    if (wordsSize <= 0) {
        *returnSize = 0;
        return NULL;
    }
    char** result = (char*)malloc(sizeof(char*)*wordsSize);
    *returnSize = 0;
    for (int i = 0; i < wordsSize; ) {
        int len_words = strlen(words[i]);
        int len_empty = 0;
        int j;
        for (j = i + 1; j < wordsSize; ++j) {
            int temp = strlen(words[j]);
            if (len_words + len_empty + 1 + temp > maxWidth)
                break;
            len_words += temp;
            ++len_empty;
        }
        result[*returnSize] = (char*)malloc(sizeof(char)*(maxWidth+1));
        int k = 0;
        if (j == wordsSize) {
            while (i < wordsSize) {
                for (j = 0; words[i][j] != '\0'; ++j)
                    result[*returnSize][k++] = words[i][j];
                result[*returnSize][k++] = ' ';
                ++i;
            }
            while (k < maxWidth)
                result[*returnSize][k++] = ' ';
            result[(*returnSize)++][maxWidth] = '\0';
            break;
        }
        int len_count = j - i - 1;
        len_empty = maxWidth - len_words;
        while (i < j) {
            for (int index = 0; words[i][index] != '\0'; ++index)
                result[*returnSize][k++] = words[i][index];
            if (len_count != 0) {    
                int len_current_empty = len_empty / len_count + (len_empty % len_count != 0);
                for (int index = 0; index < len_current_empty; ++index)
                    result[*returnSize][k++] = ' ';
                --len_count;
                len_empty -= len_current_empty;
            }
            ++i;
        }
        while (k < maxWidth)
            result[*returnSize][k++] = ' ';
        result[(*returnSize)++][k] = '\0';
    }
    return result;
}

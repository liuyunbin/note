#include <iostream>

using namespace std;

class String {
   private:
    char p[81];

   public:
    String() {
        for (int i = 0; i != 15; ++i) p[i] = 'a' + i;
        p[15] = 'a';
        p[16] = 'a';
        p[17] = 'a';
        p[18] = '\0';
    }

    bool check_c(const int& k, const char& c) const {
        if (p[k] == '\0')
            return false;
        else
            return p[k] == c ? true : check_c(k + 1, c);
    }

    int count_c(const int& k, const char& c) const {
        if (p[k] == '\0')
            return 0;
        else
            return (p[k] == c ? 1 : 0) + count_c(k + 1, c);
    }

    void delete_c(const int& k, const char& c, int count) {
        if (p[k] == '\0')
            p[k - count] = '\0';
        else {
            if (p[k] == c)
                ++count;
            else
                p[k - count] = p[k];

            delete_c(k + 1, c, count);
        }
    }

    void print() const {
        for (int i = 0; p[i] != '\0'; ++i) cout << p[i];
        cout << endl;
    }
};

int main() {
    String st;
    char c = 'a';
    if (st.check_c(0, c))
        cout << "´æÔÚ" << endl;
    else
        cout << "²»´æÔÚ" << endl;
    cout << st.count_c(0, c) << endl;
    st.delete_c(0, c, 0);
    st.print();

    return 0;
}
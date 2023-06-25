#include <iostream>

using namespace std;

class String {
   private:
    char p[81];

   public:
    String() {
        for (int i = 0; i != 10; ++i) p[i] = 'a' + i;
        p[10] = 'a';
        p[11] = '\0';
    }

    bool check_c(const char& c) const {
        bool bo = false;
        for (int i = 0; p[i] != '\0'; ++i)
            if (p[i] == c) {
                bo = true;
                break;
            }
        return bo;
    }

    int count_c(const char& c) const {
        int count = 0;
        for (int i = 0; p[i] != '\0'; ++i)
            if (p[i] == c) ++count;
        return count;
    }

    void delete_c(const char& c) {
        int count = 0;
        int i = 0;
        while (p[i] != '\0') {
            if (p[i] == c)
                ++count;
            else
                p[i - count] = p[i];
            ++i;
        }
        p[i - count] = '\0';
    }

    void print() const {
        for (int i = 0; p[i] != '\0'; ++i) cout << p[i];
        cout << endl;
    }
};

int main() {
    String st;
    char c = 'a';
    if (st.check_c(c))
        cout << "´æÔÚ" << endl;
    else
        cout << "²»´æÔÚ" << endl;
    cout << st.count_c(c) << endl;
    st.delete_c(c);
    st.print();

    return 0;
}
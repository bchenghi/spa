#ifndef GUARD_SYNTAX_CHECK_FLAG_H
#define GUARD_SYNTAX_CHECK_FLAG_H

namespace pql {
    class SyntaxCheckFlag {
    public:
        static bool isSyntaxCheck() {
            return flag;
        }
        static void setSyntaxCheckFlag(bool new_flag) {
            flag = new_flag;
        }
    private:
        inline static bool flag;
    };
}

#endif //GUARD_SYNTAX_CHECK_FLAG_H

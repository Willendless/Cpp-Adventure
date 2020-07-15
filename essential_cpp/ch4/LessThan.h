using namespace std;

class LessThan {
public:
    LessThan(int val):_val(val) {}
    int comp_val() const   { return _val; }
    void comp_val(int val) { _val = val; } 
    
    bool operator()(int other) const {
        return other < _val;
    }
private:
    int _val;
};

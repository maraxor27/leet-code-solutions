#include <vector>
#include <iostream>
using namespace std;

#define GRID_SIZE_X 9
#define GRID_SIZE_Y 9
#define SOLVED 0x200
#define VALUE_MASK 0x1ff
#define charToInt(c) (int) (c - 48) 
#define intToChar(i) (char) (i + 48)
#define debug(x,y) cout << "[" << (x) << "," << (y) << "]: " << hex << possibilities_[y][x] << endl;

class Solution {
private:
    struct Position {
        int x, y;
    };

    short possibilities_[GRID_SIZE_X][GRID_SIZE_Y];
    vector<Position> notifications_ = vector<Position>();
public:
    void init(vector<vector<char>>& board) {
        for (int i = 0; i < GRID_SIZE_X; i++) {
            for (int j = 0; j < GRID_SIZE_Y; j++) { 
                switch (board[i][j]) {
                    case '.':
                        possibilities_[i][j] = VALUE_MASK;
                        break;
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        int value = (charToInt(board[i][j]) - 1);
                        possibilities_[i][j] = (1 << value) | SOLVED;
                        break;
                }
            }
        }
    }

    int decode(short value) {
        switch (value & VALUE_MASK) {
            case 0x1:
                return 1;
            case 0x2: 
                return 2;
            case 0x4:
                return 3;
            case 0x8:
                return 4;
            case 0x10:
                return 5;
            case 0x20:
                return 6;
            case 0x40:
                return 7;
            case 0x80:
                return 8;
            case 0x100:
                return 9; 
        }
        cout << "Tried to decode: " << hex << value << endl;
        return 0;
    }

    int countBitSet(short value) {
        value &= VALUE_MASK;
        int count = 0;
        for (int i = 0; i < sizeof(short) * 8; i++) {
            count += value & 1;
            value >>= 1;
        }
        return count;
    }

    short allowedHorizontal(int x, int y) {
        short possibilities = VALUE_MASK;
        for (int i = 0; i < GRID_SIZE_X; i++) {
            if (possibilities_[y][i] & SOLVED) {
                possibilities &= ~(possibilities_[y][i]);
            }
        }
        if (countBitSet(possibilities) == 1) {
            possibilities |= SOLVED;
        }
        return possibilities;
    }

    short allowedVertical(int x, int y) {
        short possibilities = VALUE_MASK;
        for (int i = 0; i < GRID_SIZE_X; i++) {
            if (possibilities_[i][x] & SOLVED) {
                possibilities &= ~(possibilities_[i][x]);
            }
        }
        if (countBitSet(possibilities) == 1) {
            possibilities |= SOLVED;
        }
        return possibilities;
    }

    short allowedZone(int x, int y) {
        short possibilities = VALUE_MASK;
        int base_x = x - (x%3);
        int base_y = y - (y%3);
        // cout << "allowedZone: base(" << base_x << "," << base_y << ")" << endl;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (possibilities_[base_y + j][base_x + i] & SOLVED) {
                    possibilities &= ~(possibilities_[base_y + j][base_x + i]);
                }
            }
        }
        if (countBitSet(possibilities) == 1) {
            possibilities |= SOLVED;
        }
        return possibilities;
    }

    short allowed(int x, int y) {
        short possibilities = 0;
        // cout << "allowed (" << x << "," << y << ")" << endl;
        short h_possibilities = allowedHorizontal(x, y);
        if (h_possibilities & SOLVED) return h_possibilities;
        possibilities = h_possibilities;
        // cout << "h_possibilities: " << hex << h_possibilities << endl;

        short v_possibilities = allowedVertical(x, y);
        if (v_possibilities & SOLVED) return v_possibilities;
        possibilities &= v_possibilities;
        // cout << "v_possibilities: " << hex << v_possibilities << endl;

        short z_possibilities = allowedZone(x, y);
        if (z_possibilities & SOLVED) return z_possibilities;
        possibilities &= z_possibilities;
        // cout << "z_possibilities: " << hex << z_possibilities << endl;

        if (countBitSet(possibilities) == 1) {
            possibilities |= SOLVED;
        }
        return possibilities;
    }
    
    bool notifyHorizontal(int x, int y, short value) {
        for (int i = 0; i < GRID_SIZE_X; i++) {
            if (i == x) {
                continue;
            }
            possibilities_[y][i] &= ~value;
            // debug(i,y)
            int count = countBitSet(possibilities_[y][i] & VALUE_MASK);
            if (count == 1 && !(possibilities_[y][i] & SOLVED)) {
                possibilities_[y][i] |= SOLVED;
                notifications_.push_back({i, y});
            } else if (count == 0) {
                cout << "Failed";
                debug(i, y)
                return false;
            }
        }
        return true;
    }

    bool notifyVertical(int x, int y, short value) {
        for (int i = 0; i < GRID_SIZE_Y; i++) {
            if (i == y) {
                continue;
            }
            possibilities_[i][x] &= ~value;
            // debug(x,i)
            int count = countBitSet(possibilities_[i][x]);
            if (count == 1 && !(possibilities_[i][x] & SOLVED)) {
                possibilities_[i][x] |= SOLVED;
                notifications_.push_back({x, i});
            } else if (count == 0) {
                cout << "Failed";
                debug(x, i)
                return false;
            }
        }
        return true;
    }

    bool notifyZone(int x, int y, short value) {
        int base_x = x - (x%3);
        int base_y = y - (y%3);
        // cout << "notifyZone base: (" << base_x << ", " << base_y << ")" << endl;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (possibilities_[base_y + j][base_x + i] & SOLVED) {
                    continue;
                }
                possibilities_[base_y + j][base_x + i] &= ~value;
                // debug(base_x + i, base_y + j)
                int count = countBitSet(possibilities_[base_y + j][base_x + i] & VALUE_MASK);
                if (count == 1 && !(possibilities_[base_y + j][base_x + i] & SOLVED)) {
                    possibilities_[base_y + j][base_x + i] |= SOLVED;
                    notifications_.push_back({base_x + i, base_y + j});
                } else if (count == 0) {
                    cout << "Failed";
                    debug(base_x + i, base_y + j)
                    return false;
                }
            }
        }
        return true;
    }
    
    bool notify(Position notifitication) {
        short value = possibilities_[notifitication.y][notifitication.x] & VALUE_MASK;
        if (!notifyHorizontal(notifitication.x, notifitication.y, value)) {
            return false;
        }
        if (!notifyVertical(notifitication.x, notifitication.y, value)) {
            return false;
        }
        if (!notifyZone(notifitication.x, notifitication.y, value)) {
            return false;
        }
        return true;
    }

        short byEliminationHorizontal(int x, int y) {
        short others = 0;
        for (int i = 0; i < GRID_SIZE_X; i++) {
            if (i == x) {
                continue;
            }
            others |= possibilities_[y][i];
        }
        cout << "byEliminationHorizontal: " << hex << (others & VALUE_MASK) << endl;
        return others & VALUE_MASK;
    }

    short byEliminationVertical(int x, int y) {
        short others = 0;
        for (int i = 0; i < GRID_SIZE_Y; i++) {
            if (i == y) {
                continue;
            }
            others |= possibilities_[i][x];
        }
        cout << "byEliminationVertical: " << hex << (others & VALUE_MASK) << endl;
        return others & VALUE_MASK;
    }

    short byEliminationZone(int x, int y) {
        short others = 0;
        int base_x = x - (x%3);
        int base_y = y - (y%3);
        // cout << "allowedZone: base(" << base_x << "," << base_y << ")" << endl;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (base_x + i == x && base_y + j == y) {
                    continue;
                }
                others |= possibilities_[base_y + j][base_x + i];
            }
        }
        cout << "byEliminationZone: " << hex << (others & VALUE_MASK) << endl;
        return others & VALUE_MASK;
    }

    short byElimination(int x, int y) {
        short possibilities = possibilities_[y][x];
        short horizontal = ~byEliminationHorizontal(x, y);
        short vertical = ~byEliminationVertical(x, y);
        short zone = ~byEliminationZone(x, y);
        
        if (possibilities & horizontal & vertical & zone) {
            possibilities &= horizontal & vertical & zone;
        } else if (possibilities & horizontal & vertical) {
            possibilities &= horizontal & vertical;
        } else if (possibilities & horizontal & zone) {
            possibilities &= horizontal & zone;
        } else if (possibilities & vertical & zone) {
            possibilities &= vertical & zone;
        } else if (possibilities & horizontal) {
            possibilities &= horizontal;
        } else if (possibilities & vertical) {
            possibilities &= vertical;
        } else if (possibilities & zone) {
            possibilities &= zone;
        }

        if (countBitSet(possibilities) == 1) {
            possibilities |= SOLVED;
            return possibilities;
        }
        return possibilities;
    }

    void print() {
        for (int y = 0; y < GRID_SIZE_Y; y++) {
            for (int x = 0; x < GRID_SIZE_X; x++) { 
                if (possibilities_[y][x] & SOLVED) {
                    cout << decode(possibilities_[y][x]) << "!! ";
                } else {
                    short value = possibilities_[y][x];
                    cout << hex << ((value >> 8) & 0x1) << ((value >> 4) & 0xf) << ((value) & 0xf) << " ";
                }
            }
            cout << endl;
        }
    }

    void solve() {
        for (int y = 0; y < GRID_SIZE_Y; y++) {
            for (int x = 0; x < GRID_SIZE_X; x++) { 
                if (!(possibilities_[y][x] & SOLVED)) {
                    short possibilities = allowed(x, y);
                    possibilities_[y][x] = possibilities;
                    // debug(x, y)
                    if (possibilities & SOLVED) {
                        notifications_.push_back({x, y});
                    }
                }
            }
        }
        print();
        cout << "Done with first pass" << endl;
        if (!SolveWithBacktracking()) {
            cout << "Couldn't solve for current state!" << endl;
        }
    }

    void copyState(short* src, short* dst) {
        // cout << "copyState start" << endl;
        for (int i = 0; i < GRID_SIZE_X * GRID_SIZE_Y; i++) {
            dst[i] = src[i];
        }
        // cout << "copyState end" << endl;
    }

    bool SolveWithBacktracking(int layer = 0) {
        cout << "Backtracking layer: " << layer << endl;
        while (!isDone() && !notifications_.empty()) {
            cout << "switch to Notification" << endl;
            while (!notifications_.empty()) {
                Position notification = notifications_[notifications_.size() - 1];
                notifications_.pop_back();
                // cout << "Notification<x:" << notification.x << ", y: " << notification.y << ">" << endl;
                if (!notify(notification)) {
                    notifications_.clear();
                    return false;
                }
                // print();            
            }
            if (isDone()) {
                break;
            }
            cout << "switch to ByElimination" << endl;
            for (int y = 0; y < GRID_SIZE_Y; y++) {
                for (int x = 0; x < GRID_SIZE_X; x++) { 
                    if (!(possibilities_[y][x] & SOLVED)) {
                        short possibilities = byElimination(x, y);
                        debug(x, y)
                        cout << "byElimination: " << hex << possibilities << endl;
                        if (possibilities) {
                            possibilities_[y][x] = possibilities;
                            debug(x, y)
                            if (possibilities & SOLVED) {
                                notifications_.push_back({x, y});
                            }
                        }
                    }
                }
            }
            if (notifications_.empty()) {
                break;
            }
        }
        if (!isDone() && layer > 2) {
            cout << "too deep!!!" << endl;
            return false;
        } else if (!isDone()) {
            cout << "switch to Backtracking" << endl;
            for (int y = 0; y < GRID_SIZE_Y; y++) {
                for (int x = 0; x < GRID_SIZE_X; x++) { 
                    if (!(possibilities_[y][x] & SOLVED)) {
                        for (int i = 0; i < 9; i++) {
                            if (!(possibilities_[y][x] & (1 << i))) {
                                continue;
                            }
                            short save_state[GRID_SIZE_Y][GRID_SIZE_X];
                            copyState((short*) possibilities_, (short*) save_state);
                            
                            // Apply Assumption
                            possibilities_[y][x] = (1 << i) | SOLVED;
                            notifications_.push_back({x, y});

                            cout << "Assumption: ";
                            debug(x, y)
                            print();

                            if (!SolveWithBacktracking(layer + 1)) {
                                copyState((short*) save_state, (short*) possibilities_);
                                continue;
                            }

                            if (isDone()) {

                                return true;
                            }

                            copyState((short*) save_state, (short*) possibilities_);
                        }
                    }
                }
            }
        }
        return true;
    }

    bool isDone() {
        for (int x = 0; x < GRID_SIZE_X; x++) {
            for (int y = 0; y < GRID_SIZE_Y; y++) { 
                if (!(possibilities_[y][x] & SOLVED)) {
                    return false;
                }
            }
        }
        return true;
    }

    void apply(vector<vector<char>>& board) {
        for (int i = 0; i < GRID_SIZE_X; i++) {
            for (int j = 0; j < GRID_SIZE_Y; j++) { 
                if (board[i][j] == '.') {
                    board[i][j] = intToChar(decode(possibilities_[i][j]));
                }
            }
        }
    }

    void solveSudoku(vector<vector<char>>& board) {
        cout << "--- Starting ---" << endl;
        init(board);
        solve();
        if (!isDone()) {
            cout << "Soduku is not solved!" << endl;
            print();
        } else {
            cout << "Soduku is solved!" << endl;
            print();
        }
        apply(board);
    }
};
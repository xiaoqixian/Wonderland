/**********************************************
  > File Name		: TextEditor.cpp
  > Author		    : lunar
  > Email			: lunar_ubuntu@qq.com
  > Created Time	: Thu Aug 11 11:03:47 2022
  > Location        : Shanghai
  > Copyright@ https://github.com/xiaoqixian
 **********************************************/

#include <list>
#include <string>
#include <iostream>
using namespace std;

class TextEditor {
private:
    list<string> editor;
    list<string>::iterator cursor;
    int offset;

    struct Result {
        list<string>::iterator it;
        int offset, walk_len;

        Result(list<string>::iterator it, int offset, int k): it(it), offset(offset), walk_len(k) {}
    };

    Result _moveLeft(int k) const {
        if (this->editor.empty()) {
            assert(this->cursor == this->editor.end());
            return Result(this->cursor, 0, 0);
        }

        auto _start = this->cursor;
        const auto _begin = this->editor.begin();
        int _offset = this->offset;
        const int target = k;

        while (k && _start != _begin) {
            if (k < _offset) {
                _offset -= k;
                k = 0;
            } else {
                k -= _offset;
                _start--;
                _offset = _start->size();
            }
        }

        if (k) {
            if (_offset >= k) {
                _offset -= k;
                k = 0;
            } else {
                k -= _offset;
                _offset = 0;
            }
        }

        if (_offset == 0 && _start != this->editor.begin()) {
            _start--;
            _offset = _start->size();
        }

        return Result(_start, _offset, target-k);
    }

    Result _moveRight(int k) const {
        if (this->cursor == this->editor.end()) {
            return Result(this->cursor, 0, 0);
        }

        auto _stop = this->cursor;
        const auto _end = this->editor.end();
        int _offset = this->offset;
        const int target = k;

        while (k && _stop != _end) {
            const int _size = _stop->size();
            if (_offset + k > _size) {
                k -= _size - _offset;
                _stop++;
                _offset = 0;
            } else {
                _offset += k;
                k = 0;
            }
        }

        if (_offset == 0 && _stop != this->editor.begin()) {
            _stop--;
            _offset = _stop->size();
        }

        return Result(_stop, _offset, target-k);
    }

    string _getLeft() const {
        if (this->cursor == this->editor.begin() && this->offset == 0) return "";
        auto _res = _moveLeft(10);

        //format(_res.it, _res.offset);
        //format();

        auto _start = _res.it;
        int _offset = _res.offset;

        if (_start == this->cursor) {
            assert(_offset <= this->offset);
            assert(this->cursor != this->editor.end());
            return this->cursor->substr(_offset, this->offset-_offset);
        }

        string res = "";

        while (_start != this->cursor) {
            res += _start->substr(_offset);
            _offset = 0;
            _start++;
        }

        if (this->cursor != this->editor.end()) {
            res += this->cursor->substr(0, this->offset);
        }

        return res;
    }
public:
    TextEditor() {
        this->cursor = this->editor.end();
        this->offset = 0;
    }
    
    void addText(string text) {
        if (this->cursor == this->editor.end()) {
            this->editor.push_back(std::move(text));
            this->cursor = this->editor.begin();
            this->offset = this->cursor->size();
            return;
        }

        if (this->cursor == this->editor.begin() && this->offset == 0) {
            this->editor.push_front(std::move(text));
            this->cursor = this->editor.begin();
            this->offset = this->cursor->size();
            format();
            return;
        }

        assert(offset != 0);

        if (offset == this->cursor->size()) {
            this->cursor++;
            this->cursor = this->editor.insert(this->cursor, std::move(text));
            this->offset = this->cursor->size();
            return;
        }

        string remain = this->cursor->substr(offset);
        this->cursor->resize(offset);

        this->cursor++;
        this->cursor = this->editor.insert(this->cursor, text);
        
        this->cursor++;
        this->cursor = this->editor.insert(this->cursor, remain);
        this->cursor--;
        this->offset = this->cursor->size();
    }
    
    int deleteText(int k) {
        auto _res = _moveLeft(k);
        if (_res.walk_len == 0) return 0;

        string remain = _res.it->substr(0, _res.offset) + this->cursor->substr(offset);

        this->cursor++;
        this->cursor = this->editor.erase(_res.it, this->cursor);
        this->offset = 0;

        if (remain.size()) {
            this->cursor = this->editor.insert(this->cursor, remain);
            this->offset = _res.offset;
        } else if (!this->editor.empty() && this->cursor != this->editor.begin()) {
            this->cursor--;
            this->offset = this->cursor->size();
        }

        return _res.walk_len;
    }
    
    string cursorLeft(int k) {
        auto _res = _moveLeft(k);
        if (k && _res.walk_len == 0) return "";

        this->cursor = _res.it;
        this->offset = _res.offset;

        return _getLeft();
    }
    
    string cursorRight(int k) {
        auto _res = _moveRight(k);
        
        this->cursor = _res.it;
        this->offset = _res.offset;

        return _getLeft();
    }

    void format() const {
        cout << "[format]: this->cursor(" << (this->cursor == this->editor.end() ? "" : *this->cursor) << "), this->offset = " << this->offset << endl;
    }

    void format(list<string>::iterator it, int o) const {
        cout << "[custom format]: this->cursor(" << (it == this->editor.end() ? "" : *it) << "), this->offset = " << o << endl;
    }
};

int main() {
//["Textthis->editor","addText","deleteText","addText","this->cursorLeft","addText","deleteText","addText","this->cursorLeft","deleteText"]
//[[],["arnvmumatgmyw"],[5],["zrlufuifuy"],[2],["unh"],[20],["kwwp"],[6],[9]]

    TextEditor te;
    te.addText("arnvmumatgmyw");
    cout << te.deleteText(5) << endl;
    te.addText("zrlufuifuy");
    cout << te.cursorLeft(2) << endl;
    te.addText("unh");
    cout << te.deleteText(20) << endl;
    te.addText("kwwp");
    cout << te.cursorLeft(6) << endl;
    cout << te.cursorLeft(9) << endl;
    //cout << te.deleteText(8) << endl;
    //te.addText("cqw");
    //te.addText("vybokrmbiumkyyqtyiso");
    //te.format();
    //cout << te.this->cursorRight(20) << endl;
    //te.addText("uggyesnznnbntaa");
}

